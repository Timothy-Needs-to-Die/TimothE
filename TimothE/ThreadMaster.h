#pragma once
#include "pch.h"

class ThreadMaster
{
public:
	ThreadMaster(int workerCount) : _lk{ _mtx }, _workerCount(workerCount)
	{

	}

	void SignalDone() {
		{
			std::lock_guard lk{ _mtx };
			++_doneCount;
		}

		if (_doneCount == _workerCount) {
			_cv.notify_one();
		}
	}

	void WaitForAllDone() {
		_cv.wait(_lk, [this] {return _doneCount == _workerCount; });
		_doneCount = 0;
	}

private:
	std::condition_variable _cv;
	std::mutex _mtx;
	std::unique_lock<std::mutex> _lk;
	int _workerCount;

	//Shared Mem
	int _doneCount = 0;
};

