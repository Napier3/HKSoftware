#pragma once
#include "../GuideBook/GuideBookInterface.h"

#define COMMCMD_ATTR_ROW_MAXREAD   8
#define COMMCMD_ATTR_ROW_TIMEGAP    9

class CCommCmdAttrGrid :	public CListCtrl
{
		DECLARE_DYNAMIC(CCommCmdAttrGrid)

public:
	CCommCmdAttrGrid(void);
	~CCommCmdAttrGrid(void);

	void CreateGrid(CWnd *pParent, CRect rcWnd, UINT nID);
	void ShowCommCmdAttr(CExBaseObject *pItem);
	void ShowAttr(const CString &strName,const CString &strValue, long nAttrIndex=-1);

	void ShowAttr(const CString &strName,long nValue, long nAttrIndex=-1);
	void ShowAttr(const CString &strName,float fValue, long nAttrIndex=-1);
	void ShowAttr(const CString &strName,double dValue, long nAttrIndex=-1);

protected:
	CExBaseObject* m_pCurrItem;
	long m_nCurrRowIndex;
};
