//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChsAnalog.h  CIecCfgChsAnalog

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgAnalogCh.h"
#include "IecCfgChsBase.h"

class CIecCfgChsAnalog : public CIecCfgChsBase
{
public:
	CIecCfgChsAnalog();
	virtual ~CIecCfgChsAnalog();


//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGCHSANALOG;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgChsAnalogKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CIecCfgDataChBase* CreateChannel();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

