#include "GoosePubWidget.h"
#include <QDebug>
#include <QSpacerItem>

#include "../SttUIDefine.h"
#include "../../Module/SttTestSysGlobalPara.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#include "../../SttTestCntrFrameBase.h"

#include "qgooseparawidget.h"
#include "../../Controls/SttCheckBox.h"

extern long g_nLogDebugInfor;

//2022-3-20  lijunqing 注释
//#pragma execution_character_set("utf-8")
GoosePubWidget::GoosePubWidget(QGooseParaWidget *pParaWidget,QWidget *parent)
	: QWidget(parent)
{
	m_pIecCfgGoutChsGrid = NULL;
	m_pCfgGoutData = NULL;
	m_pParent = pParaWidget;

	initUI();
	SetGoosePubFont();
	connect(chb_Invert, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InvertStateChanged(int)));
	connect(chb_Repair, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_RepairStateChanged(int)));
}

GoosePubWidget::~GoosePubWidget()
{

}

void GoosePubWidget::SetGoosePubFont()
{
	label_IEDName->setFont(*g_pSttGlobalFont);
	lne_IEDName->setFont(*g_pSttGlobalFont);
	label_APPID->setFont(*g_pSttGlobalFont);
	lne_APPID->setFont(*g_pSttGlobalFont);
	chb_Invert->setFont(*g_pSttGlobalFont);
	chb_Repair->setFont(*g_pSttGlobalFont);
}

void GoosePubWidget::initUI()
{
	QGroupBox *groupBox;
	QGridLayout *gridLayout,*gridLayout_2;
	QHBoxLayout *horizontalLayout;
	QSpacerItem *horizontalSpacer;
	
	setObjectName(QString::fromUtf8("GoosePubWidget"));
	resize(295, 362);
	
// 	QFont font;
// 	font.setPointSize(20);
// 	setFont(font);

	gridLayout_2 = new QGridLayout(this);
	gridLayout_2->setSpacing(2);
	gridLayout_2->setContentsMargins(11, 11, 11, 11);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	gridLayout_2->setContentsMargins(-1, 2, -1, 2);

	m_pIecCfgGoutChsGrid = new CIecCfgGoutChsGrid(this);
	m_pIecCfgGoutChsGrid->setFont(*g_pSttGlobalFont);
	m_pIecCfgGoutChsGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgGoutChsGrid->InitGrid();
	gridLayout_2->addWidget(m_pIecCfgGoutChsGrid, 2, 0, 1, 1);
	m_pIecCfgGoutChsGrid->setDisabled(m_pParent->m_bGooseFlag);

	groupBox = new QGroupBox(this);
	groupBox->setObjectName(QString::fromUtf8("groupBox"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
	groupBox->setSizePolicy(sizePolicy);
// 	QFont font1;
// 	font1.setPointSize(20);
//	groupBox->setFont(font1);

	gridLayout = new QGridLayout(groupBox);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
	gridLayout->setHorizontalSpacing(2);
	gridLayout->setVerticalSpacing(1);
	gridLayout->setContentsMargins(4, 2, 4, 2);

	label_IEDName = new QLabel(groupBox);
	label_IEDName->setObjectName(QString::fromUtf8("label_IEDName"));
	CString strIEDName;
	xlang_GetLangStrByFile(strIEDName,"Native_IEDName");
//	label_IEDName->setText(tr("IED名称"));
	label_IEDName->setText(strIEDName);

	gridLayout->addWidget(label_IEDName, 0, 0, 1, 1);

	lne_IEDName = new QLineEdit(groupBox);
	lne_IEDName->setObjectName(QString::fromUtf8("lne_IEDName"));
	lne_IEDName->setEnabled(false);
	gridLayout->addWidget(lne_IEDName, 0, 1, 1, 1);

	label_APPID = new QLabel(groupBox);
	label_APPID->setObjectName(QString::fromUtf8("label_APPID"));
	CString strAppID;
	xlang_GetLangStrByFile(strAppID,"Native_APPID");
//	label_APPID->setText(tr("应用标识(APPID)    0x"));
	label_APPID->setText(strAppID);
	gridLayout->addWidget(label_APPID, 0, 2, 1, 1);

	lne_APPID = new QLineEdit(groupBox);
	lne_APPID->setObjectName(QString::fromUtf8("lne_APPID"));
	lne_APPID->setEnabled(false);
	gridLayout->addWidget(lne_APPID, 0, 3, 1, 1);

	horizontalLayout = new QHBoxLayout();
	horizontalLayout->setSpacing(6);
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	horizontalSpacer = new QSpacerItem(102, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	horizontalLayout->addItem(horizontalSpacer);

	chb_Invert = new QSttCheckBox(groupBox);
	chb_Invert->setObjectName(QString::fromUtf8("chb_Invert"));
	CString strReverse;
	xlang_GetLangStrByFile(strReverse,"Native_Reverse");
//	chb_Invert->setText(tr("取反"));
	chb_Invert->setText(strReverse);
// 	font1 = chb_Invert->font();
// 	font1.setPointSize(20);
// 	chb_Invert->setFont(font1);

	horizontalLayout->addWidget(chb_Invert);
	chb_Invert->setDisabled(m_pParent->m_bGooseFlag);//开始之后取反置灰

	chb_Repair = new QSttCheckBox(groupBox);
	chb_Repair->setObjectName(QString::fromUtf8("chb_Repair"));
	CString strRepair;
	xlang_GetLangStrByFile(strRepair,"Native_Repair");
//	chb_Repair->setText(tr("置检修"));
	chb_Repair->setText(strRepair);
// 	font1 = chb_Repair->font();
// 	font1.setPointSize(20);
// 	chb_Repair->setFont(font1);

	horizontalLayout->addWidget(chb_Repair);
	chb_Repair->setDisabled(m_pParent->m_bGooseFlag);//开始之后置检修置灰

	gridLayout->addLayout(horizontalLayout, 0, 4, 1, 1);
	gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);
}

void GoosePubWidget::initData( CIecCfgGoutData *pCfgGoutData, bool bInitEditable)
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>>>>>> begin GoosePubWidget::initData   >>");	}

	m_pCfgGoutData = pCfgGoutData;
	CString str = m_pCfgGoutData->m_strIedRefDesc;
	
	lne_IEDName->setText(str);
	lne_APPID->setText(QString("%1").arg(m_pCfgGoutData->m_dwAppID,4,16,QChar('0')));
	ASSERT(pCfgGoutData->m_pCfgChs);
	
	if (bInitEditable)
	{
		m_pIecCfgGoutChsGrid->SetRunState(STT_UI_RUN_STATE_Stoped);
	}
	else
	{
		m_pIecCfgGoutChsGrid->SetRunState(STT_UI_RUN_STATE_StateTested_Editable);
	}

	chb_Repair->setChecked(m_pCfgGoutData->m_bTest);

	m_pIecCfgGoutChsGrid->ShowDatas(pCfgGoutData->m_pCfgChs);
 	connect(m_pIecCfgGoutChsGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()),Qt::DirectConnection);
	connect(m_pIecCfgGoutChsGrid,SIGNAL(sig_GoutMap_Changed()),this,SLOT(slot_GoutMapChanged()));


	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> >>>>>>>>>> end GoosePubWidget::initData   >>");	}
}

void GoosePubWidget::slot_chb_InvertStateChanged( int nStateValue)
{
	if (m_pIecCfgGoutChsGrid->m_bIsUpdateParas)
	{
		disconnect(chb_Invert, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InvertStateChanged(int)));
		chb_Invert->setChecked(!nStateValue);
		connect(chb_Invert, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_InvertStateChanged(int)));
		return;
	}

	m_pIecCfgGoutChsGrid->m_bIsUpdateParas = TRUE;
	ASSERT(m_pIecCfgGoutChsGrid);
	disconnect(m_pIecCfgGoutChsGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()));
	m_pIecCfgGoutChsGrid->UpdateData_AllValues(nStateValue);
	emit sig_GooseDataChanged();
	connect(m_pIecCfgGoutChsGrid,SIGNAL(sig_GoutValue_Changed()),this,SLOT(slot_dataChanged()),Qt::DirectConnection);
	m_pIecCfgGoutChsGrid->m_bIsUpdateParas = FALSE;
}

void GoosePubWidget::slot_chb_RepairStateChanged( int nStateValue)
{
	if (m_pCfgGoutData == NULL)
	{
		return;
	}

	disconnect(chb_Repair, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_RepairStateChanged(int)));

	if (m_pIecCfgGoutChsGrid->m_bIsUpdateParas)
	{
		chb_Repair->setChecked(!nStateValue);
	}
	else
	{
		m_pIecCfgGoutChsGrid->m_bIsUpdateParas = TRUE;

		if (chb_Repair->isChecked())
		{
			m_pCfgGoutData->m_bTest = 1;
		}
		else
		{
			m_pCfgGoutData->m_bTest = 0;
		}

		emit sig_GooseDataChanged();
		m_pIecCfgGoutChsGrid->m_bIsUpdateParas = FALSE;
	}

	connect(chb_Repair, SIGNAL(stateChanged (int)), this, SLOT(slot_chb_RepairStateChanged(int)));
}

void GoosePubWidget::slot_dataChanged()
{
	Q_EMIT sig_GooseDataChanged();
}

void GoosePubWidget::slot_GoutMapChanged()
{
	Q_EMIT sig_GoutMapChanged();
}

void GoosePubWidget::SetRunState(int nRunState)
{
	ASSERT(m_pIecCfgGoutChsGrid);
	m_pIecCfgGoutChsGrid->SetRunState(nRunState);
}

void GoosePubWidget::EnableInverseCol(BOOL bEnable)
{
	m_pIecCfgGoutChsGrid->EnableInverseCol(bEnable);
}

void GoosePubWidget::SetTestCheckBox_Visible(BOOL bVisible)
{
	chb_Repair->setVisible(bVisible);
}