#pragma once

class IRenderable
{
public:
	virtual void Render() = 0;
	virtual void SetVisible(bool visible) = 0;
};
