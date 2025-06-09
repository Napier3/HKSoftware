#include "SclVirLoopCheckTool.h"
#include "../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"

CSclVirLoopCheckTool::CSclVirLoopCheckTool(void)
{
	m_pVirtualLoopResults = NULL;
	m_pVirLoopChecks = NULL;
	m_pStdSclStation = NULL;
	m_pStartCheckThread = NULL;
	m_BeCheckFinished = TRUE;
}

CSclVirLoopCheckTool::~CSclVirLoopCheckTool(void)
{
}

BOOL CSclVirLoopCheckTool::InitVirTermConfigs(const CString &strSMVVirTermCfg,const CString &strGooseVirTermCfg
											  ,const CString &strSGCCFilePath)
{
	m_oSMVKeyDB.OpenKeyDbFile(strSMVVirTermCfg);
	m_oGSKeyDB.OpenKeyDbFile(strGooseVirTermCfg);

	BOOL bRet = TRUE;

	if (!m_oTemplateFile1396.OpenTemplateFile1396(strSGCCFilePath))
	{
		bRet = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("打开配置文件(%s)失败.")*/g_sLangTxt_configurationfile.GetString(),strSGCCFilePath.GetString());
	}

	return bRet;
}

UINT CSclVirLoopCheckTool::StartVirCheckThread(LPVOID pParam)
{
	CSclVirLoopCheckTool *pVirCheckObject = (CSclVirLoopCheckTool *)pParam;
	return pVirCheckObject->StartCheck();
}

void CSclVirLoopCheckTool::FreeStartVirCheckThread()
{
#ifdef _PSX_IDE_QT_
	if (m_pStartCheckThread != NULL)
	{
		m_pStartCheckThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pStartCheckThread->wait();
		m_pStartCheckThread = NULL;
	}
#endif
}

int CSclVirLoopCheckTool::StartVirCheckFromThread(CSclStation *pStdSclStation,CVirLoopChecks *pVirLoopChecks,CResultsRec *pVirLoopResults)
{
	m_pStdSclStation = pStdSclStation;
	m_pVirLoopChecks = pVirLoopChecks;
	m_pVirtualLoopResults = pVirLoopResults;

#ifdef _PSX_IDE_QT_
	FreeStartVirCheckThread();
	m_BeCheckFinished = FALSE;
	m_pStartCheckThread = new CWinThread(StartVirCheckThread, this);
	m_pStartCheckThread->m_bAutoDelete = FALSE;
	m_pStartCheckThread->ResumeThread();
#else
	m_pStartCheckThread = AfxBeginThread(StartVirCheckThread, this); //启动线程 
	m_pStartCheckThread->m_bAutoDelete = TRUE;
#endif

	return 1;
}

int CSclVirLoopCheckTool::StartVirCheckNormal(CSclStation *pStdSclStation,CVirLoopChecks *pVirLoopChecks,CResultsRec *pVirLoopResults)
{
	m_pStdSclStation = pStdSclStation;
	m_pVirLoopChecks = pVirLoopChecks;
	m_pVirtualLoopResults = pVirLoopResults;
	return StartCheck();
}

BOOL CSclVirLoopCheckTool::StartCheck()
{

	if (m_pStdSclStation->GetCount()<=0)
	{
		return FALSE;
	}

	POS iedPos = m_pStdSclStation->GetHeadPosition();
	POS ctrlsPos = NULL;
	POS ctrlPos = NULL;
	CExBaseList *pIedDev = NULL;
	CExBaseList *pIedCtrls = NULL;
	CSclIed *pSclIed = NULL;

	CString strErrorIedPos;

	m_mapAppID.clear();
	m_mapSMVID.clear();
	m_mapGOOSEID.clear();

	while(iedPos!=NULL)
	{
		pIedDev = (CExBaseList *)m_pStdSclStation->GetNext(iedPos);

		if (pIedDev->GetClassID() != SCLIECCLASSID_IED)
			continue;

		pSclIed = (CSclIed *)pIedDev;

		strErrorIedPos.Format("Ied: name=(%s) desc=(",pSclIed->m_strID.GetString());
		strErrorIedPos += pSclIed->m_strName;
		strErrorIedPos += ") type=(";
		strErrorIedPos += pSclIed->m_strModel;
		strErrorIedPos += ") manufacturer=(";
		strErrorIedPos += pSclIed->m_strManufacturer;
		strErrorIedPos += ").";

		ctrlsPos = pSclIed->GetHeadPosition();

		while(ctrlsPos!=NULL)
		{
			pIedCtrls = (CExBaseList *)pSclIed->GetNext(ctrlsPos);
			ctrlPos = pIedCtrls->GetHeadPosition();

			if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_SMV_OUT)
			{
				while(ctrlPos!=NULL)
				{
					CheckSmvOutVirLoop((CSclCtrlSmvOut *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,m_pVirLoopChecks);
				}
			} 
			else if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_SMV_IN)
			{
				while(ctrlPos!=NULL)
				{
					CheckSmvInVirLoop((CSclCtrlSmvIn *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,m_pVirLoopChecks);
				}
			}
			else if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_GS_OUT)
			{
				while(ctrlPos!=NULL)
				{
					CheckGsOutVirLoop((CSclCtrlGsOut *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,m_pVirLoopChecks);
				}
			}
			else if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_GS_IN)
			{
				while(ctrlPos!=NULL)
				{
					CheckGsInVirLoop((CSclCtrlGsIn *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,m_pVirLoopChecks);
				}
			}
			else if (pIedCtrls->GetClassID() == DVMCLASSID_CDVMDEVICE)
			{
				CExBaseList *pCtrlLog = NULL;
				while(ctrlPos!=NULL)
				{
					pCtrlLog = (CExBaseList *)pIedCtrls->GetNext(ctrlPos);
					CheckRptCtrlBrcb(pCtrlLog ,strErrorIedPos ,m_pVirLoopChecks);
					CheckLogCtrlLcb(pCtrlLog ,strErrorIedPos ,m_pVirLoopChecks);
				}
			}
		}

	}
	m_mapAppID.clear();
	m_mapSMVID.clear();
	m_mapGOOSEID.clear();
	m_BeCheckFinished = TRUE;
	return TRUE;
}

BOOL CSclVirLoopCheckTool::VirLoopCheckIsEmpty(CVirLoopChecks *pVirLoopChecks)
{
	POS pos = pVirLoopChecks->GetHeadPosition();
	CCheckObject *pCheckObject = NULL;

	while(pos != NULL)
	{
		pCheckObject = (CCheckObject*)pVirLoopChecks->GetNext(pos);

		if (pCheckObject->m_nChoose)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CSclVirLoopCheckTool::BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID)
{
	strObjectID = "";
	if (pCheckObject == NULL)
	{
		return TRUE;
	} 
	else
	{
		strObjectID = pCheckObject->m_strErrorType;
		return pCheckObject->m_nChoose;
	}
}

void CSclVirLoopCheckTool::CheckSmvOutVirLoop(CSclCtrlSmvOut *pSclCtrlSmvOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CString strDesc;
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	//////////////////////////////////////////////////////Start检查AppID、SVID、GOOSEID的唯一性检查////////////////////////////////////////////////////////////////////////////////////////////
	std::map<long ,CString>::iterator iterAppID;
	std::map<CString ,CString>::iterator iterSVID;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterAppID = m_mapAppID.find(pSclCtrlSmvOut->m_dwAppID);
		if (iterAppID != m_mapAppID.end())
		{
			/*strErrorText.Format("本IED中输出的(%s)采样值控制块中, APPID\"%x\" 全站不唯一 , 与(",
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->m_dwAppID);
			strErrorText += iterAppID->second;
			strErrorText += ") 控制块冲突;";*/
			FormatString(strErrorText,/*"本IED中输出的(%s)采样值控制块中, APPID\"%x\" 全站不唯一 , 与(%s)) 控制块冲突;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription1.GetString(),
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->m_dwAppID,iterAppID->second);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlSmvOut->m_strSVID;
			m_mapAppID.insert(std::make_pair(pSclCtrlSmvOut->m_dwAppID ,strDesc));
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("SVID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterSVID = m_mapSMVID.find(pSclCtrlSmvOut->m_strSVID);
		if (iterSVID != m_mapSMVID.end())
		{
			/*strErrorText.Format("本IED中输出的(%s)采样值控制块中, SVID 全站不唯一 , 与(",
				pSclCtrlSmvOut->m_strSVID.GetString());
			strErrorText += iterSVID->second;
			strErrorText += ") 控制块冲突;";*/
			FormatString(strErrorText,/*"本IED中输出的(%s)采样值控制块中, SVID 全站不唯一 , 与(%s)) 控制块冲突;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription2.GetString(),
				pSclCtrlSmvOut->m_strSVID.GetString() ,iterSVID->second);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlSmvOut->m_strSVID;
			m_mapSMVID.insert(std::make_pair(pSclCtrlSmvOut->m_strSVID ,strDesc));
		}
	}
	/////////////////////////////////////////////////////////////////END///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////Start检查MAC地址、AppID、VlanID、Vlan优先级的有效性//////////////////////////////////////////////////////////////////////////////
	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("MAC-SMV");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (!CheckMACAddrValidity(pSclCtrlSmvOut->m_strMac ,1))
		{
			/*strErrorText.Format("本IED中输出的(%s)控制块中, MAC地址为(%s) 不在9-2 SV 组播地址范围01-0C-CD-04-00-00 ~ 01-0C-CD-04-01-FF 之间;",
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->m_strMac.GetString());*/
			FormatString(strErrorText,/*"本IED中输出的(%s)控制块中, MAC地址为(%s) 不在9-2 SV 组播地址范围01-0C-CD-04-00-00 ~ 01-0C-CD-04-01-FF 之间;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription3.GetString(),
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->m_strMac.GetString());
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if ((pSclCtrlSmvOut->m_dwAppID < 0x4000)||(pSclCtrlSmvOut->m_dwAppID > 0x7FFF))
		{
			/*strErrorText.Format("本IED中输出的(%s)采样值控制块中, APPID为\"%x\" 不在标准要求的0x4000~0x7FFF 之间;",
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->m_dwAppID);*/
			FormatString(strErrorText,/*"本IED中输出的(%s)采样值控制块中, APPID为\"%x\" 不在标准要求的0x4000~0x7FFF 之间;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription4.GetString(),
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->m_dwAppID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VLANID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlSmvOut->scl_smv_VLANID > 0xFFF)
		{
			/*strErrorText.Format("本IED中输出的(%s) SMV控制块中, VlanID为\"%x\" 不在标准要求的3位16进制内;",
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->scl_smv_VLANID);*/
			FormatString(strErrorText,/*"本IED中输出的(%s) SMV控制块中, VlanID为\"%x\" 不在标准要求的3位16进制内;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription5.GetString(),
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->scl_smv_VLANID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VlanPriority-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlSmvOut->scl_smv_VLANPRI > 7)
		{
			/*strErrorText.Format("本IED中输出的(%s) SMV控制块中, VLAN优先级为\"%x\" 不在标准要求的0-7之间;",
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->scl_smv_VLANPRI);*/
			FormatString(strErrorText,/*"本IED中输出的(%s) SMV控制块中, VLAN优先级为\"%x\" 不在标准要求的0-7之间;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription6.GetString(),
				pSclCtrlSmvOut->m_strSVID.GetString() ,pSclCtrlSmvOut->scl_smv_VLANPRI);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	///////////////////END////检查MAC地址、AppID的正确性//////////////////////////////////////////////////////////////////////////////
	POS chPos = pSclCtrlSmvOut->GetHeadPosition();
	CSclChSmvOut *pSclChSmvOut = NULL;

	long nCount = 0;

	while(chPos!=NULL)
	{
		pSclChSmvOut = (CSclChSmvOut *)pSclCtrlSmvOut->GetNext(chPos);
		nCount++;

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Channel-DataType");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{

			if (pSclChSmvOut->fcda_cdc != "SAV")
			{
				/*strErrorText.Format("本IED输出的(%s)控制块中, 通道%d : (",
					pSclCtrlSmvOut->m_strSVID.GetString() ,nCount);
				strErrorText += pSclChSmvOut->fcda_desc;
				strErrorText.AppendFormat(") 所用cdc 为(%s) ,所在DOType为(%s) ,标准要求使用cdc为\"SAV\";",
					pSclChSmvOut->fcda_cdc.GetString() ,pSclChSmvOut->fcda_DOType.GetString());*/
				FormatString(strErrorText,/*"本IED输出的(%s)控制块中, 通道%d : (%s) 所用cdc 为(%s) ,所在DOType为(%s) ,标准要求使用cdc为\"SAV\";"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription7.GetString(),
					pSclCtrlSmvOut->m_strSVID.GetString() ,nCount, pSclChSmvOut->fcda_desc.GetString(),pSclChSmvOut->fcda_cdc.GetString() ,pSclChSmvOut->fcda_DOType.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChSmvOut->fcda_dodesc != pSclChSmvOut->fcda_desc)
			{
				/*strErrorText.Format("本IED输出的(%s)控制块中, 通道%d的 DOI描述(",
					pSclCtrlSmvOut->m_strSVID.GetString() ,nCount);
				strErrorText += pSclChSmvOut->fcda_dodesc;
				strErrorText += ") 与dU赋值 (";
				strErrorText += pSclChSmvOut->fcda_desc;
				strErrorText += ") 两者不相同 ;";*/
				FormatString(strErrorText,/*"本IED输出的(%s)控制块中, 通道%d的 DOI描述(%s) 与dU赋值 (%s) 两者不相同 ;"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription8.GetString(),
					pSclCtrlSmvOut->m_strSVID.GetString() ,nCount,
					pSclChSmvOut->fcda_dodesc.GetString(),pSclChSmvOut->fcda_desc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}

bool CSclVirLoopCheckTool::CheckMACAddrValidity(CString strMAC ,bool bSMVType)
{
	strMAC.MakeLower();
	long nIndex = -1;
	if (strMAC.GetLength()!=17)
	{
		return false;
	}

	if (bSMVType)
	{
		nIndex = strMAC.Find("01-0c-cd-04-0");
		if ((nIndex==0)&&((strMAC[13]=='0')||(strMAC[13]=='1'))&&IsHex(strMAC[15])&&IsHex(strMAC[16]))
		{
			return true;
		}
	} 
	else
	{
		nIndex = strMAC.Find("01-0c-cd-01-0");
		if ((nIndex==0)&&((strMAC[13]=='0')||(strMAC[13]=='1'))&&IsHex(strMAC[15])&&IsHex(strMAC[16]))
		{
			return true;
		}
	}
	return false;
}

void CSclVirLoopCheckTool::CheckSmvInVirLoop(CSclCtrlSmvIn *pSclCtrlSmvIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	POS chPos = pSclCtrlSmvIn->GetHeadPosition();
	CSclChSmvIn *pSclChSmvIn = NULL;

	CString strErrorText;

	CString strInDesc ,strOutDesc;

	while(chPos!=NULL)
	{
		pSclChSmvIn = (CSclChSmvIn *)pSclCtrlSmvIn->GetNext(chPos);

		strInDesc = pSclChSmvIn->inDADesc;
		AddStringAvoidRepeat(strInDesc ,pSclChSmvIn->inDODesc);
		AddStringAvoidRepeat(strInDesc ,pSclChSmvIn->inLNDesc);
		AddStringAvoidRepeat(strInDesc ,pSclCtrlSmvIn->m_strLDdesc);

		strOutDesc = pSclChSmvIn->fcda_desc;
		AddStringAvoidRepeat(strOutDesc ,pSclChSmvIn->fcda_dodesc);
		AddStringAvoidRepeat(strOutDesc ,pSclChSmvIn->fcda_lndesc);
		AddStringAvoidRepeat(strOutDesc ,pSclCtrlSmvIn->m_strExLDdesc);

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("smvin-check-KeyDB");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			CString strKeysDesc;

			if (!m_oXMatchVirTerminal.Match(strInDesc ,strOutDesc ,&m_oSMVKeyDB ,strKeysDesc))
			{
				/*strErrorText = "本IED中SMVIN接收的(";
				strErrorText += pSclCtrlSmvIn->iedStr;
				strErrorText.AppendFormat(")控制块中, 通道%d的 输入端描述 (",pSclChSmvIn->outIndex);
				strErrorText += strInDesc;
				strErrorText += ") , 输出端描述 (";
				strErrorText += strOutDesc;
				strErrorText += ") ,其中关键字 (";
				strErrorText += strKeysDesc;
				strErrorText += ") 冲突.";*/
				FormatString(strErrorText,/*"本IED中SMVIN接收的(%s)控制块中, 通道%d的 输入端描述 (%s) , 输出端描述 (%s) ,其中关键字 (%s) 冲突."*/
					g_sLangTxt_SCLCompare_LoopCheckDescription9.GetString(),
					pSclCtrlSmvIn->iedStr.GetString(),pSclChSmvIn->outIndex, strInDesc.GetString(),
					strOutDesc.GetString(),strKeysDesc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Channel-DataType");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChSmvIn->inputRef_cdc != "MV")
			{
				/*strErrorText = "本IED中SMVIN接收的(";
				strErrorText += pSclCtrlSmvIn->iedStr;
				strErrorText.AppendFormat(")控制块中, 内部通道%d : (",pSclChSmvIn->inIndex);
				strErrorText += pSclChSmvIn->inDADesc;
				strErrorText.AppendFormat(") 所用cdc 为(%s) ,所在type为(%s) ,标准要求使用cdc为\"MV\";",
					pSclChSmvIn->inputRef_cdc.GetString() ,pSclChSmvIn->inputRef_DOType.GetString());*/
				FormatString(strErrorText,/*"本IED中SMVIN接收的(%s)控制块中, 内部通道%d : (%s) 所用cdc 为(%s) ,所在type为(%s) ,标准要求使用cdc为\"MV\";"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription10.GetString(),
					pSclCtrlSmvIn->iedStr.GetString(), pSclChSmvIn->inIndex,
					pSclChSmvIn->inDADesc.GetString(),pSclChSmvIn->inputRef_cdc.GetString() ,pSclChSmvIn->inputRef_DOType.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}

			if (pSclChSmvIn->fcda_cdc != "SAV")
			{
				/*strErrorText = "本IED中SMVIN接收的(";
				strErrorText += pSclCtrlSmvIn->iedStr;
				strErrorText.AppendFormat(")控制块中, 外部通道%d : (",pSclChSmvIn->outIndex);
				strErrorText += pSclChSmvIn->fcda_desc;
				strErrorText.AppendFormat(") 所用cdc 为(%s) ,所在DOType为(%s) ,标准要求使用cdc为\"SAV\";",
					pSclChSmvIn->fcda_cdc.GetString() ,pSclChSmvIn->fcda_DOType.GetString());*/
				FormatString(strErrorText,/*"本IED中SMVIN接收的(%s)控制块中, 外部通道%d : (%s) 所用cdc 为(%s) ,所在DOType为(%s) ,标准要求使用cdc为\"SAV\";"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription11.GetString(),
					pSclCtrlSmvIn->iedStr.GetString(), pSclChSmvIn->outIndex,
					pSclChSmvIn->fcda_desc.GetString(),pSclChSmvIn->fcda_cdc.GetString() ,pSclChSmvIn->fcda_DOType.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChSmvIn->inDODesc != pSclChSmvIn->inDADesc)
			{
				/*strErrorText = "本IED中SMVIN接收的(";
				strErrorText += pSclCtrlSmvIn->iedStr;
				strErrorText.AppendFormat(")控制块中, 通道%d的内部 DOI描述(",pSclChSmvIn->outIndex);
				strErrorText += pSclChSmvIn->inDODesc;
				strErrorText += ") 与dU赋值 (";
				strErrorText += pSclChSmvIn->inDADesc;
				strErrorText += ") 两者不相同 ;";*/
				FormatString(strErrorText,/*"本IED中SMVIN接收的(%s)控制块中, 通道%d的内部 DOI描述(%s) 与dU赋值 (%s) 两者不相同 ;"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription12.GetString(),
					pSclCtrlSmvIn->iedStr.GetString(), pSclChSmvIn->outIndex,
					pSclChSmvIn->inDODesc.GetString(),pSclChSmvIn->inDADesc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}

			if (pSclChSmvIn->fcda_dodesc != pSclChSmvIn->fcda_desc)
			{
				/*strErrorText = "本IED中SMVIN接收的(";
				strErrorText += pSclCtrlSmvIn->iedStr;
				strErrorText.AppendFormat(")控制块中, 通道%d的外部 DOI描述(",pSclChSmvIn->outIndex);
				strErrorText += pSclChSmvIn->fcda_dodesc;
				strErrorText += ") 与dU赋值 (";
				strErrorText += pSclChSmvIn->fcda_desc;
				strErrorText += ") 两者不相同 ;";*/
				FormatString(strErrorText,/*"本IED中SMVIN接收的(%s)控制块中, 通道%d的外部 DOI描述(%s) 与dU赋值 (%s) 两者不相同 ;"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription13.GetString(),
					pSclCtrlSmvIn->iedStr.GetString(), pSclChSmvIn->outIndex,
					pSclChSmvIn->fcda_dodesc.GetString(),pSclChSmvIn->fcda_desc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}

void CSclVirLoopCheckTool::AddStringAvoidRepeat(CString &strDesc ,CString strChild)
{
	int nIndex = 0;
	nIndex = strDesc.Find(strChild);
	if (nIndex == -1)
	{
		strDesc += "  ";
		strDesc += strChild;
	} 
}

bool CSclVirLoopCheckTool::IsHex(unsigned char ch)
{
	if ((ch>47)&&(ch<58))
	{
		return true;
	}
	else if ((ch>96)&&(ch<103))
	{
		return true;
	}
	return false;
}

void CSclVirLoopCheckTool::CheckGsOutVirLoop(CSclCtrlGsOut *pSclCtrlGsOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CString strDesc;
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	//////////////////////////////////////////////////////Start检查AppID、SVID、GOOSEID的唯一性检查////////////////////////////////////////////////////////////////////////////////////////////
	std::map<long ,CString>::iterator iterAppID;
	std::map<CString ,CString>::iterator iterGoID;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterAppID = m_mapAppID.find(pSclCtrlGsOut->m_dwAppID);
		if (iterAppID != m_mapAppID.end())
		{
			/*strErrorText.Format("本IED中输出的(%s)GOOSE控制块中, APPID\"%x\" 全站不唯一 , 与(",
				pSclCtrlGsOut->m_strGooseId.GetString() ,pSclCtrlGsOut->m_dwAppID);
			strErrorText += iterAppID->second;
			strErrorText += ") 控制块冲突;";*/
			FormatString(strErrorText,/*"本IED中输出的(%s)GOOSE控制块中, APPID\"%x\" 全站不唯一 , 与(%s) 控制块冲突;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription14.GetString(),
				pSclCtrlGsOut->m_strGooseId.GetString() ,pSclCtrlGsOut->m_dwAppID,iterAppID->second.GetString());
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlGsOut->m_strGooseId;
			m_mapAppID.insert(std::make_pair(pSclCtrlGsOut->m_dwAppID ,strDesc));
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("GoID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterGoID = m_mapGOOSEID.find(pSclCtrlGsOut->m_strGooseId);
		if (iterGoID != m_mapGOOSEID.end())
		{
			/*strErrorText.Format("本IED中输出的(%s)GOOSE控制块中, GoID 全站不唯一 , 与(",
				pSclCtrlGsOut->m_strGooseId.GetString());
			strErrorText += iterGoID->second;
			strErrorText += ") 控制块冲突;";*/
			FormatString(strErrorText,/*"本IED中输出的(%s)GOOSE控制块中, GoID 全站不唯一 , 与(%s) 控制块冲突;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription15.GetString(),
				pSclCtrlGsOut->m_strGooseId.GetString(), iterGoID->second.GetString());
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlGsOut->m_strGooseId;
			m_mapGOOSEID.insert(std::make_pair(pSclCtrlGsOut->m_strGooseId ,strDesc));
		}
	}
	/////////////////////////////////////////////////////////////////END///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////Start检查MAC地址、AppID、VLANID、VLAN-PRIORITY的有效性//////////////////////////////////////////////////////////////////////////////
	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("MAC-GOOSE");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (!CheckMACAddrValidity(pSclCtrlGsOut->m_strMac ,0))
		{
			strErrorText.Format(/*"本IED中输出的(%s)控制块中, MAC地址为(%s) 不在GOOSE 组播地址范围01-0C-CD-01-00-00 ~ 01-0C-CD-01-01-FF 之间;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription16.GetString(),
				pSclCtrlGsOut->m_strGooseId.GetString() ,pSclCtrlGsOut->m_strMac.GetString());
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlGsOut->m_dwAppID > 0x3FFF)
		{
			strErrorText.Format(/*"本IED中输出的(%s) GOOSE控制块中, APPID为\"%x\" 不在标准要求的0x0000~0x3FFF 之间;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription17.GetString(),
				pSclCtrlGsOut->m_strGooseId.GetString() ,pSclCtrlGsOut->m_dwAppID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VLANID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlGsOut->m_dwVLandID > 0xFFF)
		{
			strErrorText.Format(/*"本IED中输出的(%s) GOOSE控制块中, VlanID为\"%x\" 不在标准要求的3位16进制内;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription18.GetString(),
				pSclCtrlGsOut->m_strGooseId.GetString() ,pSclCtrlGsOut->m_dwVLandID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VlanPriority-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlGsOut->m_dwVLandPriority > 7)
		{
			strErrorText.Format(/*"本IED中输出的(%s) SMV控制块中, VLAN优先级为\"%x\" 不在标准要求的0-7之间;"*/
				g_sLangTxt_SCLCompare_LoopCheckDescription19.GetString(),
				pSclCtrlGsOut->m_strGooseId.GetString() ,pSclCtrlGsOut->m_dwVLandPriority);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	///////////////////END////检查MAC地址、AppID的正确性//////////////////////////////////////////////////////////////////////////////
	POS chPos = pSclCtrlGsOut->GetHeadPosition();
	CSclChGsOut *pSclChGsOut = NULL;

	long nCount = 0;

	while(chPos!=NULL)
	{
		pSclChGsOut = (CSclChGsOut *)pSclCtrlGsOut->GetNext(chPos);
		nCount++;

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChGsOut->fcda_dodesc != pSclChGsOut->fcda_desc)
			{
				/*strErrorText.Format("本IED输出的(%s)控制块中, 通道%d的 DOI描述(",
					pSclCtrlGsOut->m_strGooseId.GetString() ,nCount);
				strErrorText += pSclChGsOut->fcda_dodesc;
				strErrorText += ") 与dU赋值 (";
				strErrorText += pSclChGsOut->fcda_desc;
				strErrorText += ") 两者不相同 ;";*/
				FormatString(strErrorText,/*"本IED输出的(%s)控制块中, 通道%d的 DOI描述(%s) 与dU赋值 (%s) 两者不相同 ;"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription20.GetString(),
					pSclCtrlGsOut->m_strGooseId.GetString() ,nCount,
					pSclChGsOut->fcda_dodesc.GetString(), pSclChGsOut->fcda_desc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}


////////////////////////////////////////////////虚回路描述及冲突检查 部分函数及成员变量////////////////////////////////////////////////////////////	
void CSclVirLoopCheckTool::AddCheckResultVirLoop(CString strErrorType ,CString strText ,CString strErrorPos)
{
	CResultRec *pResultRec = new CResultRec();
	m_pVirtualLoopResults->AddNewChild(pResultRec);
	pResultRec->m_strErrorText = strText;
	pResultRec->m_strErrorPos = strErrorPos;
	if (strErrorType == "tips")
	{
		m_pVirtualLoopResults->m_nAllTipIndex++;
		pResultRec->m_strErrorType = /*"提示信息"*/g_sLangTxt_PromptMessage;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pVirtualLoopResults->m_nAllTipIndex);
		pResultRec->m_nTipIndex = 1;	
	}
	else if (strErrorType == "warning")
	{
		m_pVirtualLoopResults->m_nAllWarningIndex++;
		pResultRec->m_strErrorType = /*"告警"*/g_sLangTxt_SCLCompare_Warning;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pVirtualLoopResults->m_nAllWarningIndex);
		pResultRec->m_nWarningIndex = 1;	
	}
	else if (strErrorType == "error")
	{
		m_pVirtualLoopResults->m_nAllErrorIndex++;
		pResultRec->m_strErrorType = /*"错误"*/g_sLangTxt_Native_error;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pVirtualLoopResults->m_nAllErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (strErrorType == "fatalerror")
	{
		m_pVirtualLoopResults->m_nAllFatalErrorIndex++;
		pResultRec->m_strErrorType = /*"严重"*/g_sLangTxt_SCLCompare_Serious;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pVirtualLoopResults->m_nAllFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;	
	}
}

void CSclVirLoopCheckTool::CheckGsInVirLoop(CSclCtrlGsIn *pSclCtrlGsIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	POS chPos = pSclCtrlGsIn->GetHeadPosition();
	CSclChGsIn *pSclChGsIn = NULL;

	CString strDesc;
	CString strErrorText;

	CString strGSInDesc ,strGSOutDesc;

	while(chPos!=NULL)
	{
		pSclChGsIn = (CSclChGsIn *)pSclCtrlGsIn->GetNext(chPos);

		strGSInDesc = pSclChGsIn->inDADesc;
		AddStringAvoidRepeat(strGSInDesc ,pSclChGsIn->inDODesc);
		AddStringAvoidRepeat(strGSInDesc ,pSclChGsIn->inLNDesc);
		AddStringAvoidRepeat(strGSInDesc ,pSclCtrlGsIn->m_strExLDdesc);

		strGSOutDesc = pSclChGsIn->fcda_desc;
		AddStringAvoidRepeat(strGSOutDesc ,pSclChGsIn->fcda_dodesc);
		AddStringAvoidRepeat(strGSOutDesc ,pSclChGsIn->fcda_lndesc);
		AddStringAvoidRepeat(strGSOutDesc ,pSclCtrlGsIn->m_strLDdesc);

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("goosein-check-KeyDB");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			CString strKeysDesc;

			if (!m_oXMatchVirTerminal.Match(strGSInDesc ,strGSOutDesc ,&m_oGSKeyDB ,strKeysDesc))
			{
				/*strErrorText = "本IED中GSIN接收的(";
				strErrorText += pSclCtrlGsIn->m_strIedDesc;
				strErrorText.AppendFormat(")控制块中, 通道%d的输入端描述(",pSclChGsIn->outIndex);
				strErrorText += strGSInDesc;
				strErrorText += ") , 输出端描述(";
				strErrorText += strGSOutDesc;
				strErrorText += ") ,其中关键字(";
				strErrorText += strKeysDesc;
				strErrorText += ") 冲突.";*/
				FormatString(strErrorText, /*"本IED中GSIN接收的(%s)控制块中, 通道%d的输入端描述(%s) , 输出端描述(%s) ,其中关键字(%s) 冲突."*/
					g_sLangTxt_SCLCompare_LoopCheckDescription21.GetString(),
					pSclCtrlGsIn->m_strIedDesc.GetString(), pSclChGsIn->outIndex,
					strGSInDesc.GetString(), strGSOutDesc.GetString(), strKeysDesc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Channel-DataType");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChGsIn->inputRef_type != pSclChGsIn->fcda_type)
			{
				/*strErrorText = "本IED中GSIN接收的(";
				strErrorText += pSclCtrlGsIn->m_strIedDesc;
				strErrorText.AppendFormat(")控制块中, 内部通道%ld:",pSclChGsIn->inIndex);
				strErrorText += pSclChGsIn->inDADesc;
				strErrorText.AppendFormat(" 所用通道数据类型为(%s), 与之相连的外部通道%ld: "
					 ,pSclChGsIn->inputRef_type.GetString(),pSclChGsIn->outIndex);
				strErrorText += pSclChGsIn->fcda_desc;
				strErrorText.AppendFormat(" 所用数据类型为(%s) 两者不一致 ;",pSclChGsIn->fcda_type.GetString());*/
				FormatString(strErrorText,/*"本IED中GSIN接收的(%s)控制块中, 内部通道%ld:%s 所用通道数据类型为(%s), 与之相连的外部通道%ld: %s"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription22.GetString(),
					pSclCtrlGsIn->m_strIedDesc.GetString(), pSclChGsIn->inIndex, pSclChGsIn->inDADesc.GetString(), 
					pSclChGsIn->inputRef_type.GetString(),pSclChGsIn->outIndex, pSclChGsIn->fcda_desc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChGsIn->inDODesc != pSclChGsIn->inDADesc)
			{
				/*strErrorText = "本IED中GSIN接收的(";
				strErrorText += pSclCtrlGsIn->m_strIedDesc;
				strErrorText.AppendFormat(")控制块中, 通道%d的内部 DOI描述(",pSclChGsIn->outIndex);
				strErrorText += pSclChGsIn->inDODesc;
				strErrorText += ") 与dU赋值 (";
				strErrorText += pSclChGsIn->inDADesc;
				strErrorText += ") 两者不相同 ;",*/
				FormatString(strErrorText,/*"本IED中GSIN接收的(%s)控制块中, 通道%d的内部 DOI描述(%s) 与dU赋值 (%s) 两者不相同 ;"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription23.GetString(),
					pSclCtrlGsIn->m_strIedDesc.GetString(), pSclChGsIn->outIndex,
					pSclChGsIn->inDODesc.GetString(), pSclChGsIn->inDADesc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}

			if (pSclChGsIn->fcda_dodesc != pSclChGsIn->fcda_desc)
			{
				/*strErrorText = "本IED中GSIN接收的(";
				strErrorText += pSclCtrlGsIn->m_strIedDesc;
				strErrorText.AppendFormat(")控制块中, 通道%d的外部 DOI描述(",pSclChGsIn->outIndex);
				strErrorText += pSclChGsIn->fcda_dodesc;
				strErrorText += ") 与dU赋值 (";
				strErrorText += pSclChGsIn->fcda_desc;
				strErrorText += ") 两者不相同 ;";*/
				FormatString(strErrorText,/*"本IED中GSIN接收的(%s)控制块中, 通道%d的外部 DOI描述(%s) 与dU赋值 (%s) 两者不相同 ;"*/
					g_sLangTxt_SCLCompare_LoopCheckDescription24.GetString(),
					pSclCtrlGsIn->m_strIedDesc.GetString(), pSclChGsIn->outIndex,
					pSclChGsIn->fcda_dodesc.GetString(), pSclChGsIn->fcda_desc.GetString());
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}

void CSclVirLoopCheckTool::CheckRptCtrlBrcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	if (pSclLogicDev->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
	{
		return;
	}

	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Rpt-Brcb");

	if (!BeCheckThisObject(pCheckObject ,strObjectID))
	{
		return;
	}

	POS RptsPos = pSclLogicDev->GetHeadPosition();
	POS RptPos = NULL;

	CRptCtrl *pRptCtrl = NULL;

	CExBaseList *pRptCtrls = NULL;

	CDataSet_Scl *pDataSetTmps = NULL;

	CString strDatasetName;
	CString strErrorText;

	long nFind = -1;

	while(RptsPos!=NULL)
	{
		pRptCtrls = (CExBaseList*)pSclLogicDev->GetNext(RptsPos);

		if (pRptCtrls->GetClassID() == DVMCLASSID_CRPTCTRLS)
		{
			RptPos  = pRptCtrls->GetHeadPosition();
			while(RptPos!=NULL)
			{
				pRptCtrl = (CRptCtrl*)pRptCtrls->GetNext(RptPos);

				strDatasetName = pRptCtrl->m_strDatSet;
				DelTailDigtal(&strDatasetName);
				pDataSetTmps = (CDataSet_Scl *)m_oTemplateFile1396.FindByID(strDatasetName);

				if (pDataSetTmps!=NULL)
				{
					if (pDataSetTmps->m_strBrcbname.IsEmpty())
					{
						strErrorText.Format(/*"本IED中的 逻辑设备(%s)下的报告控制块name值为(%s) 其对应数据集(%s) 不能关联报告控制块 ;"*/
							g_sLangTxt_SCLCompare_LoopCheckDescription25.GetString(),
							pRptCtrls->m_strName.GetString() ,pRptCtrl->m_strName.GetString() ,pRptCtrl->m_strDatSet.GetString());
						AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
						continue;
					}

					nFind = pRptCtrl->m_strName.Find(pDataSetTmps->m_strBrcbname);
					if (nFind == 0)
					{
						if(CheckTailDigital(pRptCtrl->m_strName))
						{
							strErrorText.Format(/*"本IED中的 逻辑设备(%s)下的报告控制块name值为(%s) 命名错误， 标准要求多个同类型的报告控制块应加字母后缀区分 ;"*/
								g_sLangTxt_SCLCompare_LoopCheckDescription26.GetString(),
								pRptCtrls->m_strName.GetString() ,pRptCtrl->m_strName.GetString());
							AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
						}
					}
					else
					{
						strErrorText.Format(/*"本IED中的 逻辑设备(%s)下的报告控制块name值为(%s) 与 标准要求的(%s) 不一致 ;"*/
							g_sLangTxt_SCLCompare_LoopCheckDescription27.GetString(),
							pRptCtrls->m_strName.GetString() ,pRptCtrl->m_strName.GetString() ,pDataSetTmps->m_strBrcbname.GetString());
						AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
					}
				}
			}
		}
	}
}

long CSclVirLoopCheckTool::DelTailDigtal(CString *strName )
{
	long nIndex = 0;
	char szDigtal[20] = {""};
	char szNew[20] = {""};
	szDigtal[0] = strName->GetAt(strName->GetLength()-1);
	char *pzfTmp = szDigtal;
	bool bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');

	while(bSmb)
	{
		pzfTmp++;
		*strName = strName->Left(strName->GetLength()-1);
		*pzfTmp = strName->GetAt(strName->GetLength()-1);
		bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');
	}
	*pzfTmp = '\0';

	nIndex = strlen(szDigtal);
	for (int i=0; i<nIndex;i++)
	{
		szNew[i] = szDigtal[nIndex-i-1];
	}

	nIndex = CString_To_long(szNew);
	return nIndex;
}

void CSclVirLoopCheckTool::CheckLogCtrlLcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	if (pSclLogicDev->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
	{
		return;
	}

	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Log-Lcb");

	if (!BeCheckThisObject(pCheckObject ,strObjectID))
	{
		return;
	}

	POS LogsPos = pSclLogicDev->GetHeadPosition();
	POS LogPos = NULL;

	CLogCtrl *pLogCtrl = NULL;

	CExBaseList *pLogCtrls = NULL;

	CDataSet_Scl *pDataSetTmps = NULL;

	CString strDatasetName;
	CString strErrorText;

	long nFind = -1;

	while(LogsPos!=NULL)
	{
		pLogCtrls = (CExBaseList*)pSclLogicDev->GetNext(LogsPos);

		if (pLogCtrls->GetClassID() == DVMCLASSID_CLOGCTRLS)
		{
			LogPos  = pLogCtrls->GetHeadPosition();
			while(LogPos!=NULL)
			{
				pLogCtrl = (CLogCtrl*)pLogCtrls->GetNext(LogPos);

				strDatasetName = pLogCtrl->m_strDatSet;
				DelTailDigtal(&strDatasetName);
				pDataSetTmps = (CDataSet_Scl *)m_oTemplateFile1396.FindByID(strDatasetName);

				if (pDataSetTmps!=NULL)
				{
					if (pDataSetTmps->m_strLcbname.IsEmpty())
					{
						continue;
					}

					nFind = pLogCtrl->m_strID.Find(pDataSetTmps->m_strLcbname);
					if (nFind == 0)
					{
						if(CheckTailDigital(pLogCtrl->m_strID))
						{
							strErrorText.Format(/*"本IED中的 逻辑设备(%s)下的日志控制块name值为(%s) 命名错误， 标准要求多个同类型的日志控制块应加字母后缀区分 ;"*/
								g_sLangTxt_SCLCompare_LoopCheckDescription28.GetString(),
								pLogCtrls->m_strName.GetString() ,pLogCtrl->m_strID.GetString());
							AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
						}
					}
					else
					{
						strErrorText.Format(/*"本IED中的 逻辑设备(%s)下的日志控制块name值为(%s) 与 标准要求的(%s) 不一致 ;"*/
							g_sLangTxt_SCLCompare_LoopCheckDescription29.GetString(),
							pLogCtrls->m_strName.GetString() ,pLogCtrl->m_strID.GetString() ,pDataSetTmps->m_strLcbname.GetString());
						AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
					}
				}
			}
		}
	}
}

bool CSclVirLoopCheckTool::CheckTailDigital(const CString &strText)
{
	if (strText.IsEmpty())
	{
		return false;
	}
	unsigned char zfTmp = strText.GetAt(strText.GetLength()-1);
	return (('0'<=zfTmp)&&(zfTmp<='9'));
}

void CSclVirLoopCheckTool::FormatString(CString &strText, const char *strFormat, ...)
{
#ifdef _PSX_IDE_QT_
	va_list argList;
	va_start( argList, strFormat );
	str_formart_v(strFormat, argList, strText);
	va_end( argList );
#else
	va_list argList;
    va_start( argList, format );
    strText.vsprintf(format, argList );
    va_end( argList );
#endif
}