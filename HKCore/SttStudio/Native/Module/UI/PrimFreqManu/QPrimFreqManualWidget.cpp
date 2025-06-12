//#include "stdafx.h"
#include "QPrimFreqManualWidget.h"
#include "../../../Module/XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SttMacroParaEditViewPrimFreqManu.h"
//#include "QSttManualBinBoutDlg.h"
#include "../SttTestCntrFrameBase.h"

QPrimFreqManualWidget::QPrimFreqManualWidget(QWidget *parent) : QWidget(parent)
{
    m_pEditStep = 0;
    m_pEditInitVal = 0;
	m_pEditFinishVal = 0;
    m_pEditTime = 0;
    m_pCbbChannel = 0;
    m_pCbbSelect = 0;
    m_pCbbChangeType = 0;
    m_pCbOut1 = 0;
    m_pCbOut2 = 0;
    m_pCbOut3 = 0;
    m_pCbOut4 = 0;

    m_pCbAuto = 0;
	m_nChanneType = 0;
	m_nUnitType = 0;

	InitUI();
}

QPrimFreqManualWidget::~QPrimFreqManualWidget()
{

}

void QPrimFreqManualWidget::Init()
{
	m_bControlLock = false;
	m_pManualParas = NULL;
	m_nVChNums = m_nIChNums = 0;
	m_pEvent = NULL;

    CString strText;
	xlang_GetLangStrByFile(strText, "Native_Amplitude");
	m_pCbbSelect->setItemText(0, strText);
	xlang_GetLangStrByFile(strText, "Native_Angle");
	m_pCbbSelect->setItemText(1, strText);
	xlang_GetLangStrByFile(strText, "Native_Freq");
	m_pCbbSelect->setItemText(2, strText);

	xlang_GetLangStrByFile(strText, "Manual_S_E");
	m_pCbbChangeType->setItemText(0, strText);
	xlang_GetLangStrByFile(strText, "Manual_S_E_S");
	m_pCbbChangeType->setItemText(1, strText);

	m_pBtnAdd->setDisabled(true);
	m_pBtnMinus->setDisabled(true);
	m_pBtnLock->setDisabled(true);

}

void QPrimFreqManualWidget::InitUI()
{
	m_pVMainLayout = new QVBoxLayout;
	m_pTabWidget = new QSttTabWidget();

	m_pVMainLayout->addWidget(m_pTabWidget);

	// ��ʼ����ǩ
	m_pLabStep = new QLabel(_T("����(V):"));
	m_pLabInitVal = new QLabel(_T("ʼֵ(V):"));
	m_pLabFinishVal = new QLabel(_T("��ֵ(V):"));
	m_plabChannel = new QLabel(_T("ͨ��ѡ��:"));
	m_plabTime = new QLabel(_T("ʱ��(s):"));
	m_plabChangeType = new QLabel(_T("�仯��ʽ:"));

	// ��ʼ�������
	m_pEditStep = new QSttLineEdit();
	m_pEditInitVal = new QSttLineEdit();
	m_pEditFinishVal = new QSttLineEdit();
	m_pEditTime = new QSttLineEdit();

	// ����ѡ���
	m_pCbbChannel = new QScrollComboBox();
	m_pCbbSelect = new QScrollComboBox();
	m_pCbbChangeType = new QScrollComboBox();

	m_pCbbSelect->addItem(_T("��ֵ"));
	m_pCbbSelect->addItem(_T("��λ"));
	m_pCbbSelect->addItem(_T("Ƶ��"));

	m_pCbbChangeType->addItem(_T("ʼ-��"));
	m_pCbbChangeType->addItem(_T("ʼ-��-ʼ"));

	// ��ť
	m_pInBinaryOutSet = new QPushButton(_T("����������"));
	m_pBtnAdd = new QPushButton(_T("+"));
	m_pBtnMinus = new QPushButton(_T("-"));
	m_pBtnLock = new QPushButton();
	m_pCbAuto = new QCheckBox(_T("�Զ�"));

	m_pBtnAdd->setFixedSize(QSize(60,35));
	m_pBtnMinus->setFixedSize(QSize(60,35));
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

	m_pBtnLayout1 = new QHBoxLayout;
	m_pBtnLayout1->addWidget(m_plabChannel);
	m_pBtnLayout1->addWidget(m_pCbbChannel);
	m_pBtnLayout1->addWidget(m_pCbbSelect);
	m_pBtnLayout1->addWidget(m_plabTime);
	m_pBtnLayout1->addWidget(m_pEditTime);
	m_pBtnLayout1->addWidget(m_pCbAuto);
	m_pBtnLayout1->addWidget(m_pBtnLock);
	m_pBtnLayout1->addWidget(m_pBtnAdd);
	m_pBtnLayout1->addWidget(m_pBtnMinus);
	m_pBtnLayout1->addWidget(m_pInBinaryOutSet);

	m_pBtnLayout2 = new QHBoxLayout;
// 	m_pLabInitVal->setMinimumWidth(110);
	m_pBtnLayout2->addWidget(m_pLabInitVal);
	m_pBtnLayout2->addWidget(m_pEditInitVal);
	m_pBtnLayout2->addWidget(m_pLabFinishVal);
	m_pBtnLayout2->addWidget(m_pEditFinishVal);
	m_pBtnLayout2->addWidget(m_pLabStep);
	m_pBtnLayout2->addWidget(m_pEditStep);
	m_pBtnLayout2->addWidget(m_plabChangeType);
	m_pBtnLayout2->addWidget(m_pCbbChangeType);

	m_pVBtnLayout = new QVBoxLayout;
	m_pVBtnLayout->addLayout(m_pBtnLayout1);
	m_pVBtnLayout->addLayout(m_pBtnLayout2);

	m_pHDownLayout = new QHBoxLayout;
	m_pHDownLayout->addLayout(m_pVBtnLayout,8);

	// ��ѡ��
	m_pCbOut1 = new QCheckBox(_T("1") );
	m_pCbOut2 = new QCheckBox(_T("2") );
	m_pCbOut3 = new QCheckBox(_T("3") );
	m_pCbOut4 = new QCheckBox(_T("4") );
	QGridLayout	*m_pBOutGridLayout = new QGridLayout;
	m_pBOutGridLayout->addWidget(m_pCbOut1, 0, 0);
	m_pBOutGridLayout->addWidget(m_pCbOut2, 0, 1);
	m_pBOutGridLayout->addWidget(m_pCbOut3, 1, 0);
	m_pBOutGridLayout->addWidget(m_pCbOut4, 1, 1);
	m_pGrpCbOut = new QGroupBox();
	m_pGrpCbOut->setTitle(_T("��������"));
	m_pGrpCbOut->setLayout(m_pBOutGridLayout);
	m_pHDownLayout->addWidget(m_pGrpCbOut,2);

	m_pVMainLayout->addLayout(m_pHDownLayout);

	// ת�������ź�
	m_pGrpPulseSignal = new QGroupBox(_T("ת�������ź�") );
	m_pGrpPulseSignal->setCheckable(true);
	m_pLblPulseType = new QLabel(_T("�����ź�") );
	m_pCbbPulseType = new QScrollComboBox( );
	m_pCbbPulseType->addItem(_T("���β�"));
	m_pCbbPulseType->addItem(_T("���Ҳ�"));

	m_pLblPulseWidth = new QLabel(_T("������ (ms)") );
	m_pEditPulseWidth = new QSttLineEdit( );
	m_pEditPulseWidth->setText(_T("10"));

	m_pLblPeakValue = new QLabel(_T("���ֵ (V)") );
	m_pCbbPeakValue = new QScrollComboBox( );
	m_pCbbPeakValue->addItem(_T("6"));
	m_pCbbPeakValue->addItem(_T("12"));
	m_pCbbPeakValue->addItem(_T("16"));
	m_pCbbPeakValue->addItem(_T("24"));

	m_pLblPulseFreq = new QLabel(_T("Ƶ�� (Hz)") );
	m_pEditPulseFreq = new QSttLineEdit( );
	m_pEditPulseFreq->setText(_T("50.000"));

	m_pPulseLayout = new QHBoxLayout;
	m_pPulseLayout->addWidget(m_pLblPulseType);
	m_pPulseLayout->addWidget(m_pCbbPulseType);
	m_pPulseLayout->addWidget(m_pLblPulseWidth);
	m_pPulseLayout->addWidget(m_pEditPulseWidth);
	m_pPulseLayout->addWidget(m_pLblPeakValue);
	m_pPulseLayout->addWidget(m_pCbbPeakValue);
	m_pPulseLayout->addWidget(m_pLblPulseFreq);
	m_pPulseLayout->addWidget(m_pEditPulseFreq);

// 	QVBoxLayout *pulseLayout = new QVBoxLayout;
// 	pulseLayout->addLayout(m_pPulseLayout);
	m_pGrpPulseSignal->setLayout(m_pPulseLayout);

	m_pVMainLayout->addWidget(m_pGrpPulseSignal);

	// ֱ���ź�Դ
	m_pGrpDcSignal = new QGroupBox(_T("ֱ���ź�Դ") );
	m_pGrpDcSignal->setCheckable(true);
	m_pLblDc1 = new QLabel(_T("Idc1 (mA)") );
	m_pEditDc1 = new QSttLineEdit();
	m_pEditDc1->setText(_T("12.000"));

	m_pCbbChangeType = new QScrollComboBox;

	m_pCbbDcChangeType = new QScrollComboBox(this);
	m_pCbbDcChangeType->addItem(_T("����Ƶ��"));
	m_pCbbDcChangeType->addItem(_T("�����ת��"));

	m_pEditDcChangeValue = new QSttLineEdit(this);

	m_pLblDc2 = new QLabel(_T("Idc2 (mA)") );
	m_pEditDc2 = new QSttLineEdit(this);
	m_pEditDc2->setText(_T("12.000"));

	m_pBtnMapping = new QPushButton(_T("��Ӧ��ϵ") );

	m_pDcLayout = new QHBoxLayout;
	m_pDcLayout->addWidget(m_pLblDc1);
	m_pDcLayout->addWidget(m_pEditDc1);
	m_pDcLayout->addWidget(m_pCbbDcChangeType);
	m_pDcLayout->addWidget(m_pEditDcChangeValue);
	m_pDcLayout->addWidget(m_pLblDc2);
	m_pDcLayout->addWidget(m_pEditDc2);
	m_pDcLayout->addWidget(m_pBtnMapping);

// 	QVBoxLayout *dcLayout = new QVBoxLayout;
// 	dcLayout->addLayout(m_pDcLayout);
	m_pGrpDcSignal->setLayout(m_pDcLayout);
	m_pVMainLayout->addWidget(m_pGrpDcSignal);

	this->setLayout(m_pVMainLayout);
}
void QPrimFreqManualWidget::ChannelTableItemValue_AllFreq(float fstep,int AddOrMinus,bool bDC)
{
	if (m_pTestResource != NULL)
	{
		CString strChID;
		CExBaseObject *pChObj = NULL;

		for (int nChIndex = 0;nChIndex<6;nChIndex++ )
		{
			strChID.Format(_T("U%ld"),nChIndex+1);
			pChObj = m_pTestResource->m_oVolChRsListRef.FindByID(strChID);

			if (pChObj != NULL)
			{
				emit sig_ChannelTableItemValue(/*pChObj->m_strName*/pChObj->m_strID,fstep,fre_type,AddOrMinus,bDC);//dingxy 20250122 ��Ϊͨ��ID
			}

			strChID.Format(_T("I%ld"),nChIndex+1);
			pChObj = m_pTestResource->m_oCurChRsListRef.FindByID(strChID);

			if (pChObj != NULL)
			{
				emit sig_ChannelTableItemValue(/*pChObj->m_strName*/pChObj->m_strID,fstep,fre_type,AddOrMinus,bDC);
			}
		}
	}
}

long QPrimFreqManualWidget::GetChanneType()
{
	return m_nChanneType;
}

long QPrimFreqManualWidget::GetCbbSelect()
{
	return m_pCbbSelect->currentIndex();
}
