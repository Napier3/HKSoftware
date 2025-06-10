#include "SttReplayWaveformEditWidget.h"
#include "SttMacroParaEditViewTransPlay.h"
#include "../../Module/OSInterface/QT/XMessageBox.h"
#include "../../ReplayTest/BigComtradeTransPlay.h"


SttReplayWaveformEditWidget::SttReplayWaveformEditWidget(QWidget *pParent)
:QWidget(pParent)
{
	ui.setupUi(this);
	initUI();	
	InitWidget();
	initSignalSlots();

	m_nWaveEditType = 0;
}

SttReplayWaveformEditWidget::~SttReplayWaveformEditWidget(void)
{
	
}

void SttReplayWaveformEditWidget::initUI()
{

	setFont(*g_pSttGlobalFont);

	ui.m_edt_InsertBegin->InitCoverage(0,999,3);
	ui.m_edt_InsertEnd->InitCoverage(0,999,3);
	ui.m_edt_InsertCycNum->InitCoverage(0,999,1);
	ui.m_edt_DeleteBegin->InitCoverage(0,999,3);
	ui.m_edt_DeleteEnd->InitCoverage(0,999,3);
	ui.m_edt_InsertNormalCur->InitCoverage(0,999,3);
	ui.m_edt_InsertNormalVal->InitCoverage(0,999,3);
	ui.m_edt_InsertNormaloutTime->InitCoverage(0,999,3);

	CString strText = _T("ʱ��");
	ui.m_Cbox_InsertType->addItem(strText);
	strText = _T("���");
	ui.m_Cbox_InsertType->addItem(strText);

	ui.m_Cbox_InsertType->setFont(*g_pSttGlobalFont);
	ui.m_rb_InsertWave->setFont(*g_pSttGlobalFont);
	ui.m_rb_WaveEdit->setFont(*g_pSttGlobalFont);
	ui.m_pb_Replay->setFont(*g_pSttGlobalFont);
	ui.m_edt_InsertBegin->setFont(*g_pSttGlobalFont);
	ui.m_edt_InsertEnd->setFont(*g_pSttGlobalFont);
	ui.m_edt_InsertCycNum->setFont(*g_pSttGlobalFont);
	ui.m_edt_InsertNormalVal->setFont(*g_pSttGlobalFont);
	ui.m_edt_InsertNormalCur->setFont(*g_pSttGlobalFont);
	ui.m_edt_InsertNormaloutTime->setFont(*g_pSttGlobalFont);

	ui.m_edt_DeleteBegin->setFont(*g_pSttGlobalFont);
	ui.m_edt_DeleteEnd->setFont(*g_pSttGlobalFont);
	ui.m_pb_delete->setFont(*g_pSttGlobalFont);
	ui.m_pb_Insert->setFont(*g_pSttGlobalFont);
}


void SttReplayWaveformEditWidget::InitWaveEditWidget()
{
	if(g_theBigComtradeTransPlay == NULL)
	{
		return;
	}

	if(m_nWaveEditType == 0)
	{
		ui.m_rb_WaveEdit->click();

	}
	else if(m_nWaveEditType == 1)
	{
		ui.m_rb_InsertWave->click();
	}

	//ui.m_edt_InsertBegin->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin,'f',3));
	//ui.m_edt_InsertEnd->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd,'f',3));
	//ui.m_edt_InsertCycNum->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nCycleIndex,'f',0));

	ui.m_edt_DeleteBegin->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin,'f',3));
	ui.m_edt_DeleteEnd->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dEnd,'f',3));
	
	ui.m_edt_InsertNormalCur->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fCurrent,'f',3));
	ui.m_edt_InsertNormalVal->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fVoltage,'f',3));
	ui.m_edt_InsertNormaloutTime->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_dOutputTime,'f',2));

	ui.m_Cbox_InsertType->setCurrentIndex(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_nInsertWaveType);

	UpdateInsertTypeWidgetChange(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_nInsertWaveType);
		
	ui.m_edt_InsertCycNum->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nCycleIndex,'f',0));

}

void SttReplayWaveformEditWidget::InitWidget()
{
// 	ui.m_rb_WaveEdit->click();
// 	ui.m_rb_InsertWave->setVisible(false);
// 	SetDeleteWaveLayoutControlEnable(TRUE);
}

void SttReplayWaveformEditWidget::SetEnableState( bool bEnable )
{
	SetDeleteWaveLayoutControlEnable(bEnable);
	if(ui.m_rb_WaveEdit->isChecked())
	{
		SetInsertWaveLayoutControlEnable(bEnable);
	}
	if(ui.m_rb_InsertWave->isChecked())
	{
		SetInsertNormalLayoutControlEnable(bEnable);
	}
}


void SttReplayWaveformEditWidget::initSignalSlots()
{
	connect(ui.m_rb_InsertWave, SIGNAL(clicked()), this, SLOT(slot_InsertNormalRbuttonClicked()));
	connect(ui.m_rb_WaveEdit, SIGNAL(clicked()), this, SLOT(slot_InsertRbuttonClicked()));

	//������
	connect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_ZeroChanged()));
	connect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_DestinationChanged()));
	//����ʱ��
	connect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_BeginTimeChanged()));
	connect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_EndTimeChanged()));

	connect(ui.m_edt_InsertNormalCur, SIGNAL(editingFinished()), this, SLOT(slot_InsertNormal_CurChanged()));
	connect(ui.m_edt_InsertNormalVal, SIGNAL(editingFinished()), this, SLOT(slot_InsertNormal_ValChanged()));
	connect(ui.m_edt_InsertNormaloutTime, SIGNAL(editingFinished()), this, SLOT(slot_InsertNormal_OutTimeChanged()));
	connect(ui.m_edt_InsertCycNum, SIGNAL(editingFinished()), this, SLOT(slot_Insert_CycleIndexChanged()));
	connect(ui.m_edt_DeleteBegin, SIGNAL(editingFinished()), this, SLOT(slot_Delete_ZeroChanged()));
	connect(ui.m_edt_DeleteEnd, SIGNAL(editingFinished()), this, SLOT(slot_Delete_DestinationChanged()));
	connect(ui.m_pb_delete, SIGNAL(clicked()), this, SLOT(slot_Delete_OK()));
	connect(ui.m_pb_Insert, SIGNAL(clicked()), this, SLOT(slot_Insert_OK()));
	connect(ui.m_pb_Replay, SIGNAL(clicked()), this, SLOT(slot_Wave_ReCovery()));
	connect(ui.m_Cbox_InsertType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_Insert_TypeChanged(int)));
}



void SttReplayWaveformEditWidget::uninitSignalSlots()
{
	disconnect(ui.m_rb_InsertWave, SIGNAL(clicked()), this, SLOT(slot_InsertNormalRbuttonClicked()));
	disconnect(ui.m_rb_WaveEdit, SIGNAL(clicked()), this, SLOT(slot_InsertRbuttonClicked()));
	//������
	disconnect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_ZeroChanged()));
	disconnect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_DestinationChanged()));
	//����ʱ��
	disconnect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_BeginTimeChanged()));
	disconnect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_EndTimeChanged()));
	disconnect(ui.m_edt_InsertCycNum, SIGNAL(editingFinished()), this, SLOT(slot_Insert_CycleIndexChanged()));
	disconnect(ui.m_edt_InsertNormalCur, SIGNAL(editingFinished()), this, SLOT(slot_InsertNormal_CurChanged()));
	disconnect(ui.m_edt_InsertNormalVal, SIGNAL(editingFinished()), this, SLOT(slot_InsertNormal_ValChanged()));
	disconnect(ui.m_edt_InsertNormaloutTime, SIGNAL(editingFinished()), this, SLOT(slot_InsertNormal_OutTimeChanged()));
	disconnect(ui.m_edt_InsertCycNum, SIGNAL(editingFinished()), this, SLOT(slot_Insert_CycleIndexChanged()));
	disconnect(ui.m_edt_DeleteBegin, SIGNAL(editingFinished()), this, SLOT(slot_Delete_ZeroChanged()));
	disconnect(ui.m_edt_DeleteEnd, SIGNAL(editingFinished()), this, SLOT(slot_Delete_DestinationChanged()));
	disconnect(ui.m_pb_delete, SIGNAL(clicked()), this, SLOT(slot_Delete_OK()));
	disconnect(ui.m_pb_Insert, SIGNAL(clicked()), this, SLOT(slot_Insert_OK()));
	disconnect(ui.m_pb_Replay, SIGNAL(clicked()), this, SLOT(slot_Wave_ReCovery()));
	disconnect(ui.m_Cbox_InsertType, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_Insert_TypeChanged(int)));

}


BOOL SttReplayWaveformEditWidget::CheckMaxDataTime(double dTime) 
{
	if (dTime > g_pReplayTestMain->m_pWaveGraphWidget->m_dRecordDataTimeLength) 
	{
		return FALSE;
	}
	return TRUE;
}


void SttReplayWaveformEditWidget::slot_InsertRbuttonClicked()
{
	SetInsertWaveLayoutControlEnable(TRUE);
	SetInsertNormalLayoutControlEnable(FALSE);

	m_nWaveEditType = 0;
}

void SttReplayWaveformEditWidget::slot_InsertNormalRbuttonClicked()
{
	SetInsertWaveLayoutControlEnable(FALSE);
	SetInsertNormalLayoutControlEnable(TRUE);

	m_nWaveEditType = 1;
}

void SttReplayWaveformEditWidget::SetInsertWaveLayoutControlEnable( BOOL bState )
{
	ui.m_lb_InsertBegin->setEnabled(bState);
	ui.label_2->setEnabled(bState);
	ui.label_3->setEnabled(bState);
	ui.m_edt_InsertBegin->setEnabled(bState);
	ui.m_edt_InsertEnd->setEnabled(bState);
	ui.m_edt_InsertCycNum->setEnabled(bState);
	ui.m_Insert_GroupBox->setEnabled(bState);
	return;
}

void SttReplayWaveformEditWidget::SetInsertNormalLayoutControlEnable( BOOL bState )
{
	ui.label_8->setEnabled(bState);
	ui.label_5->setEnabled(bState);
	ui.label_7->setEnabled(bState);
	ui.m_edt_InsertNormalVal->setEnabled(bState);
	ui.m_edt_InsertNormalCur->setEnabled(bState);
	ui.m_edt_InsertNormaloutTime->setEnabled(bState);
	ui.m_InsertNomal_GroupBox->setEnabled(bState);
	return;
}

void SttReplayWaveformEditWidget::SetDeleteWaveLayoutControlEnable( BOOL bState )
{
	ui.label_6->setEnabled(bState);
	ui.label_4->setEnabled(bState);
	ui.m_edt_DeleteBegin->setEnabled(bState);
	ui.m_edt_DeleteEnd->setEnabled(bState);
	ui.m_DeleteWave_GroupBox->setEnabled(bState);
	return;
}

void SttReplayWaveformEditWidget::slot_Insert_ZeroChanged()
{
// 	CString strValue =  strText;
// 	long nNewValue = CString_To_long(strValue);

	long nNewValue = ui.m_edt_InsertBegin->GetValue_Long();

	int nCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nBeginPoint;
	int nEnd = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nEndPoint;

	if(nNewValue <= 0)
	{
		nNewValue = nCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("������С���Ϊ1�����������룡"));
	}
	else if(nNewValue > g_theBigComtradeTransPlay->m_oBigComtradeFileRead.GetTotalPointsNum())
	{
		nNewValue = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.GetTotalPointsNum();
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("�������ʼ���/�յ��Ų��ܳ��������ܵ���[%d]�����������룡"),g_theBigComtradeTransPlay->m_oBigComtradeFileRead.GetTotalPointsNum());
	}
	else if(nNewValue > nEnd)
	{
		ui.m_edt_InsertEnd->setText(QString::number(nNewValue));
	}
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nBeginPoint = nNewValue;
	ui.m_edt_InsertBegin->setText(QString::number(nNewValue));

}

void SttReplayWaveformEditWidget::slot_Insert_DestinationChanged()
{
// 	CString strValue =  strText;
// 	long nNewValue = CString_To_long(strValue);

	long nNewValue = ui.m_edt_InsertEnd->GetValue_Long();

	int nCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nEndPoint;
	int nBegin = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nBeginPoint;

	if(nNewValue <= 0)
	{
		nNewValue = nCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("������С���Ϊ1�����������룡"));
	}
	else if(nNewValue > g_theBigComtradeTransPlay->m_oBigComtradeFileRead.GetTotalPointsNum())
	{
		nNewValue = g_theBigComtradeTransPlay->m_oBigComtradeFileRead.GetTotalPointsNum();
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("�������ʼ���/��ֹ��Ų��ܳ��������ܵ���[%d]�����������룡"),g_theBigComtradeTransPlay->m_oBigComtradeFileRead.GetTotalPointsNum());
	}
	else if(nBegin > nNewValue)
	{
		nNewValue = nBegin;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("�������ֹ��Ų���С���������ʼ���[%d]�����������룡"),nBegin);
	}
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nEndPoint = nNewValue;
	ui.m_edt_InsertEnd->setText(QString::number(nNewValue));
}

void SttReplayWaveformEditWidget::slot_Insert_CycleIndexChanged()
{
	double dNewValue = ui.m_edt_InsertCycNum->GetValue();
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nCycleIndex;

	if(dNewValue < 1)
	{
		dNewValue = dCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("ѭ��������������1�Σ����������룡"));
	}
 	else
 	{
 		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nCycleIndex = dNewValue;
 	}
	ui.m_edt_InsertCycNum->setText(QString::number(dNewValue,'f',0));
}

void SttReplayWaveformEditWidget::slot_Insert_OK()
{
	double dBegin = ui.m_edt_InsertBegin->GetValue();
	double dEnd = ui.m_edt_InsertEnd->GetValue();

	long nBegin = ui.m_edt_InsertBegin->GetValue();
	long nEnd = ui.m_edt_InsertEnd->GetValue();

	if(ui.m_rb_WaveEdit->isChecked())
	{	
		if(ui.m_Cbox_InsertType->currentIndex() == INSERT_WAVE_TYPE_TIME)//ʱ������
		{
		if(dEnd <= dBegin)
		{
			CXMessageBox::information(this,_T("��ʾ"),_T("������㲻��С�ڻ������ֹ��ţ�����������!"),QMessageBox::Yes);
			return;
		}		
		g_pReplayTestMain->m_pWaveGraphWidget->m_bInsertWaveformBackColor = FALSE;
	}
	else//���
	{
			if(nEnd <= nBegin)
			{
				CXMessageBox::information(this,_T("��ʾ"),_T("������ʼ��Ų���С�ڻ������ֹ��ţ�����������!"),QMessageBox::Yes);
				return;
			}
		}	
	}
	
	//�������������
	g_pReplayTestMain->StartInsertWaveThread();

	CTickCount32 oTick;
	while(TRUE)
	{
		if(g_pReplayTestMain->m_pSttInsertWaveThread == NULL)
		{
			break;
		}
		oTick.DoEvents(5);
	}

	g_theBigComtradeTransPlay->m_oComtradePlayConfig.CalcReplayChMaxValue();


	//�����������¼��������Сֵ
	g_pReplayTestMain->m_ParaSetWidget->UpdateUIMax();
	g_pReplayTestMain->CreateWaveGraphByComtrade();
	g_pReplayTestMain->m_ParaSetWidget->initTabPage();

}

void SttReplayWaveformEditWidget::slot_Delete_OK()
{
	double dBegin = ui.m_edt_DeleteBegin->GetValue();
	double dEnd = ui.m_edt_DeleteEnd->GetValue();

	if(dEnd <= dBegin)
	{
		CXMessageBox::information(this,_T("��ʾ"),_T("ɾ����㲻��С�ڻ�����յ㣬����������!"),QMessageBox::Yes);
		return;
	}	
	g_pReplayTestMain->m_pWaveGraphWidget->m_bDeleteWaveformBackColor = FALSE;
	g_theBigComtradeTransPlay->m_oBigComtradeFileRead.DeletePointsByRelTime(dBegin, dEnd);
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.CalcReplayChMaxValue();


	g_pReplayTestMain->m_ParaSetWidget->UpdateUIMax();
	g_pReplayTestMain->CreateWaveGraphByComtrade();
	g_pReplayTestMain->m_ParaSetWidget->initTabPage();

}

void SttReplayWaveformEditWidget::slot_Delete_ZeroChanged()
{
	double dNewValue = ui.m_edt_DeleteBegin->GetValue();
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin;
	double dEnd = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dEnd;
	double dRecordDataTimeLength = g_pReplayTestMain->m_pWaveGraphWidget->m_dRecordDataTimeLength;

	// ȷ�������ʱ�����ԭ����ʱ�䷶Χ��
	if(!CheckMaxDataTime(dNewValue))
	{
		if(dCurValue > dRecordDataTimeLength)
		{
			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin = dRecordDataTimeLength;
			dCurValue = dRecordDataTimeLength;
		}	
		dNewValue = dCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("��������/�յ㲻�ܳ����ܲ��γ���[%.3fs]�����������룡"),dRecordDataTimeLength);
	}
	else if(dNewValue > dEnd)
	{
		ui.m_edt_DeleteEnd->setText(QString::number(dNewValue,'f',3));
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin = dNewValue;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin = dNewValue;
		g_pReplayTestMain->m_pWaveGraphWidget->m_bDeleteWaveformBackColor = TRUE;
	}
	ui.m_edt_DeleteBegin->setText(QString::number(dNewValue,'f',3));



}

void SttReplayWaveformEditWidget::slot_Delete_DestinationChanged()
{
	double dNewValue = ui.m_edt_DeleteEnd->GetValue();
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dEnd;
	double dBegin = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dBegin;
	double dRecordDataTimeLength = g_pReplayTestMain->m_pWaveGraphWidget->m_dRecordDataTimeLength;

	// ȷ�������ʱ�����ԭ����ʱ�䷶Χ��
	if(!CheckMaxDataTime(dNewValue))
	{
		if(dCurValue > dRecordDataTimeLength)
		{
			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dEnd = dRecordDataTimeLength;
			dCurValue = dRecordDataTimeLength;
		}	
		dNewValue = dCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("��������/�յ㲻�ܳ����ܲ��γ���[%.3fs]�����������룡"),dRecordDataTimeLength);
	}
	else if(dBegin > dNewValue)
	{
		dNewValue = dBegin;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("������յ㲻��С����������[%.3fs]�����������룡"),dBegin);
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oDeleteWaveData.m_dEnd = dNewValue;
	}
	ui.m_edt_DeleteEnd->setText(QString::number(dNewValue,'f',3));

	g_pReplayTestMain->m_pWaveGraphWidget->m_bDeleteWaveformBackColor = TRUE;


}

void SttReplayWaveformEditWidget::slot_InsertNormal_ValChanged()
{
	double dNewValue = ui.m_edt_InsertNormalVal->GetValue();
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fVoltage;

	double Ratio = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[1]/g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fPTRatio[0];
// 	dNewValue *= Ratio;
	double dChangeValue = dNewValue * Ratio;

	// ȷ�������ʱ�����ԭ����ʱ�䷶Χ��
	if ((dNewValue* Ratio)>g_oLocalSysPara.m_fAC_VolMax)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ�����ʵ�ʳ�̬���ε�ѹֵ(%f),���ڲ�������������ѹ(%f)."),dChangeValue,g_oLocalSysPara.m_fAC_VolMax);
		dNewValue = dCurValue;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fVoltage = dNewValue;
	}
	ui.m_edt_InsertNormalVal->setText(QString::number(dNewValue,'f',3));

}

void SttReplayWaveformEditWidget::slot_InsertNormal_CurChanged()
{
	double dNewValue = ui.m_edt_InsertNormalCur->GetValue();
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fCurrent;

	double Ratio = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[1]/g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_fCTRatio[0];
// 	dNewValue *= Ratio;
	double dChangeValue = dNewValue * Ratio;

	// ȷ�������ʱ�����ԭ����ʱ�䷶Χ��
	if ((dNewValue* Ratio)>g_oLocalSysPara.m_fAC_CurMax)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ�����ʵ�ʳ�̬���ε���ֵ(%f),���ڲ���������������(%f)."),dChangeValue,g_oLocalSysPara.m_fAC_CurMax);
		dNewValue = dCurValue;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_fCurrent = dNewValue;
	}
	ui.m_edt_InsertNormalCur->setText(QString::number(dNewValue,'f',3));
}

void SttReplayWaveformEditWidget::slot_InsertNormal_OutTimeChanged()
{
	double dNewValue = ui.m_edt_InsertNormaloutTime->GetValue();
	double dTime = 20;//Ŀǰ����������ʱ��
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_dOutputTime;

	// ȷ�������ʱ�����ԭ����ʱ�䷶Χ��
	if(dNewValue >dTime)
	{
		dNewValue = dCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("��ǰ���ʱ�䲻�ܳ���[%.3fs]�����������룡"),dTime);
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertNormalWaveData.m_dOutputTime = dNewValue;
	}
	ui.m_edt_InsertNormaloutTime->setText(QString::number(dNewValue,'f',3));

}

void SttReplayWaveformEditWidget::slot_Wave_ReCovery()
{
	g_pReplayTestMain->ReCoveryWave();

}

BOOL SttReplayWaveformEditWidget::VaildWaveOverlap()
{
	double dInsertBegin = ui.m_edt_InsertBegin->GetValue();
	double dInsertEnd= ui.m_edt_InsertEnd->GetValue();
	double dDeleteBegin= ui.m_edt_DeleteBegin->GetValue();
	double dDeleteEnd= ui.m_edt_DeleteEnd->GetValue();

	// ����ص�
	if (!(dInsertEnd <= dDeleteBegin || dInsertBegin >= dDeleteEnd)) 
	{
		CXMessageBox::warning(this, "����", "������ɾ��ʱ����ص���������ѡ��ʱ�䣡");
		return FALSE;
	}
	return TRUE;
}

void SttReplayWaveformEditWidget::slot_Insert_TypeChanged(int nIndex)
{
	if(nIndex < 0)
	{
		return;
	}
	g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_nInsertWaveType = nIndex;

	UpdateInsertTypeWidgetChange(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_nInsertWaveType);
}

void SttReplayWaveformEditWidget::UpdateInsertTypeWidgetChange( int nType )
{
	disconnect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_ZeroChanged()));
	disconnect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_DestinationChanged()));
	disconnect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_BeginTimeChanged()));
	disconnect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_EndTimeChanged()));
	CString strText;

	if(nType == INSERT_WAVE_TYPE_TIME)
	{
		connect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_BeginTimeChanged()));
		connect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_EndTimeChanged()));
		ui.m_edt_InsertBegin->InitCoverage(0,999,3);
		ui.m_edt_InsertEnd->InitCoverage(0,999,3);
        strText = _T("��ʼʱ�̣�s����");
		ui.m_lb_InsertBegin->setText(strText);
        strText = _T("��ֹʱ�̣�s����");
		ui.label_2->setText(strText);
		ui.m_edt_InsertBegin->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin,'f',3));
		ui.m_edt_InsertEnd->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd,'f',3));
	}
	else
	{
		connect(ui.m_edt_InsertBegin, SIGNAL(editingFinished()), this, SLOT(slot_Insert_ZeroChanged()));
		connect(ui.m_edt_InsertEnd, SIGNAL(editingFinished()), this, SLOT(slot_Insert_DestinationChanged()));
		ui.m_edt_InsertBegin->InitCoverage(0,9999999,0);
		ui.m_edt_InsertEnd->InitCoverage(0,9999999,0);
        strText = _T("��ʼ��ţ�");
		ui.m_lb_InsertBegin->setText(strText);
        strText = _T("��ֹ��ţ�");
		ui.label_2->setText(strText);
		ui.m_edt_InsertBegin->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nBeginPoint));
		ui.m_edt_InsertEnd->setText(QString::number(g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_nEndPoint));
	}	
}

int SttReplayWaveformEditWidget::GetWaveEditType()
{
	return m_nWaveEditType;
}

void SttReplayWaveformEditWidget::slot_Insert_BeginTimeChanged()
{
	double dNewValue = ui.m_edt_InsertBegin->GetValue();
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin;
	double dEnd = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd;
	double dRecordDataTimeLength = g_pReplayTestMain->m_pWaveGraphWidget->m_dRecordDataTimeLength;

	// ȷ�������ʱ�����ԭ����ʱ�䷶Χ��
	if(!CheckMaxDataTime(dNewValue))
	{
		if(dCurValue > dRecordDataTimeLength)
		{
			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin = dRecordDataTimeLength;
			dCurValue = dRecordDataTimeLength;
		}		
		dNewValue = dCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("��������/�յ㲻�ܳ����ܲ��γ���[%.3fs]�����������룡"),dRecordDataTimeLength);
	}
	else if(dNewValue > dEnd)
	{
		ui.m_edt_InsertEnd->setText(QString::number(dNewValue,'f',3));
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin = dNewValue;
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin = dNewValue;
		g_pReplayTestMain->m_pWaveGraphWidget->m_bInsertWaveformBackColor = TRUE;
	}
	ui.m_edt_InsertBegin->setText(QString::number(dNewValue,'f',3));
}

void SttReplayWaveformEditWidget::slot_Insert_EndTimeChanged()
{
	double dNewValue = ui.m_edt_InsertEnd->GetValue();
	double dCurValue = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd;
	double dBegin = g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dBegin;
	double dRecordDataTimeLength = g_pReplayTestMain->m_pWaveGraphWidget->m_dRecordDataTimeLength;

	// ȷ�������ʱ�����ԭ����ʱ�䷶Χ��
	if(!CheckMaxDataTime(dNewValue))
	{
		if(dCurValue > dRecordDataTimeLength)
		{
			g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd = dRecordDataTimeLength;
			dCurValue = dRecordDataTimeLength;
		}	
		dNewValue = dCurValue;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("��������/�յ㲻�ܳ����ܲ��γ���[%.3fs]�����������룡"),g_pReplayTestMain->m_pWaveGraphWidget->m_dRecordDataTimeLength);
	}
	else if(dBegin > dNewValue)
	{
		dNewValue = dBegin;
		CLogPrint::LogFormatString(XLOGLEVEL_WARNING, _T("������յ㲻��С����������[%.3fs]�����������룡"),dBegin);
	}
	else
	{
		g_theBigComtradeTransPlay->m_oComtradePlayConfig.m_oWaveEditParas.m_oInsertWaveData.m_dEnd = dNewValue;
	}
	ui.m_edt_InsertEnd->setText(QString::number(dNewValue,'f',3));

	g_pReplayTestMain->m_pWaveGraphWidget->m_bInsertWaveformBackColor = TRUE;
}
