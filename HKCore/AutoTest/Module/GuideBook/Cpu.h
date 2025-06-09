#pragma once

#include "GuideBookDefine.h"

// #ifndef _use_device_model_ds
// #include "Sets.h"
// #include "Soes.h"
// #include "Binarys.h"
// #include "Analogs.h"
// #include "CtrlWords.h"
// #include "BinaryIns.h"
// #include "BinaryOuts.h"
// #include "SoftSwitchs.h"
// #endif

#include "reports.h"
#include "DataSet.h"
#include "DataSetGroup.h"
#include "GbLogCtrls.h"

class CCpu :public CExBaseList
{
public:
	CCpu(void);
	virtual ~CCpu(void);

	static CCpu* _New(CBaseObject *pParent=NULL)
	{
		CCpu *pNew = new CCpu();
		pNew->InitAfterRead();
		return pNew;
	}

public:
	//attribute
	long m_nIndex;

	//包含设备数据属性
	long m_nDsParameter;
	long m_nDsSetting;
	long m_nDsEna;
	long m_nDsAin;
	long m_nDsDin;
	long m_nDsRec;
	long m_nDsTripInfo;
	long m_nDsAlarm;
	long m_nDsWarning;
	long m_nDsSoe;
	long m_nDsSV;
	long m_nDsGOOSE;

// #ifndef _use_device_model_ds
// 	CAnalogs* m_pAnalogs;
// 	CSets* m_pSets;
// 	CCtrlWords* m_pCtrlWords;
// 	CSoftSwitchs* m_pSoftSwitchs;
// 	CBinaryIns* m_pBinaryIns;
// 	CBinaryOuts* m_pBinaryOuts;
// 	CSoes* m_pSoes;
// #endif
	CGbLogCtrls *m_pLogCtrls;

	CReport* GetReport();

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()																		{		return GBCLASSID_CPU;				}
	virtual BSTR GetXmlElementKey()													{      return CGbXMLKeys::g_pGbXMLKeys->m_strLDeviceKey;     }
	
	//WriteXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	virtual void InitAfterRead();
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);

	//Interface Mathods
//#ifndef _use_device_model_ds
// 	CAnalogs* GetAnalogs()																			{		return m_pAnalogs;						}
// 	CSets* GetSets()																							{		return m_pSets;								}
// 	CCtrlWords* GetCtrlWords()																	{		return m_pCtrlWords;					}
// 	CSoftSwitchs* GetSoftSwitchs()															{		return m_pSoftSwitchs;				}
// 	CBinaryIns* GetBinaryIns()																	{		return m_pBinaryIns;					}
// 	CBinaryOuts* GetBinaryOuts()															{		return m_pBinaryOuts;				}
// 	CSoes* GetSoes()																							{		return m_pSoes;								}
// #else
// 	CDataSet* GetAnalogs();
// 	CDataSet* GetSets();
// 	CDataSet* GetCtrlWords();
// 	CDataSet* GetSoftSwitchs();
// 	CDataSet* GetBinaryIns();
// 	CDataSet* GetBinaryOuts();
// 	CDataSet* GetSoes();
// #endif
// 
	long GetDataSet(const CString &strType, CExBaseList &oListDataSet, CDataSet **pDataSet);
	//shaolei 20220330
	long SelectDatas_FilterByPath(const CString &strDatasetPath, const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator=_T("$"));
	CDataSet* GetDataSet(const CString &strType);
	CDataSet* GetDataSetByKey(const CString &strKey);
	BOOL GetAllDatasByDatasetKey(CDataSet *pDatasetRef,const CString &strKey);//zhouhj20190723
	CExBaseList* GetDeviceModelDatasById(const CString &strCpuID, const CString &strDeviceModelTypeID);
	CExBaseList* GetDeviceModelDatasById(const CString &strDeviceModelTypeID);
// 	CSet* FindBySetName(const CString &strName);

	CDataSet* GetDataSet(UINT nDataSetIndex)
	{
		ASSERT(nDataSetIndex < DSID_dsMaxCount);
		return GetDataSet(g_strDataSetID[nDataSetIndex]);
	}

	CDataSet* GetDataSetByKey(UINT nDataSetIndex)
	{
		ASSERT(nDataSetIndex < DSID_dsMaxCount);
		return GetDataSetByKey(g_strDataSetIDKey[nDataSetIndex]);
	}

	CDataSet* GetDataset_Setting()	{		return GetDataSetByKey(DSID_dsSetting);	}
	CDataSet* GetDataset_Ena()		{		return GetDataSetByKey(DSID_dsEna);	}
	CDataSet* GetDataset_TripInfo()	{		return GetDataSetByKey(DSID_dsTripInfo);	}
	CDataSet* GetDataset_Ain()		{		return GetDataSetByKey(DSID_dsAin);	}
	CDataSet* GetDataset_Alam()		{		return GetDataSetByKey(DSID_dsAlarm);	}
	CDataSet* GetDataset_Warning()	{		return GetDataSetByKey(DSID_dsWarning);	}
	CDataSet* GetDataset_Parameter(){		return GetDataSetByKey(DSID_dsParameter);	}
	CDataSet* GetDataset_Din()		{		return GetDataSetByKey(DSID_dsDin);	}
	CDataSet* GetDataset_Soe()		{		return GetDataSetByKey(DSID_dsSoe);	}
	CDataSet* GetDataset_Dout()		{		return GetDataSetByKey(DSID_dsDout);	}

	CDataObj* FindDataObjByName(const CString &strName);
	CDataObj* FindDataObjByID(const CString &strID);
	long FindDataObjByID(const CString &strID, CExBaseList &listDatas);
	CDataObj* FindDataObjByID_Has(const CString &strID);
	long FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas);
	void ResetDvmValue();

	void GetDataObjsByNameHas(const CString &strDsIDHas, const CString &strDataNameHas, CExBaseList *pList);
	//模型更新  shaolei 20220716
	void UpdateDataSetValue(CCpu *pSrcCpu, BOOL bNewNotExist = TRUE);

protected:
	CReport* m_pReport;

private:
	void TransToDataSet();
};

void Gb_GetDeviceParaDataPath(CExBaseObject *pData, CString &strPath);
