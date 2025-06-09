#include "SttRecordToComtradeTool.h"
#include "../../API/FileApi.h"
#include "../../../RelayTest/Module/RecordTest/SttRcdSocketBufferZip.h"
#include "../../Record/Comtrade/ComtradeRateData.h"
#include "../../Record/Algorithm/AlgorithmAPI.h"

SttRecordToComtradeTool::SttRecordToComtradeTool()
{
	m_pRecordChList = NULL;
	m_pCapDeviceMngr = NULL;
	m_pSrcAt02DFile = NULL;

}


SttRecordToComtradeTool::~SttRecordToComtradeTool()
{
	if (m_pSrcAt02DFile != NULL)
	{
		delete m_pSrcAt02DFile;
		m_pSrcAt02DFile == NULL;
	}

}

void SttRecordToComtradeTool::InitRecordSrcDatas_at02dz(const CString &strSrcAt02dzFile, CCapDeviceMngr *pCapDeviceMngr, CExBaseList *pRecordChList)
{
	if (!IsFileExist(strSrcAt02dzFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前原始数据文件(%s)不存在.")/*g_sLangTxt_Native_CurRawFileNotEx.GetString()*/, strSrcAt02dzFile.GetString());
		return;
	}

	CString strPostfix, strAt02dFilePath;
	strAt02dFilePath = strSrcAt02dzFile;
	strPostfix = ParseFilePostfix(strSrcAt02dzFile);
	strPostfix.MakeLower();

	if (strPostfix == _T("at02dz"))
	{
		strAt02dFilePath = ChangeFilePostfix(strSrcAt02dzFile, _T("at02d"));
		stt_rcd_unzip_file(strSrcAt02dzFile.GetString(), strAt02dFilePath.GetString());
	}

	InitRecordSrcDatas_at02d(strAt02dFilePath, pCapDeviceMngr, pRecordChList);
}

void SttRecordToComtradeTool::InitRecordSrcDatas_at02d(const CString &strSrcAt02dFile, CCapDeviceMngr *pCapDeviceMngr, CExBaseList *pRecordChList)
{
	if (!IsFileExist(strSrcAt02dFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前原始数据文件(%s)不存在.")/*g_sLangTxt_Native_CurRawFileNotEx.GetString()*/, strSrcAt02dFile.GetString());
		return;
	}

	m_strSrcAt02dFilePath = strSrcAt02dFile;
	m_pCapDeviceMngr = pCapDeviceMngr;
	m_pRecordChList = pRecordChList;

	CreateComtradeFile();
}

void SttRecordToComtradeTool::CreateComtradeFile()
{
	long nTotalPoints = 0;
	long nBinaryIndex = 0;
	long nChannelIndex = 0;
	int nType = 0;
	CString strPhase = "";
	double dPrimValue = 0;
	double dSecondValue = 0;
	unsigned short* pBinaryPreBuffer = NULL;

	CComtradeDataBase *pDataBase = NULL;
	CExBaseList* pAnalogList = m_oRcdComtradeFile.GetAnalogs();
	CExBaseList* pBinaryList = m_oRcdComtradeFile.GetBinarys();
	CExBaseList* pRatesList = m_oRcdComtradeFile.GetRates();

	nTotalPoints = GetSrcFilePointNum();
	m_oRcdComtradeFile.m_nTotalPoints = nTotalPoints;
	m_oRcdComtradeFile.m_nBufBeginPos1 = 0;
	m_oRcdComtradeFile.m_nBufLength1 = nTotalPoints;

	//采样率
	POS pos_record = m_pCapDeviceMngr->GetHeadPosition();
	while (pos_record)
	{
		CCapDeviceRecord* pRecord = (CCapDeviceRecord*)m_pCapDeviceMngr->GetNext(pos_record);
		if (pRecord != NULL)
		{
			double dSampleRate = pRecord->m_nSampleRate;

			m_oRcdComtradeFile.m_pnDataPoints = new long[1];
			m_oRcdComtradeFile.m_pdSamRate = new float[1];
			m_oRcdComtradeFile.m_pnDataPoints[0] = nTotalPoints;
			m_oRcdComtradeFile.m_pdSamRate[0] = dSampleRate;
			m_oRcdComtradeFile.m_nSamAmount = 1;

			CComtradeRateData *pRateData = new CComtradeRateData();
			pRateData->m_nSamprate = m_oRcdComtradeFile.m_pdSamRate[0];
			pRateData->m_nEndsamp = m_oRcdComtradeFile.m_pnDataPoints[0];
			m_oRcdComtradeFile.AddNewChild(pRateData);
			pRatesList->AddTail(pRateData);
		}
	}

	//通道
	POS pos = m_pRecordChList->GetHeadPosition();
	CExBaseObject *pObject = NULL;
	while (pos)
	{
		pObject = m_pRecordChList->GetNext(pos);
		if (pObject->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		CDataGroup *pDataGroup = (CDataGroup*)pObject;
		POS posDataGroup = pDataGroup->GetHeadPosition();
		while (posDataGroup)
		{
			CDataGroup *pGroup = (CDataGroup*)pDataGroup->GetNext(posDataGroup);
			POS posGroup = pGroup->GetHeadPosition();

			while (posGroup)
			{
				CDvmData *pData = (CDvmData *)pGroup->GetNext(posGroup);
				if (pData->m_strID == STT_RECORD_COMTRADE_CHANGTYPE)
				{
					strPhase = pData->m_strValue;
				}
				else if (pData->m_strID == STT_RECORD_COMTRADE_PRIMEVALUE)
				{
					dPrimValue = CString_To_double(pData->m_strValue);
				}
				else if (pData->m_strID == STT_RECORD_COMTRADE_SECONDVALUE)
				{
					dSecondValue = CString_To_double(pData->m_strValue);
				}
				else if (pData->m_strID == STT_RECORD_COMTRADE_ETYPE)
				{
					nType = CString_To_long(pData->m_strValue);
				}
			}

			//根据通道类型，创建对应的模拟量通道或者开关量通道
			switch (nType)
			{
			case 1://电压
				pDataBase = new CComtradeAnalogData;
				pDataBase->m_strID = pGroup->m_strID;
				pDataBase->m_strName = pGroup->m_strName;
				nChannelIndex++;
				pDataBase->m_nChannelIndex = nChannelIndex;
				pDataBase->m_strPhaseID = strPhase;
				((CComtradeAnalogData*)pDataBase)->m_strUnit = "V";
				((CComtradeAnalogData*)pDataBase)->m_dCoefValue = 0.1;
				((CComtradeAnalogData*)pDataBase)->m_dZeroValue = 0;
				((CComtradeAnalogData*)pDataBase)->m_dPrimaryValue = dPrimValue;
				((CComtradeAnalogData*)pDataBase)->m_dSecondaryValue = dSecondValue;
				((CComtradeAnalogData*)pDataBase)->m_nTotalPoints = nTotalPoints;
				m_oRcdComtradeFile.AddNewChild(pDataBase);
				pAnalogList->AddTail(pDataBase);
				break;
			case 2://电流
				pDataBase = new CComtradeAnalogData;
				pDataBase->m_strID = pGroup->m_strID;
				pDataBase->m_strName = pGroup->m_strName;
				nChannelIndex++;
				pDataBase->m_nChannelIndex = nChannelIndex;
				pDataBase->m_strPhaseID = strPhase;
				((CComtradeAnalogData*)pDataBase)->m_strUnit = "A";
				((CComtradeAnalogData*)pDataBase)->m_dCoefValue = 0.1;
				((CComtradeAnalogData*)pDataBase)->m_dZeroValue = 0;
				((CComtradeAnalogData*)pDataBase)->m_dPrimaryValue = dPrimValue;
				((CComtradeAnalogData*)pDataBase)->m_dSecondaryValue = dSecondValue;
				((CComtradeAnalogData*)pDataBase)->m_nTotalPoints = nTotalPoints;
				m_oRcdComtradeFile.AddNewChild(pDataBase);
				pAnalogList->AddTail(pDataBase);
				break;
			case 3:
			case 4://开关量
				pDataBase = new CComtradeBinaryData;
				pDataBase->m_strID = pGroup->m_strID;
				pDataBase->m_strName = pGroup->m_strName;
				nChannelIndex++;
				pDataBase->m_nChannelIndex = nChannelIndex;
				pDataBase->m_strPhaseID = strPhase;
				((CComtradeBinaryData*)pDataBase)->m_nTotalPoints = nTotalPoints;
				m_oRcdComtradeFile.AddNewChild(pDataBase);
				pBinaryList->AddTail(pDataBase);
				break;
			}

			//在m_pCapDeviceMngr链表中找到对应通道，将comtrade文件指针传递给m_dwComtradeChData
			CDvmData *pModulePos = (CDvmData*)pGroup->FindByID(STT_RECORD_COMTRADE_MODULEPOS);
			if (pModulePos != NULL)
			{
				CString strModuleName = pModulePos->m_strName;

				POS posModule = m_pCapDeviceMngr->GetHeadPosition();
				while (posModule)
				{
					CCapDeviceRecord *pRecord = (CCapDeviceRecord*)m_pCapDeviceMngr->GetNext(posModule);
					if (strModuleName == pRecord->m_strName)
					{
						CCapDeviceRcdCh* pRcdCh = (CCapDeviceRcdCh*)pRecord->FindByID(pGroup->m_strID);
						pRcdCh->m_dwComtradeChData = (DWORD)pDataBase;
					}
				}
			}
		}		
	}

	//创建通道缓存
	POS pos_file = m_oRcdComtradeFile.GetHeadPosition();

	while (pos_file != NULL)
	{
		CComtradeDataBase* pObj = (CComtradeDataBase*)m_oRcdComtradeFile.GetNext(pos_file);

		if (pObj->IsAnalogData())
		{
			if (m_oRcdComtradeFile.m_nDataFileType)
			{
				pObj->AllocBuffer(nTotalPoints);
			}
			else
			{
				pObj->AllocBuffer(nTotalPoints * 2);
			}
		}
		else
		{
			if (pObj->GetClassID() == GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			if (nBinaryIndex % 16 == 0)
			{
				pObj->AllocBuffer(nTotalPoints);
				pBinaryPreBuffer = pObj->GetBuffer();
			}
			else
			{
				pObj->AttachBuffer(pBinaryPreBuffer);
			}

			nBinaryIndex++;
		}
	}
}

long SttRecordToComtradeTool::GetSrcFilePointNum()
{
	m_pSrcAt02DFile = new CFile;
	if (!m_pSrcAt02DFile->Open(m_strSrcAt02dFilePath, CFile::modeRead))
	{
		return 0;
	}

	int nFileLength = m_pSrcAt02DFile->GetLength();//at02d文件数据长度

	int nModuleIndex = 0;
	int nChIndex = 0;
	int nChNum = 0;

	POS posModule = m_pCapDeviceMngr->GetHeadPosition();
	while (posModule)
	{
		CCapDeviceRecord *pRecord = (CCapDeviceRecord*)m_pCapDeviceMngr->GetNext(posModule);
		nModuleIndex++;//插件
		nChIndex = pRecord->m_nChannelNum;//对应插件的通道数量
		nChNum += nChIndex; //总的通道数量
	}

	m_nModuleNum = nModuleIndex;
	int nChLength = nChNum * 4 + nModuleIndex * STT_RECORD_COMTRADE_REPORTHEAD_POINT;  //所有通道长度：通道数量*4 + 插件数量*报告头长度
	int nTotalPoints = (nFileLength + STT_RECORD_COMTRADE_RESERVE_POINT) / nChLength;//总点数，保留50个点的裕度
	return nTotalPoints;
}

BOOL SttRecordToComtradeTool::SaveContradeFile(const CString &strComtradeFile, bool bIsDeleteFile)
{
	BYTE pszReadDatas[COMTRADE_RCD_BUFFER_MAX_LEN * 2];
	size_t szRead = 0;
	DWORD dwHeadFrm = 0, dwAt02dPkgLenth = 0, dwTimeValue_s = 0, dwTimeValue_ns = 0, dwChValue = 0;
	long nCurrParseLen = 0, nCurrParseLen_Head = 0, nValidLenth = 0;//上次解析最后一帧报文,从报文头到已读取内容的长度
	int nTime = 0; int nPoint = 0;

	if (m_pSrcAt02DFile == NULL)
	{
		return false;
	}

	szRead = m_pSrcAt02DFile->Read(pszReadDatas + nCurrParseLen_Head, COMTRADE_RCD_BUFFER_MAX_LEN*sizeof(BYTE));
	
	//定义当前点数
	long* nCurrPoints = new long[m_nModuleNum];
	for (int i = 0; i < m_nModuleNum; ++i)
	{
		nCurrPoints[i] = 0;
	}

	while (szRead > 0)
	{
		nValidLenth = nCurrParseLen_Head + szRead;//当前读取的有效长度
		nCurrParseLen = 0;
		dwHeadFrm = Global_BufferGetDWORD(pszReadDatas);

		while ((dwHeadFrm != STT_AT02_FIXED_HEAD) && (nCurrParseLen < nValidLenth))
		{
			nCurrParseLen++;
			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
		}
		if (dwHeadFrm != STT_AT02_FIXED_HEAD)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前读取报文长度(%u),未找到报文头,源文件(%s)存在问题."), szRead, m_strSrcAt02dFilePath.GetString());
			return false;
		}
		nCurrParseLen_Head = nCurrParseLen;
		nCurrParseLen += 4;//跳过报文头
		dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);//获取当前帧报文长度
		dwAt02dPkgLenth *= 4;//当前帧报文长度乘以4为实际报文的长度(原长度单位为4字节整数倍)

		while (((nCurrParseLen_Head /*+ nCurrParseLen*/ + dwAt02dPkgLenth + 4) <= nValidLenth)//当前帧报文起始位置长度+报文数据长度+报文头长度,在读取的有效长度范围内,则进行解析,否则继续读取
			&& (dwAt02dPkgLenth < nValidLenth))//防止dwAt02dPkgLenth为特别大值,加上其它值后溢出
		{
			//nCurrParseLen += 4 + 4 + 4 + 2 + 2;//HEAD + utc-s + Utc-ns + Type +保留
			nCurrParseLen += 4; // 跳过数据包头部HEAD
			dwTimeValue_s = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);// 时间戳utc-s
			nCurrParseLen += 4;
			dwTimeValue_ns = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);// 时间戳纳秒Utc-ns
			if (nTime == 0)//获取第一个点的时间
			{
				CString strGpsTime;
				QDateTime dateTime = QDateTime::fromTime_t(dwTimeValue_s);
				dateTime = dateTime.addMSecs((int)(dwTimeValue_ns / 1000000));
				strGpsTime = dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
				SYSTEMTIME tmSys;
				CString_To_SystemTime(strGpsTime, tmSys);
				rcd_InitRtTime(m_oRcdComtradeFile.m_oFirstPointTime, tmSys);
				rcd_InitRtTime(m_oRcdComtradeFile.m_oTrigPointTime, tmSys);
				nTime++;
			}			

			nCurrParseLen += 4;
			dwAt02dPkgLenth -= 24; // 跳过自定义数据结构部分

			nCurrParseLen += 4;// Type +保留
			int nChLen = *(pszReadDatas + nCurrParseLen);//采集通道总数量
			int nModulePos = *(pszReadDatas + nCurrParseLen + 1);//模块位置
			
			nCurrParseLen += 1 + 1 + 6;//通道数+模块位置+保留
			dwChValue = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen); //通道数据

			int nModuleIndex = 0;
			POS posModule = m_pCapDeviceMngr->GetHeadPosition();
			while (posModule)
			{
				CCapDeviceRecord *pRecord = (CCapDeviceRecord*)m_pCapDeviceMngr->GetNext(posModule);
				if (pRecord->m_nModulePos == nModulePos)
				{

					SetComtradeData(pszReadDatas + nCurrParseLen, pRecord, nCurrPoints[nModuleIndex]);   //数据填充

					nCurrPoints[nModuleIndex] += 1;
					nPoint = nCurrPoints[nModuleIndex];//记录当前报文点数
					nCurrParseLen += 4 * nChLen;
				}

				nModuleIndex++;
			}

			// 查找下一个帧头
			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);

			while ((dwHeadFrm != STT_AT02_FIXED_HEAD) && (nCurrParseLen < nValidLenth))
			{
				nCurrParseLen++;
				dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
			}

			if (dwHeadFrm == STT_AT02_FIXED_HEAD)
			{
				nCurrParseLen_Head = nCurrParseLen;
				nCurrParseLen += 4; // 跳过帧头
				dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
				dwAt02dPkgLenth *= 4; // 从4字节单位转换为实际长度
			}

			//nPoint++;
		}

		// 移动缓冲区中的数据，准备读取下一个数据包
		memmove(pszReadDatas, pszReadDatas + nCurrParseLen_Head, (nValidLenth - nCurrParseLen_Head));
		nCurrParseLen_Head = nValidLenth - nCurrParseLen_Head;
		szRead = m_pSrcAt02DFile->Read(pszReadDatas + nCurrParseLen_Head, COMTRADE_RCD_BUFFER_MAX_LEN * sizeof(BYTE));
	}

	//根据现在报文总点数，将估算总点数进行更新
	CExBaseList *pAnalogList = m_oRcdComtradeFile.GetAnalogs();
	CComtradeAnalogData *pAnalogData = NULL;
	POS pos_Analog = pAnalogList->GetHeadPosition();
	while (pos_Analog)
	{
		pAnalogData = (CComtradeAnalogData *)pAnalogList->GetNext(pos_Analog);
		pAnalogData->m_nTotalPoints = nPoint;
	}

	CExBaseList *pBinaryList = m_oRcdComtradeFile.GetBinarys();
	CComtradeBinaryData *pBinaryData = NULL;
	POS pos_Binary = pBinaryList->GetHeadPosition();
	while (pos_Binary)
	{
		pBinaryData = (CComtradeBinaryData *)pBinaryList->GetNext(pos_Binary);
		pBinaryData->m_nTotalPoints = nPoint;
	}

	m_oRcdComtradeFile.m_pnDataPoints[0] = nPoint;
	m_oRcdComtradeFile.m_nTotalPoints = nPoint;

	m_oRcdComtradeFile.SaveComtradeFile(strComtradeFile);//保存成comtrade格式

	m_pSrcAt02DFile->close();
	if (bIsDeleteFile)//判断是否要删除at02d文件，如果源文件传入的是at02dz，则要删除中间文件
	{
		X_DeleteFile(m_strSrcAt02dFilePath);
	}
	return true;
}

void SttRecordToComtradeTool::SetComtradeData(BYTE *pszReadChDatas, CCapDeviceRecord *pCapDeviceRecord, int nCurrPoint)
{
	DWORD dwChDatas = 0;
	long nCurrParseLen = 0;
	long nBinaryIndex = 0;
	float fValue = 0;

	POS pos = pCapDeviceRecord->GetHeadPosition();
	while (pos)
	{
		CCapDeviceRcdCh* pCap = (CCapDeviceRcdCh*)pCapDeviceRecord->GetNext(pos);
		if (pCap->m_dwComtradeChData != NULL)
		{
			dwChDatas = Global_BufferGetDWORD(pszReadChDatas + nCurrParseLen);//通道数据
			//整数转换为浮点数
			if (dwChDatas >= 0x80000000)
			{
				dwChDatas -= 0x80000000;
				dwChDatas = dwChDatas >> 16;
				fValue = dwChDatas / 32767.0;
			}
			else
			{
				dwChDatas = 0xFFFF0000 - dwChDatas;
				dwChDatas -= 0x80000000;
				dwChDatas = dwChDatas >> 16;
				fValue = dwChDatas / 32767.0;
				fValue = 0 - fValue;
			}

			//根据不同档位进行补偿系数处理
			switch (pCap->m_nMeasGear)
			{
			case 4:
				fValue = fValue / 2000.0;
				break;
			case 3:
				fValue = fValue / 380.5668;
				break;
			case 2:
				fValue = fValue / 54.4105;
				break;
			case 1:
				fValue = fValue / 5.982;
				break;
			case 0:
				fValue = fValue / (0.9995002 * 1.07);
				break;
			}

			fValue = fValue*(505.1 * 2.048);

			switch (pCap->m_nEType)//通道类型
			{
			case 1://电压
			case 2://电流
			{
				CComtradeAnalogData *pAnalogData = (CComtradeAnalogData *)m_oRcdComtradeFile.FindByID(pCap->m_strID);
				SetComtradeAnalogData(pAnalogData,fValue, nCurrPoint);
			}
				break;
			case 3://有源开关量
			case 4://无源开关量
			{
				CComtradeBinaryData *pBinaryData = (CComtradeBinaryData *)m_oRcdComtradeFile.FindByID(pCap->m_strID);
				SetComtradeBinaryData(pBinaryData, pCap, fValue, nBinaryIndex, nCurrPoint);
				nBinaryIndex++;
			}
				break;
			}
		}

		nCurrParseLen += 4;
	}
}

void SttRecordToComtradeTool::SetComtradeAnalogData(CComtradeAnalogData *pDataBase, float fChDatas, int nCurrPoint)
{
	int *pnAttachBufferValue = (int *)pDataBase->m_pnAttachBuffer;

	double dCurrPointValue = (fChDatas - pDataBase->m_dZeroValue) / pDataBase->m_dCoefValue;

	if (m_oRcdComtradeFile.m_nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		pDataBase->m_pnAttachBuffer[nCurrPoint] = DoubleToUShortPointValue(dCurrPointValue);
	}
	else
	{

		pnAttachBufferValue[nCurrPoint] = static_cast<int>(DoubleToLongPointValue(dCurrPointValue));
	}

	if ((dCurrPointValue)>32767)
	{
		double dNewCoef = 1.2* (pDataBase->m_dCoefValue) * dCurrPointValue / 32767;
		pDataBase->AdjustCoefValue(pDataBase->m_nTotalPoints, dNewCoef);
	}

}

void SttRecordToComtradeTool::SetComtradeBinaryData(CComtradeBinaryData *pDataBase, CCapDeviceRcdCh *pCapDeviceRcdCh, float fChDatas, long nBinaryIndex, int nCurrPoint)
{
	unsigned short unValue = 0;
	switch (pCapDeviceRcdCh->m_nEType)
	{
	case 3://有源开关量
		if (fChDatas > pCapDeviceRcdCh->m_fSwitchVolt)
		{
			unValue = 1;
		}
		else
		{
			unValue = 0;
		}
		break;
	case 4://无源开关量
		if (fChDatas > 6.23)
		{
			unValue = 0;
		}
		else
		{
			unValue = 1;
		}
		break;
	}

	unValue <<= (nBinaryIndex % 16); //移动到要保存的位
	if (unValue == 1)
	{
		pDataBase->m_pnAttachBuffer[nCurrPoint] |= unValue;
	}
	else
	{
		pDataBase->m_pnAttachBuffer[nCurrPoint] &= unValue;
	}

}
