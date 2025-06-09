//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBatchDataMap.h  CRptBatchDataMap

#pragma once

#include "RptBkmkBatchAddGlobal.h"



class CRptBatchDataMap : public CExBaseObject
{
public:
	CRptBatchDataMap();
	virtual ~CRptBatchDataMap();


	long  m_nRepeatIndex;
	CString  m_strDataAttr;
	CString  m_strPrecision;
	long  m_nMapIndex;
	CString m_strDataProcess;
	CExBaseObject *m_pDataRef;

//重载函数
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHDATAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchDataMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void ClearMap()
	{
		m_nRepeatIndex = -1;
		m_strDataAttr.Empty();
		m_strPrecision = _T("3");
		m_nMapIndex = -1;
		m_strName.Empty();
		m_strID.Empty();
		m_pDataRef = NULL;
	}

	BOOL IsMaped();

};

