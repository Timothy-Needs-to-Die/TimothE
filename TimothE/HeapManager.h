#pragma once

#include "Heap.h"
#include <unordered_map>
#include <iostream>

class HeapManager
{
public:
	//Creates the root heap and attaches the default to the root
	static void Init();

	//Returns the default heap
	static Heap& GetDefaultHeap();

	//Creates a heap and returns it
	static Heap* CreateHeap(std::string name, std::string parent);

	//Gets a heap by name
	static Heap* GetHeap(std::string name);

	//Deletes all heaps
	static void CleanHeaps();

	//Debugs all heaps
	static void DebugAll();

	//Gets the amount of allocations
	static int GetMemoryBookmark();

	//Reports memory leaks between the passed in bookmark and the current state of memory
	static void ReportMemoryLeaks(int bookmark);

	//Reports any memory leaks between the two passed in bookmarks
	static void ReportMemoryLeaks(int bookmark1, int bookmark2);

	//Prints all information about the memory manager
	static void PrintInfo();

	//Gets the root heap for the project
	static Heap* GetRootHeap();

private:
	static Heap _defaultHeap;
	static Heap* _pRootHeap;
	static std::unordered_map<std::string, Heap*> _heapMap;
};

