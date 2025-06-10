#include "CBOperateResultAssessGrid.h"
#include <QHeaderView>
#include "../Module/SttGlobalDef.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QCheckBox>
#include "../../Controls/SttCheckBox.h"
#include <QComboBox>
#include <QSpinBox>
#include "../../Module/CommonMethod/commonMethod.h"

CBOperateResultAssessGrid::CBOperateResultAssessGrid(tmt_CBOperateParas *pCBOperateParas, QWidget *parent) : QDialog(parent)
{
	m_oCBOperateParas = pCBOperateParas;

	InitUI();
	InitFont();
	InitConnections();
}

CBOperateResultAssessGrid::~CBOperateResultAssessGrid()
{

}

void CBOperateResultAssessGrid::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
    m_pResultTableWidget = new QTableWidget(3, 5, this);
    m_pResultTableWidget->horizontalHeader()->setSectionsClickable(false);
    m_pResultTableWidget->horizontalHeader()->setSectionsMovable(false);

    QStringList headers;
    headers << /*"名称"*/g_sLangTxt_AttrID_Name << /*"误差类型"*/g_sLangTxt_StateEstimate_ErrorType <</* "相对误差(%)"*/g_sLangTxt_StateEstimate_RelError << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError << g_sLangID_StateEstimate_SettingValue/*"整定值"*/;
    m_pResultTableWidget->setHorizontalHeaderLabels(headers);
    m_pResultTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background: skyblue;}"); // 设置表头背景色
	m_pResultTableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");
    m_pResultTableWidget->verticalHeader()->setVisible(false);

    m_pResultTableWidget->resizeColumnsToContents(); // 根据内容调整列宽
	m_pResultTableWidget->setColumnWidth(0, 200);
	for (int col = 1; col < 5; ++col) 
	{
		m_pResultTableWidget->setColumnWidth(col, 120); 
	}

	m_pResultTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); 
	m_pResultTableWidget->setFixedSize(680, 200); // 设置固定大小

	m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 设置固定列宽
	m_pResultTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 设置固定行高


	m_pChbActionTime = new QSttCheckBox(g_sLangTxt_Gradient_ActionTime);
	m_pResultTableWidget->setCellWidget(0, 0, m_pChbActionTime);

	m_pChbTripTime = new QSttCheckBox(g_sLangTxt_Native_RecloseTime);
	m_pResultTableWidget->setCellWidget(1, 0, m_pChbTripTime);

	m_pChbAccTime = new QSttCheckBox(g_sLangTxt_Native_PostAccTime);
	m_pResultTableWidget->setCellWidget(2, 0, m_pChbAccTime);

	m_pCmbActionTime = new QComboBox();
	m_pCmbTtripTime = new QComboBox();
	m_pCmbAccTime = new QComboBox();


	QStringList headers1;
	headers1 << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError << /*"相对误差"*/g_sLangTxt_StateEstimate_RelError << /*"绝对or相对"*/g_sLangTxt_CBOperate_AbsOrRelative << /*"绝对&相对"*/g_sLangTxt_CBOperate_AbsRelative << /*"组合误差"*/g_sLangTxt_CBOperate_CombError;
	m_pCmbActionTime->addItems(headers1);
	m_pCmbTtripTime->addItems(headers1);
	m_pCmbAccTime->addItems(headers1);
	m_pResultTableWidget->setCellWidget(0, 1, m_pCmbActionTime);
	m_pResultTableWidget->setCellWidget(1, 1, m_pCmbTtripTime);
	m_pResultTableWidget->setCellWidget(2, 1, m_pCmbAccTime);
	m_pResultTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->addWidget(m_pResultTableWidget);
	m_pButtonLayout = new QHBoxLayout();
	m_pBtnOK = new QPushButton(/*"确定"*/g_sLangTxt_OK, this);
	m_pBtnCancel = new QPushButton(/*"取消"*/g_sLangTxt_Cancel, this);
	m_pButtonLayout->addWidget(m_pBtnOK);
	m_pButtonLayout->addWidget(m_pBtnCancel);
	m_pButtonLayout->setAlignment(Qt::AlignCenter);
	m_pMainLayout->addLayout(m_pButtonLayout);

	m_pResultTableWidget->viewport()->installEventFilter(this);
	setLayout(m_pMainLayout);
	UpdataResultAssess();
}

void CBOperateResultAssessGrid::InitFont()
{
	m_pChbActionTime->setFont(*g_pSttGlobalFont);
	m_pChbTripTime->setFont(*g_pSttGlobalFont);
	m_pChbAccTime->setFont(*g_pSttGlobalFont);
	m_pCmbActionTime->setFont(*g_pSttGlobalFont);
	m_pCmbTtripTime->setFont(*g_pSttGlobalFont);
	m_pCmbAccTime->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pBtnOK->setFont(*g_pSttGlobalFont);
	m_pBtnCancel->setFont(*g_pSttGlobalFont);
}
void CBOperateResultAssessGrid::slot_btnOK_Clicked()
{
	
	m_oCBOperateParas->m_fTtripRelErr = m_pResultTableWidget->item(0, 2)->text().toFloat();
	m_oCBOperateParas->m_fTtripAbsErr = m_pResultTableWidget->item(0, 3)->text().toFloat();
	m_oCBOperateParas->m_fTSetting = m_pResultTableWidget->item(0, 4)->text().toFloat();

	m_oCBOperateParas->m_fTtripDRelErr = m_pResultTableWidget->item(1, 2)->text().toFloat();
	m_oCBOperateParas->m_fTtripDAbsErr = m_pResultTableWidget->item(1, 3)->text().toFloat();
	m_oCBOperateParas->m_fDTSetting = m_pResultTableWidget->item(1, 4)->text().toFloat();

	m_oCBOperateParas->m_fTtripAccRelErr = m_pResultTableWidget->item(2, 2)->text().toFloat();
	m_oCBOperateParas->m_fTtripAccAbsErr = m_pResultTableWidget->item(2, 3)->text().toFloat();
	m_oCBOperateParas->m_fAccTSetting = m_pResultTableWidget->item(2, 4)->text().toFloat();
	
	m_oCBOperateParas->m_nTtripErrorLogic = m_pCmbActionTime->currentIndex();
	m_oCBOperateParas->m_nTtripDErrorLogic = m_pCmbTtripTime->currentIndex();
	m_oCBOperateParas->m_nTtripAccErrorLogic = m_pCmbAccTime->currentIndex();
	UpdataResultAssess();

	accept();
}

void CBOperateResultAssessGrid::InitConnections()
{
	connect(m_pChbActionTime,SIGNAL(clicked(bool)),this,SLOT(slot_ChbActionTime(bool)));
	connect(m_pChbTripTime,SIGNAL(clicked(bool)),this,SLOT(slot_ChbTripTime(bool)));
	connect(m_pChbAccTime,SIGNAL(clicked(bool)),this,SLOT(slot_ChbAccTime(bool)));

	connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slot_btnOK_Clicked()));
	connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slot_btnCancel_Clicked()));

	connect(m_pResultTableWidget,SIGNAL(cellChanged(int, int)),this,SLOT(slot_cellClicked(int, int)));
}
void CBOperateResultAssessGrid::slot_btnCancel_Clicked()
{
	reject();
}

void CBOperateResultAssessGrid::slot_ChbActionTime(bool state)
{
	if (!state)
	{
		for (int col = 1; col < m_pResultTableWidget->columnCount(); col++)
		{
			QTableWidgetItem *item = m_pResultTableWidget->item(0, col);
			QWidget *widget = m_pResultTableWidget->cellWidget(0, col);
			if (item) 
			{
				item->setFlags(item->flags() & ~Qt::ItemIsEnabled); // 禁用item
			}
			if (widget) 
			{
				widget->setEnabled(false);
			}
		}
	}
	else
	{
		for (int col = 1; col < m_pResultTableWidget->columnCount(); col++)
		{
			QWidget *widget = m_pResultTableWidget->cellWidget(0, col);
			QTableWidgetItem *item = m_pResultTableWidget->item(0, col);
			if (item) 
			{
				item->setFlags(item->flags() | Qt::ItemIsEnabled); // 启用item
			}
			if (widget) 
			{
				widget->setEnabled(true);
			}
		}
	}

	m_oCBOperateParas->m_nTtripCheck = state;

}
void CBOperateResultAssessGrid::slot_ChbTripTime(bool state)
{
	if (!state)
	{
		for (int col = 1; col < m_pResultTableWidget->columnCount(); col++)
		{
			QTableWidgetItem *item = m_pResultTableWidget->item(1, col);
			QWidget *widget = m_pResultTableWidget->cellWidget(1, col);
			if (item) 
			{
				item->setFlags(item->flags() & ~Qt::ItemIsEnabled); // 禁用item
			}
			if (widget) 
			{
				widget->setEnabled(false);
			}
		}
	}
	else
	{
		for (int col = 1; col < m_pResultTableWidget->columnCount(); col++)
		{
			QWidget *widget = m_pResultTableWidget->cellWidget(1, col);
			QTableWidgetItem *item = m_pResultTableWidget->item(1, col);
			if (item) 
			{
				item->setFlags(item->flags() | Qt::ItemIsEnabled); // 启用item
			}
			if (widget) 
			{
				widget->setEnabled(true);
			}
		}
	}
	m_oCBOperateParas->m_nTtripDCheck = state;

}

void CBOperateResultAssessGrid::slot_ChbAccTime(bool state)
{
	if (!state)
	{
		for (int col = 1; col < m_pResultTableWidget->columnCount(); col++)
		{
			QTableWidgetItem *item = m_pResultTableWidget->item(2, col);
			QWidget *widget = m_pResultTableWidget->cellWidget(2, col);
			if (item) 
			{
				item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
			}
			if (widget) 
			{
				widget->setEnabled(false);
			}
		}
	}
	else
	{
		for (int col = 1; col < m_pResultTableWidget->columnCount(); col++)
		{
			QWidget *widget = m_pResultTableWidget->cellWidget(2, col);
			QTableWidgetItem *item = m_pResultTableWidget->item(2, col);
			if (item) 
			{
				item->setFlags(item->flags() | Qt::ItemIsEnabled);
			}
			if (widget) 
			{
				widget->setEnabled(true);
			}
		}
	}
		m_oCBOperateParas->m_nTtripAccCheck = state;
}

void CBOperateResultAssessGrid::UpdataResultAssess()
{
	m_pItem1 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripRelErr, 'f', 3));
	m_pItem1->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(0, 2, m_pItem1);
	
	m_pItem2 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAbsErr, 'f', 3));
	m_pItem2->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(0, 3, m_pItem2);

	m_pItem3 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTSetting, 'f', 3));
	m_pItem3->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(0, 4, m_pItem3);

	m_pItem4 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripDRelErr, 'f', 3));
	m_pItem4->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(1, 2, m_pItem4);

	m_pItem5 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripDAbsErr, 'f', 3));
	m_pItem5->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(1, 3, m_pItem5);

	m_pItem6 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fDTSetting, 'f', 3));
	m_pItem6->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(1, 4, m_pItem6);

	m_pItem7 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAccRelErr, 'f', 3));
	m_pItem7->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(2, 2, m_pItem7);

	m_pItem8 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAccAbsErr, 'f', 3));
	m_pItem8->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(2, 3, m_pItem8);

	m_pItem9 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fAccTSetting, 'f', 3));
	m_pItem9->setTextAlignment(Qt::AlignCenter);
	m_pResultTableWidget->setItem(2, 4, m_pItem9);

	slot_ChbActionTime(m_oCBOperateParas->m_nTtripCheck);
	slot_ChbTripTime(m_oCBOperateParas->m_nTtripDCheck);
	slot_ChbAccTime(m_oCBOperateParas->m_nTtripAccCheck);

	m_pChbActionTime->setChecked(m_oCBOperateParas->m_nTtripCheck);
	m_pChbTripTime->setChecked(m_oCBOperateParas->m_nTtripDCheck);
	m_pChbAccTime->setChecked(m_oCBOperateParas->m_nTtripAccCheck);

	m_pCmbActionTime->setCurrentIndex(m_oCBOperateParas->m_nTtripErrorLogic);;
	m_pCmbTtripTime->setCurrentIndex(m_oCBOperateParas->m_nTtripDErrorLogic);;
	m_pCmbAccTime->setCurrentIndex(m_oCBOperateParas->m_nTtripAccErrorLogic);;
}

void CBOperateResultAssessGrid::slot_cellClicked(int row ,int col)
{
	if (col == 2 && row >= 0 && row <= 2) 
	{
		QTableWidgetItem *item = m_pResultTableWidget->item(row, col);
		if (item) 
		{
			float fv = item->text().toFloat();
			fv = setLimit(0,100.000,fv);
			item->setText(QString::number(fv, 'f', 3)); 
		}
	}
	if (col == 3 && row >= 0 && row <= 2) 
	{
		QTableWidgetItem *item2 = m_pResultTableWidget->item(row, col);
		if (item2) 
		{
			float fv = item2->text().toFloat();
			fv = setLimit(0,200.000,fv);
			item2->setText(QString::number(fv, 'f', 3)); 
		}
	}
	if (col == 4 && row >= 0 && row <= 2) 
	{
		QTableWidgetItem *item3 = m_pResultTableWidget->item(row, col);
		if (item3) 
		{
			float fv = item3->text().toFloat();
			fv = setLimit(0,999999.000,fv);
			item3->setText(QString::number(fv, 'f', 3)); 
		}
	}
}

bool CBOperateResultAssessGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == m_pResultTableWidget->viewport() && event->type() == QEvent::MouseButtonPress) 
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button() == Qt::LeftButton) 
		{
			// 获取鼠标点击位置
			QPoint point = mouseEvent->pos();
			// 转换为单元格坐标
			QModelIndex index = m_pResultTableWidget->indexAt(point);
			// 打开编辑模式
			m_pResultTableWidget->edit(index);
			return true; // 停止事件传播
		}
	}
	return QObject::eventFilter(obj, event);
}
