//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcNetDevice.h  CEmcNetDevice

#pragma once

#include "MonitorCapConfigGlobal.h"



class CEmcNetDevice : public CExBaseObject
{
public:
	CEmcNetDevice();
	virtual ~CEmcNetDevice();


	CString  m_strProtocol;
	long  m_nUDP;
	long  m_nTCP;
	long  m_nOther;
	long  m_nCapAllIP;
	long  m_nNetCardIndex;
//重载函数
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCNETDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcNetDeviceKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

