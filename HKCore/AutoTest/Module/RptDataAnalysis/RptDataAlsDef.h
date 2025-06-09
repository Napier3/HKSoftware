//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptDataAlsDef.h  CRptDataAlsDef

#pragma once

#include "RptAnalysisGlobal.h"

typedef CArray<double> CDoubleArray;

class CRptDataAlsDef : public CExBaseObject
{
public:
	CRptDataAlsDef();
	virtual ~CRptDataAlsDef();

	CDoubleArray m_darrRptDataValue;

	CString  m_strItemPath;
	CString  m_strValueID;
//重载函数
public:
	virtual UINT GetClassID() {    return RPTALSCLASSID_CRPTDATAALSDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CRptAnalysisXmlRWKeys::CRptDataAlsDefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	void SplitItemPath();
	CStringArray m_astrItemID;

//私有成员变量访问方法
public:
	BOOL MatchItem(CExBaseObject *pItem);
	void AddDataValue(double dValue)	{	m_darrRptDataValue.Add(dValue);	}
};

