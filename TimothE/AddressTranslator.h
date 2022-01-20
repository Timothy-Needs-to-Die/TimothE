#pragma once

#include <unordered_map>

class AddressTranslator
{
public:
	static void AddAddress(void* oldAddress, void* newAddress);
	static void* TranslateAddress(void* oldAddress);
	static void Reset();

private:
	typedef std::unordered_map<int, int> AddressTable;
	static AddressTable _table;
};

