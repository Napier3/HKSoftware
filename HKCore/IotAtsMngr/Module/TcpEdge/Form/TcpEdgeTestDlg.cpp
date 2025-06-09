#include "TcpEdgeTestDlg.h"
#include "ui_TcpEdgeTestDlg.h"
#include "TcpEdgeUIGlobalDef.h"
#include "TcpEdgeInformationDlg.h"
#include "Test/TcpEdgeTestDataView_TimeSyncReq.h"
#include "Test/TcpEdgeTestDataView_DataSubs.h"
#include "Test/TcpEdgeTestDataView_DeviceUpdateReq.h"
#include "Test/TcpEdgeTestDataView_DeviceCtrlReq.h"
#include "Test/TcpEdgeTestDataView_DeviceConfigReq.h"
#include "Test/TcpEdgeTestDataView_ConInstallReq.h"
#include "Test/TcpEdgeTestDataView_ConCommonReq.h"
#include "Test/TcpEdgeTestDataView_AppInstallReq.h"
#include "Test/TcpEdgeTestDataView_AppCommonReq.h"
#include "Test/TcpEdgeTestDataView_AppSetConfigReq.h"
#include "Test/TcpEdgeTestDataView_AppSetCfgFileReq.h"
#include "Test/TcpEdgeTestDataView_FileGet.h"
#include "Test/TcpEdgeTestDataView_ModelDevRead.h"
#include "Test/TcpEdgeTestDataView_GetDataSubs.h"
#include "Test/TcpEdgeTestDataView_DataRead.h"
#include "Test/TcpEdgeTestDataView_ParaRead.h"
#include "Test/TcpEdgeTestDataView_GetMessage.h"
#include "Test/TcpEdgeTestDataView_CtrlCmd.h"
#include "Test/TcpEdgeTestDataView_ParaCommon.h"
#include "Test/TcpEdgeTestDataView_GetHisCommon.h"
#include "Test/TcpEdgeTestDataView_StatusReq.h"
#include "../TcpEdgeGlobalDef.h"

CTcpEdgeTestDlg::CTcpEdgeTestDlg(QWidget *parent) :
	CTcpEdgeFormUI(parent),
	ui(new Ui::CTcpEdgeTestDlg)
{
	ui->setupUi(this);
	m_viewData = NULL;
	m_viewHeader = NULL;
	m_pProducePkg = NULL;
	m_pDevice = NULL;
	InitUI();
	InitFormUI(this, ui->title);
}

CTcpEdgeTestDlg::~CTcpEdgeTestDlg()
{
	if(m_viewData)
	{
		delete m_viewData;
		m_viewData = NULL;
	}

	if(m_viewHeader)
	{
		delete m_viewHeader;
		m_viewHeader = NULL;
	}

	delete ui;
}

void CTcpEdgeTestDlg::InitUI()
{
	QGridLayout* layout = (QGridLayout*)ui->_Head_->layout();
	m_viewHeader = new CTcpEdgeTestHeaderView;
	layout->addWidget(m_viewHeader);	
	connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(slot_ok(bool)));
	connect(ui->_Data_, SIGNAL(clicked(bool)), this, SLOT(slot_clicked(bool)));
	connect(ui->_Head_, SIGNAL(clicked(bool)), this, SLOT(slot_clicked(bool)));

	QString strConfigFile = _P_GetConfigPath();
	strConfigFile += "TcpEdgeServerCfg.errxml";

	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	m_oErrCfg.OpenXmlFile(strConfigFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
}

void CTcpEdgeTestDlg::AttachDevice(CTcpEdgeDevice* pDevice)
{
	m_pDevice = pDevice;
}

void CTcpEdgeTestDlg::InitViewData(const QString& strFunName)
{
	if(strFunName == PkgData_FileGet
		|| strFunName == "FileModelGet"
		|| strFunName == "FileTopoGet"
		|| strFunName == "FileMessageGet")
	{
		m_viewData = new CTcpEdgeTestDataView_FileGet;
	}
	else if(strFunName == PkgData_TimeSyncReq)
	{
		m_viewData = new CTcpEdgeTestDataView_TimeSyncReq;
	}
	else if(strFunName == PkgData_DeviceUpdateReq)
	{
		m_viewData = new CTcpEdgeTestDataView_DeviceUpdateReq;
	}
	else if(strFunName == PkgData_DeviceUpdateStatusReq
		|| strFunName == PkgData_AppInstallStatusReq)
	{
		m_viewData = new CTcpEdgeTestDataView_StatusReq;
	}
	else if(strFunName == PkgData_DeviceCtrlReq)
	{
		m_viewData = new CTcpEdgeTestDataView_DeviceCtrlReq;
	}
	else if(strFunName == PkgData_DeviceConfigReq)
	{
		m_viewData = new CTcpEdgeTestDataView_DeviceConfigReq;
	}
	else if(strFunName == PkgData_ConInstallReq
		|| strFunName == PkgData_ConSetConfigReq)
	{
		m_viewData = new CTcpEdgeTestDataView_ConInstallReq;
	}
	else if(strFunName == PkgData_ConStatusReq
		|| strFunName == PkgData_ConStartReq
		|| strFunName == PkgData_ConStopReq
		|| strFunName == PkgData_ConRestartReq
		|| strFunName == PkgData_ConRemoveReq
		|| strFunName == PkgData_ConGetConfigReq
		|| strFunName == PkgData_ContGetLogReq)
	{
		m_viewData = new CTcpEdgeTestDataView_ConCommonReq;
	}
	else if(strFunName == PkgData_AppInstallReq)
	{
		m_viewData = new CTcpEdgeTestDataView_AppInstallReq;
	}
	else if(strFunName == PkgData_AppStatusReq
		|| strFunName == PkgData_AppStartReq
		|| strFunName == PkgData_AppStopReq
		|| strFunName == PkgData_AppRemoveReq
		|| strFunName == PkgData_AppEnableReq
		|| strFunName == PkgData_AppDisableReq
		|| strFunName == PkgData_AppGetConfigReq
		|| strFunName == PkgData_AppGetCfgFileReq
		|| strFunName == PkgData_AppGetLogReq)
	{
		m_viewData = new CTcpEdgeTestDataView_AppCommonReq;
	}
	else if (strFunName == PkgData_AppSetConfigReq)
	{
		m_viewData = new CTcpEdgeTestDataView_AppSetConfigReq;
	}
	else if (strFunName == PkgData_AppSetCfgFileReq)
	{
		m_viewData = new CTcpEdgeTestDataView_AppSetCfgFileReq;
	}
	else if (strFunName == PkgData_ModelDevRead)
	{
		m_viewData = new CTcpEdgeTestDataView_ModelDevRead;
	}
	else if(strFunName == PkgData_DataSubs)
	{
		m_viewData = new CTcpEdgeTestDataView_DataSubs;
	}
	else if(strFunName == PkgData_GetDataSubs)
	{
		m_viewData = new CTcpEdgeTestDataView_GetDataSubs;
	}
	else if(strFunName == PkgData_DataRead)
	{
		m_viewData = new CTcpEdgeTestDataView_DataRead;
	}
	else if(strFunName == PkgData_ParaRead)
	{
		m_viewData = new CTcpEdgeTestDataView_ParaRead;
	}
	else if(strFunName == PkgData_GetMessage)
	{
		m_viewData = new CTcpEdgeTestDataView_GetMessage;
	}
	else if(strFunName == PkgData_CtrlCmd)
	{
		m_viewData = new CTcpEdgeTestDataView_CtrlCmd;
	}
	else if(strFunName == PkgData_ParaSet
		|| strFunName == PkgData_ParaActivate
		|| strFunName == PkgData_ParaCancel)
	{
		m_viewData = new CTcpEdgeTestDataView_ParaCommon;
	}
	else if(strFunName == PkgData_GetHisData
		|| strFunName == PkgData_GetHisEvent)
	{
		m_viewData = new CTcpEdgeTestDataView_GetHisCommon;
	}
	else
	{
		m_viewData = new CTcpEdgeTestDataView;
	}

	m_viewData->m_strFunName = strFunName;
	m_viewData->m_strRelFunName = strFunName;
	m_viewData->m_pDevice = m_pDevice;
	if(strFunName == "FileModelGet"
		|| strFunName == "FileTopoGet"
		|| strFunName == "FileMessageGet")
	{
		m_pProducePkg = m_oProducer.Produce(PkgData_FileGet);
	}
	else
	{
		m_pProducePkg = m_oProducer.Produce(strFunName);
	}
}

int CTcpEdgeTestDlg::exec(const QString& strTitle, const QString& strFunName)
{
	ui->titleName->setText(strTitle);

	InitViewData(strFunName);

	m_viewHeader->InitUI((CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_Head));
	m_viewData->InitUI((CDvmDataset*)m_pProducePkg->FindByID(PkgData_Node_Data));
	
	if(m_viewData)
	{
		QGridLayout* layout = (QGridLayout*)ui->_Data_->layout();
		layout->addWidget(m_viewData);
		connect(m_viewData, SIGNAL(sig_adjustSize()), this, SLOT(slot_adjustSize()));
	}

	return QDialog::exec();
}

void CTcpEdgeTestDlg::UpdateDatasetNode(CDvmDataset* pDataset, QString& strMessage)
{
	POS pos = pDataset->GetHeadPosition();
	while (pos)
	{
		CExBaseList* pObj = (CExBaseList*)pDataset->GetNext(pos);
		if(pObj->m_dwItemData == 0)
		{
			//节点需要删除
			if(pObj->m_dwReserved == 1)
			{
				//lmy,20230919,删除判断

				//必需项没有被勾选,需要弹出提示
				QString strText = QString("[%1]节点[%2]是必需项\n").arg(pDataset->m_strID).arg(pObj->m_strID);
				strMessage += strText;
			}
		}
		else if(pObj->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			UpdateDatasetNode((CDvmDataset*)pObj, strMessage);
			UpdateDataNode((CDvmDataset*)pObj, strMessage);
		}
		else if (pObj->GetClassID() == DVMCLASSID_CDVMDATASETGROUP)
		{
			UpdateDatasetNode((CDvmDatasetGroup*)pObj, strMessage);
			UpdateDataNode((CDvmDataset*)pObj, strMessage);
		}
	}
}

bool CTcpEdgeTestDlg::UpdateDatasetNode()
{
	QString strMessage;
	UpdateDatasetNode(m_pProducePkg, strMessage);
	if(strMessage.length())
	{
		strMessage = "项目存在以下隐患:\n" + strMessage + "是否继续测试?";
		CTcpEdgeInformationDlg dlg;
		if(dlg.exec(CTcpEdgeInformationDlg::INFO, strMessage) == QDialog::Accepted)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

CDvmDataset* CTcpEdgeTestDlg::GetDataset()
{
	return m_oProducer.GetDataset();
}

CDvmDataset* CTcpEdgeTestDlg::GetDefaultDataset(const QString& strFunName)
{
	InitViewData(strFunName);
	return m_oProducer.GetDataset();
}

void CTcpEdgeTestDlg::slot_adjustSize()
{
	m_viewData->adjustSize();
	m_viewHeader->adjustSize();
	adjustSize();
}

void CTcpEdgeTestDlg::slot_ok(bool bChecked)
{
	UIGetDataset(m_viewHeader, m_viewHeader->m_pProducePkg);
	m_viewData->OnOK();
	if(UpdateDatasetNode())
	{
		accept();
	}
}

void CTcpEdgeTestDlg::slot_clicked(bool bChecked)
{
	QWidget* pWidget = (QWidget*)sender();
	QList<QCheckBox*>list = pWidget->findChildren<QCheckBox*>();
	for (int i = 0; i < list.size(); i++)
	{
		QString strObjName = list[i]->objectName();
		if(strObjName.indexOf("__") == 0)
		{
			list[i]->setChecked(bChecked);
		}
	}

	QString strName = pWidget->objectName();
	long nStart = strName.indexOf("_") + 1;
	long nEnd = strName.lastIndexOf("_");
	QString strTempName = strName.mid(nStart, nEnd - nStart);
	CDvmDataset* pDataset = (CDvmDataset*)m_pProducePkg->FindByID(strTempName);
	pDataset->m_dwItemData = bChecked == true;
}
//lmy,20230910添加判断下发命令参数格式容错判断------Head部分
void CTcpEdgeTestDlg::UpdateDatasetNode_FmtHead(CDvmData* pData, QString& strMessage, QString& strRootNodeID)
{
	if(pData->m_strID == PkgData_Node_FunName)
	{
		CDvmDatasetGroup* pGroupFunc = (CDvmDatasetGroup*)m_oErrCfg.FindByID(PkgData_Node_FunName);
		if(pGroupFunc != NULL)
		{
			CDvmDataset* pGroupMngr = (CDvmDataset*)pGroupFunc->FindByID(pData->m_strValue);
			if(pGroupMngr == NULL)
			{
				QString strText = QString("Head节点的[%1]节点超出输入范围\n").arg(PkgData_Node_FunName);
				strMessage += strText;
			}
		}
	}
	else if(pData->m_strID == PkgData_Node_Cot)
	{
		//if(pData->m_strValue != "1" && pData->m_strValue != "2" && pData->m_strValue != "3"
		//	&& pData->m_strValue != "4" && pData->m_strValue != "5")
		//{
		//	QString strText = QString("Head节点的[%1]节点超出输入范围\n").arg(PkgData_Node_Cot);
		//	strMessage += strText;
		//}
		QString strTemp = QString(_T("Head"));
		UpdateDatasetNode_FmtDataComBo(pData, strMessage, strTemp);
	}
	else if(pData->m_strID == PkgData_Node_Mid)
	{
		JudgeNumAndRange(pData, strMessage, 0, 4294967295, _T("Head"));
	}
}

//lmy,20230910添加判断下发命令参数格式容错判断------判断字符串是否为数字,并且是否在范围内
void CTcpEdgeTestDlg::JudgeNumAndRange(CDvmData* pData, QString &strMessage, double dLevel, double dUp, CString strRootNodeId)
{
	QString strTemp = QString("%1").arg(pData->m_strValue);
	bool ok = false;
	double val = strTemp.toDouble(&ok);
	if(dUp != 0)
	{
		if((!ok) || (!((val>=dLevel && val<= dUp))))
		{
			QString strText = QString("[%1]节点的[%2]节点超出输入范围\n").arg(strRootNodeId).arg(pData->m_strID);
			strMessage += strText;
		}
	}
	else
	{
		if((!ok) || (!(val>=dLevel)))
		{
			QString strText = QString("[%1]节点的[%2]节点超出输入范围\n").arg(strRootNodeId).arg(pData->m_strID);
			strMessage += strText;
		}
	}

}

//lmy,20230910添加判断下发命令参数格式容错判断------Data部分
void CTcpEdgeTestDlg::UpdateDatasetNode_FmtData(CDvmData* pData, QString& strMessage, QString& strRootNodeID)
{
	if(UpdateDatasetNode_FmtDataComBo(pData, strMessage, strRootNodeID))
	{
		return;
	}
	else if(UpdateDatasetNode_FmtDataNumType(pData, strMessage, strRootNodeID))
	{
		return;
	}
	else
	{
		UpdateDatasetNode_FmtDataOther(pData, strMessage, strRootNodeID);
	}

}


//lmy,20230910添加判断下发命令参数格式容错判断------Data部分
BOOL CTcpEdgeTestDlg::UpdateDatasetNode_FmtDataComBo(CDvmData* pData, QString& strMessage, QString& strRootNodeID)
{
	CString strConfigFile = _P_GetConfigPath();
	strConfigFile += "TcpEdgeServerCfg.uixml";
	CDvmDatasetGroup cfg;
	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	cfg.OpenXmlFile(strConfigFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	QString strTemp = QString("_%1_").arg(pData->m_strID);
	CDvmData* pTempData = (CDvmData*)cfg.FindByID(strTemp);
	if(pTempData)
	{
		QString strObjClassName = pTempData->m_strName;
		if(strObjClassName == "QComboBox")
		{
			POS pos = pTempData->GetHeadPosition();
			while (pos)
			{
				CDvmValue* pValue = (CDvmValue*)pTempData->GetNext(pos);
				if(pData->m_strValue == pValue->m_strID)
				{
					return TRUE;
				}
			}
			if(pData->m_strID == PkgData_Node_ServiceId)
			{
				if(pData->m_strValue == "parameter")
				{
					return TRUE;
				}
			}
			QString strText = QString("[%1]节点的[%2]节点超出输入范围\n").arg(strRootNodeID).arg(pData->m_strID);
			strMessage += strText;
			return TRUE;
		}
	}

	return FALSE;
}

//不能为中文的参数
void CTcpEdgeTestDlg::UpdateDatasetNode_FmtDataOther(CDvmData* pData, QString& strMessage, QString& strRootNodeID)
{
	CDvmDatasetGroup* pGroupFunc = (CDvmDatasetGroup*)m_oErrCfg.FindByID("HasChinese");
	CDvmData* pNumData = (CDvmData*)pGroupFunc->FindByID(pData->m_strID);

	if(pNumData)
	{
		//lmy,20230919修改		
		if(HasChineseChar(pData->m_strValue))
		{
			QString strText = QString("[%1]节点的[%2]节点超出输入范围\n").arg(strRootNodeID).arg(pData->m_strID);
			strMessage += strText;
		}
	}
}

//lmy,20230914添加, 判断字符串是否含有中文
BOOL CTcpEdgeTestDlg::HasChineseChar(CString strData)
{
	int nLen = strData.GetLength();
	char ch1;

	for(int i = 0; i != nLen; ++i)
	{
		ch1 = strData[i];
		//lmy,20230919修改
		if ((ch1 >= 'a' && ch1 <= 'z') || (ch1 >= 'A' && ch1 <= 'Z') || (ch1 >= '0' && ch1 <= '9') || ch1 == '.' || ch1 == '-')
		{
			continue;
		}
		else
		{
			return TRUE;
		}
	} 

	return FALSE;
}

//lmy,20230913,添加对数字类型进行处理
BOOL CTcpEdgeTestDlg::UpdateDatasetNode_FmtDataNumType(CDvmData* pData, QString& strMessage, QString& strRootNodeID)
{
	CDvmDatasetGroup* pGroupFunc = (CDvmDatasetGroup*)m_oErrCfg.FindByID("NumType");
	CDvmData* pNumData = (CDvmData*)pGroupFunc->FindByID(pData->m_strID);

	if(pNumData)
	{
		QString strTemp = QString("%1").arg(pNumData->m_strMax);
		bool ok = false;
		double dUp = strTemp.toDouble(&ok);
		strTemp = QString("%1").arg(pNumData->m_strMin);
		double dLevel = strTemp.toDouble(&ok);
		JudgeNumAndRange(pData, strMessage, dLevel, dUp, strRootNodeID);
	    return TRUE;
	}

	return FALSE;
}

//lmy,20230914添加,用于判断单个节点的容错测试
void CTcpEdgeTestDlg::UpdateDataNode(CDvmDataset* pObj, QString& strMessage)
{
	if(pObj->m_strID == PkgData_Node_Head)
	{
		POS pos = pObj->GetHeadPosition();
		while(pos)
		{
			CDvmData *pData = (CDvmData*)pObj->GetNext(pos);
			if(pos != NULL)
			{
				UpdateDatasetNode_FmtHead((CDvmData*)pData, strMessage, pObj->m_strID);
			}
		}
	}
	else
	{
		POS pos = pObj->GetHeadPosition();
		CDvmData *pData = NULL;

		if(UpdateDataset_StringArray(pObj, strMessage))
		{
			return;
		}
		else
		{
			while(pos)
			{
				pData = (CDvmData*)pObj->GetNext(pos);
				if(pData != NULL)
				{
					if(pData->GetClassID() == DVMCLASSID_CDVMDATA)
					{
						if(pData->m_strValue == "")
						{
							//lmy,20230920修改
							//if(pData->m_dwItemData == 0)
							if(pData->m_dwReserved == 1 && pData->m_dwItemData == 1)
							{
								QString strText = QString("[%1]节点的[%2]节点(必需项)未检测到参数值\n").arg(pObj->m_strID).arg(pData->m_strID);
								strMessage += strText;
								continue;
							}
							else
							{
								continue;
							}
						}
					}
					else if(pData->GetClassID() == DVMCLASSID_CDVMDATASET && pData->m_strID == PkgData_Node_Data)
					{
						if(pData->m_strName != "Dataset" && pData->m_strID != "dataset")
						{
							UpdateDataNode((CDvmDataset *)pData, strMessage);
						}
					}

					UpdateDatasetNode_FmtData((CDvmData*)pData, strMessage, pObj->m_strID);
				}
			}
		}
	}
}

//lmy,20230914添加,用于对字符串数组进行容错测试
BOOL CTcpEdgeTestDlg::UpdateDataset_StringArray(CDvmDataset* pObj, QString& strMessage)
{
	CDvmDatasetGroup* pGroupFunc = (CDvmDatasetGroup*)m_oErrCfg.FindByID("StringArray");
	CDvmData* pNumData = (CDvmData*)pGroupFunc->FindByID(pObj->m_strID);
	BOOL bJudge = FALSE;

	if(pNumData)// && pObj->GetClassID() == DVMCLASSID_CDVMDATASETGROUP)
	{
		bJudge = UpdateData_StringArray(pObj, strMessage, pObj->m_dwItemData, pObj->m_strID);
	}

	return bJudge;
}

//lmy,20230914添加,用于对字符串数组进行容错测试
BOOL CTcpEdgeTestDlg::UpdateData_StringArray(CDvmDataset* pObj, QString& strMessage, DWORD dwItemData, CString strRootNodeID)
{
	POS pos = pObj->GetHeadPosition();
	CDvmData *pData = NULL;
	BOOL bJudge = FALSE;
	while(pos)
	{
		pData = (CDvmData *)pObj->GetNext(pos);
		if((pData->m_strName == "Dataset" && pData->m_strID == "dataset") || (pData->m_strName == "" && pData->m_strID == ""))
		{
			if(pData->GetClassID() == DVMCLASSID_CDVMDATASET)
			{
				UpdateData_StringArray((CDvmDataset *)pData, strMessage, pObj->m_dwItemData, pObj->m_strID);
			}
			else if(pData->GetClassID() == DVMCLASSID_CDVMDATA)
			{
				//lmy,20230920修改
				//if(pData->m_strValue == "" && dwItemData)
				if(pData->m_strValue == "" && dwItemData == 1 && pData->m_dwReserved == 1)
				{
					QString strText = QString("[Data]节点的[%2]节点(必需项)未检测到参数值\n").arg(strRootNodeID);
					strMessage += strText;
				}
				else
				{
					if(HasChineseChar(pData->m_strValue))
					{
						QString strText = QString("[Data]节点的[%2]节点中包含中文内容\n").arg(strRootNodeID);
						strMessage += strText;
					}
				}
				bJudge = TRUE;
			}
		}
	}
	return bJudge;
}
