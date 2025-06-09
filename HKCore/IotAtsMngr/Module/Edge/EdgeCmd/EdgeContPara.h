//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeContPara.h  CEdgeContPara

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeMemLmt.h"
#include "EdgeDiskLmt.h"
#include "EdgeCpuLmt.h"
#include "EdgeParaDatas.h"

class CEdgeContPara : public CEdgeParaDatas
{
public:
	CEdgeContPara();
	virtual ~CEdgeContPara();


	CString  m_strContainer;
	CString  m_strPort;
//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGECONTPARA;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeContParaKey();     }
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
	CEdgeDiskLmt *m_pEdgeDiskLmt;
	CEdgeMemLmt *m_pEdgeMemLmt;

	CJSON* m_pMountJson;
	CJSON* m_pDevJson;

//˽�г�Ա�������ʷ���
public:
	CEdgeCpuLmt* GetEdgeCpuLmt()	{	return m_pEdgeCpuLmt;	}
	void SetEdgeCpuLmt(CEdgeCpuLmt* pEdgeCpuLmt)	{	m_pEdgeCpuLmt = pEdgeCpuLmt;AddTail(pEdgeCpuLmt);	}
	CEdgeDiskLmt* GetEdgeDiskLmt()	{	return m_pEdgeDiskLmt;	}
	void SetEdgeDiskLmt(CEdgeDiskLmt* pEdgeDiskLmt)	{	m_pEdgeDiskLmt = pEdgeDiskLmt;AddTail(pEdgeDiskLmt);	}
	CEdgeMemLmt* GetEdgeMemLmt()	{	return m_pEdgeMemLmt;	}
	void SetEdgeMemLmt(CEdgeMemLmt* pEdgeMemLmt)	{	m_pEdgeMemLmt = pEdgeMemLmt;AddTail(pEdgeMemLmt);	}

	CJSON* GetDevJson() { return m_pDevJson; }
	CJSON* GetMountJson() { return m_pMountJson; }

//���Ա������ʷ���
public:
};

