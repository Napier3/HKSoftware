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
	m_pSttProgDlg = NULL;
	m_font = font;
	m_bUseMutiSelect = false;

	CString strConfig = _P_GetConfigPath();
	strConfig += "TestMacroToolBar.xml";

	CClassDefMngrXmlRWKeys::Create();

	m_pTestMacroToolBar = new CTestMacroToolBar;
	m_pTestMacroToolBar->OpenXmlFile(strConfig, CClassDefMngrXmlRWKeys::g_pXmlKeys);

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
	qDeleteAll(m_listToolButton);
	m_listToolButton.clear();

    delete ui;
	delete m_pTestMacroToolBar;
	CClassDefMngrXmlRWKeys::Release();

	if (m_pSttProgDlg != NULL)
	{
		delete m_pSttProgDlg;
		m_pSttProgDlg = NULL;
	}
}

void QTestMacroToolDlg::InitData()
{
	UpdateBtnTree(m_pTestMacroToolBar);
	InitTreeBtn();
	InitCmbTitleLevel();
	ui->m_chkRptTitle->setCheckState(Qt::Checked);
	ui->m_cmbTitleLevel->setVisible(true);
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

QTestMacroToolButton* QTestMacroToolDlg::CreateItem(const CString strName, const CString strPic, QSize sizeBtn, QSize sizeIcon, bool bUseMultiSelect)
{
	QTestMacroToolButton* pBtn = new QTestMacroToolButton;
	pBtn->m_bMutiSelect = bUseMultiSelect;
	pBtn->setText(strName);
	if(strPic.GetLength())
	{
		CString strIcon = _P_GetResourcePath();
		strIcon += strPic;
		pBtn->setIcon((QPixmap(strIcon)));
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
	qDeleteAll(m_listToolButton);
	m_listToolButton.clear();

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

		QTestMacroToolButton* pBtn = CreateItem(pData->m_strName, strPic, QSize(140, 140), QSize(80, 80), m_bUseMutiSelect);
		pBtn->m_pData = pData;
		if (m_bUseMutiSelect)
		{
			bool bChecked;
			//bChecked = ((CTestMacroGroup*)pData)->m_isChecked;
			if (pData->GetClassID() == MNGRCLASSID_CTESTMACROREF)
			{
				CTestMacroRef* pTestRefData = (CTestMacroRef*)pData;
				bChecked = pTestRefData->m_isChecked;
				pBtn->setChecked(bChecked);
				m_listToolButton.append(pBtn);
				if (pTestRefData->m_isChecked)
				{
					EnableAddBtns(true);
				}
			}
			
			ui->m_editName->setEnabled(false);
		}
		else
		{
		pBtn->setStyleSheet("QToolButton{border-style:flat;background:transparent;}"
			"QToolButton:checked{background-color:rgb(200,200,200); border-radius:6px;}");
		}

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
			QTestMacroToolButton* pBtn = CreateItem(pGroup->m_strName, pGroup->m_strPic, QSize(110, 110), QSize(60, 60),false);
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

	if(pList->m_nUseMutiSelect == 0)
	{
		m_bUseMutiSelect = false;
	}
	else
	{
		m_bUseMutiSelect = true;
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

	m_pCurrentSelTest = pBtn->m_pData;

	if (!m_bUseMutiSelect)
	{
	if(pBtn != m_pLastTableBtnClicked && m_pLastTableBtnClicked)
	{
		m_pLastTableBtnClicked->setChecked(false);
	}

	pBtn->setCheckable(true);
	pBtn->setChecked(true);

	m_pLastTableBtnClicked = pBtn;

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
	else
	{
		if (m_pCurrentSelTest->GetClassID() == MNGRCLASSID_CTESTMACROREF)
		{
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

			CTestMacroRef* pMacroRef = (CTestMacroRef*)m_pCurrentSelTest;
			bool bChecked = pMacroRef->m_isChecked;

			// 切换复选框的选中状态
			pBtn->setChecked(!bChecked);
			if (pMacroRef->m_isChecked)
			{
	EnableAddBtns(true);
			}
			else
			{
				EnableAddBtns(false);

				for (int i = 0; i < m_listToolButton.size(); ++i)
				{
					CExBaseList* pList = m_listToolButton[i]->m_pData;
					if (pList->GetClassID() == MNGRCLASSID_CTESTMACROREF)
					{
						CTestMacroRef* pRef = (CTestMacroRef*)pList;
						if (pRef->m_isChecked)
						{
	EnableAddBtns(true);
						}
					}
				}
			}
		}
	}	
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

void QTestMacroToolDlg:: StartProgDlg()
{
	//CTickCount32 oTickCount;

	if (m_pSttProgDlg == NULL)
	{
		m_pSttProgDlg = new QSttProgDlg(NULL);
		//m_pSttProgDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
	}

	m_pSttProgDlg->initUI(_T("模版生成进度条"),_T("模版正在加载,请稍后..."));
	m_pSttProgDlg->setModal(false);
	m_pSttProgDlg->Start(0,30,0);
	//setEnabled(false);
	//long nDelayTimeMs = 2000;//zhouhj  2023.7.27 在普通电脑,延时2s

	//oTickCount.DoEvents(nDelayTimeMs);
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

void  QTestMacroToolDlg::GetAllSelTestID(QStringList &listTestId, QStringList &listTestName)
{
	// 遍历按钮列表并判断当前状态，如果勾选则记录ID和name
	for (int i = 0; i < m_listToolButton.size(); ++i)
	{
		CExBaseList* pList = m_listToolButton[i]->m_pData;
		if (pList->GetClassID() == MNGRCLASSID_CTESTMACROREF)
		{
			CTestMacroRef* pRef = (CTestMacroRef*)pList;
			CString strTestID;
			if (pRef->m_isChecked)
			{
				strTestID = pRef->m_strID;
				listTestId.append(strTestID);
				listTestName.append(pRef->m_strName);
			}
		}
	}
}

void  QTestMacroToolDlg::GetAllSelTestID(QStringList &listCurSelTestID, QStringList &listItemsName, QStringList &listItemsID)
{
	// 遍历m_pTestMacroToolBar并判断当前状态，如果勾选则记录ID和name
	if (!m_pTestMacroToolBar)
	{
		return;
	}

	POS pos_Group = m_pTestMacroToolBar->GetHeadPosition();
	while (pos_Group)
	{
		CExBaseList* pTempList = (CExBaseList*)m_pTestMacroToolBar->GetNext(pos_Group);
		if (pTempList->GetClassID() == MNGRCLASSID_CTESTMACROGROUP)
		{
			CTestMacroGroup* pGroup = (CTestMacroGroup*)pTempList;
			if (!pGroup)
			{
				return;
			}
			POS pos_Data = pGroup->GetHeadPosition();
			while (pos_Data)
			{
				CExBaseList* pData = (CExBaseList*)pGroup->GetNext(pos_Data);
				if (pData->GetClassID() == MNGRCLASSID_CTESTMACROREF)
				{
					CTestMacroRef* pTestRef = (CTestMacroRef*)pData;
					if (pTestRef->m_isChecked)
					{
						listCurSelTestID.append(pTestRef->m_strID);

						long nIndex = CalAutoIndex(pTestRef->m_strID);
						if (nIndex == 0)
						{
							listItemsID.append(pTestRef->m_strID);
							listItemsName.append(pTestRef->m_strName);
						}
						else if (nIndex != -1)
						{
							listItemsID.append(pTestRef->m_strID + QString::number(nIndex));
							CString strText = pTestRef->m_strName + QString::number(nIndex);
							listItemsName.append(strText);
						}
					}
				}
			}
		}
	}
				
}

//////////////////////////////////////////////////////////////////////////

QTestMacroToolButton::QTestMacroToolButton()
	: QToolButton()
{
	m_pData = NULL; 
	m_pItem = NULL;

	setCheckable(true);
	m_bMutiSelect = false;

	InitStyleSheet();
}

QTestMacroToolButton::~QTestMacroToolButton()
{
	m_oSelectedPixmap = QPixmap();  
	m_oUnselectedPixmap = QPixmap();
	m_iconPixmap = QPixmap();
}

void QTestMacroToolButton::InitStyleSheet()
{
	CString strSelectPath, strUnSelectPath;
#ifdef _PSX_QT_WINDOWS_
	strSelectPath = _P_GetResourcePath();
	strSelectPath += _T("checked.png");
	strUnSelectPath = _P_GetResourcePath();
	strUnSelectPath += _T("unchecked.png");
#else
	strSelectPath = ":/ctrls/images/checked.png";
	strUnSelectPath += ":/ctrls/images/unchecked.png";
#endif
	m_oSelectedPixmap.load(strSelectPath);
	m_oSelectedPixmap.scaled(20, 20);
	m_oUnselectedPixmap.load(strUnSelectPath);
	m_oUnselectedPixmap.scaled(20, 20);
}

void QTestMacroToolButton::paintEvent(QPaintEvent *event)
{
	if (m_bMutiSelect)
	{
		QPainter painter(this);
		QStyleOptionToolButton option;
		initStyleOption(&option);

		// 获取绘制区域
		QRect rect = this->rect();

		// 确定图片的位置
		QPoint pt = rect.topLeft();
		QSize checkBoxSize;
		// 根据复选框状态绘制图片
		if (m_pData != NULL)
		{
			if (m_pData->GetClassID() == MNGRCLASSID_CTESTMACROREF)
			{
				CTestMacroRef* pDataGroup = (CTestMacroRef*)m_pData;
				if (pDataGroup->m_isChecked)
				{
					checkBoxSize = m_oSelectedPixmap.size();
					painter.drawPixmap(pt, m_oSelectedPixmap);
				}
				else
				{
					checkBoxSize = m_oUnselectedPixmap.size();
					painter.drawPixmap(pt, m_oUnselectedPixmap);
				}
			}
		}

		// 图标的大小
		QSize iconSize = QSize(80, 80);

		// 确定图标的位置
		QPoint iconPt = rect.topLeft() + QPoint((rect.width() - iconSize.width()) / 2, pt.y() + checkBoxSize.height());
		// 使用 painter 绘制图标
		painter.drawPixmap(iconPt, m_iconPixmap.scaled(iconSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

		// 确定文本的位置（图标下方，保持适当间距）
		QFontMetrics fm(painter.font());
		int textY = iconPt.y() + iconSize.height() + fm.lineSpacing(); // 文本垂直居中于图标下方

		QRect textRect(pt.x(), textY, rect.width() - checkBoxSize.width() - 5, fm.height());
		textRect.setRight(rect.right() - 5); // 确保文本不会超出按钮右边界

		// 使用elidedText处理过长文本，并绘制文本
		QString ellipsisText = fm.elidedText(option.text, Qt::ElideRight, textRect.width());
		painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, ellipsisText); // 文本居中

		painter.end();
	}
	else
	{
		QToolButton::paintEvent(event);
	}
}

// 设置复选框状态
void QTestMacroToolButton::setChecked(bool checked) 
{
	if (m_bMutiSelect)
	{
		if (m_pData != NULL)
		{
			if (m_pData->GetClassID() == MNGRCLASSID_CTESTMACROREF)
			{
				CTestMacroRef* pDataGroup = (CTestMacroRef*)m_pData;
				pDataGroup->m_isChecked = checked;

				update(); // 触发重绘
			}
		}
	}
	else
	{
		QToolButton::setChecked(checked); 
	}

}

void QTestMacroToolButton::setIcon(const QPixmap &pixmap) 
{
	if (m_bMutiSelect)
	{
		m_iconPixmap = pixmap;
		update(); // 触发重绘以显示新图标
	}
	else
	{
		QToolButton::setIcon(QIcon(pixmap));
	}
}

// 设置按钮文本
void QTestMacroToolButton::setText(const QString &text) 
{
	if (m_bMutiSelect)
	{
		QToolButton::setText(text); // 使用基类的setText方法，但我们需要自定义绘制来确保布局正确
		update(); // 触发重绘以显示新文本
	}
	else
	{
		QToolButton::setText(text);
	}
}