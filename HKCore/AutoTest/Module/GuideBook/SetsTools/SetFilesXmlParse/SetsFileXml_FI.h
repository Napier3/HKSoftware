//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_FI.h  CSetsFileXml_FI

#pragma once

#include "SetFileXmlParseGlobal.h"



class CSetsFileXml_FI : public CExBaseObject
{
public:
	CSetsFileXml_FI();
	virtual ~CSetsFileXml_FI();


	CString  m_strText;
	CString  m_strDesc;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_FI;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_FIKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

