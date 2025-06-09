#pragma once

#include "ProtocolGlobalDef.h"
#include "..\..\..\..\Module\System\VariantData.h"

class CBbInffor : public CExBaseObject
{
public:
	CBbInffor(const CString &strID, BYTE &val, long nDxBegin, long nDxEnd);
	CBbInffor(const CString &strID, short &val, long nDxBegin, long nDxEnd);
	CBbInffor(const CString &strID, WORD &val, long nDxBegin, long nDxEnd);
	CBbInffor(const CString &strID, DWORD &val, long nDxBegin, long nDxEnd);
	CBbInffor(const CString &strID, long &val, long nDxBegin, long nDxEnd);
	CBbInffor(const CString &strID, float &val, long nDxBegin, long nDxEnd);
	CBbInffor(const CString &strID, double &val, long nDxBegin, long nDxEnd);
	CBbInffor(const CString &strID, const CString &val);
// 	CBbInffor(const CString &strID, TIME64 &val, long nDxBegin, long nDxEnd);
	virtual ~CBbInffor(void);

//属性
public:
	long m_nDxBegin;
	long m_nDxEnd;
	CVariantData m_var;
	
protected:
	
public:
	//基本方法
	virtual UINT GetClassID(){return STPROTOCOLCLASSID_BBINFOR;};

	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

	virtual void GetBbInfor(CString &strInfor);
	virtual void GetBbInforVal(CString &strInfor, CString &strDesc);
};
