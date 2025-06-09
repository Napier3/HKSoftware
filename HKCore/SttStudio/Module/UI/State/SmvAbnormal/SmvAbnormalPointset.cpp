#include "SmvAbnormalPointset.h"
#include <QVBoxLayout>
#include "stdafx.h"
#include "../../Controls/SttCheckBox.h"
#include "../../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QSmvAbnormalPointSet::QSmvAbnormalPointSet(int flag,QList<bool> &validpoint,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::X11BypassWindowManagerHint);
	headerFlag = flag;
	for (int i=0;i<validpoint.size();i++)
	{
		abnomalPointEnabled.append(validpoint.at(i));
	}

	
	this->setFixedWidth(800);
	ui.point_groupbox->setMinimumWidth(800);


	init();
	initConnect();
    InitLanguage();
}

QSmvAbnormalPointSet::~QSmvAbnormalPointSet()
{
}

void QSmvAbnormalPointSet::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.ck_point1, (g_sLangTxt_State_Oclock + "1"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point2, (g_sLangTxt_State_Oclock + "2"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point3, (g_sLangTxt_State_Oclock + "3"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point4, (g_sLangTxt_State_Oclock + "4"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point5, (g_sLangTxt_State_Oclock + "5"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point6, (g_sLangTxt_State_Oclock + "6"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point7, (g_sLangTxt_State_Oclock + "7"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point8, (g_sLangTxt_State_Oclock + "8"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point9, (g_sLangTxt_State_Oclock + "9"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point10, (g_sLangTxt_State_Oclock + "10"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point11, (g_sLangTxt_State_Oclock + "11"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point12, (g_sLangTxt_State_Oclock + "12"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point13, (g_sLangTxt_State_Oclock + "13"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point14, (g_sLangTxt_State_Oclock + "14"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point15, (g_sLangTxt_State_Oclock + "15"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point16, (g_sLangTxt_State_Oclock + "16"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point17, (g_sLangTxt_State_Oclock + "17"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point18, (g_sLangTxt_State_Oclock + "18"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point19, (g_sLangTxt_State_Oclock + "19"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point20, (g_sLangTxt_State_Oclock + "20"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point21, (g_sLangTxt_State_Oclock + "21"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point22, (g_sLangTxt_State_Oclock + "22"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point23, (g_sLangTxt_State_Oclock + "23"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point24, (g_sLangTxt_State_Oclock + "24"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point25, (g_sLangTxt_State_Oclock + "25"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point26, (g_sLangTxt_State_Oclock + "26"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point27, (g_sLangTxt_State_Oclock + "27"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point28, (g_sLangTxt_State_Oclock + "28"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point29, (g_sLangTxt_State_Oclock + "29"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point30, (g_sLangTxt_State_Oclock + "30"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point31, (g_sLangTxt_State_Oclock + "31"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point32, (g_sLangTxt_State_Oclock + "32"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point33, (g_sLangTxt_State_Oclock + "33"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point34, (g_sLangTxt_State_Oclock + "34"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point35, (g_sLangTxt_State_Oclock + "35"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point36, (g_sLangTxt_State_Oclock + "36"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point37, (g_sLangTxt_State_Oclock + "37"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point38, (g_sLangTxt_State_Oclock + "38"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point39, (g_sLangTxt_State_Oclock + "39"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point40, (g_sLangTxt_State_Oclock + "40"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point41, (g_sLangTxt_State_Oclock + "41"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point42, (g_sLangTxt_State_Oclock + "42"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point43, (g_sLangTxt_State_Oclock + "43"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point44, (g_sLangTxt_State_Oclock + "44"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point45, (g_sLangTxt_State_Oclock + "45"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point46, (g_sLangTxt_State_Oclock + "46"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point47, (g_sLangTxt_State_Oclock + "47"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point48, (g_sLangTxt_State_Oclock + "48"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point49, (g_sLangTxt_State_Oclock + "49"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point50, (g_sLangTxt_State_Oclock + "50"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point51, (g_sLangTxt_State_Oclock + "51"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point52, (g_sLangTxt_State_Oclock + "52"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point53, (g_sLangTxt_State_Oclock + "53"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point54, (g_sLangTxt_State_Oclock + "54"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point55, (g_sLangTxt_State_Oclock + "55"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point56, (g_sLangTxt_State_Oclock + "56"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point57, (g_sLangTxt_State_Oclock + "57"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point58, (g_sLangTxt_State_Oclock + "58"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point59, (g_sLangTxt_State_Oclock + "59"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point60, (g_sLangTxt_State_Oclock + "60"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point61, (g_sLangTxt_State_Oclock + "61"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point62, (g_sLangTxt_State_Oclock + "62"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point63, (g_sLangTxt_State_Oclock + "63"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point64, (g_sLangTxt_State_Oclock + "64"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point65, (g_sLangTxt_State_Oclock + "65"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point66, (g_sLangTxt_State_Oclock + "66"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point67, (g_sLangTxt_State_Oclock + "67"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point68, (g_sLangTxt_State_Oclock + "68"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point69, (g_sLangTxt_State_Oclock + "69"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point70, (g_sLangTxt_State_Oclock + "70"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point71, (g_sLangTxt_State_Oclock + "71"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point72, (g_sLangTxt_State_Oclock + "72"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point73, (g_sLangTxt_State_Oclock + "73"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point74, (g_sLangTxt_State_Oclock + "74"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point75, (g_sLangTxt_State_Oclock + "75"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point76, (g_sLangTxt_State_Oclock + "76"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point77, (g_sLangTxt_State_Oclock + "77"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point78, (g_sLangTxt_State_Oclock + "78"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point79, (g_sLangTxt_State_Oclock + "79"), XLang_Ctrls_QCheckBox);
    xlang_SetLangStrToWidget_Txt(ui.ck_point80, (g_sLangTxt_State_Oclock + "80"), XLang_Ctrls_QCheckBox);

    xlang_SetLangStrToWidget_Txt(ui.pbn_AllSelsect, g_sLangTxt_SelAll, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_SelectInvert, g_sLangTxt_Gradient_Inverse, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Ok, g_sLangTxt_OK, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Cancle, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}

void QSmvAbnormalPointSet::init()
{
	CString name;
	switch(headerFlag)
	{
	case 1:
		name = /*_T("¶ªÖ¡"*/g_sLangTxt_State_Dropframes; //lcq
		break;
	case 2:
		name = /*_T("·Éµã")*/g_sLangTxt_State_Flypoint; //lcq
		break; 
	case 3:
		name = /*_T("¶¶¶¯")*/g_sLangTxt_State_Dithering;  //lcq
		break;
	case 4:
		name = /*_T("´íÐò")*/g_sLangTxt_State_OutofOrder; //lcq
		break;
	default:
		break;
	}
	ui.point_groupbox->setTitle(name);
	initData();
}

void QSmvAbnormalPointSet::initConnect()
{
	connect(ui.pbn_AllSelsect,SIGNAL(clicked()),this,SLOT(slot_pbn_AllSelsectClicked()));
	connect(ui.pbn_SelectInvert,SIGNAL(clicked()),this,SLOT(slot_pbn_SelectInvertClicked()));
	connect(ui.pbn_Ok,SIGNAL(clicked()),this,SLOT(slot_pbn_OkClicked()));
	connect(ui.pbn_Cancle,SIGNAL(clicked()),this,SLOT(slot_pbn_CancleClicked()));
}

void QSmvAbnormalPointSet::initData()
{
	int num = 80;
	QString name = "ck_point";
	for (int i = 0; i<=num-1;i++)
	{
		name = QString(tr("ck_point%1").arg(i+1));
		QSttCheckBox*ckbox = ui.point_groupbox->findChild<QSttCheckBox *>(name);
		if (abnomalPointEnabled.at(i))
		{
			ckbox->setCheckState(Qt::Checked);
		}
		else
		{
			ckbox->setCheckState(Qt::Unchecked);
		}
	}
}

void QSmvAbnormalPointSet::slot_pbn_AllSelsectClicked()
{
	QString name = "ck_point";
	for (int i = 1;i<=80;i++)
	{
		name = QString(tr("ck_point%1").arg(i));
		QSttCheckBox *ckbox = ui.point_groupbox->findChild<QSttCheckBox *>(name);
		ckbox->setCheckState(Qt::Checked);
	}
}

void QSmvAbnormalPointSet::slot_pbn_SelectInvertClicked()
{
	QString name = "ck_point";
	for (int i = 1;i<=80;i++)
	{
		name = QString(tr("ck_point%1").arg(i));
		QSttCheckBox *ckbox = ui.point_groupbox->findChild<QSttCheckBox *>(name);
		if (ckbox->checkState()==Qt::Checked)
		{
			ckbox->setCheckState(Qt::Unchecked);
		}
		else
		{
			ckbox->setCheckState(Qt::Checked);
		}
	}
}

void QSmvAbnormalPointSet::slot_pbn_OkClicked()
{
	QList<bool> templist;
	templist.clear();
	QString name = "ck_point";
	for (int i = 1; i<=80;i++)
	{
		name = QString(tr("ck_point%1").arg(i));
		QSttCheckBox *ckbox = ui.point_groupbox->findChild<QSttCheckBox *>(name);
		if (ckbox->checkState()==Qt::Checked)
		{
			templist.append(1);
		}
		else
		{
			templist.append(0);
		}
	}
	emit sig_validPoint(templist);
	close();
}

void QSmvAbnormalPointSet::slot_pbn_CancleClicked()
{
	close();
}