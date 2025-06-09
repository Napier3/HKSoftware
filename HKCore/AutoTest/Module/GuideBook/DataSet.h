#pragma once

#include "GuideBookDefine.h"
#include "DataObj.h"

#include "../../../Module/DataMngr/DvmDevice.h"

static const CString g_strAinExand_Abs = _T("Abs_");
static const CString g_strAinExand_Rel = _T("Rel_");
static const CString g_strAinExand_Rst = _T("Rst_");

#ifdef GUIDEBOOK_DEV_MODE
#include "AinExpandMngr.h"
#endif

#define DVM_DATASET_FIND_MODE_NAME   0X00000001
#define DVM_DATASET_FIND_MODE_ID        0X00000002

class CDataSet :public CExBaseList
{
public:
	CDataSet(void);
	virtual ~CDataSet(void);

	static CDataSet* _New(CBaseObject *pParent=NULL)
	{
		CDataSet *pNew = new CDataSet();
		pNew->InitAfterRead();
		return pNew;
	}

	CString m_strType;
	CString m_strRWAttr;
	

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_DATASET;		}
	virtual BSTR GetXmlElementKey()  ;

	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

	virtual CDataObj* InsertData(CDataObj *pData);
	virtual CDataObj* FindDataByID(const CString &strID);

public:
	CDataObj* AddNewDataObj(CDvmData *pData);
	CDataObj* AddNewDataObj(CShortData *pData);
	CDataObj* AddNewDataObj(const CString &strName, const CString &strID);
	void SetDataSetValue(CValues* pValues);
	void InitValueByDatas(CShortDatas *pDatas);
	//shaolei 20211031
	void InitValueByDvmDataset(CDvmDataset *pSrcDataset);
	void WriteToDatas(CShortDatas *pDatas);
	CValues* GetValues();

    //void InitValueByDvmDataset(CDvmDataset *pDataset, BOOL bSetMinMax, DWORD dwMode_Name_ID);  //2021-10-14  lijunqing
	void WriteToDvmDataset(CDvmDataset *pDataset);
	void AddToDvmDataset(CDvmDataset *pDataset);
	CDataObj* FindDataObjByID_Has(const CString &strIDPath);
	CDataObjValue* FindDataObjValueByID_Has(const CString &strIDPath);
	CDataObj* FindDataObjByID_Has2(const CString &strIDPath);
	void InitValueByDataset(CDataSet *pSrcDataset);
	long GetValueLong(const CString &strValueID);
	double GetValueDouble(const CString &strValueID);

	CString FindDataObjValue_Name(const CString &strIDPath);//获取对应子对象的Name  shaolei 20211017

	void ResetDvmValue();
	CDataObj* FindByNameEx(CDvmData *pDataSrc);
	long CompareVersionInfo(CDvmData *pStandInfo, CDvmDataset *pRlstDs);

	void GetDataObjsByNameHas(const CString &strDataNameHas, CExBaseList *pList);
	//模型更新  shaolei 20220716
	void UpdateDataObjValue(CDataSet *pSrcDataSet, BOOL bNewNotExist = TRUE);

#ifdef GUIDEBOOK_DEV_MODE
public:
	long ExpandDsAin(CAinExpandMngr *pAinExpandMngr);

private:
	CAinExpand* CanExpand(CAinExpandMngr *pAinExpandMngr, CDataObjValue *pValue);
	long ExpandDsAin(CAinExpandMngr *pAinExpandMngr, CDataObj *pData, CExBaseList &oList);
	long ExpandDsAin(CDataObj *pData, const CString &strExpand, CExBaseList &oList);
	long ExpandDsAin(CDataObj *pData, CDataObjValue *pValue, const CString &strExpand);
	long ExpandDsAin(CExBaseList *pParent, CDataObjValue *pValue);
	long ExpandDsAin(CExBaseList *pParent, CDataObjValue *pValue, const CString &strExpand);
	long ExpandDsAin(CDataObjValue *pParent, CDataObjValue *pValue, const CString &strExpand);

	CAinExpandMngr *m_pAinExpandMngr;
	long m_nExpandCount;
#endif

//2021-10-14  lijunqing
public:
	virtual CDvmDataset* GetWriteDvmDataset(CValues *pValues);
	virtual void InitValueByDvmDataset(CDvmDataset *pDataset, BOOL bSetMinMax, DWORD dwMode_Name_ID);

protected:
	virtual void GetWriteDvmDataset(CDvmDataset *pDvmDataset);
	virtual void GetWriteDvmDataset(CDvmDataset *pDvmDataset, CValues *pValues);

	void InitValueByDvmData(CDvmData *pDvmData, BOOL bSetMinMax, DWORD dwMode_Name_ID);

public:
	//shaolei 2022-12-06   CDataSet对象转换成CDvmDataset对象
	virtual void Data_Gb_to_Dvm(CDvmDataset *pDestDvm);

};

inline BOOL dvm_dataset_find_mode_name(DWORD dwMode)
{
	return (dwMode & DVM_DATASET_FIND_MODE_NAME) == DVM_DATASET_FIND_MODE_NAME ;
}

inline BOOL dvm_dataset_find_mode_id(DWORD dwMode)
{
	return (dwMode & DVM_DATASET_FIND_MODE_ID) == DVM_DATASET_FIND_MODE_ID ;
}

inline DWORD dvm_dataset_find_mode_name()
{
	return DVM_DATASET_FIND_MODE_NAME ;
}
inline DWORD dvm_dataset_find_mode_id()
{
	return DVM_DATASET_FIND_MODE_ID ;
}

inline DWORD dvm_dataset_find_mode_name_id()
{
	return DVM_DATASET_FIND_MODE_NAME | DVM_DATASET_FIND_MODE_ID ;
}

//lijunqing 2020-09-05
void Gb_Append_Datas(CExBaseList *pDvmList, CExBaseList *pSrcDataObjList);

//lijunqing 2020-09-12
void Gb_InitValueByDvmDatas(CExBaseList *pSrcDvmDatas, CExBaseList *pDestList);
