#include "SttReportHeadSetDlg.h"
#include "ui_SttReportHeadSetDlg.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
//#include "../SttTestCntrFrameBase.h"
#include "SttCheckBox.h"
#include "../Interface/SttHtmlReportVIewInterface.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"


QTreeWidgetItemEx::QTreeWidgetItemEx(QTreeWidget *pParent, CExBaseObject *pDataRef) : QTreeWidgetItem(pParent)
{
    m_pDataRef = pDataRef;
}

QTreeWidgetItemEx::QTreeWidgetItemEx(QTreeWidgetItem *pParent, CExBaseObject *pDataRef) : QTreeWidgetItem(pParent)
{
    m_pDataRef = pDataRef;
}

QSttReportHeadSetDlg::QSttReportHeadSetDlg(CDataGroup* pSttReports,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttReportHeadSetDlg)
{
    ui->setupUi(this);
	if(xlang_GetCurrLanguageID() == CURRLANGUAGE_RUSSIAN)
	{
		this->resize(970,279);
	}
	else if(xlang_GetCurrLanguageID() == CURRLANGUAGE_ENGLISH)
	{
		this->resize(620,279);
	}
	else
	{
		this->resize(550,279);
	}
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	CString strTitle;

    if (CXLanguageMngr::xlang_IsCurrXLanguageChinese())
    {
        strTitle = /*"报告头设置"*/g_sLangTxt_Native_ReportHeadSet;
    }
    else
    {
        xlang_GetLangStrByFile(strTitle,"Report_Title");
    }
	
	m_pTempData = NULL;
	m_pSttReports = NULL;
	this->setWindowTitle(strTitle);

    CString strText/*("确定")*/;
	xlang_GetLangStrByFile(strText,"sOK");
    ui->btnOK->setText(strText);
    //strText = "取消";
	xlang_GetLangStrByFile(strText, "sCancel");
   ui->btnCancel->setText(strText);

    //xlang_SetLangStrToWidget(ui->btnOK, "Native_OK", XLang_Ctrls_QPushButton);
    //xlang_SetLangStrToWidget(ui->btnCancel, "Native_Cancel", XLang_Ctrls_QPushButton);

	m_pSttReports = pSttReports;
	m_pTempData = (CDataGroup*)m_pSttReports->Clone();
	m_nOkFlag = 0;
	m_bUpataHeadHtml =TRUE;

	SetData();
	setReportHeadFont();
	InitStyleSheet();
}

QSttReportHeadSetDlg::~QSttReportHeadSetDlg()
{
	delete m_pTempData;
	m_pTempData = NULL;
    delete ui;
}
void QSttReportHeadSetDlg::setReportHeadFont()
{
	ui->btnCancel->setFont(*g_pSttGlobalFont);
	ui->btnOK->setFont(*g_pSttGlobalFont);
	ui->treeWidget->setFont(*g_pSttGlobalFont);
}

void QSttReportHeadSetDlg::OpenEngKeyboard(QSttLineEdit* pEditLine)
{
	QString str = pEditLine->text();
	GetEngWidgetBoard_DigitData(str, parentWidget());
	pEditLine->setText(str);
}


void QSttReportHeadSetDlg::SetData()
{
	CString strContext;
	xlang_GetLangStrByFile(strContext,"Report_TestChoose");
	ui->treeWidget->setHeaderLabel(strContext);
	ui->treeWidget->setColumnCount(1);

    QTreeWidgetItemEx *pTopTreeItem = new QTreeWidgetItemEx(ui->treeWidget, NULL);
    xlang_GetLangStrByFile(m_pTempData->m_strName,"Gradient_ReportHeader"); //报告头信息  lcq
	pTopTreeItem->setText(0,m_pTempData->m_strName);
	ui->treeWidget->addTopLevelItem(pTopTreeItem);

	if (m_pTempData->m_strValue == _T("1"))
	{
		pTopTreeItem->setCheckState(0,Qt::Checked);
	}
	else
		pTopTreeItem->setCheckState(0,Qt::Unchecked);
	
	POS pos = m_pTempData->GetHeadPosition();

    while(pos)
	{
		CDataGroup *pData = (CDataGroup*)m_pTempData->GetNext(pos);
        SetTreeItem(pData,pTopTreeItem);
		InitObjValue(pData);
	}
 
 	ui->treeWidget->expandAll();

	CDataGroup *pObj = (CDataGroup*)m_pTempData->GetHead();
    UpdateShow(pObj);
 
 	connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(slot_TreeItemChanged(QTreeWidgetItem*,int)));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
    connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
}

void QSttReportHeadSetDlg::InitObjValue(CDataGroup *pDataGroup)
{
	UINT nClassID = 0;
	CString strTemp;
	POS pos = pDataGroup->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmData *pDvmData = NULL;

	while(pos)
	{
		p = pDataGroup->GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}

		pDvmData = (CDvmData *)p;

		if (pDvmData->m_strID == STT_REPORTHEAD_Vnom)
		{
			strTemp.Format("%f", g_oSystemParas.m_fVNom);
			pDvmData->m_strValue.Format("%.03f", g_oSystemParas.m_fVNom);
			pDvmData->m_nIndex = 0;
		}
		else if (pDvmData->m_strID == STT_REPORTHEAD_Inom)
		{
			pDvmData->m_strValue.Format("%.03f", g_oSystemParas.m_fINom);
			pDvmData->m_nIndex = 0;
		}
		else if (pDvmData->m_strID == STT_REPORTHEAD_Fnom)
		{
			pDvmData->m_strValue.Format("%.03f", g_oSystemParas.m_fFNom);
			pDvmData->m_nIndex = 0;
		}
		else if (pDvmData->m_strID == STT_REPORTHEAD_SureTime)
		{
			pDvmData->m_strValue.Format("%f", g_oSystemParas.m_fStabTime);
			pDvmData->m_nIndex = 0;
		}
		else if (pDvmData->m_strID == STT_REPORTHEAD_AppModel)
		{
			pDvmData->m_strValue = g_oSttTestResourceMngr.GetCurrModel();;
			pDvmData->m_nIndex = 0;
		}
		else if (pDvmData->m_strID == STT_REPORTHEAD_AppSN)
		{
			pDvmData->m_strValue = g_oSttTestResourceMngr.GetCurrSelSN();
			pDvmData->m_nIndex = 0;
		}
		else if (pDvmData->m_strID == STT_REPORTHEAD_Imax)
		{
			pDvmData->m_strValue.Format("%.03f", g_oLocalSysPara.m_fAC_CurMax);
			pDvmData->m_nIndex = 0;
		}
		else if (pDvmData->m_strID == STT_REPORTHEAD_Vmax)
		{
			pDvmData->m_strValue.Format("%.03f", g_oLocalSysPara.m_fAC_VolMax);
			pDvmData->m_nIndex = 0;
		}
		else
		{
			pDvmData->m_nIndex = 1;
		}
	}
	
}

void QSttReportHeadSetDlg::SetTreeItem( CDataGroup *pData,QTreeWidgetItem *pParent )
{
	if (pData == NULL)
	{
		return;
	}

    QTreeWidgetItemEx *pTreeItem = new QTreeWidgetItemEx(pParent, pData);
    pTreeItem->setText(0,pData->m_strName);

	//20240507 suyang 根据配置文件来是否显示表头
	if (pData->m_strValue == _T("0"))
	{
		 pTreeItem->setCheckState(0,Qt::Unchecked);	
	}
	else
    {

       pTreeItem->setCheckState(0,Qt::Checked);
    }
// 	pTreeItem->setCheckState(0, Qt::Checked);//dingxiaoya 20231107 默认都勾选
}

void QSttReportHeadSetDlg::InitStyleSheet()
{
	CString strStyleSheet;
#ifndef _PSX_QT_WINDOWS_
	strStyleSheet.Format("QTreeView::indicator:checked {image: url(:/ctrls/images/checked.png);} QTreeView::indicator:unchecked {image: url(:/ctrls/images/unchecked.png);}");
#endif
	ui->treeWidget->setStyleSheet(strStyleSheet);
}
void QSttReportHeadSetDlg::slot_TreeItemChanged( QTreeWidgetItem* pItem,int nCol )
{
    QTreeWidgetItemEx *pTreeItem = (QTreeWidgetItemEx*)pItem;

	CString itemText = pItem->text(0);
	CDataGroup * pData = NULL;
	QTreeWidgetItemEx *pTreechildItem = NULL;

	if (pItem->checkState(0) == Qt::Checked)
	{
		QTreeWidgetItem *parent = pItem->parent();
		int cnt = pItem->childCount();
		if (cnt >0)
		{
			for (int i = 0;i < cnt;i++)
			{
				pItem->child(i)->setCheckState(0,Qt::Checked);

				//20240511 suyang 更改选中状态后更新值
				pTreechildItem = (QTreeWidgetItemEx *)pItem->child(i);
				pData = (CDataGroup*)pTreechildItem->m_pDataRef;
				pData->m_strValue.Format(_T("%d"), pItem->child(i)->checkState(0));
				
			}
		}
		else
		{
			UpdateParentItem(pItem);
		}
	}
	else if (pItem->checkState(0) == Qt::Unchecked)
	{
		int cnt = pItem->childCount();
		if (cnt > 0)
		{
			for (int i = 0;i < cnt;i++)
			{	
				if (i == cnt-1)
			{
					CString strMsgText = _T("至少选择一个");
					CXMessageBox::information(this,/* tr("提示")*/g_sLangTxt_Message,strMsgText);

					if (pItem->child(i)->checkState(0) == Qt::Unchecked)
					{
						pItem->child(i)->setCheckState(0,Qt::Checked);
						pTreechildItem = (QTreeWidgetItemEx *)pItem->child(i);
						pData = (CDataGroup*)pTreechildItem->m_pDataRef;
						pData->m_strValue.Format(_T("%d"), pItem->child(i)->checkState(0));
					}

					break;

				}
				pItem->child(i)->setCheckState(0,Qt::Unchecked);
				pTreechildItem = (QTreeWidgetItemEx *)pItem->child(i);
				pData = (CDataGroup*)pTreechildItem->m_pDataRef;
				pData->m_strValue.Format(_T("%d"), pItem->child(i)->checkState(0));
			}
		}
		else
		{
			UpdateParentItem(pItem);
		}
	}

    UpdateShow(pTreeItem->m_pDataRef);
}



void QSttReportHeadSetDlg::UpdateParentItem( QTreeWidgetItem *pitem )
{
	QTreeWidgetItem *parent = pitem->parent();

	if (parent == NULL)
	{
		return;
	}
	//选中的子节点个数
	int selectedCount = 0;
	int childCount = parent->childCount();
	for (int i = 0; i < childCount; i++)
	{
		QTreeWidgetItem *childItem = parent->child(i);
		if (childItem->checkState(0) == Qt::Checked)
		{
			selectedCount++;
		}
	}
	if (selectedCount <= 0)
	{

		CString strMsgText = _T("至少选择一个");
		CXMessageBox::information(this,/* tr("提示")*/g_sLangTxt_Message,strMsgText);

		if (parent->child(0)->checkState(0) == Qt::Unchecked)
		{
			parent->child(0)->setCheckState(0,Qt::Checked);
			QTreeWidgetItemEx *pTreechildItem = (QTreeWidgetItemEx *)parent->child(0);
			CDataGroup *pData = (CDataGroup*)pTreechildItem->m_pDataRef;
			pData->m_strValue.Format(_T("%d"), parent->child(0)->checkState(0));
		}

		parent->setCheckState(0, Qt::PartiallyChecked);
		//未选中状态
		//parent->setCheckState(0, Qt::Unchecked);
		
	}
	else if (selectedCount > 0 && selectedCount < childCount)
	{
	//部分选中状态
		parent->setCheckState(0, Qt::PartiallyChecked);
	}
	else if (selectedCount == childCount)
	{
		//选中状态
		parent->setCheckState(0, Qt::Checked);
	}

    QTreeWidgetItemEx *p = (QTreeWidgetItemEx*)pitem;
    CDataGroup *pGroup = (CDataGroup*)p->m_pDataRef;
    pGroup->m_strValue.Format(_T("%d"), pitem->checkState(0));
}

void QSttReportHeadSetDlg::UpdateShow( CExBaseObject *pSel )
{
    if (pSel == NULL)
    {
        return;
    }

    if (pSel == m_pCurrSelGroup)
    {
        return;
    }

    m_pCurrSelGroup = (CDataGroup*)pSel;

	for (int i = 0 ; i < m_labelList.size(); i++)
	{
		delete m_labelList[i];
		m_labelList[i] = NULL;
	}
	for (int i = 0 ; i < m_editList.size(); i++)
	{
		delete m_editList[i];
		m_editList[i] = NULL;
	}

	m_labelList.clear();
	m_editList.clear();

    POS posObj = m_pCurrSelGroup->GetHeadPosition();
    int nRow = 0;
    while(posObj)
    {
        CDvmData *pObj = (CDvmData*)m_pCurrSelGroup->GetNext(posObj);
         AddObjToGroup(pObj,nRow++);
    }
}

void QSttReportHeadSetDlg::slot_OKClick()
{
	POS pos = m_pSttReports->GetHeadPosition();
	CDvmData * pDvmData = NULL;
	CDvmData *pData = NULL;
	int nCount = 0;
	while(pos)
	{
		pDvmData = (CDvmData *)m_pSttReports->GetNext(pos);

		pData = (CDvmData *)m_pTempData->FindByID(pDvmData->m_strID);

		if (pData != NULL)
		{
			if ((pData-> m_strValue!= pDvmData->m_strValue)&&(pDvmData->m_strValue == _T("0")))
			{
				nCount ++;
			}
		}

	}
	if (nCount > 0)
	{
		m_bUpataHeadHtml = FALSE;
	}


    m_pSttReports->InitDataValues(m_pTempData, FALSE);

	m_nOkFlag = 1;
	
	close();
}

void QSttReportHeadSetDlg::slot_CancelClick()
{
	m_nOkFlag = 2;

	close();
}

void QSttReportHeadSetDlg::AddObjToGroup( CDvmData* pData,int nRow )
{
	QSttDvmEdit *tempEdit = new QSttDvmEdit(pData,parentWidget());
	QFont font = tempEdit->font();
	font.setPixelSize(18);

	tempEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//	tempEdit->setFont(font);
	tempEdit->setFont(*g_pSttGlobalFont);//2022-10-25 sy 采用g_pSttGlobalFont
	tempEdit->setText(pData->m_strValue);
	ui->m_pVBox->addWidget(tempEdit,nRow,1);
	m_editList.append(tempEdit);
	tempEdit->setEnabled(pData->m_nIndex);
	QLabel *tempLabel = new QLabel;
	tempLabel->setFont(*g_pSttGlobalFont);
     tempLabel->setText(pData->m_strName);
	ui->m_pVBox->addWidget(tempLabel,nRow,0);
	m_labelList.append(tempLabel);

	if ((pData->m_strID == STT_REPORTHEAD_TestStartTime) || (pData->m_strID == STT_REPORTHEAD_TestEndTime))
	{
		tempEdit->setVisible(false);
		tempLabel->setVisible(false);
	}
}
