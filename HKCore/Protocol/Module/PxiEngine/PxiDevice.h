
#pragma once

#include "PxiLogicDevice.h"
#include "PxiDataInterface.h"

#include "../../../Module/DataMngr/ShortData.h"

// CPxiDevice 


//2022-11-18  lijunqing  PpEngine、MmsEngine、CmsEngine都有相关内的定义，统一定义
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"
/*
#define  ParaID_setzone      _T("Set_Zone_Index")
#define  ParaID_path      _T("path")

#define  ParaID_CmdState  _T("CmdState")
#define  ParaID_wParam    _T("wParam")
#define  ParaID_lParam    _T("lParam")

#define  ParaID_TrgOps_1    _T("TrgOps_1")
#define  ParaID_TrgOps_4    _T("TrgOps_4")

#define  CMDID_writeenaone  _T("writeenaone")
#define  CMDID_changesetzone  _T("changesetzone")
#define  CMDID_readain  _T("readain")
#define  CMDID_readsetting  _T("readsetting")
#define  CMDID_writesetting  _T("writesetting")
#define  CMDID_readena       _T("readena")
#define  CMDID_writeena       _T("writeena")
#define  CMDID_writedout       _T("writedout")
#define  CMDID_readparameter       _T("readparameter")
#define  CMDID_writeparameter       _T("writeparameter")
#define  CMDID_readsoe       _T("readsoe")
#define  CMDID_readsoeds       _T("readsoeds")
#define  CMDID_reset       _T("reset")
#define  CMDID_registerreport       _T("registerreport")
#define  CMDID_unregisterreport       _T("unregisterreport")
#define  CMDID_readzone        _T("readzone")
#define  CMDID_readdataset        _T("readdataset")
#define  CMDID_record_dir        _T("record_dir")
#define  CMDID_record_file        _T("record_file")
#define  CMDID_ReadMmsAttr        _T("readmmsattr")
#define  CMDID_WriteMmsAttr        _T("writemmsattr")

#define  CMDID_connect        _T("connect")
#define  CMDID_disconnect     _T("disconnect")
#define  CMDID_logmmserr      _T("logmmserr")
#define  CMDID_ReadDataOne       _T("readone")
#define  CMDID_SetDataRef       _T("setdaref")

#define     dsID_MmsDvmAttr         _T("dsmmsdvmattr")

//2020-5-21 lijunqing
#define  Pxi_ID_Procedure    _T("id-procedure")
*/

#include "../Engine/PpEngineDataMngrCntr.h"
#include "../Engine/PpEngineThreadBase.h"
#include "PxiEngineGlobal.h"

class CPxiDevice :public CPoDeviceProcedureInterface
{
public:
	virtual void OnProcedureEnd(const CString &strProcedure, WPARAM wParam, LPARAM lParam);
	virtual void OnSystemMsg(WPARAM wParam, LPARAM lParam);

	ULONG m_hClientMsgWnd;
	ULONG m_nClientMsgID;
	ULONG m_hClientSysMsgWnd;
	ULONG m_nClientSysMsgID;

	void StartProgress();
	void StopProgress();

	long m_nWriteDataCount;
	long m_nDataIndex;
	CDvmDataset *m_pCurrDataset;

	void RunProcedure_WriteSingle(const CString &strProcedureID);
	long RunProcedure_WriteAll(const CString &strProcedureID);
    void Attatch(CPxiDeviceCommCmdMessage *p)   {   m_pPxiDeviceCommCmdMessage = p; }
	BOOL IsWriteProcedure();

private:
	CDvmData* GetCurrWriteData();
	long GetCurrWriteDataCount();

	void PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam);
	void PostDeviceSysMessage(WPARAM wParam, LPARAM lParam);
//	BOOL IsWriteProcedure();//zhouhj 2024.9.12 修改为public

	void In_ConnectDevice(BOOL bConnect=TRUE);

public:
	CDvmDevice *m_pACSI_NODE;
	CString m_strProcedureID;
    CString m_strDatasetPathOfProcedure;  //2020-11-25  lijunqing
	CString m_strDeviceFile;
	CString m_strLastOpenDeviceFile;

	CPpEngineData *m_pEngineData;
	CString m_strDeviceID;
	CString m_strReadSoeDsPath;
	CDvmData  m_oShortData;
    CPxiDeviceCommCmdMessage *m_pPxiDeviceCommCmdMessage;

	static CPxiDevice* _New_CDevice(CPpEngineData *pEngineData, CString strDeviceID)
	{
		ASSERT (pEngineData != NULL);

		CPxiDevice *pPoDevice = new CPxiDevice();
		pPoDevice->m_pEngineData = pEngineData;
		pPoDevice->m_pEngineThread = (CPpEngineThreadBase*)pEngineData->m_pEngineThread;
		if (pEngineData->m_pPpDeviceRef->m_nDvmDeviceMode == PPTEMPLATE_DEVICEMODE_MULTI)
		{
			CDvmDevices* pDevices = (CDvmDevices*)pEngineData->m_pPpDeviceRef->GetDeviceModel();
			pPoDevice->m_pACSI_NODE = (CDvmDevice*)pDevices->SelectData(strDeviceID);
		}
		else
		{
			pPoDevice->m_pACSI_NODE = (CDvmDevice*)pEngineData->m_pPpDeviceRef->GetDeviceModel();
		}


		if (pPoDevice->m_pEngineThread != NULL)
		{
			pPoDevice->m_pCmmChannel = pPoDevice->m_pEngineThread->m_pDeviceCmmChannel;
		}

		return pPoDevice;
	}

	CDvmDevice* GetDevice()
	{
		return m_pACSI_NODE;
	}
	CPpEngineThreadBase* GetThread()
	{
		return m_pEngineThread;
	}
	CPpTemplate* GetTemplate()
	{
		if (m_pTemplateSel != NULL)
		{
			return m_pTemplateSel;
		}

		return m_pTemplate;
	}

	void Out_ConnectDevice();

public:
	CPpEngineThreadBase *m_pEngineThread;

	//模型/模板
	CPpTemplate *m_pTemplate;     //规约模板对象
	CPpTemplate *m_pTemplateSel;  //规约模板对象
	CDeviceCmmChannel *m_pCmmChannel;    //关联的设备通讯对象
	CExBaseList m_listDataInterface;
	BOOL m_bHasCreateDataInterface;


	CDvmDataset* GetReportDataset(const CString &strDatasetPath);
	void AddData2(const CString &strID, const CString &strValue);
	void AddData2(const CString &strID, const long &nValue);
	BOOL RunProcedure_Static();
	CString FindDataInterfaceValue(const CString &strID);
	void InitProcedureInterface(CDvmDataset *pDvmDataset);

//通讯端口设计
private:
	CDeviceCmmConfig   m_oDeviceCmmConfig;

	BOOL RunProcedure_ChnTest();
	BOOL RunProcedure_ChnTest_Serial();
	BOOL RunProcedure_ChnTest_UdpClient();
	BOOL RunProcedure_ChnTest_UdpServer();
	BOOL RunProcedure_ChnTest_TcpClient();
	BOOL RunProcedure_ChnTest_TcpServer();
	BOOL RunProcedure_ChnTest_Exit();

	void GetVariableVal(const CString &strID, long &nVal, long nDefaultVal);
	void GetVariableVal(const CString &strID, float &fVal, float fDefaultVal);
	void GetVariableVal(const CString &strID, CString &strVal, const CString &strDefaultVal);
	void GetVariableVal(BSTR strID, long &nVal, long nDefaultVal);
	void GetVariableVal(BSTR strID, float &fVal, float fDefaultVal);
	void GetVariableVal(BSTR strID, CString &strVal, const CString &strDefaultVal);

	void AddPachageSend();
	
public:
	CPxiDevice();
	virtual ~CPxiDevice();

	virtual void OnFinalRelease();

	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(CString newVal);
	long CommConfig(const CString &strCmmConfig);
	long IsConnectSuccessful(void);
	long GetCount(void);
	CPxiLogicDevice* GetItem(long nIndex);
	CPxiDataSet* FindDataSet(const CString &strDataSetName);
	CPxiData* FindData(const CString &strPath);
	long RunProcedure(const CString &strProcedureID, const CString &strDatasetPath);
	long RunProcedureEx(const CString &strProcedureScript);
	long AttachSystemWndMsg(ULONG hWnd, ULONG nMsgID);
	long RegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID);
	long UnRegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID);
	long RegisterDataChangedWndMsg(const CString &strDataPath, ULONG hWnd, ULONG nWMsgID);
	long UnRegisterDataChangedWndMsg(const CString &strDataPath);
	long UnLoad(void);
	CString GetXmlData(void);
	long SetXmlData(const CString &bstrXmlData);
	CString GetXmlDataEx(const CString &strDatasetPath);
	long SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData);
	CPxiDataInterface* GetDataInterface(void);
    CPxiDataInterface* GetDataInterface(CPxiDataInterface &oDataInterface);
    long ConnectDevice(void);
	CString GetAttrByID(const CString &strAttrID);
	long SetAttrByID(const CString &strAttrID, const CString &strValue);
	long SaveDvmFile(const CString &strDvmFile);
	long SetCommConfig(const CString &strCommConfig);
	CString GetCommConfig(void);

    //2020-9-8  lijunqing
    BOOL InitCmmConfig(CDataGroup *pGroup, BOOL bConnect);

	//shaolei 2023-9-11 通过定时器，读实时值。不发通讯消息，不弹进度条。仅在后台执行
	long RunProcedure_Timer_ReadAin();

public:
    CDvmDataset* FindDvmDataset(const CString &strDataSetName);

};
