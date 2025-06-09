#include "SttCommCmdWzd_DsWriteWidget.h"
#include "ui_SttCommCmdWzd_DsWriteWidget.h"
#include "..\..\SttTestCtrl\SttTestAppBase.h"
#include "..\..\..\..\Module\BaseClass\QT\ExBaseListComboBox.h"
#include "SttCommCmdWzdMainWidget.h"

//2022-09-09  lijunqing
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

void QSttCommCmdWzd_DsWriteWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
// 	if (pGridCtrl == m_pSrcDataGrid)
// 	{
// 		m_pSelSrc = (CDvmData *)m_pSrcDataGrid->GetCurrSelData();
// 	}
// 
// 	if (pGridCtrl == m_pDesDataGrid)
// 	{
// 		m_pSelDes = (CDvmData *)m_pDesDataGrid->GetCurrSelData();
// 	}
// 
// 	EnableBtns();
}

QSttCommCmdWzd_DsWriteWidget::QSttCommCmdWzd_DsWriteWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCommCmdWzd_DsWriteWidget)
{
    ui->setupUi(this);
	
	InitLanguage();
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	m_font = font;
	UI_SetFont();
	ui->lineEdit_DS->setReadOnly(true);
	m_pDatasetDes = NULL;
	m_pDatasetSrc = NULL;
	//m_pSelSrc = NULL;
	//m_pSelDes = NULL;
	m_pSetpWzd = NULL;

	m_cmbSettingZone = new CSettingZoneComboBox(this);
	m_cmbSettingZone->setObjectName("m_cmbSettingZone");
	m_cmbSettingZone->SetBoxSize(font.pixelSize(), 20);
	m_cmbSettingZone->SetDefaultVisibleItems();
	connect(m_cmbSettingZone, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cmbSettingZone_currentIndexChanged(int)));
	ui->horizontalLayout_Ds->insertWidget(3, m_cmbSettingZone);

	m_cmbDelayBft = new CCmdDelayComboBox(this);
	m_cmbDelayBft->setObjectName("m_cmbDelayBft");
	m_cmbDelayBft->SetBoxSize(font.pixelSize(), 20);
	m_cmbDelayBft->SetDefaultVisibleItems();
	connect(m_cmbDelayBft, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cmbDelayBft_currentIndexChanged(int)));
	ui->horizontalLayout_Ds->insertWidget(5, m_cmbDelayBft);

	m_cmbDelayAft = new CCmdDelayComboBox(this);
	m_cmbDelayAft->setObjectName("m_cmbDelayAft");
	m_cmbDelayAft->SetBoxSize(font.pixelSize(), 20);
	m_cmbDelayAft->SetDefaultVisibleItems();
	connect(m_cmbDelayAft, SIGNAL(currentIndexChanged(int)), this, SLOT(on_m_cmbDelayAft_currentIndexChanged(int)));
	ui->horizontalLayout_Ds->insertWidget(7, m_cmbDelayAft);

// 	m_pSrcDataGrid = new CSttCmdWzdGrid_DsData(this);
// 	m_pSrcDataGrid->m_nGridType = DSDATA_GRID_TYPE_SRC;
// 	m_pSrcDataGrid->InitGrid();
// 	m_pSrcDataGrid->AttachDataViewOptrInterface(this);
// 	ui->horizontalLayout_SRC->insertWidget(0, m_pSrcDataGrid);

	m_pDesDataGrid = new CSttCmdWzdDsEditGrid(this);
	m_pDesDataGrid->InitTypeRwOptr(COMMCMD_RWOPTR_WRITE);
	//m_pDesDataGrid->m_nGridType = DSDATA_GRID_TYPE_DES;
	m_pDesDataGrid->InitGrid();
	m_pDesDataGrid->AttachDataViewOptrInterface(this);
	ui->horizontalLayout_DES->insertWidget(0, m_pDesDataGrid);

	InitSettingZone();
	m_cmbDelayAft->Init(g_theGbSmartGenWzd->m_pCmdDelay);
	m_cmbDelayBft->Init(g_theGbSmartGenWzd->m_pCmdDelay);

	connect(m_pDesDataGrid,SIGNAL(sig_CmdWzd_UpdateData(CDvmData*)),this,
		SLOT(slot_CmdWzd_UpdateData(CDvmData*)),Qt::DirectConnection);

// 	connect(ui->pushButton_AddAll,SIGNAL(clicked()),this,SLOT(slot_AddAllClick()));
// 	connect(ui->pushButton_AddOne,SIGNAL(clicked()),this,SLOT(slot_AddOneClick()));
// 	connect(ui->pushButton_RemoveAll,SIGNAL(clicked()),this,SLOT(slot_RemoveAllClick()));
// 	connect(ui->pushButton_RemoveOne,SIGNAL(clicked()),this,SLOT(slot_RemoveOneClick()));
// 	connect(ui->pushButton_AddAs0,SIGNAL(clicked()),this,SLOT(slot_AddAs_0_Click()));
// 	connect(ui->pushButton_AddAs1,SIGNAL(clicked()),this,SLOT(slot_AddAs_1_Click()));

	ui->label_DS->hide();
	ui->lineEdit_DS->hide();
}

QSttCommCmdWzd_DsWriteWidget::~QSttCommCmdWzd_DsWriteWidget()
{
	delete ui;

	if(m_cmbSettingZone)
	{
		delete m_cmbSettingZone;
		m_cmbSettingZone = NULL;
	}
	
	if(m_cmbDelayAft)
	{
		delete m_cmbDelayAft;
		m_cmbDelayAft = NULL;
	}

	if(m_cmbDelayBft)
	{
		delete m_cmbDelayBft;
		m_cmbDelayBft = NULL;
	}
}

void QSttCommCmdWzd_DsWriteWidget::UI_SetFont()
{
	ui->label_DS->setFont(m_font);
	ui->label_SettingZone->setFont(m_font);
	ui->lineEdit_DS->setFont(m_font);
// 	ui->pushButton_AddAll->setFont(m_font);
// 	ui->pushButton_AddOne->setFont(m_font);
// 	ui->pushButton_RemoveAll->setFont(m_font);
// 	ui->pushButton_RemoveOne->setFont(m_font);
// 	ui->pushButton_AddAs0->setFont(m_font);
// 	ui->pushButton_AddAs1->setFont(m_font);
	ui->m_txtDelayAft->setFont(m_font);
	ui->m_txtDelayBft->setFont(m_font);
}

void QSttCommCmdWzd_DsWriteWidget::InitSettingZone()
{
	m_cmbSettingZone->Init();
}

/*
void QSttCommCmdWzd_DsWriteWidget::EnableBtns()
{
	ui->pushButton_AddAll->setDisabled(false);
	ui->pushButton_AddOne->setDisabled(false);
	ui->pushButton_RemoveAll->setDisabled(false);
	ui->pushButton_RemoveOne->setDisabled(false);
	ui->pushButton_AddAs0->setDisabled(false);
	ui->pushButton_AddAs1->setDisabled(false);

	if (m_pDatasetSrc == NULL)
	{
		ui->pushButton_AddAll->setDisabled(true);
	}

	if (m_pDatasetSrc != NULL && m_pDatasetSrc->GetCount() == 0)
	{
		ui->pushButton_AddAll->setDisabled(true);
	}

	if (m_pDatasetSrc != NULL && m_pDatasetDes != NULL)
	{
		if (m_pDatasetSrc->GetCount() == m_pDatasetDes->GetCount())
		{
			ui->pushButton_AddAll->setDisabled(true);
		}
	}

	if (m_pDatasetDes == NULL)
	{
		ui->pushButton_RemoveAll->setDisabled(true);
	}

	if (m_pDatasetDes != NULL && m_pDatasetDes->GetCount() == 0)
	{
		ui->pushButton_RemoveAll->setDisabled(true);
	}

	//CDvmData *pSelSrc = (CDvmData *)m_pSrcDataGrid->GetCurrSelData();

	if (m_pSelSrc == NULL)
	{
		ui->pushButton_AddOne->setDisabled(true);
		ui->pushButton_AddAs0->setDisabled(true);
		ui->pushButton_AddAs1->setDisabled(true);
	}

	//CDvmData *pSelDes = (CDvmData *)m_pDesDataGrid->GetCurrSelData();

	if (m_pSelDes == NULL)
	{
		ui->pushButton_RemoveOne->setDisabled(true);
	}
}
*/

void QSttCommCmdWzd_DsWriteWidget::EnableSettingZone(const CString &strDsPath)
{
	if (strDsPath.Find(_T("Setting")) >= 0)
	{
		m_cmbSettingZone->setDisabled(false);

		int index = m_cmbSettingZone->currentIndex();
		m_pSetpWzd->m_nZoneIndex = index;
	}
	else
	{
		m_cmbSettingZone->setDisabled(true);
	}
}

/*
形参pCmdGrp， 其数据结构如下：结构中的data应该显示到des表格

<group id="WriteSetting" data-type="write" value="">
	<group id="PT2201APROT$LLN0$dsSetting1" data-type="">
		<data id="PDIF1$SG$StrValSG" data-type="STRUCT" value="">
			<value id="PDIF1$SG$StrValSG$setMag$f" data-type="FLOAT" value=""/>
		</data>
		<data id="PDIF2$SG$StrValSG" data-type="STRUCT" value="">
			<value id="PDIF2$SG$StrValSG$setMag$f" data-type="FLOAT" value=""/>
		</data>
		……
	</group>
</group>
*/
void QSttCommCmdWzd_DsWriteWidget::UpdateShow(CDataGroup *pCmdGrp)
{
	m_pDesDataGrid->ShowDatas(NULL);
	//写指令，只有一个数据集
	m_pDatasetDes = (CDataGroup *)pCmdGrp->GetHead();

	if (m_pDatasetDes == NULL)
	{
		//EnableBtns();
		return;
	}

	ui->lineEdit_DS->setText(m_pDatasetDes->m_strID);
	m_pDesDataGrid->ShowDatas(m_pDatasetDes);
	m_pDatasetSrc = g_theGbSmartGenWzd->FindDatasetByPath(m_pDatasetDes->m_strID);
	//m_pSrcDataGrid->ShowDatas(m_pDatasetSrc);
	//m_pSelDes = NULL;
	//m_pSelSrc = NULL;

	//定值区
	if (m_pSetpWzd->m_nZoneIndex != -1)
	{
		m_cmbSettingZone->setCurrentIndex(m_pSetpWzd->m_nZoneIndex);
	}
	else
	{
		m_cmbSettingZone->setCurrentIndex(0);
	}

	//通讯前延时
	CDvmData *pDelay = (CDvmData *)g_theGbSmartGenWzd->m_pCmdDelay->FindByID(m_pSetpWzd->m_strDelayBft);
	long nIndex = 0;

	if (pDelay != NULL)
	{
		nIndex = g_theGbSmartGenWzd->m_pCmdDelay->FindIndex(pDelay);
	}

	m_cmbDelayBft->setCurrentIndex(nIndex);

	//通讯后延时
	pDelay = (CDvmData *)g_theGbSmartGenWzd->m_pCmdDelay->FindByID(m_pSetpWzd->m_strDelayAft);
	nIndex = 0;

	if (pDelay != NULL)
	{
		nIndex = g_theGbSmartGenWzd->m_pCmdDelay->FindIndex(pDelay);
	}

	m_cmbDelayAft->setCurrentIndex(nIndex);
	
	EnableSettingZone(m_pDatasetDes->m_strID);
	//EnableBtns();
}

void QSttCommCmdWzd_DsWriteWidget::ShowDatas(CDataGroup* pRef, CDataGroup* pBK)
{
	m_pDesDataGrid->m_pDataGroupBK = pBK;
	UpdateShow(pRef);
}

/*
//添加全部参数到目标
void QSttCommCmdWzd_DsWriteWidget::slot_AddAllClick()
{
	if (m_pDatasetSrc == NULL || m_pDatasetDes == NULL)
	{
		return;
	}

	POS pos = m_pDatasetSrc->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pSrcData = (CDvmData *)m_pDatasetSrc->GetNext(pos);

		if (m_pDatasetDes->FindByID(pSrcData->m_strID) != NULL)
		{
			continue;
		}

		CDvmData *pNew = new CDvmData;
		pSrcData->CopyOwn(pNew);
		m_pDatasetDes->AddNewChild(pNew);
	}

	m_pDesDataGrid->ShowDatas(m_pDatasetDes);
	EnableBtns();
}

//添加选中的参数到目标
void QSttCommCmdWzd_DsWriteWidget::slot_AddOneClick()
{
	if (m_pSelSrc == NULL)
	{
		return;
	}

	if (m_pDatasetDes->FindByID(m_pSelSrc->m_strID) != NULL)
	{
		return;
	}

	CDvmData *pNew = new CDvmData;
	m_pSelSrc->CopyOwn(pNew);
	m_pDatasetDes->AddNewChild(pNew);
	m_pDesDataGrid->InsertData(pNew);
	EnableBtns();
}

//移除所有目标参数
void QSttCommCmdWzd_DsWriteWidget::slot_RemoveAllClick()
{
	if (m_pDatasetDes == NULL)
	{
		return;
	}

	m_pDatasetDes->DeleteAll();
	m_pDesDataGrid->ShowDatas(NULL);
	m_pSelDes = NULL;
	EnableBtns();
}

//移除选中的目标参数
void QSttCommCmdWzd_DsWriteWidget::slot_RemoveOneClick()
{
	if (m_pSelDes == NULL)
	{
		return;
	}

	m_pDesDataGrid->DeleteDataRow(m_pSelDes);
	m_pSelDes = NULL;
	EnableBtns();
}

//添加选中的参数到目标，并且将目标参数的值设置为0；
void QSttCommCmdWzd_DsWriteWidget::slot_AddAs_0_Click()
{
	if (m_pSelSrc == NULL)
	{
		return;
	}

	CDvmData *pDes = (CDvmData *)m_pDatasetDes->FindByID(m_pSelSrc->m_strID);

	if (pDes != NULL)
	{
		pDes->m_strValue = _T("0");
		m_pDesDataGrid->UpdateData(pDes);
		EnableBtns();
		return;
	}

	CDvmData *pNew = new CDvmData;
	m_pSelSrc->CopyOwn(pNew);
	pNew->m_strValue = _T("0");
	m_pDatasetDes->AddNewChild(pNew);
	m_pDesDataGrid->InsertData(pNew);
	EnableBtns();
}

//添加选中的参数到目标，并且将目标参数的值设置为1；
void QSttCommCmdWzd_DsWriteWidget::slot_AddAs_1_Click()
{
	if (m_pSelSrc == NULL)
	{
		return;
	}

	CDvmData *pDes = (CDvmData *)m_pDatasetDes->FindByID(m_pSelSrc->m_strID);

	if (pDes != NULL)
	{
		pDes->m_strValue = _T("1");
		m_pDesDataGrid->UpdateData(pDes);
		EnableBtns();
		return;
	}

	CDvmData *pNew = new CDvmData;
	m_pSelSrc->CopyOwn(pNew);
	pNew->m_strValue = _T("1");
	m_pDatasetDes->AddNewChild(pNew);
	m_pDesDataGrid->InsertData(pNew);
	EnableBtns();
}
*/

//更新修改过的数据，到设备数据模型中
void QSttCommCmdWzd_DsWriteWidget::slot_CmdWzd_UpdateData(CDvmData *pDvmData)
{
	if (m_pDatasetSrc == NULL)
	{
		m_pDatasetSrc = g_theGbSmartGenWzd->FindDatasetByPath(m_pDatasetDes->m_strID);
	}

	CDvmData *pData = (CDvmData *)m_pDatasetSrc->FindByID(pDvmData->m_strID);

	if (pData != NULL)
	{
		pData->m_strValue = pDvmData->m_strValue;
	}
}

void QSttCommCmdWzd_DsWriteWidget::on_m_cmbSettingZone_currentIndexChanged(int index)
{
	if (index < 0)
	{
		index = m_cmbSettingZone->currentIndex();
	}

	if (m_pSetpWzd != NULL)
	{
		m_pSetpWzd->m_nZoneIndex = index;
	}
}

void QSttCommCmdWzd_DsWriteWidget::on_m_cmbDelayBft_currentIndexChanged(int index)
{
	CString strDelay = m_cmbDelayBft->GetCmdDelay();

	if (m_pSetpWzd != NULL)
	{
		m_pSetpWzd->m_strDelayBft = strDelay;
		QSttCommCmdWzdMainWidget* pMain = (QSttCommCmdWzdMainWidget*)parentWidget();
		if(m_pSetpWzd->m_pCmdGrpBk->m_strID == "WriteSetting")
		{
			pMain->m_strBFDelayTime_Setting = strDelay;
		}
		else if (m_pSetpWzd->m_pCmdGrpBk->m_strID == "WriteEna")
		{
			pMain->m_strBFDelayTime_Ena = strDelay;
		}
		else if (m_pSetpWzd->m_pCmdGrpBk->m_strID == "WriteParameter")
		{
			pMain->m_strBFDelayTime_Parameter = strDelay;
		}
	}
}

void QSttCommCmdWzd_DsWriteWidget::on_m_cmbDelayAft_currentIndexChanged(int index)
{
	CString strDelay = m_cmbDelayAft->GetCmdDelay();

	if (m_pSetpWzd != NULL)
	{
		m_pSetpWzd->m_strDelayAft = strDelay;
		QSttCommCmdWzdMainWidget* pMain = (QSttCommCmdWzdMainWidget*)parentWidget();
		if(m_pSetpWzd->m_pCmdGrpBk->m_strID == "WriteSetting")
		{
			pMain->m_strAFTDelayTime_Setting = strDelay;
		}
		else if (m_pSetpWzd->m_pCmdGrpBk->m_strID == "WriteEna")
		{
			pMain->m_strAFTDelayTime_Ena = strDelay;
		}
		else if (m_pSetpWzd->m_pCmdGrpBk->m_strID == "WriteParameter")
		{
			pMain->m_strAFTDelayTime_Parameter = strDelay;
		}
	}
}void QSttCommCmdWzd_DsWriteWidget::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->label_DS,g_sLangTxt_DataSet,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_SettingZone,g_sLangTxt_FixedValueRegion,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtDelayBft,g_sLangTxt_ComictnFront+"(ms)",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_txtDelayAft,g_sLangTxt_ComictnLater+"(ms)",XLang_Ctrls_QLabel);
}
