#include <QMessageBox>
#include "SttIecSMVFT3OutWidget.h"
#include <QDebug>
#include <fstream>
#include <QEvent>
#include <QKeyEvent>
#include "SttIecSMVFT3OtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
//#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../../XLangResource_Native.h"

QSttIecSMVFT3OutWidget::QSttIecSMVFT3OutWidget(QFont oIecFont,QWidget *parent)
: QSttIecConfigWidgetBase(parent)
{
	m_oIecFont = oIecFont;
	SetFont(m_oIecFont);
	InitUI();
	this->installEventFilter(this);
}

QSttIecSMVFT3OutWidget::~QSttIecSMVFT3OutWidget()
{
	if (m_pIecCfgDatasSMVCopy != NULL)
	{
		m_pIecCfgDatasSMVCopy = NULL;
		delete m_pIecCfgDatasSMVCopy;
	}
}

void QSttIecSMVFT3OutWidget::InitUI()
{
	QSttIecConfigWidgetBase::InitUI();
	CreateToolbar();
	SetIecSMVFT3OutFont();

	m_pIecCfgDatasSMVCopy = new CIecCfgDatasSMV;

	m_pIecCfgDataGridBase = new CIecCfgSmvDataFT3Grid(this);
	m_pIecCfgDataGridBase->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pIecCfgDataGridBase->setFont(*g_pSttGlobalFont);
	m_pIecCfgDataGridBase->InitGrid();

	m_pMainVLayout = new QVBoxLayout;
	setLayout(m_pMainVLayout);
	m_pMainVLayout->addLayout(m_pSMVFT3OutFirstHLayout);
	m_pMainVLayout->addWidget(m_pIecCfgDataGridBase);
	m_pMainVLayout->addLayout(m_pCtrlBlocksSetHLayout);


}

void QSttIecSMVFT3OutWidget::SetIecSMVFT3OutFont()
{
	m_pBAUDComboBox->setFont(*g_pSttGlobalFont);
	m_pSmpRateComboBox->setFont(*g_pSttGlobalFont);
	m_pLabel->setFont(*g_pSttGlobalFont);
	m_Baud_Label->setFont(*g_pSttGlobalFont);
	m_pSMVFT3OutOtherSetButton->setFont(*g_pSttGlobalFont);
	m_pPkgTypeSel_Label->setFont(*g_pSttGlobalFont);
	m_pPkgTypeSelCombox->setFont(*g_pSttGlobalFont);
	m_pCRC_ComboBox->setFont(*g_pSttGlobalFont);
	m_pCRC_Label->setFont(*g_pSttGlobalFont);
}

void QSttIecSMVFT3OutWidget::CreateToolbar()
{
	CString strTemp;
	
	m_pSmpRateComboBox = new QScrollComboBox;
	m_pSmpRateComboBox->setFixedWidth(120);
	int oSmpRate[STT_IEC_SMVFT3_RATE_MAX_NUM] = {500,4000,5000,8000,10000,50000,100000};

	for (int nIndex=0; nIndex<STT_IEC_SMVFT3_RATE_MAX_NUM; nIndex++)
	{
		m_pSmpRate[nIndex]=oSmpRate[nIndex];
		QString strSmpRate=QString (tr("%1Hz")).arg(m_pSmpRate[nIndex]);
		m_pSmpRateComboBox->addItem(strSmpRate);
	}

	m_pBAUDComboBox = new QScrollComboBox;
	m_pBAUDComboBox->setFixedWidth(120);
	float m_pBaud[STT_IEC_SMVFT3_BAUD_MAX_NUM] = {2.5,5,10,20};

	for (int nIndex=0; nIndex<STT_IEC_SMVFT3_BAUD_MAX_NUM; nIndex++)
	{
		QString strBaud=QString (tr("%1Mbps")).arg(m_pBaud[nIndex]);
		m_pBAUDComboBox->addItem(strBaud);
	}

	m_pSMVFT3OutFirstHLayout = new QHBoxLayout;
	
	m_pLabel = new QLabel(strTemp,this);
	xlang_SetLangStrToWidget_Txt(m_pLabel, g_sLangTxt_IEC_SamplingRate, XLang_Ctrls_QLabel);
	// 	xlang_GetLangStrByFile(strTemp,"IEC_SamplingRate");
	m_pSMVFT3OutFirstHLayout->addWidget(m_pLabel/*new QLabel(strTemp)*/);
	m_pSMVFT3OutFirstHLayout->addWidget(m_pSmpRateComboBox);

	m_Baud_Label = new QLabel(strTemp,this);
	xlang_SetLangStrToWidget_Txt(m_Baud_Label, g_sLangTxt_IEC_BaudRate, XLang_Ctrls_QLabel);
	m_pSMVFT3OutFirstHLayout->addWidget(m_Baud_Label/*new QLabel(tr("BAUD"))*/);
	m_pSMVFT3OutFirstHLayout->addWidget(m_pBAUDComboBox);

	strTemp = _T("报文类型");
	xlang_GetLangStrByFile(strTemp,"Gradient_MessageType"); //lcq 
	m_pPkgTypeSel_Label = new QLabel(strTemp,this);
	m_pPkgTypeSelCombox = new CExBaseListComboBox(this);
	m_pPkgTypeSelCombox->SetAddEmptyString(TRUE);

	m_pSMVFT3OutFirstHLayout->addWidget(m_pPkgTypeSel_Label);
	m_pSMVFT3OutFirstHLayout->addWidget(m_pPkgTypeSelCombox);

	m_pCRC_Label =new QLabel("CRC类型选择",this);
	m_pCRC_ComboBox = new QComboBox(this);
	m_pSMVFT3OutFirstHLayout->addWidget(m_pCRC_Label);
	m_pSMVFT3OutFirstHLayout->addWidget(m_pCRC_ComboBox);
	m_pCRC_ComboBox->hide();
	m_pCRC_Label->hide();


	m_pSMVFT3OutFirstHLayout->addStretch();
	//2023/10/12 wjs 修改按钮名称为码值设置
	m_pSMVFT3OutOtherSetButton =  new QPushButton(/* _T("码值设置") */g_sLangTxt_Native_codesSetting);
	m_pSMVFT3OutFirstHLayout->addWidget(m_pSMVFT3OutOtherSetButton);
	//详细设置
	connect(m_pSMVFT3OutOtherSetButton, SIGNAL(clicked()), SLOT(slot_SMVFT3OutOtherSetClicked()));

}

void QSttIecSMVFT3OutWidget::InitData(CIecCfgDatasBase* pIecCfgDatasBase)
{
	ASSERT(pIecCfgDatasBase);
	CIecCfgDatasSMV* pIecCfgDatasSMV = (CIecCfgDatasSMV*)pIecCfgDatasBase;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();
	int nRateIndex = 0;

	switch (pSmvCommon->m_nSampleRate_FT3)
	{
	case 500:
		nRateIndex=0;
		break;
	case 4000:
		nRateIndex=1;
		break;
	case 5000:
		nRateIndex=2;
		break;
	case 8000:
		nRateIndex=3;
		break;
	case 10000:
		nRateIndex=4;
		break;
	case 50000:
		nRateIndex=5;
		break;
	case 100000:
		nRateIndex=6;
		break;
	}

	m_pSmpRateComboBox->setCurrentIndex(nRateIndex);
	m_pBAUDComboBox->setCurrentIndex(pSmvCommon->m_nBaudRate);

// 	CString strPath;
// 	strPath = _P_GetConfigPath();
// 	strPath += _T("FT3Cfg/Pub/FT3_PkgTemplates.xml");
// 
// 	if (IsFileExist(strPath))
// 	{
// 		m_oPkgTypeList.DeleteAll();
// 		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
// 		m_oPkgTypeList.OpenXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys);
// 		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
// 	}
// 
// 	m_pPkgTypeSelCombox->ShowBaseList(&m_oPkgTypeList);

	if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		m_pPkgTypeSelCombox->ShowBaseList(NULL);
		m_pPkgTypeSelCombox->hide();
		m_pPkgTypeSel_Label->hide();
		m_pCRC_ComboBox->show();
		m_pCRC_Label->show();
		m_pCRC_ComboBox->clear();
		m_pCRC_ComboBox->insertItem(STT_IEC_SMVFT3_CRC_16BYTE_VERIFICATION,"标准16字节校验");
		m_pCRC_ComboBox->insertItem(STT_IEC_SMVFT3_CRC_END_VERIFICATION,"报文末尾校验");
		//m_pCRC_ComboBox->setCurrentIndex(STT_IEC_SMVFT3_CRC_16BYTE_VERIFICATION);

		int nCrcIndex = pIecCfgDatasSMV->m_nFT3CRCType;

		if(nCrcIndex == STT_IEC_SMVFT3_CRC_14BYTE_VERIFICATION)
		{
			nCrcIndex = STT_IEC_SMVFT3_CRC_16BYTE_VERIFICATION;
		}

		m_pCRC_ComboBox->setCurrentIndex(nCrcIndex);

		UpdateDates(pIecCfgDatasSMV);
		QSttIecConfigWidgetBase::InitData(pIecCfgDatasBase);

	}
	else /*if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)*/
	{
		disconnect(m_pPkgTypeSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CurrentPkgTypeSelChanged(int)));
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += _T("FT3Cfg/Pub/FT3_PkgTemplates.xml");

	if (IsFileExist(strPath))
	{
		m_oPkgTypeList.DeleteAll();
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		m_oPkgTypeList.OpenXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	}

	m_pPkgTypeSelCombox->ShowBaseList(&m_oPkgTypeList);
	QSttIecConfigWidgetBase::InitData(pIecCfgDatasBase);

	connect(m_pPkgTypeSelCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_CurrentPkgTypeSelChanged(int)));

	//m_pPkgTypeSelCombox->setCurrentIndex(0);
	CString strFT3ID = pIecCfgDatasSMV->m_strFT3_ProtocolID;
	if (strFT3ID.isEmpty())
	{
		m_pPkgTypeSelCombox->setCurrentIndex(0);
	}
	else
	{	
		int nComboxCount = m_pPkgTypeSelCombox->GetCount();

		CDvmData *pDvmData =NULL;
		for (int i =0;i<nComboxCount;i++)
		{
			pDvmData =  (CDvmData*)m_pPkgTypeSelCombox->GetItemData(i);
			if (pDvmData != NULL)
			{
				if (pDvmData->m_strID == strFT3ID)
				{
					m_pPkgTypeSelCombox->setCurrentIndex(i);
					break;
				}
			}

		}
	}

	}

}

void QSttIecSMVFT3OutWidget::SaveData()
{
	CIecCfgDatasSMV* pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatasBase;
	CIecCfgDataSmvCommon *pSmvCommon = pIecCfgDatasSMV->GetCommonData();
	int nIndex = m_pSmpRateComboBox->currentIndex();
	pSmvCommon->m_nSampleRate_FT3 = m_pSmpRate[nIndex];
	pSmvCommon->m_nBaudRate = m_pBAUDComboBox->currentIndex();

// 	CExBaseObject *pCurObj = NULL;
// 	CIecCfg6044CommonData *pIecCfgFT3Data = NULL;
// 	POS pos = pIecCfgDatasSMV->GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pCurObj = pIecCfgDatasSMV->GetNext(pos);
// 		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044DATA)
// 		{
// 			pIecCfgFT3Data = (CIecCfg6044CommonData *)pCurObj;
// 		}
// 	}

	if(g_oSystemParas.m_nIecFormat != STT_IEC_FORMAT_61850_92)
	{
		CDvmData *pDvmData =  (CDvmData*)m_pPkgTypeSelCombox->GetCurrSelObject();
		if (pDvmData == NULL)
		{
			pIecCfgDatasSMV->m_strFT3_ProtocolID ="";

			if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
			{
				int nIndex = m_pCRC_ComboBox->currentIndex();
				pIecCfgDatasSMV->m_nFT3CRCType = nIndex;
			}
			else
			{
				pIecCfgDatasSMV->m_nFT3CRCType = 0;
			}

		}
		else
		{
			pIecCfgDatasSMV->m_strFT3_ProtocolID = pDvmData->m_strID;
			pIecCfgDatasSMV->m_nFT3CRCType = pDvmData->m_strUnit.toLong();
		}


		if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
		{
			CExBaseList oList;
	CExBaseObject *pCurObj = NULL;
	CIecCfg6044CommonData *pIecCfgFT3Data = NULL;
	POS pos = pIecCfgDatasSMV->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgDatasSMV->GetNext(pos);

				if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfgFT3Data = (CIecCfg6044CommonData *)pCurObj;

					if (pDvmData != NULL)
					{
						if (pIecCfgFT3Data->m_strProtocolID != pDvmData->m_strID)
						{
							oList.AddTail(pIecCfgFT3Data);
						}
					}
					else
					{
						if (!pIecCfgFT3Data->m_strProtocolID.isEmpty())
						{
							oList.AddTail(pIecCfgFT3Data);
		}
	}
		}
	}

			int nCount = oList.GetCount();

			if(nCount > 0)
			{
				for (int i=0;i<nCount;i++)
				{
					pIecCfgFT3Data = (CIecCfg6044CommonData *)oList.GetAt(i);
					m_pIecCfgDatasBase->Remove(pIecCfgFT3Data);

		}
	}

			oList.DeleteAll();

		}
	}


	pIecCfgDatasSMV->InitCfgDatasByCommon();
}

void QSttIecSMVFT3OutWidget::UpdateDates(CIecCfgDatasSMV* pIecCfgDatasSmvIn)
{	
	if (pIecCfgDatasSmvIn == NULL)
	{
		return;
	}

	CDvmData *pDvmData =   (CDvmData*)m_pPkgTypeSelCombox->GetCurrSelObject();

	CExBaseList oList;
	POS pos = pIecCfgDatasSmvIn->GetHeadPosition();
	CExBaseObject *pObject = NULL;
	CIecCfg6044CommonData *pIecCfgFT3Data  = NULL;

	while(pos)
	{
		pObject = pIecCfgDatasSmvIn->GetNext(pos);

		if (pObject->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfgFT3Data = (CIecCfg6044CommonData *)pObject;

			if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
			{
				if (pIecCfgFT3Data->m_nUseFlag == 1)//切换时需将勾选取消
				{
					pIecCfgFT3Data->m_nUseFlag = 0;
				}

			}

			if (pDvmData == NULL)
			{
				if (!pIecCfgFT3Data->m_strProtocolID.isEmpty())
				{
					oList.AddTail(pIecCfgFT3Data);
				}
			}
			else
			{
				if (pDvmData->m_strID != pIecCfgFT3Data->m_strProtocolID)
				{
					oList.AddTail(pIecCfgFT3Data);					
				}

			}

		}
	}


	int nCount = oList.GetCount();

	if(nCount > 0)
	{
		for (int i=0;i<nCount;i++)
		{
			pIecCfgFT3Data = (CIecCfg6044CommonData *)oList.GetAt(i);
			pIecCfgDatasSmvIn->Remove(pIecCfgFT3Data);
		}
		}

	oList.DeleteAll();
}

void QSttIecSMVFT3OutWidget::slot_CurrentPkgTypeSelChanged(int nIndex)
{
	/* 20240716 suyang 增加对报文类型的筛选，如选择国网标准22通道的FT3 ，则下发对应的FT3
	*  
	*   UpdateFT3Datas(）函数只是将表格里面对应的数据移除，并没有将对应通道删除，防止在切换通道类型时数据丢失
	*   删除是在SaveData()函数中做处理
	*/
	if (m_pIecCfgDatasBase == NULL)
	{
		return;
	}

	m_pIecCfgDatasSMVCopy->RemoveAll();
	//m_pIecCfgDatasBase->Copy(m_pIecCfgDatasSMVCopy);
	UpdateDates((CIecCfgDatasSMV*)m_pIecCfgDatasBase);
	//m_pIecCfgDatasSMVCopy->Copy(m_pIecCfgDatasBase);

	emit sig_UpdateCB_ChDatas(NULL);//更新控制块通道数据,切换时，有的标准是没有数据的，所以先将通道置为空
	m_pIecCfgDataGridBase->ShowDatas(m_pIecCfgDatasBase);
	update();
}

void QSttIecSMVFT3OutWidget::EnableAllButtons()
{
	QSttIecConfigWidgetBase::EnableAllButtons();

	if (m_pIecCfgDataGridBase == NULL)
	{
		return;
	}

	CIecCfg6044CommonData *pIecCfgFT3Data = (CIecCfg6044CommonData*)m_pIecCfgDataGridBase->GetCurrSelData();

	if (pIecCfgFT3Data == NULL)
	{
		return;
	}

	m_pPkgTypeSelCombox->SetSelByID(pIecCfgFT3Data->m_strProtocolID);
}


bool QSttIecSMVFT3OutWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) 
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Down) 
		{	
		}
		else if (keyEvent->key() == Qt::Key_Up)
		{
		}
		else if (keyEvent->key() == Qt::Key_Escape)
		{
			return true;
		}

		return false;
	}else{
		return false;
	}
}

void QSttIecSMVFT3OutWidget::slot_SMVFT3OutOtherSetClicked()
{
	long nResult = QDialog::Rejected;
	CIecCfgDatasSMV* pIecCfgDatasSMV = (CIecCfgDatasSMV*)m_pIecCfgDatasBase;
	if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)		//只有当系统参数中当前输出报文类型为柔直(FT3)创建该Dialog
	{
		QSttIecSMVFT3DCOtherSetDialog oSmvFT3DCOtherSetDlg(this);
		oSmvFT3DCOtherSetDlg.setWindowModality(Qt::WindowModal);
		oSmvFT3DCOtherSetDlg.InitData(pIecCfgDatasSMV->GetIecCfgSmvRates());
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::AttachObj(&oSmvFT3DCOtherSetDlg);
		nResult = oSmvFT3DCOtherSetDlg.exec();
		QSoftKeyBoard::ReAttachObj();
#else
		nResult = oSmvFT3DCOtherSetDlg.exec();
#endif
	}
	else
	{
		QSttIecSMVFT3OtherSetDialog oSmvFT3OtherSetDlg(FALSE,this);
		oSmvFT3OtherSetDlg.setWindowModality(Qt::WindowModal);
		oSmvFT3OtherSetDlg.InitData(pIecCfgDatasSMV->GetIecCfgSmvRates());

#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::AttachObj(&oSmvFT3OtherSetDlg);
		nResult = oSmvFT3OtherSetDlg.exec();
		QSoftKeyBoard::ReAttachObj();
#else
		nResult = oSmvFT3OtherSetDlg.exec();
#endif
	}

	if (nResult == QDialog::Accepted)
	{
		QExBaseListGridBase *pRefChsGrid = m_pIecCfgDataGridBase->GetRefChsGrid();

		if (pRefChsGrid != NULL)
		{
			pRefChsGrid->UpdateDatas();
		}
	}

}

CIecCfgDataBase* QSttIecSMVFT3OutWidget::AddNewIecCfgData()
{
	if (m_pIecCfgDatasBase == NULL)
	{
		return NULL;
	}

	if (m_pIecCfgDatasBase->GetCount()>32)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,/*_T("当前总控制块数量大于32个,无法继续添加.")*/g_sLangTxt_block.GetString());//lcq	
		return NULL;
	}

	//2024-5-21 wuxinyi 添加FT3光口不限制
// 	CIecCfgDataBase *pCfgData = NULL;
// 	POS pos = m_pIecCfgDatasBase->GetHeadPosition();
// 	while(pos)
// 	{
// 		pCfgData = (CIecCfgDataBase *)m_pIecCfgDatasBase->GetNext(pos);
// 		if (pCfgData->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
// 		{
// 			long nFiberCount = CCfgDataMngrConstGlobal::GetAppPortFT3Num_ST();
// 			int nGirdRowCount = m_pIecCfgDataGridBase->rowCount();
// 
// 			if (nGirdRowCount >= nFiberCount && nFiberCount >= 0)
// 			{
// 				QMessageBox::information(this, tr("提示"),tr("光口已全部占用，当前无可选择的光口！"));
// 				return NULL;
// 			}
// 		}
// 	}

	CDvmData *pDvmData =  (CDvmData*)m_pPkgTypeSelCombox->GetCurrSelObject();

	if (pDvmData == NULL)
	{
		return m_pIecCfgDatasBase->AddNewIecCfgData();
	}
	
	CString strPath;
	if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		strPath = _P_GetConfigPath();
		strPath += _T("FT3Cfg/Pub-DC/");
	}
	else if(g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
	{
	strPath = _P_GetConfigPath();
	strPath += _T("FT3Cfg/Pub/");
	}
	strPath += pDvmData->m_strValue;

	if (!IsFileExist(strPath))
	{
		return m_pIecCfgDatasBase->AddNewIecCfgData();
	}

	CIecCfg6044CommonData *pData = NULL;
	pData = (CIecCfg6044CommonData*)m_pIecCfgDatasBase->CreateIecCfgData();
	BOOL b = pData->OpenXmlFile(strPath, pData->GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	m_pIecCfgDatasBase->AddNewChild(pData);
	pData->m_strProtocolID = pDvmData->m_strID;
	return pData;
}

