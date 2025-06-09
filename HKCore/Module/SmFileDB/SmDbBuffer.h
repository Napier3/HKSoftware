//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbBuffer.h  CSmDbBuffer

#pragma once

#include "SmFileDBGlobal.h"



class CSmDbBuffer : public CExBaseObject
{
public:
	CSmDbBuffer();
	virtual ~CSmDbBuffer();


//重载函数
public:
	virtual UINT GetClassID() {    return SMDBCLASSID_CSMDBBUFFER;   }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

