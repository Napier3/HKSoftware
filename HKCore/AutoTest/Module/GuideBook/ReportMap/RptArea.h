#pragma once

//功能描述 试验报告区域对象，子对象为CRptBkmk

#include "RptBkmk.h"

#define RPT_AREA_TYPE_ADJUST     _T("adjust")  
#define RPT_AREA_TYPE_MGRP        _T("mgrp")

class CRptArea :	public CExBaseList
{
public:
	CRptArea(void);
	virtual ~CRptArea(void);

//属性
public:
	CRptBkmk *m_pBkmkBegin;
	CRptBkmk *m_pBkmkEnd;
	CString m_strAreaType;   //区域标签类型  0=报告调整区域标签；1=多通道报告合并标签

//公共接口
public:
// 	CExBaseObject* AddNew();					//新建标签对象,根据特定的规则自动生成IRptBkmk的标签
// 	CExBaseObject* AddNew2(const CString  strRptBkmk);

	//重写父类方法
public:
	virtual UINT GetClassID()									{        return RPTCLASSID_RPTAREA;             }
	virtual BSTR GetXmlElementKey()				{      return CGbXMLKeys::g_pGbXMLKeys->m_strAreaKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CBaseObject* Clone();

	virtual void InitAfterRead();
	void ClearDWData();
	virtual BOOL CopyOwn(CBaseObject* pDest);

	//区域标签类型  0=报告调整区域标签；1=多通道报告合并标签
	BOOL IsRptAdjustArea();
	BOOL IsRptMgrpCmbArea();
	void SetRptAdjustArea();
	void SetRptMgrpCmbArea();
	void SetRptAreaType(const CString &strType);

	void DeleteArea();
	void InitAreaBkmkID(CRptBkmk *pBkmk, DWORD &dwBkmkIndex);
};
