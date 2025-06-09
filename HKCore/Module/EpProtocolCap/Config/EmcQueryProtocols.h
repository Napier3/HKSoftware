//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcQueryProtocols.h  CEmcQueryProtocols

#pragma once

#include "MonitorCapConfigGlobal.h"

//#include "MonitorCapConfig.h"

#include "EmcQueryProtocol.h"

class CEmcQueryProtocols : public CExBaseList
{
public:
	CEmcQueryProtocols();
	virtual ~CEmcQueryProtocols();


//重载函数
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCQUERYPROTOCOLS;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcQueryProtocolsKey();     }
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
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return CEmcQueryProtocol::InitListCtrlColumnsFunc;	}

//私有成员变量
private:

//私有成员变量访问方法
public:
};

