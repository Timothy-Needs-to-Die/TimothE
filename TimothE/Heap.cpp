#include "pch.h"
#include "Heap.h"

#include "MemoryManager.h"
#include <iostream>
#include <cassert>

Heap::Heap(std::string name) : _currentlyAllocated(0), _peak(0), _name(name), _instances(0) {}

void Heap::AttachTo(Heap* pParent)
{
	//Check we have a parent
	assert(pParent != NULL);

	//if the passed in heap is the same as our parent return
	if (pParent == _pParent)
		return;

	// First detach from its current parent
	//Step 1: Disconnect from previous sibling
	if (_pPrevSibling != NULL)
		_pPrevSibling->_pNextSibling = _pNextSibling;
	//Step 2: Disconnect from next sibling
	if (_pNextSibling != NULL)
		_pNextSibling->_pPrevSibling = _pPrevSibling;
	//Step 3: Disconnect from main parent by setting the new first child
	if (_pParent != NULL)
		if (_pParent->_pFirstChild == this)
			_pParent->_pFirstChild = _pNextSibling;

	// Now attach itself to the new parent
	_pNextSibling = pParent->_pFirstChild;
	_pPrevSibling = NULL;
	_pParent = pParent;
	pParent->_pFirstChild = this;
}

void Heap::PrintInfo(int indentLevel /*= 0*/)
{
	//Outputs the spaces for the passed in indent level
	for (int i = 0; i < indentLevel; ++i)
		std::cout << "  ";

	//Create variables to store the tree stats
	size_t totalBytes = 0;
	size_t totalPeakBytes = 0;
	int totalInstances = 0;
	GetTreeStats(totalBytes, totalPeakBytes, totalInstances);

	int spacing = 20 - indentLevel * 2;
	//Nice formatting for the data %-*s sets the width of the name field area
	printf("%-*s %6d %6d %5d  %6d %6d %5d\n",
		spacing, _name,
		_currentlyAllocated, _peak, _instances,
		totalBytes, totalPeakBytes, totalInstances);
}

void Heap::PrintTreeInfo(int indentLevel /*= 0*/)
{
	//Prints the info for the base level of this heap
	PrintInfo(indentLevel);
	//If we have children
	Heap* pChild = _pFirstChild;
	while (pChild != NULL)
	{
		//Print the children's information
		pChild->PrintTreeInfo(indentLevel + 1);
		//Set our current child to the sibling
		pChild = pChild->_pNextSibling;
	}
}

void Heap::AllocateMemory(Header* header, int size)
{
	//Adds memory to total allocated
	_currentlyAllocated += size;
	//if total allocated is now greater than the peak, then set the new peak
	if (_currentlyAllocated > _peak) _peak = _currentlyAllocated;

	//Set the size of this allocation
	header->size = size;
	//Set the check code in debug mode only
	header->checkCode = deadcode;

	//Setup the previous and next elements in the doubly linked list
	header->_pPrev = NULL;
	header->_pNext = _pHead;
	if (_pHead != NULL)
		_pHead->_pPrev = header;
	_pHead = header;

	header->allocationNumber = ++_numberOfAllocations;
	_instances++;
}

void Heap::DeallocateMemory(Header* header, int size)
{
	//Remove the total allocation
	_currentlyAllocated -= size;

	//Find what elements need to be changed around to allow this element to be removed in the doubly linked list
	if (_pHead == header) {
		_pHead = header->_pNext;
	}
	if (header->_pNext != NULL) {
		header->_pNext->_pPrev = header->_pPrev;
	}
	if (header->_pPrev != NULL) {
		header->_pPrev->_pNext = header->_pNext;
	}
	_instances--;
}

int Heap::GetAmountAllocated()
{
	return _currentlyAllocated;
}

void* Heap::operator new(size_t size)
{
	//Allocate the amount of size required for the memory block
	void* pMem = (void*)malloc(size);
	return pMem;
}

void Heap::CheckIntegrity()
{
	std::cout << "Checking integrity of " << _name << std::endl;

	bool errorFound = false;
	int totalErrors = 0;

	if (_pHead != NULL) {
		//Start at the current head of the list
		Header* pCurrent = _pHead;

		//while our current head is not null
		while (pCurrent != NULL) {
			//Check we have the correct check code
			if (pCurrent->checkCode != deadcode) {
				TIM_LOG_ERROR("Header check code does not match");
				errorFound = true;
				totalErrors++;
			}

			//Get the address of the footer
			void* pFooterAddr = ((char*)pCurrent + sizeof(Header) + pCurrent->size);

			//Set current to the next element in the linked list
			pCurrent = pCurrent->_pNext;
		}
	}

	if (errorFound) {
		TIM_LOG_ERROR("Error(s) found: " << totalErrors);
	}
	else {
		TIM_LOG_ERROR("No errors found in " << _name);
	}
}

void Heap::GetTreeStats(size_t& totalBytes, size_t& totalPeak, int& totalInstances)
{
	//Adds the heaps stats to the passed in references
	totalBytes += _currentlyAllocated;
	totalPeak += _peak;
	totalInstances += _instances;

	//Gets our child and cycles through all our trees children and siblings
	Heap* pChild = _pFirstChild;
	while (pChild != NULL)
	{
		//Gets the tree stats
		pChild->GetTreeStats(totalBytes, totalPeak, totalInstances);
		//Sets the child to the next sibling
		pChild = pChild->_pNextSibling;
	}
}

int Heap::ReportMemoryLeaks(int bookmark1, int bookmark2)
{
	int nLeaks = 0;
	size_t hSize = sizeof(Header);
	Header* pHeader = _pHead;
	while (pHeader != NULL)
	{
		//Checks if our current allocations is greater than the allocations at bookmark 1 and less than the allocations in bookmark 2
		if (pHeader->allocationNumber >= bookmark1 &&
			pHeader->allocationNumber < bookmark2)
		{
			auto& address = *(pHeader + hSize);
			std::cout << "Leak in " << _name << ". Size: " << pHeader->size << ". Address: " << &address << std::endl;
			nLeaks++;
		}
		//Go to the next header
		pHeader = pHeader->_pNext;
	}
	return nLeaks;
}

int Heap::GetMemoryBookmark()
{
	//Gets the amount of allocations at this point in time
	return _numberOfAllocations;
}

int Heap::_numberOfAllocations = 1;