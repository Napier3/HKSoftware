#pragma once

#include "GuideBookDefine.h"

class CSet :public CExBaseObject
{
public:
	CSet(void);
	virtual ~CSet(void);

	static CSet* _New(CBaseObject *pParent=NULL)
	{
		CSet *pNew = new CSet();
		pNew->m_bNewCreate = TRUE;
		return pNew;
	}

public:
	//attribute
	CString m_strValue;
	CString m_strUnit;
	CString m_strDataType;
	CString m_strMinVal;
	CString m_strMaxVal;
	CString m_strDefaultValue;

	double m_dMinVal;
	double m_dMaxVal;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{			return GBCLASSID_SET;			}
	virtual BSTR GetXmlElementKey();
	virtual void InitAfterRead();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	
	BOOL IsNewCreate()	{	return m_bNewCreate;		}
	void ClearNewCreate()	{	m_bNewCreate = FALSE;	}

	void GetIDForPath(CString &strID, const CString &strPathSp = _T("\\"));

	void InitValueByData(CShortData *pData);
	void WriteToData(CShortData *pData);

	CDataTypes* GetDataTypes();
protected:

private:
	BOOL m_bNewCreate;
};

inline void Gb_GetSetName(CString &strSetName, CSet *pSet)
{
	if (pSet == NULL)
	{
		return;
	}

	CExBaseObject *p = (CExBaseObject*)pSet->GetParent();
	strSetName.Format(_T("%s(%s)"), pSet->m_strName,p->m_strID);
}