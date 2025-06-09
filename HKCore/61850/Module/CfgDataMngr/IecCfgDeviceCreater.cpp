#include "stdafx.h"
#include "IecCfgDeviceCreater.h"
// #ifdef IecCfg_With_SCL
// #include "../../Iec61850Config/Iec61850Config.h"
// #endif

CIecCfgDeviceCreater::CIecCfgDeviceCreater()
{
	m_pSrcIecfg = NULL;
	m_pNewIecfg = NULL;
	m_pSclToIecCfgTool = NULL;
// 	m_pSmvins = NULL;
// 	m_pGsins = NULL;
// 	m_pGsouts = NULL;
	m_pCurrSelSclIed = NULL;
}

CIecCfgDeviceCreater::~CIecCfgDeviceCreater()
{

}
void CIecCfgDeviceCreater::InitCreate(CIecCfgDevice *pSrcIecfg, CIecCfgDevice *pNewIecfg, CSclToIecCfgTool *pSclToIecCfgTool,CSclIed *pCurrSelSclIed)
{
	m_pSrcIecfg = pSrcIecfg;
	m_pNewIecfg = pNewIecfg;
	m_pSclToIecCfgTool = pSclToIecCfgTool;
// #ifdef IecCfg_With_SCL
// 	m_pSmvins = theApp.m_pCurrSelSclIed->GetSmvIns();
// 	m_pGsins = theApp.m_pCurrSelSclIed->GetGsIns();
// 	m_pGsouts = theApp.m_pCurrSelSclIed->GetGsOuts();
// #endif
}

CIecCfgDatasMngr* CIecCfgDeviceCreater::CreateCIecCfgDatasMngr(CIecCfgDatasMngr *pSrc )
{
	CIecCfgDatasSMV  *pIecCfgDatasSrc = pSrc->GetSmvMngr();
	CIecCfgGinDatas *pIecCfgGinDatas = pSrc->GetGinMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = pSrc->GetGoutMngr();
	
 	CIecCfgDatasMngr *pIecCfgDatasMngr = new CIecCfgDatasMngr();
 	CreateCIecCfgDatasMngr_CfgSmvDatas(pIecCfgDatasSrc ,pIecCfgDatasMngr);
	CreateCIecCfgDatasMngr_CfgGinDatas(pIecCfgGinDatas ,pIecCfgDatasMngr);
	CreateCIecCfgDatasMngr_CfgGoutDatas(pIecCfgGoutDatas ,pIecCfgDatasMngr);

	if (m_pNewIecfg->GetHead() == NULL)
	{
		m_pNewIecfg->AddHead(pIecCfgDatasMngr);
		ASSERT(m_pCurrSelSclIed);
		m_pNewIecfg->SetSclIed(m_pCurrSelSclIed);
// #ifdef IecCfg_With_SCL
// 		m_pNewIecfg->SetSclIed(theApp.m_pCurrSelSclIed);
// #endif
	}
	else
	{
		m_pNewIecfg->AddTail(pIecCfgDatasMngr);
	}

// 	CString StrJudgment;
// 	StrJudgment = pSrc->m_strName;
// 	StrJudgment = StrJudgment.Right(9);

	pIecCfgDatasMngr->m_strName = pSrc->m_strName;
	pIecCfgDatasMngr->m_strID = pSrc->m_strID;

// 	if (StrJudgment == _T("_智能生成"))
// 	{
// 		pIecCfgDatasMngr->m_strName = pSrc->m_strName;
// 		pIecCfgDatasMngr->m_strID = pSrc->m_strID;
// 	} 
// 	else
// 	{
// 		pIecCfgDatasMngr->m_strName = pSrc->m_strName + _T("_智能生成");
// 		pIecCfgDatasMngr->m_strID = pSrc->m_strID + _T("_智能生成");
// 	}
	return pIecCfgDatasMngr;
}
void CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_CfgSmvDatas(CIecCfgDatasSMV*pSrc ,CIecCfgDatasMngr *pNew)
{
	long nIndex = pSrc->GetCount();
	long strIndex = 1;
	CIecCfg92Data *pIecCfg92DataSrc = NULL;

	while (strIndex<nIndex)
	{
		pIecCfg92DataSrc = (CIecCfg92Data*)pSrc->GetAtIndex(strIndex-1);
		strIndex++;

		if (pIecCfg92DataSrc->GetClassID() != CFGCLASSID_CIECCFG92DATA)
		{
			continue;
		}

		CreateCIecCfgDatasMngr_CfgSmvData(pIecCfg92DataSrc ,pNew);
	}

}
void CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_CfgSmvData(CIecCfg92Data*pSrc , CIecCfgDatasMngr *pNew)
{
	CIecCfg92Chs *pIecCfgChsSrc = (CIecCfg92Chs *)pSrc->m_pCfgChs;
	CIecCfg92Ch *pIecCfg92ChSrc = NULL;
	CSclCtrlSmvIn *pSclSmvIn = NULL;
	CSclChSmvIn * pSclInSmvIn =NULL;
	POS posCh = pIecCfgChsSrc->GetHeadPosition();
	POS posSclCtrl = NULL;
	POS posCtrlCh = NULL;
	CIecCfg92Data *pIecCfg92DataNew = NULL;
	CIecCfg92Ch *pIecCfg92ChNew = NULL;
	CString strInPath;
	BOOL bIndex = TRUE;
	CIecCfgDatasSMV  *pIecCfgDatasNew = pNew->GetSmvMngr();
	ASSERT(m_pCurrSelSclIed);
	CSclCtrlsSmvIn  *pSmvins = m_pCurrSelSclIed->GetSmvIns();

	while(posCh != NULL)
	{
		pIecCfg92ChSrc = (CIecCfg92Ch*)pIecCfgChsSrc->GetNext(posCh);
		if (pIecCfg92ChSrc->m_nIndexExternal != -1)
		{
			bIndex = TRUE;
			strInPath = pIecCfg92ChSrc->m_strAddrExternal;
			pIecCfg92ChNew = CreateCIecCfgDatasMngr_SearchPath(strInPath ,pIecCfgDatasNew);
			if (pIecCfg92ChNew != NULL)
			{
				pIecCfg92ChNew->m_strAppChID = pIecCfg92ChSrc->m_strAppChID;
				bIndex = FALSE;
			}
			posSclCtrl = pSmvins->GetHeadPosition();
			while ((posSclCtrl != NULL)&&(bIndex == TRUE))
			{
				pSclSmvIn = (CSclCtrlSmvIn *)pSmvins->GetNext(posSclCtrl);
				posCtrlCh = pSclSmvIn->GetHeadPosition();
				while ((posCtrlCh != NULL)&&(bIndex == TRUE))
				{
					pSclInSmvIn = (CSclChSmvIn *)pSmvins->GetNext(posCtrlCh);
					if (pSclInSmvIn->inPath == strInPath)
					{
						pIecCfg92DataNew = (CIecCfg92Data *)m_pSclToIecCfgTool->AddSMVInput_92(pNew ,pSclSmvIn);
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能配置生成SMV控制块【%s】【%s】"), pIecCfg92DataNew->m_strIedRefDesc ,pIecCfg92DataNew->m_strSVID);
						pIecCfg92DataNew->m_nFiberIndex = pSrc->m_nFiberIndex;
						pIecCfg92DataNew->m_nFiber2Index = pSrc->m_nFiber2Index;
						pIecCfg92ChNew = CreateCIecCfgDatasMngr_SearchPath(strInPath ,pIecCfgDatasNew);
						if (pIecCfg92ChNew != NULL)
						{
							pIecCfg92ChNew->m_strAppChID = pIecCfg92ChSrc->m_strAppChID;
							bIndex = FALSE;
						}
						bIndex = FALSE;
					}
				}
			}
			if (bIndex == TRUE)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("在新SCD文件的中未能找到本保护SMV中内部路径为【%s】的通道"), strInPath);
			}
		}
	}

}
CIecCfg92Ch* CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_SearchPath(CString path , CIecCfgDatasSMV *pIecCfgDatasNew)
{
	CIecCfg92Data *pIecCfg92DataNew = NULL;
	CIecCfg92Ch *pIecCfg92ChNew = NULL;
	POS posDataNew = NULL;
	POS posChNew = NULL;
	posDataNew= pIecCfgDatasNew->GetHeadPosition();
	while (posDataNew!= NULL)
	{
		pIecCfg92DataNew = (CIecCfg92Data *)pIecCfgDatasNew->GetNext(posDataNew);
		posChNew = pIecCfg92DataNew->m_pCfgChs->GetHeadPosition();
		while (posChNew != NULL)
		{
			pIecCfg92ChNew = (CIecCfg92Ch *)pIecCfg92DataNew->m_pCfgChs->GetNext(posChNew);
			if (pIecCfg92ChNew->m_strAddrExternal == path)
			{
				return pIecCfg92ChNew;
			}
		}
	}
	return NULL;
}
void CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_CfgGoutDatas(CIecCfgGoutDatas *pSrc ,CIecCfgDatasMngr *pNew)
{
	long nIndex = pSrc->GetCount();
	long strIndex = 0;
	CIecCfgGoutData *pIecCfgGoutDataSrc = NULL;
	while (strIndex<nIndex)
	{
		pIecCfgGoutDataSrc = (CIecCfgGoutData*)pSrc->GetAtIndex(strIndex);
		CreateCIecCfgDatasMngr_CfgGoutData(pIecCfgGoutDataSrc ,pNew);
		strIndex++;
	}

}
void CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_CfgGoutData(CIecCfgGoutData *pSrc ,CIecCfgDatasMngr *pNew)
{
	CIecCfgGoutChs *pIecCfgChsSrc = (CIecCfgGoutChs *)pSrc->m_pCfgChs;
	CIecCfgGoutCh *pIecCfgGoutChSrc = NULL;
	CSclCtrlGsIn *pSclGsIn = NULL;
	CSclChGsIn * pSclChGsIn =NULL;
	POS posCh = pIecCfgChsSrc->GetHeadPosition();
	POS posSclCtrl = NULL;
	POS posCtrlCh = NULL;
	CIecCfgGoutData *pIecCfgGoutDataNew = NULL;
	CIecCfgGoutCh *pIecCfgGoutChNew = NULL;
	CString strInPath;
	BOOL bIndex = TRUE;
	CIecCfgGoutDatas  *pIecCfgDatasNew = pNew->GetGoutMngr();
	ASSERT(m_pCurrSelSclIed);
	CSclCtrlsGsIn *pGsins = m_pCurrSelSclIed->GetGsIns();

	while(posCh != NULL)
	{
		pIecCfgGoutChSrc = (CIecCfgGoutCh*)pIecCfgChsSrc->GetNext(posCh);
		if (pIecCfgGoutChSrc->m_nIndexExternal != -1)
		{
			bIndex = TRUE;
			strInPath = pIecCfgGoutChSrc->m_strAddrExternal;
			pIecCfgGoutChNew = CreateCIecCfgDatasMngr_SearchPath(strInPath ,pIecCfgDatasNew);
			if (pIecCfgGoutChNew != NULL)
			{
				pIecCfgGoutChNew->m_strAppChID = pIecCfgGoutChSrc->m_strAppChID;
				bIndex = FALSE;
			}
			posSclCtrl = pGsins->GetHeadPosition();
			while ((posSclCtrl != NULL)&&(bIndex == TRUE))
			{
				pSclGsIn = (CSclCtrlGsIn *)pGsins->GetNext(posSclCtrl);
				posCtrlCh = pSclGsIn->GetHeadPosition();
				while ((posCtrlCh != NULL)&&(bIndex == TRUE))
				{
					pSclChGsIn = (CSclChGsIn *)pGsins->GetNext(posCtrlCh);
					if (pSclChGsIn->inPath == strInPath)
					{
						pIecCfgGoutDataNew = (CIecCfgGoutData *)m_pSclToIecCfgTool->AddCfgGout_By_SclGin(pNew ,pSclGsIn);
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能配置生成GOOSE发布控制块【%s】【%s】"), pIecCfgGoutDataNew->m_strIedRefDesc , pIecCfgGoutDataNew->m_strgocbRef);
						pIecCfgGoutDataNew->m_nFiberIndex = pSrc->m_nFiberIndex;
						pIecCfgGoutDataNew->m_nFiber2Index = pSrc->m_nFiber2Index;
						pIecCfgGoutChNew = CreateCIecCfgDatasMngr_SearchPath(strInPath ,pIecCfgDatasNew);
						if (pIecCfgGoutChNew != NULL)
						{
							pIecCfgGoutChNew->m_strAppChID = pIecCfgGoutChSrc->m_strAppChID;
							bIndex = FALSE;
						}
						bIndex = FALSE;
					}
				}
			}
			if (bIndex == TRUE)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("在新SCD文件的中未能找到本保护GsIn中内部路径为【%s】的通道"), strInPath);
			}
		}
	}
}
CIecCfgGoutCh* CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_SearchPath(CString path , CIecCfgGoutDatas  *pIecCfgDatasNew)
{
	CIecCfgGoutData *pIecCfgGoutDataNew = NULL;
	CIecCfgGoutCh *pIecCfgGoutChNew = NULL;
	POS posDataNew = NULL;
	POS posChNew = NULL;
	posDataNew= pIecCfgDatasNew->GetHeadPosition();
	while (posDataNew!= NULL)
	{
		pIecCfgGoutDataNew = (CIecCfgGoutData *)pIecCfgDatasNew->GetNext(posDataNew);
		posChNew = pIecCfgGoutDataNew->m_pCfgChs->GetHeadPosition();
		while (posChNew != NULL)
		{
			pIecCfgGoutChNew = (CIecCfgGoutCh *)pIecCfgGoutDataNew->m_pCfgChs->GetNext(posChNew);
			if (pIecCfgGoutChNew->m_strAddrExternal == path)
			{
				return pIecCfgGoutChNew;
			}
		}
	}
	return NULL;
}

void CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_CfgGinDatas(CIecCfgGinDatas *pSrc  ,CIecCfgDatasMngr *pNew)
{
	long nIndex = pSrc->GetCount();
	long strIndex = 0;
	CIecCfgGinData *pIecCfgGinDataSrc = NULL;
	while (strIndex<nIndex)
	{
		pIecCfgGinDataSrc = (CIecCfgGinData*)pSrc->GetAtIndex(strIndex);
		CreateCIecCfgDatasMngr_CfgGinData(pIecCfgGinDataSrc ,pNew);
		strIndex++;
	}
}
void CIecCfgDeviceCreater::CreateCIecCfgDatasMngr_CfgGinData(CIecCfgGinData *pSrc  ,CIecCfgDatasMngr *pNew)
{
	CIecCfgGinChs *pIecCfgChsSrc = (CIecCfgGinChs *)pSrc->m_pCfgChs;
	CIecCfgGinChs *pIecCfgChsNew = NULL;
	CIecCfgGinCh *pIecCfgGinChSrc = NULL;
	CIecCfgGinCh *pIecCfgGinChNew = NULL;
	CSclCtrlGsOut *pSclGsOut = NULL;
	BOOL bIndex = TRUE;
	POS posChSrc = pIecCfgChsSrc->GetHeadPosition();
	POS posChNew = NULL;
	POS posSclCtrl = NULL;
	CIecCfgGinData *pIecCfgGinDataNew = NULL;
	CString strInPath , strPathNew;
	ASSERT(m_pCurrSelSclIed);
	CSclCtrlsGsOut *pGsouts = m_pCurrSelSclIed->GetGsOuts();
	long nIndex = pGsouts->GetCount();
	CIecCfgGinDatas  *pIecCfgDatasNew = pNew->GetGinMngr();
	strInPath = pSrc->m_strGooseId;
	long nPos = strInPath.ReverseFind('/');
	strInPath = strInPath.Right(strInPath.GetLength() - nPos);
	if (nIndex<= 1)
	{
		pSclGsOut = (CSclCtrlGsOut *)pGsouts->GetHead();
		strPathNew = pSclGsOut->m_strGooseId;
		nPos = strPathNew.ReverseFind('/');
		strPathNew = strPathNew.Right(strPathNew.GetLength() - nPos);
		if (strPathNew == strInPath)
		{
			pIecCfgGinDataNew = (CIecCfgGinData *)m_pSclToIecCfgTool->AddCfgGin_By_SclGout(pNew ,pSclGsOut);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能配置生成GOOSE订阅控制块【%s】【%s】"), pIecCfgGinDataNew->m_strIedRefDesc, pIecCfgGinDataNew->m_strgocbRef);
			bIndex = FALSE;
			pIecCfgGinDataNew->m_nFiberIndex = pSrc->m_nFiberIndex;
			pIecCfgGinDataNew->m_nFiber2Index = pSrc->m_nFiber2Index;
			pIecCfgChsNew = (CIecCfgGinChs *)pIecCfgGinDataNew->m_pCfgChs;
			posChSrc = pIecCfgChsSrc->GetHeadPosition();
			posChNew = pIecCfgChsNew->GetHeadPosition();
			while((posChNew != NULL)&&(posChSrc != NULL))
			{
				pIecCfgGinChSrc = (CIecCfgGinCh *)pIecCfgChsSrc->GetNext(posChSrc);
				pIecCfgGinChNew = (CIecCfgGinCh *)pIecCfgChsNew->GetNext(posChNew);
				pIecCfgGinChNew->m_strAppChID = pIecCfgGinChSrc->m_strAppChID;

			}
		}
	} 
	else
	{
		posSclCtrl = pGsouts->GetHeadPosition();
		while (posSclCtrl != NULL)
		{
			pSclGsOut = (CSclCtrlGsOut *)pGsouts->GetNext(posSclCtrl);
			strPathNew = pSclGsOut->m_strGooseId;
			nPos = strPathNew.ReverseFind('/');
			strPathNew = strPathNew.Right(strPathNew.GetLength() - nPos);
			if (strPathNew == strInPath)
			{
				pIecCfgGinDataNew = (CIecCfgGinData *)m_pSclToIecCfgTool->AddCfgGin_By_SclGout(pNew ,pSclGsOut);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能配置生成GOOSE订阅控制块【%s】【%s】"), pIecCfgGinDataNew->m_strIedRefDesc,pIecCfgGinDataNew->m_strgocbRef);
				bIndex = FALSE;
				pIecCfgGinDataNew->m_nFiberIndex = pSrc->m_nFiberIndex;
				pIecCfgGinDataNew->m_nFiber2Index = pSrc->m_nFiber2Index;
				pIecCfgChsNew = (CIecCfgGinChs *)pIecCfgGinDataNew->m_pCfgChs;
				posChSrc = pIecCfgChsSrc->GetHeadPosition();
				posChNew = pIecCfgChsNew->GetHeadPosition();
				while((posChNew != NULL)&&(posChSrc != NULL))
				{
					pIecCfgGinChSrc = (CIecCfgGinCh *)pIecCfgChsSrc->GetNext(posChSrc);
					pIecCfgGinChNew = (CIecCfgGinCh *)pIecCfgChsNew->GetNext(posChNew);
					pIecCfgGinChNew->m_strAppChID = pIecCfgGinChSrc->m_strAppChID;

				}
			}
		}
	}
	if (bIndex == TRUE)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("在新SCD文件的中未能找到本保护【%s】的GOOSE输出数据集"), strInPath);
	}
}