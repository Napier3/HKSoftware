//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapDbConfig.h  CEpCapDbConfig

#pragma once

#include "EpCapDbConfigGlobal.h"


#include "EpCapDbFileCfg.h"

class CEpCapDbConfig : public CExBaseList
{
public:
	CEpCapDbConfig();
	virtual ~CEpCapDbConfig();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEPCAPDBCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDbConfigXmlRWKeys::CEpCapDbConfigKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

