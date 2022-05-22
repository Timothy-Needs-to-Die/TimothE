#pragma once
#include "Heap.h"
#include "HeapManager.h"
#include "Core.h"

#define deadcode 0xDEADC0DE

struct Header {
	//Size of the allocation
	int size;

	//Checkcode for error checking
	int checkCode = deadcode;

	//Heap this allocation belongs to
	Heap* _pHeap;

	//The next header in the linked list
	Header* _pNext = NULL;
	//The previous header in the linked list
	Header* _pPrev = NULL;

	//the allocation number assigned to this allocation, can help track memory leaks
	int allocationNumber = 0;
};


void* operator new(size_t size, Heap* heap);
void* operator new[](size_t size, Heap* heap);
void* operator new[](size_t size);
void* operator new(size_t size);
void operator delete (void* pMem);
