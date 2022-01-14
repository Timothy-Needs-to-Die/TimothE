#pragma once
#include "Heap.h"
#include "HeapManager.h"

#define deadcode 0xDEADC0DE

struct Header {
	int size;

	int checkCode = deadcode;

	Heap* _pHeap;
	Header* _pNext = NULL;
	Header* _pPrev = NULL;
};


void* operator new(size_t size, Heap* heap);
void* operator new[](size_t size, Heap* heap);
void* operator new(size_t size);
void operator delete (void* pMem);
