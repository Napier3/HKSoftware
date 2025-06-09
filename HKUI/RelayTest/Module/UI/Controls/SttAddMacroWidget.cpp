#include "SttAddMacroWidget.h"
#include "ui_SttAddMacroWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QSttAddMacroWidget::QSttAddMacroWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttAddMacroWidget)
{
	m_pCurrentSelGbItem = NULL;
    ui->setupUi(this);

	InitLanguage();

	setWindowTitle(g_sLangTxt_Native_SelectTestFunction);
	m_bUseNameID = FALSE;

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	m_pCurrUIRef = NULL;
    m_font = font;
    m_pTestMacroUIMngr = (CSttMacroTestUI_TestMacroUIMngr *)CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB->GetTestMacroUIMngr()->CloneEx(TRUE, TRUE);
	g_theTestCntrFrame->InitTestMacroUI_by_DeviceType(m_pTestMacroUIMngr);

    m_pTreeCtrl = new CExBaseListTreeCtrl(this);
	m_pTreeCtrl->header()->hide();
	m_pTreeCtrl->AttachOptrInterface(this);
	m_pTreeCtrl->setFont(font);

    m_pTreeCtrl->AddClassID(MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_GROUP);
    m_pTreeCtrl->AddClassID(MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF);

    m_pTreeCtrl->ShowBaseList(m_pTestMacroUIMngr,false);

    ui->verticalLayout->insertWidget(0,m_pTreeCtrl);
	ui->m_Btn_OK->setFont(m_font);
	ui->m_Btn_Cancel->setFont(m_font);

	ui->m_Btn_OK->setDisabled(true);//开始时默认禁用

	//connect(m_pTreeCtrl,SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(slot_TreeItemClicked(QTreeWidgetItem *, int)));
	connect(ui->m_Btn_OK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
	connect(ui->m_Btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
}

QSttAddMacroWidget::~QSttAddMacroWidget()
{
    delete ui;
	delete m_pTreeCtrl;
	delete m_pTestMacroUIMngr;
}

void QSttAddMacroWidget::Use_Name_ID(BOOL bUse)  //lijunqing 2022-6-24  lijunqing
{
	m_bUseNameID = bUse;
	//南瑞要求项目标识采用默认的
	ui->m_lblItemsID->setVisible(false);
	ui->m_edtItemsID->setVisible(false);

	if (m_bUseNameID)
	{
		return;
	}

	ui->m_lblItemsName->hide();
//	ui->m_lblItemsID->hide();
	ui->m_edtItemsName->hide();
/*	ui->m_edtItemsID->hide();*/

}

void QSttAddMacroWidget::EnableOK()
{
    if (m_pCurrUIRef == NULL)
    {
        ui->m_Btn_OK->setDisabled(true);
        return;
    }

    if (!m_bUseNameID)
    {
         ui->m_Btn_OK->setDisabled(false);
		 return;
    }

	if (!CanAddMacro())
	{        
		ui->m_Btn_OK->setDisabled(true);
		return;
	}

    m_strItemsName = ui->m_edtItemsName->text();
    m_strItemsID = ui->m_edtItemsID->text();
    m_strItemsName.trimmed();
    m_strItemsID.trimmed();

    if (m_strItemsName.GetLength() == 0)
    {
        ui->m_Btn_OK->setDisabled(true);
        return;
    }

    if (m_strItemsID.GetLength() == 0)
    {
        ui->m_Btn_OK->setDisabled(true);
        return;
    }

	if (m_pCurrentSelGbItem->FindByID(m_strItemsID) != NULL)
	{
		ui->m_Btn_OK->setDisabled(true);
		//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("当前选中的节点，已经包含相同  标识  的测试项……"));
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_The.GetString()); //lcq
		return;
	}

	if (m_pCurrentSelGbItem->FindByName(m_strItemsName) != NULL)
	{
		ui->m_Btn_OK->setDisabled(true);
		//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("当前选中的节点，已经包含相同  名称  的测试项……"));
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_current.GetString()); //lcq
		return;
	}

    ui->m_Btn_OK->setDisabled(false);
}

BOOL QSttAddMacroWidget::CanAddMacro()
{
	if (!m_bUseNameID)
	{
		return TRUE;
	}

	if (m_pCurrentSelGbItem == NULL)
	{
		//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("当前选中的节点为空，无法添加项目……"));
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_Node.GetString());//lcq
		return FALSE;
	}

	if (m_pCurrentSelGbItem->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE
		|| m_pCurrentSelGbItem->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		return TRUE;
	}

	//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("当前选中的节点，其类型不支持添加项目……"));
	CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_Items.GetString()); //lcq
	return FALSE;
}

void QSttAddMacroWidget::slot_OKClick()
{
	m_strItemsName = ui->m_edtItemsName->text();
	m_strItemsID = ui->m_edtItemsID->text();

    m_strItemsName.trimmed();
    m_strItemsID.trimmed();

//	if (m_pCurrUIRef != NULL)
//	{
//	//	emit sig_TreeItemSelect(m_pCurrUIRef, m_strItemsName, m_strItemsID);
//	}
	//close();
	accept();
}

void QSttAddMacroWidget::slot_CancelClick()
{
	//close();
	reject();
}

long QSttAddMacroWidget::CalAutoIndex(const CString& strID)
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

void QSttAddMacroWidget::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	UINT nClassID = pSelObj->GetClassID();

	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF)
	{
		m_pCurrUIRef = (CSttMacroTestUI_TestMacroUIRef*)pSelObj;
	}
	else
	{
		m_pCurrUIRef = NULL;
	}

	//默认填写名称、标识
	//标识根据不同测试类型作计算以保证不重复,名称以计算结果为准,可能重复
	if(m_pCurrUIRef)
	{
		long nIndex = CalAutoIndex(m_pCurrUIRef->m_strID);

		if (nIndex == 0)
		{
			ui->m_edtItemsID->setText(m_pCurrUIRef->m_strID);
			ui->m_edtItemsName->setText(m_pCurrUIRef->m_strName);
		}
		else if(nIndex != -1)
		{
			CString strText = m_pCurrUIRef->m_strID + QString::number(nIndex);
			ui->m_edtItemsID->setText(strText);
			strText = m_pCurrUIRef->m_strName + QString::number(nIndex);
			ui->m_edtItemsName->setText(strText);		
		}

		if (m_pCurrUIRef->m_strID == STT_CMD_TYPE_SYSTEM_IECConfig && g_oSystemParas.m_nHasDigital == 0)
		{
			ui->m_Btn_OK->setDisabled(true);
			//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("系统参数设置中，未勾选数字量，不能创建IEC61850配置……"));
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_IEC_IEC61850.GetString()); //lcq
			return;
		}
	}

    EnableOK();
}

BOOL QSttAddMacroWidget::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)
{
	return FALSE;
}

void QSttAddMacroWidget::on_m_edtItemsName_textChanged(const QString &arg1)
{
    EnableOK();
}

void QSttAddMacroWidget::on_m_edtItemsID_textChanged(const QString &arg1)
{
    EnableOK();
}

void QSttAddMacroWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_OK,g_sLangTxt_OK,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);

	xlang_SetLangStrToWidget_Txt(ui->m_lblItemsName,g_sLangTxt_Name,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblItemsID,g_sLangTxt_Native_Identifier,XLang_Ctrls_QLabel);
}
