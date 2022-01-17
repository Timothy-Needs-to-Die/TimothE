#pragma once

class IStream;

class ISerializable {
public:
	virtual ~ISerializable() {};
	virtual bool Write(IStream& stream) const = 0;
	virtual bool Read(IStream& stream) = 0;
	virtual void Fixup() = 0;
};
