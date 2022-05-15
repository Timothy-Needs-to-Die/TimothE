#include "pch.h"
#include "MemoryManager.h"
#include <iostream>

void* operator new(size_t size, Heap* heap)
{
	//Calculates the required bytes
	size_t requestedBytes = size + sizeof(Header);
	//Allocates the required bytes and returns the starting memory pointer
	char* pMem = (char*)malloc(requestedBytes);

	//Casts the memory to a header object
	Header* pHeader = (Header*)pMem;
	//Sets the heap for this header
	pHeader->_pHeap = heap;

	//Allocates memory for the heap (handles the linked list)
	heap->AllocateMemory(pHeader, size);
	
	//Gets the start of the usable memory block
	void* pStartMemBlock = pMem + sizeof(Header);
	return pStartMemBlock;
}

void* operator new[](size_t size, Heap* heap)
{
	//Gets the requested bytes needed
	size_t requestedBytes = size + sizeof(Header);
	//Allocates the memory and returns the pointer to the start of the block
	char* pMem = (char*)malloc(requestedBytes);

	//Sets the header at the start of this block
	Header* pHeader = (Header*)pMem;
	pHeader->_pHeap = heap;

	heap->AllocateMemory(pHeader, size);

	//Gets and returns the start of the usable memory block
	void* pStartMemBlock = pMem + sizeof(Header);
	return pStartMemBlock;
}

void* operator new[](size_t size)
{
	//Gets the default heap if a heap is not specified
	return ::operator new[](size, &HeapManager::GetDefaultHeap());
}

void* operator new(size_t size)
{
	//Gets the default heap if a heap is not specified
	return ::operator new(size, &HeapManager::GetDefaultHeap());
}

void operator delete(void* pMem)
{
	//Gets the location of the header memory
	Header* pHeader = (Header*)((char*)pMem - sizeof(Header));

	//Checks if our dead codes match up in the header and footer
	if (pHeader->checkCode != deadcode) {
		TIM_LOG_ERROR("Header check code does not match");
	}

	//Deallocates the memory from the heap (handles the linked list)
	pHeader->_pHeap->DeallocateMemory(pHeader, pHeader->size);

	free(pHeader);
}
