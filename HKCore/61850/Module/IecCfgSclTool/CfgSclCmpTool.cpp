#include "StdAfx.h"
#include "CfgSclCmpTool.h"

CCfgSclCmpTool::CCfgSclCmpTool(void)
{
}

CCfgSclCmpTool::~CCfgSclCmpTool(void)
{
}

BOOL CCfgSclCmpTool::RegisterCmpData2(long nType, DWORD dwItrAddr)
{
	BOOL bCanCmp = TRUE;

	switch (nType)
	{
	case SCLTYPE_ID_SMVIN:
		RegisterSclData((SMVINPtr)dwItrAddr);
		break;
	case SCLTYPE_ID_SMVOUT:
		RegisterSclData((SMVOUTPtr)dwItrAddr);
		break;
	case SCLTYPE_ID_GIN:
		RegisterSclData((GOOSEINPtr)dwItrAddr);
		break;
	case SCLTYPE_ID_GOUT:
		RegisterSclData((GOOSEOUTPtr)dwItrAddr);
		break;
	default:
		bCanCmp = FALSE;
		break;
	}

	if (!bCanCmp)
	{
		return bCanCmp;
	}

	return bCanCmp;
}

void CCfgSclCmpTool::RegisterSclData(const SMVINPtr& smviptPtr)
{
	//本身数据
	CCfgSclCmpParaObjects *pParas = m_oCmpData2.GetDataParas();

// 	pCfgData->m_dwAppID = ST_StringToHex(smviptPtr->strAppID);
// 	pCfgData->m_strDestAddress = smviptPtr->strMac;

	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, smviptPtr->strAppID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, smviptPtr->strMac);
	//pParas->RegisterPara(CFGSCL_CMP_ID_IED, smviptPtr->strCtrlIED);
	//pParas->RegisterPara(_T("AppID"), smviptPtr->strOutputIEDName);
	//pParas->RegisterPara(_T("AppID"), smviptPtr->strOutputIEDDesc);
	pParas->RegisterPara(CFGSCL_CMP_ID_SVID, smviptPtr->strsmvID);

	//通道数据
	PINPUTCHN smviptchnitr;
	//smviptchnitrB = smviptPtr->list_smvinputchn.begin();
	//smviptchnitrE = smviptPtr->list_smvinputchn.end();
	TPOS pos = smviptPtr->GetHeadPosition();

	while (pos != NULL)//for (smviptchnitr = smviptchnitrB; smviptchnitr != smviptchnitrE; smviptchnitr++)
	{
		smviptchnitr = (PINPUTCHN)smviptPtr->GetNext(pos);
// 		pCh->m_strName = (*smviptchnitr)->strExtSigDes;

		pParas = m_oCmpData2.CreateNewChParaObjects();
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->strIntAddress);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->strIntSigDes);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->nExtSigIndex);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->strExtSigAddress);
		pParas->RegisterPara(CFGSCL_CMP_ID_Name, smviptchnitr->strExtSigDes);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->prefix);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->intAddr);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->doName);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->lnInst);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->iedName);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->daName);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->ldInst);
		//pParas->RegisterPara(_T("AppID"), (*smviptchnitr)->extrefPtr->lnClass);
	}
}

void CCfgSclCmpTool::RegisterSclData(const SMVOUTPtr& smvoptPtr)
{
// 	pCfgData->m_dwAppID = ST_StringToHex(smvoptPtr->strsmvID);
// 	pCfgData->m_strDestAddress = smvoptPtr->scgsData.address.MacAddress;
// 	pCfgData->m_dwVersion = CString_To_long(smvoptPtr->strVersion);
// 	pCfgData->m_dwVID = CString_To_long(smvoptPtr->scgsData.address.VLanID);
// 	pCfgData->m_nPriority = CString_To_long(smvoptPtr->scgsData.address.VLanpriority);
	CCfgSclCmpParaObjects *pParas = m_oCmpData2.GetDataParas();

	pParas->RegisterPara(CFGSCL_CMP_ID_SVID, smvoptPtr->strsmvID);
	pParas->RegisterPara(CFGSCL_CMP_ID_Version, smvoptPtr->strVersion);
	//pParas->RegisterPara(_T("AppID"), smvoptPtr->scgsData.cbName);
	//pParas->RegisterPara(_T("AppID"), smvoptPtr->scgsData.ldInst);
	//pParas->RegisterPara(_T("AppID"), smvoptPtr->scgsData.strAPName);
	//pParas->RegisterPara(CFGSCL_CMP_ID_TDelay, smvoptPtr->scgsData.MinTime);
	//pParas->RegisterPara(CFGSCL_CMP_ID_TDelay2, smvoptPtr->scgsData.MaxTime);
	pParas->RegisterPara(CFGSCL_CMP_ID_VID, smvoptPtr->scgsData.address.VLanID,CFGSCL_PARA_TYPE_HEX,  2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Priority, smvoptPtr->scgsData.address.VLanpriority);
	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, smvoptPtr->scgsData.address.MacAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, smvoptPtr->scgsData.address.AppID);

	int nSize = smvoptPtr->GetCount();
	std::list<CString>::iterator lstr,lstrE;
	lstr = smvoptPtr->chnAddr.begin();
	lstrE = smvoptPtr->chnAddr.end();;

	SMVOUTPUTCHNPtr smvoptchnPtr;
	for (; lstr != lstrE; lstr++)
	{
		pParas = m_oCmpData2.CreateNewChParaObjects();
		smvoptchnPtr = smvoptPtr->FindByAddress((*lstr));
		//pParas->RegisterPara(_T("AppID"), smvoptchnPtr->strLNDes);
		pParas->RegisterPara(CFGSCL_CMP_ID_Name, smvoptchnPtr->strDOIDes);
		pParas->RegisterPara(CFGSCL_CMP_ID_AddrInternal, smvoptchnPtr->strAddress);
	}
}

void CCfgSclCmpTool::RegisterSclData(const GOOSEINPtr& giptPtr)
{
// 	pCfgData->m_strDestAddress = giptPtr->strMac;
// 	pCfgData->m_dwAppID = ST_StringToHex(giptPtr->strAppID);
// 	pCfgData->m_strDataSetDesc = giptPtr->strDes;
// 	pCfgData->m_strgocbRef = giptPtr->strgocbRef;
// 	pCfgData->m_strDataSet = giptPtr->strDataSet;
// 	pCfgData->m_strGooseId = giptPtr->strgoID;
// 	pCfgData->m_strgocbIED = giptPtr->strOutputIEDName;
	//gseinputptr->strOutputIEDDesc;
	CCfgSclCmpParaObjects *pParas = m_oCmpData2.GetDataParas();

	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, giptPtr->strMac);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, giptPtr->strAppID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSetDesc, giptPtr->strDes);
	pParas->RegisterPara(CFGSCL_CMP_ID_gocbRef, giptPtr->strgocbRef);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, giptPtr->strDataSet);
	pParas->RegisterPara(CFGSCL_CMP_ID_goID, giptPtr->strgoID);
//	pParas->RegisterPara(CFGSCL_CMP_ID_gocbIED, giptPtr->strOutputIEDName);
	//pParas->RegisterPara(_T("AppID"), giptPtr->strOutputIEDDesc);

	PINPUTCHN giptchnitr = NULL;
	//giptchnitrB = giptPtr->list_gseinputchn.begin();
	//giptchnitrE = giptPtr->list_gseinputchn.end();
	TPOS pos = giptPtr->GetHeadPosition();

	while (pos != NULL)//for (giptchnitr = giptchnitrB; giptchnitr != giptchnitrE; giptchnitr++)
	{
		giptchnitr = (PINPUTCHN)giptPtr->GetNext(pos);
		//pCh->m_strID   = (*giptchnitr)->strExtSigDes;

		pParas = m_oCmpData2.CreateNewChParaObjects();
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->strIntAddress);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->strIntSigDes);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->nExtSigIndex);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->strExtSigAddress);
		//pParas->RegisterPara(CFGSCL_CMP_ID_AppChID, (*giptchnitr)->strExtSigDes);
		//pParas->RegisterPara(CFGSCL_CMP_ID_Name, (*giptchnitr)->strExtSigDes);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->extrefPtr->prefix);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->extrefPtr->intAddr);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->extrefPtr->doName);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->extrefPtr->lnInst);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->extrefPtr->iedName);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->extrefPtr->daName);
		//pParas->RegisterPara(_T("AppID"), (*giptchnitr)->extrefPtr->ldInst);
		pParas->RegisterPara(CFGSCL_CMP_ID_DataType, giptchnitr->extrefPtr.lnClass);
	}
}

void CCfgSclCmpTool::RegisterSclData(const GOOSEOUTPtr& goptPtr)
{

// 	pCfgData->m_strDestAddress = goptPtr->scgsData.address.MacAddress;
// 	pCfgData->m_dwAppID = ST_StringToHex(goptPtr->scgsData.address.AppID);
// 	pCfgData->m_strDataSetDesc = goptPtr->strDes;
// 	pCfgData->m_strgocbRef = goptPtr->strgocbRef;
// 	pCfgData->m_strDataSet = goptPtr->strDataset;
// 	pCfgData->m_strGooseId = goptPtr->strgoID;
// 	//pCfgData->m_strgocbIED = goptPtr->strOutputIEDName;
// 	pCfgData->m_dwVersion = CString_To_long(goptPtr->strVersion);
	CCfgSclCmpParaObjects *pParas = m_oCmpData2.GetDataParas();
	pParas->RegisterPara(CFGSCL_CMP_ID_gocbRef, goptPtr->strgocbRef);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, goptPtr->strDataset);
	pParas->RegisterPara(CFGSCL_CMP_ID_goID, goptPtr->strgoID);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSetDesc, goptPtr->strDes);
	pParas->RegisterPara(CFGSCL_CMP_ID_Version, goptPtr->strVersion);
	//pParas->RegisterPara(_T("AppID"), goptPtr->strAPName);
	//pParas->RegisterPara(_T("AppID"), goptPtr->scgsData.cbName);
	//pParas->RegisterPara(_T("AppID"), goptPtr->scgsData.ldInst);
	//pParas->RegisterPara(_T("AppID"), goptPtr->scgsData.strAPName);
	pParas->RegisterPara(CFGSCL_CMP_ID_T1, goptPtr->scgsData.MinTime);
	pParas->RegisterPara(CFGSCL_CMP_ID_T0, goptPtr->scgsData.MaxTime);
	pParas->RegisterPara(CFGSCL_CMP_ID_VID, goptPtr->scgsData.address.VLanID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Priority, goptPtr->scgsData.address.VLanpriority);
	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, goptPtr->scgsData.address.MacAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, goptPtr->scgsData.address.AppID, CFGSCL_PARA_TYPE_HEX, 2);

	CONTAINER_LIST_TYPE_ITERATOR(GOOSEOUTPUTCHN) giptchnitr,giptchnitrB,giptchnitrE;
	std::list<CString>::iterator lstr,lstrE;
	lstr = goptPtr->chnAddr.begin();
	lstrE = goptPtr->chnAddr.end();
	GOOSEOUTPUTCHNPtr goptchnPtr;

	for (; lstr != lstrE; lstr++)
	{
		goptchnPtr = goptPtr->FindByAddress((*lstr));
// 		pCh->m_strID   = goptchnPtr->strLNDes;
// 		pCh->m_strName = pCh->m_strID;
// 		pCh->SetDataTypeByName(goptchnPtr->strType);
// 		nIndex++;
		pParas = m_oCmpData2.CreateNewChParaObjects();

		pParas->RegisterPara(CFGSCL_CMP_ID_Name, goptchnPtr->strLNDes);
		//pParas->RegisterPara(_T("AppID"), goptchnPtr->strDOIDes);
		//pParas->RegisterPara(_T("AppID"), goptchnPtr->strDAIDes);
		pParas->RegisterPara(CFGSCL_CMP_ID_DataType, goptchnPtr->strType);
		//pParas->RegisterPara(_T("AppID"), goptchnPtr->strAddress);
		//pParas->RegisterPara(_T("AppID"), goptchnPtr->strValue);
	}
}

