#include "stdafx.h"
#include "SclToIecCfgTool.h"
#include "../CfgDataMngr/IecCfg92ChIn.h"
#include "../CfgDataMngr/IecCfg92ChsIn.h"



CSclToIecCfgTool::CSclToIecCfgTool(void)
{
	m_pCSclFileRead = NULL;
}

CSclToIecCfgTool::~CSclToIecCfgTool(void)
{

}

//////////////////////////////////////////////////////////////////////////
//外部接口部分
void CSclToIecCfgTool::AddToIecCfg(CSclIed *pIed, CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	if (pIed == NULL)
	{
		return;
	}

	CSclCtrlsSmvOut *pSclCtrlsSmvOut = pIed->GetSmvOuts();
	CSclCtrlsSmvIn  *pSclCtrlsSmvIn  = pIed->GetSmvIns();
	CSclCtrlsGsOut  *pSclCtrlsGsOut  = pIed->GetGsOuts();
	CSclCtrlsGsIn   *pSclCtrlsGsIn   = pIed->GetGsIns();

	CIecCfgGinDatas  *pIecCfgGinDatas  = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV  *pIecCfgDatasSMV  = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = pIecCfgDatasMngr->GetGoutMngr();

	AddSMVInput(pIecCfgDatasMngr, pSclCtrlsSmvIn);
	AddCfgGout_By_SclGin(pIecCfgDatasMngr, pSclCtrlsGsIn);
	AddCfgGin_By_SclGout(pIecCfgDatasMngr, pSclCtrlsGsOut);

	pIecCfgDatasSMV->InitAfterRead();
	pIecCfgGinDatas->InitAfterRead();
}

void CSclToIecCfgTool::AddGinEx(CIecCfgDatasMngr *pIecfgDatasMngr,CSclIed *pCurrSelSclIed,CSclStation *pSclStation)
{
	if ((pIecfgDatasMngr == NULL)||(pCurrSelSclIed == NULL) || ( pSclStation == NULL))
	{
		return;
	}

	CExBaseList oIedListRef;
	CSclCtrlsGsOut  *pIED_GoutCtrls  = pCurrSelSclIed->GetGsOuts();
	CSclCtrlGsOut *pGoutCtrl = NULL;
	POS pos = pIED_GoutCtrls->GetHeadPosition();

	while (pos != NULL)
	{
		pGoutCtrl = (CSclCtrlGsOut *)pIED_GoutCtrls->GetNext(pos);
		pSclStation->AddIedsByGinParas(&oIedListRef,pGoutCtrl->m_strMac,pGoutCtrl->m_dwAppID);
	}

	CSclCtrlsGsOut oSclCtrlsGsOutRef;
	CSclIed *pTmpIed = NULL;
	pos = oIedListRef.GetHeadPosition();

	while (pos != NULL)
	{
		pTmpIed = (CSclIed *)oIedListRef.GetNext(pos);
		pIED_GoutCtrls = pTmpIed->GetGsOuts();
		oSclCtrlsGsOutRef.AddGsOut_NoRepeat(pIED_GoutCtrls);
	}

	CIecCfgGinDatas  *pIecCfgGinDatas  = pIecfgDatasMngr->GetGinMngr();
	CIecCfgGinData* pCfgGinData = NULL;
	pos = pIecCfgGinDatas->GetHeadPosition();

	while (pos != NULL)
	{
		pCfgGinData = (CIecCfgGinData *)pIecCfgGinDatas->GetNext(pos);
		pGoutCtrl = (CSclCtrlGsOut*)oSclCtrlsGsOutRef.FindSclCtrlByAppID_DesMac(pCfgGinData->m_dwAppID,pCfgGinData->m_strDestAddress);

		if (pGoutCtrl !=NULL)
		{
			oSclCtrlsGsOutRef.Remove(pGoutCtrl);
		}

	}

	AddCfgGin_By_SclGout(pIecfgDatasMngr, &oSclCtrlsGsOutRef);
	oSclCtrlsGsOutRef.RemoveAll();
	oIedListRef.RemoveAll();
}

#ifndef Not_USE_IECCFGFILES
void CSclToIecCfgTool::AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgFiles *pIecCfgFiles)
{
	if (pGsSmvCtrls == NULL)
	{
		return;
	}

	POS pos = pIecCfgFiles->GetHeadPosition();
	CIecCfgFile *pFile = NULL;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)pIecCfgFiles->GetNext(pos);
		AddToIecCfg_Mix(pGsSmvCtrls, pFile);
	}
}


void CSclToIecCfgTool::AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgFile *pIecCfgFile)
{
	if (pGsSmvCtrls == NULL)
	{
		return;
	}

	DWORD dwValue = 0;

	if (IFTCLASSID_CIECCFGFILE == pIecCfgFile->GetClassID())
	{
		CIecCfgDatasMngr *pDatasMngr = pIecCfgFile->m_pIecCfgDatasMngr;

		dwValue = AddToIecCfg_Mix(pGsSmvCtrls, pDatasMngr);
#ifndef _PSX_IDE_QT_
		iecfg_SetModified(pDatasMngr);
		pIecCfgFile->GetRefFrameWnd()->PostMessage(WM_IECCFGDATA_CHANGED_MIX, (WPARAM)pIecCfgFile, dwValue);
#endif
	}
	else
	{
		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile;
		CIecCfgDevice *pIecCfgDevice = pIecCfgFileDevice->GetIecCfgDevice();
		CIecCfgDatasMngr *pDatasMngr = NULL;
		POS pos = pIecCfgDevice->GetHeadPosition();

		while (pos != NULL)
		{
			pDatasMngr = (CIecCfgDatasMngr *)pIecCfgDevice->GetNext(pos);

			if (CFGCLASSID_CIECCFGDATASMNGR == pDatasMngr->GetClassID())
			{
				dwValue = AddToIecCfg_Mix(pGsSmvCtrls, pDatasMngr);
			}
		}

		CExBaseList *pListIecfgFile = pIecCfgFileDevice->GetListIecfgFile();
		pos = pListIecfgFile->GetHeadPosition();

		while (pos != NULL)
		{
			pIecCfgFile = (CIecCfgFile *)pListIecfgFile->GetNext(pos);
#ifndef _PSX_IDE_QT_
			pIecCfgFile->GetRefFrameWnd()->PostMessage(WM_IECCFGDATA_CHANGED_MIX, (WPARAM)pIecCfgFile, dwValue);
#endif
		}
	}
}
#endif

long CSclToIecCfgTool::AddToIecCfg_Mix(CExBaseList *pGsSmvCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr,BOOL bSmvInOutMerge)
{
	if (pGsSmvCtrls == NULL)
	{
		return 0;
	}

	UINT nClassID = 0;
	POS pos = pGsSmvCtrls->GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;
	long nPubGroupIndex = 1,nSubGroupIndex = 1;
	long nRetValue = 0;
	BOOL bHasSmvSub = FALSE,bHasSmvPub = FALSE,bHasGsSub = FALSE,bHasGsPub = FALSE;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)pGsSmvCtrls->GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if (nClassID == SCLIECCLASSID_CTRL_GS_OUT)
		{
			if (pSclCtrl->m_dwItemData == 0)//用于测试仪Goose订阅
			{
				AddCfgGin_By_SclGout(pIecCfgDatasMngr, (CSclCtrlGsOut*)pSclCtrl);
				bHasGsSub = TRUE;
			} 
			else
			{
				AddCfgGout_By_SclGout(pIecCfgDatasMngr, (CSclCtrlGsOut*)pSclCtrl);
				bHasGsPub = TRUE;
			}
		}
		else if (nClassID == SCLIECCLASSID_CTRL_GS_IN)
		{
			if (pSclCtrl->m_dwItemData == 0)//用于测试仪Goose订阅
			{
				AddCfgGin_By_SclGin(pIecCfgDatasMngr, (CSclCtrlGsIn*)pSclCtrl);
				bHasGsSub = TRUE;
			} 
			else
			{
				AddCfgGout_By_SclGin(pIecCfgDatasMngr, (CSclCtrlGsIn*)pSclCtrl);
				bHasGsPub = TRUE;
			}
		}
		else if ((nClassID == SCLIECCLASSID_CTRL_SMV_OUT)&&(bSmvInOutMerge))
		{
			AddSMVOutput(pIecCfgDatasMngr, (CSclCtrlSmvOut*)pSclCtrl,nPubGroupIndex);
			bHasSmvPub = TRUE;
			nPubGroupIndex++;
		}
		else if ((nClassID == SCLIECCLASSID_CTRL_SMV_IN)&&(bSmvInOutMerge))
		{
			AddSMVInput(pIecCfgDatasMngr, (CSclCtrlSmvIn*)pSclCtrl,nPubGroupIndex);
			bHasSmvPub = TRUE;
			nPubGroupIndex++;
		}
		else if ((nClassID == SCLIECCLASSID_CTRL_SMV_OUT)/*&&(!bSmvInOutMerge)*/)
		{
			if (pSclCtrl->m_dwItemData == 0)//用于测试仪SMV订阅
			{
				AddSmvCfg_By_SclSmvOut(pIecCfgDatasMngr, (CSclCtrlSmvOut*)pSclCtrl,IEC_CFG_SMV_TYPE_IN,nSubGroupIndex);
				bHasSmvSub = TRUE;
				nSubGroupIndex++;
			} 
			else
			{
				AddSmvCfg_By_SclSmvOut(pIecCfgDatasMngr, (CSclCtrlSmvOut*)pSclCtrl,IEC_CFG_SMV_TYPE_OUT,nPubGroupIndex);
				bHasSmvPub = TRUE;
				nPubGroupIndex++;
			}
		}
		else if ((nClassID == SCLIECCLASSID_CTRL_SMV_IN)/*&&(!bSmvInOutMerge)*/)
		{
			if (pSclCtrl->m_dwItemData == 0)//用于测试仪SMV订阅
			{
				AddSmvCfg_By_SclSmvIn(pIecCfgDatasMngr, (CSclCtrlSmvIn*)pSclCtrl,IEC_CFG_SMV_TYPE_IN,nSubGroupIndex);
				bHasSmvSub = TRUE;
				nSubGroupIndex++;
			} 
			else
			{
				AddSmvCfg_By_SclSmvIn(pIecCfgDatasMngr, (CSclCtrlSmvIn*)pSclCtrl,IEC_CFG_SMV_TYPE_OUT,nPubGroupIndex);
				bHasSmvPub = TRUE;
				nPubGroupIndex++;
			}
		}
	}

	if (bHasSmvPub)
	{
		nRetValue += SCL_IECFG_CTRL_TYPE_SMV;
	}

	if (bHasSmvSub &&(!bSmvInOutMerge))
	{
		nRetValue += SCL_IECFG_CTRL_TYPE_SMVSUB;
	}

	if (bHasGsSub)
	{
		CIecCfgGinDatas *pIecCfgGin = pIecCfgDatasMngr->GetGinMngr();
		pIecCfgGin->InitGinAppChMaps();
		nRetValue += SCL_IECFG_CTRL_TYPE_GS_SUB;
	}

	if (bHasGsPub)
	{
		nRetValue += SCL_IECFG_CTRL_TYPE_GS_PUB;
	}

	return nRetValue;
}

CIecCfgDataBase* CSclToIecCfgTool::AddCfgSmvInGin_By_SclSmvOutGout(CSclCtrlBase *pSclCtrlBase, CIecCfgDatasMngr *pIecCfgDatasMngr,BOOL bCoverRepeat )
{
	CIecCfgDataBase *pIecCfgDataBase = NULL;

	if (pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)
	{
		pIecCfgDataBase = AddSmvCfg_By_SclSmvOut(pIecCfgDatasMngr, (CSclCtrlSmvOut*)pSclCtrlBase,IEC_CFG_SMV_TYPE_IN,1,bCoverRepeat);
	} 
	else if (pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
	{
		pIecCfgDataBase = AddCfgGin_By_SclGout(pIecCfgDatasMngr,(CSclCtrlGsOut*)pSclCtrlBase,bCoverRepeat);
	} 
// 	else
// 	{
// 		return NULL;
// 	}

	return pIecCfgDataBase;
}

#ifndef Not_USE_IECCFGFILES
BOOL CSclToIecCfgTool::HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgFiles *pIecCfgFiles,CExBaseList &oRepeatListRef)
{
	if (pGsSmvCtrls == NULL)
	{
		return FALSE;
	}

	POS pos = pIecCfgFiles->GetHeadPosition();
	CIecCfgFile *pFile = NULL;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)pIecCfgFiles->GetNext(pos);
		HasRepeatCtrls(pGsSmvCtrls, pFile,oRepeatListRef);
	}

	return (oRepeatListRef.GetCount()>0);
}

BOOL CSclToIecCfgTool::HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgFile *pIecCfgFile,CExBaseList &oRepeatListRef)
{
	if (pGsSmvCtrls == NULL)
	{
		return FALSE;
	}

	if (IFTCLASSID_CIECCFGFILE == pIecCfgFile->GetClassID())
	{
		CIecCfgDatasMngr *pDatasMngr = pIecCfgFile->m_pIecCfgDatasMngr;

		HasRepeatCtrls(pGsSmvCtrls, pDatasMngr,oRepeatListRef);
	}
 	else
 	{
 		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile;
 		CIecCfgDevice *pIecCfgDevice = pIecCfgFileDevice->GetIecCfgDevice();
 		CIecCfgDatasMngr *pDatasMngr = NULL;
 		POS pos = pIecCfgDevice->GetHeadPosition();
 
 		while (pos != NULL)
 		{
 			pDatasMngr = (CIecCfgDatasMngr *)pIecCfgDevice->GetNext(pos);
 
 			if (CFGCLASSID_CIECCFGDATASMNGR == pDatasMngr->GetClassID())
 			{
 				HasRepeatCtrls(pGsSmvCtrls, pDatasMngr,oRepeatListRef);
 			}
 		}
 	}

	return (oRepeatListRef.GetCount()>0);
}
#endif

void CSclToIecCfgTool::AddCtrlToList(CExBaseList &oRepeatListRef,CSclCtrlBase *pSclCtrl)
{
	if (pSclCtrl == NULL)
	{
		return;
	}

	if (oRepeatListRef.Find(pSclCtrl) == NULL)
	{
		oRepeatListRef.AddTail(pSclCtrl);
	}
}

BOOL CSclToIecCfgTool::HasRepeatCtrls(CExBaseList *pGsSmvCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oRepeatListRef,BOOL bSmvInOutMerge)
{
	if (pGsSmvCtrls == NULL)
	{
		return FALSE;
	}

	UINT nClassID = 0;
	POS pos = pGsSmvCtrls->GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;
	CIecCfgDatasSMV* pSmvMngr = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgDatasSmvIn* pSmvInMngr = pIecCfgDatasMngr->GetSmvInMngr();
	CIecCfgGinDatas* pGinMngr = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgGoutDatas* pGoutMngr = pIecCfgDatasMngr->GetGoutMngr();

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)pGsSmvCtrls->GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if ((nClassID == SCLIECCLASSID_CTRL_GS_OUT)||(nClassID == SCLIECCLASSID_CTRL_GS_IN))
		{
			if (pSclCtrl->m_dwItemData == 0)//用于测试仪Goose订阅
			{
				if (pGinMngr->HasRepeatCtrl(pSclCtrl->GetAppID()))
				{
					AddCtrlToList(oRepeatListRef,pSclCtrl);
				}
			} 
			else
			{
				if (pGoutMngr->HasRepeatCtrl(pSclCtrl->GetAppID()))
				{
					AddCtrlToList(oRepeatListRef,pSclCtrl);
				}
			}
		}
		else
		{
			if ((pSclCtrl->m_dwItemData == 0)&&(!bSmvInOutMerge))//用于测试仪SMV订阅
			{
				if (pSmvInMngr->HasRepeatCtrl(pSclCtrl->GetAppID()))
				{
					AddCtrlToList(oRepeatListRef,pSclCtrl);
				}
			} 
			else
			{
				if (pSmvMngr->HasRepeatCtrl(pSclCtrl->GetAppID()))
				{
					AddCtrlToList(oRepeatListRef,pSclCtrl);
				}
			}
		}
	}

	return (oRepeatListRef.GetCount()>0);
}

#ifndef Not_USE_IECCFGFILES
void CSclToIecCfgTool::DeleteAllRepeatCtrls(CIecCfgFiles *pIecCfgFiles,CExBaseList &oRepeatListRef)
{
	POS pos = pIecCfgFiles->GetHeadPosition();
	CIecCfgFile *pFile = NULL;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)pIecCfgFiles->GetNext(pos);
		DeleteAllRepeatCtrls(pFile,oRepeatListRef);
	}
}

void CSclToIecCfgTool::DeleteAllRepeatCtrls(CIecCfgFile *pIecCfgFile,CExBaseList &oRepeatListRef)
{
	if (IFTCLASSID_CIECCFGFILE == pIecCfgFile->GetClassID())
	{
		CIecCfgDatasMngr *pDatasMngr = pIecCfgFile->m_pIecCfgDatasMngr;

		DeleteAllRepeatCtrls(pDatasMngr,oRepeatListRef);
	}
	else
	{
		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile;
		CIecCfgDevice *pIecCfgDevice = pIecCfgFileDevice->GetIecCfgDevice();
		CIecCfgDatasMngr *pDatasMngr = NULL;
		POS pos = pIecCfgDevice->GetHeadPosition();

		while (pos != NULL)
		{
			pDatasMngr = (CIecCfgDatasMngr *)pIecCfgDevice->GetNext(pos);

			if (CFGCLASSID_CIECCFGDATASMNGR == pDatasMngr->GetClassID())
			{
				DeleteAllRepeatCtrls(pDatasMngr,oRepeatListRef);
			}
		}
	}
}
#endif

void CSclToIecCfgTool::DeleteAllRepeatCtrls(CIecCfgDatasMngr *pIecCfgDatasMngr,CExBaseList &oRepeatListRef,BOOL bSmvInOutMerge)
{
	UINT nClassID = 0;
	POS pos = oRepeatListRef.GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;
	CIecCfgDatasSMV* pSmvOutMngr = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgDatasSmvIn* pSmvInMngr = pIecCfgDatasMngr->GetSmvInMngr();
	CIecCfgGinDatas* pGinMngr = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgGoutDatas* pGoutMngr = pIecCfgDatasMngr->GetGoutMngr();

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)oRepeatListRef.GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if ((nClassID == SCLIECCLASSID_CTRL_GS_OUT)||(nClassID == SCLIECCLASSID_CTRL_GS_IN))
		{
			if (pSclCtrl->m_dwItemData == 0)//用于测试仪Goose订阅
			{
				pGinMngr->DeleteRepeatCtrl(pSclCtrl->GetAppID());
			} 
			else
			{
				pGoutMngr->DeleteRepeatCtrl(pSclCtrl->GetAppID());
			}
		}
		else
		{
			if ((pSclCtrl->m_dwItemData == 0)&&(!bSmvInOutMerge))//用于测试仪订阅
			{
				pSmvInMngr->DeleteRepeatCtrl(pSclCtrl->GetAppID());
			} 
			else
			{
				pSmvOutMngr->DeleteRepeatCtrl(pSclCtrl->GetAppID());
			}
		}
	}
}

void CSclToIecCfgTool::AddToIecCfg(CSclCtrlsSmvIn  *pSclCtrlsSmvIn,CSclCtrlsGsOut  *pSclCtrlsGsOut,CSclCtrlsGsIn   *pSclCtrlsGsIn , CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	CIecCfgGinDatas  *pIecCfgGinDatas  = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV  *pIecCfgDatasSMV  = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = pIecCfgDatasMngr->GetGoutMngr();

	AddSMVInput(pIecCfgDatasMngr, pSclCtrlsSmvIn);
	AddCfgGin_By_SclGout(pIecCfgDatasMngr, pSclCtrlsGsOut);
	AddCfgGout_By_SclGin(pIecCfgDatasMngr, pSclCtrlsGsIn);

	pIecCfgDatasSMV->InitAfterRead();
	pIecCfgGinDatas->InitAfterRead();
}

void CSclToIecCfgTool::AddToIecCfg(CSclCtrlsSmvOut  *pSclCtrlsSmvOut,CSclCtrlsGsOut  *pSclCtrlsGsOut,CSclCtrlsGsIn   *pSclCtrlsGsIn , CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	CIecCfgGinDatas  *pIecCfgGinDatas  = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV  *pIecCfgDatasSMV  = pIecCfgDatasMngr->GetSmvMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = pIecCfgDatasMngr->GetGoutMngr();

	AddSMVOutput(pIecCfgDatasMngr, pSclCtrlsSmvOut);
	AddCfgGin_By_SclGout(pIecCfgDatasMngr, pSclCtrlsGsOut);
	AddCfgGout_By_SclGin(pIecCfgDatasMngr, pSclCtrlsGsIn);

	pIecCfgDatasSMV->InitAfterRead();
	pIecCfgGinDatas->InitAfterRead();
}

#ifndef Not_USE_IECCFGFILES
void CSclToIecCfgTool::AddToIecCfg(CExBaseList &oListSclCtrls, CExBaseObject *pIecCfgFile, UINT nAddToType)
{
	ASSERT (oListSclCtrls.GetCount() > 0);

	if (pIecCfgFile == NULL)
	{
		CIecCfgFiles *pFiles = CIecCfgTool::GetIecCfgFiles();
		AddToIecCfg(oListSclCtrls, pFiles, nAddToType);
	}
	else
	{
		ASSERT (pIecCfgFile->GetClassID() == IFTCLASSID_CIECCFGFILE);
		AddToIecCfg(oListSclCtrls, (CIecCfgFile*)pIecCfgFile, nAddToType);
	}
}
#endif

void CSclToIecCfgTool::OverwriteIecCfg(CExBaseObject *pSclData, CExBaseObject *pIecCfgData)
{
	
}

#ifndef Not_USE_IECCFGFILES
void CSclToIecCfgTool::AddToIecCfg(CExBaseList &oListSclCtrls, CIecCfgFiles *pIecCfgFiles, UINT nAddToType)//oListSclCtrls为添加的总控制块；pIecCfgFiles为添加入的总配置文件，在此函数里分配置文件添加；
{
	POS pos = pIecCfgFiles->GetHeadPosition();
	CIecCfgFile *pFile = NULL;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)pIecCfgFiles->GetNext(pos);
		AddToIecCfg(oListSclCtrls, pFile, nAddToType);
	}
}
#endif

void CSclToIecCfgTool::AddToIecCfg(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pDatasMngr,  UINT nAddToType)//总控制块；分SV、GOODE具体类型
{
	switch(nAddToType)
	{
	case CFGCLASSID_CIECCFGDATASSMV:
		AddToIecCfg_SMV(oListSclCtrls, pDatasMngr);
		break;

	case CFGCLASSID_CIECCFGDATASSMVINPUT:
		AddToIecCfg_SmvIn(oListSclCtrls, pDatasMngr);
		break;

	case CFGCLASSID_CIECCFGDATASGIN:
		AddToIecCfg_Gin(oListSclCtrls, pDatasMngr);
		break;

	case CFGCLASSID_CIECCFGDATASGOUT:
		AddToIecCfg_Gout(oListSclCtrls, pDatasMngr);
		break;

	}
}

#ifndef Not_USE_IECCFGFILES
void CSclToIecCfgTool::AddToIecCfg(CExBaseList &oListSclCtrls, CIecCfgFile  *pIecCfgFile,  UINT nAddToType)//总控制块，单配置文件；
{
	if (IFTCLASSID_CIECCFGFILE == pIecCfgFile->GetClassID())
	{
		CIecCfgDatasMngr *pDatasMngr = pIecCfgFile->m_pIecCfgDatasMngr;

		AddToIecCfg(oListSclCtrls, pDatasMngr, nAddToType);

#ifndef _PSX_IDE_QT_
		iecfg_SetModified(pDatasMngr);
		pIecCfgFile->GetRefFrameWnd()->PostMessage(WM_IECCFGDATA_CHANGED, (WPARAM)pIecCfgFile, nAddToType);
#endif
	}
	else
	{
		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile;
		CIecCfgDevice *pIecCfgDevice = pIecCfgFileDevice->GetIecCfgDevice();
		CIecCfgDatasMngr *pDatasMngr = NULL;
		POS pos = pIecCfgDevice->GetHeadPosition();

		while (pos != NULL)
		{
			pDatasMngr = (CIecCfgDatasMngr *)pIecCfgDevice->GetNext(pos);

			if (CFGCLASSID_CIECCFGDATASMNGR == pDatasMngr->GetClassID())
			{
				AddToIecCfg(oListSclCtrls, pDatasMngr, nAddToType);
			}
		}

		CExBaseList *pListIecfgFile = pIecCfgFileDevice->GetListIecfgFile();
		pos = pListIecfgFile->GetHeadPosition();

		while (pos != NULL)
		{
			pIecCfgFile = (CIecCfgFile *)pListIecfgFile->GetNext(pos);
#ifndef _PSX_IDE_QT_
			pIecCfgFile->GetRefFrameWnd()->PostMessage(WM_IECCFGDATA_CHANGED, (WPARAM)pIecCfgFile, nAddToType);
#endif
		}

	}
	
	//更新界面显示
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("添加到【%s】成功"), pIecCfgFile->m_strName.GetString());
}
#endif

void CSclToIecCfgTool::AddToIecCfg_SMV(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr)//此函数中分控制块逐个，同时分出是SVIn或者SVout
{
	UINT nClassID = 0;
	POS pos = oListSclCtrls.GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;
	long nGroupIndex = 1;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)oListSclCtrls.GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if (nClassID == SCLIECCLASSID_CTRL_SMV_OUT)
		{
			AddSMVOutput(pIecCfgDatasMngr, (CSclCtrlSmvOut*)pSclCtrl,nGroupIndex);
		}
		else if (nClassID == SCLIECCLASSID_CTRL_SMV_IN)
		{
			AddSMVInput(pIecCfgDatasMngr, (CSclCtrlSmvIn*)pSclCtrl,nGroupIndex);
		}
		else
		{
			ASSERT (FALSE);
		}

		nGroupIndex++;
	}
}

void CSclToIecCfgTool::AddToIecCfg_SmvIn(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr)//
{
	UINT nClassID = 0;
	POS pos = oListSclCtrls.GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;
	long nGroupIndex = 1;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)oListSclCtrls.GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if (nClassID == SCLIECCLASSID_CTRL_SMV_OUT)
		{
			AddSMVOutput(pIecCfgDatasMngr, (CSclCtrlSmvOut*)pSclCtrl,nGroupIndex);
		}
		else if (nClassID == SCLIECCLASSID_CTRL_SMV_IN)
		{
			AddSMVInput(pIecCfgDatasMngr, (CSclCtrlSmvIn*)pSclCtrl,nGroupIndex);
		}
		else
		{
			ASSERT (FALSE);
		}

		nGroupIndex++;
	}
}

void CSclToIecCfgTool::AddToIecCfg_Gin(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	UINT nClassID = 0;
	POS pos = oListSclCtrls.GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)oListSclCtrls.GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if (nClassID == SCLIECCLASSID_CTRL_GS_OUT)
		{
			AddCfgGin_By_SclGout(pIecCfgDatasMngr, (CSclCtrlGsOut*)pSclCtrl);
		}
		else if (nClassID == SCLIECCLASSID_CTRL_GS_IN)
		{
			AddCfgGin_By_SclGin(pIecCfgDatasMngr, (CSclCtrlGsIn*)pSclCtrl);
		}
		else
		{
			ASSERT (FALSE);
		}
	}
}

void CSclToIecCfgTool::AddToIecCfg_Gout(CExBaseList &oListSclCtrls, CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	UINT nClassID = 0;
	POS pos = oListSclCtrls.GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)oListSclCtrls.GetNext(pos);
		nClassID = pSclCtrl->GetClassID();

		if (nClassID == SCLIECCLASSID_CTRL_GS_OUT)
		{
			AddCfgGout_By_SclGout(pIecCfgDatasMngr, (CSclCtrlGsOut*)pSclCtrl);
		}
		else if (nClassID == SCLIECCLASSID_CTRL_GS_IN)
		{
			AddCfgGout_By_SclGin(pIecCfgDatasMngr, (CSclCtrlGsIn*)pSclCtrl);
		}
		else
		{
			ASSERT (FALSE);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//内部功能
CString scl_GetGsName(const CString &strName1, const CString &strName2)
{
	if (strName2 == strName1)
	{
		return strName1;
	}

	if (strName1.GetLength() == 0)
	{
		return strName2;
	}

	if (strName2.GetLength() == 0)
	{
		return strName1;
	}

	return strName1 + _T("-") + strName2;
}

CString scl_GetChName(const CString &strName1, const CString &strName2, const CString &strName3)
{
	//如果3个内容都不为空,取前两者
	if ((!strName1.IsEmpty())&&(!strName2.IsEmpty())&&(!strName3.IsEmpty()))
	{
		return scl_GetGsName(strName1,strName2);
	}

	if (strName1.IsEmpty())
	{
		return scl_GetGsName(strName2,strName3);
	}

	if (strName2.IsEmpty())
	{
		return scl_GetGsName(strName1,strName3);
	}

	return scl_GetGsName(strName1,strName2);
}

void CSclToIecCfgTool::InitCfgGin_By_SclGin(CIecCfgGinData *pCfgData, CSclCtrlGsIn *pSclGsIn)
{
	CSclCtrlGsOut* pGsOut = NULL;
	
	pGsOut = m_pCSclFileRead->FindGooseOutput(pSclGsIn->m_strIedID, pSclGsIn->gocbref,pSclGsIn->m_strgocbRef);

	if (pGsOut != NULL)
	{
		InitCfgGin_By_SclGout(pCfgData, pGsOut);
	}

	pCfgData->m_strDestAddress = pSclGsIn->m_strMac;
	pCfgData->m_dwAppID = pSclGsIn->m_dwAppID;

	//zhouhj 2023.9.15 
	if (pSclGsIn->m_strExIedDesc.IsEmpty())
	{
		pCfgData->m_strIedRefDesc = pSclGsIn->m_strIedID;
	} 
	else
	{
		pCfgData->m_strIedRefDesc = pSclGsIn->m_strExIedDesc;
	}

	pCfgData->m_strIedRefDesc +=  _T("-");
	pCfgData->m_strIedRefDesc += pSclGsIn->apName_own;
	//.Format(_T("%s-%s"),pSclGsIn->m_strIedID.GetString(),.GetString());// = pSclGsIn->m_strIedDesc;

	pCfgData->m_strDataSetDesc = pSclGsIn->m_strDataSetDesc;
	pCfgData->m_strgocbRef = pSclGsIn->m_strgocbRef;
	pCfgData->m_strDataSet = pSclGsIn->m_strDataSetPath;
	pCfgData->m_strGooseId = pSclGsIn->m_strGooseId;
	pCfgData->m_strgocbIED = pSclGsIn->m_strIedID;
	pCfgData->m_dwVLandPriority = pSclGsIn->m_dwVLandPriority;
	pCfgData->m_dwVLandID = pSclGsIn->m_dwVLandID;

	int nSize = pSclGsIn->m_nChnRefCount;
	CIecCfgGinCh *pCh = NULL;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->SetChannelNum(nSize);
	pChs->InitChs();

	CSclChGsIn *pSclCh = NULL;
	CString strTmp;
	POS pos = pSclGsIn->GetHeadPosition();

	while (pos != NULL)
	{
		pSclCh = (CSclChGsIn*)pSclGsIn->GetNext(pos);
		pCh = (CIecCfgGinCh *)pChs->GetAtIndex(pSclCh->outIndex);

		if (pCh != NULL)
		{
			strTmp = scl_GetGsName(pSclCh->inDADesc, pSclCh->fcda_desc);

			if (!strTmp.IsEmpty())
			{
				pCh->m_strName = strTmp;
				pCh->m_strID = pCh->m_strName;
			}

			if (!pSclCh->fcda_type.IsEmpty())
			{
				pCh->m_strDataType = pSclCh->fcda_type;
			}
		}
	}

	pCfgData->m_nChannelNum = pChs->GetCount();

}

void CSclToIecCfgTool::InitCfgGin_By_SclGout(CIecCfgGinData *pCfgData, CSclCtrlGsOut *pSclGsOut)
{
	pCfgData->m_strDestAddress = pSclGsOut->m_strMac;
	pCfgData->m_dwAppID = pSclGsOut->m_dwAppID;
	pCfgData->m_strIedRefDesc = pSclGsOut->apName;

	CSclIed *pSclIed = (CSclIed*)pSclGsOut->GetAncestor(SCLIECCLASSID_IED);

	if (pSclIed != NULL)
	{
		//pCfgData->m_strIedRefDesc.Format(_T("%s-%s-%s"),pSclIed->m_strName.GetString(), pSclIed->m_strID.GetString(),pSclGsOut->apName.GetString());
		pCfgData->m_strIedRefDesc = pSclIed->m_strName;
		pCfgData->m_strIedRefDesc.AppendFormat(_T("-%s-"),pSclIed->m_strID.GetString());
		pCfgData->m_strIedRefDesc += pSclGsOut->apName;
	}

#ifndef exbase_not_use_m_dwReserved
	if ((pSclGsOut->m_dwReserved >= 0)&&(pSclGsOut->m_dwReserved < 8))//zhouhj 20200807  用于在PNI302通过探测生成配置文件时，记录对应光口号，并对光口号赋值
	{
		pCfgData->m_nFiberIndex = pSclGsOut->m_dwReserved;
		pCfgData->m_nFiber2Index = pSclGsOut->m_dwReserved;
	}
#endif

	pCfgData->m_strDataSetDesc = pSclGsOut->m_strDataSetDesc;
	pCfgData->m_strgocbRef = pSclGsOut->m_strgocbRef;
	pCfgData->m_strDataSet = pSclGsOut->m_strDataSetPath;
	pCfgData->m_strGooseId = pSclGsOut->m_strGooseId;
	pCfgData->m_dwVersion = pSclGsOut->m_dwVersion;
	pCfgData->m_dwVLandID = pSclGsOut->m_dwVLandID;
	pCfgData->m_dwVLandPriority = pSclGsOut->m_dwVLandPriority;
	pCfgData->m_strgocbIED = pSclGsOut->GetIedString();

	pCfgData->m_nT0 = pSclGsOut->scl_gse_MaxTime;;
	pCfgData->m_nT1 = pSclGsOut->scl_gse_MinTime;

	int nSize = pSclGsOut->GetCount();
	CIecCfgGinCh *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->SetChannelNum(nSize);
	pChs->InitChs();

	POS pos = pSclGsOut->GetHeadPosition();
	CSclChGsOut *pSclCh = NULL;
	int nRow = 1;

	while (pos != NULL)
	{
		pSclCh = (CSclChGsOut*)pSclGsOut->GetNext(pos);
		pCh = (CIecCfgGinCh *)pChs->GetAtIndex(nIndex);
		pCh->m_strName   = scl_GetGsName(pSclCh->fcda_lndesc, pSclCh->fcda_dodesc);//  zhouhj  20200619  修改Gin对应的ID为通道路径
		pCh->m_strID = pSclCh->m_strID;
		pCh->m_strDataType = pSclCh->fcda_type;
		pCh->SetDataTypeByName(pSclCh->fcda_type);
		pCh->m_strExternAddr = pSclCh->m_strGinPath;
		nIndex++;
	}

	pCfgData->m_nChannelNum = pChs->GetCount();

}

void CSclToIecCfgTool::InitCfgGout_By_SclGin(CIecCfgGoutData *pCfgData, CSclCtrlGsIn *pSclGsIn)
{
	CSclCtrlGsOut* pSclGsOutFind = m_pCSclFileRead->FindGooseOutput(pSclGsIn->m_strIedID, pSclGsIn->gocbref,pSclGsIn->m_strgocbRef);
	
	if (pSclGsOutFind != NULL)
	{
		InitCfgGout_By_SclGout(pCfgData, pSclGsOutFind);
		CSclIed *pSclIed = (CSclIed*)pSclGsOutFind->GetAncestor(SCLIECCLASSID_IED);

		if (pSclIed != NULL)
		{
			if (pSclIed->m_strName.IsEmpty())
			{
				pCfgData->m_strIedRefDesc = pSclIed->m_strID;
			} 
			else
			{
				pCfgData->m_strIedRefDesc = pSclIed->m_strName;
			}
		} 
		else
		{
			pCfgData->m_strIedRefDesc = pSclGsIn->m_strIedID;
			pCfgData->m_strIedRefDesc += _T("-");
			pCfgData->m_strIedRefDesc += pSclGsIn->apName_own;
		}
	}
	else
	{
		pCfgData->m_strIedRefDesc = pSclGsIn->m_strIedID;
		pCfgData->m_strIedRefDesc += _T("-");
		pCfgData->m_strIedRefDesc += pSclGsIn->apName_own;
	}

#ifndef exbase_not_use_m_dwReserved
	if ((pSclGsIn->m_dwReserved >= 0)&&(pSclGsIn->m_dwReserved < 8))//zhouhj 20200807  用于在PNI302通过探测生成配置文件时，记录对应光口号，并对光口号赋值
	{
		pCfgData->m_nFiberIndex = pSclGsIn->m_dwReserved;
		pCfgData->m_nFiber2Index = pSclGsIn->m_dwReserved;
	}
#endif

	pCfgData->m_strDestAddress = pSclGsIn->m_strMac;
	pCfgData->m_dwAppID = pSclGsIn->m_dwAppID;


	pCfgData->m_strDataSetDesc = pSclGsIn->m_strDataSetDesc;
	pCfgData->m_strgocbRef = pSclGsIn->m_strgocbRef;
	pCfgData->m_strDataSet = pSclGsIn->m_strDataSetPath;
	pCfgData->m_strGooseId = pSclGsIn->m_strGooseId;
	pCfgData->m_strgocbIED = pSclGsIn->m_strIedID;
	//gseinputptr->strOutputIEDDesc;

	// 	int nSize = pSclGsIn->list_gseinputchn.size();
	int nSize = pSclGsIn->m_nChnRefCount;
	CIecCfgGoutCh *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;

	if (pSclGsOutFind == NULL)
	{
		pChs->SetChannelNum(nSize);
		pChs->InitChs();
	}

	POS pos = pSclGsIn->GetHeadPosition();
	CSclChGsIn *pSclCh = NULL;

	while (pos != NULL)
	{
		pSclCh = (CSclChGsIn*)pSclGsIn->GetNext(pos);
		pCh = (CIecCfgGoutCh *)pChs->GetAtIndex(pSclCh->outIndex);

		if (pCh == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("SclGsIn在对应IED输出端未查找到,IED描述(%s),GsIn中总通道数索引(%ld),当前通道对应的开出通道索引值为%ld."),
				pCfgData->m_strIedRefDesc.GetString(),pSclGsIn->m_nChnRefCount,pSclCh->outIndex);
			continue;
		}
		//pCh->m_strID   = scl_GetGsName(pSclCh->inDADesc, pSclCh->fcda_desc);
		//pCh->m_strName = pCh->m_strID;

		if ((!pSclCh->fcda_type.IsEmpty())&&(pSclGsOutFind == NULL))
		{
			pCh->m_strDataType = pSclCh->fcda_type;
		}

		pCh->m_strAddrExternal = pSclCh->inPath;
		pCh->m_nIndexExternal  = pSclCh->inIndex;
		pCh->m_strDescExternal = scl_GetChName(pSclCh->inDADesc, pSclCh->fcda_desc,pSclCh->inDODesc);
		pCh->InitAfterRead();
		nIndex++;
	}

	pCfgData->m_nChannelNum = pChs->GetCount();

}

void CSclToIecCfgTool::InitCfgGout_By_SclGout(CIecCfgGoutData *pCfgData, CSclCtrlGsOut *pSclGsOut)
{
	pCfgData->m_strDestAddress = pSclGsOut->m_strMac;
	pCfgData->m_dwAppID = pSclGsOut->m_dwAppID;
	pCfgData->m_strIedRefDesc = pSclGsOut->apName;

	CSclIed *pSclIed = (CSclIed*)pSclGsOut->GetAncestor(SCLIECCLASSID_IED);

	if (pSclIed != NULL)
	{
		//pCfgData->m_strIedRefDesc.Format(_T("%s-%s-%s"), pSclIed->m_strName.GetString(), pSclIed->m_strID.GetString(),pSclGsOut->apName.GetString());
		pCfgData->m_strIedRefDesc = pSclIed->m_strName;

		if (!pSclIed->m_strID.IsEmpty())
		{
			pCfgData->m_strIedRefDesc.AppendFormat(_T("-%s-"),pSclIed->m_strID.GetString());
			pCfgData->m_strIedRefDesc += pSclGsOut->apName;
		}
	}

	pCfgData->m_strDataSetDesc = pSclGsOut->m_strDataSetDesc;
	pCfgData->m_strgocbRef = pSclGsOut->m_strgocbRef;
	pCfgData->m_strDataSet = pSclGsOut->m_strDataSetPath;
	pCfgData->m_strGooseId = pSclGsOut->m_strGooseId;
	pCfgData->m_strgocbIED = pSclGsOut->GetIedString();
	pCfgData->m_dwVersion = pSclGsOut->m_dwVersion;
	pCfgData->m_dwVLandID = pSclGsOut->m_dwVLandID;
	pCfgData->m_dwVLandPriority = pSclGsOut->m_dwVLandPriority;
	pCfgData->m_nT0 = pSclGsOut->scl_gse_MaxTime;
	pCfgData->m_nT1 = pSclGsOut->scl_gse_MinTime;

	int nSize = pSclGsOut->GetCount();//gseoutputchn.size();
	CIecCfgGoutCh *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->SetChannelNum(nSize);
	pChs->InitChs();

	POS pos = pSclGsOut->GetHeadPosition();
	CSclChGsOut *pSclCh = NULL;
	int nRow = 1;
	
	while (pos != NULL)
	{
		pSclCh = (CSclChGsOut*)pSclGsOut->GetNext(pos);
		pCh = (CIecCfgGoutCh *)pChs->GetAtIndex(nIndex);
		pCh->m_strName   = scl_GetGsName(pSclCh->fcda_lndesc, pSclCh->fcda_dodesc);
		pCh->m_strID = pSclCh->fcda_name;
		pCh->m_strAddrExternal = _T("");//zhouhongjun  20200624
		pCh->m_strDataType = pSclCh->fcda_type;
		pCh->SetDataTypeByName(pSclCh->fcda_type);
		pCh->InitAfterRead();
		nIndex++;
		pCh->m_nIndexExternal = -1;
	}

	pCfgData->m_nChannelNum = pChs->GetCount();

}


void CSclToIecCfgTool::AddCfgGin_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsIn *pGsIns)
{
	POS pos = pGsIns->GetHeadPosition();
	CSclCtrlGsIn *pGsIn = NULL;

	while (pos != NULL)
	{
		pGsIn = (CSclCtrlGsIn *)pGsIns->GetNext(pos);
		AddCfgGin_By_SclGin(pIecCfgDatasMngr, pGsIn);
	}
}

void CSclToIecCfgTool::AddCfgGin_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsOut *pGsOuts)
{
	POS pos = pGsOuts->GetHeadPosition();
	CSclCtrlGsOut *pGsOut = NULL;

	while (pos != NULL)
	{
		pGsOut = (CSclCtrlGsOut *)pGsOuts->GetNext(pos);
		AddCfgGin_By_SclGout(pIecCfgDatasMngr, pGsOut);
	}
}

void CSclToIecCfgTool::AddCfgGout_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsIn *pGsIns)
{
	POS pos = pGsIns->GetHeadPosition();
	CSclCtrlGsIn *pGsIn = NULL;

	//ZHJ
	CString strMACAddr = _T("");

	while (pos != NULL)
	{
		pGsIn = (CSclCtrlGsIn *)pGsIns->GetNext(pos);
		if (pGsIn->m_strMac != strMACAddr)
		{
			strMACAddr = pGsIn->m_strMac ;
			AddCfgGout_By_SclGin(pIecCfgDatasMngr, pGsIn);
		}
	}

//	while (pos != NULL)
//	{
//		pGsIn = (CSclCtrlGsIn *)pGsIns->GetNext(pos);
//		AddCfgGout_By_SclGin(pIecCfgDatasMngr, pGsIn);
//	}
}

void CSclToIecCfgTool::AddCfgGout_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlsGsOut *pGsOuts)
{
	POS pos = pGsOuts->GetHeadPosition();
	CSclCtrlGsOut *pGsOut = NULL;

	while (pos != NULL)
	{
		pGsOut = (CSclCtrlGsOut *)pGsOuts->GetNext(pos);
		AddCfgGout_By_SclGout(pIecCfgDatasMngr, pGsOut);
	}
}



CIecCfgGooseDataBase* CSclToIecCfgTool::AddCfgGin_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlGsIn *pSclGsIn)
{
	CIecCfgGinData *pCfgData = (CIecCfgGinData*)pIecCfgDatasMngr->CreateNewGinCfgData();
	
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGINDATA);

	InitCfgGin_By_SclGin(pCfgData, pSclGsIn);

	return pCfgData;
}

CIecCfgGooseDataBase* CSclToIecCfgTool::AddCfgGin_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlGsOut *pSclGsOut,BOOL bCoverRepeat)
{
	CIecCfgGinData *pCfgData = NULL;

	if (bCoverRepeat)
	{
		CIecCfgGinDatas *pGinMngr = pIecCfgDatasMngr->GetGinMngr();
		pCfgData = (CIecCfgGinData *)pGinMngr->FindByAppIDFiber(pSclGsOut->m_dwAppID,pSclGsOut->m_nFiberIndex);

		if (pCfgData == NULL)
		{
			pCfgData = (CIecCfgGinData*)pIecCfgDatasMngr->CreateNewGinCfgData();
		}
	} 
	else
	{
		pCfgData = (CIecCfgGinData*)pIecCfgDatasMngr->CreateNewGinCfgData();
	}

	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGINDATA);

	InitCfgGin_By_SclGout(pCfgData, pSclGsOut);
	pCfgData->InitAfterRead();
	return pCfgData;
}

CIecCfgGooseDataBase* CSclToIecCfgTool::AddCfgGout_By_SclGin(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlGsIn *pSclGsIn)
{
	CIecCfgGoutData *pCfgData = (CIecCfgGoutData*)pIecCfgDatasMngr->CreateNewGoutCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGOUTDATA);

	InitCfgGout_By_SclGin(pCfgData, pSclGsIn);
	pCfgData->InitAfterRead();

	return pCfgData;
}

CIecCfgGooseDataBase* CSclToIecCfgTool::AddCfgGout_By_SclGout(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlGsOut *pSclGsOut)
{
	CIecCfgGoutData *pCfgData = (CIecCfgGoutData*)pIecCfgDatasMngr->CreateNewGoutCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGGOUTDATA);

	InitCfgGout_By_SclGout(pCfgData, pSclGsOut);

	return pCfgData;
}

void CSclToIecCfgTool::AddSMVInput(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlsSmvIn *pSmvIns)
{
	POS pos = pSmvIns->GetHeadPosition();
	CSclCtrlSmvIn *pSmvIn = NULL;

	//ZHJ
	CString strMACAddr = _T("") ;
	while (pos != NULL)
	{
		pSmvIn = (CSclCtrlSmvIn *)pSmvIns->GetNext(pos);
		if (strMACAddr != pSmvIn->m_strMac)
		{
			strMACAddr = pSmvIn->m_strMac ;
			AddSMVInput(pIecCfgDatasMngr, pSmvIn);
		}
	}
//	while (pos != NULL)
//	{
//		pSmvIn = (CSclCtrlSmvIn *)pSmvIns->GetNext(pos);
//		AddSMVInput(pIecCfgDatasMngr, pSmvIn);
//	}
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVInput(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvIn *pSmvIn,long nGroupIndex)//辨别选出SV的具体类型；
{
	long nSmvType = pIecCfgDatasMngr->GetSmvType();
	CIecCfgSmvDataBase* pCfgData = NULL;
	long nGroupIndexNew = nGroupIndex%6;

	switch (nSmvType)
	{
	case SMVTYPE_91:
		pCfgData = AddSMVInput_91(pIecCfgDatasMngr, pSmvIn);
		break;
	case SMVTYPE_92:
		pCfgData = AddSMVInput_92(pIecCfgDatasMngr, pSmvIn);
		break;
	case SMVTYPE_6044:
		pCfgData = AddSMVInput_60448(pIecCfgDatasMngr, pSmvIn);
		break;
	}

	switch(nGroupIndexNew)
	{
	case 1:
		pCfgData->SetAbc(TRUE, TRUE, TRUE);
		break;
	case 2:
		pCfgData->SetPabc(TRUE, TRUE, TRUE);
		break;
	case 3:
		pCfgData->SetSabc(TRUE, TRUE, TRUE);
		break;
	case 4:
		pCfgData->SetTabc(TRUE, TRUE, TRUE);
		break;
	case 5:
		pCfgData->Setabc5(TRUE, TRUE, TRUE);
		break;
	case 0:
		pCfgData->Setabc6(TRUE, TRUE, TRUE);
		break;
	default:
		pCfgData->SetAbc(TRUE, TRUE, TRUE);
		break;
	}

	return pCfgData;
}
	//ZHJ
// CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVInputAll(CIecCfgDatasMngr *pIecCfgDatasMngr, CExBaseList &oListSclCtrls)//辨别选出SV的具体类型；
// {
// 	long nSmvType = pIecCfgDatasMngr->GetSmvType();
// 	CIecCfgSmvDataBase* pCfgDataIn = NULL;
// 
// 	switch (nSmvType)
// 	{
// // 	case SMVTYPE_91:
// // 		pCfgData = AddSMVInput_91(pIecCfgDatasMngr, pSmvIn);
// // 		break;
// 	case SMVTYPE_92:
// 		pCfgDataIn = AddSMVInput_92All(pIecCfgDatasMngr, oListSclCtrls);
// 		break;
// // 	case SMVTYPE_6044:
// // 		pCfgData = AddSMVInput_60448(pIecCfgDatasMngr, pSmvIn);
// // 		break;
// 	}
// 	return pCfgDataIn;
// }

void CSclToIecCfgTool::InitCfgSmv_By_SclSMVInput_91(CIecCfg91Data *pCfgData, CSclCtrlSmvIn *pSclSmvIn)
{
	CSclCtrlSmvOut  *pOutFind = m_pCSclFileRead->FindSmvOutput(pSclSmvIn->iedExtName, pSclSmvIn->m_strSVID);

	if (pOutFind != NULL)
	{
		InitCfgSmv_By_SclSMVOutput_91(pCfgData, pOutFind);
	}

	pCfgData->m_dwAppID = pSclSmvIn->m_dwAppID;
	pCfgData->m_strDestAddress = pSclSmvIn->m_strMac;
	pCfgData->m_dwVID = pSclSmvIn->scl_smv_VLANID;
	pCfgData->m_strIedRefDesc = pSclSmvIn->iedStr;

	long nSize = GetChSize(pSclSmvIn);;

	pCfgData->SetChannelNum(12);
	CIecCfg91Ch *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->InitChs();

	long nUChIndex = 0;
	long nIChIndex = 0;
	POS pos = pSclSmvIn->GetHeadPosition();
	CSclChSmvIn *pSclCh = NULL;

	while (pos != NULL)//for (smviptchnitr = smviptchnitrB; smviptchnitr != smviptchnitrE; smviptchnitr++)
	{
		pSclCh = (CSclChSmvIn*)pSclSmvIn->GetNext(pos);
		pCh = (CIecCfg91Ch *)pChs->GetAtIndex(pSclCh->outIndex);

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}

		pCh->m_strName =  scl_GetGsName(pSclCh->inDADesc, pSclCh->fcda_desc);
		pCh->m_strID = pCh->m_strName;
		pCh->SetChTypeID(pSclCh->inDADesc);
		pCh->InitForSclRead(nUChIndex, nIChIndex);
	}

	pCfgData->m_nChannelNum = pChs->GetCount();

}

void CSclToIecCfgTool::InitCfgSmv_By_SclSMVInput_92(CIecCfg92Data *pCfgData, CSclCtrlSmvIn *pSclSmvIn)
{
	CSclCtrlSmvOut  *pOutFind = m_pCSclFileRead->FindSmvOutput(pSclSmvIn->iedExtName, pSclSmvIn->m_strSVID);

	if (pOutFind)
	{
		InitCfgSmv_By_SclSMVOutput_92(pCfgData, pOutFind);
	}
	else//zhouhj 2023.8.24 如果输出端IED查找成功,则以输出端查找的为准
	{
		if (pSclSmvIn->iedStr.Find(pSclSmvIn->iedExtName) >= 0)
		{
			//pCfgData->m_strIedRefDesc.Format(_T("%s-%s"),pSclSmvIn->iedExtName.GetString(),pSclSmvIn->apName_own.GetString());// = pSclSmvIn->iedStr;
			pCfgData->m_strIedRefDesc = pSclSmvIn->iedExtName;
			pCfgData->m_strIedRefDesc += _T("-");
			pCfgData->m_strIedRefDesc += pSclSmvIn->apName_own;

		}
		else
		{
			//pCfgData->m_strIedRefDesc.Format(_T("%s-%s-%s"), pSclSmvIn->iedStr.GetString(), pSclSmvIn->iedExtName.GetString(),pSclSmvIn->apName_own.GetString());// = pSclSmvIn->iedStr;
			pCfgData->m_strIedRefDesc = pSclSmvIn->iedStr;
			pCfgData->m_strIedRefDesc += _T("-");
			pCfgData->m_strIedRefDesc += pSclSmvIn->iedExtName;
			pCfgData->m_strIedRefDesc += _T("-");
			pCfgData->m_strIedRefDesc += pSclSmvIn->apName_own;
		}
	}

	pCfgData->m_pSclRef = pSclSmvIn;

#ifndef exbase_not_use_m_dwReserved
	if ((pSclSmvIn->m_dwReserved >= 0)&&(pSclSmvIn->m_dwReserved < 8))//zhouhj 20200807  用于在PNI302通过探测生成配置文件时，记录对应光口号，并对光口号赋值
	{
		pCfgData->m_nFiberIndex = pSclSmvIn->m_dwReserved;
		pCfgData->m_nFiber2Index = pSclSmvIn->m_dwReserved;
	}
#endif

	

	pCfgData->m_dwAppID = pSclSmvIn->m_dwAppID;
	pCfgData->m_strDestAddress = pSclSmvIn->m_strMac;
	pCfgData->m_strSVID = pSclSmvIn->m_strSVID;

	if (!pSclSmvIn->m_strDataSetPath.IsEmpty())
	{
		pCfgData->m_strDataSet = pSclSmvIn->m_strDataSetPath;
	}

	pCfgData->m_nSyn           = 1;  //缺省本地同步


	CSclChSmvIn *pSclCh = NULL;
	long nSize = 0;

	if (pOutFind == NULL)
	{
		nSize = GetChSize(pSclSmvIn);//pSclSmvIn->nChnCount;  //引用的通道数
	}
	else
	{
		nSize = pOutFind->GetCount();
		nSize = GetChSize(pOutFind);
	}

	pCfgData->SetChannelNum(nSize);
	CIecCfg92Ch *pCh = NULL;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->InitChs();
	POS pos = NULL;

	if (pOutFind == NULL)//zhouhj 20211029 只在找不到输出的情况下,将通道映射初始化为空
	{
		pos = pChs->GetHeadPosition();

		while (pos != NULL)
		{
			pCh = (CIecCfg92Ch *)pChs->GetNext(pos);
			pCh->m_strAppChID = g_strAppChID_None;
		}
	}

	long nUChIndex = 0;
	long nIChIndex = 0;
	pos = pSclSmvIn->GetHeadPosition();

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvIn*)pSclSmvIn->GetNext(pos);
		pCh = (CIecCfg92Ch*)pChs->FindByID(pSclCh->m_strID);

		if (pCh == NULL)
		{
		pCh = (CIecCfg92Ch *)pChs->GetAtIndex(pSclCh->outIndex);
		}

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}

		//pCh->m_strName = scl_GetGsName(pSclCh->inDADesc, pSclCh->fcda_desc);
		//pCh->m_strID = pSclCh->inPath;
		pCh->m_strAddrExternal = pSclCh->inPath;//pSclCh->outPath;
		pCh->m_strDescExternal = scl_GetChName(pSclCh->inDADesc, pSclCh->fcda_desc,pSclCh->inDODesc);//pSclCh->outPath;

		pCh->SetChTypeID(pSclCh->fcda_name);
		pCh->InitForSclRead(nUChIndex, nIChIndex);
		pCh->m_nIndexExternal  = pSclCh->inIndex;
	}

	pCfgData->m_nChannelNum = pChs->GetCount();
}

void CSclToIecCfgTool::InitCfgSmvIn_By_SclSMVInput_92(CIecCfg92InData *pCfg92InData, CSclCtrlSmvIn *pSclSmvIn)
{
	InitCfgSmv_By_SclSMVInput_92(pCfg92InData,pSclSmvIn);
}
	//ZHJ
void CSclToIecCfgTool::InitCfgSmv_By_SclSMVInput_92(CIecCfg92InData *pCfgDataIn, CExBaseList &oListSclCtrls)
{
	POS posFirst = oListSclCtrls.GetHeadPosition();
	CSclCtrlSmvIn* pSclSmvIn = NULL;//CSclCtrlBase *
	while (posFirst != NULL)
	{
		pSclSmvIn = (CSclCtrlSmvIn *)oListSclCtrls.GetNext(posFirst);
		InitCfgSmv_SclSMVInput_92_Str(pCfgDataIn,pSclSmvIn);

	}
	pCfgDataIn/*->DeleteAt((long)0)*/;
}

void CSclToIecCfgTool::InitCfgSmv_SclSMVInput_92_Str(CIecCfg92InData *pCfgDataIn, CSclCtrlSmvIn *pSclSmvIn)
{
	CSclCtrlSmvOut  *pOutFind = m_pCSclFileRead->FindSmvOutput(pSclSmvIn->iedExtName, pSclSmvIn->m_strSVID);

	//pCfgDataIn->m_strIedRefDesc.Format(_T("%s-%s"),pSclSmvIn->iedExtName.GetString(),pSclSmvIn->apName_own.GetString());
	pCfgDataIn->m_strIedRefDesc = pSclSmvIn->iedExtName;
	pCfgDataIn->m_strIedRefDesc += _T("-");
	pCfgDataIn->m_strIedRefDesc += pSclSmvIn->apName_own;

//	pCfgDataIn->m_strIedRefDesc = pSclSmvIn->iedStr;
	pCfgDataIn->m_strSVID = pSclSmvIn->m_strSVID;
	pCfgDataIn->m_nSyn           = 1;  //缺省本地同步
	int nSize = GetChSize(pOutFind);//pSclSmvOut->smvoutputchn.size();
	long nIndexOldAll = pCfgDataIn->m_pCfgChs->GetCount();
	pCfgDataIn->SetChannelNum(nSize);
	CIecCfg92ChIn *pCh = NULL;
	long nIndex = 0;
	CIecCfg92ChsIn *pChs = (CIecCfg92ChsIn*)pCfgDataIn->m_pCfgChs;
	pChs->InitChs();
	if (pOutFind)
	{
		POS pos = pOutFind->GetHeadPosition();
		CSclChSmvOut *pSclCh = NULL;
		while (pos != NULL)
		{
			pSclCh = (CSclChSmvOut*)pOutFind->GetNext(pos);
			pCh = (CIecCfg92ChIn *)pChs->GetAtIndex(nIndex+nIndexOldAll);

			if (pCh == NULL)
			{
				break;
			}

			if (IsQCh(pSclCh))
			{
				continue;
			}

			pCh->m_nIndexExternal = -1;
			pCh->m_strName = scl_GetGsName(pSclCh->fcda_lndesc, pSclCh->fcda_dodesc);
			pCh->m_strID = pSclCh->fcda_name;
			pCh->SetChTypeID(pSclCh->fcda_name);
			pCh->InitAccLevelByName();
			nIndex++;
		}

		pCfgDataIn->m_nChannelNum = pChs->GetCount();
	}
	CSclChSmvIn *pSclCh = NULL;
	long nUChIndex = 0;
	long nIChIndex = 0;
	POS pos = pSclSmvIn->GetHeadPosition();

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvIn*)pSclSmvIn->GetNext(pos);
		pCh = (CIecCfg92ChIn *)pChs->GetAtIndex(pSclCh->outIndex+nIndexOldAll);

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}
		pCh->m_strAddrExternal = pSclCh->inPath;//pSclCh->outPath;
		pCh->m_strDescExternal = scl_GetChName(pSclCh->inDADesc, pSclCh->fcda_desc,pSclCh->inDODesc);//pSclCh->outPath;

		pCh->SetChTypeID(pSclCh->fcda_name);
		pCh->InitForSclRead(nUChIndex, nIChIndex);
		pCh->m_nIndexExternal  = pSclCh->inIndex;
		pCh->m_strCfg92DoDesc = pSclCh->inDODesc;
		pCh->m_strCfg92dUVal = pSclCh->inDADesc;   
		pCh->m_nFiberIndex = pCfgDataIn->m_nFiberIndex; 
		pCh->m_nFiber2Index = pCfgDataIn->m_nFiber2Index; 
	}
	pCfgDataIn->m_nChannelNum = pChs->GetCount();


	CIecCfgSmvDataBase* strCfgSmvDataBase = (CIecCfgSmvDataBase*)pCfgDataIn;
	strCfgSmvDataBase->SetAbc(TRUE, TRUE, TRUE);
	POS posStr = NULL;
	pos = pChs->GetHeadPosition();
	posStr = pos;
	while (pos != NULL)
	{
		pCh = (CIecCfg92ChIn*)pChs->GetNext(pos);
		if (pCh == NULL)
		{
			break;
		}
		if (pCh->m_nIndexExternal == -1)
		{
			pChs->DeleteAt(posStr);//FreeNode
		}
		posStr = pos;

	}
}
void CSclToIecCfgTool::InitCfgSmv_By_SclSMVInput_60448(CIecCfg6044Data *pCfgData, CSclCtrlSmvIn *pSclSmvIn)
{
	CSclCtrlSmvOut  *pOutFind = m_pCSclFileRead->FindSmvOutput(pSclSmvIn->iedExtName, pSclSmvIn->m_strSVID);

	if (pOutFind != NULL)
	{
		InitCfgSmv_By_SclSMVOutput_60448(pCfgData, pOutFind);
	}

	CSclChSmvIn *pSclCh = NULL;
	long nSize = GetChSize(pSclSmvIn);
	pCfgData->SetChannelNum(12);

	CIecCfg6044Ch *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->InitChs();
	POS pos = pChs->GetHeadPosition();

	while (pos != NULL)
	{
		pCh = (CIecCfg6044Ch *)pChs->GetNext(pos);
		pCh->m_strAppChID = g_strAppChID_None;
	}

	long nUChIndex = 0;
	long nIChIndex = 0;
	pos = pSclSmvIn->GetHeadPosition();

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvIn*)pSclSmvIn->GetNext(pos);
		pCh = (CIecCfg6044Ch *)pChs->GetAtIndex(pSclCh->outIndex);

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}

		pCh->m_strName = scl_GetGsName(pSclCh->inDADesc, pSclCh->fcda_desc);
		pCh->m_strID = pCh->m_strName;
		pCh->SetChTypeID(pSclCh->fcda_name);
		pCh->InitForSclRead(nUChIndex, nIChIndex);
		nIndex++;
	}

	pCfgData->m_nChannelNum = pChs->GetCount();

}

void CSclToIecCfgTool::InitCfgSmv_By_SclSMVOutput_91(CIecCfg91Data *pCfgData, CSclCtrlSmvOut *pSclSmvOut)
{
	pCfgData->m_dwAppID = pSclSmvOut->m_dwAppID;
	pCfgData->m_strDestAddress = pSclSmvOut->m_strMac;
	pCfgData->m_dwVersion = pSclSmvOut->scl_svcb_confRev;
	pCfgData->m_dwVID = pSclSmvOut->scl_smv_VLANID;
	pCfgData->m_nPriority = pSclSmvOut->scl_smv_VLANPRI;
	pCfgData->m_strIedRefDesc = pSclSmvOut->apName;

	int nSize = GetChSize(pSclSmvOut);//pSclSmvOut->smvoutputchn.size();

	pCfgData->SetChannelNum(12);
	CIecCfg91Ch *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->InitChs();

	CSclChSmvOut *pSclCh = NULL;
	POS pos = pSclSmvOut->GetHeadPosition();

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvOut*)pSclSmvOut->GetNext(pos);
		pCh = (CIecCfg91Ch *)pChs->GetAtIndex(nIndex);

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}

		pCh->m_strName = scl_GetGsName(pSclCh->fcda_lndesc, pSclCh->fcda_dodesc);
		pCh->m_strID = pCh->m_strName;
		pCh->SetChTypeID(pSclCh->fcda_desc);

		nIndex++;
	}

	pCfgData->m_nChannelNum = pChs->GetCount();

}

BOOL CSclToIecCfgTool::IsQCh(const CString &strText)
{
	CString str = strText;
	str.MakeLower();

	if (str.Find(_T(".q")) > 0)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSclToIecCfgTool::IsQCh(CSclChSmvOut *smvoptchnPtr)
{
	if (IsQCh(smvoptchnPtr->fcda_desc))
	{
		return TRUE;
	}

	if (IsQCh(smvoptchnPtr->fcda_name))
	{
		return TRUE;
	}

	if (IsQCh(smvoptchnPtr->fcda_dodesc))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSclToIecCfgTool::IsQCh(CSclChSmvIn *smviptchnPtr)
{
	if (smviptchnPtr->fcda_desc == _T("q"))
	{
		return TRUE;
	}

	if (IsQCh(smviptchnPtr->inDODesc))
	{
		return TRUE;
	}

	if (IsQCh(smviptchnPtr->fcda_dodesc))
	{
		return TRUE;
	}

	if (IsQCh(smviptchnPtr->inDADesc))
	{
		return TRUE;
	}

	if (IsQCh(smviptchnPtr->fcda_desc))
	{
		return TRUE;
	}

	return FALSE;
}

long CSclToIecCfgTool::GetChSize(CSclCtrlSmvIn *pSclSmvIn)
{
	long nChSize = 0;

	CSclChSmvIn *smviptchnitr;
	POS pos = pSclSmvIn->GetHeadPosition();

	while (pos != NULL)
	{
		smviptchnitr = (CSclChSmvIn*)pSclSmvIn->GetNext(pos);
		
		if (IsQCh(smviptchnitr))
		{
			continue;
		}

		nChSize++;
	}

	return nChSize;
}

long CSclToIecCfgTool::GetChSize(CSclCtrlSmvOut *pSclSmvOut)
{
	long nChSize = 0;
	POS pos = pSclSmvOut->GetHeadPosition();
	CSclChSmvOut *smvoptchnPtr;

	while (pos != NULL)
	{
		smvoptchnPtr = (CSclChSmvOut*)pSclSmvOut->GetNext(pos);

		if (IsQCh(smvoptchnPtr))
		{
			continue;
		}

		nChSize++;
	}

	return nChSize;
}

void CSclToIecCfgTool::InitCfgSmv_By_SclSMVOutput_92(CIecCfg92Data *pCfgData, CSclCtrlSmvOut *pSclSmvOut)
{
	pCfgData->m_strSVID = pSclSmvOut->m_strSVID;
	pCfgData->m_dwVersion = pSclSmvOut->scl_svcb_confRev;
	pCfgData->m_dwVID = pSclSmvOut->scl_smv_VLANID;
	pCfgData->m_nPriority = pSclSmvOut->scl_smv_VLANPRI;
	pCfgData->m_strDestAddress = pSclSmvOut->m_strMac;
	pCfgData->m_dwAppID = pSclSmvOut->m_dwAppID;
	pCfgData->m_strIedRefDesc = pSclSmvOut->apName;
	pCfgData->m_strDataSet = pSclSmvOut->m_strDataSetPath.GetString();

	CSclIed *pSclIed = (CSclIed*)pSclSmvOut->GetAncestor(SCLIECCLASSID_IED);

	if (pSclIed != NULL)
	{
		pCfgData->m_strIedRefDesc = pSclIed->m_strName;
		pCfgData->m_strIedRefDesc.AppendFormat(_T("-%s-"), pSclIed->m_strID.GetString());
		pCfgData->m_strIedRefDesc += pSclSmvOut->apName;
	}

	pCfgData->m_nSyn           = 1;  //缺省本地同步


	int nSize = GetChSize(pSclSmvOut);//pSclSmvOut->smvoutputchn.size();
	pCfgData->SetChannelNum(nSize);
	CIecCfg92Ch *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->InitChs();
	POS pos = pSclSmvOut->GetHeadPosition();
	CSclChSmvOut *pSclCh = NULL;

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvOut*)pSclSmvOut->GetNext(pos);
		pCh = (CIecCfg92Ch *)pChs->GetAtIndex(nIndex);

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}

		pCh->m_nIndexExternal = -1;
		pCh->m_strName = scl_GetGsName(pSclCh->fcda_lndesc, pSclCh->fcda_dodesc);
		pCh->m_strID = pSclCh->fcda_name;
		//pCh->m_strAddrExternal = pSclCh->fcdaName;//addr
		pCh->SetChTypeID(pSclCh->fcda_name);
		nIndex++;
	}

	pCfgData->m_nChannelNum = pChs->GetCount();
}

	//ZHJ
void CSclToIecCfgTool::InitCfgSmv_By_SclSMVOutput_92(CIecCfg92InData *pCfgDataIn, CSclCtrlSmvOut *pSclSmvOut)
{
	InitCfgSmvIn_By_SclSMVOutput_92(pCfgDataIn,pSclSmvOut);
}

void CSclToIecCfgTool::InitCfgSmvIn_By_SclSMVOutput_92(CIecCfg92InData *pCfgDataIn, CSclCtrlSmvOut *pSclSmvOut)
{
	pCfgDataIn->m_strSVID = pSclSmvOut->m_strSVID;
	pCfgDataIn->m_dwVersion = pSclSmvOut->scl_svcb_confRev;
	pCfgDataIn->m_dwVID = pSclSmvOut->scl_smv_VLANID;
	pCfgDataIn->m_nPriority = pSclSmvOut->scl_smv_VLANPRI;
	pCfgDataIn->m_strDestAddress = pSclSmvOut->m_strMac;
	pCfgDataIn->m_dwAppID = pSclSmvOut->m_dwAppID;
	pCfgDataIn->m_strIedRefDesc = pSclSmvOut->apName;
	pCfgDataIn->m_strDataSet = pSclSmvOut->m_strDataSetPath;

	CSclIed *pSclIed = (CSclIed*)pSclSmvOut->GetAncestor(SCLIECCLASSID_IED);

	if (pSclIed != NULL)
	{
		//pCfgDataIn->m_strIedRefDesc.Format(_T("%s-%s"),pSclIed->m_strID.GetString(),pSclSmvOut->apName.GetString());
		pCfgDataIn->m_strIedRefDesc = pSclIed->m_strName;//zhouhj 2023.8.18 增加IED描述信息
		pCfgDataIn->m_strIedRefDesc += pSclIed->m_strID;
		pCfgDataIn->m_strIedRefDesc += _T("-");
		pCfgDataIn->m_strIedRefDesc += pSclSmvOut->apName;
	}

	pCfgDataIn->m_nSyn           = 1;  //缺省本地同步


	int nSize = GetChSize(pSclSmvOut);//pSclSmvOut->smvoutputchn.size();
	pCfgDataIn->SetChannelNum(nSize);
	CIecCfg92ChIn *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgDataIn->m_pCfgChs;
	pChs->InitChs();
	POS pos = pSclSmvOut->GetHeadPosition();
	CSclChSmvOut *pSclCh = NULL;

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvOut*)pSclSmvOut->GetNext(pos);
		pCh = (CIecCfg92ChIn *)pChs->GetAtIndex(nIndex);

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}

		pCh->m_nIndexExternal = -1;
		pCh->m_strName = scl_GetGsName(pSclCh->fcda_lndesc, pSclCh->fcda_dodesc);
		pCh->m_strID = pSclCh->fcda_name;
		//pCh->m_strAddrExternal = pSclCh->fcdaName;//addr
		pCh->SetChTypeID(pSclCh->fcda_name);
//		pCh->InitForSclRead(nUChIndex, nIChIndex);

		if (pCfgDataIn->m_nInitUseFlag)
		{
			pCh->InitAccLevelByName();
		}

		nIndex++;
	}

	pCfgDataIn->m_nChannelNum = pChs->GetCount();
}

void CSclToIecCfgTool::InitCfgSmv_By_SclSMVOutput_60448(CIecCfg6044Data *pCfgData, CSclCtrlSmvOut *pSclSmvOut)
{
	int nSize = GetChSize(pSclSmvOut);

	pCfgData->SetChannelNum(12);
	CIecCfg6044Ch *pCh = NULL;
	long nIndex = 0;
	CIecCfgChsBase *pChs = pCfgData->m_pCfgChs;
	pChs->InitChs();
	POS pos = pSclSmvOut->GetHeadPosition();
	CSclChSmvOut *pSclCh = NULL;

	while (pos != NULL)
	{
		pSclCh = (CSclChSmvOut*)pSclSmvOut->GetNext(pos);
		pCh = (CIecCfg6044Ch *)pChs->GetAtIndex(nIndex);

		if (pCh == NULL)
		{
			break;
		}

		if (IsQCh(pSclCh))
		{
			continue;
		}

		pCh->m_strName = scl_GetGsName(pSclCh->fcda_lndesc, pSclCh->fcda_dodesc);
		pCh->m_strID = pCh->m_strName;
		pCh->SetChTypeID(pSclCh->fcda_name);
		nIndex++;
	}	

	pCfgData->m_nChannelNum = pChs->GetCount();

}


CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVInput_91(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvIn *pSclSmvIn)
{
	CIecCfg91Data *pCfgData = (CIecCfg91Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	ASSERT (pCfgData != NULL);

	if (pCfgData == NULL)
	{
		return NULL;
	}

	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG91DATA);

	InitCfgSmv_By_SclSMVInput_91(pCfgData, pSclSmvIn);

	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVInput_92(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvIn *pSclSmvIn)
{
	CIecCfg92Data *pCfgData = (CIecCfg92Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92DATA);

	InitCfgSmv_By_SclSMVInput_92(pCfgData, pSclSmvIn);

	return pCfgData;
}
	//ZHJ
// CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVInput_92All(CIecCfgDatasMngr *pIecCfgDatasMngr, CExBaseList &oListSclCtrls)
// {
// 
// 	CIecCfgDatasSMVInput *pCfgDatasIn = pIecCfgDatasMngr->GetSmvInputMngr();
// 	POS pos = pCfgDatasIn->GetHeadPosition();
// 	CIecCfg92InputData *pCfgDataIn = (CIecCfg92InputData*)pCfgDatasIn->GetNext(pos);
// 	UINT  nClassID = pCfgDataIn->GetClassID();
// 	ASSERT (nClassID == CFGCLASSID_CIECCFG92INPUTDATA);
// 	InitCfgSmv_By_SclSMVInput_92(pCfgDataIn, oListSclCtrls);
// 
// 	return (CIecCfg92Data*)pCfgDataIn;
// }
CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVInput_60448(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvIn *pSclSmvIn)
{
	CIecCfg6044Data *pCfgData = (CIecCfg6044Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG6044DATA);

	InitCfgSmv_By_SclSMVInput_60448(pCfgData, pSclSmvIn);	

	return pCfgData;
}

void CSclToIecCfgTool::AddSMVOutput(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlsSmvOut *pSclSmvOuts)
{
	POS pos = pSclSmvOuts->GetHeadPosition();
	CSclCtrlSmvOut *pSclSmvOut = NULL;

	while (pos != NULL)
	{
		pSclSmvOut = (CSclCtrlSmvOut *)pSclSmvOuts->GetNext(pos);
		AddSMVOutput(pIecCfgDatasMngr, pSclSmvOut);
	}
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVOutput(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvOut *pSclSmvOut,long nGroupIndex)
{
	long nSmvType = pIecCfgDatasMngr->GetSmvType();
	CIecCfgSmvDataBase *pCfgData = NULL;
	long nGroupIndexNew = nGroupIndex%6;

	switch (nSmvType)
	{
	case SMVTYPE_91:
		pCfgData = AddSMVOutput_91(pIecCfgDatasMngr, pSclSmvOut);
		break;

	case SMVTYPE_92:
		pCfgData = AddSMVOutput_92(pIecCfgDatasMngr, pSclSmvOut);
		break;

	case SMVTYPE_6044:
		pCfgData = AddSMVOutput_60448(pIecCfgDatasMngr, pSclSmvOut);
		break;
	}

//	pCfgData->SetAbc(TRUE, TRUE, TRUE);
	switch(nGroupIndex)
	{
	case 1:
		pCfgData->SetAbc(TRUE, TRUE, TRUE);
		break;
	case 2:
		pCfgData->SetPabc(TRUE, TRUE, TRUE);
		break;
	case 3:
		pCfgData->SetSabc(TRUE, TRUE, TRUE);
		break;
	case 4:
		pCfgData->SetTabc(TRUE, TRUE, TRUE);
		break;
	case 5:
		pCfgData->Setabc5(TRUE, TRUE, TRUE);
		break;
	case 0:
		pCfgData->Setabc6(TRUE, TRUE, TRUE);
		break;
	default:
		pCfgData->SetAbc(TRUE, TRUE, TRUE);
		break;
	}


	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSmvCfg_By_SclSmvOut(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvOut *pSclSmvOut,long nCfgInOutType
															 ,long nGroupIndex,BOOL bCoverRepeat)
{
	CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = pIecCfgDatasMngr->GetSmvInMngr();
	CIecCfgDatasSMV* pIecCfgDatasSmvOut = pIecCfgDatasMngr->GetSmvMngr();
	long nSmvType = pIecCfgDatasSmvOut->GetSmvType();
	CIecCfgSmvDataBase *pCfgData = NULL;
	long nGroupIndexNew = nGroupIndex%6;

//	if (nCfgInOutType == IEC_CFG_SMV_TYPE_IN)  2023.6.25 zhouhj  目前只支持9-2采样值控制块导入SCD,故强制改92方式
	{
		nSmvType = pIecCfgDatasSmvIn->GetSmvType();

		if (nSmvType != SMVTYPE_92)
		{
			pIecCfgDatasSmvIn->m_strSmvType = iecfg_GetSmvTypeByID(SMVTYPE_92);
//			pIecCfgDatasSmvIn->SetSmvType(SMVTYPE_92);//导入SCL时目前只支持9-2模式,强制设置为9-2
			nSmvType = SMVTYPE_92;
		}
	}

	BOOL bIsCreateNewCB = TRUE;

	switch (nSmvType)
	{
	case SMVTYPE_91:
//		pCfgData = AddSMVOutput_91(pIecCfgDatasMngr, pSclSmvOut);
		break;

	case SMVTYPE_92:

		if (nCfgInOutType == IEC_CFG_SMV_TYPE_IN)
		{
			pCfgData = AddCfgSmvIn_By_SclSmvOut_92(pIecCfgDatasMngr, pSclSmvOut,bCoverRepeat);
			CIecCfg92InData *pIecCfg92InData = (CIecCfg92InData*)pCfgData;
			bIsCreateNewCB = pIecCfg92InData->m_nInitUseFlag;
		} 
		else
		{
			pCfgData = AddCfgSmvOut_By_SclSmvOut_92(pIecCfgDatasMngr, pSclSmvOut);
		}
		break;

	case SMVTYPE_6044:
//		pCfgData = AddSMVOutput_60448(pIecCfgDatasMngr, pSclSmvOut);
		break;
	}

	if (bCoverRepeat)
	{
		if (bIsCreateNewCB)//zhouhj 2023.11.6 目前SetAbc函数中,会把根据通道描述重新设置通道映射,故对于已有的控制块不进行自动设置
		{
			pCfgData->SetAbc(TRUE, TRUE, TRUE);//zhouhj 2023.7.12 覆盖重复的方式,固定映射到第一组
		}
	}
	else
	{
		switch(nGroupIndex)
		{
		case 1:
			pCfgData->SetAbc(TRUE, TRUE, TRUE);
			break;
		case 2:
			pCfgData->SetPabc(TRUE, TRUE, TRUE);
			break;
		case 3:
			pCfgData->SetSabc(TRUE, TRUE, TRUE);
			break;
		case 4:
			pCfgData->SetTabc(TRUE, TRUE, TRUE);
			break;
		case 5:
			pCfgData->Setabc5(TRUE, TRUE, TRUE);
			break;
		case 0:
			pCfgData->Setabc6(TRUE, TRUE, TRUE);
			break;
		default:
			pCfgData->SetAbc(TRUE, TRUE, TRUE);
			break;
		}
	}

	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSmvCfg_By_SclSmvIn(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvIn *pSmvIn,long nCfgInOutType,long nGroupIndex)
{
	CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = pIecCfgDatasMngr->GetSmvInMngr();
	CIecCfgDatasSMV* pIecCfgDatasSmvOut = pIecCfgDatasMngr->GetSmvMngr();
	long nSmvType = pIecCfgDatasSmvOut->GetSmvType();
	CIecCfgSmvDataBase *pCfgData = NULL;
	long nGroupIndexNew = nGroupIndex%6;

//	if (nCfgInOutType == IEC_CFG_SMV_TYPE_IN)   2023.6.25 zhouhj  目前只支持9-2采样值控制块导入SCD,故强制改92方式
	{
		nSmvType = pIecCfgDatasSmvIn->GetSmvType();

		if (nSmvType != SMVTYPE_92)
		{
			pIecCfgDatasSmvIn->SetSmvType(SMVTYPE_92);//导入SCL时目前只支持9-2模式,强制设置为9-2
			nSmvType = SMVTYPE_92;
		}
	}

	switch (nSmvType)
	{
	case SMVTYPE_91:
		//		pCfgData = AddSMVOutput_91(pIecCfgDatasMngr, pSclSmvOut);
		break;

	case SMVTYPE_92:

		if (nCfgInOutType == IEC_CFG_SMV_TYPE_IN)
		{
			pCfgData = AddCfgSmvIn_By_SclSmvIn_92(pIecCfgDatasMngr, pSmvIn);
		} 
		else
		{
			pCfgData = AddCfgSmvOut_By_SclSmvIn_92(pIecCfgDatasMngr, pSmvIn);
		}
		break;

	case SMVTYPE_6044:
		//		pCfgData = AddSMVOutput_60448(pIecCfgDatasMngr, pSclSmvOut);
		break;
	}

	switch(nGroupIndex)
	{
	case 1:
		pCfgData->SetAbc(TRUE, TRUE, TRUE);
		break;
	case 2:
		pCfgData->SetPabc(TRUE, TRUE, TRUE);
		break;
	case 3:
		pCfgData->SetSabc(TRUE, TRUE, TRUE);
		break;
	case 4:
		pCfgData->SetTabc(TRUE, TRUE, TRUE);
		break;
	case 5:
		pCfgData->Setabc5(TRUE, TRUE, TRUE);
		break;
	case 0:
		pCfgData->Setabc6(TRUE, TRUE, TRUE);
		break;
	default:
		pCfgData->SetAbc(TRUE, TRUE, TRUE);
		break;
	}


	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVOutput_91(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvOut *pSclSmvOut)
{
	CIecCfg91Data *pCfgData = (CIecCfg91Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG91DATA);

	InitCfgSmv_By_SclSMVOutput_91(pCfgData, pSclSmvOut);

	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVOutput_92(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvOut *pSclSmvOut)
{
	CIecCfg92Data *pCfgData = (CIecCfg92Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92DATA);

	InitCfgSmv_By_SclSMVOutput_92(pCfgData, pSclSmvOut);

	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddCfgSmvIn_By_SclSmvOut_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSclSmvOut,BOOL bCoverRepeat)
{
	CIecCfg92InData *pCfgData = NULL;

	if (bCoverRepeat)
	{
		CIecCfgDatasSmvIn *pSmvInMngr = pIecCfgDatasMngr->GetSmvInMngr();
		pCfgData = (CIecCfg92InData *)pSmvInMngr->FindByAppIDFiber(pSclSmvOut->m_dwAppID,pSclSmvOut->m_nFiberIndex);

		if (pCfgData == NULL)
		{
			pCfgData = (CIecCfg92InData*)pIecCfgDatasMngr->CreateNewSmvInCfgData();
		}
		else
		{
			pCfgData->m_nInitUseFlag = 0;
		}
	}
	else
	{
		pCfgData = (CIecCfg92InData*)pIecCfgDatasMngr->CreateNewSmvInCfgData();
	}

	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92INPUTDATA);
	InitCfgSmvIn_By_SclSMVOutput_92(pCfgData, pSclSmvOut);
	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddCfgSmvOut_By_SclSmvOut_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvOut *pSclSmvOut)
{
	CIecCfg92Data *pCfgData = (CIecCfg92Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92DATA);

	InitCfgSmv_By_SclSMVOutput_92(pCfgData, pSclSmvOut);

	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddCfgSmvIn_By_SclSmvIn_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSclSmvIn)
{
	CIecCfg92InData *pCfgData = (CIecCfg92InData*)pIecCfgDatasMngr->CreateNewSmvInCfgData();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92INPUTDATA);
	InitCfgSmvIn_By_SclSMVInput_92(pCfgData, pSclSmvIn);
	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddCfgSmvOut_By_SclSmvIn_92(CIecCfgDatasMngr *pIecCfgDatasMngr,CSclCtrlSmvIn *pSclSmvIn)
{
	CIecCfg92Data *pCfgData = (CIecCfg92Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG92DATA);
	InitCfgSmv_By_SclSMVInput_92(pCfgData, pSclSmvIn);
	return pCfgData;
}

CIecCfgSmvDataBase* CSclToIecCfgTool::AddSMVOutput_60448(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclCtrlSmvOut *pSclSmvOut)
{
	CIecCfg6044Data *pCfgData = (CIecCfg6044Data*)pIecCfgDatasMngr->CreateNewSmvCfgData();
	//pCfgData->InitAfterRead();
	UINT nClassID = pCfgData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFG6044DATA);

	InitCfgSmv_By_SclSMVOutput_60448(pCfgData, pSclSmvOut);

	return pCfgData;
}

//#ifndef Not_USE_IECCFGFILES
//void CSclToIecCfgTool::ValidCtrls_Repeat(CIecCfgFiles *pIecCfgFiles,CExBaseList *pListSclDatas ,UINT nClassID)
//{
//	POS pos = pIecCfgFiles->GetHeadPosition();
//	CIecCfgFile *pFile = NULL;
//
//	while (pos != NULL)
//	{
//		pFile = (CIecCfgFile *)pIecCfgFiles->GetNext(pos);
//
//		switch(nClassID)
//		{
//		case CFGCLASSID_CIECCFGDATASSMV:
//			{
//				CIecCfgDatasSMV* pIecCfgDatasSMV = pFile->m_pIecCfgDatasMngr->GetSmvMngr();
//				ValidCtrls_Repeat(pListSclDatas,pIecCfgDatasSMV);
//			}
//			break;
//
//		case CFGCLASSID_CIECCFGDATASGIN:
//			{
//				CIecCfgGinDatas* pIecCfgGinDatas = pFile->m_pIecCfgDatasMngr->GetGinMngr();
//				ValidCtrls_Repeat(pListSclDatas,pIecCfgGinDatas);
//
//			}
//			break;
//
//		case CFGCLASSID_CIECCFGDATASGOUT:
//			{
//				CIecCfgGoutDatas* pIecCfgGoutDatas = pFile->m_pIecCfgDatasMngr->GetGoutMngr();
//				ValidCtrls_Repeat(pListSclDatas,pIecCfgGoutDatas);
//			}
//			break;
//
//		}
//	}
//}
//#endif
//
//void CSclToIecCfgTool::ValidCtrls_Repeat(CExBaseList *pListSclDatas,CIecCfgDatasBase* pIecCfgDatas)
//{
//	CSclCtrlBase* pTemp = NULL;
//	POS pos = pListSclDatas->GetHeadPosition();
//	CString strMsg;
//	UINT nRet = 0;
//	DWORD dwAppID;
//
//	while (pos)
//	{
//		pTemp = (CSclCtrlBase*)pListSclDatas->GetNext(pos);
//		dwAppID = pTemp->GetAppID();
//
//		if (pIecCfgDatas->IsAppID_Repeat(dwAppID))
//		{
//			strMsg.Format(_T("当前控制块(AppID=0x%04X)已存在,是否重复添加?"),dwAppID);
//#ifdef _PSX_IDE_QT_
//			if (nRet == IDNO)
//#else
//			nRet = MessageBox(NULL,strMsg.GetString(), _T("提示"), MB_YESNO | MB_ICONQUESTION);
//			if (nRet == IDNO)
//#endif
//
//			{
//				pListSclDatas->Remove(pTemp);
//			}
//		}
//	}
//}
