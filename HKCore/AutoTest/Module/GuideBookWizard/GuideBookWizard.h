#pragma once

#include "GbWzdCmdGbAttr.h"
#include "GbWzdCmdDeviceModel.h"

#include "..\GbWzdAuto\GbWzdAutoConfig.h"
#include "..\GuideBook\ItemMngr.h"
#include "..\GuideBook\ItemParaMngr.h"
#include "..\GuideBook\Safety.h"

class CGuideBookWizard : public CExBaseList
{
private:
	CGuideBookWizard();
	virtual ~CGuideBookWizard();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_GBWIZARD;	} 

	friend class CGbWzdCmd;
	friend class CGbWzdCmdList;
public:
	static CGuideBookWizard* g_pGuideBookWizard;
	static long g_nGuideBookWizardRef;
	static CGuideBookWizard* Create(const CString &strWzdAutoCfgFile=_T(""));
	static void Release();

//	static CWordRptEdit* GetCWordRptEdit();
	static CRptEditInterface* GetCWordRptEdit();
	static CGuideBook* GetCGuideBook();
	static BOOL IsWizardValid();

public:
	//初始化
	static CString GetGbFileType();
	static BOOL SetGbWizardType(const CString &strGbFileType);
//	static BOOL InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit, BOOL bQuick=FALSE);
//	static BOOL InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit);
	static BOOL InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit, BOOL bQuick=FALSE);
	static BOOL InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit);

	static CGbWzdCmd* AddFile(const CString &strFile);
	static CGbWzdCmd* AddSaveCmd(long &nOldSaveCmdIndex);
	static CWnd* GetWndGbWzd();
	static void OnGbNodeSelChange(CExBaseObject *pGbNode);
	static BOOL IsSubWzdCmd(CGbWzdCmd *pWzdCmd);
	static long GetWzdCmdIndex(CGbWzdCmd *pWzdCmd);
	
	//向导函数
	static BOOL IsWizardFinish();
	static BOOL InitWizardCmdHead();
	static long GetCurrGbWzdCmdIndex();
	static CGbWzdCmd* GetCurrGbWzdCmd();
	static CGbWzdCmd* GetNextGbWzdCmd();
	static CGbWzdCmd* GetGbWzdCmd(long nCmdIndex);
	static BOOL ExecCurr(DWORD dwExecMode);
	static BOOL ExecNext(DWORD dwExecMode);
	static BOOL IsGuideBookFileWzd();
	static BOOL IsStxmlFileWzd();

	//操作函数
	static BOOL MoveUp(CGbWzdCmd *pWzdCmd);
	static BOOL MoveDown(CGbWzdCmd *pWzdCmd);
	static BOOL DeleteWzdCmd(CGbWzdCmd *pWzdCmd);

	//获取命令相关函数
	static CGbWzdCmdGbAttr* GetCurrWzdCmd_GbAttr();
	static CGbWzdCmdDeviceModel* GetCurrWzdCmd_DeviceModel();

	static void SetCurrWzdCmd_GbAttr(CGuideBook *pGuideBook);
	static void SetCurrWzdCmd_DeviceModel(CDevice *pDevice);
	static void SetCurrWzdCmd_DeviceModel(CCpus *pCpus);
	static void SetCurrWzdCmd_DeviceModel(CCharacteristics *pCharacteristics);

	//自动向导文件
	static void SaveWizard();
	static void OpenWizard();

	static DWORD GetWzdExecMode();
	static void SetWzdExecMode(DWORD dwWzdExecMode);

	static BOOL IsQuickWizard();
	static BOOL IsWordPageVert();

	static void InitWordPage();
	static CGbWzdAutoConfig* GetGbWzdAutoConfig();
	static BOOL IsGbWzdAuto();
	static BOOL IsGbWzdAuto_Auto();

protected:
	CGuideBook *m_pGuideBook;
//	CWordRptEdit *m_pWordRptEdit;
	CRptEditInterface *m_pRptEdit;

	CGbWzdAutoConfig *m_pGbWzdAutoConfig;

	CTreeCtrl *m_pGbTree;
	CFrameWnd *m_pMainFrame;
	CWnd *m_pWndGbWzd;
	long m_nWzdCmdIndex;
	CString m_strGbFileType;
	DWORD m_dwWzdExecMode;
	BOOL  m_bQuickWizard;
	BOOL m_bWordPageOrientationVert;

	BOOL In_SetGbWizardType(const CString &strGbFileType);
//	BOOL In_InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit, BOOL bQuick);
//	BOOL In_InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CWordRptEdit *pWordEdit);
	BOOL In_InitGbWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit, BOOL bQuick);
	BOOL In_InitStxmlWizard(CGuideBook *pGuideBook, CTreeCtrl *pGbTree, CFrameWnd *pMainFrame, CWnd *pWzdWnd, CRptEditInterface *pRptEdit);

	CGbWzdCmd* In_AddFile(const CString &strFile);
	CGbWzdCmd* In_AddSaveCmd(long &nOldSaveCmdIndex);
	void In_OnGbNodeSelChange(CExBaseObject *pGbNode);

	//向导函数
	BOOL In_IsWizardFinish();
	BOOL In_InitWizardCmdHead();
	CGbWzdCmd* In_GetCurrGbWzdCmd();
	CGbWzdCmd* In_GetNextGbWzdCmd();
	BOOL In_ExecCurrGbWzdCmd(DWORD dwExecMode);
	BOOL In_ExecNextGbWzdCmd(DWORD dwExecMode);

	BOOL In_IsCurrCmdFinish();

	BOOL In_IsSubWzdCmd(CGbWzdCmd *pWzdCmd);
	long In_GetWzdCmdIndex(CGbWzdCmd *pWzdCmd);

	//操作函数
	BOOL In_MoveUp(CGbWzdCmd *pWzdCmd);
	BOOL In_MoveDown(CGbWzdCmd *pWzdCmd);
	BOOL In_DeleteWzdCmd(CGbWzdCmd *pWzdCmd);

	CGbWzdCmdGbAttr* In_GetCurrWzdCmd_GbAttr();
	CGbWzdCmdDeviceModel* In_GetCurrWzdCmd_DeviceModel();

	//自动向导文件
	void In_SaveWizard();
	void In_OpenWizard();

	void In_InitWordPage();
	void CreateWzdAutoConfig(const CString &strWzdAutoCfgFile);
	void InsertBmkByGlobalDatas();
	void InsertDIORsltJdgs();
	void InsertItemParas();
	void AddSubItems(CItems *pItems, CGbWzdAutoItems *pGbWzdAutoItems);
	void AddRsltJdgBmk(CSafety *pSafety, const CString &strBmkText, const CString &strBmkAttrid);

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey() ;

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
};

