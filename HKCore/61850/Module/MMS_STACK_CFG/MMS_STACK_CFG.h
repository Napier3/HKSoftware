//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MMS_STACK_CFG.h  CMMS_STACK_CFG

#pragma once

#include "MMS_STACK_CFGGlobal.h"


#include "StkCfg_MMS.h"
#include "StkCfg_Transport.h"
#include "StkCfg_NetworkAddressing.h"

class CMMS_STACK_CFG : public CExBaseList
{
public:
	CMMS_STACK_CFG();
	virtual ~CMMS_STACK_CFG();


//重载函数
public:
	virtual UINT GetClassID() {    return MMSCLASSID_CMMS_STACK_CFG;   }
	virtual BSTR GetXmlElementKey()  {      return CMMS_STACK_CFGXmlRWKeys::CMMS_STACK_CFGKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CString m_strFilePath;
	CStkCfg_NetworkAddressing *m_pNetworkAddressing;

//私有成员变量访问方法
public:
	void Open_MMS_STACK_CFG_Outer();
	void Save_MMS_STACK_CFG_Outer();
	CStkCfg_RemoteAddressList* GetRemoteAddressList();

	void WriteIpToVMDFile();
};

