#pragma once

#include "../../SttStudio/Module/SttGlobalDef.h"
#include "AutoTestGlobalDefine.h"
#include "../../Module/BaseClass/XObjectRefBase.h"
#include "../../Module/BaseClass/ExBaseList.h"

#define AtsRpcTestDef_devices      _T("devices")
#define AtsRpcTestDef_device      _T("device")
#define AtsRpcTestDef_test_apps   _T("test-apps")
#define AtsRpcTestDef_test_app   _T("test-app")
//shaolei 20211015
#define AtsRpcTestDef_InspectionBases      _T("InspectionBases")   //�������ݡ������׼
#define AtsRpcTestDef_InspectionBasis      _T("InspectionBasis")
#define AtsRpcTestDef_Testors   _T("Testors")  //����Ա
#define AtsRpcTestDef_MainInspection   _T("MainInspection")   //����
#define AtsRpcTestDef_Proofreader   _T("Proofreader")   //У��
#define AtsRpcTestDef_Checker   _T("Checker")   //���
#define AtsRpcTestDef_GlobalDatas   _T("GlobalDatas")   //ȫ������


#define WM_ATS_CREATETEST  (WM_USER+1444)
#define WM_ATS_TEST              (WM_USER+1445)
#define WM_ATS_TEST_PARA_OPENGBRPTFILE   (WM_USER+1446)
#define WM_ATS_TEST_GETALLTESTITEMS   (WM_USER + 1447)
#define WM_ATS_TEST_GETTESTITEMSREPORTS  (WM_USER + 1449)

//STTЭ�����õ����Զ�������Ϣ����
#define WM_STT_CREATETEST	(WM_USER + 1450)
#define WM_STT_CLOSETEST    (WM_USER + 1451)
#define WM_STT_BEGINETEST	(WM_USER + 1452)
#define WM_STT_FINISHINPUTDATA   (WM_USER + 1453)
#define WM_STT_CREATETEST_EX   (WM_USER + 1454)
#define WM_STT_STOPTEST	(WM_USER + 1455)
#define WM_STT_OPENGBRPTFILE	(WM_USER + 1456)
#define WM_STT_ADJUSTMAINWND	(WM_USER + 1457)
#define WM_STT_EXPORTREPORT	(WM_USER + 1458)
#define WM_STT_FREETESTCONTROL (WM_USER + 1459)
#define WM_STT_CREATETEST_BY_CMD   (WM_USER + 1460)
#define WM_STT_TESTPOINT   (WM_USER + 1461)    //���Ե�ǰ��
#define WM_STT_TESTBELOW   (WM_USER + 1462)    //�ӵ�ǰ�ʼ����
#define WM_STT_TESTALLINLEGIBLEITEMS   (WM_USER + 1463)    //����ȫ�����ϸ���Ŀ
#define WM_STT_ADJUSTREPORT   (WM_USER + 1464)    //��������
#define WM_STT_CREATEDEVICEREFS 	(WM_USER + 1465)   //�����豸ͨѶ����
#define WM_STT_SENDTESTCMD 	(WM_USER + 1466)   //ת��TestCmd
#define WM_STT_GENWORDRPT_BYTOOL   (WM_USER + 1467)  //ͨ��CRptTemplate_GendocTool����word���档
#define WM_STT_CLEARREPORTSRSLTS   (WM_USER + 1468)    //�����������
#define WM_STT_RELEASEPPENGINE   (WM_USER + 1469)    //ReleasePpEngine
#define WM_STT_CONNECTSTTSERVER_19814	(WM_USER + 1470)   //LINUX�£�����������ͨ����Ϣȥ���Ӳ����ǵײ����

#define WM_ATS_TEST_PARA_BEGINTEST                    0
#define WM_ATS_TEST_PARA_STOPTEST                     1
#define WM_ATS_TEST_PARA_CLOSETEST                    2
#define WM_ATS_TEST_PARA_EXPORTRPTS                   3
#define WM_ATS_TEST_PARA_VIEWITEMRPT                  4
#define WM_ATS_TEST_PARA_TESTALLINLEGIBLEITEMS        5
#define WM_ATS_TEST_PARA_TESTPOINT                    6
#define WM_ATS_TEST_PARA_TESTBELOW                    7

class CAtsTestDefineInterface : public CXObjectRefBase
{
public:
	CAtsTestDefineInterface();
	virtual ~CAtsTestDefineInterface();

	void SetTestMode_gbrpt();
	void SetTestMode_gbmdmrpt();

	void SetReportMode_WPS();
	void SetReportMode_WORD();
	void SetReportMode_SYSTEM();
	void SetReportMode_NONE();

	void FreeAtsTestDefineInterface();

	CString GetDeviceAttrByID(long nIndex, const CString &strAttrID);

	virtual CExBaseList* GetDeviceAttrs(long nIndex = 0);

public:
	CExBaseList *m_pTestApps;
	CExBaseList *m_pDevices;
	//shaolei 20211015
	CExBaseList *m_pInspectionBases;//���ڽ��������׼
	CExBaseList *m_pTesters;//���ڽ�������Ա��Ϣ
	CExBaseList *m_pGlobalDatas;  //��¼��Ҫ��д�����ȫ�����ݣ����磺��������

	CString m_strTestMode;
	CString m_strFolder;
	CString m_strReportMode;

	CString m_strTaskName;

protected:
	CString m_strGbxmlFile;
	CString m_strEngineProgID;
	CString m_strPpXmlFile;
	CString m_strDvmFile;


public:
	virtual BOOL GetGuideBookFile(CString &strGbFile);
	virtual BOOL GetEngineProgID(CString &strEngineProgID);
	virtual BOOL GetEngineMode(CString &strEngineMode);   //shaolei 2023-11-2
	virtual BOOL GetPpxmlFile(CString &strPpxmlFile);
	virtual BOOL GetDvmFile(CString &strDvmFile);
	virtual BOOL GetTestType(CString &strTestType);
	virtual BOOL GetDeviceSN(CString &strDeviceSN, long nIndex);  //shaolei 2023-11-3
	virtual BOOL GetDvmFile(CString &strDvmFile, long nIndex);
	virtual BOOL GetPpxmlFile(CString &strPpxmlFile, long nIndex);

public:
	virtual void InitTestTaskName(const CString &strModel);
	virtual void SetTestTaskName(const CString &strTaskName);
	virtual void SetTestTmplateFile(const CString &strGbxmlFile, const CString &strEngineProgID, const CString &strPpXmlFile, const CString &strDvmFile);
	virtual CExBaseObject* AddDeviceTest(const CString &strDvmFile, const CString &strBRCode, long nPort, long nBaudRate, long nByteSize, long nStopBit
		, long nParity, long nBinOffset, long nBoutOffset, long nUdc_Power, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode
		, const CString &strSignPath, const CString &strDevIndex);
	virtual CExBaseObject* AddDeviceTest(const CString &strBRCode, long nPort, long nBaudRate, long nByteSize, long nStopBit, long nParity, long nBinOffset
		, long nBoutOffset, long nUdc_Power, long nTestAppGroup, long nAcCurr, const CString &strDevOnlyCode, const CString &strSignPath
		, const CString &strDevIndex);

	virtual CExBaseObject* AddDeviceTest(CExBaseObject *pDeviceAttrs);
	virtual CExBaseObject* AddDeviceTest(const CString &strBRCode);
	virtual CExBaseObject* AddDeviceTest(const CString &strIP, long nPort);
	virtual CExBaseObject* SetDeviceTest(long nIndex, const CString &strIP, long nPort);
	virtual CExBaseObject* AddDeviceTest(long nPort, long nBaudRate, long nByteSize, long nStopBit, long nParity, long nBinOffset, long nBoutOffset, long nCOM);

	virtual void AddTestApp(const CString &strAppType, const CString &strFactory, const CString &strModel, const CString &strIP, const CString &strSN, const CString &strTime);
	virtual void AddTestApp(CExBaseObject *pData);
};

