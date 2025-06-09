#pragma once

// CSclCheckView 窗体视图

//#include "..\resource.h"
#include "SclCheckDoc.h"
#include "SclCheckFrame.h"

#include "SclCheckCtrlView.h"
#include "..\..\..\61850\Module\SCL\SclIecCfgDatas.h"

#include "ResultsRec.h"
#include "SchemaCode\XmlCheckObject.h"
#include "..\SclCheckDataMngr\DataTypeTemplates.h"

#include "..\SclCheckDataMngr\SclCheckObjectsSet.h"
#include<list>

#include "..\..\..\Module\KeyDb\XMatchVirTerminal.h"

#include <string>
#include <map>
//#include <cstdlib>
using namespace std;

class CSclCheckView : public CFormView
{
protected:
	CSclCheckView(); 
	DECLARE_DYNCREATE(CSclCheckView)
public:
	enum { IDD = IDD_SCLCHECK_FORM };
	CSclCheckDoc* GetDocument() const;
	CMFCTabCtrl m_tabPara;

	bool UTF8ToMultiByte(CString &srcStr);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate();
	virtual ~CSclCheckView();
public:
	void SetSclChStation(CSclStation *pSclChStation){m_pSclChStation = pSclChStation;}
	void SetStrSclPath(CString &strSclPath){m_pStrSclPath = &strSclPath;}
	LRESULT OnFinishSchemaCheck(WPARAM wParam, LPARAM lParam);
private:
	CSclStation *m_pSclChStation;
	CString *m_pStrSclPath;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	void ShowAllGridDatas();

////////////////////////////////////////////////Schema语法检查 部分函数及成员变量//////////////////////////////////////////////////////////////////
	CString m_strSclFilePath;
	CString m_strSchemaPath;
	CResultsRec m_oSchemaResultsRec;
	CXmlCheckObject *m_pSclCheckObject;
	CSclCheckCtrlView *m_pSclSchemaView;
	void StartSchemaCheck(CSchemaChecks *pSchemaChecks);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////DL/T860数据类型模板一致性检查 部分函数及成员变量///////////////////////////////////////////////////////////////
	CTemplateFile1396 *m_pTemplateFile1396;
	CSCLTemplates *m_pSCLTestObjectFile;
	CResultsRec m_oDLT860TmpsResultsRec;
	CSclCheckCtrlView *m_pDLT860TempsView;

	CSCLTemplates *m_pSCLDataTypeTemplates;

	BOOL TemplateCheckIsEmpty(CDLT860ModelChecks *pDLT860ModelChecks);
	BOOL TemplateCompareIsEmpty(CDLT860ModelChecks *pDLT860ModelChecks);

	BOOL BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID);
	void AddCheckResultDLT860Tmps(CString strErrorType ,CString strText  ,CString strErrorPos = "");
	void CheckLNodeTypeOfGDW1396(CLNodeType *pObjDataType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);
	void CheckDOTypeOfGDW1396(CDOType *pObjDOType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);
	void CheckDATypeOfGDW1396(CDAType *pObjDAType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);
	void CheckEnumTypeOfGDW1396(CEnumType *pObjEnumType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks);

	bool CheckTailDigital(CString strName);
	long DelTailDigtal(CString *strName );
	POS checkDO_withRepeat(CLNodeType *pObjDataType ,POS pos , bool bDigtalTail ,CDLT860ModelChecks *pDLT860ModelChecks);
	long FindRepeat(CString strParant ,CString strChild );

	bool DataTypeCompareWithTemplates(CExBaseList *pTmpDataType , CExBaseList *pObjDataType );

	void SetDLT860ModelChecks(CDLT860ModelChecks *pDLT860ModelChecks)
	{
		m_pDLT860ModelChecks = pDLT860ModelChecks;
	}
	void StartTemplatesCheckComp1396();
	static UINT StartTemplatesCheckCompThread(LPVOID pParam);
	void StartTmpsCheckComp1396Thr();
	void AddNewDataTypesToTemplates(CString strSclFilePath ,BOOL bAddLNodeType ,BOOL bAddDOType ,BOOL bAddDAType ,BOOL bAddEnumType);
private:
	CDLT860ModelChecks *m_pDLT860ModelChecks;
	void StartTemplateCheck1396(CDLT860ModelChecks *pDLT860ModelChecks);
	void StartTemplatesCompare(CDLT860ModelChecks *pDLT860ModelChecks);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////通过tinyxml解析整个SCL文件获取结果的检测项目/////////////////////////////////////////////////////////////////////////////////////////////////
public:
	CResultsRec m_oProjAppModelResultsRec;
	CSclCheckCtrlView *pProjAppModelView;

	CExBaseList m_oTinySCLStation;

	BOOL ProjAppModelCheckIsEmpty(CProjAppModelChecks *pProjAppModelChecks);

	void AddCheckResultProjAppModel(CString strErrorType ,CString strText  ,CString strErrorPos = "");
	void GetIEDMSG(TiXmlElement* pTinyIEDNode , CString &strIEDMSG);
	void GetSDOFromDoName(CString &strDOName ,CString &strSDOName );
	void GetDataSetName(TiXmlElement* pTinyLN0Node ,std::list<CString> &list_DataSetName);
	BOOL FindTinyChildAttrValue(TiXmlElement *pTinyElement ,TiXmlElement **pTinyChild ,CString strAttrName ,CString strChildAttrValue);
	void GetTinyDescAndName(TiXmlElement *pTinySubNetwork ,CString &strSubNetwork);

	void CheckPhysConnPort(TiXmlElement *pTinyCommu ,CString strObjectID );
	BOOL CheckPortNameValid(CString strPortName);

	void GetIEDInputsRef(TiXmlElement *pDocRoot);
	void CheckIntAddrOfExRef(TiXmlElement *pTinyExtRef ,CString strIntAddr ,map<CString ,TiXmlElement*> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
		CProjAppModelChecks *pProjAppModelChecks);

	void CheckAccessPointName(TiXmlElement *pTinyAccessPointNode ,CString strAccessPoint ,CString strIEDMSG ,CString  strObjectID);
	void GetIEDMaxConfigNum(TiXmlElement *pTinyAccessPointNode,long &nConfDataSet ,long &nConfReportControl ,long &nConfLogControl);
	void CheckLDeviceInst(TiXmlElement* pTinyLDNode ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CString strObjectID);
	void CheckSDI_DAIValid(TiXmlElement* pTinyDOI ,CExBaseList *pTestObjectTemplates , CString strType,CString strMSGFull ,CString strObjectID);
	void CheckDOI_SDI_DAI_RefValid(TiXmlElement *pTinyLNNode ,TiXmlElement *pTinyLDNode ,CExBaseList *pTestObjectTemplates, map<CString ,TiXmlElement*> *mapLNFullName ,
		CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckDataSetRelated(TiXmlElement *pTinyLNNode ,TiXmlElement* pTinyLDNode ,map<CString ,TiXmlElement*> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,
		CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks ,long &nCurDataSetNum);
	void CheckInputsExtRef(TiXmlElement *pTinyLN0Node ,TiXmlElement *pTinyLDNode ,map<CString ,TiXmlElement*> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,
		CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks );
	void CheckReportCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks ,long &nCurRptNum);
	void CheckLogCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks ,long &nCurLogNum);
	void CheckSMVCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckGSECtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckSettingCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckFCDARefValid(TiXmlElement* pTinyFCDANode ,map<CString ,TiXmlElement*> *mapLNFullName , CString strMsg , CString &strLdInst, CString &strDaName, CString &strFCDAPath, 
		CString strDataSetNameNew ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckRelayEnaInit(TiXmlElement* pTinyDOI ,CString strMsg ,CString strFCDAPath ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckDataSetRptCtrlLogCtrlMaxNum(TiXmlElement *pTinyIEDNode ,long nConfDataSet ,long nCurDataSetNum ,long nConfReportControl ,long nCurRptNum ,long nConfLogControl ,long nCurLogNum ,CString strIEDMSG,
		CProjAppModelChecks *pProjAppModelChecks );


	void SetpProjAppModelChecks(CProjAppModelChecks *pProjAppModelChecks)
	{
		m_pProjAppModelChecks = pProjAppModelChecks;
	}
	void StartCheckProjAppModel();
	static UINT StartCheckProjAppModelThread(LPVOID pParam);
	void StartCheckProjAppModelThr();

private:
	CProjAppModelChecks *m_pProjAppModelChecks;
	void CheckProjAppModelBytinyxml(CProjAppModelChecks *pProjAppModelChecks , CString strPath);
////////////////////////////////////////////////虚回路描述及冲突检查 部分函数及成员变量///////////////////////////////////////////////////////////////	
public:
	map<int ,string > m_mapCheck;

	map<long ,CString > m_mapAppID;
	map<CString ,CString > m_mapSMVID;
	map<CString ,CString > m_mapGOOSEID;

	CResultsRec m_oVirLoopResultsRec;
	CSclCheckCtrlView *m_pSclVirLoopView;

	CXKeyDB *m_pSMVKeyDB;
	CXKeyDB *m_pGSKeyDB;
	CXMatchVirTerminal m_oXMatchVirTerminal;

	BOOL VirLoopCheckIsEmpty(CVirLoopChecks *pVirLoopChecks);

	void AddCheckResultVirLoop(CString strErrorType ,CString strText  ,CString strErrorPos = "");

	void AddStringAvoidRepeat(CString &strDesc ,CString strChild);
	bool CheckMACAddrValidity(CString strMAC ,bool bSMVType);
	bool IsHex(unsigned char ch);

	void CheckSmvOutVirLoop(CSclCtrlSmvOut *pSclCtrlSmvOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckSmvInVirLoop(CSclCtrlSmvIn *pSclCtrlSmvIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckGsOutVirLoop(CSclCtrlGsOut *pSclCtrlGsOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckGsInVirLoop(CSclCtrlGsIn *pSclCtrlGsIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);

	void CheckRptCtrlBrcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);
	void CheckLogCtrlLcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks);

	void SetpVirLoopChecks(CVirLoopChecks *pVirLoopChecks)
	{
		m_pVirLoopChecks = pVirLoopChecks;
	}
	void StartVirLoopCheck();
	static UINT StartVirLoopCheckThread(LPVOID pParam);
	void StartVirLoopCheckThr();

private:
	CVirLoopChecks *m_pVirLoopChecks;
	void StartVirLoopCheck(CVirLoopChecks *pVirLoopChecks);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};


