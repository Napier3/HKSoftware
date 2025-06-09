//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetCard.h  CEpCapNetCard

#pragma once

#include "EpCapConfigGlobal.h"


#include "EpCapNetGroup.h"
#include "EpCapDirs.h"

class CEpCapNetCard : public CExBaseList
{
public:
	CEpCapNetCard();
	virtual ~CEpCapNetCard();


	long  m_nTcp;
	long  m_nUdp;
//重载函数
public:
	virtual UINT GetClassID() {    return ECCLASSID_CEPCAPNETCARD;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapConfigXmlRWKeys::CEpCapNetCardKey();     }
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
	CEpCapNetGroup *m_pNetGroup;
	CEpCapDirs *m_pDirs;

//私有成员变量访问方法
public:
};

