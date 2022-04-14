#pragma once
#include "Pointer.h"


//	* malloc
//	* free
#include <stdlib.h>


//	* memset
#include <string>

//	* assert
#include <assert.h>


///////////////////////////////////////////////////////////////////////////////
//	Pointer Base

template<typename T>
inline T * PointerBase<T>::operator->()
{
	return (this->object);
}

template<typename T>
inline T & PointerBase<T>::operator*()
{
	return *(this->object);
}

template<typename T>
void * PointerBase<T>::getAddress()
{
	return (void*)(this->object);
}

template<typename T>
unsigned int PointerBase<T>::getSize() const
{
	return sizeof(T);
}



///////////////////////////////////////////////////////////////////////////////
//	Custom New Delete Pointer Base

template<typename T>
template<typename NewT>
void CustomNewDeletePointerBase<T>::new_(const NewT & value, std::function<void*(unsigned int)> alloc_func) noexcept
{
	unsigned int size = sizeof(value);
	this->new_execute(size);

	if (alloc_func == nullptr)
		this->object = (T*)malloc(size);
	else
		this->object = (T*)alloc_func(size);

	memcpy(this->object, &value, size);
}

template<typename T>
void CustomNewDeletePointerBase<T>::delete_(std::function<void(void*)> free_func) noexcept
{
	this->delete_execute();

	this->object->~T();

	if (free_func == nullptr)
		free(this->object);
	else
		free_func(this->object);

	this->object = nullptr;
}



///////////////////////////////////////////////////////////////////////////////
//	Default New Delete Pointer Base

template<typename T>
template<typename NewT>
void DefaultNewDeletePointerBase<T>::new_(const NewT & value) noexcept
{
	unsigned int size = sizeof(value);
	this->new_execute(size);

	//	alloc
	this->object = (T*)malloc(size);
	memcpy(this->object, &value, size);
}

template<typename T> 
void DefaultNewDeletePointerBase<T>::delete_() noexcept
{
	this->delete_execute();

	//	free
	delete (this->object);
	this->object = nullptr;
}



///////////////////////////////////////////////////////////////////////////////
//	Default Pointer

template<typename T>
Pointer<T>::Pointer(const Pointer & copyOther) noexcept
	:object(copyOther.object)
{
	// ...
}

template<typename T>
Pointer<T>::Pointer(Pointer && moveOther) noexcept
	: object(moveOther.object)
{
	moveOther.object = nullptr;
}

template<typename T>
inline const Pointer<T> & Pointer<T>::operator=(const Pointer & assignmentOther)
{
	object = assignmentOther.object;
	return *this;
}

template<typename T>
inline T * Pointer<T>::operator=(T * addressOther)
{
	this->object = addressOther;
	return this->object;
}



///////////////////////////////////////////////////////////////////////////////
//	Unique Pointer

//	...



///////////////////////////////////////////////////////////////////////////////
//	Shared Pointer

template<typename T>
Shared_Pointer<T>::Shared_Pointer(const Shared_Pointer & copyOther) noexcept
{
	this->subRef();

	this->shared_count = copyOther.shared_count;
	this->object = copyOther.object;

	this->addRef();
}

template<typename T>
Shared_Pointer<T>::Shared_Pointer(Shared_Pointer && moveOther) noexcept
	:object(moveOther.object), shared_count(moveOther.shared_count)
{
	moveOther.object = nullptr;
	moveOther.shared_count = nullptr;
}

template<typename T>
Shared_Pointer<T>::~Shared_Pointer() noexcept
{
	this->subRef();
}

template<typename T>
inline const Shared_Pointer<T> & Shared_Pointer<T>::operator=(const Shared_Pointer & assignmentOther)
{
	this->subRef();

	this->shared_count = assignmentOther.shared_count;
	this->object = assignmentOther.object;

	this->addRef();

	return *this;
}

template<typename T>
void Shared_Pointer<T>::release()
{
	this->subRef();

	this->object = nullptr;
	this->shared_count = nullptr;
}

template<typename T>
void Shared_Pointer<T>::new_execute(unsigned int allocSize) noexcept
{
	this->shared_count = new unsigned int(1);
}

template<typename T>
void Shared_Pointer<T>::delete_execute() noexcept
{
	if ((*this->shared_count) > 1)
		assert(false && " < CRITICAL > : Another pointer is sharing the same object.");

	delete (this->shared_count);
	this->shared_count = nullptr;
}

template<typename T>
inline void Shared_Pointer<T>::addRef()
{
	if (this->shared_count == nullptr)
		return;

	(*this->shared_count)++;
}

template<typename T>
inline void Shared_Pointer<T>::subRef()
{
	if (this->shared_count == nullptr)
		return;

	(*this->shared_count)--;

	if ((*this->shared_count) <= 0)
	{
		delete (this->object);
		delete (this->shared_count);

		this->object = nullptr;
		this->shared_count = nullptr;
	}
}



///////////////////////////////////////////////////////////////////////////////
//	Auto Pointer

template<typename T>
Auto_Pointer<T>::~Auto_Pointer() noexcept
{
	if (this->object != nullptr)
	{
		delete (this->object);
	}
}


