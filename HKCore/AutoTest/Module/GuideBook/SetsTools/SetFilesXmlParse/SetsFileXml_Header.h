//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_Header.h  CSetsFileXml_Header

#pragma once

#include "SetFileXmlParseGlobal.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"



class CSetsFileXml_Header : public CExBaseObject
{
public:
	CSetsFileXml_Header();
	virtual ~CSetsFileXml_Header();


	CString  m_strDevType;
	CString  m_strDevID;
	CString  m_strIedName;
	CString  m_strUpdateTime;
	CString  m_strmd5;

	pugi::xml_node *m_pNode;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_HEADER;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_HeaderKey();     }
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
	void SetMd5(const CString &strMd5);
	void SetUpdateTime(const CString &strTime);

	CString m_strHeaderMD5_Cal; // ʵ�ʼ������õ�MD5
};

