// IEDGSSVInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SclFileRead.h"
#include "..\..\..\Module\System\TickCount32.h"
#include "..\..\Module\DataMngr\DvmDevice.h"

CSclFileRead::CSclFileRead()
{
	m_bIsInReadState = FALSE;
	m_pThreadProgress = FALSE;
}

CSclFileRead::~CSclFileRead()
{
	scl_info_destroy(&m_SclInfo);
}

DWORD CSclFileRead::Filter(const CString &strTxtFilter, DWORD dwMode)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->FilterOwn(strTxtFilter, dwMode);
	}

	return 0;
}

BOOL CSclFileRead::ReadSclFile(const CString &strFile, CWnd *pOwnerWnd, CThreadProgressInterface *pThreadProgress)
{
	m_pThreadProgress = pThreadProgress;
	m_strFile = strFile;
	m_pOwnerWnd = pOwnerWnd;
	CWinThread *pThread = AfxBeginThread(ReadSCLThread, this);
	pThread->m_bAutoDelete = TRUE;
	return TRUE;
}

CSclCtrlGsOut* CSclFileRead::FindGooseOutput(const CString &strIedName, const CString &strGsID)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsGsOut *pSclCtrlsGsOut = pIed->GetGsOuts();

	FindGSSVControl(pSclCtrlsGsOut);

	CSclCtrlGsOut *pFind = (CSclCtrlGsOut*)pSclCtrlsGsOut->FindByID(strGsID);

	return pFind;
}

CSclCtrlSmvOut* CSclFileRead::FindSmvOutput(const CString &strIedName, const CString &strSmvID)
{
	CSclIed *pIed = (CSclIed*)FindByID(strIedName);

	if (pIed == NULL)
	{
		return NULL;
	}

	CSclCtrlsSmvOut *pSclCtrlsSmvOut = pIed->GetSmvOuts();

	FindGSSVControl(pSclCtrlsSmvOut);

	CSclCtrlSmvOut *pFind = (CSclCtrlSmvOut*)pSclCtrlsSmvOut->FindByID(strSmvID);

	return pFind;
}

void CSclFileRead::FindGSSVControl(CSclCtrls *pCtrls)
{
	if (pCtrls->IsRead())
	{
		return;
	}

	BOOL bGsIn = scl_IsGsIns(pCtrls);
	BOOL bGsOut = scl_IsGsOuts(pCtrls);
	BOOL bSmvIn = scl_IsSmvIns(pCtrls);
	BOOL bSmvOut = scl_IsSmvOuts(pCtrls);

	CSclIed *pIed = scl_GetIed(pCtrls);
	FindGSSVControl(&m_SclInfo, pIed, bGsIn, bGsOut, bSmvIn, bSmvOut);

	//获取通道
	POS pos = pCtrls->GetHeadPosition();
	CSclCtrlBase *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CSclCtrlBase *)pCtrls->GetNext(pos);

		if (bGsIn)
		{
			FindGSSVInChannelInfo(&m_SclInfo, pCtrl);
		}

		if (bGsOut)
		{
			FindGSSVOutChannelInfo(&m_SclInfo, pCtrl);
		}

		if (bSmvIn)
		{
			FindGSSVInChannelInfo(&m_SclInfo, pCtrl);
		}

		if (bSmvOut)
		{
			FindGSSVOutChannelInfo(&m_SclInfo, pCtrl);
		}

		pCtrl->m_nChnCount = pCtrl->GetCount();
	}

	pCtrls->SetRead();
}

BOOL CSclFileRead::FindGSSVControl(CExBaseList *pList)
{
	UINT nClassID = pList->GetClassID();

	if (   (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
		|| (nClassID == SCLIECCLASSID_CTRLS_GS_OUT)
		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_IN)
		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_OUT) )
	{
		FindGSSVControl((CSclCtrls*)pList);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CSclFileRead::FindGSSVControl(CSclIed *pIed, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut)
{
	FindGSSVControl(&m_SclInfo, pIed, bGsIn, bGsOut, bSmvIn, bSmvOut);
}

UINT CSclFileRead::ReadSCLThread( LPVOID pParam )
{
	::CoInitialize(NULL);
	CSclFileRead *pSclFileRead = (CSclFileRead *)pParam;
	pSclFileRead->m_bIsInReadState = TRUE;

	pSclFileRead->m_pThreadProgress->SetMaxRange(40);
	pSclFileRead->m_pThreadProgress->ShowMsg(_T("读取SCD文件......"));
	ST_RET ret = scl_parse(pSclFileRead->m_strFile.GetBuffer(), &pSclFileRead->m_SclInfo);

	if (ret == SD_SUCCESS)
	{
		pSclFileRead->m_pThreadProgress->StepIt();
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("处理IED数据......"));
		pSclFileRead->ReadGSSVInfo(&pSclFileRead->m_SclInfo);
		long nCount = pSclFileRead->GetCount() + 2;
		pSclFileRead->m_pThreadProgress->SetMaxRange(nCount);
		pSclFileRead->m_pThreadProgress->StepIt();
		CSclIed *pIed = (CSclIed*)pSclFileRead->GetHead();
		CString strMsg;

		if (nCount > 0)
		{
			strMsg.Format(_T("1 / %d 处理IED【%s】"), nCount-2, pIed->m_strName);
			pSclFileRead->m_pThreadProgress->ShowMsg(strMsg);
			pSclFileRead->ReadIed(pIed);
			pSclFileRead->m_pThreadProgress->StepIt();

			if (pSclFileRead->m_pOwnerWnd != NULL)
			{
				pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_SHOW);
			}
		}

		POS pos = pSclFileRead->GetHeadPosition();
		pIed = (CSclIed *)pSclFileRead->GetNext(pos);
		long nIndex = 2;

		while (pos != NULL)
		{
			strMsg.Format(_T("%d / %d 处理IED【%s】"), nIndex, nCount-2, pIed->m_strName);
			pIed = (CSclIed *)pSclFileRead->GetNext(pos);
			pSclFileRead->m_pThreadProgress->ShowMsg(strMsg);
			pSclFileRead->ReadIed(pIed);
			pSclFileRead->m_pThreadProgress->StepIt();
			nIndex++;
		}
	}
	else
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("无法解析SCL文件【%s】！"), pSclFileRead->m_strFile);
	}

	//继续处理数据

	if (pSclFileRead->m_pOwnerWnd != NULL)
	{
		pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_FINISH);
	}

	pSclFileRead->m_bIsInReadState = FALSE;
	scl_info_destroy(&pSclFileRead->m_SclInfo);

	::CoUninitialize();

	return 0;
}


void CSclFileRead::ReadGSSVInfo(SCL_INFO* scl_info)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;

	SCL_DATASET *scl_dataset = NULL;
	SCL_FCDA	*scl_fcda = NULL;

	SCL_INPUTS	*scl_inputs = NULL;
	SCL_EXTREF	*scl_extref = NULL;

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)scl_info->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)scl_info->iedHead, (DBL_LNK *)scl_ied))
	{
		CSclIed *pNew = new CSclIed();
		pNew->SetRefIED(scl_ied);
		AddNewChild(pNew);

		CDvmDevice *pDvmDevice = pNew->GetDvmDevice();
		
		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{
			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				CDvmLogicDevice *pDvmLdevice=new CDvmLogicDevice();			//cgl	对应逻辑节点
				pDvmLdevice->m_strID=scl_ld->inst;
				pDvmLdevice->m_strName=scl_ld->desc;
				pDvmDevice->AddNewChild(pDvmLdevice);				

				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					//if (strcmp(_strupr(_strdup(lnName)), _T("LLN0")) == 0)
					if (0 == stricmp(lnName, _T("LLN0")))
					{
						for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)scl_ln->datasetHead);
							scl_dataset != NULL;
							scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)scl_ln->datasetHead, (DBL_LNK *)scl_dataset))
						{
							if (IsDatasetInGSSV(scl_ln, scl_dataset->name))
							{
								for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
									scl_fcda != NULL;
									scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
								{
									//get fcda type, value and desc
									GetFCDAInfo(scl_info, scl_ap, scl_fcda);
								}

// 								if (strcmp(scl_dataset->name, "dsRelayAin") == 0)
// 								{
// 									for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
// 										scl_fcda != NULL;
// 										scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
// 									{
// 										LogFCDAInfo(scl_info, scl_ap, scl_fcda);
// 									}
// 								}
							}
							else
							{
								CDvmDataset *pDataset=new CDvmDataset();
								pDataset->m_strID=scl_dataset->name;
								pDataset->m_strName=scl_dataset->desc;
								pDvmLdevice->AddNewChild(pDataset);

								for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
									scl_fcda != NULL;
									scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
								{
									//get fcda type, value and desc

									CDvmData *pData=new CDvmData();
									pDataset->AddNewData(pData);
									LogFCDAInfo(scl_info, scl_ap, scl_fcda,pData);								
														
								}
							}
						}

						for (scl_inputs = (SCL_INPUTS *)list_find_last((DBL_LNK *)scl_ln->inputsHead);
							scl_inputs != NULL;
							scl_inputs = (SCL_INPUTS *)list_find_prev((DBL_LNK *)scl_ln->inputsHead, (DBL_LNK *)scl_inputs))
						{
							for (scl_extref = (SCL_EXTREF *)list_find_last((DBL_LNK *)scl_inputs->extrefHead);
								scl_extref != NULL;
								scl_extref = (SCL_EXTREF *)list_find_prev((DBL_LNK *)scl_inputs->extrefHead, (DBL_LNK *)scl_extref))
							{
								//get extref desc
								GetExtRefDesc(scl_ap, scl_extref);

								//GOOSE Subscribe
								if (/*!rootinfo.bGOOSEInput*/
									/*&& */(strlen(scl_extref->inAddr) > 0)
									&& (strlen(scl_extref->domName) > 0))
								{
									CSclCtrlsGsIn *pGsIns = pNew->GetGsIns();
									//m_TIED.InsertItem(_T("GOOSE Inputs"), hroot);
									///rootinfo.bGOOSEInput = true;
								} 

								//SV Subscribe
								if (/*!rootinfo.bSMVInput
									&& */(strlen(scl_extref->inAddr) > 0)
									&& (strlen(scl_extref->domName) > 0))
								{
									//m_TIED.InsertItem(_T("SMV Inputs"), hroot);
									//rootinfo.bSMVInput = true;
									CSclCtrlsSmvIn *pGsIns = pNew->GetSmvIns();
								}
							}
						}

						//GOOSE Outputs
						if (/*!rootinfo.bGOOSEOutput 
							&& */(NULL != (SCL_GCB *)list_find_last((DBL_LNK *)scl_ln->gcbHead)))							
						{
							//m_TIED.InsertItem(_T("GOOSE Outputs"), hroot);
							//rootinfo.bGOOSEOutput = true;
							CSclCtrlsGsOut *pGsOuts = pNew->GetGsOuts();
						}

						//SMV Outputs
						if (/*!rootinfo.bSMVOutput 
							&& */(NULL != (SCL_SVCB *)list_find_last((DBL_LNK *)scl_ln->svcbHead)))
						{
							//m_TIED.InsertItem(_T("SMV Outputs"), hroot);
							//rootinfo.bSMVOutput = true;
							CSclCtrlsSmvOut *pGsIns = pNew->GetSmvOuts();
						}
						
						break;
					}
				}
			}
		}

		//m_Rootlist.push_back(rootinfo);
		CString strFile;
		strFile = _P_GetLibraryPath();
		strFile.AppendFormat(_T("%s.xml"), pDvmDevice->m_strID);
		pDvmDevice->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	}

	//读取第一个IED
	CSclIed *pIed = (CSclIed*)GetHead();


	//m_TIED.Invalidate();
	//m_TIED.UpdateWindow();
}

//whether the dataset is in GOOSE or SV
bool CSclFileRead::IsDatasetInGSSV(SCL_LN *sclln, char *dataset)
{
	SCL_GCB		*scl_gcb = NULL;
	SCL_SVCB	*scl_svcb = NULL;

	for (scl_gcb = (SCL_GCB *)list_find_last((DBL_LNK *)sclln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev((DBL_LNK *)sclln->gcbHead, (DBL_LNK *)scl_gcb))
	{
		if(scl_gcb->isGoose == SD_FALSE)
		{
			continue;
		}

		if (0 == strcmp(dataset, scl_gcb->datSet))
		{
			return true;
		}
	}

	for (scl_svcb = (SCL_SVCB *)list_find_last((DBL_LNK *)sclln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *)list_find_prev((DBL_LNK *)sclln->svcbHead, (DBL_LNK *)scl_svcb))
	{
		if (0 == strcmp(dataset, scl_svcb->datSet))
		{
			return true;
		}
	}

	return false;
}

//get extref desc
ST_RET CSclFileRead::GetExtRefDesc(SCL_AP *sclap, SCL_EXTREF *sclextref)
{
	SCL_LD	*scl_ld = NULL;
	SCL_LN	*scl_ln = NULL;
	SCL_DAI	*scl_dai = NULL;

	ST_CHAR extrefldName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR extreflnName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	extrefdoName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	extrefdescName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR extrefdoiName	[MAX_IDENT_LEN + 1] = {0};

	//find extref ld/ln/do name from sclextref
	FindextrefName(sclextref, extrefldName, extreflnName, extrefdoName);

	strncpy (extrefdescName, extrefdoName, MAX_IDENT_LEN + 1);
	strcat (extrefdescName, _T("$dU"));
	strncpy (extrefdoiName, extrefdoName, MAX_IDENT_LEN + 1);
	strcat (extrefdoiName, _T("$desc"));

	for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)sclap->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)sclap->ldHead, (DBL_LNK *)scl_ld))
	{
		if (0 == strcmp(extrefldName, scl_ld->inst))
		{
			for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
			{
				ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
				//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
				//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
				//strncat (lnName, scl_ln->inst,  MAX_IDENT_LEN + 1 - strlen(lnName));
				scl_get_ln_name(scl_ln, lnName);

				if (0 == strcmp(extreflnName, lnName))
				{
					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
						scl_dai != NULL;
						scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
						if (strcmp(scl_dai->flattened, extrefdescName) == 0)
						{//sclextref dU desc 
							if (scl_dai->Val)
							{
								strncpy (sclextref->desc, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(sclextref->desc);
							}
						}
						else if (strcmp(scl_dai->flattened, extrefdoiName) == 0)
						{//sclextref do desc
							if (scl_dai->Val)
							{
								strncpy (sclextref->dodesc, scl_dai->Val, MAX_IDENT_LEN + 1);
							}
						}
					}
					
					if (scl_ln->desc)
					{//sclextref ln desc
						strncpy (sclextref->lndesc, scl_ln->desc, MAX_IDENT_LEN + 1);
					}

					break;
				}
			}
			break;
		}
	}

	return SD_SUCCESS;
}

//get fcda type, /*value*/ and desc
ST_RET CSclFileRead::GetFCDAInfo(SCL_INFO* sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda)
{
	SCL_LD	*scl_ld = NULL;
	SCL_LN	*scl_ln = NULL;
	SCL_DAI	*scl_dai = NULL;

	ST_CHAR fcdaldName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdalnName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadaiName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadescName[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdadoiName	[MAX_IDENT_LEN + 1] = {0};

	strncpy (fcdaldName, sclfcda->ldInst, MAX_IDENT_LEN + 1);
	strncpy (fcdalnName, sclfcda->prefix, MAX_IDENT_LEN + 1);
	strncat (fcdalnName, sclfcda->lnClass, MAX_IDENT_LEN + 1 - strlen(fcdalnName));
	strncat (fcdalnName, sclfcda->lnInst,  MAX_IDENT_LEN + 1 - strlen(fcdalnName));

	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadaiName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadescName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadoiName, sclfcda->doName, MAX_IDENT_LEN + 1);
	}
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadaiName, _T("$"));
		strncat (fcdadaiName, sclfcda->daName, MAX_IDENT_LEN + 1 - strlen(fcdadaiName));
	}

	ReplaceDotToDollar(fcdadaiName);
	ConfigDescName(fcdadescName);
	ConfigDoiName(fcdadoiName);

	for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)sclap->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)sclap->ldHead, (DBL_LNK *)scl_ld))
	{
		if (0 == strcmp(fcdaldName, scl_ld->inst))
		{
			for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
			{
				ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
				//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
				//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
				//strncat (lnName, scl_ln->inst,  MAX_IDENT_LEN + 1 - strlen(lnName));
				scl_get_ln_name(scl_ln, lnName);

				//!!! -- lijunqing  2014-10-27
				//sclfcda->prefix == scl_ln->prefix and sclfcda->lnClass == scl_ln->lnClass and sclfcda->inst == scl_ln->inst
				if (0 == strcmp(fcdalnName, lnName))
				{
					ST_CHAR lnType [MAX_IDENT_LEN + 1] = {0};
					strncpy(lnType, scl_ln->lnType, MAX_IDENT_LEN + 1);

					//fcda type
					GetFCDAType(sclinfo, sclfcda, lnType);

					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
						scl_dai != NULL;
						scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
						//if (strcmp(scl_dai->flattened, fcdadaiName) == 0)
						//{//fcda value
						//	if (scl_dai->Val)
						//	{
						//		strncpy (sclfcda->value, scl_dai->Val, MAX_IDENT_LEN + 1);
						//	}
						//}

						if (0 == strcmp(scl_dai->flattened, fcdadescName))
						{//fcda desc dU
							if (scl_dai->Val)
							{
								strncpy (sclfcda->desc, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(sclfcda->desc);
							}
						}
						else if (0 == strcmp(scl_dai->flattened, fcdadoiName))
						{//fcda do desc
							if (scl_dai->Val)
							{
								strncpy(sclfcda->dodesc, scl_dai->Val, MAX_IDENT_LEN + 1);
							}
						}
					}

					if (scl_ln->desc)
					{//sclextref ln desc
						strncpy (sclfcda->lndesc, scl_ln->desc, MAX_IDENT_LEN + 1);
					}

					break;
				}
			}
			break;
		}
	}

	return SD_SUCCESS;
}

ST_RET CSclFileRead::LogFCDAInfo(SCL_INFO* sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda, CDvmData *pDvmData)
{
	SCL_LD	*scl_ld = NULL;
	SCL_LN	*scl_ln = NULL;
	SCL_DAI	*scl_dai = NULL;

	ST_CHAR fcdaldName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdalnName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadaiName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadescName[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdadoiName	[MAX_IDENT_LEN + 1] = {0};

	strncpy (fcdaldName, sclfcda->ldInst, MAX_IDENT_LEN + 1);
	strncpy (fcdalnName, sclfcda->prefix, MAX_IDENT_LEN + 1);
	strncat (fcdalnName, sclfcda->lnClass, MAX_IDENT_LEN + 1 - strlen(fcdalnName));
	strncat (fcdalnName, sclfcda->lnInst,  MAX_IDENT_LEN + 1 - strlen(fcdalnName));

	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadaiName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadescName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadoiName, sclfcda->doName, MAX_IDENT_LEN + 1);
	}
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadaiName, _T("$"));
		strncat (fcdadaiName, sclfcda->daName, MAX_IDENT_LEN + 1 - strlen(fcdadaiName));
	}

	ReplaceDotToDollar(fcdadaiName);
	ConfigDescName(fcdadescName);
	ConfigDoiName(fcdadoiName);
	int nLen = strlen(fcdadaiName);

	pDvmData->m_strID= sclfcda->prefix;
	pDvmData->m_strID += sclfcda->lnClass;
	pDvmData->m_strID += sclfcda->lnInst;

	if (*sclfcda->fc != 0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += sclfcda->fc;
	}

	if (*sclfcda->doName != 0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += sclfcda->doName;
	}

	if (*sclfcda->daName != 0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += sclfcda->daName;
	}

	for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)sclap->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)sclap->ldHead, (DBL_LNK *)scl_ld))
	{
		if (0 == strcmp(sclfcda->ldInst, scl_ld->inst))
		{
			for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
			{
				//ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
				//scl_get_ln_name(scl_ln, lnName);

				//!!! -- lijunqing  2014-10-27
				if ( (strcmp(sclfcda->prefix , scl_ln->prefix) == 0)
					&& (strcmp(sclfcda->lnClass, scl_ln->lnClass) == 0)
					&& (strcmp(sclfcda->lnInst, scl_ln->inst) == 0) )
					//if (0 == strcmp(fcdalnName, lnName))
				{
					ST_CHAR lnType [MAX_IDENT_LEN + 1] = {0};
					strncpy(lnType, scl_ln->lnType, MAX_IDENT_LEN + 1);
					GetFCDAType(sclinfo, sclfcda, lnType);
					pDvmData->m_strDataType=sclfcda->type;

					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
						scl_dai != NULL;
						scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
						if (strncmp(scl_dai->flattened, fcdadaiName, nLen) != 0)
						{
							continue;
						}

						if (strstr(scl_dai->flattened, "$dU") != NULL)
						{
							strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
							UTF8ToMultiByte(fcdaldName);
							pDvmData->m_strName = fcdaldName;
						}
						else if (strstr(scl_dai->flattened, "$min") != NULL)
						{
							strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
							UTF8ToMultiByte(fcdaldName);
							pDvmData->m_strMin = fcdaldName;
						}
						else if (strstr(scl_dai->flattened, "$max") != NULL)
						{
							strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
							UTF8ToMultiByte(fcdaldName);
							pDvmData->m_strMax = fcdaldName;
						}
						else if (strstr(scl_dai->flattened, "$units") != NULL)
						{
							strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
							UTF8ToMultiByte(fcdaldName);
							pDvmData->m_strUnit= fcdaldName;
						}
						else if (IsValueKey(scl_dai->flattened))
						{
							strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
							UTF8ToMultiByte(fcdaldName);
							pDvmData->m_strUnit= fcdaldName;
							CDvmValue *pNew = new CDvmValue();
							pNew->m_strValue = fcdaldName;
							pNew->m_strID = scl_dai->flattened;
							pDvmData->AddNewChild(pNew);
						}
// 						if (0 == strcmp(scl_dai->flattened, fcdadescName))
// 						{//fcda desc dU
// 							if (scl_dai->Val)
// 							{
// 								strncpy (sclfcda->desc, scl_dai->Val, MAX_IDENT_LEN + 1);
// 								UTF8ToMultiByte(sclfcda->desc);
// 							}
// 						}
// 						else if (0 == strcmp(scl_dai->flattened, fcdadoiName))
// 						{//fcda do desc
// 							if (scl_dai->Val)
// 							{
// 								strncpy(sclfcda->dodesc, scl_dai->Val, MAX_IDENT_LEN + 1);
// 							}
// 						}
					}

// 					if (scl_ln->desc)
// 					{//sclextref ln desc
// 						strncpy (sclfcda->lndesc, scl_ln->desc, MAX_IDENT_LEN + 1);
// 					}

					break;
				}
			}
			break;
		}
	}

	return SD_SUCCESS;
}

BOOL CSclFileRead::IsValueKey(const char *pszKey)
{
	if (strstr(pszKey, "$cVal") != NULL)
	{
		return TRUE;
	}

	if (strstr(pszKey, "$setVal") != NULL)
	{
		return TRUE;
	}

	if (strstr(pszKey, "$setMag") != NULL) 
	{
		return TRUE;
	}

	return FALSE;
}

//get fcda type
void CSclFileRead::GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, ST_CHAR *lntype)
{
	ST_CHAR	dotype		[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	datype		[MAX_IDENT_LEN + 1] = {0};

	ST_CHAR	fcdadodaName[MAX_IDENT_LEN + 1] = {0};

	//fcda doname is empty
	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadodaName, sclfcda->doName, strlen(sclfcda->doName) + 1);
	}

	//fcda daname is empty
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadodaName, _T("$"));
		strncat (fcdadodaName, sclfcda->daName, strlen(sclfcda->daName) + 1);
	}

	//find dotype from scl_lntype
	FindDoType(sclinfo, sclfcda, lntype, dotype, fcdadodaName);

	//find datype from scl_dotype
	if (strlen (sclfcda->doName))
	{
		FindDaType(sclinfo, sclfcda, dotype, datype, fcdadodaName);
	} 
	else
	{
		//find fcda do struct
		return;
	}

	//find final type from scl_datype
	if (strlen (sclfcda->daName))
	{
		FindFinalType(sclinfo, sclfcda, datype, fcdadodaName);
	} 
	else
	{
		//find fcda da struct
		return;
	}
	
	return ;
}

//find dotype from scl_lntype
void CSclFileRead::FindDoType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *lntype, char *dotype, char *fcdadodaName)
{
	SCL_LNTYPE	*scl_lntype = NULL;
	SCL_DO		*scl_do = NULL;

	for (scl_lntype = (SCL_LNTYPE *)list_find_last((DBL_LNK *)sclinfo->lnTypeHead);
		scl_lntype != NULL;
		scl_lntype = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)sclinfo->lnTypeHead, (DBL_LNK *)scl_lntype))
	{
		if (0 == strcmp(scl_lntype->id, lntype))
		{
			ST_CHAR doName[MAX_IDENT_LEN + 1] = {0};
			FindDelStr(fcdadodaName, doName);

			for (scl_do = (SCL_DO *)list_find_last((DBL_LNK *)scl_lntype->doHead);
				scl_do != NULL;
				scl_do = (SCL_DO *)list_find_prev((DBL_LNK *)scl_lntype->doHead, (DBL_LNK *)scl_do))
			{
				if (0 == strcmp(scl_do->name, doName))
				{
					strncpy (dotype, scl_do->type,  MAX_IDENT_LEN + 1);
					break;
				}	
			}
			break;
		}
	}
}

//find datype from scl_dotype
void CSclFileRead::FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName)
{
	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;

	//not find dotype
	if (strlen(dotype) <= 0)
	{
		if (strlen(sclfcda->type) <= 0)
		{
			strcpy (sclfcda->type, _T("Struct"));
		}
	}
	else
	{
		if (strlen(fcdadodaName) <= 0)
		{
			FindDaStruct(sclinfo, sclfcda, dotype);
		} 
		else
		{
			for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
				scl_dotype != NULL;
				scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
			{
				if (0 == strcmp(scl_dotype->id, dotype))
				{
					ST_CHAR daFstName[MAX_IDENT_LEN + 1] = {0};
					FindDelStr(fcdadodaName, daFstName);

					for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
						scl_da != NULL;
						scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
					{
						if (0 == strcmp(scl_da->name, daFstName))
						{
							if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
							{
								ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
								strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

								FindDaType(sclinfo, sclfcda, tdotype, datype, fcdadodaName);
							}
							else//da type
							{
								if (0 == strcmp(scl_da->bType, _T("Struct")))
								{
									strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);
								}
								else
								{
									strncpy(sclfcda->type, scl_da->bType, MAX_IDENT_LEN + 1);
								}
							}	
							break;
						}
					}
					break;
				}
			}
		}
	}
}

void CSclFileRead::FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype)
{
	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;
	
	//strncat(sclfcda->type, _T("<"), 2);

	for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
		scl_dotype != NULL;
		scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
	{
		if (0 == strcmp(scl_dotype->id, dotype))
		{
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
			{
				if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
				{
					ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
					strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

					FindDaStruct(sclinfo, sclfcda, tdotype);
				}
				else//da type
				{
					if (0 == strcmp(scl_da->bType, _T("Struct")))
					{
						ST_CHAR datype[MAX_IDENT_LEN + 1] = {0};
						strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);

						FindFinalStruct(sclinfo, sclfcda, datype);
					}
					else
					{
						strncat(sclfcda->type, scl_da->bType, strlen(scl_da->bType));
						strncat(sclfcda->type, _T(","), 2);
					}
				}	
			}
			break;
		}
	}

	//sclfcda->type[strlen(sclfcda->type) - 1] = _T('>');
}

//find final type from scl_datype
void CSclFileRead::FindFinalType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype, char *fcdadodaName)
{
	SCL_DATYPE	*scl_datype = NULL; 
	SCL_BDA		*scl_bda = NULL;

	ST_CHAR		tdatype[MAX_IDENT_LEN + 1] = {0};

	if (strlen(datype) <= 0)
	{
		if (strlen(sclfcda->type) <= 0)
		{
			strcpy (sclfcda->type, _T("Struct"));
		}
	}
	else
	{
		if (strlen(fcdadodaName) <= 0)
		{
			FindFinalStruct(sclinfo, sclfcda, datype);
		}
		else
		{
			for (scl_datype = (SCL_DATYPE *)list_find_last((DBL_LNK *)sclinfo->daTypeHead);
				scl_datype != NULL;
				scl_datype = (SCL_DATYPE *)list_find_prev((DBL_LNK *)sclinfo->daTypeHead, (DBL_LNK *)scl_datype))
			{
				if (0 == strcmp(scl_datype->id, datype))
				{
					ST_CHAR daFstName[MAX_IDENT_LEN + 1] = {0};
					FindDelStr(fcdadodaName, daFstName);

					for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
						scl_bda != NULL;
						scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
					{
						if (0 == strcmp(scl_bda->name, daFstName))
						{
							if (0 == strcmp(scl_bda->bType, _T("Struct")))
							{
								strncpy (tdatype, scl_bda->type, MAX_IDENT_LEN + 1);
							}
							else
							{
								strncpy(sclfcda->type, scl_bda->bType, MAX_IDENT_LEN + 1);
							}
							break;
						}
					}
					break;
				}
			}

			FindFinalType(sclinfo, sclfcda, tdatype, fcdadodaName);
		}	
	}
}

void CSclFileRead::FindFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype)
{
	SCL_DATYPE	*scl_datype = NULL; 
	SCL_BDA		*scl_bda = NULL;

	ST_CHAR		tdatype[MAX_IDENT_LEN + 1] = {0};

	strncat(sclfcda->type, _T("<"), 2);

	for (scl_datype = (SCL_DATYPE *)list_find_last((DBL_LNK *)sclinfo->daTypeHead);
		scl_datype != NULL;
		scl_datype = (SCL_DATYPE *)list_find_prev((DBL_LNK *)sclinfo->daTypeHead, (DBL_LNK *)scl_datype))
	{
		if (0 == strcmp(scl_datype->id, datype))
		{
			for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
				scl_bda != NULL;
				scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
			{
				if (0 == strcmp(scl_bda->bType, _T("Struct")))
				{
					strncpy (tdatype, scl_bda->type, MAX_IDENT_LEN + 1);

					FindFinalStruct(sclinfo, sclfcda, tdatype);
				}
				else
				{
					strncat(sclfcda->type, scl_bda->bType, strlen(scl_bda->bType));
					strncat(sclfcda->type, _T(","), 2);
				}
			}

			break;
		}
	}

	sclfcda->type[strlen(sclfcda->type) - 1] = _T('>');
}

// find extref ld/ln/do name from sclextref;
// sclextref->inAddr: ldname/lnname.doname, doname: ***.***.***,(dot number is 0,1,......);
void CSclFileRead::FindextrefName(SCL_EXTREF *sclextref, char *ldName, 
									char *lnName, char *doName)
{
	char *pch = NULL; 

	strncpy (ldName, sclextref->inAddr, MAX_IDENT_LEN + 1);

	for (pch = ldName; *pch; pch++)
	{
		if (*pch == _T('/'))
		{
			*pch++ = _T('\0');
			strcpy (lnName, pch);
			break;
		}
	}

	for (pch = lnName; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch++ = _T('\0');
			strcpy (doName, pch);
			break;
		}
	}

	for (pch = doName; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch++ = _T('\0');
			break;
		}
	}
}

//replace dot to dollar in string srcStr
void CSclFileRead::ReplaceDotToDollar(char *srcStr)
{
	for (; *srcStr; srcStr++)
	{
		if (*srcStr == _T('.'))
		{
			*srcStr = _T('$');
		}
	}
}

//if srcStr have dot, remove dot and the string behind dot, 
//and link dU at the end of srcStr
void CSclFileRead::ConfigDescName(char *srcStr)
{
	char *pch = srcStr;

	for (; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch = _T('$');
		}
	}
	strcat (srcStr, _T("$dU"));
}

//if srcStr have dot, replace the dot to \0, 
//and link desc at the end of srcStr
void CSclFileRead::ConfigDoiName(char *srcStr)
{
	char *pch = srcStr;

	for (; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch = 0;
		}
	}
	strcat (srcStr, _T("$desc"));
}

// find string before the first $/. form srcStr, remove the string and the first $/. from srcStr
// if find, return true, findStr = find string, srcStr = the string after $/.;
// else return false, findStr = srcStr, srcStr = {};
bool CSclFileRead::FindDelStr(char *srcStr, char *findStr)
{
	char *pch = srcStr;

	for (; *pch; pch++)
	{
		if ((*pch == _T('$')) || (*pch == _T('.')))
		{
			*pch++ = _T('\0');

			strcpy(findStr, srcStr);
			strcpy(srcStr, pch);

			return true;
		}
	}

	strcpy(findStr, srcStr);
	strcpy(srcStr, _T("\0"));
	return false;
}

bool CSclFileRead::UTF8ToMultiByte(char *srcStr)
{
	ST_INT iTextLen = 0;
	unsigned short wszGBK[256] = {0};

	memset(wszGBK, 0, 256);

	iTextLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, NULL,0); 
	memset(wszGBK, 0, iTextLen * 2 + 2); 
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, (LPWSTR)wszGBK, iTextLen); 

	iTextLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, srcStr, iTextLen, NULL, NULL); 

	return true;
}


void CSclFileRead::FindGSSVControl(SCL_INFO *sclinfo, CSclIed *pIed/*CString iedStr*/, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut)
{
	SCL_IED	*scl_ied = NULL;
	SCL_AP *scl_ap = NULL;
	SCL_LD *scl_ld = NULL;
	SCL_LN *scl_ln = NULL;

	scl_ied = pIed->GetRefIED();
	ASSERT (scl_ied != NULL);

// 	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
// 		scl_ied != NULL;
// 		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
//		if (0 == strcmp(pIed->m_strID.GetBuffer(), scl_ied->name))
		{
			for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
				scl_ap != NULL;
				scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
			{
				CString apName(scl_ap->name);
				if ((scl_ap->desc) && (strlen(scl_ap->desc) > 0))
				{
					apName = apName + _T("--") + scl_ap->desc;
				}

				for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
					scl_ld != NULL;
					scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
				{
					for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
						scl_ln != NULL;
						scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
					{
						ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
						//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
						//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
						//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
						scl_get_ln_name(scl_ln, lnName);

						//if (0 == strcmp(_strupr(_strdup(lnName)), _T("LLN0")))
						if (0 == stricmp(lnName, _T("LLN0")))
						{
							if (bGsOut)//ClickType_GOOSE_Outputs == m_iClickType)
							{
								FindGSOutControl(sclinfo, scl_ln, scl_ied->name, 
												apName.GetBuffer(), scl_ld->inst, lnName, pIed->GetGsOuts());
							} 
							/*else*/ 
							if (bSmvOut)//ClickType_SMV_Outputs == m_iClickType)
							{
								FindSVOutControl(sclinfo, scl_ln, scl_ied->name, 
												apName.GetBuffer(), scl_ld->inst, lnName, pIed->GetSmvOuts());
							} 
							/*else */
							if (bGsIn)//ClickType_GOOSE_Inputs == m_iClickType || ClickType_SMV_Inputs == m_iClickType)
							{
								SCL_NODE_PATH scl_path;
								_scl_init_node_path(scl_path, scl_ied, scl_ap, scl_ld, scl_ln);
								FindGSSVInputs(sclinfo, scl_ln, pIed->GetGsIns(), scl_path);
							} 											
					
							if (bSmvIn)//ClickType_GOOSE_Inputs == m_iClickType || ClickType_SMV_Inputs == m_iClickType)
							{
								SCL_NODE_PATH scl_path;
								_scl_init_node_path(scl_path, scl_ied, scl_ap, scl_ld, scl_ln);
								FindGSSVInputs(sclinfo, scl_ln, pIed->GetSmvIns(), scl_path);
							} 											

							break;
						}
					}
				}
			}
			//break;
		}
	}
}

void CSclFileRead::FindGSSVInputs(SCL_INFO *sclinfo, SCL_LN *sclln, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path)
{
	SCL_INPUTS		*scl_inputs = NULL;
	SCL_EXTREF		*scl_extref = NULL;

	std::list<CString>	list_ied;
	std::list<CString>	list_extref;

	for (scl_inputs = (SCL_INPUTS *)list_find_last((DBL_LNK *)sclln->inputsHead);
		scl_inputs != NULL;
		scl_inputs = (SCL_INPUTS *)list_find_prev((DBL_LNK *)sclln->inputsHead, (DBL_LNK *)scl_inputs))
	{
		for (scl_extref = (SCL_EXTREF *)list_find_last((DBL_LNK *)scl_inputs->extrefHead);
			scl_extref != NULL;
			scl_extref = (SCL_EXTREF *)list_find_prev((DBL_LNK *)scl_inputs->extrefHead, (DBL_LNK *)scl_extref))
		{
			if (strlen(scl_extref->domName) <= 0)
			{
				continue;
			}

			CString extrefname(_T(""));
			extrefname.Format(_T("%s%s/%s%s%s"), scl_extref->domName, 
				scl_extref->ldInst,	scl_extref->prefix, 
				scl_extref->lnClass, scl_extref->lnInst);
			if (strlen(scl_extref->doName))
			{
				extrefname = extrefname + _T(".") + CString(scl_extref->doName);
			}
			if (strlen(scl_extref->daName))
			{
				extrefname = extrefname + _T(".") + CString(scl_extref->daName);
			}
			list_extref.push_back(extrefname);

			if (list_ied.empty())
			{
				list_ied.push_back(CString(scl_extref->domName));
			}
			else
			{
				std::list<CString>::iterator iter = list_ied.begin();
				std::list<CString>::iterator iend = list_ied.end();
				for(; iter != iend; iter++)
				{
					if (*iter == CString(scl_extref->domName))
					{
						break;
					}
				}

				if (iter == iend)
				{
					list_ied.push_back(CString(scl_extref->domName));
				}
			}
		}
	}

	if (!list_ied.empty())
	{
		FindGSSVInControl(sclinfo, &list_ied, &list_extref, pCtrls, scl_path);
	}
}

void CSclFileRead::FindGSSVInControl(SCL_INFO *sclinfo, std::list<CString> *listied, 
									  std::list<CString> *listextref, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
		std::list<CString>::iterator iter = listied->begin();
		std::list<CString>::iterator iend = listied->end();
		for(; iter != iend; iter++)
		{
			if (*iter == CString(scl_ied->name))
			{
				break;
			}
		}
		if (iter == iend)
		{
			continue;
		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{
			CString apName(scl_ap->name);
			if ((scl_ap->desc) && (strlen(scl_ap->desc) > 0))
			{
				apName = apName + _T("--") + scl_ap->desc;
			}

			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					//if (0 != strcmp(_strupr(_strdup(lnName)), _T("LLN0")))
					if (0 != stricmp(lnName, _T("LLN0")))
					{
						continue;
					}

					//if (ClickType_GOOSE_Inputs == m_iClickType)
					if (scl_IsGsIns(pCtrls))
					{//GOOSE in
						FindGSINControl(sclinfo, scl_ln, scl_ied->name, scl_ied->desc, apName.GetBuffer(), 
										scl_ld->inst, lnName, listied, listextref, (CSclCtrlsGsIn*)pCtrls, scl_path);
					} 
					else  if (scl_IsSmvIns(pCtrls))
					{//sv in (ClickType_SMV_Inputs == m_iClickType)
						FindSVINControl(sclinfo, scl_ln, scl_ied->name, scl_ied->desc, apName.GetBuffer(), 
										scl_ld->inst, lnName, listied, listextref, (CSclCtrlsSmvIn*)pCtrls, scl_path);
					}
					break;
				}
			}
		}
	}
}

void CSclFileRead::FindGSINControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
									char *iedDesc, char *apName, char *ldName, char *lnName, 
									std::list<CString> *listied, std::list<CString> *listextref, CSclCtrlsGsIn *pGsIns
									, SCL_NODE_PATH &scl_path)
{
	SCL_GCB		*scl_gcb = NULL;
	SCL_DATASET	*scl_dataset = NULL;

	for (scl_gcb = (SCL_GCB *)list_find_last((DBL_LNK *)sclln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev((DBL_LNK *)sclln->gcbHead, (DBL_LNK *)scl_gcb))
	{
		if(scl_gcb->isGoose == SD_FALSE)
		{
			continue;
		}

// 		//去掉重复control
// 		CString dataset(_T(""));
// 		dataset.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);
// 		int count = m_LControl.GetItemCount();
// 		int i = 0;
// 		for (; i < count; i++)
// 		{
// 			if (m_LControl.GetItemText(i, 7) == dataset)
// 			{
// 				break;
// 			}
// 		}
// 		if (i < count)
// 		{
// 			continue;
// 		}

		if (pGsIns->IsExist(iedName, ldName, lnName, scl_gcb->datSet))
		{
			continue;
		}

		if (!IsOutGSSVHaveInGSSVChannel(sclln, scl_gcb->datSet, iedName, listextref))
		{
			continue;
		}
		
// 		CString countStr(_T(""));
// 		countStr.Format(_T("%d"), count);
		//m_LControl.InsertItem(count, countStr);
		CSclCtrlGsIn *pNew = new CSclCtrlGsIn();
		pGsIns->AddNewChild(pNew);

		CString iedStr(iedName);
		if (iedDesc && (strlen(iedDesc) > 0))
		{
			iedStr = iedStr + _T("--") + CString(iedDesc);
		}

		pNew->iedExtName = iedName;
		pNew->iedStr = iedStr;//m_LControl.SetItemText(count, 3, iedStr);
		pNew->apName = apName;//m_LControl.SetItemText(count, 4, apName);

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
			if((0 == strcmp(scl_gcb->datSet, scl_dataset->name))
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				//m_LControl.SetItemText(count, 5, scl_dataset->desc);
				pNew->scl_dataset_desc = scl_dataset->desc;
				break;
			}
		}


		//CString gocbref(_T(""));
		//gocbref.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->gocbref = scl_gcb->name;//.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->gocbref_path.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->m_strID = scl_gcb->name;
		//m_LControl.SetItemText(count, 6, gocbref);

		pNew->ldName = ldName;
		pNew->lnName = lnName;
		pNew->scl_datset = scl_gcb->datSet;
		pNew->scl_datset_path.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);
		//m_LControl.SetItemText(count, 7, dataset);

		//m_LControl.SetItemText(count, 8, scl_gcb->appID);//goID
		pNew->scl_gcb_APPID = scl_gcb->appID;

		ST_CHAR lnName2	[MAX_TYPE_LEN + 1] = {0};
		scl_get_ln_name(scl_path.scl_ln, lnName2);
		pNew->ldName_own = scl_path.scl_ld->inst;
		pNew->lnName_own = lnName2;
		//pNew->scl_datset_own = ;
		pNew->apName_own = scl_path.scl_ap->name;
		
		//CString confrev(_T(""));
		//confrev.Format(_T("%d"), scl_gcb->confRev);
		//m_LControl.SetItemText(count, 9, confrev);
		pNew->scl_gcb_confRev = scl_gcb->confRev;

		FindGSConnectAP(sclinfo, iedName, apName, ldName, scl_gcb->name, pNew);
	}
}

void CSclFileRead::FindSVINControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
									char *iedDesc, char *apName, char *ldName, char *lnName, 
									std::list<CString> *listied,  std::list<CString> *listextref, CSclCtrlsSmvIn *pSmvIns
									, SCL_NODE_PATH &scl_path)
{
	SCL_SVCB	*scl_svcb = NULL;
	SCL_DATASET *scl_dataset = NULL;

	for (scl_svcb = (SCL_SVCB *)list_find_last((DBL_LNK *)sclln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *)list_find_prev((DBL_LNK *)sclln->svcbHead, (DBL_LNK *)scl_svcb))
	{
		//去掉重复control
// 		CString dataset(_T(""));
// 		dataset.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_svcb->datSet);
// 		int count = m_LControl.GetItemCount();
// 	
// 		int i = 0;
// 		for (; i < count; i++)
// 		{
// 			if (m_LControl.GetItemText(i, 7) == dataset)
// 			{
// 				break;
// 			}
// 		}
// 		if (i < count)
// 		{
// 			continue;
// 		}

		if (pSmvIns->IsExist(iedName, ldName, lnName, scl_svcb->datSet))
		{
			continue;
		}

		if (!IsOutGSSVHaveInGSSVChannel(sclln, scl_svcb->datSet, iedName, listextref))
		{
			continue;
		}

		CSclCtrlSmvIn *pNew = new CSclCtrlSmvIn();
		pSmvIns->AddNewChild(pNew);

		CString iedStr(iedName);
		if ((iedDesc) && (strlen(iedDesc) > 0))
		{
			iedStr = iedStr + _T("--") + CString(iedDesc);
		}

		pNew->iedExtName = iedName;
		pNew->iedStr = iedStr;//m_LControl.SetItemText(count, 3, iedStr);
		pNew->apName = apName;//m_LControl.SetItemText(count, 4, apName);

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
			if((0 == strcmp(scl_svcb->datSet, scl_dataset->name))
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				//m_LControl.SetItemText(count, 5, scl_dataset->desc);
				pNew->scl_dataset_desc = scl_dataset->desc;
				break;
			}
		}

// 		CString smprate(_T(""));
// 		smprate.Format(_T("%d"), scl_svcb->smpRate);
// 		m_LControl.SetItemText(count, 6, smprate);
		pNew->scl_svcb_smpRate = scl_svcb->smpRate;
		pNew->scl_datset = scl_svcb->datSet;//dataset;
		pNew->ldName = ldName;
		pNew->lnName = lnName;
		//m_LControl.SetItemText(count, 7, dataset);

		pNew->scl_svcb_smvID = scl_svcb->smvID;
		pNew->m_strID = scl_svcb->smvID;
		//m_LControl.SetItemText(count, 8, scl_svcb->smvID);

// 		CString nofasdu(_T(""));
// 		nofasdu.Format(_T("%d"), scl_svcb->nofASDU);
// 		m_LControl.SetItemText(count, 9, nofasdu);
		pNew->scl_svcb_nofASDU = scl_svcb->nofASDU;

		pNew->scl_svcb_confRev = scl_svcb->confRev;

		ST_CHAR lnName2	[MAX_TYPE_LEN + 1] = {0};
		scl_get_ln_name(scl_path.scl_ln, lnName2);
		pNew->ldName_own = scl_path.scl_ld->inst;
		pNew->lnName_own = lnName2;
		//pNew->scl_datset_own = ;
		pNew->apName_own = scl_path.scl_ap->name;

		FindSVConnectAP(sclinfo, iedName, apName, ldName, scl_svcb->name, pNew);
	}
}

bool CSclFileRead::IsOutGSSVHaveInGSSVChannel(SCL_LN *sclln, char *dataset, char *iedName,
										  std::list<CString> *listextref)
{
	SCL_DATASET	*scl_dataset = NULL;
	SCL_FCDA	*scl_fcda = NULL;

	for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
	{
		if(0 != strcmp(dataset, scl_dataset->name))
		{
			continue;
		}

		for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
			scl_fcda != NULL;
			scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
		{
			CString fcdaname(_T(""));
			fcdaname.Format(_T("%s%s/%s%s%s"), iedName, 
							scl_fcda->ldInst, scl_fcda->prefix, 
							scl_fcda->lnClass, scl_fcda->lnInst);
			if (strlen(scl_fcda->doName))
			{
				fcdaname = fcdaname + _T(".") + CString(scl_fcda->doName);
			}
			if (strlen(scl_fcda->daName))
			{
				fcdaname = fcdaname + _T(".") + CString(scl_fcda->daName);
			}

			std::list<CString>::iterator iter = listextref->begin();
			std::list<CString>::iterator iend = listextref->end();
			for(; iter != iend; iter++)
			{
				if (*iter == fcdaname)
				{
					break;
				}
			}

			if (iter != iend)
			{
				return true;
			}
		}
	}

	return false;
}

void CSclFileRead::FindGSOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
									char *apName, char *ldName, char *lnName, CSclCtrlsGsOut *pGsOuts)
{
	SCL_GCB		*scl_gcb = NULL;
	SCL_DATASET	*scl_dataset = NULL;

	for (scl_gcb = (SCL_GCB *)list_find_last((DBL_LNK *)sclln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev((DBL_LNK *)sclln->gcbHead, (DBL_LNK *)scl_gcb))
	{
		if (SD_FALSE == scl_gcb->isGoose)
		{
			continue;
		}

// 		int count = m_LControl.GetItemCount();
// 		CString countStr(_T(""));
// 		countStr.Format(_T("%d"), count);

		//m_LControl.InsertItem(count, countStr);
		CSclCtrlGsOut *pNew = new CSclCtrlGsOut();
		pGsOuts->AddNewChild(pNew);

		//m_LControl.SetItemText(count, 3, apName);
		pNew->apName = apName;

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
			if ((0 == strcmp(scl_dataset->name, scl_gcb->datSet)) 
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				//m_LControl.SetItemText(count, 4, scl_dataset->desc);
				pNew->scl_dataset_desc = scl_dataset->desc;

				break;
			}
		}

// 		CString gocbref(_T(""));
// 		gocbref.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
// 		m_LControl.SetItemText(count, 5, gocbref);
		pNew->gocbref = scl_gcb->name;
		pNew->gocbref_path.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->m_strID = scl_gcb->name;

// 		CString dataset(_T(""));
// 		dataset.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);
// 		m_LControl.SetItemText(count, 6, dataset);
		pNew->ldName = ldName;
		pNew->lnName = lnName;
		pNew->scl_datset = scl_gcb->datSet;
		pNew->scl_datset_path.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);

		//m_LControl.SetItemText(count, 7, scl_gcb->appID);//goID
		pNew->scl_gcb_APPID = scl_gcb->appID;

// 		CString confrev(_T(""));
// 		confrev.Format(_T("%d"), scl_gcb->confRev);
// 		m_LControl.SetItemText(count, 8, confrev);
		pNew->scl_gcb_confRev = scl_gcb->confRev;

		FindGSConnectAP(sclinfo, iedName, apName, ldName, scl_gcb->name, pNew);
	}

}

void CSclFileRead::FindGSConnectAP(SCL_INFO *sclinfo, char *iedName, char *apName, 
								   char *ldName, char *gcbName, CSclCtrlGs *pGs)
{
	SCL_SUBNET	*scl_subnet = NULL;
	SCL_CAP		*scl_cap = NULL;
	SCL_GSE		*scl_gse = NULL;

	int ipos = 0;
	CString apStr(apName);
	if ((ipos = apStr.Find(_T("--"))) >= 0)
	{
		apStr = apStr.Left(ipos);
	}

	for (scl_subnet = (SCL_SUBNET *)list_find_last((DBL_LNK *)sclinfo->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *)list_find_prev((DBL_LNK *)sclinfo->subnetHead, (DBL_LNK *)scl_subnet))
	{
		for (scl_cap = (SCL_CAP *)list_find_last((DBL_LNK *)scl_subnet->capHead);
			scl_cap != NULL;
			scl_cap = (SCL_CAP *)list_find_prev((DBL_LNK *)scl_subnet->capHead, (DBL_LNK *)scl_cap))
		{
			if (0 != (strcmp(iedName, scl_cap->iedName)) 
				|| (0 != strcmp(apStr, scl_cap->apName)))
			{
				continue;
			}

			for (scl_gse = (SCL_GSE *)list_find_last((DBL_LNK *)scl_cap->gseHead);
				scl_gse != NULL;
				scl_gse = (SCL_GSE *)list_find_prev((DBL_LNK *)scl_cap->gseHead, (DBL_LNK *)scl_gse))
			{
				if (0 != (strcmp(ldName, scl_gse->ldInst)) 
					|| (0 != strcmp(gcbName, scl_gse->cbName)))
				{
					continue;
				}

				//m_LControl.SetItemText(nItem, 1, scl_gse->APPID);//appid
				pGs->scl_gse_APPID = scl_gse->APPID;


// 				CString mac(_T(""));
// 				unsigned char tmpmac[6] = {0};
// 				memcpy(tmpmac, scl_gse->MAC, 6);
// 				for(int i = 0; i < 6; i++)
// 				{
// 					CString tmp(_T(""));
// 					if(tmpmac[i] < 16)
// 						tmp.Format("0%x", tmpmac[i]);
// 					else
// 						tmp.Format("%x", tmpmac[i]);
// 					mac += tmp;
// 				}
				//m_LControl.SetItemText(nItem, 2, mac);
				scl_SetMac(pGs->strMac, (unsigned char*)scl_gse->MAC);
				
				//CString vlanpri(_T(""));
				//vlanpri.Format(_T("%d"), scl_gse->VLANPRI);
				pGs->scl_gse_VLANPRI = scl_gse->VLANPRI;
				
				//CString minTime(_T(""));
				//minTime.Format(_T("%d"), scl_gse->MinTime);
				pGs->scl_gse_MinTime = scl_gse->MinTime;

				//CString maxTime(_T(""));
				//maxTime.Format(_T("%d"), scl_gse->MaxTime);
				pGs->scl_gse_MaxTime = scl_gse->MaxTime;

				pGs->scl_gse_VLANID = scl_gse->VLANID;//	m_LControl.SetItemText(nItem, 9, scl_gse->VLANID);//vlanid

// 				if (ClickType_GOOSE_Outputs == m_iClickType)
// 				{//GOOSE Out
// 					m_LControl.SetItemText(nItem, 9, scl_gse->VLANID);//vlanid
// 					m_LControl.SetItemText(nItem, 10, vlanpri);
// 					m_LControl.SetItemText(nItem, 11, minTime);
// 					m_LControl.SetItemText(nItem, 12, maxTime);
// 				} 
// 				else
// 				{//GOOSE In m_iClickType == 1
// 					m_LControl.SetItemText(nItem, 10, scl_gse->VLANID);//vlanid
// 					m_LControl.SetItemText(nItem, 11, vlanpri);
// 					m_LControl.SetItemText(nItem, 12, minTime);
// 					m_LControl.SetItemText(nItem, 13, maxTime);
// 				}

				return;
			}
		}
	}
}

void CSclFileRead::FindSVOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, char *iedName, 
									char *apName, char *ldName, char *lnName, CSclCtrlsSmvOut *pSmvOuts)
{
	SCL_SVCB	*scl_svcb = NULL;
	SCL_DATASET *scl_dataset = NULL;

	for (scl_svcb = (SCL_SVCB *)list_find_last((DBL_LNK *)sclln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *)list_find_prev((DBL_LNK *)sclln->svcbHead, (DBL_LNK *)scl_svcb))
	{
// 		int count = m_LControl.GetItemCount();
// 		CString countStr(_T(""));
// 		countStr.Format(_T("%d"), count);

		CSclCtrlSmvOut *pNew = new CSclCtrlSmvOut();
		pSmvOuts->AddNewChild(pNew);

		//m_LControl.InsertItem(count, countStr);

		pNew->apName = apName;//m_LControl.SetItemText(count, 3, apName);

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
			if ((0 == strcmp(scl_dataset->name, scl_svcb->datSet)) 
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				pNew->scl_dataset_desc = scl_dataset->desc;//m_LControl.SetItemText(count, 4, scl_dataset->desc);

				break;
			}
		}

		pNew->scl_svcb_smpRate = scl_svcb->smpRate;
// 		CString smprate(_T(""));
// 		smprate.Format(_T("%d"), scl_svcb->smpRate);
// 		m_LControl.SetItemText(count, 5, smprate);
		
		//CString dataset(_T(""));
		pNew->ldName = ldName;
		pNew->lnName = lnName;
		pNew->scl_datset = scl_svcb->datSet;
		pNew->scl_datset_path.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_svcb->datSet);
		//m_LControl.SetItemText(count, 6, dataset);
		
		pNew->scl_svcb_smvID =  scl_svcb->smvID;
		pNew->m_strID = scl_svcb->smvID;

		pNew->scl_svcb_nofASDU = scl_svcb->nofASDU;
		//CString nofasdu(_T(""));
		//nofasdu.Format(_T("%d"), scl_svcb->nofASDU);	
		//m_LControl.SetItemText(count, 8, nofasdu);
		pNew->scl_svcb_confRev = scl_svcb->confRev;

		FindSVConnectAP(sclinfo, iedName, apName, ldName, scl_svcb->name, pNew);
	}

}

void CSclFileRead::FindSVConnectAP(SCL_INFO *sclinfo, char *iedName, char *apName, 
								   char *ldName, char *svcbName, CSclCtrlSmv *pSmv)
{
	SCL_SUBNET	*scl_subnet = NULL;
	SCL_CAP		*scl_cap = NULL;
	SCL_SMV		*scl_smv = NULL;

	int ipos = 0;
	CString apStr(apName);
	if ((ipos = apStr.Find(_T("--"))) >= 0)
	{
		apStr = apStr.Left(ipos);
	}

	for (scl_subnet = (SCL_SUBNET *)list_find_last((DBL_LNK *)sclinfo->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *)list_find_prev((DBL_LNK *)sclinfo->subnetHead, (DBL_LNK *)scl_subnet))
	{
		for (scl_cap = (SCL_CAP *)list_find_last((DBL_LNK *)scl_subnet->capHead);
			scl_cap != NULL;
			scl_cap = (SCL_CAP *)list_find_prev((DBL_LNK *)scl_subnet->capHead, (DBL_LNK *)scl_cap))
		{
			if (0 != (strcmp(iedName, scl_cap->iedName)) 
				|| (0 != strcmp(apStr, scl_cap->apName)))
			{
				continue;
			}

			for (scl_smv = (SCL_SMV *)list_find_last((DBL_LNK *)scl_cap->smvHead);
				scl_smv != NULL;
				scl_smv = (SCL_SMV *)list_find_prev((DBL_LNK *)scl_cap->smvHead, (DBL_LNK *)scl_smv))
			{
				if (0 != (strcmp(ldName, scl_smv->ldInst)) 
					|| (0 != strcmp(svcbName, scl_smv->cbName)))
				{
					continue;
				}

				//if item have been checked or not
// 				int count = m_LSelectControl.GetItemCount();
// 				for (int i = 0; i < count; i++)
// 				{
// 					if (m_LSelectControl.GetItemText(i, 1) == CString(scl_smv->APPID))
// 					{
// 						m_LControl.SetCheck(nItem, TRUE);
// 
// 						break;
// 					}
// 				}

// 				CString mac(_T(""));
// 				unsigned char tmpmac[6] = {0};
// 				memcpy(tmpmac, scl_smv->MAC, 6);
// 				for(int i = 0; i < 6; i++)
// 				{
// 					CString tmp(_T(""));
// 					if(tmpmac[i] < 16)
// 						tmp.Format("0%x", tmpmac[i]);
// 					else
// 						tmp.Format("%x", tmpmac[i]);
// 					mac += tmp;
// 				}			

				scl_SetMac(pSmv->strMac, (unsigned char *)scl_smv->MAC);

				pSmv->scl_smv_VLANPRI = scl_smv->VLANPRI;
				//CString vlanpri(_T(""));
				//vlanpri.Format(_T("%d"), scl_smv->VLANPRI);

// 				int i = 0;
// 				for (; i < nItem; i++)
// 				{
// 					CString oldAppID = m_LControl.GetItemText(i, 1);
// 					if (oldAppID == CString(scl_smv->APPID))
// 					{
// 						break;
// 					}
// 				}
// 				if (i < nItem)
// 				{
// 					m_LControl.DeleteItem(nItem);	//已插入的不显示
// 				} 
// 				else
				{
						pSmv->scl_smv_APPID = scl_smv->APPID;//m_LControl.SetItemText(nItem, 1, scl_smv->APPID);
						//pSmv->mac = mac;//m_LControl.SetItemText(nItem, 2, mac);
						pSmv->scl_smv_VLANID = scl_smv->VLANID; //m_LControl.SetItemText(nItem, 9, scl_smv->VLANID);//vlanid
						//pSmv->vlanpri = vlanpri;//m_LControl.SetItemText(nItem, 10, vlanpri);
// 				
// 					if (ClickType_SMV_Outputs == m_iClickType)
// 					{//sv out
// 						m_LControl.SetItemText(nItem, 1, scl_smv->APPID);
// 						m_LControl.SetItemText(nItem, 2, mac);
// 						m_LControl.SetItemText(nItem, 9, scl_smv->VLANID);//vlanid
// 						m_LControl.SetItemText(nItem, 10, vlanpri);
// 					}
// 					else
// 					{//sv in m_iClickType == ClickType_SMV_Inputs
// 						m_LControl.SetItemText(nItem, 1, scl_smv->APPID);
// 						m_LControl.SetItemText(nItem, 2, mac);
// 						m_LControl.SetItemText(nItem, 10, scl_smv->VLANID);//vlanid
// 						m_LControl.SetItemText(nItem, 11, vlanpri);
// 					}
				}

				return;
			}
		}
	}
}


void CSclFileRead::FindGSSVOutChannelInfo(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;
	CSclIed *pIed = scl_GetIed(pCtrlBase);

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
		if (pIed->m_strID != scl_ied->name)
		{
			continue;
		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{
			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				ST_CHAR domName[MAX_TYPE_LEN + 1] = {0};
				strncpy (domName, scl_ied->name, MAX_IDENT_LEN + 1);
				strncat (domName, scl_ld->inst, MAX_IDENT_LEN + 1 - strlen(domName));
				strncat (domName, _T("//"), 1);
				
				//??????????????
				if (pCtrlBase->ldName != scl_ld->inst)// != strncmp(domName, dataSet.GetBuffer(), strlen(domName)))
				{
					continue;
				}

				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					//????????????
					if (pCtrlBase->lnName != lnName)
					{
						continue;
					}

					FindOutChannel(scl_ln, scl_ied->name, pCtrlBase);
				}

				return;
			}
		}
	}
}

void CSclFileRead::FindOutChannel(SCL_LN *sclln, char *iedName, CSclCtrlBase *pCtrlBase)
{
	SCL_DATASET *scl_dataset = NULL;
	SCL_FCDA	*scl_fcda = NULL;

	for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
	{
		//int dsnLen = strlen(scl_dataset->name);
		//int dsLen = dataSet.GetLength();
		//CString dsStr = dataSet.Mid(dsLen - dsnLen);
		if (pCtrlBase->scl_datset != scl_dataset->name)//strncmp(scl_dataset->name, dsStr.GetBuffer(), dsnLen))
		{
			continue;
		}

		for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
			scl_fcda != NULL;
			scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
		{
			CString fcdaName(_T(""));
			fcdaName.Format(_T("%s%s/%s%s%s"), iedName, scl_fcda->ldInst, scl_fcda->prefix, 
							scl_fcda->lnClass, scl_fcda->lnInst);
			if (strlen(scl_fcda->doName))
			{
				fcdaName = fcdaName + _T(".") + CString(scl_fcda->doName);
			}
			if (strlen(scl_fcda->daName))
			{
				fcdaName = fcdaName + _T(".") + CString(scl_fcda->daName);
			}

// 			int count = m_LChannel.GetItemCount();
// 			CString countStr(_T(""));
// 			countStr.Format(_T("%d"), count);
// 			m_LChannel.InsertItem(count, countStr);
			CSclChBase *pCh = pCtrlBase->CreateNewCh();
			
			//if (ClickType_GOOSE_Outputs == m_iClickType)
			if (scl_IsGsOutCh(pCh))
			{//GOOSE out
				CSclChGsOut *pNew = (CSclChGsOut*)pCh;//new CSclChGsOut();
				pNew->fcda_lndesc = scl_fcda->lndesc;
				pNew->fcda_dodesc = scl_fcda->dodesc;
				pNew->fcda_desc =  scl_fcda->desc;
				pNew->fcda_type = scl_fcda->type;
				pNew->fcdaName = fcdaName;

#ifdef DEBUG
				pNew->m_strName = fcdaName;
				pNew->m_strID = scl_fcda->lndesc;
#endif
			} 
			else  if (scl_IsSmvOutCh(pCh))
			{//SV out (ClickType_SMV_Outputs == m_iClickType)
				CSclChSmvOut *pNew = (CSclChSmvOut*)pCh;//new CSclChSmvOut();
				pNew->fcda_lndesc = scl_fcda->lndesc;
				pNew->fcda_dodesc =  scl_fcda->dodesc;
				pNew->fcda_desc = scl_fcda->desc;
				pNew->fcdaName =  fcdaName;

#ifdef DEBUG
				pNew->m_strName = fcdaName;
				pNew->m_strID = scl_fcda->lndesc;
#endif
			}
		}

		return;
	}
}

void CSclFileRead::FindGSSVInChannelInfo(SCL_INFO *sclinfo, /*CString dataset,*/ CSclCtrlBase *pCtrlBase)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;
	SCL_INPUTS	*scl_inputs = NULL;
	SCL_EXTREF	*scl_extref = NULL;

	CSclIed *pIed = scl_GetIed(pCtrlBase);
	std::list<EXTREFINFO>	list_extref;

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
		if (pIed->m_strID != scl_ied->name)// != strcmp(iedStr.GetBuffer(), scl_ied->name))
		{
			continue;
		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{
			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					//if (0 == strcmp(_strupr(_strdup(lnName)), _T("LLN0")))
					if (0 == stricmp(lnName, _T("LLN0")))
					{
						for (scl_inputs = (SCL_INPUTS *)list_find_last((DBL_LNK *)scl_ln->inputsHead);
							scl_inputs != NULL;
							scl_inputs = (SCL_INPUTS *)list_find_prev((DBL_LNK *)scl_ln->inputsHead, (DBL_LNK *)scl_inputs))
						{
							for (scl_extref = (SCL_EXTREF *)list_find_last((DBL_LNK *)scl_inputs->extrefHead);
								scl_extref != NULL;
								scl_extref = (SCL_EXTREF *)list_find_prev((DBL_LNK *)scl_inputs->extrefHead, (DBL_LNK *)scl_extref))
							{
								char domName[MAX_TYPE_LEN + 1] = {0};
								strncpy(domName, scl_extref->domName, MAX_IDENT_LEN + 1);
								strncat(domName, scl_extref->ldInst, MAX_IDENT_LEN + 1 - strlen(domName));

								//??????????if (0 == strncmp(domName, dataset.GetBuffer(), strlen(scl_extref->domName)))
								//if (pCtrlBase->ldName == scl_extref->ldInst)
								if (pCtrlBase->ldName == scl_extref->ldInst)
								{
										CString extrefname(_T(""));
									extrefname.Format(_T("%s%s/%s%s%s"), scl_extref->domName, 
										scl_extref->ldInst,	scl_extref->prefix, 
										scl_extref->lnClass, scl_extref->lnInst);

									if (strlen(scl_extref->doName))
									{
										extrefname = extrefname + _T(".") + CString(scl_extref->doName);
									}
									if (strlen(scl_extref->daName))
									{
										extrefname = extrefname + _T(".") + CString(scl_extref->daName);
									}

									EXTREFINFO tmpextref;
									tmpextref.inPath = CString(scl_extref->inAddr);
									tmpextref.inLNDesc = CString(scl_extref->lndesc);
									tmpextref.inDODesc = CString(scl_extref->dodesc);
									tmpextref.inDADesc = CString(scl_extref->desc);
									tmpextref.outPath = extrefname;

									list_extref.push_back(tmpextref);
								}
							}
						}

						break;
					}
				}
			}
		}

		break;
	}

	if (!list_extref.empty())
	{
		FindInChannel(sclinfo, pCtrlBase, &list_extref);
	}
}

void CSclFileRead::FindInChannel(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase, 
								  std::list<EXTREFINFO> *listextref)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;
	SCL_DATASET *scl_dataset = NULL;
	SCL_FCDA	*scl_fcda = NULL;

	CSclIed *pIed = scl_GetIed(pCtrlBase);
	ASSERT (pIed != NULL);
	scl_ied = pIed->GetRefIED();
	CString strInRefIedStr = pCtrlBase->GetInIedExtName();

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
		if (strInRefIedStr != scl_ied->name)//dataSet.Find(scl_ied->name) < 0)
		{
			continue;
		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{
			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				ST_CHAR domName[MAX_TYPE_LEN + 1] = {0};
				strncpy (domName, scl_ied->name, MAX_IDENT_LEN + 1);
				strncat (domName, scl_ld->inst, MAX_IDENT_LEN + 1 - strlen(domName));
				strncat (domName, _T("//"), 1);
				
				///?????????????????????????///???
				//if (pCtrlBase->ldName != scl_ld->inst)// != strncmp(domName, dataSet.GetBuffer(), strlen(domName)))
				if (pCtrlBase->ldName != scl_ld->inst)// != strncmp(domName, dataSet.GetBuffer(), strlen(domName)))
				{
					continue;
				}

				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					if (pCtrlBase->lnName != lnName)//dataSet.Find(lnName) < 0)
					{
						continue;
					}

					for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)scl_ln->datasetHead);
						scl_dataset != NULL;
						scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)scl_ln->datasetHead, (DBL_LNK *)scl_dataset))
					{
						//int dsnLen = strlen(scl_dataset->name);
						//int dsLen = dataSet.GetLength();
						//CString dsStr = dataSet.Mid(dsLen - dsnLen);
						if (pCtrlBase->scl_datset != scl_dataset->name)// 0 != strncmp(scl_dataset->name, dsStr.GetBuffer(), dsnLen))
						{
							continue;
						}

						std::list<EXTREFINFO>::iterator iter = listextref->begin();
						std::list<EXTREFINFO>::iterator iend = listextref->end();
						for(; iter != iend; iter++)
						{
							int outcount = 0;

							for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
								scl_fcda != NULL;
								scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
							{
								CString fcdaName(_T(""));
								fcdaName.Format(_T("%s%s/%s%s%s"), scl_ied->name, scl_fcda->ldInst, 
									scl_fcda->prefix, scl_fcda->lnClass, scl_fcda->lnInst);

								if (strlen(scl_fcda->doName))
								{
									fcdaName = fcdaName + _T(".") + CString(scl_fcda->doName);
								}
								if (strlen(scl_fcda->daName))
								{
									fcdaName = fcdaName + _T(".") + CString(scl_fcda->daName);
								}

								if ((*iter).outPath == fcdaName)
								{
// 									int count = m_LChannel.GetItemCount();
// 									m_LChannel.InsertItem(count, _T(""));
// 
									CSclChBase *pCh = pCtrlBase->CreateNewCh();

									//if (ClickType_GOOSE_Inputs == m_iClickType)
									if (scl_IsGsInCh(pCh))
									{//GS in
										CSclChGsIn *pNew = (CSclChGsIn*)pCh;//new CSclChGsIn();
										pNew->fcda_map = scl_fcda->map;
										pNew->fcda_type = scl_fcda->type;
										pNew->inLNDesc =  (*iter).inLNDesc;
										pNew->fcda_lndesc =  scl_fcda->lndesc;
										pNew->inDODesc = (*iter).inDODesc;
										pNew->fcda_dodesc =  scl_fcda->dodesc;
										pNew->inDADesc =  (*iter).inDADesc;
										pNew->fcda_desc =  scl_fcda->desc;
										pNew->inIndex =  pCtrlBase->GetCount()-1;
										pNew->outIndex = outcount;
										pNew->inPath=  (*iter).inPath;
										pNew->outPath =  (*iter).outPath;	

#ifdef DEBUG
										pNew->m_strName = (*iter).inPath;
										pNew->m_strID = (*iter).outPath;
#endif
									}
									else  if (scl_IsSmvInCh(pCh))
									{//SV in (ClickType_SMV_Inputs == m_iClickType)
										CSclChSmvIn *pNew = (CSclChSmvIn*)pCh;//new CSclChSmvIn();
										pNew->inLNDesc = (*iter).inLNDesc;
										pNew->fcda_lndesc =  scl_fcda->lndesc;
										pNew->inDODesc =  (*iter).inDODesc;
										pNew->fcda_dodesc =  scl_fcda->dodesc;
										pNew->inDADesc =  (*iter).inDADesc;
										pNew->fcda_desc =  scl_fcda->desc;
										pNew->inIndex =  pCtrlBase->GetCount()-1;
										pNew->outIndex =  outcount;
										pNew->inPath =  (*iter).inPath;
										pNew->outPath =  (*iter).outPath;

#ifdef DEBUG
										pNew->m_strName = (*iter).inPath;
										pNew->m_strID = (*iter).outPath;
#endif
									}
								}

								outcount++;
								if (pCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)
								{
									((CSclCtrlGsIn*)pCtrlBase)->m_nChnRefCount = outcount;
								}
								else if (pCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN)
								{
									((CSclCtrlSmvIn*)pCtrlBase)->m_nChnRefCount = outcount;
								}
							}	
						}

						break;
					}
				}

				break;
			}
		}
	}
}

void CSclFileRead::ReadIed_Ctrls(CSclIed *pIed, CSclCtrls *pCtrls)
{
	FindGSSVControl(pCtrls);

	if (pCtrls->GetCount() == 0)
	{
		if (m_pOwnerWnd != NULL)
		{
			m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pCtrls, (WPARAM)SCLFILE_READ_DELCTRLS);
		}
	}
}

void CSclFileRead::ReadIed(CSclIed *pIed)
{
	if (pIed->HasGsIns())
	{
		ReadIed_Ctrls(pIed, pIed->GetGsIns());	
	}

	if (pIed->HasGsOuts())
	{
		ReadIed_Ctrls(pIed, pIed->GetGsOuts());
	}

	if (pIed->HasSmvIns())
	{
		ReadIed_Ctrls(pIed, pIed->GetSmvIns());
	}

	if (pIed->HasSmvOuts())
	{
		ReadIed_Ctrls(pIed, pIed->GetSmvOuts());
	}


}


