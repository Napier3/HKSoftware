#pragma once
#include "ExBaseList.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "DeviceClassIDDefine.h"

#include "CmmNetConfig.h"
#include "CmmSerialConfig.h"
#include "CmmMmsConfig.h"

class CDeviceCmmConfig :	public CExBaseList
{
public:
	CDeviceCmmConfig(void);
	virtual ~CDeviceCmmConfig(void);


public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_DEVICECMMCONFIG;};

	//串行化
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
#ifndef _DeviceCmmConfig_with_no_pptemplate
	//打开文件
	BOOL OpenPpTemplateXmlFile(const CString &strFile, CString &strDeviceModelFile,const long &nXmlRWType = _PUGI_XML_TYPE_);
#endif

	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	CExBaseObject* GetChildByClassID(UINT nClassID);

public:
	CCmmMmsConfig* AddConfigMms();
	CCmmSerialConfig* AddConfigSerial();
	CCmmTcpServerConfig* AddConfigTcpServer();
	CCmmTcpClientConfig* AddConfigTcpClient();
	CCmmUdpServerConfig* AddConfigUdpServer();
	CCmmUdpClientConfig* AddConfigUdpClient();

	void ChangeToMmsMode();
	void ChangeToSerialMode();
	void ChangeToNetMode();

	CCmmMmsConfig* GetConfigMms();
	CCmmSerialConfig* GetConfigSerial();
	CCmmNetConfig* GetConfigNet();
	CCmmTcpServerConfig* GetConfigTcpServer();
	CCmmTcpClientConfig* GetConfigTcpClient();
	CCmmUdpServerConfig* GetConfigUdpServer();
	CCmmUdpClientConfig* GetConfigUdpClient();

	void DeleteConfigTcpServer();
	void DeleteConfigTcpClient();
	void DeleteConfigUdpServer();
	void DeleteConfigUdpClient();

	void InitBy(CDeviceCmmConfig *pCmmCfg);
	void InitByOnlyConfig(BSTR strCmmConfig);
	void InitByOnlyConfig(CDeviceCmmConfig *pCmmCfg);
	void SelectCmmCfgChannel(CExBaseList &listCmmCfg);
	CCmmNetConfig* GetNetConfig();

private:
	void InitByOnlyConfig(CExBaseList *pDestCmmCfg, CExBaseList *pSrcCmmCfg);
	void SelectCmmCfgChannel(CExBaseList *pListSrc, CExBaseList &listCmmCfg);

public:
    //2020-5-19  lijunqing
    BOOL InitCmmConfig(CDataGroup *pGroup);

	//2023-4-18 lijunqing
	void SetPort(long nPort);
	void SetPort(CExBaseList *pListSrc, long nPort);

protected:
     BOOL InitCmmConfig_Net_TcpClient(CDvmData *pData);
     BOOL InitCmmConfig_Net_TcpServer(CDvmData *pData);
     BOOL InitCmmConfig_Net_UdpClient(CDvmData *pData);
     BOOL InitCmmConfig_Net_UdpServer(CDvmData *pData);
     BOOL InitCmmConfig_Serial(CDvmData *pData);
};

CString pp_GetDeviceCmmCfgFile(const CString &strDeviceFile);
