//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapGenMngr.h  CEpCapGenMngr

#pragma once

#include "EpCapDatasGeneratorGlobal.h"


#include "EpCapGenSerial.h"
#include "EpCapGenUdp.h"

class CEpCapGenMngr : public CExBaseList
{
public:
	CEpCapGenMngr();
	virtual ~CEpCapGenMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return ECGCLASSID_CEPCAPGENMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDatasGeneratorXmlRWKeys::CEpCapGenMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CString GetCapGenFile();

//˽�г�Ա�������ʷ���
public:
	BOOL OpenCapGenFile();
	BOOL SaveCapGenFile();
};

