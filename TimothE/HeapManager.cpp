#include "HeapManager.h"

void HeapManager::Init()
{
	_heapMap.insert(std::make_pair("DefaultHeap", &_defaultHeap));
}

Heap& HeapManager::GetDefaultHeap()
{
	return _defaultHeap;
}

Heap* HeapManager::CreateHeap(std::string name)
{
	//Creates the heap
	Heap* heap = new Heap(name);
	//Inserts the heap into the heapMap
	_heapMap.insert(std::make_pair(name, heap));
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
		it->second->DisplayDebugInformation();
		it->second->CheckIntegrity();
	}

	//Default heap debug and integrity
	_defaultHeap.DisplayDebugInformation();
	_defaultHeap.CheckIntegrity();
}

int HeapManager::GetMemoryBookmark()
{
	return Heap::GetMemoryBookmark();
}

void HeapManager::ReportMemoryLeaks(int bookmark)
{
	ReportMemoryLeaks(bookmark, GetMemoryBookmark());
}

void HeapManager::ReportMemoryLeaks(int bookmark1, int bookmark2)
{
	int nLeaks = 0;
	std::unordered_map<std::string, Heap*>::iterator it;
	for (it = _heapMap.begin(); it != _heapMap.end(); it++) {
		nLeaks += it->second->ReportMemoryLeaks(bookmark1, bookmark2);
	}

	if (nLeaks > 0)
		printf("%d memory leaks found\n", nLeaks);
	else
		printf("No memory leaks detected.\n");
}

//Static initializations of the default heap and the heap map
Heap HeapManager::_defaultHeap = Heap("DefaultHeap");
std::unordered_map<std::string, Heap*> HeapManager::_heapMap;


