//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapGenDatas.h  CEpCapGenDatas

#pragma once

#include "EpCapDatasGeneratorGlobal.h"


#include "EpCapGenData.h"

class CEpCapGenDatas : public CExBaseList
{
public:
	CEpCapGenDatas();
	virtual ~CEpCapGenDatas();


//���غ���
public:
	virtual UINT GetClassID() {    return ECGCLASSID_CEPCAPGENDATAS;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDatasGeneratorXmlRWKeys::CEpCapGenDatasKey();     }
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

