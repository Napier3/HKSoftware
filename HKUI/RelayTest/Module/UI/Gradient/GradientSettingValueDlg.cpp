#include "GradientSettingValueDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../../XLangResource_Native.h"

GradientSettingValueDlg::GradientSettingValueDlg(tmt_GradientParasEx* pParas, QWidget* parent) : QDialog(parent)
{
	m_pUActEdit = NULL;
	m_pParas = pParas;
	InitUI();
}

GradientSettingValueDlg::~GradientSettingValueDlg()
{

}

void GradientSettingValueDlg::InitUI()
{
	//CString strTitle = "整定值";

	setWindowTitle(/*整定值*/g_sLangTxt_State_SettingValue); //lcq
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QGridLayout* pGridLayout = new QGridLayout(this);

	CString strText;
	QLabel* pLabel = new QLabel(this);
	//strText = "电压动作值(V)";
	pLabel->setText(/*电压动作值(V)*/g_sLangTxt_Gradient_VActionValue); //lcq
	pGridLayout->addWidget(pLabel, 0, 0);
	m_pUActEdit = new QLineEdit(this);
	m_pUActEdit->setText(QString::number(m_pParas->m_fUSet));
	pGridLayout->addWidget(m_pUActEdit, 0, 1);

	pLabel = new QLabel(this);
	//strText = "电流动作值(A)";
	pLabel->setText(/*电流动作值(A)*/g_sLangTxt_Gradient_CActionValue);//lcq
	pGridLayout->addWidget(pLabel, 1, 0);
	m_pIActEdit = new QLineEdit(this);
	m_pIActEdit->setText(QString::number(m_pParas->m_fISet));
	pGridLayout->addWidget(m_pIActEdit, 1, 1);

	pLabel = new QLabel(this);
	//strText = "返回系数";
	pLabel->setText(/*返回系数*/g_sLangTxt_Gradient_ReCoefficient); //lcq
	pGridLayout->addWidget(pLabel, 2, 0);
	m_pRetCoefSetEdit = new QLineEdit(this);
	m_pRetCoefSetEdit->setText(QString::number(m_pParas->m_fRetCoefSet));
	pGridLayout->addWidget(m_pRetCoefSetEdit, 2, 1);

	pLabel = new QLabel(this);
	//strText = "频率动作值(Hz)";
	pLabel->setText(/*频率动作值(Hz)*/g_sLangTxt_Gradient_FreAValue); //lcq
	pGridLayout->addWidget(pLabel, 3, 0);
	m_pHzSetEdit = new QLineEdit(this);
	m_pHzSetEdit->setText(QString::number(m_pParas->m_fHzSet));
	pGridLayout->addWidget(m_pHzSetEdit, 3, 1);

	pLabel = new QLabel(this);
	//strText = "边界角1(°)";
	pLabel->setText(/*边界角1(°)*/g_sLangTxt_Gradient_FirBoundAngle); //lcq
	pGridLayout->addWidget(pLabel, 0, 2);
	m_pAngleFSetEdit = new QLineEdit(this);
	m_pAngleFSetEdit->setText(QString::number(m_pParas->m_fAngleFSet));
	pGridLayout->addWidget(m_pAngleFSetEdit, 0, 3);

	pLabel = new QLabel(this);
	//strText = "边界角2(°)";
	pLabel->setText(/*边界角2(°)*/g_sLangTxt_Gradient_SecBoundAngle); //lcq
	pGridLayout->addWidget(pLabel, 1, 2);
	m_pAngleSSetEdit = new QLineEdit(this);
	m_pAngleSSetEdit->setText(QString::number(m_pParas->m_fAngleSSet));
	pGridLayout->addWidget(m_pAngleSSetEdit, 1, 3);

	pLabel = new QLabel(this);
	//strText = "最大灵敏角(°)";
	pLabel->setText(/*最大灵敏角(°)*/g_sLangTxt_Gradient_MaxSenAngle); //lcq
	pGridLayout->addWidget(pLabel, 2, 2);
	m_pMaxAngleSetEdit = new QLineEdit(this);
	m_pMaxAngleSetEdit->setText(QString::number(m_pParas->m_fMaxAngleSet));
	pGridLayout->addWidget(m_pMaxAngleSetEdit, 2, 3);

	pLabel = new QLabel(this);
	strText = "相位动作值(°)";
	pLabel->setText(/*相位动作值(°)*/g_sLangTxt_Gradient_PhaseAValue); //lcq
	pGridLayout->addWidget(pLabel, 3, 2);
	m_pAngleSetEdit = new QLineEdit(this);
	m_pAngleSetEdit->setText(QString::number(m_pParas->m_fAngleSet));
	pGridLayout->addWidget(m_pAngleSetEdit, 3, 3);

	pVLayout->addLayout(pGridLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	pHLayout->addStretch();
	QPushButton* pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sOK");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	pHLayout->addWidget(pBtn);
	pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sCancel");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	pHLayout->addWidget(pBtn);
	pHLayout->addStretch();
	pVLayout->addLayout(pHLayout);
}

void GradientSettingValueDlg::slot_btnOK_Clicked()
{
	m_pParas->m_fUSet = m_pUActEdit->text().toFloat();	
	m_pParas->m_fISet = m_pIActEdit->text().toFloat();			
	m_pParas->m_fAngleSet = m_pAngleSetEdit->text().toFloat();		
	m_pParas->m_fHzSet = m_pHzSetEdit->text().toFloat();		
	m_pParas->m_fRetCoefSet = m_pRetCoefSetEdit->text().toFloat();	
	m_pParas->m_fAngleFSet = m_pAngleFSetEdit->text().toFloat();	
	m_pParas->m_fAngleSSet = m_pAngleSSetEdit->text().toFloat();	
	m_pParas->m_fMaxAngleSet = m_pMaxAngleSetEdit->text().toFloat();	

	accept();
}

void GradientSettingValueDlg::slot_btnCancel_Clicked()
{
	reject();
}