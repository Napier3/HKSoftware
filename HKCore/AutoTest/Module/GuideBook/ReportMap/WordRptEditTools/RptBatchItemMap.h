//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBatchItemMap.h  CRptBatchItemMap

#pragma once

#include "RptBkmkBatchAddGlobal.h"



class CRptBatchItemMap : public CExBaseObject
{
public:
	CRptBatchItemMap();
	virtual ~CRptBatchItemMap();


	long  m_nItemIndex;
	long  m_nMapIndex;

	CExBaseObject *m_pItemRef;
//重载函数
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBATCHITEMMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBatchItemMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void ClearMap()
	{
		m_nMapIndex = -1;
		m_nItemIndex = -1;
		m_strID.Empty();
		m_strName.Empty();
	}

	BOOL IsMaped()	{	return m_strID.GetLength() > 0;	}
};

