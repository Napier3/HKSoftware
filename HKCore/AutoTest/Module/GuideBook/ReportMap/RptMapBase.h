#pragma once

//�������� ��������ӳ���ļ�

#include "RptData.h"

class CRptMapBase : public CExBaseList
{
public:
	CRptMapBase(void);
	virtual ~CRptMapBase(void);

protected:
	//ΪFindBkmk���ã�
	CExBaseObject* FindBkmkInList(const CString&  strBkmk,CExBaseList* pList);

//�����ӿ�
public:
	CExBaseObject* FindBkmk(const CString  &strBkmk);
	void InsertBkmk(const CString  &strBkmk);
	CExBaseObject* FindItemByID(const CString  &strID);//���Բ��ҵ���Items��Item��Datas��Data
	CExBaseObject* FindItem(long nIndex);
	
	CRptData* AddNewRptData(const CString  &strName, const CString  &strID, const CString &strPrecision);
public:
	BOOL HasBkmk();
	void ClearDWData();
};


//CExBaseObject* _FindTheItemByID(CExBaseList *pList, CString strID);