#pragma once
#include "../WzdDlgDef.h"
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../Module/WndGroupMngr/XUIAutoAdjTool.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CWzdDlgBase : public CDialog, public CExBaseObject, public CXUIAdjItem_Area
{
	DECLARE_DYNAMIC(CWzdDlgBase)
protected:
	BOOL m_bIsActived;
	BOOL m_bIsEnabled;

	CDataGroup* m_pDataCfg;
	CBrush m_oBkBrush;

	CString m_strErrorLog;

public:
	CWzdDlgBase(UINT nIDTemplate, CWnd* pParent = NULL);
	virtual ~CWzdDlgBase();

protected:
	virtual void XUI_InitAdjust();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	virtual void XmlToUI(CEdit* pEdit, CDvmData* pDvmData, CButton* pCheckBox = 0);
	virtual void XmlToUI(CComboBox* pComboBox, CDvmData* pDvmData);
	virtual CDvmData* ParseUIXml(CDataGroup* pDataGroup, const CString& strID);
	virtual CDvmValue* ParseUIXml(CDvmData* pDvmData, const CString& strID);
	virtual void UIToXml() {}

public:
	BOOL IsActived();
	void SetActived(BOOL bActive);
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnable);
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual void SetParentWnd(CWnd* pWnd);
	virtual CWnd* GetParentWnd();
	virtual BOOL InitUI(CDataGroup* pDataGroup);
	virtual BOOL DoNext();
	virtual BOOL DoNextForThead();
	virtual BOOL DoPrev();
	virtual CString GetErrorLog() { return m_strErrorLog; }
	virtual void OnWindowPosChanging() {}
	DECLARE_MESSAGE_MAP()
};