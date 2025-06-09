#pragma once

//功能描述 试验报告数据对象，子对象为CRptBkmk
//代表试验过程中需要填入报告的一个数据，包含数据精度

#include "RptBkmk.h"

#define _RPTDATA_PRECISION_INIT -1
class CGbItemBase;

class CRptData :	public CExBaseList
{
public:
	CRptData(void);
	CRptData(const CString  &strName, const CString  &strID, const CString  &strPrecision);
	virtual ~CRptData(void);

//属性
protected:
	long m_nPrecision;										//数据的精度，定义填写报告时使用

public:
	CString m_strPrecision;
	CString m_strDataType;
	long m_nDataFill;

//公共接口
public:
//	CExBaseObject* AddNew();					//新建标签对象,根据特定的规则自动生成IRptBkmk的标签
	CExBaseObject* AddNew2(const CString  strRptBkmk);
	void SetPrecision(long nPrecision);
	void SetPrecision(const CString &strPrecision)	;
	long GetPrecision();//												{		return m_nPrecision;					}

	//重写父类方法
public:
	virtual UINT GetClassID()									{        return RPTCLASSID_RPTDATA;             }
	virtual BSTR GetXmlElementKey()				{      return CGbXMLKeys::g_pGbXMLKeys->m_strDataKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

	void ClearDWData();
	CGbItemBase* GetParentItem();    //获取父项目
};
