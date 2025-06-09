#include "QSttFAStateSequenceGroupGrid.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttTestCntrFrameBase.h"
#include "../../../../SttGlobalDef.h"
#include"../../Module/XLangResource_Native.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "QSttFAStateSequenceGroupGrid.h"
#include "../../../../UI/VoltageTimeTypeSectorMode/QSttMacroParaEditViewVolTimeTypeSec.h"
#include <QHeaderView>

QSttFAStateSequenceGroupGrid::QSttFAStateSequenceGroupGrid(QWidget *parent )
:QExBaseListGridBase(parent)
{
	setEditTriggers(QAbstractItemView::AllEditTriggers);
	connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(slot_ItemClicked(QTableWidgetItem*)));
}

QSttFAStateSequenceGroupGrid::~QSttFAStateSequenceGroupGrid()
{

}

void QSttFAStateSequenceGroupGrid::InitGrid()
{
	InitGridTitle();
	setFont(*g_pSttGlobalFont);
	verticalHeader()->setVisible(false);
}

void QSttFAStateSequenceGroupGrid::InitGridTitle()
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    // 禁止表头点击
    horizontalHeader()->setSectionsClickable(false);
    // 禁止表头大小修改
    horizontalHeader()->setSectionsMovable(false);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
#else
    // 禁止表头点击
    horizontalHeader()->setClickable(false);
    // 禁止表头大小修改
    horizontalHeader()->setMovable(false);
    horizontalHeader()->setResizeMode(QHeaderView::Fixed);
#endif
	horizontalHeader()->setFont(*g_pSttGlobalFont);

	CString astrGridTitle[QSTTFASTATEGRIDCOL] = {_T("名称"),_T("电源侧电压(V)"),_T("负荷侧电压(V)"),_T("状态量"),_T("触发条件"),_T("参数(s)")};
	int siColType[QSTTFASTATEGRIDCOL]={QT_GVET_EDITBOX, QT_GVET_EDITBOX,QT_GVET_EDITBOX,QT_GVET_EDITBOX,QT_GVET_EDITBOX,QT_GVET_EDITBOX};
	int iGridWidth[QSTTFASTATEGRIDCOL]={65, 120, 120, 60, 115, 60};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QSTTFASTATEGRIDCOL);
}

void QSttFAStateSequenceGroupGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
	CDataGroup *pDataGroup = (CDataGroup*)pData;
	Show_StaticString(pDataGroup, nRow, 0, &pDataGroup->m_strName);
	ShowChildren(pDataGroup, nRow);
	nRow++;
}

void QSttFAStateSequenceGroupGrid::ShowChildren(CDataGroup *pDataGroup, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pDataGroup);
	POS pos = pDataGroup->GetHeadPosition();
	CDvmData *pDvmValue = NULL;
	long nIndex = 1;
	while (pos)
	{
		pDvmValue = (CDvmData *)pDataGroup->GetNext(pos);

		if (pDvmValue->m_strID == "para1" || pDvmValue->m_strID == "para2" || pDvmValue->m_strID == "para5")
		{
			Show_String(pDvmValue, nRow, nIndex, &pDvmValue->m_strValue);  
		}
		else
		{
			Show_StaticString(pDvmValue, nRow, nIndex, &pDvmValue->m_strValue);
		}
		nIndex++;
	}
}

void QSttFAStateSequenceGroupGrid::slot_ItemClicked(QTableWidgetItem *item)
{
	if (item->flags() & Qt::ItemIsEditable) 
	{
		if (item->text() == "-")
		{
			return; 
		}

		bool ok;
		double m_strValue = item->text().toDouble(&ok);
		if (ok)
		{
			if (m_strValue < 0)
			{
				m_strValue = 0;
			}
			else if (m_strValue > 130)
			{
				m_strValue = 130;
			}
			item->setText(QString::number(m_strValue));
		}
		else // 处理不合法数字
		{
			item->setText("0");
		}
	}
}

void QSttFAStateSequenceGroupGrid::mousePressEvent(QMouseEvent *event)
{
	QTableWidgetItem *item = itemAt(event->pos());
	if (item && item->flags() & Qt::ItemIsEditable)
	{
		editItem(item); // 开始编辑当前单击的单元格
	}
	else
	{
		QTableWidget::mousePressEvent(event);
	}
}




