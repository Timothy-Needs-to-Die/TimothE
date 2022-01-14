#pragma once

#include "Heap.h"
#include <unordered_map>

class HeapManager
{
public:
	//Returns the default heap
	static Heap& GetDefaultHeap();

	//Creates a heap and returns it
	static Heap* CreateHeap(std::string name);

	//Gets a heap by name
	static Heap* GetHeap(std::string name);

	//Deletes all heaps
	static void CleanHeaps();

	//Debugs all heaps
	static void DebugAll();

private:
	static Heap defaultHeap;
	static std::unordered_map<std::string, Heap*> heapMap;
};

