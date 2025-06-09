#pragma once

#include "GuideBookWizardDefine.h"
#include "..\..\Module\KeyDb\XMatchToolBase.h"
#include "..\..\Module\KeyDb\XMatchEditGridCtrlBase.h"
#include "..\..\Module\KeyDb\XKeyDB.h"
#include "..\GuideBook\GuideBook.h"
#include "..\..\Module\FilterText\FilterTextMngr.h"
#include "..\..\Module\FilterText\FilterTextComboBox.h"
#include "..\..\Module\GuideBook\GbItemVariableIDReplace.h"

#ifdef GB_USE_XFILEMNGRBASE
#include "..\..\Module\XFileMngrBase\DlgXFileMngr.h"
#else
#include "..\..\Module\FileMngr\Dlg\DlgFileMngr.h"
#endif

class CGuideBookMmsModelReplace : public CExBaseList
{
public:
	CGuideBookMmsModelReplace();
	virtual ~CGuideBookMmsModelReplace();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_GBWIZARD;	} 

public:
	CXKeyDB m_oKeyDB;
	CCpus m_oCpusSrc;
	CCpus m_oCpusDest;
	CXMatchToolBase m_oXMatchTool;
	CXMatchEditGridCtrlBase *m_pGridXMatchEdit;
//	CFilterTextMngr m_oFilterMmsDvmFiles;

	//当前的设备数据模型数据集
	CString m_strCurrDatasetPath;      

	//用来替换的数据集
	CString m_strRepalceDatasetPath;   

	BOOL m_bReplaceAinDataset;

public:
	virtual void AttatchWndRef(CWnd *pWnd)	{	m_pWndRef = pWnd;	}
	virtual void AttachXMatchGrid(CXMatchEditGridCtrlBase *pGrid);	//{	m_pGridXMatchEdit = pGrid;	}
//	CFilterTextMngr* GetFilterMmsDvmFiles()	{	return &m_oFilterMmsDvmFiles;	}
	virtual void InitReplace();
	virtual void SetEditCpus(CCpus *pDestCpus);
	virtual void OpenKeyDbFile();
	virtual void ReplaceDataSet(CThreadProgressInterface *pThreadProgress);
	virtual void OnGbNodeSelChanged_Src(CExBaseList *pSelNode);
	virtual void OnGbNodeSelChanged_Dest(CExBaseList *pSelNode);
// 	virtual BOOL PopOpenMmsDvmDlg(CFilterText** ppFilterText);
	virtual BOOL MatchOrder();
	virtual BOOL MatchFrom(CExBaseObject *pCurrFrom, CExBaseObject *pRefFrom);

	virtual BOOL XMatchConfigSave();
	virtual BOOL XMatchConfigOpen(CXMatchConfig &oXMatchConfig);
	virtual void InitDestCpus();

protected:
	CCpus *m_pDestCpus;
	CExBaseList m_oListTemp;
	CExBaseList m_oListDatasetRef;

	CExBaseList *m_pSelCurrGbDataObject;
	CExBaseList *m_pSelDataObjectOpened;
	CThreadProgressInterface *m_pThreadProgress;
	BOOL m_bInsertNoMatch;
	CString m_strXMatchFile;
	CWnd *m_pWndRef;
	CString m_strMmsDvmFile;

	CExBaseObject *m_pDestObject;
	CGbItemVariableIDReplace m_oGbItemVariableIDReplace;

protected:
	virtual BOOL XMatch(BOOL bShowMatch=TRUE);
	virtual void XMatchByConfig(CXMatchConfig *pConfig);
	virtual void XMatchRead(CXMatchConfig *pConfig);
	virtual void InitXMatchConfig(CXMatchConfig *pXMatchConfig);
	virtual void InitXMatchConfigDataset(CXMatchConfig *pXMatchConfig);
	virtual BOOL OpenMmsDvmFile(const CString &strFile);

	static UINT ReplaceDataSetThread(LPVOID pParam);
	UINT ReplaceDataSetThread();

	virtual void RelpaceID(const CString &strSrcID, const CString &strDestID);
	virtual void AfterReplace(){}
	virtual void InitListDatasetRef()	{	};
	BOOL GetReplaceID(CExBaseObject *pSrc, CExBaseObject *pDest, CString &strSrc, CString &strDest);
};