
#pragma once

class CXDrawBaseInterface_ViewWindow
{
public:
	virtual void ViewToWindow(CPoint &point) = 0;
	virtual void WindowToView(CPoint &point) = 0;

	virtual void ViewToWindow(CRect &rect) = 0;
	virtual void WindowToView(CRect &rect) = 0;
};

