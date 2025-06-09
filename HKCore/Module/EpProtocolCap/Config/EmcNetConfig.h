//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcNetConfig.h  CEmcNetConfig

#pragma once

#include "MonitorCapConfigGlobal.h"



class CEmcNetConfig : public CExBaseObject
{
public:
	CEmcNetConfig();
	virtual ~CEmcNetConfig();

	CString  m_strProtocol;
	long m_nDir; //方向：0=监视方向；1=控制方向
	CString m_strDvmFile;

//重载函数
public:
	virtual UINT GetClassID() {    return EMCCLASSID_CEMCNETCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CMonitorCapConfigXmlRWKeys::CEmcNetConfigKey();     }
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

