#pragma once
#include "pch.h"
#include "ThreadMaster.h"


class ThreadWorker
{
public:
	ThreadWorker(ThreadMaster* pMaster) :
		_pMaster(pMaster), _thread{ &ThreadWorker::Run, this }
	{

	}

	~ThreadWorker() {
		_thread.join();
	}

	void SetJob(std::function<void()> task, std::function<void()> finished) {
		{
			std::lock_guard lk{ _mtx };

			_task = task;
			_callbackFunc = finished;
		}
		_cv.notify_one();
	}

	void Kill() {
		{
			std::lock_guard lk{ _mtx };
			_dying = true;
		}
		_cv.notify_one();
	}

private:
	void Run() {
		std::unique_lock lk{ _mtx };
		while (true) {
			_cv.wait(lk, [this] {return _task != nullptr || _dying == true; });

			if (_dying) {
				break;
			}

			_task();
			_callbackFunc;

			_task = {};
			_callbackFunc = {};

			_pMaster->SignalDone();
		}
	}

	ThreadMaster* _pMaster;
	std::thread _thread;
	std::condition_variable _cv;
	std::mutex _mtx;


	std::function<void()> _task;
	std::function<void()> _callbackFunc;

	//shared memory
	bool _dying = false;
};

