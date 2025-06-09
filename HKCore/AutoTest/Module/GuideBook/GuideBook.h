#pragma once
#include "GbItemBase.h"
#include "ItemContainer.h"
#include "GbCommCmdConfig/GbCommCmdConfig.h"
//#include "ScriptDataVariables.h"
#include "TestTypeMngr.h"
#include "Device.h"
#include "../../../Module/TestMacro/TestMacroInterface.h"
#include "MacroTestPara.h"
#include "TestGlobalDatasMngr.h"
#include "../../../Module/System/StringTokenizer.h"
#include "MacroCharItems.h"
#include "Safety.h"
#include "SysParaEdit.h"
#include "CommCmd.h"
#include "HdResReqest.h"

class CJobGuide;
class CItemContainer;

#ifdef CGuideBook_with_iecfg_file
#include "../../61850/Module/CfgDataMngr/IecCfgDevice.h"
#endif

class CGuideBook :	public CGbItemBase
{
public:
	CGuideBook(void);
	virtual ~CGuideBook(void);

	static const CString g_strTestTypeConfigFile;
	static const CString g_strCmmCmdConfigFile;

	BOOL m_bIsOpenXmlReportFile;
	BOOL m_bIsOpenDscFile;

public:
	CExBaseList m_oVsdxPagesList;   //��Ӧ��visio�ļ���page������	//shaolei 2021.3.12
	CString m_strPpTemplateFile;      //��Լģ���ļ�
	CString m_strCommCmdConfigFile;		//ͨѶ�����ļ�
	CString m_strDeviceModelFile;		//����ļ�
	long    m_nTestControlMode;         //2015-6-10 �� ���Կ���ģʽ��test-control-mode��single��single-many-report
	CString m_strEngineMode;   //shaolei  2023-11-3
	CItemContainer* m_pItemContainer;
	CString m_strDevID;
	CString m_strDevBy;
	CString m_strVersion;
	long  m_nIsReadOnly;   //ģ��ֻ�����ԣ���ֹ�ڴ򿪶��ģ��༭��ʱ����༭
	
	//2020-01-28   ģ����Ȩ
	CString m_strAuthoritySN;
	CString m_strAuthorityCop;
	CDvmDataset *m_pGbDev;

	//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
	//m_strTestMacroFile�޸�ΪTestMacroFileID��������ֲ��Թ�������TestMacroFile����������
	CString m_strTestMacroFileID; 
	CString m_strTestTypeFile;
	CString m_strDvmFile;
	CString m_strStandNameFile;
	CString  m_strExpandConfigFile;

	CJobGuide* m_pJobGuide;  //��ҵָ��
	CDvmDataset *m_pGlobalDatas;	//���Ե�ȫ������
	CDvmDataset *m_pTestAppDefine;	//�����Ƕ���
	CDvmDataset *m_pTestApp;
	//CDvmDataset *m_pTesters;   //������Ա��Ϣ  shaolei  20211018
	CTestGlobalDatasMngr *m_pTestGlobalDatasMngr; //����ȫ�����ݹ���2017-4-14���
	CDvmDataset *m_pExtendRptTemplateDef;
	CDataGroup *m_pHdRes;  //2023-5-6  lijunqing  ��Ӧ���׮�Զ�����ϵͳ��Ӳ����Դ������
	CDataGroup *m_pItemsTec;  //2023-10-23 shaolei   ����windows�����Ҫ����д�������еġ�����Ҫ�󡱡����������ݱ���С��λ�����ɱ༭
	CDataGroup *m_pAinDataMapCfg;  //2023-11-14 ң�����ӳ�䡣�ڵ���word����ʱ����Ҫ����ӳ�䡣������ָ���¼��ģ����

	CScriptTextMngr *m_pScriptLibGlobal; //�ű��������
	CScriptTextMngr *m_pScriptLibLocal; //�ű��������
	CItemsRsltExprScriptMngr *m_pItemsRsltExprScriptMngr; 
	long   m_nIsSaveRptToDB;
	CTestMacros *m_pTestMacros;

	CGbCommCmdConfig m_oGbCommCmdConfig;	//ͨѶ������
	CTestTypes m_oTestTypes;    //�������Ͷ���

// 	CScriptDataVariables m_oScriptDataVariables;  //��ҵָ�������ʱ����

	CString m_strScriptMngrFile;
	CString m_strPpEngineProgID;
	CString m_strIecfgFile;  //�����ǵ������ļ�

#ifdef CGuideBook_with_iecfg_file
	CIecCfgDevice *m_pIecCfgDevice;
	CDataType *m_pIecfgDataType;
#endif
	
	CString m_strGuideBookFileType;    //ģ������ͣ�gbxml�� stxml
	BOOL m_bIsInGbWizardState;
	long m_nTestTimeLong;   //�����ܵ�ʱ�䳤��
	DWORD m_dwIsTestError;

	CString m_strAotuSaveReportFileName;   //�Զ�����Ĳ��Ա�����ļ���
	CString m_strGbXmlFile;   //����ģ���ļ�
	CString m_strGuideBookFile;    //��ʱ����������ģ��༭ģʽ����¼�򿪵�ģ���ļ����Զ�����ģʽ����¼�����ļ�

	BOOL m_bWSetsUseMinMax;
	
	//�ű��ĸ�ʽ��LUA��XVM   //2020-6-2
	CString m_strScriptType; 
	long m_nScriptType;   
	long m_nXvmLength;
	BYTE *m_pXvmTasmBuffer;

	//2021-11-17  lijunqing
	long m_nGbDevSaveStruDescFile; 
	long m_nGbDevSaveStruDescDsv; 

	////2026-6-18  lijunqing Ϊ����Դ���벿����Ŀ�ķ��㣬������ϣ�����������ȥ����ǰ��Ŀ
	BOOL m_bCanRemoveItemTestFinished;

	//Serialize mathods
	virtual long Serialize(CBinarySerialBuffer &oBinaryBuffer);   //lijunqing 2020-07-07
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()				{		return GBCLASSID_GUIDEBOOK;											}
	virtual BSTR GetXmlElementKey()	{      return CGbXMLKeys::g_pGbXMLKeys->m_strGuideBookKey;	}
	virtual void InitAfterRead();
	virtual BOOL CanPaste(UINT nClassID);

	//Interface Mathode
	void SetGuideBookName(const CString &strName);
	void SetBinaryFileName(const CString &strName);
	CExBaseObject* GetJobGuide();
	CDvmDataset* GetGlobalDatas(BOOL bCreate=FALSE);
	CDvmDataset* GetTestAppDefine(BOOL bCreate);
	CDvmDataset* GetTestApp(BOOL bCreate);
	CDataGroup* GetTestApps(BOOL bCreate);  //2023-6-17  lijunqing
	CDvmDataset* GetExtendRptTemplateDef(BOOL bCreate);
	CDvmDataset* FindGlobalDataset(const CString &strID);
	CExBaseObject* GetItemContainer();
	CScriptTextMngr* GetScriptLibGlobal()	{	return m_pScriptLibGlobal;	}
	CScriptTextMngr* GetScriptLibLocal()	{	return m_pScriptLibLocal;	}
	CItemsRsltExprScriptMngr * GetItemsRsltExprScriptMngr()	{	return m_pItemsRsltExprScriptMngr;	}
	CScriptText* FindScriptText(const CString &strID);
	CItemsRsltExprScript* FindItemsRsltExprScript(const CString &strID);
	long GetScriptLibItems();

	void FreeGuideBook();
	void FreeGuideBook_ExceptItems(const CString &strItemID, CExBaseList *pListBk);
	long Open(const CString &strFile, BOOL bOnlyReadAttr = FALSE);
	long OpenBinaryFile(const CString &strFile, long nRWReportFileMode, BOOL bOnlyReadAttr = FALSE);
	long SaveBinaryFile(const CString &strFile, long nRWReportFileMode=0);
	long OpenXMLFile(const CString &strFile, BOOL bOnlyReadAttr = FALSE,const long &nXmlRWType = _PUGI_XML_TYPE_);
	long OpenXMLFile_DscFile(const CString &strFile, const long &nXmlRWType = _PUGI_XML_TYPE_);  //��ģ��ṹ�����ļ� shaolei 20210226 
	long OpenVisioFile(const CString &strFile);
	long OpenXmlReportFile(const CString &strFile,const long &nXmlRWType = _PUGI_XML_TYPE_);
	long SaveXMLFile(const CString &strFile);
	long SaveFinalXMLReport(const CString &strFile);
	long BuildGbexe();

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	void OpenCommConfigFile(const CString &strCommConfigFile);
	void OpenTestTypeConfigFile(const CString &strConfigFile);
	void InitTestMacros();
	void OpenCommConfigFile();
	void OpenTestTypeConfigFile();
	void GetExtendRptFilePath(CStringArray &astrFile);

	BOOL IsGuideBookFile()			{	return m_strGuideBookFileType == g_strGbFileFilter;		}
	BOOL IsGuideBookTemplateFile()	{	return m_strGuideBookFileType == g_strTGbFileFilter;	}
	void SetGuideBookFileType()			{	m_strGuideBookFileType = g_strGbFileFilter;		}
	void SetGuideBookTemplateFileType()	{	m_strGuideBookFileType = g_strTGbFileFilter;	}
	CDevice* GetDevice();
	long GetDevice(CExBaseList &oListDevice);
	long GetAllCpus(CExBaseList &oListCpus);

	BOOL Is61850Protocol();
	BOOL IsScriptTextExist(CScriptText *pScriptText);

	void InitGuideBook();

	void RemoveExpandDatas();
	void ImportExpandDatas();
	void ImportExpandDatas(CDvmDataset *pExpandDatas);
	void ImportExpandDatas(CDevice *pDevice);
	void UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew);
	CString GetExpandFile();
	void OpenExpandFile(CDvmDataset *pDataset);
	void OpenExpandFile(CDvmDataset *pCmmCmdManyConfig, CDvmDataset *pTestApp, CDvmDataset *pDeviceAttr);

	void InitGuideBookAttrs();

	void SetIecfgFile(const CString &strIecfgFile);
	CString GetIecfgFile();
	BOOL IsReadOnly()	{	return (m_nIsReadOnly != 0);		}
	BOOL IsTestError();
	void InitTestError(CDvmData *pData);
	BOOL IsSaveRptToDB()		{	return m_nIsSaveRptToDB > 0;	}

#ifdef CGuideBook_with_iecfg_file
	CString WriteIecfgTempFile(CMacroTestPara *pPara, const CString &strExp);
	void InitByIecfFile();
	void CopyIecCfgFile(const CString &strDestGuideBookFile);
#endif


private:
	void InitAfterReadGb();
	void InitAfterReadGbt();
	void InitGlobalDatas(CExBaseList &listDatas);

	void ReadAttr(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	BOOL m_bOpenBinaryFileSucc;

public:
	void InitGlobalDatas_TestDefine();
	void InitGlobalDatas();
	void AddGlobalDatas();
	void AddTestMan(const CString &strName, const CString &strID);
	BOOL SetTestBeginTime();
	BOOL SetTestEndTime();
	void SetTestTime(CDvmData *pTestBeginTime, CDvmData *pTestEndTime);
	void SetgVmProgID(const CString &strVmProgID);
	BOOL SetTestError(const CString &strTestError);
	BOOL IsTestFirstItem();
	BOOL IsGuideBookFirstCreate();
	void AddReportData(CShortData *pData);
	void AddReportData(CDvmData *pData);
	void AddReportData(const CString &strID, const CString &strValue);
	void AddReportData(const CString &strID, const CString &strName, const CString &strValue);
	void AddReportData(CDvmDataset *pDvmDataset);

	void InitMacroCharTestItems();
	void SetGlobalDatas(const CString &strReportSN, CDvmDataset *pDsDeviceAttr, CDvmDataset *pTestApp);
	void SetGlobalDatas_DeviceAttr(CDvmDataset *pDsDeviceAttr);
	void SetGlobalDatas_DeviceAttr(CDvmData *pTestDefineDvAttr);
	void SetGlobalDatas_TestApp(CDvmDataset *pTestApp);
	void SetGlobalDatas_InspectionBases(CDvmDataset *pInspectionBases);  //�����׼
	void SetGlobalDatas_InspectionBases_Ex(CDataGroup *pInspectionBases);  //�����׼
	void SetGlobalDatas_Testers(CDvmDataset *pTesters);  //������Ա
	void SetGlobalDatas_GlobalDatas(CExBaseList *pGlobalDatas);  //�������ȫ������
	void SetTestAppDefine(CDvmDataset *pTestAppDefine);
	void AddReportDatas_GlobalDatas();//������ȫ�����ݣ����ŵ��������棬�Ա���д����

	//2021-1-20  lijunqing
	BOOL IsOfflineTestMode();
	void SetOfflineTestMode(BOOL bIsOfflineTestMode=TRUE);
	BOOL IsOfflineTestMode_Test();
	BOOL IsOfflineTestMode_ImportResult();
	BOOL SetOfflineTestMode_Test();
	BOOL SetOfflineTestMode_ImportResult();

protected:
	void InitMacroCharTestItems(CExBaseList *pList);

private:
	CDvmData *m_pTestBeginTime;
	CDvmData *m_pTestEndTime;

	void InitTimeData(CShortData *pData);
	void InitTimeData(CDvmData *pData);
	void InitTimeData(double &dTime, const CString &strFormat, CString &strValue);
	CValue* FindReportData(const CString &strID);

//////////////////////////////////////////////////////////////////////////
//����ȫ������
public:
	CTestGlobalDatasMngr* GetTestGlobalDatasMngr();

	void SetTestGlobaoDatasMngrs(CDataSet *pDataset);
	
	void AddSysPara(const CString &strID, const CString &strValue);
	CDvmData* GetTestBeginTime()	{	return m_pTestBeginTime;	}
	CDvmData* GetTestEndTime()		{	return m_pTestEndTime;		}

public:
// 	void AdjustByTkIDIndex();
	void AdjustByTkIDIndex(DWORD dwTkIDIndex, BOOL bDelete);
	void AdjustByTkIDIndex(const CString strTestType, BOOL bDelete);

private:
	void AdjustByTkIDIndex_Select(CExBaseList *pList, DWORD dwTkIDIndex);
	void AdjustByTkIDIndex_Delete(CExBaseList *pList, DWORD dwTkIDIndex);

public:
	//װ�õ�ȫ�ֲ���
	void GBS_SetGlobal_Str(const CString &strID, const CString &strValue);
	CString GBS_GetGlobal_Str(const CString &strID);
	BOOL GBS_GetGlobal_Str(const CString &strID, CString &strValue);

public:
	CStringTokenizer m_oStringTokenizer;

	long GBS_InitStrTok(char *pszString, char *pControl);
	long GBS_StrTokCount();
	const char* GBS_StrTokIndex(long nIndex);
	const char* GBS_StrTokNext();

public:
	CString GetReportTemplateRelativePath(const CString &strFullPath);
	CString GetReportTemplateFullPath(const CString &strRelPath);
	CString GetItemTempPath();

public:
	long m_nBinOffset;
	long m_nBoutOffset;
	CString m_strTestAppGroup;  //2019-1-14  lijq

	void OffsetBinary(long nBinOffset, long nBoutOffset);
	void OffsetBinary();
	BOOL UseBinaryOffset();
	void GetOffsetBinary(long &nBinOffset, long &nBoutOffset);

public:
	virtual void CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile);
	BOOL IsAuthority();
	BOOL IsAuthority(const CString &strAuthoritySN);
	void Encrypt(const CString &strAuthoritySN);
	CString GetEncryptString(const CString &strAuthoritySN);
	void UpdateAuthoritySN();
	CString GetAuthoritySN();
	BOOL GetAuthoritySN(CString &strAuthoritySN, CString &strName, CString &strMacroID, CString &strDevKey);
	void ValidateGbName();

	void InitGbDev();
	void InitGbDev(const CString &strUserCopSN, const CString &strAuthoritySN, const CString &strKeySN, const CString &strUserID);
	BOOL GetGbDev(CString &strUserCopSN, CString &strAuthoritySN, CString &strKeySN, CString &strUserID, CString &strDevKey);
	long GetGbDevValue(const CString &strKeyID, CString &strValue, BOOL bValDec);
	BOOL GetGbDevKey(CString &strDevKey);

public:
	BOOL IsScriptType_LUA();
	BOOL IsScriptType_XVM();
	void SetScriptType_LUA();
	void SetScriptType_XVM();
	void InitScriptTypeID();

	void FreeXvmTasmBuffer();
	void SetXvmTasmBuffer(BYTE *pBuffer, long nLen);

	//2021-4-4  lijunqing  
	BOOL HasLogic();
	CString GetSummaryRslt();
	void GetItemsCount(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount);
	void GetItemsCountByItemsType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount);

	//2023-3-29  lijunqing ͨ��Э�鲿�֣��޸�ΪSttIotģʽ.ͨ���������ñ��浽ȫ��������
	void SetCommConfig_DvmFile(const CString &strDvmFile);
	void SetCommConfig(CDataGroup *pCommConfig);
	void SetCommConfigs(CDataGroup *pCommConfig);
	CDataGroup* GetCommConfig(BOOL bCreateNew);
	CDataGroup* GetCommConfigs(BOOL bCreateNew);

	CDataGroup* GetHdRes();
	void SetHdRes(CDataGroup *pHdRes);
	CDataGroup* GetItemsTec();
	void SetItemsTec(CDataGroup *pItemsTec);
	CDataGroup* GetAinDataMapCfg();
	void SetAinDataMapCfg(CDataGroup *pAinDataMapCfg);
	CDataGroup* GetAinRatios();  //��ȡ����ֵ�ı����Ϣ����ȫ�����ݻ�ȡ
	void SetAinRatios(CDataGroup *pAinRatios);  //������ֵ�ı����Ϣ�����µ�ģ��ȫ������
	CDataGroup* GetTestApps();
	void SetTestApps(CDataGroup *pTestApps);
	void UpdateTestApps(CDataGroup *pTestApps);
	void AddMacroFileToTestApps();  //�ڲ�������Ϣ�У����ӹ����ļ���Ϣ

	////2026-6-18  lijunqing Ϊ����Դ���벿����Ŀ�ķ��㣬������ϣ�����������ȥ����ǰ��Ŀ
	//�Ӷ�����Ŀִ�����̵��㷨������ֻ������Ҫ���Ե���Ŀ��ȥ���Ѿ�������ɵ���Ŀ
	//������Դ����ɹ��󣬾Ϳ��Լ������²���
	BOOL CanRemoveItemTestFinished()	{	return m_bCanRemoveItemTestFinished;	}
	void InitCanRemoveItemTestFinished();

	//20230609 huangliang ���²�ͬ��ȫ�ֱ���ֵ
	void UpdateGlobalDifferentData(const CString &strID, const CString &strName, const CString &strDataType, const CString &strValue
		, const CString &strUnit=_T(""), const CString &strMin=_T(""), const CString &strMax=_T(""), const CString &strStep=_T(""));

	CDataTypeValue* GetDataTypeValue(const CString &strMacroID, const CString &strIDPath, const CString &strValue);
};


CString Gb_GetItemPath(CExBaseObject *pItem);
CExBaseObject* Gb_GetItem(CGuideBook *pGuideBook, CExBaseObject *pItem);
CExBaseObject* Gb_GetItem(CGuideBook *pGuideBook, const CString &strItemPath);
CExBaseObject* Gb_GetItem(CDevice *pGbDevice, const CString &strItemPath);

//shaolei 2022 0527  ͨ����Ŀ�����γɵ�·��ȥ���Ҷ�Ӧ�Ĳ�����Ŀ
CExBaseObject* Gb_GetItem_Name(CGuideBook *pGuideBook, const CString &strItemPath);
CExBaseObject* Gb_GetItem_Name(CDevice *pGbDevice, const CString &strItemPath);

CDataType* Gb_GetDataType(CExBaseObject *pGbObj, CDataTypes *pDataTypes, const CString &strDataType);
CString Gb_GetMacroTestPara_Iec61850Config(CMacroTestPara *pPara, const CString &strExpress);
CString Gb_GetReportFilePath(CExBaseObject *pObj, BOOL bHasRptFileFolder);
BOOL Gb_IsReadOnly(CExBaseObject *pObj);
CGuideBook* Gb_GetGuideBook(CExBaseObject *pObj);

CGbItemBase* Gb_GetItemByIndex(CExBaseList *pList, long nIndex);

//2019-1-6:�������ݶ����Ƿ�ϸ�Ĺ���   lijq
extern BOOL g_bAddDataErrorValueToRpt;
void Gb_AddDataErrorToRpt_Rslt(CValues *pValues, const CString &strValueID, long nRslt);

CString ats_GetBinaryTempFile(CGbItemBase* pItem);
CString ats_GetBinaryTempFile(const CString strTempFilePath, CGbItemBase* pItem);
void gb_ClearReportDatasByMap(CExBaseList *pList, const CString &strTempFilePath, BOOL bIsWriteTestTempFile);
void gb_ClearItemInDbState(CExBaseList *pList, const CString &strTempFilePath, BOOL bIsWriteTestTempFile);

//2020-02-03  lijq   ����ģ��༭������Զ��������֮��������ݵĽ���
#ifndef _PSX_QT_LINUX_
#include "../../../System/Module/XAtsSysSvrClient.h"
BOOL Gb_GetItemPara(const CString &strExeModule, CExBaseObject *pItem, const CString &strGbXml, BOOL bOpenModule);
BOOL Gb_SetItemPara(const CString &strExeModule, CExBaseObject *pItem, const CString &strGbXml, BOOL bOpenModule);
void OnXAtsSvrClientMsg_GetItemPara(const CString &strExeModule, CGuideBook *pGuideBook, AtsSysSvr::CSysMsg &oSysMsg, BOOL bOpenModule);
CGbItemBase* OnXAtsSvrClientMsg_SetItemPara(CGuideBook *pGuideBook, AtsSysSvr::CSysMsg &oSysMsg, CExBaseObject **ppOldItem);
#endif

//lijunqing 2020-7-9  
BOOL Gb_IsScriptType_LUA(CExBaseObject *pObj);
BOOL Gb_IsScriptType_XVM(CExBaseObject *pObj);

