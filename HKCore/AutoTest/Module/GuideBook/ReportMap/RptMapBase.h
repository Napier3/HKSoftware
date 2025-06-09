#pragma once

//功能描述 用来管理映射文件

#include "RptData.h"

class CRptMapBase : public CExBaseList
{
public:
	CRptMapBase(void);
	virtual ~CRptMapBase(void);

protected:
	//为FindBkmk调用；
	CExBaseObject* FindBkmkInList(const CString&  strBkmk,CExBaseList* pList);

//公共接口
public:
	CExBaseObject* FindBkmk(const CString  &strBkmk);
	void InsertBkmk(const CString  &strBkmk);
	CExBaseObject* FindItemByID(const CString  &strID);//可以查找的有Items，Item，Datas，Data
	CExBaseObject* FindItem(long nIndex);
	
	CRptData* AddNewRptData(const CString  &strName, const CString  &strID, const CString &strPrecision);
public:
	BOOL HasBkmk();
	void ClearDWData();
};


//CExBaseObject* _FindTheItemByID(CExBaseList *pList, CString strID);