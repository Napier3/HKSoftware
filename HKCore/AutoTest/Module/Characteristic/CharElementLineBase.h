//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLineBase.h  CCharElementLineBase

#pragma once

#include "CharElement.h"



class CCharElementLineBase : public CCharElement, public CXDrawData_Line
{
public:
	CCharElementLineBase();
	virtual ~CCharElementLineBase();

	void GetLine(double &xb, double &yb, double &xe, double &ye);
public:
	virtual void CalTestLines_Plumb();
	virtual void CalTestLines_Vert();
	virtual void CalTestLines_Horz();

	virtual CXDrawDataBase* GetCXDrawDataBase();
	virtual CXDrawBase* CreateDrawElement();

};

