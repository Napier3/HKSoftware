//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_DevInfo.h  CSetsFileXml_DevInfo

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_DI.h"

class CSetsFileXml_DevInfo : public CExBaseList
{
public:
	CSetsFileXml_DevInfo();
	virtual ~CSetsFileXml_DevInfo();


	long  m_nItemNum;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_DEVINFO;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_DevInfoKey();     }
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

