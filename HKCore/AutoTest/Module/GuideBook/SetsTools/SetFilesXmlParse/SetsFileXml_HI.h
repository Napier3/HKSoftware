//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_HI.h  CSetsFileXml_HI

#pragma once

#include "SetFileXmlParseGlobal.h"

#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"

class CSetsFileXml_HI : public CExBaseObject
{
public:
	CSetsFileXml_HI();
	virtual ~CSetsFileXml_HI();


	CString  m_strClass;
	CString  m_strmd5;

	pugi::xml_node *m_pNode;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_HI;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_HIKey();     }
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

