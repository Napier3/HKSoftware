#include "QSCLCheckResultGrid.h"
#include "..\..\Module\UI\Module\QExBaseListGridBase\QGridDefine.h"
#include "..\..\..\SCLCompareCheck\Module\SclCheck\ResultRec.h"
#include <QHeaderView>
#include <QPalette>


QSCLCheckResultGrid::QSCLCheckResultGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	
}

QSCLCheckResultGrid::~QSCLCheckResultGrid()
{

}

void QSCLCheckResultGrid::InitGrid()
{
	//2024 1-2 zhouyangyong 新增奇偶行不同颜色
	m_oColor = QColor(135, 206, 235);
	verticalHeader()->setVisible(false);
	InitGridTitle();
	setAlternatingRowColors(true);
	QPalette palette = this->palette();
	palette.setColor(QPalette::Base, QColor(255, 255, 255)); // 奇数行颜色
	palette.setColor(QPalette::AlternateBase, m_oColor); // 偶数行颜色
	setPalette(palette);
}

void QSCLCheckResultGrid::InitGridTitle()
{
	CString astrGridTitle[SCLCHECKRESULTGRID_COLS] = {_T("序号"),_T("类型"),_T("描述信息"),_T("异常定位"),_T("提示数"),_T("告警数"),_T("错误数"),_T("严重错误")};
	int  iColType[SCLCHECKRESULTGRID_COLS]={QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[SCLCHECKRESULTGRID_COLS]={100, 100, 600, 200, 200,200,200,200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCHECKRESULTGRID_COLS);
}

void QSCLCheckResultGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT(pData);
	long nIndex = long(nRow+1);
	CResultRec *pResult = (CResultRec*)pData;
	Show_Long(pResult, nRow, 0, &nIndex, FALSE);
	Show_StaticString(pResult, nRow, 1, &pResult->m_strErrorType);
	Show_StaticString(pResult, nRow, 2, &pResult->m_strErrorText);
	Show_StaticString(pResult, nRow, 3, &pResult->m_strErrorPos);
	Show_Long(pResult, nRow, 4, &pResult->m_nTipIndex, FALSE);
	Show_Long(pResult, nRow, 5, &pResult->m_nWarningIndex, FALSE);
	Show_Long(pResult, nRow, 6, &pResult->m_nErrorIndex, FALSE);
	Show_Long(pResult, nRow, 7, &pResult->m_nFatalErrorIndex, FALSE);
	nRow++;

}
//2024 1-2 zhouyangyong 新增换行后刷新颜色
void QSCLCheckResultGrid::slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("currentRow=%d;currentColumn=%d;previousRow=%d;previousColumn=%d;"),currentRow,currentColumn,previousRow,previousColumn);

	if ((currentRow >= 0))
	{
		const QColor colorCurr = QColor(204,204,204);
		setRowColor(currentRow,colorCurr);
		OnDataSelChanged(currentRow,currentColumn);
	}

	if (previousRow >= 0)
	{
		if(previousRow%2 == 1)
		{
			const QColor colorOld = QColor(m_oColor);
			setRowColor(previousRow,colorOld);
		}
		else
		{
			const QColor colorOld = QColor(255,255,255);
			setRowColor(previousRow,colorOld);
		}
		
	}
}
