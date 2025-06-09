
#pragma once

#include "PoMmsData.h"
#include "../MmsWriteXml.h"
// CPoMmsDataSet 命令目标
#include "../../../Module/DataMngr/DvmCmp/DvmDeviceMap.h"
#include "../MmsDatasetMapTool.h"

// #define ATTRID_NUMOFSG      _T("NUMOFSG")
// #define ATTRID_ACTSG        _T("ACTSG")
// #define ATTRID_TMTOTAL      _T("TMTOTAL")
// #define ATTRID_TMEXEC       _T("TMEXEC")
// #define ATTRID_TMSEL        _T("TMSEL")
// #define ATTRID_ERRINFO      _T("ERRINFO")
// #define ATTRID_RECORD_PATH  _T("rcd-file-path")
// #define ATTRID_TimeStartExec  _T("TimeStartExec")
// 
// #define ATTRID_InfoEXEC  _T("InfoEXEC")
// #define ATTRID_InfoSEL  _T("InfoSEL")
// #define ATTRID_TimeGapEnaWrite  _T("TimeGapEnaWrite")
// #define ATTRID_TimeGapSelExec  _T("TimeGapSelExec")
// #define ATTRID_LogMmsMsg  _T("LogMmsMsg")
// 
// #define ATTRID_InfoSetSE  _T("InfoSetSE")
// #define ATTRID_InfoSetSG  _T("InfoSetSG")
// #define ATTRID_tmSetSE       _T("TMSETSE")
// #define ATTRID_tmSetSG        _T("TMSETSG")
// #define ATTRID_InfoWriteData  _T("InfoWriteData")
// #define ATTRID_TestLinkState  _T("TestLinkState")
// #define ATTRID_EnaReadBeforeWrite  _T("ReadBeforeEnaWrite")
// #define ATTRID_TEnaReadBeforeWrite  _T("ReadBeforeEnaWriteT")
// #define ATTRID_LogCount  _T("LogCount")
// #define ATTRID_CurDirFileNum  _T("CurDirFileNum")
// 
// #define ATTRID_DVM_NAME_IS_STD  _T("dvm_name_is_std")//zhouhj 20200210 SOE上送报文采用标准名称
// #define ATTRID_COMM_Error_Code  _T("CommErrorCode")  ////通讯命令错误码值
// #define ATTRID_COMM_Error_Class  _T("CommErrorClass")  ////通讯命令错误类
// #define ATTRID_COMM_Error_InforRpt  _T("CommErrorInforRpt")  ////通讯命令错误信息报告
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"

class CPoMmsDataSet
{
public:
	ACSI_NODE *m_pACSI_NODE;  //设备的指针
	LD_NODE *m_pLD_NODE;      //逻辑设备的指针
	LD_DATASET_INFO *m_pDataset;
	CDvmDataset m_oDatasetForReadXml;
	tagRpt *m_pRpt;
	XMMS_FILE_SYS_OBJ *m_pFileDir;

	CDvmDatasetMap *m_pDvmDatasetMap;
	CDvmDeviceMap  *m_pDvmDeviceMap;
	CDvmDataset    *m_pDvmDataset;
	CString m_strReadSoeDsPath;
	CString m_strDatasetPath;

	CMmsDatasetMapTool *m_pMmsDatasetMapTool;
	CDvmDataset *m_pTempNewDataset;  //2022-11-25  lijunqing 临时创建的数据集对象，用于返回数据
	BOOL m_bTempNewDataset;

	void TempNewDataset();
	void FreeTempNewDataset();

	static CPoMmsDataSet* _NewPoDataset(CMmsDatasetMapTool *pMmsDatasetMapTool);

	static CPoMmsDataSet* _NewPoDataset(ACSI_NODE *pACSI_NODE, LD_NODE *pLD_NODE, LD_DATASET_INFO *pDataset)
	{
		CPoMmsDataSet *pNew = new CPoMmsDataSet();
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = pLD_NODE;
		pNew->m_pDataset = pDataset;
		pNew->m_pRpt = NULL;
		pNew->m_pFileDir = NULL;
		return pNew;
	}
	static CPoMmsDataSet* _NewPoDataset(ACSI_NODE *pACSI_NODE, tagRpt *pRpt)
	{
		CPoMmsDataSet *pNew = new CPoMmsDataSet();
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = NULL;;
		pNew->m_pDataset = NULL;
		pNew->m_pRpt = pRpt;
		pNew->m_pFileDir = NULL;
		return pNew;
	}
	static CPoMmsDataSet* _NewPoDataset(ACSI_NODE *pACSI_NODE, CDvmDataset *pDvmDataset)
	{
		CPoMmsDataSet *pNew = new CPoMmsDataSet();
		pNew->m_pDvmDataset = pDvmDataset;
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = NULL;;
		pNew->m_pDataset = NULL;
		pNew->m_pRpt = NULL;
		pNew->m_pFileDir = NULL;
		return pNew;
	}
	static CPoMmsDataSet* _NewPoFileDir(ACSI_NODE *pACSI_NODE, XMMS_FILE_SYS_OBJ *pFileDir)
	{
		CPoMmsDataSet *pNew = new CPoMmsDataSet();
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = NULL;;
		pNew->m_pDataset = NULL;
		pNew->m_pRpt = NULL;
		pNew->m_pFileDir = pFileDir;
		return pNew;
	}
	
public:
	CPoMmsDataSet();
	virtual ~CPoMmsDataSet();

	virtual void OnFinalRelease();
	BOOL SetXmlData_LD_DATASET_INFO(const CString &strXmlData);
	BOOL SetXmlData_DvmDataset(const CString &strXmlData);

	//2022-12-31 lijunqing  兼容CMS部分
	virtual BOOL SetXmlData_Data(CDvmData *pData);

	BOOL GetXmlDataEx_LD_DATASET_INFO();
	BOOL GetXmlDataEx_DvmDataset();
	BOOL GetXmlDataEx_Rpt();
	BOOL GetXmlDataEx_FileDir();

	//2022-12-31 lijunqing  兼容CMS部分
	virtual BOOL GetXmlDataEx_DvmData(CDvmData *pData);

public:
	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(CString newVal);
	long GetCount(void);
	CPoMmsData* GetItem(long nIndex);
	CPoMmsData* FindDataByID(const CString &strDataID);
	CPoMmsData* FindDataByName(const CString &strName);
	CString GetXmlData(void);
	long SetXmlData(const CString &strXmlData);
	CString GetXmlDataEx(void);

    //2020-9-8  lijunqing
    void InitByDataset(CDvmDataset *pDataset);
};

BOOL po_GetXmlDataEx_DvmData(CDvmData *pData, ACSI_NODE *pDevice);


