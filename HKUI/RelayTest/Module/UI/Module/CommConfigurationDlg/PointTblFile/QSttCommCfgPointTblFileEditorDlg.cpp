#include "QSttCommCfgPointTblFileEditorDlg.h"
#include <QDirIterator>

#include "../../CommonMethod/commonMethod.h"
#include "../../../../XLangResource_Native.h"
#include "../../../../../../Module/DataMngr/DvmData.h"
#include "../../../../../../Module/API/GlobalConfigApi.h"
#include "SttPointTblEdtTabTeleMeasureGrid.h"
#include "../../../Module/PopupDialog/SttPopupOpenDialog.h"
#include "../../../Module/PopupDialog/SttPopupSaveAsDialog.h"
//#include "../../../../UI/SoftKeyboard/Keyboard/Keyboard.h"
#ifdef _USE_SoftKeyBoard_
#include "../../../../UI/SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../../../../../../Module/OSInterface/QT/XMessageBox.h"
extern CFont *g_pSttGlobalFont;

#include <QDesktopWidget>
#include <QApplication>
#include <QFileDialog>

QSttCommCfgPointTblFileEditorDlg::QSttCommCfgPointTblFileEditorDlg(CString strFullPath,QWidget *parent)
	: QDialog(parent)
{
	//CString strText;
	//strText = _T("输出功率设置";
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	setWindowTitle(CString("点表编辑"));
	m_pCrtPointTbFullPath = strFullPath;
	m_bApplyAllFlg = FALSE;
	initUI();
	InitDatas();


}

QSttCommCfgPointTblFileEditorDlg::~QSttCommCfgPointTblFileEditorDlg()
{
	if (m_pDvmDevice != NULL)
	{
		delete m_pDvmDevice;
		m_pDvmDevice = NULL;
	}
		

}

void QSttCommCfgPointTblFileEditorDlg::initUI()
{
	ReleaseUI();
	resize(900, 630);
	setMinimumSize(QSize(0, 0));
	setMaximumSize(QSize(16777215, 16777215));

	QVBoxLayout *pAllVLayout = new QVBoxLayout(this);

	QHBoxLayout *pUp_HLayout = new QHBoxLayout(this);
	m_pTabWidget = new QTabWidget(this);
	
	m_pIntervalSetGrid = new SttCPointTblEdtTabIntervalSetGrid(this);
	////m_pIntervalSetGrid->InitGrid();
	m_pTabWidget->addTab(m_pIntervalSetGrid,CString("首地址设置表"));
	pUp_HLayout->addWidget(m_pTabWidget);
	pAllVLayout->addLayout(pUp_HLayout);

	m_pLabelIntSetNum = new QLabel(this);
	m_pLabelIntSetNum->setText(CString("间隔数:"));
	

	QFont font1;
	font1.setPointSize(15);
	m_pIntervalNums_Combo = new QScrollComboBox(this);
	for (int i=1; i<=QSTTCOMMCFGPOINTTB_MAX_TABS; i++)
	{
		CString strComboItem;
		strComboItem.Format("%d",i);
		m_pIntervalNums_Combo->addItem(strComboItem);
	}
	m_pIntervalNums_Combo->setFont(font1);
	m_pImportPointFile_PushButton = new QPushButton(this);
	m_pImportPointFile_PushButton->setText(CString("导入"));
	m_pExportPointFile_PushButton = new QPushButton(this);
	m_pExportPointFile_PushButton->setText(CString("导出"));
	m_pSavePointFile_PushButton = new QPushButton(this);
	m_pSavePointFile_PushButton->setText(CString("保存"));
	m_pInsertPointFile_PushButton = new QPushButton(this);
	m_pInsertPointFile_PushButton->setText(CString("插入"));
	m_pInsertPointFile_PushButton->setEnabled(false);
	m_pDelPointFile_PushButton = new QPushButton(this);
	m_pDelPointFile_PushButton->setText(CString("删除"));
	m_pLabelStartAddr = new QLabel(this);
	m_pLabelStartAddr->setText(CString("起始地址:0x"));
	m_pStartAddr_LineEdit = new QSttLineEdit(this);
	//m_pStartAddr_LineEdit->setText(CString("0x"));
	m_pApplyAll_PushButton = new QPushButton(this);
	m_pApplyAll_PushButton->setText(CString("间隔参数同步"));
	m_pLabelStartAddr->setEnabled(false);
	m_pStartAddr_LineEdit->setEnabled(false);
	//m_pApplyAll_PushButton->setEnabled(false);
	m_pApplyAll_PushButton->setEnabled(true);

	QHBoxLayout *pDown_HLayout = new QHBoxLayout(this);
	//pDown_HLayout->addStretch();
	pDown_HLayout->addWidget(m_pLabelIntSetNum);
	pDown_HLayout->addWidget(m_pIntervalNums_Combo);
	//pDown_HLayout->addSpacing(10);
	pDown_HLayout->addWidget(m_pImportPointFile_PushButton);
	pDown_HLayout->addWidget(m_pExportPointFile_PushButton);
	//pDown_HLayout->addWidget(m_pSavePointFile_PushButton);
	pDown_HLayout->addWidget(m_pInsertPointFile_PushButton);
	//pDown_HLayout->addSpacing(10);
	pDown_HLayout->addWidget(m_pDelPointFile_PushButton);
	//pDown_HLayout->addWidget(m_pSavePointFile_PushButton);
	pDown_HLayout->addWidget(m_pLabelStartAddr);
	pDown_HLayout->addWidget(m_pStartAddr_LineEdit);
	pDown_HLayout->addWidget(m_pApplyAll_PushButton);
	//pDown_HLayout->addStretch();
	pDown_HLayout->setDirection(QBoxLayout::LeftToRight);
	pAllVLayout->addLayout(pDown_HLayout);
	
// 	m_pOK_PushButton = new QPushButton(this);
// 	m_pOK_PushButton->setText(g_sLangTxt_OK);
	//strText = _T("取消");
	m_pCancel_PushButton = new QPushButton(this);
	m_pCancel_PushButton->setText(g_sLangTxt_Close); //取消换成关闭
	QHBoxLayout *m_pOkCancel_HBoxLayout = new QHBoxLayout(this);
	m_pOkCancel_HBoxLayout->addStretch();
	//m_pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);//去掉确定按钮,把保存按钮布局调整
	m_pOkCancel_HBoxLayout->addWidget(m_pSavePointFile_PushButton);
	//m_pOkCancel_HBoxLayout->addWidget(m_pOK_PushButton);
	m_pOkCancel_HBoxLayout->addSpacing(10);
	m_pOkCancel_HBoxLayout->addWidget(m_pCancel_PushButton);
	m_pOkCancel_HBoxLayout->addStretch();
	m_pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);
	pAllVLayout->addLayout(m_pOkCancel_HBoxLayout);

	this->setLayout(pAllVLayout);

	//connect(m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_OKClicked()));
	connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
 	connect(m_pImportPointFile_PushButton, SIGNAL(clicked()), this, SLOT(slot_Import_Clicked()));
 	connect(m_pExportPointFile_PushButton, SIGNAL(clicked()), this, SLOT(slot_Export_Clicked()));
 	connect(m_pSavePointFile_PushButton, SIGNAL(clicked()), this, SLOT(slot_SaveClicked()));
 	//connect(m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
	connect(m_pDelPointFile_PushButton, SIGNAL(clicked()), this, SLOT(slot_DelCurrRow_Clicked()));
	connect(m_pInsertPointFile_PushButton, SIGNAL(clicked()), this, SLOT(slot_InsertRow_Clicked()));
	connect(m_pApplyAll_PushButton, SIGNAL(clicked()), this, SLOT(slot_ApplyAll_Clicked()));
	connect(m_pTabWidget,  SIGNAL(currentChanged(int)), this, SLOT(slot_CrtChangedTabWidget(int)));
	//connect(m_pStartAddr_LineEdit, &QLineEdit::editingFinished, this, slot_StartAddrEdit_Finished());
	connect(m_pStartAddr_LineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_StartAddrEdit_Finished()));
	connect(m_pIntervalNums_Combo, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_IntervalSetComboChanged(int)));

	//connect(m_pIntervalSetGrid, SIGNAL(sig_ChangedIntervSetDevAddr()), this, SLOT(slot_IntervalSetTableChanged()));
	//connect(m_pIntervalSetGrid, SIGNAL(sig_ChangedAdress(int,int,QString)), this, SLOT(slot_ChangedAdress(int,int,QString)));

	connect(m_pIntervalSetGrid, SIGNAL(sig_ApplyAll(bool)), this, SLOT(slot_ApplyAll(bool)));

	SetDialogFont();
}


void QSttCommCfgPointTblFileEditorDlg::SetDialogFont()
{
	if (g_pSttGlobalFont == NULL)
	{
		return;
	}
	m_pTabWidget->setFont(*g_pSttGlobalFont);
	m_pLabelIntSetNum->setFont(*g_pSttGlobalFont);
	m_pImportPointFile_PushButton->setFont(*g_pSttGlobalFont);
	m_pExportPointFile_PushButton->setFont(*g_pSttGlobalFont);
	m_pSavePointFile_PushButton->setFont(*g_pSttGlobalFont);
	m_pInsertPointFile_PushButton->setFont(*g_pSttGlobalFont);
	m_pDelPointFile_PushButton->setFont(*g_pSttGlobalFont);
	m_pApplyAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pLabelStartAddr->setFont(*g_pSttGlobalFont);
	m_pStartAddr_LineEdit->setFont(*g_pSttGlobalFont);
	//m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	
}

void Global_SetCommCfgGridEnable(QTableWidget *uitableWidget)
{
	//# 遍历表格的每一行
	for(int iCol=0; iCol<uitableWidget->columnCount()-1; iCol++)
	{
		for(int irow=0; irow<<uitableWidget->rowCount()-1; irow++)
		{
			QTableWidgetItem *item = uitableWidget->item(irow,iCol); //获取每行第1列的单元格指针
			item->setFlags(Qt::ItemIsEnabled);//设置改item不可修改；
		}
	}
	//int iRow=1;
	//m_pIntervalSetGrid->item(iRow,1)->setFlags(Qt::ItemIsEnabled);
	//m_pIntervalSetGrid->item(iRow,2)->setFlags(Qt::ItemIsEnabled);
	//m_pIntervalSetGrid->item(iRow,3)->setFlags(Qt::ItemIsEnabled);
}

void QSttCommCfgPointTblFileEditorDlg::ReleaseUI()
{

}

void QSttCommCfgPointTblFileEditorDlg::InitDatas()
{
	m_pDvmDevice = new CDvmDevice();
	m_pDvmDevice->OpenXmlFile(m_pCrtPointTbFullPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	ProcessOverMaxExtraTabs();
	//m_pDvmDevice->SaveXmlFile(CString("C:/Users/HP/Desktop/Work/规约文件测试/zzzpcs.xml"), CDataMngrXmlRWKeys::g_pXmlKeys);
	CalcColums();
}

GeneralTab::GeneralTab(QWidget *parent):QWidget(parent)
{
	mpParentDlg=parent;
	//parent
	//QSttCommCfgPointTblFileEditorDlg *parent = (QSttCommCfgPointTblFileEditorDlg*) parent;
	m_pTeleGridTabWight = new QTabWidget;
	m_pTeleGridTabWight->setFont(*g_pSttGlobalFont);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	//mainLayout->addStretch();
	mainLayout->addWidget(m_pTeleGridTabWight);
	//mainLayout->addStretch();
	setLayout(mainLayout);
}

GeneralTab::~GeneralTab()
{

}


void GeneralTab::AddDatasetCols(CDvmDataset *pDataset)
{
	CString strDasetID = pDataset->m_strID;
	strDasetID.MakeUpper();	
	int nPos = strDasetID.Find(CString("AIN")); //dsRelayAin 
	if (nPos >= 0) //遥测
	{
		SttCPointTblEdtTabTeleMeasureGrid *pRightTelMarGrid = new SttCPointTblEdtTabTeleMeasureGrid(this);
		pRightTelMarGrid->InitGrid();
		pRightTelMarGrid->ShowDatas(pDataset);
		CString strTabName = pDataset->m_strName;
		if (strTabName.IsEmpty())
		{
			strTabName = pDataset->m_strID;
		}
		m_pTeleGridTabWight->addTab(pRightTelMarGrid, strTabName);

		QSttCommCfgPointTblFileEditorDlg* pDlg = (QSttCommCfgPointTblFileEditorDlg*)mpParentDlg;
		connect(pRightTelMarGrid, SIGNAL(sig_ChangedTeleMeasureIndex()), pDlg, SLOT(slot_RightTeleMearTableChanged()));
	}
	else
	{
		SttCPointTblEdtTabTeleParaCommGrid *pRightParaCommGrid = new SttCPointTblEdtTabTeleParaCommGrid(this);
		pRightParaCommGrid->InitGrid();
		pRightParaCommGrid->ShowDatas(pDataset);
		CString strTabName = pDataset->m_strName;
		if (strTabName.IsEmpty())
		{
			strTabName = pDataset->m_strID;
		}
		m_pTeleGridTabWight->addTab(pRightParaCommGrid, strTabName);

		QSttCommCfgPointTblFileEditorDlg* pDlg = (QSttCommCfgPointTblFileEditorDlg*)mpParentDlg;
		connect(pRightParaCommGrid, SIGNAL(sig_ChangedParaComIndex()), pDlg, SLOT(slot_RightParaSetTableChanged()));

	}
}


//void GeneralTab::slot_RightTeleParaSetChanged()
//{
//	QSttCommCfgPointTblFileEditorDlg* pDlg = (QSttCommCfgPointTblFileEditorDlg*)parentWidget();
//	pDlg->slot_SaveClicked();
//}

BOOL QSttCommCfgPointTblFileEditorDlg::SaveXmlFile()
{
	return m_pDvmDevice->SaveXmlFile(m_pCrtPointTbFullPath,CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttCommCfgPointTblFileEditorDlg::SaveDvmXmlFile()
{
	m_pDvmDevice->SaveXmlFile(m_pCrtPointTbFullPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	
}

void QSttCommCfgPointTblFileEditorDlg::CalcColums()
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}
	m_pIED_Hash.clear();

	QStringList oColIdsList, oColNamesList;
	POS pos = m_pDvmDevice->GetHeadPosition();

	CExBaseList *pLogicDev = NULL;
	CExBaseList *pDataSet = NULL;
	m_nIntervalNums = 0;
	while (pos != NULL)
	{
		pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(pos);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}
		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
 		if(pLogicDevice->m_strID == "report")
 		{
 			continue;
 		}
		m_nIntervalNums++;
		GeneralTab  *pGeneralTab = new GeneralTab(this);

		//QStringList *pHashDatasetList = new QStringList;
		//if(!m_pIED_Hash.contains(pLogicDevice->m_strID))
		//{
		//	m_pIED_Hash.insert(pLogicDevice->m_strID,pHashDatasetList);
		//}
		CString strTabName = pLogicDevice->m_strName;
		CString strTabName22 =  pLogicDevice->m_strID;
		if (strTabName.IsEmpty())
		{
			strTabName = pLogicDevice->m_strID;
		}
		m_pTabWidget->addTab(pGeneralTab, strTabName);
		int nn = m_pTabWidget->count();

		POS posLgDev = pLogicDev->GetHeadPosition();
		while(posLgDev != NULL)
		{
			pDataSet = (CExBaseList*)pLogicDev->GetNext(posLgDev);
			int crtidDaset = pDataSet->GetClassID();
			if (crtidDaset != DVMCLASSID_CDVMDATASET)
			{
				continue;
			}
			CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
			pGeneralTab->AddDatasetCols(pDataset);
			CString strDataId = pDataset->m_strID;
			CString strDatasetName = pDataset->m_strName;
			if (!oColIdsList.contains(strDataId))
			{
				if(strDataId != "package" && strDataId != "soe")
				{
				oColIdsList.append(strDataId);
			}
			}
			if (strDatasetName.IsEmpty())
			{
				strDatasetName = strDataId;
			}
			if (!oColNamesList.contains(strDatasetName))
			{
				if(strDataId != "package" && strDataId != "soe")
				{
				oColNamesList.append(strDatasetName);
			}
				//oColNamesList.append(strDatasetName);
			}
		}

	}

	//m_pIntervalSetGrid->m_pIED_Hash = m_pIED_Hash;

	m_pIntervalSetGrid->SetColumns(&oColIdsList, &oColNamesList);
	//pColNamesList
	m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);

	m_pIntervalNums_Combo->setCurrentIndex(m_nIntervalNums-1);

}

void QSttCommCfgPointTblFileEditorDlg::slot_StartAddrEdit_Finished()
{
	CString strCurValue = m_pStartAddr_LineEdit->text();
	strCurValue = _T("0x") + strCurValue;

	if (strCurValue.IsEmpty())
	{
		return;
	}

	long lTransCurValue = 0;
	if ((strCurValue.Find("0X")==-1) && (strCurValue.Find("0x")==-1))
	{
			lTransCurValue = CString_To_long(strCurValue);
	}
	else
	{
		long nValue = 0;
		char *pzfTmp = NULL;
		CString_to_char(strCurValue,&pzfTmp);
		HexToLong(pzfTmp,nValue);
		delete pzfTmp;
		lTransCurValue = nValue;
	}

	QString strCurrTabName = "";
	int nIndexChildTab = 0;

	int nIndex = m_pTabWidget->currentIndex();
	if (nIndex > 0)
	{
		//static int iIntervSetNms = 1;
		strCurrTabName = m_pTabWidget->tabText(nIndex);
		GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
		nIndexChildTab = pGenTab->m_pTeleGridTabWight->currentIndex();

		QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
		CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
		CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;

		POS posLgDev = pDataset->GetHeadPosition();
		int i = 0;
		while(posLgDev != NULL)
		{
			CExBaseList  *pData = (CExBaseList *)pDataset->GetNext(posLgDev);
			int crtidDaset = pData->GetClassID();
			if (crtidDaset != DVMCLASSID_CDVMDATA)
			{
				continue;
			}
			CDvmData *pDataFind = (CDvmData*)pData;
			pDataFind->m_nIndex = lTransCurValue+i;
			++i;
			//pGeneralTab->AddDatasetCols(pDataset);

			//stringlist->append(dataidStr);
		}

		pRightGrid->ShowDatas(pDataset);
	}	
}

void QSttCommCfgPointTblFileEditorDlg::slot_SaveClicked()
{
 	CString strMsgText;

	BOOL nRet = SaveXmlFile();
	if (nRet)
	{
		strMsgText = _T("保存成功.");
	}
	else
	{
		strMsgText = _T("保存失败.");
	}

	CXMessageBox::information(this,g_sLangTxt_Message,strMsgText);
}

void QSttCommCfgPointTblFileEditorDlg::slot_OKClicked()
{
	close();
}

void QSttCommCfgPointTblFileEditorDlg::slot_CancelClicked()
{
	close();
}

void QSttCommCfgPointTblFileEditorDlg::slot_CrtChangedTabWidget(int nCurrIndex)
{
	//OnCurrFuncChanged(nCurrIndex);
	if (nCurrIndex == 0)
	{
		m_pLabelIntSetNum->setEnabled(true);
		m_pIntervalNums_Combo->setEnabled(true);
		m_pLabelStartAddr->setEnabled(false);
		m_pStartAddr_LineEdit->setEnabled(false);	
		//m_pApplyAll_PushButton->setEnabled(false);
		m_pApplyAll_PushButton->setEnabled(true);
		m_pInsertPointFile_PushButton->setEnabled(false);	//首地址设置表插入按钮灰掉
	}
	else if (nCurrIndex > 0)
	{	
 		if (m_bApplyAllFlg)
	{
 			UpdateIntervalGrid(nCurrIndex); 
		}

		m_pLabelIntSetNum->setEnabled(false);
		m_pIntervalNums_Combo->setEnabled(false);
		m_pLabelStartAddr->setEnabled(true);
		m_pStartAddr_LineEdit->setEnabled(true);	
		//m_pApplyAll_PushButton->setEnabled(true);
		m_pApplyAll_PushButton->setEnabled(false);
		m_pInsertPointFile_PushButton->setEnabled(true);
	}
}


void QSttCommCfgPointTblFileEditorDlg::slot_DelCurrRow_Clicked()
{	
	if (m_pTabWidget->currentIndex() == 0)//间隔表删除
	{
		if (m_pIntervalSetGrid->rowCount() <= 0)
		{
			return;
		}
		/*
		CExBaseObject *pXSclFileObj = (CExBaseObject*)m_pIntervalSetGrid->GetCurrSelData();
		if (pXSclFileObj == NULL)
		{
			return;
		}
		CString strDatasetNm = pXSclFileObj->m_strName;
		if (strDatasetNm.IsEmpty())
		{
			strDatasetNm = pXSclFileObj->m_strID;
		}
		//m_pIntervalSetGrid->DeleteDataRow(pXSclFileObj);
		m_pDvmDevice->DeleteByID(pXSclFileObj->m_strID);*/
		//return;

		
		int iCrtRow = m_pIntervalSetGrid->currentRow();
		if (iCrtRow < 0)
		{
			return;
		}
		CString strFirstLDName = m_pIntervalSetGrid->item(iCrtRow,0)->text();
		DeleteDvmDeviceByName(strFirstLDName);
	

		//m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);
		//m_pTabWidget->count()
		for (int i=0; i<m_pTabWidget->count(); i++)
		{
			if (m_pTabWidget->tabText(i) == strFirstLDName /*strFirstLDId*/)
			{

				m_pTabWidget->removeTab(i);
				
			}
		}
		//间隔Combo设置-1
		int nIndex = m_pTabWidget->count() - 2;
		m_pIntervalNums_Combo->setCurrentIndex(nIndex);
		
		ModifyIdxInIntervalSetCombo();
		
	}
	else //右侧非间隔表
	{
		 GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
		 QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
		 CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
		 CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
		 if (pRightGrid->rowCount() <= 0)
		 {
			 return;
		 }

		 CExBaseObject *pSelItem = (CExBaseObject*) pRightGrid->GetCurrSelData();
		 CDvmData *pDataSel = (CDvmData*) pSelItem;
		 if (pDataSel == NULL)
		 {
			 return;
		 }
		 pDataset->DeleteByID(pDataSel->m_strID);

		 //删除后需要重新地址排序 chenling20240313
		 CString strAddress = pRightGrid->item(0,1)->text();
		 long lAdressCurValue = 0;
		 if ((strAddress.contains("0X") == -1) && (strAddress.contains("0x") == -1))
		 {
			 lAdressCurValue = CString_To_long(strAddress);
		 }
		 else
		 {
			 long nValue = 0;
			 char *pzfTmp = NULL;
			 CString_to_char(strAddress,&pzfTmp);
			 HexToLong(pzfTmp,nValue);
			 delete pzfTmp;
			 lAdressCurValue = nValue;
		 }

		 long nIndexAddress = 0;
		 POS pos = pDataset->GetHeadPosition();
		 while(pos)
		 {
			 CDvmData *pDataFind = (CDvmData*)pDataset->GetNext(pos);
			 pDataFind->m_nIndex = lAdressCurValue + nIndexAddress;
			 ++nIndexAddress;
		 }
		 pRightGrid->ShowDatas(pDataset);
	}
	////SaveDvmXmlFile();
}


void QSttCommCfgPointTblFileEditorDlg::Append_IntervalSetTab()
{
	//int nCrtSize = m_pDvmDevice->GetCount();
	int nCrtSize = m_pTabWidget->count() - 1;
	int iIntervSetNms = nCrtSize + 1;
	if (m_pIntervalSetGrid->rowCount() <= 0)
	{
		return;
	}

	POS posHead = m_pDvmDevice->GetHeadPosition();
	CDvmLogicDevice *pHeadItem = (CDvmLogicDevice*)m_pDvmDevice->GetAt(posHead);

	CDvmLogicDevice *pDvmLogDev = (CDvmLogicDevice*)pHeadItem->Clone();//CloneEx(true,true);

	CString strName;
	strName.Format("间隔%d", iIntervSetNms++);
	pDvmLogDev->m_strName = strName;
	CString strID;
	strID.Format("LDevice%d", iIntervSetNms-1);
	pDvmLogDev->m_strID = strID;
	GeneralTab  *pGeneralTab = new GeneralTab(this);
	m_pTabWidget->addTab(pGeneralTab, pDvmLogDev->m_strName);
	//////////////////////////////////
	CExBaseList *pDataSet=-NULL;
	POS posLgDev = pDvmLogDev->GetHeadPosition();
	while(posLgDev != NULL)
	{
		pDataSet = (CExBaseList *)pDvmLogDev->GetNext(posLgDev);
		int crtidDaset = pDataSet->GetClassID();
		if (crtidDaset != DVMCLASSID_CDVMDATASET)
		{
			continue;
		}

		CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
		pGeneralTab->AddDatasetCols(pDataset);
		//stringlist->append(dataidStr);
	}
	/////////////////////////////////
	m_pDvmDevice->AddNewChild(pDvmLogDev);
	m_pIntervalSetGrid->InsertData(pDvmLogDev);
	//m_pIntervalSetGrid->SelectRow(g_oXSclFileMngr.GetCount());
}

void QSttCommCfgPointTblFileEditorDlg::Append_TeleMeasureTab()
{
	return;
	static int iIntervSetNms = 1;
	GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
	QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
	CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
	CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
	POS posHead = pDataset->GetHeadPosition();
	CDvmData *pHeadItem = (CDvmData*)pDataset->GetAt(posHead);
	CDvmData *pCpData = (CDvmData*)pHeadItem->Clone();
	CString strName;
	strName.Format("%d", iIntervSetNms++);
	pCpData->m_strName += strName;
	CString strID;
	strID.Format("%d", iIntervSetNms-1);
	pCpData->m_strID += strID;
	pDataset->AddNewChild(pCpData);
	pRightGrid->InsertData(pCpData);
}

void QSttCommCfgPointTblFileEditorDlg::Insert_IntervalSetTab()
{
	//static int iLdInsertNums = 1;
	int nCrtSize = m_pTabWidget->count() - 1;
	int iLdInsertNums = nCrtSize + 1;

	if (m_pIntervalSetGrid->rowCount() <= 0)
	{
		return;
	}
	
	int iCrtRow = m_pIntervalSetGrid->currentRow();
	if (iCrtRow < 0)
	{
		return;
	}
	CString strFirstLDId = m_pIntervalSetGrid->item(iCrtRow,0)->text();
	CDvmLogicDevice *pFindDevice = FindDvmDeviceByName(strFirstLDId);
	if (pFindDevice == NULL)
	{
		return;
	}
	CDvmLogicDevice *pCpDev = (CDvmLogicDevice*)pFindDevice->Clone();

	/*CExBaseObject *pDvmLogDvInsert = m_pDvmDevice->FindChildByID(strFirstLDId);
	CDvmLogicDevice *pCpDev = (CDvmLogicDevice*)pDvmLogDvInsert->Clone();*/

	//CDvmLogicDevice *pXSclFileObj = (CDvmLogicDevice*)m_pIntervalSetGrid->GetCurrSelData();
	//if (pXSclFileObj == NULL)
	//{
	//	return;
	//}
	//CDvmLogicDevice *pCpDev = (CDvmLogicDevice*)pXSclFileObj->Clone();

	CString strID;
	CString strDevID = pCpDev->m_strID;
	int iPos = strDevID.ReverseFind('-');
	if (iPos >= 0)
	{
		strDevID = strDevID.left(iPos);
	}
	strID.Format("%s-%d", strDevID.GetString(), iLdInsertNums);
	pCpDev->m_strID = strID;

	CString strName;
	CString strDevName = pCpDev->m_strName;
	int iNmPos = strDevName.ReverseFind('-');
	if (iNmPos >= 0)
	{
		strDevName = strDevName.left(iNmPos);
	}
	strName.Format("%s-%d", strDevName.toUtf8().constData(), iLdInsertNums);
	pCpDev->m_strName = strName;
	//m_pDvmDevice->InsertBefore();

	if (iCrtRow == 0)
	{
		m_pDvmDevice->AddHead(pCpDev);
	}else
	{
		POS crtPos = m_pDvmDevice->Find(pFindDevice);
		CDvmLogicDevice *pFindTem = (CDvmLogicDevice*)m_pDvmDevice->GetPrev(crtPos);
		CDvmLogicDevice *pDvmLogDvPrev = (CDvmLogicDevice*)m_pDvmDevice->GetAt(crtPos);
		if (pDvmLogDvPrev == NULL)
		{
			return;
		}

		//CString strPrevLDId = m_pIntervalSetGrid->item(iCrtRow-1,0)->text();
		//CExBaseObject *pDvmLogDvPrev = m_pDvmDevice->FindChildByID(strPrevLDId);
		POS posLgDev = m_pDvmDevice->GetHeadPosition();
		while(posLgDev != NULL)
		{
			CExBaseList *pLgDev = (CExBaseList *)m_pDvmDevice->GetNext(posLgDev);
			if (pLgDev != pDvmLogDvPrev)
			{
				continue;
			}
			m_pDvmDevice->InsertBefore(posLgDev,pCpDev);
		}
	}
	CDvmLogicDevice *pLogDvFindInserted = (CDvmLogicDevice*)m_pDvmDevice->FindChildByID(strID);
	if (pLogDvFindInserted == NULL)
	{
		return;
	}
	//++iLdInsertNums;
	//////////////////////////////////
	GeneralTab  *pGeneralTab = new GeneralTab(this);
	CString strTabName = pLogDvFindInserted->m_strName;
	if (strTabName.IsEmpty())
	{
		strTabName = pLogDvFindInserted->m_strID;
	}
	m_pTabWidget->addTab(pGeneralTab, strTabName);
	CExBaseList *pDataSet = NULL;
	POS posDaset = pLogDvFindInserted->GetHeadPosition();
	while(posDaset != NULL)
	{
		pDataSet = (CExBaseList *)pLogDvFindInserted->GetNext(posDaset);
		int crtidDaset = pDataSet->GetClassID();
		if (crtidDaset != DVMCLASSID_CDVMDATASET)
		{
			continue;
		}
		CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
		pGeneralTab->AddDatasetCols(pDataset);
		//stringlist->append(dataidStr);
	}
	/////////////////////////////////
	m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);

	//m_pTabWidget->count()
//for (int i=0; i<m_pTabWidget->count(); i++)
//{
//	if (m_pTabWidget->tabText(i) == strFirstLDId)
//	{
//		m_pTabWidget->addTab(pGeneralTab,pLogDvFindInserted->m_strID);
//	}
//}
}

void QSttCommCfgPointTblFileEditorDlg::Insert_TeleMeasureTab()
{
	static int iTeleTabNms = 1;
	GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
	QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
	CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
	CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
	if (pRightGrid->rowCount() <= 0)
	{
		return;
	}
	int iCrtRow = pRightGrid->currentRow();
	if (iCrtRow < 0)
	{
		return;
	}
	CDvmData *pCrtItem = (CDvmData*)pRightGrid->GetCurrSelData();
	CDvmData *pCpData = (CDvmData*)pCrtItem->Clone();
	CString strID;
	CString strDevID = pCpData->m_strID;
	int iPosid = strDevID.ReverseFind('-');
	if (iPosid >= 0)
	{
		strDevID = strDevID.left(iPosid);
	}
	strID.Format("%s-%d", strDevID.GetString(), iTeleTabNms);
	pCpData->m_strID = strID;
	
	CString strName;
	CString strDevName = pCpData->m_strName;
	int iNmPos = strDevName.ReverseFind('-');
	if (iNmPos >= 0)
	{
		strDevName = strDevName.left(iNmPos);
	}
	strName.Format("%s-%d", strDevName.toUtf8().constData(), iTeleTabNms);
	pCpData->m_strName = strName;


	//CString strNameTem;
	//CString strDevName = pCpData->m_strName;
	//int iPosnm = strDevName.ReverseFind('-');
	//if (iPosnm >= 0)
	//{
	//	strDevName = strDevName.left(iPosnm);
	//}
	//strNameTem.Format("%s-%d",strDevName.GetString(),iTeleTabNms);
	//pCpData->m_strName=strName;
	////////////////
	if (iCrtRow == 0)
	{
		pDataset->AddHead(pCpData);
	}else
	{
		POS posDataset = pDataset->Find(pCrtItem);
		pDataset->GetPrev(posDataset);
		CDvmData *pPrevFindItm = (CDvmData*)pDataset->GetAt(posDataset);
		POS pos = pDataset->GetHeadPosition();
		while(pos != NULL)
		{
			CExBaseList *pData = (CExBaseList *)pDataset->GetNext(pos);
			if (pData != pPrevFindItm)
			{
				continue;
			}
			pDataset->InsertBefore(pos, pCpData);
		}
	}
	++iTeleTabNms;



	//插入重新地址排序
	CString strAddress = pRightGrid->item(0,1)->text();
	long lAdressCurValue = 0;
	if ((strAddress.contains("0X") == -1) && (strAddress.contains("0x") == -1))
	{
		lAdressCurValue = CString_To_long(strAddress);
	}
	else
	{
		long nValue = 0;
		char *pzfTmp = NULL;
		CString_to_char(strAddress,&pzfTmp);
		HexToLong(pzfTmp,nValue);
		delete pzfTmp;
		lAdressCurValue = nValue;
	}

	long nIndexAddress = 0;
	POS pos = pDataset->GetHeadPosition();
	while(pos)
	{
		CDvmData *pDataFind = (CDvmData*)pDataset->GetNext(pos);
		pDataFind->m_nIndex = lAdressCurValue + nIndexAddress;
		++nIndexAddress;
	}

	pRightGrid->ShowDatas(pDataset);

}

void QSttCommCfgPointTblFileEditorDlg::slot_AppendRow_Clicked()
{
	if (m_pTabWidget->currentIndex() == 0)
	{
		Append_IntervalSetTab();
	}else
	{
		Append_TeleMeasureTab();

	}
}

void QSttCommCfgPointTblFileEditorDlg::slot_InsertRow_Clicked()
{
	//m_pDvmDevice->ChangePosition(0,1);
	//m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);
	if (m_pTabWidget->currentIndex() == 0)
	{
		int nTabCount = m_pTabWidget->count() - 1;
		//if (m_pDvmDevice->GetCount() < QSTTCOMMCFGPOINTTB_MAX_TABS)
		if (nTabCount < QSTTCOMMCFGPOINTTB_MAX_TABS)
		{
			Insert_IntervalSetTab();
			ModifyIdxInIntervalSetCombo();
		}
		//间隔Combo设置+1  (m_pTabWidget->count()-1)
		//if (m_pDvmDevice->GetCount()<= QSTTCOMMCFGPOINTTB_MAX_TABS) 
		int nTabCount2 = m_pTabWidget->count() - 1;
		if (nTabCount2 <= QSTTCOMMCFGPOINTTB_MAX_TABS) 
		{
			m_pIntervalNums_Combo->setCurrentIndex(nTabCount2-1);
		}

	}
	else
	{
		Insert_TeleMeasureTab();
	}
	////SaveDvmXmlFile();
}

void QSttCommCfgPointTblFileEditorDlg::CopyToDataListUnExistInApplyAll(CDvmDataset *pDatasetChk,QList<CDvmData*>& pDataCpSrc)
 { 
	 for (int i=0; i<pDataCpSrc.size(); i++)
	 {
		 CDvmData*pCpDvmdata = (CDvmData*)pDataCpSrc.at(i);
		 POS posData = pDatasetChk->GetHeadPosition();
		 bool isFind = false;
		 while(posData != NULL)
		 {
			 CExBaseList  *pData = (CExBaseList *)pDatasetChk->GetNext(posData);
			 int crtidDaset = pData->GetClassID();
			 if (crtidDaset != DVMCLASSID_CDVMDATA)
			 {
				 continue;
			 }
			 CDvmData *pDataEnd = (CDvmData*)pData;
			 CString dataidStr = pDataEnd->m_strID;
			 if (dataidStr == pCpDvmdata->m_strID)
			 {
				 isFind = true;
				 break;
			 }
		 }
		 if (!isFind)
		 {
			 CDvmData *pConeData = (CDvmData*)pCpDvmdata->Clone();
			 //pListNew->append(pConeData);
			 pDatasetChk->AddNewChild(pConeData);
		 }
	 }
 }

void QSttCommCfgPointTblFileEditorDlg::SearchDatasetInOtherTab(CString strLdID,CString strDatasetID,QList<CDvmData*>& pDataCpSrc)
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}
	POS posLogicDev = m_pDvmDevice->GetHeadPosition();
	CExBaseList *pLogicDev = NULL;
	CExBaseList *pDataSet = NULL;
	while (posLogicDev != NULL)
	{
		pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(posLogicDev);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}	
		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
		if (pLogicDev->m_strID == strLdID)
		{
			continue;
		}
		POS posDataset = pLogicDev->GetHeadPosition();
		while(posDataset != NULL)
		{
			pDataSet = (CExBaseList *)pLogicDev->GetNext(posDataset);
			int crtidDaset = pDataSet->GetClassID();
			if (crtidDaset != DVMCLASSID_CDVMDATASET)
			{
				continue;
			}
			CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
			CString dataidStr = pDataset->m_strID;
			if (dataidStr == strDatasetID)
			{
				CopyToDataListUnExistInApplyAll(pDataset,pDataCpSrc);
			}
			//stringlist->append(dataidStr);
		}
	}
}

void QSttCommCfgPointTblFileEditorDlg::slot_ApplyAll_Clicked()
{
	//m_pDvmDevice->ChangePosition(0,1);
	//m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);

	m_bApplyAllFlg = TRUE;
	if (m_pTabWidget->currentIndex() == 0)
	{
		return;
	}
	GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
	QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
	CExBaseList *pXSclFileObj = (CExBaseList*)pRightGrid->GetDatas();
	CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
	 CDvmLogicDevice *parentlogDev = (CDvmLogicDevice*)(pDataset->GetParent());
	 parentlogDev->m_strID;
	 parentlogDev->GetHeadPosition();

	///////////////////////
	 POS posDataset = parentlogDev->GetHeadPosition();
	 while(posDataset != NULL)
	 {
		 CExBaseList *pDataSet = (CExBaseList *)parentlogDev->GetNext(posDataset);
		 int crtidDaset = pDataSet->GetClassID();
		 if (crtidDaset != DVMCLASSID_CDVMDATASET)
			{
				continue;
			}
		 CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
		 CString dataidStr = pDataset->m_strID;
		 POS posData = pDataset->GetHeadPosition();
		 QList<CDvmData*> pDatasList;
		 while(posData != NULL)
		 {
			CExBaseList  *pData = (CExBaseList *)pDataset->GetNext(posData);
			int crtidDaset = pData->GetClassID();
			if (crtidDaset != DVMCLASSID_CDVMDATA)
			{
				continue;
			}
			CDvmData *pDataFind = (CDvmData*)pData;
			pDatasList.append(pDataFind);		

		 }
		 SearchDatasetInOtherTab(parentlogDev->m_strID, pDataset->m_strID, pDatasList);

		 //stringlist->append(dataidStr);
	 }
	////////////////	 /
	SetStartAddrAllTeleTabs();
	RefreshAllTeleTabs();
}

void QSttCommCfgPointTblFileEditorDlg::SetStartAddrAllTeleTabs()
{
	m_pTabWidget->count();
	for (int i=1; i<m_pTabWidget->count(); i++)
	{
		GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->widget(i);
		pGenTab->m_pTeleGridTabWight;
		for (int j=0; j<pGenTab->m_pTeleGridTabWight->count(); j++)
		{
			QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->widget(j);
			CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
			CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
			POS posData = pDataset->GetHeadPosition();
			int startAddrTem = 0;
			while(posData != NULL)
			 {
				 CExBaseList  *pData = (CExBaseList *)pDataset->GetNext(posData);
				 int crtidDaset = pData->GetClassID();
				 if (crtidDaset != DVMCLASSID_CDVMDATA)
				 {
					 continue;
				 }
				 CDvmData *pDataFind = (CDvmData*)pData;
				 pDataFind->m_nIndex = pDataset->m_nAddr+startAddrTem;
				 ++startAddrTem;
			 }

		}

	}

	//m_pTabWidget->currentIndex();
	//GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
	//QExBaseListGridBase *pRightGrid=(QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
	//CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
	//CDvmDataset *pDataset=(CDvmDataset*) pXSclFileObj;
}

void QSttCommCfgPointTblFileEditorDlg::RefreshAllTeleTabs()
{
	m_pTabWidget->count();
	for (int i=1; i<m_pTabWidget->count(); i++)
	{
		GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->widget(i);
		pGenTab->m_pTeleGridTabWight;
		for (int j=0; j<pGenTab->m_pTeleGridTabWight->count(); j++)
		{
			QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->widget(j);
			CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
			CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
			pRightGrid->ShowDatas(pDataset);
		}		
	}
	//m_pTabWidget->currentIndex();
	//GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
	//QExBaseListGridBase *pRightGrid=(QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
	//CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
	//CDvmDataset *pDataset=(CDvmDataset*) pXSclFileObj;
}



void QSttCommCfgPointTblFileEditorDlg::DeleleIntervalSetTableMultiRow(int nDelNum)
{
	if (m_pIntervalSetGrid->rowCount() <= 0)
	{
		return;
	}
	while(nDelNum > 0)
	{
		int iLastRow = m_pIntervalSetGrid->rowCount() - 1;
		//CString strFirstLDId = m_pIntervalSetGrid->item(iLastRow,0)->text();
		//m_pDvmDevice->DeleteByID(strFirstLDId);	

		m_pDvmDevice->DeleteTail();
		
		//m_pTabWidget->count()
//for (int i=0; i<m_pTabWidget->count(); i++)
//{
//	if (m_pTabWidget->tabText(i) == strFirstLDId)
//	{
//		m_pTabWidget->removeTab(i);
//	}
//}
		m_pIntervalSetGrid->removeRow(iLastRow);

		--nDelNum;


		m_pTabWidget->removeTab(m_pTabWidget->count()-1);


	}
	m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);
	//间隔Combo设置-1
	//m_pIntervalNums_Combo->setCurrentIndex(m_pDvmDevice->GetCount());

	//while((m_pTabWidget->count()) > QSTTCOMMCFGPOINTTB_MAX_TABS)
	//{
	//	m_pTabWidget->removeTab(m_pTabWidget->count()-1);
	//}

}

void QSttCommCfgPointTblFileEditorDlg::slot_IntervalSetTableChanged()
{
	//slot_SaveClicked();
}

void QSttCommCfgPointTblFileEditorDlg::slot_RightParaSetTableChanged()
{
	//slot_SaveClicked();
}

void QSttCommCfgPointTblFileEditorDlg::slot_RightTeleMearTableChanged()
{
	//slot_SaveClicked();
}


void QSttCommCfgPointTblFileEditorDlg::slot_IntervalSetComboChanged(int iCurretIdx)
{
	if (m_pTabWidget->currentIndex() == 0)
	{
		int nCurrTabCount = m_pTabWidget->count() - 1;

		CString strCrtText = m_pIntervalNums_Combo->itemText(iCurretIdx);
		long lCrtSel = CString_To_long(strCrtText);
		//if (lCrtSel == m_pDvmDevice->GetCount())
		if (lCrtSel == nCurrTabCount)
		{
			return;
		}
		//if (lCrtSel < m_pDvmDevice->GetCount())
		if (lCrtSel < nCurrTabCount)
		{
			//int nDelNum = m_pDvmDevice->GetCount()-lCrtSel;
			int nDelNum = nCurrTabCount - lCrtSel;
			DeleleIntervalSetTableMultiRow(nDelNum);
			//return;
		}
		//else if (lCrtSel > m_pDvmDevice->GetCount())
		else if (lCrtSel > nCurrTabCount)
		{
			//int iSize = lCrtSel-m_pDvmDevice->GetCount();
			int iSize = lCrtSel- nCurrTabCount;
			for (int i=0; i<iSize; i++)
			{
				Append_IntervalSetTab();
			}
		}
		ModifyIdxInIntervalSetCombo();
		////SaveDvmXmlFile();
	}

}

void QSttCommCfgPointTblFileEditorDlg::slot_Export_Clicked()
{
	if (m_pTabWidget->currentIndex() == 0)//间隔表导出
	{
		CString strFilePath;
		CString strDevID = m_pDvmDevice->m_strID;
#ifdef _PSX_QT_LINUX_
		CString strDefFileName = "AllLdAddrsExport.xml";
		if (!strDevID.IsEmpty())
		{
			strDefFileName = strDevID + ".xml";
		}
		strFilePath = GetLinuxPathAtExportAddrClicked(strDefFileName);
#else
		strFilePath = QFileDialog::getSaveFileName(this, g_sLangTxt_Save, _P_GetInstallPath(), _T("首地址配置文件(*.xml)"));
#endif
		
		CDvmDevice *pCopyDvmDevice = (CDvmDevice*)m_pDvmDevice->Clone();
		POS pos = pCopyDvmDevice->GetHeadPosition();
		CExBaseList *pLogicDev = NULL;
		CExBaseList *pDataSet = NULL;	
		while (pos != NULL)
		{
			pLogicDev = (CExBaseList *)pCopyDvmDevice->GetNext(pos);
			int crtidLgDev = pLogicDev->GetClassID();
			if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
			{
				continue;
			}	
			CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;		
			POS posLgDev = pLogicDev->GetHeadPosition();
			while(posLgDev != NULL)
			{
				pDataSet = (CExBaseList *)pLogicDev->GetNext(posLgDev);
				int crtidDaset = pDataSet->GetClassID();
				if (crtidDaset != DVMCLASSID_CDVMDATASET)
				{
					continue;
				}
				CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
				pDataSet->DeleteChildren();		
				CString dataidStr = pDataset->m_strID;
				//stringlist->append(dataidStr);
			}

		}
		pCopyDvmDevice->SaveXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
		delete pCopyDvmDevice;
		//
		////dete

	}
	else
	{
		GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
		QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
		CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
		CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
		if (pDataset == NULL)
		{
			return;
		}

		CString strFilePath;
		CString strDataSetID = pDataset->m_strID;
#ifdef _PSX_QT_LINUX_
		CString strDefFileName = "SingleLdAddrsExport.xml";
		if (!strDataSetID.IsEmpty())
		{
			strDefFileName = strDataSetID + ".xml";
		}
		strFilePath = GetLinuxPathAtExportAddrClicked(strDefFileName);
#else
		strFilePath = QFileDialog::getSaveFileName(this, g_sLangTxt_Save, _P_GetInstallPath(), _T("数据集内容(*.xml)"));
#endif
		
		//GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
		//QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
		//CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
		//CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
		CDvmDataset *pCopyDataset = (CDvmDataset*)pDataset->Clone();
		pCopyDataset->SaveXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
		//pCopyDataset->SaveXmlFile(CString("C:/Users/HP/Desktop/Work/规约文件测试/zzzExportAddr.xml"), CDataMngrXmlRWKeys::g_pXmlKeys);

	}
}

void QSttCommCfgPointTblFileEditorDlg::slot_Import_Clicked()
{

	if (m_pTabWidget->currentIndex() == 0)//间隔表导出
	{
		CString strFilePath;
#ifdef _PSX_QT_LINUX_
		strFilePath = GetLinuxPathAtImportAddrClicked();
#else
		 strFilePath = QFileDialog::getOpenFileName(this,g_sLangTxt_Open,_P_GetInstallPath(),_T("首地址配置文件(*.xml)"));
#endif
		CDvmDevice *pNewDvmDevice = new CDvmDevice;
		pNewDvmDevice->OpenXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
		//pNewDvmDevice->OpenXmlFile(CString("C:/Users/HP/Desktop/Work/规约文件测试/zzzExportInterval.xml"), CDataMngrXmlRWKeys::g_pXmlKeys);

		POS pos = pNewDvmDevice->GetHeadPosition();
		while (pos != NULL)
		{
			CExBaseList *pLogicDev = (CExBaseList *)pNewDvmDevice->GetNext(pos);
			int crtidLgDev = pLogicDev->GetClassID();
			if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
			{
				continue;
			}	
			CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;		
			POS posLgDev = pLogicDev->GetHeadPosition();
			while(posLgDev != NULL)
			{
				CExBaseList *pDataSet = (CExBaseList *)pLogicDev->GetNext(posLgDev);
				int crtidDaset = pDataSet->GetClassID();
				if (crtidDaset != DVMCLASSID_CDVMDATASET)
				{
					continue;
				}
				CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
				CString dataidStr = pDataset->m_strID;
				if ((pDataset->m_nAddr>0) && (!dataidStr.IsEmpty()))
				{
					SyncAddrToInvalSetTable(pLogicDevice->m_strID, pDataset->m_strID, pDataset->m_nAddr);
				}
				//stringlist->append(dataidStr);
			}
		}
		m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);
	}
	else
	{
		CString strFilePath;
#ifdef _PSX_QT_LINUX_
		strFilePath = GetLinuxPathAtImportAddrClicked();
#else
		strFilePath = QFileDialog::getOpenFileName(this,g_sLangTxt_Open,_P_GetInstallPath(),_T("数据集内容(*.xml)"));
#endif
		
		CDvmDataset *pNewDataset = new CDvmDataset;
		GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->currentWidget();
		QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->currentWidget();
		CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
		CDvmDataset *pCurrentDataset = (CDvmDataset*) pXSclFileObj;
		pNewDataset->OpenXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
		//pNewDataset->OpenXmlFile(CString("C:/Users/HP/Desktop/Work/规约文件测试/zzzExportAddr.xml"), CDataMngrXmlRWKeys::g_pXmlKeys);
		if (pNewDataset->m_strID != pCurrentDataset->m_strID)
		{
			return;
		}
		POS posNew = pNewDataset->GetHeadPosition();
		while (posNew != NULL)
		{
			CExBaseList *pDataNew = (CExBaseList *)pNewDataset->GetNext(posNew);
			int crtidLgDev = pDataNew->GetClassID();
			if (crtidLgDev != DVMCLASSID_CDVMDATA)
			{
				continue;
			}
			CDvmData *pDataNw = (CDvmData*)pDataNew;
			CString dataidStr = pDataNw->m_strID;
			if (pDataNw->m_nIndex == 0)
			{
				continue;
			}
			POS posOld = pCurrentDataset->GetHeadPosition();
			while(posOld != NULL)
			{
				CExBaseList *pDataOld = (CExBaseList *)pCurrentDataset->GetNext(posOld);
				int crtidLgDev = pDataOld->GetClassID();
				if (crtidLgDev != DVMCLASSID_CDVMDATA)
				{
					continue;
				}
				CDvmData *pDataOd = (CDvmData*)pDataOld;
				if (pDataOd->m_strID == pDataNw->m_strID)
				{
					pDataOd->m_nIndex = pDataNw->m_nIndex;
				}
			}

		}
		pRightGrid->ShowDatas(pCurrentDataset);
	}
}


void QSttCommCfgPointTblFileEditorDlg::SyncAddrToInvalSetTable(CString strLdID,CString strDatasetID,long nArgAddr)
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}
	POS posLogicDev = m_pDvmDevice->GetHeadPosition();
	CExBaseList *pLogicDev = NULL;
	CExBaseList *pDataSet = NULL;
	while (posLogicDev != NULL)
	{
		pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(posLogicDev);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}	
		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
		if (pLogicDev->m_strID != strLdID)
		{
			continue;
		}
		POS posDataset = pLogicDev->GetHeadPosition();
		while(posDataset != NULL)
		{
			pDataSet = (CExBaseList *)pLogicDev->GetNext(posDataset);
			int crtidDaset = pDataSet->GetClassID();
			if (crtidDaset != DVMCLASSID_CDVMDATASET)
			{
				continue;
			}
			CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
			CString dataidStr = pDataset->m_strID;
			if (dataidStr == strDatasetID)
			{
				pDataset->m_nAddr = nArgAddr;
				
			}

			//stringlist->append(dataidStr);
		}

	}

}

void QSttCommCfgPointTblFileEditorDlg::ProcessOverMaxExtraTabs()
{
	//while((m_pTabWidget->count()) > QSTTCOMMCFGPOINTTB_MAX_TABS)
	//{
	//	m_pTabWidget->removeTab(m_pTabWidget->count()-1);
	//}
	//m_pTabWidget->count();
	if (m_pDvmDevice->GetCount() <= QSTTCOMMCFGPOINTTB_MAX_TABS)
	{
		return;
	}
	POS pos = m_pDvmDevice->GetHeadPosition();

	CExBaseList *pLogicDev = NULL;
	int iIntervalSetLDNums = 0;
	while (pos != NULL)
	{
		pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(pos);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}
		iIntervalSetLDNums++;
		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
		if (iIntervalSetLDNums > QSTTCOMMCFGPOINTTB_MAX_TABS)
		{
			m_pDvmDevice->DeleteByID(pLogicDevice->m_strID);	
		}
	}


	


}

CString QSttCommCfgPointTblFileEditorDlg::GetLinuxPathAtImportAddrClicked()
{
	CString strFilePath, strFolderPath;
	strFolderPath = _P_GetInstallPath();
	long nSize = 0;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;

	astrPostfix<<"*.xml";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	if (oOpenDlg.exec() != QDialog::Accepted)
		return strFilePath;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return strFilePath;
	}

	nSize = oOpenDlg.GetFileSize();

#endif

	return strFilePath;
}


CString QSttCommCfgPointTblFileEditorDlg::GetLinuxPathAtExportAddrClicked(CString strDefFileNm)
{
	//CString strFilePath = QFileDialog::getSaveFileName(this, g_sLangTxt_Save, _P_GetInstallPath(), _T("首地址配置文件(*.xml)"));

	CString strFilePath, strFolderPath;
	strFolderPath = _P_GetInstallPath();
	CString fileName;
#ifdef _PSX_QT_LINUX_
	QStringList astrPostfix;

	astrPostfix<<"*.xml";	
	QSttPopupSaveAsDialog dlg(strFolderPath,astrPostfix, strDefFileNm, this);
	dlg.InitUI();
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if(rect.height()<650)
	{
		dlg.resize(850,500);
		dlg.setFixedHeight(500);
	}
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg,Keyboard::ENGLISH);
#endif
	if (dlg.exec() != QDialog::Accepted)
	{
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		//return;
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
	strFilePath = dlg.GetFilePath();
	//	fileName += dlg.m_strFileName;

#endif

	return strFilePath;
}

 
void QSttCommCfgPointTblFileEditorDlg::DeleteDvmDeviceByName(CString strName)
{
		CString strDeleteId;
		POS pos = m_pDvmDevice->GetHeadPosition();
		while (pos != NULL)
		{
			CExBaseList *pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(pos);
			int crtidLgDev = pLogicDev->GetClassID();
			if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
			{
				continue;
			}
			
			CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
			if (pLogicDevice != NULL)
			{
				if (pLogicDevice->m_strName == strName)
				{
					strDeleteId = pLogicDevice->m_strID;
					break;
				}
			}
			
		}
		if (!strDeleteId.IsEmpty())
		{
			m_pDvmDevice->DeleteByID(strDeleteId);
		}

}

CDvmLogicDevice* QSttCommCfgPointTblFileEditorDlg::FindDvmDeviceByName(CString strName)
{

 	CDvmLogicDevice* pFindLogicDev = NULL;
	POS pos = m_pDvmDevice->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseList *pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(pos);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
		if (pLogicDevice != NULL)
		{
			if (pLogicDevice->m_strName == strName)
			{
				return pLogicDevice;
			}
		}

	}
	return pFindLogicDev;
}

void QSttCommCfgPointTblFileEditorDlg::ModifyIdxInIntervalSetCombo()
{
	if (m_pDvmDevice->GetCount() == 0)
	{
		return;
	}
	int iIntervSetNms = 1;
	POS pos = m_pDvmDevice->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseList *pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(pos);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}
		//iIntervalSetLDNums++;

		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
		if (pLogicDevice != NULL)
		{
			if(pLogicDevice->m_strID == "report")
			{
				continue;
			}

			CString strDevName = pLogicDevice->m_strName;
			if (strDevName.IsEmpty())
			{
				continue;
			}
			int nSpltPos = strDevName.Find("间隔");
			int nLinePos = strDevName.Find("-");
			//if ((nSpltPos >= 0) && (nLinePos < 0))
			if (nSpltPos >= 0)
			{
				CString strName;
				strName.Format("间隔%d", iIntervSetNms);
				pLogicDevice->m_strName = strName;
				CString strID;
				strID.Format("LDevice%d", iIntervSetNms);
				pLogicDevice->m_strID = strID;
				/////////////////////////////////////////
				for (int i=0; i<m_pTabWidget->count(); i++)
				{
					if (m_pTabWidget->tabText(i) == strDevName )
					{
						m_pTabWidget->setTabText(i,strName);
						break;
					}
				}
				/////////////////////////////////////////

			}
			++iIntervSetNms;
		}

	}
	m_pIntervalSetGrid->ShowDatas(m_pDvmDevice);
	/*
	int sizeTest = m_pTabWidget->count();
	if (sizeTest >= 2)
	{
		for(int i=sizeTest-1; i>=1; i--)
		{
			m_pTabWidget->removeTab(i);
		}
		CalcColums();
	}*/
		
	//for(int i=sizeTest-1; i>=1; i--)
	//{
	//	m_pTabWidget->removeTab(i);
	//}
}


void QSttCommCfgPointTblFileEditorDlg::slot_ChangedAdress(int nRow,int nCol,QString strValue)
{
	if (strValue.isEmpty()) return;

	long lAdressCurValue = 0;
	if ((strValue.contains("0X")==-1) && (strValue.contains("0x")==-1))
	{
		lAdressCurValue = CString_To_long(strValue);
	}
	else
	{
		long nValue = 0;
		char *pzfTmp = NULL;
		CString_to_char(strValue,&pzfTmp);
		HexToLong(pzfTmp,nValue);
		delete pzfTmp;
		lAdressCurValue = nValue;
	}
	
	int nIndex = 0;
	CString strColName = m_pIntervalSetGrid->m_oColNamesList.at(nCol-1);
	CString strTabName = m_pIntervalSetGrid->item(nRow,0)->text();

	//chenling20240301
	if (m_pDvmDevice == NULL)
	{
		return;
	}
	CExBaseList *pLogicDev = NULL;
	CExBaseList *pDataSet = NULL;
	POS pos = m_pDvmDevice->GetHeadPosition();
	while(pos)
	{
		pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(pos);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}
		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
		if (pLogicDevice->m_strName == strTabName)
		{
			POS posLgDev = pLogicDev->GetHeadPosition();
			while(posLgDev != NULL)
			{
				pDataSet = (CExBaseList*)pLogicDev->GetNext(posLgDev);
				int crtidDaset = pDataSet->GetClassID();
				if (crtidDaset != DVMCLASSID_CDVMDATASET)
				{
					continue;
				}
				CDvmDataset *pDataset = (CDvmDataset*)pDataSet;
				if (pDataSet->m_strName == strColName)
				{
					POS pos = pDataSet->GetHeadPosition();
					while(pos)
					{
						CDvmData *pDataFind = (CDvmData*)pDataSet->GetNext(pos);
				pDataFind->m_nIndex = lAdressCurValue + nIndex;
				++nIndex;
					}	
				}
			}
		}
	}

//	for (int i = 1; i < m_pTabWidget->count(); i++)
//	{
//		QString strTabNameTemp = m_pTabWidget->tabText(i);
//		if(strTabNameTemp == strTabName)
//		{
//			GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->widget(i);
//			QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->widget((nCol-1));
// 			CExBaseList *pXSclFileObj = (CExBaseList*) pRightGrid->GetDatas();
// 			CDvmDataset *pDataset = (CDvmDataset*) pXSclFileObj;
// 
// 			POS posLgDev = pDataset->GetHeadPosition();
// 			int nIndex = 0;
// 			while(posLgDev != NULL)
// 			{
// 				CExBaseList  *pData = (CExBaseList *)pDataset->GetNext(posLgDev);
// 				int crtidDaset = pData->GetClassID();
// 				if (crtidDaset != DVMCLASSID_CDVMDATA)
// 				{
// 					continue;
// 				}
// 				CDvmData *pDataFind = (CDvmData*)pData;
// 				pDataFind->m_nIndex = lAdressCurValue + nIndex;
// 				++nIndex;
// 			}
// 			//pRightGrid->ShowDatas(pDataset);
// 			break;
//	}
//	}
}

void QSttCommCfgPointTblFileEditorDlg::EditChangedAdress(QString strtabName,int nChildTabIndex,QString strValue)
{
	if (strValue.isEmpty() || strtabName.isEmpty()) return;
	
	int nRowCount = m_pIntervalSetGrid->rowCount();
	for (int i = 0; i < nRowCount; i++)
	{
		QString strTempName = m_pIntervalSetGrid->item(i,0)->text();
		if(strTempName == strtabName)
		{
			m_pIntervalSetGrid->item(i,(nChildTabIndex+ 1))->setText(strValue);
		}
	}
}

void QSttCommCfgPointTblFileEditorDlg::UpdateIntervalGrid(int nIndex)
{
 	GeneralTab *pGenTab = (GeneralTab*)m_pTabWidget->widget(nIndex);
	if (m_pDvmDevice == NULL)
	{
		return;
	}
	CExBaseList *pLogicDev = NULL;
	CExBaseList *pDataSet = NULL;
	POS pos = m_pDvmDevice->GetHeadPosition();
	while(pos)
	{
		pLogicDev = (CExBaseList *)m_pDvmDevice->GetNext(pos);
		int crtidLgDev = pLogicDev->GetClassID();
		if (crtidLgDev != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}
		CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)pLogicDev;
 		if(pLogicDevice->m_strID == "report")
 		{
 			continue;
 		}
		if (pLogicDevice->m_strName == m_pTabWidget->tabText(nIndex))
		{
			POS posLgDev = pLogicDev->GetHeadPosition();
			while(posLgDev != NULL)
			{
				int nIndexAddress = 0;
				pDataSet = (CExBaseList*)pLogicDev->GetNext(posLgDev);
				
				int crtidDaset = pDataSet->GetClassID();
				if (crtidDaset != DVMCLASSID_CDVMDATASET)
				{
					continue;
				}
				CDvmDataset *pDataset = (CDvmDataset*)pDataSet;

				for (int i = 0; i < pGenTab->m_pTeleGridTabWight->count(); i++)
				{
					long nAddrress = pDataset->m_nAddr;
					CString strName = pGenTab->m_pTeleGridTabWight->tabText(i);
					
					if (pDataset->m_strName == strName)
					{
						POS pos = pDataset->GetHeadPosition();
						while(pos)
					{
							CDvmData *pDataFind = (CDvmData*)pDataSet->GetNext(pos);
							pDataFind->m_nIndex = nAddrress + nIndexAddress;
							++nIndexAddress;
						}	

						QExBaseListGridBase *pRightGrid = (QExBaseListGridBase*)pGenTab->m_pTeleGridTabWight->widget(i);
						pRightGrid->ShowDatas(pDataset);
						break;
					}
				}
			}
		}
	}
}

void QSttCommCfgPointTblFileEditorDlg::slot_ApplyAll( bool bApplyAllFlg )
{
	m_bApplyAllFlg = bApplyAllFlg;
}

