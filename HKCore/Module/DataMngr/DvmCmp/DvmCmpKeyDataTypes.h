//DvmCmpKeyDataTypes.h  CDvmCmpKeyDataTypes

#pragma once


#include "../DataTypes.h"
#include "../DvmValue.h"
#include <vector>
using namespace std;

class CDvmCmpKeyDataTypes : public CDataTypes
{
public:
	CDvmCmpKeyDataTypes();
	virtual ~CDvmCmpKeyDataTypes();

protected:
	static const CString g_strLdeviceDataTypeID;
	static const CString g_strDatasetDataTypeID;
	static const CString g_strDvmCmpValueKeyDataTypeID;
	static const CString g_strDvmCmpFullNameIdKeyTypeID;


	CDataType *m_pLdeviceDataType;
	CDataType *m_pDatasetDataType;
	CDataType *m_pDvmCmpValueKeyDataType;
	CDataType *m_pDvmCmpFullNameIdKeyType;

public:
	static long CanCmpDvmObject(CExBaseObject *pStand, CExBaseObject *pDestCmpObj);
	static long CanCmpDvmObject_ID(CExBaseObject *pStand, CExBaseObject *pDestCmpObj);
	
	void OpenKeyDataTypesFile(const CString &strFile);
	long GetLdeviceKey(const CString &strText);
	long GetDatasetKey(const CString &strText);
	long GetCmpFullNameIdKey(const CString &strText);
	long GetKey(CDataType *pDataType, const CString &strText);
	CString GetDvmValueKey(CDvmValue *pDvmValue);

public:
	void DvmCmpLdevice(CExBaseList *pSrcDevice, CExBaseList *pDestDevice, CExBaseList &listMap);
	void DvmCmpDataset(CExBaseList *pSrcLdevice, CExBaseList *pDestLdevice, CExBaseList &listMap);

protected:
	CExBaseObject* FindLdevice(CExBaseList *pDevice, long nKey);
	CExBaseObject* FindDataset(CExBaseList *pLdevice, long nKey);

	static long CanCmpID(const CString &strSrcID1, const CString &strSrcID2);
	static vector<CString> SplitCString(const CString &strSource, const CString &ch);
};
