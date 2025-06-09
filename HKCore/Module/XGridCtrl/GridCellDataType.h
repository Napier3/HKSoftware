// GridCellDataType.h: interface for the CGridCellDataType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GridCellDataType_h__)
#define _GridCellDataType_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include <afxole.h>                     // This is sloppy I know...

class CGridDataTypeValue : public CObject
{
public:
	CGridDataTypeValue(const CString &strName, const CString &strID, long nID);
	virtual ~CGridDataTypeValue();
	
	CString m_strName;
	CString m_strID;
	long     m_nID;
	
private:
	CGridDataTypeValue(){}
};

typedef CTypedPtrArray<CObArray, CGridDataTypeValue*> CGridDataTypeValueArray;

class CGridDataType : public CGridDataTypeValueArray
{
public:
	CGridDataType(const CString &strName, const CString &strID, long nID);
	virtual ~CGridDataType();

	CString m_strName;
	CString m_strID;
	long     m_nID;
	
public:
	CGridDataTypeValue* AddNew(const CString &strName, const CString &strID, long nID);
	
	CGridDataTypeValue* FindByName(const CString &strName);
	CGridDataTypeValue* FindByID(const CString &strID);
	CGridDataTypeValue* FindByID(long nID);
	
private:
	CGridDataType() {}
};


typedef CTypedPtrArray<CObArray, CGridDataType*> CGridDataTypeArray;

class CGridDataTypes : public CGridDataTypeArray
{
public:
	CGridDataTypes();
	virtual ~CGridDataTypes();
	
public:
	CGridDataType* AddNew(const CString &strName, const CString &strID, long nID);
	CGridDataType* FindByName(const CString &strName);
	CGridDataType* FindByID(const CString &strID);
	CGridDataType* FindByID(long nID);
	
};


#endif // !defined(_GridCellDataType_h__)
