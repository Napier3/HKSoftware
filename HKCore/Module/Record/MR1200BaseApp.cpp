// MR1200BaseApp.cpp: implementation of the CMR1200BaseApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MR1200BaseApp.h"
#include "Comtrade/ComtradeMngr.h"

#ifndef _USE_NO_GUI_
#include "Draw/DrawGlobalDef.h"
#include "Draw/ViewAnalyse.h"
#endif
#ifndef _no_use_RecordCompare_
#include "Compare/RecordCompareTool.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CRecordTest *g_pCurrRecordTest;

//////////////////////////////////////////////////////////////////////////
//
CMR1200BaseApp g_theRecordApp;

CMR1200BaseApp::CMR1200BaseApp()
{
	CDFT::CreateDft();
	SetRecordDataModeComtrade();
	m_dRecordDataReadBeginTime = 0;
	m_bADStart = FALSE;
	//m_pRtMemBufferMngr = NULL;
	m_bCanJudgeStartup = FALSE;
	m_bCanFireSysMessage = FALSE;

	m_pRecordCompare = NULL;
	m_bRecordCmpDrawAllMatchCh = FALSE;
}

CMR1200BaseApp::~CMR1200BaseApp()
{
	UnloadRecordTest();
#ifndef _no_use_RecordCompare_
	FreeRecordCompare();
#endif
	CDFT::ReleaseDFT();
}


BOOL CMR1200BaseApp::IsRecordStartup()
{
	ASSERT (g_pCurrRecordTest != NULL);
	ASSERT (g_pCurrRecordTest->m_pStartup != NULL);
	
	if (g_pCurrRecordTest != NULL)
	{
		if (g_pCurrRecordTest->m_pStartup != NULL)
		{
			return g_pCurrRecordTest->m_pStartup->IsStartup();
		}
	}
	
	return FALSE;
}



void CMR1200BaseApp::SetOnlineExWriteBeginPos(long nWriteRecordBeginPos)
{
//	if (m_pMrOnlineThreadEx != NULL)
//	{
//		m_pMrOnlineThreadEx->g_pMrOnlineRecordEx->SetWriteRecordBeginPos(nWriteRecordBeginPos);
//	}
}


void CMR1200BaseApp::ReadComtradeFile()
{
	CRcdComtradeFile* pComtradeFile = CRcdComtradeFileMngr::OpenComtradeFile(m_strComtradeFilePath);
	
	//根据COMTRADE的文件大小映射CMrOnlineRecordEx的缓存长度，并关联缓冲区数据
	//这里一次性映射全部的长度，不考虑多次映射
	long nBufferLen = 0;//pComtradeFile->CalDataPoints(m_strComtradeFilePath) + 65536;  //增加点裕度
	//CMrOnlineRecordEx *pOnlineRecord = CMrOnlineRecordEx::g_pMrOnlineRecordEx;
	long nChBuffCount = pComtradeFile->GetChannelBuffferCount();
	long nIndex = 0;
	CComtradeDataBase *pComtradeCh = NULL;
// 	CShareMemClientEx *pMemClientEx = NULL;
	nBufferLen *= 2;
	
	//读取COMTRADE数据文件
	long nPoints = pComtradeFile->ReadComtradeFile(m_strComtradeFilePath, CMTRD_RDF_READDATA);

// 	nPoints *= 2;

	//设置起点时间和启动点时间
// 	memcpy(&g_oFirstDataTime,&(pMngr->m_oFirstPointTime),sizeof(RtTime));
// 	memcpy(&g_oStartupTime,&(pMngr->m_oTrigPointTime),sizeof(RtTime));


	//为每个通道关联缓存
	AttachOnlineRecordExBuffer(pComtradeFile, NULL);

	//FireSysOptrMsg(MR1200_SYSOPTR_ONLINE_RECORD_DATA_COPY, SYSOPTRPARA_ONLINERECORDDATACOPY_FINISH, MAKELONG(1, 1));
}


void CMR1200BaseApp::AttachOnlineRecordExBuffer(CRcdComtradeFile *pComtradeFile, CRecordTest *pRecordTest)
{
	//g_bCalUseRecordBuffer = FALSE;
	CRtVariables *pVariables = pRecordTest->m_pVariables;
	CRtVariable  *pVariable = NULL;
	//CMrOnlineRecordEx *pOnlineRecordEx = CMrOnlineRecordEx::g_pMrOnlineRecordEx;
	POS pos = pVariables->GetHeadPosition();
	long nAnalogChIndex = 0;
	CComtradeDataBase *pCh = NULL;
	POS posCh = pComtradeFile->GetHeadPosition();
	long nTotalPoints = pComtradeFile->GetTotalPoints();

	//处理模拟量通道
	while (pos != NULL)
	{
		pVariable = (CRtVariable*)pVariables->GetNext(pos);
		pCh = (CComtradeDataBase *)pComtradeFile->GetNext(posCh);

		if (pCh == NULL)
		{
			break;
		}

		if (pVariable->GetClassID() != RTCLASSID_BINARYVARIABLE && (pVariable->GetVariableUseState() > 0) )
		{
			pVariable->m_pAttachRecordBuffer = pCh->GetMemBuffer_UShort();
			pVariable->Set_ChIndex(nAnalogChIndex);
			nAnalogChIndex++;
		}

		if (pVariable->GetClassID() == RTCLASSID_BINARYVARIABLE && (pVariable->GetVariableUseState() > 0))
		{
			long nChIndex = nAnalogChIndex + ((CRtBinaryVariable*)pVariable)->m_nIndex / 16;
			pVariable->m_pAttachRecordBuffer = pCh->GetMemBuffer_UShort();
			pVariable->Set_ChIndex(nChIndex);
		}
	}

	pVariables->InitDataAttributeCalFunc(FALSE);
}


void CMR1200BaseApp::ReadComtradeFile(const CString& strPath)
{
	SetRecordDataModeComtrade();
	CRcdComtradeFile* pComtradeFile = CRcdComtradeFileMngr::OpenComtradeFile(strPath);

	//记录COMTRADE文件的路径
	m_strComtradeFilePath = strPath;
	ReadComtradeFile(pComtradeFile);
}

CRecordTest* CMR1200BaseApp::ReadComtradeFile(CRcdComtradeFile *pComtradeFile)
{
	//根据COMTRADE通道创建RecordTest
	CRecordTest *pRecordTest = InitRecordTestByComtradeEx(pComtradeFile);

	//限定谐波次数
	pRecordTest->ValidateAttrCal();

	//创建CMrOnlineThreadEx数据对象
	// 	if (m_pMrOnlineThreadEx == NULL)
	// 	{
	// 		m_pMrOnlineThreadEx = CMrOnlineThreadEx::CreateMrOnlineThreadEx();
	// 		ASSERT(m_pMrOnlineThreadEx != NULL);
	// 	}

	//给各变量关联缓冲区
	AttachOnlineRecordExBuffer(pComtradeFile, pRecordTest);

	// 	CComtradeMngr* pMngr = CComtradeMngr::CreateCComtradeMngr();
	// 	pMngr->ReadComtradeFile(strPath);
	// 	
	// 	
	// 	//初始化读comtradeFile标识
	// 	SetRecordDataModeComtrade();
	//pComtradeFile->Release();

	return pRecordTest;
}

long CMR1200BaseApp::UnloadRecordTest()
{

// 	if (g_pHarmHistogramConfig != NULL)
// 	{
// 		g_pHarmHistogramConfig->ReSetHarmList();
// 	}
// 
// 	if (m_pRecordTestCalThread != NULL)
// 	{
// 		m_pRecordTestCalThread->SetRecordTest(NULL);
// 	}

// 	if (m_pRecordTest != NULL)
// 	{
// 		delete m_pRecordTest;
// 		m_pRecordTest = NULL;
// 	}

// 	m_pMrGpsSysTime->AttachGPSBuffer(NULL);

// 	if (m_pRtMemBufferMngr != NULL)
// 	{
// 		m_pRtMemBufferMngr->Release();
// 		m_pRtMemBufferMngr = NULL;
// 	}

	return 0;
}


CRecordTest* CMR1200BaseApp::InitRecordTestByComtradeEx(CRcdComtradeFile *pComtradeFile)
{
	g_wBufferState = 1;
	long nAnalogChanAmount = 0;
	long nBinaryChanAmount = 0;
	POS pos = pComtradeFile->GetHeadPosition();
	long nIndex = 0;
	CRecordTest *pRecordTest = new CRecordTest();
	InitMR1200SysAnalyseMngr(pRecordTest->m_oMR1200SysAnalyseMngr);

// 	if (m_pRecordTest != NULL)
// 	{
// 		UnloadRecordTest();
// 	}

	//设置采样率
	if (pComtradeFile->m_pdSamRate != NULL)
	{
		pRecordTest->g_nSampleRate = (DWORD)(pComtradeFile->m_pdSamRate[0]);
	}

	//创建试验
	AddNewChild(pRecordTest);

	g_pCurrRecordTest = pRecordTest;
	CRtVariables* pVariables = new CRtVariables();
	pRecordTest->m_pVariables = pVariables;
	pVariables->SetParent(pRecordTest);
	pRecordTest->AddTail(pVariables);
	unsigned short* pPreBuffer = NULL;
	int iIndex = 0;

	while (pos != NULL)
	{
		CComtradeDataBase* pObj = (CComtradeDataBase*)pComtradeFile->GetNext(pos);

		if (pObj->IsAnalogData())
		{		
			CComtradeAnalogData* pAnalog = (CComtradeAnalogData*)pObj;
			CRtSingleVariable* pVariable = InitAnalogVariableByComtrade(pRecordTest, pAnalog, NULL, nAnalogChanAmount);
			pVariables->AddTail(pVariable);
			pVariable->SetParent(pVariables);
			pVariable->SetVariableUseState(1);
			pVariable->m_pRefRecordData = pAnalog;

			pVariables->SetVariable(pVariable, nAnalogChanAmount);

			nAnalogChanAmount++;

			PRECORDDRAWOBJECTCONTROL pDrawVar = &(pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl[iIndex]);
			nIndex++;
			pDrawVar->nShow = 1;
			pDrawVar->nUse  = 1;
			pDrawVar->dRange = pVariable->GetRangeEx();

		}
		else
		{
			CComtradeBinaryData* pBinary = (CComtradeBinaryData*)pObj;

			if (nBinaryChanAmount % 16 == 0)
			{
				nIndex++;
			}

			CRtBinaryVariable* pVariable = InitBinaryVariableByComtrade(pBinary, NULL, nBinaryChanAmount);
			pVariables->AddTail(pVariable);
			pVariable->SetParent(pVariables);
			pVariable->SetVariableUseState(1);
			nBinaryChanAmount++;

			PRECORDDRAWOBJECTCONTROL pDrawVar = &(pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl[iIndex]);
			pDrawVar->nShow = 1;
			pDrawVar->nUse  = 1;
			pDrawVar->dRange = 100;
		}

		iIndex++;
	}

	if (pVariables->GetCount() > 0)
	{
		pVariables->InitAttrsBuffer(pComtradeFile->m_nTotalPoints);
		pRecordTest->m_oMR1200SysAnalyseMngr.nCurrDrawObjectCount = iIndex;

		//先设置模拟量的
		InitMR1200SysAnalyseMngrDrawControl(pRecordTest->m_oMR1200SysAnalyseMngr, nAnalogChanAmount,nBinaryChanAmount);

		CRtVariable* pRefVariable = (CRtVariable*)pVariables->GetHead();
		pVariables->SetRefVariable(pRefVariable);
		//pVariables->InitDataAttributeCalFunc();
		InitHarmHistogram(pRecordTest->m_oMR1200SysAnalyseMngr.oHarmHistogram);
		InitSysAnalyseMngr_AttrSpy(&pRecordTest->m_oMR1200SysAnalyseMngr.oAttrSpy);
		InitSysAnalyseMngr_AttrDefault(&pRecordTest->m_oMR1200SysAnalyseMngr.oAttrDefault);
	}

	InitDrawControlByRecordTest(pRecordTest);	

	return pRecordTest;
}


CRtSingleVariable* CMR1200BaseApp::InitAnalogVariableByComtrade(CRecordTest *pRecordTest, CComtradeAnalogData* pAnalog,CRtMemBufferChannel* pChannel,long& nIndex)
{
	CString strID,str;
	CRtSingleVariable* pVariable = NULL;

	if (pAnalog == NULL)
	{
		return NULL;
	}

	pVariable = new CRtSingleVariable();
	pVariable->m_pChannelBuffer = pChannel; //不能使用InitBufferMngr函数因为没有BufferID
	pVariable->Set_ChIndex( nIndex );
	pVariable->m_strID		= pAnalog->m_strName;
	pVariable->m_strName    = pAnalog->m_strName;
	pVariable->m_strPhaseID = pAnalog->m_strPhaseID;
	pVariable->m_strUnit = pAnalog->m_strUnit;
	pVariable->m_strDCAC    = g_pszKeyVariableACDC;
	pRecordTest->g_pCoefValue[nIndex]    = pAnalog->m_dCoefValue;
	pRecordTest->g_pZeroValue[nIndex]    = pAnalog->m_dZeroValue;
	double dRange = pAnalog->GetRange();//m_dPrimaryValue / pAnalog->m_dSecondaryValue;
#ifndef _USE_NO_GUI_
	dRange = MrDraw::GetFloatCarryValue2(dRange);
#endif
	pVariable->SetRange(dRange);

	if (pAnalog->m_strUnit == "V")
	{
		pVariable->m_nType = RTVARIABLE_TYPE_U;
	}

	if (pAnalog->m_strUnit == "A")
	{
		pVariable->m_nType = RTVARIABLE_TYPE_I;
	}

	//根据相别添加颜色
	pVariable->m_crColor = GetPhaseColorByPhaseID(pVariable->m_strPhaseID, pVariable->m_strID);

	pAnalog->m_strUnit = pAnalog->m_strUnit;
	pVariable->CreateStaticAttrs(pAnalog->m_strName);

	return pVariable;
}

CRtBinaryVariable* CMR1200BaseApp::InitBinaryVariableByComtrade(CComtradeBinaryData* pBinary,CRtMemBufferChannel* pChannel,long& nIndex)
{
	CRtBinaryVariable* pVariable = NULL;

	if (pBinary != NULL)
	{
		pVariable = new CRtBinaryVariable();
		pVariable->m_pChannelBuffer = pChannel;
		pVariable->m_strName = pBinary->m_strName;
		pVariable->m_nIndex  = pBinary->m_nDataIndex;
		pVariable->m_crColor = RGB(0,255,0);

		CRtDataAttributes* pAttrs = new CRtDataAttributes();
		pVariable->m_pDataAttrs = pAttrs;
		pAttrs->SetParent(pVariable);
		pVariable->AddTail(pAttrs);
	}

	return pVariable;
}

// 
// CRtDataAttribute* CMR1200BaseApp::CreateAttrByID(const CString& strID,const CString& strVarName)
// {
// 	CRtDataAttribute* pAttr = new CRtDataAttribute();
// 	pAttr->m_strID = strID;
// 	pAttr->SetUse(0);
// 	pAttr->SetSpyState(0);
// 	pAttr->m_strName.Format("%s%s",strVarName,strID);
// 	return pAttr;
// }


void CMR1200BaseApp::InitDrawControlByRecordTest(CRecordTest* pRecordTest)
{
	if (pRecordTest == NULL)
	{
		return;
	}

	pRecordTest->InitDrawControl();
// 	long nBinarys = 0;
// 	long nAnalogs = 0;
// 	long nIndex   = 0;
// 	CRtVariables* pVariables = pRecordTest->m_pVariables;
// 
// 	if (pVariables == NULL)
// 	{
// 		return;
// 	}
// 
// 	POS pos = pVariables->GetHeadPosition();
// 	CRtVariable* pVariable = NULL;
// 	PRECORDDRAWOBJECTCONTROL pDrawSet = NULL;
// 
// 	while(pos != NULL)
// 	{
// 		pVariable = (CRtVariable*)pVariables->GetNext(pos);
// 		UINT nClassID = pVariable->GetClassID();
// 
// 		if (nClassID == RTCLASSID_SINGLEVARIABLE)
// 		{
// 
// 			pDrawSet = &(pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl[nIndex]);
// 			pDrawSet->nUse = pVariable->GetVariableUseState();				
// 			pDrawSet->nShow = pDrawSet->nUse;
// 			pDrawSet->dRange = ((CRtSingleVariable*)pVariable)->GetRangeEx();
// 			pDrawSet->dRangeGrid = pDrawSet->dRange * 2;
// 			nAnalogs++;
// 			nIndex++;
// 		}
// 		else if (nClassID == RTCLASSID_BINARYVARIABLE)
// 		{
// 			pDrawSet = &(pRecordTest->m_oMR1200SysAnalyseMngr.oDrawControl[nIndex]);
// 			pDrawSet->nUse = pVariable->GetVariableUseState();
// 			pDrawSet->nShow = 0;
// 			pDrawSet->dRange = 100;
// 			pDrawSet->dRangeGrid = pDrawSet->dRange * 2;
// 			nBinarys++;
// 			nIndex++;
// 		}
// 		else
// 		{
// 		}
// 	}
// 
// 	pRecordTest->m_oMR1200SysAnalyseMngr.nDrawObjectCount = nIndex;
// 	InitMR1200SysAnalyseMngrDrawControl(pRecordTest->m_oMR1200SysAnalyseMngr, nAnalogs,nBinarys);
}



void CMR1200BaseApp::InitRtFilterData()
{
// 	g_dwSampleRate = MR1200_SAMPLE_RATE / g_nSampleGap;
// 	MR1200_DFT_CAL_LEN = g_dwSampleRate / 50;
// 
// 	g_dwRtFilterDataLenPrev = RT_FILTER_DATA_LEN_PREV / g_nSampleGap;
// 	g_dwRtFilterDataLenNext = RT_FILTER_DATA_LEN_NEXT / g_nSampleGap;
// 
// 	if (g_dwRtFilterDataLenPrev < 6 || g_dwRtFilterDataLenNext < 6)
// 	{
// 		g_dwRtFilterDataLenPrev = 6;
// 		g_dwRtFilterDataLenNext = 6;
// 	}
// 
// 	g_dwRtFilterDataLenNext = g_dwRtFilterDataLenPrev;
// 	g_dwRtFilterDataLenLen  = g_dwRtFilterDataLenPrev + g_dwRtFilterDataLenNext + 1;
}

void CMR1200BaseApp::WaveAnalyseAll()
{
    #ifndef _USE_NO_GUI_
	POS pos = GetHeadPosition();
	CRecordTest *pRecordTest = NULL;
	CViewAnalyse *pViewAnalyse = NULL;

	while (pos != NULL)
	{
		pRecordTest = (CRecordTest *)GetNext(pos);
		ASSERT (pRecordTest->m_pWaveAnalyseViewRef != NULL);
		pViewAnalyse = (CViewAnalyse*)pRecordTest->m_pWaveAnalyseViewRef;

		if (pViewAnalyse == NULL)
		{
			continue;
		}

		pViewAnalyse->WaveAnalyse();
	}
#endif
}

#ifndef _no_use_RecordCompare_
void CMR1200BaseApp::RecordCompare()
{
	FreeRecordCompare();

	WaveAnalyseAll();
	CRecordCompareTool *pRecordCompareTool = new CRecordCompareTool();
	m_pRecordCompare = pRecordCompareTool;

	CRecordTest *pRecordTest1 = (CRecordTest*)GetHead();
	CRecordTest *pRecordTest2 = (CRecordTest*)GetTail();

	pRecordCompareTool->Compare(pRecordTest1, pRecordTest2);
}

void CMR1200BaseApp::RecordAnalyse()
{
	FreeRecordCompare();

	WaveAnalyseAll();
	CRecordCompareTool *pRecordCompareTool = new CRecordCompareTool();
	m_pRecordCompare = pRecordCompareTool;

	CRecordTest *pRecordTest1 = (CRecordTest*)GetHead();
	CRecordTest *pRecordTest2 = (CRecordTest*)GetTail();

	pRecordCompareTool->Compare(pRecordTest1, pRecordTest2);
}

BOOL CMR1200BaseApp::IsRcdCmpSucc()	
{
	CRecordCompareTool *pRecordCompareTool = (CRecordCompareTool*)m_pRecordCompare;

	return pRecordCompareTool->IsRcdCmpSucc();	
}

void CMR1200BaseApp::FreeRecordCompare()
{
	if (m_pRecordCompare != NULL)
	{
		delete m_pRecordCompare;
		m_pRecordCompare = NULL;
	}
}
#endif

long CMR1200BaseApp::GetTotalPoints(CRecordTest *pRecordTest)
{
	long nIndex = FindIndex(pRecordTest);
	CRcdComtradeFile *pFile = (CRcdComtradeFile*)CRcdComtradeFileMngr::GetComtradeFile(nIndex);

	return pFile->m_nTotalPoints;
}

#ifndef _no_use_RecordCompare_
CExBaseObject* CMR1200BaseApp::FindCmpVariable1(CExBaseObject *pVar2)
{
	ASSERT (m_pRecordCompare != NULL);
	CRecordCompareTool *pRecordCompareTool = (CRecordCompareTool*)m_pRecordCompare;

	return pRecordCompareTool->FindCmpVariable1(pVar2, m_bRecordCmpDrawAllMatchCh);
}

CDvmDataset* CMR1200BaseApp::GetRcdCmpResult()
{
	ASSERT (m_pRecordCompare != NULL);
	CRecordCompareTool *pRecordCompareTool = (CRecordCompareTool*)m_pRecordCompare;

	if (pRecordCompareTool != NULL)
	{
		return pRecordCompareTool->GetRcdCmpResult();
	}
	else
	{
		return NULL;
	}
}
#endif

// 
// BOOL CMR1200BaseApp::RcdCmp(const CString &strStdFile, const CString &strTestFie)
// {
// 	AfxGetMainWnd()->PostMessage(WM_RECORD_CMP_BEGIN, 0, 0);
// 
// 	return TRUE;
// }
// 
// void CMR1200BaseApp::RcdCmpClear()
// {
// 	m_strRcdCmpStdFile.Empty();
// 	m_strRcdCmpTestFile.Empty();
// 	AfxGetMainWnd()->PostMessage(WM_RECORD_CMP_CLEAR, 0, 0);
// }
// 

CRecordTest* CMR1200BaseApp::CreateNewCrecordTest()
{
	CRecordTest *pRecordTest = new CRecordTest();
	InitMR1200SysAnalyseMngr(pRecordTest->m_oMR1200SysAnalyseMngr);
	pRecordTest->g_nSampleRate = 4000;//默认为每周波80点

	//创建试验
	AddNewChild(pRecordTest);

	g_pCurrRecordTest = pRecordTest;

	//兼容2009年的模式，没有在构造函数中新建Variables
	CRtVariables* pVariables = new CRtVariables();
	pRecordTest->m_pVariables = pVariables;
	pVariables->SetParent(pRecordTest);
	pRecordTest->AddTail(pVariables);
	
	//没有通道，暂时不初始化绘图控制部分
	//InitDrawControlByRecordTest(pRecordTest);	

	return pRecordTest;
}

