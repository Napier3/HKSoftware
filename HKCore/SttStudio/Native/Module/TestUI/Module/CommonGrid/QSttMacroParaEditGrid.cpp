#include "QSttMacroParaEditGrid.h"

QSttMacroParaEditGrid::QSttMacroParaEditGrid(QWidget *parent)
	: QExBaseListGridBase(parent)
{
	m_pCurrGridInst = NULL;
}

QSttMacroParaEditGrid::~QSttMacroParaEditGrid()
{

}

void QSttMacroParaEditGrid::InitColDef(CSttGdGridInst *pCurrGridInst)
{
	m_pCurrGridInst = pCurrGridInst;
	InitGrid();
}

void QSttMacroParaEditGrid::InitGrid()
{
	InitGridTitle();
}

void QSttMacroParaEditGrid::InitGridTitle()
{
	if (m_pCurrGridInst == NULL)
	{
		return;
	}

	long nCount = m_pCurrGridInst->GetColCount();
}

void QSttMacroParaEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

}