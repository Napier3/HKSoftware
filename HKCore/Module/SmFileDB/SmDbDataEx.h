//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbDataEx.h  CSmDbDataEx

#pragma once

#include "SmFileDBGlobal.h"

#include "SmDbData.h"


class CSmDbDataEx : public CSmDbData
{
public:
	CSmDbDataEx();
	virtual ~CSmDbDataEx();


//���غ���
public:
	virtual UINT GetClassID() {    return SMDBCLASSID_CSMDBDATAEX;   }
	virtual BSTR GetXmlElementKey()  {      return CSmFileDBXmlRWKeys::CSmDbDataExKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

