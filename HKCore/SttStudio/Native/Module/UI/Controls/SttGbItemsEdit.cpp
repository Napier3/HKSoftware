#include "SttGbItemsEdit.h"
#include "ui_SttGbItemsEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include <QMessageBox>
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "SttGbItemsNameSelDlg.h"
#include "SttTestCntrFrameWin.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QSttGbItemsEdit::QSttGbItemsEdit(CSttItemBase *pItems, CExBaseList *pParent, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttGbItemsEdit)
{
    ui->setupUi(this);
	InitLanguage();
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
	InitTitleLevel();
	
	if (pItems != NULL)
	{
		m_bEditMode = true;
		m_pSttItems = pItems;
	}
	else
	{
		m_bEditMode = false;
// 		CString strTime;
// 		SYSTEMTIME tm;
// 		::GetLocalTime(&tm);
// 		strTime.Format(_T("%d%d%d"), tm.wHour, tm.wMinute, tm.wSecond);
		m_pSttItems = stt_gb_new_items(NULL, /*"新分类"*/g_sLangTxt_Native_NewCat, "Items");
	}

	m_pSttParent = pParent;
	if (!m_bEditMode)
	{
		long nIndex = CalAutoIndex(m_pSttItems->m_strID);

		if (nIndex != -1 && nIndex != 0)
		{	
			//编辑模式下，不需要自动设置名称、ID
			CString strText;
			strText= m_pSttItems->m_strID + QString::number(nIndex);
			m_pSttItems->m_strID = strText;
			strText = m_pSttItems->m_strName + QString::number(nIndex);	
			m_pSttItems->m_strName = strText;
		}

		ui->m_txtTimes->setVisible(true);
		ui->m_editTimes->setVisible(true);
	}

	//南瑞要求项目标识默认即可，无需编辑
	ui->lineEdit_ID->setVisible(false);
	ui->label_ID->setVisible(false);

	ui->lineEdit_ID->setText(m_pSttItems->m_strID);
	ui->lineEdit_Name->setText(m_pSttItems->m_strName);

	if (m_pSttItems->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems* pSttItems = (CSttItems*)m_pSttItems;
		ui->m_txtTimes->setVisible(true);
		ui->m_editTimes->setVisible(true);
		ui->m_editTimes->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
		ui->m_editTimes->setText(QString::number(pSttItems->m_nTestTimes));
		ui->m_chkRptTitle->setVisible(true);
		ui->m_cmbTitleLevel->setCurrentIndex(pSttItems->m_nTitleLevel - 1);

		if (pSttItems->m_nRptTitle == 0)
		{
			ui->m_chkRptTitle->setCheckState(Qt::Unchecked);
			ui->m_cmbTitleLevel->setVisible(false);
			ui->m_txtTitleLevel->setVisible(false);
		}
		else
		{
			ui->m_chkRptTitle->setCheckState(Qt::Checked);
			ui->m_cmbTitleLevel->setVisible(true);
			ui->m_txtTitleLevel->setVisible(true);
		}
	}
	else
	{
		ui->m_txtTimes->setVisible(false);
		ui->m_editTimes->setVisible(false);
		ui->m_chkRptTitle->setVisible(false);
		ui->m_cmbTitleLevel->setVisible(false);
		ui->m_txtTitleLevel->setVisible(false);
	}

	ui->m_chk_AutoUpdateItemName->setVisible(false);
	connect(ui->m_Btn_OK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
	connect(ui->m_Btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
}

QSttGbItemsEdit::~QSttGbItemsEdit()
{
    delete ui;
}

long QSttGbItemsEdit::CalAutoIndex(const CString& strID)
{
	if(m_pSttParent == NULL)
	{
		return -1;
	}

	if (m_pSttParent->FindByID(strID) == NULL)
	{
		return 0;
	}

	//计算第一个不存在的ID-Index
	long nIndex = 1;
	CString strTempID = strID + QString::number(nIndex);

	while(m_pSttParent->FindByID(strTempID) != NULL)
	{
		nIndex++;
		strTempID = strID + QString::number(nIndex);
	}

	return nIndex;
}

void QSttGbItemsEdit::InitTitleLevel()
{
	ui->m_cmbTitleLevel->clear();
	CString strText;

	for (int nIndex=1; nIndex<6; nIndex++)
	{
		strText.Format(_T("%d"), nIndex);
		ui->m_cmbTitleLevel->addItem(strText);
	}

	ui->m_cmbTitleLevel->setCurrentIndex(1);
}

void QSttGbItemsEdit::slot_OKClick()
{
	CString strID, strName, strTimes;
	strID = ui->lineEdit_ID->text();
	strName = ui->lineEdit_Name->text();
	strTimes = ui->m_editTimes->text();

	long nRptTitle = 0;
	long nTitleLevel = ui->m_cmbTitleLevel->currentIndex() + 1;

	if (Qt::Checked == ui->m_chkRptTitle->checkState())
	{
		nRptTitle = 1;
	}
	else
	{
		nRptTitle = 0;
	}

	if (m_bEditMode)
	{//编辑模式下，数据没有改变，就不处理
		if (strName == m_pSttItems->m_strName
			&& strID == m_pSttItems->m_strID)
		{
			if(ui->m_editTimes->isVisible())
			{
				CSttItems* pSttItems = (CSttItems*)m_pSttItems;
				if(strTimes == QString::number(pSttItems->m_nTestTimes)
					&& pSttItems->m_nRptTitle == nRptTitle
					&& pSttItems->m_nTitleLevel == nTitleLevel)
				{
					reject();
					return;
				}
			}
			else
			{
				reject();
				return;
			}
		}
	}

	CExBaseObject *pFind_ID = m_pSttParent->FindByID(strID);
	CExBaseObject *pFind_Name = m_pSttParent->FindByName(strName);
	CString strMsg;

	if (m_bEditMode)
	{
		if (pFind_Name != NULL && pFind_Name != m_pSttItems)
		{
			strMsg = /*"存在相同名称的项目"*/g_sLangTxt_Native_ProjSameExists;
		}

		if (pFind_ID != NULL && pFind_ID != m_pSttItems)
		{
			strMsg = /*"存在相同ID的项目"*/g_sLangTxt_Native_ProjSameIDExists;
		}
	}
	else
	{
		if (pFind_Name != NULL)
		{
			strMsg = /*"存在相同名称的项目"*/g_sLangTxt_Native_ProjSameExists;
		}

		if (pFind_ID != NULL)
		{
			strMsg =  /*"存在相同ID的项目"*/g_sLangTxt_Native_ProjSameIDExists;
		}
	}

	if (strMsg.GetLength() > 0)
	{
		CXMessageBox::information(this, "", strMsg, QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	m_pSttItems->m_strName = strName;
	m_pSttItems->m_strID = strID;

	if (m_pSttItems->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems* pSttItems = (CSttItems*)m_pSttItems;
		pSttItems->m_nTestTimes = ui->m_editTimes->text().toInt();
		pSttItems->m_nTitleLevel = nTitleLevel;
		pSttItems->m_nRptTitle = nRptTitle;
	}
		
	if (!m_bEditMode)
	{
		m_pSttParent->AddNewChild(m_pSttItems);
	}

	accept();
}

void QSttGbItemsEdit::slot_CancelClick()
{
	if (!m_bEditMode)
	{//新建方式，取消则删除对象
		delete m_pSttItems;
	}

	reject();
}

//此处不修改m_pSttItems本身的属性，在点击“确认”按钮中，需要判断属性是否发生改变
void QSttGbItemsEdit::on_m_chkRptTitle_clicked()
{
	CSttItems *pSttItems = (CSttItems *)m_pSttItems;

	if (Qt::Checked ==ui->m_chkRptTitle->checkState() )
	{
// 		pSttItems->m_nRptTitle = 1;
// 		int nIndex = ui->m_cmbTitleLevel->currentIndex();
// 		pSttItems->m_nTitleLevel = nIndex + 1;

		ui->m_txtTitleLevel->setVisible(true);
		ui->m_cmbTitleLevel->setVisible(true);
	}
	else
	{
//		pSttItems->m_nRptTitle = 0;

		ui->m_txtTitleLevel->setVisible(false);
		ui->m_cmbTitleLevel->setVisible(false);
	}
}

void QSttGbItemsEdit::on_m_Btn_SelName_clicked()
{
	QSttGbItemsNameSelDlg dlg;

	if (dlg.exec() == 0)
	{
		return;
	}

	long nIndex = CalAutoIndex(dlg.m_strID);
	CString strTextID = dlg.m_strID;
	CString strTextName = dlg.m_strName;

	if (nIndex != -1 && nIndex != 0)
	{
		strTextID = dlg.m_strID + QString::number(nIndex);
		strTextName = dlg.m_strName + QString::number(nIndex);	
	}

	ui->lineEdit_ID->setText(strTextID);
	ui->lineEdit_Name->setText(strTextName);
}

void QSttGbItemsEdit::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->label_Name,g_sLangTxt_Native_ProjName,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtTimes,g_sLangTxt_numbertest,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtTitleLevel,g_sLangTxt_Native_TitleLvl,XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget_Txt(ui->m_Btn_SelName,g_sLangTxt_Select,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_OK,g_sLangTxt_Native_Confm,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);




	xlang_SetLangStrToWidget_Txt(ui->m_chk_AutoUpdateItemName,g_sLangTxt_Native_TestCntGt1AutoUpdtProjName,XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget_Txt(ui->m_chkRptTitle,g_sLangTxt_Native_NameWordTitle,XLang_Ctrls_QCheckBox);
}
