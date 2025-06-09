#pragma once


// CParaDialog

class CAudioDlgBase : public CDialog
{

public:
	CAudioDlgBase(int nID,CWnd* pParent = NULL);
	virtual ~CAudioDlgBase();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	void SetResult(CString& strResult);
	CString GetResult();
	void SetListCtrl(CListCtrl*	pListCtrl);
	CListCtrl* GetListCtrl();
	int GetCurrentSelectRow();
	void SetRowHightLight(int nRow,int nLastRow = -1);
 
	virtual void SetCurrentResult(){m_strResult = "";};
	virtual CString GetCurrentResult();
	virtual void SetListData(CDvmData* pData);
	virtual void SetBackPage();
	virtual void SetNextPage();
	virtual void SetListSelectRow(int nRow,int nLastRow = -1);
	virtual void FindSelectAnswer(CString strResult);
	virtual bool DealAnswer(CString strResult = ""){return false;};

public:
	CString		m_strResult;

	CListCtrl*	m_pListCtrl;
	int m_nScollMin;
	int m_nScollMax;
	int m_nPageStep;
	int m_nCurrentPagePos;

	//int	m_nListStateFlag;
};


