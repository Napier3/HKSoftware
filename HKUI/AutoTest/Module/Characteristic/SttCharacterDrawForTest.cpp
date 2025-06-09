// CharacterDrawForTest.cpp : 实现文件
//

#include "stdafx.h"
#include "SttCharacterDrawForTest.h"
#include "../../../Module/DataMngr/DataMngrTrans.h"

//#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
//#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCharacterDrawForTest
CSttCharacterDrawForTest::CSttCharacterDrawForTest()
{
	m_pCharDrawView = NULL;
	m_pCharacteristic = NULL;
	m_pCharacteristics = NULL;
	m_nType = CurrInverseTime;
}

CSttCharacterDrawForTest::~CSttCharacterDrawForTest()
{
	if (m_pCharDrawView != NULL)
	{
		delete m_pCharDrawView;
		m_pCharDrawView = NULL;
	}
}

void CSttCharacterDrawForTest::OnPaint(CDC *pDC)
{
	if (m_pCharDrawView == NULL)
	{
		return;
	}

	if (!m_pCharDrawView->HasDefChar())
	{
		return;
	}

	//特性曲线图
	m_pCharDrawView->Draw(pDC, 1, CPoint(0, 0));

	//当前搜索线
	if (m_pMacroCharItemLineDef == NULL)
	{
		return;
	}

	if (m_pMacroCharItemLineDef->m_nSearchActb)
	{

	}
}

void CSttCharacterDrawForTest::CreateCharacterDrawView()
{
	if (m_pCharDrawView == NULL)
	{
		m_pCharDrawView = new CCharacterDrawView();
	}

	m_pCharDrawView->UI_SetActiveElement(NULL);
}

void CSttCharacterDrawForTest::InitCharDrawTest(CExBaseObject *pItem)
{
	CSttItems *pSttItems = stt_gb_get_ancestor_items_has_char(pItem);

	if (pSttItems == NULL)
	{
		if (m_pCharDrawView != NULL)
		{
			delete m_pCharDrawView;
			m_pCharDrawView = NULL;
		}
	}
	else
	{
		CSttCharacteristic* pSttChar = (CSttCharacteristic*)pSttItems->FindByClassID(STTGBXMLCLASSID_CSTTCHARACTERISTIC);
		InitCharDrawTest(pSttItems->m_strCharacteristicID, CString_To_long(pSttChar->m_strIndex));
	}
}

void CSttCharacterDrawForTest::InitCharDrawTest(const CString &strCharID, long nIndex)
{
	CCharacteristic *pFind = NULL;
	CExBaseObject *pCurrObj = NULL;
	POS pos = m_pCharacteristics->GetHeadPosition();

	while (pos)
	{
		pCurrObj = m_pCharacteristics->GetNext(pos);

		if (pCurrObj->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
		{
			continue;
		}

		CCharacteristic *pTemp = (CCharacteristic*)pCurrObj;

		if(CString_To_long(pTemp->m_strIndex) == nIndex && pTemp->m_strID == strCharID)
		{
			pFind = pTemp;
			break;
		}
	}

	if (pFind == NULL)
	{
		delete m_pCharDrawView;
		m_pCharDrawView = NULL;
		return;
	}

	if (m_pCharacteristic == pFind)
	{
		return;
	}

	BOOL bShowLine = TRUE;

	if (m_nType == Distance)
	{
		bShowLine = FALSE;
	}

	InitCharacterDrawView(pFind,bShowLine);
	m_pCharacteristic = pFind;

	CAxisInterface *pAxisInterface = NULL;
	m_pCharDrawView->GetAxisInterface(&pAxisInterface);

	if (pAxisInterface != NULL)
	{
		CDataGroup oAxisConfig;
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_WorkAreaBkColor,(long)RGB(0, 0, 128));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisGridLineColor,(long)RGB(192, 192, 192));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisGridLineColor,(long)RGB(192, 192, 192));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterLineWidth,(long)2);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisCenterColor,(long)RGB(172, 172, 172));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorFrom,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_XAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_YAxisWorkAreaBackColorTo,(long)RGB(255, 255, 255));
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisScaleFont,(long)12);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisNameFont,(long)14);
		oAxisConfig.AddNewData(AXIS_CONFIG_ID_AxisTopGap,(long)26);
		pAxisInterface->SetAxisConfig(&oAxisConfig);
	}

	CXDrawMngr* pXDrawMngr = m_pCharDrawView->GetXDrawMngr_Axis();
	pXDrawMngr->InitDrawLineColor(RGB(0, 255, 0));
}

void CSttCharacterDrawForTest::InitCharDrawTestAxis(long nType)
{
	BOOL bShowLine = TRUE;
	m_nType = nType;

	if (nType == Distance)
	{
		bShowLine = FALSE;
	}

	if (m_pCharDrawView == NULL)
	{
		InitCharacterDrawView(m_pCharacteristics,bShowLine);
	}

	CXDrawMngr* pXDrawMngr = m_pCharDrawView->GetXDrawMngr_Axis();
	CString strAxis = "cartes";

	switch(nType)
	{
	case CurrInverseTime:
	case VolInverseTime: 
		strAxis = _T("logarithm");
		break;
	case DiffCurr6I:
	default:
		break;
	}

	if (pXDrawMngr->m_strAxis != strAxis)
	{
		delete m_pCharDrawView;
		m_pCharDrawView = NULL;
		InitCharacterDrawView(m_pCharacteristics,bShowLine);
	}

	switch(nType)
	{
	case CurrInverseTime:
		m_pCharDrawView->SetAxisName(_T("I/In"),_T("t(s)"),_T("I* - t"));
		break;
	case VolInverseTime: 
		m_pCharDrawView->SetAxisName(_T("U(V)"),_T("t(s)"),_T("U - t"));
		break;
	case DiffCurr6I:
		m_pCharDrawView->SetAxisName(_T("Ir(A)"),_T("Id(A)"),_T(" "));
		break;
	default:
		m_pCharDrawView->SetAxisName(_T("R"),_T("X"),_T("R-X(omg)"));
		break;
	}
}

CSttMacroCharItemLineDef* CSttCharacterDrawForTest::UpdateMacroTest(CExBaseObject *pMacroTest, CDataGroup *pSearchReport, CDataGroup *pSearchLine)
{
	CValues oValues;
	DvmDatas_to_Values(pSearchReport, &oValues);
	return UpdateMacroTest(pMacroTest, &oValues);
}

CSttMacroCharItemLineDef* CSttCharacterDrawForTest::UpdateMacroTest(CExBaseObject *pMacroTest, CValues *pSearchReport)
{
	if (m_pMacroCharItemLineDef == NULL)
	{
		return m_pMacroCharItemLineDef;
	}

	m_pMacroCharItemLineDef->InitSearchValues(pSearchReport);

	UpdateCurrTestPoint(m_pMacroCharItemLineDef->m_fSearchXc, m_pMacroCharItemLineDef->m_fSearchYc);

	if (m_pMacroCharItemLineDef->m_nSearchActb != TESTLINE_ACT_STATE_NONE)
	{
// 		m_strValXb.Format(_T("%f"), pMacroCharItemLineDef->m_fSearchXb);
// 		m_strValYb.Format(_T("%f"), pMacroCharItemLineDef->m_fSearchYb);

		if (m_pMacroCharItemLineDef->m_nSearchActb)
		{
// 			m_strValActb = CXLanguageResourceAts_AutoTest::g_sLangTxt_Act/*_T("动作")*/;
		}
		else
		{
// 			m_strValActb = CXLanguageResourceAts_AutoTest::g_sLangTxt_Unact/*_T("未动作")*/;
		}
	}
	else
	{
// 		m_strValXb = _T("--");
// 		m_strValYb = _T("--");
// 		m_strValActb = _T("--");
	}


	if (m_pMacroCharItemLineDef->m_nSearchActe != TESTLINE_ACT_STATE_NONE)
	{
// 		m_strValXe.Format(_T("%f"), pMacroCharItemLineDef->m_fSearchXe);
// 		m_strValYe.Format(_T("%f"), pMacroCharItemLineDef->m_fSearchYe);
// 
// 		if (pMacroCharItemLineDef->m_nSearchActe)
// 		{
// 			m_strValActe = CXLanguageResourceAts_AutoTest::g_sLangTxt_Act/*_T("动作")*/;
// 		}
// 		else
// 		{
// 			m_strValActe = CXLanguageResourceAts_AutoTest::g_sLangTxt_Unact/*_T("未动作")*/;
// 		}
	}
	else
	{
// 		m_strValXe = _T("--");
// 		m_strValYe = _T("--");
// 		m_strValActe = _T("--");
	}

// 	m_strValXc.Format(_T("%f"), pMacroCharItemLineDef->m_fSearchXc);
// 	m_strValYc.Format(_T("%f"), pMacroCharItemLineDef->m_fSearchYc);

	//UpdateData(FALSE);
// 	m_edtValXb.SetWindowText(m_strValXb);
// 	m_edtValYb.SetWindowText(m_strValYb);
// 	m_edtValActb.SetWindowText(m_strValActb);
// 	m_edtValXe.SetWindowText(m_strValXe);
// 	m_edtValYe.SetWindowText(m_strValYe);
// 	m_edtValActe.SetWindowText(m_strValActe);
// 	m_edtValXc.SetWindowText(m_strValXc);
// 	m_edtValYc.SetWindowText(m_strValYc);

	return m_pMacroCharItemLineDef;
}

CCharTestLine*  CSttCharacterDrawForTest::UpdateMacroTest(CExBaseObject *pMacroTest, CSttReport *pReport)
{
// 	CMacroCharItems *pMacroCharItems = (CMacroCharItems*)pMacroTest->GetParent();
// 	CCharTestLine *pCharTestLine = pMacroCharItems->UpdateMacroTest(pMacroTest, pReport);
// 
// 	//更新动作点
// 	InitCharacterDrawView(m_pCharacteristic);
// 
// 	return pCharTestLine;
	return NULL;
}


void CSttCharacterDrawForTest::InitByMacroTestPara_r_angle(CValues *pValues, const CString &strParaIDX, double &dValueX, const CString &strParaIDY, double &dValueY, const CString &strParaIDFlag, long &nValueFlag)
{
	BOOL bX = pValues->GetValue(strParaIDX, dValueX);
	BOOL bY = pValues->GetValue(strParaIDY, dValueY);
	BOOL bF = pValues->GetValue(strParaIDFlag, nValueFlag);

	CValue *pValue = (CValue*)pValues->FindByID(strParaIDFlag);

	if (pValue != NULL)
	{
		if (pValue->m_strValue == g_sLangTxt_Act/*_T("动作")*/)
		{
			nValueFlag = 1;
		}
		else if (pValue->m_strValue == g_sLangTxt_Unact/*_T("未动作")*/)
		{
			nValueFlag = 0;
		}
	}

	if (!bX)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_UndefinDataPara.GetString()/*_T("没有定义“%s”数据变量")*/
			, strParaIDX.GetString());
	}

	if (!bY)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_UndefinDataPara.GetString()/*_T("没有定义“%s”数据变量")*/
			, strParaIDY.GetString());
	}

	if (!bF)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_UndefinDataPara.GetString()/*_T("没有定义“%s”数据变量")*/
			, strParaIDFlag.GetString());
	}

	if (! (bX && bY && bF) )
	{
		return;
	}

	if (nValueFlag == 1)
	{
		if (m_pMacroCharItemLineDef->IsAxisMode_r_angle())
		{
			CComplexNumber oComplex(dValueX, dValueY, COMPLEX_MODE_DEGREE);
			oComplex.GetValue(dValueX, dValueY);
		}
	}
}

void CSttCharacterDrawForTest::InitMacroCharItemLineDef(const CString &strItemID)
{
	
}

BOOL CSttCharacterDrawForTest::HasCharDrawCreated(CCharacteristic *pCharTemp)
{
	if (m_pCharDrawView == NULL)
	{
		return FALSE;
	}

	return (m_pCharDrawView->HasDefChar(pCharTemp));
}

void CSttCharacterDrawForTest::InitCharacterDrawView(CCharacteristic *pCharTemp, BOOL bViewTestLines, BOOL bCalCharTemp)
{
	//创建m_pCharacterDrawView
	CreateCharacterDrawView();

	//XCreateElement：创建整个特性曲线的绘图对象，创建坐标系和绘图数据
	m_pCharDrawView->XCreateElement(pCharTemp, NULL, bViewTestLines, bCalCharTemp);
}


void CSttCharacterDrawForTest::InitCharacterDrawView(CCharacteristics *pChars, BOOL bViewTestLines, BOOL bCalCharTemp)
{
	CreateCharacterDrawView();
	m_pCharDrawView->XCreateElement(pChars, NULL, bViewTestLines, bCalCharTemp);
}

void CSttCharacterDrawForTest::SetActiveElement(CCharElement *pElement)
{
	if (m_pCharDrawView == NULL)
	{
		return;
	}

	if (pElement == NULL)
	{
		m_pCharDrawView->UI_SetActiveElement(NULL);
	}
	else
	{
		m_pCharDrawView->UI_SetActiveElement((CXDrawElement*)pElement->m_pDataRef);
	}
}

void CSttCharacterDrawForTest::UpdateCurrTestPoint(double dX, double dY)
{
	m_pCharDrawView->UpdateCurrTestPoint(dX, dY);
}

void CSttCharacterDrawForTest::FreeCurrTestPoint()
{
	m_pCharDrawView->FreeCurrTestPoint();
}

void CSttCharacterDrawForTest::OnSize(CDC *pDC, int cx, int cy)
{
	if (m_pCharDrawView == NULL)
	{
		return;
	}

	CRect rcBorder = m_pCharDrawView->GetBorder();

	if (rcBorder.Height() == cy && rcBorder.Width() == cx)
	{
		return;
	}

	CRect rcClient(0, 0, cx, cy);
	m_pCharDrawView->SetBorder(rcClient, pDC);
}
