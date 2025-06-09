#pragma once
#include "XMatchToolBase.h"
#include "XMatchRefObjectSelDlg.h"
#include "XMatchDatasetSelDlg.h"

#define WM_DVMMAPEDIT_KEY_CHANGED  (WM_USER+1015)

class CXMatchEditDvmSelDlgsBase :	public CXMatchRefObjectSelEdit
{
public:
	CXMatchEditDvmSelDlgsBase(void);
	virtual ~CXMatchEditDvmSelDlgsBase(void);

protected:
	CWnd *m_pDlgsParentWnd;
	CXMatchToolBase *m_pXMatchTool;
	static CXMatchRefObjectSelDlg *m_pMatchedDatasDlg;
	static long m_nMatchedDatasDlgRef;

	static CXMatchDatasetSelDlg *m_pAllDatasDlg;
	static long g_nAllDatasDlgRef;

	long m_nShowDataMode;
	BOOL m_bShowID;
	CWnd *m_pDataSelChangeMsgRcvWnd;
	UINT m_nXMatchRefClassID;
	BOOL m_bShowMatchDataChanged;

public:
	virtual void CreateMatchedDatasDlg();
	virtual void CreateAllDatasDlg();

	virtual void AddDatasetsToDlg(CExBaseList *pListAllDataset);
	virtual void ShowAllDatasToDlg(CExBaseList *pDataset=NULL);
	virtual void ShowMatchedDatasToDlg(long nDataIndex);
	virtual void ShowMatchedDatasToDlg(CExBaseList *pListMacthRefs);
	virtual CExBaseObject* GetPopSelectData();
	
public:
	virtual void HideAllDlgs();
};
