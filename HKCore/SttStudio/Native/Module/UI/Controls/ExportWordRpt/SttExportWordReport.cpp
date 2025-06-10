#include "ui_SttExportWordReport.h"
#include "SttExportWordReport.h"
#include "../../../SttGlobalDef.h"
#include "../../Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../../../../../AutoTest/Module/TestMacroRptTemplate/RptTemp_TestMacroUiRptDef.h"
#include <QFileDialog>

#include "../../../XLangResource_Native.h"

#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../AutoTest/Module/TestMacroRptTemplate/RptTemp_Data.h"
void QSttExportWordReport::OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (m_pTree_Gb != pTreeCtrl)
	{
		return;
	}

	UINT nClassID = pSelObj->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{
		return;
	}

}

void QSttExportWordReport::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (pTreeCtrl != m_pTree_Gb)
	{
		return;
	}

	UINT nClassID = pSelObj->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{
		return;
	}

	//在InitSttGuideBook中已经过滤了，此处可以直接刷新显示
// 	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
// 	{
// 		CSttItems *pItems = (CSttItems *)pSelObj;
// 
// 		if (! pItems->IsTypeRootNode())
// 		{
// 			return;
// 		}
// 	}

	OnGbTreeItemChanged(pSelObj);
}

BOOL QSttExportWordReport::OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)
{
	return FALSE;
}

QSttExportWordReport::QSttExportWordReport(CSttGuideBook *pGuideBook, QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttExportWordReport)
{
	m_pGuideBook = NULL;
	m_pItemsTec = NULL;
	m_pCurrSetItems = NULL;
    ui->setupUi(this);
// 	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_font = font;

	m_pTree_Gb = new QSttGbTreeCtrl_ExportRpt(m_font, this);
	m_pTree_Gb->header()->hide();
	m_pTree_Gb->AttachOptrInterface(this);
	m_pTree_Gb->setFont(font);
	m_pTree_Gb->AddClassID(STTGBXMLCLASSID_CSTTDEVICE);
	m_pTree_Gb->AddClassID(STTGBXMLCLASSID_CSTTITEMS);

	m_pGrid_DataDecimal = new CSttGrid_ExportRpt(this);
	m_pGrid_DataDecimal->InitGrid();
	m_pGrid_DataDecimal->InitDataTypes();

	m_pGrid_ItemsTec = new CSttGrid_ExportRpt_Tec(this);
	m_pGrid_ItemsTec->InitGrid();

	m_pCurrSelText = new QLabel(this);
	CString strCurrText;
	strCurrText = _T("当前项：未选择");
	m_pCurrSelText->setText(strCurrText);
	//m_pGrid_ExportRpt->AttachDataViewOptrInterface(this);

	ui->verticalLayout_tree->insertWidget(0,m_pTree_Gb);
	ui->verticalLayout_grid->insertWidget(0, m_pCurrSelText);
	ui->verticalLayout_grid->insertWidget(1,m_pGrid_DataDecimal);
	ui->verticalLayout_grid->insertWidget(2,m_pGrid_ItemsTec);

	m_pszFilePath = NULL;
	ui->m_btnExport->setDisabled(true);
	UI_SetFont();

	m_pGrid_DataDecimal->SetGuideBook(pGuideBook);
	m_pGrid_ItemsTec->SetGuideBook(pGuideBook);
	InitSttGuideBook(pGuideBook);
    InitLanguage();

	ShowSttGuideBook(m_pGuideBook);
	connect(ui->m_btnSelPath,SIGNAL(clicked()),this,SLOT(slot_SelPath()));
	connect(ui->m_btnExport,SIGNAL(clicked()),this,SLOT(slot_ExportRpt()));
	connect(ui->m_btnPrev,SIGNAL(clicked()),this,SLOT(slot_PrevClicked()));
	connect(ui->m_btnNext,SIGNAL(clicked()),this,SLOT(slot_NextClicked()));
}

QSttExportWordReport::~QSttExportWordReport()
{
	delete ui;
	m_oListItems.RemoveAll();

	if (m_pGuideBook != NULL)
	{
		delete m_pGuideBook;
		m_pGuideBook = NULL;
	}

// 	if(m_pTree_Gb)
// 	{
// 		delete m_pTree_Gb;
// 		m_pTree_Gb = NULL;
// 	}
}

void QSttExportWordReport::InitLanguage()
{

    xlang_SetLangStrToWidget_Txt(ui->label_FilePath, g_sLangTxt_Native_ExportPath, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->m_btnSelPath, g_sLangTxt_Browse, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->m_btnExport, g_sLangTxt_ExportReport, XLang_Ctrls_QPushButton);
}

void QSttExportWordReport::Init(CDataGroup *pItemsTec, CString* pszFilePath)
{
	m_pItemsTec = pItemsTec;
	m_pszFilePath = pszFilePath;
	ui->m_editFilePath->setText(*m_pszFilePath);
	InitItemsEnables();

	if (m_oListItems.GetCount() > 0)
	{
		slot_NextClicked();  //默认选中第一个
	}
	else
	{
		EnableBtns();
	}
}

//模板中的配置，是不包含enable条件的，还需要根据路径，把相关的enable找回来
void QSttExportWordReport::InitItemsEnables()
{
	if (m_pItemsTec == NULL)
	{
		return;
	}

	POS pos = m_pItemsTec->GetHeadPosition();
	CSttItems *pItems = NULL;

	while (pos != NULL)
	{
		CDataGroup *pTec = (CDataGroup *)m_pItemsTec->GetNext(pos);
		pItems = (CSttItems *)stt_gb_find_itembase(m_pGuideBook, pTec->m_strID);
		ASSERT(pItems != NULL);

		if (pItems == NULL)
		{
			continue;
		}

		InitItemsEnables(pTec, pItems->m_strstxmlFile);
	}
}

void QSttExportWordReport::InitItemsEnables(CDataGroup *pItemTec, const CString &strMacroUiID)
{
	CSttMacroTestUI_TestMacroUI* pMacro = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(strMacroUiID);
	ASSERT(pMacro != NULL);

	CString strPath = _P_GetDBPath();
	strPath += "atsgen/";
	strPath += pMacro->m_strrpt_Data_CfgFile;

	CRptTemp_TestMacroUiRptDef oRptDef;
	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oRptDef.OpenXmlFile(strPath, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	CDataGroup *pSrc = oRptDef.GetItemsTec();

	if (pSrc == NULL)
	{
		return;
	}

	//将RptData.xml文件中配置的enable，添加到pItemTec
	POS pos = pItemTec->GetHeadPosition();
	
	while (pos != NULL)
	{
		CRptTemp_Data *pTecData = (CRptTemp_Data *)pItemTec->GetNext(pos);

		if (pTecData->GetEnable() != NULL)
		{
			continue;
		}

		CRptTemp_Data *pSrcData = (CRptTemp_Data *)pSrc->FindByID(pTecData->m_strID);
		ASSERT(pSrcData != NULL);
		CRptTemp_Enable *pSrcEnable = pSrcData->GetEnable();

		if (pSrcEnable == NULL)
		{
			continue;
		}

		CRptTemp_Enable *pNewEnable = (CRptTemp_Enable *)pSrcEnable->CloneEx(TRUE, TRUE);
		pTecData->SetEnable(pNewEnable);
	}
}

void QSttExportWordReport::InitItemsTecDataTypes(CDataGroup *pItemTec)
{
	CDataTypes *pTypes = (CDataTypes *)m_oDataTypes.FindByID(pItemTec->m_strID);

	if (pTypes == NULL)
	{
		pTypes = m_pGrid_ItemsTec->InitDataTypes(pItemTec);

		if (pTypes == NULL)
		{
			return;
		}

		m_oDataTypes.AddTail((CDataTypes *)pTypes->CloneEx(TRUE, TRUE));
		return;
	}
	
	m_pGrid_ItemsTec->InitDataTypes(pTypes);
}

void QSttExportWordReport::UI_SetFont()
{
	ui->m_btnExport->setFont(m_font);
 	ui->label_FilePath->setFont(m_font);
 	ui->m_btnSelPath->setFont(m_font);
 	ui->m_editFilePath->setFont(m_font);
 	m_pGrid_DataDecimal->setFont(m_font);
 	m_pTree_Gb->setFont(m_font);
	m_pCurrSelText->setFont(m_font);
	ui->m_btnPrev->setFont(m_font);
	ui->m_btnNext->setFont(m_font);
}

//同一个CExBaseList链表，不能在两个树形控件中显示
//原因：参考QExBaseTreeWidgetItem构造函数，会影响pData的m_dwItemData属性
//因此，此处重新克隆一份GuideBook，用于显示
//只
void QSttExportWordReport::InitSttGuideBook(CSttGuideBook *pGuideBook)
{
	if (m_pGuideBook != NULL)
	{
		delete m_pGuideBook;
	}

	if (pGuideBook == NULL)
	{
		return;
	}

	m_pGuideBook = new CSttGuideBook();
	m_pGuideBook->m_strName = pGuideBook->m_strName;
	m_pGuideBook->m_strID = pGuideBook->m_strID;

	CSttDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	CSttDevice *pNewDevice = m_pGuideBook->GetDevice(TRUE);
	pNewDevice->m_strName = pDevice->m_strName;
	pNewDevice->m_strID = pDevice->m_strID;

	POS pos = pDevice->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pItems = (CSttItems *)pObj;

		if (pItems->m_nSelect == 0)
		{
			continue;
		}

		if (pItems->IsTypeNone())
		{
			continue;
		}

		if (pItems->m_strID == _T("_DevReset_")
			|| pItems->m_strID == _T("_AfterTest_")
			|| pItems->m_strID == _T("_BeforeTest_"))
		{
			continue;
		}

		CSttItems *pNewItems = new CSttItems();
		pNewDevice->AddNewChild(pNewItems);
		pNewItems->m_strID = pItems->m_strID;
		pNewItems->m_strName = pItems->m_strName;
		pNewItems->m_strstxmlFile = pItems->m_strstxmlFile;
		pNewItems->m_strType = pItems->m_strType;

		if (pNewItems->IsTypeRootNode())
		{
			m_oListItems.AddTail(pNewItems);
		}

		InitSttGuideBook_Items(pNewItems, pItems);
	}
}

void QSttExportWordReport::InitSttGuideBook_Items(CSttItems *pNewItems, CSttItems *pItems)
{
	POS pos = pItems->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pChildItems = (CSttItems *)pObj;

		if (pChildItems->m_nSelect == 0)
		{
			continue;
		}

		if (pChildItems->IsTypeNone())
		{
			continue;
		}

		if (pChildItems->m_strID == _T("_DevReset_")
			|| pChildItems->m_strID == _T("_AfterTest_")
			|| pChildItems->m_strID == _T("_BeforeTest_"))
		{
			continue;
		}

		CSttItems *pNew = new CSttItems();
		pNewItems->AddNewChild(pNew);
		pNew->m_strID = pChildItems->m_strID;
		pNew->m_strName = pChildItems->m_strName;
		pNew->m_strstxmlFile = pChildItems->m_strstxmlFile;
		pNew->m_strType = pChildItems->m_strType;

		if (pNew->IsTypeRootNode())
		{
			m_oListItems.AddTail(pNew);
		}

		InitSttGuideBook_Items(pNew, pChildItems);
	}
}

void QSttExportWordReport::ShowSttGuideBook(CSttGuideBook *pGuideBook)
{
	if (pGuideBook == NULL)
	{
		return;
	}

	if (m_pTree_Gb == NULL)
	{
		return;
	}

	CSttDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	m_pTree_Gb->ShowBaseList(pDevice);
}

void QSttExportWordReport::OnGbTreeItemChanged(CExBaseObject *pSelObj)
{
	if (m_pItemsTec == NULL)
	{
		return;
	}

	CSttItems *pItems = (CSttItems *)pSelObj;

	if (! pItems->IsTypeRootNode())
	{
		return;
	}

	m_pCurrSetItems = pItems;
	CString strItemPath, strItemPath_Name, strCurrSelText;
	stt_gb_get_itempath_id(pItems, strItemPath);
	stt_gb_get_itempath_name(pItems, strItemPath_Name);
	strItemPath_Name.Replace(_T("$"), _T("->"));
	strCurrSelText = _T("当前项：");
	strCurrSelText += strItemPath_Name;
	m_pCurrSelText->setText(strCurrSelText);

	CDataGroup *pItemTec = (CDataGroup *)m_pItemsTec->FindByID(strItemPath);

	if (pItemTec == NULL)
	{
		pItemTec = m_pItemsTec->AddNewGroup(_T(""), strItemPath, STT_CMD_PARA_items_tec);
	}

	//从RptData中解析默认的信息
	GetItemsTecFromRptDataXml(pItemTec, pItems->m_strstxmlFile);
	m_pGrid_DataDecimal->SetItems(pItems);
	m_pGrid_DataDecimal->ShowDatas(pItemTec);

	InitItemsTecDataTypes(pItemTec);
	m_pGrid_ItemsTec->SetItems(pItems);
	m_pGrid_ItemsTec->ShowDatas(pItemTec);
	m_pGrid_ItemsTec->ShowDatas(pItemTec);
	
	EnableBtns();
}

void QSttExportWordReport::GetItemsTecFromRptDataXml(CDataGroup *pItemTec, const CString &strMacroUiID)
{
	if (pItemTec == NULL)
	{
		return;
	}

	CSttMacroTestUI_TestMacroUI* pMacro = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(strMacroUiID);
	ASSERT(pMacro != NULL);

	if (pMacro == NULL)
	{
		return;
	}

	CString strPath = _P_GetDBPath();
	strPath += "atsgen/";
	strPath += pMacro->m_strrpt_Data_CfgFile;

	CRptTemp_TestMacroUiRptDef oRptDef;
	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oRptDef.OpenXmlFile(strPath, CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys);
	CTestMacroRptTemplateXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	CDataGroup *pSrc = oRptDef.GetItemsTec();

	if (pSrc == NULL)
	{
		return;
	}

	//将RptData.xml文件中配置的默认值，添加到pItemTec
	pItemTec->AddDataValuesNotExist(pSrc);  
}

CString QSttExportWordReport::ExportWordRptDlg()
{
    CString strText = /*  _T("导出Word报告") */ g_sLangTxt_Native_ExportWords;
	QFileDialog dlg(this, strText);
	dlg.setFileMode(QFileDialog::AnyFile);
    strText = /* _T("Word报告文件 (*.doc)") */ g_sLangTxt_Native_WordDoc;
	dlg.setNameFilter(strText);
	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetWorkspacePath();
	dlg.setDirectory(strPath);
    strText = /*  _T("文件路径") */ g_sLangTxt_FilePath;
	dlg.setLabelText(QFileDialog::LookIn, strText);
    strText = /* _T("文件名") */ g_sLangTxt_FileName;
	dlg.setLabelText(QFileDialog::FileName, strText);
    strText = /* _T("文件类型") */ g_sLangTxt_Native_FileType;
	dlg.setLabelText(QFileDialog::FileType, strText);
	dlg.setAcceptMode(QFileDialog::AcceptSave);
    strText = /*  _T("保存") */ g_sLangTxt_Save;
    dlg.setLabelText(QFileDialog::Accept, strText);
    strText = /* _T("取消") */ g_sLangTxt_Cancel;
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strFileName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
	}

	return strFileName;
}

void QSttExportWordReport::EnableBtns()
{
	if (m_oListItems.GetCount() == 0)
	{
		ui->m_btnNext->setDisabled(true);
		ui->m_btnPrev->setDisabled(true);
		return;
	}

	if (m_pCurrSetItems == NULL)
	{
		//刚进入时，还没有选中任何项目
		ui->m_btnNext->setDisabled(false);
		ui->m_btnPrev->setDisabled(true);
		return;
	}

	ui->m_btnPrev->setDisabled(false);
	ui->m_btnNext->setDisabled(false);

	if (m_oListItems.GetTail() == m_pCurrSetItems)
	{
		ui->m_btnNext->setDisabled(true);
	}

	if (m_oListItems.GetHead() == m_pCurrSetItems)
	{
		ui->m_btnPrev->setDisabled(true);
	}
}

void QSttExportWordReport::ExpandItems(CSttItems *pItems)
{
	if (pItems == NULL)
	{
		return;
	}

	CExBaseObject *pParent = pItems;
	QExBaseTreeWidgetItem* hItem = NULL;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == STTGBXMLCLASSID_CSTTDEVICE)
		{
			break;
		}

		hItem = (QExBaseTreeWidgetItem*)pParent->m_dwItemData;

		if (hItem != NULL)
		{
			hItem->setExpanded(true);
		}

		pParent = (CExBaseObject *)pParent->GetParent();
	}
}

void QSttExportWordReport::FormatItemsTec()
{
	if (m_pItemsTec == NULL)
	{
		return;
	}

	POS pos = m_pItemsTec->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pGrp = (CDataGroup *)m_pItemsTec->GetNext(pos);

		POS posGrp = pGrp->GetHeadPosition();

		while (posGrp != NULL)
		{
			CRptTemp_Data *pData = (CRptTemp_Data *)pGrp->GetNext(posGrp);
			
			if (! IsDataItemsTec(pData))
			{
				continue;
			}

			FormatItemsTec(pData);
		}
	}
}

void QSttExportWordReport::FormatItemsTec(CDvmData *pData)
{
	CString strID = pData->m_strID + _postfix_ID_TimesTerm;   //固定后缀：过量欠量倍数条件
	CDvmValue *pTimesTerm = (CDvmValue *)pData->FindByID(strID);
	strID = pData->m_strID + _postfix_ID_ErrRange;   //固定后缀：时间/动作值误差范围
	CDvmValue *pErrRange = (CDvmValue *)pData->FindByID(strID);

	if (pTimesTerm == NULL && pErrRange == NULL)
	{
		return;
	}

	CString strItemTec, strAdd;
	strItemTec = _T("技术要求：");
	strAdd = _T("，");

	if (pTimesTerm != NULL && pErrRange != NULL)
	{
		strItemTec += pTimesTerm->m_strValue;

		if (! pTimesTerm->m_strValue.IsEmpty() && ! pErrRange->m_strValue.IsEmpty())
		{
			strItemTec += strAdd;
		}
		
		strItemTec += pErrRange->m_strValue;
		pData->m_strValue = strItemTec;
		return;
	}

	if (pTimesTerm != NULL)
	{
		strItemTec += pTimesTerm->m_strValue;
	}

	if (pErrRange != NULL)
	{
		strItemTec += pErrRange->m_strValue;
	}

	pData->m_strValue = strItemTec;
}

void QSttExportWordReport::ClearItemsTecEnables()
{
	if (m_pItemsTec == NULL)
	{
		return;
	}

	POS pos = m_pItemsTec->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pGrp = (CDataGroup *)m_pItemsTec->GetNext(pos);

		POS posGrp = pGrp->GetHeadPosition();

		while (posGrp != NULL)
		{
			CRptTemp_Data *pData = (CRptTemp_Data *)pGrp->GetNext(posGrp);
			pData->DeleteEnable();
		}
	}
}

void QSttExportWordReport::slot_SelPath()
{
	CString strFile = ExportWordRptDlg();

	if(strFile.GetLength() < 4)
	{
		return;
	}

	*m_pszFilePath = strFile;
	ui->m_editFilePath->setText(*m_pszFilePath);
	ui->m_btnExport->setDisabled(false);

	if (ui->m_editFilePath->text().length() < 4)
	{
		ui->m_btnExport->setDisabled(true);
		return;
	}
}

void QSttExportWordReport::slot_ExportRpt()
{
	FormatItemsTec();
	ClearItemsTecEnables();
	this->accept();
}

void QSttExportWordReport::slot_PrevClicked()
{
	ASSERT(m_pCurrSetItems != NULL);
	ASSERT(m_pCurrSetItems != m_oListItems.GetHead());

	long nCurrIndex = m_oListItems.FindIndex(m_pCurrSetItems);
	CSttItems *pPrevItems = (CSttItems *)m_oListItems.GetAtIndex(nCurrIndex - 1);

	QExBaseTreeWidgetItem* hItem = NULL;

	if (m_pCurrSetItems != NULL)
	{
		hItem = (QExBaseTreeWidgetItem*)m_pCurrSetItems->m_dwItemData;
		hItem->setSelected(false);
	}

	m_pTree_Gb->SetCurrSelObj(pPrevItems);
	OnGbTreeItemChanged(pPrevItems);
	ExpandItems(pPrevItems);
}

void QSttExportWordReport::slot_NextClicked()
{
	CSttItems *pNextItems = NULL;

	if (m_pCurrSetItems == NULL)
	{
		pNextItems = (CSttItems *)m_oListItems.GetHead();
	}
	else
	{
		long nCurrIndex = m_oListItems.FindIndex(m_pCurrSetItems);
		pNextItems = (CSttItems *)m_oListItems.GetAtIndex(nCurrIndex + 1);
	}

	QExBaseTreeWidgetItem* hItem = NULL;

	if (m_pCurrSetItems != NULL)
	{
		hItem = (QExBaseTreeWidgetItem*)m_pCurrSetItems->m_dwItemData;
		hItem->setSelected(false);
	}

	if (pNextItems != NULL)
	{
		m_pTree_Gb->SetCurrSelObj(pNextItems);
		OnGbTreeItemChanged(pNextItems);
		ExpandItems(pNextItems);
	}
}