//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
