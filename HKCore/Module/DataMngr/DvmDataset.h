//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataset.h  CDvmDataset

#pragma once

#include "DataMngrGlobal.h"


#include "DvmData.h"
#include "Values.h"

#define DVM_DATASET_FIND_MODE_NAME   0X00000001
#define DVM_DATASET_FIND_MODE_ID        0X00000002


class CDvmDataset : public CExBaseList
{
public:
	CDvmDataset();
	virtual ~CDvmDataset();

	CString m_strDataType;
	long    m_nWriteMode;
	long    m_nIndex;

	//2023.11.15 lichao PNS331 新增
#ifdef _DVMDATASET_USE_ADDR_
	long	m_nAddr;
#endif

	CDvmBrcb *m_pDvmBrcb;
//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMDATASET;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDatasetKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
	virtual void InitAfterRead();
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CDvmData* AddNewData(CDvmData *pSrc=NULL);
//	long GetIndex()	{	return CString_To_long(m_strID);	}
	CDvmData* FindByIndex(long nIndex);

	void InitValue(CDvmDataset *pSrcDataset, BOOL bNoChangeWhenSame=FALSE);
	BOOL IsWriteModeSingle()	{	return m_nWriteMode == 0;	}
	CDvmData* FindByID_Has(const CString &strIDPath);

	void SetIndex(long nIndex)	{ m_nIndex = nIndex; }
	long GetIndex()				{ return m_nIndex; }
	BOOL HasValueID(const CString &strValueID);
	BOOL SetAttr(const CString &strAttrID, const CString &strValue);
	CDvmData* AddNewData(const CString &strName, const CString &strID, const CString &strDataType, const CString &strValue
		, const CString &strUnit=_T(""), const CString &strMin=_T(""), const CString &strMax=_T(""), const CString &strStep=_T(""));
	CDvmData* AddNewDataEx(const CString &strName, const CString &strID, const CString &strDataType, const CString &strValue
		, const CString &strUnit=_T(""), const CString &strMin=_T(""), const CString &strMax=_T(""), const CString &strStep=_T(""));
	CDvmData* AddNewDataEx(CDvmData *pSrc);   //2023-2-18  lijunqing
	CDvmData* AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID
		, const CString &strValue, const CString &strFormat,BOOL bAddSame=TRUE);

	long ClearByReserved(DWORD dwReserved);

	//选择性复制，保证子对象没有重复的Name和ID shaolei 2019.07.06
	//2021-8-4  lijunqing CDvmDataset *pDatasetSrc ==>> CExBaseList *pListSrc
	void AppendCloneWithoutRepeat(CExBaseList *pListSrc); 

//直接的二进制串行化功能
public:
	virtual long SerializeRead(char *pBuffer, long nLen); 
	virtual long SerializeRead(CBinarySerialBuffer &oBinaryBuffer); 
	virtual long SerializeWrite(CBinarySerialBuffer &oBinaryBuffer); 
#ifdef _DBLIB_USE_SHAREMEM_
    virtual long SerializeWrite(CShareMemSerialize *pBinaryBuffer);
#endif

	//xxy 20181127
	CDvmData *FindByDataType(const CString& strDataType);
	
	//shaolei  20200613
	virtual BOOL UpdateDataValue(CDvmDataset *pSrcDataset, BOOL bIsNew = FALSE);
 
	//2021-1-3 lijunqing
	void ResetDvmDataValues();

	//2023-3-11  lijunqing
	void SetDataChange(long nChange=0);

	CValues* GetValues();

	long GetValueLong(const CString &strValueID);
	double GetValueDouble(const CString &strValueID);

public:
	CDvmData* FindDataObjByID_Has(const CString &strIDPath);
	CDvmValue* FindDataObjValueByID_Has(const CString &strIDPath);
	CDvmData* FindDataObjByID_Has2(const CString &strIDPath);
	CDvmData* FindByNameEx(CDvmData *pDataSrc);

	virtual CDvmData* FindDataByID(const CString &strID);

	virtual void InitValueByDvmDataset(CDvmDataset *pDataset, BOOL bSetMinMax, DWORD dwMode_Name_ID);
	virtual void InitValueList(CExBaseList *pList, BOOL bSetMinMax, DWORD dwMode_Name_ID);

protected:
	void InitValueByDvmData(CDvmData *pDvmData, BOOL bSetMinMax, DWORD dwMode_Name_ID);

};

class CDvmLogControl : public CDvmDataset
{
public:
	CDvmLogControl();
	virtual ~CDvmLogControl();

	virtual UINT GetClassID() {    return DVMCLASSID_CDVMLOGCTRL;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmLogControlKey();     }

	long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};
long dvm_SerializeWrite(CExBaseObject *pObject, CBinarySerialBuffer &oBinaryBuffer);
#ifdef _DBLIB_USE_SHAREMEM_
BOOL dvm_SerializeWrite(CExBaseObject *pObject, CShareMemSerialize *pBinaryBuffer);
#endif
long dvm_SerializeRead(CExBaseObject *pObject, char *pBuffer, long nLen);
long dvm_SerializeRead(CExBaseObject *pObject, CBinarySerialBuffer &oBinaryBuffer);


inline DWORD xdvm_dataset_find_mode_name()
{
	return DVM_DATASET_FIND_MODE_NAME ;
}
inline DWORD xdvm_dataset_find_mode_id()
{
	return DVM_DATASET_FIND_MODE_ID ;
}

inline DWORD xdvm_dataset_find_mode_name_id()
{
	return DVM_DATASET_FIND_MODE_NAME | DVM_DATASET_FIND_MODE_ID ;
}

