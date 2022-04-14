#pragma once

#include <windef.h>

class IModule
{
public:
	virtual ~IModule() {}

public:
	virtual void Regist() = 0;
	virtual void Unregist() = 0;

	virtual void FrameStart() = 0;
	virtual void FrameEnd() = 0;
};

