#pragma once
#include "CommCmdGrid.h"

class CCommCmdGrid_Analogs :	public CCommCmdGrid
{
public:
	CCommCmdGrid_Analogs(void);
	~CCommCmdGrid_Analogs(void);

protected:
		virtual void SaveValue(CExBaseObject *pParaObject, const CString &strValue);

protected:
	virtual CExBaseList* GetDatas();
	virtual BOOL ShowOneObject(CExBaseObject * pParaObject,long &nRow);
};
