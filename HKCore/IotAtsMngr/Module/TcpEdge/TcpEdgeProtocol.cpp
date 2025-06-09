#include "stdafx.h"
#include "TcpEdgeProtocol.h"
#include "TcpEdgeDevice.h"
#include "TcpEdgePrcdr_Auth.h"
#include "TcpEdgePrcdr_Read.h"
#include "TcpEdgePrcdr_File.h"
#include "TcpEdgePrcdr_Write.h"
#include "Pkg/TcpEdgePkg.h"
#include "Pkg/TcpEdgePkgData_DataSpontResp.h"
#include "Pkg/Pkg_DataSpontRespDevs.h"
#include "Pkg/Pkg_DataSpontRespDev.h"
#include "Pkg/Pkg_DataSpontDev.h"
#include "Pkg/Pkg_DataSpontDevs.h"
#include "Pkg/Pkg_ModelChange_Mods.h"
#include "Pkg/Pkg_ModelChangeResp_Mods.h"
#include "Pkg/TcpEdgePkgData_ModelChangeResp.h"
#include "Pkg/Pkg_ModelChange_Mod.h"
#include "Pkg/Pkg_ModelChangeResp_Mod.h"
#include "Pkg/Pkg_DevAdd_Dev.h"
#include "Pkg/TcpEdgePkgData_DevAddResp.h"
#include "Pkg/Pkg_DevAddResp_Devs.h"
#include "Pkg/Pkg_DevAddResp_Dev.h"
#include "Pkg/Pkg_DevAdd_Devs.h"
#include "Pkg/TcpEdgePkgData_DevUpdateResp.h"
#include "Pkg/Pkg_DevUpdate_Devs.h"
#include "Pkg/Pkg_DevUpdateResp_Devs.h"
#include "Pkg/Pkg_DevUpdate_Dev.h"
#include "Pkg/Pkg_DevUpdateResp_Dev.h"
#include "Pkg/TcpEdgePkgData_Health.h"
#include "Pkg/TcpEdgePkgData_GetModelResp.h"
#include "Pkg/Pkg_GetModelResp_Models.h"
#include "Pkg/Pkg_GetModelResp_Model.h"
#include "Pkg/TcpEdgePkgData_GetTopoFileResp.h"
#include "Pkg/Pkg_GetTopFileResp_Files.h"
#include "Pkg/Pkg_GetTopFileResp_File.h"
#include "Pkg/TcpEdgePkgData_GetMessageResp.h"
#include "Pkg/Pkg_GetMessageResp_Files.h"
#include "Pkg/Pkg_GetMessageResp_File.h"
#include "../ProtocolBase/PxPkgBase.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include <QDir>

CTcpEdgeProtocol::CTcpEdgeProtocol()
{
	m_bExitEngineThread = false;
	m_nMngrPort = 0;
	m_nDataPort = 0;
	m_nMngrHealthRespCount = 0;
	m_nMngrHealthTime = 60;
	m_nDataHealthRespCount = 0;
	m_nDataHealthTime = 60;
	m_pThread = NULL;
}

CTcpEdgeProtocol::~CTcpEdgeProtocol()
{
	if(m_pThread)
	{
		ExitEngineThread();
	}
}

void CTcpEdgeProtocol::AttachDevice(CTcpEdgeDevice* pDevice)
{
	m_pDevice = pDevice;
	m_oModelParser.m_pDevice = pDevice;
}

void CTcpEdgeProtocol::AttachPort(long nMngrPort, long nDataPort)
{
	m_nMngrPort = nMngrPort;
	m_nDataPort = nDataPort;
}

long CTcpEdgeProtocol::OnTestMsg(long nPort, QByteArray bytes)
{
	char* pBuf = bytes.data() + 32;

	CString strAutoDataset, strAutoDatasetID;
	CDvmDataset* pAutoDataset = NULL;

	char strID[32] = {0};
	memcpy(strID, bytes.data() + 8, 23);

	CTcpEdgePkg* pData = NULL;
	if(pBuf[0] == 0x01)
	{
		char strName[64] = {0};
		memcpy(strName, pBuf + 1, 64);
		m_pDevice->m_strDeviceName = strName;
		m_pDevice->m_strDeviceID = strID;
		memcpy(m_pDevice->m_byteRecvR1, pBuf + 65, 8);
		pData = new CTcpEdgePkg;
		pData->m_strCmdID = "0x01";
		pData->m_strName = strID;

		if(!m_pDevice->m_strLogFile.length())
		{
			//创建设备日志文件
			CString strFile = _P_GetWorkspacePath();
			strFile += m_pDevice->m_strSetupTime;
			strFile += "/";
			strFile += m_pDevice->m_strDeviceName;
			
			QDateTime date = QDateTime::currentDateTime();
			QString strFullLogFile = QString("%1_pkg_%2.txt").arg(strFile).arg(date.toString("hh_mm_ss_z"));
			QString strFullRptFile = QString("%1_rpt_%2.docx").arg(strFile).arg(date.toString("hh_mm_ss_z"));

			m_pDevice->m_strLogFile = strFullLogFile;
			m_pDevice->m_strRptFile = strFullRptFile;
			m_pDevice->m_strRecvFilePath += m_pDevice->m_strDeviceName;
			m_pDevice->m_strRecvFilePath += "\\";
		}
	}
	else if(pBuf[0] == 0x03)
	{
		memcpy(m_pDevice->m_byteRecvR2, pBuf + 1, 8);
		pData = new CTcpEdgePkg;
		pData->m_strCmdID = "0x03";
	}
	else
	{
		//处理正常报文
		pData = m_oParser.Parser(strID, pBuf);
		pData->m_strCmdID = pData->m_pPkgHead->m_strFunName;

		if(pData->m_strCmdID == PkgData_DataSpont)
		{
			pAutoDataset = OnDataSpontReq(pData, strAutoDatasetID, strAutoDataset);
			m_oModelParser.ParsePkg((CTcpEdgePkgData_DataSpont*)pData->m_pPkgData);
 			if(m_oModelParser.m_strErrorInfo.length())
 			{
 				pData->m_pPkgData->m_strErrorInfo = m_oModelParser.m_strErrorInfo + pData->m_pPkgData->m_strErrorInfo;
 			}
		}
		else if (pData->m_strCmdID == PkgData_ModelChange)
		{
			pAutoDataset = OnModelChange(pData, strAutoDatasetID, strAutoDataset);
		}
		else if (pData->m_strCmdID == PkgData_DevAdd)
		{
			pAutoDataset = OnDevAddReq(pData, strAutoDatasetID, strAutoDataset);
		}
		else if (pData->m_strCmdID == PkgData_DevUpdate)
		{
			pAutoDataset = OnDevUpdate(pData, strAutoDatasetID, strAutoDataset);
		}
		else if (pData->m_strCmdID == PkgData_HealthReq)
		{
			pAutoDataset = OnHealthReq(pData, strAutoDatasetID, strAutoDataset);
		}
		else if(pData->m_strCmdID == PkgData_HealthResp)
		{
			//特殊处理心跳回复接收
			if(nPort == m_nMngrPort)
			{
				m_nMngrHealthRespCount = 0;
				m_nMngrHealthTime = 60;
			}
			else
			{
				m_nDataHealthRespCount = 0;
				m_nDataHealthTime = 60;
			}

			strAutoDataset = pBuf;
			pData->m_nPort = nPort;
			pAutoDataset = OnHealthResp(pData, strAutoDatasetID, strAutoDataset);
		}
	}

	//更新数据集
	if(pData)
	{
		pData->m_nPort = nPort;
		//lmy,20230915添加判断,鉴权认证数据集中增加协议头的显示，0x02显示了报文协议头
		if(pBuf[0] == 0x01 || pBuf[0] == 0x03)
		{
			UpdateDataset(pData, bytes.data());
		}
		else
		{
			UpdateDataset(pData, pBuf);
		}
	}

	//自动回复需要在更新完上报报文后再更新至数据集
	if(pAutoDataset)
	{
		CDvmValue* pValue = UpdateDataset(pAutoDataset, strAutoDatasetID, strAutoDataset);
		pValue->m_dwReserved = pData->m_nPort;
		if(m_pDevice->m_pWordTool)
		{
			m_pDevice->m_pWordTool->FillTestReport(pAutoDataset);
		}
	}

	if(pData)
	{
		QMutexLocker lock(&m_oRecvPkgLocker);
		m_listRecvPkg.AddNewChild(pData);
	}

	return 0;
}


CTcpEdgePrcdrBase* CTcpEdgeProtocol::CreateProcedure(QString& strPrcdrID)
{
	CTcpEdgePrcdrBase *pProcedure = NULL;

	//此处需要找到一个地方安置上报报文id -> Mid
	//根据过程ID创建不同的过程对象
	if(strPrcdrID == PkgData_Auth)
	{
		pProcedure = new CTcpEdgePrcdr_Auth();
	}
	else if(strPrcdrID == PkgData_TimeSyncReq 
		|| strPrcdrID == PkgData_ConInstallReq 
		|| strPrcdrID == PkgData_ConRemoveReq 
		|| strPrcdrID == PkgData_ConRestartReq
		|| strPrcdrID == PkgData_ConSetConfigReq
		|| strPrcdrID == PkgData_ConStatusReq 
		|| strPrcdrID == PkgData_ConStartReq
		|| strPrcdrID == PkgData_ConGetConfigReq 
		|| strPrcdrID == PkgData_ConStopReq
		|| strPrcdrID == PkgData_ModelChange 
		|| strPrcdrID == PkgData_DevAdd 
		|| strPrcdrID == PkgData_DevUpdate 
		|| strPrcdrID == PkgData_ModelDevRead
		|| strPrcdrID == PkgData_DataSubs 
		|| strPrcdrID == PkgData_GetDataSubs
		|| strPrcdrID == PkgData_DataSpont 
		|| strPrcdrID == PkgData_DataRead
		|| strPrcdrID == PkgData_ParaRead
		|| strPrcdrID == PkgData_DeviceCtrlReq        //设备控制
		|| strPrcdrID == PkgData_DeviceConfigReq        //设备配置参数修改
		|| strPrcdrID == PkgData_ParaCancel			//撤销参数定值预置
		|| strPrcdrID == PkgData_ParaActivate		//参数、定值激活
		|| strPrcdrID == PkgData_AppSetConfigReq		//应用配置修改
		|| strPrcdrID == PkgData_AppGetConfigReq		//应用配置查询
		|| strPrcdrID == PkgData_AppDisableReq		//应用去使能
		|| strPrcdrID == PkgData_AppEnableReq			//应用使能	
		|| strPrcdrID == PkgData_AppRemoveReq		//应用卸载
		|| strPrcdrID == PkgData_AppStopReq			//应用停止
		|| strPrcdrID == PkgData_AppStartReq			//应用启动
		|| strPrcdrID == PkgData_AppStatusReq		//应用状态查询
		|| strPrcdrID == PkgData_GetHisData			//历史数据查询
		|| strPrcdrID == PkgData_CtrlCmd				//遥控、遥调报文定义
		|| strPrcdrID == PkgData_ParaSet
		|| strPrcdrID == PkgData_GetHisEvent        //历史操作记录查询
		|| strPrcdrID == PkgData_GetMessage
		) 
	{
		pProcedure = new CTcpEdgePrcdr_Write();
	}
	else if(strPrcdrID == PkgData_TimeReadReq 
		|| strPrcdrID == PkgData_DeviceInfoReq 
		|| strPrcdrID == PkgData_DeviceStatusReq
		|| strPrcdrID == PkgData_GetModel 
		|| strPrcdrID == PkgData_GetTopoFile)
	{
		pProcedure = new CTcpEdgePrcdr_Read();
	}
	else if (strPrcdrID == PkgData_DeviceGetLogReq
		|| strPrcdrID == PkgData_ContGetLogReq
		|| strPrcdrID == PkgData_AppGetLogReq
		|| strPrcdrID == PkgData_FileGet
		|| strPrcdrID == PkgData_FileSend
		|| strPrcdrID == PkgData_AppGetCfgFileReq
		|| strPrcdrID == PkgData_AppSetCfgFileReq
		|| strPrcdrID == PkgData_DeviceUpdateReq      //设备升级
		|| strPrcdrID == PkgData_DeviceUpdateStatusReq
		|| strPrcdrID == PkgData_AppInstallReq		//应用安装
		|| strPrcdrID == PkgData_AppInstallStatusReq
		)
	{
		pProcedure = new CTcpEdgePrcdr_File();
	}
	else if(strPrcdrID == "FileModelGet"
		|| strPrcdrID == "FileTopoGet"
		|| strPrcdrID == "FileMessageGet")
	{
		pProcedure = new CTcpEdgePrcdr_File();
		((CTcpEdgePrcdr_File*)pProcedure)->SetFileGetType(strPrcdrID);
		strPrcdrID = PkgData_FileGet;
	}

	if(pProcedure)
	{
		pProcedure->m_strIP = m_pDevice->m_strID;
		connect(pProcedure, SIGNAL(sig_updateViewPkg(QString,QString,long)), this, SLOT(slot_updateViewPkg(QString,QString,long)));
	}
	
	return pProcedure;
}

CTcpEdgePrcdrBase* CTcpEdgeProtocol::CreateUserProcedure(QString& strPrcdrID)
{
	CTcpEdgePrcdrBase *pProcedure = NULL;

	//此处需要找到一个地方安置上报报文id -> Mid
	//根据过程ID创建不同的过程对象
	if(strPrcdrID == PkgData_Auth)
	{
		pProcedure = new CTcpEdgePrcdr_Auth();
	}
	else if(strPrcdrID == PkgData_TimeSyncReq 
		|| strPrcdrID == PkgData_ConInstallReq 
		|| strPrcdrID == PkgData_ConRemoveReq 
		|| strPrcdrID == PkgData_ConRestartReq
		|| strPrcdrID == PkgData_ConSetConfigReq
		|| strPrcdrID == PkgData_ConStatusReq 
		|| strPrcdrID == PkgData_ConStartReq
		|| strPrcdrID == PkgData_ConGetConfigReq 
		|| strPrcdrID == PkgData_ConStopReq
		|| strPrcdrID == PkgData_ModelChange 
		|| strPrcdrID == PkgData_DevAdd 
		|| strPrcdrID == PkgData_DevUpdate 
		|| strPrcdrID == PkgData_ModelDevRead
		|| strPrcdrID == PkgData_DataSubs 
		|| strPrcdrID == PkgData_GetDataSubs
		|| strPrcdrID == PkgData_DataSpont 
		|| strPrcdrID == PkgData_DataRead
		|| strPrcdrID == PkgData_ParaRead
		|| strPrcdrID == PkgData_DeviceCtrlReq        //设备控制
		|| strPrcdrID == PkgData_DeviceConfigReq        //设备配置参数修改
		|| strPrcdrID == PkgData_ParaCancel			//撤销参数定值预置
		|| strPrcdrID == PkgData_ParaActivate		//参数、定值激活
		|| strPrcdrID == PkgData_AppSetConfigReq		//应用配置修改
		|| strPrcdrID == PkgData_AppGetConfigReq		//应用配置查询
		|| strPrcdrID == PkgData_AppDisableReq		//应用去使能
		|| strPrcdrID == PkgData_AppEnableReq			//应用使能	
		|| strPrcdrID == PkgData_AppRemoveReq		//应用卸载
		|| strPrcdrID == PkgData_AppStopReq			//应用停止
		|| strPrcdrID == PkgData_AppStartReq			//应用启动
		|| strPrcdrID == PkgData_AppStatusReq		//应用状态查询
		|| strPrcdrID == PkgData_GetHisData			//历史数据查询
		|| strPrcdrID == PkgData_CtrlCmd				//遥控、遥调报文定义
		|| strPrcdrID == PkgData_ParaSet
		|| strPrcdrID == PkgData_GetHisEvent        //历史操作记录查询
		|| strPrcdrID == PkgData_GetMessage
		) 
	{
		pProcedure = new CTcpEdgePrcdr_Write();
	}
	else if(strPrcdrID == PkgData_TimeReadReq 
		|| strPrcdrID == PkgData_DeviceInfoReq 
		|| strPrcdrID == PkgData_DeviceStatusReq
		|| strPrcdrID == PkgData_GetModel 
		|| strPrcdrID == PkgData_GetTopoFile)
	{
		pProcedure = new CTcpEdgePrcdr_Read();
	}
	else if (strPrcdrID == PkgData_DeviceGetLogReq
		|| strPrcdrID == PkgData_ContGetLogReq
		|| strPrcdrID == PkgData_AppGetLogReq
		|| strPrcdrID == PkgData_FileGet
		|| strPrcdrID == PkgData_FileSend
		|| strPrcdrID == PkgData_AppGetCfgFileReq
		|| strPrcdrID == PkgData_AppSetCfgFileReq
		|| strPrcdrID == PkgData_DeviceUpdateReq      //设备升级
		|| strPrcdrID == PkgData_DeviceUpdateStatusReq
		|| strPrcdrID == PkgData_AppInstallReq		//应用安装
		|| strPrcdrID == PkgData_AppInstallStatusReq
		)
	{
		pProcedure = new CTcpEdgePrcdr_File();
	}
	else if(strPrcdrID == "FileModelGet"
		|| strPrcdrID == "FileTopoGet"
		|| strPrcdrID == "FileMessageGet")
	{
		pProcedure = new CTcpEdgePrcdr_File();
		((CTcpEdgePrcdr_File*)pProcedure)->SetFileGetType(strPrcdrID);
		strPrcdrID = PkgData_FileGet;
	}

	return pProcedure;
}

CDvmValue* CTcpEdgeProtocol::UpdateDataset(CDvmDataset* pDataset, const CString &strID, QString strPkgData)
{
	if(pDataset)
	{
		CDvmData* pData = (CDvmData*)pDataset->FindByID(strID);
		if(pData)
		{
			CJSON* pJson = CJSON_Parse(strPkgData.toStdString().c_str());
			CString strPkg = CJSON_Print(pJson);
			if(pJson)
			{
				CJSON_Delete(pJson);

				if(strID == "0x01" || strID == "0x02" || strID == "0x03")
				{
					strPkg = strPkgData;
				}
			}
			else
			{
				strPkg = strPkgData;
			}

			pData->m_strValue = strPkg;
			CDvmValue* pValue = new CDvmValue;
			pValue->m_strID = QString("%1").arg(pDataset->m_nIndex++);
			QDateTime dateTime = QDateTime::currentDateTime();
			pValue->m_strName = dateTime.toString("yyyy-MM-dd hh:mm:ss.z");
			pValue->m_strValue = strPkg;
			pData->AddNewChild(pValue);
			return pValue;
		}
	}
	return 0;
}

void CTcpEdgeProtocol::UpdateDataset(CTcpEdgePkg* pData, char *pBuf)
{
	CDvmLogicDevice* pIOT = (CDvmLogicDevice*)m_pDvmDevice->GetHead();
	CString strPrcdrID;
	if(pData->m_strCmdID == "0x01"
		|| pData->m_strCmdID == "0x03")
	{
		strPrcdrID = PkgData_Auth;
		CDvmDataset* pDataset = (CDvmDataset*)pIOT->FindByID(strPrcdrID);
		if(pDataset)
		{
			//lmy,20230915修改,鉴权认证数据集中增加协议头的显示，0x02显示了报文协议头
			CString strPkg;
			long nLen = 169;//137;
			if(pData->m_strCmdID == "0x03")
			{
				nLen = 105;//73;
			}
			for (int i = 0; i < nLen; i++)
			{
				QString strTemp = QString("0x%1 ").arg(pBuf[i] & 0xff, 2, 16, QLatin1Char('0'));
				strTemp = strTemp.toUpper();
				strPkg += strTemp;
			}
			CDvmValue* pValue = UpdateDataset(pDataset, pData->m_strCmdID, strPkg);
			pValue->m_dwItemData = 1;
			pValue->m_dwReserved = pData->m_nPort;
		}
	}
	else
	{
		if(pData->m_pPkgData)
		{
			strPrcdrID = pData->GetPrcdrIDByPkgData(pData->m_pPkgData);

			//更新错误原因
			CDvmDataset* pDataset = (CDvmDataset*)pIOT->FindByID(PkgData_ErrorInfo);
			CDvmData* pErrData = (CDvmData*)pDataset->FindByID(strPrcdrID);
			pErrData->m_strValue += pData->m_pPkgData->m_strErrorInfo;

			if(pDataset)
			{
				pDataset = (CDvmDataset*)pIOT->FindByID(strPrcdrID);
				//将接收报文记录进数据集前要转ascii
				QString strBuf = QString::fromUtf8(pBuf);
				CDvmValue* pDvmValue = UpdateDataset(pDataset, pData->m_strCmdID, strBuf);
				pDvmValue->m_dwItemData = 1;
				pDvmValue->m_dwReserved = pData->m_nPort;
				pDvmValue->m_strDataType = pData->m_pPkgData->m_strErrorInfo; 

				if(m_pDevice->m_pWordTool)
				{
					m_pDevice->m_pWordTool->FillTestReport(pDataset);
				}
			}
		}
	}
}

CString CTcpEdgeProtocol::OnReqSend(CTcpEdgePkgData* pPkgData, const CString& strPrcdrID, const CString& strMid, long nPort)
{
	//new对象已经在send中析构
	CTcpEdgePkg* pRespPkg = new CTcpEdgePkg;
	pRespPkg->m_pPkgData = pPkgData;

	CTcpEdgePrcdrBase oPrcdr;
	oPrcdr.SetTcpProtocol(this);
	oPrcdr.m_strMid = strMid;
	oPrcdr.m_strDeviceID = m_pDevice->m_strDeviceID;

	if(strPrcdrID == PkgData_HealthReq)
	{
		oPrcdr.Send(pRespPkg, strPrcdrID, PkgData_Value_CotReq, nPort);
	}
	else
	{
		oPrcdr.Send(pRespPkg, strPrcdrID, PkgData_Value_CotConfirm, nPort);
	}
	
	return oPrcdr.m_strASDU;
}


void CTcpEdgeProtocol::OnModelFileGet(CString strFileName)
{
	CString strFile = m_pDevice->m_strRecvFilePath;
	QDir dirFile(strFile);
	if (!dirFile.exists())
	{
		dirFile.mkpath(strFile);
	}
	strFile += strFileName;

	m_oModelParser.ParseFile(strFile);
	CModelRecord* pRecord = m_pDevice->m_oRecord.FindModelByFileName(strFileName);
	pRecord->m_datas.DeleteAll();
	m_oModelParser.m_oDataMapping.CopyChildren(&pRecord->m_datas);
	if(m_oModelParser.m_strParseErrorInfo.length())
	{
		emit sig_updatePkg(m_pDevice->m_strID, m_oModelParser.m_strParseErrorInfo, 0);
	}
}

CDvmDataset* CTcpEdgeProtocol::OnDataSpontReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg)
{
	//这里new的对象将在CTcpEdgePkg析构时析构
	CTcpEdgePkgData_DataSpontResp* pResp = new CTcpEdgePkgData_DataSpontResp;
	CPkg_DataSpontRespDevs* pRespDevs = new CPkg_DataSpontRespDevs;
	pRespDevs->m_strID = PkgData_Node_Devices;
	pResp->AddNewChild(pRespDevs);

	CPkg_DataSpontDevs* pDevs = (CPkg_DataSpontDevs*)pData->m_pPkgData->FindByID(PkgData_Node_Devices);
	if(pDevs == NULL)    //避免收到的DataSpont报文出现缺少Devices数组时,会在此中断，添加判断
	{
		return NULL;
	}

	POS pos = pDevs->GetHeadPosition();
	while (pos)
	{
		CPkg_DataSpontDev* pDevs = (CPkg_DataSpontDev*)pData->m_pPkgData->GetNext(pos);
		CPkg_DataSpontRespDev* pRespDev = new CPkg_DataSpontRespDev;
		pRespDev->m_strDeviceId = pDevs->m_strDeviceId;
		pRespDev->m_strStatus = "0";
		pRespDevs->AddNewChild(pRespDev);
	}

	strPkg = OnReqSend(pResp, PkgData_DataSpontResp, pData->m_pPkgHead->m_strMid);
	strID = PkgData_DataSpontResp;
	return (CDvmDataset*)m_pDvmDevice->FindDataset(PkgData_DataSpont);
}

CDvmDataset* CTcpEdgeProtocol::OnModelChange(CTcpEdgePkg* pData, CString& strID, CString& strPkg)
{
	//这里new的对象将在CTcpEdgePkg析构时析构
	CTcpEdgePkgData_ModelChangeResp* pResp = new CTcpEdgePkgData_ModelChangeResp;
	CPkg_ModelChangeResp_Mods* pRespMods = new CPkg_ModelChangeResp_Mods;
	pRespMods->m_strID = PkgData_Node_Models;
	pResp->AddNewChild(pRespMods);

	CPkg_ModelChange_Mods* pMods = (CPkg_ModelChange_Mods*)pData->m_pPkgData->FindByID(PkgData_Node_Models);
	if(pMods == NULL)    //当收到的ModelChange报文出现缺少Modles数组的错误时,会在此中断，添加判断
	{
		return NULL;
	}

	POS pos = pMods->GetHeadPosition();
	while (pos)
	{
		CPkg_ModelChange_Mod* pMod = (CPkg_ModelChange_Mod*)pData->m_pPkgData->GetNext(pos);
		CPkg_ModelChangeResp_Mod* pRespMod = new CPkg_ModelChangeResp_Mod;
		pRespMod->m_strModelName = pMod->m_strModelName;
		pRespMod->m_strStatus = "0";
		pRespMods->AddNewChild(pRespMod);
	}

	strPkg = OnReqSend(pResp, PkgData_ModelChangeResp, pData->m_pPkgHead->m_strMid);
	strID = PkgData_ModelChangeResp;
	return (CDvmDataset*)m_pDvmDevice->FindDataset(PkgData_ModelChange);
}

CDvmDataset* CTcpEdgeProtocol::OnDevAddReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg)
{
	CTcpEdgePkgData_DevAddResp *pResp = new CTcpEdgePkgData_DevAddResp;
	CPkg_DevAddResp_Devs* pRespDevs = new CPkg_DevAddResp_Devs;
	pRespDevs->m_strID = PkgData_Node_Devices;
	pResp->AddNewChild(pRespDevs);
	CPkg_DevAdd_Devs* pDevs = (CPkg_DevAdd_Devs*)pData->m_pPkgData->FindByID(PkgData_Node_Devices);
	if(pDevs == NULL)    //避免收到的报文出现缺少数组时,会在此中断，添加判断
	{
		return NULL;
	}

	POS pos = pDevs->GetHeadPosition();
	{
		CPkg_DevAdd_Dev* pDev = (CPkg_DevAdd_Dev*)pData->m_pPkgData->GetNext(pos);
		CPkg_DevAddResp_Dev* pRespDev = new CPkg_DevAddResp_Dev;
		pRespDev->m_strDeviceId = pDev->m_strDeviceId;
		pRespDev->m_strStatus = "0";
		pRespDevs->AddNewChild(pRespDev);
	}
	strPkg = OnReqSend(pResp, PkgData_DevAddResp, pData->m_pPkgHead->m_strMid);
	strID = PkgData_DevAddResp;
	return (CDvmDataset*)m_pDvmDevice->FindDataset(PkgData_DevAdd);
}

CDvmDataset* CTcpEdgeProtocol::OnDevUpdate(CTcpEdgePkg* pData, CString& strID, CString& strPkg)
{
	//这里new的对象将在CTcpEdgePkg析构时析构
	CTcpEdgePkgData_DevUpdateResp* pResp = new CTcpEdgePkgData_DevUpdateResp;
	CPkg_DevUpdateResp_Devs* pRespDevs = new CPkg_DevUpdateResp_Devs;
	pRespDevs->m_strID = PkgData_Node_Devices;
	pResp->AddNewChild(pRespDevs);

	CPkg_DevUpdate_Devs* pDevs = (CPkg_DevUpdate_Devs*)pData->m_pPkgData->FindByID(PkgData_Node_Devices);
	if(pDevs == NULL)    //避免收到的报文出现缺少数组时,会在此中断，添加判断
	{
		return NULL;
	}

	POS pos = pDevs->GetHeadPosition();
	while (pos)
	{
		CPkg_DevUpdate_Dev* pDev = (CPkg_DevUpdate_Dev*)pData->m_pPkgData->GetNext(pos);
		CPkg_DevUpdateResp_Dev* pRespDev = new CPkg_DevUpdateResp_Dev;
		pRespDev->m_strDeviceId = pDev->m_strDeviceId;
		pRespDev->m_strStatus = pDev->m_strStatus;
		pRespDev->m_strErrorCode = "";
		pRespDev->m_strNote = "成功";
		pRespDevs->AddNewChild(pRespDev);
	}

	strPkg = OnReqSend(pResp, PkgData_DevUpdateResp, pData->m_pPkgHead->m_strMid);
	strID = PkgData_DevUpdateResp;
	return (CDvmDataset*)m_pDvmDevice->FindDataset(PkgData_DevUpdate);
}

CDvmDataset* CTcpEdgeProtocol::OnHealthReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg)
{
	//这里new的对象将在CTcpEdgePkg析构时析构
	CTcpEdgePkgData_Health* pResp = new CTcpEdgePkgData_Health;
	strPkg = OnReqSend(pResp, PkgData_HealthResp, pData->m_pPkgHead->m_strMid);
	strID = PkgData_HealthResp;
	return (CDvmDataset*)m_pDvmDevice->FindDataset(PkgData_HealthReq);
}

CDvmDataset* CTcpEdgeProtocol::OnHealthResp(CTcpEdgePkg* pData, CString& strID, CString& strPkg)
{
	//HealthResp没有对应类,所以单独处理报文的接收
	CDvmDataset* pDataset = (CDvmDataset*)m_pDvmDevice->FindDataset(PkgData_HealthReq);
	CDvmValue* pValue = UpdateDataset(pDataset, PkgData_HealthResp, strPkg);
	pValue->m_dwItemData = 1;
	pValue->m_dwReserved = pData->m_nPort;
	return NULL;
}

long CTcpEdgeProtocol::RunProcedure(QString& strProcedureID, CExBaseList *pListDatas ,CDvmDataset *pDataset, long nPort)
{
	//根据过程ID创建不同的过程对象，添加到过程链表中
	CTcpEdgePrcdrBase *pProcedure = CreateProcedure(strProcedureID);
	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_EDGE_ERR, _T("未知的测试过程ID[%s]!"), strProcedureID);
		return 0;
	}

	pProcedure->SetTcpProtocol(this);
	if(nPort)
	{
		pProcedure->m_nPort = nPort;
	}
	else
	{
		pProcedure->m_nPort = pProcedure->GetPortFromPrcdrID(strProcedureID);
	}

	//初始化过程: 2021-8-22 lijunqing  对于边设备来说，过程都是针对设备本身，所以不需要传入DeviceID
	//2021-9-10 yzj 判断报文是否属于某设备时报文PxProtocol中需要一个DeviceID
	QString strDatasetID = strProcedureID;
	if(strProcedureID == PkgData_DeviceUpdateStatusReq)
	{
		strDatasetID = PkgData_DeviceUpdateReq;
	}
	else if (strProcedureID == PkgData_AppInstallStatusReq)
	{
		strDatasetID = PkgData_AppInstallReq;
	}

	pProcedure->InitProcedure(m_pDevice->m_strDeviceID, strProcedureID, 
		pListDatas, m_pDevice->m_oDvmDevice.FindDataset(strDatasetID), "0");
	pProcedure->m_pDvmDataset = pDataset;

	//添加到协议服务过程链表m_listTempPrcdr中
	QMutexLocker lock(&m_oPrcdrTmpCriticSection);
	m_listTempPrcdr.AddTail(pProcedure);

	return 1;
}

void CTcpEdgeProtocol::RunUserProcedure(QString strPkg, bool bIsMngrPort)
{
	CTcpEdgePrcdrBase oProcedure;
	oProcedure.SetTcpProtocol(this);
	if(bIsMngrPort)
	{
		oProcedure.m_nPort = m_nMngrPort;
	}
	else
	{
		oProcedure.m_nPort = m_nDataPort;
	}
	oProcedure.m_strDeviceID = m_pDevice->m_strDeviceID;
	oProcedure.SendUser(strPkg);
	CDvmDataset* pDataset = (CDvmDataset*)m_pDvmDevice->FindDataset(PkgData_UserEdit);
	CDvmValue* pValue = UpdateDataset(pDataset, PkgData_UserEdit, strPkg);
	pValue->m_dwItemData = -1;
	pValue->m_dwReserved = oProcedure.m_nPort;
}

void CTcpEdgeProtocol::UpdatePrcdrList()
{
	QMutexLocker lock(&m_oPrcdrTmpCriticSection);
	m_listPrcdr.AppendEx(m_listTempPrcdr);
	m_listTempPrcdr.RemoveAll();
}

//提取所有未处理的报文，用于过程处理
void CTcpEdgeProtocol::GetNotProcessedPkgs(CExBaseList &oList)
{
	QMutexLocker lock(&m_oRecvPkgLocker);
	POS pos = m_listRecvPkg.GetHeadPosition();
	CPxPkgBase* p = NULL;

	while(pos != NULL)
	{
		p = (CPxPkgBase*)m_listRecvPkg.GetNext(pos);

		if (p->IsPkgState_NotProcessed())
		{
			oList.AddTail(p);
		}
	}
}

void CTcpEdgeProtocol::DeleteUnvalidPkgs()
{
	QMutexLocker lock(&m_oRecvPkgLocker);
	long nPkgLifeTime = 0;
	long nPkgCnt = m_listRecvPkg.GetCount();
	if (nPkgCnt <= 1)
	{
		return;
	}

	//约定半个小时未处理数据丢弃
	long nValidTimeLong = 1800000;
	SYSTEMTIME tmCur;
	GetLocalTime(&tmCur);

	POS pos = m_listRecvPkg.GetHeadPosition();
	POS posTail = m_listRecvPkg.GetTailPosition();
	POS prePos = NULL;
	CPxPkgBase* p = NULL;

	while(pos != NULL)
	{
		if (pos == posTail)
		{
			break;
		}

		prePos = pos;
		p = (CPxPkgBase*)m_listRecvPkg.GetNext(pos);

		if (p->IsPkgState_CanDelete())
		{
			m_listRecvPkg.DeleteAt(prePos);
			continue;
		}

		nPkgLifeTime = GetSpanMSeconds(p->m_tmPkg,tmCur);
		if (nPkgLifeTime >= nValidTimeLong)
		{
			m_listRecvPkg.DeleteAt(prePos);
			continue;
		}
	}
}

void CTcpEdgeProtocol::StartEngineThread()
{
	m_pThread = new CTcpEdgeEngineThread;
	connect(m_pThread, SIGNAL(sig_exit()), this, SLOT(slot_exitEngine()));
	m_pThread->m_pProtocol = this;
	m_pThread->start();
}

void CTcpEdgeProtocol::ExitEngineThread()
{
	m_bExitEngineThread = true;
	while (m_bExitEngineThread)
	{
		CTickCount32 event;
		event.DoEvents(50);
	}

	delete m_pThread;
	m_pThread = NULL;
}

void CTcpEdgeProtocol::OnMngrTimeOut()
{
	if(m_pDevice && m_pDevice->m_nHasAuth == 2)
	{
		if(m_nMngrHealthRespCount == 3)
		{
			emit sig_timeout();
			emit sig_updatePkg(m_pDevice->m_strID, "心跳已经3次未收到回复,判断管理通道断连,请重新连接!", 0);
			return;
		}

		if(m_nMngrHealthRespCount == 1)
		{
			m_nMngrHealthTime = 30;
		}

		CTcpEdgePkgData_Health* pPkg = new CTcpEdgePkgData_Health;
		CDvmDataset* pDataset = m_pDvmDevice->FindDataset(PkgData_HealthReq);
		CString strPkg = OnReqSend(pPkg, PkgData_HealthReq, "1000", m_nMngrPort);
		CDvmValue* pValue = UpdateDataset(pDataset, PkgData_HealthReq, strPkg);
		pValue->m_dwReserved = m_nMngrPort;
		pValue->m_dwItemData = -1;

		m_nMngrHealthRespCount++;
	}
}

void CTcpEdgeProtocol::OnDataTimeOut()
{
	if(m_pDevice && m_pDevice->m_nHasAuth == 2)
	{
		if(m_nDataHealthRespCount == 3)
		{
			emit sig_timeout();
			emit sig_updatePkg(m_pDevice->m_strID, "心跳已经3次未收到回复,判断业务通道断连,请重新连接!", 0);
			return;
		}

		if(m_nDataHealthRespCount == 1)
		{
			m_nDataHealthTime = 30;
		}

		CDvmDataset* pDataset = m_pDvmDevice->FindDataset(PkgData_HealthReq);
		CTcpEdgePkgData_Health* pPkg = new CTcpEdgePkgData_Health;
		CString strPkg = OnReqSend(pPkg, PkgData_HealthReq, "1000", m_nDataPort);
		CDvmValue* pValue = UpdateDataset(pDataset, PkgData_HealthReq, strPkg);
		pValue->m_dwReserved = m_nDataPort;
		pValue->m_dwItemData = -1;

		m_nDataHealthRespCount++;
	}
}

void CTcpEdgeProtocol::slot_exitEngine()
{
	m_bExitEngineThread = false;
}

void CTcpEdgeProtocol::slot_updateViewPkg(QString strIP, QString strLog, long nType)
{
	emit sig_updatePkg(strIP, strLog, nType);
}
