//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcQueryAddrMap.h  CEmcQueryAddrMap

#pragma once

#include "MonitorCapConfigGlobal.h"



class CEmcQueryAddrMap : public CExBaseObject
{
public:
	CEmcQueryAddrMap();
	virtual ~CEmcQueryAddrMap();


	CString  m_strSrc;
	CString  m_strDest;
//重载函数
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCQUERYADDRMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcQueryAddrMapKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	static long InitListCtrlColumnsFunc(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual PFuc_InitListCtrlColumns* GetInitListCtrlColumnsFunc()	{	return InitListCtrlColumnsFunc;	}

//私有成员变量
private:

//私有成员变量访问方法
public:
};

