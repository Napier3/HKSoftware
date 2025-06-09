#pragma once

#include "..\EpGlobalDefine.h"
#include "..\..\System\VariantDataAddress.h"

class CEpBbInffor : public CExBaseObject
{
public:
	CEpBbInffor(const CString &strID, BYTE &val, long nDxBegin, long nDxEnd);
	CEpBbInffor(const CString &strID, short &val, long nDxBegin, long nDxEnd);
	CEpBbInffor(const CString &strID, long &val, long nDxBegin, long nDxEnd);
	CEpBbInffor(const CString &strID, float &val, long nDxBegin, long nDxEnd);
	CEpBbInffor(const CString &strID, double &val, long nDxBegin, long nDxEnd);
	CEpBbInffor(const CString &strID, EPTIME64 &val, long nDxBegin, long nDxEnd);
	virtual ~CEpBbInffor(void);

//属性
public:
	long m_nDxBegin;
	long m_nDxEnd;
	CVariantDataAddress m_var;
	
protected:
	
public:
	//基本方法
	virtual UINT GetClassID(){return EPCLASSID_BBINFOR;};

	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

	virtual void GetBbInfor(CString &strInfor);
	virtual void GetBbInforVal(CString &strInfor, CString &strDesc);
};
