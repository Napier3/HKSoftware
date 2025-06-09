#pragma once

#include "..\GuideBook\Device.h"
#include "..\GuideBook\CommCmd.h"
#include "..\GuideBook\MacroTest.h"
#include "..\GuideBook\MacroCharItems.h"

#include "..\..\Module\DialogBase\DynDialogEx.h"


class CGbItemCheckDlg : public CDynDialogEx
{
	DECLARE_DYNAMIC(CGbItemCheckDlg)

public:
	CGbItemCheckDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGbItemCheckDlg();

	CString m_strFilePath;
	CEdit m_editPath;
	CButton m_btnOK;

	virtual int DoModal(); 
	virtual BOOL OnInitDialog();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	void CreateControls();

};

// class CGbTestItemCheck : public CExBaseList
// {
// public:
// 	CGbTestItemCheck(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode);
// 	virtual ~CGbCommCmdCheck();
// };

//数据集映射的一个组别，对应一个Items
class CGbCommCmdCheck : public CExBaseList
{
protected:
	CGbCommCmdCheck(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode);
	virtual ~CGbCommCmdCheck();


public:
	static CGbCommCmdCheck *g_pGbCommCmdCheck;

	static void Create(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode);
	static void Release();
	static void CreateCheckThread();

private:
	static UINT CheckCmdValuesThread(LPVOID pObject);
	void CheckCmdValues();
	CCpus* GetCpus(CDevice *pDevice);
	CCpus *m_pCpus;
	CTreeCtrl *m_pGbTreeCtrl;
	CWnd *m_pMainFrame;
	void GetAllCommCmd(CExBaseList *pDataList);
	BOOL CheckCommCmd(CCommCmd *pCommCmd);
	BOOL IsCmdValueSame(CValue *pValueSrc, CValue *pValueDest);

	void ValidateCmdValues(CDevice *pDevice, CCommCmd *pCommCmd);
	CExBaseObject* FindDataObjByRptDataPath(const CString &strPath);
};

void Gb_CheckMacroTestItem(CMacroTest *pMacroTest);

//数据集映射的一个组别，对应一个Items
class CGbMacroTestItemCheck : public CExBaseList
{
protected:
	CGbMacroTestItemCheck(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode);
	virtual ~CGbMacroTestItemCheck();


public:
	static CGbMacroTestItemCheck *g_pGbMacroTestCheck;

	static void Create(CWnd *pMainFrame, CTreeCtrl *pTreeCtrl, CExBaseList *pGbNode);
	static void Release();
	static void CreateCheckThread();

private:
	static UINT CheckMacroTestParasThread(LPVOID pObject);
	void CheckMacroTestParas();
	CCpus* GetCpus(CDevice *pDevice);
	CCpus *m_pCpus;
	CTreeCtrl *m_pGbTreeCtrl;
	CWnd *m_pMainFrame;
	void GetAllMacroTest(CExBaseList *pDataList);
	BOOL CheckMacroTest(CMacroTest *pMacroTest);
	BOOL IsCmdValueSame(CValue *pValueSrc, CValue *pValueDest);
	//CExBaseObject* FindDataObjByRptDataPath(const CString &strPath);
};
