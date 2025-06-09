//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpPrjDevice.cpp  CPpPrjDevice


#include "stdafx.h"
#include "PpPrjDevice.h"
#include "../SttMqttClientTool.h"
#include "../MqttClientEngineBase.h"
#include "../CmdExecRslt/CmdExecRslt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPpPrjDevice::CPpPrjDevice()
{
	m_pRefEngineData = NULL;
	m_pReadAinDs = NULL;
	m_pCurProcedure = NULL;

	GetLocalTime(&m_tmUpdate);

	SetTestProgress_NoStart();
}

CPpPrjDevice::~CPpPrjDevice()
{
}

long CPpPrjDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CPpPrjXmlRWKeys *pXmlKeys = (CPpPrjXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTemplate_FileKey, oNode, m_strTemplate_File);
	xml_GetAttibuteValue(pXmlKeys->m_strDdvm_FileKey, oNode, m_strDdvm_File);
	return 0;
}

long CPpPrjDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CPpPrjXmlRWKeys *pXmlKeys = (CPpPrjXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTemplate_FileKey, oElement, m_strTemplate_File);
	xml_SetAttributeValue(pXmlKeys->m_strDdvm_FileKey, oElement, m_strDdvm_File);
	return 0;
}

long CPpPrjDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeCalLen(oBinaryBuffer, m_strDdvm_File);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeRead(oBinaryBuffer, m_strDdvm_File);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTemplate_File);
		BinarySerializeWrite(oBinaryBuffer, m_strDdvm_File);
	}
	return 0;
}

void CPpPrjDevice::InitAfterRead()
{
}

BOOL CPpPrjDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpPrjDevice *p = (CPpPrjDevice*)pObj;

	if(m_strTemplate_File != p->m_strTemplate_File)
	{
		return FALSE;
	}

	if(m_strDdvm_File != p->m_strDdvm_File)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpPrjDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpPrjDevice *p = (CPpPrjDevice*)pDest;

	p->m_strTemplate_File = m_strTemplate_File;
	p->m_strDdvm_File = m_strDdvm_File;
	return TRUE;
}

CBaseObject* CPpPrjDevice::Clone()
{
	CPpPrjDevice *p = new CPpPrjDevice();
	Copy(p);
	return p;
}

CBaseObject* CPpPrjDevice::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPpPrjDevice *p = new CPpPrjDevice();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPpPrjDevice::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPpPrjDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPpPrjXmlRWKeys *pXmlKeys = (CPpPrjXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPpPrjDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;
	return pNew;
}

void CPpPrjDevice::SetTestProgress_NoStart()
{
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_NOTBEGIN;
	m_nTimeOut = 0;
	m_dwStartTime = 0;
}

void CPpPrjDevice::SetTestProgress_Start(DWORD dwStartTime,long nTimeOut)
{
	m_nTimeOut = nTimeOut;
	m_dwStartTime = dwStartTime;
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_WAITING;
}

void CPpPrjDevice::SetTestProgress_HasReport()
{
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_HASREPORT;
}

void CPpPrjDevice::SetTestProgress_TimeOut()
{
	m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_TIMEOUT;
}

BOOL CPpPrjDevice::IsTestProgress_HasReport()
{
	return (m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_HASREPORT);
}

BOOL CPpPrjDevice::IsTestProgress_Finish(DWORD dwCurTime)
{
	if (m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_NOTBEGIN)
	{
		return FALSE;
	}

	if ((m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_HASREPORT) || (m_nTestProgress == ATS_DEVICE_TEST_PROGRESS_TIMEOUT))
	{
		return TRUE;
	}

	if(dwCurTime - m_dwStartTime >= m_nTimeOut)
	{
		m_nTestProgress = ATS_DEVICE_TEST_PROGRESS_TIMEOUT;
		return TRUE;
	}

	return FALSE;
}

void CPpPrjDevice::Init(CExBaseObject *pRefEngineData,const CString &strReadAinDsID)
{
	m_pReadAinDs = NULL;
	m_pRefEngineData = pRefEngineData;

	if (!m_oDvmDevice.OpenXmlFile(m_strDdvm_File,CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("打开模型文件【%s】失败。"), m_strDdvm_File);
	}
	else if (!strReadAinDsID.IsEmpty())
	{
		m_pReadAinDs = m_oDvmDevice.FindDataset(strReadAinDsID);
	}
}

long CPpPrjDevice::GetTimeout()
{
	ASSERT(m_pCurProcedure != NULL);

	CMqttPpOverTime* pPpOverTime = m_pCurProcedure->GetOvertime();
	return pPpOverTime->m_nValue;
}

BOOL CPpPrjDevice::RunProcedure(CMqttPpProcedure *pCurProcedure,CMqttPpProduce *pProduce)
{//pProduce：参数列表值已更新
	m_pCurProcedure = pCurProcedure;

	if (pProduce != NULL)
	{//非读测量值
		char *pBuf = NULL;
		long nLen = 0;
		BOOL bRet = FALSE;

// 		BOOL bRet = CSensorProtocalEngine::GenerateSensorPacket(pProduce,&pBuf,nLen);
// 		if (!bRet)
// 		{
// 			return FALSE;
// 		}

// 		bRet = CSttMqttClientTool::SendPublicSensorPkg(pBuf,nLen,m_strID,MQTT_TOPIC_SensorCmd);
// 		delete pBuf;

		if (!bRet)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前项目装置【%s】发送报文失败"),m_strID);
			SetTestProgress_TimeOut();
		}
	}

	SetTestProgress_Start(GetTickCount(),GetTimeout());

	return TRUE;
}

BOOL CPpPrjDevice::ProcessRecvPacket(CMqttPpTemplate *pMqttPpTemplate,char *pBuf,long nLen)
{
	SensorPkgInfo oSensorPkgInfo;
	CMqttPpPrase *pPrase = NULL;
// 	CMqttPpPrase *pPrase = CSensorProtocalEngine::PraseSensorPkgInfo(pMqttPpTemplate,pBuf,nLen,oSensorPkgInfo);
// 	if (pPrase == NULL)
// 	{
// 		return FALSE;
// 	}

	CDvmDataset *pModelDataset = m_oDvmDevice.FindDataset(pPrase->GetDsID());

	if (pPrase->IsModelOptr_Write())
	{//更新数据集
	//	UpdateDatasByPrase(*pModelDataset,pPrase);

		if (pModelDataset == m_pReadAinDs)
		{//如果是实时监测数据，更新界面
			GetLocalTime(&m_tmUpdate);
			g_pMqttClientEngineBase->UpdateRTDevice(this);
		}
	}

	if(m_pCurProcedure == NULL)
	{//当前无测试命令
		return FALSE;
	}
	else
	{
		CMqttPpAck *pFindAck = m_pCurProcedure->FindAck(pPrase->m_strID);
		if (pFindAck == NULL)
		{
			return FALSE;
		}

		if (pFindAck->IsJumpTo_End())
		{//填写报告文件
			long nRslt = GetAckPkgRslt(oSensorPkgInfo);

			//更新报告文件
			UpdateReportFile(nRslt,pModelDataset);

			//更新装置状态
			SetTestProgress_HasReport();
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("暂不支持跳转"));
			return FALSE;
		}
	}

	return TRUE;
}

void CPpPrjDevice::UpdateDataset(CDvmDataset *pSrcDataset)
{
	CDvmDataset *pDataset = m_oDvmDevice.FindDataset(pSrcDataset->m_strID);
	if (pDataset == NULL)
	{
		return;
	}

	pDataset->UpdateDataValue(pSrcDataset);
}

void CPpPrjDevice::UpdateDataset2(CDvmDataset *pDestDataset)
{
	CDvmDataset *pDataset = m_oDvmDevice.FindDataset(pDestDataset->m_strID);
	if (pDataset == NULL)
	{
		return;
	}

	pDestDataset->UpdateDataValue(pDataset);
}

// void CPpPrjDevice::UpdatePraseValue(SensorPkgInfo &oSensorPkgInfo,CMqttPpPrase *pPrase)
// {
// 	CDvmDataset *pModelDataset = NULL;
// 	if (pPrase->IsModelOptr_Write())
// 	{
// 		pModelDataset = m_oDvmDevice.FindDataset(pPrase->GetDsID());
// 	}
// 
// 	POS pos = pPrase->GetHeadPosition();
// 	CDvmData *p = NULL;
// 	int nParaIndex = 0;
// 
// 	while(pos != NULL)
// 	{
// 		p = (CDvmData *)pPrase->GetNext(pos);
// 
// 		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
// 		{
// 			continue;
// 		}
// 
// 		SensorParaData *pParaData = oSensorPkgInfo.vec[nParaIndex];
// 		int nDataLen = pParaData->GetDataLen();
// 		long nDecimal = 0;
// 		p->GetValueByID(SENSOR_MODEL_ID_Decimal,nDecimal);
// 
// 		if (nDecimal > 0)
// 		{
// 			double fValue = 0;
// 			CString strFormat;
// 			strFormat.Format(_T("%%.%df"),nDecimal);
// 
// 			if(nDataLen == 8)
// 			{
// 				fValue = sensor_pkt_get_doubleVal(pParaData);
// 			}
// 			else if (nDataLen == 4)
// 			{
// 				fValue = sensor_pkt_get_floatVal(pParaData);
// 			}
// 			else
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报文数据长度【nDataLen=%d】非法！"),nDataLen);
// 				return;
// 			}
// 
// 			p->m_strValue.Format(strFormat,fValue);	
// 		}
// 		else
// 		{
// 			if((nDataLen > 4) && (nDataLen <= 8))
// 			{
// 				__int64 nValue = sensor_pkt_get_int64Val(pParaData);
// 				p->m_strValue.Format(_T("%ld"),nValue);
// 			}
// 			else if (nDataLen <= 4)
// 			{
// 				int nValue = sensor_pkt_get_intVal(pParaData);
// 				p->m_strValue.Format(_T("%d"),nValue);
// 			}
// 			else
// 			{//Blob
// // 				CString strRootPath = CSttMqttCmdExecMngr::GetTaskBlobPath();
// // 				oRTReport.GenerateValueBlobFile(strRootPath,p->m_strID,p->m_strValue);
// // 				sensor_pkg_write_file(p->m_strValue,pParaData);
// 			}
// 		}
// 
// 		if (pModelDataset != NULL)
// 		{
// 			CDvmData *pFind = (CDvmData *)pModelDataset->FindByID(p->m_strID);
// 			if (pFind != NULL)
// 			{
// 				pFind->m_strValue = p->m_strValue;
// 			}
// 		}
// 
// 		nParaIndex++;
// 	}
// }

void CPpPrjDevice::UpdateReportFile(long nRslt,CDvmDataset *pModelDataset)
{
	CCmdExecRslt oExecRslt;
	oExecRslt.GenerateCmdExecRslt(nRslt,pModelDataset);

	CString strReportFile = g_pMqttClientEngineBase->GetDeviceReportFile(this);
	oExecRslt.SaveXmlFile(strReportFile,CCmdExecXmlRWKeys::g_pXmlKeys);
}

CString CPpPrjDevice::GetRTDataInfo()
{
	if (m_pReadAinDs == NULL)
	{
		return _T("");
	}

	CString strInfo = _T("");

	POS pos = m_pReadAinDs->GetHeadPosition();
	CDvmData *pData = NULL;

	while(pos != NULL)
	{
		pData = (CDvmData *)m_pReadAinDs->GetNext(pos);

		strInfo.AppendFormat(_T("%s:%s;"),pData->m_strName,pData->m_strValue);
	}

	return strInfo;
}