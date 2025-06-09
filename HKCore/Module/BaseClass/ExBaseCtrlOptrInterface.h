#pragma once

#include "ExBaseList.h"

//2019-4-20   ���
//���еĺ�������ǰ׺��Optr_������Ϊ����֮ǰ�Ѿ�����õ�ExBase*�ؼ�����ĺ������֣������ͻ
class CExBaseCtrlOptrInterface
{
public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE) = 0;
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;

	virtual void Optr_UpdateDataIndex()	{	};
};

