#pragma once
//	Pointer

//	* std::function
#include <functional>

template <typename T> class Pointer;
template <typename T> class Unique_Pointer;
template <typename T> class Shared_Pointer;
template <typename T> class Auto_Pointer;


///////////////////////////////////////////////////////////////////////////////
//	Interface Of Pointer
class IPointer
{
public:
	virtual ~IPointer() noexcept {}

public:
	virtual void* getAddress() = 0;
	virtual unsigned int getSize() const = 0;
};


///////////////////////////////////////////////////////////////////////////////
//	Pointer Base (Pointer Class의 기본적인 기능)
template <typename T> class PointerBase : public IPointer
{
public:		// Operator
	T * operator->();
	T & operator*();

public:		// Functions
	void* getAddress() override;
	unsigned int getSize() const override;

	inline const T * get() { return object; }
	template <typename CastType>
	inline const CastType * get() { return static_cast<CastType*>(object); }

protected:	// Protected Functions
	//	execute before alloc
	virtual void new_execute(unsigned int allocSize) noexcept {}
	//	execute before free
	virtual void delete_execute() noexcept {}

protected:	// Protected Constructor
	PointerBase() noexcept : object(nullptr) {}

protected:	// Protected Annihilator
	virtual ~PointerBase() noexcept {}

protected:	// Protected Field
	T * object;
};

///////////////////////////////////////////////////////////////////////////////
//	New / Delete Function Class (object 의 할당에 관해서 기본 할당 , 커스텀 할당을 나눈 기능들)

//	Custom New Delete Pointer Base ( malloc | func / free | func )
template <typename T> class CustomNewDeletePointerBase : public PointerBase<T>
{
protected:
	virtual ~CustomNewDeletePointerBase() noexcept {}

public:
	//	* Must do not 'alloc' in constructor of T
	template <typename NewT>
	void new_(const NewT& value, std::function<void*(unsigned int)> alloc_func = malloc) noexcept;

	//	* Must do not 'free' in annihilator of T
	void delete_(std::function<void(void*)> free_func = free) noexcept;
};

//	Default New Delete Pointer Base ( malloc / free )
template <typename T> class DefaultNewDeletePointerBase : public PointerBase<T>
{
protected:
	virtual ~DefaultNewDeletePointerBase() noexcept {}

public:
	//	* Must do not 'alloc' in constructor of T
	template <typename NewT>
	void new_(const NewT& value) noexcept;

	//	* Must do not 'free' in annihilator of T
	void delete_() noexcept;
};

///////////////////////////////////////////////////////////////////////////////
//	Default Pointer (기본적인 Pointer Class , object 공유를 할 수 있지만 참조 카운터가 없다. 커스텀 할당이 가능)
template <typename T> class Pointer : public CustomNewDeletePointerBase<T>
{
public:		// Constructor
	Pointer() noexcept :PointerBase<T>() {}
	Pointer(const Pointer& copyOther) noexcept;
	Pointer(Pointer&& moveOther) noexcept;

public:		// Annihilator
	virtual ~Pointer() noexcept {}

public:		// Operator
	const Pointer& operator=(const Pointer& assignmentOther);
	T * operator=(T * addressOther);
};

template <> class Pointer<void>
{ };


///////////////////////////////////////////////////////////////////////////////
//	Unique Pointer (유니크 Pointer Class , object 공유가 불가능하다. 커스텀 할당이 가능)
template <typename T> class Unique_Pointer : public CustomNewDeletePointerBase<T>
{
public:		// Constructor
	Unique_Pointer() noexcept : PointerBase<T>() {}

public:		// Annihilator
	virtual ~Unique_Pointer() noexcept {}

private:	// Private Constructor
	Unique_Pointer(const Unique_Pointer& copyOther) {}
	Unique_Pointer(Unique_Pointer&& moveOther) {}

private:	// Private Operator
	const Unique_Pointer& operator=(const Unique_Pointer& assignmentOther) {}
};

template <> class Unique_Pointer<void>
{ };


///////////////////////////////////////////////////////////////////////////////
//	Shared Pointer (공유 Pointer Class , object 공유가 가능하다. 카운터가 있어 자동 삭제에 편하다. 기본 할당만 가능)
template <typename T> class Shared_Pointer : public DefaultNewDeletePointerBase<T>
{
public:		// Constructor
	Shared_Pointer() noexcept : PointerBase<T>(), shared_count(nullptr) {}
	Shared_Pointer(const Shared_Pointer& copyOther) noexcept;
	Shared_Pointer(Shared_Pointer&& moveOther) noexcept;

public:		// Annihilator
	virtual ~Shared_Pointer() noexcept;

public:		// Operator
	const Shared_Pointer& operator=(const Shared_Pointer& assignmentOther);

public:		// Functions
	void release();

protected:	// Protected Functions
	//	execute before alloc
	void new_execute(unsigned int allocSize) noexcept override;
	//	execute before free
	void delete_execute() noexcept override;


private:	// Private Functions
	void addRef();
	void subRef();

private:	// Private Field
	unsigned int * shared_count;
};

template <> class Shared_Pointer<void>
{ };


///////////////////////////////////////////////////////////////////////////////
//	Auto Pointer (자동 Pointer Class , object 공유가 불가능하다. 해당 개체가 있는 지역을 벗어날때 자동으로 삭제된다. 기본 할당만 가능)
template <typename T> class Auto_Pointer : public DefaultNewDeletePointerBase<T>
{
public:		// Constructor 
	Auto_Pointer() noexcept : PointerBase<T>() {}

public:		// Annihilator
	virtual ~Auto_Pointer() noexcept;

private:	// Private Constructor
	Auto_Pointer(const Auto_Pointer& copyOther) {}
	Auto_Pointer(Auto_Pointer&& moveOther) {}

private:	// Private Operator
	const Auto_Pointer& operator=(const Auto_Pointer& assignmentOther) {}
};

template <> class Auto_Pointer<void>
{ };


#include "Memory\Source\PointerImpl.h"

