//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeApps.h  CEdgeApps

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeProcess.h"

class CEdgeApps : public CExBaseList
{
public:
	CEdgeApps();
	virtual ~CEdgeApps();


	CString  m_strApp;
	CString  m_strVersion;
	CString  m_strAppHash;
	long  m_nSrvNumber;
	long  m_nLifeTime;
//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEAPPS;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeAppsKey();     }
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
	CEdgeProcess *m_pEdgeProcess;

//˽�г�Ա�������ʷ���
public:
	CEdgeProcess* GetEdgeProcess()	{	return m_pEdgeProcess;	}
	void SetEdgeProcess(CEdgeProcess* pEdgeProcess)	{	m_pEdgeProcess = pEdgeProcess;AddTail(pEdgeProcess);	}

//���Ա������ʷ���
public:
};

