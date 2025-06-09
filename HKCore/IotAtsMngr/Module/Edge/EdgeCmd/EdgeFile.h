//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeFile.h  CEdgeFile

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeSign.h"
#include "EdgeCmdErrorMngr.h"

class CEdgeFile : public CEdgeCmdErrorMngr
{
public:
	CEdgeFile();
	virtual ~CEdgeFile();


	CString  m_strUrl;
	long  m_nSize;
	CString  m_strMd5;
	CString m_strFileType;
//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeFileKey();     }
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
	CEdgeSign *m_pEdgeSign;

//˽�г�Ա�������ʷ���
public:
	CEdgeSign* GetEdgeSign()	{	return m_pEdgeSign;	}
	void SetEdgeSign(CEdgeSign* pEdgeSign)	{	m_pEdgeSign = pEdgeSign;AddTail(pEdgeSign);	}

//���Ա������ʷ���
public:
};

