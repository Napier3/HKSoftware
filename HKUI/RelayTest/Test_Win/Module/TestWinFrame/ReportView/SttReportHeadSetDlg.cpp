#include "SttReportHeadSetDlg.h"
#include "ui_SttReportHeadSetDlg.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "XLangResource_PowerTestWin.h"
#include"../../XLanguage/QT/XLanguageAPI_QT.h"


#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
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

	CString strTitle;
	strTitle = GetCtrlDesc("Report_Title");

	m_pTempData = NULL;
	m_pSttReports = NULL;
	this->setWindowTitle(strTitle);

	m_pSttReports = pSttReports;
	m_pTempData = (CDataGroup*)m_pSttReports->Clone();
	
	m_nOkFlag = 0;
	m_bUpataHeadHtml = TRUE;

	SetData();
}

QSttReportHeadSetDlg::~QSttReportHeadSetDlg()
{
	delete m_pTempData;
	m_pTempData = NULL;
    delete ui;
}

void QSttReportHeadSetDlg::SetData()
{
	ui->pushButton_2->setText(/*tr("确定")*/g_sLangTxt_OK);
	ui->pushButton->setText(/*tr("取消")*/g_sLangTxt_Cancel);

	CString strContext;
	strContext = GetCtrlDesc("Report_TestChoose");

	ui->treeWidget->setHeaderLabel(strContext);
	ui->treeWidget->setColumnCount(1);

	QTreeWidgetItemEx *pTopTreeItem = new QTreeWidgetItemEx(ui->treeWidget, NULL);
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
		if (pData != NULL)
		{
			SetTreeItem(pData,pTopTreeItem);
			InitObjValue(pData);
		}
	}
 
 	ui->treeWidget->expandAll();

	CDataGroup *pObj = (CDataGroup*)m_pTempData->GetHead();
	UpdateShow(pObj);

 	connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(slot_TreeItemChanged(QTreeWidgetItem*,int)));
 	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
 	connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
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

	//202405014 suyang 根据配置文件来是否显示表头
	if (pData->m_strValue == _T("0"))
	{
		pTreeItem->setCheckState(0,Qt::Unchecked);
	}
	else
	{
		pTreeItem->setCheckState(0,Qt::Checked);
	}
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

//	UpdateShow(itemText);
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

		if (pitem->checkState(0) == Qt::Unchecked)
		{
			pitem->setCheckState(0,Qt::Checked);
			QTreeWidgetItemEx *pTreechildItem = (QTreeWidgetItemEx *)pitem;
			CDataGroup *pData = (CDataGroup*)pTreechildItem->m_pDataRef;
			pData->m_strValue.Format(_T("%d"), pitem->checkState(0));
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

// void QSttReportHeadSetDlg::UpdateShow( CString strName )
// {
// 	for (int i = 0 ; i < m_labelList.size(); i++)
// 	{
// 		delete m_labelList[i];
// 		m_labelList[i] = NULL;
// 	}
// 	for (int i = 0 ; i < m_editList.size(); i++)
// 	{
// 		delete m_editList[i];
// 		m_editList[i] = NULL;
// 	}
// 
// 	m_labelList.clear();
// 	m_editList.clear();
// 
// 	POS pos = m_pTempData->GetHeadPosition();
// 	while(pos)
// 	{
// 		CDataGroup *pData = (CDataGroup*)m_pTempData->GetNext(pos);
// 		if (pData != NULL)
// 		{
// 			CString str;
// 			str = GetCtrlDesc(StrAddPre(pData->m_strID));
// 
// 			if (strName == str)
// 			{
// 				POS posObj = pData->GetHeadPosition();
// 				int nRow = 0;
// 				while(posObj)
// 				{
// 					CDvmData *pObj = (CDvmData*)pData->GetNext(posObj);
// 					if (pObj != NULL)
// 					{
// 						AddObjToGroup(pObj,nRow++);
// 					}
// 				}
// 			}
// 		}
// 	}
// }

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
// 	m_strValue.clear();
// 
// 	QTreeWidgetItemIterator iterator(ui->treeWidget);
// 	while (*iterator)
// 	{
// 		QTreeWidgetItem *pItem = (*iterator);
// 		CString str;
// 		if (pItem->checkState(0) == Qt::Unchecked)
// 		{
// 			str = _T("0");
// 		}
// 		else
// 			str = _T("1");
// 		
// 		m_strValue.append(str);
// 		iterator++;
// 	}
// 	m_pTempData->m_strValue = m_strValue.at(0);
// 	int nFlag = 1;
// 	POS pos = m_pTempData->GetHeadPosition();
// 	while(pos)
// 	{
// 		CDataGroup *pData = (CDataGroup*)m_pTempData->GetNext(pos);
// 
// 		if(nFlag > m_strValue.size())
// 			return;
// 
// 		if (pData != NULL)
// 		{
// 			pData->m_strValue = m_strValue.at(nFlag++);
// 		}
// 	}
// 
// 	m_pTempData->Copy(m_pSttReports);


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


CString QSttReportHeadSetDlg::StrAddPre( CString strID )
{
	CString str = _T("Report_");

	return str + strID;
}

void QSttReportHeadSetDlg::AddObjToGroup( CDvmData* pData,int nRow )
{
	QSttDvmEdit *tempEdit = new QSttDvmEdit(pData,parentWidget());
	QFont font = tempEdit->font();
	font.setPixelSize(18);

	tempEdit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	tempEdit->setFont(font);
	tempEdit->setText(pData->m_strValue);
	ui->m_pVBox->addWidget(tempEdit,nRow,1);
	m_editList.append(tempEdit);

	tempEdit->setEnabled(pData->m_nIndex);
	QLabel *tempLabel = new QLabel;
	tempLabel->setFont(font);

//	CString str;
//	str = GetCtrlDesc(StrAddPre(pData->m_strID));
//	tempLabel->setText(str + _T(":"));

	tempLabel->setText(pData->m_strName);
	ui->m_pVBox->addWidget(tempLabel,nRow,0);
	m_labelList.append(tempLabel);

	if ((pData->m_strID == STT_REPORTHEAD_TestStartTime) || (pData->m_strID == STT_REPORTHEAD_TestEndTime))
	{
		tempEdit->setVisible(false);
		tempLabel->setVisible(false);
	}
}

CString QSttReportHeadSetDlg::GetCtrlDesc(const CString& strID)
{
	CString strDesc;

	if (strID == _T("Report_Title"))
	{
		strDesc = /*_T("报告内容与格式")*/g_sLangTxt_Report_Title;
	}
	else if (strID == _T("Report_TestChoose"))
	{
		strDesc = /*_T("内容选择")*/g_sLangTxt_Report_TestChoose;
	}
	else if (strID == _T("Report_SubInformation")){
		strDesc = /*_T("变电站信息")*/g_sLangTxt_Report_SubInformation;
	}
	else if (strID == _T("Report_SubName")){
		strDesc = /*_T("变电站名称")*/g_sLangTxt_Report_SubName;
	}
	else if (strID == _T("Report_SubAddr")){
		strDesc = /*_T("变电站地址")*/g_sLangTxt_Report_SubAddr;
	}
	else if (strID == _T("Report_LoopName")){
		strDesc = /*_T("回路名称")*/g_sLangTxt_Report_LoopName;
	}
	else if (strID == _T("Report_LoopAddr")){
		strDesc = /*_T("回路地址")*/g_sLangTxt_Report_LoopAddr;
	}
	else if (strID == _T("Report_Tester")){
		strDesc = /*_T("测试人员")*/g_sLangTxt_Report_Tester;
	}
	else if (strID == _T("Report_DeviceInfor")){
		strDesc = /*_T("被测装置信息")*/g_sLangTxt_Native_TestDevInfo;
	}
	else if (strID == _T("Report_DeviceName")){
		strDesc = /*_T("装置名称")*/g_sLangTxt_Report_DeviceName;
	}
	else if (strID == _T("Report_DeviceSN")){
		strDesc = /*_T("序列号")*/g_sLangTxt_Report_AppSN;
	}
	else if (strID == _T("Report_DeviceModel")){
		strDesc = /*_T("装置型号")*/g_sLangTxt_Report_DeviceModel;
	}
	else if (strID == _T("Report_SettingsNO")){
		strDesc = /*_T("定制单编号")*/g_sLangTxt_Report_SettingsNO;
	}
	else if (strID == _T("Report_DeviceAddr")){
		strDesc = /*_T("装置地址")*/g_sLangTxt_Report_DeviceAddr;
	}
	else if (strID == _T("Report_AdditionalInf")){
		strDesc = /*_T("附加信息")*/g_sLangTxt_Report_AdditionalInf;
	}
	else if (strID == _T("Report_DeviceFactory")){
		strDesc = /*_T("生产厂家")*/g_sLangTxt_Report_DeviceFactory;
	}
	else if (strID == _T("Report_DeviceModel")){
		strDesc = /*_T("装置型号")*/g_sLangTxt_Report_DeviceModel;
	}
	else if (strID == _T("Report_NomSettings")){
		strDesc = /*_T("额定值")*/g_sLangTxt_Report_RatedValue;
	}
	else if (strID == _T("Report_Vnom")){
		strDesc = /*_T("额定电压")*/g_sLangTxt_Report_Vnom;
	}
	else if (strID == _T("Report_Vdc")){
		strDesc = /*_T("辅助直流")*/g_sLangTxt_Report_Vdc;
	}
	else if (strID == _T("Report_SureTime")){
		strDesc = /*_T("开入防抖时间")*/g_sLangTxt_Report_SureTime;
	}
	else if (strID == _T("Report_Inom")){
		strDesc = /*_T("额定电流")*/g_sLangTxt_Native_EDCurrent;
	}
	else if (strID == _T("Report_Vprim")){
		strDesc = /*_T("一次侧电压")*/g_sLangTxt_Report_Vprim;
	}
	else if (strID == _T("Report_Fnom")){
		strDesc = /*_T("额定频率")*/g_sLangTxt_Report_Fnom;
	}
	else if (strID == _T("Report_Iprim")){
		strDesc = /*_T("一次侧电流")*/g_sLangTxt_Report_Iprim;
	}
	else if (strID == _T("Report_TestAppInfor")){
		strDesc = /*_T("测试设备信息")*/g_sLangTxt_Report_TestAppInfor;
	}
	else if (strID == _T("Report_AppModel")){
		strDesc = /*_T("型号")*/g_sLangTxt_Report_AppModel;
	}
	else if (strID == _T("Report_Imax")){
		strDesc = /*_T("电流最大值")*/g_sLangTxt_Report_Imax;
	}
	else if (strID == _T("Report_AppSN")){
		strDesc = /*_T("序列号")*/g_sLangTxt_Report_AppSN;
	}
	else if (strID == _T("Report_TestStartTime")){
		strDesc = /*_T("测试开始时间")*/g_sLangTxt_Report_TestStartTime;
	}
	else if (strID == _T("Report_ComPortType")){
		strDesc = /*_T("通讯口类型")*/g_sLangTxt_Report_ComPortType;
	}
	else if (strID == _T("Report_TestEndTime")){
		strDesc = /*_T("测试终止时间")*/g_sLangTxt_Report_TestEndTime;
	}
	else if (strID == _T("Report_Vmax")){
		strDesc = /*_T("电压最大值")*/g_sLangTxt_Report_Vmax;
	}
	else
	{
		strDesc == /*_T("未知")*/g_sLangTxt_Native_Unknown;
	}

	return strDesc;
}

void QSttReportHeadSetDlg::languageProcessing()
{
	xlang_SetLangStrToWidget_Txt(ui->pushButton,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->pushButton_2,g_sLangTxt_OK,XLang_Ctrls_QPushButton);
}

