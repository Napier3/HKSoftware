//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeBody.h  CEdgeBody

#pragma once

#include "EdgeCmdMngrGlobal.h"



class CEdgeBody : public CExBaseList
{
public:
	CEdgeBody();
	virtual ~CEdgeBody();


	CString  m_strFileDir;
	CString  m_strFileName;
	long  m_nFileSize;
	CString  m_strContent;
	long m_nCode;
	CString m_strMessage;
//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEBODY;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeBodyKey();     }
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

