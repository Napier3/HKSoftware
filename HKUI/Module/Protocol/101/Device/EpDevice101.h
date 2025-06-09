﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDevice101.h  CEpDevice101

#pragma once

#include "EpDevice_101Global.h"

#include "..\..\Device\EpDevice.h"

#include "EpDeviceNode101Yc.h"
#include "EpDeviceNode101Yk.h"
#include "EpDeviceNode101Yt.h"
#include "EpDeviceNode101Yx.h"

class CEpDevice101 : public CEpDevice
{
public:
	CEpDevice101();
	virtual ~CEpDevice101();


//重载函数
public:
	virtual UINT GetClassID() {    return EPDCLASSID_CEPDEVICE101;   }
	virtual BSTR GetXmlElementKey()  {      return CEpDevice_101XmlRWKeys::CEpDevice101Key();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
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
	CEpDeviceNode101Yc *m_pYc;
	CEpDeviceNode101Yk *m_pYk;
	CEpDeviceNode101Yt *m_pYt;
	CEpDeviceNode101Yx *m_pYx;

//私有成员变量访问方法
public:
	CEpDeviceNode101Yc* GetYc()	{	return m_pYc;	}
	CEpDeviceNode101Yx* GetYx()	{	return m_pYx;	}
	CEpDeviceNode101Yk* GetYk()	{	return m_pYk;	}
	CEpDeviceNode101Yt* GetYt()	{	return m_pYt;	}
};

