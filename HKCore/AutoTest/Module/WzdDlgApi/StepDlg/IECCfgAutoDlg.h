#pragma once
#include "../StepCtrl/WzdDlgButton.h"
#include "../../../iSmartTestWzd/Resource.h"
#include <vector>

class CIECAutoBtnObj : public CExBaseObject
{
public:
	CExBaseList m_oDatas;

	CIECAutoBtnObj()
	{
		m_oDatas.RemoveAll();
	}
	virtual ~CIECAutoBtnObj() {}
};

class CIECAutoBtn : public CWzdDlgNormalBtn
{
public:
	long m_nType;
	enum
	{
		NORMAL,
		CURRENT,
		SAVE,
		CURRENTSAVE
	};

public:
	CExBaseObject* m_pData;
	CIECAutoBtn(){ m_pData = NULL; m_nType = NORMAL; }
	virtual ~CIECAutoBtn() {}

public:
	virtual void LButtonUp(UINT nFlags, CPoint point);
	virtual void SetCurrentType(long nType);
};

class CIECCfgAutoLine
{
public:
	std::vector<CExBaseObject*> m_vecElements; 

	virtual ~CIECCfgAutoLine(){ m_vecElements.clear(); }
};

class CIECCfgAutoGrid
{
public:
	std::vector<CIECCfgAutoLine> m_vecLines;

	virtual ~CIECCfgAutoGrid(){}
};

class CSmvIecfgDataMngrSelDlg : public CDialog
{
	DECLARE_DYNCREATE(CSmvIecfgDataMngrSelDlg)

private:
	CExBaseList* m_pList;
	long m_nMaxWidth;
	long m_nMaxHeight;

	std::vector<CIECAutoBtn*> m_vecBtns;
	CIECCfgAutoGrid m_oBtnsGrid;
	CFont* m_pFont;

	BOOL m_bBtnsHasShow;

public:
	enum { IDD = IDD_IECCFG_AUTO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	BOOL AddToLine(CExBaseObject* pObj, long nIndex);
	void AddButton(CExBaseObject* pObj);
	void AutoShowBtns();
	void ClearBtnTypes();

public:
	CSmvIecfgDataMngrSelDlg(CWnd* pParent = NULL);
	virtual ~CSmvIecfgDataMngrSelDlg();

	void UpdateBbns();
	void AttachDatas(CExBaseList* pList);
	BOOL Create(CWnd* pParentWnd);
	BOOL Exit();
	void SetFont(CFont* pFont) { m_pFont = pFont; }

	void SetBtnType(CString strName, long nType);

	//20230620 huangliang 
	void XUI_InitAdjust();

	HRESULT OnClickBtn(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

