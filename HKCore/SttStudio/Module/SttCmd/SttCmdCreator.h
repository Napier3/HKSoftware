//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdCreator.h  CSttCmdCreator

#pragma once

#include "SttCmdDefineGlobal.h"

class CSttCmdCreator : public CExBaseList
{
public:
	CSttCmdCreator();
	virtual ~CSttCmdCreator();

//重载函数
public:
	CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	CExBaseObject* SttCmdCreate(const CString &strCmdXml);
};

