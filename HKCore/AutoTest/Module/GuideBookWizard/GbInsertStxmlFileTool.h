#pragma once

#include "GbtBatchItem.h"
#include "GbStxmlFileMap.h"
#include "GbtCommCmdEdit.h"

class CGbInsertStxmlFileTool : public CExBaseList
{
public:
	CGbInsertStxmlFileTool();
	virtual ~CGbInsertStxmlFileTool();

	void SetParentWnd(CWnd *pWnd);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL;   }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbInsertStxmlFileToolKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

public:
	CGuideBook *m_pGbStxml;        //子模板对象
	CGuideBook *m_pGuideBookDest;  //目标测试模板对象
//	CWordRptEdit *m_pWordRptEditSrc;
//	CWordRptEdit *m_pWordRptEditDest;
	CRptEditInterface *m_pRptEditSrc;
	CRptEditInterface *m_pRptEditDest;

	CExBaseList *m_pParentItems;
	CXKeyDB *m_pXKeyDB;
	BOOL m_bInsertRootItems;
	CString m_strRootItemsName;
	CString m_strRootItemsID;
	CItems *m_pNewRootItems;
	CExBaseList m_oListNewItems;

	CGbtBatchItemGroups *m_pGbtBatchItemGroups;
	CGbInsertStxmlFileMngr *m_pGbInsertStxmlFileMngr;
	CGbtCommCmdItemEditMngr *m_pGbtCommCmdItemEditMngr;

	CString m_strIec61850ConfigFile;
	CString m_strWzdFile;    //向导使用的映射文件
	long    m_nAddRptGroupTitle;

public:
	BOOL Init(const CString &strStxmlFile);
//	BOOL Init(CGuideBook *pGuideBookDest, CXKeyDB *pKeyDB, CWordRptEdit *pWordRptEditDest);
	BOOL Init(CGuideBook *pGuideBookDest, CXKeyDB *pKeyDB, CRptEditInterface *pRptEditDest);
	void AddDataset(CDataSet *pDataset);
	void ClearListDataset();
	CRptEditInterface* CreateRptEdit();

	//子模板插入到的项目分类对象，如果没有指定，则插入到Device的根目录下
	void SetParentItems(CExBaseList *pParent);
	void XMatch(long nIndex=-1, BOOL bNotUpdateSingle = TRUE, BOOL bNotUpdateNone = FALSE);
	CExBaseObject* ExecInsert();
	CXMatchList* GetXMatchList()	{	return &m_oXMatchList;	}
	CExBaseList* GetRefDatas()		{	return &m_listRefDatas;	}
	CExBaseList* GetRefDatasets()	{	return &m_listDataset;	}
	BOOL IsDatasChanged()			{	return m_bDataChanged;	}
	void SetDataChanged(BOOL bChange)	{	m_bDataChanged = bChange;	}
	BOOL ValidateMapKeys(CString &strErrorMsg);
	BOOL ValidateBatchItemsGroups(CString &strErrorMsg);
	CDevice* GetCurrDeviceDest();

protected:
	CExBaseList m_listDataset;
	CGbWzdDatasetRefMngr *m_pGbWzdDatasetRefMngr;

	CExBaseList m_listRefDatas;
	CXMatchList m_oXMatchList;
	BOOL m_bDataChanged;
	CExBaseList m_oListStxmlItem;  //子模板的全部项目列表，插入时，
	CString m_strStxmlFile;
	CWnd *m_pParentWnd;

	void InitListStxmlItem();
	void InitGbtDataInterfaceMaps();
	void Free();

	void InsertRootItems(CThreadProgressInterface *pThreadProgress);
	void InsertSysParas(CThreadProgressInterface *pThreadProgress);
	void InsertScriptLibLocal(CThreadProgressInterface *pThreadProgress);
	void InsertCharacters(CThreadProgressInterface *pThreadProgress);
	void InsertGlobalDatas(CThreadProgressInterface *pThreadProgress);
	void InsertExtendRptDef(CThreadProgressInterface *pThreadProgress);
	void InsertReportMap(CThreadProgressInterface *pThreadProgress);
//	CExBaseList* GetParentItems();
// 	CItems* InsertByDataterfaceMap(CGbtDataInterfaceMap *pGbtDataInterfaceMap);
	
// 	void InsertStxmlWord(CItems *pCurrItems);
// 	void RenameRptBkmks(CExBaseList *pList);
// 	void RenameRptBkmk(CExBaseObject *pBkmk);


	void InsertByGbtBatchItemGroup(CGbtBatchItemGroup *pBatchGroup, CThreadProgressInterface *pThreadProgress);
//////////////////////////////////////////////////////////////////////////
//插入线程
private:
	CWinThread *m_pInsertThread;
	CThreadProgrssDlg *m_pProgressDlg;
	BOOL m_bExInsertState;

	static UINT ExecInsertThread(LPVOID pParam);
	CExBaseObject* ExecInsertEx(CThreadProgressInterface *pThreadProgress=NULL);
	CExBaseObject* ExecInsert_Stxml(CThreadProgressInterface *pThreadProgress=NULL);
	CExBaseObject* ExecInsert_Gbxml(CThreadProgressInterface *pThreadProgress=NULL);

	long GetProgressStepCount();


//打开向导文件
public:
	void OpenWzdFile(const CString &strWzdFile);
	void InitTool(CGbInsertStxmlFileTool *pTool);
	void SaveWzdFile(const CString &strWzdFile);

private:
	void InitDatasetList(CGbWzdDatasetRefMngr *pWzdDatasetMngr);
	void InitGbtBatchItemGroups(CGbtBatchItemGroups *pGbtBatchItemGroups);
	void InitGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pGbInsertStxmlFileMngr);
	void InitCmdItemEditMngr(CGbtCommCmdItemEditMngr *pCmdItemEditMngrr);
};

class CGbWzdInsertThread : public CWinThread, public CThreadProgressInterface
{
DECLARE_DYNCREATE(CGbWzdInsertThread)

public:
	virtual void SetMaxRange(long nMaxRange)
	{
		m_nStepIndex = 0;
		m_nMaxRange = nMaxRange;
		PostThreadMessage(WM_USER + 2355, nMaxRange, nMaxRange);
	}
	virtual void ResetProcess()
	{
		m_nStepIndex = 0;
		PostThreadMessage(WM_USER + 2356, 0, 0);
	}
	virtual void StepIt()
	{
		m_nStepIndex++;
		PostThreadMessage(WM_USER + 2357, 0, 0);
	}

	virtual void ShowMsg(const CString &strMsg)
	{
		CString_to_char(strMsg, m_pszMessage);
		PostThreadMessage(WM_USER + 2358, 0, 0);
	}

	virtual void Exit()
	{
		PostThreadMessage(WM_QUIT, 0, 0);
	}

	void StartTimer(long nTimerLong)
	{

	}

	BOOL IsThreadCreated()	{	return m_pProgressDlg != NULL;	}
	CWnd* GetParentWnd()	{	return m_pParentWnd;			}

protected:
	CGbWzdInsertThread();           // protected constructor used by dynamic creation

	CThreadProgrssDlg *m_pProgressDlg;
	char m_pszMessage[4096];
	long m_nMaxRange;
	CWnd *m_pParentWnd;
	long m_nStepIndex;

public:
	static CGbWzdInsertThread* CreateTestCtrlThread(CWnd *pWnd)
	{
		CGbWzdInsertThread* pThread = (CGbWzdInsertThread*)AfxBeginThread(RUNTIME_CLASS(CGbWzdInsertThread));
		pThread->m_bAutoDelete = TRUE;
		pThread->ResumeThread();
		pThread->m_pParentWnd = pWnd;
		return pThread;
	}

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual ~CGbWzdInsertThread();


	// Generated message map functions
	//{{AFX_MSG(CTestWorkThread)
	afx_msg void On2355(WPARAM wParam, LPARAM lParam);
	afx_msg void On2356(WPARAM wParam, LPARAM lParam);
	afx_msg void On2357(WPARAM wParam, LPARAM lParam);
	afx_msg void On2358(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};