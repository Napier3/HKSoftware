#pragma once

#include "GuideBookDefine.h"
#include "Cpu.h"
//#include "Set.h"
// #include "Analog.h"
#include "GbParaTypeMngr.h"
#include "../XLanguageResourceAts.h"

#ifdef GUIDEBOOK_DEV_MODE
#include "../../../Module/DataMngr/DvmCmp/DvmDeviceMap.h"
#endif

#include "../../../Module/DataMngr/DvmCmp/DvmCmpKeyDataTypes.h"

class CCpus :public CExBaseList
{
//多模型，模型不一致时查找、匹配用
protected:
	static CDvmCmpKeyDataTypes *g_pDvmCmpKeyDataTypes;
	static long g_nDvmCmpKeyDataTypesRef;

	static void CreateDvmCmpKeyDataTypes();
	static void ReleaseDvmCmpKeyDataTypes();

public:
	CCpus(void);
	virtual ~CCpus(void);

	static CCpus* _New(CBaseObject *pParent=NULL)
	{
		CCpus *pNew = new CCpus();
		pNew->InitAfterRead();
		return pNew;
	}

	//2014-9-18
	CString m_strPpEngineProgID;
	CString m_strPpTemplateFile;      //规约模板文件
	CString m_strDeviceModelFile;		//点表文件

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{			return GBCLASSID_CPUS;		}
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strDeviceModelKey;     }
	
	virtual void InitAfterRead();

	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

// 	CSet* SelectSet(const CString &strPath);
// 	CSet* SelectCtrlWord(const CString &strPath);
// 	CSet* SelectSoftSwitch(const CString &strPath);
// 	CAnalog* SelectAnalog(const CString &strPath);

	CCpu* GetCpu(const CString &strPath);
	CExBaseList* GetDeviceModelDatasById(const CString &strCpuID, const CString &strDeviceModelTypeID);
	
	CDataObj* SelectDataObj(const CString &strPath);
	long SelectDataObj(const CString &strPath, CExBaseList &listDatas);
	//shaolei 20220330  
	long SelectDataObj(const CString &strDatasetPath, const CString &strPath, CExBaseList &listDatas);
	long SelectDatas_FilterByPath(const CString &strDatasetPath, const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator=_T("$"));
	long GetDataSetList(const CString &strKey, CExBaseList &oListDataSet);

	CDataSet* GetDataSetByKey(const CString &strKey);
	BOOL GetAllDatasByDatasetKey(CDataSet *pDatasetRef,const CString &strKey);
	CDataSet* GetDataSet_Setting();

protected:
	CCpu* SelectCpu(const CString &strPath, CString &strLeft, CString &strRight);

public:
	BOOL OpenModelFile(const CString &strXmlFile);
	BOOL SaveModelFile(const CString &strXmlFile);
	//模型更新  shaolei 20220716
	void UpdataModelValue(CCpus *pSrcCpus, BOOL bNewNotExist = TRUE);
	CDataObj* FindDataObjByName(const CString &strName);
	CDataObj* FindDataObjByID(const CString &strID);
	CDataSet* FindDataObjByID(const CString &strCpuID, const CString &strDsID);	//20231106 huangliang 没有父级的情况
	CDataObj* FindDataObjByID(const CString &strCpuID, const CString &strDsID, const CString &strDataID);

	long FindDataObjByID(const CString &strID, CExBaseList &listDatas);
	CDataSet* SelectDataset(const CString &strIDPath, const CString &strSeperator);
	CDataSet* SelectDatasetByKey(const CString &strIDPath);
	CDataObj* FindDataObjByID_Has(const CString &strID);
	long FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas);
	void ResetDvmValue();

	void GetDataObjsByNameHas(const CString &strDsIDHas, const CString &strDataNameHas, CExBaseList *pList);

#ifdef GUIDEBOOK_DEV_MODE
//设备数据模型替换
public:
	void DvmReplaceByMap(CDvmDeviceMap *pCDvmDeviceMap);

private:

#endif

};

inline void Gb_InitCpusNameAndID(CString &strName, CString &strID)
{
	strName = g_sLangTxt_EquipDataModel/*_T("设备数据模型")*/;
	strID = _T("CPU");
}

void Gb_GetNewCpusID(CExBaseList &oListCpus, CString &strID);
