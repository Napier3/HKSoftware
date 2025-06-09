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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰԭʼ�����ļ�(%s)������.")/*g_sLangTxt_Native_CurRawFileNotEx.GetString()*/, strSrcAt02dzFile.GetString());
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰԭʼ�����ļ�(%s)������.")/*g_sLangTxt_Native_CurRawFileNotEx.GetString()*/, strSrcAt02dFile.GetString());
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

	//������
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

	//ͨ��
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

			//����ͨ�����ͣ�������Ӧ��ģ����ͨ�����߿�����ͨ��
			switch (nType)
			{
			case 1://��ѹ
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
			case 2://����
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
			case 4://������
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

			//��m_pCapDeviceMngr�������ҵ���Ӧͨ������comtrade�ļ�ָ�봫�ݸ�m_dwComtradeChData
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

	//����ͨ������
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

	int nFileLength = m_pSrcAt02DFile->GetLength();//at02d�ļ����ݳ���

	int nModuleIndex = 0;
	int nChIndex = 0;
	int nChNum = 0;

	POS posModule = m_pCapDeviceMngr->GetHeadPosition();
	while (posModule)
	{
		CCapDeviceRecord *pRecord = (CCapDeviceRecord*)m_pCapDeviceMngr->GetNext(posModule);
		nModuleIndex++;//���
		nChIndex = pRecord->m_nChannelNum;//��Ӧ�����ͨ������
		nChNum += nChIndex; //�ܵ�ͨ������
	}

	m_nModuleNum = nModuleIndex;
	int nChLength = nChNum * 4 + nModuleIndex * STT_RECORD_COMTRADE_REPORTHEAD_POINT;  //����ͨ�����ȣ�ͨ������*4 + �������*����ͷ����
	int nTotalPoints = (nFileLength + STT_RECORD_COMTRADE_RESERVE_POINT) / nChLength;//�ܵ���������50�����ԣ��
	return nTotalPoints;
}

BOOL SttRecordToComtradeTool::SaveContradeFile(const CString &strComtradeFile, bool bIsDeleteFile)
{
	BYTE pszReadDatas[COMTRADE_RCD_BUFFER_MAX_LEN * 2];
	size_t szRead = 0;
	DWORD dwHeadFrm = 0, dwAt02dPkgLenth = 0, dwTimeValue_s = 0, dwTimeValue_ns = 0, dwChValue = 0;
	long nCurrParseLen = 0, nCurrParseLen_Head = 0, nValidLenth = 0;//�ϴν������һ֡����,�ӱ���ͷ���Ѷ�ȡ���ݵĳ���
	int nTime = 0; int nPoint = 0;

	if (m_pSrcAt02DFile == NULL)
	{
		return false;
	}

	szRead = m_pSrcAt02DFile->Read(pszReadDatas + nCurrParseLen_Head, COMTRADE_RCD_BUFFER_MAX_LEN*sizeof(BYTE));
	
	//���嵱ǰ����
	long* nCurrPoints = new long[m_nModuleNum];
	for (int i = 0; i < m_nModuleNum; ++i)
	{
		nCurrPoints[i] = 0;
	}

	while (szRead > 0)
	{
		nValidLenth = nCurrParseLen_Head + szRead;//��ǰ��ȡ����Ч����
		nCurrParseLen = 0;
		dwHeadFrm = Global_BufferGetDWORD(pszReadDatas);

		while ((dwHeadFrm != STT_AT02_FIXED_HEAD) && (nCurrParseLen < nValidLenth))
		{
			nCurrParseLen++;
			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
		}
		if (dwHeadFrm != STT_AT02_FIXED_HEAD)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰ��ȡ���ĳ���(%u),δ�ҵ�����ͷ,Դ�ļ�(%s)��������."), szRead, m_strSrcAt02dFilePath.GetString());
			return false;
		}
		nCurrParseLen_Head = nCurrParseLen;
		nCurrParseLen += 4;//��������ͷ
		dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);//��ȡ��ǰ֡���ĳ���
		dwAt02dPkgLenth *= 4;//��ǰ֡���ĳ��ȳ���4Ϊʵ�ʱ��ĵĳ���(ԭ���ȵ�λΪ4�ֽ�������)

		while (((nCurrParseLen_Head /*+ nCurrParseLen*/ + dwAt02dPkgLenth + 4) <= nValidLenth)//��ǰ֡������ʼλ�ó���+�������ݳ���+����ͷ����,�ڶ�ȡ����Ч���ȷ�Χ��,����н���,���������ȡ
			&& (dwAt02dPkgLenth < nValidLenth))//��ֹdwAt02dPkgLenthΪ�ر��ֵ,��������ֵ�����
		{
			//nCurrParseLen += 4 + 4 + 4 + 2 + 2;//HEAD + utc-s + Utc-ns + Type +����
			nCurrParseLen += 4; // �������ݰ�ͷ��HEAD
			dwTimeValue_s = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);// ʱ���utc-s
			nCurrParseLen += 4;
			dwTimeValue_ns = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);// ʱ�������Utc-ns
			if (nTime == 0)//��ȡ��һ�����ʱ��
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
			dwAt02dPkgLenth -= 24; // �����Զ������ݽṹ����

			nCurrParseLen += 4;// Type +����
			int nChLen = *(pszReadDatas + nCurrParseLen);//�ɼ�ͨ��������
			int nModulePos = *(pszReadDatas + nCurrParseLen + 1);//ģ��λ��
			
			nCurrParseLen += 1 + 1 + 6;//ͨ����+ģ��λ��+����
			dwChValue = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen); //ͨ������

			int nModuleIndex = 0;
			POS posModule = m_pCapDeviceMngr->GetHeadPosition();
			while (posModule)
			{
				CCapDeviceRecord *pRecord = (CCapDeviceRecord*)m_pCapDeviceMngr->GetNext(posModule);
				if (pRecord->m_nModulePos == nModulePos)
				{

					SetComtradeData(pszReadDatas + nCurrParseLen, pRecord, nCurrPoints[nModuleIndex]);   //�������

					nCurrPoints[nModuleIndex] += 1;
					nPoint = nCurrPoints[nModuleIndex];//��¼��ǰ���ĵ���
					nCurrParseLen += 4 * nChLen;
				}

				nModuleIndex++;
			}

			// ������һ��֡ͷ
			dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);

			while ((dwHeadFrm != STT_AT02_FIXED_HEAD) && (nCurrParseLen < nValidLenth))
			{
				nCurrParseLen++;
				dwHeadFrm = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
			}

			if (dwHeadFrm == STT_AT02_FIXED_HEAD)
			{
				nCurrParseLen_Head = nCurrParseLen;
				nCurrParseLen += 4; // ����֡ͷ
				dwAt02dPkgLenth = Global_BufferGetDWORD(pszReadDatas + nCurrParseLen);
				dwAt02dPkgLenth *= 4; // ��4�ֽڵ�λת��Ϊʵ�ʳ���
			}

			//nPoint++;
		}

		// �ƶ��������е����ݣ�׼����ȡ��һ�����ݰ�
		memmove(pszReadDatas, pszReadDatas + nCurrParseLen_Head, (nValidLenth - nCurrParseLen_Head));
		nCurrParseLen_Head = nValidLenth - nCurrParseLen_Head;
		szRead = m_pSrcAt02DFile->Read(pszReadDatas + nCurrParseLen_Head, COMTRADE_RCD_BUFFER_MAX_LEN * sizeof(BYTE));
	}

	//�������ڱ����ܵ������������ܵ������и���
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

	m_oRcdComtradeFile.SaveComtradeFile(strComtradeFile);//�����comtrade��ʽ

	m_pSrcAt02DFile->close();
	if (bIsDeleteFile)//�ж��Ƿ�Ҫɾ��at02d�ļ������Դ�ļ��������at02dz����Ҫɾ���м��ļ�
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
			dwChDatas = Global_BufferGetDWORD(pszReadChDatas + nCurrParseLen);//ͨ������
			//����ת��Ϊ������
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

			//���ݲ�ͬ��λ���в���ϵ������
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

			switch (pCap->m_nEType)//ͨ������
			{
			case 1://��ѹ
			case 2://����
			{
				CComtradeAnalogData *pAnalogData = (CComtradeAnalogData *)m_oRcdComtradeFile.FindByID(pCap->m_strID);
				SetComtradeAnalogData(pAnalogData,fValue, nCurrPoint);
			}
				break;
			case 3://��Դ������
			case 4://��Դ������
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
	case 3://��Դ������
		if (fChDatas > pCapDeviceRcdCh->m_fSwitchVolt)
		{
			unValue = 1;
		}
		else
		{
			unValue = 0;
		}
		break;
	case 4://��Դ������
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

	unValue <<= (nBinaryIndex % 16); //�ƶ���Ҫ�����λ
	if (unValue == 1)
	{
		pDataBase->m_pnAttachBuffer[nCurrPoint] |= unValue;
	}
	else
	{
		pDataBase->m_pnAttachBuffer[nCurrPoint] &= unValue;
	}

}
