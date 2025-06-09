//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
//重载函数
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

//私有成员变量
private:
	CEdgeCpuLmt *m_pEdgeCpuLmt;
	CEdgeMemLmt *m_pEdgeMemLmt;
	CEdgeDiskLmt *m_pEdgeDiskLmt;

//私有成员变量访问方法
public:
	CEdgeCpuLmt* GetEdgeCpuLmt()	{	return m_pEdgeCpuLmt;	}
	void SetEdgeCpuLmt(CEdgeCpuLmt* pEdgeCpuLmt)	{	m_pEdgeCpuLmt = pEdgeCpuLmt;AddTail(pEdgeCpuLmt);	}
	CEdgeMemLmt* GetEdgeMemLmt()	{	return m_pEdgeMemLmt;	}
	void SetEdgeMemLmt(CEdgeMemLmt* pEdgeMemLmt)	{	m_pEdgeMemLmt = pEdgeMemLmt;AddTail(pEdgeMemLmt);	}
	CEdgeDiskLmt* GetEdgeDiskLmt()	{	return m_pEdgeDiskLmt;	}
	void SetEdgeDiskLmt(CEdgeDiskLmt* pEdgeDiskLmt)	{	m_pEdgeDiskLmt = pEdgeDiskLmt;AddTail(pEdgeDiskLmt);	}

//属性变量访问方法
public:
};

