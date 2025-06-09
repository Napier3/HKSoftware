// GridCell.cpp: implementation of the CGridCell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridCellDataType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridDataTypeValue::CGridDataTypeValue(const CString &strName, const CString &strID, long nID)
{
	m_strName = strName;
	m_strID = strID;
	m_nID = nID;
}

CGridDataTypeValue::~CGridDataTypeValue()
{

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CGridDataType::CGridDataType(const CString &strName, const CString &strID, long nID)
{
	m_strName = strName;
	m_strID = strID;
	m_nID = nID;
}

CGridDataType::~CGridDataType()
{
	long nIndex = 0;
	long nCount = GetSize();
	CGridDataTypeValue *pValue = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pValue = GetAt(nIndex);
		delete pValue;
	}

	RemoveAll();
}

CGridDataTypeValue* CGridDataType::AddNew(const CString &strName, const CString &strID, long nID)
{
	CGridDataTypeValue *pValue = new CGridDataTypeValue(strName, strID, nID);

	Add(pValue);

	return pValue;
}


CGridDataTypeValue* CGridDataType::FindByName(const CString &strName)
{
	CGridDataTypeValue *p = NULL;
	CGridDataTypeValue *pFind = NULL;
	long nIndex = 0;
	long nCount = GetSize();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = GetAt(nIndex);
		
		if (p->m_strName == strName)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}

CGridDataTypeValue* CGridDataType::FindByID(const CString &strID)
{
	CGridDataTypeValue *p = NULL;
	CGridDataTypeValue *pFind = NULL;
	long nIndex = 0;
	long nCount = GetSize();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = GetAt(nIndex);
		
		if (p->m_strID == strID)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}

CGridDataTypeValue* CGridDataType::FindByID(long nID)
{
	CGridDataTypeValue *p = NULL;
	CGridDataTypeValue *pFind = NULL;
	long nIndex = 0;
	long nCount = GetSize();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = GetAt(nIndex);
		
		if (p->m_nID == nID)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}

//////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////////
CGridDataTypes::CGridDataTypes()
{

}

CGridDataTypes::~CGridDataTypes()
{
	long nIndex = 0;
	long nCount = GetSize();
	CGridDataType *pDataType = NULL;
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pDataType = GetAt(nIndex);
		delete pDataType;
	}
	
	RemoveAll();
}


CGridDataType* CGridDataTypes::AddNew(const CString &strName, const CString &strID, long nID)
{
	CGridDataType *pNew = new CGridDataType(strName, strID, nID);
	Add(pNew);
	return pNew;
}

CGridDataType* CGridDataTypes::FindByName(const CString &strName)
{
	CGridDataType *p = NULL;
	CGridDataType *pFind = NULL;
	long nIndex = 0;
	long nCount = GetSize();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = GetAt(nIndex);
		
		if (p->m_strName == strName)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}

CGridDataType* CGridDataTypes::FindByID(const CString &strID)
{
	CGridDataType *p = NULL;
	CGridDataType *pFind = NULL;
	long nIndex = 0;
	long nCount = GetSize();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = GetAt(nIndex);
		
		if (p->m_strID == strID)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}

CGridDataType* CGridDataTypes::FindByID(long nID)
{
	CGridDataType *p = NULL;
	CGridDataType *pFind = NULL;
	long nIndex = 0;
	long nCount = GetSize();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		p = GetAt(nIndex);
		
		if (p->m_nID == nID)
		{
			pFind = p;
			break;
		}
	}
	
	return pFind;
}




