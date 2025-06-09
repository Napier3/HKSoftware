#include "QCharTestPointsGrid.h"
#include "../../SttTestCntrCmdDefine.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../../AutoTest/Module/XLanguageResourceAts.h"

QCharTestPointsGrid::QCharTestPointsGrid(CCharacteristics *pCharacteristics,QWidget *parent)
	: QExBaseListGridBase(parent)
{
	m_pCurrCharacteristic = NULL;
	m_pCharacteristics = pCharacteristics;
	m_strCurrMacroID = _T("");
	m_strTestPointDescX = /*_T("制动电流")*/g_sLangTxt_State_BrakingCur; //lcq
	m_strTestPointDescY = /*_T("差动电流")*/g_sLangTxt_State_DifferentCur; //lcq
	connect(this, SIGNAL(sig_UpdateCurrTestPoint(QString,QString,double ,double)),
		this, SLOT(slot_UpdateCurrTestPoint(QString,QString,double ,double)),Qt::QueuedConnection);
}

QCharTestPointsGrid::~QCharTestPointsGrid()
{
	m_oTestPointsList.DeleteAll/*RemoveAll*/();
}

void QCharTestPointsGrid::InitGrid()
{
	InitGridTitle();

	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QCharTestPointsGrid::InitGridTitle()
{
	CString astrGridTitle[CHARTESTPOINTS_GRID_COLS];
	int iGridWidth[CHARTESTPOINTS_GRID_COLS]={100, 100,100, 100,100, 100};
	astrGridTitle[0] = /*_T("名称")*/g_sLangTxt_Name; //lcq
	astrGridTitle[1] = /*_T("类型")*/g_sLangTxt_Type; //lcq
	astrGridTitle[2] = m_strTestPointDescX;
	astrGridTitle[3] = m_strTestPointDescY;
	astrGridTitle[4] = /*_T("动作值")*/g_sLangTxt_State_ActionValue; //lcq
	astrGridTitle[5] = /*_T("误差")*/g_sLangTxt_State_Error; //lcq
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CHARTESTPOINTS_GRID_COLS);
}

void QCharTestPointsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CHARCLASSID_CCHARTESTLINE)
	{
		return;
	}

	CString strText,strIndex;
	CCharTestLine *pCharTestLine = (CCharTestLine *)pData;
	strText = /*_T("测试点")*/g_sLangTxt_State_Testpoints; //lcq
	strIndex.Format(_T("%d"),nRow);
	strText += strIndex;
 	Show_StaticString(pData, nRow, 0, strText);

	if (pCharTestLine->m_strType == _T("user"))
	{
		strText = /*_T("自定义")*/g_sLangTxt_Custom; //lcq
	} 
	else
	{
		strText = /*_T("系统生成")*/g_sLangTxt_State_Sysgenerated; //lcq
	}

	Show_StaticString(pData, nRow, 1, strText);

	if ((m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest)||
		(m_strCurrMacroID == STT_ORG_MACRO_DistSearchOneTest))
	{
		CComplexNumber oCompNum(pCharTestLine->m_fXset, pCharTestLine->m_fYset);
		double dZValue = 0.0f,dAngleValue = 0.0f;
		dZValue = sqrt(pow(pCharTestLine->m_fXset, 2) + pow(pCharTestLine->m_fYset, 2));
		dAngleValue = oCompNum.GetAngle_180_180();
		strText.Format(_T("%.03lf"),dZValue);
		Show_StaticString(pData, nRow, 2, strText);

		strText.Format(_T("%.03lf"),dAngleValue);
		Show_StaticString(pData, nRow, 3, strText);
	}
	else
	{
		strText.Format(_T("%.03lf"),pCharTestLine->m_fXset);
		Show_StaticString(pData, nRow, 2, strText);

		strText.Format(_T("%.03lf"),pCharTestLine->m_fYset);
		Show_StaticString(pData, nRow, 3, strText);
	}
	
	Show_StaticString(pData, nRow, 4, _T("--"));
	Show_StaticString(pData, nRow, 5, _T("--"));
	nRow++;
}

void QCharTestPointsGrid::UpdateCurrTestPoint(const CString &strCharaID,const CString &strIndex,
												double dX,double dY)
{
	emit sig_UpdateCurrTestPoint(strCharaID,strIndex,dX,dY);
}

void QCharTestPointsGrid::InitMacroID(const CString &strMacroID)
{
	m_strCurrMacroID = strMacroID;
	m_pCurrCharacteristic = NULL;
}

void QCharTestPointsGrid::AddTestResultPoint(double dX,double dY,BOOL bHasAct,double dX_set,double dY_set)
{
	CCharTestLine *pCurrObj = NULL, *pFind = NULL;
	POS pos = m_oTestPointsList.GetHeadPosition();

	while(pos)
	{
		pCurrObj = (CCharTestLine *)m_oTestPointsList.GetNext(pos);

		//yzj 2023.11.8 上送的误差会有时候会略大于0.001(过励磁出现了0.0011)
		if ((fabs(pCurrObj->m_fXset - dX_set)<0.002)&&(fabs(pCurrObj->m_fYset - dY_set)<0.002))
		{
			pFind = pCurrObj;
			break;
		}
	}

	if (pFind == NULL)
	{
		return;
	}

	UpdateResult(pFind,dX,dY,bHasAct);
}

void QCharTestPointsGrid::UpdateResult(CExBaseObject *pData,double dX,double dY,BOOL bHasAct)
{
	int nRow = GetDataRow(pData, 1);

	if (nRow < 0)
	{
		return;
	}

	DisConnectAll_SigSlot();

	CString strActValue,strErrorValue;
	CCharTestLine *pCharTestLine = (CCharTestLine *)pData;
	double dErrorValue = 0.0f;

	if (bHasAct)
	{
		if ((m_strCurrMacroID == STT_ORG_MACRO_DiffCurr6ITest)||(m_strCurrMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)
			||(m_strCurrMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)||(m_strCurrMacroID == STT_ORG_MACRO_ElecRailwayDiffTest)
			|| (m_strCurrMacroID == STT_ORG_MACRO_DiffTest_I))
		{
// 			if (m_pCurrCharacteristic && 
// 				(m_pCurrCharacteristic->m_strID == _T("PsuDiffHarmTest"))||(m_pCurrCharacteristic->m_strID == _T("ElecRailwayDiffHarmTest")))
			if ( IsDiffHarmTest() )   //add by shaolei  2023-9-8 
			{
				strActValue.Format(_T("%.03lf"),dX);;
				dErrorValue = dX-pCharTestLine->m_fXset;
				strErrorValue.Format(_T("%.03lf"),dErrorValue);
			} 
			else
			{
				strActValue.Format(_T("%.03lf"),dY);;
				dErrorValue = dY-pCharTestLine->m_fYset;
				strErrorValue.Format(_T("%.03lf"),dErrorValue);
			}
		}
		else if (m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest
			||(m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest_I))
		{
			strActValue.Format(_T("%.03lf"),dY);;
			dErrorValue = dY-pCharTestLine->m_fYset;
			strErrorValue.Format(_T("%.03lf"),dErrorValue);
		}
		else if (m_strCurrMacroID == STT_ORG_MACRO_UFInverseTimeTest)
		{
			strActValue.Format(_T("%.03lf"),dY);
			dErrorValue = dY-pCharTestLine->m_fYset;
			strErrorValue.Format(_T("%.03lf"),dErrorValue);
		}
		else if ((m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest)
			||(m_strCurrMacroID == STT_ORG_MACRO_DistSearchOneTest))
		{
			double dSetValue = sqrt(pow(pCharTestLine->m_fXset, 2) + pow(pCharTestLine->m_fYset, 2));
			double dActValue = sqrt(pow(dX, 2) + pow(dY, 2));
			strActValue.Format(_T("%.03lf"),dActValue);
			dErrorValue = dActValue-dSetValue;
			strErrorValue.Format(_T("%.03lf"),dErrorValue);
		}
		else if (m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest
			||(m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I))
		{
			strActValue.Format(_T("%.03lf"),dY);
			dErrorValue = dY-pCharTestLine->m_fYset;
			strErrorValue.Format(_T("%.03lf"),dErrorValue);
		}
		else 
		{
			strActValue.Format(_T("%.03lf"),dY);
			dErrorValue = dY-pCharTestLine->m_fYset;
			strErrorValue.Format(_T("%.03lf"),dErrorValue);
		}
	} 
	else
	{
		strActValue = /*_T("未动作")*/g_sLangTxt_State_NoActioned; //lcq
		strErrorValue =  _T("--");
	}

	Show_StaticString(pData, nRow, 4, strActValue);
	Show_StaticString(pData, nRow, 5, strErrorValue);
	
// 	strText.Format(_T("%.03lf"),pCharTestLine->m_fYset);
// 	Show_StaticString(pData, nRow, 3, strText);

//	ShowData(pData, nRow, FALSE);
	ConnectAll_SigSlot();
}

BOOL QCharTestPointsGrid::IsDiffHarmTest()
{
	// if (m_pCurrCharacteristic && 
	// (m_pCurrCharacteristic->m_strID == _T("PsuDiffHarmTest"))||(m_pCurrCharacteristic->m_strID == _T("ElecRailwayDiffHarmTest")))
	if (m_pCurrCharacteristic == NULL)
	{
		return FALSE;
	}

	if ( (m_pCurrCharacteristic->m_strID == _T("PsuDiffHarmTest"))||
		(m_pCurrCharacteristic->m_strID == _T("ElecRailwayDiffHarmTest")))
	{
		return TRUE;
	}

	return FALSE;
}

void QCharTestPointsGrid::ClearSearchPoints()
{
	m_pCurrCharacteristic = NULL;
}

void QCharTestPointsGrid::ClearSearchPoint(long nPtIndex)
{
	if(m_pCurrCharacteristic)
	{
		int nRowIndex = 0;
		CExBaseList* pDatas = &m_oTestPointsList;
		CExBaseObject *pObj = NULL;	
		POS pos = pDatas->GetHeadPosition();
		while (pos != NULL)
		{
			pObj = pDatas->GetNext(pos);
			if(nRowIndex != nPtIndex)
			{
				nRowIndex++;
			}
			else
			{
				ShowData(pObj, nRowIndex, FALSE);
				return;
			}
		}
	}
}

void QCharTestPointsGrid::ClearSearchPointsFrom(long nPtIndex)
{
	long nCount = m_oTestPointsList.GetCount();
	int nRowIndex = 0;
	CExBaseList* pDatas = &m_oTestPointsList;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		if(nRowIndex < nPtIndex)
		{
			nRowIndex++;
		}
		else
		{
			ShowData(pObj, nRowIndex, FALSE);
		}
	}
}

void QCharTestPointsGrid::ShowCharacteristic(CCharacteristic *pCharacteristic)
{
	m_oTestPointsList.DeleteAll/*RemoveAll*/();

	if (pCharacteristic == NULL)
	{
		ShowDatas(NULL);
		return;
	}

	CCharacterArea *pCharArea = pCharacteristic->GetCharacterArea();
	POS pos_line = pCharArea->GetHeadPosition();
	CExBaseList *pLineList = NULL;
	CExBaseObject *pCurrObj = NULL;

	while(pos_line)
	{
		pLineList = (CExBaseList *)pCharArea->GetNext(pos_line);

		if (pLineList->GetClassID() == CHARCLASSID_CCHARTESTOBJECTS)
		{
			continue;
		}

		POS pos_test = pLineList->GetHeadPosition();

		while(pos_test)
		{
			pCurrObj = pLineList->GetNext(pos_test);

			if (pCurrObj->GetClassID() == CHARCLASSID_CCHARTESTLINE)
			{
				m_oTestPointsList.AddTail((CExBaseObject*)pCurrObj->Clone());
			}
		}
	}

	CCharElement *pCCharElement = pCharArea->GetCharBisector();

	if (pCCharElement != NULL)
	{
		POS pos_test = pCCharElement->GetHeadPosition();

		while(pos_test)
		{
			pCurrObj = pCCharElement->GetNext(pos_test);

			if (pCurrObj->GetClassID() == CHARCLASSID_CCHARTESTLINE)
			{
				m_oTestPointsList.AddTail((CExBaseObject*)pCurrObj->Clone());
			}
		}
	}

	ShowDatas(&m_oTestPointsList);

// 	while(pos_line)
// 	{
// 		pLineList = (CExBaseList *)pCharArea->GetNext(pos_line);
// 
// 		if (pLineList->GetClassID() == CHARCLASSID_CCHARTESTOBJECTS)
// 		{
// 			continue;
// 		}
// 
// 		POS pos_test = pLineList->GetHeadPosition();
// 
// 		while(pos_test)
// 		{
// 			pCurrObj = pLineList->GetNext(pos_test);
// 
// 			if (pCurrObj->GetClassID() == CHARCLASSID_CCHARTESTLINE)
// 			{
// 				m_oTestPointsList.AddTail((CExBaseObject*)pCurrObj->Clone());
// 			}
// 		}
// 	}
// 
// 	ShowDatas(&m_oTestPointsList);
}

void QCharTestPointsGrid::slot_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY)
{
	CString strCharaIDNew,strIndexNew;
	strCharaIDNew = strCharaID;
	strIndexNew = strIndex;
	CCharacteristic *pCurrCharacteristic = NULL;

	if (strCharaIDNew.IsEmpty() && strIndexNew.IsEmpty())
	{
		pCurrCharacteristic = (CCharacteristic*)m_pCharacteristics->FindByClassID(CHARCLASSID_CCHARACTERISTIC);
	}
	else
	{
		pCurrCharacteristic = m_pCharacteristics->FindCharByID_Index(strCharaIDNew,strIndexNew);
	}

	if (pCurrCharacteristic == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("特性曲线查找失败(strCharaID=%s;strIndex=%s),无法更新项目列表.")*/g_sLangTxt_State_CurlfailedItems.GetString(),
			strCharaIDNew.GetString(),strIndexNew.GetString()); //lcq
		pCurrCharacteristic = (CCharacteristic*)m_pCharacteristics->FindByClassID(CHARCLASSID_CCHARACTERISTIC);

		if (pCurrCharacteristic == NULL)
		{
		return;
	}
//		return;
	}

	if (m_pCurrCharacteristic != pCurrCharacteristic)
	{
		m_pCurrCharacteristic = pCurrCharacteristic;

		if ((m_strCurrMacroID == STT_ORG_MACRO_DiffCurr6ITest)||(m_strCurrMacroID == STT_ORG_MACRO_LineDiffCurr6ITest)
			||(m_strCurrMacroID == STT_ORG_MACRO_BusDiffCurr6ITest)||(m_strCurrMacroID == STT_ORG_MACRO_ElecRailwayDiffTest))
		{
			if ((strCharaID == _T("PsuDiffHarmTest"))||(strCharaID == _T("ElecRailwayDiffHarmTest")))
			{
				m_strTestPointDescX = /*_T("谐波含量")*/g_sLangTxt_State_HarContent; //lcq
				m_strTestPointDescY = /*_T("差动电流")*/g_sLangTxt_State_DifferentCur;//lcq
			} 
			else
			{
				m_strTestPointDescX = /*_T("制动电流")*/g_sLangTxt_State_BrakingCur;//lcq
				m_strTestPointDescY = /*_T("差动电流")*/g_sLangTxt_State_DifferentCur;//lcq
			}
		}
		else if (m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest||
			m_strCurrMacroID == STT_ORG_MACRO_VolInverseTimeTest_I)
		{
			m_strTestPointDescX = /*_T("电压比值")*/g_sLangTxt_State_VoltageRat; //lcq
			m_strTestPointDescY = /*_T("动作时间")*/g_sLangTxt_Gradient_ActionTime; //lcq
		}
		else if (m_strCurrMacroID == STT_ORG_MACRO_UFInverseTimeTest)
		{
			m_strTestPointDescX = _T("U*/F*");
			m_strTestPointDescY = /*_T("动作时间")*/g_sLangTxt_Gradient_ActionTime; //lcq
		}
		else if ((m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest)||
			(m_strCurrMacroID == STT_ORG_MACRO_DistSearchOneTest))
		{
			m_strTestPointDescX = /*_T("阻抗值(Z)")*/g_sLangTxt_State_ZImpValue; //lcq
			m_strTestPointDescY = /*_T("角度(°)")*/g_sLangTxt_State_DAngle; //lcq
		}
		else if (m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest||
			(m_strCurrMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I))
		{
			m_strTestPointDescX = /*_T("电流比值")*/g_sLangTxt_State_CurrentRat; //lcq
			m_strTestPointDescY = /*_T("动作时间")*/g_sLangTxt_Gradient_ActionTime; //lcq
		}
		else if (m_strCurrMacroID == STT_ORG_MACRO_SynTest_I)
		{
			m_strTestPointDescX = _T("频率差值"); //lcq
			m_strTestPointDescY =  /*_T("电压比值")*/g_sLangTxt_State_VoltageRat; //lcq
		}
		else 
		{
			m_strTestPointDescX = /*_T("阻抗值(Z)")*/g_sLangTxt_State_ZImpValue; //lcq
			m_strTestPointDescY = /*_T("角度(°)")*/g_sLangTxt_State_DAngle; //lcq
		}

		InitGridTitle();
		ShowCharacteristic(pCurrCharacteristic);
	}

// 	m_pCharacterDrawView->UpdateCurrTestPoint(dX, dY);
// 	update();
}

