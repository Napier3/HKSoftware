#include "stdafx.h"
#include "SensorProtocalEngine.h"
#include "ModbusCRCApi.h"


CSensorProtocalEngine::CSensorProtocalEngine()
{

}

CSensorProtocalEngine::~CSensorProtocalEngine()
{

}

BOOL CSensorProtocalEngine::CheckPkgCRC(BYTE *pBuf,long nLen)
{
	unsigned short nCalcCRC16 = 0;
	unsigned short nRecvCRC16 = 0;
	nCalcCRC16 = Modbus_CRC16(pBuf, nLen-2);
	nRecvCRC16 = (pBuf[nLen-1]<<8) + pBuf[nLen-2];

	if (nCalcCRC16 != nRecvCRC16)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报文CRC校验不通过。【nCalcCRC16=%04X】【nRecvCRC16=%04X】"),nCalcCRC16,nRecvCRC16);
		return FALSE;
	}
	return TRUE;
}

//解析传感器业务数据报文
long CSensorProtocalEngine::PraseSensorPkgInfoHead(BYTE *pBuf,long nLen, SensorPkgInfo &oSensorPkgInfo)
{
	if (!CheckPkgCRC(pBuf,nLen))
	{
		//return PP_PRASE_ErrType_CRCERR;
	}

	__int64 n64SensorID = 0;
	int nParaCnt = 0,nFragInd = 0,nPkgType = 0;
	n64SensorID = sensor_pkg_get_sensorid(pBuf);
	sensor_pkg_get_info(pBuf,nParaCnt,nFragInd,nPkgType);

	oSensorPkgInfo.m_n64SensorID = n64SensorID;
	oSensorPkgInfo.m_nPkgType = nPkgType;

	if (nFragInd == SENSOR_PKG_Frag_YES)
	{//分片
		//调试用
// 		BOOL bRet = CSensorFragMngr::CheckWholeFragSDU(oSensorPkgInfo,pBuf,nLen,n64SensorID,nPkgType,nParaCnt);
// 		if (!bRet)
// 		{
// 			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("收到分片报文，继续接收分片……"));
// 			return PP_PRASE_ErrType_FRAG;
// 		}
			return PP_PRASE_ErrType_FRAG;

		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("收到分片报文，拼包已完成。"));

		//拼包完成
		if (IsPacketCtrlType(nPkgType))
		{//控制报文
			sensor_pkg_get_ctrlinfo(pBuf,oSensorPkgInfo.m_nCtrlType,oSensorPkgInfo.m_nRequestSetFlag);
		}
	}
	else
	{//完整报文
		if (IsPacketCtrlType(nPkgType))
		{//控制报文
			sensor_pkg_get_ctrlinfo(pBuf,oSensorPkgInfo.m_nCtrlType,oSensorPkgInfo.m_nRequestSetFlag);
		}
	}

	return PP_PRASE_SUCCESS;
}

//将报文缓存解析为结构体
long CSensorProtocalEngine::PraseSensorPkgInfo(char *pBuf,long nLen,SensorPkgInfo &oSensorPkgInfo)
{
	long nRet = PraseSensorPkgInfoHead((BYTE *)pBuf,nLen,oSensorPkgInfo);
	if (nRet != 0)
	{//可能是分包未收齐，或校验失败
		return nRet;
	}

	int nParaCnt = 0,nFragInd = 0,nPkgType = 0;
	sensor_pkg_get_info((BYTE *)pBuf,nParaCnt,nFragInd,nPkgType);

	if (oSensorPkgInfo.m_pFragSDUBuf == NULL)
	{//不是分包

		//保存报文缓存
		oSensorPkgInfo.m_pPkgBuf = new BYTE[nLen];
		oSensorPkgInfo.m_nPkgBufLen = nLen;
		memcpy(oSensorPkgInfo.m_pPkgBuf,pBuf,nLen);

		if (IsPacketCtrlType(nPkgType))
		{//控制报文
			//解析参数列表，控制报文的参数列表，从第9个字节开始
			sensor_pkt_get_paraDatas(oSensorPkgInfo.m_pPkgBuf+SENSOR_PKG_INDEX_CTRLDATA
				,oSensorPkgInfo.m_pPkgBuf+oSensorPkgInfo.m_nPkgBufLen-2,oSensorPkgInfo);
		}
		else
		{
			//解析参数列表
			sensor_pkt_get_paraDatas(oSensorPkgInfo.m_pPkgBuf+SENSOR_PKG_INDEX_DATA
				,oSensorPkgInfo.m_pPkgBuf+oSensorPkgInfo.m_nPkgBufLen-2,oSensorPkgInfo);
		}
	}
	else
	{//分包
		//解析参数列表
		sensor_pkt_get_paraDatas(oSensorPkgInfo.m_pFragSDUBuf
			,oSensorPkgInfo.m_pFragSDUBuf+oSensorPkgInfo.m_nFragSDUBufLen,oSensorPkgInfo);
	}

	return PP_PRASE_SUCCESS;
}

// long CSensorProtocalEngine::CalcSensorCtrlPacketLength(CMqttPpProduce *pProduce)
// {
// 	POS pos = pProduce->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	long nLen = SENSOR_PKG_HEADLEN + 1;
// 	while(pos != NULL)
// 	{
// 		pData = (CDvmData *)pProduce->GetNext(pos);
// 
// 		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
// 		{
// 			continue;
// 		}
// 
// 		long nParaType = 0,nDataFieldLen = 0,nDataLen = 0;
// 		pData->GetValueByID(SENSOR_MODEL_ID_ParaType,nParaType);
// 		pData->GetValueByID(SENSOR_MODEL_ID_DataFieldLen,nDataFieldLen);
// 		pData->GetValueByID(SENSOR_MODEL_ID_DataLen,nDataLen);
// 
// 		if (nParaType == 0)
// 		{//表明当前参数格式为：参数值【长度为nDataLen】
// 			nLen += nDataLen;
// 		}
// 		else
// 		{//表明当前参数格式为：参数类型+数据域长度+数据长度+参数值
// 			nLen += 2;
// 
// 			if (nDataFieldLen == 0)
// 			{
// 				nLen += 4;
// 			}
// 			else
// 			{
// 				nLen += (nDataFieldLen + nDataLen);
// 			}
// 		}
// 	}
// 
// 	//crc 2字节
// 	nLen += 2;
// 
// 	return nLen;
// }

// BOOL CSensorProtocalEngine::GenerateSensorPacket(CMqttPpProduce *pProduce,char **ppBuf,long &nLen)
// {
// 	CMqttPpPkg *pPpPkg = pProduce->Getpkg();
// 	ASSERT(pPpPkg != NULL);
// 
// 	long nPacketType = 0;
// 	pPpPkg->GetValueByID(SENSOR_MODEL_ID_PacketType,nPacketType);
// 
// 	nLen = 0;
// 	if (nPacketType != SENSOR_PKG_TYPE_CONTROL)
// 	{//不是控制报文，出错
// 		return FALSE;
// 	}
// 
// 	//是控制报文
// 	int nParaCnt = pProduce->GetCount() - 1;
// 	if (nParaCnt > 15)
// 	{
// 		nParaCnt = 15;
// 	}
// 
// 	long nFragInd = 0,nCtrlType = 0,nRequestSetFlag = 0;
// 	pPpPkg->GetValueByID(SENSOR_MODEL_ID_FragInd,nFragInd);
// 	pPpPkg->GetValueByID(SENSOR_MODEL_ID_CtrlType,nCtrlType);
// 	pPpPkg->GetValueByID(SENSOR_MODEL_ID_RequestSetFlag,nRequestSetFlag);
// 
// 	//计算控制报文长度
// 	nLen = CalcSensorCtrlPacketLength(pProduce);
// 
// 	*ppBuf = new char[nLen + 2];
// 	BYTE *pPkg = (BYTE *)(*ppBuf);
// 
// 	sensor_pkg_set_info(pPkg,nParaCnt,nFragInd,nPacketType);
// 	sensor_pkg_set_ctrlinfo(pPkg,(int)nCtrlType,(int)nRequestSetFlag);
// 
// 	POS pos = pProduce->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	int nOffset = SENSOR_PKG_INDEX_CTRLDATA;
// 	while(pos != NULL)
// 	{
// 		pData = (CDvmData *)pProduce->GetNext(pos);
// 
// 		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
// 		{
// 			continue;
// 		}
// 
// 		long nDataFieldLen = 0,nDataLen = 0,nParaType = 0,nDecimal = 0;
// 		pData->GetValueByID(SENSOR_MODEL_ID_ParaType,nParaType);
// 		pData->GetValueByID(SENSOR_MODEL_ID_Decimal,nDecimal);
// 		pData->GetValueByID(SENSOR_MODEL_ID_DataFieldLen,nDataFieldLen);
// 		pData->GetValueByID(SENSOR_MODEL_ID_DataLen,nDataLen);
// 
// 		if (nParaType == 0)
// 		{//表明当前参数格式为：参数值【长度为nDataLen】
// 	
// 		}
// 		else
// 		{//表明当前参数格式为：参数类型+数据域长度+数据长度+参数值
// 			pPkg[nOffset+1] = nParaType >> 6;
// 			pPkg[nOffset] = ((nParaType & 0xfc) << 2) + (nDataFieldLen & 0x3);
// 			nOffset += 2;
// 
// 			for(int i=0; i<nDataFieldLen; i++)
// 			{
// 				pPkg[nOffset+i] = (nDataLen >> (8*i)) & 0xff;
// 			}
// 			nOffset += nDataFieldLen;
// 		}
// 
// 		if (nDecimal == 0)
// 		{//如果是整形
// 			if (nDataLen > 4)
// 			{
// 				__int64 nData = CString_To_i64(pData->m_strValue);
// 				nOffset = sensor_pkt_set_int64Val(pPkg,nOffset,nData,nDataLen);
// 			}
// 			else
// 			{
// 				int nData = (int)CString_To_long(pData->m_strValue);
// 				nOffset = sensor_pkt_set_intVal(pPkg,nOffset,nData,nDataLen);
// 			}
// 		}
// 		else if((nDataLen == 0) || (nDataLen == 4))
// 		{//如果是浮点
// 			float fData = (float)CString_To_double(pData->m_strValue);
// 			Float_to_Byte(fData,pPkg+nOffset);
// 			nOffset += 4;
// 		}
// 		else if (nDataLen == 8)
// 		{
// 			double fData = CString_To_double(pData->m_strValue);
// 			Double_to_Byte(fData,pPkg+nOffset);
// 			nOffset += 8;
// 		}
// 	}
// 
// 	return TRUE;
// }

void CSensorProtocalEngine::UpdateSensorAppPacket(__int64 n64SensorID,char *pBuf,long nLen)
{
	BYTE *pPkg = (BYTE *)pBuf;
	sensor_pkg_set_sensorid(pPkg,n64SensorID);

	Modbus_ProduceCRC(pPkg,nLen);
}

long sensor_pkt_get_paraData(BYTE *pPkg,long nOffset,SensorParaData *pParaData)
{
	//表明当前参数格式为：参数类型+数据域长度+数据长度+参数值
	pParaData->m_nParaInfo = (pPkg[nOffset+1] << 8) + pPkg[nOffset];

	nOffset += 2;
	pParaData->m_nDataLen = 0;

	int nLengthFlag = pParaData->GetLengthFlag();
	for(int i=0; i<nLengthFlag; i++)
	{
		pParaData->m_nDataLen += pPkg[nOffset+i] << (8*i);
	}
	nOffset += nLengthFlag;

	pParaData->m_pBuff = pPkg + nOffset;
	if (pParaData->m_nDataLen == 0)
	{
		nOffset += 4;
	}
	else
	{
		nOffset += pParaData->m_nDataLen;
	}

	return nOffset;
}

long sensor_pkt_get_paraDatas(BYTE *pPkgDataBegin,BYTE *pPkgDataEnd,SensorPkgInfo &oSensorPkgInfo)
{
	long nReadPos = 0;
	BYTE *pPkgData = pPkgDataBegin;

	if (oSensorPkgInfo.IsQueryMonitorAck() || oSensorPkgInfo.IsSensorResetAck())
	{//如果是查询监测数据应答,或者复位应答
		//当前参数格式为：参数值【长度为nDataLen】
		SensorParaData *pData = new SensorParaData;
		pData->m_nParaInfo = 0;
		pData->m_nDataLen = 1;
		pData->m_pBuff = pPkgData;
		oSensorPkgInfo.vec.push_back(pData);
		nReadPos += pData->m_nDataLen;
	}
	else if (oSensorPkgInfo.IsSensorIDCmdAck())
	{//如果是传感器ID设置应答
		//当前参数格式为：参数值【长度为nDataLen】
		SensorParaData *pData = new SensorParaData;
		pData->m_nParaInfo = 0;
		pData->m_nDataLen = 6;
		pData->m_pBuff = pPkgData;
		oSensorPkgInfo.vec.push_back(pData);
		nReadPos += pData->m_nDataLen;
	}
	else if (oSensorPkgInfo.IsTimestampCmdAck())
	{//如果是传感器ID设置应答
		//当前参数格式为：参数值【长度为nDataLen】
		SensorParaData *pData = new SensorParaData;
		pData->m_nParaInfo = 0;
		pData->m_nDataLen = 4;
		pData->m_pBuff = pPkgData;
		oSensorPkgInfo.vec.push_back(pData);
		nReadPos += pData->m_nDataLen;
	}
	else
	{//参数格式为：参数类型+数据域长度+数据长度+参数值
		while(pPkgData+nReadPos < pPkgDataEnd)
		{//根据报文数据长度遍历解析【而不是参数个数，因为参数个数>=15永远都是15】，这样可以独立解析参数列表
			SensorParaData *pData = new SensorParaData;
			nReadPos = sensor_pkt_get_paraData(pPkgData,nReadPos,pData);
			oSensorPkgInfo.vec.push_back(pData);
		}
// 		for (int i=0; i<nParaCnt; i++)
// 		{
// 			SensorParaData *pData = new SensorParaData;
// 			nReadPos = sensor_pkt_get_paraData(pPkgData,nReadPos,pData);
// 			oSensorPkgInfo.vec.push_back(pData);
// 		}
	}
	
	return nReadPos;
}

// long UpdatePraseValue(SensorPkgInfo &oSensorPkgInfo,CMqttPpPrase *pPrase)
// {
// 	CDvmData *p = (CDvmData *)pPrase->GetAtIndex(1);
// 	if (oSensorPkgInfo.IsQueryMonitorAck() 
// 		|| oSensorPkgInfo.IsSensorResetAck()
// 		|| oSensorPkgInfo.IsTimestampCmdAck())
// 	{//如果是查询监测数据应答,或者复位应答,或者时间参数命令应答
// 		int nValue = sensor_pkt_get_intVal(oSensorPkgInfo.vec[0]);
// 		if (p != NULL)
// 		{
// 			p->m_strValue.Format(_T("%d"),nValue);
// 			return PP_PRASE_SUCCESS;
// 		}
// 		else
// 		{
// 			return PP_PRASE_ErrType_PARANOTMATCH;
// 		}	
// 	}
// 	else if (oSensorPkgInfo.IsSensorIDCmdAck())
// 	{//如果是传感器ID设置应答
// 		__int64 nValue = sensor_pkt_get_int64Val(oSensorPkgInfo.vec[0]);
// 		if (p != NULL)
// 		{
// 			p->m_strValue.Format(_T("%ld"),nValue);
// 			return PP_PRASE_SUCCESS;
// 		}
// 		else
// 		{
// 			return PP_PRASE_ErrType_PARANOTMATCH;
// 		}
// 	}
// 
// 	POS pos = pPrase->GetHeadPosition();
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
// 		long nDecimal = 0,nParaType = 0;
// 		p->GetValueByID(SENSOR_MODEL_ID_Decimal,nDecimal);
// 		p->GetValueByID(SENSOR_MODEL_ID_ParaType,nParaType);
// 
// 		SensorParaData *pParaData = oSensorPkgInfo.FindSensorParaData(nParaType);
// 		if (pParaData == NULL)
// 		{
// 			continue;
// 		}
// 
// 		int nDataLen = pParaData->GetDataLen();
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
// 				return PP_PRASE_ErrType_PARALENERR;
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
// 				CString strValue((char *)pParaData->m_pBuff,nDataLen);
// 				p->m_strValue = strValue;
// 			}
// 		}
// 	}
// 
// 	return PP_PRASE_SUCCESS;
// }

// void UpdateDatasByPrase(CExBaseList &oDvmDatas,CMqttPpPrase *pPrase,BOOL bAddIfNotExist)
// {
// 	POS pos = pPrase->GetHeadPosition();
// 	CDvmData *p = NULL;
// 	CDvmData *pDest = NULL;
// 
// 	while(pos != NULL)
// 	{
// 		p = (CDvmData *)pPrase->GetNext(pos);
// 		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
// 		{
// 			continue;
// 		}
// 
// 		pDest = (CDvmData *)oDvmDatas.FindByID(p->m_strID);
// 		if (pDest == NULL)
// 		{
// 			if (bAddIfNotExist)
// 			{
// 				pDest = (CDvmData *)oDvmDatas.AddNewChild(new CDvmData);
// 				pDest->m_strID = p->m_strID;
// 			}
// 			else
// 			{
// 				continue;
// 			}	
// 		}
// 		else if (pDest->GetClassID() != DVMCLASSID_CDVMDATA)
// 		{
// 			continue;
// 		}
// 
// 		CString strUnit = _T("");
// 		p->GetValueByID(SENSOR_MODEL_ID_Unit,strUnit);
// 
// 		pDest->m_strValue = p->m_strValue;
// 		pDest->m_strUnit = strUnit;
// 	}
// }

//根据报文结构体更新数据集
long UpdateDatasetValue(SensorPkgInfo &oSensorPkgInfo,CDvmDataset *pDataset)
{
	POS pos = pDataset->GetHeadPosition();
	CDvmData *p = NULL;

	while(pos != NULL)
	{
		p = (CDvmData *)pDataset->GetNext(pos);

		long nDecimal = 0,nParaType = 0;
		p->GetValueByID(SENSOR_MODEL_ID_Decimal,nDecimal);
		p->GetValueByID(SENSOR_MODEL_ID_ParaType,nParaType);

		//根据参数类型在报文结构体中查找匹配的参数
		SensorParaData *pParaData = oSensorPkgInfo.FindSensorParaData(nParaType);
		if (pParaData == NULL)
		{
			continue;
		}

		int nDataLen = pParaData->GetDataLen();
		p->SetValue(SENSOR_MODEL_ID_DataLen, (long)nDataLen);
		p->SetValue(SENSOR_MODEL_ID_DataFieldLen, (long)pParaData->GetLengthFlag());

		//根据小数点数判断是否是浮点还是整形
		if (nDecimal > 0)
		{
			double fValue = 0;
			CString strFormat;
			strFormat.Format(_T("%%.%df"),nDecimal);

			if(nDataLen == 8)
			{
				fValue = sensor_pkt_get_doubleVal(pParaData);
			}
			else if (nDataLen == 4)
			{
				fValue = sensor_pkt_get_floatVal(pParaData);
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("报文数据长度【nDataLen=%d】非法！"),nDataLen);
				return PP_PRASE_ErrType_PARALENERR;
			}

			p->m_strValue.Format(strFormat,fValue);	
		}
		else
		{
			if((nDataLen > 4) && (nDataLen <= 8))
			{
				__int64 nValue = sensor_pkt_get_int64Val(pParaData);
				p->m_strValue.Format(_T("%ld"),nValue);
			}
			else if (nDataLen <= 4)
			{
				int nValue = sensor_pkt_get_intVal(pParaData);
				p->m_strValue.Format(_T("%d"),nValue);
			}
			else
			{//Blob
				CString strValue((char *)pParaData->m_pBuff,nDataLen);
				p->m_strValue = strValue;
			}
		}
	}

	return PP_PRASE_SUCCESS;
}