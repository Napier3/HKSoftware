#pragma once

#include "..\GuideBook\GuideBook.h"
#include "..\GuideBook\Items.h"
#include "..\GuideBook\GbItemVariableIDReplace.h"
#include "..\..\..\Module\KeyDb\XMatchToolBase.h"
#include "..\GuideBook\ReportMap\WordRptEdit.h"

#include "..\..\Module\MfcCtrlEx\ThreadProgrssDlg.h"

#include "GuideBookWizardDefine.h"

#define GBTWZDCLASSID_BASE                       (CLASSID_EXLISTCLASS + 0X07FF0000)
#define GBTWZDCLASSID_BATCHITEMREF               (GBTWZDCLASSID_BASE + 0X00000001)
#define GBTWZDCLASSID_BTACHITEMGROUP             (GBTWZDCLASSID_BASE + 0X00000002)
#define GBTWZDCLASSID_BTACHITEMGROUPS            (GBTWZDCLASSID_BASE + 0X00000003)
#define GBTWZDCLASSID_GBTDATASCRIPTMAP           (GBTWZDCLASSID_BASE + 0X00000004)
#define GBTWZDCLASSID_GBTDATAINTERFACEMAP        (GBTWZDCLASSID_BASE + 0X00000005)
#define GBTWZDCLASSID_GBTINSERTSTXMLFILE         (GBTWZDCLASSID_BASE + 0X00000006)
#define GBTWZDCLASSID_GBTINSERTSTXMLFILEMNGR     (GBTWZDCLASSID_BASE + 0X00000007)
#define GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL     (GBTWZDCLASSID_BASE + 0X00000008)
#define GBTWZDCLASSID_GBTDATASETREF     (GBTWZDCLASSID_BASE + 0X00000009)
#define GBTWZDCLASSID_GBTDATASETREFMNGR     (GBTWZDCLASSID_BASE + 0X0000000A)
#define GBTWZDCLASSID_BATCHITEMREFVALUE               (GBTWZDCLASSID_BASE + 0X0000000B)

#define WM_WZD_INSERT_STXML_FINISH  (WM_USER+2251)

//////////////////////////////////////////////////////////////////////////
//批量添加
//拥有m_nBatchItem==1的测试项目的引用

class CGbtBatchItemRefValue : public CExBaseObject
{
public:
	CGbtBatchItemRefValue();
	virtual ~CGbtBatchItemRefValue();
	long m_nUse;
	CString m_strValue;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMREFVALUE;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CValueKey();     }
};


class CGbtBatchItemRef : public CExBaseList
{
public:
	CGbtBatchItemRef();
	virtual ~CGbtBatchItemRef();
	UINT m_nRefItemClassID;
	CString m_strDatasetPath;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BATCHITEMREF;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchItemRefKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void InitByCopy(CGbtBatchItemRef *pSrc);

	long GetUsedBatchItemRefValues(CExBaseList &oListValue);
	void InitBatchItemRef(CValues *pValues);
};

//测试项目的一个序列，一个组别，循环添加（枚举）的一个环节
class CGbtBatchItemGroup : public CExBaseList
{
public:
	CGbtBatchItemGroup();
	virtual ~CGbtBatchItemGroup();

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_BTACHITEMGROUP;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchItemGroupKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void InitByCopy(CGbtBatchItemGroup *pSrc);

public:
	CGbtBatchItemRef* NewBatchItemRef(CExBaseObject *pItem);

	BOOL HasBatchItems();
	BOOL IsAllCommCmdItems();
	BOOL IsAllMacroTestItems();
	long GetValuesCount();
	void SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath);
	BOOL ValidateBatchItemsGroup(CString &strErrorMsg);
	long GetUsedBatchItemRefValues(CExBaseList &oListValue);
	void ChangeBatchItemRefValueSel(long nItemRefIndex, CGbtBatchItemRefValue *pValue);

protected:
	CGbtBatchItemRef* NewBatchItemRef_CommCmd(CExBaseObject *pItem);


};

#define BATCH_ITEMS_MODE_EXTERNER   0
#define BATCH_ITEMS_MODE_INTERNAL   1


//管理对象，实现对CGbtBatchItemGroup的管理
class CGbtBatchItemGroups : public CExBaseList
{
public:
	CGbtBatchItemGroups();
	virtual ~CGbtBatchItemGroups();
	long m_nBatchVariableMode;
	long m_nBatchItemsMode;


	virtual UINT GetClassID() {    return GBTWZDCLASSID_BTACHITEMGROUPS;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtBatchItemGroupsKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

	void InitByCopy(CGbtBatchItemGroups *pSrc);

	CGbtBatchItemGroup *m_pGbtBatchItemGroupRef;

public:
	void InitListBatchItem(CGuideBook *pGuideBook);
	CGbtBatchItemGroup* NewBatchItemGroup();
	BOOL HasBatchItems();
	BOOL IsAllCommCmdItems();
	BOOL IsAllMacroTestItems();
	void SetBatchItemRefDatasetPath(long nItemRefIndex, const CString &strDatasetPath);
	BOOL ValidateBatchItemsGroups(CString &strErrorMsg);
	void ChangeBatchItemRefValueSel(long nItemRefIndex, CGbtBatchItemRefValue *pValue);

private:
	void InitListBatchItemRef(CExBaseList *pList);
};

//////////////////////////////////////////////////////////////////////////
//映射组别功能

class CGbtDataScriptMap : public CExBaseList
{
public:
	CGbtDataScriptMap();
	virtual ~CGbtDataScriptMap();

	virtual CBaseObject* Clone();
	virtual BOOL Copy(CBaseObject* pDest);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATASCRIPTMAP;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtDataScriptMapKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual long XmlReadChildren(const MSXML2::IXMLDOMNodeListPtr &oNodes, CXmlRWKeys *pXmlRWKeys)	{	return 0;	}
	virtual long XmlWriteChildren(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)	{	return 0;	}

	void InitByCopy(CGbtDataScriptMap *pSrc);

public:
	CGbtDataScript *m_pGbtDataScript;
	CString m_strDataValue;
	CString m_strRefObjName;
	CString m_strRefObjPath;

private:
	CExBaseObject *m_pRefObject;  //关联的数据对象

public:
	void SetRefObject(CExBaseObject *pRefObject, BOOL bRemoveAll=TRUE);
	CExBaseObject* GetRefObject()	{	return m_pRefObject;	}
	void InitGbtDataScript(CGbtDataScript *pGbtDataScript);
	void XMatch(CXMatchList &oXMatchList);
	void XMatch(CXMatchList &oXMatchList, const CStringArray &strKey);
	BOOL InitRefObject();
	CString GetRefObjIDPath();
	CString GetGbtDataScriptValue();

	BOOL HasAllKey(const CStringArray &astrKey, const CString &strName);
	BOOL HasKey(const CStringArray &astrKey, const CString &strName);
};

class CGbtDataInterfaceMap : public CExBaseList
{
public:
	CGbtDataInterfaceMap();
	virtual ~CGbtDataInterfaceMap();

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATAINTERFACEMAP;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbtDataInterfaceMapKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	void InitByCopy(CGbtDataInterfaceMap *pSrc);

public:
	CGbtDataInterface *m_pGbtDataInterface;

public:
	void InitGbtDataInterface(CGbtDataInterface *pGbtDataInterface);
	void XMatch(CXMatchList &oXMatchList);
	void XMatch(CXMatchList &oXMatchList, const CStringArray &strKey);
	BOOL CanInsert();
	BOOL ValidateMapKeys(CString &strErrorMsg);
};

void wzd_InsertIecConfigMacroTest(const CString &strIecFile, CExBaseList *pParent);

CItems* GbtWzd_InsertRootItems(CExBaseList *pParentItems, const CString &strName, const CString &strID);


//数据集映射的一个组别，对应一个Items
class CGbInsertStxmlFile : public CExBaseList
{
public:
	CGbInsertStxmlFile();
	virtual ~CGbInsertStxmlFile();

	CString m_strKey;
	CStringArray m_astrKey;

	CWordRptEdit *m_pWordRptEditSrc;
	CWordRptEdit *m_pWordRptEditDest;
	CString m_strStxmlFile;
	long m_bInsertFileRoot;

	CString m_strIec61850ConfigFile;

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTINSERTSTXMLFILE;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbInsertStxmlFileKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//void InitByCopy(CGbInsertStxmlFile *pSrc, CDevice *pDevice, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	void InitByCopy(CGbInsertStxmlFile *pSrc);

public:
	void InitGbFileInsert(const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	void InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	CExBaseObject* ExecInsert(CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	CExBaseObject* ExecInsertByBatchItemGroups(CGbtBatchItemGroups *pBatchItemGroups, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	CExBaseObject* ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchItemGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	CItems* ExcuteInsertFile(CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	void XMatch(CXMatchList &oXMatchList);

	void UpdateByBatchGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pRootItems);
	BOOL ValidateMapKeys(CString &strErrorMsg);
	void SetKey(const CString &strKey);
	long GetProgressStepCount()		{		return GetCount() * 2;		}

	void InsertIecConfigMacroTest(CExBaseList *pParent)
	{
		wzd_InsertIecConfigMacroTest(m_strIec61850ConfigFile, pParent);
	}

	CDataObj *FindMapDataObj(const CString &strGbtDataID);

private:
	CItems* InsertByDataterfaceMap(CGbtDataInterfaceMap *pGbtDataInterfaceMap, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);
	void InitCommCmdItemDatasetPath(CDevice *pDevice, CExBaseList *pItems);
	void InitCommCmdItemDatasetPath(CDevice *pDevice, CCommCmd *pCommCmd);

	void InsertStxmlWord(CItems *pCurrItems);
	void RenameRptBkmks(CExBaseList *pList);
	void RenameRptBkmk(CExBaseObject *pBkmk);

	void UpdateByBatchItemRef(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems);
	CExBaseObject* SelectByRefItem(CGbtBatchItemRef *pBatchItemRef, CExBaseList *pRootItems);
	void UpdateItem_CommCmd(CExBaseObject *pItem, CGbtBatchItemRef *pBatchItemRef);
	
};



//CGbInsertStxmlFile管理对象，如果
class CGbInsertStxmlFileMngr : public CExBaseList
{
public:
	CGbInsertStxmlFileMngr();
	virtual ~CGbInsertStxmlFileMngr();


	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTINSERTSTXMLFILEMNGR;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbInsertStxmlFileMngrKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	CGbInsertStxmlFile *m_pHeadStxmlFile;

	CGbInsertStxmlFile* NewGbInsertStxmlFile();

public:
	void InitGbtDataInterfaceMaps(CDevice *pDevice, const CString &strStxmlFile, CWordRptEdit *pDestWordEdit, CWordRptEdit *pSrcWordEdit);
	void XMatch(CXMatchList &oXMatchList, long nIndex);
	CExBaseObject* ExecInsertByBatchItemGroup(CGbtBatchItemGroup *pBatchGroup, CExBaseList *pParentItems, CExBaseList &oListStxmlItem, CThreadProgressInterface *pThreadProgress);

	//void UpdateByBatchGroup(CGbtBatchItemGroup *pBatchGroup, CThreadProgressInterface *pThreadProgress);
	BOOL ValidateMapKeys(CString &strErrorMsg);
	long GetProgressStepCount();

	void InitByCopy(CGbInsertStxmlFileMngr *pSrc);
	CDataObj *FindMapDataObj(const CString &strGbtDataID);
protected:
	void Validate();
};

class CGbWzdDatasetRef : public CExBaseObject
{
public:
	CGbWzdDatasetRef()	{	m_pDataSetRef = NULL;	}
	virtual ~CGbWzdDatasetRef()	{};

	CDataSet *m_pDataSetRef;

	void SetDataSet(CDataSet *pDataSet)
	{
		m_pDataSetRef = pDataSet;
		m_strName = pDataSet->m_strName;
		m_strID = pDataSet->GetIDPathEx(GBCLASSID_CPUS, FALSE);
	}

public:
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATASETREF;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbWzdDatasetRefKey();     }

};

class CGbWzdDatasetRefMngr : public CExBaseList
{
public:
	CGbWzdDatasetRefMngr(){};
	virtual ~CGbWzdDatasetRefMngr(){};

public:
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTDATASETREFMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbWzdDatasetRefsKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
};

class CGbInsertStxmlFileTool : public CExBaseList
{
public:
	CGbInsertStxmlFileTool();
	virtual ~CGbInsertStxmlFileTool();

	void SetParentWnd(CWnd *pWnd);
	virtual UINT GetClassID() {    return GBTWZDCLASSID_GBTINSERTSTXMLFILETOOL;   }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CGbInsertStxmlFileToolKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);


public:
	CGuideBook *m_pGbStxml;        //子模板对象
	CGuideBook *m_pGuideBookDest;  //目标测试模板对象
	CWordRptEdit *m_pWordRptEditSrc;
	CWordRptEdit *m_pWordRptEditDest;

	CExBaseList *m_pParentItems;
	CXKeyDB *m_pXKeyDB;
	BOOL m_bInsertRootItems;
	CString m_strRootItemsName;
	CString m_strRootItemsID;
	CItems *m_pNewRootItems;
	CExBaseList m_oListNewItems;

	CGbtBatchItemGroups *m_pGbtBatchItemGroups;
	CGbInsertStxmlFileMngr *m_pGbInsertStxmlFileMngr;

	CString m_strIec61850ConfigFile;

public:
	BOOL Init(const CString &strStxmlFile);
	BOOL Init(CGuideBook *pGuideBookDest, CXKeyDB *pKeyDB, CWordRptEdit *pWordRptEditDest);
	void AddDataset(CDataSet *pDataset);
	void ClearListDataset();

	//子模板插入到的项目分类对象，如果没有指定，则插入到Device的根目录下
	void SetParentItems(CExBaseList *pParent);
	void XMatch(long nIndex=-1);
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
	CExBaseList m_oListStxmlItem;
	CString m_strStxmlFile;
	CWnd *m_pParentWnd;

	void InitListStxmlItem();
	void InitGbtDataInterfaceMaps();
	void Free();

	void InsertRootItems(CThreadProgressInterface *pThreadProgress);
	void InsertSysParas(CThreadProgressInterface *pThreadProgress);
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
	long GetProgressStepCount();


//打开向导文件
public:
	void OpenWzdFile(const CString &strWzdFile);

private:
	void InitDatasetList(CGbWzdDatasetRefMngr *pWzdDatasetMngr);
	void InitGbtBatchItemGroups(CGbtBatchItemGroups *pGbtBatchItemGroups);
	void InitGbInsertStxmlFileMngr(CGbInsertStxmlFileMngr *pGbInsertStxmlFileMngr);
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

	BOOL IsThreadCreated()	{	return m_pProgressDlg != NULL;}

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