#pragma once

class CSharedPointer
{
public:
	CSharedPointer();
	CSharedPointer(class CObject* Object);
	CSharedPointer(const CSharedPointer& Pointer);
	CSharedPointer(CSharedPointer&& Pointer);
	~CSharedPointer();

public:
	void operator = (class CObject* Object);
	void operator = (const CSharedPointer& Pointer);
	void operator = (CSharedPointer&& Pointer);

	bool operator == (class CObject* Object) const;
	bool operator == (const CSharedPointer& Pointer) const;
	bool operator == (CSharedPointer&& Pointer) const;

	bool operator != (class CObject* Object) const;
	bool operator != (const CSharedPointer& Pointer) const;
	bool operator != (CSharedPointer&& Pointer) const;

	class CObject* operator -> () const;
	operator class CObject* () const;
	
	class CObject* Get() const;

private:
	class CObject* mObject = nullptr;
};

