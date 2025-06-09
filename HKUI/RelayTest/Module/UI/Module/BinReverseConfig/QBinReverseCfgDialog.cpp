#include "QBinReverseCfgDialog.h"
#include "../../../AdjustTool/SttAdjDevice.h"
#include "../../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "QValidator"
#include "../../../SttTestCtrl/SttTestAppBase.h"

QBinReverseCfgDialog::QBinReverseCfgDialog(QWidget *parent)
: QDialog(parent)
{
	ui.setupUi(this);
	InitBinInfos();
	InitUI();
}

QBinReverseCfgDialog::~QBinReverseCfgDialog()
{

}

void QBinReverseCfgDialog::InitBinInfos()
{
	for (int nBinIndex = 0; nBinIndex < g_nBinCount; nBinIndex++)
	{
		char strIndex = 'A' + nBinIndex;
		m_strName[nBinIndex] = g_sLangTxt_Native_BinX;
		m_strName[nBinIndex].AppendFormat("%c", strIndex);
		m_oBinCfg[nBinIndex].m_nEmpty = g_oSystemParas.m_BinConfig[nBinIndex].m_nEmpty;
		m_oBinCfg[nBinIndex].m_fTripVolt = g_oSystemParas.m_BinConfig[nBinIndex].m_fTripVolt;
	}
}

void QBinReverseCfgDialog::SaveBinConfigs()
{
	for (int nBinIndex = 0; nBinIndex < g_nBinCount; nBinIndex++)
	{
		char strIndex = 'A' + nBinIndex;
		g_oSystemParas.m_BinConfig[nBinIndex].m_nEmpty = m_oBinCfg[nBinIndex].m_nEmpty;
		g_oSystemParas.m_BinConfig[nBinIndex].m_fTripVolt = m_oBinCfg[nBinIndex].m_fTripVolt;
	}
}

void QBinReverseCfgDialog::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint);
	for (int nIndex = 0; nIndex < g_nBinCount; nIndex++)
	{
		m_pCheckBoxBeEmpty[nIndex] = new QCheckBox;
		m_pCheckBoxBeEmpty[nIndex]->setChecked(m_oBinCfg[nIndex].m_nEmpty);
		m_pCheckBoxBeEmpty[nIndex]->setStyleSheet(
			"QCheckBox {"
			"padding-left: 23px; " 
			"}");
		ui.m_GLayout_Center->addWidget(m_pCheckBoxBeEmpty[nIndex], nIndex+2, 1, 1, 1);
		m_pEdit[nIndex] = new QLineEdit(this);
		m_pEdit[nIndex]->setMaximumWidth(90);
		m_pEdit[nIndex]->setProperty("index", nIndex);
		QDoubleValidator *validator = new QDoubleValidator(0, 999999, 2, this);//限制输入为0-999999的双精度数
		validator->setNotation(QDoubleValidator::StandardNotation); // 使用标准表示法
		m_pEdit[nIndex]->setValidator(validator);
		ui.m_GLayout_Center->addWidget(m_pEdit[nIndex], nIndex+2, 2, 1, 1);
		m_pTextLabelBin[nIndex] = new QLabel;
		m_pTextLabelBin[nIndex]->setText(m_strName[nIndex]);
		m_pTextLabelBin[nIndex]->setAlignment(Qt::AlignCenter);
		m_pTextLabelBin[nIndex]->setEnabled(!m_oBinCfg[nIndex].m_nEmpty);
		ui.m_GLayout_Center->addWidget(m_pTextLabelBin[nIndex], nIndex+2, 0, 1, 1);
		connect(m_pCheckBoxBeEmpty[nIndex], SIGNAL(toggled(bool)), this, SLOT(On_BeEmptyChanged()));
		connect(m_pEdit[nIndex], SIGNAL(editingFinished()), this, SLOT(On_ReverseThresholdChanged()));
		m_pCheckBoxBeEmpty[nIndex]->setProperty("index", nIndex);
		m_pCheckBoxBeEmpty[nIndex]->setChecked(m_oBinCfg[nIndex].m_nEmpty);
		QString tripVoltStr = QString::number(m_oBinCfg[nIndex].m_fTripVolt);
		m_pEdit[nIndex]->setText(tripVoltStr);
		m_pEdit[nIndex]->setEnabled(!m_oBinCfg[nIndex].m_nEmpty);//支持采集的时候才开放编辑，不然一直灰掉
	}
	connect(ui.m_Btn_OK, SIGNAL(clicked()), this, SLOT(On_Btn_OK_clicked()));
	connect(ui.m_Btn_Cancel, SIGNAL(clicked()), this, SLOT(On_Btn_Cancel_clicked()));
}

void QBinReverseCfgDialog::GenerareParas()
{
	m_oBinCfgParas.DeleteAll();
	for (int nIndex = 0; nIndex < g_nBinCount; nIndex++)
	{
		char strIndex = 'A' + nIndex;
		CString strID;
		strID.Format(_T("Bin%cType"), strIndex);
		m_oBinCfgParas.AddNewData(strID, static_cast<long>(m_oBinCfg[nIndex].m_nEmpty));
		strID.Format(_T("Bin%cVolt"), strIndex);
		m_oBinCfgParas.AddNewData(strID, m_oBinCfg[nIndex].m_fTripVolt);
	}

}

void QBinReverseCfgDialog::SetParas()
{
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_BinConfig(&m_oBinCfgParas);
}

void QBinReverseCfgDialog::handleEnterKey()
{

}

void QBinReverseCfgDialog::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		// 处理 Enter 键的逻辑
		handleEnterKey();
		event->accept(); // 处理完事件后接受它
	}
	else 
	{
		QDialog::keyPressEvent(event);
	}
}

void QBinReverseCfgDialog::On_Btn_OK_clicked()
{
	GenerareParas();
	SetParas();
	SaveBinConfigs();
	close();
}

void QBinReverseCfgDialog::On_Btn_Cancel_clicked()
{
	close();
}

void QBinReverseCfgDialog::On_BeEmptyChanged()
{
	QCheckBox *checkbox = qobject_cast<QCheckBox*>(sender());
	if (checkbox) 
	{
		int index = checkbox->property("index").toInt();
		m_pEdit[index]->setEnabled(!m_pCheckBoxBeEmpty[index]->isChecked());
		m_oBinCfg[index].m_nEmpty = m_pCheckBoxBeEmpty[index]->isChecked();
	}
}

void QBinReverseCfgDialog::On_ReverseThresholdChanged()
{
	QLineEdit *pCurEdit = qobject_cast<QLineEdit*>(sender());
	if (pCurEdit)
	{
		int index = pCurEdit->property("index").toInt();
		m_oBinCfg[index].m_fTripVolt = pCurEdit->text().toFloat();
	}
}
