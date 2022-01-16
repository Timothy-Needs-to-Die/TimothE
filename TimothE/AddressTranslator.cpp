#include "AddressTranslator.h"

void AddressTranslator::AddAddress(void* oldAddress, void* newAddress)
{
	_table[(int)oldAddress] = (int)newAddress;
}

void* AddressTranslator::TranslateAddress(void* oldAddress)
{
	AddressTable::iterator it = _table.find((int)oldAddress);
	if (it == _table.end()) return NULL;

	return (void*)(*it).second;
}

void AddressTranslator::Reset()
{
	_table.clear();
}

AddressTranslator::AddressTable AddressTranslator::_table;
