#include "SttImportDvmFileWidget.h"
#include "ui_SttImportDvmFileWidget.h"
#include "..\Config\MacroTestUI\SttTestCtrrlMacroTestUIMngrGlobal.h"
#include "..\..\SttTestCtrl\SttTestAppBase.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

#define STT_CMD_KEY_WRITE_ENA       _T("WriteEna")
#define STT_CMD_KEY_WRITE_SETTING   _T("WriteSetting")

void QSttImportDvmFileWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
}

QSttImportDvmFileWidget::QSttImportDvmFileWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttImportDvmFileWidget)
{
    ui->setupUi(this);

	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	m_font = font;
	m_pItems = NULL;
	m_pListSort = NULL;
	m_pCurrStep = NULL;

	//左边步骤表格
	m_pGridStep = new CSttImportDvmFile_StepGrid(this);
	m_pGridStep->verticalHeader()->setHidden(true);
	m_pGridStep->InitGrid();
	ui->horizontalLayoutWzd->insertWidget(0,m_pGridStep);
	m_pGridStep->AttachDataViewOptrInterface(this);

	//右边编辑表格
	m_pGridEdit = new CSttImportDvmFile_EditGrid(this);
	m_pGridEdit->InitGrid();
	ui->horizontalLayoutWzd->insertWidget(1,m_pGridEdit);
	m_pGridEdit->AttachDataViewOptrInterface(this);

	ui->horizontalLayoutWzd->setStretch(0,1);
	ui->horizontalLayoutWzd->setStretch(1,2);
	UI_SetFont();

	connect(ui->pushButton_Pre,SIGNAL(clicked()),this,SLOT(slot_PreClick()));
	connect(ui->pushButton_Next,SIGNAL(clicked()),this,SLOT(slot_NextClick()));
	connect(ui->pushButton_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));

	InitLanguage();
}

QSttImportDvmFileWidget::~QSttImportDvmFileWidget()
{
    delete ui;
	delete m_pItems;
	m_pItems = NULL;

	delete m_pListSort;
	m_pListSort = NULL;
}

void QSttImportDvmFileWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->pushButton_Pre,g_sLangTxt_Native_previtem,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->pushButton_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
}

void QSttImportDvmFileWidget::UI_SetFont()
{
	ui->pushButton_Pre->setFont(m_font);
	ui->pushButton_Next->setFont(m_font);
	ui->pushButton_Cancel->setFont(m_font);
}

long QSttImportDvmFileWidget::InitShow()
{
	if (m_pItems == NULL)
	{
		return 0;
	}

	SortItems();

	if (m_pListSort->GetCount() == 0)
	{
		return 0;
	}

	m_pGridStep->ShowDatas(m_pListSort);
	ShowSetp((CSttItems*)m_pListSort->GetHead());
	ui->pushButton_Pre->setDisabled(true);

	return 1;
}

void QSttImportDvmFileWidget::ShowSetp(CSttItems *pItemsStep)
{
	if (pItemsStep == NULL)
	{
		return;
	}

	m_pCurrStep = pItemsStep;
	m_pGridStep->Update_ShowCurr(pItemsStep, FALSE);

	if (pItemsStep->m_strstxmlFile == STT_CMD_KEY_WRITE_ENA)
	{
		CStringArray strKeyArray;
		CString strDatasetKey = _T("dsEna");
		strKeyArray.Add(strDatasetKey);
		strDatasetKey = _T("dsRelayEna");
		strKeyArray.Add(strDatasetKey);
		m_pGridEdit->InitDatasList(strKeyArray);
	}
	else
	{
		m_pGridEdit->InitDatasList(_T("dsSetting"));
	}

	m_pGridEdit->ClearCmdsValues();
	m_pGridEdit->ClearEditList();
	CExBaseList oCommCmds;
	GetCommCmds(pItemsStep, &oCommCmds);
	POS pos = oCommCmds.GetHeadPosition();

	while (pos != NULL)
	{
		CSttCommCmd *pCommCmd = (CSttCommCmd *)oCommCmds.GetNext(pos);
		m_pGridEdit->InitCmdsValues(pCommCmd);
	}

	oCommCmds.RemoveAll();
	m_pGridEdit->ShowDatas(NULL);
	m_pGridEdit->ShowDatas();
}

void QSttImportDvmFileWidget::GetCommCmds(CSttItems *pItemsStep, CExBaseList *pListCommCmds)
{
	if (m_pItems == NULL || pItemsStep == NULL)
	{
		return;
	}

	CSttItems *pItems = (CSttItems *)m_pItems->FindByID(pItemsStep->m_strID);
	ASSERT(pItems != NULL);

	if (pItems == NULL)
	{
		return;
	}

	POS pos = pItems->GetHeadPosition();

	while (pos != NULL)
	{
		CSttCommCmd *pCommCmd = (CSttCommCmd *)pItems->GetNext(pos);

		if (pItemsStep->m_strstxmlFile == pCommCmd->m_strCommCmdID)
		{
			pListCommCmds->AddTail(pCommCmd);
		}
	}
}

void QSttImportDvmFileWidget::SortItems()
{
	if (m_pItems == NULL)
	{
		return;
	}

	if (m_pListSort == NULL)
	{
		m_pListSort = new CExBaseList();
	}

	m_pListSort->DeleteAll();

	POS pos = m_pItems->GetHeadPosition();
	CStringArray oArray;
	CString strCmdKey;

	while (pos != NULL)
	{
		CSttItems *pItems = (CSttItems *)m_pItems->GetNext(pos);

		if (IsItemsDevReset(pItems->m_strID))
		{
			continue;
		}

		GetCmdArray(oArray, pItems);

		for (int n=0; n<oArray.GetCount(); n++)
		{
			strCmdKey = oArray.GetAt(n);

			CSttItems *pNew = new CSttItems();
			pNew->m_strID = pItems->m_strID;  //用于与m_pItems下的项目ID作映射
			CString strName;
			GetItemName(strName, pItems->m_strID, strCmdKey);
			pNew->m_strName = strName;
			pNew->m_strstxmlFile = strCmdKey;  //记录类型，用于区分是定值还是压板
			m_pListSort->AddNewChild(pNew);
		}
	}
}

//测试后恢复 + 装置复归态。都认为是复归态
BOOL QSttImportDvmFileWidget::IsItemsDevReset(const CString &strID)
{
	if (strID.Find(STT_ITEMS_ID_AFTERTEST) >= 0)
	{
		return TRUE;
	}

	if (strID.Find(STT_ITEMS_ID_DEVRESET) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

//只处理修改定值、投退压板指令
void QSttImportDvmFileWidget::GetCmdArray(CStringArray &strCmdArray, CSttItems *pItems)
{
	strCmdArray.RemoveAll();
	BOOL bSet = FALSE, bEna = FALSE;

	POS pos = pItems->GetHeadPosition();
	
	while (pos != NULL)
	{
		CSttCommCmd *pCommCmd = (CSttCommCmd *)pItems->GetNext(pos);

		if (pCommCmd->m_strCommCmdID == STT_CMD_KEY_WRITE_ENA)
		{
			if (!bEna)
			{
				strCmdArray.Add(STT_CMD_KEY_WRITE_ENA);
				bEna = TRUE;
			}
		}

		if (pCommCmd->m_strCommCmdID == STT_CMD_KEY_WRITE_SETTING)
		{
			if (!bSet)
			{
				strCmdArray.Add(STT_CMD_KEY_WRITE_SETTING);
				bSet = TRUE;
			}
		}
	}
}

//例如：ManualTest$_BeforeTest_。返回名称为“通用试验”
void QSttImportDvmFileWidget::GetItemName(CString &strName, const CString &strPath, const CString &strCmdKey)
{
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttItemBase *pItem = stt_gb_find_itembase(pGuideBook, strPath);  //对应测试前准备、测试后恢复

	if (pItem == NULL)
	{
		return;
	}

	CSttItems *pRootNode = Stt_GetFirstParentItems(pItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pRootNode == NULL)
	{
		CSttItemBase *pParent = (CSttItemBase *)pItem->GetParent();
		UINT nClassID = pParent->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTDEVICE)
		{
			strName = pItem->m_strName;
		}
		else
		{
			strName = pParent->GetNamePathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
		}
	}
	else
	{
		strName = pRootNode->GetNamePathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}

	if (strCmdKey == STT_CMD_KEY_WRITE_ENA)
	{
		strName += /*_T("_投退压板整定")*/g_sLangTxt_Native_ttybzd;
	}

	if (strCmdKey == STT_CMD_KEY_WRITE_SETTING)
	{
		strName += /*_T("_修改定值整定")*/g_sLangTxt_Native_FixedValueSet;
	}
}

BOOL QSttImportDvmFileWidget::IsFirstStep()
{
	if (m_pListSort == NULL)
	{
		return FALSE;
	}

	if (m_pCurrStep == NULL)
	{
		return FALSE;
	}

	long nIndex = m_pListSort->FindIndex(m_pCurrStep);

	return (nIndex == 0);
}

BOOL QSttImportDvmFileWidget::IsLastStep()
{
	if (m_pListSort == NULL)
	{
		return FALSE;
	}

	if (m_pCurrStep == NULL)
	{
		return FALSE;
	}

	long nIndex = m_pListSort->FindIndex(m_pCurrStep);

	if (nIndex == (m_pListSort->GetCount() - 1))
	{
		return TRUE;
	}

	return FALSE;
}

//待改进：根据Step的勾选，跳过对应的步骤
CSttItems* QSttImportDvmFileWidget::GetNextStep()
{
	if (m_pListSort == NULL)
	{
		return NULL;
	}

	if (m_pCurrStep == NULL)
	{
		return NULL;
	}

	long nIndex = m_pListSort->FindIndex(m_pCurrStep);

	return (CSttItems *)m_pListSort->GetAtIndex(nIndex + 1);
}

CSttItems* QSttImportDvmFileWidget::GetPreStep()
{
	if (m_pListSort == NULL)
	{
		return NULL;
	}

	long nIndex = 0;

	if (m_pCurrStep == NULL)
	{
		nIndex = m_pListSort->GetCount() - 1;
	}
	else
	{
		nIndex = m_pListSort->FindIndex(m_pCurrStep);
	}

	return (CSttItems *)m_pListSort->GetAtIndex(nIndex - 1);
}

void QSttImportDvmFileWidget::NextClick_Finish()
{
	m_pGridEdit->ClearEmptyDatas();  //清理
	UpdateCommCmds();
	
	accept();
}

void QSttImportDvmFileWidget::UpdateCommCmds()
{
	CExBaseList *pListEdit = m_pGridEdit->m_pDatasEdit;

	if (pListEdit == NULL)
	{
		return;
	}

	CString strCmdKey = m_pCurrStep->m_strstxmlFile;
	CSttItems *pItems = (CSttItems *)m_pItems->FindByID(m_pCurrStep->m_strID);

	POS pos = pItems->GetHeadPosition();

	while (pos != NULL)
	{
		CSttCommCmd *pCommCmd = (CSttCommCmd *)pItems->GetNext(pos);

		if (pCommCmd->m_strCommCmdID != strCmdKey)
		{
			continue;
		}

		if (UpdateCommCmd(pCommCmd, pListEdit))
		{
			//下发update指令、向导中更新commcmd-update、上位机模板树中更新项目参数
			CString strPath;

			if (pItems->m_strID.GetLength() > 0)
			{
				strPath = pItems->m_strID;
				strPath += _T("$");
			}	

			strPath += pCommCmd->m_strID;

			CString strItemParas;
			pCommCmd->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, strItemParas);
			g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateItem(strPath, strItemParas, _T("commcmd"));
			g_theGbSmartGenWzd->CommCmdUpdate(pItems->m_strID, pCommCmd->m_strID, pCommCmd->m_strName, strItemParas);

			CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
			CSttItemBase *pParent = stt_gb_find_itembase(pGuideBook, pItems->m_strID);
			CSttCommCmd *pTreeCommCmd = (CSttCommCmd *)pParent->FindByID(pCommCmd->m_strID);
			pCommCmd->UpdateEx(pTreeCommCmd);
		}
	}

	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

//返回值表示是否需要参数更新
BOOL QSttImportDvmFileWidget::UpdateCommCmd(CSttCommCmd *pCommCmd, CExBaseList *pListDatas)
{
	if (pListDatas == NULL)
	{
		return FALSE;
	}

	BOOL bUpdate = FALSE;
	CSttCommCmdData *pCmd = pCommCmd->GetCommCmdData(FALSE);
	CString strDatasetPath = pCmd->m_strDatasetPath;
	CDvmDataset *pDataset = g_theGbSmartGenWzd->m_pDvmDevice->FindDatasetByPath(strDatasetPath);

	POS pos = pListDatas->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pData = (CDvmData *)pListDatas->GetNext(pos);

		if (pData->GetParent() == pDataset)
		{
			//同一个数据集，表示当前编辑的参数，属于当前通讯命令
			if (!pCmd->SetValue(pData->m_strID, pData->m_strValue))
			{
				pCmd->AddValue(pData->m_strID, pData->m_strValue);
			}

			pListDatas->Remove(pData);
			bUpdate = TRUE;
		}
	}

	return bUpdate;
}

void QSttImportDvmFileWidget::slot_PreClick()
{
	m_pGridStep->Update_ShowCurr(m_pCurrStep, TRUE);
	CSttItems *pPrev = GetPreStep();
	ShowSetp(pPrev);
	ui->pushButton_Next->setDisabled(false);
	CString strText;
	strText =/* _T("下一项")*/g_sLangTxt_Native_nextitem;
	ui->pushButton_Next->setText(strText);

	if (IsFirstStep())
	{
		ui->pushButton_Pre->setDisabled(true);
	}
}

void QSttImportDvmFileWidget::slot_NextClick()
{
	if (IsLastStep())
	{
		NextClick_Finish();
		return;
	}

	m_pGridEdit->ClearEmptyDatas();  //清理
	UpdateCommCmds();
	m_pGridStep->Update_ShowCurr(m_pCurrStep, TRUE);
	CSttItems *pNext = GetNextStep();
	ShowSetp(pNext);
	ui->pushButton_Pre->setDisabled(false);

	if (IsLastStep())
	{
		CString strText;
		strText = /*_T("完成配置")*/g_sLangTxt_Native_completeconfig;
		ui->pushButton_Next->setText(strText);
	}
}

void QSttImportDvmFileWidget::slot_CancelClick()
{
	emit sig_FreeImportDvmFileWidget();
}

//点击右上角“×”取消添加向导
void QSttImportDvmFileWidget::reject()
{
	slot_CancelClick();
}

void QSttImportDvmFileWidget::accept()
{
	emit sig_FreeImportDvmFileWidget();
}