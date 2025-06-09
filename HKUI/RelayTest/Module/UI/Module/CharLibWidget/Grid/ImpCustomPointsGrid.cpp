#include "ImpCustomPointsGrid.h"
#include "../../../../XLangResource_Native.h"

QImpCustomPointsGrid::QImpCustomPointsGrid(QWidget *parent)
	: QExBaseListGridBase(parent)
{
}

QImpCustomPointsGrid::~QImpCustomPointsGrid()
{
}

void QImpCustomPointsGrid::InitGrid()
{
	InitGridTitle();

	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QImpCustomPointsGrid::InitGridTitle()
{
	CString astrGridTitle[IMPCUSTOMPOINTS_GRID_COLS];
	int iGridWidth[IMPCUSTOMPOINTS_GRID_COLS]={100, 100,80, 80,100};
	astrGridTitle[0] = /*_T("故障类型")*/g_sLangTxt_Gradient_FailType;//lcq
	astrGridTitle[1] = /*_T("故障方向")*/g_sLangTxt_Gradient_FailDirect;//lcq
	astrGridTitle[2] = _T("Z(Ω)");
	astrGridTitle[3] = _T("Phi(°)");
	astrGridTitle[4] = /*_T("故障时间")*/g_sLangTxt_Gradient_FailTime;//lcq
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IMPCUSTOMPOINTS_GRID_COLS);
}

void QImpCustomPointsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
// 	if (pData->GetClassID() != CHARCLASSID_CCHARTESTLINE)
// 	{
// 		return;
// 	}
// 
// 	CString strText,strIndex;
// 	CCharTestLine *pCharTestLine = (CCharTestLine *)pData;
// 	strText = _T("测试点");
// 	strIndex.Format(_T("%d"),nRow);
// 	strText += strIndex;
//  	Show_StaticString(pData, nRow, 0, strText);
// 
// 	if (pCharTestLine->m_strType == _T("user"))
// 	{
// 		strText = _T("自定义");
// 	} 
// 	else
// 	{
// 		strText = _T("系统生成");
// 	}
// 
// 	Show_StaticString(pData, nRow, 1, strText);
// 
// 	if ((m_strCurrMacroID == STT_ORG_MACRO_DistanceSearchTest)||
// 		(m_strCurrMacroID == STT_ORG_MACRO_DistSearchOneTest))
// 	{
// 		CComplexNumber oCompNum(pCharTestLine->m_fXset, pCharTestLine->m_fYset);
// 		double dZValue = 0.0f,dAngleValue = 0.0f;
// 		dZValue = sqrt(pow(pCharTestLine->m_fXset, 2) + pow(pCharTestLine->m_fYset, 2));
// 		dAngleValue = oCompNum.GetAngle_180_180();
// 		strText.Format(_T("%.03lf"),dZValue);
// 		Show_StaticString(pData, nRow, 2, strText);
// 
// 		strText.Format(_T("%.03lf"),dAngleValue);
// 		Show_StaticString(pData, nRow, 3, strText);
// 	}
// 	else
// 	{
// 		strText.Format(_T("%.03lf"),pCharTestLine->m_fXset);
// 		Show_StaticString(pData, nRow, 2, strText);
// 
// 		strText.Format(_T("%.03lf"),pCharTestLine->m_fYset);
// 		Show_StaticString(pData, nRow, 3, strText);
// 	}
// 	
// 	Show_StaticString(pData, nRow, 4, _T("--"));
// 	Show_StaticString(pData, nRow, 5, _T("--"));
	nRow++;
}

