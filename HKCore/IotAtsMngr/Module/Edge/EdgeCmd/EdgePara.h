//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgePara.h  CEdgePara

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeMemLmt.h"
#include "EdgeCpuLmt.h"
#include "EdgeDiskLmt.h"

class CEdgePara : public CExBaseList
{
public:
	CEdgePara();
	virtual ~CEdgePara();


	CString  m_strContainer;
	CString  m_strPort;
//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEPARA;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeParaKey();     }
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
	CEdgeCpuLmt *m_pEdgeCpuLmt;
	CEdgeMemLmt *m_pEdgeMemLmt;
	CEdgeDiskLmt *m_pEdgeDiskLmt;

//˽�г�Ա�������ʷ���
public:
	CEdgeCpuLmt* GetEdgeCpuLmt()	{	return m_pEdgeCpuLmt;	}
	void SetEdgeCpuLmt(CEdgeCpuLmt* pEdgeCpuLmt)	{	m_pEdgeCpuLmt = pEdgeCpuLmt;AddTail(pEdgeCpuLmt);	}
	CEdgeMemLmt* GetEdgeMemLmt()	{	return m_pEdgeMemLmt;	}
	void SetEdgeMemLmt(CEdgeMemLmt* pEdgeMemLmt)	{	m_pEdgeMemLmt = pEdgeMemLmt;AddTail(pEdgeMemLmt);	}
	CEdgeDiskLmt* GetEdgeDiskLmt()	{	return m_pEdgeDiskLmt;	}
	void SetEdgeDiskLmt(CEdgeDiskLmt* pEdgeDiskLmt)	{	m_pEdgeDiskLmt = pEdgeDiskLmt;AddTail(pEdgeDiskLmt);	}

//���Ա������ʷ���
public:
};

