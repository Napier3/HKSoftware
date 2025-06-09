#pragma once
#include "SclCheckObjectsSet.h"
#include "SclDataTemplates.h"
#include "DataTypeTemplates.h"
#include "../SclCheck/ResultsRec.h"
#include "../../../Module/xml/XPugiXML/xpugixml.hpp"

class CTinyExtRef : public CExBaseList
{
public:
	CString m_strCtrlName;

	CTinyExtRef();
	virtual ~CTinyExtRef();
};

class CSclProjAppModelCheckTool
{
public:
	CSclProjAppModelCheckTool(void);
	virtual ~CSclProjAppModelCheckTool(void);

	BOOL StartCheck();
	//直接启动检查
	int StartProCheckNormal(const CString &strSclFilePath,CProjAppModelChecks *pProjAppModelChecks,CResultsRec *pProModResults);
	//从线程启动检查
	int StartProCheckFromThread(const CString &strSclFilePath,CProjAppModelChecks *pProjAppModelChecks,CResultsRec *pProModResults);
	CWinThread *m_pStartCheckThread;
	CString m_strSclFilePath;
	BOOL m_BeCheckFinished;
	void FreeStartProCheckThread();
	static UINT StartProCheckThread(LPVOID pParam);
protected:
	void GetIEDInputsRef(xpugi::xml_node pDocRoot);
	BOOL BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID);

	void CheckPhysConnPort(xpugi::xml_node pTinyCommu ,CString strObjectID );
	void GetIEDMSG(xpugi::xml_node pTinyIEDNode , CString &strIEDMSG);
	void CheckAccessPointName(xpugi::xml_node pTinyAccessPointNode ,CString strAccessPoint ,CString strIEDMSG ,CString  strObjectID);
	void CheckLDeviceInst(xpugi::xml_node pTinyLDNode ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CString strObjectID);
	void CheckDOI_SDI_DAI_RefValid(xpugi::xml_node pTinyLNNode ,xpugi::xml_node pTinyLDNode  ,CExBaseList *pTestObjectTemplates ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,
		CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckDataSetRelated(xpugi::xml_node pTinyLNNode ,xpugi::xml_node pTinyLDNode ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,CString strLDevice ,
		CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks ,long &nCurDataSetNum);
	void CheckInputsExtRef(xpugi::xml_node pTinyLN0Node ,xpugi::xml_node pTinyLDNode ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,
		CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks );
	void GetDataSetName(xpugi::xml_node pTinyLN0Node ,std::list<CString> &list_DataSetName);
	void CheckReportCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
		CProjAppModelChecks *pProjAppModelChecks ,long &nCurRptNum);
	void CheckLogCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
		CProjAppModelChecks *pProjAppModelChecks ,long &nCurLogNum);
	void CheckSMVCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
		CProjAppModelChecks *pProjAppModelChecks);
	void CheckGSECtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
		CProjAppModelChecks *pProjAppModelChecks);
	void CheckSettingCtrlRelated(xpugi::xml_node pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
		CProjAppModelChecks *pProjAppModelChecks);
	void AddCheckResultProjAppModel(CString strErrorType ,CString strText ,CString strErrorPos);
	void GetIEDMaxConfigNum(xpugi::xml_node pTinyAccessPointNode,long &nConfDataSet ,long &nConfReportControl ,long &nConfLogControl);
	void CheckDataSetRptCtrlLogCtrlMaxNum(xpugi::xml_node pTinyIEDNode ,long nConfDataSet ,long nCurDataSetNum ,long nConfReportControl ,long nCurRptNum ,long nConfLogControl ,long nCurLogNum ,CString strIEDMSG,
		CProjAppModelChecks *pProjAppModelChecks );
	void CheckIntAddrOfExRef(xpugi::xml_node pTinyExtRef ,CString strIntAddr ,std::map<CString ,xpugi::xml_node> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
		CProjAppModelChecks *pProjAppModelChecks);
	BOOL CheckPortNameValid(CString strPortName);
	BOOL FindTinyChildAttrValue(xpugi::xml_node pTinyElement ,xpugi::xml_node *pTinyChild ,CString strAttrName ,CString strChildAttrValue);
	void CheckFCDARefValid(xpugi::xml_node pTinyFCDANode ,std::map<CString ,xpugi::xml_node> *mapLNFullName , CString strMsg , CString &strLdInst, CString &strDaName, CString &strFCDAPath, 
		CString strDataSetNameNew ,CProjAppModelChecks *pProjAppModelChecks);
	void GetSDOFromDoName(CString &strDOName ,CString &strSDOName );
	void CheckRelayEnaInit(xpugi::xml_node pTinyDOI ,CString strMsg ,CString strFCDAPath ,CProjAppModelChecks *pProjAppModelChecks);
	void CheckSDI_DAIValid(xpugi::xml_node pTinyDOI ,CExBaseList *pTestObjectTemplates , CString strType,CString strMSGFull ,CString strObjectID);
	void GetTinyDescAndName(xpugi::xml_node pTinySubNetwork ,CString &strSubNetwork);
	long DelTailDigtal(CString *strName );
	void FormatString(CString &strText, const char *strFormat, ...);
	CString GetAttributeText(xpugi::xml_node oPugiNode,const char *pstrID);

	CSCLTemplates m_oSCLTestObjectFile_ProjApp;
	CExBaseList m_oTinySCLStation;
	CResultsRec *m_pProModResults;
	CProjAppModelChecks *m_pProjAppModelChecks;

};
