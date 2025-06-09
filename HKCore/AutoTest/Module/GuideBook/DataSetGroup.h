#pragma once

#include "GuideBookDefine.h"
#include "DataSet.h"

class CDataSetGroup :public CDataSet
{
public:
	CDataSetGroup(void);
	virtual ~CDataSetGroup(void);

	static CDataSetGroup* _New(CBaseObject *pParent=NULL)
	{
		CDataSetGroup *pNew = new CDataSetGroup();
		pNew->InitAfterRead();
		return pNew;
	}

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_DATASETGROUP;		}
	virtual BSTR GetXmlElementKey()  ;

	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

public:
	CDataSetGroup* FindByDataType(const CString &strDataType);
	CDataSetGroup* FindByDataType(const CString &strDataType, long nFindIndex);
	long FindByDataType(const CString &strDataType, CExBaseList &oList);
	long FindByDataType_Data(const CString &strDataType, CExBaseList &oList);
	CDataSetGroup* AddNewGroup(const CString &strName, const CString &strID, const CString &strDataType);

	virtual CDataObj* InsertData(CDataObj *pData);
	virtual CDataObj* FindDataByID(const CString &strID);
	virtual CDataObj* FindByID_InChildren(const CString &strID);
	virtual CDataObj* FindByID_InAllChildren(const CString &strID);
	long SelectAllDatas(CExBaseList &listDatas);

	void WriteTo(CDvmDatasetGroup *pDest);
	void ReadFrom(CDvmDatasetGroup *pSrc);

	//2021-10-14  lijunqing
public:
	virtual CDvmDataset* GetWriteDvmDataset(CValues *pValues);
	virtual void InitValueByDvmDataset(CDvmDataset *pDataset, BOOL bSetMinMax, DWORD dwMode_Name_ID);
	void InitDvmDataGroup(CDvmDatasetGroup *pDvmGroup); //2021-10-22  lijunqing

	CDvmData* AddData(CDvmDatasetGroup *pRoot, CDataObj *pData, CValues *pValues);

protected:
	virtual void GetWriteDvmDatasetG(CDvmDataset *pDvmDataset);
	virtual void GetWriteDvmDatasetG(CDvmDatasetGroup *pRoot, CValues *pValues);
	virtual CDvmData* InsertData(CDvmDatasetGroup *pRoot, CDataObj *pData);

public:
	//shaolei 2022-12-06   CDataSet对象转换成CDvmDataset对象
	virtual void Data_Gb_to_Dvm(CDvmDataset *pDestDvm);
};
