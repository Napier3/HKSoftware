#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttTestCntrFrameBase.h"
#include "../../../../SttGlobalDef.h"
#include "QSttFATestResultViewGroupGrid.h"
#include"../../../Module/XLangResource_Native.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include <QHeaderView>
#include "../../../VoltageTimeTypeSectorMode/QSttMacroParaEditViewVolTimeTypeSec.h"

QSttFATestResultViewGroupGrid::QSttFATestResultViewGroupGrid(QWidget *parent)
:QExBaseListGridBase(parent)
{

}

QSttFATestResultViewGroupGrid::~QSttFATestResultViewGroupGrid()
{

}

void QSttFATestResultViewGroupGrid::InitGrid()
{
	InitGridTitle();
	setFont(*g_pSttGlobalFont);
	verticalHeader()->setVisible(false);
}

void QSttFATestResultViewGroupGrid::InitGridTitle()
{
	horizontalHeader()->setFont(*g_pSttGlobalFont);
	CString astrGridTitle[QSTTFASOEGRIDCOL] = {_T("状态"), _T("开入动作"), _T("SOE信息")};
	int iColType[QSTTFASOEGRIDCOL]={QT_GVET_EDITBOX, QT_GVET_EDITBOX, QT_GVET_EDITBOX};
	int iGridWidth[QSTTFASOEGRIDCOL]={100, 100, 300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QSTTFASOEGRIDCOL);
}

void QSttFATestResultViewGroupGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
	CDvmData *pDvmData = (CDvmData*)pData;
	Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
	Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strDefaultValue);
	Show_StaticString(pDvmData, nRow, 2, &pDvmData->m_strValue);
	nRow++;
}