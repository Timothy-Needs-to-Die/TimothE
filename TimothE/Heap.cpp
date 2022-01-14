#include "Heap.h"

#include "MemoryManager.h"
#include <iostream>

Heap::Heap(std::string name) : _currentlyAllocated(0), _peak(0), _name(name) {}

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
	header->_pNext = pHead;
	if (pHead != NULL)
		pHead->_pPrev = header;
	pHead = header;
}

void Heap::DeallocateMemory(Header* header, int size)
{
	//Remove the total allocation
	_currentlyAllocated -= size;

	//Find what elements need to be changed around to allow this element to be removed in the doubly linked list
	if (pHead == header) {
		pHead = header->_pNext;
	}
	if (header->_pNext != NULL) {
		header->_pNext->_pPrev = header->_pPrev;
	}
	if (header->_pPrev != NULL) {
		header->_pPrev->_pNext = header->_pNext;
	}
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

void Heap::DisplayDebugInformation()
{
	//Outputs the name of this heap
	std::cout << "Name: " << _name << std::endl;
	std::cout << "____________________________________________" << std::endl;

	//if we have a head
	if (pHead != NULL) {
		//Output the total allocated and the peak memory
		//Outputs a nice layout for the debug information
		std::cout << "Current memory: " << _currentlyAllocated << "\tPeak memory: " << _peak << std::endl;
		std::cout << "____________________________________________" << std::endl;
		std::cout << "ADDRESS\t\t\tTYPE\t\tSIZE" << std::endl;
		std::cout << "____________________________________________" << std::endl;

		//Stores the size of the header
		size_t hSize = sizeof(Header);

		//Gets the current head of the list
		Header* pCurrent = pHead;
		//While the current exists
		while (pCurrent != NULL)
		{
			if (pCurrent == NULL) break;
			auto& startMem = *(pCurrent + hSize);
			std::cout << &startMem << "\t" << typeid(startMem).name() << "\t" << pCurrent->size << std::endl;
			if (pCurrent->_pNext == NULL) {
				break;
			}

			//Cycle through to the next element of the list
			pCurrent = pCurrent->_pNext;
		}

		std::cout << std::endl;
	}
	else {
		//outputs the total and peak memory allocated if we do not have a head
		std::cout << "Current memory: " << _currentlyAllocated << "\tPeak memory: " << _peak << std::endl;
	}

	std::cout << std::endl;
}

void Heap::CheckIntegrity()
{
	std::cout << "Checking integrity of " << _name << std::endl;

	bool errorFound = false;
	int totalErrors = 0;

	if (pHead != NULL) {
		//Start at the current head of the list
		Header* pCurrent = pHead;

		//while our current head is not null
		while (pCurrent != NULL) {
			//Check we have the correct check code
			if (pCurrent->checkCode != deadcode) {
				std::cout << "[ERROR: Heap::CheckIntegrity]: Header check code does not match" << std::endl;
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
		std::cout << "[ERROR: Heap::CheckIntegrity]: Error(s) found: " << totalErrors << std::endl;
	}
	else {
		std::cout << "[MESSAGE: Heap::CheckIntegrity]: No Errors found in " << _name << std::endl;
	}
}
