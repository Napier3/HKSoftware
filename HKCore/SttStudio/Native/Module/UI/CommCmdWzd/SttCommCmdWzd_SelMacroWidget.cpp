#include "SttCommCmdWzd_SelMacroWidget.h"
#include "ui_SttCommCmdWzd_SelMacroWidget.h"
#include "..\Config\MacroTestUI\SttMacroTestUI_TestMacroUIDB.h"
#include "..\..\SttTestCtrl\SttTestAppBase.h"
#include "..\..\..\..\Module\BaseClass\QT\ExBaseListComboBox.h"
#include "SttCommCmdWzdMainWidget.h"
#include "../Controls/SttGbItemsNameSelDlg.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

//2022-09-09  lijunqing
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../SttTestCntrFrameBase.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;


void QSttCommCmdWzd_SelMacroWidget::OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (m_pTreeCtrl_Cmd != pTreeCtrl)
	{
		return;
	}

	QExBaseTreeWidgetItem *pItem = (QExBaseTreeWidgetItem*)pSelObj->m_dwItemData;
	m_pTreeCtrl_Cmd->on_slot_TreeItemChanged(pItem, 0);

	UINT nClassID = pSelObj->GetClassID();

	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDvmData *pData = (CDvmData *)pSelObj;
	CDataGroup *pParent = (CDataGroup *)pData->GetParent();

	if (pParent->m_strID == STT_CMD_PARA_CMDAFT)
	{
		return;
	}

	//对于通讯前，勾选命令后，自动勾选相应的通讯后
	CDataGroup *pAft = (CDataGroup *)m_pGbMacroGenWzd->m_pCmdCfg->FindByID(STT_CMD_PARA_CMDAFT);

	if (pAft == NULL)
	{
		return;
	}

	CDvmData *pAftData = (CDvmData *)pAft->FindByID(pSelObj->m_strID);

	if(pAftData != NULL)
	{
		pAftData->m_strValue = pData->m_strValue;
		pItem = (QExBaseTreeWidgetItem*)pAftData->m_dwItemData;

		if (pItem != NULL)
		{
			m_pTreeCtrl_Cmd->on_slot_TreeItemChanged_Aft(pItem);
		}
	}
	else 
	{
		//启动报告，对应测试后恢复的停止报告
		if (pData->m_strID == _T("RegisterReport"))
		{
			pAftData = (CDvmData *)pAft->FindByID(_T("UnRegisterReport"));

			if(pAftData != NULL)
			{
				pAftData->m_strValue = pData->m_strValue;
				pItem = (QExBaseTreeWidgetItem*)pAftData->m_dwItemData;

				if (pItem != NULL)
				{
					m_pTreeCtrl_Cmd->on_slot_TreeItemChanged_Aft(pItem);
				}
			}
		}
	}
}

void QSttCommCmdWzd_SelMacroWidget::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (pTreeCtrl == m_pTreeCtrl_Macro)
	{
		UINT nClassID = pSelObj->GetClassID();

		if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF)
		{
			m_pCurrUIRef = (CSttMacroTestUI_TestMacroUIRef*)pSelObj;
			m_pGbMacroGenWzd->m_strTestMacroUI = m_pCurrUIRef->m_strID;
		}
		else
		{
			m_pCurrUIRef = NULL;
			m_pGbMacroGenWzd->m_strTestMacroUI = "";
		}

		if (m_pCurrUIRef != NULL)
		{
			long nIndex = CalAutoIndex(m_pCurrUIRef->m_strID);

			if (nIndex == 0)
			{
				ui->lineEdit_ID->setText(m_pCurrUIRef->m_strID);
				ui->lineEdit_Name->setText(m_pCurrUIRef->m_strName);
			}
			else if(nIndex != -1)
			{
				CString strText = m_pCurrUIRef->m_strID + QString::number(nIndex);
				ui->lineEdit_ID->setText(strText);
				strText = m_pCurrUIRef->m_strName + QString::number(nIndex);
				ui->lineEdit_Name->setText(strText);		
			}

			long nRepeatTimes = m_pCurrUIRef->GetDefaultRepeatTimes();
			CString strRepeatTimes;
			strRepeatTimes.Format(_T("%d"), nRepeatTimes);
			ui->m_editTimes->setText(strRepeatTimes);
		}

		EnableBtns();
		on_slot_CmdTreeItemChanged(NULL);
	}
}

BOOL QSttCommCmdWzd_SelMacroWidget::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)
{
	return FALSE;
}

QSttCommCmdWzd_SelMacroWidget::QSttCommCmdWzd_SelMacroWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCommCmdWzd_SelMacroWidget)
{
	m_nRptTitle = 1;
	m_nTitleLevel = 1;
    ui->setupUi(this);
	InitLanguage();
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_pCurrUIRef = NULL;
	m_font = font;
	m_pTestMacroUIMngr = (CSttMacroTestUI_TestMacroUIMngr *)CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIMngr()->CloneEx(TRUE, TRUE);
	g_theTestCntrFrame->InitTestMacroUI_by_DeviceType(m_pTestMacroUIMngr);
	UI_SetFont();

	//南瑞要求项目标识默认即可，无需编辑
	ui->label_ItemID->setVisible(false);
	ui->lineEdit_ID->setVisible(false);
	
	m_pTreeCtrl_Macro = new CExBaseListTreeCtrl(this);
	m_pTreeCtrl_Macro->header()->hide();
	m_pTreeCtrl_Macro->AttachOptrInterface(this);
	m_pTreeCtrl_Macro->setFont(font);
	m_pTreeCtrl_Macro->AddClassID(MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_GROUP);
	m_pTreeCtrl_Macro->AddClassID(MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF);
	m_pTreeCtrl_Macro->ShowBaseList(m_pTestMacroUIMngr,false);

	m_pTreeCtrl_Cmd = new CTree_CommCmdWzd(this);
	m_pTreeCtrl_Cmd->setRootIsDecorated(false);
	m_pTreeCtrl_Cmd->setStyleSheet("QTreeView::branch {image:none;}");
	m_pTreeCtrl_Cmd->header()->hide();
	m_pTreeCtrl_Cmd->AttachOptrInterface(this);
	m_pTreeCtrl_Cmd->setFont(font);
	m_pTreeCtrl_Cmd->AddClassID(DTMCLASSID_CDATAGROUP);
	m_pTreeCtrl_Cmd->AddClassID(DVMCLASSID_CDVMDATA);

	ui->horizontalLayout->insertWidget(0,m_pTreeCtrl_Macro);
	ui->verticalLayout_Step->insertWidget(0,m_pTreeCtrl_Cmd);
	ui->m_editTimes->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
	ui->m_editTimes->setText("1");
	ui->m_chkRptTitle->setCheckState(Qt::Checked);
	InitCmbTitleLevel();

// 	m_cmbTestClass = new QScrollComboBox;
// 	m_cmbTestClass->setObjectName("m_cmbTestClass");
	ComboBox_SetSize(font.pixelSize(), 20, ui->m_cmbTestClass);
// 	m_cmbTestClass->SetDefaultVisibleItems();
// 	connect(m_cmbTestClass, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cmbTestClass_currentIndexChanged(int)));
// 	ui->horizontalLayout_Btns->insertWidget(1, m_cmbTestClass);

	//InitTestClass();

	ui->m_cmbTestClass->setVisible(false);
	ui->label_TestClass->setVisible(false);
	connect(m_pTreeCtrl_Cmd, SIGNAL(sig_CmdTreeItemChanged(QExBaseTreeWidgetItem*)), this, SLOT(on_slot_CmdTreeItemChanged(QExBaseTreeWidgetItem*)));
}

QSttCommCmdWzd_SelMacroWidget::~QSttCommCmdWzd_SelMacroWidget()
{
	delete ui;

// 	if(m_cmbTestClass)
// 	{
// 		delete m_cmbTestClass;
// 		m_cmbTestClass = NULL;
// 	}

	if(m_pTreeCtrl_Cmd)
	{
		delete m_pTreeCtrl_Cmd;
		m_pTreeCtrl_Cmd = NULL;
	}

	if(m_pTreeCtrl_Macro)
	{
		delete m_pTreeCtrl_Macro;
		m_pTreeCtrl_Macro = NULL;
	}

	if (m_pTestMacroUIMngr != NULL)
	{
		delete m_pTestMacroUIMngr;
	}
}

void QSttCommCmdWzd_SelMacroWidget::ShowGbMacroGenWzd()
{
	m_pGbMacroGenWzd = gb_wzd_curr_macro_gen();
	m_pTreeCtrl_Cmd->ShowBaseList(m_pGbMacroGenWzd->m_pCmdCfg,false);

	//2022-10-4 lijunqing  初始化测试分类
	long nIndex = g_theGbSmartGenWzd->m_pTestClass->FindIndexByID(m_pGbMacroGenWzd->m_strTestClass);
	ex_InsertChildreComboBox(g_theGbSmartGenWzd->m_pTestClass, ui->m_cmbTestClass);

	if (nIndex < 0)
	{
		nIndex = 0;
	}

	ui->m_cmbTestClass->setCurrentIndex(nIndex);
}

BOOL QSttCommCmdWzd_SelMacroWidget::IsHasCmdSelected()
{
	if (m_pGbMacroGenWzd == NULL)
	{
		return FALSE;
	}

	if (m_pGbMacroGenWzd->m_pCmdCfg == NULL)
	{
		return FALSE;
	}

	POS pos = m_pGbMacroGenWzd->m_pCmdCfg->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pGrp = (CDataGroup *)m_pGbMacroGenWzd->m_pCmdCfg->GetNext(pos);

		if (pGrp->m_strValue == _T("0") || pGrp->m_strID == STT_CMD_PARA_CMDAFT)
		{
			continue;
		}

		POS pos2 = pGrp->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDvmData *pData = (CDvmData *)pGrp->GetNext(pos2);

// 			if(pData->m_strID == "ReadSetting"
// 				|| pData->m_strID == "ReadEna")
// 			{
// 				continue;
// 			}

			if (pData->m_strValue == _T("1"))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL QSttCommCmdWzd_SelMacroWidget::IsHasWriteCmdSelected()
{
	if (m_pGbMacroGenWzd == NULL)
	{
		return FALSE;
	}

	if (m_pGbMacroGenWzd->m_pCmdCfg == NULL)
	{
		return FALSE;
	}

	POS pos = m_pGbMacroGenWzd->m_pCmdCfg->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pGrp = (CDataGroup *)m_pGbMacroGenWzd->m_pCmdCfg->GetNext(pos);

		if (pGrp->m_strValue == _T("0") || pGrp->m_strID == STT_CMD_PARA_CMDAFT)
		{
			continue;
		}

		POS pos2 = pGrp->GetHeadPosition();

		while (pos2 != NULL)
		{
			CDvmData *pData = (CDvmData *)pGrp->GetNext(pos2);

 			if(pData->m_strID == "WriteSetting"
 				|| pData->m_strID == "WriteEna"
				|| pData->m_strID == "WriteParameter")
 			{
				//目前仅考虑修改定值、投退软压板、修改装置参数
				if (pData->m_strValue == _T("1"))
				{
					return TRUE;
				}
 			}
		}
	}

	return FALSE;
}

long QSttCommCmdWzd_SelMacroWidget::CalAutoIndex(const CString& strID)
{
	QSttCommCmdWzdMainWidget *pMainWnd = (QSttCommCmdWzdMainWidget *)this->parentWidget();
	CExBaseList *pParentItem = pMainWnd->m_pParentItem;

	if(!pParentItem)
	{
		return -1;
	}

	if (pParentItem->FindByID(strID) == NULL)
	{
		return 0;
	}

	//计算第一个不存在的ID-Index
	long nIndex = 1;
	CString strTempID = strID + QString::number(nIndex);
	while(pParentItem->FindByID(strTempID) != NULL)
	{
		nIndex++;
		strTempID = strID + QString::number(nIndex);
	}
	return nIndex;
}

long QSttCommCmdWzd_SelMacroWidget::GetRepeatTimes()
{
	return ui->m_editTimes->text().toInt();
}

long QSttCommCmdWzd_SelMacroWidget::GetRptTitle()
{
	return m_nRptTitle;
}

long QSttCommCmdWzd_SelMacroWidget::GetTitleLevel()
{
	return m_nTitleLevel;
}

BOOL QSttCommCmdWzd_SelMacroWidget::IsSelMacroHasErrEvalute()
{
	if (m_pCurrUIRef == NULL)
	{
		return FALSE;
	}

	if (m_pCurrUIRef->m_strID == "Iec61850Config"
		|| m_pCurrUIRef->m_strID == "SystemConfig"
		|| m_pCurrUIRef->m_strID == "ChMapsConfig"
		|| m_pCurrUIRef->m_strID == "ManualTest"
		|| m_pCurrUIRef->m_strID == "HarmTest"
		|| m_pCurrUIRef->m_strID == "SequenceManuTest")
	{
		return FALSE;
	}

	return TRUE;
}

void QSttCommCmdWzd_SelMacroWidget::UI_SetFont()
{
	ui->label_TestClass->setFont(m_font);
	ui->label_ItemName->setFont(m_font);
	ui->label_ItemID->setFont(m_font);
	ui->lineEdit_ID->setFont(m_font);
	ui->lineEdit_Name->setFont(m_font);
	ui->m_btnSelItemsName->setFont(m_font);
}


void QSttCommCmdWzd_SelMacroWidget::EnableBtns()
{
	QSttCommCmdWzdMainWidget *pMainWnd = (QSttCommCmdWzdMainWidget *)this->parentWidget();

	QPalette palette;
	palette.setColor(QPalette::Base,Qt::white);
	palette.setColor(QPalette::Text,Qt::black);
	ui->lineEdit_Name->setPalette(palette);
	ui->lineEdit_ID->setPalette(palette);

	QPalette palette1;
	palette1.setColor(QPalette::Base,Qt::white);
	palette1.setColor(QPalette::Text,Qt::red);

	if (pMainWnd->m_pParentItem != NULL)
	{
		if (pMainWnd->m_pParentItem->FindByID(m_pGbMacroGenWzd->m_strItemsID) != NULL)
		{
			ui->lineEdit_ID->setPalette(palette1);
		}

		if (pMainWnd->m_pParentItem->FindByName(m_pGbMacroGenWzd->m_strItemsName) != NULL)
		{
			ui->lineEdit_Name->setPalette(palette1);
		}
	}

	pMainWnd->EnableBtns(this);
}

void QSttCommCmdWzd_SelMacroWidget::InitCmbTitleLevel()
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

void QSttCommCmdWzd_SelMacroWidget::on_m_cmbTestClass_currentIndexChanged(int index)
{
	if (index < 0)
	{
		//index = ui->m_cmbTestClass->currentIndex();
		index = 0;
	}

	CDataGroup *pTestClass = (CDataGroup*)g_theGbSmartGenWzd->m_pTestClass->GetAtIndex(index);
	m_pGbMacroGenWzd->m_strTestClass = pTestClass->m_strID;
	EnableBtns();
}

void QSttCommCmdWzd_SelMacroWidget::on_lineEdit_Name_textChanged(const QString &arg1)
{
	m_pGbMacroGenWzd->m_strItemsName = arg1;
	m_pGbMacroGenWzd->m_strItemsName.trimmed();
	EnableBtns();
}

void QSttCommCmdWzd_SelMacroWidget::on_lineEdit_ID_textChanged(const QString &arg1)
{
	m_pGbMacroGenWzd->m_strItemsID = arg1;
	m_pGbMacroGenWzd->m_strItemsID.trimmed();
	EnableBtns();
}
void QSttCommCmdWzd_SelMacroWidget::on_m_btnSelItemsName_clicked()
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

void QSttCommCmdWzd_SelMacroWidget::on_slot_CmdTreeItemChanged(QExBaseTreeWidgetItem* pTreeItem)
{
	QSttCommCmdWzdMainWidget *pMainWnd = (QSttCommCmdWzdMainWidget *)this->parentWidget();

	if ( (! IsHasWriteCmdSelected()) && (! IsSelMacroHasErrEvalute()))
	{
		pMainWnd->SetNextBtnText(/*_T("完成")*/g_sLangTxt_Native_Enter);
	}
	else
	{
		pMainWnd->SetNextBtnText(/*_T("下一步")*/g_sLangTxt_NextStep);
	}
}

void QSttCommCmdWzd_SelMacroWidget::on_m_chkRptTitle_clicked()
{
	if (Qt::Checked == ui->m_chkRptTitle->checkState())
	{
		m_nRptTitle = 1;
		ui->m_cmbTitleLevel->setVisible(true);
		ui->m_txtTitleLevel->setVisible(true);
	}
	else
	{
		m_nTitleLevel = 0;
		ui->m_cmbTitleLevel->setVisible(false);
		ui->m_txtTitleLevel->setVisible(false);
	}
}

void QSttCommCmdWzd_SelMacroWidget::on_m_cmbTitleLevel_currentIndexChanged(int index)
{
	m_nTitleLevel = index + 1;
}

void QSttCommCmdWzd_SelMacroWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}
void QSttCommCmdWzd_SelMacroWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->label_TestClass,g_sLangTxt_Native_TestCat+":",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtTimes,g_sLangTxt_numbertest+":",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtTitleLevel,g_sLangTxt_Native_TitleLvl+":",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_ItemName,g_sLangTxt_Native_ProjName+":",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_ItemID,g_sLangTxt_Native_ProjIdent+":",XLang_Ctrls_QLabel);
	
	xlang_SetLangStrToWidget_Txt(ui->m_chkRptTitle,g_sLangTxt_Native_AsWordTitle,XLang_Ctrls_QCheckBox);

	xlang_SetLangStrToWidget_Txt(ui->m_btnSelItemsName,g_sLangTxt_Native_ModProjName,XLang_Ctrls_QPushButton);
	
}
