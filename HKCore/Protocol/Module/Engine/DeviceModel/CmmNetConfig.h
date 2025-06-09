#pragma once
#include "../../../../module/baseclass/exbaselist.h"
#include "CmmTcpClientConfig.h"
#include "CmmTcpServerConfig.h"
#include "CmmUdpClientConfig.h"
#include "CmmUdpServerConfig.h"

class CCmmNetConfig :	public CExBaseList
{
public:
	CCmmNetConfig(void);
	virtual ~CCmmNetConfig(void);

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID(){return DMCLASSID_NET_CONFIG;};

	//串行化
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strNetKey;     }
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

	CExBaseObject* GetChildByClassID(UINT nClassID);

public:
	CCmmTcpServerConfig* GetConfigTcpServer();
	CCmmTcpClientConfig* GetConfigTcpClient();
	CCmmUdpServerConfig* GetConfigUdpServer();
	CCmmUdpClientConfig* GetConfigUdpClient();

	CCmmTcpServerConfig* AddConfigTcpServer();
	CCmmTcpClientConfig* AddConfigTcpClient();
	CCmmUdpServerConfig* AddConfigUdpServer();
	CCmmUdpClientConfig* AddConfigUdpClient();

	void DeleteConfigTcpServer();
	void DeleteConfigTcpClient();
	void DeleteConfigUdpServer();
	void DeleteConfigUdpClient();

	virtual void SetRemoteIP(const CString &strIP, long nPort);
};
