#pragma once

#include "..\..\GuideBook\Device.h"

#define GBTDATATRAVERSE_MODE_DATASET_NAME   _T("数据集遍历")
#define GBTDATATRAVERSE_MODE_DATASET_ID     _T("BatchDataset")
#define GBTDATATRAVERSE_MODE_DATASET_INDEX  0

#define GBTDATATRAVERSE_MODE_VALRAMP_NAME   _T("数值等差变化")
#define GBTDATATRAVERSE_MODE_VALRAMP_ID     _T("BatchValRamp")
#define GBTDATATRAVERSE_MODE_VALRAMP_INDEX  1

class CGbtDataTraverseObj :public CExBaseObject
{
public:
	CGbtDataTraverseObj(void);
	virtual ~CGbtDataTraverseObj(void);

	static CGbtDataTraverseObj* _New(CExBaseObject *pGbtData)
	{
		CGbtDataTraverseObj *pNew = new CGbtDataTraverseObj();
		pNew->m_pDataRef = pGbtData;
		return pNew;
	}

public:
	CExBaseObject  *m_pDataRef;
	CString m_strModeType;   //数据集、等差批量
	DWORD m_dwModeType;
	double m_dBeginVal;
	double m_dStep;
	long   m_nSteps;         //变化的步数

public:
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual UINT GetClassID()			{		return GBCLASSID_ANALOG;	}
// 	virtual BSTR GetXmlElementKey() ;
// 
// 	virtual BOOL IsEqual(CBaseObject* pObj);
// 	virtual BOOL CopyOwn(CBaseObject* pDesObj);
// 	virtual CBaseObject* Clone();

protected:

public:
	void SetModeType(const CString &strModelTypeID);
	void SetModeType(DWORD dwtrModelTypeID);
	DWORD GetDodelType()	{	return m_dwModeType;	}
	CString GetModelTypeName();
	BOOL IsModelTypeDataset()	{	return m_dwModeType == GBTDATATRAVERSE_MODE_DATASET_INDEX;	}
	BOOL IsModelTypeValRamp()	{	return m_dwModeType == GBTDATATRAVERSE_MODE_VALRAMP_INDEX;	}
};