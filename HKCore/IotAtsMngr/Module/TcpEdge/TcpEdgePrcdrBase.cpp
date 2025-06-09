#include "stdafx.h"
#include "TcpEdgePrcdrBase.h"
#include "TcpEdgeProtocol.h"
#include "TcpEdgeDevice.h"
#include "Socket/TcpEdgeSocket.h"
#include "Pkg/TcpEdgePkgData_DeviceInfoResp.h"
#include "Pkg/Pkg_ConStatusResp_ContStatu.h"
#include "Pkg/Pkg_ConStatusResp_ContStatus.h"
#include "Pkg/Pkg_ConGetConfigResp_ContCfgs.h"
#include "Pkg/Pkg_ConGetConfigResp_ContCfg.h"
#include "Pkg/TcpEdgePkgString.h"
#include "Pkg/Pkg_GetModelResp_Models.h"
#include "Pkg/Pkg_GetModelResp_Model.h"
#include "Pkg/Pkg_AppStatusResp_AppStatus.h"
#include "Pkg/Pkg_AppStatusResp_AppStatu.h"
#include "Pkg/Pkg_AppGetConfigResp_AppCfg.h"
#include "Pkg/Pkg_AppGetConfigResp_AppCfgs.h"
#include "Pkg/TcpEdgePkgData_AppGetConfigResp.h"
#include "Pkg/TcpEdgePkgData_GetMessageResp.h"
#include "Pkg/TcpEdgePkgData_GetTopoFileResp.h"
#include "Pkg/TcpEdgePkgData_GetModelResp.h"
#include "Pkg/TcpEdgePkgData_AppStatusResp.h"
#include "Pkg/TcpEdgePkgData_ConGetConfigResp.h"
#include "Pkg/TcpEdgePkgData_ConStatusResp.h"
#include "Pkg/Pkg_GetMessageResp_Files.h"
#include "Pkg/Pkg_GetTopFileResp_File.h"
#include "Pkg/Pkg_GetMessageResp_File.h"
#include "Pkg/Pkg_GetTopFileResp_Files.h"
#include "Pkg/Pkg_ModelDevReadResp_ModDev.h"
#include "Pkg/Pkg_ModelDevReadResp_ModDevs.h"
#include "Pkg/Pkg_ModelDevReadResp_Mod.h"
#include "Pkg/TcpEdgePkgData_ModelDevReadResp.h"
#include "Pkg/Pkg_ModelDevReadResp_Mods.h"
#include "../IotEngineGlobalDef.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"

CTcpEdgePrcdrBase::CTcpEdgePrcdrBase()
{
	m_nPort = 0;
	m_ulMid = 1000;
	m_pDvmDataset = NULL;
	m_pTcpProtocolRef = NULL;
}

CTcpEdgePrcdrBase::~CTcpEdgePrcdrBase()
{

}

//循环执行，判断超时或发送报文，过程结束返回TRUE
BOOL CTcpEdgePrcdrBase::Run()
{
	BOOL bRet = FALSE;

	switch(m_nProcedureState)
	{
	case PrcdrState_Step_NULL:
		//发送读命令，设置超时，状态置为PrcdrState_Step_1
		RunStepNull();
		break;
	case PrcdrState_Step_1:
		//检查是否超时，若超时，关闭定时器，状态置为PrcdrState_Step_End,EventID
		RunStep1();
		break;
	case PrcdrState_Step_End:
		break;
	default:
		SetProcedureState(PrcdrState_Step_End);
		break; 
	}

	return IsProcedureEnd();
}

BOOL CTcpEdgePrcdrBase::RunStepNull()
{
	return FALSE;
}

BOOL CTcpEdgePrcdrBase::RunStep1()
{
	//检查是否超时
	if (IsTimerOut(GetTickCount()))
	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_EDGE_ERR, _T("设备[%s]的[%s]过程出现超时!"), m_strDeviceID, m_strID);
		QString strLog = QString("[%1]过程出现超时!").arg(m_strID);
		//g_pTcpEdgeServer->UpdateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_INFO);
		//g_pTcpEdgeServer->UpdateViewPkg(m_strIP, strLog, XERRTYPE_TIMEOUT);
		emit sig_updateViewPkg(m_strIP, strLog, XLOGLEVEL_EDGE_PKG_RSLT);
		SetResultEvent(RUNPROCEDURE_EVENT_CommOverTime);
		SetProcedureState(PrcdrState_Step_End);
		return TRUE;
	}

	//处理报文列表,若提前应答报文，返回TRUE,否则返回FALSE
	return ProcessRecvPkgs();
}

QString CTcpEdgePrcdrBase::GetUserString(CDvmDataset* pDataset)
{
	m_pDvmDataset = pDataset;
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
	pPkg->m_pPkgHead = ProduceHead(m_strID);
	pPkg->m_pPkgData = ProduceData(m_strID);

	CString strASDU = pPkg->Produce();
	if(m_pDvmDataset)
	{
		CDvmDataset* pHead = (CDvmDataset*)m_pDvmDataset->FindByID(PkgData_Node_Head);
		CDvmDataset* pData = (CDvmDataset*)m_pDvmDataset->FindByID(PkgData_Node_Data);
		CJSON* pJson = CJSON_Parse(strASDU.GetString());
		DeleteNotMust(pJson, m_pDvmDataset);
		strASDU = CJSON_Print(pJson);
		CJSON_Delete(pJson);
	}

	return strASDU;
}

BOOL CTcpEdgePrcdrBase::ProcessRecvPkgs()
{
	if(m_pTcpProtocolRef == NULL)
	{
		return FALSE;
	}

	//提取所有未处理的报文
	CExBaseList oRecvList;
	m_pTcpProtocolRef->GetNotProcessedPkgs(oRecvList);

	//从报文列表中查找是否有应答
	POS pos = oRecvList.GetHeadPosition();
	CPxPkgBase *pPkg = NULL;
	BOOL bRet = FALSE;

	while(pos != NULL)
	{
		pPkg = (CPxPkgBase *)oRecvList.GetNext(pos);

		//报文时间<=m_tmBeginTime时间，说明报文过时
		if (CompareSysTime(pPkg->m_tmPkg,m_tmBeginTime) <= 0)
		{
			continue;
		}

		//处理报文：判断若是应答，继续处理，返回TRUE,否则返回FALSE
		if(ProcessPackageDetail(pPkg))
		{//若该报文为应答,添加到过程链表引用中

			bRet = TRUE;
			m_listRecvPkg.AddTail(pPkg);
			break;
		}
	}

	oRecvList.RemoveAll();
	return bRet;
}

//若是应答，处理应答，返回TRUE,否则返回FALSE
BOOL CTcpEdgePrcdrBase::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	////////////////////////////////////////////////////////////
	//CTcpEdgePkgBase *pEdgePkg = (CTcpEdgePkgBase *)pPkgDetail;
	////////////////////////////////////////////////////////////

	//判断该报文是否是期待应答【根据procedureID】


	//收到应答，关闭当前节点的定时器
	KillTimer();
	pPkgDetail->SetPkgState(PX_PKG_STATE_PROCESSED_MATCH);

	//处理应答逻辑
	ProcessPackageAck(pPkgDetail);

	return TRUE;
}

BOOL CTcpEdgePrcdrBase::ProcessPackageFinished(CPxPkgBase *pPkgDetail)
{
	pPkgDetail->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_End);
	SetResultEvent(RUNPROCEDURE_EVENT_CommFinish);
	return TRUE;
}

CTcpEdgeDevice* CTcpEdgePrcdrBase::GetDevice()
{
	return m_pTcpProtocolRef->m_pDevice;
}

CTcpEdgePkgHead* CTcpEdgePrcdrBase::ProduceHead(const CString& strFunName)
{
	CTcpEdgePkgHead* pHead = new CTcpEdgePkgHead;
	pHead->m_strID = PkgData_Node_Head;
	if(m_pDvmDataset && m_pDvmDataset->FindByID(PkgData_Node_Head))
	{
		CDvmDataset* pDataset = (CDvmDataset*)m_pDvmDataset->FindByID(PkgData_Node_Head);
		CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_FunName);
		if(pData)
		{	
			pHead->m_strFunName = pData->m_strValue;
		}
		pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Mid);
		if(pData)
		{	
			pHead->m_strMid = pData->m_strValue;
		}
		pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Cot);
		if(pData)
		{	
			pHead->m_strCot = pData->m_strValue;
		}
		pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Timestamp);
		if(pData)
		{	
			pHead->m_strTimestamp = pData->m_strValue;
		}
	}
	return pHead;
}

CTcpEdgePkgHead* CTcpEdgePrcdrBase::ProduceHead(const CString& strFunName, const CString& strCot)
{
	CTcpEdgePkgHead* pHead = new CTcpEdgePkgHead;
	pHead->m_strID = PkgData_Node_Head;
	pHead->m_strFunName = strFunName;
	pHead->m_strCot = strCot;
	if(strCot == PkgData_Value_CotReq)
	{
		pHead->m_strMid.Format("%lu", m_ulMid);
		if(m_ulMid == 4294967295)
		{
			m_ulMid = 1000;
		}
		else
		{
			m_ulMid++;
		}
	}
	else
	{
		pHead->m_strMid = m_strMid;
	}

	CString strTime;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	strTime.Format(_T("%d-%d-%d %d:%d:%d.%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	pHead->m_strTimestamp = strTime;

	return pHead;
}

void CTcpEdgePrcdrBase::DatasetToJson(CJSON* pJson, CExBaseList* pData)
{
	POS pos = pData->GetHeadPosition();
	while(pos)
	{
		CExBaseList* pNode = (CExBaseList*)pData->GetNext(pos);
		if (pNode->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			if(pJson->type == CJSON_Array)
			{
				CDvmData* pDvmData = (CDvmData*)pNode;
				CJSON* pStrJson = CJSON_CreateString(pDvmData->m_strValue.GetString());
				CJSON_AddItemToArray(pJson, pStrJson);
			}
			else
			{
				CDvmData* pDvmData = (CDvmData*)pNode;
				CJSON_AddStringToObject(pJson, pDvmData->m_strID.GetString(), pDvmData->m_strValue.GetString());
			}
		}
		else if (pNode->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			if(pJson->type == CJSON_Array)
			{
				CDvmDataset* pDvmDataset = (CDvmDataset*)pNode;
				CJSON* pDatasetJson = CJSON_CreateObject();
				CJSON_AddItemToArray(pJson, pDatasetJson);
				DatasetToJson(pDatasetJson, pDvmDataset);
			}
			else
			{
				CDvmDataset* pDvmDataset = (CDvmDataset*)pNode;
				CJSON* pDatasetJson = CJSON_CreateObject();
				CJSON_AddItemToObject(pJson, pDvmDataset->m_strID.GetString(), pDatasetJson);
				DatasetToJson(pDatasetJson, pDvmDataset);
			}
		}
		else if (pNode->GetClassID() == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)pNode;
			CJSON* pArrayJson = CJSON_CreateArray();
			CJSON_AddItemToObject(pJson, pGroup->m_strID.GetString(), pArrayJson);
			DatasetToJson(pArrayJson, pGroup);
		}
	}
}

void CTcpEdgePrcdrBase::UpdateDataset(const QString& strID, QString strPkgData)
{
	if(m_pRefDataset)
	{
		CDvmData* pData = (CDvmData*)m_pRefDataset->FindByID(strID);
		if(pData)
		{
			pData->m_strValue = strPkgData;
			CDvmValue* pValue = new CDvmValue;
			pValue->m_strID = QString("%1").arg(m_pRefDataset->m_nIndex++);
			QDateTime dateTime = QDateTime::currentDateTime();
			pValue->m_strName = dateTime.toString("yyyy-MM-dd hh:mm:ss.z");
			pValue->m_dwItemData = -1;
			pValue->m_dwReserved =m_nPort;
			pValue->m_strValue = strPkgData;
			pData->AddNewChild(pValue);
		}
	}
}

void CTcpEdgePrcdrBase::UpdateDataset(const CString& strID, QByteMap map)
{
	CTcpEdgeDevice* pDevice = GetDevice();

	CTickCount32 event;
	QByteMap::iterator iter = map.begin();
	for (; iter != map.end(); iter++)
	{
		BYTE* pBuf = iter.key();
		long nLen = iter.value();
		//发送报文打印至列表前要转回ascii
		QString strPkg = QString::fromUtf8((char*)pBuf);

		if(pDevice->m_bZlib)
		{
			uLongf nUncompressLen = nLen * 10;
			BYTE* pUncompress = new BYTE[nUncompressLen];
			memset(pUncompress, 0, nUncompressLen);
			uncompress(pUncompress, &nUncompressLen, pBuf, nLen);
			strPkg = QString("%1").arg((char*)pUncompress);
		}

		UpdateDataset(strID, strPkg);
		event.DoEvents(10);
	}
}

CTcpEdgePkgData* CTcpEdgePrcdrBase::ProduceData(const CString& strPrcdrID)
{
	CTcpEdgePkgData* pPkgData = NULL;
	if(m_pDvmDataset && m_pDvmDataset->FindByID(PkgData_Node_Data))
	{
		CDvmDataset* pDataset = (CDvmDataset*)m_pDvmDataset->FindByID(PkgData_Node_Data);
		CJSON* pJson = CJSON_CreateObject();
		DatasetToJson(pJson, pDataset);
		
		CString strJson = CJSON_Print(pJson);
		pPkgData = CTcpEdgePkgData::GetPrcdrDataByID(strPrcdrID);

		if(pPkgData)
		{
			pPkgData->SetXml_ASCII(const_cast<char*>(strJson.GetString()), 
				strlen(strJson.GetString()), CTcpEdgePkgXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
		}

		CJSON_Delete(pJson);
	}

	return pPkgData;
}

BOOL CTcpEdgePrcdrBase::Send(QByteMap map, QString strPrcdrID, long nPort)
{
	CTcpEdgeDevice* pDevice = (CTcpEdgeDevice*)m_pTcpProtocolRef->m_pDevice;

	CTickCount32 event;
	QByteMap::iterator iter = map.begin();
	for (; iter != map.end(); iter++)
	{
		BYTE* pBuf = iter.key();
		long nLen = iter.value();
		if(nPort)
		{
			pDevice->Send(nPort, pBuf, strPrcdrID, nLen);
		}
		else
		{
			pDevice->Send(GetPortFromPrcdrID(strPrcdrID), pBuf, strPrcdrID, nLen);
		}
		delete pBuf;
		event.DoEvents(10);
	}

	return TRUE;
}

BYTE* CTcpEdgePrcdrBase::Produce(BYTE* pStrASDU, long& nPkgLen, long nContinueID)
{
	CTcpEdgeDevice* pDevice = GetDevice();
	//nPkgLen初始值是ASDU的长度(小于65535的部分),函数结束时是整帧报文的长度
	long nASDULen = nPkgLen;

	//同步字符
	BYTE pkgHead[32] = {0};
	pkgHead[0] = pkgHead[2] = 0xEB;
	pkgHead[1] = pkgHead[3] = 0x90;
	//ASDU长度
	pkgHead[4] = nASDULen >> 8;
	pkgHead[5] = nASDULen;
	//控制域
	pkgHead[6] = 0x00;
	long nSignLen = 0;
	if(pDevice->m_bSign)
	{
		pkgHead[6] |= 0x01;
		nSignLen = 64;
	}
	//鉴权认证是单独在Auth过程中处理的,所以此处没有设置鉴权认证的地方
	if(pDevice->m_bZlib)
	{
		pkgHead[6] |= 0x04;
	}
	if(nContinueID)
	{
		pkgHead[6] |= 0x08;
	}
	//分段ID
	pkgHead[7] = nContinueID;
	//GatewayId
	for (int i = 0; i< m_strDeviceID.GetLength(); i++)
	{
		pkgHead[8 + i] = m_strDeviceID.GetAt(i);
	}
	//结尾带结束符
	pkgHead[31] = 0x00;

	//整合成为一帧报文
	BYTE* pStrPkg = new BYTE[32 + nASDULen + nSignLen];
	for (int i = 0; i < 32; i++)
	{
		pStrPkg[i] = pkgHead[i];
	}
	for (int i = 0; i < nASDULen; i++)
	{
		pStrPkg[i + 32] = pStrASDU[i];
	}
	nPkgLen = 32 + nASDULen + nSignLen;

	//填充签名
	if(pDevice->m_bSign)
	{
		SM2_SIGNATURE_STRUCT sm2;
		tcp_edge_sm2_cal(pStrPkg, 32 + nASDULen, sm2, pStrPkg + 32 + nASDULen);
	}

	return pStrPkg;
}

QByteMap CTcpEdgePrcdrBase::Produce(CTcpEdgePkg* pPkg, QByteMap& map)
{
	m_strASDU = pPkg->Produce();
	if(m_pDvmDataset)
	{
		CDvmDataset* pHead = (CDvmDataset*)m_pDvmDataset->FindByID(PkgData_Node_Head);
		CDvmDataset* pData = (CDvmDataset*)m_pDvmDataset->FindByID(PkgData_Node_Data);
		CJSON* pJson = CJSON_Parse(m_strASDU.GetString());
		DeleteNotMust(pJson, m_pDvmDataset);
		//DeleteNotMust(pJson->child, pHead);
		//DeleteNotMust(pJson->child->next, pData);
		m_strASDU = CJSON_Print(pJson);
		CJSON_Delete(pJson);
	}

	return Produce(m_strASDU, map);
}

QByteMap CTcpEdgePrcdrBase::Produce(QString strPkgData, QByteMap& map)
{
	QByteMap mapASDU;

	BYTE* pStrPkg = NULL;
	CTcpEdgeDevice* pDevice = GetDevice();

	//1.ASDU转换成BYTE*,发送报文需要utf8格式
	QByteArray bytes = strPkgData.toUtf8();
	//QByteArray bytes = strPkgData.toAscii();
 	long nASDULen = bytes.size();
 	BYTE* pStrASDU = new BYTE[nASDULen + 1];
	for (int i = 0; i < nASDULen + 1; i++)
	{
		pStrASDU[i] = 0;
	}
 	memcpy(pStrASDU, bytes.data(), nASDULen);

	//2.确定压缩状态
	uLongf nZlibLen = 0;
	BYTE* pStrZlibASDU = NULL;
	if(pDevice->m_bZlib)
	{
		pStrZlibASDU = tcp_edge_zlib_cal(&nZlibLen, pStrASDU, nASDULen);
		if(!pStrZlibASDU)
		{
			//错误,错误原因可能是Z_MEM_ERROR或Z_BUF_ERROR
			return mapASDU;
		}
		nASDULen = nZlibLen;
		delete pStrASDU;
		pStrASDU = new BYTE[nASDULen + 1];
		for (int i = 0; i < nASDULen + 1; i++)
		{
			pStrASDU[i] = 0;
		}
		memcpy(pStrASDU, pStrZlibASDU, nASDULen);
		delete pStrZlibASDU;
	}

	//3.确定分段状态
	if(nASDULen > 65535)
	{
		//生成分段报文
		long nContinueID = 1;
		while (nASDULen / 65535)
		{
			long nTempLen = 65535;
			mapASDU.insert(pStrASDU, nASDULen);
			map.insert(Produce(pStrASDU, nTempLen, nContinueID), nTempLen);
			pStrASDU += 65535;
			nASDULen -= 65535;
			nContinueID++;
		}
		mapASDU.insert(pStrASDU, nASDULen);
		map.insert(Produce(pStrASDU, nASDULen, nContinueID), nASDULen);
	}
	else
	{
		//生成一次报文
		mapASDU.insert(pStrASDU, nASDULen);
		map.insert(Produce(pStrASDU, nASDULen, 0), nASDULen);
	}
	return mapASDU;
}
/*
BYTE* CTcpEdgePrcdrBase::Produce(CString strPkgData, long& nPkgLen)
{
	CString strASDU = strPkgData;

	BYTE pkgHead[32] = {0};
	pkgHead[0] = pkgHead[2] = 0xEB;
	pkgHead[1] = pkgHead[3] = 0x90;

	long nLen = strASDU.GetLength();
	if(nLen > 65535)
	{
		pkgHead[4] = pkgHead[5] = 0xFF;
		//启用控制域来实现分段
		//暂时未实现
		return NULL;
	}
	else
	{
		pkgHead[4] = nLen >> 8;
		pkgHead[5] = nLen;
		pkgHead[6] = pkgHead[7] = 0x00;
	}

	for (int i = 0; i< m_strDeviceID.GetLength(); i++)
	{
		pkgHead[8 + i] = m_strDeviceID.GetAt(i);
	}

	pkgHead[31] = 0x00;

	BYTE* pkg = new BYTE[32 + strASDU.GetLength()];
	for (int i = 0; i < 32; i++)
	{
		pkg[i] = pkgHead[i];
	}
	for (int i = 0; i < strASDU.GetLength(); i++)
	{
		pkg[i + 32] = strASDU.GetAt(i);
	}

	nPkgLen = 32 + nLen;
	//使用完成之后需要delete
	return pkg;
}

BYTE* CTcpEdgePrcdrBase::Produce(CTcpEdgePkg* pPkg, long& nPkgLen)
{
	m_strASDU = pPkg->Produce();

	if(m_pDvmDataset)
	{
		CDvmDataset* pDvmDataset = (CDvmDataset*)m_pDvmDataset->FindByID(PkgData_Node_Data);
		CJSON* pJson = CJSON_Parse(m_strASDU.GetString());
		DeleteNotMust(pJson->child->next, pDvmDataset);
		m_strASDU = CJSON_Print(pJson);
		CJSON_Delete(pJson);
	}

	return Produce(m_strASDU, nPkgLen);
}
*/
long CJSON_GetObjectChildCount(CJSON* pJson)
{
	CJSON* pChild = pJson->child;
	long nCount = 0;
	while (pChild)
	{
		nCount++;
		pChild = pChild->next;
	}
	return nCount;
}

long CJSON_GetItemIndexFromArray(CJSON* pJson, CJSON* pItem)
{
	long nSize = CJSON_GetArraySize(pJson);
	for (int i = 0; i < nSize; i++)
	{
		if (CJSON_GetArrayItem(pJson, i) == pItem)
		{
			return i;
		}
	}
	return -1;
}

void CJSON_DeleteItem(CJSON* pJson, CJSON* pItem)
{
	if(pJson->type == CJSON_Object)
	{
		CJSON_DeleteItemFromObject(pJson, pItem->string);
	}
	else if (pJson->type == CJSON_Array)
	{
		CJSON_DeleteItemFromArray(pJson, CJSON_GetItemIndexFromArray(pJson, pItem));
	}
}

void CTcpEdgePrcdrBase::DeleteNotMust(CJSON* pJson, CExBaseList* pNode)
{
	if(!pJson)
	{
		return;
	}	
	//考虑容错测试时删除Dataset中不存在的项(用户手动取消的项)
	CJSON* pData = pJson->child;
//	POS pos = pNode->GetHeadPosition();
	while (pData)
	{
		//提前记录下一个指针
		CJSON* pTemp = pData->next;

		//检测存在
		CExBaseList* pObj = (CExBaseList*)pNode->FindByID(pData->string);

		if(!pObj->m_dwItemData)
		{
			CJSON_DeleteItem(pJson, pData);
		}
		else if (pObj->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			DeleteNotMust(pData, pObj);
		}
		else if (pObj->GetClassID() == DVMCLASSID_CDVMDATASETGROUP)
		{
			POS pos = pObj->GetHeadPosition();
			CJSON* pChild = pData->child;
			while (pChild)
			{
				CJSON* pTempChild = pChild->next;
				CExBaseList* pObjChild = (CExBaseList*)pObj->GetNext(pos);
				DeleteNotMust(pChild, pObjChild);
				pChild = pTempChild;
			}
		}

		pData = pTemp;
	}

	return;
/*
	//注意,因为Tcp即插即用协议中不存在int的value
	//所以json报文中使用int值来临时计算非必需项的子必需项空值数
	//进而删除全空非必需项
	CJSON* pData = pJson->child;
	while (pData)
	{
		CJSON* pTemp = pData->next;
		if(pData->type == CJSON_String)
		{
			CDvmData* pDvmData = (CDvmData*)pNode->FindByID(pData->string);
				if(!pDvmData->m_strValue.GetLength())
			{
				if (!pDvmData->m_dwReserved)
				{
					CJSON_DeleteItem(pJson, pData);
				}
				else if(!pNode->m_dwReserved)
				{
					//计算空值
					pJson->valueint++;
				}
			}
		}
		else if (pData->type == CJSON_Object)
		{
			CDvmDataset* pDvmDataset = (CDvmDataset*)pNode->FindByID(pData->string);
			DeleteNotMust(pData, pDvmDataset);
			if((!pData->child && !pDvmDataset->m_dwReserved)
				|| (pData->valueint == CJSON_GetObjectChildCount(pData)))
			{
				CJSON_DeleteItem(pJson, pData);
			}
		}
		else if (pData->type == CJSON_Array)
		{
			CDvmDatasetGroup* pDvmDatasetGroup = (CDvmDatasetGroup*)pNode->FindByID(pData->string);
			DeleteNotMust(pData, pDvmDatasetGroup);
			if(!pData->child && !pDvmDatasetGroup->m_dwReserved)
			{
				CJSON_DeleteItem(pJson, pData);
			}
		}

		pData = pTemp;
	}
*/
}

BOOL CTcpEdgePrcdrBase::Send(CTcpEdgePkg* pPkg, QString strPrcdrID, long nPort)
{
	QByteMap map;
	Produce(pPkg, map);
	Send(map, strPrcdrID, nPort);
	delete pPkg;
	return TRUE;
}

BOOL CTcpEdgePrcdrBase::SendUser(QString strPkg)
{
	QByteMap map;
	Produce(strPkg, map);
	
	CTcpEdgeDevice* pDevice = (CTcpEdgeDevice*)m_pTcpProtocolRef->m_pDevice;
	CTickCount32 event;
	QByteMap::iterator iter = map.begin();
	for (; iter != map.end(); iter++)
	{
		BYTE* pBuf = iter.key();
		long nLen = iter.value();
		pDevice->Send(m_nPort, pBuf, "", nLen);
		delete pBuf;
		event.DoEvents(10);
	}

	return TRUE;
}

BOOL CTcpEdgePrcdrBase::Send(QString strPkg, QString strPrcdrID)
{
	QByteMap map;
	Produce(strPkg, map);
	Send(map, strPrcdrID);
	return TRUE;
}

CString CTcpEdgePrcdrBase::ProduceASDU(CTcpEdgePkg* pPkg)
{
	return pPkg->Produce();
}

BOOL CTcpEdgePrcdrBase::Send(CTcpEdgePkg* pPkg, CString strFunName, CString strCot, long nPort)
{
	if(!pPkg->m_pPkgHead)
	{
		pPkg->m_pPkgHead = ProduceHead(strFunName, strCot);
	}

	return Send(pPkg, strFunName, nPort);
}

void CTcpEdgePrcdrBase::UpdateRecord(CTcpEdgePkg* pPkg)
{
	CTcpEdgeDevice* pDevice = GetDevice();
	if (m_strID == PkgData_DeviceInfoReq)
	{
		CTcpEdgePkgData_DeviceInfoResp* pData = (CTcpEdgePkgData_DeviceInfoResp*)pPkg->m_pPkgData;
		pDevice->m_oRecord.m_strDevName = pData->m_pTcpEdgePkgDev->m_strDevName;
		pDevice->m_oRecord.m_strCpuLmt = pData->m_pTcpEdgePkgCpu->m_strCpuLmt;
		pDevice->m_oRecord.m_strMemLmt = pData->m_pTcpEdgePkgMem->m_strMemLmt;
		pDevice->m_oRecord.m_strDiskLmt = pData->m_pTcpEdgePkgDisk->m_strDiskLmt;
		pDevice->m_oRecord.m_strTemHigh = pData->m_pTcpEdgePkgTemperature->m_strTemHigh;
		pDevice->m_oRecord.m_strTemLow = pData->m_pTcpEdgePkgTemperature->m_strTemLow;
	}
	else if (m_strID == PkgData_ConStatusReq)
	{
		pDevice->m_oRecord.m_containers.DeleteAll();
		CTcpEdgePkgData_ConStatusResp* pData = (CTcpEdgePkgData_ConStatusResp*)pPkg->m_pPkgData;
		CPkg_ConStatusResp_ContStatus* pContStatus = (CPkg_ConStatusResp_ContStatus*)pData->FindByID(PkgData_Node_ContStatus);
		POS pos = pContStatus->GetHeadPosition();
		while (pos)
		{
			CPkg_ConStatusResp_ContStatu* pContStatu = (CPkg_ConStatusResp_ContStatu*)pContStatus->GetNext(pos);
			CContianerRecord* pNew = new CContianerRecord;
			pDevice->m_oRecord.m_containers.AddNewChild(pNew);
			pNew->m_strID = pNew->m_strContainer = pContStatu->m_strContainer;
		}
	}
	else if (m_strID == PkgData_ConGetConfigReq)
	{
		pDevice->m_oRecord.m_containers.DeleteAll();
		CTcpEdgePkgData_ConGetConfigResp* pData = (CTcpEdgePkgData_ConGetConfigResp*)pPkg->m_pPkgData;
		CPkg_ConGetConfigResp_ContCfgs* pContCfgs = (CPkg_ConGetConfigResp_ContCfgs*)pData->FindByID(PkgData_Node_ContCfgs);
		POS pos = pContCfgs->GetHeadPosition();
		while (pos)
		{
			CPkg_ConGetConfigResp_ContCfg* pContCfg = (CPkg_ConGetConfigResp_ContCfg*)pContCfgs->GetNext(pos);
			CContianerRecord* pNew = new CContianerRecord;
			pDevice->m_oRecord.m_containers.AddNewChild(pNew);
			pNew->m_strID = pNew->m_strContainer = pContCfg->m_strContainer;
			pNew->m_strCpus = pContCfg->m_pTcpEdgePkgCfgCpu->m_strCpus;
			pNew->m_strCpuLmt = pContCfg->m_pTcpEdgePkgCfgCpu->m_strCpuLmt;
			pNew->m_strMemory = pContCfg->m_pTcpEdgePkgCfgMem->m_strMemory;
			pNew->m_strMemLmt = pContCfg->m_pTcpEdgePkgCfgMem->m_strMemLmt;
			pNew->m_strDisk = pContCfg->m_pTcpEdgePkgCfgDisk->m_strDisk;
			pNew->m_strDiskLmt = pContCfg->m_pTcpEdgePkgCfgDisk->m_strDiskLmt;

			CTcpEdgePkgString* pPort = (CTcpEdgePkgString*)pContCfg->FindByID(PkgData_Node_Port);
			POS posString = pPort->GetHeadPosition();
			while (posString)
			{
				CTcpEdgePkgString* pString = (CTcpEdgePkgString*)pPort->GetNext(posString);
				pNew->m_strPorts.append(pString->m_strValue);
			}
			CTcpEdgePkgString* pMount = (CTcpEdgePkgString*)pContCfg->FindByID(PkgData_Node_Mount);
			posString = pMount->GetHeadPosition();
			while (posString)
			{
				CTcpEdgePkgString* pString = (CTcpEdgePkgString*)pMount->GetNext(posString);
				pNew->m_strMounts.append(pString->m_strValue);
			}
			CTcpEdgePkgString* pDev = (CTcpEdgePkgString*)pContCfg->FindByID(PkgData_Node_Dev);
			posString = pDev->GetHeadPosition();
			while (posString)
			{
				CTcpEdgePkgString* pString = (CTcpEdgePkgString*)pDev->GetNext(posString);
				pNew->m_strDevs.append(pString->m_strValue);
			}
		}
	}
	else if (m_strID == PkgData_AppStatusReq)
	{
		CTcpEdgePkgData_AppStatusResp* pData = (CTcpEdgePkgData_AppStatusResp*)pPkg->m_pPkgData;
		CContianerRecord* pRecord = (CContianerRecord*)pDevice->m_oRecord.m_containers.FindByID(pData->m_strContainer);
		if(!pRecord)
		{
			pRecord = new CContianerRecord;
			pDevice->m_oRecord.m_containers.AddNewChild(pRecord);
			pRecord->m_strID = pRecord->m_strContainer = pData->m_strContainer;
		}

		pRecord->m_apps.DeleteAll();
		CPkg_AppStatusResp_AppStatus* pAppStatus = (CPkg_AppStatusResp_AppStatus*)pData->FindByID(PkgData_Node_AppStatus);
		POS pos = pAppStatus->GetHeadPosition();
		while (pos)
		{
			CPkg_AppStatusResp_AppStatu* pAppStatu = (CPkg_AppStatusResp_AppStatu*)pAppStatus->GetNext(pos);
			CAppRecord* pNew = new CAppRecord;
			pRecord->m_apps.AddNewChild(pNew);
			pNew->m_strID = pNew->m_strApp = pAppStatu->m_strApp;
		}
	}
	else if (m_strID == PkgData_AppGetConfigReq)
	{
		CTcpEdgePkgData_AppGetConfigResp* pData = (CTcpEdgePkgData_AppGetConfigResp*)pPkg->m_pPkgData;
		CContianerRecord* pRecord = (CContianerRecord*)pDevice->m_oRecord.m_containers.FindByID(pData->m_strContainer);
		if(!pRecord)
		{
			pRecord = new CContianerRecord;
			pDevice->m_oRecord.m_containers.AddNewChild(pRecord);
			pRecord->m_strID = pRecord->m_strContainer = pData->m_strContainer;
		}

		pRecord->m_apps.DeleteAll();
		CPkg_AppGetConfigResp_AppCfgs* pAppCfgs = (CPkg_AppGetConfigResp_AppCfgs*)pData->FindByID(PkgData_Node_AppCfgs);
		POS pos = pAppCfgs->GetHeadPosition();
		while (pos)
		{
			CPkg_AppGetConfigResp_AppCfg* pAppCfg = (CPkg_AppGetConfigResp_AppCfg*)pAppCfgs->GetNext(pos);
			CAppRecord* pNew = new CAppRecord;
			pRecord->m_apps.AddNewChild(pNew);
			pNew->m_strID = pNew->m_strApp = pAppCfg->m_strApp;
			pNew->m_strCpus = pAppCfg->m_pTcpEdgePkgCfgCpu->m_strCpus;
			pNew->m_strCpuLmt = pAppCfg->m_pTcpEdgePkgCfgCpu->m_strCpuLmt;
			pNew->m_strMemory = pAppCfg->m_pTcpEdgePkgCfgMem->m_strMemory;
			pNew->m_strMemLmt = pAppCfg->m_pTcpEdgePkgCfgMem->m_strMemLmt;
		}
	}
	else if (m_strID == PkgData_GetTopoFile)
	{
		pDevice->m_oRecord.m_strTopofiles.clear();
		CTcpEdgePkgData_GetTopoFileResp* pData = (CTcpEdgePkgData_GetTopoFileResp*)pPkg->m_pPkgData;
		CPkg_GetTopFileResp_Files* pFiles = (CPkg_GetTopFileResp_Files*)pData->FindByID(PkgData_Node_FileList);
		POS pos = pFiles->GetHeadPosition();
		while (pos)
		{
			CPkg_GetTopFileResp_File* pFile = (CPkg_GetTopFileResp_File*)pFiles->GetNext(pos);
			pDevice->m_oRecord.m_strTopofiles.append(pFile->m_strFullPathFileName);
		}
	}
	else if (m_strID == PkgData_GetMessage)
	{
		pDevice->m_oRecord.m_strMessagefiles.clear();
		CTcpEdgePkgData_GetMessageResp* pData = (CTcpEdgePkgData_GetMessageResp*)pPkg->m_pPkgData;
		CPkg_GetMessageResp_Files* pFiles = (CPkg_GetMessageResp_Files*)pData->FindByID(PkgData_Node_FileList);
		POS pos = pFiles->GetHeadPosition();
		while (pos)
		{
			CPkg_GetMessageResp_File* pFile = (CPkg_GetMessageResp_File*)pFiles->GetNext(pos);
			pDevice->m_oRecord.m_strMessagefiles.append(pFile->m_strFullPathFileName);
		}
	}
	else if(m_strID == PkgData_GetModel)
	{
		pDevice->m_oRecord.m_models.DeleteAll();
		CTcpEdgePkgData_GetModelResp* pData = (CTcpEdgePkgData_GetModelResp*)pPkg->m_pPkgData;
		CPkg_GetModelResp_Models* pModels = (CPkg_GetModelResp_Models*)pData->FindByID(PkgData_Node_Models);
		POS pos = pModels->GetHeadPosition();
		while (pos)
		{
			CPkg_GetModelResp_Model* pModel = (CPkg_GetModelResp_Model*)pModel->GetNext(pos);
			CModelRecord* pNew = new CModelRecord;
			pDevice->m_oRecord.m_models.AddNewChild(pNew);
			pNew->m_strID = pNew->m_strModelName = pModel->m_strModelName;
			pNew->m_strModifyTime = pModel->m_strModifyTime;
			pNew->m_strFullPathFileName = pModel->m_strFullPathFileName;
			pNew->m_strFileCrc = pModel->m_strFileCrc;
		}
	}
	else if(m_strID == PkgData_ModelDevRead)
	{
		CTcpEdgePkgData_ModelDevReadResp* pData = (CTcpEdgePkgData_ModelDevReadResp*)pPkg->m_pPkgData;
		CPkg_ModelDevReadResp_Mods* pModels = (CPkg_ModelDevReadResp_Mods*)pData->FindByID(PkgData_Node_Models);
		POS pos = pModels->GetHeadPosition();
		while (pos)
		{
			CPkg_ModelDevReadResp_Mod* pModel = (CPkg_ModelDevReadResp_Mod*)pModel->GetNext(pos);
			CModelRecord* pRecord = (CModelRecord*)pDevice->m_oRecord.m_models.FindByID(pModel->m_strModel);
			if(!pRecord)
			{
				pRecord = new CModelRecord;
				pDevice->m_oRecord.m_models.AddNewChild(pRecord);
				pRecord->m_strID = pRecord->m_strModelName = pModel->m_strModel;
			}

			pRecord->m_devs.DeleteAll();
			CPkg_ModelDevReadResp_ModDevs* pDevs = (CPkg_ModelDevReadResp_ModDevs*)pModel->FindByID(PkgData_Node_Devices);
			if(pDevs)
			{
				POS pos = pDevs->GetHeadPosition();
				while (pos)
				{
					CPkg_ModelDevReadResp_ModDev* pDev = (CPkg_ModelDevReadResp_ModDev*)pData->GetNext(pos);
					CModelDeviceRecord* pNew = new CModelDeviceRecord;
					pRecord->m_devs.AddNewChild(pNew);
					pNew->m_strID = pNew->m_strDeviceId = pDev->m_strDeviceId;
					pNew->m_strDeviceDesc = pDev->m_strDeviceDesc;
					pNew->m_strStatus = pDev->m_strStatus;
				}
			}
		}
	}
}

long CTcpEdgePrcdrBase::GetPortFromPrcdrID(QString strPrcdrID)
{
	//0-未找到 1-管理通道 2-数据通道(业务)
	if((strPrcdrID == PkgData_TimeSyncReq)
		|| (strPrcdrID == PkgData_TimeSyncResp)
		|| (strPrcdrID == PkgData_DeviceGetLogReq)
		|| (strPrcdrID == PkgData_DeviceGetLogResp)
		|| (strPrcdrID == PkgData_ContGetLogReq)
		|| (strPrcdrID == PkgData_ContGetLogResp)
		|| (strPrcdrID == PkgData_AppGetLogReq)
		|| (strPrcdrID == PkgData_AppGetLogResp)
		|| (strPrcdrID == PkgData_TimeReadReq)
		|| (strPrcdrID == PkgData_TimeReadResp)
		|| (strPrcdrID == PkgData_DeviceUpdateReq)
		|| (strPrcdrID == PkgData_DeviceUpdateResp)
		|| (strPrcdrID == PkgData_DeviceUpdateStatusReq)
		|| (strPrcdrID == PkgData_DeviceUpdateStatusResp)
		|| (strPrcdrID == PkgData_DeviceUpdateResult)
		|| (strPrcdrID == PkgData_DeviceCtrlReq)
		|| (strPrcdrID == PkgData_DeviceCtrlResp)
		|| (strPrcdrID == PkgData_DeviceInfoReq)
		|| (strPrcdrID == PkgData_DeviceInfoResp)
		|| (strPrcdrID == PkgData_DeviceStatusReq)
		|| (strPrcdrID == PkgData_DeviceStatusResp)
		|| (strPrcdrID == PkgData_DeviceConfigReq)
		|| (strPrcdrID == PkgData_DeviceConfigResp)
		|| (strPrcdrID == PkgData_SysAlarm)
		|| (strPrcdrID == PkgData_ConInstallReq)
		|| (strPrcdrID == PkgData_ConInstallResp)
		|| (strPrcdrID == PkgData_ConStatusReq)
		|| (strPrcdrID == PkgData_ConStatusResp)
		|| (strPrcdrID == PkgData_ConStartReq)
		|| (strPrcdrID == PkgData_ConStartResp)
		|| (strPrcdrID == PkgData_ConStopReq)
		|| (strPrcdrID == PkgData_ConStopResp)
		|| (strPrcdrID == PkgData_ConRestartReq)
		|| (strPrcdrID == PkgData_ConRestartResp)
		|| (strPrcdrID == PkgData_ConRemoveReq)
		|| (strPrcdrID == PkgData_ConRemoveResp)
		|| (strPrcdrID == PkgData_ConGetConfigReq)
		|| (strPrcdrID == PkgData_ConGetConfigResp)
		|| (strPrcdrID == PkgData_ConSetConfigReq)
		|| (strPrcdrID == PkgData_ConSetConfigResp)
		|| (strPrcdrID == PkgData_ConAlarm)
		|| (strPrcdrID == PkgData_AppSetConfigReq)
		|| (strPrcdrID == PkgData_AppSetConfigResp)
		|| (strPrcdrID == PkgData_AppGetConfigReq)
		|| (strPrcdrID == PkgData_AppGetConfigResp)
		|| (strPrcdrID == PkgData_AppDisableReq)
		|| (strPrcdrID == PkgData_AppDisableResp)
		|| (strPrcdrID == PkgData_AppEnableReq)
		|| (strPrcdrID == PkgData_AppEnableResp)
		|| (strPrcdrID == PkgData_AppRemoveReq)
		|| (strPrcdrID == PkgData_AppRemoveResp)
		|| (strPrcdrID == PkgData_AppStopReq)
		|| (strPrcdrID == PkgData_AppStopResp)
		|| (strPrcdrID == PkgData_AppStartReq)
		|| (strPrcdrID == PkgData_AppStartResp)
		|| (strPrcdrID == PkgData_AppStatusReq)
		|| (strPrcdrID == PkgData_AppStatusResp)
		|| (strPrcdrID == PkgData_AppInstallReq)
		|| (strPrcdrID == PkgData_AppInstallResp)
		|| (strPrcdrID == PkgData_AppInstallStatusReq)
		|| (strPrcdrID == PkgData_AppInstallStatusResp)
		|| (strPrcdrID == PkgData_AppInstallResult)
		|| (strPrcdrID == PkgData_AppAlarm)
		|| (strPrcdrID == PkgData_AppGetCfgFileReq)
		|| (strPrcdrID == PkgData_AppGetCfgFileResp)
		|| (strPrcdrID == PkgData_AppSetCfgFileReq)
		|| (strPrcdrID == PkgData_AppSetCfgFileResp))
	{
		return m_pTcpProtocolRef->m_nMngrPort;
	}
	else if((strPrcdrID == PkgData_ModelChange)
		|| (strPrcdrID == PkgData_ModelChangeResp)	
		|| (strPrcdrID == PkgData_DevAdd)			
		|| (strPrcdrID == PkgData_DevAddResp)		
		|| (strPrcdrID == PkgData_DevUpdate)		
		|| (strPrcdrID == PkgData_DevUpdateResp)	
		|| (strPrcdrID == PkgData_ModelDevRead)	
		|| (strPrcdrID == PkgData_ModelDevReadResp)
		|| (strPrcdrID == PkgData_DataSubs)		
		|| (strPrcdrID == PkgData_DataSubsResp)	
		|| (strPrcdrID == PkgData_GetDataSubs)		
		|| (strPrcdrID == PkgData_GetDataSubsResp)	
		|| (strPrcdrID == PkgData_DataSpont)		
		|| (strPrcdrID == PkgData_DataSpontResp)	
		|| (strPrcdrID == PkgData_DataRead)		
		|| (strPrcdrID == PkgData_DataReadResp)	
		|| (strPrcdrID == PkgData_ParaRead)		
		|| (strPrcdrID == PkgData_ParaReadResp)	
		|| (strPrcdrID == PkgData_ParaCancel)		
		|| (strPrcdrID == PkgData_ParaCancelResp)	
		|| (strPrcdrID == PkgData_ParaSet)			
		|| (strPrcdrID == PkgData_ParaSetResp)		
		|| (strPrcdrID == PkgData_ParaActivate)	
		|| (strPrcdrID == PkgData_ParaActivateResp)
		|| (strPrcdrID == PkgData_CtrlCmd)			
		|| (strPrcdrID == PkgData_CtrlCmdResp)		
		|| (strPrcdrID == PkgData_GetHisData)		
		|| (strPrcdrID == PkgData_GetHisDataResp)	
		|| (strPrcdrID == PkgData_GetModel)		
		|| (strPrcdrID == PkgData_GetModelResp)	
		|| (strPrcdrID == PkgData_GetTopoFile)		
		|| (strPrcdrID == PkgData_GetTopoFileResp)	
		|| (strPrcdrID == PkgData_GetMessage)		
		|| (strPrcdrID == PkgData_GetMessageResp)	
		|| (strPrcdrID == PkgData_GetHisEvent)		
		|| (strPrcdrID == PkgData_GetHisEventResp)
		|| (strPrcdrID == PkgData_FileGet)
		|| strPrcdrID == "FileModelGet"
		|| strPrcdrID == "FileTopoGet"
		|| strPrcdrID == "FileMessageGet")
	{
		return m_pTcpProtocolRef->m_nDataPort;
	}

	return 0;
}