
#pragma once

#include "PoMmsLogicDevice.h"
#include "PoMmsDataInterface.h"
// CPoMmsDevice 命令目标

#include "../MmsDatasetMapTool.h"

class CPoMmsDevice
{
public:
  void Attatch(CPxiDeviceCommCmdMessage *p)   {   m_pPxiDeviceCommCmdMessage = p; }
  void AttachProgress(CThreadProgressInterface *pProgress);

public:
	CShortData  m_oShortData;
	CDvmDataset m_oDsAttr;
	long m_nDeviceIndex;
	ACSI_NODE *m_pACSI_NODE;
	MMS_ADDR_VECTOR *m_pJournalDatas;//zhouhj 20180322 用于关联日志容器
	CString m_strProcedureID;

	CString m_strDeviceFile;
	CString m_strLastOpenDeviceFile;
	CExBaseList m_listDataInterface;
	BOOL m_bHasCreateDataInterface;
	CString m_strReadSoeDsPath;
    CPxiDeviceCommCmdMessage *m_pPxiDeviceCommCmdMessage;
	CThreadProgressInterface *m_pProgress;

protected:
	CDvmDeviceMap m_oDvmDeviceMap;
	CString m_strRecordPath;
	CString m_strCmdIdParaDsPath;

	CMmsDatasetMapTool m_oMmsDatasetMapTool;

	CPoMmsDataSet *m_pNewTempPoDataset;
	void FreeTempPoDataset()	{		if (m_pNewTempPoDataset != NULL)	{	delete m_pNewTempPoDataset; m_pNewTempPoDataset = NULL;}	}

public:
	CPoMmsDevice();
	virtual ~CPoMmsDevice();

	virtual void OnFinalRelease();
	void InitChangeSetZone(long &nZone);
	void InitRegisterRptPara();

	void GetVariableVal(const CString &strID, long &nVal, long nDefaultVal);
	void GetVariableVal(const CString &strID, __int64 &nVal, __int64 nDefaultVal);
	void GetVariableVal(const CString &strID, float &fVal, float fDefaultVal);
	void GetVariableVal(const CString &strID, CString &strVal, const CString &strDefaultVal);
	void GetVariableVal(const CString &strID, CTime &tmVal);
	void GetVariableVal(const CString &strID, BOOL &bVal,BOOL bDefaultVal);

	BOOL CmdNeedDsPath(const CString &strCmdID);
	virtual BOOL WriteEnaOne(long nDeviceIndex, long  nLdIndex);
	BOOL GetDataIndex_DataID(const char *strDsKey, long &nLdIndex, long &nDsIndex, long &nDaIndex, CString &strRetDataID);
	BOOL GetDataIndex_DataID(long &nLdIndex, long &nDsIndex, long &nDaIndex, CString &strRetDataID);
	BOOL GetCmdPara_Of_DataID(const CString &strParaKey, long &nLdIndex, long &nDsIndex, long &nDaIndex, CString &strRetDataID);
	virtual BOOL ReadOne();
	BOOL SetDataRef(const CString &strDsPath);
	CString GetDsPathMap(const CString &strDsPath);
	BOOL    GetDataPathMap(const CString &strDsPath, CString &strLdID, CString &strDsID, CString &strDataID);
	BOOL    GetDataPathMap_DsKey(const CString &strDsKey, const CString &strDsPath, CString &strLdID, CString &strDsID, CString &strDataID);

	long GetCmdID(const CString &strCmdID, long &nCmdID, long &nCmdState, long &wParam, long &lParam);

	void GetFilePaths(const CString &strFolderPath ,CString &strFiles ,CStringArray &arrFilePaths);
	void log_WriteRcdPath(const CString &strPath);

	CDvmDeviceMap* GetDvmDeviceMap();
	BOOL IsDvmDeviceMapExist();

protected:
	void InitDataAttr(const CString &strAttrID);
	void InitDataAttr(const CString &strAttrID, CString &strValue);

	virtual void InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, const CString &strDsPath);
	virtual void InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strDsPath);
	virtual void InitReadJournalFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strJournalName);
	CString GetJournalName(long nLdIndex,const CString &strDsPathTemp);

protected:
	virtual BOOL Run_CMDID_writesetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
	virtual void Run_CMDID_writeena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, const CString &strTitle, const char* pszKey);
	virtual void Run_CMDID_readena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
	virtual long IniSetWriteFuncParasEx(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, long nZone);
	virtual void Run_CMDID_readsetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
	virtual void Run_CMDID_readparameter(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex);
	BOOL IsValidIP(const CString &strIP);//zhouhj 判断字符串是否为有效IP地址

public:
	virtual long CommConfig(const CString &strCmmConfig);
	virtual CPoMmsLogicDevice* GetItem(long nIndex);
	virtual CPoMmsDataSet* FindDataSet(const CString &strDataSetName);
	virtual long RunProcedure(const CString &strProcedureID, const CString &strDatasetPath);

	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(CString newVal);
	long IsConnectSuccessful(void);
	long GetCount(void);
	CPoMmsData* FindData(const CString &strPath);
	long RunProcedureEx(const CString &strProcedureScript);
	long AttachSystemWndMsg(ULONG hWnd, ULONG nMsgID);
	long RegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID);
	long UnRegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID);
	long RegisterDataChangedWndMsg(const CString &strDataPath, ULONG hWnd, ULONG nWMsgID);
	long UnRegisterDataChangedWndMsg(const CString &strDataPath);
	virtual long UnLoad(void);
	CString GetXmlData(void);
	long SetXmlData(const CString &bstrXmlData);
	CString GetXmlDataEx(const CString &strDatasetPath);
	long SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData);
	CPoMmsDataInterface* GetDataInterface(void);
	long ConnectDevice(void);
	CString GetAttrByID(const CString &strAttrID);
	long SetAttrByID(const CString &strAttrID, const CString &strValue);
	long SaveDvmFile(const CString &strDvmFile);
	long SetCommConfig(const CString &strCommConfig);
	CString GetCommConfig(void);
	CString GetXmlDataLD(void);
	CString GetLogsXml(void);

    //2020-9-8  lijunqing
    virtual BOOL InitCmmConfig(CDataGroup *pGroup, BOOL bConnect);

public:
	void mms_PostDeviceSysMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam);
	void mms_PostDeviceCommCmdMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam);
	void mms_PostDeviceEventMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam);
	void mms_PostMmsReportMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam);

};


