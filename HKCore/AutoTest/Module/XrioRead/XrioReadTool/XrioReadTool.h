//XrioReadTool.h   CXrioReadTool

#pragma once
#include "..\..\XrioRead\Xrio.h"
#include "..\..\PowerTestSetMaps\PowerTestSetMaps.h"
//#include "..\..\MacroSettingsRead\MacroSettings.h"
#include "..\..\XrioRead\XrioCustomBlock.h"
#include "..\..\XrioRead\XrioCustomParameter.h"
#include "..\..\PowerTestSetMaps\XrioRefParse.h"

#include "..\..\..\..\Module\KeyDb\XKeyDB.h"
#include "..\..\GuideBook\Cpus.h"

#include <afxmt.inl>


class CXrioTplMapObj : public CExBaseList
{
public:
	CXrioTplMapObj();
	CXrioTplMapObj(CXrioCustomParameter *pXrioParas, CDvmData *pTplSetting);
	virtual ~CXrioTplMapObj();

public:
	CXrioCustomParameter *m_pXrioParas;   //记录与m_pTplSetting匹配度最高的那个XrioParameter
	CDvmData *m_pTplSetting;
	CExBaseList m_listMapXrioParas;       //记录与m_pTplSetting存在匹配关系的所有XrioParameter

};


class CXrioReadTool : public CExBaseList
{
public:
	CXrioReadTool();
	virtual ~CXrioReadTool();

	CXrio m_oXrio;
	CPowerTestSetMaps m_oPowerTestSetMaps;
	CXKeyDB m_oXrioKeyDB;					//关键字库xml
	CXKeyMatchRefList m_listMatchSettingKeys;     //Ats模板定值名称分词结果
	CXKeyMatchRefList m_listMacthParaKeys;  //Xrio文件Parameter描述分词结果

	//CMacroSettings m_oMacroSettings;

	//CXrioTplMapObj oMapObj;
	//CExBaseList m_listParaDestObject;    //将匹配的XrioPatameter添加到链表中
	//CExBaseList m_listTplSettingObject;  //将匹配的Tpl模板中的定值添加到链表中

protected:
	CExBaseList m_listCustomParas;
	BOOL m_bIsSameXrio; //是否为同一个Xrio文件
	BOOL m_bHasOpenXrioFile;
	CString m_strXrioFilePath;
	CXrioRefParse m_oPTXrioRefParse;

public:
	CExBaseList* GetCustomParasList() {	  return &m_listCustomParas;   }

	void SetIsSameXrio(BOOL bIsSameXrio = TRUE)  {    m_bIsSameXrio = bIsSameXrio;	   }

	CString GetXrioFilePath(){return m_strXrioFilePath;}
	BOOL OpenXrioFile(const CString &strXrioFilePath);

	BOOL OpenXrioFile();

	BOOL Save_SettingMapsFile();
	BOOL SaveXrioFile();
	BOOL OpenSetMapsFile();
	BOOL HasOpenXrioFile(){return m_bHasOpenXrioFile;}

	void AddAllEnabledParastoListEx(CXrioCustom *pXrioCustom);
	void AddAllEnabledParastoList(CXrioCustomBlock *pXrioCustomBlock);
	void SpliceNameAndDecsription(CXrioCustomParameter *pXrioParameter);
	void SetValueByText(CXrioCustomParameter *pXrioParameter);

	BOOL TransXrioToDeviceModel(CCpus *pCpus);
	BOOL TransXrioToSysPara(CDataSet *pSysPara);
	BOOL TransXrioRefToDevModel(CCpus *pCpus,BOOL bHasMapxmlFile);

	void DvmSettingFilter(CDvmDevice *pDvmDevice, CXKeyDB *pXKeyDB);
	void DvmSettingFilter(CDvmLogicDevice *pDvmLogicDevice, CXKeyDB *pXKeyDB);
	void DvmSettingFilter(CDvmDataset *pDvmDataset, CXKeyDB *pXKeyDB);
	void DvmSettingFilter(CDvmData *pDvmData, CXKeyDB *pXKeyDB);
	void ReplaceSetNameByMap(CDvmData *pDvmData);
	long QueryByKeys(CXKeyMatchRefList *pKeysList, /*CExBaseList &listParas, CExBaseList &listTplSettings,*/ CDvmData *pDvmData, CXKeyDB *pXKeyDB);
	void XrioParaAndSetMap(CXrioTplMapObj *pMapObj, CXrioCustomParameter *pXrioPara);
	CXrioTplMapObj* FindMapObjByDvmData(CDvmData *pDvmData);

	void OnExportModelFile(CCpus *pCpus,CWnd *pParent = NULL);
	//void FilterByDescription(CExBaseList *pListCustomParas, CMacroSettings *pMacroSettings);
	//BOOL FilterByDescription(CString &strParaDescription, CMacroSettings *pMacroSettings);
	//BOOL ParaIsUse(CString &strParaDescription, CSetting *pSetting);
		
};

BOOL ptt_PopOpenPowerTestXrioFileDlg(CString &strPath);
