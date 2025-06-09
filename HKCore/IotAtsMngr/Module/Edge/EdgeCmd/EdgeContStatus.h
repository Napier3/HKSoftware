//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeConStatus.h  CEdgeContStatus

#pragma once

#include "EdgeCmdMngrGlobal.h"



class CEdgeContStatus : public CExBaseList
{
public:
	CEdgeContStatus();
	virtual ~CEdgeContStatus();


	CString  m_strContainer;
	CString  m_strVersion;
	CString  m_strRun;
	long  m_nCpuRate;
	long  m_nMemUsed;
	long  m_nDiskUsed;
	CString  m_strIp;
	SYSTEMTIME  m_tmCreated;
	SYSTEMTIME  m_tmStarted;
	long  m_nLifeTime;
	CString  m_strImage;
//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGECONTSTATUS;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeContStatusKey();     }
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

