#pragma once

#include "ExBaseList.h"

//2019-4-20   李俊庆
//所有的函数增加前缀“Optr_”，是为了与之前已经定义好的ExBase*控件对象的函数区分，避免冲突
class CExBaseCtrlOptrInterface
{
public:
	virtual BOOL Optr_InsertData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;
	virtual BOOL Optr_UpdateData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;
	virtual BOOL Optr_DeleteData(CExBaseObject *pData, BOOL bSelectOther=TRUE, BOOL bInvalidate=TRUE) = 0;
	virtual BOOL Optr_SetCurrSelData(CExBaseObject *pData, BOOL bInvalidate=TRUE) = 0;

	virtual void Optr_UpdateDataIndex()	{	};
};

