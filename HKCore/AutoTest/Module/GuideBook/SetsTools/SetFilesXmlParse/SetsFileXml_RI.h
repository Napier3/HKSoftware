//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_RI.h  CSetsFileXml_RI

#pragma once

#include "SetFileXmlParseGlobal.h"



class CSetsFileXml_RI : public CExBaseObject
{
public:
	CSetsFileXml_RI();
	virtual ~CSetsFileXml_RI();


	CString  m_strVal;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_RI;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_RIKey();     }
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

