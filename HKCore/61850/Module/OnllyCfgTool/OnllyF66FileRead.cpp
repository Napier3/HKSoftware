#include "StdAfx.h"
#include "OnllyF66FileRead.h"
#include <bitset>


inline double XAdjustAngle(double dAngle)
{
	while (dAngle > 360.0)
	{
		dAngle -= 360;
	}

	while (dAngle <-360.0)
	{
		dAngle += 360;
	}

	if (dAngle > 180)
	{
		dAngle = dAngle - 360;
	}

	if (dAngle < -180)
	{
		dAngle = dAngle + 360;
	}

	return dAngle;
}

COnllyF66FileRead::COnllyF66FileRead(void)
{

}
COnllyF66FileRead::~COnllyF66FileRead(void)
{

}

BOOL COnllyF66FileRead::ReadF66File(const CString &strPath)
{
	m_downmu.clear();
	m_gseui.GseInCfg.clear();
	m_gseui.GseOutCfg.clear();

	if (m_MarkUp.Load(strPath))
	{
		m_MarkUp.ResetPos();
		if (m_MarkUp.FindElem(_T("F66")) == false) return FALSE;

		// 获取版本号
		CString strText,strType;
		GetAttrib(_T("Version"),strText);
		m_nVersion = _ttoi(strText);
		// 通用配置
		ReadMUGerSet(m_mugersetting);

		switch(m_mugersetting.nSampleType)
		{
		case SAMPLE_TYPE_9_1:
			strType = _T("m_muset91");
			break;
		case SAMPLE_TYPE_9_1_EX:
			strType = _T("m_muset91Ex");
			break;
		case SAMPLE_TYPE_9_2:
			strType = _T("m_muset92");
			break;
		case SAMPLE_TYPE_FT3:
			strType = _T("m_musetft3");
			break;
		default:
			break;
		}
		// SMV
		while(m_MarkUp.FindChildElem(_T("MU_SETTING")))
		{
			strText = m_MarkUp.GetChildAttrib(_T("name"));
			m_MarkUp.IntoElem();

			if (strText == strType)
			{
				ReadMUCfgXML(m_downmu,strText);
			}

			m_MarkUp.OutOfElem();
		}

		// GOOSE
		if (m_MarkUp.FindChildElem(_T("m_gseui")))
		{
			CString strTemp;  
			m_MarkUp.IntoElem();
			GETCHILDELEMDATA(_T("Version"),m_gseui.Version,0);
			GETCHILDELEMDATA(_T("GseInNumSel"),m_gseui.GseInNumSel,0);
			GETCHILDELEMDATA(_T("GseOutNumSel"),m_gseui.GseOutNumSel,0);

			while(m_MarkUp.FindChildElem(_T("GSECFG")))
			{
				m_MarkUp.IntoElem();
				strText = m_MarkUp.GetAttrib(_T("name"));
				if (strText == _T("GseInCfg"))
				{
					ReadGOOSECfgXML(m_gseui.GseInCfg,strText);
				}
				else if (strText == _T("GseOutCfg"))
				{
					ReadGOOSECfgXML(m_gseui.GseOutCfg,strText);
				}
				m_MarkUp.OutOfElem();
			}

			m_MarkUp.OutOfElem();
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void COnllyF66FileRead::ReadMUCfgXML(vector<MU_SETTING>& mu_setting,const CString& NodeName)
{
	CString str;
	MU_SETTING mu;
	mu_setting.clear();

	while(m_MarkUp.FindChildElem(NodeName))
	{
		m_MarkUp.IntoElem();
		GETCHILDELEMDATA(_T("AppId"),mu.AppId,16384);
		GETCHILDELEMDATA(_T("bSyn"),mu.bSyn,0);
		GETCHILDELEMDATA(_T("bUsed"),mu.bUsed,0);
		GETCHILDELEMDATA(_T("CurrentA"),mu.CurrentA,0);
		GETCHILDELEMDATA(_T("CurrentDelay"),mu.CurrentDelay,0);
		GETCHILDELEMDATA(_T("CurrentNeut"),mu.CurrentNeut,0);
		GETCHILDELEMDATA(_T("CurrentScp"),mu.CurrentScp,0);
		GETCHILDELEMDATA(_T("DataName"),mu.DataName,0);
		GETCHILDELEMDATA(_T("dwState1"),mu.dwState1,(DWORD)0);
		GETCHILDELEMDATA(_T("dwState2"),mu.dwState2,(DWORD)0);
		GETCHILDELEMDATA(_T("fCTBitRate"),mu.fCTBitRate,0.0f);
		GETCHILDELEMDATA(_T("fPTBitRate"),mu.fPTBitRate,0.0f);
		GETCHILDELEMDATA(_T("LDName"),mu.LDName,0);
		GETCHILDELEMDATA(_T("LNName"),mu.LNName,0);
		GETCHILDELEMDATA(_T("nChnNum"),mu.nChnNum,0);
		GETCHILDELEMDATA(_T("nIndex"),mu.nIndex,0);
		GETCHILDELEMDATA(_T("nLanNo"),mu.nLanNo,0);
		GETCHILDELEMDATA(_T("nTCIPr"),mu.nTCIPr,0);
		GETCHILDELEMDATA(_T("nTciVid"),mu.nTciVid,0);
		GETCHILDELEMDATA(_T("nVersion"),mu.nVersion,0);
		GetChildData(_T("strDes"),mu.strDes);
		GetChildData(_T("strMac"),mu.strMac);
		GetChildData(_T("SourceMac"),mu.SourceMac,_T("48-49-4A-4B-4C-4D"));
		GetChildData(_T("strSvid"),mu.strSvid);
		GETCHILDELEMDATA(_T("VoltA"),mu.VoltA,0);
		GETCHILDELEMDATA(_T("bSynAuto"),mu.bSynAuto,0);
		GETCHILDELEMDATA(_T("bConti"),mu.bConti,0);

		// 读取92其他报文选项
		ReadMU92OpData(mu.other92op);

		ReadMUChnCfgXML(mu.pmu_chnset);

		int nNum = mu.pmu_chnset.size();

		// 通道数根据实际读取到的通道数确定
		mu.nChnNum = nNum;

		//////////////////////////////////////////////////////////////////////////
		// 初始化数据
		if (m_MarkUp.FindChildElem(_T("MU_CHNDATA")) == false)
		{
			BOOL bChk = FALSE;
			MU_CHNSET *pChSet = NULL;
			int nOffSetCount = 0;
			float fAng = 0.0f;
			for (int k=0;k<MAX_TST_MUCHN;k++)
			{
				if (k<nNum)
					pChSet = &mu.pmu_chnset.at(k);

				mu.UIs[k].uIndex = k;
				if (NodeName==_T("m_muset92")&&pChSet->nTypeSel==2)
					nOffSetCount++;
				switch(k%3)
				{
				case 0: fAng = 0.0f;    break;
				case 1: fAng = -120.0f; break;
				case 2: fAng = 120.0f;  break;
				}

				fAng += nOffSetCount*120;
				mu.UIs[k].Ang = (float)XAdjustAngle(fAng);

				mu.UIs[k].Fre = 50.0f;
				mu.UIs[k].uChnType = ((k/3)==0||(k/3)==2)?0:1;

				if (k%3==0)
					bChk = !bChk;

				mu.UIs[k].nSetData = (bChk)?57:1;
				mu.UIs[k].Mag = (bChk)?57.735f:1.0f;
				mu.UIs[k].fData1 = (bChk)?220000.0f:1000.0f;
				mu.UIs[k].fData2 = (bChk)?100.0f:1.0f;

				if (NodeName==_T("m_muset92"))
				{
					mu.UIs[k].Quo = (bChk)?2200.0f:1000.0f;
				}
				else
				{
					mu.UIs[k].Quo = 0x0000;
				}

				mu.UIs[k].uChnType = (bChk)?0:1;
				mu.UIs[k].fFirstData = 0.0f;
				mu.UIs[k].fLastData = 0.0f;
				mu.UIs[k].fStep = 0.0f;
				mu.UIs[k].bQuaTest = TRUE;
				mu.UIs[k].bVar = TRUE;

				//////////////////////////////////////////////////////////////////////////
				if (pChSet)
				{
					mu.UIs[k].strName = pChSet->strChnName;

					if (NodeName==_T("m_muset91")||
						NodeName==_T("m_muset91Ex"))
					{	//类型选择
						mu.UIs[k].uChnType = pChSet->nTypeSel;
						switch(pChSet->nTypeSel)
						{
						case 0://电压	
							mu.UIs[k].Mag = 57.735f;
							mu.UIs[k].nSetData = 0;
							mu.UIs[k].Quo = 0x2d41;
							break;
						case 1://电流（保护）
							mu.UIs[k].Mag = 1.0f;
							mu.UIs[k].nSetData = 0;
							mu.UIs[k].Quo = 0x01cf;
							break;
						case 2://电流（测量）
							mu.UIs[k].uChnType = 1;
							mu.UIs[k].Mag = 1.0f;
							mu.UIs[k].nSetData = 0;
							mu.UIs[k].Quo = 0x2d41;
							break;
						}
					}

					if (NodeName==_T("m_muset92"))
					{
						mu.UIs[k].uChnType = pChSet->nTypeSel;
						switch(pChSet->nTypeSel)
						{
						case 0://电压
							mu.UIs[k].Mag = 57.735f;
							mu.UIs[k].nSetData = 0;
							mu.UIs[k].fData1 = 220000.0f;
							mu.UIs[k].fData2 = 100.0f;
							mu.UIs[k].Quo = 2200.0f;
							break;
						case 1://电流
							mu.UIs[k].Mag = 1.0f;
							mu.UIs[k].nSetData = 0;
							mu.UIs[k].fData1 = 1000.0f;
							mu.UIs[k].fData2 = 1.0f;
							mu.UIs[k].Quo = 1000.0f;
							break;
						case 2://时间
							mu.UIs[k].uChnType = 3;
							mu.UIs[k].nSetData = 0;
							mu.UIs[k].fData1 = 0.0f;
							mu.UIs[k].fData2 = 1.0f;
							mu.UIs[k].Quo = 0.0f;
#ifdef _UNICODE
							mu.UIs[k].Mag = (float)_wtof(pChSet->strInput);
#else
							mu.UIs[k].Mag = atof(pChSet->strInput);
#endif
							mu.UIs[k].Ang = 0.0f;
							mu.UIs[k].Fre = 0.0f;
							break;
						}
					}
				}
			}
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////
			ReadMUMSGCfgDataXml(mu.UIs);
		}



		mu.msgtestsetPtr = MSGTESTSETPtr(new MSGTESTSET);

		if (ReadMUMSGTestSetXML(mu.msgtestsetPtr) == FALSE)
		{
			InitMSGTestSet(mu.msgtestsetPtr);
		}

		m_MarkUp.OutOfElem();
		mu_setting.push_back(mu);
	}
}


BOOL COnllyF66FileRead::ReadMUMSGTestSetXML(MSGTESTSETPtr& MuPtr)
{
	if (m_MarkUp.FindChildElem(_T("MSGTESTSET")))
	{
		m_MarkUp.IntoElem();
		GETCHILDELEMDATA(_T("nIndex"),MuPtr->nIndex,0);
		GETCHILDELEMDATA(_T("bCheck"),MuPtr->bCheck,0);
		GETCHILDELEMDATA(_T("nNum"),MuPtr->nNum,0);
		GETCHILDELEMDATA(_T("nTestType"),MuPtr->nTestType,0);
		GETCHILDELEMDATA(_T("TestBeginPt"),MuPtr->TestBeginPt,0);
		GETCHILDELEMDATA(_T("TestTypeSet1-0"),MuPtr->TestTypeSet[1][0],0);
		GETCHILDELEMDATA(_T("TestTypeSet2-0"),MuPtr->TestTypeSet[2][0],0);
		GETCHILDELEMDATA(_T("TestTypeSet2-1"),MuPtr->TestTypeSet[2][1],0);
		GETCHILDELEMDATA(_T("TestTypeSet3-0"),MuPtr->TestTypeSet[3][0],0);
		GETCHILDELEMDATA(_T("TestTypeSet3-1"),MuPtr->TestTypeSet[3][1],0);
		GETCHILDELEMDATA(_T("TestTypeSet4-0"),MuPtr->TestTypeSet[4][0],0);
		GETCHILDELEMDATA(_T("TestTypeSet4-1"),MuPtr->TestTypeSet[4][1],0);
		GETCHILDELEMDATA(_T("TestTypeSet5-0"),MuPtr->TestTypeSet[5][0],0);
		GETCHILDELEMDATA(_T("TestTypeSet5-1"),MuPtr->TestTypeSet[5][1],0);
		GETCHILDELEMDATA(_T("TestTypeSet5-2"),MuPtr->TestTypeSet[5][2],0);
		GETCHILDELEMDATA(_T("TestTypeSet6-0"),MuPtr->TestTypeSet[6][0],0);
		GETCHILDELEMDATA(_T("TestTypeSet6-1"),MuPtr->TestTypeSet[6][1],0);
		GETCHILDELEMDATA(_T("TestTypeSet6-2"),MuPtr->TestTypeSet[6][2],0);
		GETCHILDELEMDATA(_T("TestTypeSet7-0"),MuPtr->TestTypeSet[7][0],20);
		GETCHILDELEMDATA(_T("TestTypeSet7-1"),MuPtr->TestTypeSet[7][1],5);
		GETCHILDELEMDATA(_T("TestTypeSet8-0"),MuPtr->TestTypeSet[8][0],20);
		GETCHILDELEMDATA(_T("TestTypeSet8-1"),MuPtr->TestTypeSet[8][1],5);
		// 2012-10-15 报文抖动
		GETCHILDELEMDATA(_T("TestTypeSet9-0"),MuPtr->TestTypeSet[9][0],20);
		GETCHILDELEMDATA(_T("TestTypeSet9-1"),MuPtr->TestTypeSet[9][1],5);
		GETCHILDELEMDATA(_T("TestTypeSet9-2"),MuPtr->TestTypeSet[9][2],10);

		GETCHILDELEMDATA(_T("TestTypeSetA-0"),MuPtr->TestTypeSet[10][0],/*0,*/20);
		GETCHILDELEMDATA(_T("TestTypeSetA-1"),MuPtr->TestTypeSet[10][1],/*0,*/5);
		GETCHILDELEMDATA(_T("TestTypeSetA-2"),MuPtr->TestTypeSet[10][2],/*0,*/64);

		GETCHILDELEMDATA(_T("logicCheck"),MuPtr->logicCheck,0);
		GETCHILDELEMDATA(_T("nStartType"),MuPtr->nStartType,0);

		CString strText = _T("");
		for (int i=0;i<TestType;i++)
		{
			for (int j=0;j<PointNum;j++)
			{
				strText.Format(_T("ExpPtSet%d-%d"),i,j);
				GETCHILDELEMDATA(strText,MuPtr->ExpPtSet[i][j],0);
			}
		}
		m_MarkUp.OutOfElem();
		return TRUE;
	}

	return FALSE;
}
void COnllyF66FileRead::ReadMUChnCfgXML(vector<MU_CHNSET>& mu_chnset)
{
	if (m_MarkUp.FindChildElem(_T("MU_CHNSET")))
	{
		m_MarkUp.IntoElem();
		mu_chnset.clear();
		MU_CHNSET chnset;
		while(m_MarkUp.FindChildElem(_T("pmu_chnset")))
		{
			m_MarkUp.IntoElem();
			GETCHILDELEMDATA(_T("m_DOWD_Q"),chnset.m_DOWD_Q,0);
			GETCHILDELEMDATA(_T("nChnSel"),chnset.nChnSel,0);
			GetChildData(_T("strInput"),chnset.strInput);
			GETCHILDELEMDATA(_T("nIndex"),chnset.nIndex,0);
			GetChildData(_T("strChnName"),chnset.strChnName);
			GETCHILDELEMDATA(_T("bCheck"),chnset.bCheck,0);
			GETCHILDELEMDATA(_T("nTypeSel"),chnset.nTypeSel,-1);
			m_MarkUp.OutOfElem();
			mu_chnset.push_back(chnset);
		}
		m_MarkUp.OutOfElem();
	}
}

void COnllyF66FileRead::ReadGOOSEChnCfgXML(vector<GSECHNCFG>& gsechncfg)
{
	if (m_MarkUp.FindChildElem(_T("GSECHNCFG")))
	{
		m_MarkUp.IntoElem();
		GSECHNCFG chncfg;

		while(m_MarkUp.FindChildElem(_T("ChnCfg")))
		{
			m_MarkUp.IntoElem();
			GETCHILDELEMDATA(_T("nIndex"),chncfg.nIndex,0);
			GETCHILDELEMDATA(_T("nIOIndex"),chncfg.nIOIndex,0);
			GETCHILDELEMDATA(_T("nType"),chncfg.nType,0);
			GETCHILDELEMDATA(_T("strChnName"),chncfg.strChnName,_T(""));
			GETCHILDELEMDATA(_T("strValue"),chncfg.strValue,_T(""));
			//GETCHILDELEMDATA(_T("bInStruct"),chncfg.bInStruct,0,tchildPtr);
			GETCHILDELEMDATA(_T("bInStruct"),chncfg.bInStruct,0);
			gsechncfg.push_back(chncfg);
			m_MarkUp.OutOfElem();
		}
		m_MarkUp.OutOfElem();
	}
}
void COnllyF66FileRead::ReadMUMSGCfgDataXml(MuCfgData *ChDataPtr)
{

	m_MarkUp.IntoElem();
	int i = 0;
	while (m_MarkUp.FindChildElem(_T("mucfgdata")))
	{
		m_MarkUp.IntoElem();
		if (i >= MAX_TST_MUCHN) break;
		GETCHILDELEMDATA(_T("uIndex"),ChDataPtr[i].uIndex,0);//(int)
		GETCHILDELEMDATA(_T("uChnType"),ChDataPtr[i].uChnType,0);
		GETCHILDELEMDATA(_T("Mag"),ChDataPtr[i].Mag,0.0f);
		GETCHILDELEMDATA(_T("Ang"),ChDataPtr[i].Ang,0.0f);
		GETCHILDELEMDATA(_T("Fre"),ChDataPtr[i].Fre,0.0f);
		GETCHILDELEMDATA(_T("Quo"),ChDataPtr[i].Quo,0.0f);
		GETCHILDELEMDATA(_T("fStep"),ChDataPtr[i].fStep,0.0f);
		GETCHILDELEMDATA(_T("nSetData"),ChDataPtr[i].nSetData,0);

		GETCHILDELEMDATA(_T("fData1"),ChDataPtr[i].fData1,0.0f);
		GETCHILDELEMDATA(_T("fData2"),ChDataPtr[i].fData2,0.0f);

		GETCHILDELEMDATA(_T("fFirstData"),ChDataPtr[i].fFirstData,0.0f);
		GETCHILDELEMDATA(_T("fLastData"),ChDataPtr[i].fLastData,0.0f);
		GETCHILDELEMDATA(_T("bQuaTest"),ChDataPtr[i].bQuaTest,0);
		GETCHILDELEMDATA(_T("bVar"),ChDataPtr[i].bVar,0);
		GetChildData(_T("strName"),ChDataPtr[i].strName);
		m_MarkUp.OutOfElem();
		i++;
	}
	m_MarkUp.OutOfElem();
}

void COnllyF66FileRead::ReadMU92OpData(OTHER92OP& other92op)
{

	if (m_MarkUp.FindChildElem(_T("OHTER92OP")))
	{
		m_MarkUp.IntoElem();
		GETCHILDELEMDATA(_T("m_bCheckDatSet"),other92op.m_bCheckDatSet,0);
		GETCHILDELEMDATA(_T("m_bCheckRefrTm"),other92op.m_bCheckRefrTm,0);
		GETCHILDELEMDATA(_T("m_bCheckSmpRate"),other92op.m_bCheckSmpRate,0);
		GetChildData(_T("DatSet"),other92op.DatSet,_T(""));
		GETCHILDELEMDATA(_T("RefrTm"),other92op.RefrTm,0);
		GETCHILDELEMDATA(_T("SmpRate"),other92op.SmpRate,0);

		m_MarkUp.OutOfElem();
	}else
	{
		other92op.m_bCheckDatSet = 0;
		other92op.m_bCheckRefrTm = 0;
		other92op.m_bCheckSmpRate = 0;
		other92op.DatSet = _T("");
		other92op.RefrTm = 0;
		other92op.SmpRate = 4000;
	}
}

void COnllyF66FileRead::ReadGOOSECfgXML(vector<GSECFG>& GseCfg,const CString& NodeName)
{
	CString str;
	GSECFG gsecfg;
	GseCfg.clear();
	while(m_MarkUp.FindChildElem(NodeName))
	{
		m_MarkUp.IntoElem();
		GETCHILDELEMDATA(_T("AppID"),gsecfg.AppID,0);
		GETCHILDELEMDATA(_T("BinNum"),gsecfg.BinNum,0);
		GETCHILDELEMDATA(_T("ChkMask"),gsecfg.ChkMask,0);
		GETCHILDELEMDATA(_T("ConfRev"),gsecfg.ConfRev,0);
		GETCHILDELEMDATA(_T("DataSet"),gsecfg.DataSet,_T(""));
		GETCHILDELEMDATA(_T("GocbRef"),gsecfg.GocbRef,_T(""));
		GETCHILDELEMDATA(_T("GoID"),gsecfg.GoID,_T(""));
		GETCHILDELEMDATA(_T("LanNo"),gsecfg.LanNo,0);
		GETCHILDELEMDATA(_T("MacAddr"),gsecfg.MacAddr,_T(""));
		GETCHILDELEMDATA(_T("SourceMac"),gsecfg.SourceMac,_T("48-49-4A-4B-4C-4D"));
		GETCHILDELEMDATA(_T("NdsCom"),gsecfg.NdsCom,0);
		GETCHILDELEMDATA(_T("nIndex"),gsecfg.nIndex,0);
		GETCHILDELEMDATA(_T("Priority"),gsecfg.Priority,0);
		GETCHILDELEMDATA(_T("strDes"),gsecfg.strDes,_T(""));
		GETCHILDELEMDATA(_T("T0"),gsecfg.T0,0);
		GETCHILDELEMDATA(_T("T1"),gsecfg.T1,0);
		GETCHILDELEMDATA(_T("T2"),gsecfg.T2,0);
		GETCHILDELEMDATA(_T("T3"),gsecfg.T3,0);
		GETCHILDELEMDATA(_T("Test"),gsecfg.Test,0);
		GETCHILDELEMDATA(_T("TMult"),gsecfg.TMult,0);
		GETCHILDELEMDATA(_T("Used"),gsecfg.Used,0);
		GETCHILDELEMDATA(_T("VID"),gsecfg.VID,0);

		GETCHILDELEMDATA(_T("TTL"),gsecfg.TTL,10000);
		GETCHILDELEMDATA(_T("bTTL"),gsecfg.bTTL,0);
		GETCHILDELEMDATA(_T("bTQ"),gsecfg.bTQ,0);
		if(gsecfg.bTQ != 0 && gsecfg.bTQ != 1)
			gsecfg.bTQ = 0;
		GETCHILDELEMDATA(_T("Time"),gsecfg.Time,0);

		gsecfg.OldBinNum = gsecfg.BinNum;

		gsecfg.ChnCfg.clear();
		ReadGOOSEChnCfgXML(gsecfg.ChnCfg);

		/************************************************************************/
		/* zy 2012-4-12 读取Goose报文测试数据                                   */
		/************************************************************************/
		/*
		if (m_bSaveCfgFlg)
		{
		GETCHILDELEMDATA(_T("GSETESTSET"),str,_T(""));
		gsecfg.GsetestsetPtr = GsePktTestSetPtr(new GsePktTestSet);
		if (!tchildPtr->IsNull())
		{	
		ReadGsePktTestSetXML(tchildPtr,gsecfg.GsetestsetPtr);
		}
		else
		{
		InitGseTestSet(gsecfg.GsetestsetPtr);
		}
		}*/

		GseCfg.push_back(gsecfg);
		m_MarkUp.OutOfElem();
	}
}

void COnllyF66FileRead::ReadMUGerSet(MU_GENERALSETTTING& mu_gset)
{

	if (m_MarkUp.FindChildElem(_T("m_mugersetting")))
	{
		m_MarkUp.IntoElem();
		GETCHILDELEMDATA(_T("nSampleType"),mu_gset.nSampleType,0)
			GETCHILDELEMDATA(_T("dSampleRate"),mu_gset.dSampleRate,0);

		GETCHILDELEMDATA(_T("nMode1588"),mu_gset.nMode1588,0);
		GETCHILDELEMDATA(_T("nMuCfgNum"),mu_gset.nMuCfgNum,0);
		GETCHILDELEMDATA(_T("nAsduNum"),mu_gset.nAsduNum,0);
		GETCHILDELEMDATA(_T("dSecondCurrent"),mu_gset.dSecondCurrent,0.0f);
		GETCHILDELEMDATA(_T("dwConfRev"),mu_gset.dwConfRev,0);
		GETCHILDELEMDATA(_T("dFTSampleRate"),mu_gset.dFTSampleRate,0.0f);
		GETCHILDELEMDATA(_T("nFT3Format"),mu_gset.nFT3Format,1);
		GETCHILDELEMDATA(_T("bConver"),mu_gset.bConver,0);
		//2012-02-03
		GETCHILDELEMDATA(_T("bSynMode"),mu_gset.bSynMode,0);
		//2012-03-05
		GETCHILDELEMDATA(_T("nCurSelCtrl"),mu_gset.nCurSelCtrl,-1);

		//2012-09-07 异步时间
		GETCHILDELEMDATA(_T("uAsyncSet"),mu_gset.uAsyncSet,0);

		m_MarkUp.OutOfElem();
	}
}
