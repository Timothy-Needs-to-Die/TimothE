#pragma once

class IStream;

class ISerializable {
public:
	virtual ~ISerializable() {};
	virtual bool SaveState(IStream& stream) const = 0;
	virtual bool LoadState(IStream& stream) = 0;
};
