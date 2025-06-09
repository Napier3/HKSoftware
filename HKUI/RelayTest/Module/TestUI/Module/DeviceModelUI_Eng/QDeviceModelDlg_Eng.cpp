#include "QDeviceModelDlg_Eng.h"
#include "ui_QDeviceModelDlg_Eng.h"

QDeviceModelDlg_Eng::QDeviceModelDlg_Eng(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDeviceModelDlg_Eng)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint|= Qt::WindowMaximizeButtonHint |Qt::WindowCloseButtonHint );//显示最大化最小化
    m_nDlgModeType = _FIXED_VALUE_CORRELATION_TYPE_;
    m_bHasModifyDevModel = FALSE;
	m_bHasChangedXrio = FALSE;
    m_bHasUpdateXrio = FALSE;
    m_pCharacterFolder = NULL;
 //   m_pUI_Paras = NULL;
    QFont font("Microsoft YaHei",9);
    m_pDeviceModelTreeCtrl_Eng = new QDeviceModelTreeCtrl_Eng(this,&font);
    m_pDeviceModelTreeCtrl_Eng->AttachOptrInterface(this);
    m_pDeviceModelGrid_Eng = new QDeviceModelGrid_Eng();
    m_pDeviceModelGrid_Eng->AttachDataViewOptrInterface(this);
    m_pDeviceModelGrid_Eng->SetTableFont(font);
    //m_pDeviceModelGrid_Eng->InitGrid();
    //左边树
    m_pTreeCtrlFrame = new QFrame(0);
    QVBoxLayout * TreeCtrlLayout = new QVBoxLayout(m_pTreeCtrlFrame);
    TreeCtrlLayout->addWidget(m_pDeviceModelTreeCtrl_Eng);
    ui->gridLayout->addWidget(m_pTreeCtrlFrame,4,0);
    //右边表格
    m_pGridFrame = new QFrame(0);
    ui->gridLayout->addWidget(m_pGridFrame,4,1);
    QVBoxLayout * GridLayout = new QVBoxLayout(m_pGridFrame);
    GridLayout->addWidget(m_pDeviceModelGrid_Eng);
    //中间弹簧
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(m_pTreeCtrlFrame);
    splitter->addWidget(m_pGridFrame);
    ui->gridLayout->addWidget(splitter);
    QList<int> sizes;
    sizes << 200 << 400;
    splitter->setSizes(sizes);
    //设置布局
    this->setLayout(ui->verticalLayout);

    InitUI();
    InitConnect();
}

QDeviceModelDlg_Eng::~QDeviceModelDlg_Eng()
{
	m_oDvmGridListRef.RemoveAll();
    delete ui;
}

void QDeviceModelDlg_Eng::InitXrioDeviceModel(CXDeviceModel *pXrioDeviceModel)
{
	m_pXrioDeviceModel = pXrioDeviceModel;
    m_pXrioDeviceModel->m_oCharacterLib_Show.DeleteAll();
    m_pXrioDeviceModel->m_oCharacterLib_Show = *(CCharacteristicLib*)pXrioDeviceModel->m_oCharacterLib_Global.Clone();

    //初始化确认按钮和曲线编辑按钮
    if(m_nDlgModeType == _FIXED_VALUE_CORRELATION_TYPE_)
    {
        ui->m_btnEdit->hide();
        ui->m_btnOk->setEnabled(FALSE);
    }
    else
    {
        HideTextEditDisplay();
        ui->m_btnOk->setEnabled(TRUE);
    }
    //初始化更新按钮
    CDvmLogicDevice *pCustomLogicDevice = (CDvmLogicDevice*)m_pXrioDeviceModel->m_pDvmDevice_Show->FindByID(XRIO_DEVICE_MODEL_ID_CUSTOM);
    if(pCustomLogicDevice != NULL)
    {
        ui->m_btnUpdate->setEnabled(TRUE);
    }
    else
    {
        ui->m_btnUpdate->setEnabled(FALSE);
    }

	m_pDeviceModelTreeCtrl_Eng->SetCurrentShowType(m_nDlgModeType);
    m_pDeviceModelTreeCtrl_Eng->ShowBaseListEx(m_pXrioDeviceModel->m_pDvmDevice_Show,TRUE);

	//20240815 huangliang
	ui->m_textEdit->SetExprScript(m_sEpExpressionFormat);
}

void QDeviceModelDlg_Eng::SetXrioDeviceModelUIIDAndParas(const CString &strTestMacroUI_ID, CDataGroup *pTestMacroUI_Paras)
{
    m_strUI_ID = strTestMacroUI_ID;
	m_oUI_Paras.DeleteAll();
	m_oUI_Paras.AppendClone(pTestMacroUI_Paras);
 //   m_pUI_Paras = pTestMacroUI_Paras;
}

BOOL QDeviceModelDlg_Eng::OnItemBDblClk(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
	if (pSelObj->GetClassID() == DVMCLASSID_CDVMDATASET && pSelObj->m_strID == XRIO_DEVICE_MODEL_ID_DEVICE)
    {
		QDeviceModelAttrDlg_Eng *pDeviceModelAttrDlg_Eng = new QDeviceModelAttrDlg_Eng(m_pXrioDeviceModel, this);
        pDeviceModelAttrDlg_Eng->setWindowTitle(/*_T("装置定值")*/g_sLangTxt_Xrio_DeviceSetting);
        pDeviceModelAttrDlg_Eng->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
        pDeviceModelAttrDlg_Eng->setAttribute(Qt::WA_DeleteOnClose);
        connect(pDeviceModelAttrDlg_Eng,SIGNAL(sig_UpdataDeviceAttrs(CDvmDataset*)),this,SLOT(slot_XrioDeviceModel_UpdateDeviceAttrs(CDvmDataset*)));
        pDeviceModelAttrDlg_Eng->exec();
    }
    return TRUE;
}

void QDeviceModelDlg_Eng::OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj)
{
    m_pDeviceModelGrid_Eng->ClearCurrentContents();//清空当前表格内容。

    m_oDvmGridListRef.RemoveAll();

	if (m_oXrioToDeviceModelTool.IsXrioDataset_CBCONFIGURATION(pSelObj))
	{
		m_pDeviceModelGrid_Eng->UpdateTitle(XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_CBData);
		m_pDeviceModelGrid_Eng->ShowCBDatas((CExBaseList*)pSelObj);
		ui->m_btnEdit->setEnabled(FALSE);
		return;
	}

    if (m_oXrioToDeviceModelTool.IsXrioDataset_Characteristic(pSelObj))
	{
		m_pDeviceModelGrid_Eng->UpdateTitle(XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_CBData);
		m_pDeviceModelGrid_Eng->ShowCBDatas(NULL);
		if (IsEditableCharact(((CDvmDataset*)pSelObj)->m_strDataType))
        {
            ui->m_btnEdit->setEnabled(TRUE);
        }
        else
        {
            ui->m_btnEdit->setEnabled(FALSE);
        }
		return;
	}

	if (m_oXrioToDeviceModelTool.IsXrioDataset_Device(pSelObj))
	{
		m_pDeviceModelGrid_Eng->UpdateTitle(XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_CBData);
        m_pDeviceModelGrid_Eng->ShowCBDatas(NULL);//Device节点单击不展示和OMR一致
        return;
	} 
	else
	{
		m_pDeviceModelGrid_Eng->UpdateTitle(XRIO_DEVICE_MODEL_GRID_TITLE_TYPE_NORMAL);
	}
	ui->m_btnEdit->setEnabled(FALSE);
	m_pDeviceModelGrid_Eng->AddListRef(pSelObj, &m_oDvmGridListRef);
	m_pDeviceModelGrid_Eng->ShowDatas(&m_oDvmGridListRef);
}

void QDeviceModelDlg_Eng::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
    //emit sig_InsertTextEdit();//2024-10-16 wuxinyi 北京新需求：双击时添加到编辑框，移至OnEditCellLBDblClk

//    EnableBtns();
}

BOOL QDeviceModelDlg_Eng::OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar)
{
    if(m_nDlgModeType == _FIXED_VALUE_CORRELATION_TYPE_)
    {
//        if(nCol == XRIO_PARAMETER_COL_VALUE)
//        {
//            ui->m_btnOk->setEnabled(FALSE);
//        }

//        QGV_ITEM *pItem = m_pDeviceModelGrid_Eng->GetCurrSelItem();

//        if(pItem == NULL)
//        {
//            return FALSE;
//        }

//        if(QT_GVET_EDITBOX == pItem->nDataType && pItem->m_pEditFunc != NULL)
//        {
//            ui->m_btnOk->setEnabled(FALSE);
//        }

        emit sig_InsertTextEdit();
    }

//表达式编辑界面只会在定值关联模式下才显示出来，移至上面的if分支中。
//	emit sig_InsertTextEdit();

    return TRUE;
}

void QDeviceModelDlg_Eng::OnDataEditChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{

}

void QDeviceModelDlg_Eng::HideTextEditDisplay()
{
    ui->m_btnAbs->hide();
    ui->m_btnAcos->hide();
    ui->m_btnAcosd->hide();
    ui->m_btnAddition->hide();
    ui->m_btnAsin->hide();
    ui->m_btnAsind->hide();
    ui->m_btnAtan->hide();
    ui->m_btnAtgd->hide();
    ui->m_btnCoS->hide();
    ui->m_btnCosd->hide();
    ui->m_btnDivision->hide();
    ui->m_btnExp->hide();
    ui->m_btnLeftParenthesis->hide();
    ui->m_btnMultiplication->hide();
    ui->m_btnRightParenthesis->hide();
    ui->m_btnSin->hide();
    ui->m_btnSind->hide();
    ui->m_btnSqrt->hide();
    ui->m_btnSubtraction->hide();
    ui->m_btnTan->hide();
    ui->m_btnTgd->hide();
    ui->m_textEdit->hide();
}

void QDeviceModelDlg_Eng::InitUI()
{
    this->setWindowTitle(g_sLangTxt_Xrio_TestObject);//测试对象
    ui->m_btnEdit->setText(g_sLangTxt_Edit);//编辑
    ui->m_btnImport->setText(g_sLangTxt_Import);//导入
    ui->m_btnUpdate->setText(g_sLangTxt_Xrio_Update);//更新
    ui->m_btnOk->setText(g_sLangTxt_OK);//确定
    ui->m_btnCancel->setText(g_sLangTxt_Cancel);//取消
}

void QDeviceModelDlg_Eng::InitConnect()
{
    connect(m_pDeviceModelGrid_Eng,SIGNAL(sig_EndEditCellSuccess()),this,SLOT(slot_AfterEndEditGridCellSuccess()));
    //这个connect对于判断确定按钮是否使能没有影响，暂时先去掉。
//    connect(m_pDeviceModelGrid_Eng, SIGNAL(itemClicked(QTableWidgetItem*)),this, SLOT(slot_onItemClicked(QTableWidgetItem*)));
    connect(this, SIGNAL(sig_InsertTextEdit()), this, SLOT(slot_InsertTextEdit()));
    connect(ui->m_textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(slot_TextEditChanged()));
}

void QDeviceModelDlg_Eng::slot_XrioDeviceModel_UpdateDeviceAttrs(CDvmDataset *pDataset)
{
    CDvmDataset *pDeviceAttrs = NULL;
    pDeviceAttrs = m_pXrioDeviceModel->GetDeviceAttrs();
    pDeviceAttrs->UpdateDataValue(pDataset);
    m_pXrioDeviceModel->UpdateDvmRef();
}

void QDeviceModelDlg_Eng::slot_InsertTextEdit()
{
    CExBaseObject *pSelect = GetCurrSelData();
    //QTextCursor cursor = ui->m_textEdit->textCursor();
    //cursor.insertText(pSelect->m_strName);
    //ui->m_textEdit->setTextCursor(cursor);

	//20240820 huangliang 添加对象
	if (pSelect == NULL)
		return;
	QString strFullPath = pSelect->GetIDPathEx((CExBaseObject *)pSelect->GetRoot(), false);	//20240903 huangliang 不要根目录ID

	//20241009 huangliang 区分值和名称
	QString strValue = "";
	if (g_nSettingShowType == STT_SETTING_SHOW_TYPE_INDEX_Value)
	{
		if (pSelect->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			strValue = ((CDvmData*)pSelect)->m_strValue;
		}
		else if (pSelect->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
			strValue = ((CDvmValue*)pSelect)->m_strValue;
		}
	}
	else
	{
		strValue = pSelect->m_strName;
	}

	ui->m_textEdit->InsertText(strFullPath, strValue);
	ui->m_textEdit->UpdateCursor();

}

void QDeviceModelDlg_Eng::slot_AfterEndEditGridCellSuccess()
{
    m_bHasModifyDevModel = TRUE;
//    ui->m_btnOk->setEnabled(TRUE);
}

void QDeviceModelDlg_Eng::slot_TextEditChanged()
{
    if(m_nDlgModeType == _FIXED_VALUE_CORRELATION_TYPE_)
    {
//        CString CurrText = ui->m_textEdit->toPlainText();
        ui->m_textEdit->GetExprScript(m_sEpExpressionFormat);
        if(!IsStringNumber(/*CurrText*/m_sEpExpressionFormat))
        {
            EnableBtns();
        }
        else
        {
            ui->m_btnOk->setEnabled(FALSE);
        }
    }
}

//void QDeviceModelDlg_Eng::slot_onItemClicked(QTableWidgetItem* item)
//{
//    if (item->row() < 0 || item->column() < 0)
//    {
//        return;
//    }

//    if (m_nDlgModeType == _FIXED_VALUE_CORRELATION_TYPE_)
//    {
//        ui->m_textEdit->GetExprScript(m_sEpExpressionFormat);
//        CString CurrText = ui->m_textEdit->toPlainText();
//        if (!CurrText.IsEmpty())
//        {
//            EnableBtns();
//        }
//    }
//}

void QDeviceModelDlg_Eng::EnableBtns()
{
    ui->m_btnOk->setEnabled(TRUE);
    ui->m_btnCancel->setEnabled(TRUE);
}

BOOL QDeviceModelDlg_Eng::IsEditableCharact(const CString &strCharactDataType)
{
	if ((strCharactDataType == XRIO_DEVICE_MODEL_DATA_TYPE_DISTANCE) && 
		((m_strUI_ID == STT_ORG_MACRO_DistanceTest_I) || (m_strUI_ID == STT_ORG_MACRO_DistanceSearchTest_I)))
	{
		return TRUE;
	}
	else if ((strCharactDataType == XRIO_DEVICE_MODEL_DATA_TYPE_OVERCURRENT) &&
		(m_strUI_ID == STT_ORG_MACRO_CurrInverseTimeTest_I))
	{
		return TRUE;
	}
	else if ((strCharactDataType == XRIO_DEVICE_MODEL_DATA_TYPE_DIFFERENTIAL) &&
		(m_strUI_ID == STT_ORG_MACRO_DiffTest_I))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL QDeviceModelDlg_Eng::XrioOperationSwitch(BOOL &XrioFileOperateType,const Operation &OperationType)
{
//    if(!OpenXrioFile())
//    {
//        return FALSE;
//    }
    m_pDeviceModelGrid_Eng->ClearCurrentContents();//清空当前表格内容。
    //无需调用DisConnectAll_SigSlot,后续的ShowDatas和ShowCBDatas会调用。
//    m_pDeviceModelGrid_Eng->DisConnectAll_SigSlot();
    BOOL IsSucReadXrioFile = m_pXrioDeviceModel->m_oXrio.ReadXRIOFile(m_strFilePath);

    if (IsSucReadXrioFile)
    {
        m_bHasModifyDevModel = TRUE;
    }
    XrioFileOperateType = TRUE;
    if(OperationType == Import)
    {
		//导入新的xrio后，把对应生成的设备数据模型的ID进行更新,缺省存储在_P_GetTemplatePath文件夹下,方便后续存储文件，与自动测试同步设备数据模型
// 		CString strFilePath;
// 		strFilePath = _P_GetTemplatePath();
// 		strFilePath += GetFileNameFromFilePath(m_strFilePath);
// 		strFilePath = ChangeFilePostfix(strFilePath, "xml");
		m_pXrioDeviceModel->m_pDvmDevice_Show->m_strID = GetFileTitleFromFilePath(m_strFilePath)/*strFilePath*/;
        m_oXrioToDeviceModelTool.XrioToDeviceModel(&m_pXrioDeviceModel->m_oXrio, m_pXrioDeviceModel->m_pDvmDevice_Show);
        m_oXrioToCharacterTool.XrioToCharacter(&m_pXrioDeviceModel->m_oXrio, &m_pXrioDeviceModel->m_oCharacterLib_Show);
        ui->m_btnUpdate->setEnabled(TRUE);
//        CString strFile;
//        strFile = _P_GetLibraryPath();
//		strFile += "test01.xml";
//		m_pCharacterLib_Show->SaveXmlFile(strFile, CCharacteristicXmlRWKeys::g_pXmlKeys);
    }
    else if(OperationType == Update)
    {
        m_oXrioToDeviceModelTool.UpdateDeviceModelByXrioFile(&m_pXrioDeviceModel->m_oXrio, m_pXrioDeviceModel->m_pDvmDevice_Show);
        m_oXrioToCharacterTool.UpdateCharacterByXrioFile(&m_pXrioDeviceModel->m_oXrio, &m_pXrioDeviceModel->m_oCharacterLib_Show);
    }
    m_pXrioDeviceModel->UpdateDvmRef();
//    CString strFile;
//    strFile = _P_GetLibraryPath();
//    strFile += "test01.xml";
//    m_pXrioDeviceModel->m_oCharacterLib_Show.SaveXmlFile(strFile, CCharacteristicXmlRWKeys::g_pXmlKeys);

    //测试
//    CString DestFile = _P_GetLibraryPath();
//    DestFile += "test01.xml";
//    m_pXrioDeviceModel->m_pDvmDevice_Show->SaveXmlFile(DestFile, CDataMngrXmlRWKeys::g_pXmlKeys);

//    if(m_nDlgModeType == _FIXED_VALUE_MODIFICATION_TYPE_)
//    {
//        ui->m_btnOk->setEnabled(TRUE);
//    }
//    else
//    {
//        ui->m_btnOk->setEnabled(FALSE);
//    }
	m_pDeviceModelTreeCtrl_Eng->SetCurrentShowType(m_nDlgModeType);

    if(OperationType == Import)
    {
    m_pDeviceModelTreeCtrl_Eng->ShowBaseListEx(m_pXrioDeviceModel->m_pDvmDevice_Show,TRUE);
    }
    //如果是更新操作，现在修改为展示m_pDeviceModelTreeCtrl_Eng当前的所选对象，而不是重新展示。
    else if(OperationType == Update)
    {
        CExBaseObject *pSelObj = m_pDeviceModelTreeCtrl_Eng->GetCurrSelObject();
        m_pDeviceModelTreeCtrl_Eng->ShowBaseListAfterUpdate(m_pXrioDeviceModel->m_pDvmDevice_Show,pSelObj,TRUE);
    }

    return TRUE;
}

CString QDeviceModelDlg_Eng::OpenFileDlg(const CString& OpenFileType,const CString& OpenFileTitle,BOOL bIsOpen)
{
    //CString strText = _T("XRIO文件路径");
    CString strText = /*_T("XRIO/RIO文件路径");*/OpenFileTitle;
    QFileDialog dlg(this, strText);
    dlg.setFileMode(QFileDialog::AnyFile);
    //_T("rio file(*.rio)|*.rio||")
    strText = /*_T("XRIO/RIO文件(*.xrio;*.rio)|*.xrio;*.rio||");*/OpenFileType;
    dlg.setNameFilter(strText);

    dlg.setViewMode(QFileDialog::Detail);
    dlg.setAcceptMode(QFileDialog::AcceptOpen);
//    CString strPath = _P_GetLibraryPath();
//    dlg.setDirectory(strPath);
    strText = /*_T("文件路径")*/g_sLangTxt_FilePath;
    dlg.setLabelText(QFileDialog::LookIn, strText);
    strText = /*_T("文件名")*/g_sLangTxt_Native_FileName;
    dlg.setLabelText(QFileDialog::FileName, strText);
    strText = /*_T("文件类型")*/g_sLangTxt_Native_FileType;
    dlg.setLabelText(QFileDialog::FileType, strText);
    if(bIsOpen)
    {
        dlg.setAcceptMode(QFileDialog::AcceptOpen);
        strText = /*_T("打开")*/g_sLangTxt_Open;
        dlg.setLabelText(QFileDialog::Accept, strText);
    }
    else
    {
        dlg.setAcceptMode(QFileDialog::AcceptSave);
        strText = /*_T("保存")*/g_sLangTxt_Save;
        dlg.setLabelText(QFileDialog::Accept, strText);
    }
    strText = /*_T("取消")*/g_sLangTxt_Cancel;
    dlg.setLabelText(QFileDialog::Reject, strText);
    CString m_strFileName;
    QStringList fileNames;
    if (dlg.exec() == QFileDialog::Accepted)
    {
        fileNames = dlg.selectedFiles();
        m_strFileName = fileNames.at(0);
    }
    return m_strFileName;
}

BOOL QDeviceModelDlg_Eng::OpenFile(const CString& OpenFileType,const CString& OpenFileTitle)
{
    m_strFilePath = OpenFileDlg(OpenFileType,OpenFileTitle,TRUE);

    if (m_strFilePath == _T(""))
    {
        return FALSE;
    }

    return TRUE;
}

void QDeviceModelDlg_Eng::on_m_btnImport_clicked()
{
    //对于定值关联模式，导入操作只能导入XRIO文件
    //对于定值修改模式，导入操作既能导入XRIO文件，也可以导入RIO文件。
    CString strFileName;//文件名（包括扩展名）
    CString strFileImportType;
    CString strFileImportText;
    if(_FIXED_VALUE_MODIFICATION_TYPE_ == m_nDlgModeType)
    {
        strFileImportType = IMPORT_XRIO_RIO_FILE_TYPE;
        strFileImportText = IMPORT_XRIO_RIO_FILE_TITLE;
        if(!OpenFile(strFileImportType,strFileImportText))
        {
            return;
        }
        strFileName = GetFileNameFromFilePath(m_strFilePath);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:【%s】"),g_sLangTxt_ImportFile.GetString(),strFileName.GetString());
        if(ParseFilePostfix(m_strFilePath).CompareNoCase(OPEN_FILE_TYPE_XRIO) == 0)
        {
            XrioOperationSwitch(m_bHasChangedXrio,Import);
        }
        else if(ParseFilePostfix(m_strFilePath).CompareNoCase(OPEN_FILE_TYPE_RIO) == 0)
        {
            m_pDeviceModelGrid_Eng->ClearCurrentContents();//清空当前表格内容。
            //无需调用DisConnectAll_SigSlot,后续的ShowDatas和ShowCBDatas会调用。
//            m_pDeviceModelGrid_Eng->DisConnectAll_SigSlot();
            m_oXrioTextFileToAtsCharTool.ImportCharsFromRioFile(m_strFilePath,m_pXrioDeviceModel->m_pDvmDevice_Show,&m_pXrioDeviceModel->m_oCharacterLib_Show);
            m_bHasModifyDevModel = TRUE;
            m_bHasChangedXrio = TRUE;//可能需要修改
            ui->m_btnUpdate->setEnabled(FALSE);
            m_pXrioDeviceModel->UpdateDvmRef();
            ui->m_btnOk->setEnabled(TRUE);
            m_pDeviceModelTreeCtrl_Eng->SetCurrentShowType(m_nDlgModeType);
            m_pDeviceModelTreeCtrl_Eng->ShowBaseListEx(m_pXrioDeviceModel->m_pDvmDevice_Show,TRUE);

//                CString DestFile = _P_GetLibraryPath();
//                DestFile += "test01.xml";
//                m_pXrioDeviceModel->m_pDvmDevice_Show->SaveXmlFile(DestFile, CDataMngrXmlRWKeys::g_pXmlKeys);
//                CString strFile;
//                strFile = _P_GetLibraryPath();
//                strFile += "test01.xml";
//                m_pXrioDeviceModel->m_oCharacterLib_Show.SaveXmlFile(strFile, CCharacteristicXmlRWKeys::g_pXmlKeys);
        }
    }
    else if(_FIXED_VALUE_CORRELATION_TYPE_ == m_nDlgModeType)
    {
        strFileImportType = IMPORT_XRIO_FILE_TYPE;
        strFileImportText = IMPORT_XRIO_FILE_TITLE;
        if(!OpenFile(strFileImportType,strFileImportText))
        {
            return;
        }
        strFileName = GetFileNameFromFilePath(m_strFilePath);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:【%s】"),g_sLangTxt_ImportFile.GetString(),strFileName.GetString());
        XrioOperationSwitch(m_bHasChangedXrio,Import);
    }
}

void QDeviceModelDlg_Eng::on_m_btnOk_clicked()
{
	//20240820 huangliang 
	ui->m_textEdit->GetWindowShowText(m_sEpExpressionName);
	ui->m_textEdit->GetExprScript(m_sEpExpressionFormat);
    //更新m_oCharacterLib_Global
    POS pos = m_pXrioDeviceModel->m_oCharacterLib_Show.GetHeadPosition();
    CExBaseObject *pObj = NULL;
    CExBaseObject *pFind = NULL;
    while(pos)
    {
        pObj = m_pXrioDeviceModel->m_oCharacterLib_Show.GetNext(pos);
        ASSERT(pObj != NULL);
        pFind = (CExBaseObject*)m_pXrioDeviceModel->m_oCharacterLib_Global.FindByID(pObj->m_strID);
        if (pFind != NULL)
        {
            ((CCharacterFolder*)pFind)->DeleteAll();
            ((CCharacterFolder*)pFind)->AppendClone((CCharacterFolder*)pObj);
        }
    }

    this->accept();
}

CExBaseObject* QDeviceModelDlg_Eng::GetCurrSelData()
{
	CExBaseObject *pSelect = m_pDeviceModelGrid_Eng->GetCurrSelData();
	return pSelect;
}

CExBaseObject* QDeviceModelDlg_Eng::GetCurrSelData_Global()
{
	CExBaseObject *pSelectData_Show = m_pDeviceModelGrid_Eng->GetCurrSelData();

	if (pSelectData_Show == NULL)
	{
		return NULL;
	}

	QStringList astrParentList;

	CExBaseObject *pParent = pSelectData_Show;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == DVMCLASSID_CDVMDEVICE)
		{
			break;
		}

		astrParentList.append(pParent->m_strID);
		pParent = (CExBaseObject *)pParent->GetParent();
	}

	long nCount = astrParentList.size();
	CString strPath;
	CExBaseList *pCurrList = m_pXrioDeviceModel->m_pDvmDevice_Global;
	CExBaseObject *pCurrObj = NULL,*pFind = NULL;

	for (int nIndex = nCount-1; nIndex >= 0; nIndex--)
	{
		strPath = astrParentList.at(nIndex);
		pCurrObj = pCurrList->FindByID(strPath);

		if (pCurrObj == NULL)
		{
			break;
		} 

		if (nIndex == 0)
		{
			pFind = pCurrObj;
		}
		else
		{
			pCurrList = (CExBaseList *)pCurrObj;
		}
	}

	return pFind;
}

CString QDeviceModelDlg_Eng::GetCurrSelDataPath()
{
	CExBaseObject *pSelect = m_pDeviceModelGrid_Eng->GetCurrSelData();

	if (pSelect == NULL)
	{
		return "";
	}

	CString strPath;
	strPath = pSelect->GetIDPathEx(DVMCLASSID_CDVMDEVICE,FALSE);
	return strPath;
}

void QDeviceModelDlg_Eng::on_m_btnCancel_clicked()
{
    this->close();
}

void QDeviceModelDlg_Eng::on_m_btnUpdate_clicked()
{
    CString strFileName;//文件名（包括扩展名）
    CString strFileImportType;
    CString strFileImportText;

    strFileImportType = UPDATE_XRIO_SET_CSV_TXT_FILE_TYPE;
    strFileImportText = UPDATE_XRIO_SET_CSV_TXT_FILE_TITLE;
    if(!OpenFile(strFileImportType,strFileImportText))
    {
        return;
    }
    strFileName = GetFileNameFromFilePath(m_strFilePath);
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s:【%s】"),g_sLangTxt_Xrio_LogInfo_UpdateFile.GetString(),strFileName.GetString());
    CString strFilePostfix = ParseFilePostfix(m_strFilePath);

    if(strFilePostfix.CompareNoCase(OPEN_FILE_TYPE_XRIO) == 0)
    {
        XrioOperationSwitch(m_bHasUpdateXrio,Update);
    }
    else
    {
        //TXT文件验证：
        //XRIO文件：SEL 351 ENU TU4.30 V2.200.xrio
        //TXT文件SET_T.TXT等

        //CSV文件验证：
        //XRIO文件：GE Multilin L90 V8.4x Line ENU TU4.31 V1.000.xrio
        //CSV文件：L90_ANDAHUAYLAS.csv(注意当前的CSV解析只涉及目前的CSV文件类型，CSV文件存在不同的类型，其他类型不适用)

        //SET文件验证：
        //XRIO文件：ALSTOM MiCOM P442 V71 Line ENU TU3.00 V1.000.xrio
        //SET文件：P442-1.Set
        long nModifyIndex = 0;
        CExBaseObject *pObj = NULL;
//        m_pDeviceModelGrid_Eng->ClearCurrentContents();//清空当前表格内容。
//        m_pDeviceModelGrid_Eng->DisConnectAll_SigSlot();
        //增加第四个参数，表示需要更新的表格对象链表，现在更新后不再重新使用ShowBaseListEx展示，而是直接更新表格内容。
        m_oDvmGridListRef.RemoveAll();
        m_oSettingFilesToXrioTool.SettingFilesToXrio(m_strFilePath,m_pXrioDeviceModel->m_pDvmDevice_Show,nModifyIndex,m_oDvmGridListRef);
        for(POS startPos = m_oDvmGridListRef.GetHeadPosition();startPos != NULL;)
        {
            pObj = m_oDvmGridListRef.GetNext(startPos);
            m_pDeviceModelGrid_Eng->UpdateData(pObj);
        }
        m_bHasModifyDevModel = TRUE;
        m_bHasUpdateXrio = TRUE;
//        if(m_nDlgModeType == _FIXED_VALUE_MODIFICATION_TYPE_)
//        {
//            ui->m_btnOk->setEnabled(TRUE);
//        }
//        else
//        {
//            ui->m_btnOk->setEnabled(FALSE);
//        }
//        m_pDeviceModelTreeCtrl_Eng->SetCurrentShowType(m_nDlgModeType);
//        m_pDeviceModelTreeCtrl_Eng->ShowBaseListEx(m_pXrioDeviceModel->m_pDvmDevice_Show,TRUE);
        CString strSettingFileModifyCount;
        strSettingFileModifyCount.Format(_T("%ld"),nModifyIndex);
        CXMessageBox::information(this,g_sLangTxt_Xrio_SettingFile,strSettingFileModifyCount+g_sLangTxt_Xrio_ImportRefs);
    }
}

void QDeviceModelDlg_Eng::on_m_btnSin_clicked()
{
	InsertFunc(_T("sin"));
}

void QDeviceModelDlg_Eng::on_m_btnCoS_clicked()
{
	InsertFunc(_T("cos"));
}

void QDeviceModelDlg_Eng::on_m_btnTan_clicked()
{
	InsertFunc(_T("tan"));
}

void QDeviceModelDlg_Eng::on_m_btnAsin_clicked()
{
	InsertFunc(_T("asin"));
}

void QDeviceModelDlg_Eng::on_m_btnAcos_clicked()
{
	InsertFunc(_T("acos"));
}

void QDeviceModelDlg_Eng::on_m_btnAtan_clicked()
{
	InsertFunc(_T("atan"));
}

void QDeviceModelDlg_Eng::on_m_btnSind_clicked()
{
	InsertFunc(_T("sind"));
}

void QDeviceModelDlg_Eng::on_m_btnCosd_clicked()
{
	InsertFunc(_T("cosd"));
}

void QDeviceModelDlg_Eng::on_m_btnTgd_clicked()
{
	InsertFunc(_T("tgd"));
}

void QDeviceModelDlg_Eng::on_m_btnAsind_clicked()
{
	InsertFunc(_T("asind"));
}

void QDeviceModelDlg_Eng::on_m_btnAcosd_clicked()
{
	InsertFunc(_T("acosd"));
}

void QDeviceModelDlg_Eng::on_m_btnAtgd_clicked()
{
	InsertFunc(_T("atgd"));
}

void QDeviceModelDlg_Eng::on_m_btnSqrt_clicked()
{
	InsertFunc(_T("sqrt"));
}

void QDeviceModelDlg_Eng::on_m_btnAbs_clicked()
{
	InsertFunc(_T("abs"));
}

void QDeviceModelDlg_Eng::on_m_btnExp_clicked()
{
	InsertFunc(_T("exp"));
}

void QDeviceModelDlg_Eng::on_m_btnAddition_clicked()
{
	InsertFunc(_T("+"), false);
}

void QDeviceModelDlg_Eng::on_m_btnSubtraction_clicked()
{
	InsertFunc(_T("-"), false);
}

void QDeviceModelDlg_Eng::on_m_btnMultiplication_clicked()
{
	InsertFunc(_T("*"), false);
}

void QDeviceModelDlg_Eng::on_m_btnDivision_clicked()
{
	InsertFunc(_T("/"), false);
}

void QDeviceModelDlg_Eng::on_m_btnLeftParenthesis_clicked()
{
	InsertFunc(_T("("), false);
}

void QDeviceModelDlg_Eng::on_m_btnRightParenthesis_clicked()
{
	InsertFunc(_T(")"), false);
}

void QDeviceModelDlg_Eng::on_m_btnEdit_clicked()
{
    CExBaseObject* pSelect = m_pDeviceModelTreeCtrl_Eng->GetCurrSelObject();
    CDvmDataset* pSelectDataset = (CDvmDataset*)pSelect;
    CCharacteristics oCharacteristics;
    m_pXrioDeviceModel->GetCharacteristics(&oCharacteristics,pSelectDataset);

    QCharEditMainDialog oCharEditMainDialog;
	oCharEditMainDialog.InitCharacteristics(&oCharacteristics, &m_oUI_Paras, m_strUI_ID);

    if (QDialog::Accepted == oCharEditMainDialog.exec())
    {
		if (oCharEditMainDialog.m_bCharChanged)
		{
			if (m_pCharacterFolder != NULL)
			{
				delete m_pCharacterFolder;
				m_pCharacterFolder = NULL;
			}

			oCharEditMainDialog.CharToGroupDatas(&m_oUI_Paras);
			m_pCharacterFolder = m_pXrioDeviceModel->SetCharacteristics(&oCharacteristics, pSelectDataset);
		}
    }
}

void QDeviceModelDlg_Eng::CharToGroupDatas(CDataGroup *pDatas)
{
	m_oUI_Paras.UpdateChildren(pDatas);
}

void QDeviceModelDlg_Eng::InsertFunc(const CString &strText, BOOL bFunc)
{
	if (bFunc)
	{
		ui->m_textEdit->InsertFunc(strText);
	}
	else
	{
        ui->m_textEdit->InsertText(strText, strText);
	}

	ui->m_textEdit->setFocus();
}
