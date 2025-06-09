#include "SttIecConfigWidgetBase.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QDialogButtonBox>

#include "SttIecChsEditDialog.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDataBase.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../SttTestSysGlobalPara.h"
//#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../../Module/XLangResource_Native.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
//#pragma execution_character_set("utf-8")

QSttIecConfigWidgetBase::QSttIecConfigWidgetBase(QWidget *parent)
	: QWidget(parent)
{
	m_pIecCfgDataGridBase = NULL;
	m_pIecCfgDatasBase = NULL;
	m_pCopy_IecCfgDataRef = NULL;
	m_bDataSelChanged = false;
	
}

QSttIecConfigWidgetBase::~QSttIecConfigWidgetBase()
{

}

void QSttIecConfigWidgetBase::InitUI()
{
	CreateCtrlBlocksToolbar();
	SetIecConfigWidgetFont();
}

void QSttIecConfigWidgetBase::SetFont(const QFont &oFont)
{
	if (m_pIecCfgDataGridBase != NULL)
	{
		m_pIecCfgDataGridBase->setFont(oFont);
	}
}

void QSttIecConfigWidgetBase::SetIecConfigWidgetFont()
{
	m_pAdd_PushButton->setFont(*g_pSttGlobalFont);
	m_pDel_PushButton->setFont(*g_pSttGlobalFont);
	m_pDeleteN_1_PushButton->setFont(*g_pSttGlobalFont);
	m_pSelAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pUnSelectedAll_PushButton->setFont(*g_pSttGlobalFont);
	m_pCopy_PushButton->setFont(*g_pSttGlobalFont);
	m_pPaste_PushButton->setFont(*g_pSttGlobalFont);
	m_pChannelEdit_PushButton->setFont(*g_pSttGlobalFont);
}

//控制块工具栏
void QSttIecConfigWidgetBase::CreateCtrlBlocksToolbar()
{
	m_pCtrlBlocksSetHLayout = new QHBoxLayout();
	m_pAdd_PushButton = new QPushButton(g_sLangTxt_Add);
	xlang_SetLangStrToWidget(m_pAdd_PushButton, "sAdd", XLang_Ctrls_QPushButton);
	connect(m_pAdd_PushButton,SIGNAL(clicked()),SLOT(slot_AddClicked()));
	m_pCtrlBlocksSetHLayout->addWidget(m_pAdd_PushButton);

	m_pDel_PushButton = new QPushButton(g_sLangTxt_Delete);
	xlang_SetLangStrToWidget(m_pDel_PushButton, "sDelete", XLang_Ctrls_QPushButton);
	connect(m_pDel_PushButton,SIGNAL(clicked()),SLOT(slot_DelClicked()));
	m_pCtrlBlocksSetHLayout->addWidget(m_pDel_PushButton);

	m_pDeleteN_1_PushButton = new QPushButton(g_sLangTxt_IEC_DeleteAllButFirst);
	xlang_SetLangStrToWidget(m_pDeleteN_1_PushButton, "IEC_DeleteAllButFirst", XLang_Ctrls_QPushButton);
	connect(m_pDeleteN_1_PushButton, SIGNAL(clicked()), SLOT(OnDeleteN_1Clicked()));
	m_pCtrlBlocksSetHLayout->addWidget(m_pDeleteN_1_PushButton);

	m_pSelAll_PushButton = new QPushButton(g_sLangTxt_SelAll);
	xlang_SetLangStrToWidget(m_pSelAll_PushButton, "sSelAll", XLang_Ctrls_QPushButton);
	connect(m_pSelAll_PushButton, SIGNAL(clicked()), SLOT(slot_SelAllClicked()));
	m_pCtrlBlocksSetHLayout->addWidget(m_pSelAll_PushButton);

	m_pUnSelectedAll_PushButton = new QPushButton(g_sLangTxt_SelNone);
	xlang_SetLangStrToWidget(m_pUnSelectedAll_PushButton, "sSelNone", XLang_Ctrls_QPushButton);
	connect(m_pUnSelectedAll_PushButton, SIGNAL(clicked()), SLOT(slot_UnSelectedAllClicked()));
	m_pCtrlBlocksSetHLayout->addWidget(m_pUnSelectedAll_PushButton);
 
	m_pCopy_PushButton = new QPushButton(g_sLangTxt_Copy);
	xlang_SetLangStrToWidget(m_pCopy_PushButton, "sCopy", XLang_Ctrls_QPushButton);
 	connect(m_pCopy_PushButton,SIGNAL(clicked()),SLOT(slot_CopyClicked()));
 	m_pCtrlBlocksSetHLayout->addWidget(m_pCopy_PushButton);

	m_pPaste_PushButton = new QPushButton(g_sLangTxt_Paste);
	xlang_SetLangStrToWidget(m_pPaste_PushButton, "sPaste", XLang_Ctrls_QPushButton);
	connect(m_pPaste_PushButton,SIGNAL(clicked()),SLOT(slot_PasteClicked()));
	m_pCtrlBlocksSetHLayout->addWidget(m_pPaste_PushButton);

	m_pCtrlBlocksSetHLayout->addStretch();

	m_pChannelEdit_PushButton = new QPushButton(g_sLangTxt_IEC_ChEdit);
	xlang_SetLangStrToWidget(m_pChannelEdit_PushButton, "IEC_ChEdit", XLang_Ctrls_QPushButton);
	connect(m_pChannelEdit_PushButton,SIGNAL(clicked()),SLOT(slot_ChannelEditClicked()));
	m_pCtrlBlocksSetHLayout->addWidget(m_pChannelEdit_PushButton);

#ifndef _PSX_QT_LINUX_
	m_pChannelEdit_PushButton->setVisible(false);
#endif

//	m_pCtrlBlocksSetHLayout->addStretch();
}

void QSttIecConfigWidgetBase::InitData(CIecCfgDatasBase* pIecCfgDatasBase)
{
	ASSERT(pIecCfgDatasBase);
	m_pIecCfgDatasBase = pIecCfgDatasBase;
	m_pIecCfgDataGridBase->AttachDataViewOptrInterface(this);
	m_pIecCfgDataGridBase->ShowDatas(pIecCfgDatasBase);
	m_pIecCfgDataGridBase->SelectRow(1);
	OnDataSelChanged(m_pIecCfgDataGridBase, 0, 0);//20241023 wuxinyi 打开配置文件，行不变槽函数不响应，数据不刷新，强制再次刷新
	EnableAllButtons();
}

CIecCfgChsBase* QSttIecConfigWidgetBase::GetCfgChs()
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)m_pIecCfgDataGridBase->GetCurrSelData();
	return pIecCfgData->m_pCfgChs;
}

void QSttIecConfigWidgetBase::AttachRefChsGrid(QExBaseListGridBase *pRefChsGrid)
{
	if (m_pIecCfgDataGridBase == NULL)
	{
		return;
	}

	m_pIecCfgDataGridBase->AttachRefChsGrid(pRefChsGrid);
}

void QSttIecConfigWidgetBase::SetChannelEditBtnVisible(bool bVisible)
{
	if (m_pChannelEdit_PushButton == NULL)
	{
		return;
	}
	
	m_pChannelEdit_PushButton->setVisible(bVisible);
}

void QSttIecConfigWidgetBase::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)//update
{
	EnableAllButtons();

	if (m_pIecCfgDataGridBase == NULL)
	{
		return;
	}

	if (m_pIecCfgDataGridBase != pGridCtrl)
	{
		return;
	}

	CExBaseList *pCurrSelData =  (CExBaseList*)m_pIecCfgDataGridBase->GetCurrSelData();

	if (pCurrSelData == NULL)
	{
		return;
	}

	m_bDataSelChanged = true;
	emit sig_UpdateCB_ChDatas(pCurrSelData);//更新控制块通道数据
}

CIecCfgDataBase* QSttIecConfigWidgetBase::AddNewIecCfgData()
{
	if (m_pIecCfgDatasBase == NULL)
	{
		return NULL;
	}

	if (m_pIecCfgDatasBase->GetCount()>32)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,_T("当前总控制块数量大于32个,无法继续添加."));
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_block.GetString());	
		return NULL;
	}

	return m_pIecCfgDatasBase->AddNewIecCfgData();
}

void QSttIecConfigWidgetBase::OnScrollGridFinished()
{
	EnableAllButtons();
}

void QSttIecConfigWidgetBase::slot_AddClicked()
{
	CIecCfgDataBase *pCfgData = AddNewIecCfgData();

	if (pCfgData == NULL)
	{
		return;
	}
	//2023-12-15 suyang FT3 判断当前光口数是否添加控制块
// 	int nGirdRowCount = m_pIecCfgDataGridBase->rowCount();
// 	long nFiberCount = 0;
// 	if (pCfgData->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
// 	{
// 		nFiberCount = CCfgDataMngrConstGlobal::GetAppPortFT3Num_ST();
// 
// 	}
// 	else if (pCfgData->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA)
// 	{
// 		nFiberCount = CCfgDataMngrConstGlobal::GetAppPortFT3InNum_ST();
// 	}
// 
// 	if (nFiberCount != 0)
// 	{
// 		if (nGirdRowCount >= nFiberCount)
// 		{
// 			QMessageBox::information(this, tr("提示"),tr("光口已全部占用，当前无可选择的光口！"));
// 			return;
// 		}
// 	}

	pCfgData->m_nUseFlag = 0;

	if (m_pIecCfgDatasBase->CanAddCfgData(pCfgData->GetClassID()))
	{
		pCfgData->m_nUseFlag = 1;
	}

	AutoSetCfgDataValue(pCfgData, 1);
	UpdateAppMaps();
	m_pIecCfgDataGridBase->InsertData(pCfgData);
//	emit sig_UpdateCB_ChDatas(pCfgData);
// #endif

	emit sig_UpdateCB_ChDatas(pCfgData);
//	m_pIecCfgDataGridBase->ShowDatas(m_pIecCfgDatasBase);

	EnableAllButtons();
	m_pIecCfgDataGridBase->SelectRow(pCfgData);
	//dingxy 20240904 linux下槽函数不响应，直接根据当前选择的控制块初始化通道数据
#ifdef _PSX_QT_LINUX_
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)m_pIecCfgDataGridBase->GetCurrSelData();
	if (pIecCfgData == NULL)
	{
		return;
	}
	if ((pIecCfgData->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA)
		|| (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA))
	{
		g_oSttTestResourceMngr.m_oIecDatasMngr.UpdateFT3ChsTypeChanged(pIecCfgData->m_pCfgChs, g_oSystemParas.m_nIecFormat);
	}
#endif
}

void QSttIecConfigWidgetBase::slot_DelClicked()
{
	ASSERT (m_pIecCfgDataGridBase != NULL);
	ASSERT(m_pIecCfgDatasBase);
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)m_pIecCfgDataGridBase->GetCurrSelData();

	if (pIecCfgData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_Controlblock.GetString());
		return;
	}

	CExBaseList oList;
	m_pIecCfgDatasBase->GetIecCfgDatas(oList);
	long nCurCount = oList.GetCount();

	if (nCurCount <= 1)
	{
		oList.RemoveAll();
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_leastone.GetString());
		return;
	}


	if ((m_pCopy_IecCfgDataRef != NULL)&&(m_pCopy_IecCfgDataRef == pIecCfgData))
	{
		m_pCopy_IecCfgDataRef = NULL;
	}

	long nIndex = oList.FindIndex(pIecCfgData);
	CIecCfgDataBase *pNextCfgData = (CIecCfgDataBase*)oList.GetAt(nIndex-1);
	oList.Remove(pIecCfgData);
	m_pIecCfgDataGridBase->DeleteDataRow(pIecCfgData,TRUE);
//	m_pIecCfgDatasBase->Delete(pIecCfgData);
	UpdateAppMaps();
//	m_pIecCfgDataGridBase->ShowDatas(m_pIecCfgDatasBase);
	EnableAllButtons();

	if (pNextCfgData == NULL)
	{
		pNextCfgData = (CIecCfgDataBase*)oList.GetHead();
	}

	if (pNextCfgData != NULL)
	{
		if(g_oSystemParas.m_nIecFormat != STT_IEC_FORMAT_61850_92)//20240801 suyang 除9-2其他类型删除后子节点都先清空,通过点击控制块显示通道数据
		{
			emit sig_UpdateCB_ChDatas(NULL);
		}
		else
		{
		emit sig_UpdateCB_ChDatas(pNextCfgData);
		}

		//emit sig_UpdateCB_ChDatas(pNextCfgData);
		m_pIecCfgDataGridBase->SelectRow(pNextCfgData);
	} 
	else
	{
		emit sig_UpdateCB_ChDatas(NULL);
	}

	oList.RemoveAll();
}

void QSttIecConfigWidgetBase::slot_CopyClicked()
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)m_pIecCfgDataGridBase->GetCurrSelData();

	if (pIecCfgData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_copyblock.GetString());
		return;
	}

	m_pCopy_IecCfgDataRef = pIecCfgData;
	EnableAllButtons();
}

void QSttIecConfigWidgetBase::slot_PasteClicked()
{
	if (m_pCopy_IecCfgDataRef == NULL)
	{
		return;
	}

	CIecCfgDataBase *pCfgData = (CIecCfgDataBase*)m_pCopy_IecCfgDataRef->Clone();

	if (pCfgData->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
	{
		CIecCfgGinData *pGinData = (CIecCfgGinData*)pCfgData;
		pGinData->InitBinChMaps();
	}

	unsigned long long vFiberMin, vFiberMax;
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(m_pIecCfgDataGridBase->GetAppPortDataType());
	vFiberMin = 0;
	vFiberMax = -1;

	if (pDataType != NULL)
	{
		if (pDataType->GetCount()<=0)
		{
			vFiberMax = 0;
		}
		else
		{
			vFiberMax =  pDataType->GetCount() - 1;
		}
	}

	unsigned long long  vValue;
	m_pIecCfgDatasBase->AutoSetCfgDataValue(pCfgData, CFGDATAID_FIBER, vValue, 1, &vFiberMin, &vFiberMax);
	unsigned long long  vAppID = pCfgData->GetAppID();
	unsigned long long  vFiberIndex = pCfgData->m_nFiberIndex;

	if (m_pIecCfgDatasBase->HasCfgDataValue(pCfgData,CFGDATAID_APPID,vAppID)&&
		m_pIecCfgDatasBase->HasCfgDataValue(pCfgData,CFGDATAID_FIBER,vFiberIndex))
	{
		CXMessageBox::information(NULL,QObject::tr("error"),QObject::tr("AppID Repeat !"));
		delete pCfgData;
		return;
	}

//	pCfgData->InitAfterRead();
	m_pIecCfgDatasBase->AddNewChild(pCfgData);

	if (!m_pIecCfgDatasBase->CanAddCfgData(pCfgData->GetClassID()))
	{
		pCfgData->m_nUseFlag = 0;
	}
	else
	{
		pCfgData->m_nUseFlag = 1;
	}

	UpdateAppMaps();
	m_pIecCfgDataGridBase->ShowDatas(m_pIecCfgDatasBase);
	EnableAllButtons();
	m_pIecCfgDataGridBase->SelectRow(pCfgData);
}

void QSttIecConfigWidgetBase::slot_ChannelEditClicked()
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)m_pIecCfgDataGridBase->GetCurrSelData();

	if (pIecCfgData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_viewchannel.GetString());
		return;
	}

	long nChsType = STT_IEC_CHS_TYPE_SMV92;

	if (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFG92DATA)
	{
		nChsType = STT_IEC_CHS_TYPE_SMV92;
	}
	else if (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
	{
		nChsType = STT_IEC_CHS_TYPE_SMV92IN;
	}
	else if (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
	{
		nChsType = STT_IEC_CHS_TYPE_GIN;
	}
	else if (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
	{
		nChsType = STT_IEC_CHS_TYPE_GOUT;
	}
	else if (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
	{
		nChsType = STT_IEC_CHS_TYPE_SMV_FT3OUT;
	}
	else if (pIecCfgData->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA)
	{
		nChsType = STT_IEC_CHS_TYPE_SMV_FT3IN;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_dataobject.GetString(),pIecCfgData->GetClassID());
		return;
	}

	QSttIecChsEditDialog oSttIecChsEdit(nChsType,this);
	oSttIecChsEdit.setFont(font());

	if (m_pIecCfgDataGridBase != NULL)
	{
		oSttIecChsEdit.InitData(pIecCfgData->m_pCfgChs);
	}

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oSttIecChsEdit,Keyboard::ENGLISH);
#endif
	oSttIecChsEdit.exec();
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::ReAttachObj();
#endif
}

void QSttIecConfigWidgetBase::slot_SelAllClicked()
{
	ASSERT (m_pIecCfgDataGridBase != NULL);
	ASSERT(m_pIecCfgDatasBase);
	UINT nClassID = GetClassID();
	m_pIecCfgDatasBase->SetSelectState_AllCtrlBlock(1,nClassID);
	m_pIecCfgDataGridBase->UpdateSelectedState();
//	m_pIecCfgDataGridBase->ShowDatas(m_pIecCfgDatasBase);
}

void QSttIecConfigWidgetBase::slot_UnSelectedAllClicked()
{
	ASSERT (m_pIecCfgDataGridBase != NULL);
	ASSERT(m_pIecCfgDatasBase);
	UINT nClassID = GetClassID();
	m_pIecCfgDatasBase->SetSelectState_AllCtrlBlock(0,nClassID);
	m_pIecCfgDataGridBase->UpdateSelectedState();
//	m_pIecCfgDataGridBase->ShowDatas(m_pIecCfgDatasBase);
}

void QSttIecConfigWidgetBase::OnDeleteN_1Clicked()
{
	ASSERT (m_pIecCfgDataGridBase != NULL);
	ASSERT(m_pIecCfgDatasBase);
	CExBaseList oList;
	m_pIecCfgDatasBase->GetIecCfgDatas(oList);
	long nCurCount = oList.GetCount();

	if (nCurCount <= 1)
	{
		oList.RemoveAll();
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,g_sLangTxt_leastone.GetString());
		return;
	}

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		nIndex++;

		if (nIndex>1)
		{
			m_pIecCfgDatasBase->Delete(pCurObj);
		}
		else if (m_pCopy_IecCfgDataRef != pCurObj)
		{
			m_pCopy_IecCfgDataRef = NULL;
		}
	}

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase *)oList.GetHead();
	oList.RemoveAll();
	UpdateAppMaps();
	m_pIecCfgDataGridBase->ShowDatas(m_pIecCfgDatasBase);
	EnableAllButtons();

	if (pIecCfgData != NULL)
	{
		m_pIecCfgDataGridBase->SelectRow(pIecCfgData);
		
		if(g_oSystemParas.m_nIecFormat != STT_IEC_FORMAT_61850_92)//20240801 suyang 除9-2其他类型删除后子节点都先清空,通过点击控制块显示通道数据
		{
			emit sig_UpdateCB_ChDatas(NULL);
		}
		else
		{
		emit sig_UpdateCB_ChDatas(pIecCfgData);
		}
		//emit sig_UpdateCB_ChDatas(pIecCfgData);
	} 
	else
	{
		emit sig_UpdateCB_ChDatas(NULL);
	}
}

void QSttIecConfigWidgetBase::EnableAllButtons()
{
	if (m_pCopy_IecCfgDataRef == NULL)
	{
		m_pPaste_PushButton->setEnabled(false);
	}
	else
	{
		m_pPaste_PushButton->setEnabled(true);
	}

	if (m_pIecCfgDataGridBase->GetCurrSelData() == NULL)
	{
		m_pCopy_PushButton->setEnabled(false);
		m_pDel_PushButton->setEnabled(false);
		m_pChannelEdit_PushButton->setEnabled(false);
	} 
	else
	{
		m_pCopy_PushButton->setEnabled(true);
		m_pDel_PushButton->setEnabled(true);
		m_pChannelEdit_PushButton->setEnabled(true);
	}
}

void QSttIecConfigWidgetBase::AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nOffset)
{
	if (m_pIecCfgDatasBase == NULL)
	{
		return;
	}

	unsigned long long vFiberMin, vFiberMax;
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(m_pIecCfgDataGridBase->GetAppPortDataType());
	vFiberMin = 0;
	vFiberMax = -1;

	if (pDataType != NULL)
	{
		if (pDataType->GetCount()<=0)
		{
			vFiberMax = 0;
		}
		else
		{
			vFiberMax =  pDataType->GetCount() - 1;
		}
	}

	unsigned long long vAppIDMin, vAppIDMax;
	vAppIDMin = 0;
	vAppIDMax = 0x0FFFF;
	unsigned long long  vMacMin, vMacMax;
	vMacMin = 0;
	vMacMax = 0x0FFFFFFFFFFFF;

	unsigned long long  vValue;

	m_pIecCfgDatasBase->AutoSetCfgDataValue(pCfgData, CFGDATAID_FIBER, vValue, nOffset, &vFiberMin, &vFiberMax);
	m_pIecCfgDatasBase->AutoSetCfgDataValue(pCfgData, CFGDATAID_APPID, vValue, nOffset, &vAppIDMin, &vAppIDMax);
	m_pIecCfgDatasBase->AutoSetCfgDataValue(pCfgData, CFGDATAID_SRCMAC, vValue, nOffset, &vMacMin, &vMacMax);
	m_pIecCfgDatasBase->AutoSetCfgDataValue(pCfgData, CFGDATAID_DESTMAC, vValue, nOffset, &vMacMin, &vMacMax);
}

