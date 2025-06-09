#include "ADMUAccurAutoTestParasSetDialog.h"
#include "../../Module/UI/Module/CommonMethod/commonMethod.h"
#include "SttMacroParaEditViewADMUAccurAutoTest.h"

QAdmuAccurAutoTestParasSetDialog::QAdmuAccurAutoTestParasSetDialog( QWidget *parent): QDialog(parent)
{
	CString strText;
	strText = _T("ģ��������������������������");
	setWindowTitle(strText);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);
	resize(700,300);
	this->setFixedWidth(800);
	this->setFixedHeight(320);
	InitUI();
	InitConnect();
}

QAdmuAccurAutoTestParasSetDialog::~QAdmuAccurAutoTestParasSetDialog()
{

}

void QAdmuAccurAutoTestParasSetDialog::InitUI()
{
	CString strText;
	QGroupBox *pContinGroupBox = new QGroupBox;
	strText = _T("�������������������:");
	pContinGroupBox->setTitle(strText);
	QGridLayout *pContinLayout = new QGridLayout(pContinGroupBox);
	QLabel *pThreePhaseVolLabel = new QLabel;
	strText = _T("�����ѹ����(V):");
	pThreePhaseVolLabel->setText(strText);
	QLineEdit *pThreePhaseVolLineEdit = new QLineEdit;
	QLabel *pThreePhaseVolUn = new QLabel;
	strText = _T("Un");
	pThreePhaseVolUn->setText(strText);
	QLabel *pThreePhaseCurLabel = new QLabel;
	strText = _T("�����������(A):");
	pThreePhaseCurLabel->setText(strText);
	QLineEdit *pThreePhaseCurLineEdit = new QLineEdit;
	QLabel *pThreePhaseCurIn = new QLabel;
	strText = _T("In");
	pThreePhaseCurIn->setText(strText);

	pThreePhaseVolLineEdit->setObjectName(QString::fromUtf8("LTO_U"));
	GetLineEditValue(pThreePhaseVolLineEdit,_T("LTO_U"));
	connect(pThreePhaseVolLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pThreePhaseCurLineEdit->setObjectName(QString::fromUtf8("LTO_I"));
	GetLineEditValue(pThreePhaseCurLineEdit,_T("LTO_I"));
	connect(pThreePhaseCurLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));

	QLabel *pZeroPhaseVolLabel = new QLabel;
	strText = _T("�����ѹ����(V):");
	pZeroPhaseVolLabel->setText(strText);
	QLineEdit *pZeroPhaseVolLineEdit = new QLineEdit;
	QLabel *pZeroPhaseVolUn = new QLabel;
	strText = _T("Un");
	pZeroPhaseVolUn->setText(strText);
	QLabel *pZeroPhaseCurLabel = new QLabel;
	strText = _T("�����������(A):");
	pZeroPhaseCurLabel->setText(strText);
	QLineEdit *pZeroPhaseCurLineEdit = new QLineEdit;
	QLabel *pZeroPhaseCurIn = new QLabel;
	strText = _T("In");
	pZeroPhaseCurIn->setText(strText);
	QLabel *pWorkLabel = new QLabel;
	strText = _T("��������(h):");
	pWorkLabel->setText(strText);
	QLineEdit *pWorkLineEdit = new QLineEdit;

	pZeroPhaseVolLineEdit->setObjectName(QString::fromUtf8("LTO_U0"));
	GetLineEditValue(pZeroPhaseVolLineEdit,_T("LTO_U0"));
	connect(pZeroPhaseVolLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pZeroPhaseCurLineEdit->setObjectName(QString::fromUtf8("LTO_I0"));
	GetLineEditValue(pZeroPhaseCurLineEdit,_T("LTO_I0"));
	connect(pZeroPhaseCurLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pWorkLineEdit->setObjectName(QString::fromUtf8("LTO_Time"));
	GetLineEditValue(pWorkLineEdit,_T("LTO_Time"));
	connect(pWorkLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));


	pContinLayout->addWidget(pThreePhaseVolLabel,0,0,1,1);
	pContinLayout->addWidget(pThreePhaseVolLineEdit,0,1,1,1);
	pContinLayout->addWidget(pThreePhaseVolUn,0,2,1,1);
	pContinLayout->addWidget(pThreePhaseCurLabel,0,3,1,1);
	pContinLayout->addWidget(pThreePhaseCurLineEdit,0,4,1,1);
	pContinLayout->addWidget(pThreePhaseCurIn,0,5,1,1);
	pContinLayout->addWidget(pZeroPhaseVolLabel,1,0,1,1);
	pContinLayout->addWidget(pZeroPhaseVolLineEdit,1,1,1,1);
	pContinLayout->addWidget(pZeroPhaseVolUn,1,2,1,1);
	pContinLayout->addWidget(pZeroPhaseCurLabel,1,3,1,1);
	pContinLayout->addWidget(pZeroPhaseCurLineEdit,1,4,1,1);
	pContinLayout->addWidget(pZeroPhaseCurIn,1,5,1,1);
	pContinLayout->addWidget(pWorkLabel,1,6,1,1);
	pContinLayout->addWidget(pWorkLineEdit,1,7,1,1);

	QGroupBox *pShortGroupBox = new QGroupBox;
	strText = _T("��ʱ���������������:");
	pShortGroupBox->setTitle(strText);
	QGridLayout *pShortLayout = new QGridLayout(pShortGroupBox);
	QLabel *pApplyMultipleVolLabel = new QLabel;
	strText = _T("��ѹʩ�ӱ���:");
	pApplyMultipleVolLabel->setText(strText);
	QLineEdit *pApplyMultipleVolLineEdit = new QLineEdit;
	QLabel *pApplyMultipleVolUn = new QLabel;
	strText = _T("Un");
	pApplyMultipleVolUn->setText(strText);
	QLabel *pApplyNumVolLabel = new QLabel;
	strText = _T("ʩ�Ӵ���(��):");
	pApplyNumVolLabel->setText(strText);
	QLineEdit *pApplyNumVolLineEdit = new QLineEdit;
	QLabel *pApplyTimeVolLabel = new QLabel;
	strText = _T("ʩ��ʱ��(s):");
	pApplyTimeVolLabel->setText(strText);
	QLineEdit *pApplyTimeVolLineEdit = new QLineEdit;
	QLabel *pInterTimeVolLabel = new QLabel;
	strText = _T("���ʱ��(s):");
	pInterTimeVolLabel->setText(strText);
	QLineEdit *pInterTimeVolLineEdit = new QLineEdit;

	pApplyMultipleVolLineEdit->setObjectName(QString::fromUtf8("Vol_InflictTimes"));
	GetLineEditValue(pApplyMultipleVolLineEdit,_T("Vol_InflictTimes"));
	connect(pApplyMultipleVolLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pApplyNumVolLineEdit->setObjectName(QString::fromUtf8("Vol_InflictCount"));
	GetLineEditValue(pApplyNumVolLineEdit,_T("Vol_InflictCount"));
	connect(pApplyNumVolLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pApplyTimeVolLineEdit->setObjectName(QString::fromUtf8("Vol_OnceInflictTime"));
	GetLineEditValue(pApplyTimeVolLineEdit,_T("Vol_OnceInflictTime"));
	connect(pApplyTimeVolLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pInterTimeVolLineEdit->setObjectName(QString::fromUtf8("Vol_IntervalTime"));
	GetLineEditValue(pInterTimeVolLineEdit,_T("Vol_IntervalTime"));
	connect(pInterTimeVolLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));

	QLabel *pApplyMultipleCurLabel = new QLabel;
	strText = _T("����ʩ�ӱ���:");
	pApplyMultipleCurLabel->setText(strText);
	QLineEdit *pApplyMultipleCurLineEdit = new QLineEdit;
	QLabel *pApplyMultipleCurIn = new QLabel;
	strText = _T("In");
	pApplyMultipleCurIn->setText(strText);
	QLabel *pApplyNumCurLabel = new QLabel;
	strText = _T("ʩ�Ӵ���(��):");
	pApplyNumCurLabel->setText(strText);
	QLineEdit *pApplyNumCurLineEdit = new QLineEdit;
	QLabel *pApplyTimeCurLabel = new QLabel;
	strText = _T("ʩ��ʱ��(s):");
	pApplyTimeCurLabel->setText(strText);
	QLineEdit *pApplyTimeCurLineEdit = new QLineEdit;
	QLabel *pInterTimeCurLabel = new QLabel;
	strText = _T("���ʱ��(s):");
	pInterTimeCurLabel->setText(strText);
	QLineEdit *pInterTimeCurLineEdit = new QLineEdit;

	pApplyMultipleCurLineEdit->setObjectName(QString::fromUtf8("Curr_InflictTimes"));
	GetLineEditValue(pApplyMultipleCurLineEdit,_T("Curr_InflictTimes"));
	connect(pApplyMultipleCurLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pApplyNumCurLineEdit->setObjectName(QString::fromUtf8("Curr_InflictCount"));
	GetLineEditValue(pApplyNumCurLineEdit,_T("Curr_InflictCount"));
	connect(pApplyNumCurLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pApplyTimeCurLineEdit->setObjectName(QString::fromUtf8("Curr_OnceInflictTime"));
	GetLineEditValue(pApplyTimeCurLineEdit,_T("Curr_OnceInflictTime"));
	connect(pApplyTimeCurLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	pInterTimeCurLineEdit->setObjectName(QString::fromUtf8("Curr_IntervalTime"));
	GetLineEditValue(pInterTimeCurLineEdit,_T("Curr_IntervalTime"));
	connect(pInterTimeCurLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));

	pShortLayout->addWidget(pApplyMultipleVolLabel,0,0,1,1);
	pShortLayout->addWidget(pApplyMultipleVolLineEdit,0,1,1,1);
	pShortLayout->addWidget(pApplyMultipleVolUn,0,2,1,1);
	pShortLayout->addWidget(pApplyNumVolLabel,0,3,1,1);
	pShortLayout->addWidget(pApplyNumVolLineEdit,0,4,1,1);
	pShortLayout->addWidget(pApplyTimeVolLabel,0,5,1,1);
	pShortLayout->addWidget(pApplyTimeVolLineEdit,0,6,1,1);
	pShortLayout->addWidget(pInterTimeVolLabel,0,7,1,1);
	pShortLayout->addWidget(pInterTimeVolLineEdit,0,8,1,1);

	pShortLayout->addWidget(pApplyMultipleCurLabel,1,0,1,1);
	pShortLayout->addWidget(pApplyMultipleCurLineEdit,1,1,1,1);
	pShortLayout->addWidget(pApplyMultipleCurIn,1,2,1,1);
	pShortLayout->addWidget(pApplyNumCurLabel,1,3,1,1);
	pShortLayout->addWidget(pApplyNumCurLineEdit,1,4,1,1);
	pShortLayout->addWidget(pApplyTimeCurLabel,1,5,1,1);
	pShortLayout->addWidget(pApplyTimeCurLineEdit,1,6,1,1);
	pShortLayout->addWidget(pInterTimeCurLabel,1,7,1,1);
	pShortLayout->addWidget(pInterTimeCurLineEdit,1,8,1,1);

	m_pOkBtn = new QPushButton(this);
	strText = _T("ȷ��");
	m_pOkBtn->setText(strText);
	m_pCancelBtn = new QPushButton(this);
	strText = _T("ȡ��");
	m_pCancelBtn->setText(strText);

	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(m_pOkBtn);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(m_pCancelBtn);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);

	QVBoxLayout* pMainLayout = new QVBoxLayout(this);
	pMainLayout->addWidget(pContinGroupBox);
	pMainLayout->addWidget(pShortGroupBox);
	pMainLayout->addLayout(pOkCancel_HBoxLayout);

	setFocusPolicy(Qt::StrongFocus);

	setLayout(pMainLayout);	
}

void QAdmuAccurAutoTestParasSetDialog::InitConnect()
{
	connect(m_pOkBtn, SIGNAL(clicked()), this, SLOT(slot_OkClicked()));
	connect(m_pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void QAdmuAccurAutoTestParasSetDialog::slot_OkClicked()
{
	QMap<QString, float>::iterator i;
	for (i = m_TempData.begin(); i != m_TempData.end(); ++i)
	{
		QString strID = i.key();
		float fValue = i.value();
		g_pAdmuAccurAutoTest->m_pADMUAutoTestDataGroup.SetDataValue(strID, fValue);
	}

	m_TempData.clear();

	close();
}

void QAdmuAccurAutoTestParasSetDialog::slot_CancelClicked()
{
	close();
}



void QAdmuAccurAutoTestParasSetDialog::GetLineEditValue( QLineEdit * pLineEdit,CString strID )
{
	CDvmData* pCurData = (CDvmData*)g_pAdmuAccurAutoTest->m_pADMUAutoTestDataGroup.FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	long decimal = 0;
	if (strID == _T("LTO_U")|| strID == _T("LTO_I")|| strID == _T("LTO_U0")|| strID == _T("LTO_I0"))
	{
		decimal = 1;
	}
	else
	{
		decimal = 0;
	}
	pLineEdit->setText(QString::number(fValue,'f',decimal));
}


void QAdmuAccurAutoTestParasSetDialog::slot_LineEditFinished()
{
	CString strID;
	float fValue ,fMaxValue,fMinValue;
	long decimal = 0;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		if (strID == _T("LTO_U")|| strID == _T("LTO_I")|| strID == _T("LTO_U0")|| strID == _T("LTO_I0"))
		{
			fMaxValue = 1.2 * 3;
			fMinValue = 0;
			decimal = 1;
		}
		else if (strID == _T("Vol_InflictTimes"))
		{
			fMaxValue = 2 * 3;
			fMinValue = 0;
			decimal = 0;
		}
		else if (strID == _T("Vol_InflictCount") || strID == _T("Vol_IntervalTime"))
		{
			fMaxValue = 10 * 3;
			fMinValue = 0;
			decimal = 0;
		}
		else if (strID == _T("Vol_OnceInflictTime") || strID == _T("Curr_OnceInflictTime"))
		{
			fMaxValue = 1 * 3;
			fMinValue = 0;
			decimal = 0;
		}
		else if (strID == _T("Curr_InflictTimes"))
		{
			fMaxValue = 20 * 3;
			fMinValue = 0;
			decimal = 0;
		}
		else if (strID == _T("Curr_InflictCount"))
		{
			fMaxValue = 5 * 3;
			fMinValue = 0;
			decimal = 0;
		}
		else if (strID == _T("Curr_IntervalTime"))
		{
			fMaxValue = 300 * 3;
			fMinValue = 0;
			decimal = 0;
		}
		else if (strID == _T("LTO_Time"))
		{
			fMaxValue = 24 * 3;
			fMinValue = 1;
			decimal = 0;
		}
		fValue = pLineEdit->text().toFloat();
		
		if (fValue < fMinValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����ֵ%fС����Сֵ%f"), fValue,fMinValue);
		}
		if (fValue > fMaxValue)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("����ֵ%f�������ֵ%f"), fValue,fMaxValue);
		}
		fValue = setLimit(fMinValue,fMaxValue,fValue);
		m_TempData[strID] = fValue;
		pLineEdit->setText(QString::number(fValue,'f',decimal));
	}
}
