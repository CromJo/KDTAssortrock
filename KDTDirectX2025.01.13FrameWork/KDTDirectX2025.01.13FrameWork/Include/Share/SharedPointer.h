#pragma once

class CSharedPointer
{
public:
	CSharedPointer();
	CSharedPointer(class CObject* Obj);
	CSharedPointer(const CSharedPointer& Ptr);
	CSharedPointer(CSharedPointer&& Ptr);

	~CSharedPointer();

public:
	void operator = (class CObject* Obj);
	void operator = (const CSharedPointer& Ptr);
	void operator = (CSharedPointer&& Ptr);
	
	bool operator == (class CObject* Obj)			const;
	bool operator == (const CSharedPointer& Ptr)	const;
	bool operator == (CSharedPointer&& Ptr)			const;
	
	bool operator != (class CObject* Obj)			const;
	bool operator != (const CSharedPointer& Ptr)	const;
	bool operator != (CSharedPointer&& Ptr)			const;

	class CObject* operator -> () const;
	operator class CObject* () const;

	class CObject* Get() const;

private:
	class CObject* mObj = nullptr;

};

