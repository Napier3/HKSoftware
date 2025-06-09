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
	CXrioCustomParameter *m_pXrioParas;   //��¼��m_pTplSettingƥ�����ߵ��Ǹ�XrioParameter
	CDvmData *m_pTplSetting;
	CExBaseList m_listMapXrioParas;       //��¼��m_pTplSetting����ƥ���ϵ������XrioParameter

};


class CXrioReadTool : public CExBaseList
{
public:
	CXrioReadTool();
	virtual ~CXrioReadTool();

	CXrio m_oXrio;
	CPowerTestSetMaps m_oPowerTestSetMaps;
	CXKeyDB m_oXrioKeyDB;					//�ؼ��ֿ�xml
	CXKeyMatchRefList m_listMatchSettingKeys;     //Atsģ�嶨ֵ���Ʒִʽ��
	CXKeyMatchRefList m_listMacthParaKeys;  //Xrio�ļ�Parameter�����ִʽ��

	//CMacroSettings m_oMacroSettings;

	//CXrioTplMapObj oMapObj;
	//CExBaseList m_listParaDestObject;    //��ƥ���XrioPatameter��ӵ�������
	//CExBaseList m_listTplSettingObject;  //��ƥ���Tplģ���еĶ�ֵ��ӵ�������

protected:
	CExBaseList m_listCustomParas;
	BOOL m_bIsSameXrio; //�Ƿ�Ϊͬһ��Xrio�ļ�
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
