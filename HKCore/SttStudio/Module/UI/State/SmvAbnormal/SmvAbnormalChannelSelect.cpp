#include "SmvAbnormalChannelSelect.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../Controls/SttCheckBox.h"

QSmvAbnormalChannelSelect::QSmvAbnormalChannelSelect(tmt_StateAbnormalSMV *pAbnormalSMV,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::X11BypassWindowManagerHint);
	m_pAbnormalSMV = pAbnormalSMV;
// 	m_channelNum.clear();
// 	if (channelnum.size()>0)
// 	{
// 		for (int i=0;i<channelnum.size();i++)
// 		{
// 			m_channelNum.append(channelnum.at(i)+1);
// 		}
// 	}
// 	else
// 	{
// 		m_channelNum.clear();
// 	}
	
	initData();
	initConnnect();
    InitLanguage();
}

QSmvAbnormalChannelSelect::~QSmvAbnormalChannelSelect()
{

}

void QSmvAbnormalChannelSelect::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.ck_channel1, (g_sLangTxt_Native_Channel + "1"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel2, (g_sLangTxt_Native_Channel + "2"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel3, (g_sLangTxt_Native_Channel + "3"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel4, (g_sLangTxt_Native_Channel + "4"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel5, (g_sLangTxt_Native_Channel + "5"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel6, (g_sLangTxt_Native_Channel + "6"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel7, (g_sLangTxt_Native_Channel + "7"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel8, (g_sLangTxt_Native_Channel + "8"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel9, (g_sLangTxt_Native_Channel + "9"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel10, (g_sLangTxt_Native_Channel + "10"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel11, (g_sLangTxt_Native_Channel + "11"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel12, (g_sLangTxt_Native_Channel + "12"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel13, (g_sLangTxt_Native_Channel + "13"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel14, (g_sLangTxt_Native_Channel + "14"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel15, (g_sLangTxt_Native_Channel + "15"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel16, (g_sLangTxt_Native_Channel + "16"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel17, (g_sLangTxt_Native_Channel + "17"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel18, (g_sLangTxt_Native_Channel + "18"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel19, (g_sLangTxt_Native_Channel + "19"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel20, (g_sLangTxt_Native_Channel + "20"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel21, (g_sLangTxt_Native_Channel + "21"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel22, (g_sLangTxt_Native_Channel + "22"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel23, (g_sLangTxt_Native_Channel + "23"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel24, (g_sLangTxt_Native_Channel + "24"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel25, (g_sLangTxt_Native_Channel + "25"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel26, (g_sLangTxt_Native_Channel + "26"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel27, (g_sLangTxt_Native_Channel + "27"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel28, (g_sLangTxt_Native_Channel + "28"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel29, (g_sLangTxt_Native_Channel + "29"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel30, (g_sLangTxt_Native_Channel + "30"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel31, (g_sLangTxt_Native_Channel + "31"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel32, (g_sLangTxt_Native_Channel + "32"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel33, (g_sLangTxt_Native_Channel + "33"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel34, (g_sLangTxt_Native_Channel + "34"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel35, (g_sLangTxt_Native_Channel + "35"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel36, (g_sLangTxt_Native_Channel + "36"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel37, (g_sLangTxt_Native_Channel + "37"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel38, (g_sLangTxt_Native_Channel + "38"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel39, (g_sLangTxt_Native_Channel + "39"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel40, (g_sLangTxt_Native_Channel + "40"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel41, (g_sLangTxt_Native_Channel + "41"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel42, (g_sLangTxt_Native_Channel + "42"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel43, (g_sLangTxt_Native_Channel + "43"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel44, (g_sLangTxt_Native_Channel + "44"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel45, (g_sLangTxt_Native_Channel + "45"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel46, (g_sLangTxt_Native_Channel + "46"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel47, (g_sLangTxt_Native_Channel + "47"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel48, (g_sLangTxt_Native_Channel + "48"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel49, (g_sLangTxt_Native_Channel + "49"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_channel50, (g_sLangTxt_Native_Channel + "50"), XLang_Ctrls_QCheckBox);

    xlang_SetLangStrToWidget_Txt(ui.pbn_ALlReset, g_sLangTxt_SelAll, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_ALlNoReset, g_sLangTxt_SelNone, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Ok, g_sLangTxt_OK, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Cancle, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}

void QSmvAbnormalChannelSelect::initData()
{
	CString strTmp;
	QSttCheckBox *pCurCheckBox = NULL;

	for (int nIndex = 0;nIndex<50;nIndex++)
	{
		strTmp.Format("ck_channel%d",nIndex+1);
		pCurCheckBox = ui.groupBox->findChild<QSttCheckBox *>(strTmp);

		if (pCurCheckBox == NULL)
		{
			continue;
		}

		if (m_pAbnormalSMV->m_nInvalidChanel[nIndex])
				{
			pCurCheckBox->setCheckState(Qt::Checked);
		} 
	else
	{
			pCurCheckBox->setCheckState(Qt::Unchecked);
		}
	}
// 	if (m_channelNum.size()>0)
// 	{
// 		QString name = "ck_channel";
// 		QString name1 ="ck_channel"; 
// 		for (int j = 1;j<=50;j++)
// 		{
// 			name1 = QString(tr("ck_channel%1").arg(j));
// 			for (int i =0;i<m_channelNum.size();i++)
// 			{
// 				name = QString(tr("ck_channel%1").arg(m_channelNum.at(i)));
// 				if (name1 ==name)
// 				{
// 					QSttCheckBox *ckbox = ui.groupBox->findChild<QSttCheckBox *>(name1);
// 					ckbox->setCheckState(Qt::Checked);
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		QString name = "ck_channel";
// 		for (int i = 1;i<=50;i++)
// 		{
// 			name = QString(tr("ck_channel%1").arg(i));
// 			QSttCheckBox *ckbox = ui.groupBox->findChild<QSttCheckBox *>(name);
// 			ckbox->setCheckState(Qt::Unchecked);
// 		}
// 	}
}

void QSmvAbnormalChannelSelect::initConnnect()
{
	connect(ui.pbn_ALlReset,SIGNAL(clicked()),this,SLOT(slot_pbn_ALlReset()));
	connect(ui.pbn_ALlNoReset,SIGNAL(clicked()),this,SLOT(slot_pbn_ALlNoReset()));
	connect(ui.pbn_Ok,SIGNAL(clicked()),this,SLOT(slot_pbn_OK()));
	connect(ui.pbn_Cancle,SIGNAL(clicked()),this,SLOT(slot_pbn_Cancle()));
}

void QSmvAbnormalChannelSelect::slot_pbn_ALlReset()
{
	QString name = "ck_channel";
	for (int i = 1;i<=50;i++)
	{
		name = QString(tr("ck_channel%1").arg(i));
		QSttCheckBox *ckbox = ui.groupBox->findChild<QSttCheckBox *>(name);
		ckbox->setCheckState(Qt::Checked);
	}
}

void QSmvAbnormalChannelSelect::slot_pbn_ALlNoReset()
{
	QString name = "ck_channel";
	for (int i = 1;i<=50;i++)
	{
		name = QString(tr("ck_channel%1").arg(i));
		QSttCheckBox *ckbox = ui.groupBox->findChild<QSttCheckBox *>(name);
		ckbox->setCheckState(Qt::Unchecked);
	}
}

void QSmvAbnormalChannelSelect::slot_pbn_OK()
{
	QList<int> ChannelValue;
	ChannelValue.clear();
	QString name = "ck_channel";

	for (int nIndex = 0;nIndex<50;nIndex++)
	{
		name = QString(tr("ck_channel%1").arg(nIndex+1));
		QSttCheckBox *ckbox = ui.groupBox->findChild<QSttCheckBox *>(name);
		m_pAbnormalSMV->m_nInvalidChanel[nIndex] = (ckbox->checkState()==Qt::Checked);
//		if(ckbox->checkState()==Qt::Checked)
//		{
//			ChannelValue.append(ckbox->checkState()==Qt::Checked);
//		}
	}
//	emit sig_ChannelOkClicked(ChannelValue);
	close();
}

void QSmvAbnormalChannelSelect::slot_pbn_Cancle()
{
	close();
}