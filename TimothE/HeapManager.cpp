#include "HeapManager.h"

Heap& HeapManager::GetDefaultHeap()
{
	return defaultHeap;
}

Heap* HeapManager::CreateHeap(std::string name)
{
	//Creates the heap
	Heap* heap = new Heap(name);
	//Inserts the heap into the heapMap
	heapMap.insert(std::make_pair(name, heap));
	return heap;
}

Heap* HeapManager::GetHeap(std::string name)
{
	return heapMap[name];
}

void HeapManager::CleanHeaps()
{
	heapMap.clear();

	//No need to delete defaultHeap or heapMap as they are created on the stack and therefore
	//deleted on program shutdown
}

void HeapManager::DebugAll()
{
	//Iterates over the heapMap and displays debug information and checks the integrity
	std::unordered_map<std::string, Heap*>::const_iterator it;
	for (it = heapMap.begin(); it != heapMap.end(); it++) {
		it->second->DisplayDebugInformation();
		it->second->CheckIntegrity();
	}

	//Default heap debug and integrity
	defaultHeap.DisplayDebugInformation();
	defaultHeap.CheckIntegrity();
}

//Static initializations of the default heap and the heap map
Heap HeapManager::defaultHeap = Heap("DefaultHeap");
std::unordered_map<std::string, Heap*> HeapManager::heapMap;


