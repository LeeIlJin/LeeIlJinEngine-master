#pragma once

class IUpdatable
{
public:
	virtual void Update() = 0;
	virtual void SetActive(bool active) = 0;
};
