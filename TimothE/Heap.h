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

	//Methods for displaying debug information about the project
	void DisplayDebugInformation();
	void CheckIntegrity();

	void GetTreeStats(size_t& totalBytes, size_t& totalPeak, int& totalInstances);

	int ReportMemoryLeaks(int bookmark1, int bookmark2);
	static int GetMemoryBookmark();

	Heap(const Heap&) = default;
	Heap& operator=(const Heap&) = default;

	void AttachTo(Heap* pParent);

	void PrintInfo(int indentLevel = 0);
	void PrintTreeInfo(int indentLevel = 0);

private:
	int _currentlyAllocated;
	int _peak;
	std::string _name;

	static int _numberOfAllocations;
	int _instances;

	Heap* _pParent = NULL;
	Heap* _pFirstChild = NULL;
	Heap* _pNextSibling = NULL;
	Heap* _pPrevSibling = NULL;

};

