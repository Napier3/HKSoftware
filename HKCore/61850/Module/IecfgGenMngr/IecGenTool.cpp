#include "StdAfx.h"
#include "IecGenTool.h"

CIecGenTool::CIecGenTool(void)
{
	m_pCurDeivceRule = NULL;
}

CIecGenTool::~CIecGenTool(void)
{
}

BOOL CIecGenTool::Generate(CIecCfgDevice *pIecfgDevice,const CString &strIecfgName)
{
#ifdef IECFG_USE_KEYDB
	OpenKeyDbFile();
#endif
	CExBaseObject *pCurrObj = NULL;
	CIecDeviceRule *pCurDeivceRule = NULL;
	m_pCurDeivceRule = NULL;
	POS pos = g_oIecfgGenMngr.GetHeadPosition();

	while(pos)
	{
		pCurrObj = g_oIecfgGenMngr.GetNext(pos);

		if (pCurrObj->GetClassID() != GENRATECLASSID_CIECDEVICERULE)
		{
			continue;
		}

		pCurDeivceRule = (CIecDeviceRule *)pCurrObj;

		if (strIecfgName == pCurDeivceRule->m_strIecfg)//zhouhj 20220330 修改为根据iecfg文件名查找的方式
		{
			m_pCurDeivceRule = pCurDeivceRule;
			return GenerateIecfgDevice(pCurDeivceRule,pIecfgDevice);
		}

	}

	return FALSE;
}

// BOOL CIecGenTool::GetCurDeivceGinChFileName(CString &strGinChFileName)
// {
// 	if (m_pCurDeivceRule == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备IEC映射对象为空."));
// 		return FALSE;
// 	}
// 
// 	strGinChFileName = m_pCurDeivceRule->m_strGinChFileName;
// 	return TRUE;
// }

BOOL CIecGenTool::GenerateIecfgDevice(CIecDeviceRule* pCurDeivceRule,CIecCfgDevice *pIecfgDevice)
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->FindByClassID(CFGCLASSID_CIECCFGDATASMNGR);

	if (pIecCfgDatasMngr == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前CIecCfgDevice对象中,缺少缺省CIecCfgDatasMngr对象."));
		return FALSE;
	}

	if (pCurDeivceRule->GetCount() <= 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备(name=%s;ID=%s;)配置生成规则对象为空."),pCurDeivceRule->m_strName,pCurDeivceRule->m_strID);
		return FALSE;
	}

	//创建临时对象,用于后期clone结果为初始状态的CIecCfgDatasMngr
	CIecCfgDatasMngr *pTmpIecfgDataMngr = (CIecCfgDatasMngr*)pIecCfgDatasMngr->Clone();

	POS pos = pCurDeivceRule->GetHeadPosition();
	CIecGenCfgDataMngrRule *pIecGenCfgDataMngrRule = (CIecGenCfgDataMngrRule*)pCurDeivceRule->GetNext(pos);

	//第一个生成规则，生成第一个配置
	if (! GenarateIecCfgDatasMngr(pIecGenCfgDataMngrRule,pIecCfgDatasMngr))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备(name=%s;ID=%s;)生成第一个子配置(name=%s;ID=%s;)失败."),pCurDeivceRule->m_strName,pCurDeivceRule->m_strID,pIecGenCfgDataMngrRule->m_strName,pIecGenCfgDataMngrRule->m_strID);
	}

	CIecCfgDatasMngr *pNew = NULL;

	//第二个至最后的其他规则
	while(pos)
	{
		pIecGenCfgDataMngrRule = (CIecGenCfgDataMngrRule*)pCurDeivceRule->GetNext(pos);

		pNew  = (CIecCfgDatasMngr*)pTmpIecfgDataMngr->Clone();
		pIecfgDevice->AddNewChild(pNew, TRUE);
		pIecfgDevice->InitSclRef(pNew);

		if (!GenarateIecCfgDatasMngr(pIecGenCfgDataMngrRule,pNew))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备(name=%s;ID=%s;)生成子配置(name=%s;ID=%s;)失败."),pCurDeivceRule->m_strName,pCurDeivceRule->m_strID,pIecGenCfgDataMngrRule->m_strName,pIecGenCfgDataMngrRule->m_strID);
		}
	}

	//	iecfg_SetModified(pNew, TRUE);
	delete pTmpIecfgDataMngr;
	return TRUE;
}

BOOL CIecGenTool::GenarateIecCfgDatasMngr(CIecGenCfgDataMngrRule *pIecGenCfgDataMngrRule,CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	ASSERT(pIecCfgDatasMngr);
	pIecCfgDatasMngr->m_strID = pIecGenCfgDataMngrRule->m_strID;
	pIecCfgDatasMngr->m_strName = pIecGenCfgDataMngrRule->m_strName;
	pIecCfgDatasMngr->m_strGinChMapFileName = pIecGenCfgDataMngrRule->m_strGinChFileName;

	CIecCfgDatasSMV *pSmvMngr = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas* pGoutMngr = pIecCfgDatasMngr->GetGoutMngr();
	CIecCfgGinDatas *pIecCfgGinDatas = pIecCfgDatasMngr->GetGinMngr();
	pSmvMngr->SetSelectState_AllCtrlBlock(0);
	pGoutMngr->SetSelectState_AllCtrlBlock(0);
	pIecCfgGinDatas->SetSelectState_AllCtrlBlock(0);

	CIecGenCfgDataMngrRule_SMV* pCfgDataMngrRule_SMV =  pIecGenCfgDataMngrRule->GetSmvRule();
	CIecGenCfgDataMngrRule_Gin* pCfgDataMngrRule_Gin =  pIecGenCfgDataMngrRule->GetGinRule();
	CIecGenCfgDataMngrRule_Gout* pCfgDataMngrRule_Gout =  pIecGenCfgDataMngrRule->GetGoutRule();
	CIecGenRule_CtrlBlock *pCurCtrlBlock = NULL;

	if (pCfgDataMngrRule_SMV)
	{
		GenarateIecCfgDatas(pCfgDataMngrRule_SMV,pSmvMngr);
//		pCfgDataMngrRule_SMV->GenarateIecCfgDatasSMV(pSmvMngr);
	}

	if (pCfgDataMngrRule_Gin)
	{
		pCurCtrlBlock = (CIecGenRule_CtrlBlock*)pCfgDataMngrRule_Gin->FindByClassID(GENRATECLASSID_CIECGENRULE_CTRLBLOCK);

		if (pCurCtrlBlock)
		{//根据控制块规则，配置光口
			pIecCfgGinDatas->SetAllFiberIndex(pCurCtrlBlock->m_nFiberIndex-1);
		}

		GenarateIecCfgDatas(pCfgDataMngrRule_Gin,pIecCfgGinDatas);
		pIecCfgGinDatas->InitAfterRead();
//		pCfgDataMngrRule_Gin->GenarateIecCfgGinDatas(pIecCfgGinDatas);
	}

	if (pCfgDataMngrRule_Gout)
	{
		pCurCtrlBlock = (CIecGenRule_CtrlBlock*)pCfgDataMngrRule_Gout->FindByClassID(GENRATECLASSID_CIECGENRULE_CTRLBLOCK);

		if (pCurCtrlBlock)
		{
			pGoutMngr->SetAllFiberIndex(pCurCtrlBlock->m_nFiberIndex-1);
		}

		GenarateIecCfgDatas(pCfgDataMngrRule_Gout,pGoutMngr);
//		pCfgDataMngrRule_Gout->GenarateIecCfgGoutDatas(pGoutMngr);
	}

	return TRUE;
}

#ifdef IECFG_USE_KEYDB
CIecCfgDataBase* CIecGenTool::GetIecCfgDataBase(CXMatchObject *pXMatchObject,long nMatchRatio)
{
	POS pos = pXMatchObject->m_listMacthObjectRatio.GetHeadPosition();
	CXMatchObjectRatio *pCurXMatchObjectRatio = NULL;
	CIecCfgDataChBase *pIecCfgDataChBase = NULL;

	while(pos)
	{
		pCurXMatchObjectRatio = (CXMatchObjectRatio *)pXMatchObject->m_listMacthObjectRatio.GetNext(pos);

		if (pCurXMatchObjectRatio->m_nMatchRatio>nMatchRatio)
		{
			ASSERT(pCurXMatchObjectRatio->m_pRefObject);
			pIecCfgDataChBase = (CIecCfgDataChBase *)pCurXMatchObjectRatio->m_pRefObject;
			return (CIecCfgDataBase* )pIecCfgDataChBase->GetAncestorIecCfgData();
		}
	}

	return NULL;
}

CXMatchObjectRatio* CIecGenTool::GetMaxRatio_XMatchObject(CExBaseList *pMacthObjectRatioList)
{
	POS pos = pMacthObjectRatioList->GetHeadPosition();
	CXMatchObjectRatio *pCurXMatchObjectRatio = NULL;
	CXMatchObjectRatio *pMax_XMatchObjectRatio = (CXMatchObjectRatio*)pMacthObjectRatioList->GetHead();

	while(pos)
	{
		pCurXMatchObjectRatio = (CXMatchObjectRatio *)pMacthObjectRatioList->GetNext(pos);

		if (pCurXMatchObjectRatio->m_nMatchRatio > pMax_XMatchObjectRatio->m_nMatchRatio)
		{
			pMax_XMatchObjectRatio = pCurXMatchObjectRatio;
		}
	}

	return pMax_XMatchObjectRatio;
}

BOOL CIecGenTool::SetChMaps(CIecGenRule_CtrlCh *pCurrCtrlCh,CExBaseList *pMacthObjectRatioList,CIecCfgDataBase *pIecCfgDataBase)
{
	CXMatchObjectRatio *pCurXMatchObjectRatio = NULL;
	CIecCfgDataChBase *pIecCfgDataChBase = NULL;

	if (pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
	{
		pCurXMatchObjectRatio = GetMaxRatio_XMatchObject(pMacthObjectRatioList);

		if (pCurXMatchObjectRatio == NULL)
		{
			return FALSE;
		}

		if (pCurXMatchObjectRatio->m_nMatchRatio>pCurrCtrlCh->m_nMatchRatio)
		{
			pIecCfgDataChBase = (CIecCfgDataChBase*)pCurXMatchObjectRatio->m_pRefObject;
			pIecCfgDataChBase->m_strAppChID = pCurrCtrlCh->m_strAppCh;
			pIecCfgDataBase->m_nUseFlag = 1;
			return TRUE;
		}
		else
			return FALSE;
	}

	POS pos = pMacthObjectRatioList->GetHeadPosition();

	while(pos)
	{
		pCurXMatchObjectRatio = (CXMatchObjectRatio *)pMacthObjectRatioList->GetNext(pos);

		if (pCurXMatchObjectRatio->m_nMatchRatio > pCurrCtrlCh->m_nMatchRatio)
		{
			ASSERT(pCurXMatchObjectRatio->m_pRefObject);
			pIecCfgDataChBase = (CIecCfgDataChBase*)pCurXMatchObjectRatio->m_pRefObject;
			pIecCfgDataChBase->m_strAppChID = pCurrCtrlCh->m_strAppCh;

			if (pIecCfgDataChBase->GetClassID() == CFGCLASSID_CIECCFG92CH)
			{
				((CIecCfg92Ch*)pIecCfgDataChBase)->m_strChType = pCurrCtrlCh->m_strAppCh;
			}

			pIecCfgDataBase->m_nUseFlag = 1;
		}
	}

	return TRUE;
}

BOOL CIecGenTool::SetChMaps(CIecGenRule_CtrlCh *pCurrCtrlCh,CExBaseList *pMacthObjectRatioList)
{
	CXMatchObjectRatio *pCurXMatchObjectRatio = (CXMatchObjectRatio*)pMacthObjectRatioList->GetHead();
	CIecCfgDataBase *pIecCfgDataBase = NULL;
	
	if (pCurXMatchObjectRatio == NULL)
	{
		return FALSE;
	}

	CIecCfgDataChBase *pIecCfgDataChBase =  (CIecCfgDataChBase*)pCurXMatchObjectRatio->m_pRefObject;


	if (pIecCfgDataChBase->GetClassID() == CFGCLASSID_CIECCFGGINCH)
	{
		pCurXMatchObjectRatio = GetMaxRatio_XMatchObject(pMacthObjectRatioList);

		if (pCurXMatchObjectRatio == NULL)
		{
			return FALSE;
		}

		if (pCurXMatchObjectRatio->m_nMatchRatio>pCurrCtrlCh->m_nMatchRatio)
		{
			pIecCfgDataChBase = (CIecCfgDataChBase*)pCurXMatchObjectRatio->m_pRefObject;
			pIecCfgDataChBase->m_strAppChID = pCurrCtrlCh->m_strAppCh;
			pIecCfgDataBase = (CIecCfgDataBase*)pIecCfgDataChBase->GetAncestorIecCfgData();

			if (pIecCfgDataBase != NULL)
			{
				pIecCfgDataBase->m_nUseFlag = 1;
			}

			return TRUE;
		}
		else
			return FALSE;
	}

	POS pos = pMacthObjectRatioList->GetHeadPosition();

	while(pos)
	{
		pCurXMatchObjectRatio = (CXMatchObjectRatio *)pMacthObjectRatioList->GetNext(pos);

		if (pCurXMatchObjectRatio->m_nMatchRatio > pCurrCtrlCh->m_nMatchRatio)
		{
			ASSERT(pCurXMatchObjectRatio->m_pRefObject);
			pIecCfgDataChBase = (CIecCfgDataChBase*)pCurXMatchObjectRatio->m_pRefObject;
			pIecCfgDataChBase->m_strAppChID = pCurrCtrlCh->m_strAppCh;

			if (pIecCfgDataChBase->GetClassID() == CFGCLASSID_CIECCFG92CH)
			{
				((CIecCfg92Ch*)pIecCfgDataChBase)->m_strChType = pCurrCtrlCh->m_strAppCh;
			}

			pIecCfgDataBase = (CIecCfgDataBase*)pIecCfgDataChBase->GetAncestorIecCfgData();

			if (pIecCfgDataBase != NULL)
			{
				pIecCfgDataBase->m_nUseFlag = 1;
			}
		}
	}

	return TRUE;
}

BOOL CIecGenTool::SetAllChMaps_KeyDB(CIecGenRule_CtrlBlock *pCurCtrlBlock,CIecCfgDataBase *pIecCfgDataBase)
{
	pCurCtrlBlock->InitMatchList(&m_oKeyDB);
	pIecCfgDataBase->InitMatchList(&m_oKeyDB);
	pCurCtrlBlock->m_pChMatchList->Match(pIecCfgDataBase->m_pMatchList, 80, NULL, TRUE);

	pIecCfgDataBase->m_nFiberIndex = pCurCtrlBlock->m_nFiberIndex-1;
	POS pos = pCurCtrlBlock->m_pChMatchList->GetHeadPosition();
	CXMatchObject *pXMatchObject = NULL;
	CIecGenRule_CtrlCh *pCurrCtrlCh = NULL;

	while(pos)
	{
		pXMatchObject = (CXMatchObject*)pCurCtrlBlock->m_pChMatchList->GetNext(pos);
		ASSERT(pXMatchObject->m_pRefObject);

		if (pXMatchObject->m_pRefObject->GetClassID() == GENRATECLASSID_CIECGENRULE_CTRLCH)
		{
			pCurrCtrlCh = (CIecGenRule_CtrlCh *)pXMatchObject->m_pRefObject;
			SetChMaps(pCurrCtrlCh,&pXMatchObject->m_listMacthObjectRatio,pIecCfgDataBase);
		}
	}
	return TRUE;
}
#endif

BOOL CIecGenTool::GenarateIecCfgDatas_KeyDB(CIecGenCfgDataMngrRule_Base *pGenCfgDataMngrRule_Base,CIecCfgDatasBase *pIecCfgDatasBase)
{
#ifdef IECFG_USE_KEYDB
	pGenCfgDataMngrRule_Base->InitMatchList(&m_oKeyDB);
	pIecCfgDatasBase->InitMatchList(&m_oKeyDB);
	pGenCfgDataMngrRule_Base->m_pCtrlMatchList->Match(pIecCfgDatasBase->m_pMatchList, 80, NULL, TRUE);

	CIecCfgDataBase *pIecCfgDataBase = NULL;
	CIecGenRule_CtrlBlock *pCurCtrlBlock = NULL;
	CXMatchObject *pXMatchObject = NULL;
	CIecGenRule_CtrlCh *pCurrCtrlCh = NULL;
	POS pos = pGenCfgDataMngrRule_Base->m_pCtrlMatchList->GetHeadPosition();

	while (pos != NULL)
	{
		pXMatchObject = (CXMatchObject*)pGenCfgDataMngrRule_Base->m_pCtrlMatchList->GetNext(pos);
		ASSERT(pXMatchObject->m_pRefObject);

		if ((pXMatchObject->m_pRefObject->GetClassID() == GENRATECLASSID_CIECGENRULE_CTRLBLOCK))
		{
			pCurCtrlBlock = (CIecGenRule_CtrlBlock *)pXMatchObject->m_pRefObject;
			pIecCfgDataBase = GetIecCfgDataBase(pXMatchObject,pCurCtrlBlock->m_nMatchRatio);// pXMatchObject->m_listMacthObjectRatio.GetHead();

			if (pIecCfgDataBase == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找控制块(%s)失败."),pXMatchObject->m_pRefObject->m_strID);
				continue;
			}

			SetAllChMaps_KeyDB(pCurCtrlBlock,pIecCfgDataBase);
		}
		else if ((pXMatchObject->m_pRefObject->GetClassID() == GENRATECLASSID_CIECGENRULE_CTRLCH))
		{
			pCurrCtrlCh = (CIecGenRule_CtrlCh *)pXMatchObject->m_pRefObject;
			SetChMaps(pCurrCtrlCh,&pXMatchObject->m_listMacthObjectRatio);
		}
	}

#endif

	return TRUE;
}

BOOL CIecGenTool::GenarateIecCfgDatas(CIecGenCfgDataMngrRule_Base *pGenCfgDataMngrRule_Base,CIecCfgDatasBase *pIecCfgDatasBase)
{
#ifdef IECFG_USE_KEYDB

	return GenarateIecCfgDatas_KeyDB(pGenCfgDataMngrRule_Base, pIecCfgDatasBase);

#else

	POS pos = pGenCfgDataMngrRule_Base->GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CIecGenRule_CtrlBlock *pCurCtrlBlock = NULL;
	CIecGenRule_CtrlCh *pCurrCtrlCh = NULL;
 
	while(pos)
	{
		pCurObj = pGenCfgDataMngrRule_Base->GetNext(pos);

		if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENRULE_CTRLBLOCK)
		{
			pCurCtrlBlock = (CIecGenRule_CtrlBlock *)pCurObj;
			GenerateIecCfgDatas(pCurCtrlBlock,pIecCfgDatasBase);
		}
		else if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENRULE_CTRLCH)
		{
			pCurrCtrlCh = (CIecGenRule_CtrlCh *)pCurObj;
			SetAllChMaps(pCurrCtrlCh,pIecCfgDatasBase);
		}
	}

	return TRUE;

#endif
}

BOOL CIecGenTool::GenerateIecCfgDatas(CIecGenRule_CtrlBlock *pCurCtrlBlock,CIecCfgDatasBase *pIecCfgDatasBase)
{
	CIecGenCfgKeys *pKeys = (CIecGenCfgKeys*)pCurCtrlBlock->FindByClassID(GENRATECLASSID_CIECGENCFGKEYS);

	if (pKeys == NULL)
	{
		if (pIecCfgDatasBase->GetClassID() == GENRATECLASSID_CIECGENCFGDATAMNGRRULE_SMV)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("iecfg-generate-mngr文件中,控制块(%s)缺少关键字映射."),pCurCtrlBlock->m_strID);
		}

		return FALSE;
	}

	CIecCfgDataBase *pIecCfgDataBase = (CIecCfgDataBase*)pKeys->FindIecCfgData(pIecCfgDatasBase);

	if (pIecCfgDataBase != NULL)
	{
		pIecCfgDataBase->m_nFiberIndex = pCurCtrlBlock->m_nFiberIndex-1;
		POS pos = pCurCtrlBlock->GetHeadPosition();
		CExBaseObject *pCurObj = NULL;
		CIecGenRule_CtrlCh *pCurrCtrlCh = NULL;

		while(pos)
		{
			pCurObj = pCurCtrlBlock->GetNext(pos);

			if (pCurObj->GetClassID() == GENRATECLASSID_CIECGENRULE_CTRLCH)
			{
				pCurrCtrlCh = (CIecGenRule_CtrlCh *)pCurObj;
				SetAllChMaps(pCurrCtrlCh,pIecCfgDataBase);
			}
		}

		return TRUE;
	} 
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("查找控制块(%s)失败."),pCurCtrlBlock->m_strID);
		return FALSE;
	}
}

BOOL CIecGenTool::SetAllChMaps(CIecGenRule_CtrlCh *pCurrCtrlCh,CIecCfgDatasBase *pIecCfgDatasBase)
{
	POS pos = pIecCfgDatasBase->GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CIecCfgDataBase *pIecCfgDataBase = NULL;

	while (pos != NULL)
	{
		pCurObj = pIecCfgDatasBase->GetNext(pos);

		if (pIecCfgDatasBase->IsCfgData(pCurObj->GetClassID()))
		{
			pIecCfgDataBase = (CIecCfgDataBase *)pCurObj;

			if (SetAllChMaps(pCurrCtrlCh,pIecCfgDataBase))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CIecGenTool::SetAllChMaps(CIecGenRule_CtrlCh *pChRule,CIecCfgDataBase *pIecCfgDataBase)
{
	if (pIecCfgDataBase->m_pCfgChs == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前控制块,通道信息为空."));
		return FALSE;
	}

	CIecGenCfgKeys *pKeys = (CIecGenCfgKeys*)pChRule->FindByClassID(GENRATECLASSID_CIECGENCFGKEYS);

	if (pKeys == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("控制块通道(%s)缺少关键字映射."),pChRule->m_strName);
		return FALSE;
	}

	CIecCfgChsBase *pIecCfgChsBase = pIecCfgDataBase->m_pCfgChs;
	POS pos = pIecCfgChsBase->GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Ch *pIecCfg92Ch = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	BOOL bFind = FALSE;
	CString strMatchString;

	while (pos != NULL)
	{
		pCurObj = pIecCfgChsBase->GetNext(pos);
		strMatchString = pCurObj->m_strName;

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CH)
		{
			pIecCfg92Ch = (CIecCfg92Ch *)pCurObj;
			strMatchString += pIecCfg92Ch->m_strDescExternal;
		}
		else if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
		{
			pIecCfgGoutCh = (CIecCfgGoutCh *)pCurObj;
			strMatchString += pIecCfgGoutCh->m_strDescExternal;
		}

		if (! pKeys->IsMatchSuccess(strMatchString))
		{//如果关键字不匹配，则跳过
			continue;
		}

		if (pChRule->m_strPhsID.GetLength() > 0)
		{
			if (pCurObj->m_strID.Find(pChRule->m_strPhsID) < 0)
			{
				continue;
			}
		}

			bFind = TRUE;
			CIecCfgDataChBase *pIecCfgDataChBase = (CIecCfgDataChBase*)pCurObj;
		pIecCfgDataChBase->m_strAppChID = pChRule->m_strAppCh;

			if (pIecCfgDataChBase->GetClassID() == CFGCLASSID_CIECCFG92CH)
			{
			((CIecCfg92Ch*)pIecCfgDataChBase)->m_strChType = pChRule->m_strChType;
			}

			pIecCfgDataBase->m_nUseFlag = 1;

			if (pIecCfgDataChBase->GetClassID() == CFGCLASSID_CIECCFGGINCH)
			{
				return TRUE;//Gin只能映射1个通道,SMV、Gout可映射为多个通道
			}
		}

	return bFind;
}

void CIecGenTool::OpenKeyDbFile()
{
	CString strFile;
	strFile = _P_GetCommonLibraryPath();
	strFile += _T("RelayTestKeyDb.xml");
	m_oKeyDB.OpenKeyDbFile(strFile);
}

