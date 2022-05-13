#include "Tag.h"

std::string Tag::_tags[32];

void Tag::AddTag(const std::string& tagName)
{
	for (int i = 0; i < 31; i++)
	{
		if (_tags[i].empty()) {
			_tags[i] = tagName;
			std::cout << "Tag Added: " << tagName << std::endl;
			return;
		}
		//If all tags are filled
		if (!_tags[31].empty()) {
			std::cout << "Tag Array full, remove tags to add more" << std::endl;
		}

	}
}

void Tag::RemoveTag(const std::string& tagName) 
{
	for (int i = 0; i < 31; i++)
	{
		if (_tags[i] == tagName) {
			_tags[i].clear();
			return;
		}
		if (_tags[31] != tagName) {
			std::cout << "Could not remove tag, not found in array" << std::endl;
		}
	}
}

bool Tag::CheckTag(const std::string& tagName)
{
	for (int i = 0; i < 31; i++)
	{
		if (_tags[i] == tagName) {
			std::cout << "Tag Found " << std::endl;
			return true;
		}
	}
}

void Tag::PrintTags()
{
	for (int i = 0; i < 31; i++)
	{
		std::cout << "Tag: " << i << _tags[i] << std::endl;
	}
}
