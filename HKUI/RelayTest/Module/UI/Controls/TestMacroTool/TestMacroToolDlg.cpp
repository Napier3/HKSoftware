#include "TestMacroToolDlg.h"
#include "ui_TestMacroToolDlg.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../SttGlobalDef.h"
#include "../../../SttTestSysGlobalPara.h"
#include "../../Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"

#include "../../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QTestMacroToolDlg::QTestMacroToolDlg(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QTestMacroToolDlg)
{
    ui->setupUi(this);
	InitLanguage();
	m_nRepeatTimes = 1;
	m_nRptTitle = 0;
	m_nTitleLevel = 1;
	m_pCurrentSelGbItem = NULL;
	m_pCurrentSelTest = NULL;
	m_pLastTreeBtnClicked = NULL;
	m_pLastTableBtnClicked = NULL;
	m_font = font;

	CString strConfig = _P_GetConfigPath();
	strConfig += "TestMacroToolBar.xml";

	CClassDefMngrXmlRWKeys::Create();

	m_pTestMacroToolBar = new CTestMacroToolBar;
	m_pTestMacroToolBar->OpenXmlFile(strConfig, CClassDefMngrXmlRWKeys::g_pXmlKeys);
	//2024 09-13 zhouyangyong 多语言处理
#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(m_pTestMacroToolBar, _T("TestMacroToolBar.xml"));
#endif
	ui->m_tableTest->setStyleSheet("background-color:white;");
	ui->m_editTimes->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));

	InitConnect();
	EnableAddBtns(false);
	UpdateBtnTree(m_pTestMacroToolBar);
	InitTreeBtn();
	InitCmbTitleLevel();
	ui->m_chkRptTitle->setCheckState(Qt::Checked);
	ui->m_cmbTitleLevel->setVisible(true);
}

QTestMacroToolDlg::~QTestMacroToolDlg()
{
    delete ui;
	delete m_pTestMacroToolBar;
	CClassDefMngrXmlRWKeys::Release();
}

void QTestMacroToolDlg::InitConnect()
{
	connect(ui->m_btnClose, SIGNAL(clicked(bool)), this, SLOT(OnBtnCloseClick(bool)));
	connect(ui->m_btnAddAfter, SIGNAL(clicked(bool)), this, SLOT(OnBtnAddAfterClick(bool)));
	connect(ui->m_btnAddBefore, SIGNAL(clicked(bool)), this, SLOT(OnBtnAddBeforeClick(bool)));
	connect(ui->m_btnAddChild, SIGNAL(clicked(bool)), this, SLOT(OnBtnAddChildClick(bool)));
}

void QTestMacroToolDlg::InitTreeBtn()
{
	QTreeWidgetItem* pItem = ui->m_treeTest->topLevelItem(0);
	if(pItem)
	{
		QTestMacroToolButton* pBtn = (QTestMacroToolButton*)ui->m_treeTest->itemWidget(pItem, 0);
		pBtn->SendClickSig();
	}
}

QTestMacroToolButton* QTestMacroToolDlg::CreateItem(const CString strName, const CString strPic, QSize sizeBtn, QSize sizeIcon)
{
	QTestMacroToolButton* pBtn = new QTestMacroToolButton;
	pBtn->setText(strName);
	if(strPic.GetLength())
	{
		CString strIcon = _P_GetResourcePath();
		strIcon += strPic;
		pBtn->setIcon(QIcon(QPixmap(strIcon)));
		pBtn->setIconSize(sizeIcon);
		pBtn->setFixedSize(sizeBtn);
		pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	}
	return pBtn;
}

void QTestMacroToolDlg::InitCmbTitleLevel()
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

CString QTestMacroToolDlg::GetCurSelTestName()
{
	if(m_pLastTableBtnClicked)
	{
		CExBaseList* pData = (CExBaseList*)m_pLastTableBtnClicked->m_pData;
		return pData->m_strName;
	}

	return CString("");
}

CString QTestMacroToolDlg::GetCurSelTestID()
{
	if(m_pLastTableBtnClicked)
	{
		CExBaseList* pData = (CExBaseList*)m_pLastTableBtnClicked->m_pData;
		return pData->m_strID;
	}

	return CString("");
}

void QTestMacroToolDlg::EnableAddBtns(bool bEnable)
{
	//暂时不增加添加至前后的选项
	ui->m_btnAddAfter->setEnabled(false);
	ui->m_btnAddBefore->setEnabled(false);
	ui->m_btnAddChild->setEnabled(bEnable);
}

void QTestMacroToolDlg::ClearLayout(QLayout* pLayout)
{
	QLayoutItem *child;
	while ((child = pLayout->takeAt(0)) != 0)
	{
		//setParent为NULL，防止删除之后界面不消失
		if(child->widget())
		{
			child->widget()->setParent(NULL);
		}
		delete child;
	}
	m_pLastTableBtnClicked = NULL;
	EnableAddBtns(false);
}

void QTestMacroToolDlg::UpdateBtnTable(CExBaseList* pList)
{
	if(!pList)
	{
		return;
	}

	QGridLayout* pLayout = (QGridLayout*)ui->m_tableTest->layout();

	ClearLayout(pLayout);

	POS pos = pList->GetHeadPosition();
	long nCol = 0;
	while (pos)
	{
		CExBaseList* pData = (CExBaseList*)pList->GetNext(pos);

		CString strPic;
		if(pData->GetClassID() == MNGRCLASSID_CTESTMACROREF)
		{						    
			CTestMacroRef* pTestRef = (CTestMacroRef*)pData;
			strPic = pTestRef->m_strPic;
		}
		else if (pData->GetClassID() == MNGRCLASSID_CCOMMCMDREF)
		{
			CCommcmdRef* pComRef = (CCommcmdRef*)pData;
			strPic = pComRef->m_strPic;
		}

		long nRow = pLayout->rowCount() - 1;
		if(nCol == 4)
		{
			nRow++;
			nCol = 0;
		}

		QTestMacroToolButton* pBtn = CreateItem(pData->m_strName, strPic, QSize(140, 140), QSize(80, 80));
		pBtn->m_pData = pData;
		pBtn->setStyleSheet("QToolButton{border-style:flat;background:transparent;}"
			"QToolButton:checked{background-color:rgb(200,200,200); border-radius:6px;}");
		connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(OnTableBtnClick(bool)));

		pLayout->addWidget(pBtn, nRow, nCol);
		nCol++;
	}
}

void QTestMacroToolDlg::UpdateBtnTree(CExBaseList* pList, QTreeWidgetItem* pParentItem)
{
	if(!pList)
	{
		return;
	}

	POS pos = pList->GetHeadPosition();
	while (pos)
	{
		CExBaseList* pTempList = (CExBaseList*)pList->GetNext(pos);
		if(pTempList->GetClassID() == MNGRCLASSID_CTESTMACROGROUP)
		{
			CTestMacroGroup* pGroup = (CTestMacroGroup*)pTempList;
			QTestMacroToolButton* pBtn = CreateItem(pGroup->m_strName, pGroup->m_strPic, QSize(110, 110), QSize(60, 60));
			pBtn->setStyleSheet("QToolButton{border-style:flat;background:transparent;}"
				"QToolButton:checked{background-color:rgb(200,200,200); border-radius:6px;}");
			QTreeWidgetItem* pItem = pParentItem;
			if(pItem)
			{
				pItem = new QTreeWidgetItem;
				pParentItem->addChild(pItem);
				ui->m_treeTest->setItemWidget(pItem, 0, pBtn);
			}
			else
			{
				pItem = new QTreeWidgetItem;
				ui->m_treeTest->addTopLevelItem(pItem);
				ui->m_treeTest->setItemWidget(pItem, 0, pBtn);
			}
			pBtn->m_pItem = pItem;

			if(pGroup->FindByClassID(MNGRCLASSID_CTESTMACROGROUP))
			{
				UpdateBtnTree(pGroup, pItem);
				connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(OnTreeBtnExpand(bool)));
			}
			else
			{
				pBtn->m_pData = pGroup;
				connect(pBtn, SIGNAL(clicked(bool)), this, SLOT(OnTreeBtnClick(bool)));
			}
		}
	}
}

void QTestMacroToolDlg::OnTreeBtnClick(bool bChecked)
{
	QTestMacroToolButton* pBtn = (QTestMacroToolButton*)sender();
	CTestMacroGroup* pList = (CTestMacroGroup*)pBtn->m_pData;

	if(pBtn != m_pLastTreeBtnClicked && m_pLastTreeBtnClicked)
	{
		m_pLastTreeBtnClicked->setChecked(false);
	}

	pBtn->setCheckable(true);
	pBtn->setChecked(true);
	m_pLastTreeBtnClicked = pBtn;

	if(m_pLastTreeBtnClicked->m_pData->m_strID == "TestAppCtrl"
		|| m_pLastTreeBtnClicked->m_pData->m_strID == "RelayCtrl")
	{
		ui->m_editTimes->setVisible(false);
		ui->m_txtTimes->setVisible(false);
		ui->m_chkRptTitle->setVisible(false);
		ui->m_txtTitleLevel->setVisible(false);
		ui->m_cmbTitleLevel->setVisible(false);
	}
	else
	{
		ui->m_editTimes->setVisible(true);
		ui->m_txtTimes->setVisible(true);	

		ui->m_chkRptTitle->setVisible(true);

		if (Qt::Checked == ui->m_chkRptTitle->checkState())
		{
			ui->m_cmbTitleLevel->setVisible(true);
			ui->m_txtTitleLevel->setVisible(true);
		}
		else
		{
			ui->m_cmbTitleLevel->setVisible(false);
			ui->m_txtTitleLevel->setVisible(false);
		}
	}

	UpdateBtnTable(pList);
}

void QTestMacroToolDlg::OnTreeBtnExpand(bool bChecked)
{
	QTestMacroToolButton* pBtn = (QTestMacroToolButton*)sender();
	QTreeWidgetItem* pItem = pBtn->m_pItem;
	if(ui->m_treeTest->isItemExpanded(pItem))
	{
		ui->m_treeTest->collapseItem(pItem);
	}
	else
	{
		ui->m_treeTest->expandItem(pItem);
		ui->m_treeTest->scrollToBottom();
	}
}

void QTestMacroToolDlg::OnTableBtnClick(bool bChecked)
{
	QTestMacroToolButton* pBtn = (QTestMacroToolButton*)sender();

	if(pBtn != m_pLastTableBtnClicked && m_pLastTableBtnClicked)
	{
		m_pLastTableBtnClicked->setChecked(false);
	}

	pBtn->setCheckable(true);
	pBtn->setChecked(true);

	m_pLastTableBtnClicked = pBtn;

	m_pCurrentSelTest = pBtn->m_pData;
	if(m_pCurrentSelTest->GetClassID() == MNGRCLASSID_CTESTMACROREF)
	{
		long nIndex = CalAutoIndex(m_pCurrentSelTest->m_strID);
		if (nIndex == 0)
		{
			m_strItemsID = m_pCurrentSelTest->m_strID;
			ui->m_editName->setText(m_pCurrentSelTest->m_strName);
		}
		else if(nIndex != -1)
		{
			m_strItemsID = m_pCurrentSelTest->m_strID + QString::number(nIndex);
			CString strText = m_pCurrentSelTest->m_strName + QString::number(nIndex);
			ui->m_editName->setText(strText);		
		}

		CSttMacroTestUI_TestMacroUI *pUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(m_pCurrentSelTest->m_strID);
		if ( pUI == NULL)
		{
			EnableAddBtns(false);
			CLogPrint::LogString(XLOGLEVEL_TRACE, /*_T("该功能暂不支持……")*/g_sLangTxt_Native_NotSupportFeature.GetString());
			return;
		}

		CString strRepeatTimes;
		strRepeatTimes.Format(_T("%d"), pUI->m_nDefaultRepeatTimes);
		ui->m_editTimes->setText(strRepeatTimes);

		if (m_pCurrentSelTest->m_strID == STT_CMD_TYPE_SYSTEM_IECConfig && g_oSystemParas.m_nHasDigital == 0)
		{
			EnableAddBtns(false);
			CLogPrint::LogString(XLOGLEVEL_TRACE, /*_T("系统参数设置中，未勾选数字量，不能创建IEC61850配置……")*/g_sLangTxt_IEC_IEC61850.GetString());
			return;
		}
	}
	else if(m_pCurrentSelTest->GetClassID() == MNGRCLASSID_CCOMMCMDREF)
	{
		m_strItemsID = m_pCurrentSelTest->m_strID;
		m_strItemsName = m_pCurrentSelTest->m_strName;
	}
	EnableAddBtns(true);
}

void QTestMacroToolDlg::OnBtnCloseClick(bool bChecked)
{
	reject();
}

void QTestMacroToolDlg::OnBtnAddAfterClick(bool bChecked)
{
	m_strItemsName = ui->m_editName->text();
	m_strItemsName.trimmed();
	m_strItemsID.trimmed();
	accept();
}

void QTestMacroToolDlg::OnBtnAddBeforeClick(bool bChecked)
{
	m_strItemsName = ui->m_editName->text();
	m_strItemsName.trimmed();
	m_strItemsID.trimmed();
	accept();
}

void QTestMacroToolDlg::OnBtnAddChildClick(bool bChecked)
{
	m_strItemsName = ui->m_editName->text();
	m_strItemsName.trimmed();
	m_strItemsID.trimmed();
	if(ui->m_editTimes->isVisible() && ui->m_editTimes->text().length())
	{
		m_nRepeatTimes = ui->m_editTimes->text().toInt();
	}
	else
	{
		m_nRepeatTimes = 1;
	}

	if (Qt::Checked ==ui->m_chkRptTitle->checkState())
	{
		m_nRptTitle = 1;
	}
	else
	{
		m_nTitleLevel = 0;
	}

	m_nTitleLevel = ui->m_cmbTitleLevel->currentIndex() + 1;
	accept();
}

long QTestMacroToolDlg::CalAutoIndex(const CString& strID)
{
	if(!m_pCurrentSelGbItem)
	{
		return -1;
	}

	if (m_pCurrentSelGbItem->FindByID(strID) == NULL)
	{
		return 0;
	}

	//计算第一个不存在的ID-Index
	long nIndex = 1;
	CString strTempID = strID + QString::number(nIndex);
	while(m_pCurrentSelGbItem->FindByID(strTempID) != NULL)
	{
		nIndex++;
		strTempID = strID + QString::number(nIndex);
	}
	return nIndex;
}

void QTestMacroToolDlg::on_m_chkRptTitle_clicked()
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

void  QTestMacroToolDlg::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_btnAddChild,g_sLangTxt_Native_AddSubitem,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnAddBefore,g_sLangTxt_Native_AddBeforeItem,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnAddAfter,g_sLangTxt_Native_AddAfterItem,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnClose,g_sLangTxt_Close,XLang_Ctrls_QPushButton);

	xlang_SetLangStrToWidget_Txt(ui->m_txtTimes,g_sLangTxt_numbertest+":",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtTitleLevel,g_sLangTxt_Native_TitleLvl,XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget_Txt(ui->m_chkRptTitle,g_sLangTxt_Native_AsWordTitle,XLang_Ctrls_QCheckBox);
	

}
