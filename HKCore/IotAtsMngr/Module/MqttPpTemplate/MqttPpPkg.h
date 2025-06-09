//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpPkg.h  CMqttPpPkg

#pragma once

#include "MqttPpCfgGlobal.h"

#include "../../../Module/DataMngr/DvmData.h"


class CMqttPpPkg : public CDvmData
{
public:
	CMqttPpPkg();
	virtual ~CMqttPpPkg();


	CString  m_strDs;
//重载函数
public:
	virtual UINT GetClassID() {    return MQTTCLASSID_CMQTTPPPKG;   }
	virtual BSTR GetXmlElementKey()  {      return CMqttPpCfgXmlRWKeys::CMqttPpPkgKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL IsMatchPkg(int nPkgType,int nCtrlType,int nRequestSetFlag);
	BOOL IsReadAinPkg();
};

