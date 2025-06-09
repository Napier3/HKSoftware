//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetConfig.h  CEpCapNetConfig

#pragma once

#include "EpCapConfigGlobal.h"


#include "EpCapNetRemote.h"
#include "EpCapNetLocal.h"
#include "EpCapDirs.h"

class CEpCapNetConfig : public CExBaseList
{
public:
	CEpCapNetConfig();
	virtual ~CEpCapNetConfig();


//重载函数
public:
	virtual UINT GetClassID() {    return ECCLASSID_CEPCAPNETCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapConfigXmlRWKeys::CEpCapNetConfigKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CEpCapNetRemote *m_pNetRemote;
	CEpCapNetLocal *m_pNetLocal;
	CEpCapDirs *m_pDirs;

//私有成员变量访问方法
public:
};

