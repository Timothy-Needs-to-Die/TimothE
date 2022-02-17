#pragma once

class IStream;

//Pure virtual class, anything that needs to be saved needs to use this class.
class ISerializable {
public:
	virtual ~ISerializable() {};
	virtual bool SaveState(IStream& stream) const = 0;
	virtual bool LoadState(IStream& stream) = 0;
};
