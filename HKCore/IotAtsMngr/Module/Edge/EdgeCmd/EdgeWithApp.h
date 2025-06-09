//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeWithApp.h  CEdgeWithApp

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeFile.h"
#include "EdgeCfgCpu.h"
#include "EdgeCfgMem.h"
#include "EdgeCmdErrorMngr.h"

class CEdgeWithApp : public CEdgeCmdErrorMngr
{
public:
	CEdgeWithApp();
	virtual ~CEdgeWithApp();


	CString  m_strVersion;
	CString  m_strEnable;
//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEWITHAPP;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeWithAppKey();     }
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
	CEdgeFile *m_pEdgeFile;
	CEdgeCfgMem *m_pEdgeCfgMem;
	CEdgeCfgCpu *m_pEdgeCfgCpu;

//˽�г�Ա�������ʷ���
public:
	CEdgeFile* GetEdgeFile()	{	return m_pEdgeFile;	}
	void SetEdgeFile(CEdgeFile* pEdgeFile)	{	m_pEdgeFile = pEdgeFile;AddTail(pEdgeFile);	}
	CEdgeCfgMem* GetEdgeCfgMem()	{	return m_pEdgeCfgMem;	}
	void SetEdgeCfgMem(CEdgeCfgMem* pEdgeCfgMem)	{	m_pEdgeCfgMem = pEdgeCfgMem;AddTail(pEdgeCfgMem);	}
	CEdgeCfgCpu* GetEdgeCfgCpu()	{	return m_pEdgeCfgCpu;	}
	void SetEdgeCfgCpu(CEdgeCfgCpu* pEdgeCfgCpu)	{	m_pEdgeCfgCpu = pEdgeCfgCpu;AddTail(pEdgeCfgCpu);	}

//���Ա������ʷ���
public:
};

