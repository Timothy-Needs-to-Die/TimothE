#pragma once

#include "Heap.h"
#include <unordered_map>

class HeapManager
{
public:
	static void Init();

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

	//Gets the amount of allocations
	static int GetMemoryBookmark();

	static void ReportMemoryLeaks(int bookmark);


	static void ReportMemoryLeaks(int bookmark1, int bookmark2);

private:
	static Heap _defaultHeap;
	static std::unordered_map<std::string, Heap*> _heapMap;
};

