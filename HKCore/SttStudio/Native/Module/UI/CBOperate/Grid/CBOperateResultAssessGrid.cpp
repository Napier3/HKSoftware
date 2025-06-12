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
#include "../../Interface/SttMacroParaEditViewOriginal.h"
#include "../../Controls/SettingCtrls/QSettingItem.h"
#include <QDesktopWidget>
#include <QApplication>

#ifdef _PSX_QT_WINDOWS_
//#include <QApplication>
//#include <QDesktopWidget>
#include <QRect>
#include "../../SttTestCntrFrameBase.h"
#endif

CBOperateResultAssessGrid::CBOperateResultAssessGrid(tmt_CBOperateParas *pCBOperateParas, QWidget *parent) 
: QDialog(parent)
{
	if (parent->inherits(STT_SETTING_ORIGINAL_ClassID/*"CSttMacroParaEditViewOriginal"*/))
	{
		//���ü�¼Maps��ϵ�ĵ�ַ
		g_pCurrTestMacroUI_DataMaps = &(((CSttMacroParaEditViewOriginal*)parent)->m_oDvmDataMaps);
	}
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
    m_pResultTableWidget = new QTableWidget(3, 6, this);
	 	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	 	QRect rect = desktopWidget->screenGeometry();
	 	if(rect.height() == 1400)
	 	{
			m_pResultTableWidget->setMinimumSize(1100, 200);
	 	}
		else
		{
			m_pResultTableWidget->setMinimumSize(1000, 200);
		}
    
	m_pResultTableWidget->setEditTriggers(QAbstractItemView::CurrentChanged);

    QStringList headers;
    headers << /*"����"*/g_sLangTxt_Name << g_sLangTxt_SetValue/*"����ֵ"*/ <</*"�������"*/g_sLangTxt_StateEstimate_ErrorType <</* "������(%)"*/g_sLangTxt_StateEstimate_RelError + "(%)" << /*"�������"*/g_sLangTxt_StateEstimate_AbsError << "g_sLangTxt_Distance_AbsErrMinus";
    m_pResultTableWidget->setHorizontalHeaderLabels(headers);
    m_pResultTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background: skyblue;}"); // ���ñ�ͷ����ɫ
	m_pResultTableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");
    m_pResultTableWidget->verticalHeader()->setVisible(false);
	m_pResultTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	m_pResultTableWidget->horizontalHeader()->setSectionsClickable(false);
	m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	m_pResultTableWidget->horizontalHeader()->setSectionsClickable(false);
	m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif
	//m_pResultTableWidget->horizontalHeader()->setSectionsClickable(false);

    //m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pResultTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); 

	m_pLabActionTime = new QLabel(g_sLangTxt_Gradient_ActionTime + "(s)");
	m_pLabActionTime->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->setCellWidget(0, 0, m_pLabActionTime);

	m_pLabTripTime = new QLabel(g_sLangTxt_Native_RecloseTime + "(s)");
	m_pLabTripTime->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->setCellWidget(1, 0, m_pLabTripTime);

	m_pLabAccTime = new QLabel(g_sLangTxt_Native_PostAccTime + "(s)");
	m_pLabAccTime->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->setCellWidget(2, 0, m_pLabAccTime);

	m_pCmbActionTime = new QComboBox();
	m_pCmbTtripTime = new QComboBox();
	m_pCmbAccTime = new QComboBox();

	QStringList headers1;
    headers1 << /*"�������"*/g_sLangTxt_StateEstimate_AbsError << /*"������"*/g_sLangTxt_StateEstimate_RelError << /*"����or���"*/g_sLangTxt_CBOperate_AbsOrRelative << /*"����&���"*/g_sLangTxt_CBOperate_AbsRelative << /*"������"*/g_sLangTxt_CBOperate_CombError << "������";
	m_pCmbActionTime->addItems(headers1);
	m_pCmbTtripTime->addItems(headers1);
	m_pCmbAccTime->addItems(headers1);
	m_pResultTableWidget->setCellWidget(0, 2, m_pCmbActionTime);
	m_pResultTableWidget->setCellWidget(1, 2, m_pCmbTtripTime);
	m_pResultTableWidget->setCellWidget(2, 2, m_pCmbAccTime);
	m_pResultTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->addWidget(m_pResultTableWidget);
	m_pButtonLayout = new QHBoxLayout();
	m_pBtnOK = new QPushButton(/*"ȷ��"*/g_sLangTxt_OK, this);
	m_pBtnCancel = new QPushButton(/*"ȡ��"*/g_sLangTxt_Cancel, this);
	m_pButtonLayout->addWidget(m_pBtnOK);
	m_pButtonLayout->addWidget(m_pBtnCancel);
	m_pButtonLayout->setAlignment(Qt::AlignCenter);
	m_pMainLayout->addLayout(m_pButtonLayout);

	//m_pResultTableWidget->viewport()->installEventFilter(this);
	setLayout(m_pMainLayout);

	UpdataResultAssess();
}

void CBOperateResultAssessGrid::InitFont()
{
	m_pItem3->setFont(*g_pSttGlobalFont);
	m_pItem6->setFont(*g_pSttGlobalFont);
	m_pItem9->setFont(*g_pSttGlobalFont);
	//m_pChbActionTime->setFont(*g_pSttGlobalFont);
	//m_pChbTripTime->setFont(*g_pSttGlobalFont);
	//m_pChbAccTime->setFont(*g_pSttGlobalFont);
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
	
	m_oCBOperateParas->m_fTtripRelErr = m_pResultTableWidget->item(0, 3)->text().toFloat();
	m_oCBOperateParas->m_fTtripAbsErr = m_pResultTableWidget->item(0, 4)->text().toFloat();
	m_oCBOperateParas->m_fTtripAbsErrMinus = m_pResultTableWidget->item(0, 5)->text().toFloat();
	m_oCBOperateParas->m_fTSetting = m_pItem3->text().toFloat();

	m_oCBOperateParas->m_fTtripDRelErr = m_pResultTableWidget->item(1, 3)->text().toFloat();
	m_oCBOperateParas->m_fTtripDAbsErr = m_pResultTableWidget->item(1, 4)->text().toFloat();
	m_oCBOperateParas->m_fTtripDAbsErrMinus = m_pResultTableWidget->item(1, 5)->text().toFloat();
	m_oCBOperateParas->m_fDTSetting = m_pItem6->text().toFloat();

	m_oCBOperateParas->m_fTtripAccRelErr = m_pResultTableWidget->item(2, 3)->text().toFloat();
	m_oCBOperateParas->m_fTtripAccAbsErr = m_pResultTableWidget->item(2, 4)->text().toFloat();
	m_oCBOperateParas->m_fTtripAccAbsErrMinus = m_pResultTableWidget->item(1, 5)->text().toFloat();
	m_oCBOperateParas->m_fAccTSetting = m_pItem9->text().toFloat();
	
	m_oCBOperateParas->m_nTtripErrorLogic = m_pCmbActionTime->currentIndex();
	m_oCBOperateParas->m_nTtripDErrorLogic = m_pCmbTtripTime->currentIndex();
	m_oCBOperateParas->m_nTtripAccErrorLogic = m_pCmbAccTime->currentIndex();
	UpdataResultAssess();

	accept();
}

void CBOperateResultAssessGrid::InitConnections()
{
	//connect(m_pLabActionTime,SIGNAL(clicked(bool)),this,SLOT(slot_ChbActionTime(bool)));
	//connect(m_pLabTripTime, SIGNAL(clicked(bool)), this, SLOT(slot_ChbTripTime(bool)));
	//connect(m_pLabAccTime, SIGNAL(clicked(bool)), this, SLOT(slot_ChbAccTime(bool)));

	connect(m_pCmbActionTime, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbActionTime(int)));
	connect(m_pCmbTtripTime, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbTripTime(int)));
	connect(m_pCmbAccTime, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbAccTime(int)));
	
	connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slot_btnOK_Clicked()));
	connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slot_btnCancel_Clicked()));
	connect(m_pResultTableWidget, SIGNAL((int, int)), this, SLOT(slot_cellClicked(int, int)));
	//connect(m_pItem3, SIGNAL(editingFinished()), this, SLOT(slot_Item3()));
	//connect(m_pItem6, SIGNAL(editingFinished()), this, SLOT(slot_Item6()));
	//connect(m_pItem9, SIGNAL(editingFinished()), this, SLOT(slot_Item9()));

	connect(m_pResultTableWidget,SIGNAL(cellChanged(int, int)),this,SLOT(slot_cellClicked(int, int)));
}
void CBOperateResultAssessGrid::slot_btnCancel_Clicked()
{
	reject();
}

void CBOperateResultAssessGrid::UpdateTable(int nIndex, int row)
{
	bool disable = false;

	// ����nIndex�趨���õ���
	QVector<int> columnsToDisable;
	if (nIndex == 0)
			{
		columnsToDisable.append(3); // ���õ�����
			}
	else if (nIndex == 1)
			{
		columnsToDisable.append(4); // ���õ�����
		columnsToDisable.append(5); // ���õ�����
	}
	else if (nIndex == 5)
		{
		disable = true; 
			}

	for (int col = 2; col < m_pResultTableWidget->columnCount(); col++)
			{
		if (col == 2)
			{
			continue;
	}

		QTableWidgetItem *item = m_pResultTableWidget->item(row, col);
		QWidget *widget = m_pResultTableWidget->cellWidget(row, col);

		bool shouldDisable = disable || columnsToDisable.contains(col);

		if (item)
		{
			if (shouldDisable)
			{
				item->setFlags(item->flags() & ~Qt::ItemIsEnabled); // ����item
			}
	else
	{
				item->setFlags(item->flags() | Qt::ItemIsEnabled); // ����item
			}
			}

		if (widget)
			{
			widget->setEnabled(!shouldDisable); // �ؼ��������
		}
	}
}

void CBOperateResultAssessGrid::slot_CmbActionTime(int nIndex)
{
	UpdateTable(nIndex, 0);
}

void CBOperateResultAssessGrid::slot_CmbTripTime(int nIndex)
{
	UpdateTable(nIndex, 1);
}

void CBOperateResultAssessGrid::slot_CmbAccTime(int nIndex)
{
	UpdateTable(nIndex, 2);
}


void CBOperateResultAssessGrid::UpdataResultAssess()
{
	m_pItem1 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripRelErr, 'f', 3));
	m_pResultTableWidget->setItem(0, 3, m_pItem1);
	
	m_pItem2 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAbsErr, 'f', 3));
	m_pResultTableWidget->setItem(0, 4, m_pItem2);

	m_pItem10 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAbsErrMinus, 'f', 3));
	m_pResultTableWidget->setItem(0, 5, m_pItem10);

	m_pItem3 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTSetting, 'f',3));
	m_pResultTableWidget->setItem(0, 1, m_pItem3);

	m_pItem4 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripDRelErr, 'f', 3));
	m_pResultTableWidget->setItem(1, 3, m_pItem4);

	m_pItem5 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripDAbsErr, 'f', 3));
	m_pResultTableWidget->setItem(1, 4, m_pItem5);

	m_pItem11 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripDAbsErrMinus, 'f', 3));
	m_pResultTableWidget->setItem(1, 5, m_pItem11);

	m_pItem6 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fDTSetting, 'f',3));
	m_pResultTableWidget->setItem(1, 1, m_pItem6);

	m_pItem7 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAccRelErr, 'f', 3));
	m_pResultTableWidget->setItem(2, 3, m_pItem7);

	m_pItem8 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAccAbsErr, 'f', 3));
	m_pResultTableWidget->setItem(2, 4, m_pItem8);

	m_pItem12 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fTtripAccAbsErrMinus, 'f', 3));
	m_pResultTableWidget->setItem(2, 5, m_pItem12);

	m_pItem9 = new QTableWidgetItem(QString::number(m_oCBOperateParas->m_fAccTSetting, 'f',3));
	m_pResultTableWidget->setItem(2, 1, m_pItem9);

	m_pCmbActionTime->setCurrentIndex(m_oCBOperateParas->m_nTtripErrorLogic);
	m_pCmbTtripTime->setCurrentIndex(m_oCBOperateParas->m_nTtripDErrorLogic);
	m_pCmbAccTime->setCurrentIndex(m_oCBOperateParas->m_nTtripAccErrorLogic);

	slot_CmbActionTime(m_oCBOperateParas->m_nTtripErrorLogic);
	slot_CmbTripTime(m_oCBOperateParas->m_nTtripDErrorLogic);
	slot_CmbAccTime(m_oCBOperateParas->m_nTtripAccErrorLogic);
}

void CBOperateResultAssessGrid::slot_cellClicked(int row ,int col)
{

	if (col == 3 && row >= 0 && row <= 2) 
	{
		QTableWidgetItem *item = m_pResultTableWidget->item(row, col);
		if (item) 
		{
			float fv = item->text().toFloat();
			fv = setLimit(0,100.000,fv);
			item->setText(QString::number(fv, 'f', 3)); 
		}
	}
	if (col == 4 && row >= 0 && row <= 2) 
	{
		QTableWidgetItem *item2 = m_pResultTableWidget->item(row, col);
		if (item2) 
		{
			float fv = item2->text().toFloat();
			fv = setLimit(0,200.000,fv);
			item2->setText(QString::number(fv, 'f', 3)); 
		}
	}
	if (col == 5 && row >= 0 && row <= 2)
	{
		QTableWidgetItem *item2 = m_pResultTableWidget->item(row, col);
		if (item2)
		{
			float fv = item2->text().toFloat();
			fv = setLimit(0, 200.000, fv);
			item2->setText(QString::number(fv, 'f', 3));
		}
	}
}
void CBOperateResultAssessGrid::slot_Item3()
{
		float fv = m_pItem3->text().toFloat();
	fv = setLimit(0, 999.999, fv);
		m_pItem3->setText(QString::number(fv, 'f', 3));
}
void CBOperateResultAssessGrid::slot_Item6()
{
		float fv = m_pItem6->text().toFloat();
	fv = setLimit(0, 999.999, fv);
		m_pItem6->setText(QString::number(fv, 'f', 3));
}
void CBOperateResultAssessGrid::slot_Item9()
{
		float fv = m_pItem9->text().toFloat();
	fv = setLimit(0, 999.999, fv);
		m_pItem9->setText(QString::number(fv, 'f', 3));
}
