//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_Remark.h  CSetsFileXml_Remark

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_RI.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"
class CSetsFileXml_Remark : public CExBaseList
{
public:
	CSetsFileXml_Remark();
	virtual ~CSetsFileXml_Remark();


	long  m_nItemNum;
	long  m_nUpdate;  //�Ƿ���±��
	CString  m_strmd5;
//���غ���

	pugi::xml_node *m_pNode;
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_REMARK;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	void GetValStringTotal_V110_Remark(CString &strValTotal);
	void GetMd5_ForCal(CString &strMd5, const CString &strValTotal, BOOL bReCalMd5,BOOL bIsUpdateMD5 = false);

//˽�г�Ա����
private:
	CString m_strMd5_Cal;   //����õ���MD5

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

