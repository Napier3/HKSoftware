#include "StdAfx.h"
#include "AT02D_Tool.h"
#include "../../../Module/DataMngr/DvmDevice.h"

CAT02D_Tool::CAT02D_Tool(void)
{
}


CAT02D_Tool::~CAT02D_Tool(void)
{
}

#ifdef _USE_IN_AT02D_MODE_
BOOL CAT02D_Tool::ExportDeviceModel(CIecCfgDatasMngr *pIecCfgDatasMngr,const CString &strAT02D_CfgPath,const CString &strSaveFilePath ,BOOL bUseHarm)
{
	CDvmDevice oDvmDevice;

	if (oDvmDevice.OpenXmlFile(strAT02D_CfgPath,CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		CDvmLogicDevice *pDvmLogicDevice = (CDvmLogicDevice*)oDvmDevice.FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);
		long nSV_DatasetIndex = 1;
		long nGin_DatasetIndex = 1;
		long nGout_DatasetIndex = 1;
		//		long nDelayIndex = 1,nCurIndex = 1,nVolIndex = 1,nGinChIndex = 1,nGoutChIndex = 1;
		long nSV_CBIndex = 1,nGinCBIndex = 1,nGoutCBIndex = 1;
		CExBaseList oSVList,oGinList,oGoutList;

		pIecCfgDatasMngr->SetAT02D_ChannelID(&oSVList,&oGinList,&oGoutList,nSV_CBIndex,nGinCBIndex,nGoutCBIndex);
		pIecCfgDatasMngr->AddAT02D_Dataset(pDvmLogicDevice,nSV_DatasetIndex,nGin_DatasetIndex,nGout_DatasetIndex,bUseHarm,FALSE);

		oSVList.RemoveAll();
		oGinList.RemoveAll();
		oGoutList.RemoveAll();

		AT02D_ADD_SV_GOOSE_ControlBlocks(pDvmLogicDevice);
		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGin);

		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGin);

		if (oDvmDevice.SaveXmlFile(strSaveFilePath,CDataMngrXmlRWKeys::g_pXmlKeys))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ģ���ļ�[%s],����ɹ�."),strSaveFilePath.GetString());
		} 
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ģ���ļ�[%s],����ʧ��."),strSaveFilePath.GetString());
		}
		}
		else
		{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ļ�[%s]������."),strAT02D_CfgPath.GetString());
		return FALSE;
	}

	return TRUE;
}

BOOL CAT02D_Tool::ExportDeviceModel(CIecCfgDevice *pIecCfgDevice,const CString &strAT02D_CfgPath,const CString &strSaveFilePath ,BOOL bUseHarm)
{
	CDvmDevice oDvmDevice;

	if (oDvmDevice.OpenXmlFile(strAT02D_CfgPath,CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		CDvmLogicDevice *pDvmLogicDevice = (CDvmLogicDevice*)oDvmDevice.FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);
		GenDeviceModel(pIecCfgDevice, pDvmLogicDevice, bUseHarm,FALSE);

		if (oDvmDevice.SaveXmlFile(strSaveFilePath,CDataMngrXmlRWKeys::g_pXmlKeys))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ģ���ļ�[%s],����ɹ�."),strSaveFilePath.GetString());
		} 
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ģ���ļ�[%s],����ʧ��."),strSaveFilePath.GetString());
		}
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ļ�[%s]������."),strAT02D_CfgPath.GetString());
		return FALSE;
	}

	return TRUE;
}

BOOL CAT02D_Tool::GenDeviceModel(CIecCfgDevice *pIecCfgDevice, CDvmLogicDevice *pDvmLogicDevice, BOOL bUseHarm,BOOL bhasMUTestParas)
{
		ASSERT(pDvmLogicDevice);
		long nSV_DatasetIndex = 1;
		long nGin_DatasetIndex = 1;
		long nGout_DatasetIndex = 1;
		long nSV_CBIndex = 1,nGinCBIndex = 1,nGoutCBIndex = 1;
		CExBaseList oSVList,oGinList,oGoutList;
			CExBaseObject *pCurObj = NULL;
			CIecCfgDatasMngr *pCurDatasMngr = NULL;
			CDvmDataset *pIecfgDataset = new CDvmDataset;
			pIecfgDataset->m_strName = _T("�����ļ����ݼ�");
			pIecfgDataset->m_strID = AT02D_DATASET_dsIecfg/*_T("dsIecfg")*/;
			pDvmLogicDevice->AddNewChild(pIecfgDataset);
			CDvmData *pDvmData = NULL;
			POS pos = pIecCfgDevice->GetHeadPosition();

			while(pos)
			{
				pCurObj = pIecCfgDevice->GetNext(pos);

				if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
				{
					pCurDatasMngr = (CIecCfgDatasMngr *)pCurObj;
					pCurDatasMngr->SetAT02D_ChannelID(&oSVList,&oGinList,&oGoutList,nSV_CBIndex,nGinCBIndex,nGoutCBIndex);
					pCurDatasMngr->AddAT02D_Dataset(pDvmLogicDevice,nSV_DatasetIndex,nGin_DatasetIndex,nGout_DatasetIndex,bUseHarm,bhasMUTestParas);
					pDvmData = new CDvmData;
					pDvmData->m_strName = pCurDatasMngr->m_strName;
					pDvmData->m_strID = pCurDatasMngr->m_strID;
					pDvmData->m_strDataType = _T("string");
					pDvmData->m_strValue = pCurDatasMngr->m_strID;
					pIecfgDataset->AddNewChild(pDvmData);
				}
			}

		oSVList.RemoveAll();
		oGinList.RemoveAll();
		oGoutList.RemoveAll();

		AT02D_ADD_SV_GOOSE_ControlBlocks(pDvmLogicDevice);
		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGin);

		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGin);

	return TRUE;
}

BOOL CAT02D_Tool::GenDeviceModel(CIecCfgDatasMngr *pCfgDatasMngr, CDvmLogicDevice *pDvmLogicDevice, BOOL bUseHarm,BOOL bhasMUTestParas)
{
	ASSERT(pDvmLogicDevice);
	long nSV_DatasetIndex = 1;
	long nGin_DatasetIndex = 1;
	long nGout_DatasetIndex = 1;
	long nSV_CBIndex = 1,nGinCBIndex = 1,nGoutCBIndex = 1;
	CExBaseList oSVList,oGinList,oGoutList;
	CDvmDataset *pIecfgDataset = new CDvmDataset;
	pIecfgDataset->m_strName = _T("�����ļ����ݼ�");
	pIecfgDataset->m_strID = AT02D_DATASET_dsIecfg/*_T("dsIecfg")*/;
	pDvmLogicDevice->AddNewChild(pIecfgDataset);
	CDvmData *pDvmData = NULL;

	pCfgDatasMngr->SetAT02D_ChannelID(&oSVList,&oGinList,&oGoutList,nSV_CBIndex,nGinCBIndex,nGoutCBIndex);
	pCfgDatasMngr->AddAT02D_Dataset(pDvmLogicDevice,nSV_DatasetIndex,nGin_DatasetIndex,nGout_DatasetIndex,bUseHarm,bhasMUTestParas);
	pDvmData = new CDvmData;
	pDvmData->m_strName = pCfgDatasMngr->m_strName;
	pDvmData->m_strID = pCfgDatasMngr->m_strID;
	pDvmData->m_strDataType = _T("string");
	pDvmData->m_strValue = pCfgDatasMngr->m_strID;
	pIecfgDataset->AddNewChild(pDvmData);

	oSVList.RemoveAll();
	oGinList.RemoveAll();
	oGoutList.RemoveAll();

	AT02D_ADD_SV_GOOSE_ControlBlocks(pDvmLogicDevice);
	AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
	AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
	AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGin);

	AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
	AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
	AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGin);

	return TRUE;
}

BOOL CAT02D_Tool::GenDeviceModel_BySmvInGin(CIecCfgDatasMngr *pCfgDatasMngr, CDvmLogicDevice *pDvmLogicDevice, BOOL bUseHarm,BOOL bhasMUTestParas)
{
	ASSERT(pDvmLogicDevice);
	long nSmvIn_DatasetIndex = 1;
	long nGin_DatasetIndex = 1;
	long nSmvIn_CBIndex = 1,nSmvOut_CBIndex = 1,nGinCBIndex = 1,nGoutCBIndex = 1;
	CExBaseList oSmvInList,oGinList;
	CDvmDataset *pIecfgDataset = new CDvmDataset;
	pIecfgDataset->m_strName = _T("�����ļ����ݼ�");
	pIecfgDataset->m_strID = AT02D_DATASET_dsIecfg/*_T("dsIecfg")*/;
	pDvmLogicDevice->AddNewChild(pIecfgDataset);
	CDvmData *pDvmData = NULL;

	pCfgDatasMngr->SetAT02D_ChannelID(&oSmvInList,NULL,&oGinList,NULL,nSmvIn_CBIndex,nSmvOut_CBIndex,nGinCBIndex,nGoutCBIndex);
	pCfgDatasMngr->AddAT02D_Dataset_SmvInGin(pDvmLogicDevice,nSmvIn_DatasetIndex,nGin_DatasetIndex,bUseHarm,bhasMUTestParas);
	pDvmData = new CDvmData;
	pDvmData->m_strName = pCfgDatasMngr->m_strName;
	pDvmData->m_strID = pCfgDatasMngr->m_strID;
	pDvmData->m_strDataType = _T("string");
	pDvmData->m_strValue = pCfgDatasMngr->m_strID;
	pIecfgDataset->AddNewChild(pDvmData);

	oSmvInList.RemoveAll();
	oGinList.RemoveAll();

	AT02D_ADD_SV_GOOSE_ControlBlocks(pDvmLogicDevice);
	AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
	AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGin);

	AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
	AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGin);
	return TRUE;
}

// BOOL CAT02D_Tool::ExportDeviceModel(CIecCfgFile *pIecCfgFile,const CString &strAT02D_CfgPath,const CString &strSaveFilePath ,BOOL bUseHarm)
// {
// 	CDvmDevice oDvmDevice;
// 
// 	if (oDvmDevice.OpenXmlFile(strAT02D_CfgPath,CDataMngrXmlRWKeys::g_pXmlKeys))
// 	{
// 		CDvmLogicDevice *pDvmLogicDevice = (CDvmLogicDevice*)oDvmDevice.FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);
// 		ASSERT(pDvmLogicDevice);
// 		CExBaseObject *pAncestor = (CExBaseObject *)pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
// 		long nSV_DatasetIndex = 1;
// 		long nGin_DatasetIndex = 1;
// 		long nGout_DatasetIndex = 1;
// //		long nDelayIndex = 1,nCurIndex = 1,nVolIndex = 1,nGinChIndex = 1,nGoutChIndex = 1;
// 		long nSV_CBIndex = 1,nGinCBIndex = 1,nGoutCBIndex = 1;
// 		CExBaseList oSVList,oGinList,oGoutList;
// 
// 		if (pAncestor == NULL)
// 		{
// 			ASSERT (pIecCfgFile->m_pIecCfgDatasMngr != NULL);
// 			pIecCfgFile->m_pIecCfgDatasMngr->SetAT02D_ChannelID(&oSVList,&oGinList,&oGoutList,nSV_CBIndex,nGinCBIndex,nGoutCBIndex);
// 			pIecCfgFile->m_pIecCfgDatasMngr->AddAT02D_Dataset(pDvmLogicDevice,nSV_DatasetIndex,nGin_DatasetIndex,nGout_DatasetIndex,bUseHarm);
// 		}
// 		else
// 		{
// 			CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pAncestor;
// 			CIecCfgDevice *pIecCfgDevice = pIecCfgFileDevice->GetIecCfgDevice();
// 			ASSERT(pIecCfgDevice);
// 			CExBaseObject *pCurObj = NULL;
// 			CIecCfgDatasMngr *pCurDatasMngr = NULL;
// 			CDvmDataset *pIecfgDataset = new CDvmDataset;
// 			pIecfgDataset->m_strName = _T("�����ļ����ݼ�");
// 			pIecfgDataset->m_strID = AT02D_DATASET_dsIecfg/*_T("dsIecfg")*/;
// 			pDvmLogicDevice->AddNewChild(pIecfgDataset);
// 			CDvmData *pDvmData = NULL;
// 			POS pos = pIecCfgDevice->GetHeadPosition();
// 
// 			while(pos)
// 			{
// 				pCurObj = pIecCfgDevice->GetNext(pos);
// 
// 				if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
// 				{
// 					pCurDatasMngr = (CIecCfgDatasMngr *)pCurObj;
// 					pCurDatasMngr->SetAT02D_ChannelID(&oSVList,&oGinList,&oGoutList,nSV_CBIndex,nGinCBIndex,nGoutCBIndex);
// 					pCurDatasMngr->AddAT02D_Dataset(pDvmLogicDevice,nSV_DatasetIndex,nGin_DatasetIndex,nGout_DatasetIndex,bUseHarm);
// 					pDvmData = new CDvmData;
// 					pDvmData->m_strName = pCurDatasMngr->m_strName;
// 					pDvmData->m_strID = pCurDatasMngr->m_strID;
// 					pDvmData->m_strDataType = _T("string");
// 					pDvmData->m_strValue = pCurDatasMngr->m_strID;
// 					pIecfgDataset->AddNewChild(pDvmData);
// 				}
// 			}
// 		}
// 
// 		oSVList.RemoveAll();
// 		oGinList.RemoveAll();
// 		oGoutList.RemoveAll();
// 
// 		AT02D_ADD_SV_GOOSE_ControlBlocks(pDvmLogicDevice);
// 		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
// 		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
// 		AT02D_SortDataset(pDvmLogicDevice,AT02D_DATASET_dsGin);
// 
// 		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsSV);
// 		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGout);
// 		AT02D_Add_SV_GS_ContrlBlock_Dataset(pDvmLogicDevice,AT02D_DATASET_dsGin);
// 
// 		if (oDvmDevice.SaveXmlFile(strSaveFilePath,CDataMngrXmlRWKeys::g_pXmlKeys))
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ģ���ļ�[%s],����ɹ�."),strSaveFilePath);
// 		} 
// 		else
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("ģ���ļ�[%s],����ʧ��."),strSaveFilePath);
// 		}
// 	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ļ�[%s]������."),strAT02D_CfgPath);
// 		return FALSE;
// 	}
// 
// 	return TRUE;
// }

BOOL CAT02D_Tool::AT02D_ADD_SV_GOOSE_ControlBlocks(CDvmLogicDevice *pDvmLogicDevice)
{
	ASSERT(pDvmLogicDevice);
	CExBaseObject *pCurObj = NULL;
	CDvmDataset *pCurDataset = NULL;
	POS pos = pDvmLogicDevice->GetHeadPosition();
	CString strAppID;
	long nControlBlockIndex = 0;
	CDvmDataset *pDsSvParameter = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsSVCstc/*_T("dsSVCstc")*/);
	CDvmData *pDataSvParameter = NULL;
	CDvmDataset *pDsGooseParameter = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsGoCstc/*_T("dsGoCstc")*/);
	CDvmData *pDataGooseParameter = NULL;
	CDvmDataset *pDsGsIn = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsGsIn/*_T("dsGsIn")*/);
	CDvmData *pDataGsIn = NULL;
	CDvmDataset *pDsLinkState = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsLinkState/*_T("dsLinkState")*/);
	CDvmData *pDataLinkState = NULL;
	CDvmData *pCurData = NULL;
	CDvmDataset *pDs_SvAbnormal = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsSVErr/*_T("dsSVErr")*/);
	CDvmData *pData_SvAbnormal = NULL;
	CDvmDataset *pDs_GooseAbnormal = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsGooseErr/*_T("dsGooseErr")*/);
	CDvmData *pData_GooseAbnormal = NULL;

	CDvmDataset *pDs_RcdStep6U6IRlt = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsRcdStep6U6IRlt/*_T("AT02D_DATASET_dsRcdStep6U6IRlt")*/);
	CDvmData *pData_RcdStep6U6IRlt = NULL;

	CDvmDataset *pDs_Discrete = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsDiscrete/*_T("dsDiscrete")*/);
	CDvmData *pData_Discrete = NULL;
	CDvmDataset *pDs_SVDelay = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsSVDelay/*_T("dsSVDelay")*/);
	CDvmData *pData_SVDelay = NULL;
	CDvmDataset *pDs_SVSyn = (CDvmDataset*)pDvmLogicDevice->FindByID(AT02D_DATASET_dsSVSyn);
	CDvmData *pData_SVSyn = NULL;
	CDvmData *pData_RcdFile = NULL;
	CDvmDataset *pDsTHD = new CDvmDataset;
	pDsTHD->m_strName = _T("������");
	pDsTHD->m_strID = AT02D_DATASET_dsTHD/*_T("dsTHD")*/;
	pDvmLogicDevice->AddNewChild(pDsTHD);
	CDvmData *pCurTHD_Data = NULL;

	pDataSvParameter = AT02D_FindAppIDDataFromDataset(pDsSvParameter);
	pDataGooseParameter = AT02D_FindAppIDDataFromDataset(pDsGooseParameter);
	pDataGsIn = AT02D_FindAppIDDataFromDataset(pDsGsIn);
	pDataLinkState = AT02D_FindAppIDDataFromDataset(pDsLinkState);
	pData_SvAbnormal = AT02D_FindAppIDDataFromDataset(pDs_SvAbnormal);
	pData_RcdStep6U6IRlt = AT02D_FindAppIDDataFromDataset(pDs_RcdStep6U6IRlt);
	pData_GooseAbnormal = AT02D_FindAppIDDataFromDataset(pDs_GooseAbnormal);
	pData_Discrete = AT02D_FindAppIDDataFromDataset(pDs_Discrete);
	pData_SVDelay = AT02D_FindAppIDDataFromDataset(pDs_SVDelay);
	pData_SVSyn = AT02D_FindAppIDDataFromDataset(pDs_SVSyn);

	if (pDs_SVDelay != NULL)
	{
		pData_RcdFile = (CDvmData *)pDs_SVDelay->FindByID(_T("RcdFile"));
	}

	while(pos)
	{
		pCurObj = pDvmLogicDevice->GetNext(pos);

		if (pCurObj->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			pCurDataset = (CDvmDataset*)pCurObj;

			if (IsSV_Dataset(pCurDataset->m_strName,strAppID,nControlBlockIndex))
			{
				AT02D_AddSV_THD_Datas(pDsTHD,pCurDataset);
				AT02D_AddSVSyn(pDs_SVSyn,nControlBlockIndex);//zhouhj ���SVͬ�������ݼ��еڶ����Ժ�Ŀ��ƿ����һ�����ƿ�֮���ͬ�����
				AT02D_CloneSVGooseData(pDsSvParameter,pDataSvParameter,strAppID,AT02D_DATA_ID_SV/*_T("SV")*/,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDs_SvAbnormal,pData_SvAbnormal,strAppID,AT02D_DATA_ID_SV/*_T("SV")*/,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDs_RcdStep6U6IRlt,pData_RcdStep6U6IRlt,strAppID,AT02D_DATA_ID_SV,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDs_Discrete,pData_Discrete,strAppID,AT02D_DATA_ID_SV/*_T("SV")*/,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDs_SVDelay,pData_SVDelay,strAppID,AT02D_DATA_ID_SV/*_T("SV")*/,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDsLinkState,pDataLinkState,strAppID,AT02D_DATA_ID_SV/*_T("SV")*/,nControlBlockIndex);
//				AT02D_CloneRcdFileData(pDs_SVDelay,pData_RcdFile,strAppID,AT02D_DATA_ID_RCD_FILE/*_T("_Rcd_file")*/,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDs_SVSyn,pData_SVSyn,strAppID,AT02D_DATA_ID_SV/*_T("SV")*/,nControlBlockIndex);
			}
			else if (IsGout_Dataset(pCurDataset->m_strName,strAppID,nControlBlockIndex))
			{
				AT02D_CloneSVGooseData(pDsGooseParameter,pDataGooseParameter,strAppID,AT02D_DATA_ID_GOOSE/*_T("Goose")*/,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDs_GooseAbnormal,pData_GooseAbnormal,strAppID,AT02D_DATA_ID_GOOSE/*_T("Goose")*/,nControlBlockIndex);
				AT02D_CloneSVGooseData(pDsLinkState,pDataLinkState,strAppID,AT02D_DATA_ID_GOOSE/*_T("Goose")*/,nControlBlockIndex);
			}
			else if (IsGin_Dataset(pCurDataset->m_strName,strAppID,nControlBlockIndex))
			{
				CDvmData *pDataTmp = AT02D_CloneSVGooseData(pDsGsIn,pDataGsIn,strAppID,AT02D_DATA_ID_GSIN/*_T("GsIn")*/,nControlBlockIndex);
				
				if (pDataTmp != NULL)
				{
					pDataTmp->m_strValue = strAppID;
				}
			}
		}
	}

	AT02D_DeleteDataFromDataset(pDsSvParameter,pDataSvParameter);
	AT02D_DeleteDataFromDataset(pDsGooseParameter,pDataGooseParameter);
	AT02D_DeleteDataFromDataset(pDs_SvAbnormal,pData_SvAbnormal);
	AT02D_DeleteDataFromDataset(pDs_RcdStep6U6IRlt,pData_RcdStep6U6IRlt);
	AT02D_DeleteDataFromDataset(pDs_GooseAbnormal,pData_GooseAbnormal);
	AT02D_DeleteDataFromDataset(pDs_Discrete,pData_Discrete);
	AT02D_DeleteDataFromDataset(pDs_SVDelay,pData_SVDelay);
	AT02D_DeleteDataFromDataset(pDs_SVDelay,pData_RcdFile);
	AT02D_DeleteDataFromDataset(pDs_SVSyn,pData_SVSyn);
	AT02D_DeleteDataFromDataset(pDsGsIn,pDataGsIn);
	AT02D_DeleteDataFromDataset(pDsLinkState,pDataLinkState);

	return TRUE;
}

void CAT02D_Tool::AT02D_SortDataset(CDvmLogicDevice *pDvmLogicDevice,const CString &strDatasetID)
{
	ASSERT(pDvmLogicDevice);
	CExBaseList oTmpList;
	CExBaseObject *pCurObj = NULL;
	POS pos = pDvmLogicDevice->GetHeadPosition();

	while(pos)
	{
		pCurObj = pDvmLogicDevice->GetNext(pos);

		if (pCurObj->m_strID.Find(strDatasetID) == 0)
		{
			oTmpList.AddTail(pCurObj);
			pDvmLogicDevice->Remove(pCurObj);
		}
	}

	pDvmLogicDevice->Append(oTmpList);
	oTmpList.RemoveAll();
}

void CAT02D_Tool::AT02D_Add_SV_GS_ContrlBlock_Dataset(CDvmLogicDevice *pDvmLogicDevice,const CString &strDatasetID)
{
	ASSERT(pDvmLogicDevice);
	CDvmDataset *pDataset = NULL;

	if (strDatasetID == AT02D_DATASET_dsSV)
	{
		pDataset = new CDvmDataset;
		pDataset->m_strName = _T("����ֵ���ƿ����ݼ�");
		pDataset->m_strID = AT02D_DATASET_dsCBlockSV;
		pDvmLogicDevice->AddNewChild(pDataset);
	}
	else if (strDatasetID == AT02D_DATASET_dsGout)
	{
		pDataset = new CDvmDataset;
		pDataset->m_strName = _T("GOOSE�������ƿ����ݼ�");
		pDataset->m_strID = AT02D_DATASET_dsCBlockGout;
		pDvmLogicDevice->AddNewChild(pDataset);
	}
	else if (strDatasetID == AT02D_DATASET_dsGin)
	{
		pDataset = new CDvmDataset;
		pDataset->m_strName = _T("GOOSE������ƿ����ݼ�");
		pDataset->m_strID = AT02D_DATASET_dsCBlockGin;
		pDvmLogicDevice->AddNewChild(pDataset);
	}
	else 
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("AT02D_Add_SV_GS_ContrlBlock_Dataset��������2��ID��%s��������."),strDatasetID.GetString());
		return;
	}
	
	CString strTmp;
	CDvmData *pDvmData = NULL;
	CExBaseObject *pCurObj = NULL;
	POS pos = pDvmLogicDevice->GetHeadPosition();

	while(pos)
	{
		pCurObj = pDvmLogicDevice->GetNext(pos);

		if (pCurObj->m_strID.Find(strDatasetID) == 0)
		{
			strTmp = pCurObj->m_strID;
			strTmp.Replace(strDatasetID,_T(""));

			if ((strTmp.GetLength()>0)&&(strTmp.GetAt(0)>='0')&&(strTmp.GetAt(0)<='9'))//���ݼ����ƺ���ַ����������ֵĲ���
			{
				pDvmData = new CDvmData;
				pDvmData->m_strName = pCurObj->m_strName;
				pDvmData->m_strID = pCurObj->m_strID;
				pDvmData->m_strDataType = _T("string");

				if (pDvmData->m_strName.GetLength()>6)
				{
					pDvmData->m_strValue = pDvmData->m_strName.Left(6);//name�����е�ǰ6���ַ�ΪAppID
				}

				pDataset->AddNewChild(pDvmData);
			}
		}
	}
}

CDvmData* CAT02D_Tool::AT02D_FindAppIDDataFromDataset(CDvmDataset *pDs)
{
	if (pDs == NULL)
	{
		return NULL;
	}

	return (CDvmData*)pDs->FindByID(_T("AppID"));
}

BOOL CAT02D_Tool::IsSV_Dataset(const CString &strDatasetName,CString &strAppID,long &nControlBlockIndex)
{
	long nIndex = strDatasetName.Find(AT02D_DATASET_dsSV/*_T("dsSV")*/);

	if (nIndex == -1)
	{
		return FALSE;
	}

	strAppID = strDatasetName.Mid(nIndex+4);
	nControlBlockIndex = CString_To_long(strAppID);

	nIndex = strDatasetName.Find('_');

	if (nIndex<=0)
	{
		return FALSE;
	}

	strAppID = strDatasetName.Left(nIndex);
	return TRUE;
}

BOOL CAT02D_Tool::IsGin_Dataset(const CString &strDatasetName,CString &strAppID,long &nControlBlockIndex)
{
	long nIndex = strDatasetName.Find(AT02D_DATASET_dsGin/*_T("dsGin")*/);

	if (nIndex == -1)
	{
		return FALSE;
	}

	strAppID = strDatasetName.Mid(nIndex+5);
	nControlBlockIndex = CString_To_long(strAppID);

	nIndex = strDatasetName.Find('_');

	if (nIndex<=0)
	{
		return FALSE;
	}

	strAppID = strDatasetName.Left(nIndex);
	return TRUE;
}

BOOL CAT02D_Tool::IsGout_Dataset(const CString &strDatasetName,CString &strAppID,long &nControlBlockIndex)
{
	long nIndex = strDatasetName.Find(AT02D_DATASET_dsGout/*_T("dsGout")*/);

	if (nIndex == -1)
	{
		return FALSE;
	}

	strAppID = strDatasetName.Mid(nIndex+6);
	nControlBlockIndex = CString_To_long(strAppID);

	nIndex = strDatasetName.Find('_');

	if (nIndex<=0)
	{
		return FALSE;
	}

	strAppID = strDatasetName.Left(nIndex);
	return TRUE;
}

void CAT02D_Tool::AT02D_AddSV_THD_Datas(CDvmDataset *pDsTHD,CDvmDataset *pDsSV)
{
	ASSERT(pDsTHD);
	ASSERT(pDsSV);
	POS pos = pDsSV->GetHeadPosition();
	CDvmData *pCurData = NULL;
	CExBaseObject *pCurObj = NULL;
	CDvmData *pTHD_Data = NULL;

	while(pos)
	{
		pCurObj = pDsSV->GetNext(pos);

		if (pCurObj->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			pCurData = (CDvmData *)pCurObj;
			pTHD_Data = new CDvmData;
			pTHD_Data->m_strName = pCurData->m_strName;
			pTHD_Data->m_strID.Format(_T("%s_THD"),pCurData->m_strID.GetString());
			pTHD_Data->m_strDataType = _T("FLOAT");
			pDsTHD->AddNewChild(pTHD_Data);
		}
	}
}

void CAT02D_Tool::AT02D_AddSVSyn(CDvmDataset *pDs_SVSyn,long nControlBlockIndex)
{
	if ((pDs_SVSyn == NULL)||(nControlBlockIndex< 2))
	{
		return;
	}

	CString strID;
	strID.Format(_T("SV%ld_SV1"),nControlBlockIndex);
	CDvmData *pDvmData = (CDvmData*)pDs_SVSyn->FindByID(strID);

	if (pDvmData == NULL)
	{
		pDvmData = new CDvmData;
		pDs_SVSyn->AddNewChild(pDvmData);
		pDvmData->m_strDataType = _T("FLOAT");
		pDvmData->m_strID = strID;
		pDvmData->m_strName.Format(_T("SV%d-SV1ͬ�����"),nControlBlockIndex);
	}
}

CDvmData* CAT02D_Tool::AT02D_CloneSVGooseData(CDvmDataset *pDs,CDvmData *pData,const CString &strAppID,const CString &strContrlName,const long &nControlBlockIndex)
{
	if (pData == NULL)
	{
		return NULL;
	}

	CDvmData *pCurData = (CDvmData*)pData->Clone();
	pCurData->m_strID.Format(_T("%s%ld"),strContrlName.GetString(),nControlBlockIndex);
	pCurData->m_strName = strAppID;
	pDs->AddNewChild(pCurData);
	CString strParentID,strTmp;
	strParentID.Format(_T("%s$"),pCurData->m_strID.GetString());

	POS pos_value1 = pCurData->GetHeadPosition();
	CDvmValue *pDvmValue1 = NULL;

	while(pos_value1)
	{
		pDvmValue1 = (CDvmValue*)pCurData->GetNext(pos_value1);
		strTmp.Format(_T("%s%s"),strParentID.GetString(),pDvmValue1->m_strID.GetString());
		pDvmValue1->m_strID = strTmp;
//		pDvmValue1->m_strID.Insert(0,strParentID);

		if (pDvmValue1->GetCount()>0)
		{
			POS pos_value2 = pDvmValue1->GetHeadPosition();
			CDvmValue *pDvmValue2 = NULL;

			while(pos_value2)
			{
				pDvmValue2 = (CDvmValue*)pDvmValue1->GetNext(pos_value2);
				strTmp.Format(_T("%s%s"),strParentID.GetString(), pDvmValue2->m_strID.GetString());
				pDvmValue2->m_strID = strTmp;
			}
		}
	}

	return pCurData;
}

void CAT02D_Tool::AT02D_CloneRcdFileData(CDvmDataset *pDs,CDvmData *pData,const CString &strAppID,const CString &strContrlName,const long &nControlBlockIndex)
{
	if (pData == NULL)
	{
		return;
	}

	CDvmData *pCurData = (CDvmData*)pData->Clone();
	pCurData->m_strID.Format(_T("SV%ld%s"), nControlBlockIndex, strContrlName.GetString());
	pCurData->m_strName.Format(_T("%s%s"), strAppID.GetString(), strContrlName.GetString());
	pDs->AddNewChild(pCurData);
	CString strParentID,strTmp;
	strParentID.Format(_T("%s$"), pCurData->m_strID.GetString());

	POS pos_value1 = pCurData->GetHeadPosition();
	CDvmValue *pDvmValue1 = NULL;

	while(pos_value1)
	{
		pDvmValue1 = (CDvmValue*)pCurData->GetNext(pos_value1);
		strTmp.Format(_T("%s%s"),  strParentID.GetString(),  pDvmValue1->m_strID.GetString());
		pDvmValue1->m_strID = strTmp;

		if (pDvmValue1->GetCount()>0)
		{
			POS pos_value2 = pDvmValue1->GetHeadPosition();
			CDvmValue *pDvmValue2 = NULL;

			while(pos_value2)
			{
				pDvmValue2 = (CDvmValue*)pDvmValue1->GetNext(pos_value2);
				strTmp.Format(_T("%s%s"),  strParentID.GetString(),  pDvmValue2->m_strID.GetString());
				pDvmValue2->m_strID = strTmp;
			}
		}
	}
}

void CAT02D_Tool::AT02D_DeleteDataFromDataset(CDvmDataset *pDs,CDvmData *pData)
{
	if ((pDs== NULL)||(pData == NULL))
	{
		return;
	}

	pDs->Delete(pData);
}

void CAT02D_Tool::GenerateAT02D_Iecfg(CIecCfgDevice *pIecfgDevice ,long nMaxFiberNum)
{
	ASSERT(pIecfgDevice);
	CIecCfgDatasMngr *pIecfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->FindByClassID(CFGCLASSID_CIECCFGDATASMNGR);

	if (pIecfgDatasMngr == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("�����ļ�����Ϊ��."));
		return;
	}

	pIecfgDevice->m_pCurrDatasMngr = NULL;
	pIecfgDevice->Remove(pIecfgDatasMngr);

	long nMaxSVControlNum = 2;//��ͬ���ͬʱ�����SV���ƿ�����
	long nMaxTestCount = nMaxFiberNum/nMaxSVControlNum;//��Ҫ�ּ��ν��в���,���ܽ����й�ڲ�����ȫ
	long nCurTestIndex = 0;

	if ((nMaxFiberNum%nMaxSVControlNum)>0)
	{
		nMaxTestCount++;
	}

	for (nCurTestIndex = 0;nCurTestIndex<nMaxTestCount;nCurTestIndex++)
	{
		AddIecfgDatasMngr_SVAccuracyTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
		AddIecfgDatasMngr_ThdTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
	}

	nMaxSVControlNum = 3;
	nMaxTestCount = nMaxFiberNum/nMaxSVControlNum;

	if ((nMaxFiberNum%nMaxSVControlNum)>0)
	{
		nMaxTestCount++;
	}

	for (nCurTestIndex = 0;nCurTestIndex<nMaxTestCount;nCurTestIndex++)
	{
		AddIecfgDatasMngr_DispersionTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
		AddIecfgDatasMngr_SVSnyTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
		AddIecfgDatasMngr_SVDelayTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
		AddIecfgDatasMngr_GooseSnyTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
	}

	if (nMaxFiberNum<=3)//���ܹ����С�ڵ���3ʱ,����3�����ƿ�ͬʱ�������,�������6�����ƿ�ͬʱ����
	{
		nMaxSVControlNum = 3;
	} 
	else
	{
		nMaxSVControlNum = 6;
	}
	
	nMaxTestCount = nMaxFiberNum/nMaxSVControlNum;

	if ((nMaxFiberNum%nMaxSVControlNum)>0)
	{
		nMaxTestCount++;
	}

	for (nCurTestIndex = 0;nCurTestIndex<nMaxTestCount;nCurTestIndex++)
	{
		AddIecfgDatasMngr_TimeControlTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
		AddIecfgDatasMngr_TimeMeasureTest(pIecfgDevice,pIecfgDatasMngr,nCurTestIndex,nMaxSVControlNum,nMaxFiberNum);
	}

//	AddIecfgDatasMngr_SVAccuracyTest(pIecfgDevice,pIecfgDatasMngr);
//	AddIecfgDatasMngr_ThdTest(pIecfgDevice,pIecfgDatasMngr);
//	AddIecfgDatasMngr_DispersionTest(pIecfgDevice,pIecfgDatasMngr);
//	AddIecfgDatasMngr_SVSnyTest(pIecfgDevice,pIecfgDatasMngr);
//	AddIecfgDatasMngr_GooseSnyTest(pIecfgDevice,pIecfgDatasMngr);
//	AddIecfgDatasMngr_SVDelayTest(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_TimeControlTest(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_TimeMeasureTest(pIecfgDevice,pIecfgDatasMngr);

// 	AddIecfgDatasMngr_GooseSendTest(pIecfgDevice,pIecfgDatasMngr);//��δʵ������
// 	AddIecfgDatasMngr_GooseAcceptTest1(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_GooseAcceptTest2(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_SVCstcTest(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_GooseCstcTest(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_SVErrorTest(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_GooseErrorTest(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_BoutTimeTest(pIecfgDevice,pIecfgDatasMngr);
// 	AddIecfgDatasMngr_MultiFiberSVAccuracyTest(pIecfgDevice,pIecfgDatasMngr);

//	pIecfgDevice->SetFiber2IndexByFiberIndex(-2);

	pIecfgDevice->SortByID();
	delete pIecfgDatasMngr;
}

void CAT02D_Tool::AddIecfgDatasMngr_SVAccuracyTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr
												   ,long nTestIndex,long nMaxSVControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("����ֵ׼ȷ�Ȳ���%ld"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%d"),AT02D_FUNC_ID_SVAccuracyTest,nTestIndex+1);
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	long nBeginFiberIndex = nTestIndex*nMaxSVControlNum;

	if (!pSmvMngr->SetCfgDataCountEx(nMaxSVControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����ֵ׼ȷ�Ȳ���[SVAccuracyTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pSmvMngr->GetCfgDataCount(),nMaxSVControlNum);
	}

	if (!pGinMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����ֵ׼ȷ�Ȳ���[SVAccuracyTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����ֵ׼ȷ�Ȳ���[SVAccuracyTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_ThdTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr,long nTestIndex,long nMaxSVControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("�����ʲ���%ld"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%ld"),AT02D_FUNC_ID_ThdTest,nTestIndex+1);
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	long nBeginFiberIndex = nTestIndex*nMaxSVControlNum;

	if (!pSmvMngr->SetCfgDataCountEx(nMaxSVControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ʲ���[ThdTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pSmvMngr->GetCfgDataCount(),nMaxSVControlNum);
	}

	if (!pGinMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ʲ���[ThdTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ʲ���[ThdTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_DispersionTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr,long nTestIndex,long nMaxSVControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("��ɢ�Ȳ���%d"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%ld"),AT02D_FUNC_ID_DispersionTest,nTestIndex+1);
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	long nBeginFiberIndex = nTestIndex*nMaxSVControlNum;

	if (!pSmvMngr->SetCfgDataCountEx(nMaxSVControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ɢ�Ȳ���[DispersionTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pSmvMngr->GetCfgDataCount(),nMaxSVControlNum);
	}

	if (!pGinMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ɢ�Ȳ���[DispersionTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ɢ�Ȳ���[DispersionTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_SVSnyTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr,long nTestIndex,long nMaxSVControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("SVͬ�������%ld"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%ld"),AT02D_FUNC_ID_SVSnyTest,nTestIndex+1)/*_T("SVSnyTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	CIecCfg92Data *pCurCfg92Data = (CIecCfg92Data*)pSmvMngr->GetIecCfgData(0);
	long nBeginFiberIndex = nTestIndex*nMaxSVControlNum;

	if (pCurCfg92Data != NULL)
	{
		pCurCfg92Data->m_nDelay = 1000;
		pCurCfg92Data = (CIecCfg92Data*)pSmvMngr->GetIecCfgData(1);

		if (pCurCfg92Data != NULL)
		{
			pCurCfg92Data->m_nDelay = 1000;
			pCurCfg92Data = (CIecCfg92Data*)pSmvMngr->GetIecCfgData(2);

			if (pCurCfg92Data != NULL)
			{
				pCurCfg92Data->m_nDelay = 1000;
			}
		}
	}

	if (!pSmvMngr->SetCfgDataCountEx(nMaxSVControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SVͬ�������[SVSnyTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pSmvMngr->GetCfgDataCount(),nMaxSVControlNum);
	}

	if (!pGinMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SVͬ�������[SVSnyTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SVͬ�������[SVSnyTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_GooseSnyTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr,long nTestIndex,long nMaxSVControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("GOOSEͬ�������%ld"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%ld"),AT02D_FUNC_ID_GooseSnyTest,nTestIndex+1);
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	long nBeginFiberIndex = nTestIndex*nMaxSVControlNum;

	if (!pSmvMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSEͬ�������[GooseSnyTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSEͬ�������[GooseSnyTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCountEx(nMaxSVControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSEͬ�������[GooseSnyTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pGoutMngr->GetCfgDataCount(),nMaxSVControlNum);
	}

	long nGoutNum = pGoutMngr->GetCfgDataCount();

	for (long nIndex = 0;nIndex<nGoutNum;nIndex++)
	{
		if (!pGoutMngr->SetCfgDataGoutMap(nIndex,nIndex + 1,1))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSEͬ�������[GooseSnyTest]Gout���ƿ�%ld: Gout����ӳ��ʧ��."),nIndex+1);
		}
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_SVDelayTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr,long nTestIndex,long nMaxSVControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("SV��ʱ����%ld"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%ld"),AT02D_FUNC_ID_SVDelayTest,nTestIndex+1);/*_T("SVDelayTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	CIecCfg92Data *pCurCfg92Data = (CIecCfg92Data*)pSmvMngr->GetIecCfgData(0);
	long nBeginFiberIndex = nTestIndex*nMaxSVControlNum;

	if (pCurCfg92Data != NULL)
	{
		pCurCfg92Data->m_nDelay = 500;
		pCurCfg92Data->SetAbc(1, 1, 0);
		pCurCfg92Data = (CIecCfg92Data*)pSmvMngr->GetIecCfgData(1);

		if (pCurCfg92Data != NULL)
		{
			pCurCfg92Data->m_nDelay = 1000;
			pCurCfg92Data->SetPabc(1, 1, 0);
			pCurCfg92Data = (CIecCfg92Data*)pSmvMngr->GetIecCfgData(2);

			if (pCurCfg92Data != NULL)
			{
				pCurCfg92Data->SetSabc(1, 1, 0);
				pCurCfg92Data->m_nDelay = 3000;
			}
		}
	}

	if (!pSmvMngr->SetCfgDataCountEx(nMaxSVControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SV��ʱ����[SVDelayTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pSmvMngr->GetCfgDataCount(),nMaxSVControlNum);
	}

	if (!pGinMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SV��ʱ����[SVDelayTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SV��ʱ����[SVDelayTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_TimeControlTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr,long nTestIndex,long nMaxGSControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("ʱ�����׼ȷ�Ȳ���%ld"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%ld"),AT02D_FUNC_ID_TimeControlTest,nTestIndex+1);
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	long nBeginFiberIndex = nTestIndex*nMaxGSControlNum;

	if (!pSmvMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ʱ�����׼ȷ�Ȳ���[TimeControlTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ʱ�����׼ȷ�Ȳ���[TimeControlTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCountEx(nMaxGSControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ʱ�����׼ȷ�Ȳ���[TimeControlTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pGoutMngr->GetCfgDataCount(),nMaxGSControlNum);
	}

	long nGoutNum = pGoutMngr->GetCfgDataCount();

	for (long nIndex = 0;nIndex<nGoutNum;nIndex++)
	{
		if (!pGoutMngr->SetCfgDataGoutMap(nIndex,nIndex + 1,1))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSEʱ�����׼ȷ�Ȳ���[GooseSnyTest]Gout���ƿ�%ld: Gout����ӳ��ʧ��."),nIndex+1);
		}
	}

// 	if (!pGoutMngr->SetCfgDataGoutMap(0,1,nMaxGSControlNum))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSEʱ�����׼ȷ�Ȳ���[TimeControlTest]Gout���ƿ�1: Gout����ӳ��ʧ��."));
// 	}
}

void CAT02D_Tool::AddIecfgDatasMngr_TimeMeasureTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr,long nTestIndex,long nMaxGSControlNum,long nTotalFiberNum)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName.Format(_T("ʱ�����׼ȷ�Ȳ���%ld"),nTestIndex+1);
	pCurIecfgDatasMngr->m_strID.Format(_T("%s%ld"),AT02D_FUNC_ID_TimeMeasureTest,nTestIndex+1);
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	long nBeginFiberIndex = nTestIndex*nMaxGSControlNum;

	if (!pSmvMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ʱ�����׼ȷ�Ȳ���[TimeMeasureTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCountEx(nMaxGSControlNum,nBeginFiberIndex,nBeginFiberIndex+AT02D_FIRST_FIBER_Index,nTotalFiberNum,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ʱ�����׼ȷ�Ȳ���[TimeMeasureTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���%ld."),pGinMngr->GetCfgDataCount(),nMaxGSControlNum);
	}

	if (!pGoutMngr->SetCfgDataCountEx(1,nBeginFiberIndex,AT02D_FIRST_FIBER_Index,nTotalFiberNum,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("ʱ�����׼ȷ�Ȳ���[TimeMeasureTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}

	long nGinNum = pGinMngr->GetCfgDataCount();

	for (long nIndex = 0;nIndex<nGinNum;nIndex++)
	{
		if (!pGinMngr->SetCfgDataGinMap(nIndex,nIndex + 1,1))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSEʱ�����׼ȷ�Ȳ���[GooseSnyTest]Gin���ƿ�%ld: Gin����ӳ��ʧ��."),nIndex+1);
		}
	}

// 	if (!pGinMngr->SetCfgDataGinMap(0,1,nMaxGSControlNum))
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("ʱ�����׼ȷ�Ȳ���[TimeMeasureTest]Gin���ƿ�: Gin����ӳ��ʧ��."));
// 	}
}

void CAT02D_Tool::AddIecfgDatasMngr_GooseSendTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("GOOSE������������");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_GooseSendTest/*_T("GooseSendTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();
	pGoutMngr->IsAT02D_Invalid();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������[GooseSendTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������[GooseSendTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(15,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������[GooseSendTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���15."),pGoutMngr->GetCfgDataCount());
	}

	long nGoutNum = pGoutMngr->GetCfgDataCount();

	for (long nIndex = 0;nIndex<nGoutNum;nIndex++)
	{
		if (!pGoutMngr->SetCfgDataGoutMap(nIndex,1,1))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������[GooseSendTest]Gout���ƿ�%ld: Gout����ӳ��ʧ��."),nIndex+1);
		}
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_GooseAcceptTest1(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("GOOSE������������1");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_GooseAcceptTest1/*_T("GooseAcceptTest1")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������1[GooseAcceptTest1]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(7,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������1[GooseAcceptTest1]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���7."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������1[GooseAcceptTest1]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}

	long nGinNum = pGinMngr->GetCfgDataCount();

	for (long nIndex = 0;nIndex<nGinNum;nIndex++)
	{
		if (!pGinMngr->SetCfgDataGinMap(nIndex,nIndex+1,1))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������1[GooseAcceptTest1]Gin���ƿ�%ld: Gin����ӳ��ʧ��."),nIndex+1);
		}
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_GooseAcceptTest2(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("GOOSE������������2");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_GooseAcceptTest2/*_T("GooseAcceptTest2")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������2[GooseAcceptTest2]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	pGinMngr->IsAT02D_Invalid();
	pGinMngr->DeleteCfgDataByNum(7);

	if (!pGinMngr->SetCfgDataCount(8,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������2[GooseAcceptTest2]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���8."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������2[GooseAcceptTest2]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}

	long nGinNum = pGinMngr->GetCfgDataCount();

	for (long nIndex = 0;nIndex<nGinNum;nIndex++)
	{
		if (!pGinMngr->SetCfgDataGinMap(nIndex,nIndex+1,1))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE������������2[GooseAcceptTest2]Gin���ƿ�%ld: Gin����ӳ��ʧ��."),nIndex+8);
		}
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_SVCstcTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("��������һ���Բ���");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_SVCstcTest/*_T("SVCstcTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������һ���Բ���[SVCstcTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������һ���Բ���[SVCstcTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������һ���Բ���[SVCstcTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_GooseCstcTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("GOOSE����һ���Բ���");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_GooseCstcTest/*_T("GooseCstcTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE����һ���Բ���[GooseCstcTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE����һ���Բ���[GooseCstcTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE����һ���Բ���[GooseCstcTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_SVErrorTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("���������쳣ģ�����");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_SVErrorTest/*_T("SVErrorTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���������쳣ģ�����[SVErrorTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���������쳣ģ�����[SVErrorTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���������쳣ģ�����[SVErrorTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_GooseErrorTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("GOOSE�����쳣ģ�����");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_GooseErrorTest/*_T("GooseErrorTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����쳣ģ�����[GooseErrorTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����쳣ģ�����[GooseErrorTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����쳣ģ�����[GooseErrorTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_BoutTimeTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("Ӳ�ӵ�ʱ�����");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_BoutTimeTest/*_T("BoutTimeTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Ӳ�ӵ�ʱ�����[BoutTimeTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Ӳ�ӵ�ʱ�����[BoutTimeTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Ӳ�ӵ�ʱ�����[BoutTimeTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataGinMap(0,1,1))
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("Ӳ�ӵ�ʱ�����[BoutTimeTest]Gin���ƿ�: Gin����ӳ��ʧ��."));
	}

	if (!pGoutMngr->SetCfgDataGoutMap(0,1,1))
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("Ӳ�ӵ�ʱ�����[BoutTimeTest]Gout���ƿ�: Gout����ӳ��ʧ��."));
	}
}

void CAT02D_Tool::AddIecfgDatasMngr_MultiFiberSVAccuracyTest(CIecCfgDevice *pIecfgDevice,CIecCfgDatasMngr *pSTD_IecfgDatasMngr)
{
	CIecCfgDatasMngr *pCurIecfgDatasMngr = (CIecCfgDatasMngr*)pSTD_IecfgDatasMngr->Clone();
	pCurIecfgDatasMngr->m_strName = _T("���ڲ���ֵ׼ȷ�Ȳ���");
	pCurIecfgDatasMngr->m_strID = AT02D_FUNC_ID_MultiSVAccuracyTest/*_T("MultiSVAccuracyTest")*/;
	pIecfgDevice->AddNewChild(pCurIecfgDatasMngr);

	CIecCfgGinDatas *pGinMngr = pCurIecfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pCurIecfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pCurIecfgDatasMngr->GetGoutMngr();

	if (!pSmvMngr->SetCfgDataCount(6,AT02D_FIRST_FIBER_Index,FALSE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ڲ���ֵ׼ȷ�Ȳ���[MultiSVAccuracyTest]ȱ��SV���ƿ�: ��ǰSV���ƿ���%ld,ʵ����Ҫ���ƿ���6."),pSmvMngr->GetCfgDataCount());
	}

	if (!pGinMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+2,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ڲ���ֵ׼ȷ�Ȳ���[MultiSVAccuracyTest]ȱ��Gin���ƿ�: ��ǰGin���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGinMngr->GetCfgDataCount());
	}

	if (!pGoutMngr->SetCfgDataCount(1,AT02D_FIRST_FIBER_Index+3,TRUE))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("���ڲ���ֵ׼ȷ�Ȳ���[MultiSVAccuracyTest]ȱ��Gout���ƿ�: ��ǰGout���ƿ���%ld,ʵ����Ҫ���ƿ���1."),pGoutMngr->GetCfgDataCount());
	}

	pSmvMngr->IsAT02D_Invalid();
}

#endif
BOOL iec_GenDeviceModel(CIecCfgDevice *pIecCfgDevice, CDvmLogicDevice *pDvmLogicDevice, BOOL bUseHarm)
{
#ifdef _USE_IN_AT02D_MODE_
	CAT02D_Tool oTool;
	return oTool.GenDeviceModel(pIecCfgDevice, pDvmLogicDevice, bUseHarm,FALSE);
#endif

	return TRUE;
}

BOOL iec_GenDeviceModel(CIecCfgDatasMngr *pCfgDatasMngr, CDvmLogicDevice *pDvmLogicDevice, BOOL bUseHarm)
{
#ifdef _USE_IN_AT02D_MODE_
	CAT02D_Tool oTool;
	return oTool.GenDeviceModel(pCfgDatasMngr, pDvmLogicDevice, bUseHarm,FALSE);
#endif

	return TRUE;
}

BOOL iec_GenDeviceModel_BySmvInGin(CIecCfgDatasMngr *pCfgDatasMngr, CDvmLogicDevice *pDvmLogicDevice, BOOL bUseHarm,BOOL bhasMUTestParas)
{
#ifdef _USE_IN_AT02D_MODE_
	CAT02D_Tool oTool;
	return oTool.GenDeviceModel_BySmvInGin(pCfgDatasMngr, pDvmLogicDevice, bUseHarm,bhasMUTestParas);
#endif

	return TRUE;
}
