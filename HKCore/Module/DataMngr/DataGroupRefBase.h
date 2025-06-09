//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataGroupRefBase.h  CDataGroupRefBase

#pragma once

#include "DataGroup.h"


class CDataGroupRefBase : public CExBaseList
{
public:
	CDataGroupRefBase(CDataGroup *pRoot);
	CDataGroupRefBase();
	virtual ~CDataGroupRefBase();

	virtual void Attacth(CDataGroup *pRoot);
	virtual void InitAfterAttach(){}
	
protected:
	CDataGroup *m_pRoot;

};
