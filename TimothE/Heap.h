#pragma once
#include <string>

struct Header;

class Heap
{
public:
	//Stores the name of the heap
	Heap(std::string name);
	//Handle the linked list and total allocated
	void AllocateMemory(Header* header, int size);
	//Handle the linked list and total allocated
	void DeallocateMemory(Header* header, int size);
	int GetAmountAllocated();
	std::string GetName() const { return _name; }

	//Class specific new override, heaps don't need to have a header or footer for themselves.
	void* operator new (size_t size);

	//The head of the linked list
	Header* _pHead = NULL;

	//Checks the integrity of this heap
	void CheckIntegrity();

	//Gets some information about this heap tree
	void GetTreeStats(size_t& totalBytes, size_t& totalPeak, int& totalInstances);

	//A way to say how many leaks there are in this heap
	int ReportMemoryLeaks(int bookmark1, int bookmark2);
	//Gets the current amount of allocations 
	static int GetMemoryBookmark();

	//Default contstructors for the copy and assignment constructors
	Heap(const Heap&) = default;
	Heap& operator=(const Heap&) = default;

	//Attaches this heap the passed in parent
	void AttachTo(Heap* pParent);

	//Prints information about the heap
	void PrintInfo(int indentLevel = 0);
	void PrintTreeInfo(int indentLevel = 0);

private:
	//Stores the current amount of memory allocated to it and the peak amount of memory allocated at any given time
	int _currentlyAllocated;
	int _peak;
	//Stores the heaps name
	std::string _name;

	//Number of allocations
	static int _numberOfAllocations;

	int _instances;

	//Parent heap
	Heap* _pParent = NULL;
	//First child heap
	Heap* _pFirstChild = NULL;
	//Siblings of this heap
	Heap* _pNextSibling = NULL;
	Heap* _pPrevSibling = NULL;

};

