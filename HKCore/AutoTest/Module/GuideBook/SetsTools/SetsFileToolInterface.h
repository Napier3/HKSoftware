#pragma once

#include "..\..\..\..\Module\FileImExPortBase\FileToolInterface.h"
//#include "..\SysParaEditGroupMngr.h"

#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
#include "..\Device.h"
#endif

#define SETS_TITLE_ID_PARAMETER _T("设备参数")
#define SETS_TITLE_ID_SETTING     _T("保护定值")
#define SETS_TITLE_ID_CTRL           _T("控制字")
#define SETS_TITLE_ID_ENA             _T("软压板")
#define SETS_TITLE_ID_MATRIX       _T("跳闸矩阵")
#define SETS_TITLE_ID_PROT			_T("保护")
#define SETS_TITLE_ID_SETTING2    _T("定值")


class CSetsFileToolInterface : public CFileToolInterface
{
public:
	CSetsFileToolInterface();
	virtual ~CSetsFileToolInterface();

public:
	void CreateSetsMapByFile();
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	void SetCpus(CCpus *pCpus);
#endif

public:
	CDvmLogicDevice m_oLogicDeviceFile;

#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	//GuideBook对象
	CCpus *m_pDestCpus;
	CSysParas* m_pSysParas;
	CDvmDataset *m_pDestGlobalDatas;

	CCpu m_oSetsMap;

	void GetDataset(const CString &strSrcTypeName, const CString &strGbTypeName, CDvmDataset **ppSrcDatast, CDataSet **ppGbDataset);
#endif

protected:
#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	void AddToSetsMap(CCpu *pCpu);
	void AddToSetsMap(CDataSet *pGbDataset);
	void AddToSetsMap(CDataSet *pGbDataset, const CString &strName, const CString &strID);
#endif
	
	CString GetDatatype(CDvmDataset *pDataset);
	void InitGbDataset();
	void InitGbDataset(CDvmDataset *pSrc);
	virtual void InitDatasetIDByName(CDvmDataset *pDataset);

#ifndef _SETS_FILE_TOOL_NOT_USE_GB_
	//CDataObj* FindDataObj(const CString &strDsID, CDataSet *pDest, const CString &strDataName);
	CDataObj* FindDataObj(const CString &strDataType, CDataSet *pDest, const CString &strDataName);
#endif

public:
	void Time_S_to_ms();
	void Time_S_to_ms(CDvmDataset *pSrc);

	void Time_ms_to_S();
	void Time_ms_to_S(CDvmDataset *pSrc);
};
