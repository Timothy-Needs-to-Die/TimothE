#include "pch.h"
#include "HeapManager.h"

void HeapManager::Init()
{
	_heapMap.insert(std::make_pair("Default", &_defaultHeap));
	_heapMap.insert(std::make_pair("Root", _pRootHeap));
	_defaultHeap.AttachTo(_pRootHeap);
}

Heap& HeapManager::GetDefaultHeap()
{
	return _defaultHeap;
}

Heap* HeapManager::CreateHeap(std::string name, std::string parent)
{
	Heap* pParent = _heapMap[parent];
	if (pParent == NULL) {
		pParent = new Heap(parent);
		pParent->AttachTo(_pRootHeap);
	}

	//Creates the heap
	Heap* heap = new Heap(name);
	//Inserts the heap into the heapMap
	_heapMap.insert(std::make_pair(name, heap));

	//Attach the new heap to the parent
	heap->AttachTo(pParent);

	return heap;
}

Heap* HeapManager::GetHeap(std::string name)
{
	return _heapMap[name];
}

void HeapManager::CleanHeaps()
{
	_heapMap.clear();

	//No need to delete defaultHeap or heapMap as they are created on the stack and therefore
	//deleted on program shutdown
}

void HeapManager::DebugAll()
{
	//Iterates over the heapMap and displays debug information and checks the integrity
	std::unordered_map<std::string, Heap*>::const_iterator it;
	for (it = _heapMap.begin(); it != _heapMap.end(); it++) {
		it->second->CheckIntegrity();
	}

	//Default heap debug and integrity
	_defaultHeap.CheckIntegrity();
}

int HeapManager::GetMemoryBookmark()
{
	//Gets a memory bookmark of the heap
	return Heap::GetMemoryBookmark();
}

void HeapManager::ReportMemoryLeaks(int bookmark)
{
	//Reports memory leaks between the passed in bookmark and current state of memory.
	ReportMemoryLeaks(bookmark, GetMemoryBookmark());
}

void HeapManager::ReportMemoryLeaks(int bookmark1, int bookmark2)
{
	int nLeaks = 0;
	//Iterates over every heap in the heapmap and checks for leaks
	std::unordered_map<std::string, Heap*>::iterator it;
	for (it = _heapMap.begin(); it != _heapMap.end(); it++) {
		nLeaks += it->second->ReportMemoryLeaks(bookmark1, bookmark2);
	}

	if (nLeaks > 0)
		std::cout << nLeaks << " memory leaks found" << std::endl;
	else
		std::cout << "No memory leaks detected." << std::endl;
}

Heap* HeapManager::GetRootHeap()
{
	if (_pRootHeap == NULL) {
		Init();
	}
	return _pRootHeap;
}

void HeapManager::PrintInfo()
{
	std::cout << "MEMORY INFORMATION" << std::endl;
	std::cout << "\t\t\tLocal\t\t\tTotal" << std::endl;
	std::cout << "Name\t\tMemory\tPeak\tInst\tMemory\tPeak\tInst" << std::endl;
	//Starts a recursive call of printing all information
	GetRootHeap()->PrintTreeInfo(0);
	std::cout << std::endl;
}

//Static initializations of the default heap and the heap map
Heap HeapManager::_defaultHeap = Heap("Default");
Heap* HeapManager::_pRootHeap = new Heap("Root");
std::unordered_map<std::string, Heap*> HeapManager::_heapMap;


