//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CmdExecRslt.h  CCmdExecRslt

#pragma once

#include "CmdExecGlobal.h"


#include "ExecResult.h"

class CCmdExecRslt : public CExBaseList
{
public:
	CCmdExecRslt();
	virtual ~CCmdExecRslt();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CCMDEXECRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CCmdExecXmlRWKeys::CCmdExecRsltKey();     }
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
	CDvmDataset *m_pDvmDataset;
	CExecResult *m_pExecResult;

//˽�г�Ա�������ʷ���
public:
	CDvmDataset* GetDvmDataset()	{	return m_pDvmDataset;	}
	CExecResult* GetExecResult()	{	return m_pExecResult;	}

//���Ա������ʷ���
public:
	void GenerateCmdExecRslt(long nRslt,CDvmDataset *pDataset);
};

