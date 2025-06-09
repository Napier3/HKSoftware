#include "RemoteCtrlBtnWidget.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../Module/XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../../../../Module/DataMngr/DvmDevice.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "SttMacroParaEditViewRemoteCtrl.h"
#include "../SttTestCntrFrameBase.h"

QRemoteCtrlBtnWidget::QRemoteCtrlBtnWidget(QWidget *parent)
	: QWidget(parent)
{
	m_pMain_VLayout = NULL;
	m_pHLayout = NULL;
	m_pBtn_HLayout = NULL;
	m_pVLayout = NULL;
	m_pRemoteCtrlGridFirst = NULL;
	m_pRemoteCtrlGridSecond = NULL;

	m_pInterSelect_ComboBox = NULL;
	m_pChannelSelect_ComboBox = NULL;
	m_pDataType_LineEdit = NULL;
	m_pOperationSelect_ComboBox = NULL;
	m_pRemoteCtrlPre_Button = NULL;
	m_pRemoteCtrlExe_Button = NULL;
	m_pRemoteCtrlCancel_Button = NULL;
	m_pReadCondition = NULL;
	m_pCondition_LineEdit = NULL;
	m_pBtnClearOperationRecords = NULL;
	m_pBtnClearEventRecords = NULL;

	initUI();
	SetFont();
}

QRemoteCtrlBtnWidget::~QRemoteCtrlBtnWidget()
{
	DeleteEnaInterDatas();
//	DeleteEnaChDatas();
	m_oEnaChDatasRef.RemoveAll();
}

void QRemoteCtrlBtnWidget::DeleteEnaInterDatas()
{
	CExBaseList *pChildList = NULL;
	POS pos = m_oEnaInterDatasRef.GetHeadPosition();

	while(pos)
	{
		pChildList = (CExBaseList *)m_oEnaInterDatasRef.GetNext(pos);
		pChildList->RemoveAll();
	}

	m_oEnaInterDatasRef.DeleteAll();
}

// void QRemoteCtrlBtnWidget::DeleteEnaChDatas()
// {
// 	CExBaseList *pChildList = NULL;
// 	POS pos = m_oEnaChDatasRef.GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pChildList = (CExBaseList *)m_oEnaChDatasRef.GetNext(pos);
// 		pChildList->RemoveAll();
// 	}
// 	
// 	m_oEnaChDatasRef.DeleteAll();
// }

void QRemoteCtrlBtnWidget::SetFont()
{
	m_pInterSelect->setFont(*g_pSttGlobalFont);
	m_pInterSelect_ComboBox->setFont(*g_pSttGlobalFont);
	m_pChannelSelect->setFont(*g_pSttGlobalFont);
	m_pChannelSelect_ComboBox->setFont(*g_pSttGlobalFont);
	m_pDataType->setFont(*g_pSttGlobalFont);
	m_pDataType_LineEdit->setFont(*g_pSttGlobalFont);
	m_pOperationSelect->setFont(*g_pSttGlobalFont);
	m_pOperationSelect_ComboBox->setFont(*g_pSttGlobalFont);
	m_pRemoteCtrlPre_Button->setFont(*g_pSttGlobalFont);
	m_pRemoteCtrlExe_Button->setFont(*g_pSttGlobalFont);
	m_pRemoteCtrlCancel_Button->setFont(*g_pSttGlobalFont);
	m_pReadCondition->setFont(*g_pSttGlobalFont);
	m_pCondition_LineEdit->setFont(*g_pSttGlobalFont);
	m_pBtnClearOperationRecords->setFont(*g_pSttGlobalFont);
	m_pBtnClearEventRecords->setFont(*g_pSttGlobalFont);
}

void QRemoteCtrlBtnWidget::initUI()
{
	CString strText;
	strText = _T("间隔选择");
	m_pInterSelect =new QLabel(this);
	m_pInterSelect->setText(strText);
	m_pInterSelect_ComboBox = new CExBaseListComboBox(this);
	m_pInterSelect_ComboBox->setFixedWidth(130);
	strText = _T("通道选择");
	m_pChannelSelect=new QLabel(this);
	m_pChannelSelect->setText(strText);
	m_pChannelSelect_ComboBox = new CExBaseListComboBox(this);
	//m_pChannelSelect_ComboBox = new QScrollComboBox(this);
	m_pChannelSelect_ComboBox->setFixedWidth(500);
	strText = _T("数据类型");
	m_pDataType=new QLabel(this);
	m_pDataType->setText(strText);
	m_pDataType_LineEdit = new QSttLineEdit(this);
	m_pDataType_LineEdit->setFixedWidth(70);
	strText = _T("操作选择");
	m_pOperationSelect=new QLabel(this);
	m_pOperationSelect->setText(strText);
	m_pOperationSelect_ComboBox = new QScrollComboBox(this);
	m_pOperationSelect_ComboBox->setFixedWidth(130);
	strText = _T("遥控预置");
	m_pRemoteCtrlPre_Button = new QPushButton(strText);
	m_pRemoteCtrlPre_Button->setFixedWidth(130);
	strText = _T("遥控执行");
	m_pRemoteCtrlExe_Button = new QPushButton(strText);
	m_pRemoteCtrlExe_Button->setFixedWidth(130);
	m_pRemoteCtrlExe_Button->setEnabled(false);
	strText = _T("遥控撤销");
	m_pRemoteCtrlCancel_Button = new QPushButton(strText);
	m_pRemoteCtrlCancel_Button->setFixedWidth(130);
	m_pRemoteCtrlCancel_Button->setEnabled(false);


	strText = _T("清空操作记录");
	m_pBtnClearOperationRecords  = new QPushButton(this);
	m_pBtnClearOperationRecords->setText(strText);
	strText = _T("清空事件记录");
	m_pBtnClearEventRecords  = new QPushButton(this);
	m_pBtnClearEventRecords->setText(strText);

	strText = _T("读状态");
	m_pReadCondition = new QPushButton(strText);
	m_pReadCondition->hide();
	m_pCondition_LineEdit = new QSttLineEdit(this);
	m_pCondition_LineEdit->setFixedWidth(70);
	m_pCondition_LineEdit->hide();

	m_pHLayout = new QHBoxLayout();
	m_pHLayout->addWidget(m_pInterSelect);
	m_pHLayout->addWidget(m_pInterSelect_ComboBox);
	m_pHLayout->addWidget(m_pChannelSelect);
	m_pHLayout->addWidget(m_pChannelSelect_ComboBox);
	m_pHLayout->addWidget(m_pDataType);
	m_pHLayout->addWidget(m_pDataType_LineEdit);
	m_pHLayout->addStretch();

	m_pBtn_HLayout = new QHBoxLayout();
	m_pBtn_HLayout->addWidget(m_pOperationSelect);
	m_pBtn_HLayout->addWidget(m_pOperationSelect_ComboBox);
	m_pBtn_HLayout->addWidget(m_pRemoteCtrlPre_Button);
	m_pBtn_HLayout->addWidget(m_pRemoteCtrlExe_Button);
	m_pBtn_HLayout->addWidget(m_pRemoteCtrlCancel_Button);
	m_pBtn_HLayout->addWidget(m_pReadCondition);
	m_pBtn_HLayout->addWidget(m_pCondition_LineEdit);
	m_pBtn_HLayout->addWidget(m_pBtnClearOperationRecords);
	m_pBtn_HLayout->addWidget(m_pBtnClearEventRecords);
	m_pBtn_HLayout->addStretch();

	m_pVLayout = new QVBoxLayout();
	m_pRemoteCtrlGridFirst = new QRemoteCtrlTable(REMOTECTRL_TABLE_First);
	m_pVLayout = new QVBoxLayout();
	m_pRemoteCtrlGridSecond = new QRemoteCtrlTable(REMOTECTRL_TABLE_Second);
	m_pVLayout->addLayout(m_pHLayout);
	m_pVLayout->addLayout(m_pBtn_HLayout);
	m_pVLayout->addWidget(m_pRemoteCtrlGridFirst);
	m_pVLayout->addWidget(m_pRemoteCtrlGridSecond);

	setLayout(m_pVLayout);

	initInterSelectData();

	connect(m_pBtnClearOperationRecords, SIGNAL(clicked()), this, SLOT(slot_btn_ClearOperationRecordsClicked()));	
	connect(m_pBtnClearEventRecords, SIGNAL(clicked()), this, SLOT(slot_btn_ClearClearEventRecordsClicked()));	

}

void QRemoteCtrlBtnWidget::initInterSelectData()
{
	DeleteEnaInterDatas();
	CDvmDevice* pDvmDevice = g_pTheSttTestApp->m_pDvmDevice;
// 	if (g_theTestCntrFrame->m_pEngineClientWidget == NULL)
// 	{
// 		g_theTestCntrFrame->CreateEngineClientWidget();
// 	}
// 
// 
// 	CDvmDevice* pDvmDevice = g_theTestCntrFrame->m_pEngineClientWidget->m_pDvmDevice;

	if (pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDvmDatasetRef = NULL,*pCurrDataset = NULL;
	POS pos = pDvmDevice->GetHeadPosition();
	CExBaseList *pCurObj = NULL;
	
	while(pos)
	{
		pCurObj = (CExBaseList*)pDvmDevice->GetNext(pos);

		if (pCurObj->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		if (pCurObj->m_strID == _T("report"))
		{
			continue;
		}

		pDvmDatasetRef = new CDvmDataset;
		m_oEnaInterDatasRef.AddNewChild(pDvmDatasetRef);
		pDvmDatasetRef->m_strName = pCurObj->m_strName;
		pDvmDatasetRef->m_strID = pCurObj->m_strID;

		POS pos_dataset = pCurObj->GetHeadPosition();
		long nIndex = 0;

		while(pos_dataset)
		{
			pCurrDataset = (CDvmDataset *)pCurObj->GetNext(pos_dataset);

			if (pCurrDataset->m_strID.Find(g_strPxDataSetIDKey[PX_DSID_dsEna]) >= 0)
			{
				pDvmDatasetRef->Append(*pCurrDataset);

				if (nIndex == 0)//将对应的ID设置为第一个遥控数据集的路径,方便后续从装置读取遥控数据
				{
					pDvmDatasetRef->m_strID.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());
				}

				nIndex++;
			}
			else if (pCurrDataset->m_strID.Find(g_strPxDataSetIDKey[PX_DSID_dsDin]) >= 0)
			{
				pDvmDatasetRef->m_strDataType.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());
			}
		}
	}

	m_pInterSelect_ComboBox->ShowBaseList(&m_oEnaInterDatasRef);
}

void QRemoteCtrlBtnWidget::setData()
{
	initBaseData();
}

void QRemoteCtrlBtnWidget::initBaseData()
{
// 	if(m_pManualParas == NULL)
// 	{
// 		return;
// 	}
	
	InitComboxData();

	m_pDataType_LineEdit->setDisabled(true);

	UpdateData();
}

void QRemoteCtrlBtnWidget::InitComboxData()
{
	m_oEnaChDatasRef.RemoveAll();
//	DeleteEnaChDatas();
	CExBaseList *pDataset = (CExBaseList*)m_pInterSelect_ComboBox->GetCurrSelObject();

	if (pDataset == NULL)
	{
		return;
	}

	POS posDataset = pDataset->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	CDvmData *pDvmDataRef = NULL;

	while (posDataset)
	{
		pCurrData = (CDvmData *)pDataset->GetNext(posDataset);

		if (pCurrData->m_strDataType == "BOOL" || pCurrData->m_strDataType == "INT")
		{
			m_oEnaChDatasRef.AddTail(pCurrData);
// 			pDvmDataRef = new CDvmData;
// 			m_oEnaChDatasRef.AddNewChild(pDvmDataRef);
// 			pDvmDataRef->m_strName = pCurrData->m_strName;
// 			pDvmDataRef->m_strID = pCurrData->m_strID;
// 			pDvmDataRef->m_strDataType = pCurrData->m_strDataType;
// 			pDvmDataRef->m_strValue = pCurrData->m_strValue;
// 			pDvmDataRef->Append(*pCurrData);
		}
	}	

	m_pChannelSelect_ComboBox->ShowBaseList(&m_oEnaChDatasRef);		
}

void QRemoteCtrlBtnWidget::UpdateData()
{
	UpdateState();
	UpdateOperationSelect();
}

void QRemoteCtrlBtnWidget::UpdateState()
{
	CExBaseList *pDvmData = (CExBaseList*)m_pChannelSelect_ComboBox->GetCurrSelObject();

	if (pDvmData == NULL)
			{
		return;
	}
	
	CDvmData *pCurrData = NULL;
	pCurrData = (CDvmData *)pDvmData;
	CString strType;
	if (pCurrData->m_strDataType == _T("BOOL") || pCurrData->m_strDataType == _T("bool"))
	{
		strType = _T("单点");
	}
	else
	{
		strType = _T("双点");
	}
	m_pDataType_LineEdit->setText(strType);
	m_pCondition_LineEdit->setText(pCurrData->m_strValue);
}

void QRemoteCtrlBtnWidget::UpdateOperationSelect()
{
	CString strChannel = m_pChannelSelect_ComboBox->GetSelectName();

	CString strSwitch,strReturn,strBattery;
	strSwitch = _T("开关");
	strReturn = _T("复归");
	strBattery = _T("电池活化");

	if (strChannel.Find(strSwitch)>=0)
	{
		m_pOperationSelect_ComboBox->setDisabled(false);
		m_listOprSeclect.clear();
		m_listOprSeclect << _T("分闸")<< _T("合闸");	
		m_pOperationSelect_ComboBox->clear();
		m_pOperationSelect_ComboBox->addItems(m_listOprSeclect);
	}
	else if (strChannel.Find(strReturn)>=0)
	{
		m_pOperationSelect_ComboBox->setDisabled(true);
	}
	else if (strChannel.Find(strBattery)>=0)
	{
		m_pOperationSelect_ComboBox->setDisabled(false);
		m_listOprSeclect.clear();
		m_listOprSeclect << _T("启动")<< _T("停止");	
		m_pOperationSelect_ComboBox->clear();
		m_pOperationSelect_ComboBox->addItems(m_listOprSeclect);
	}
	else
	{
		m_pOperationSelect_ComboBox->setDisabled(false);
		m_listOprSeclect.clear();
		m_listOprSeclect << _T("退出")<< _T("投入");
		m_pOperationSelect_ComboBox->clear();
		m_pOperationSelect_ComboBox->addItems(m_listOprSeclect);
	}
}

void QRemoteCtrlBtnWidget::slot_cmb_ChannelSelectChanged(int index)
{
	UpdateData();
}

void QRemoteCtrlBtnWidget::slot_PushButton_ReadConditionClicked()
{
	UpdateData();
}

void QRemoteCtrlBtnWidget::startInit()
{
	setEnabled(false);
	m_pInterSelect_ComboBox->setDisabled(true);
	m_pChannelSelect_ComboBox->setDisabled(true);
	m_pDataType_LineEdit->setDisabled(true);
	m_pOperationSelect_ComboBox->setDisabled(true);
	m_pRemoteCtrlPre_Button->setDisabled(true);
	m_pRemoteCtrlExe_Button->setDisabled(true);
	m_pRemoteCtrlCancel_Button->setDisabled(true);
	m_pReadCondition->setDisabled(true);
	m_pCondition_LineEdit->setDisabled(true);
}

void QRemoteCtrlBtnWidget::stopInit()
{
	setEnabled(true);

 	m_pInterSelect_ComboBox->setDisabled(false);
	m_pChannelSelect_ComboBox->setDisabled(false);
	m_pDataType_LineEdit->setDisabled(false);
	m_pOperationSelect_ComboBox->setDisabled(false);
	m_pRemoteCtrlPre_Button->setDisabled(false);
	m_pRemoteCtrlExe_Button->setDisabled(false);
	m_pRemoteCtrlCancel_Button->setDisabled(false);
	m_pReadCondition->setDisabled(false);
	m_pCondition_LineEdit->setDisabled(false);
}
void QRemoteCtrlBtnWidget::slot_btn_ClearOperationRecordsClicked()
{
	if (m_pRemoteCtrlGridFirst == NULL)
	{
		return;
	}
	m_pRemoteCtrlGridFirst->clearContents();
	m_pRemoteCtrlGridFirst->setRowCount(0);
	g_pRemoteCtrl->m_nRecordIndex = 0;
}

void QRemoteCtrlBtnWidget::slot_btn_ClearClearEventRecordsClicked()
{
	if (m_pRemoteCtrlGridSecond == NULL)
	{
		return;
	}
	m_pRemoteCtrlGridSecond->clearContents();
	m_pRemoteCtrlGridSecond->setRowCount(0);
}
