#include "QAinDataMapDlg.h"
#include "ui_QAinDataMapDlg.h"
#include "..\..\..\..\..\AutoTest\Module\GbItemsGen\GbSmartGenWzd\GbSmartGenWzd.h"

#include "../../../XLangResource_Native.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QAinDataMapDlg::QAinDataMapDlg(QWidget *parent, CDataGroup *pAinDataMap, CDataGroup *pAinRatios) : ui(new Ui::QAinDataMapDlg)
{
	m_pDvmDevice = g_theGbSmartGenWzd->m_pDvmDevice;
	SetAinDataMap(pAinDataMap);
	SetAinRatios(pAinRatios);

    ui->setupUi(this);
	disconnect(ui->m_cmbDevMeas, SIGNAL(currentIndexChanged(int)),this,SLOT(on_m_cmbDevMeas_currentIndexChanged(int)));
	DevMeasComboBox_Init(ui->m_cmbDevMeas);
	connect(ui->m_cmbDevMeas, SIGNAL(currentIndexChanged(int)),this,SLOT(on_m_cmbDevMeas_currentIndexChanged(int)));
	InitUI();
	InitGridData();
	InitDataSetPath();
    InitLanguage();
	EnableBtns();
}

QAinDataMapDlg::~QAinDataMapDlg()
{
	m_oListDatasets.RemoveAll();
}
void QAinDataMapDlg::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui->m_labTip, g_sLangTxt_Native_DeviceModel, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->m_labDataSet, g_sLangTxt_Native_Dataset, XLang_Ctrls_QLabel);
    xlang_SetLangStrToWidget_Txt(ui->m_btnAdd, g_sLangTxt_Native_AddNew, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->m_btnDelete, g_sLangTxt_Delete, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->m_btnClearAllMap, g_sLangTxt_Native_ClearMap, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->m_btnClearClickedMap, g_sLangTxt_Native_ClearSel, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->m_btnOK, g_sLangTxt_OK, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui->m_btnCancel, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}

void QAinDataMapDlg::InitUI()
{
	m_pAinDataMapGrid = new QAinDataMapGrid(this);
	m_pAinDataSetGrid = new QAinDataMapDataSetGrid(this);

	m_pAinDataMapGrid->InitGrid();
	m_pAinDataSetGrid->InitDataSetGrid();

	ui->m_LeftLayout->insertWidget(1, m_pAinDataMapGrid);
	ui->m_RightLayout->insertWidget(1, m_pAinDataSetGrid);

	m_pAinDataMapGrid->AttachDataViewOptrInterface(this);
	m_pAinDataSetGrid->AttachDataViewOptrInterface(this);

	ui->m_edtPtPrimary->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
	ui->m_edtPtSecondary->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
	ui->m_edtCtPrimary->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
	ui->m_edtCtSecondary->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));

	CDvmData *pDevMeas = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas == NULL)
	{
		pDevMeas = m_pAinRatios->AddNewData(ID_PARA_DevMeas, _T("1")); //默认采样值为一次侧
	}

	long nDevMeas = CString_To_long(pDevMeas->m_strValue);

	if (nDevMeas <= 0)
	{
		nDevMeas = 1;
	}

	ui->m_cmbDevMeas->setCurrentIndex(nDevMeas - 1);

	CDvmData *pPtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary != NULL)
	{
		ui->m_edtPtPrimary->setText(pPtPrimary->m_strValue);
	}

	CDvmData *pPtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary != NULL)
	{
		ui->m_edtPtSecondary->setText(pPtSecondary->m_strValue);
	}

	CDvmData *pCtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary != NULL)
	{
		ui->m_edtCtPrimary->setText(pCtPrimary->m_strValue);
	}

	CDvmData *pCtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary != NULL)
	{
		ui->m_edtCtSecondary->setText(pCtSecondary->m_strValue);
	}
}

void QAinDataMapDlg::InitGridData()
{
	if (m_pAinDataMapCfg == NULL)
	{
		m_pAinDataMapCfg = new CDataGroup();

		CString strFile;
		strFile = _P_GetConfigPath();
		strFile += _T("AinDataMapCfg.xml");
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		m_pAinDataMapCfg->OpenXmlFile(strFile,CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	}

	m_pAinDataMapGrid->ShowDatas(m_pAinDataMapCfg);
}

void QAinDataMapDlg::DevMeasComboBox_Init(QComboBox *pComboBox)
{
	pComboBox->clear();
	CString strText;
	strText = _T("一次值");
	pComboBox->addItem(strText);
	strText = _T("二次值");
	pComboBox->addItem(strText);
}

void QAinDataMapDlg::InitDataSetPath()
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}

	//遥测相关的数据集，是固定的ID
	m_oListDatasets.RemoveAll();
	CStringArray strKeyArray;
	CString strDatasetKey;
	strDatasetKey = _T("dsRelayAin");
	strKeyArray.Add(strDatasetKey);
	strDatasetKey = _T("dsAin");
	strKeyArray.Add(strDatasetKey);
	m_pDvmDevice->GetDatasetList(strKeyArray, m_oListDatasets);

	POS pos = m_oListDatasets.GetHeadPosition();

	while(pos)
	{
		CDvmDataset *pDataset = (CDvmDataset *)m_oListDatasets.GetNext(pos);

		//优先显示名称
		if (pDataset->m_strName.GetLength() > 0)
		{
			ui->m_cmbDataSet->addItem(pDataset->m_strName.GetString());
		}
		else
		{
			ui->m_cmbDataSet->addItem(pDataset->m_strID.GetString());
		}
	}

	//若是打开测试记录或者重新打开映射对话框，则已经选择过数据集，此处要刷新为已选择的数据集
	CDvmDataset *pCurrDs = GetCurrentDataset();

	if (pCurrDs != NULL)
	{
		long nIndex = m_oListDatasets.FindIndex(pCurrDs);
		ui->m_cmbDataSet->setCurrentIndex(nIndex);  //刷新为当前选中的
	}
	else
	{
		ui->m_cmbDataSet->setCurrentIndex(0);  //默认显示第一个
	}
}

void QAinDataMapDlg::GetCurrentDsPath(CString &strDsPath)
{
	long nIndex = ui->m_cmbDataSet->currentIndex();

	CDvmDataset *pDataset = (CDvmDataset *)m_oListDatasets.GetAtIndex(nIndex);

	if (pDataset == NULL)
	{
		return;
	}

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDataset->GetParent();
	strDsPath = pLDevice->m_strID + _T("$");
	strDsPath += pDataset->m_strID;
}

CDvmDataset* QAinDataMapDlg::GetCurrentDataset()
{
	if (m_pAinDataMapCfg == NULL)
	{
		return NULL;
	}

	if (m_pDvmDevice == NULL)
	{
		return NULL;
	}

	CDvmDataset *pFind = NULL;
	POS pos = m_pAinDataMapCfg->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pAin = (CDvmData *)m_pAinDataMapCfg->GetNext(pos);

		if (pAin->m_strDataType.GetLength() > 0)
		{
			pFind = m_pDvmDevice->FindDatasetByPath(pAin->m_strDataType);

			if (pFind != NULL)
			{
				//遥测参数映射，映射时，只能选相同的数据集；
				break;
			}
		}
	}

	return pFind;
}

void QAinDataMapDlg::EnableBtns()
{
	ui->m_btnAdd->setDisabled(true);
	ui->m_btnDelete->setDisabled(true);
	ui->m_btnClearClickedMap->setDisabled(true);

	if (m_pAinDataMapGrid != NULL)
	{
		CDvmData *pData =  (CDvmData*)m_pAinDataMapGrid->GetCurrSelData();

		if (pData != NULL)
		{
			ui->m_btnDelete->setDisabled(false);
			ui->m_btnClearClickedMap->setDisabled(false);
		}
	}

	EnableBtns_DevMeas();
}

void QAinDataMapDlg::EnableBtns_DevMeas()
{
	ui->m_edtCtPrimary->setVisible(true);
	ui->m_edtCtSecondary->setVisible(true);
	ui->m_edtPtPrimary->setVisible(true);
	ui->m_edtPtSecondary->setVisible(true);
	ui->m_stcCtPirmary->setVisible(true);
	ui->m_stcCtSecondary->setVisible(true);
	ui->m_stcPtPirmary->setVisible(true);
	ui->m_stcPtSecondary->setVisible(true);
	ui->m_stcCt->setVisible(true);
	ui->m_stcPt->setVisible(true);
	ui->m_btnOK->setDisabled(false);

	CDvmData *pDevMeas = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas->m_strValue == _T("2"))
	{
		ui->m_edtCtPrimary->setVisible(false);
		ui->m_edtCtSecondary->setVisible(false);
		ui->m_edtPtPrimary->setVisible(false);
		ui->m_edtPtSecondary->setVisible(false);
		ui->m_stcCtPirmary->setVisible(false);
		ui->m_stcCtSecondary->setVisible(false);
		ui->m_stcPtPirmary->setVisible(false);
		ui->m_stcPtSecondary->setVisible(false);
		ui->m_stcCt->setVisible(false);
		ui->m_stcPt->setVisible(false);
		return;
	}

	CDvmData *pPtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtPrimary);
	CDvmData *pPtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtSecondary);
	CDvmData *pCtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtPrimary);
	CDvmData *pCtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pPtPrimary == NULL || pPtSecondary == NULL || pCtPrimary == NULL || pCtSecondary == NULL)
	{
		ui->m_btnOK->setDisabled(true);
		return;
	}

	if (pPtPrimary->m_strValue.IsEmpty()
		|| pPtSecondary->m_strValue.IsEmpty()
		|| pCtPrimary->m_strValue.IsEmpty()
		|| pCtSecondary->m_strValue.IsEmpty())
	{
		ui->m_btnOK->setDisabled(true);
		return;
	}
}

CDataGroup* QAinDataMapDlg::GetAinDataMap()
{
	return m_pAinDataMapCfg;
}

void QAinDataMapDlg::SetAinDataMap(CDataGroup* pAinDataMap)
{
	m_pAinDataMapCfg = pAinDataMap;
}

CDataGroup* QAinDataMapDlg::GetAinRatios()
{
	return m_pAinRatios;
}

void QAinDataMapDlg::SetAinRatios(CDataGroup* pAinRatios)
{
	m_pAinRatios = pAinRatios;

	if (pAinRatios == NULL)
	{
		m_pAinRatios = new CDataGroup();
		m_pAinRatios->m_strID = ID_AIN_RATIOS;
		m_pAinRatios->m_strName = ID_AIN_RATIOS;
	}
}

BOOL QAinDataMapDlg::IsMapValid()
{
	POS pos = m_pAinDataMapCfg->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pDataMap = (CDvmData *)m_pAinDataMapCfg->GetNext(pos);
		
		//2023-9-4  由于传递报文时，只传递了name、id、value、data-type。
		//记录数据集路径的属性，由format改为data-type
		if (pDataMap->m_strDataType.GetLength() > 0
			&& pDataMap->m_strValue.GetLength() > 0)
		{
			//包含一个有效配置，则认为配置有效；
			return TRUE;
		}
	}

	return FALSE;
}

CDvmData* QAinDataMapDlg::IsMapRepeat(const CString &strID, const CString &strDsPath)
{
	POS pos = m_pAinDataMapCfg->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pDataMap = (CDvmData *)m_pAinDataMapCfg->GetNext(pos);

		if (pDataMap->m_strDataType == strDsPath
			&& pDataMap->m_strValue == strID)
		{
			return pDataMap;
		}
	}

	return NULL;
}

void QAinDataMapDlg::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol) 
{
	EnableBtns();
}

BOOL QAinDataMapDlg::OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar)
{
	if (pGridCtrl != m_pAinDataSetGrid)
	{
		return FALSE;
	}

	//获取到左边当前item，
	CDvmData *pData =  (CDvmData *)m_pAinDataMapGrid->GetCurrSelData();

	if(pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, /* _T("请先在左侧选中需要映射的参数，然后再进行映射……") */ g_sLangTxt_Native_SelectParamFirst.GetString());
		return FALSE;
	}

	//2023-9-4  由于传递报文时，只传递了name、id、value、data-type。
	//记录数据集路径的属性，由format改为data-type
	CDvmData *pData2 = (CDvmData *)m_pAinDataSetGrid->GetCurrSelData();
	CString strDsPath;

	GetCurrentDsPath(strDsPath);
	CDvmData *pRepeatMap = IsMapRepeat(pData2->m_strID, strDsPath);

	if (pRepeatMap != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前双击的数据，已经映射到 %s，请勿重复映射！"), pRepeatMap->m_strName.GetString());
		return FALSE;
	}

	pData->m_strValue = pData2->m_strID;
	pData->m_strDataType = strDsPath;
	m_pAinDataMapGrid->UpdateData(pData);
	return TRUE;
}

void QAinDataMapDlg::on_m_btnAdd_clicked()
{
	//新增的先不做，因为默认配置的已经够用了
	//若需要新增，则应该弹一个小窗口，让输入name和id。因为目前m_pAinDataMapGrid是不允许编辑的
// 	CDvmData *pData = new CDvmData;
// 	pData->m_strName = "";
// 	pData->m_strID = "";
// 	m_pAinDataMapGrid->InsertData(pData);
}

void QAinDataMapDlg::on_m_btnDelete_clicked()
{
	if (m_pAinDataMapGrid == NULL)
	{
		return;
	}

	CDvmData *pData =  (CDvmData*)m_pAinDataMapGrid->GetCurrSelData();

	if (pData == NULL)
	{
		return;
	}

	m_pAinDataMapGrid->DeleteDataRow(pData);
}

void QAinDataMapDlg::on_m_btnClearAllMap_clicked()
{
	POS pos = m_pAinDataMapCfg->GetHeadPosition();

	while (pos != NULL)
	{
		//2023-9-4  由于传递报文时，只传递了name、id、value、data-type。
		//记录数据集路径的属性，由format改为data-type
		CDvmData *pDataMap = (CDvmData *)m_pAinDataMapCfg->GetNext(pos);
		pDataMap->m_strValue.Empty();
		pDataMap->m_strDataType.Empty();
	}
	
	m_pAinDataMapGrid->ShowDatas(m_pAinDataMapCfg);
}

void QAinDataMapDlg::on_m_btnClearClickedMap_clicked()
{
	if (m_pAinDataMapGrid == NULL)
	{
		return;
	}

	CDvmData *pData =  (CDvmData*)m_pAinDataMapGrid->GetCurrSelData();

	if (pData == NULL)
	{
		return;
	}

	//2023-9-4  由于传递报文时，只传递了name、id、value、data-type。
	//记录数据集路径的属性，由format改为data-type
	pData->m_strValue.Empty();
	pData->m_strDataType.Empty();
	m_pAinDataMapGrid->UpdateData(pData);

}

void QAinDataMapDlg::on_m_btnOK_clicked()
{
	if (! IsMapValid())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, /* _T("当前配置没找到有效的映射数据，配置无效！") */ g_sLangTxt_Native_NoValidMapData.GetString());
		this->close();
		return;
	}

	this->accept();
}

void QAinDataMapDlg::on_m_btnCancel_clicked()
{
	this->close();
}

void QAinDataMapDlg::on_m_cmbDataSet_currentIndexChanged(int index)
{
	if (index < 0)
	{
		index = ui->m_cmbDataSet->currentIndex();
	}

	CDvmDataset *pDataset = (CDvmDataset *)m_oListDatasets.GetAtIndex(index);
	m_pAinDataSetGrid->ShowDatas(pDataset);
}

void QAinDataMapDlg::on_m_cmbDevMeas_currentIndexChanged(int index)
{
	if (index < 0)
	{
		index = ui->m_cmbDevMeas->currentIndex();
	}

	CString strValue;
	strValue.Format(_T("%d"), index+1);

	CDvmData *pDevMeas = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas == NULL)
	{
		pDevMeas = m_pAinRatios->AddNewData(ID_PARA_DevMeas, strValue); 
	}
	else
	{
		pDevMeas->m_strValue = strValue;
	}

	EnableBtns_DevMeas();
}

void QAinDataMapDlg::on_m_edtPtPrimary_textChanged(const QString &arg1)
{
	CString strValue = arg1;
	strValue.trimmed();

	CDvmData *pPtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		pPtPrimary = m_pAinRatios->AddNewData(ID_PARA_PtPrimary, strValue);
	}
	else
	{
		pPtPrimary->m_strValue = strValue;
	}

	EnableBtns_DevMeas();
}

void QAinDataMapDlg::on_m_edtPtSecondary_textChanged(const QString &arg1)
{
	CString strValue = arg1;
	strValue.trimmed();

	CDvmData *pPtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		pPtSecondary = m_pAinRatios->AddNewData(ID_PARA_PtSecondary, strValue);
	}
	else
	{
		pPtSecondary->m_strValue = strValue;
	}

	EnableBtns_DevMeas();
}

void QAinDataMapDlg::on_m_edtCtPrimary_textChanged(const QString &arg1)
{
	CString strValue = arg1;
	strValue.trimmed();

	CDvmData *pCtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		pCtPrimary = m_pAinRatios->AddNewData(ID_PARA_CtPrimary, strValue);
	}
	else
	{
		pCtPrimary->m_strValue = strValue;
	}

	EnableBtns_DevMeas();
}

void QAinDataMapDlg::on_m_edtCtSecondary_textChanged(const QString &arg1)
{
	CString strValue = arg1;
	strValue.trimmed();

	CDvmData *pCtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		pCtSecondary = m_pAinRatios->AddNewData(ID_PARA_CtSecondary, strValue);
	}
	else
	{
		pCtSecondary->m_strValue = strValue;
	}

	EnableBtns_DevMeas();
}