#include "QSttAntiShakeTimeDinEventGroupGrid.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../UI/SttTestCntrFrameBase.h"
#include "../../../../Module/SttGlobalDef.h"
#include"../../../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/XLanguageResource.h"

QSttAntiShakeTimeDinEventGroupGrid::QSttAntiShakeTimeDinEventGroupGrid(QWidget *parent)
{
	m_pTableWidget = NULL;
	CleanTestResultData();

}

QSttAntiShakeTimeDinEventGroupGrid::~QSttAntiShakeTimeDinEventGroupGrid()
{

}

void QSttAntiShakeTimeDinEventGroupGrid::InitUI()
{
	m_pTableWidget = new QTableWidget(1000, 6, this);

	// 设置表头
	QStringList m_pListHeaders;
	m_pListHeaders << "编号" << "间隔" << "YX通道" << "事件描述" << "事件发生时间" << "";
	m_pTableWidget->setHorizontalHeaderLabels(m_pListHeaders);
	m_pTableWidget->verticalHeader()->setVisible(false);

	// 设置表头样式和全局字体
	m_pTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	m_pTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);

	// 其他样式设置
	m_pTableWidget->setStyleSheet("QTableWidget { gridline-color: white; selection-background-color: grey; selection-color: black; }");
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    m_pTableWidget->horizontalHeader()->setSectionsClickable(false);
#else
    m_pTableWidget->horizontalHeader()->setClickable(false);
#endif
	m_pTableWidget->setColumnWidth(0, 100);
	m_pTableWidget->setColumnWidth(1, 130);
	m_pTableWidget->setColumnWidth(2, 130);
	m_pTableWidget->setColumnWidth(3, 200);
	m_pTableWidget->setColumnWidth(4, 200);
	m_pTableWidget->setColumnWidth(5, 260);

	int totalWidth = 1020;
	m_pTableWidget->setFixedWidth(totalWidth);
	m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	m_pTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    m_pTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
#else
    m_pTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
#endif
	m_pTableWidget->setFont(*g_pSttGlobalFont);
}

void QSttAntiShakeTimeDinEventGroupGrid::CleanTestResultData()
{

}

void QSttAntiShakeTimeDinEventGroupGrid::AddItem(tmt_antishake_time_result_set *pData)
{

}
