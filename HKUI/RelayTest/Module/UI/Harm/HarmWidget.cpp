#include "HarmWidget.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "SttMacroParaEditViewHarm.h"
#include "../SttTestCntrFrameAPI.h"
#include "../Controls/SttTabWidget.h"
#include "HarmEstimateDlg.h"
int    g_nUpdateActTime = -1;
QString g_strContent;


QHarmWidget::QHarmWidget(QWidget *parent) : QParaSetBase(parent)
{
	m_pHarmTest = NULL;
    //m_pOscillogramGroupWidget = NULL;
	m_pExBinParaWidget = NULL;	//扩展开入设置
	m_pExBoutParaWidget = NULL;	//扩展开出设置
	m_pGooseParaWidget = NULL;	//GOOSE数据发送
	m_pFT3OutParaWidget = NULL;
	m_bIsChanging = false;
	m_pInterharmonicsWidget = NULL;
	InitUI();
	SetHarmFont();

	
}

QHarmWidget::~QHarmWidget()
{
	if (m_lne_BasicHarmHz != NULL)
	{
		delete m_lne_BasicHarmHz;
		m_lne_BasicHarmHz = NULL;
	}
	m_strIChannelList.clear();
	m_strUChannelList.clear();
}

void QHarmWidget::InitUI()
{
	m_pVBoxLayout_Main = new QVBoxLayout(this);
	this->setLayout(m_pVBoxLayout_Main);
	
	m_pParaTable = new QHarmParaTable(this);
	m_pParaWidget = new QHarmParaWidget(this);
	m_pTabWidget = new QSttTabWidget(this);
	m_pTabWidget->setFont(*g_pSttGlobalFont);
    //m_pOscillogramGroupWidget = new OscillogramGroupWidget(this);
	
	CString strTitle,strText;
	xlang_GetLangStrByFile(strTitle,"Manual_IV");
	m_pTabWidget->addTab(m_pParaTable,strTitle);

	xlang_GetLangStrByFile(strTitle,"Manual_OtherParam");
	m_pTabWidget->addTab(m_pParaWidget,strTitle);

	xlang_GetLangStrByFile(strTitle,"Manual_Oscillogram");//新增波形图显示 20230202 zhouyy
    //m_pTabWidget->addTab(m_pOscillogramGroupWidget,strTitle);

	xlang_GetLangStrByFile(strTitle,"Harm_InterHarm");
	m_pTabWidget->addTab(m_pInterharmonicsWidget,strTitle);

// 	QFont font = m_pTabWidget->font();
// 	font.setPointSize(20);
// 	m_pTabWidget->setFont(font);

	m_pVBoxLayout_Main->addWidget(m_pTabWidget);

	m_pGridLayout_Bottom = new QGridLayout(this);

	m_Label_UChannel = new QLabel(tr("电压通道"),this);

	xlang_SetLangStrToWidget(m_Label_UChannel, "Harm_UChannel", XLang_Ctrls_QLabel);
	m_pGridLayout_Bottom->addWidget(m_Label_UChannel,0,0);
	m_pUChannel = new QScrollComboBox();
	m_pUChannel->setFixedWidth(150);
	m_pGridLayout_Bottom->addWidget(m_pUChannel,0,1);

	m_Label_IChannel = new QLabel(tr("电流通道"),this);
	xlang_SetLangStrToWidget(m_Label_IChannel, "Harm_IChannel", XLang_Ctrls_QLabel);
	m_pGridLayout_Bottom->addWidget(m_Label_IChannel,0,2);

	m_pIChannel = new QScrollComboBox(this);
	m_pIChannel->setFixedWidth(150);
	m_pGridLayout_Bottom->addWidget(m_pIChannel,0,3);
	
	m_pbn_SetZero = new QPushButton(tr("谐波清零"),this);
	xlang_SetLangStrToWidget(m_pbn_SetZero, "Harm_Reset", XLang_Ctrls_QPushButton);
	m_pGridLayout_Bottom->addWidget(m_pbn_SetZero,1,3);

 	m_pbnEstimate = new QPushButton(tr(""),this);
	//xlang_SetLangStrToWidget(m_pbnEstimate, "State_Estimate", XLang_Ctrls_QPushButton);//整定及结果评估 
	m_pbnEstimate->setText(g_sLangTxt_StateEstimate_ResultEstimate);
 	m_pGridLayout_Bottom->addWidget(m_pbnEstimate,1,4);

	strText = "电压清空";
	m_pVolSelBtn = new QPushButton(strText,this);//电压全选/清空 
	xlang_SetLangStrToWidget(m_pVolSelBtn, "Harm_UClear", XLang_Ctrls_QPushButton);
	m_pGridLayout_Bottom->addWidget(m_pVolSelBtn,1,5);

	strText = "电流清空";
	m_pCurrSelBtn = new QPushButton(strText,this);//电流全选/清空 
	xlang_SetLangStrToWidget(m_pCurrSelBtn, "Harm_IClear", XLang_Ctrls_QPushButton);
	m_pGridLayout_Bottom->addWidget(m_pCurrSelBtn,1,6);

// 	m_pVolSelBtn->setVisible(false);
// 	m_pCurrSelBtn->setVisible(false);

	CString strBasicHarmHz;
	xlang_GetLangStrByFile(strBasicHarmHz,"Harm_FundFreq");
	strBasicHarmHz += "(Hz):";
	m_Label_BasicHarmHz = new QLabel(tr("基波频率"),this);
	m_Label_BasicHarmHz->setText(strBasicHarmHz);
	m_pGridLayout_Bottom->addWidget(m_Label_BasicHarmHz,1,0);

	//m_lne_BasicHarmHz = new QSttLineEdit(this);
	m_lne_BasicHarmHz = new QSettingLineEdit(this);	//20240624 huangliang
	m_lne_BasicHarmHz->setFixedWidth(150);
	m_pGridLayout_Bottom->addWidget(m_lne_BasicHarmHz,1,1);

	m_pbn_Add = new QPushButton(tr("+"),this);
	m_pGridLayout_Bottom->addWidget(m_pbn_Add,0,5);
	m_pbn_Add->setFixedWidth(100);

	m_pbn_Del = new QPushButton(tr("-"),this);
	m_pGridLayout_Bottom->addWidget(m_pbn_Del,0,6);
	m_pbn_Del->setFixedWidth(100);

	//增加一个空白的QLabel，使gridLayout的第四列变宽
// 	QLabel *pLable_Ex = new QLabel(tr("      "),this);
// 	m_pGridLayout_Bottom->addWidget(pLable_Ex,1,7);
// 	pLable_Ex->setFixedWidth(100);

	m_pbn_Lock = new QPushButton(tr("锁"),this);

	//xlang_SetLangStrToWidget(m_pbn_Lock, "Manual_Lock", XLang_Ctrls_QPushButton);
	m_pGridLayout_Bottom->addWidget(m_pbn_Lock,0,4);
	m_pbn_Lock->setDisabled(true);
#ifdef _PSX_QT_WINDOWS_
	CString strImagePath = _P_GetResourcePath();
	m_imgLock.addFile(strImagePath + "Lock.png");
	m_imgUnlock.addFile(strImagePath + "Unlock.png");
#else
    CString strImagePath ;
	strImagePath = ":/ctrls/images/Lock.png";
	m_imgLock.addFile(strImagePath);
	strImagePath = ":/ctrls/images/Unlock.png";
    m_imgUnlock.addFile(strImagePath);
#endif
	m_pbn_Lock->setIcon(m_imgUnlock);
	m_pbn_Lock->setIconSize(QSize(m_pbn_Add->height(), m_pbn_Add->height()));
	m_pbn_Lock->setFixedWidth(m_pbn_Add->width());
	m_pbn_Lock->setFixedHeight(m_pbn_Add->height());
	m_pbn_Lock->setText("");

	//2024-8-7 wuxy 设置按钮大小一致
#ifdef _PSX_QT_WINDOWS_
	int nWidth = 120, nHeight = 30;
	for (int nRow = 0; nRow < m_pGridLayout_Bottom->rowCount(); nRow++)
	{
		for (int nCol = 0; nCol < m_pGridLayout_Bottom->columnCount(); nCol++)
		{
			QLayoutItem *item = m_pGridLayout_Bottom->itemAtPosition(nRow, nCol);
			if (item)
			{
				QWidget *widget = item->widget();
				if (widget)
				{
					// 设置控件的固定高度
					widget->setFixedSize(nWidth, nHeight);
				}
			}
		}
	}
#endif

//	m_pGridLayout_Bottom->setRowStretch(1,1);

	/*
	m_Label_ActValue = new QLabel(tr("动作值(V):"),this);
	m_Label_ActValue->setFont(font);
	xlang_SetLangStrToWidget(m_Label_ActValue, "Native_Action", XLang_Ctrls_QLabel);
	m_pGridLayout_Bottom->addWidget(m_Label_ActValue,1,4);

	m_lne_ActionValue = new QLineEdit(this);
	m_lne_ActionValue->setFont(font);
	m_pGridLayout_Bottom->addWidget(m_lne_ActionValue,1,5);
	m_lne_ActionValue->setStyleSheet(QString::fromUtf8("QLineEdit { background-color:gray;color:white;}"));
	m_lne_ActionValue->setReadOnly(true);

	m_Label_ActTime = new QLabel(tr("动作时间(s):"),this);
	m_Label_ActTime->setFont(font);
	xlang_SetLangStrToWidget(m_Label_ActTime, "Manual_ActionTime", XLang_Ctrls_QLabel);
	m_pGridLayout_Bottom->addWidget(m_Label_ActTime,1,6);

	m_lne_ActionTime = new QLineEdit(this);
	m_lne_ActionTime->setFont(font);
	m_pGridLayout_Bottom->addWidget(m_lne_ActionTime,1,7);
	m_lne_ActionTime->setStyleSheet(QString::fromUtf8("QLineEdit { background-color:gray;color:white;}"));
	m_lne_ActionTime->setReadOnly(true);
	*/	

	m_pVBoxLayout_Main->addLayout(m_pGridLayout_Bottom);

}

void QHarmWidget::SetHarmFont()
{
	m_pbn_Lock->setFont(*g_pSttGlobalFont);
	m_pbn_Del->setFont(*g_pSttGlobalFont);
	m_pbn_Add->setFont(*g_pSttGlobalFont);
	m_lne_BasicHarmHz->setFont(*g_pSttGlobalFont);
	m_Label_BasicHarmHz->setFont(*g_pSttGlobalFont);
	m_pbn_SetZero->setFont(*g_pSttGlobalFont);
	m_pVolSelBtn->setFont(*g_pSttGlobalFont);
	m_pCurrSelBtn->setFont(*g_pSttGlobalFont);
	m_pIChannel->setFont(*g_pSttGlobalFont);
	m_Label_IChannel->setFont(*g_pSttGlobalFont);
	m_pUChannel->setFont(*g_pSttGlobalFont);
	m_Label_UChannel->setFont(*g_pSttGlobalFont);
	m_pTabWidget->setFont(*g_pSttGlobalFont);
	m_pbnEstimate->setFont(*g_pSttGlobalFont);
}

void QHarmWidget::UpdateVolCurTable(bool bSate)
{

	if (bSate)//电压电流全选需要显示
	{
		m_pGridLayout_Bottom->removeWidget(m_pbn_SetZero);
		m_pGridLayout_Bottom->removeWidget(m_pbnEstimate);
		m_pGridLayout_Bottom->addWidget(m_pbn_SetZero, 1, 3);
		m_pGridLayout_Bottom->addWidget(m_pbnEstimate, 1, 4);		
		m_pGridLayout_Bottom->addWidget(m_pVolSelBtn, 1, 5);
		m_pGridLayout_Bottom->addWidget(m_pCurrSelBtn, 1, 6);

		m_pVolSelBtn->show();
		m_pCurrSelBtn->show();
	}
	else
	{
		m_pVolSelBtn->hide();
		m_pCurrSelBtn->hide();

		m_pGridLayout_Bottom->removeWidget(m_pVolSelBtn);
		m_pGridLayout_Bottom->removeWidget(m_pCurrSelBtn);
		m_pGridLayout_Bottom->addWidget(m_pbn_SetZero , 1, 5);
		m_pGridLayout_Bottom->addWidget(m_pbnEstimate, 1, 6);
	}

}

void QHarmWidget::SetDatas( tmt_HarmTest *pHarmTest,CSttTestResourceBase *pSttTestResource )
{
	DisConnectAll();
	m_pHarmTest = pHarmTest;
#ifndef _PSX_QT_LINUX_// zhouhj  20230628 在linux下暂时不显示间谐波
	if (!m_pInterharmonicsWidget)
	{
		m_pInterharmonicsWidget = new QInterharmonicsWidget(&m_pHarmTest->m_oHarmParas, this);
		m_pTabWidget->insertTab(1, m_pInterharmonicsWidget, g_sLangTxt_Harm_InterHarm);
		connect(m_pInterharmonicsWidget, SIGNAL(sig_updataParas()), g_pHarmTest, SLOT(slot_updateParas()), Qt::UniqueConnection);
	
	}
	else
	{
		disconnect(m_pInterharmonicsWidget, SIGNAL(sig_updataParas()), g_pHarmTest, SLOT(slot_updateParas()));
		m_pInterharmonicsWidget->m_pParas = &m_pHarmTest->m_oHarmParas;
		m_pInterharmonicsWidget->setPropertyOfParaSet(P_Common, stt_GetSttTestResource(), m_pInterharmonicsWidget->m_pParas->m_uiVOL, m_pInterharmonicsWidget->m_pParas->m_uiCUR);
		connect(m_pInterharmonicsWidget, SIGNAL(sig_updataParas()), g_pHarmTest, SLOT(slot_updateParas()), Qt::UniqueConnection);
	}
#endif

 	m_pSttTestResource = pSttTestResource;
// 	m_pOscillogramGroupWidget->setArrUIVOL(m_pHarmTest->m_oHarmParas.m_uiVOL);
// 	m_pOscillogramGroupWidget->setArrUICUR(m_pHarmTest->m_oHarmParas.m_uiCUR);
// 	m_pOscillogramGroupWidget->Clear();
// 	m_pOscillogramGroupWidget->initUI(m_pSttTestResource);//20230215 zhouyy 设置参数到波形图

	int nVolChIndex = m_pHarmTest->m_oHarmParas.m_nVolChSelect; // m_pUChannel->currentIndex();//20240327 suyang 初始化时获取到结构体中值，不应该获取到当前选中数据 
	int nCurrChIndex =  m_pHarmTest->m_oHarmParas.m_nCurChSelect; // m_pIChannel->currentIndex();
	m_strIChannelList.clear();
	m_strUChannelList.clear();
	m_pUChannel->clear();
	m_pIChannel->clear();

	if (pSttTestResource != NULL)
	{
		m_pParaSetSttTestResource = pSttTestResource;
	}

	if (m_pParaSetSttTestResource == NULL)
	{
		return;
	}

	POS pos = pSttTestResource->m_oListGroups.GetHeadPosition();
	CSttChGroupResource *pObj = NULL;
	CSttChResource *pChResource = NULL;
	QHarmTable *pHarmTable = NULL;

	while(pos)
	{
		pObj = (CSttChGroupResource*)pSttTestResource->m_oListGroups.GetNext(pos);

		POS posObj = pObj->GetHeadPosition();
		while(posObj)
		{
			pChResource = (CSttChResource *)pObj->GetNext(posObj);

			if (pChResource)
			{
			if (pChResource->IsVolCh())
			{
					m_strUChannelList << pChResource->m_strName;
			}
			else
			{
					m_strIChannelList << pChResource->m_strName;
			}
			}

		}
	}
	m_pUChannel->addItems(m_strUChannelList);
	m_pIChannel->addItems(m_strIChannelList);

	if ((nVolChIndex >= m_strUChannelList.size())||(nVolChIndex<0))
	{
		nVolChIndex = 0;
	}

	if ((nCurrChIndex >= m_strIChannelList.size())||(nCurrChIndex<0))
	{
		nCurrChIndex = 0;
	}

	m_pUChannel->setCurrentIndex(nVolChIndex);
	m_pIChannel->setCurrentIndex(nCurrChIndex);
	slot_UChannelChanged(nVolChIndex);
	slot_IChannelChanged(nCurrChIndex);

	m_pParaWidget->SetData(m_pParaSetSttTestResource,&m_pHarmTest->m_oHarmParas);

	bool bAuto = pHarmTest->m_oHarmParas.m_bAuto;
	m_pbn_Add->setDisabled(bAuto);
	m_pbn_Del->setDisabled(bAuto);

	//20240624 huangliang
	//m_lne_BasicHarmHz->setText(QString::number(pHarmTest->m_oHarmParas.m_fBaseFre, 'f', 3));
	m_lne_BasicHarmHz->UpdateStructText(CVariantDataAddress(&pHarmTest->m_oHarmParas.m_fBaseFre), 3);

	ConnectAll();
}

void QHarmWidget::ConnectAll()
{
	connect(m_pParaWidget,SIGNAL(sig_AutoStateChanged(bool)),this,SLOT(slot_AutoStateChanged(bool)),Qt::UniqueConnection);
	connect(m_pUChannel,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_UChannelChanged(int)),Qt::UniqueConnection);
	connect(m_pIChannel,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_IChannelChanged(int)),Qt::UniqueConnection);

	connect(m_lne_BasicHarmHz, SIGNAL(editingFinished ()), this, SLOT(slot_lne_BasicHarmHzChanged()),Qt::UniqueConnection);
	connect(m_pbn_SetZero, SIGNAL(clicked ()), this, SLOT(slot_pbn_SetZeroClicked()),Qt::UniqueConnection);
	connect(m_pbn_Add, SIGNAL(clicked ()), this, SLOT(slot_pbn_AddClicked()),Qt::UniqueConnection);
	connect(m_pbn_Del, SIGNAL(clicked ()), this, SLOT(slot_pbn_DelClicked()),Qt::UniqueConnection);
	connect(m_pbn_Lock, SIGNAL(clicked ()), this, SLOT(slot_pbn_LockClicked()),Qt::UniqueConnection);
	connect(m_pbnEstimate, SIGNAL(clicked ()), this, SLOT(slot_pbn_Estimate()),Qt::UniqueConnection);

	connect(m_pVolSelBtn, SIGNAL(clicked ()), this, SLOT(slot_VolSelBtnClicked()),Qt::UniqueConnection);
	connect(m_pCurrSelBtn, SIGNAL(clicked ()), this, SLOT(slot_CurrSelBtnClicked()),Qt::UniqueConnection);

	connect(m_pParaTable->m_pUChannel,SIGNAL(sig_updataParas()), this, SIGNAL(sig_updataParas()),Qt::UniqueConnection);
	connect(m_pParaTable->m_pIChannel,SIGNAL(sig_updataParas()), this, SIGNAL(sig_updataParas()),Qt::UniqueConnection);

	connect(m_pParaTable->m_pUChannel,  SIGNAL(sig_ChanelValueChanged()),   this,  SLOT(slot_ChanelValueUChanged()),Qt::UniqueConnection);
	connect(m_pParaTable->m_pUChannel,  SIGNAL(sig_WaveValueChanged()),   this,  SLOT(slot_WaveValueUChanged()),Qt::UniqueConnection);

	connect(m_pParaTable->m_pIChannel,  SIGNAL(sig_ChanelValueChanged()),   this,  SLOT(slot_ChanelValueIChanged()),Qt::UniqueConnection);
	connect(m_pParaTable->m_pIChannel,  SIGNAL(sig_WaveValueChanged()),   this,  SLOT(slot_WaveValueIChanged()),Qt::UniqueConnection);

	connect(m_pParaTable->m_pUChannel,  SIGNAL(sig_ChIndexChanged(int)), this, SLOT(slot_ChIndexChanged(int)),Qt::UniqueConnection);
	connect(m_pParaTable->m_pIChannel,  SIGNAL(sig_ChIndexChanged(int)), this, SLOT(slot_ChIndexChanged(int)),Qt::UniqueConnection);

// 	connect(m_pParaTable->m_pUChannel,  SIGNAL(sig_CheckStateChanged()),   this,  SLOT(slot_CheckStateChanged()),Qt::UniqueConnection);
// 	connect(m_pParaTable->m_pIChannel,  SIGNAL(sig_CheckStateChanged()),   this,  SLOT(slot_CheckStateChanged()),Qt::UniqueConnection);


//	connect(this, SIGNAL(sig_WaveValueChanged(int,int)), m_pOscillogramGroupWidget, SLOT(slot_ValueChanged(int,int)),Qt::UniqueConnection);
//	connect(this, SIGNAL(sig_ChIndexChanged(int)),m_pOscillogramGroupWidget,SLOT(slot_ChnIndexChanged(int)),Qt::UniqueConnection);
	//20230217 zyy 增加数据改变对应的波形图更新响应
#ifdef _PSX_QT_LINUX_
	connect(m_lne_BasicHarmHz, SIGNAL(clicked()), this, SLOT(slot_lne_BasicHarmHzClicked()),Qt::UniqueConnection);
#endif
}

void QHarmWidget::DisConnectAll()
{
	disconnect(m_pParaWidget,SIGNAL(sig_AutoStateChanged(bool)),this,SLOT(slot_AutoStateChanged(bool)));
	disconnect(m_pUChannel,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_UChannelChanged(int)));
	disconnect(m_pIChannel,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_IChannelChanged(int)));

	disconnect(m_lne_BasicHarmHz, SIGNAL(editingFinished ()), this, SLOT(slot_lne_BasicHarmHzChanged()));
	disconnect(m_pbn_SetZero, SIGNAL(clicked ()), this, SLOT(slot_pbn_SetZeroClicked()));
	disconnect(m_pbn_Add, SIGNAL(clicked ()), this, SLOT(slot_pbn_AddClicked()));
	disconnect(m_pbn_Del, SIGNAL(clicked ()), this, SLOT(slot_pbn_DelClicked()));
	disconnect(m_pbn_Lock, SIGNAL(clicked ()), this, SLOT(slot_pbn_LockClicked()));
	disconnect(m_pbnEstimate, SIGNAL(clicked ()), this, SLOT(slot_pbn_Estimate()));

	disconnect(m_pVolSelBtn, SIGNAL(clicked ()), this, SLOT(slot_VolSelBtnClicked()));
	disconnect(m_pCurrSelBtn, SIGNAL(clicked ()), this, SLOT(slot_CurrSelBtnClicked()));

	disconnect(m_pParaTable->m_pUChannel,SIGNAL(sig_updataParas()), this, SIGNAL(sig_updataParas()));
	disconnect(m_pParaTable->m_pIChannel,SIGNAL(sig_updataParas()), this, SIGNAL(sig_updataParas()));

	disconnect(m_pParaTable->m_pUChannel,  SIGNAL(sig_ChanelValueChanged()),   this,  SLOT(slot_ChanelValueUChanged()));
	disconnect(m_pParaTable->m_pUChannel,  SIGNAL(sig_WaveValueChanged()),   this,  SLOT(slot_WaveValueUChanged()));

	disconnect(m_pParaTable->m_pIChannel,  SIGNAL(sig_ChanelValueChanged()),   this,  SLOT(slot_ChanelValueIChanged()));
	disconnect(m_pParaTable->m_pIChannel,  SIGNAL(sig_WaveValueChanged()),   this,  SLOT(slot_WaveValueIChanged()));

	disconnect(m_pParaTable->m_pUChannel,  SIGNAL(sig_ChIndexChanged(int)), this, SLOT(slot_ChIndexChanged(int)));
	disconnect(m_pParaTable->m_pIChannel,  SIGNAL(sig_ChIndexChanged(int)), this, SLOT(slot_ChIndexChanged(int)));

// 	disconnect(m_pParaTable->m_pUChannel,  SIGNAL(sig_CheckStateChanged()),   this,  SLOT(slot_CheckStateChanged()));
// 	disconnect(m_pParaTable->m_pIChannel,  SIGNAL(sig_CheckStateChanged()),   this,  SLOT(slot_CheckStateChanged()));


//	disconnect(this, SIGNAL(sig_WaveValueChanged(int,int)), m_pOscillogramGroupWidget, SLOT(slot_ValueChanged(int,int)));
//	disconnect(this, SIGNAL(sig_ChIndexChanged(int)),m_pOscillogramGroupWidget,SLOT(slot_ChnIndexChanged(int)));
	//20230217 zyy 增加数据改变对应的波形图更新响应
#ifdef _PSX_QT_LINUX_
	disconnect(m_lne_BasicHarmHz, SIGNAL(clicked()), this, SLOT(slot_lne_BasicHarmHzClicked()));
#endif
}


void QHarmWidget::slot_UChannelChanged( int nIndex )
{
	if(m_pUChannel->IsScrolling())
	{
		return;
	}

	if (nIndex < 0)
	{
		nIndex = 0;
	}
	
	CSttChResource *pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oVolChRsListRef.GetAt(nIndex));

	if (pChResource == NULL)
	{
		nIndex = 0;
		pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oVolChRsListRef.GetAt(nIndex));
	}
	m_pHarmTest->m_oHarmParas.m_nVolChSelect  = nIndex;

	m_pParaTable->m_pUChannel->Disconnect();
	m_pParaTable->m_pUChannel->SetData(pChResource,m_pHarmTest->m_oHarmParas.m_uiVOL);
}

void QHarmWidget::slot_IChannelChanged( int nIndex )
{
	if(m_pIChannel->IsScrolling())
	{
		return;
	}

	if (nIndex < 0)
	{
		nIndex = 0;
	}
	CSttChResource *pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oCurChRsListRef.GetAt(nIndex));

	if (pChResource == NULL)
	{
		nIndex = 0;
		pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oCurChRsListRef.GetAt(nIndex));
	}
	m_pHarmTest->m_oHarmParas.m_nCurChSelect = nIndex;
	m_pParaTable->m_pIChannel->Disconnect();
	m_pParaTable->m_pIChannel->SetData(pChResource,m_pHarmTest->m_oHarmParas.m_uiCUR);
}

void QHarmWidget::slot_lne_BasicHarmHzChanged()
{
	//20240705 huangliang 
	if (m_lne_BasicHarmHz->inherits(STT_SETTING_LINEEDIT_ClassID/*"QSettingEdit"*/))
	{
		if(((QSettingLineEdit*)m_lne_BasicHarmHz)->IsSetting())
		{
			return ;
		}		
	}
	float fv  = m_lne_BasicHarmHz->text().toFloat();

	if (fv <= 1)//20220816 基波频率最新按1Hz处理
	{
		fv = 1;
	}

	if (fv >= 500)
	{
		fv = 500;
	}
	m_lne_BasicHarmHz->setText(QString::number(fv,  'f',  3));
	m_pHarmTest->m_oHarmParas.m_fBaseFre  =  fv;
}

void QHarmWidget::slot_AutoStateChanged( bool bState )
{
	m_pbn_Add->setDisabled(bState);
	m_pbn_Del->setDisabled(bState);
}

void QHarmWidget::slot_pbn_SetZeroClicked()
{
	POS posU = m_pParaSetSttTestResource->m_oVolChRsListRef.GetHeadPosition();
	int nIndex = 0;
	CSttChResource* pObj = NULL;
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();

	while(posU)
	{
		pObj = (CSttChResource*)m_pParaSetSttTestResource->m_oVolChRsListRef.GetNext(posU);

		if (pObj != NULL)
		{
			for (int i  =  2; i < nMaxRowCount; i++)
			{
				m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].setAmp(i,0, g_oSystemParas.m_nHasAnalog + g_oSystemParas.m_nHasWeek);
			}
		}

		nIndex ++;
	}

	nIndex = 0;

	POS posI = m_pParaSetSttTestResource->m_oCurChRsListRef.GetHeadPosition();
	while(posI)
	{
		pObj = (CSttChResource*)m_pParaSetSttTestResource->m_oCurChRsListRef.GetNext(posI);

		if (pObj != NULL)
		{
			for (int i  =  2; i < nMaxRowCount; i++)
			{
				m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].setAmp(i,0, g_oSystemParas.m_nHasAnalog + g_oSystemParas.m_nHasWeek);
			}
		}

		nIndex ++;
	}

	slot_ResetChangeFlag(1);

	m_pParaTable->m_pUChannel->updataTableData();
	m_pParaTable->m_pIChannel->updataTableData();

	//2024-9-4 wuixnyi 谐波清零之后波形图没有刷新
#ifdef _PSX_QT_WINDOWS_
//	m_pOscillogramGroupWidget->slot_ChnIndexChanged(0);//传进的参数无论是多少，都刷新全部波形
#endif // DEBUG

	
	emit sig_SetToZero();
	emit sig_updataParas();//zhouhj 20220405 增加用于更新参数
}

void QHarmWidget::slot_pbn_AddClicked()
{
	IncreaseOneStepGradient();
}

void QHarmWidget::slot_pbn_DelClicked()
{	
	DecreaseOneStepGradient();
}

void QHarmWidget::slot_pbn_LockClicked()
{
	m_pHarmTest->m_oHarmParas.m_bBinStop = true;//周磊让改的 2021-7-1 mym add
	if (m_pHarmTest->m_oHarmParas.m_bLock)
	{
		m_bControlLock = true;
		m_pHarmTest->m_oHarmParas.m_bLock = false;
		//xlang_SetLangStrToWidget(m_pbn_Lock, "Manual_Lock", XLang_Ctrls_QPushButton);
		m_pbn_Lock->setIcon(m_imgUnlock);
		g_nUpdateActTime = 2;	
	}
	else
	{
		m_bControlLock = false;
		m_pHarmTest->m_oHarmParas.m_bLock = true;
		//xlang_SetLangStrToWidget(m_pbn_Lock, "Manual_UnLock", XLang_Ctrls_QPushButton);
		m_pbn_Lock->setIcon(m_imgLock);
		g_nUpdateActTime = 1; 
	}
	m_bControlLock = m_pHarmTest->m_oHarmParas.m_bLock;
	emit sig_LockChanged();
}

void QHarmWidget::slot_pbn_Estimate()
{
	HarmEstimateDlg dlg(&m_pHarmTest->m_oHarmParas, this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QHarmWidget::slot_VolSelBtnClicked()
{
	//2024-9-18 wuxinyi 按照需求修改为所有通道全部清空
// 	int nIndex = m_pUChannel->currentIndex();
// 	CSttChResource *pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oVolChRsListRef.GetAt(nIndex));
// 
// 	if (pChResource == NULL)
// 	{
// 		nIndex = 0;
// 		pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oVolChRsListRef.GetAt(nIndex));
// 	}
// 	int nChIndex = pChResource->GetChIndex_FromZero();
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();
	int nMaxHarmCount = 30;


	CString strText;
	bool bIsSelectAll = (m_pVolSelBtn->text() == g_sLangTxt_Harm_UAllSelect);
	strText = bIsSelectAll ? g_sLangTxt_Harm_UClear : g_sLangTxt_Harm_UAllSelect;

 	if (m_pParaTable->m_pUChannel == NULL)
 	{
 		return;
 	}

	// 2024-9-4 wuxinyi 暂停表格更新，优化界面刷新速度
	m_pParaTable->m_pUChannel->blockSignals(true);

	for (int nChIndex = 0; nChIndex < m_pParaSetSttTestResource->m_oVolChRsListRef.GetCount();nChIndex++)
	{
		for (int i = 0; i < nMaxRowCount; ++i)
		{
			if (bIsSelectAll)
			{
				if (i < nMaxHarmCount + 1)
			{
				m_pParaTable->m_pUChannel->item(i, 0)->setCheckState(Qt::Checked);
			m_pHarmTest->m_oHarmParas.m_uiVOL[nChIndex].Harm[i].m_bSelect = 1;
		}
		}
	else
	{
				m_pParaTable->m_pUChannel->item(i, 0)->setCheckState(Qt::Unchecked);
			m_pHarmTest->m_oHarmParas.m_uiVOL[nChIndex].Harm[i].m_bSelect = 0;
		}
	}

	}

	m_pParaTable->m_pUChannel->blockSignals(false);
	m_pVolSelBtn->setText(strText);

    //m_pOscillogramGroupWidget->slot_updateOscillogramGroup();

}

void QHarmWidget::slot_CurrSelBtnClicked()
{
// 	int nIndex = m_pIChannel->currentIndex();
// 	CSttChResource *pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oCurChRsListRef.GetAt(nIndex));
// 
// 	if (pChResource == NULL)
// 	{
// 		nIndex = 0;
// 		pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oCurChRsListRef.GetAt(nIndex));
// 	}
// 	int nChIndex = pChResource->GetChIndex_FromZero();
	long nMaxRowCount = Global_GetHarmTableMaxRowCount();
	int nMaxHarmCount = 30;
	CString strText;
	bool bIsSelectAll = (m_pCurrSelBtn->text() == g_sLangTxt_Harm_IAllSelect);
	strText = bIsSelectAll ? g_sLangTxt_Harm_IClear : g_sLangTxt_Harm_IAllSelect;

	if (m_pParaTable->m_pIChannel == NULL)
	{
		return;
	}

	m_pParaTable->m_pIChannel->blockSignals(true);
	for (int nChIndex = 0; nChIndex < m_pParaSetSttTestResource->m_oVolChRsListRef.GetCount(); nChIndex++)
	{
		for (int i = 0; i < nMaxRowCount; ++i)
	{
			if (bIsSelectAll)
		{
				if (i < nMaxHarmCount + 1)
			{
				m_pParaTable->m_pIChannel->item(i, 0)->setCheckState(Qt::Checked);
			m_pHarmTest->m_oHarmParas.m_uiCUR[nChIndex].Harm[i].m_bSelect = 1;
		}
		}
	else
	{
				m_pParaTable->m_pIChannel->item(i, 0)->setCheckState(Qt::Unchecked);
			m_pHarmTest->m_oHarmParas.m_uiCUR[nChIndex].Harm[i].m_bSelect = 0;
		}
	}
	}

	m_pParaTable->m_pIChannel->blockSignals(false);
	m_pCurrSelBtn->setText(strText);

    //m_pOscillogramGroupWidget->slot_updateOscillogramGroup();
}

void QHarmWidget::IncreaseOneStepGradient()
{
	float fStep = m_pParaWidget->m_pEdit_Step->text().toFloat();
	int nHarmIndex = m_pParaWidget->m_pCmb_HarmNum->currentIndex();
	int nChIndex = m_pParaWidget->m_pCmb_Chanel->currentIndex();
	CString str = m_pParaWidget->m_pCmb_Chanel->currentText();

	QStringList listName = str.split(",");

	BOOL bGradientVol = FALSE;
	int  nItem = 0;
	for (nItem = 0;  nItem < listName.size(); nItem++)
	{
		long nIndexTemp = 0;
		POS pos = m_pParaSetSttTestResource->GetHeadPosition();
		CSttChResource *pChResource = NULL;

		while(pos)
		{
			pChResource = (CSttChResource *)m_pParaSetSttTestResource->GetNext(pos);
			if (pChResource->m_strName == listName[nItem])		// 查找到相同名称的时候；
			{
				long nIndex = pChResource->GetChIndex_FromZero();
				if (pChResource->IsVolCh())
				{
					bGradientVol = TRUE;
					float fValue = m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp + fStep;

					if (m_pParaWidget->IsHarmGradPercentType())
					{
						 fValue = m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp + fStep*m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[1].fAmp/100;
					} 

					if (nHarmIndex != 0)
					{
						if (nHarmIndex == 1)
						{
							m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp = fValue;
						}

						m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].setAmp(nHarmIndex,fValue, g_oSystemParas.m_nHasAnalog + g_oSystemParas.m_nHasWeek);
					}
					else
					{
						m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp = fValue;
					}
				}
				else
				{
					float fValue = m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[nHarmIndex].fAmp + fStep;

					if (m_pParaWidget->IsHarmGradPercentType())
					{
						fValue = m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[nHarmIndex].fAmp + fStep*m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[1].fAmp/100;
					} 

					if (nHarmIndex != 0)
					{
						if (nHarmIndex == 1)
						{
							m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[nHarmIndex].fAmp = fValue;
						}
						m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].setAmp(nHarmIndex,fValue, g_oSystemParas.m_nHasAnalog + g_oSystemParas.m_nHasWeek);
					}
					else
					{
						m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp = fValue;
					}
				}

				//在存在模拟的情况下如果基波变化，需要重新确定谐波的最大值
// 				if(g_oSystemParas.m_nHasWeek || g_oSystemParas.m_nHasAnalog)//20220915 zhouhj 已去除对谐波的限制,统一由底层限制
// 				{
// 					tmt_Channel* pCh = NULL;
// 					if(pChResource->IsVolCh())
// 					{
// 						pCh = &m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex];
// 					}
// 					else
// 					{
// 						pCh = &m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex];
// 					}
// 					for (int i = 2; i < MAX_HARM_COUNT; i++)
// 					{
//  						if(pCh->Harm[i].fAmp > pCh->Harm[1].fAmp)
//  						{
//  							pCh->Harm[i].fAmp = pCh->Harm[1].fAmp;
//  						}	
// 					}
// 				}
			}
			nIndexTemp++;
		}
	}
	slot_ResetChangeFlag(1);

//	m_pOscillogramGroupWidget->slot_updateOscillogramGroup();

	if (bGradientVol)
	{
		m_pParaTable->m_pUChannel->updataTableData();
	} 
	else
	{
		m_pParaTable->m_pIChannel->updataTableData();
	}

	emit sig_updataParas();
}

void QHarmWidget::DecreaseOneStepGradient()
{
	float fStep  =  m_pParaWidget->m_pEdit_Step->text().toFloat();
	int nHarmIndex  = m_pParaWidget->m_pCmb_HarmNum->currentIndex();
	int nChIndex  =  m_pParaWidget->m_pCmb_Chanel->currentIndex();
	CString str = m_pParaWidget->m_pCmb_Chanel->currentText();

	QStringList listName = str.split(",");
	BOOL bGradientVol = FALSE;
	int  nItem = 0;
	for (nItem = 0;  nItem < listName.size(); nItem++)
	{
		long nIndexTemp = 0;
		POS pos = m_pParaSetSttTestResource->GetHeadPosition();
		CSttChResource *pChResource = NULL;

		while(pos)
		{
			pChResource = (CSttChResource *)m_pParaSetSttTestResource->GetNext(pos);

			if (pChResource->m_strName == listName[nItem])		// 查找到相同名称的时候；
			{
				long nIndex = pChResource->GetChIndex_FromZero();

				if (pChResource->IsVolCh())
				{
					bGradientVol = TRUE;
					float fValue = m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp - fStep;

					if (m_pParaWidget->IsHarmGradPercentType())
					{
						fValue = m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp - fStep*m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[1].fAmp/100;
					} 

					if (nHarmIndex == 0)
					{
						m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp = fValue;
					}
					else
						m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].setAmp(nHarmIndex,fValue, g_oSystemParas.m_nHasAnalog + g_oSystemParas.m_nHasWeek);
				}
				else
				{
					float fValue = m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[nHarmIndex].fAmp - fStep;

					if (m_pParaWidget->IsHarmGradPercentType())
					{
						fValue = m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[nHarmIndex].fAmp - fStep*m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[1].fAmp/100;
					} 

					if (nHarmIndex == 0)
					{
						m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[nHarmIndex].fAmp = fValue;
					}
					else
						m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].setAmp(nHarmIndex,fValue, g_oSystemParas.m_nHasAnalog + g_oSystemParas.m_nHasWeek);
				}

				//在存在模拟的情况下如果基波变化，需要重新确定谐波的最大值
// 				if(g_oSystemParas.m_nHasWeek || g_oSystemParas.m_nHasAnalog)//20220915 zhouhj 已去除对谐波的限制,统一由底层限制
// 				{
// 					tmt_Channel* pCh = NULL;
// 					if(pChResource->IsVolCh())
// 					{
// 						pCh = &m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex];
// 					}
// 					else
// 					{
// 						pCh = &m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex];
// 					}
// 					for (int i = 2; i < MAX_HARM_COUNT; i++)
// 					{
// 						if(pCh->Harm[i].fAmp > pCh->Harm[1].fAmp)
// 						{
// 							pCh->Harm[i].fAmp = pCh->Harm[1].fAmp;
// 						}	
// 					}
// 				}
			}
			nIndexTemp++;
		}
	}

	slot_ResetChangeFlag(1);

//	m_pOscillogramGroupWidget->slot_updateOscillogramGroup();

	if (bGradientVol)
	{
		m_pParaTable->m_pUChannel->updataTableData(nHarmIndex);
	}
	else
	{
		m_pParaTable->m_pIChannel->updataTableData(nHarmIndex);
	}

	emit sig_updataParas();
}

void QHarmWidget::StartInit()
{
	tmt_HarmParas *pHarmParas = &m_pHarmTest->m_oHarmParas;

	pHarmParas->m_bLock = false;
	pHarmParas->m_bBinStop = false;//周磊让改的 2021-7-1 mym add

	//m_lne_ActionTime->setText("");
	//m_lne_ActionValue->setText("");

	bool bAuto = pHarmParas->m_bAuto;

	m_pbn_Lock->setDisabled(bAuto);
	m_pbn_Add->setDisabled(bAuto);
	m_pbn_Del->setDisabled(bAuto);	

	//m_pUChannel->setDisabled(true);
	//m_pIChannel->setDisabled(true);

	m_lne_BasicHarmHz->setDisabled(bAuto);
	m_pbn_SetZero->setDisabled(bAuto);
	m_pbnEstimate->setDisabled(bAuto);

	//运行过程中,暂不支持
	m_pVolSelBtn->setEnabled(false);
	m_pCurrSelBtn->setEnabled(false);

	m_pParaWidget->StartInit();
}

void QHarmWidget::StopInit()
{
	tmt_HarmParas *pHarmParas = &m_pHarmTest->m_oHarmParas;

	m_pbn_Lock->setDisabled(pHarmParas->m_bAuto);
	m_pbn_Add->setDisabled(pHarmParas->m_bAuto);
	m_pbn_Del->setDisabled(pHarmParas->m_bAuto);

	m_bControlLock = true;
	pHarmParas->m_bLock = false;
	//xlang_SetLangStrToWidget(m_pbn_Lock, "Manual_Lock", XLang_Ctrls_QPushButton);
	m_pbn_Lock->setIcon(m_imgUnlock);
	m_pbn_Lock->setDisabled(true);
	m_pbn_SetZero->setDisabled(false);
	m_lne_BasicHarmHz->setDisabled(false);
	m_pbnEstimate->setDisabled(false);

	m_pVolSelBtn->setEnabled(true);
	m_pCurrSelBtn->setEnabled(true);

	//m_pUChannel->setDisabled(false);
	//m_pIChannel->setDisabled(false);

	m_pParaWidget->StopInit();
}

/*
void QHarmWidget::UpdateResult( float fActValue, float fActTime, float fReturnValue, float fReturnTime )
{
	if (fActTime>0.00001  && !m_pHarmTest->m_oHarmParas.m_bLock)//更新信息时候锁定的时候不更新界面上动作值；
	{
		m_lne_ActionTime->setText(QString::number(fActTime,'f',4));
	}
	if (fActValue>0.00001  && !m_pHarmTest->m_oHarmParas.m_bLock)//更新信息时候锁定的时候不更新界面上动作值；
	{
		m_lne_ActionValue->setText(QString::number(fActValue,'f',4));
	}
}
*/


void QHarmWidget::UpdateTestResource()
{
	m_pSttTestResource = stt_GetSttTestResource();

	if (m_pSttTestResource != NULL)
	{
		m_pParaSetSttTestResource = m_pSttTestResource;
	}

    SetDatas(m_pHarmTest,stt_GetSttTestResource());

// 	long nI = m_pIChannel->currentIndex();
// 	long nU = m_pUChannel->currentIndex();
// 
// 	if (nI >= 0)
// 	{
// 		CSttChResource *pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oCurChRsListRef.GetAt(nI));
// 		m_pParaTable->m_pIChannel->Disconnect();
// 		m_pParaTable->m_pIChannel->SetData(pChResource,m_pHarmTest->m_oHarmParas.m_uiCUR);
// 	}
// 
// 	if (nU >= 0)
// 	{
// 		CSttChResource *pChResource = (CSttChResource *)(m_pParaSetSttTestResource->m_oVolChRsListRef.GetAt(nU));
// 		m_pParaTable->m_pUChannel->Disconnect();
// 		m_pParaTable->m_pUChannel->SetData(pChResource,m_pHarmTest->m_oHarmParas.m_uiVOL);
// 	}
//
//'	m_pParaWidget->SetData(m_pParaSetSttTestResource,&m_pHarmTest->m_oHarmParas);
}

void QHarmWidget::slot_lne_BasicHarmHzClicked()
{
	QString strValue = m_lne_BasicHarmHz->text();
	 GetWidgetBoard_DigitData(3, strValue,m_lne_BasicHarmHz, this);
	//m_lne_BasicHarmHz->setText(strValue);

	/*
	WidgetKeyboardV_Digit dlg(3,this);
	dlg.m_strEditInfo = m_lne_BasicHarmHz->text();
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_lne_BasicHarmHz->setText(dlg.m_strEditInfo);
	}
	*/
	//slot_lne_BasicHarmHzChanged();
}


void QHarmWidget::AddExBinParaWidget()
{
	if (m_pExBinParaWidget)
	{
		return;
	}

	m_pExBinParaWidget = new ExSwitchSet(ExInput);
	int nInsertPos = 2;

	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_ExBinSet");
	m_pTabWidget->insertTab(nInsertPos,m_pExBinParaWidget,strTitle);
}

void QHarmWidget::RemoveExBinParaWidget()
{
	if(m_pExBinParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pTabWidget->indexOf(m_pExBinParaWidget);
	m_pTabWidget->removeTab(nIndex);

	delete m_pExBinParaWidget;
	m_pExBinParaWidget = NULL;
}

void QHarmWidget::AddExBoutParaWidget()
{
	if (m_pExBoutParaWidget)
	{
		return;
	}

	m_pExBoutParaWidget = new ExSwitchSet(ExOutPut);
	int nInsertPos = 2;

	if (ExistExBinParaWidget())
	{
		nInsertPos++;
	}

	//	m_tabWidget->insertTab(nInsertPos,m_pExBoutParaWidget,tr("开出设置(扩展)"));

	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_ExBoutSet");
	m_pTabWidget->insertTab(nInsertPos,m_pExBoutParaWidget,strTitle);
}

void QHarmWidget::RemoveExBoutParaWidget()
{
	if(m_pExBoutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pTabWidget->indexOf(m_pExBoutParaWidget);
	m_pTabWidget->removeTab(nIndex);

	delete m_pExBoutParaWidget;
	m_pExBoutParaWidget = NULL;
}

void QHarmWidget::AddGooseParaWidget(CIecCfgGoutDatas* pCfgGoutDatas)
{
	if (m_pGooseParaWidget)
	{
		return;
	}

	m_pGooseParaWidget = new QGooseParaWidget(pCfgGoutDatas,TRUE);
	int nInsertPos = 3;

	if (ExistExBinParaWidget())
	{
		nInsertPos++;
	}

	if (ExistExBoutParaWidget())
	{
		nInsertPos++;
	}

	//	m_tabWidget->insertTab(nInsertPos,m_pExBoutParaWidget,tr("开出设置(扩展)"));

	CString strTitle;
	xlang_GetLangStrByFile(strTitle,"Native_GooseDataSet");
	m_pTabWidget->insertTab(nInsertPos,m_pGooseParaWidget,strTitle);
}

void QHarmWidget::AddFT3OutParaWidget(CIecCfgDatasSMV* pIecCfgDatasSMV)
{
	if (m_pFT3OutParaWidget)
	{
		return;
	}

	m_pFT3OutParaWidget = new QFT3OutParaWidget(pIecCfgDatasSMV,TRUE);
	int nInsertPos = 4;

	if (ExistExBinParaWidget())
	{
		nInsertPos++;
	}

	if (ExistExBoutParaWidget())
	{
		nInsertPos++;
	}


	//CString strTitle = _T("FT3发布");
	CString strTitle = g_sLangTxt_Gradient_ReleasedFTT; //;lcq
	m_pTabWidget->insertTab(nInsertPos,m_pFT3OutParaWidget,strTitle);
}

void QHarmWidget::RemoveGooseParaWidget()
{
	if(m_pGooseParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pTabWidget->indexOf(m_pGooseParaWidget);
	m_pTabWidget->removeTab(nIndex);

	delete m_pGooseParaWidget;
	m_pGooseParaWidget = NULL;
}

void QHarmWidget::RemoveFT3OutParaWidget()
{
	if(m_pFT3OutParaWidget == NULL)
	{
		return;
	}

	int nIndex = m_pTabWidget->indexOf(m_pFT3OutParaWidget);
	m_pTabWidget->removeTab(nIndex);

	delete m_pFT3OutParaWidget;
	m_pFT3OutParaWidget = NULL;
}

bool QHarmWidget::ExistExBinParaWidget()
{
	int nIndex = m_pTabWidget->indexOf(m_pExBinParaWidget);
	return (nIndex>=0);
}

bool QHarmWidget::ExistExBoutParaWidget()
{
	int nIndex = m_pTabWidget->indexOf(m_pExBoutParaWidget);
	return (nIndex>=0);
}

bool QHarmWidget::ExistGooseParaWidget()
{
	int nIndex = m_pTabWidget->indexOf(m_pGooseParaWidget);
	return (nIndex>=0);
}

bool QHarmWidget::ExistFT3OutParaWidget()
{
	int nIndex = m_pTabWidget->indexOf(m_pFT3OutParaWidget);
	return (nIndex>=0);
}

void QHarmWidget::EnableBinParaWidget(bool b)
{
	if (ExistExBinParaWidget())
	{
		m_pTabWidget->setTabEnabled(m_pTabWidget->indexOf(m_pExBinParaWidget),b);
	}
}

void QHarmWidget::EnableBoutParaWidget(bool b)
{
	if (ExistExBoutParaWidget())
	{
		m_pTabWidget->setTabEnabled(m_pTabWidget->indexOf(m_pExBoutParaWidget),b);
	}
}

void QHarmWidget::EnableGooseParaWidget(bool b)
{
	if (ExistGooseParaWidget())
	{
		m_pTabWidget->setTabEnabled(m_pTabWidget->indexOf(m_pGooseParaWidget),b);
	}
}

void QHarmWidget::EnableFT3OutParaWidget(bool b)
{
	if (ExistFT3OutParaWidget())
	{
		m_pTabWidget->setTabEnabled(m_pTabWidget->indexOf(m_pFT3OutParaWidget),b);
	}
}

void QHarmWidget::slot_WaveValueUChanged()
{
	int nIndexVolt = m_pUChannel->currentIndex();
	emit sig_WaveValueChanged(nIndexVolt,1);
}

void QHarmWidget::slot_ChanelValueUChanged()
{
	int nIndexVolt = m_pUChannel->currentIndex();
	emit sig_WaveValueChanged(nIndexVolt,1);
}

void QHarmWidget::slot_WaveValueIChanged()
{
	int nIndexVolt = m_pIChannel->currentIndex();
	emit sig_WaveValueChanged(nIndexVolt,2);
}

void QHarmWidget::slot_ChanelValueIChanged()
{
	int nIndexVolt = m_pIChannel->currentIndex();
	emit sig_WaveValueChanged(nIndexVolt,2);
}

void QHarmWidget::slot_ChIndexChanged( int nChIndex)
{
	emit sig_ChIndexChanged(nChIndex);
}

void QHarmWidget::slot_ResetChangeFlag( int nValue )
{
// 	m_pParaTable->m_pUChannel->m_nChangeFlag = nValue;
// 	m_pParaTable->m_pIChannel->m_nChangeFlag = nValue;
}

void QHarmWidget::SetEnableTable( bool bEnable )
{
	m_pParaTable->m_pUChannel->setDisabled(!bEnable);
	m_pParaTable->m_pIChannel->setDisabled(!bEnable);
}

// void QHarmWidget::slot_CheckStateChanged()
// {
// 	emit sig_CheckStateChanged();
// }






















