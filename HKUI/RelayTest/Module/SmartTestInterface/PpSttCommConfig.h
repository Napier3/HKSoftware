#pragma once

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"

class CPpSttCommConfig : public CDataGroup
{
public:
	CPpSttCommConfig();
	virtual ~CPpSttCommConfig();

    virtual void InitAfterRead();

	void InitEngine(const CString &strDeviceSN, const CString &strEngineID, const CString &strPpXmlFile, const CString &strDvmFile);
	void Set_DeviceSN(const CString &strDeviceSN);
	void Set_PpXmlFile(const CString &strPpXmlFile);
	void Set_EngineID(const CString &strEngineID);
	void Set_DvmFile(const CString &strDvmFile);

    bool Is_MmsEngine();
    bool Is_CmsEngine();
    bool Is_PpEngine();
	bool Is_PpEngine_Net();
	bool Is_PpEngine_Serial();

	CString Get_DeviceSN();
    CString Get_DvmFile();

	//获取Ppxml项内容
	CString Get_PpxmlFile(); //2023.11.15 lichao PNS331 新增
	CDvmData* Get_TcpClient();
	CDvmData* Get_TcpServer();
	CDvmData* Get_UdpClient();
	CDvmData* Get_UdpServer();
	CDvmData* Get_Serial();
	CDvmData* Get_MMS();
	CDvmData* Get_CMS();

	CDvmData* Add_TcpClient();
	CDvmData* Add_TcpServer();
	CDvmData* Add_UdpClient();
	CDvmData* Add_UdpServer();

	void Set_Net();
	CDvmData* Set_TcpClient();
	CDvmData* Set_TcpServer();
	CDvmData* Set_UdpClient();
	CDvmData* Set_UdpServer();

	CDvmData* Set_Serial();
	CDvmData* Set_MMS();
	CDvmData* Set_CMS();

    void MMS_Init(const CString &strLocalIP, const CString &strRemoteIP, long nRemotePort, const CString &strPsw, const CString &strKey);
	void MMS_Set_LocalIP(const CString &strLocalIP);
    void MMS_Set_EncryptPsw(const CString &strPsw);
    void MMS_Set_EncryptKey(const CString &strKey);
	void MMS_Set_RemoteIP(const CString &strRemoteIP);
	void MMS_Set_RemotePort(long nRemotePort);


    void CMS_Init(const CString &strLocalIP, const CString &strRemoteIP, long nRemotePort, const CString &strPsw, const CString &strKey);
	void CMS_Set_LocalIP(const CString &strLocalIP);
     void CMS_Set_EncryptKey(const CString &strKey);
     void CMS_Set_EncryptPsw(const CString &strPsw);
	void CMS_Set_RemoteIP(const CString &strRemoteIP);
	void CMS_Set_RemotePort(long nRemotePort);

	void PpEngineNet_Init(const CString &strLocalIP,const CString &strRemoteIP, long nRemotePort);

  void Serial_Set_port_number(long nPortNumber);
    void Serial_Set_baud_rate(long nBaudRate);
    void Serial_Set_byte_size(long nByteSize);
    void Serial_Set_stop_bit(long nStopBit);
    void Serial_Set_parity(long nParity);

    void TcpClient_Set_LocalIP(const CString &strLocalIP);
    void TcpClient_Set_LocalPort(long nLocalPort);
    void TcpClient_Set_RemoteIP(const CString &strRemoteIP);
    void TcpClient_Set_RemotePort(long nRemotePort);

    void TcpServer_Set_LocalIP(const CString &strLocalIP);
    void TcpServer_Set_LocalPort(long nLocalPort);

    void UdpServer_Set_LocalIP(const CString &strLocalIP);
    void UdpServer_Set_LocalPort(long nLocalPort);
    void UdpServer_Set_MuticastIP(const CString &strMuticastIP);

    void UdpClient_Set_LocalIP(const CString &strLocalIP);
    void UdpClient_Set_LocalPort(long nLocalPort);
    void UdpClient_Set_MuticastIP(const CString &strMuticastIP);
    void UdpClient_Set_RemoteIP(const CString &strRemoteIP);
    void UdpClient_Set_RemotePort(long nRemotePort);

    CString  TcpClient_Get_RemotePort();
    CString  TcpClient_Get_RemoteIP();
    CString  TcpClient_Get_LocalPort();
    CString  TcpClient_Get_LocalIP();

    CString  TcpServer_Get_LocalPort();
    CString  TcpServer_Get_LocalIP();

    CString  UdpServer_Get_MuticastIP();
    CString  UdpServer_Get_LocalPort();
    CString  UdpServer_Get_LocalIP();

    CString  UdpClient_Get_RemotePort();
    CString  UdpClient_Get_RemoteIP();
    CString  UdpClient_Get_LocalPort();
    CString  UdpClient_Get_LocalIP();
    CString  UdpClient_Get_MuticastIP();

    CString  Serial_Get_port_number();
    CString  Serial_Get_baud_rate();
    CString  Serial_Get_byte_size();
    CString  Serial_Get_stop_bit();
    CString  Serial_Get_parity();

    CString MMS_Get_RemoteIP();
	CString MMS_Get_LocalIP();
    CString MMS_Get_EncryptKey();
    CString MMS_Get_EncryptPsw();

    CString CMS_Get_LocalIP();
    CString CMS_Get_EncryptKey();
    CString CMS_Get_EncryptPsw();
    CString CMS_Get_RemoteIP();
    CString CMS_Get_RemotePort();

	BOOL OpenCommConfigFile(const CString &strFile);
	void SaveCommConfigFile(const CString &strFile);
	void UpdateFilePath_UseAbs();//zhouhj 2023.12.6 更新文件路径,使用绝对路径方式
protected:
	CDataGroup *m_pCmmConfig;

	CDataGroup* GetCommConfig();
	CDataGroup* NewCommConfig();

    bool CmmConfigIsKey(BSTR bstrKey);
    bool CmmConfigIsKey(const CString &strKey);

	CDvmData* CmmCfg_GetByKey(const CString &strKey);
	CDvmData* CmmCfg_GetByKey(BSTR bstrKey);
	CDvmData* CmmCfg_SetByKey(const CString &strKey);
	CDvmData* CmmCfg_SetByKey(BSTR bstrKey);
	CDvmData* CmmCfg_AddByKey(const CString &strKey, BOOL bClearAll);
	CDvmData* CmmCfg_AddByKey(BSTR bstrKey, BOOL bClearAll);
	void CmmCfg_DelByKey(const CString &strKey);
	void CmmCfg_DelByKey(BSTR bstrKey);

	void dvmdata_set_value(CDvmData *pData, BSTR bstrKey, const CString &strValue);
	void dvmdata_set_value(CDvmData *pData, BSTR bstrKey, long nValue);
};

class CPpSttCommConfigs : public CDataGroup
{
public:
	CPpSttCommConfigs();
	virtual ~CPpSttCommConfigs();

	BOOL OpenCommConfigsFile(const CString &strFile);
	void SaveCommConfigsFile(const CString &strFile);

};


CString File_SmartTestCommConfig_mms();
CString File_SmartTestCommConfig_cms();
CString File_SmartTestCommConfig_pp();
