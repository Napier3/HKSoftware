// RecordCompareTool.cpp: implementation of the CRecordCompareTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordCompareTool.h"
#include "..\..\API\FileApi.h"
#include "..\..\API\MathApi.h"
#include "..\..\API\GlobalConfigApi.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRecordCompareTool::CRecordCompareTool()
{
	m_pRecordTest1 = NULL;
	m_pRecordTest2 = NULL;

	m_bAlignRlt = 0;
	m_nBeginPos1 = 0;
	m_nBeginPos2 = 0;
	m_nAlignPos1 = 0;
	m_nAlignPos2 = 0;
	m_nEndPos1 = 0;
	m_nEndPos2 = 0;

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("CfgTestConfig.xml");
	m_oCfgTestConfig.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CRecordCompareTool::~CRecordCompareTool()
{
	m_listCmpVariable.RemoveAll();
}

void CRecordCompareTool::Compare(CRecordTest *pRecordTest1, CRecordTest *pRecordTest2)
{
	m_pRecordTest1 = pRecordTest1;
	m_pRecordTest2 = pRecordTest2;

	//创建比较对象
	CreateCmpVariableEx(pRecordTest1->m_pVariables, pRecordTest2->m_pVariables
		, m_pRecordTest1->g_nSampleRate, m_pRecordTest2->g_nSampleRate);//, m_fSetValForFind, m_fSetValForCmp);

	if (GetCount() == 0)
	{
		CreateCmpVariable(pRecordTest1->m_pVariables, pRecordTest2->m_pVariables
			, m_pRecordTest1->g_nSampleRate, m_pRecordTest2->g_nSampleRate);//, m_fSetValForFind, m_fSetValForCmp);
	}

	InitCmpVariablesList();

	//对齐波形位置
	AlignRecord();

	//准备测试结果
	InitCmpResult();
}

void CRecordCompareTool::InitCmpVariablesList()
{
	POS pos = GetHeadPosition();
	CRecordCmpVariable *p = NULL;

	while (pos != NULL)
	{
		p = (CRecordCmpVariable *)GetNext(pos);

		if (p->IsAlignSucc())
		{
			m_listCmpVariable.AddTail(p);
		}
	}
}

void CRecordCompareTool::CreateCmpVariableEx(CRtVariables *pRtVariables1, CRtVariables *pRtVariables2
										   , long nSampleRate1, long nSampleRate2)
{
	CRtVariable *p = NULL;
	POS pos = pRtVariables1->GetHeadPosition();
	CRecordCmpVariable *pNew = NULL;
	CRtSingleVariable *pSingle = NULL;

	while (pos != NULL)
	{
		p = (CRtVariable *)pRtVariables1->GetNext(pos);

		if (p->GetClassID() != RTCLASSID_SINGLEVARIABLE)
		{
			continue;
		}

		pSingle = (CRtSingleVariable *)p;

		if (pSingle->m_strPhaseID == _T("A") || pSingle->m_strPhaseID == _T("B") || pSingle->m_strPhaseID == _T("C"))
		{
			pNew = CreateCmpVariable((CRtSingleVariable*)p, pRtVariables2, nSampleRate1, nSampleRate2);
		}
	}
}

void CRecordCompareTool::CreateCmpVariable(CRtVariables *pRtVariables1, CRtVariables *pRtVariables2
										   , long nSampleRate1, long nSampleRate2)
{
	CRtVariable *p = NULL;
	POS pos = pRtVariables1->GetHeadPosition();
	CRecordCmpVariable *pNew = NULL;

	while (pos != NULL)
	{
		p = (CRtVariable *)pRtVariables1->GetNext(pos);

		if (p->GetClassID() != RTCLASSID_SINGLEVARIABLE)
		{
			continue;
		}

		pNew = CreateCmpVariable((CRtSingleVariable*)p, pRtVariables2, nSampleRate1, nSampleRate2);
	}
}

CRecordCmpVariable* CRecordCompareTool::CreateCmpVariable(CRtSingleVariable *pVariable, CRtVariables *pRtVariables
														   , long nSampleRate1, long nSampleRate2)
{
	CRecordCmpVariable *pNew = NULL;
	CRtSingleVariable *pFind = FindCmpVariable(pVariable, pRtVariables);

	if (pFind == NULL)
	{
		return NULL;
	}

	double dRange = pVariable->GetRange();
	float fSetValForFind = dRange * 0.01;
	float fSetValForCmp = dRange * 0.1;
	pVariable->m_nVariableUse = 1;
	pFind->m_nVariableUse = 1;
	pNew = new CRecordCmpVariable(pVariable, pFind, nSampleRate1, nSampleRate2, fSetValForFind, fSetValForCmp);
	AddNewChild(pNew);

	return pNew;
}

CRtSingleVariable* CRecordCompareTool::FindCmpVariable(CRtSingleVariable *pVariable, CRtVariables *pRtVariables)
{
	CRtVariable *p = NULL;
	CRtSingleVariable *pFind = NULL;
	CRtSingleVariable *pSingle = NULL;
	POS pos = pRtVariables->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CRtVariable *)pRtVariables->GetNext(pos);

		if (p->GetClassID() != RTCLASSID_SINGLEVARIABLE)
		{
			continue;
		}

		pSingle = (CRtSingleVariable*)p;

		if (pSingle->m_strPhaseID == pVariable->m_strPhaseID && pSingle->m_strUnit == pVariable->m_strUnit)
		{
			pFind = pSingle;
			break;
		}
	}

	return pFind;
}

BOOL CRecordCompareTool::AlignRecord()
{
	m_bAlignRlt = 0; 
	CRecordCmpVariable *pFind = NULL;
	long nTotalPoints1 = g_theRecordApp.GetTotalPoints(m_pRecordTest1);
	long nTotalPoints2 = g_theRecordApp.GetTotalPoints(m_pRecordTest2);
	long nAlignPos1 = -1;
	long nAlignPos2 = -1;
	nAlignPos2 = nTotalPoints2;

	pFind = GetAlignPosVariable2(nAlignPos2);

	if (pFind == NULL)
	{
		return FALSE;
	}

	nAlignPos1 = pFind->m_nAllignPosition1;
	m_nAlignPos2 = nAlignPos2;
	m_nAlignPos1 = nAlignPos1;

	//计算波形的起点和终点
	double dTimeAfter2 = nTotalPoints2 - nAlignPos2;
	double dTime2 = nAlignPos2;
	dTimeAfter2    /= m_pRecordTest2->g_nSampleRate;
	dTime2           /= m_pRecordTest2->g_nSampleRate;

	//基于波形2，将对齐的波形1，向前、向后推dTimeBefore2、dTimeAfter2
	double dTimeBefore1 = 0;
	double dTimeAfter1 = dTimeAfter2;
	double dTime1 = nAlignPos1;
	dTime1           /= m_pRecordTest1->g_nSampleRate;
	dTimeBefore1  = dTime1 -  dTime2;
	dTimeAfter1    = dTime1 + dTimeAfter2;
	
	double dTimeOffset = 0;
	double dPointsOffset = 0;

	//向前调整位置
	//如果波形1前部波形数据少，调整波形2位置
	if (dTimeBefore1 < 0)
	{
		dTimeOffset = -dTimeBefore1;
		dPointsOffset = dTimeOffset * m_pRecordTest2->g_nSampleRate;
		m_nBeginPos1 = 0; //波形1起点为0
		m_nBeginPos2 = (long)dPointsOffset;
	}
	else
	{//如果波形1前部波形数据多，调整波形1位置
		dTimeOffset = dTimeBefore1;
		dPointsOffset = dTimeOffset * m_pRecordTest1->g_nSampleRate;
		m_nBeginPos1 = (long)dPointsOffset;
		m_nBeginPos2 = 0;
	}

	
	//向后调整位置
	//如果波形1后部波形数据少，调整波形2位置
	if (dTimeAfter1 < dTimeAfter2)
	{
		dTimeOffset = dTimeAfter2 - dTimeAfter1;
		dPointsOffset = dTimeOffset * m_pRecordTest2->g_nSampleRate;
		m_nEndPos1 = nTotalPoints1; //波形1起点为0
		m_nEndPos2 = nTotalPoints2 - (long)dPointsOffset;
	}
	else
	{//如果波形1后部波形数据多，调整波形1位置
		dTimeOffset = dTimeAfter2;
		dPointsOffset = dTimeOffset * m_pRecordTest1->g_nSampleRate;
		m_nEndPos1 = (long)dPointsOffset;
		m_nEndPos1 += nAlignPos1 - 1;
		m_nEndPos2 = nTotalPoints2-1;
	}

	m_bAlignRlt = 1;
	return TRUE;
}

CRecordCmpVariable* CRecordCompareTool::GetAlignPosVariable2(long &nAlignPos)
{
	POS pos = m_listCmpVariable.GetHeadPosition();
	CRecordCmpVariable *p = NULL;
	CRecordCmpVariable *pFind = NULL;

	while (pos != NULL)
	{
		p = (CRecordCmpVariable *)m_listCmpVariable.GetNext(pos);

		if (p->GetAlignPosVariable2(nAlignPos))
		{
			pFind = p;
		}
	}

	return pFind;
}

void CRecordCompareTool::SetVariablesUse(CRtVariables *pRtVariables, BOOL bUse)
{
	POS pos = pRtVariables->GetHeadPosition();
	CRtVariable *p = NULL;

	while (pos != NULL)
	{
		p = (CRtVariable *)pRtVariables->GetNext(pos);
		p->m_nVariableUse = bUse;
	}
}

CExBaseObject* CRecordCompareTool::FindCmpVariable1(CExBaseObject *pVar2, BOOL bRecordCmpDrawAllMatchCh)
{
	CRecordCmpVariable *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CRecordCmpVariable *)GetNext(pos);

		if (!bRecordCmpDrawAllMatchCh)
		{
			if (!p->IsAlignSucc())
			{
				continue;
			}
		}

		if (p->m_pRtVariable2 == pVar2)
		{
			return p->m_pRtVariable1;
		}
	}

	return NULL;
}

void CRecordCompareTool::InitCmpResult()
{
	m_oCmpResult.DeleteAll();

	InitCmpResult_Fault();

	InitCmpResult_Other();

	//录波文件格式测试
	InitCmpResult_Cfg();

	//单通道位图
	InitCmpResult_Single_bmp();

	CString strRlt;
	strRlt.Format(_T("%ld"),m_bAlignRlt);
	m_oCmpResult.AddNewData(_T("cmp_rslt"), _T("cmp_rslt"), _T("int"), strRlt);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("rcd_cmp_result.xml");
	m_oCmpResult.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CRecordCompareTool::InitCmpResult_Fault()
{
	m_pRecordTest1->CalCurrValuesFromPos(m_nBeginPos1);
	m_pRecordTest2->CalCurrValuesFromPos(m_nBeginPos2);
	InitCmpResult_Fault(_T("Pre"));

	//相位差
	InitCmpResult_Fault_Ph_Pp(m_pRecordTest2->m_pVariables, _T("Cmp_Pre"));

	if (m_nAlignPos1 == -1 || m_nAlignPos2 == -1)
	{
		return;
	}

	//故障态
	m_pRecordTest1->CalCurrValuesFromPos(m_nAlignPos1);
	m_pRecordTest2->CalCurrValuesFromPos(m_nAlignPos2);
	InitCmpResult_Fault(_T("Aft"));

	//故障后稳态
	long nCyclePoints1 = m_pRecordTest1->g_nSampleRate * 2 / 50;
	long nCyclePoints2 = m_pRecordTest2->g_nSampleRate * 2 / 50;
	m_pRecordTest1->CalCurrValuesFromPos(m_nAlignPos1 + nCyclePoints1);
	m_pRecordTest2->CalCurrValuesFromPos(m_nAlignPos2 + nCyclePoints2);
	InitCmpResult_Fault(_T("Aft2"));
}

void CRecordCompareTool::InitCmpResult_Fault_Ph_Pp(CRtVariables *pRtVariables, const CString &strPrefix)
{
	CRtSingleVariable *pIa = pRtVariables->FindVariable(_T("Ia"));
	CRtSingleVariable *pIb = pRtVariables->FindVariable(_T("Ib"));
	CRtSingleVariable *pIc = pRtVariables->FindVariable(_T("Ic"));

	if (pIa == NULL || pIb == NULL || pIc == NULL)
	{
		return;
	}

	double dPh = NULL;
	CString strValue, strValID;

	dPh = pIb->m_oCurrValue.dFundPhase - pIa->m_oCurrValue.dFundPhase;
	MakeAngleTo180(dPh);
	dPh = abs(dPh);
	strValue.Format(_T("%f"), dPh);
	strValID.Format(_T("%s_Ph_Iab"), strPrefix);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	dPh = pIc->m_oCurrValue.dFundPhase - pIb->m_oCurrValue.dFundPhase;
	MakeAngleTo180(dPh);
	dPh = abs(dPh);
	strValue.Format(_T("%f"), dPh);
	strValID.Format(_T("%s_Ph_Ibc"), strPrefix);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	dPh = pIc->m_oCurrValue.dFundPhase - pIa->m_oCurrValue.dFundPhase;
	MakeAngleTo180(dPh);
	dPh = abs(dPh);
	strValue.Format(_T("%f"), dPh);
	strValID.Format(_T("%s_Ph_Ica"), strPrefix);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

}

void CRecordCompareTool::InitCmpResult_Fault(const CString &strPrefix)
{
	POS pos = m_listCmpVariable.GetHeadPosition();
	CRecordCmpVariable *pCmpVar = NULL;

	while (pos != NULL)
	{
		pCmpVar = (CRecordCmpVariable *)m_listCmpVariable.GetNext(pos);
		InitCmpResult_Variable(pCmpVar->m_pRtVariable1, _T("Std"), strPrefix);
		InitCmpResult_Variable(pCmpVar->m_pRtVariable2, _T("Cmp"), strPrefix);
	}
}

//单通道位图,20220918,LiuMy
void CRecordCompareTool::InitCmpResult_Single_bmp()
{
	CString strValID, strValue_Stea,strValue_Tran,strName,strValue_File,strVar;
	double dValue = 0;

	POS pos = m_listCmpVariable.GetHeadPosition();
	CRecordCmpVariable *pCmpVar = NULL;

	while(pos != NULL)
	{
		pCmpVar = (CRecordCmpVariable *)m_listCmpVariable.GetNext(pos);
		//Steady
		CRcdComtradeFile *pComtradeFile = CRcdComtradeFileMngr::GetComtradeFile(1);
		strValue_File = ParseFileName(pComtradeFile->m_strComtradeFile);
		strVar = pCmpVar->m_pRtVariable2->CmbVariableID();
		strName.Format(_T("稳态录波通道%s_波形文件"), strVar);
		strValID.Format(_T("%s_bmp_file_Steady"), strVar);
		strValue_Stea.Format(_T("%s-%s-1"),strValue_File,strVar);
		strValue_Stea = ChangeFilePostfix(strValue_Stea, _T("bmp"));
		m_oCmpResult.AddNewData(strName, strValID, _T("File"), strValue_Stea);
		
		//Transient
		strName.Format(_T("暂态录波通道%s_波形文件"), strVar);
		strValID.Format(_T("%s_bmp_file_Transient"), strVar);
		strValue_Tran.Format(_T("%s-%s-2"),strValue_File,strVar);
		strValue_Tran = ChangeFilePostfix(strValue_Tran, _T("bmp"));
		m_oCmpResult.AddNewData(strName, strValID, _T("File"), strValue_Tran);
	}
}

void CRecordCompareTool::InitCmpResult_Variable(CRtSingleVariable *pRtVariable, const CString &strType, const CString &strPrefix)
{
	//频率、总有效值、基波有效值
	CString strVarID, strValID;

	strVarID = pRtVariable->CmbVariableID();
	CString strValID_Pre;
	CString strValue;
	strValID_Pre.Format(_T("%s_%s_%s_"), strType, strPrefix, strVarID);

	//频率
	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_Frequancy];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dFrequency);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	//总有效值
/*
	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_EffecValue];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dEffecValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_EffecPhase];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dEffecPhase);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
*/

	//基波有效值
	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_FundValue];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dFundValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_FundPhase];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dFundPhase);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
}

void CRecordCompareTool::InitCmpResult_Other()
{
	CString strValID, strValue;
	double dValue = 0;

	//采样率
	strValID = _T("Std_SampleRate");
	strValue.Format(_T("%d"), m_pRecordTest1->g_nSampleRate);
	m_oCmpResult.AddNewData(strValID, strValID, _T("long"), strValue);

	strValID = _T("Cmp_SampleRate");
	strValue.Format(_T("%d"), m_pRecordTest2->g_nSampleRate);
	m_oCmpResult.AddNewData(strValID, strValID, _T("long"), strValue);

	//启动前/后周波数
	CRcdComtradeFile *pFile = CRcdComtradeFileMngr::GetComtradeFile(1);
	dValue = pFile->CalCyclesBeforeStart();
	strValID = _T("Cmp_Cycles_Befre_Start");
	strValue.Format(_T("%f"), dValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
	double dTotalCycles = pFile->GetTotalPoints();
	dTotalCycles /= pFile->GetSampleRate();
	dTotalCycles *= pFile->m_dFreq;
	dTotalCycles -= dValue;
	strValID = _T("Cmp_Cycles_After_Start");
	strValue.Format(_T("%f"), dTotalCycles);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	//故障前周波数
	dValue = m_nAlignPos2;
	dValue /= m_pRecordTest2->g_nSampleRate;
	dValue *= 50;
	strValID = _T("Cmp_Pre_Cycles");
	strValue.Format(_T("%f"), dValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	//故障后周波数
	dValue = m_nEndPos2 - m_nAlignPos2;
	dValue /= m_pRecordTest2->g_nSampleRate;
	dValue *= 50;
	strValID = _T("Cmp_Aft_Cycles");
	strValue.Format(_T("%f"), dValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	//是否存在零序
	long nCount = m_pRecordTest2->m_pVariables->GetCountByPhaseID(_T("0"), _T("A"));

	//去掉不正确的零序表达方式
// 	if (nCount == 0)
// 	{
// 		nCount = m_pRecordTest2->m_pVariables->GetCountByPhaseID(_T("O"), _T("A"));
// 	}
// 
// 	if (nCount == 0)
// 	{
// 		nCount = m_pRecordTest2->m_pVariables->GetCountByPhaseID(_T("o"), _T("A"));
// 	}

	strValID = _T("Cmp_I0_Count");
	strValue.Format(_T("%d"), nCount);
	m_oCmpResult.AddNewData(strValID, strValID, _T("long"), strValue);

	InitCmpResult_PeakVellay();

	//位图文件
	CRcdComtradeFile *pComtradeFile = CRcdComtradeFileMngr::GetComtradeFile(1);
	strValue = ParseFileName(pComtradeFile->m_strComtradeFile);
	strValue = ChangeFilePostfix(strValue, _T("bmp"));
	strValID = _T("Cmp_bmp_file");
	m_oCmpResult.AddNewData(strValID, strValID, _T("file"), strValue);
}

//通过Variable2的通道名称获得峰值,Liumy,20220927
double CRecordCompareTool::FindPeakValueByStrName(double PeakValue, CString strPh)
{

	long nCyclePoints2 = m_pRecordTest2->g_nSampleRate * 2 / 50;
	m_pRecordTest2->CalValues_PeakVellay(m_nAlignPos2, nCyclePoints2);

	POS pos = m_listCmpVariable.GetHeadPosition();
	CRecordCmpVariable *pCmpVar = NULL;
	while (pos != NULL)
	{
		pCmpVar = (CRecordCmpVariable *)m_listCmpVariable.GetNext(pos);
		if( pCmpVar->m_pRtVariable2->m_strName == strPh )
		{
			PeakValue = pCmpVar->m_pRtVariable2->m_oCurrValue.dPeakValue;
		}
	}
	return PeakValue;
}

void CRecordCompareTool::InitCmpResult_PeakVellay()
{
	CString strValID, strValue, strVar;
	double dValue = 0;

	long nCyclePoints1 = m_pRecordTest1->g_nSampleRate * 2 / 50;
	long nCyclePoints2 = m_pRecordTest2->g_nSampleRate * 2 / 50;

	m_pRecordTest1->CalValues_PeakVellay(m_nAlignPos1, nCyclePoints1);
	m_pRecordTest2->CalValues_PeakVellay(m_nAlignPos2, nCyclePoints2);
	POS pos = m_listCmpVariable.GetHeadPosition();
	CRecordCmpVariable *pCmpVar = NULL;

	while (pos != NULL)
	{
		pCmpVar = (CRecordCmpVariable *)m_listCmpVariable.GetNext(pos);

		//Std
		strVar = pCmpVar->m_pRtVariable1->CmbVariableID();

		strValID.Format(_T("Std_%s_Peak"), strVar);
		strValue.Format(_T("%f"), pCmpVar->m_pRtVariable1->m_oCurrValue.dPeakValue);
		m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

		strValID.Format(_T("Std_%s_Vellay"), strVar);
		strValue.Format(_T("%f"), pCmpVar->m_pRtVariable1->m_oCurrValue.dVellayValue);
		m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

		//Cmp
		strVar = pCmpVar->m_pRtVariable2->CmbVariableID();

		strValID.Format(_T("Cmp_%s_Peak"), strVar);
		strValue.Format(_T("%f"), pCmpVar->m_pRtVariable2->m_oCurrValue.dPeakValue);
		m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

		strValID.Format(_T("Cmp_%s_Vellay"), strVar);
		strValue.Format(_T("%f"), pCmpVar->m_pRtVariable2->m_oCurrValue.dVellayValue);
		m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
	}
}

//////////////////////////////////////////////////////////////////////////
//单个波形分析
void CRecordCompareTool::InitAnalyseResult()
{
	m_oCmpResult.DeleteAll();

	InitAnalyseResult_Fault();

	InitAnalyseResult_Other();

	InitCmpResult_Cfg();

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("rcd_analyse_result.xml");
	m_oCmpResult.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CRecordCompareTool::InitAnalyseResult_Fault()
{
	m_pRecordTest1->CalCurrValuesFromPos(m_nBeginPos1);
	InitAnalyseResult_Fault(_T(""));

}

void CRecordCompareTool::InitAnalyseResult_Fault(const CString &strPrefix)
{
	POS pos = m_pRecordTest1->m_pVariables->GetHeadPosition();
	CRtVariable *pVariable = NULL;

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)m_pRecordTest1->m_pVariables->GetNext(pos);

		if (pVariable->IsRtSingleVariable())
		{
			InitAnalyseResult_Variable((CRtSingleVariable*)pVariable, _T(""), strPrefix);
		}
	}
}

void CRecordCompareTool::InitAnalyseResult_Variable(CRtSingleVariable *pRtVariable, const CString &strType, const CString &strPrefix)
{
	//频率、总有效值、基波有效值
	CString strVarID, strValID;

	strVarID = pRtVariable->CmbVariableID();
	CString strValID_Pre;
	CString strValue;

	if (strType.GetLength() > 0)
	{
		strValID_Pre.AppendFormat(_T("%s_"), strType);
	}

	if (strPrefix.GetLength() > 0)
	{
		strValID_Pre.AppendFormat(_T("%s_"), strPrefix);
	}

	strValID_Pre.AppendFormat(_T("%s_"), strVarID);

	//频率
	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_Frequancy];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dFrequency);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	//总有效值
/*
	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_EffecValue];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dEffecValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_EffecPhase];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dEffecPhase);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
*/

	//基波有效值
	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_FundValue];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dFundValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	strValID = strValID_Pre;
	strValID += g_pszChannelKeyAttrID[SingleVariableAttrID_FundPhase];
	strValue.Format(_T("%f"), pRtVariable->m_oCurrValue.dFundPhase);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
}

void CRecordCompareTool::InitAnalyseResult_Other()
{
	CString strValID, strValue;
	double dValue = 0;

	//采样率
	strValID = _T("SampleRate");
	strValue.Format(_T("%d"), m_pRecordTest1->g_nSampleRate);
	m_oCmpResult.AddNewData(strValID, strValID, _T("long"), strValue);

	//启动前/后周波数
	CRcdComtradeFile *pFile = CRcdComtradeFileMngr::GetComtradeFile(0);
	dValue = pFile->CalCyclesBeforeStart();
	strValID = _T("Cycles_Before_Start");
	strValue.Format(_T("%f"), dValue);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
	double dTotalCycles = pFile->GetTotalPoints();
	dTotalCycles /= pFile->GetSampleRate();
	dTotalCycles *= pFile->m_dFreq;
	dTotalCycles -= dValue;
	strValID = _T("Cycles_After_Start");
	strValue.Format(_T("%f"), dTotalCycles);
	m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

	//是否存在零序
	long nCount = m_pRecordTest2->m_pVariables->GetCountByPhaseID(_T("0"), _T("A"));

	if (nCount == 0)
	{
		nCount = m_pRecordTest2->m_pVariables->GetCountByPhaseID(_T("O"), _T("A"));
	}

	if (nCount == 0)
	{
		nCount = m_pRecordTest2->m_pVariables->GetCountByPhaseID(_T("o"), _T("A"));
	}

	strValID = _T("I0_Count");
	strValue.Format(_T("%d"), nCount);
	m_oCmpResult.AddNewData(strValID, strValID, _T("long"), strValue);

	InitAnalyseResult_PeakVellay();

	//位图文件
	CRcdComtradeFile *pComtradeFile = CRcdComtradeFileMngr::GetComtradeFile(0);
	strValue = ParseFileName(pComtradeFile->m_strComtradeFile);
	strValue = ChangeFilePostfix(strValue, _T("bmp"));
	strValID = _T("Analyse_bmp_file");
	m_oCmpResult.AddNewData(strValID, strValID, _T("file"), strValue);
}

void CRecordCompareTool::InitAnalyseResult_PeakVellay()
{
	CString strValID, strValue, strVar;
	double dValue = 0;

	long nCyclePoints1 = m_pRecordTest1->g_nSampleRate * 2 / 50;

	m_pRecordTest1->CalValues_PeakVellay(m_nBeginPos1, nCyclePoints1);
	POS pos = m_pRecordTest1->m_pVariables->GetHeadPosition();
	CRtVariable *pVariable = NULL;
	CRtSingleVariable *pRtSingleVariable = NULL;

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)m_pRecordTest1->m_pVariables->GetNext(pos);

		if (!pVariable->IsRtSingleVariable())
		{
			continue;
		}

		pRtSingleVariable = (CRtSingleVariable*)pVariable;
		strVar = pRtSingleVariable->CmbVariableID();

		strValID.Format(_T("%s_Peak"), strVar);
		strValue.Format(_T("%f"), pRtSingleVariable->m_oCurrValue.dPeakValue);
		m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);

		strValID.Format(_T("%s_Vellay"), strVar);
		strValue.Format(_T("%f"), pRtSingleVariable->m_oCurrValue.dVellayValue);
		m_oCmpResult.AddNewData(strValID, strValID, _T("float"), strValue);
	}
}


void CRecordCompareTool::InitCmpResult_Cfg()
{
	//目标录波文件的格式测试
	//Cfg_U_Count,Cfg_I_Count,Cfg_U_Order,Cfg_I_Order,Cfg_UI_Order_Rslt
	InitCmpResult_Cfg_Order();

	//Cfg_UI_Name_Rslt,Cfg_UI_Name_Err
	InitCmpResult_Cfg_Name();
	
	//Cfg_Phase_Rslt,Cfg_Phase_Err
	InitCmpResult_Cfg_Phase();
}

void CRecordCompareTool::InitCmpResult_Cfg_Order()
{
	//Cfg_U_Count,Cfg_I_Count,Cfg_U_Order,Cfg_I_Order,Cfg_UI_Order_Rslt
	CRcdComtradeFile *pFile = CRcdComtradeFileMngr::GetComtradeFile(1);
	CString strValue;

	strValue.Format(_T("%d"), pFile->GetUCount());
	m_oCmpResult.AddNewData(_T("Cfg_U_Count"), _T("Cfg_U_Count"), _T("long"), strValue);
	strValue.Format(_T("%d"), pFile->GetICount());
	m_oCmpResult.AddNewData(_T("Cfg_I_Count"), _T("Cfg_I_Count"), _T("long"), strValue);

	strValue.Format(_T("%d"), pFile->GetUOrder());
	m_oCmpResult.AddNewData(_T("Cfg_U_Order"), _T("Cfg_U_Order"), _T("long"), strValue);
	strValue.Format(_T("%d"), pFile->GetIOrder());
	m_oCmpResult.AddNewData(_T("Cfg_I_Order"), _T("Cfg_I_Order"), _T("long"), strValue);

	if (pFile->GetUOrder() == 0)
	{
		strValue = _T("1");
	}
	else
	{
		strValue = _T("0");
	}

	m_oCmpResult.AddNewData(_T("Cfg_UI_Order_Rslt"), _T("Cfg_UI_Order_Rslt"), _T("long"), strValue);

}

void CRecordCompareTool::InitCmpResult_Cfg_Name()
{
	CRcdComtradeFile *pFile = CRcdComtradeFileMngr::GetComtradeFile(1);
	CExBaseList *pAnalogs = pFile->GetAnalogs();
	POS pos = pAnalogs->GetHeadPosition();
	CComtradeAnalogData *pAnalog = NULL;
	CString strError ,strRslt;

	while (pos != NULL)
	{
		pAnalog = (CComtradeAnalogData *)pAnalogs->GetNext(pos);
		InitCmpResult_Cfg_Name(pAnalog->m_strUnit, pAnalog->m_strPhaseID, pAnalog->m_strName, strError);
	}

	if (strError.GetLength() == 0)
	{
		strRslt = _T("1");
	}
	else
	{
		strRslt = _T("0");
	}

	m_oCmpResult.AddNewData(_T("Cfg_UI_Name_Rslt"), _T("Cfg_UI_Name_Rslt"), _T("long"), strRslt);
	m_oCmpResult.AddNewData(_T("Cfg_UI_Name_Err"), _T("Cfg_UI_Name_Err"), _T("string"), strError);
}

void CRecordCompareTool::InitCmpResult_Cfg_Name(const CString &strUnit, const CString &strCh, const CString &strName, CString &strError)
{
	POS pos = m_oCfgTestConfig.GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_oCmpResult.GetNext(pos);

		if (pData->m_strUnit == strUnit && pData->m_strDataType == strCh)
		{
			if (pData->FindByName(strName) == NULL)
			{
				strError.AppendFormat(_T("[%s,%s:%s error]"), strUnit, strCh, strName);
			}

			break;
		}
	}
}


void CRecordCompareTool::InitCmpResult_Cfg_Phase()
{
	CRcdComtradeFile *pFile = CRcdComtradeFileMngr::GetComtradeFile(1);
	CExBaseList *pAnalogs = pFile->GetAnalogs();
	POS pos = pAnalogs->GetHeadPosition();
	CComtradeAnalogData *pAnalog = NULL;
	CString strError ,strRslt;
	CString strPhase;

	while (pos != NULL)
	{
		pAnalog = (CComtradeAnalogData *)pAnalogs->GetNext(pos);
		
		if (pAnalog->m_strPhaseID == _T("A") || pAnalog->m_strPhaseID == _T("B") 
			|| pAnalog->m_strPhaseID == _T("C") || pAnalog->m_strPhaseID == _T("0"))
		{

		}
		else
		{
			strError.AppendFormat(_T("[%s:%s Error]"), pAnalog->m_strName, pAnalog->m_strPhaseID);
		}
	}

	if (strError.GetLength() == 0)
	{
		strRslt = _T("1");
	}
	else
	{
		strRslt = _T("0");
	}

	m_oCmpResult.AddNewData(_T("Cfg_Phase_Rslt"), _T("Cfg_Phase_Rslt"), _T("long"), strRslt);
	m_oCmpResult.AddNewData(_T("Cfg_Phase_Err"), _T("Cfg_Phase_Err"), _T("string"), strError);
}
