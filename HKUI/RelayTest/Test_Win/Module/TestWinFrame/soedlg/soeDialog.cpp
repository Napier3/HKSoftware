#include "soeDialog.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>

#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../ReportView/XLangResource_PowerTestWin.h"

SoeDialog::SoeDialog()
{
	ui.setupUi(this);
	setWindowTitle(/*tr("SOE测试")*/ g_sLangTxt_Native_SOETest);

	m_pSoeParas = NULL;
	m_bInit = false;
	initUI();
        InitLanguage();

	connect(ui.comboBoxTime,SIGNAL(currentIndexChanged(int)),this,SLOT(changeHoldTime(int)));
	connect(ui.comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(changeTestType(int)));
	connect(ui.checkBox_1,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));
	connect(ui.checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));
	connect(ui.checkBox_3,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));
	connect(ui.checkBox_4,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));
	connect(ui.checkBox_5,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));
	connect(ui.checkBox_6,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));
	connect(ui.checkBox_7,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));
	connect(ui.checkBox_8,SIGNAL(stateChanged(int)),this,SLOT(savecheckSate(int)));

	m_pTimer = new QTimer;
	connect(m_pTimer,SIGNAL(timeout()),this,SLOT(stopTest()));
}

void SoeDialog::InitLanguage()
{
  // ui
  xlang_SetLangStrToWidget_Txt(ui.label_2, g_sLangTxt_Native_OutTotalTime,
                               XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label, g_sLangTxt_Native_TrigMode,
                               XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_3, g_sLangTxt_Harm_Enable,
                               XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_4, g_sLangTxt_Native_ShiftMoment,
                               XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_5, g_sLangTxt_Native_CloseTimes,
                               XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_6, g_sLangTxt_Native_BreakTime,
                               XLang_Ctrls_QLabel);
  xlang_SetLangStrToWidget_Txt(ui.label_7, g_sLangTxt_Native_ShiftCount,
                               XLang_Ctrls_QLabel);
}

bool SoeDialog::isGPSTrig()
{
	if (m_pSoeParas)
	{
		return (m_pSoeParas->m_nMode==STARTTYPE_GPS);
	}

	return false;
}

bool SoeDialog::isImmedTrig()
{
	if (m_pSoeParas)
	{
		return (m_pSoeParas->m_nMode==STARTTYPE_IMMED);
	}

	return false;
}

void SoeDialog::initUI()
{
        m_startAct = new QAction(QIcon("Images/start.png"), /*tr("开始测试")*/ g_sLangTxt_StartTest, this);
        m_startAct->setStatusTip(/*tr("开始测试")*/ g_sLangTxt_StartTest);
	connect(m_startAct, SIGNAL(triggered()), this, SLOT(startTest()));

        m_stopAct = new QAction(QIcon("Images/stop.png"), /*tr("停止测试")*/ g_sLangTxt_StopTest, this);
        m_stopAct->setStatusTip(/*tr("停止测试")*/ g_sLangTxt_StopTest);
	connect(m_stopAct, SIGNAL(triggered()), this, SLOT(stopTest()));

        m_saveAct = new QAction(QIcon("Images/save.png"), /*tr("保存配置")*/ g_sLangTxt_Native_SaveConfig, this);
        m_saveAct->setStatusTip( /*tr("保存目前配置参数")*/ g_sLangTxt_Native_SaveCurrConfig);
	connect(m_saveAct, SIGNAL(triggered()), this, SLOT(saveConfig()));
	
	m_headerToolBar = new QToolBar(ui.widget);
	m_headerToolBar->addAction(m_startAct);
	m_headerToolBar->addAction(m_stopAct);
	m_headerToolBar->addAction(m_saveAct);
	m_headerToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	
	m_startAct->setEnabled( true );
	m_stopAct->setEnabled( false );

//	validator = new QDoubleValidator(0, 100000 ,1, this);	
	validator = new QIntValidator(0, 100000, this);	
	validatorCount = new QIntValidator(0, 100000, this);
	
	QStringList strName;
        strName.append(/*tr("开始时触发")*/ g_sLangTxt_Native_StartTrigger);
        strName.append(/*tr("GPS触发")*/ g_sLangTxt_GPS);
	ui.comboBox->insertItems(0,strName);

	strName.clear();
	strName.append(tr("10秒"));
	strName.append(tr("20秒"));
	strName.append(tr("50秒"));
	strName.append(tr("100秒"));
	strName.append(tr("500秒"));
	strName.append(tr("1000秒"));
	ui.comboBoxTime->insertItems(0,strName);
	
	ui.lineEditChange_1->setValidator(validator);
	ui.lineEditChange_2->setValidator(validator);
	ui.lineEditChange_3->setValidator(validator);
	ui.lineEditChange_4->setValidator(validator);
	ui.lineEditChange_5->setValidator(validator);
	ui.lineEditChange_6->setValidator(validator);
	ui.lineEditChange_7->setValidator(validator);
	ui.lineEditChange_8->setValidator(validator);

	ui.lineEditClose_1->setValidator(validator);
	ui.lineEditClose_2->setValidator(validator);
	ui.lineEditClose_3->setValidator(validator);
	ui.lineEditClose_4->setValidator(validator);
	ui.lineEditClose_5->setValidator(validator);
	ui.lineEditClose_6->setValidator(validator);
	ui.lineEditClose_7->setValidator(validator);
	ui.lineEditClose_8->setValidator(validator);

	ui.lineEdit_1->setValidator(validator);
	ui.lineEdit_2->setValidator(validator);
	ui.lineEdit_3->setValidator(validator);
	ui.lineEdit_4->setValidator(validator);
	ui.lineEdit_5->setValidator(validator);
	ui.lineEdit_6->setValidator(validator);
	ui.lineEdit_7->setValidator(validator);
	ui.lineEdit_8->setValidator(validator);

	ui.lineEditCount_1->setValidator(validatorCount);
	ui.lineEditCount_2->setValidator(validatorCount);
	ui.lineEditCount_3->setValidator(validatorCount);
	ui.lineEditCount_4->setValidator(validatorCount);
	ui.lineEditCount_5->setValidator(validatorCount);
	ui.lineEditCount_6->setValidator(validatorCount);
	ui.lineEditCount_7->setValidator(validatorCount);
	ui.lineEditCount_8->setValidator(validatorCount);

	ui.lineEditChange_1->installEventFilter(this);
	ui.lineEditChange_2->installEventFilter(this);
	ui.lineEditChange_3->installEventFilter(this);
	ui.lineEditChange_4->installEventFilter(this);
	ui.lineEditChange_5->installEventFilter(this);
	ui.lineEditChange_6->installEventFilter(this);
	ui.lineEditChange_7->installEventFilter(this);
	ui.lineEditChange_8->installEventFilter(this);

	ui.lineEditClose_1->installEventFilter(this);
	ui.lineEditClose_2->installEventFilter(this);
	ui.lineEditClose_3->installEventFilter(this);
	ui.lineEditClose_4->installEventFilter(this);
	ui.lineEditClose_5->installEventFilter(this);
	ui.lineEditClose_6->installEventFilter(this);
	ui.lineEditClose_7->installEventFilter(this);
	ui.lineEditClose_8->installEventFilter(this);

	ui.lineEdit_1->installEventFilter(this);
	ui.lineEdit_2->installEventFilter(this);
	ui.lineEdit_3->installEventFilter(this);
	ui.lineEdit_4->installEventFilter(this);
	ui.lineEdit_5->installEventFilter(this);
	ui.lineEdit_6->installEventFilter(this);
	ui.lineEdit_7->installEventFilter(this);
	ui.lineEdit_8->installEventFilter(this);

	ui.lineEditCount_1->installEventFilter(this);
	ui.lineEditCount_2->installEventFilter(this);
	ui.lineEditCount_3->installEventFilter(this);
	ui.lineEditCount_4->installEventFilter(this);
	ui.lineEditCount_5->installEventFilter(this);
	ui.lineEditCount_6->installEventFilter(this);
	ui.lineEditCount_7->installEventFilter(this);
	ui.lineEditCount_8->installEventFilter(this);
	ui.timeEdit->installEventFilter(this);

	setWindowFlags(Qt::WindowCloseButtonHint);
}

int SoeDialog::getCurrentIndex(unsigned int nHoldTime)
{
	int idx = 0;

	switch(nHoldTime)
	{
	case 10:
		idx = 0;break;
	case 20:
		idx = 1;break;
	case 50:
		idx = 2;break;
	case 100:
		idx = 3;break;
	case 500:
		idx = 4;break;
	case 1000:
		idx = 5;break;
	default:
		break;
	}

	return idx;
}

int SoeDialog::getCurrentHoldTime(int nTimeIdx)
{
	int nHoldTime = 10;
	switch (nTimeIdx)
	{
	case 1:
		nHoldTime = 20;
		break;
	case 2:
		nHoldTime = 50;
		break;
	case 3:
		nHoldTime = 100;
		break;
	case 4:
		nHoldTime = 500;
		break;
	case 5:
		nHoldTime = 1000;
		break;
	case 0:
	default:
		nHoldTime = 10;
		break;
	}

	return nHoldTime;
}

void SoeDialog::setData(tmt_SoeParas* pSoeParas)
{
	ASSERT(pSoeParas != NULL);
	m_pSoeParas = pSoeParas;

	QTime tm;
	int n;

	//初始化持续时间
	ui.comboBoxTime->setCurrentIndex(getCurrentIndex(m_pSoeParas->m_fHoldTime));
	ui.comboBox->setCurrentIndex(m_pSoeParas->m_nMode);
	changeTestType(m_pSoeParas->m_nMode);

	tm.setHMS(m_pSoeParas->m_tGps.nHour, m_pSoeParas->m_tGps.nMinutes, m_pSoeParas->m_tGps.nSeconds);
	ui.timeEdit->setTime(tm);

	QObjectList list = children();
	foreach (QObject *obj, list)
	{
		if (obj->inherits("QLineEdit"))
		{
			QLineEdit *b = qobject_cast<QLineEdit*>(obj);
			QString strName = b->objectName();
			n = strName.right(1).toUInt();

			if (strName.contains("Change"))
			{
//				b->setText( QString("%1").arg(m_pSoeParas->m_binOut[n-1].otmt_SoeState[0].time, 0, 'f', 1));
				b->setText( (QString("%1").arg(m_pSoeParas->m_binOut[n-1].otmt_SoeState[0].time, 0, 'f', 1)));
			}
			else if (strName.contains("Close"))
			{
//				b->setText( QString("%1").arg(m_pSoeParas->m_binOut[n-1].otmt_SoeState[1].time, 0, 'f', 1));
				b->setText( QString("%1").arg(m_pSoeParas->m_binOut[n-1].otmt_SoeState[1].time, 0, 'f', 1));
			}
			else if (strName.contains("Count"))
			{
				b->setText( QString(m_pSoeParas->m_binOut[n-1].cnt,10));
			}
			else
			{
//				b->setText( QString("%1").arg(m_pSoeParas->m_binOut[n-1].otmt_SoeState[2].time, 0, 'f', 1));
				b->setText( QString("%1").arg(m_pSoeParas->m_binOut[n-1].otmt_SoeState[2].time, 0,'f', 1));
			}
		}
		if (obj->inherits("QCheckBox"))
		{
			QCheckBox *b = qobject_cast<QCheckBox*>(obj);
			QString strName = b->objectName();
			n = strName.right(1).toUInt();

			b->setChecked(m_pSoeParas->m_binOut[n-1].isValid);
		}
	}

	m_bInit = true;
}

bool SoeDialog::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type()==QEvent::FocusOut)
	{
		if (watched==ui.lineEditChange_1 ||
			watched==ui.lineEditChange_2 ||
			watched==ui.lineEditChange_3 ||
			watched==ui.lineEditChange_4 ||
			watched==ui.lineEditChange_5 ||
			watched==ui.lineEditChange_6 ||
			watched==ui.lineEditChange_7 ||
			watched==ui.lineEditChange_8)
		{
			QLineEdit* pEdit = static_cast<QLineEdit*>(watched);
//			const QDoubleValidator* pValidator = static_cast<const QDoubleValidator*>(pEdit->validator());
//			double val = pEdit->text().toDouble( 0);
			const QIntValidator* pValidator = static_cast<const QIntValidator*>(pEdit->validator());
			int val =  pEdit->text().toUInt(0);
			if ( val > pValidator->top() )
			{
				val = pValidator->top();
			}
			else if ( val < pValidator->bottom() )
			{
				val = pValidator->bottom();
			}
//			pEdit->setText( QString("%1").arg(val, 0, 'f', 1) );
			pEdit->setText( QString::number(val, 10));

			QString strName = pEdit->objectName();
			int n = strName.right(1).toUInt();

			m_pSoeParas->m_binOut[n-1].otmt_SoeState[0].time = val;//故障前时间（变位时间）
		}
		else if (watched==ui.lineEditClose_1 ||
			watched==ui.lineEditClose_2 ||
			watched==ui.lineEditClose_3 ||
			watched==ui.lineEditClose_4 ||
			watched==ui.lineEditClose_5 ||
			watched==ui.lineEditClose_6 ||
			watched==ui.lineEditClose_7 ||
			watched==ui.lineEditClose_8)
		{
			QLineEdit* pEdit = static_cast<QLineEdit*>(watched);
//			const QDoubleValidator* pValidator = static_cast<const QDoubleValidator*>(pEdit->validator());
//			double val = pEdit->text().toDouble( 0);
			const QIntValidator* pValidator = static_cast<const QIntValidator*>(pEdit->validator());
			unsigned int val =  pEdit->text().toUInt(0);

			if ( val > pValidator->top() )
			{
				val = pValidator->top();
			}
			else if ( val < pValidator->bottom() )
			{
				val = pValidator->bottom();
			}
//			pEdit->setText( QString("%1").arg(val, 0, 'f', 1) );
			pEdit->setText( QString::number(val, 10));

			QString strName = pEdit->objectName();
			int n = strName.right(1).toUInt();

			m_pSoeParas->m_binOut[n-1].otmt_SoeState[1].time = val;	//闭合时间
		}
		else if (watched==ui.lineEdit_1 ||
			watched==ui.lineEdit_2 ||
			watched==ui.lineEdit_3 ||
			watched==ui.lineEdit_4 ||
			watched==ui.lineEdit_5 ||
			watched==ui.lineEdit_6 ||
			watched==ui.lineEdit_7 ||
			watched==ui.lineEdit_8)
		{
			QLineEdit* pEdit = static_cast<QLineEdit*>(watched);
//			const QDoubleValidator* pValidator = static_cast<const QDoubleValidator*>(pEdit->validator());
//			double val = pEdit->text().toDouble( 0);
			const QIntValidator* pValidator = static_cast<const QIntValidator*>(pEdit->validator());
			unsigned int val =  pEdit->text().toUInt(0);
			if ( val > pValidator->top() )
			{
				val = pValidator->top();
			}
			else if ( val < pValidator->bottom() )
			{
				val = pValidator->bottom();
			}
//			pEdit->setText( QString("%1").arg(val, 0, 'f', 1) );
			pEdit->setText( QString::number(val, 10));

			QString strName = pEdit->objectName();
			int n = strName.right(1).toUInt();

			m_pSoeParas->m_binOut[n-1].otmt_SoeState[2].time = val;	//断开时间
		}
		else if (watched==ui.lineEditCount_1 ||
			watched==ui.lineEditCount_2 ||
			watched==ui.lineEditCount_3 ||
			watched==ui.lineEditCount_4 ||
			watched==ui.lineEditCount_5 ||
			watched==ui.lineEditCount_6 ||
			watched==ui.lineEditCount_7 ||
			watched==ui.lineEditCount_8)
		{
			QLineEdit* pEdit = static_cast<QLineEdit*>(watched);
//			const QIntValidator* pValidator = static_cast<const QIntValidator*>(pEdit->validator());
//			double val = pEdit->text().toDouble( 0);
			const QIntValidator* pValidator = static_cast<const QIntValidator*>(pEdit->validator());
			unsigned int val =  pEdit->text().toUInt(0);
			if ( val > pValidator->top() )
			{
				val = pValidator->top();
			}
			else if ( val < pValidator->bottom() )
			{
				val = pValidator->bottom();
			}
			pEdit->setText( QString::number(val, 10));

			QString strName = pEdit->objectName();
			int n = strName.right(1).toUInt();

			m_pSoeParas->m_binOut[n-1].cnt = val;
		}
		else if (watched == ui.timeEdit)
		{	
			QDateTime time = QDateTime::currentDateTime();
			time.setTime(ui.timeEdit->time());		
			QDate dt = time.date();
			QTime tm = time.time();
			m_pSoeParas->m_tGps.nYear = dt.year();
			m_pSoeParas->m_tGps.nMonth = dt.month();
			m_pSoeParas->m_tGps.nDay = dt.day();
			m_pSoeParas->m_tGps.nHour = tm.hour();
			m_pSoeParas->m_tGps.nMinutes = tm.minute();
			m_pSoeParas->m_tGps.nSeconds = tm.second();
			m_pSoeParas->m_tGps.nMilliSeconds = 0;
		}
	}
	return QWidget::eventFilter(watched,event);
}

void SoeDialog::savecheckSate(int nState)
{
	if(m_pSoeParas == NULL || m_bInit == false)
	{
		return;
	}

	m_pSoeParas->m_binOut[0].isValid = ui.checkBox_1->isChecked();
	m_pSoeParas->m_binOut[1].isValid = ui.checkBox_2->isChecked();
	m_pSoeParas->m_binOut[2].isValid = ui.checkBox_3->isChecked();
	m_pSoeParas->m_binOut[3].isValid = ui.checkBox_4->isChecked();
	m_pSoeParas->m_binOut[4].isValid = ui.checkBox_5->isChecked();
	m_pSoeParas->m_binOut[5].isValid = ui.checkBox_6->isChecked();
	m_pSoeParas->m_binOut[6].isValid = ui.checkBox_7->isChecked();
	m_pSoeParas->m_binOut[7].isValid = ui.checkBox_8->isChecked();
}

void SoeDialog::saveConfig()
{
	emit sig_SoeParasSave();
}

void SoeDialog::changeTestType(int nType)
{
	if (nType == 0)
	{
		m_pSoeParas->m_nMode = STARTTYPE_IMMED;
		ui.timeEdit->setDisabled(true);
	}
	else if (nType == 1)
	{
		m_pSoeParas->m_nMode = STARTTYPE_GPS;
		ui.timeEdit->setDisabled(false);
	}
}

void SoeDialog::changeHoldTime(int nTimeIdx)
{
	if (m_pSoeParas)
	{
		m_pSoeParas->m_fHoldTime = getCurrentHoldTime(nTimeIdx);
	}
}

void SoeDialog::stopTest()
{
	emit sig_SoeStopClicked();
}	

void SoeDialog::startTest()
{
	emit sig_SoeStartClicked();
}

void SoeDialog::OnViewStartState(bool bStart)
{
	if (bStart)
	{
		m_startAct->setEnabled( false );
		m_stopAct->setEnabled( true );	
		int nCurrentIndex = ui.comboBoxTime->currentIndex();
		switch(nCurrentIndex)
		{
		case 0:
			m_pTimer->start(10000);
			break;
		case 1:
			m_pTimer->start(20000);
			break;
		case 2:
			m_pTimer->start(50000);
			break;
		case 3:
			m_pTimer->start(100000);
			break;
		case 4:
			m_pTimer->start(500000);
			break;
		case 5:
			m_pTimer->start(1000000);
			break;
		default:
			m_pTimer->start(10000);
			break;
		}
	}
	else
	{
		m_startAct->setEnabled( true );
		m_stopAct->setEnabled( false );
		QString note = /*tr("开始实验失败")*/ g_sLangTxt_Native_StartExpFail;;
		QMessageBox::information(this, tr("error"), note );
	}
}

void SoeDialog::OnViewStopState(bool bStop)
{
	if (bStop)
	{
		m_startAct->setEnabled( true );
		m_stopAct->setEnabled( false );	
		m_pTimer->stop();
	}
	else
	{
		m_startAct->setEnabled( false );
		m_stopAct->setEnabled( true );			
		QString note =  /*tr("实验停止失败")*/ g_sLangTxt_Native_StopExpFail;
		QMessageBox::information(this, tr("error"), note );
	}
}

SoeDialog::~SoeDialog()
{
	
}