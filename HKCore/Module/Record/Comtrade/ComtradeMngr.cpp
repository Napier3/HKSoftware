// ComtradeMngr.cpp: implementation of the CComtradeMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComtradeMngr.h"
#include <math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "../../MemBuffer/BufferBase.h"
#include "../../API/FileApi.h"
#include "../../GpsPcTime/GpsPcTime.h"
#include "ComtradeRateData.h"
#include "../../API/MathApi.h"

#ifdef _PSX_IDE_QT_ 
#include <QDebug>
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CRcdComtradeFile::g_pszKeyBinary	   = "BINARY";
const char* CRcdComtradeFile::g_pszKeyASCII	   = "ASCII";
const char* CRcdComtradeFile::g_pszKeyCfg		   = "CFG";
const char* CRcdComtradeFile::g_pszKeyDat		   = "DAT";


CRcdComtradeFile::CRcdComtradeFile(BOOL bCreateBuffer)
{
	m_nBufBeginPos1	= -1;
	m_nBufBeginPos2	= -1;
	m_nBufLength1	= -1;
	m_nBufLength2	= -1;

	m_strBasicInfo   = "RecordTest,1,1999";
	m_pdSamRate		 = NULL;
	m_pnDataPoints	 = NULL;

	m_nSamAmount	 = 1;
	m_dFreq			 = 50.0;
	m_dTimeCoef		 = 1;
	m_nDataFileType	 = COMTRADE_DATAFILE_TYPE_BINARY;

	m_nComtradeVersion = 1999;

	m_nAllChs = 0;
	m_nAnalogs	= 0;
	m_nBinarys	= 0;
	memset(&m_oFirstPointTime,0,sizeof(RTTIME));
	memset(&m_oTrigPointTime,0,sizeof(RTTIME));

	m_strStationName	= "PONOCO";
	m_strRecordingDeviceID		= _T("Devcie");

	m_nSaveGap = 1;
	m_nBufferLen = 0;
	m_bCreateBuffer = bCreateBuffer;
	m_nTotalPoints = 0;

	//2021-1-17  lijunqing
	m_nRefCount = 0;
}

CRcdComtradeFile::~CRcdComtradeFile()
{
	BufferClear();

	m_listAnalog.RemoveAll();
	m_listBinary.RemoveAll();
	m_listRates.RemoveAll();

}

void CRcdComtradeFile::AddRef()
{
	m_nRefCount++;
}

void CRcdComtradeFile::Release()
{
	if (m_nRefCount == 0)
	{
		return;
	}

	m_nRefCount--;
}

long CRcdComtradeFile::GetUCount()
{
	return GetChCount(_T("V")) + GetChCount(_T("v")) ;
}

long CRcdComtradeFile::GetICount()
{
	return GetChCount(_T("A")) + GetChCount(_T("a")) ;
}

long CRcdComtradeFile::GetChCount(const CString &strUnit)
{
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CComtradeAnalogData *)m_listAnalog.GetNext(pos);

		if (p->m_strUnit == strUnit)
		{
			nCount++;
		}
	}

	return nCount;
}

// CComtradeAnalogData* CRcdComtradeFile::GetAnalogData(long nCh_Index, const CString &strUnit)
// {
// 	if (nCh_Index<=0)
// 	{
// 		return NULL;
// 	}
// 
// 	POS pos = m_listAnalog.GetHeadPosition();
// 	CComtradeAnalogData *p = NULL;
// 	long nCurIndex = 1;
// 
// 	while (pos != NULL)
// 	{
// 		p = (CComtradeAnalogData *)m_listAnalog.GetNext(pos);
// 
// 		if (p->m_strUnit == strUnit)
// 		{
// 			if (nCurIndex == nCh_Index)
// 			{
// 				return p;
// 			}
// 			else if (nCurIndex>nCh_Index)
// 			{
// 				break;
// 			}
// 
// 			nCurIndex++;
// 		}
// 	}
// 
// 	return NULL;
// }

CComtradeAnalogData* CRcdComtradeFile::GetAnalogDataByChIndex(long nCh_Index,BOOL bTypeU)
{
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pCurObj = NULL;
	CComtradeAnalogData *pAnalogChFind = NULL;

	while(pos)
	{
		pCurObj = (CComtradeAnalogData*)m_listAnalog.GetNext(pos);

		if (pCurObj->IsAnalogUData() != bTypeU)
		{
			continue;
		}

		if (((CComtradeAnalogData *)pCurObj)->m_nChannelIndex == nCh_Index)
		{
			pAnalogChFind = pCurObj;
			break;
		}
	}

	return pAnalogChFind;
}

CComtradeAnalogData* CRcdComtradeFile::GetAnalogDataByChIndex(long nCh_Index)
{
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pCurObj = NULL;
	CComtradeAnalogData *pAnalogChFind = NULL;

	while(pos)
	{
		pCurObj = (CComtradeAnalogData*)m_listAnalog.GetNext(pos);

		if (((CComtradeAnalogData *)pCurObj)->m_nChannelIndex == nCh_Index)
		{
			pAnalogChFind = pCurObj;
			break;
		}
	}

	return pAnalogChFind;
}

CComtradeAnalogData* CRcdComtradeFile::GetAnalogDataByIndex(long nIndex)
{
	return (CComtradeAnalogData*)m_listAnalog.GetAtIndex(nIndex);
}

CComtradeAnalogData* CRcdComtradeFile::FindAnalogDataByChID(const CString &strID)
{
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pCurObj = NULL;
	CComtradeAnalogData *pAnalogChFind = NULL;

	while(pos)
	{
		pCurObj = (CComtradeAnalogData*)m_listAnalog.GetNext(pos);

		if (pCurObj->m_strID == strID)
		{
			pAnalogChFind = pCurObj;
			break;
		}
	}

	return pAnalogChFind;
}

CComtradeAnalogData* CRcdComtradeFile::FindAnalogDataByChType(const CString &strChType, long nIndex)
{
	CExBaseList listTemp;
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pCurObj = NULL;
	CComtradeAnalogData *pAnalogChFind = NULL;

	while(pos)
	{
		pCurObj = (CComtradeAnalogData*)m_listAnalog.GetNext(pos);

		if (pCurObj->MatchType(strChType))
		{
			listTemp.AddTail(pCurObj);
		}
	}

	if (nIndex < 0)
	{
		nIndex = 0;
	}

	pAnalogChFind = (CComtradeAnalogData *)listTemp.GetAtIndex(nIndex);
	listTemp.RemoveAll();

	return pAnalogChFind;
}

long CRcdComtradeFile::GetUOrder()
{
	return GetChOrder(_T("V"));
}

long CRcdComtradeFile::GetIOrder()
{
	return GetChOrder(_T("A"));
}

long CRcdComtradeFile::GetChOrder(const CString &strUnit)
{
	long nCount = m_listAnalog.GetCount();

	if (nCount == 0)
	{
		return -1;
	}

	long nIndex = 0;
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *p = NULL;
	long nFirstOrder = 0;
	BYTE *pBuffer = new BYTE [nCount];
	ZeroMemory(pBuffer, nCount);
	long nBeginPos = 0;

	while (pos != NULL)
	{
		p = (CComtradeAnalogData *)m_listAnalog.GetNext(pos);

		if (p->m_strUnit == strUnit)
		{
			pBuffer[nIndex] = 1;
		}

		nIndex++;
	}

	while (nBeginPos < nCount)
	{
		for (; nBeginPos<nCount; nBeginPos++)
		{
			if (pBuffer[nBeginPos] == 1)
			{
				nFirstOrder += nBeginPos;
				break;
			}
		}

		for (nIndex=nBeginPos+1; nIndex<nCount; nIndex++)
		{
			if (pBuffer[nIndex] != pBuffer[nIndex-1])
			{
				break;
			}
		}

		nBeginPos = nIndex;
	}

	delete []pBuffer;

	return nFirstOrder;
}



void CRcdComtradeFile::Init()
{
	DeleteAll();
	m_listAnalog.RemoveAll();
	m_listBinary.RemoveAll();
	m_listRates.RemoveAll();

	m_nBufBeginPos1	= -1;
	m_nBufBeginPos2	= -1;
	m_nBufLength1	= -1;
	m_nBufLength2	= -1;

	if (m_pdSamRate != NULL)
	{
		delete []m_pdSamRate;
		m_pdSamRate = NULL;
	}

	if (m_pnDataPoints != NULL)
	{
		delete []m_pnDataPoints;
		m_pnDataPoints = NULL;
	}

	m_nAnalogs	= 0;
	m_nBinarys	= 0;
	memset(&m_oFirstPointTime,0,sizeof(RTTIME));
	memset(&m_oTrigPointTime,0,sizeof(RTTIME));
}

//����Comtrade��Ϣ
void CRcdComtradeFile::BufferClear()
{
	Init();
}

void CRcdComtradeFile::ClearDataBuffer()
{
	POS pos = GetHeadPosition();
	CComtradeDataBase* pObj = NULL;
	long nIndex = -1;

	while (pos != NULL)
	{
		pObj = (CComtradeDataBase*)GetNext(pos);

		if (pObj->IsAnalogData())
		{
			pObj->ClearBuffer();
		}
		else
		{
			if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}
			CComtradeBinaryData* pBinary = (CComtradeBinaryData*)pObj;
			long nWordIndex = pBinary->m_nDataIndex / 16;

			if (nWordIndex != nIndex)
			{
				nIndex = nWordIndex;
				pBinary->ClearBuffer();
			}	
		}
	}
}

void CRcdComtradeFile::ResetDataBuffer()
{
	POS pos = GetHeadPosition();
	CComtradeDataBase* pObj = NULL;
	long nIndex = -1;

	while (pos != NULL)
	{
		pObj = (CComtradeDataBase*)GetNext(pos);

		if (pObj->IsAnalogData())
		{
			pObj->GetMemBuffer_UShort()->Init();
		}
		else
		{
			if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			CComtradeBinaryData* pBinary = (CComtradeBinaryData*)pObj;
			long nWordIndex = pBinary->m_nDataIndex / 16;

			if (nWordIndex != nIndex)
			{
				nIndex = nWordIndex;
				pBinary->GetMemBuffer_UShort()->Init();
			}	
		}
	}
}

void CRcdComtradeFile::UpdateSmpRatesList()
{
	m_listRates.RemoveAll();
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == GLOBALCLASSID_CCOMTRADERATEDATA)
		{
			Delete(pCurObj);
		}
	}

	CComtradeRateData *pNew = NULL;

	for (int nSamIndex = 0;nSamIndex<m_nSamAmount;nSamIndex++)
	{
		pNew = new CComtradeRateData();
		pNew->m_nSamprate = m_pdSamRate[nSamIndex];
		pNew->m_nEndsamp = m_pnDataPoints[nSamIndex];
		AddNewChild(pNew);
		m_listRates.AddTail(pNew);
	}
}

void CRcdComtradeFile::GetChannelAmount()
{
	POS pos = GetHeadPosition();
	m_nAnalogs	= 0;
	m_nBinarys	= 0;
	m_nAllChs = 0;
	CComtradeDataBase* pObj = NULL;

	while (pos != NULL)
	{
		pObj = (CComtradeDataBase*)GetNext(pos);
		if (pObj == NULL)
		{
			break;
		}
		if (pObj->IsAnalogData())
		{
			m_nAnalogs++;
		}
		else
		{
			if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}
			m_nBinarys++;
		}
		m_nAllChs++;
	}
}

void CRcdComtradeFile::CalMinMaxValue()
{
	CComtradeDataBase *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CComtradeDataBase *)GetNext(pos);

		if (p->IsAnalogData())
		{
			((CComtradeAnalogData*)p)->CalMinMaxValue(m_nTotalPoints);
		}
	}
}

void CRcdComtradeFile::UpdateCoef_SpecialSmpRate()
{
	if (m_nDataFileType != COMTRADE_DATAFILE_TYPE_BINARY)
	{
		return;
	}

	CComtradeDataBase *p = NULL;
	double dCurFreq = m_dFreq;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CComtradeDataBase *)GetNext(pos);

		if (p->IsAnalogData())
		{
			long nPtBeginIndex = 0;
			double dMaxValue = 0.0f, dMinValue = 0.0f;

			for (int nIndex = 0; nIndex < m_nSamAmount; nIndex++)
			{
				if ((fabs(dCurFreq * 2 - m_pdSamRate[nIndex]) < 0.0001) || (fabs(dCurFreq - m_pdSamRate[nIndex]) < 0.0001))
				{
					((CComtradeAnalogData*)p)->GetMaxMinValue(nPtBeginIndex, m_pnDataPoints[nIndex],  dMaxValue, dMinValue);
				}

				nPtBeginIndex += m_pnDataPoints[nIndex];
			}

			if (fabs(dMaxValue) < fabs(dMinValue))
			{
				dMaxValue = fabs(dMinValue);
			}

			((CComtradeAnalogData*)p)->UpdateCoef_SpecialSmpRate(dMaxValue);
		}
	}
}

void CRcdComtradeFile::ResetCoefZeroValue()
{
	CComtradeDataBase *p = NULL;
	POS pos = GetHeadPosition();
	CComtradeAnalogData *pComtradeAnalogData = NULL;

	while (pos != NULL)
	{
		p = (CComtradeDataBase *)GetNext(pos);

		if (p->IsAnalogData())
		{
			pComtradeAnalogData = (CComtradeAnalogData *)p;
			pComtradeAnalogData->m_dCoefValue = pComtradeAnalogData->m_dCoefValueBK;
			pComtradeAnalogData->m_dZeroValue = pComtradeAnalogData->m_dZeroValueBK;
		}
	}
}

//strFilePath���ļ�·������������׺��
void CRcdComtradeFile::SaveComtradeFile(const CString& strFilePath)
{
	if (m_nBufLength1 < 1)
	{
		return;
	}


	switch(m_nComtradeVersion)
	{
	case 1991:
		break;
	case 1999:
		{
			SaveCFGFile(strFilePath);

			if (m_nDataFileType == COMTRADE_DATAFILE_TYPE_ASCII)
			{
				SaveDataAsASIIMode(strFilePath);
			}
			else
			{
				SaveDataAsBINARYMode(strFilePath);
			}
			SaveMrttFile(strFilePath);
		}
		break;
	}
}

void CRcdComtradeFile::SaveDatFile(const CString& strFilePath)
{
	if (m_nBufLength1 < 1)
	{
		return;
	}

	if (m_nDataFileType == COMTRADE_DATAFILE_TYPE_ASCII)
	{
		SaveAsciiDatDataFile(strFilePath);
	}
	else
	{
		SaveBinaryDatDataFile(strFilePath);
	}
}

void CRcdComtradeFile::SaveMrttFile(const CString& strFilePath)
{
	// 	CMR1200BaseApp *//pApp = (CMR1200BaseApp *)AfxGetApp();
	// 	//g_theRecordApp.WriteMrttFile(strFilePath);
}

void CRcdComtradeFile::SaveCFGFile(const CString& strFilePath)
{
	FILE* pFile = NULL;
	CString strCFGFilePath;
	//strCFGFilePath.Format(_T("%s.%s"),strFilePath,g_pszKeyCfg);
	strCFGFilePath = strFilePath;

	CString strTempKey = CString(g_pszKeyCfg);
	strCFGFilePath = ChangeFilePostfix(strCFGFilePath, strTempKey);
	CString strTemp;
	char pszCFGFilePath[MAX_PATH*2];
	CString_to_char(strCFGFilePath, pszCFGFilePath);
	pFile = fopen(pszCFGFilePath,"w");
	long nIndex = 0;
	//Edit by lipenghui 2020-04-15
	m_strBasicInfo.Format(_T("%s,%s,%d"),m_strStationName.GetString(),m_strRecordingDeviceID.GetString(),m_nComtradeVersion);

	// 	long nLen = m_nBufLength1;
	// 
	// 	if (m_nBufLength2 > 0)
	// 	{
	// 		nLen += m_nBufLength2;
	// 	}
	// 
	// 	m_pnDataPoints[0] = nLen / m_nSaveGap;

	if (pFile != NULL)
	{
		fprintf(pFile,"%s\n",m_strBasicInfo.GetString());//վ������Ϣ
		GetChannelAmount();

		if (m_oTrigPointTime.wDay == 0 || m_oTrigPointTime.wMonth ==0)
		{
			CTime oTime = CTime::GetCurrentTime();
			m_oTrigPointTime.wYear	 = oTime.GetYear();
			m_oTrigPointTime.wMonth  = oTime.GetMonth();
			m_oTrigPointTime.wDay    = oTime.GetDay();
			m_oTrigPointTime.wHour   = oTime.GetHour();
			m_oTrigPointTime.wMinute = oTime.GetMinute();
			m_oTrigPointTime.wSecond = oTime.GetSecond();
			m_oTrigPointTime.wMicroseconds = 0;
			m_oTrigPointTime.wMilliseconds = 0;

			m_oFirstPointTime.wYear	 = oTime.GetYear();
			m_oFirstPointTime.wMonth  = oTime.GetMonth();
			m_oFirstPointTime.wDay    = oTime.GetDay();
			m_oFirstPointTime.wHour   = oTime.GetHour();
			m_oFirstPointTime.wMinute = oTime.GetMinute();
			m_oFirstPointTime.wSecond = oTime.GetSecond();
			m_oFirstPointTime.wMicroseconds = 0;
			m_oFirstPointTime.wMilliseconds = 0;
		}

		fprintf(pFile,"%d,%dA,%dD\n",m_nBinarys + m_nAnalogs, m_nAnalogs, m_nBinarys);//ͨ������
		//����ͨ������Ϣ
		POS pos = GetHeadPosition();
		CComtradeDataBase* pObj = NULL;

		while (pos != NULL)
		{
			pObj = (CComtradeDataBase*)GetNext(pos);

			if (pObj->GetClassID() == GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			pObj->SaveChanInfo(strTemp);
			fprintf(pFile,"%s\n",strTemp.GetString());
		}

		fprintf(pFile,"%.3f\n",m_dFreq);//����Ƶ��

		//��������Ϣ
		fprintf(pFile,"%d\n",m_nSamAmount);//����������

		for(nIndex = 0; nIndex < m_nSamAmount ; nIndex++)
		{
			fprintf(pFile,"%.3f,%d\n",(m_pdSamRate[nIndex] / m_nSaveGap), m_pnDataPoints[nIndex]);//����������
		}
		//��һ�����ʱ��
		double dSec = m_oFirstPointTime.wSecond + m_oFirstPointTime.wMilliseconds / 1000.0 + m_oFirstPointTime.wMicroseconds / 1000000.0;
		strTemp.Format(_T("%02d/%02d/%d,%02d:%02d:%.6f"),m_oFirstPointTime.wDay,m_oFirstPointTime.wMonth,
			m_oFirstPointTime.wYear,m_oFirstPointTime.wHour,m_oFirstPointTime.wMinute,dSec);
		fprintf(pFile,"%s\n",strTemp.GetString());
		//������ʱ��
		dSec = m_oTrigPointTime.wSecond + m_oTrigPointTime.wMilliseconds / 1000.0 + m_oTrigPointTime.wMicroseconds / 1000000.0;
		strTemp.Format(_T("%02d/%02d/%d,%02d:%02d:%.6f"),m_oTrigPointTime.wDay,m_oTrigPointTime.wMonth,
			m_oTrigPointTime.wYear,m_oTrigPointTime.wHour,m_oTrigPointTime.wMinute,dSec);
		fprintf(pFile,"%s\n",strTemp.GetString());

		//�ļ���ʽ
		if (m_nDataFileType == COMTRADE_DATAFILE_TYPE_ASCII)
		{
			fprintf(pFile,"%s\n",g_pszKeyASCII);
		}
		else
		{
			fprintf(pFile,"%s\n",g_pszKeyBinary);
		}

		fprintf(pFile,"%.3f\n",m_dTimeCoef);
		///////
		fclose(pFile);
		pFile = NULL;
	}

	m_nSaveGap = 1;//ʹ�����ʱ��ʵ�ʲ�����
	m_oTrigPointTime.wMonth = 0;
}

void CRcdComtradeFile::SaveDataAsBINARYMode(const CString& strFilePath)
{
	//	CMR1200BaseApp *//pApp = (CMR1200BaseApp*)AfxGetApp();
	long nIndex = 0;
	//	long nTotalPoints = 0;

	// 	if (m_nBufLength1 > 0)
	// 	{
	// 		nTotalPoints += m_nBufLength1;
	// 	}
	// 
	// 	if (m_nBufLength2 > 0)
	// 	{
	// 		nTotalPoints += m_nBufLength2;
	// 	}

	long nSteps = 20;
	long nStepPoints = m_nTotalPoints / nSteps;
	long nStep = 0;

	if (nStepPoints > 65536)
	{
		nStepPoints = 65536;
		nStepPoints = m_nTotalPoints / nSteps;
		nSteps = m_nTotalPoints / nStepPoints + 1;
	}

	if (nStepPoints * nSteps < m_nTotalPoints)
	{
		nSteps++;
	}

	long nStepIndex = 0;

	FILE* pFile = NULL;
	CString strDatFilePath;
	//strDatFilePath.Format(_T("%s.%s"),strFilePath,g_pszKeyDat);
	strDatFilePath = strFilePath;

	CString strTempKey = CString(g_pszKeyDat);
	strDatFilePath = ChangeFilePostfix(strFilePath, strTempKey);

	CString strTemp;
	char pszDatFilePath[MAX_PATH];
	CString_to_char(strDatFilePath, pszDatFilePath);
	pFile = fopen(pszDatFilePath,"wb");
	unsigned short unCurrentData = 0;
	CComtradeDataBase* pObj = NULL;
	POS pos = NULL;
	long nBinaryIndex = 0;//����ͨ������
	WORD wBinaryValue = 0;

	//	//g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_SAVE_RECORDFILE, 0, MAKELONG(nStep, nSteps));

	if (pFile == NULL)
		return;

	DWORD dwIndex = 1;
	DWORD dwmTimestamp = 0xFFFFFFFF; //������ʱ���ˣ���Ϊ�����ʺ͸����������µĵ�������
	nIndex = 0;
	unsigned short unCurBinaryData = 0;//zhouhj ��Ϊֻ�е�һ��������ͨ����¼������������16��ͨ����״ֵ̬���轫���¼

	/////// ��������	
	//		if (m_nBufLength1 > 0)
	for(nIndex = 0 ; nIndex < m_nTotalPoints; nIndex += m_nSaveGap)
	{
		dwmTimestamp = GetCurPointTimeStamp(nIndex);
		fwrite(&dwIndex,4,1,pFile);
		fwrite(&dwmTimestamp,4,1,pFile);
		nBinaryIndex = 0;
		wBinaryValue = 0;
		unCurBinaryData = 0;
		pos = GetHeadPosition();

		while (pos != NULL)
		{
			pObj = (CComtradeDataBase*)GetNext(pos);

			if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			unsigned short* pBuffer = pObj->GetBuffer() ;

			//���ڿ�����ͨ���ǹ���buffer������ͨ��û��ʵ�ʻ�����,����Խ���ж�
			if(pObj->m_nTotalPoints <= 0)
			{
				continue;
			}

			unCurrentData = *(pBuffer + m_nBufBeginPos1 + nIndex);

			if (pObj->IsAnalogData())
			{				
				if (unCurrentData == 0x8000)//0x8000 ����
				{
					unCurrentData = 0x8001;			
				}

				fwrite(&unCurrentData,2,1,pFile);
			}
			else // ��Ϊ�������ǰ�����ģ��󿪹ص�˳�����
			{
				if ((nBinaryIndex%16) == 0)
				{
					unCurBinaryData = unCurrentData;
				}
				else
				{
					unCurrentData = unCurBinaryData;
				}

				CComtradeBinaryData* pBinary = (CComtradeBinaryData*)pObj;
				unCurrentData >>= (pBinary->m_nDataIndex);//���Ƶ�0λ
				unCurrentData &= 0x1;//����0λ������λ��Ϊ0
				unCurrentData <<= (nBinaryIndex % 16); //�ƶ���Ҫ�����λ
				wBinaryValue |= unCurrentData;

				if ((nBinaryIndex%16) == 15) //zhouhj 20200912 nBinaryIndexΪ�ܵĿ�����Index
				{
					//							nBinaryIndex = 0;  zhouhj  20200911 �˴���������Ϊ0�����򿪹���ȱ��һ��ͨ��
					fwrite(&wBinaryValue,2,1,pFile);
					wBinaryValue = 0;
				}
				else
				{
					if (nBinaryIndex == m_nBinarys - 1)//����ͨ����
					{
						fwrite(&wBinaryValue,2,1,pFile);
					}
				}

				nBinaryIndex++;
			}
		}

		nStepIndex++;

		if (nStepIndex >= nStepPoints)
		{
			nStepIndex = 0;
			////g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_SAVE_RECORDFILE, 0, MAKELONG(nStep, nSteps));
			nStep++;
		}

		dwIndex++;
	}
	//////////////////////////

	fclose(pFile);
	pFile = NULL;

	////g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_SAVE_RECORDFILE, 1, MAKELONG(nStep, nSteps));

}

void CRcdComtradeFile::SaveDataAsASIIMode(const CString& strFilePath)
{
}

void CRcdComtradeFile::GetSaveTimeRange(long nBeginPos1,long nLen1,long nBeginPos2,long nLen2)
{
	m_nBufBeginPos1 = nBeginPos1;
	m_nBufBeginPos2 = nBeginPos2;
	m_nBufLength1	= nLen1;
	m_nBufLength2	= nLen2;
}

long CRcdComtradeFile::ReadComtradeFile(const CString& strFilePath, UINT nReadMask)
{
	if ( (nReadMask & CMTRD_RDF_CLEARBUFF) == CMTRD_RDF_CLEARBUFF)
	{
		BufferClear();
	}

	BOOL bReadCfgRet = TRUE;//20220915 zhouhj �������ڷ�ֹcfg�ļ���ʧ��,������֤ʧ��,���º������ݽ�������

	if ( (nReadMask & CMTRD_RDF_READCFG) == CMTRD_RDF_READCFG)
	{
		bReadCfgRet = ReadCFGFile(strFilePath);
	}

	if (( (nReadMask & CMTRD_RDF_READDATA) == CMTRD_RDF_READDATA)&&(bReadCfgRet))
	{
		m_strComtradeFile = strFilePath;

		// 		m_listAnalog.RemoveAll();
		// 		m_listBinary.RemoveAll();
		m_nTotalPoints = ReadDataFile(strFilePath);

	}

	if (bReadCfgRet)
	{
		CalMinMaxValue();
	}

	return m_nTotalPoints;
}

void CRcdComtradeFile::ReadCfg_SampRate(char *pString, float &fRampRate, long &nTotalPoints)
{
	//sscanf(pString,"%f,%d", &fRampRate, &nTotalPoints);
	fRampRate = atof(pString);

	char *p = pString;
	char *pEnd = pString + strlen(pString);

	while (*p != ',' && p < pEnd)
	{
		p++;
	}

	if (*p == ',')
	{
		p++;

		while (*p == ' ')
		{
			p++;
		}

		nTotalPoints = atol(p);
	}
	else
	{
		nTotalPoints = 0;
	}
}

void CRcdComtradeFile::SetDataFileTypeByString(char *sString)
{
	if (_stricmp(sString, g_pszKeyASCII) == 0)
	{
		m_nDataFileType = COMTRADE_DATAFILE_TYPE_ASCII;
	}
	else if (_stricmp(sString, g_pszKeyBinary) == 0)
	{
		m_nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;
	}
}

BOOL CRcdComtradeFile::ReadCFGFile(const CString& strFilePath)
{
	char *sString = NULL;
	CString strCFGFilePath;
	CBufferBase oBuffer;
	CString strTemp = CString(g_pszKeyCfg);
	strCFGFilePath = ChangeFilePostfix(strFilePath, strTemp);

#ifdef _PSX_QT_LINUX_
	if(!IsFileExist(strCFGFilePath))
	{
        strTemp = _T("cfg");
		strCFGFilePath = ChangeFilePostfix(strFilePath, strTemp);			
		if(!IsFileExist(strCFGFilePath.GetString()))
		{
			return FALSE;
		}
	}

#endif
	//strCFGFilePath.Format(_T("%s.%s"),strFilePath,g_pszKeyCfg);

	if (!oBuffer.ReadFromFile(strCFGFilePath))
	{
		return FALSE;
	}

	oBuffer.FormatBuffer('\r');
	oBuffer.FormatBuffer('\n');

	long nIndex = 0;
	m_nBufLength1 = 0;
	CString strParse[PARSE_PART_AMOUNT];//
	long nBinaryIndex = 0;
	//	int nChans = 0;
	long nTotalPoints = 0;
	long nSamIndex = 0;
	unsigned short* pBinaryPreBuffer = NULL;

	while (TRUE) 
	{
		sString = oBuffer.GetString();

		if (!oBuffer.IsPoiterInBuffer(sString))
		{
			break;
		}

		nIndex++;

		if (nIndex == 1) 
		{
			CString strTemp[3];
			ParseString(CString(sString),strTemp);
			m_strStationName = strTemp[0];
			m_strRecordingDeviceID = strTemp[1];
			m_nComtradeVersion = CString_To_long(strTemp[2]);
		}
		else if (nIndex == 2) //�ڶ�����ͨ��������,�̶���
		{
			sscanf(sString,"%d,%dA,%dD",&m_nAllChs,&m_nAnalogs,&m_nBinarys);
		}
		else if (nIndex > 2 && nIndex < m_nAnalogs + 3)
		{
			CComtradeAnalogData *pNew = new CComtradeAnalogData();
			ParseString(CString(sString), strParse);
			pNew->GetChanInfor(strParse);
			//���������
			AddNewChild(pNew);//zhouhj 20210918 ������ͨ���в���,��ǰ�Ƕ����ƻ���ASCII��ʽ
			m_listAnalog.AddTail(pNew);
		}
		else if (nIndex > m_nAnalogs + 2 && nIndex < m_nAllChs + 3)
		{
			CComtradeBinaryData* pNew = new CComtradeBinaryData();
			ParseString(CString(sString),strParse);

			if (CString_To_long(strParse[0]) == (nIndex-2))//ֻ���ڱ��Ϊģ�������������������ʱ����Ҫȥ��ģ�����ı�ţ������õ�ǰʵ�ʱ��
			{
				pNew->GetChanInfor(strParse,m_nAnalogs);
			} 
			else
			{
				pNew->GetChanInfor(strParse,0);
			}

			AddNewChild(pNew);
			m_listBinary.AddTail(pNew);
		}
		else if (nIndex == m_nAllChs + 3)//����Ƶ��
		{
			m_dFreq = atof(sString);
		}
		else if (nIndex == m_nAllChs + 4)//�����ʸ���
		{
			m_nSamAmount = atoi(sString);

			//һ�������,����������һ��Ϊ����,�Ҳ�Ӧ�ó���10,������ִ�ֵ,����ʾ�û�ȷ��
			if ((m_nSamAmount>30)||(m_nSamAmount<=0))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����������쳣(m_nSamAmount=%ld),��ע��ȷ��.")
					,m_nSamAmount);
			}

			m_pnDataPoints = new long[m_nSamAmount];
			m_pdSamRate    = new float[m_nSamAmount];
		}
		else if (nIndex > m_nAllChs + 4 && nIndex < (m_nAllChs + 5 + m_nSamAmount))
		{
			//�����淶�ĸ�ʽ�����磺25462.914062  ,      5732
			ReadCfg_SampRate(sString, m_pdSamRate[nSamIndex], m_pnDataPoints[nSamIndex]);
			//CString strLeft,strRight;
			//sscanf(sString,"%f,%d", &m_pdSamRate[nSamIndex], &m_pnDataPoints[nSamIndex]);
			// 			nLength = strTemp.GetLength();
			// 			nPos    = strTemp.FindOneOf(_T(","));
			// 			strLeft = strTemp.Left(nPos);
			// 			strRight = strTemp.Right(nLength - nPos - 1);
			// 			m_pnDataPoints[nSamIndex] = CString_To_long(strRight);
			// 			m_pdSamRate[nSamIndex]    = CString_To_double(strLeft);

			CComtradeRateData *pNew = new CComtradeRateData();
			pNew->m_nSamprate = m_pdSamRate[nSamIndex];
			pNew->m_nEndsamp = m_pnDataPoints[nSamIndex];
			AddNewChild(pNew);
			m_listRates.AddTail(pNew);

//			nTotalPoints += m_pnDataPoints[nSamIndex];//zhouhj ��У���������,�ٽ����ܵ���ͳ��
			nSamIndex++;
		}
		else if (nIndex == m_nAllChs + 5 + m_nSamAmount) //��һ����ʱ��
		{
			double dSec = 0;
			sscanf(sString,"%hd/%hd/%hd,%hd:%hd:%lf",&(m_oFirstPointTime.wDay),
				&(m_oFirstPointTime.wMonth),&(m_oFirstPointTime.wYear),
				&(m_oFirstPointTime.wHour),&(m_oFirstPointTime.wMinute),&dSec);

			m_strFirstPointTime.Format(_T("%02hd/%02hd/%02hd,%02hd:%02hd:%lf"), (m_oFirstPointTime.wDay),
				(m_oFirstPointTime.wMonth),(m_oFirstPointTime.wYear),
				(m_oFirstPointTime.wHour),(m_oFirstPointTime.wMinute),dSec);

			m_oFirstPointTime.wSecond = (WORD)dSec;

			double dRemain = (dSec - m_oFirstPointTime.wSecond ) * 1000;
			m_oFirstPointTime.wMilliseconds = (WORD)dRemain;

			dRemain = (dRemain - m_oFirstPointTime.wMilliseconds ) * 1000;
			m_oFirstPointTime.wMicroseconds = (WORD)dRemain;
		}
		else if (nIndex == m_nAllChs + 6 + m_nSamAmount) //������ʱ��
		{
			double dSec = 0;
			sscanf(sString,"%hd/%hd/%hd,%hd:%hd:%lf",&(m_oTrigPointTime.wDay),
				&(m_oTrigPointTime.wMonth),&(m_oTrigPointTime.wYear),
				&(m_oTrigPointTime.wHour),&(m_oTrigPointTime.wMinute),&dSec);
			m_oTrigPointTime.wSecond = (WORD)dSec;

			m_strTrigPointTime.Format(_T("%02hd/%02hd/%02hd,%02hd:%02hd:%lf"), (m_oTrigPointTime.wDay),
				(m_oTrigPointTime.wMonth),(m_oTrigPointTime.wYear),
				(m_oTrigPointTime.wHour),(m_oTrigPointTime.wMinute),dSec);

			double dRemain = (dSec - m_oTrigPointTime.wSecond ) * 1000;
			m_oTrigPointTime.wMilliseconds = (WORD)dRemain;

			dRemain = (dRemain - m_oTrigPointTime.wMilliseconds ) * 1000;
			m_oTrigPointTime.wMicroseconds = (WORD)dRemain;
		}
		else if (nIndex == m_nAllChs + 7 + m_nSamAmount) 
		{
			if (_stricmp(sString, g_pszKeyASCII) == 0)
			{
				m_nDataFileType = COMTRADE_DATAFILE_TYPE_ASCII;
			}
			else if (_stricmp(sString, g_pszKeyBinary) == 0)
			{
				m_nDataFileType = COMTRADE_DATAFILE_TYPE_BINARY;
			}
			else
			{
			}
		}
		else if (nIndex == m_nAllChs + 8 + m_nSamAmount) 
		{
			m_dTimeCoef = atof(sString);
			break;
		}
		else
		{
		}

		SetDataFileTypeByString(sString);//��ֹcfg�ļ���ʽ�����⵼�µĽ�������
		sString = oBuffer.NextString();
	}

	if (!ValidTotalPoints(strCFGFilePath))
	{
		return FALSE;
	}

	nTotalPoints = GetTotalPoints();

	POS pos = GetHeadPosition(); //zhouhj 20210918 �޸Ķ���ASCII�����,ÿ��ͨ����������2��unsigned int

	while (pos != NULL)
	{
		CComtradeDataBase* pObj = (CComtradeDataBase*)GetNext(pos);

		if (pObj->IsAnalogData())
		{
			if (m_bCreateBuffer)
			{
				if (m_nDataFileType)
				{
					pObj->AllocBuffer(nTotalPoints);
				} 
				else
				{
					pObj->AllocBuffer(nTotalPoints*2);
				}
			}
		}
		else
		{
			if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			if (nBinaryIndex % 16 == 0)
			{
				if (m_bCreateBuffer)
				{
					pObj->AllocBuffer(nTotalPoints);
					pBinaryPreBuffer = pObj->GetBuffer();
				}
			}
			else
			{
				pObj->AttachBuffer(pBinaryPreBuffer);
			}
		}
	}

	m_nTotalPoints = nTotalPoints;
	m_nBufLength2 = -1;
	m_nBufBeginPos2 = -1;
	m_nBufBeginPos1 = 0;
	m_nBufLength1 = m_pnDataPoints[0];
	m_nBufferLen = m_pnDataPoints[0];

	return TRUE;
}

void CRcdComtradeFile::BigComtrade_InitChsAllocBufferNext()
{
	POS pos = GetHeadPosition();
	CComtradeDataBase* pObj = NULL;
	int nFlag = 0;
	unsigned short* pBinaryPreBuffer = NULL;
	unsigned short uTmp = 0,uTmp2 = 0;

	while (pos != NULL)
	{
		pObj = (CComtradeDataBase*)GetNext(pos);

		if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
		{
			continue;
		}

		if (pObj->IsAnalogData())
		{
			pObj->InitBuffer_Circle(m_nDataFileType,m_nTotalPoints);
		}
		else
		{
			if (nFlag % 16 == 0)
			{
				pObj->InitBuffer_Circle(m_nDataFileType,m_nTotalPoints);
				pBinaryPreBuffer = pObj->GetBuffer();
			}
			else
			{
				pObj->AttachBuffer(pBinaryPreBuffer);
			}

			nFlag++;
		}
	}
}

void CRcdComtradeFile::ParseString(const CString& strIn, CString* pstrOut)
{
	CString strTemp = strIn;
	long nIndex = 0;
	long nPos = strTemp.FindOneOf(_T(","));
	long nLength = strTemp.GetLength();
	CString strLeft,strRight;

	while ( nPos >= 0)
	{
		strLeft = strTemp.Left(nPos);
		nLength = strTemp.GetLength();
		strRight = strTemp.Right(nLength - nPos -1);
		strTemp = strRight;
		pstrOut[nIndex] = strLeft;
		nIndex++;
		nPos = strTemp.FindOneOf(_T(","));
	}

	pstrOut[nIndex] = strTemp;
}

void CRcdComtradeFile::ParseString(const CString& strIn, CStringArray &straOut)
{
	straOut.RemoveAll();
	CString strTemp = strIn;
	long nIndex = 0;
	long nPos = strTemp.FindOneOf(_T(","));
	long nLength = strTemp.GetLength();
	CString strLeft,strRight;

	while ( nPos >= 0)
	{
		strLeft = strTemp.Left(nPos);
		nLength = strTemp.GetLength();
		strRight = strTemp.Right(nLength - nPos -1);
		strTemp = strRight;
		straOut.Add(strLeft);
		nIndex++;
		nPos = strTemp.FindOneOf(_T(","));
	}

	straOut.Add(strTemp);
}

void CRcdComtradeFile::ParseString_Char(char *pString, CStringArray &straOut)
{
	straOut.RemoveAll();

	if (pString == NULL)
	{
		return;
	}

	CString strTemp;
	char *pStartString = pString,*pCurString = pString;

	while(*pCurString != 0)
	{
		if (*pCurString == ',')
		{
			*pCurString = 0;
			strTemp = pStartString;
			straOut.Add(strTemp);
			*pCurString = ',';
			pCurString++;
			pStartString = pCurString;
		}

		pCurString++;
	}

	strTemp = pStartString;
	straOut.Add(strTemp);

// 	long nTotalLenth = strlen(pString);
// 	CString strTemp = strIn;
// 	long nIndex = 0;
// 	long nPos = strTemp.FindOneOf(_T(","));
// 	long nLength = strTemp.GetLength();
// 	CString strLeft,strRight;
// 
// 	while ( nPos >= 0)
// 	{
// 		strLeft = strTemp.Left(nPos);
// 		nLength = strTemp.GetLength();
// 		strRight = strTemp.Right(nLength - nPos -1);
// 		strTemp = strRight;
// 		straOut.Add(strLeft);
// 		nIndex++;
// 		nPos = strTemp.FindOneOf(_T(","));
// 	}
// 
// 	straOut.Add(strTemp);
}

long CRcdComtradeFile::ReadDataFile(const CString& strFilePath)
{
	BOOL bRet = FALSE;

	if (m_nDataFileType == COMTRADE_DATAFILE_TYPE_ASCII)
	{
		bRet = ReadDataAsASIIMode(strFilePath);
	}
	else
	{
		bRet = ReadDataAsBINARYMode(strFilePath);
	}

	return bRet;
}

long CRcdComtradeFile::GetTotalPoints()
{
	//2021-9-20  lijunqing
	if (m_pnDataPoints == NULL || m_nSamAmount == 0)
	{
		return 0;
	}

	long nIndex = 0;
	long nTotalPoints = 0;

	//����ܵ����ݵ���
	for(nIndex = 0; nIndex < m_nSamAmount; nIndex++)
	{
		nTotalPoints += m_pnDataPoints[nIndex];
	}

	return nTotalPoints;
}

long CRcdComtradeFile::GetChannelBuffferCount()
{
	long nBChs = m_nBinarys/16;
	if (m_nBinarys > nBChs * 16)
	{
		nBChs++;
	}

	return m_nAnalogs + nBChs;
}

double CRcdComtradeFile::CalCyclesBeforeStart()
{
	CGpsPcTime oGpsTime1(m_oTrigPointTime.wYear, m_oTrigPointTime.wMonth, m_oTrigPointTime.wDay
		, m_oTrigPointTime.wHour, m_oTrigPointTime.wMinute, m_oTrigPointTime.wSecond
		, m_oTrigPointTime.wMilliseconds, m_oTrigPointTime.wMicroseconds);

	CGpsPcTime oGpsTime2(m_oFirstPointTime.wYear, m_oFirstPointTime.wMonth, m_oFirstPointTime.wDay
		, m_oFirstPointTime.wHour, m_oFirstPointTime.wMinute, m_oFirstPointTime.wSecond
		, m_oFirstPointTime.wMilliseconds, m_oFirstPointTime.wMicroseconds);

	CGpsPcTimeSpan ts = oGpsTime1 - oGpsTime2;
	long nMs = ts.GetTotalMilliseconds();
	double dCycles = nMs;
	dCycles = dCycles * m_dFreq / 1000;

	return dCycles;
}

double CRcdComtradeFile::GetSampleRate(long nIndex)
{
	if (m_pdSamRate == NULL)
	{
		return 10000;
	}

	return m_pdSamRate[nIndex];
}

double CRcdComtradeFile::CalComtradeFileSumTime()
{
	double dTotalTime = 0;
	BOOL bIsFirstSmpRate = TRUE;// ��ֹ��һ��������,��������Ϊ0�����

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		if (m_pnDataPoints[nIndex]<=0)
		{
			continue;
		}

		if (bIsFirstSmpRate)
		{
			dTotalTime = (1/m_pdSamRate[nIndex])*(m_pnDataPoints[nIndex]-1);
			bIsFirstSmpRate = FALSE;
		} 
		else
		{
			dTotalTime += (1/m_pdSamRate[nIndex])*(m_pnDataPoints[nIndex]);
		}
	}

	return dTotalTime;
}

long CRcdComtradeFile::GetBinarySinglePointLength()
{
	long nPointLength = 4+4;//��ż�ʱ�������
	nPointLength += m_nAnalogs*2;//ģ��������
	nPointLength += (m_nBinarys/16)*2;//����������

	if (m_nBinarys%16 > 0)//�����Ϊ16��������,���������2���ֽ�
	{
		nPointLength += 2;
	}

	return nPointLength;
}

void CRcdComtradeFile::SetInPhase_SpecialSmpRate(BOOL bInPhase_SpecialSmpRate)
{
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pCurObj = NULL;

	while(pos)
	{
		pCurObj = (CComtradeAnalogData *)m_listAnalog.GetNext(pos);
		pCurObj->m_bInPhase_SpecialSmpRate = bInPhase_SpecialSmpRate;
	}
}

void CRcdComtradeFile::InitBeginAng_SpecialSmpRate(long nPointIndex,double dOffsetTime,double dFreq)
{
	if (nPointIndex>=m_nTotalPoints)
	{
		nPointIndex = m_nTotalPoints-1;
	}

	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pCurObj = NULL;

	while(pos)
	{
		pCurObj = (CComtradeAnalogData *)m_listAnalog.GetNext(pos);
		pCurObj->m_dBeginAng_SpecialSmpRate = pCurObj->GetCurPointAng(m_pdSamRate,m_pnDataPoints,m_nSamAmount,dFreq,nPointIndex) + dOffsetTime*dFreq*2*_PI;

		while(pCurObj->m_dBeginAng_SpecialSmpRate>(2*_PI))
		{
			pCurObj->m_dBeginAng_SpecialSmpRate-= (2*_PI);
		}
	}
}

DWORD CRcdComtradeFile::GetCurPointTimeStamp(long nPointIndex)//zhouhj 20200911
{
	DWORD dwTimeStamp = 0/*0xFFFFFFFF*/;
	long nCurPointNum = 0;
	double dGapTime = 0;

	for (int nSmpRateIndex = 0; nSmpRateIndex<m_nSamAmount;nSmpRateIndex++)
	{
		if (m_pnDataPoints[nSmpRateIndex]<=0)//������������Ϊ0�Ĳ�����
		{
			continue;
		}

		dGapTime = (1000000/m_pdSamRate[nSmpRateIndex]);//�������²�����ļ��ʱ��

		if (nPointIndex<=(nCurPointNum+m_pnDataPoints[nSmpRateIndex]))//�жϸò������Ƿ��ڵ�ǰ����Ƶ�ʷ�Χ��
		{
			dwTimeStamp += ((nPointIndex - nCurPointNum)*dGapTime);
			break;
		}

		nCurPointNum += m_pnDataPoints[nSmpRateIndex];

		if (dwTimeStamp == 0)//����ǵ�һ�������㣬��Ҫ��ȥ1
		{
			dwTimeStamp += (m_pnDataPoints[nSmpRateIndex]-1)*dGapTime;
		} 
		else
		{
			dwTimeStamp += m_pnDataPoints[nSmpRateIndex]*dGapTime;
		}
	}

	if (m_dTimeCoef>0)
	{
		dwTimeStamp = dwTimeStamp/m_dTimeCoef;
	}

	return dwTimeStamp;
}

void CRcdComtradeFile::SetSamAmount(long nSamAmount)
{
	if (m_pnDataPoints != NULL)
	{
		delete []m_pnDataPoints;
	}

	if (m_pdSamRate != NULL)
	{
		delete []m_pdSamRate;
	}

	m_nSamAmount = nSamAmount;
	m_pnDataPoints = new long[m_nSamAmount];
	m_pdSamRate    = new float[m_nSamAmount];
}

void CRcdComtradeFile::SetSamValue(long nSamIndex, long nDataPoints, float fSampleRate)
{
	if (0 > nSamIndex || nSamIndex >= m_nSamAmount)
	{
		return;
	}

	m_pnDataPoints[nSamIndex] = nDataPoints;
	m_pdSamRate[nSamIndex] = fSampleRate;
}

void CRcdComtradeFile::SetSamPoints(long nSamIndex, long nDataPoints)
{
	if (0 > nSamIndex || nSamIndex >= m_nSamAmount)
	{
		return;
	}

	m_pnDataPoints[nSamIndex] = nDataPoints;
}

void CRcdComtradeFile::SetSamReate(long nSamIndex, float fSampleRate)
{
	if (0 > nSamIndex || nSamIndex >= m_nSamAmount)
	{
		return;
	}

	m_pdSamRate[nSamIndex] = fSampleRate;
}

long CRcdComtradeFile::CalDataPoints(const CString &strPath)
{
	FILE* pFile = NULL;
	CString strFile;
	//Edit by lipenghui 2020-04-15
	strFile.Format(_T("%s.%s"), strPath.GetString(), g_pszKeyDat);

#ifdef _PSX_QT_LINUX_
	if(!IsFileExist(strFile))
	{
        CString strTemp;
		strTemp = _T("dat");
		strFile = ChangeFilePostfix(strPath, strTemp);
		if(!IsFileExist(strFile))
		{
			return FALSE;
		}
	}

    QTextCodec *pOldTextCodec = NULL;
    InitLocalCodec_BeforeReadWrite(strFile,&pOldTextCodec);//�������Ϊutf-8
#endif

	char pszFile[MAX_PATH];
	CString_to_char(strFile, pszFile);
	pFile = fopen(pszFile,"rb");

#ifdef _PSX_QT_LINUX_
    ResetLocalCodec(pOldTextCodec);
    //system("sync");//20220616 д�ļ�����Ҫͬ��
#endif

	long nPoints = 0;

	if (pFile != NULL)
	{
		fseek(pFile, 0, SEEK_END);
		long nPos = ftell(pFile);
		long nChs = GetChannelBuffferCount();
		nPoints = nPos / nChs;
	}
	else
	{
		nPoints = 655360;
	}

	nPoints /= 2;
	fclose(pFile);
	pFile = NULL;

	return nPoints;
}

void CRcdComtradeFile::GetSmpRateString(CString &strSmpRateString)
{
	strSmpRateString = _T("");

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		strSmpRateString.AppendFormat(_T("SmpRate%dPoints=%d;"),nIndex+1,m_pnDataPoints[nIndex]);
	}
}

BOOL CRcdComtradeFile::ValidTotalPoints(const CString &strCfgFilePath)
{
	if ((m_nSamAmount == 0)||(m_pnDataPoints == NULL))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����������Ϊ0,�ܲ�������У��ʧ��."));
		return FALSE;
	}

	CString strTemp = CString(g_pszKeyDat);
	CString strDatFilePath = ChangeFilePostfix(strCfgFilePath, strTemp);

#ifdef _PSX_QT_LINUX_
	if(!IsFileExist(strDatFilePath))
	{
        strTemp = _T("dat");
		strDatFilePath = ChangeFilePostfix(strDatFilePath, strTemp);
		if(!IsFileExist(strDatFilePath))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��dat�ļ�(%s)ʧ��."), strDatFilePath.GetString());
			return FALSE;
		}
	}
#endif

	long nDataPoints = GetDataFilePoints(strDatFilePath);
	long nCfgPoints = GetTotalPoints();

	if (nDataPoints < nCfgPoints)//��dat�ļ��еĵ���С��cfg�ļ��еĵ���ʱ,��ʾ�޸�
	{
		long nErrorPoints = m_pnDataPoints[0];

		for (int nIndex = 1;nIndex<m_nSamAmount;nIndex++)
		{
			nErrorPoints += (m_pnDataPoints[nIndex]-m_pnDataPoints[nIndex-1]);
		}

		if (nErrorPoints == nDataPoints)
		{
			long nTmp = m_pnDataPoints[0];

			for (int nIndex = 1;nIndex<m_nSamAmount;nIndex++)
			{
				m_pnDataPoints[nIndex] -= nTmp;
				nTmp += m_pnDataPoints[nIndex];
			}

			return TRUE;
		}

		CString strSmpRateString;
		GetSmpRateString(strSmpRateString);

		if (strSmpRateString.GetLength()>1000)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰCFG�ļ��б�ʶ���ܵ���%ld(�����ʲ����쳣),��DAT�ļ��е�ʵ���ܵ���%ld��һ��,���޸�CFG�ļ�.")
				, nCfgPoints,nDataPoints);
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��ǰCFG�ļ��б�ʶ���ܵ���%ld(%s),��DAT�ļ��е�ʵ���ܵ���%ld��һ��,���޸�CFG�ļ�.")
				, nCfgPoints,strSmpRateString.GetString(), nDataPoints);
		}
		
		return FALSE;
	}

	return TRUE;
}

long CRcdComtradeFile::GetDataFilePoints(const CString &strDataFilePath)
{
	long nPoints = 0;

	if (m_nDataFileType == 0)//ASCII
	{
		CBufferBase oASII_ModeBuffer;

		if (!oASII_ModeBuffer.ReadFromFile(strDataFilePath))
		{
			return 0;
		}

		oASII_ModeBuffer.FormatBuffer('\r');
		oASII_ModeBuffer.FormatBuffer('\n');
		char *sString = NULL;
		sString = oASII_ModeBuffer.GetString();

		while(oASII_ModeBuffer.IsPoiterInBuffer(sString))
		{
			nPoints++;
			sString = oASII_ModeBuffer.NextString();
		}
	}
	else//Binary
	{
#ifdef _PSX_QT_LINUX_
		QTextCodec *pOldTextCodec = NULL;
        InitLocalCodec_BeforeReadWrite(strDataFilePath,&pOldTextCodec);//�������Ϊutf-8
#endif

		FILE* pFile = NULL;
		pFile = fopen(strDataFilePath.GetString(),"rb");

#ifdef _PSX_QT_LINUX_
		ResetLocalCodec(pOldTextCodec);
		system("sync");//20220616 д�ļ�����Ҫͬ��
#endif
		if (pFile == NULL)
		{
			return 0;
		}

		fseek(pFile,0,SEEK_END); //��λ���ļ�ĩ
		long nFileLen = ftell(pFile);
		fclose(pFile);
		pFile = NULL;

// 		CFile oFile;
// 		if (!oFile.Open(strDataFilePath,CFile::modeRead))
// 		{
// 			return 0;
// 		}
// 
// 		long nFileLen = oFile.GetLength();
// 		oFile.Close();

		long nSinglePointLength = GetBinarySinglePointLength();
		nPoints = nFileLen / nSinglePointLength;
	}

	return nPoints;
}

long CRcdComtradeFile::ReadDataAsBINARYMode(const CString& strFilePath)
{
	if (m_pnDataPoints == NULL)
	{
		return 0;
	}

	//CMR1200BaseApp *//pApp = (CMR1200BaseApp*)AfxGetApp();
	long nIndex = 0;
	long nTotalPoints = GetTotalPoints();
	long nSteps = 20;
	long nStepPoints = nTotalPoints / nSteps;
	long nStep = 1;

	if (nStepPoints > 65536)
	{
		nStepPoints = 65536;
		nStepPoints = nTotalPoints / nSteps;
		nSteps = nTotalPoints / nStepPoints + 1;
	}

	long nStepIndex = 0;

	//����ܵ����ݵ���
	// 	for(nIndex = 0; nIndex < m_nSamAmount; nIndex++)
	// 	{
	// 		DWORD dwPoints = m_pnDataPoints[nIndex];
	// 		nTotalPoints += dwPoints;
	// 	}
	////g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_ONLINE_RECORD_DATA_COPY, SYSOPTRPARA_ONLINERECORDDATACOPY_BEGIN, MAKELONG(nStep, nSteps));

	unsigned short* pnBuffer = NULL;
	unsigned short* pnTemp = NULL;

	FILE* pFile = NULL;
	CString strDatFilePath;

	CString strTemp = CString(g_pszKeyDat);
	strDatFilePath = ChangeFilePostfix(strFilePath, strTemp);

#ifdef _PSX_QT_LINUX_
	if(!IsFileExist(strDatFilePath))
	{
        strTemp = _T("dat");
		strDatFilePath = ChangeFilePostfix(strFilePath, strTemp);
		if(!IsFileExist(strDatFilePath))
		{
			return FALSE;
		}
	}
	QTextCodec *pOldTextCodec = NULL;
    InitLocalCodec_BeforeReadWrite(strDatFilePath,&pOldTextCodec);//�������Ϊutf-8

#endif

	char pszDatFilePath[MAX_PATH];
	CString_to_char(strDatFilePath, pszDatFilePath);

//	long nFileSize = file_GetFileSize(pszDatFilePath);
	pFile = fopen(pszDatFilePath,"rb");

#ifdef _PSX_QT_LINUX_
	ResetLocalCodec(pOldTextCodec);
	//system("sync");//20220616 д�ļ�����Ҫͬ��
#endif
	if (pFile == NULL)
	{
		return 0;
	}

	int  nSize = (int)(ceil(m_nBinarys / 16.0));
	nSize += (2 + 2 + m_nAnalogs);
	pnBuffer = new unsigned short[nSize];
	CComtradeDataBase* pObj = NULL;
	long nBinaryIndex = 0;
	long nAnalogIndex = 0;
	unsigned short* pBuffer = NULL;
	long nReadSize = 0;

	for (long nIndex = 0; nIndex < nTotalPoints; nIndex++)
	{
		nReadSize = fread(pnBuffer,2,nSize,pFile);//sizeof(unsigned short)

		if (nReadSize == 0)
		{
			break;
		}

		ReadDataAsBINARYMode(pnBuffer, nIndex);
		// 		pnTemp = pnBuffer + 4;//4��ʱ���������ռ��4����
		// 		POS pos = GetHeadPosition();
		// 		nBinaryIndex = 0;
		// 		nAnalogIndex = 0;
		// 		
		// 		while (pos != NULL)
		// 		{
		// 			pObj = (CComtradeDataBase*)GetNext(pos);
		// 			pBuffer = pObj->GetBuffer();
		// 
		// 			if (pObj->IsAnalogData())
		// 			{			
		// 				pBuffer[nIndex] = *pnTemp;
		// 				pnTemp++;			
		// 				nAnalogIndex++;
		// 			}
		// 			else
		// 			{
		// 				if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
		// 				{
		// 					continue;
		// 				}
		// 				if (nBinaryIndex % 16 == 0)//ÿ16��״̬һ��short
		// 				{
		// 					pBuffer[nIndex] = *pnTemp;
		// 					pnTemp++;
		// 				}
		// 				
		// 				nBinaryIndex++;
		// 			}
		// 		}

		nStepIndex++;

		if (nStepIndex >= nStepPoints)
		{
			nStepIndex = 0;
			//g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_ONLINE_RECORD_DATA_COPY, SYSOPTRPARA_ONLINERECORDDATACOPY_COPY, MAKELONG(nStep, nSteps));
			nStep++;
		}
	}

	fclose(pFile);
	pFile = NULL;
	UpdateAllChsTotalPointsNum();
	delete []pnBuffer;
	return nTotalPoints;
}

void CRcdComtradeFile::UpdateAllChsTotalPointsNum()
{
	//xupf ת��ΪCData
	POS pos = GetHeadPosition();
	CComtradeDataBase* pObj = NULL;
	int nFlag = 0;

	while (pos != NULL)
	{
		pObj = (CComtradeDataBase*)GetNext(pos);

		if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
		{
			continue;
		}

		if (pObj->IsAnalogData())
		{
			pObj->m_nTotalPoints = m_nTotalPoints;
		}
		else
		{
			if (nFlag % 16 == 0)
			{
				pObj->m_nTotalPoints = m_nTotalPoints;
			}

			nFlag++;
		}
	}
}

unsigned short CRcdComtradeFile::CtringToUShort(const CString &strValue)
{
	unsigned short unValue = CString_To_ulong(strValue);
	return unValue;
}

// void WriteRecordDataFile(short nValue, CFile &oFile)
// {
// 	CString strText;
// 	strText.Format(_T("%d\t"), nValue);
// 	oFile.Write(strText, strText.GetLength());
// 	oFile.Write(_T("\r\n"), 2);
// }


void CRcdComtradeFile::ReadDataAsBINARYMode(unsigned short* pnBuffer, long nIndex)
{
	unsigned short* pnTemp = NULL;
	CComtradeDataBase* pObj = NULL;
	long nBinaryIndex = 0;
	long nAnalogIndex = 0;
	unsigned short* pBuffer = NULL;

	pnTemp = pnBuffer + 4;//4��ʱ���������ռ��4����
	POS pos = GetHeadPosition();
	nBinaryIndex = 0;
	nAnalogIndex = 0;

	while (pos != NULL)
	{
		pObj = (CComtradeDataBase*)GetNext(pos);
		pBuffer = pObj->GetBuffer();

		if (pObj->IsAnalogData())
		{			
			pBuffer[nIndex] = *pnTemp;
			pnTemp++;			
			nAnalogIndex++;
		}
		else
		{
			if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			if (nBinaryIndex % 16 == 0)//ÿ16��״̬һ��short
			{
				pBuffer[nIndex] = *pnTemp;
				pnTemp++;
			}

			nBinaryIndex++;
		}
	}
}

void CRcdComtradeFile::ReadDataAsASIIMode(char *pString, long nIndex)
{
	CStringArray straCurPointValues;
	ParseString_Char(pString,straCurPointValues);
	POS pos = GetHeadPosition();
	long nBinaryIndex = 0;
	long nAnalogIndex = 0;
	long nDataIndex = 2;//������һ�����ڶ���ֵ����Ӧ��ż�ʱ���ֵ
	CComtradeDataBase* pObj = NULL;
	CComtradeAnalogData *pAnalogCh = NULL;
	int* pBuffer = NULL;
	unsigned short* pBufferBinary = NULL;
	CString strCurString;
	long nTmp = 0;

	//2024-7-23 wuxinyi �޸Ĳ���¼���ļ������⵼���ж�
	if(straCurPointValues.GetSize() <= nDataIndex)
	{
		return;
	}

	while (pos != NULL)
	{
		pObj = (CComtradeDataBase*)GetNext(pos);
		pBuffer = (int *)pObj->GetBuffer();
		pBufferBinary = (unsigned short*)pObj->GetBuffer();

		if (pObj->IsAnalogData())
		{
			strCurString = straCurPointValues.GetAt(nDataIndex);
			pAnalogCh = (CComtradeAnalogData *)pObj;
			pBuffer[nIndex] = static_cast<int>(CString_To_long(strCurString));	//zhouhj 20210918 ��ASCII�����,����long���ݴ洢
			nAnalogIndex++;
			nDataIndex++;
		}
		else
		{
			if (pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			//2024-03-20 wuxinyi �޸�ascii�ļ� �������洢
// 			if (nBinaryIndex % 16 == 0)//ÿ16��״̬һ��short
// 			{
// 				strCurString = straCurPointValues.GetAt(nDataIndex);
// 				pBufferBinary[nIndex] = CtringToUShort(strCurString);	
// 				nDataIndex++;
// 			}
				
			if (nBinaryIndex % 16 == 0)//ÿ16��״̬һ��short
			{
				unsigned short usValue = 0;
				for(int i = 0;i < 16; i++)
				{
					if(nDataIndex < straCurPointValues.GetSize())
					{
				strCurString = straCurPointValues.GetAt(nDataIndex);
						unsigned short usBitValue = CtringToUShort(strCurString);
						usValue |= (usBitValue ? 1ULL << i : 0ULL);
					}
					else
					{
						usValue &= ~(1ULL << i);//ʣ��λ��0
					}
				nDataIndex++;
			}
				pBufferBinary[nIndex] = usValue;

			}				
			nBinaryIndex++;


		}
	}
}

long CRcdComtradeFile::ReadDataAsASIIMode(const CString& strFilePath)
{
	if (m_pnDataPoints == NULL)
	{
		return 0;
	}

	long nIndex = 0;
	long nTotalPoints = GetTotalPoints();
	long nSteps = 20;
	long nStepPoints = nTotalPoints / nSteps;
	long nStep = 1;

	if (nStepPoints > 65536)
	{
		nStepPoints = 65536;
		nStepPoints = nTotalPoints / nSteps;
		nSteps = nTotalPoints / nStepPoints + 1;
	}

	long nStepIndex = 0;
	CString strDatFilePath;
	CString strTemp = CString(g_pszKeyDat);
	strDatFilePath = ChangeFilePostfix(strFilePath, strTemp);

#ifdef _PSX_QT_LINUX_
	if(!IsFileExist(strDatFilePath))
	{
        strTemp = _T("dat");
		strDatFilePath = ChangeFilePostfix(strFilePath, strTemp);
		if(!IsFileExist(strDatFilePath))
		{
			return FALSE;
		}
	}
#endif

	CBufferBase oBuffer;
	char *sString = NULL;

	if (!oBuffer.ReadFromFile(strDatFilePath))
	{
		return 0;
	}

	oBuffer.FormatBuffer('\r');
	oBuffer.FormatBuffer('\n');

	for (long nIndex = 0; nIndex < nTotalPoints; nIndex++)
	{
		sString = oBuffer.GetString();

		if (!oBuffer.IsPoiterInBuffer(sString))
		{
			break;
		}

		ReadDataAsASIIMode(sString,nIndex);
		nStepIndex++;

		if (nStepIndex >= nStepPoints)
		{
			nStepIndex = 0;
			nStep++;
		}

		sString = oBuffer.NextString();
	}

	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pAnalog = NULL;

	while(pos)
	{
		pAnalog = (CComtradeAnalogData*)m_listAnalog.GetNext(pos);

		// 		if ((pAnalog->m_nMin == 0)&&(pAnalog->m_nMax == 65535))
		// 		{
		// 			pAnalog->m_dZeroValue += 32767*pAnalog->m_dCoefValue; // �ڴӷ�Χ0~65535  ת��Ϊ-32767 ~ 32767ʱ����Ӧ��m_dZeroValue��Ҫ�޸�
		// 			pAnalog->m_nMin = 0;
		// 			pAnalog->m_nMax = 0;
		// 			pAnalog->m_dPrimaryValue = 1;
		// 			pAnalog->m_dSecondaryValue = 1;
		// 		}
	}

	m_nTotalPoints = nTotalPoints;
	UpdateAllChsTotalPointsNum();
	return nTotalPoints;
}

//����Comtrade�ļ�
void CRcdComtradeFile::CreateComtradeFile(long nAnalogChs, long nBinaryChs, long nTotalPoints)
{
	m_nBufBeginPos1 = 0;
	m_nBufLength1	= nTotalPoints;

	long nIndex = 0;
	CComtradeAnalogData *pAnalog = NULL;
	long nChannelIndex = 1;

	for (nIndex=0; nIndex<nAnalogChs; nIndex++)
	{
		pAnalog = new CComtradeAnalogData();

		if (m_nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
		{
			pAnalog->AllocBuffer(nTotalPoints);
		} 
		else
		{
			pAnalog->AllocBuffer(nTotalPoints*2);
		}

		pAnalog->m_nChannelIndex = nChannelIndex++;

		AddNewChild(pAnalog);
		m_listAnalog.AddTail(pAnalog);
	}

	unsigned short *pRefBuffer = NULL;
	CComtradeBinaryData *pBinary = NULL;

	for (nIndex=0; nIndex<nBinaryChs; nIndex++)
	{
		pBinary = new CComtradeBinaryData();
		pBinary->m_nDataIndex = nIndex % 16;
		pBinary->m_nChannelIndex = nChannelIndex++;

		AddNewChild(pBinary);
		m_listBinary.AddTail(pBinary);

		if (pBinary->m_nDataIndex == 0)
		{
			pBinary->AllocBuffer(nTotalPoints);
			pRefBuffer = pBinary->m_pnAttachBuffer;
		}
		else
		{
			pBinary->AttachBuffer(pRefBuffer);
		}
	}

	m_nTotalPoints = nTotalPoints;

}

CRcdComtradeFile* CRcdComtradeFile::CloneComtradeWithSingleSmpRate(double dSmpRate,const double &dDstBeginOffsetTime)
{
	CRcdComtradeFile* pFile = new CRcdComtradeFile(TRUE);
	CopyOwn(pFile);//����Cfg�ļ��е���ز�������
	pFile->SetSamAmount(1);//����ֻ��һ��������
	pFile->m_pdSamRate[0] = dSmpRate;//����ʵ�ʲ�����
	double dTotalTime = CalComtradeFileSumTime() - dDstBeginOffsetTime;//��ȡ��ʱ��
	pFile->m_pnDataPoints[0] = (dTotalTime*dSmpRate+2);//������ʱ�������ܵĲ�������,���ڲ�Ϊ����������,ֻ��������ʱ�����Ĳ�����
	pFile->m_nTotalPoints = pFile->m_pnDataPoints[0];

	pFile->m_nDataFileType = m_nDataFileType;
	pFile->CreateComtradeFile(m_nAnalogs,m_nBinarys,pFile->m_pnDataPoints[0]);//��������ͨ��,ģ��������������������
	pFile->m_nComtradeVersion = 1999;

	CExBaseList *pSmpRates = pFile->GetRates();
	CComtradeRateData *pRateData = new CComtradeRateData();
	pFile->AddNewChild(pRateData);
	pSmpRates->AddTail(pRateData);
	pRateData->m_nSamprate = dSmpRate;//��ʵ�ʲ����ʸ�ֵ
	pRateData->m_nEndsamp = pFile->m_pnDataPoints[0];

	CExBaseList *pAnalogList = pFile->GetAnalogs();
	CExBaseList *pBinaryList = pFile->GetBinarys();
	POS pos_ch = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pSrcAnalogData = NULL;
	CComtradeAnalogData *pDstAnalogData = NULL;
	long nChIndex = 0;
	long nActTotalPoints = pFile->m_nTotalPoints;

	while(pos_ch)
	{
		pSrcAnalogData = (CComtradeAnalogData *)m_listAnalog.GetNext(pos_ch);
		pDstAnalogData = (CComtradeAnalogData *)pAnalogList->GetAtIndex(nChIndex);
		nActTotalPoints = pSrcAnalogData->InsertBySampleRate(m_pdSamRate,m_pnDataPoints,m_nSamAmount,dSmpRate, pDstAnalogData,dDstBeginOffsetTime);
		nChIndex++;
	}

	CComtradeBinaryData *pSrcBinaryData = NULL;
	CComtradeBinaryData *pDstBinaryData = NULL;
	nChIndex = 0;
	pos_ch = m_listBinary.GetHeadPosition();

	while(pos_ch)
	{
		pSrcBinaryData = (CComtradeBinaryData *)m_listBinary.GetNext(pos_ch);
		pDstBinaryData = (CComtradeBinaryData *)pBinaryList->GetAtIndex(nChIndex);

		if (pSrcBinaryData->m_nDataIndex == 0)
		{
			pSrcBinaryData->InsertBySampleRate(m_pdSamRate,m_pnDataPoints,m_nSamAmount,dSmpRate, pDstBinaryData,dDstBeginOffsetTime);
		}
		else
		{
			pSrcBinaryData->CopyOwn(pDstBinaryData);
		}

		nChIndex++;
	}

	ASSERT(pFile->m_nTotalPoints  >= nActTotalPoints);
	pFile->m_nTotalPoints = nActTotalPoints;
	pFile->m_pnDataPoints[0] = nActTotalPoints;
	pFile->UpdateAllChsTotalPointsNum();
	return pFile;
}

CRcdComtradeFile* CRcdComtradeFile::CloneComtrade_AddSlowlyRising(double dSecondTime,long nAddCircleStartNum,long nAddCircleEndNum)
{
	CRcdComtradeFile* pFile = new CRcdComtradeFile(TRUE);
	CopyOwn(pFile);//����Cfg�ļ��е���ز�������
	ASSERT(m_pnDataPoints[0]>0);
	long nAddSlowlyRisingPoints = dSecondTime*m_pdSamRate[0];//��ӵĻ��������ĵ���
	long nAddStartSteadyPoints = nAddCircleStartNum*m_pdSamRate[0]/50;//��ӵ���̬����
	long nAddEndSteadyPoints = nAddCircleEndNum*m_pdSamRate[m_nSamAmount-1]/50;
	pFile->m_pnDataPoints[0] += (nAddSlowlyRisingPoints+nAddStartSteadyPoints);
	pFile->m_pnDataPoints[m_nSamAmount-1] += (nAddEndSteadyPoints);
	pFile->m_nTotalPoints += (nAddSlowlyRisingPoints+nAddStartSteadyPoints+nAddEndSteadyPoints);
	pFile->CreateComtradeFile(m_nAnalogs,m_nBinarys,pFile->m_nTotalPoints);//��������ͨ��,ģ��������������������
	pFile->m_nComtradeVersion = 1999;
	pFile->m_nDataFileType = m_nDataFileType;
	pFile->UpdateSmpRatesList();

	CExBaseList *pAnalogList = pFile->GetAnalogs();
	CExBaseList *pBinaryList = pFile->GetBinarys();
	POS pos_ch = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pSrcAnalogData = NULL;
	CComtradeAnalogData *pDstAnalogData = NULL;
	long nChIndex = 0;
	long nTwoSineWavePoints = 2*m_pdSamRate[m_nSamAmount-1]/50;//��������ܲ����ܵ���

	while(pos_ch)
	{
		pSrcAnalogData = (CComtradeAnalogData *)m_listAnalog.GetNext(pos_ch);
		pDstAnalogData = (CComtradeAnalogData *)pAnalogList->GetAtIndex(nChIndex);
		pSrcAnalogData->Copy_AddSlowlyRising(m_pdSamRate[0],nAddSlowlyRisingPoints,nAddStartSteadyPoints,pDstAnalogData,TRUE);
		pDstAnalogData->m_nTotalPoints = pFile->m_nTotalPoints;

		if (nAddCircleEndNum>0)
		{
			pDstAnalogData->SetSteadySineWave(m_pdSamRate[m_nSamAmount-1],pSrcAnalogData->m_nTotalPoints+nAddSlowlyRisingPoints+nAddStartSteadyPoints-nTwoSineWavePoints,nAddEndSteadyPoints+nTwoSineWavePoints);//��������ܲ�������������̬�ܲ���ȫ���������õ�ֵ
		}

		nChIndex++;
	}

	CComtradeBinaryData *pSrcBinaryData = NULL;
	CComtradeBinaryData *pDstBinaryData = NULL;
	nChIndex = 0;
	pos_ch = m_listBinary.GetHeadPosition();

	while(pos_ch)
	{
		pSrcBinaryData = (CComtradeBinaryData *)m_listBinary.GetNext(pos_ch);
		pDstBinaryData = (CComtradeBinaryData *)pBinaryList->GetAtIndex(nChIndex);

		if (pSrcBinaryData->m_nDataIndex == 0)
		{
//			pSrcBinaryData->InsertBySampleRate(m_pdSamRate,m_pnDataPoints,m_nSamAmount,dSmpRate, pDstBinaryData,dDstBeginOffsetTime);
		}
		else
		{
			pSrcBinaryData->CopyOwn(pDstBinaryData);
		}

		nChIndex++;
	}

	pFile->UpdateAllChsTotalPointsNum();
	return pFile;
}

long CRcdComtradeFile::CalTotalPoints_InsertWithSingleSmpRate(double dSmpRate,const double &dDstBeginOffsetTime)
{
	double dTotalTime = CalComtradeFileSumTime() - dDstBeginOffsetTime;//��ȡ��ʱ��
	double dCalTotalPoints = dTotalTime*dSmpRate;//������ʱ�������ܵĲ�������,���ڲ�Ϊ����������,ֻ��������ʱ�����Ĳ�����
	long nCalTotalPoints = dCalTotalPoints;

	if (fabs(nCalTotalPoints+1-dCalTotalPoints)<0.00001)//��Ҫ���ϵ�һ���㣬ͬʱ��Ҫ������Ϊ���ȶ�ʧ��ȥ��һ����
	{
		nCalTotalPoints += 2;
	} 
	else
	{
		nCalTotalPoints += 1;
	}

	return nCalTotalPoints;
}

void CRcdComtradeFile::InitAnalogChsIncreaseValue(long nMaxValue)
{
	POS pos = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pAnalogCh = NULL;
	long nIndex = 0;
	long nChValue = 1;
	int *pnAttachBuffer = NULL;

	while(pos)
	{
		pAnalogCh = (CComtradeAnalogData*)m_listAnalog.GetNext(pos);
		pnAttachBuffer = (int*)pAnalogCh->m_pnAttachBuffer;
		nChValue = 1;

		for (nIndex = 0;nIndex<m_nTotalPoints;nIndex++)
		{
			if (m_nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
			{
				pAnalogCh->m_pnAttachBuffer[nIndex] = nChValue;
			} 
			else
			{
				pnAttachBuffer[nIndex] = nChValue;
			}

			nChValue++;

			if (nChValue>nMaxValue)
			{
				nChValue = 1;
			}
		}
	}
}

BOOL CRcdComtradeFile::SetAnalogAttr(long nAnalog, const CString &strName, const CString &strChID, const CString &strUnit
									 , float fZero, float fCoef, float fPrimary, float fSecondary
									 , unsigned short** ppnAttachBuffer)
{
	CComtradeAnalogData *pAnalog = (CComtradeAnalogData*)m_listAnalog.GetAtIndex(nAnalog);

	if (pAnalog == NULL)
	{
		*ppnAttachBuffer = NULL;
		return FALSE;
	}

	pAnalog->m_strName = strName;
	pAnalog->m_strID = strName;
	pAnalog->m_strUnit = strUnit;
	pAnalog->m_strPhaseID = strChID;
	pAnalog->m_dCoefValue = fCoef;
	pAnalog->m_dZeroValue = fZero;
	pAnalog->m_dPrimaryValue = fPrimary;
	pAnalog->m_dSecondaryValue = fSecondary;

	*ppnAttachBuffer = pAnalog->m_pnAttachBuffer;

	return TRUE;
}

BOOL CRcdComtradeFile::SetAnalogData(long nAnalog, const CString &strName, const CString &strChID, const CString &strUnit
									 , float fZero, float fCoef, float fPrimary, float fSecondary
									 , double *pdBuffer)
{
	CComtradeAnalogData *pAnalog = (CComtradeAnalogData*)m_listAnalog.GetAtIndex(nAnalog);

	if (pAnalog == NULL)
	{
		pAnalog = new CComtradeAnalogData();
		m_listAnalog.AddNewChild(pAnalog);

		if (m_nDataFileType)
		{
			pAnalog->AllocBuffer(m_nTotalPoints);
		} 
		else
		{
			pAnalog->AllocBuffer(m_nTotalPoints*2);
		}
	}

	pAnalog->m_nChannelIndex = nAnalog;
	pAnalog->m_strName = strName;
	pAnalog->m_strID = strChID;
	pAnalog->m_strPhaseID = strChID;
	pAnalog->m_strUnit = strUnit;
	pAnalog->m_dCoefValue = fCoef;
	pAnalog->m_dZeroValue = fZero;
	pAnalog->m_dPrimaryValue = fPrimary;
	pAnalog->m_dSecondaryValue = fSecondary;

	pAnalog->AllocBuffer(m_nTotalPoints);

	if (m_nDataFileType == COMTRADE_DATAFILE_TYPE_BINARY)
	{
		unsigned short *pRcdBuf = pAnalog->GetBuffer();

		long nIndex = 0;

		for (nIndex=0; nIndex<m_nTotalPoints; nIndex++)
		{
			pRcdBuf[nIndex] = (unsigned short)(pdBuffer[nIndex] / fCoef);
		}
	} 
	else
	{
		int *pRcdBuf = (int*)pAnalog->GetBuffer();

		long nIndex = 0;

		for (nIndex=0; nIndex<m_nTotalPoints; nIndex++)
		{
			pRcdBuf[nIndex] = (int)(pdBuffer[nIndex] / fCoef);
		}
	}

	return TRUE;
}

void CRcdComtradeFile::InitAfterCreate(float fFreq, long nSampRate, long nTotolPoints)
{
	m_nSamAmount = 1;
	m_dFreq = fFreq;
	m_pnDataPoints = new long[1];
	m_pnDataPoints[0] = nTotolPoints;
	m_pdSamRate = new float[1];
	m_pdSamRate[0] = nSampRate;

	m_nTotalPoints = nTotolPoints;
	CalMinMaxValue();
}

long CRcdComtradeFile::XmlReadOwn( CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strStationName);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strRecordingDeviceID);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_nComtradeVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strAllchsKey, oNode, m_nAllChs);
	xml_GetAttibuteValue(pXmlKeys->m_strUIchsKey, oNode, m_nAnalogs);
	xml_GetAttibuteValue(pXmlKeys->m_strStatechKey, oNode, m_nBinarys);
	xml_GetAttibuteValue(pXmlKeys->m_strFreqKey, oNode, m_dFreq);
	xml_GetAttibuteValue(pXmlKeys->m_strRatesKey, oNode, m_nSamAmount);
	xml_GetAttibuteValue(pXmlKeys->m_strFirstpttmKey, oNode, m_strFirstPointTime);
	xml_GetAttibuteValue(pXmlKeys->m_strTriptmKey, oNode, m_strTrigPointTime);
	xml_GetAttibuteValue(pXmlKeys->m_strDatafiletypeKey, oNode, m_nDataFileType);
	xml_GetAttibuteValue(pXmlKeys->m_strTmmultKey, oNode, m_dTimeCoef);
	return 0;
}

long CRcdComtradeFile::XmlWriteOwn( CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys )
{
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strStationName);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strRecordingDeviceID);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_nComtradeVersion);
	xml_SetAttributeValue(pXmlKeys->m_strAllchsKey, oElement, m_nAllChs);
	xml_SetAttributeValue(pXmlKeys->m_strUIchsKey, oElement, m_nAnalogs);
	xml_SetAttributeValue(pXmlKeys->m_strStatechKey, oElement, m_nBinarys);
	xml_SetAttributeValue(pXmlKeys->m_strFreqKey, oElement, m_dFreq);
	xml_SetAttributeValue(pXmlKeys->m_strRatesKey, oElement, m_nSamAmount);
	xml_SetAttributeValue(pXmlKeys->m_strFirstpttmKey, oElement, m_strFirstPointTime);
	xml_SetAttributeValue(pXmlKeys->m_strTriptmKey, oElement, m_strTrigPointTime);
	xml_SetAttributeValue(pXmlKeys->m_strDatafiletypeKey, oElement, m_nDataFileType);
	xml_SetAttributeValue(pXmlKeys->m_strTmmultKey, oElement, m_dTimeCoef);
	return 0;
}
// #include <QDebug>
CExBaseObject* CRcdComtradeFile::CreateNewChild( const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys )
{
	CExBaseObject *pNew  = NULL;
	CComtradeFileXmlRWKeys *pXmlKeys = (CComtradeFileXmlRWKeys*)pXmlRWKeys;

	//qDebug()<<strClassID;
	if (strClassID == pXmlKeys->m_strCComtradeAnalogDataKey)
	{
		pNew = new CComtradeAnalogData();
		m_listAnalog.AddTail(pNew);
	}
	else if (strClassID == pXmlKeys->m_strCComtradeBinaryDataKey)
	{
		pNew = new CComtradeBinaryData();
		m_listBinary.AddTail(pNew);
	}
	else if (strClassID == pXmlKeys->m_strCComtradeRateDataKey)
	{
		pNew = new CComtradeRateData();
		m_listRates.AddTail(pNew);
	}

	return pNew;
}

CExBaseObject* CRcdComtradeFile::CreateNewChild( long nClassID/*, BOOL &bAddToTail*/ )
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GLOBALCLASSID_CCOMTRADEANALOGDATA)
	{
		pNew = new CComtradeAnalogData();
		m_listAnalog.AddTail(pNew);
	}
	else if (nClassID == GLOBALCLASSID_CCOMTRADEBINARYDATA)
	{
		pNew = new CComtradeBinaryData();
		m_listBinary.AddTail(pNew);
	}
	else if (nClassID == GLOBALCLASSID_CCOMTRADERATEDATA)
	{
		pNew = new CComtradeRateData();
		m_listRates.AddTail(pNew);
	}

	return pNew;
}

BOOL CRcdComtradeFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRcdComtradeFile *p = (CRcdComtradeFile*)pDest;
	p->m_strComtradeFile = m_strComtradeFile;
	p->m_strBasicInfo = m_strBasicInfo;
	p->m_oTrigPointTime = m_oTrigPointTime;
	p->m_oFirstPointTime = m_oFirstPointTime;
	p->m_nBufBeginPos1 = m_nBufBeginPos1;
	p->m_nBufBeginPos2 = m_nBufBeginPos2;
	p->m_nBufLength1 = m_nBufLength1;
	p->m_nBufLength2 = m_nBufLength2;
	p->m_nBufferLen = m_nBufferLen;
	p->m_nTotalPoints = m_nTotalPoints;
	p->m_oComtradeFile = m_oComtradeFile;
	p->m_nComtradeVersion = m_nComtradeVersion;
	p->m_strStationName = m_strStationName;
	p->m_strRecordingDeviceID = m_strRecordingDeviceID;
	p->m_nAllChs = m_nAllChs;
	p->m_nAnalogs = m_nAnalogs;
	p->m_nBinarys = m_nBinarys;
	p->m_dFreq = m_dFreq;
	//	p->m_nSamAmount = m_nSamAmount;
	p->m_strTrigPointTime = m_strTrigPointTime;
	p->m_strFirstPointTime = m_strFirstPointTime;
	p->m_dTimeCoef = m_dTimeCoef;
	p->m_nDataFileType = m_nDataFileType;
	p->m_nSaveGap = m_nSaveGap;
	p->m_bCreateBuffer = m_bCreateBuffer;

	p->SetSamAmount(m_nSamAmount);

	for (long nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		p->m_pdSamRate[nIndex] = m_pdSamRate[nIndex];
		p->m_pnDataPoints[nIndex] = m_pnDataPoints[nIndex];
	}

	return TRUE;
}

void CRcdComtradeFile::CalUIMax(double &fUMax,double &fIMax)
{
	CComtradeAnalogData *pData = NULL;
	POS pos = m_listAnalog.GetHeadPosition();

	double fVal = 0;
	fUMax = -100;
	fIMax = -100;

	while(pos != NULL)
	{
		pData = (CComtradeAnalogData *)m_listAnalog.GetNext(pos);
		fVal = pData->m_nMaxCal * pData->m_dCoefValue + pData->m_dZeroValue;

		if (pData->IsAnalogUData())
		{
			if (fUMax < fVal)
			{
				fUMax = fVal;
			}
		}
		else
		{
			if (fIMax < fVal)
			{
				fIMax = fVal;
			}
		}
	}
}

long CRcdComtradeFile::GetCurrPosByTime(double dTime)
{
	if ((m_pdSamRate == NULL)||(m_pnDataPoints == NULL))
	{
		return 0;
	}

	double dCurrTime = 0.0f,dIntervalTime = 0.0f,dCurrSmpRateMaxTime = 0.0f;
	long nCurrPos = 0;

	for (long nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		dIntervalTime = 1/m_pdSamRate[nIndex];
		dCurrSmpRateMaxTime = dIntervalTime*m_pnDataPoints[nIndex];

		if ((dCurrSmpRateMaxTime+dCurrTime)>=dTime)
		{
			nCurrPos += ((dTime - dCurrTime)/dIntervalTime + 0.0001);
			break;
		} 
		else
		{
			nCurrPos += (dCurrSmpRateMaxTime/dIntervalTime + 0.0001);
			dCurrTime += dCurrSmpRateMaxTime;
		}
	}

	return nCurrPos;
}


BOOL CRcdComtradeFile::InsertCyclePointsByRelTime( double dBeginTime, double dEndTime, double dInsertTime, int nCycleIndex )
{
	long nBeginPos = GetCurrPosByTime(dBeginTime);
	long nEndPos = GetCurrPosByTime(dEndTime);
	long nInsertLength = nEndPos - nBeginPos;
	long nInsertPos = GetCurrPosByTime(dInsertTime);

	// ȷ�����С���յ㣬���������յ㶼С���ܵ���
	if (nBeginPos > nEndPos || nBeginPos >= m_nTotalPoints || nEndPos >= m_nTotalPoints) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����ʱ��ε������������¼����ٴ����룡"));
		return FALSE;
	}

	POS pos_ch = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pAnalogData = NULL;

	while(pos_ch)
	{
		pAnalogData = (CComtradeAnalogData *)m_listAnalog.GetNext(pos_ch);
		pAnalogData->InsertCyclePoints(nBeginPos, nEndPos, nInsertPos, nCycleIndex,m_nDataFileType);
	}

	POS pos_BinaryCh = m_listBinary.GetHeadPosition();
	CComtradeBinaryData *pBinaryData = NULL;
	while (pos_BinaryCh)
	{
		pBinaryData = (CComtradeBinaryData *)m_listBinary.GetNext(pos_BinaryCh);
		pBinaryData->InsertCyclePoints(nBeginPos, nEndPos, nInsertPos, nCycleIndex,m_nDataFileType);
	}

	UpdateSamDateAfterInsert(nBeginPos, nEndPos, nInsertPos, nCycleIndex);
	m_nTotalPoints += (nInsertLength/*+ 1*/) * nCycleIndex ;

// 	m_pnDataPoints[0] = m_nTotalPoints;
//	UpdateSmpRatesList();//zhouhj 2024.1.20�ڸ��²����ʹ����и���
// 	CalMinMaxValue();//ɾ�����¼��������Сֵ

	return TRUE;
}


BOOL CRcdComtradeFile::InsertCyclePointsByPoint( long nBeginPoint, long nEndPoint, long nInserPoint, int nCycleIndex )
{
	long nBeginPos = nBeginPoint;
	long nEndPos = nEndPoint;
	long nInsertLength = nEndPos - nBeginPos;
	long nInsertPos = nInserPoint;

	// ȷ�����С���յ㣬���������յ㶼С���ܵ���
	if (nBeginPos > nEndPos || nBeginPos > m_nTotalPoints || nEndPos > m_nTotalPoints) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����ʱ��ε������������¼����ٴ����룡"));
		return FALSE;
	}

	POS pos_ch = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pAnalogData = NULL;

	while(pos_ch)
	{
		pAnalogData = (CComtradeAnalogData *)m_listAnalog.GetNext(pos_ch);
		pAnalogData->InsertCyclePoints(nBeginPos, nEndPos, nInsertPos, nCycleIndex,m_nDataFileType);
	}

	POS pos_BinaryCh = m_listBinary.GetHeadPosition();
	CComtradeBinaryData *pBinaryData = NULL;
	while (pos_BinaryCh)
	{
		pBinaryData = (CComtradeBinaryData *)m_listBinary.GetNext(pos_BinaryCh);
		pBinaryData->InsertCyclePoints(nBeginPos, nEndPos, nInsertPos, nCycleIndex,m_nDataFileType);
	}

	UpdateSamDateAfterInsert(nBeginPos, nEndPos, nInsertPos, nCycleIndex);
	m_nTotalPoints += (nInsertLength/*+ 1*/) * nCycleIndex ;

	// 	m_pnDataPoints[0] = m_nTotalPoints;
	//	UpdateSmpRatesList();//zhouhj 2024.1.20�ڸ��²����ʹ����и���
// 	CalMinMaxValue();//ɾ�����¼��������Сֵ

	return TRUE;
}

BOOL CRcdComtradeFile::DeletePointsByRelTime( double dBeginTime, double dEndTime )
{
	long nBeginPos = GetCurrPosByTime(dBeginTime);
	long nEndPos = GetCurrPosByTime(dEndTime);

	// ȷ�����С���յ㣬���������յ㶼С���ܵ���
	if (nBeginPos >= nEndPos || nBeginPos >= m_nTotalPoints) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ɾ��ʱ��ε������������¼����ٴ����룡"));
		return FALSE;
	}
	else if(nEndPos >= m_nTotalPoints)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("ɾ��ʱ�̳���������ʱ�Σ������¼����ٴ����룡"));
		return FALSE;
	}

	long nDeleteLength = nEndPos - nBeginPos;

	POS pos_ch = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pAnalogData = NULL;

	while(pos_ch)
	{
		pAnalogData = (CComtradeAnalogData *)m_listAnalog.GetNext(pos_ch);
		pAnalogData->DeletePoints(nBeginPos, nEndPos,m_nDataFileType);
	}

	POS pos_BinaryCh = m_listBinary.GetHeadPosition();
	CComtradeBinaryData *pBinaryData = NULL;
	while (pos_BinaryCh)
	{
		pBinaryData = (CComtradeBinaryData *)m_listBinary.GetNext(pos_BinaryCh);
		pBinaryData->DeletePoints(nBeginPos, nEndPos,m_nDataFileType);
	}

	UpdateSamDateAfterDelete(nBeginPos, nEndPos);
	m_nTotalPoints -= nDeleteLength;// �����ܵ���

//	UpdateSmpRatesList();//zhouhj 2024.1.20�ڸ��²����ʹ����и���
	CalMinMaxValue();//ɾ�����¼��������Сֵ
	return TRUE;
}

BOOL CRcdComtradeFile::InsertNormalCyclePoints(double dVolValue,double dCurrentValue,double dTime_Second)
{
	if ((m_pdSamRate == NULL)||(m_pnDataPoints == NULL))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����ȱ�ٲ���������."));
		return FALSE;
	}

	long nInsertPoints = dTime_Second*m_pdSamRate[0];//����Ĳ�������
	m_pnDataPoints[0] += nInsertPoints;

	POS pos_ch = m_listAnalog.GetHeadPosition();
	CComtradeAnalogData *pAnalogData = NULL;

	while(pos_ch)
	{
		pAnalogData = (CComtradeAnalogData *)m_listAnalog.GetNext(pos_ch);
		pAnalogData->InsertNormalCyclePoints(dVolValue,dCurrentValue,m_pdSamRate[0],50.0f,nInsertPoints,m_nDataFileType);
	}

	//���¿�����ͨ����ͨ������
	POS pos_BinaryCh = m_listBinary.GetHeadPosition();
	CComtradeBinaryData *pBinaryData = NULL;

	while (pos_BinaryCh)
	{
		pBinaryData = (CComtradeBinaryData *)m_listBinary.GetNext(pos_BinaryCh);
		pBinaryData->InsertNormalCyclePoints(nInsertPoints,m_nDataFileType);
	}
 
	//���µ�һ�������ʵ��ܵ����������ܵĲ�������
// 	m_pnDataPoints[0] += nInsertPoints;
	UpdateSmpRatesList();
 	m_nTotalPoints += nInsertPoints;
	CalMinMaxValue();//ɾ�����¼��������Сֵ
	return TRUE;
}


long CRcdComtradeFile::FindPointIndexByRelTime( double dTime  ,double *pdTime,long nSamAmount)
	{
		for (int nIndex = 0; nIndex < m_nSamAmount; nIndex++)
		{
		int nDataPoints = m_pnDataPoints[nIndex];
	}
	if(dTime < 0 )
			{
		return -1;
				}

	int nTimeDurIndex = -1;
	for (int nIndex = 0; nIndex < nSamAmount; nIndex++)
				{
		if (dTime < pdTime[nIndex])
				{
			nTimeDurIndex = nIndex;
			break;
				}
			}

	return nTimeDurIndex;
		}

void CRcdComtradeFile::UpdateSampleRaes(long nSamAmount,const double* pdSamRate,const long* pnDataPoints )
{
	if (m_pnDataPoints != NULL)
	{
		delete[] m_pnDataPoints;
		m_pnDataPoints = NULL;
	}

	if (m_pdSamRate != NULL)
	{
		delete[] m_pdSamRate;
		m_pdSamRate = NULL;
	}

	// ��ʱ�������ڴ洢�ϲ��������
	long* tempDataPoints = new long[nSamAmount];
	float* tempSamRate = new float[nSamAmount];

	int newIndex = 0;
	for (int i = 0; i < nSamAmount; ++i)
	{
		if (i > 0 && pdSamRate[i] == pdSamRate[i - 1])
		{
			// �����������ͬ���ۼ����ݵ�
			tempDataPoints[newIndex - 1] += pnDataPoints[i];
		}
		else
		{
			// ���Ʋ����ʺ����ݵ�
			tempDataPoints[newIndex] = pnDataPoints[i];
			tempSamRate[newIndex] = pdSamRate[i];
			++newIndex;
		}
	}

	// ���º�Ĳ���������������
	m_nSamAmount = newIndex;

	//2025-3-18  �Ż�����������ڴ棬ֱ�ӷ������Ա����
	m_pnDataPoints = tempDataPoints;
	m_pdSamRate = tempSamRate;
	for (int i = 0; i < m_nSamAmount; ++i)
 	{ 
#ifdef _PSX_IDE_QT_ 
		//������
		qDebug()<< "��"<< i <<"�β�����"<<m_pdSamRate[i];
		qDebug()<< "��"<< i <<"�β�������"<<m_pnDataPoints[i];
#else
//  		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��%d�β�����:%.3f"), i, m_pdSamRate[i]);
//  		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��%d�β�������:%d"), i, m_pnDataPoints[i])	;
#endif
	}

// 	// ���·��������С����Ӧ�ϲ���Ĳ�������
// 	m_pnDataPoints = new long[m_nSamAmount];
// 	m_pdSamRate = new float[m_nSamAmount];
// 
// 	// ���ƺϲ�������ݵ���������
// 	for (int i = 0; i < m_nSamAmount; ++i)
// 	{
// 		m_pnDataPoints[i] = tempDataPoints[i];
// 		m_pdSamRate[i] = tempSamRate[i];
// 
// 		//������
// 		// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��%d�β�����:%.3f"), i, m_pdSamRate[i]);
// 		// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("��%d�β�������:%d"), i, m_pnDataPoints[i]	
// 	}
// 
// 	// �ͷ���ʱ����
// 	if (!tempDataPoints)
// 	{
// 		delete[]  tempDataPoints;
// 		tempDataPoints = NULL;
// 	}
// 	if (!tempSamRate)
// 	{
// 		delete[]  tempSamRate;
// 		tempSamRate = NULL;
// 	}

}

void CRcdComtradeFile::SaveAsciiDatDataFile(const CString& strFilePath)
{
	long nIndex = 0;

	long nSteps = 20;
	long nStepPoints = m_nTotalPoints / nSteps;
	long nStep = 0;

	if (nStepPoints > 65536)
	{
		nStepPoints = 65536;
		nStepPoints = m_nTotalPoints / nSteps;
		nSteps = m_nTotalPoints / nStepPoints + 1;
	}

	if (nStepPoints * nSteps < m_nTotalPoints)
	{
		nSteps++;
	}

	long nStepIndex = 0;

	FILE* pFile = NULL;
	CString strDatFilePath;
	//strDatFilePath.Format(_T("%s.%s"),strFilePath,g_pszKeyDat);
	strDatFilePath = strFilePath;

	CString strTempKey = CString(g_pszKeyDat);
	strDatFilePath = ChangeFilePostfix(strFilePath, _T("Apdat"));

	CString strTemp;
	char pszDatFilePath[MAX_PATH];
	CString_to_char(strDatFilePath, pszDatFilePath);
	pFile = fopen(pszDatFilePath, "wb");
	long nTmpValue = 0;
	CComtradeDataBase* pObj = NULL;
	POS pos = NULL;
	long nBinaryIndex = 0;//����ͨ������
	WORD wBinaryValue = 0;
	CString strTmp;
	unsigned short unCurrentData = 0;

	if (pFile == NULL)
		return;

	DWORD dwIndex = 1;
	DWORD dwmTimestamp = 0xFFFFFFFF; //������ʱ���ˣ���Ϊ�����ʺ͸����������µĵ�������
	nIndex = 0;
	unsigned short unCurBinaryData = 0;//zhouhj ��Ϊֻ�е�һ��������ͨ����¼������������16��ͨ����״ֵ̬���轫���¼
	double dDou = 0.0f;
	/////// ��������	
	//		if (m_nBufLength1 > 0)
	for (nIndex = 0; nIndex < m_nTotalPoints; nIndex += m_nSaveGap)
	{
		dwmTimestamp = GetCurPointTimeStamp(nIndex);
		// 		fwrite(&dwIndex, 4, 1, pFile);
		// 		fwrite(&dwmTimestamp, 4, 1, pFile);
		fprintf(pFile, "%lu,%lu", dwIndex, dwmTimestamp);
		nBinaryIndex = 0;
		wBinaryValue = 0;
		unCurBinaryData = 0;
		pos = GetHeadPosition();

		while (pos != NULL)
		{
			pObj = (CComtradeDataBase*)GetNext(pos);

			if (pObj->GetClassID() == GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			long* pBuffer = (long *)pObj->GetBuffer();
			unsigned short* pBinaryBuffer = pObj->GetBuffer();

			//���ڿ�����ͨ���ǹ���buffer������ͨ��û��ʵ�ʻ�����,����Խ���ж�
			if (pObj->m_nTotalPoints <= 0)
			{
				continue;
			}

			nTmpValue = *(pBuffer + nIndex);

			if (pObj->IsAnalogData())
			{
				CComtradeAnalogData *p = (CComtradeAnalogData*)pObj;
				nTmpValue = p->GetAttachBuffer_long(m_nDataFileType, nIndex);
				p->CalValue(nTmpValue, dDou);
				//strTmp.Format(_T("%ld\r\n"),nTmpValue);

				//fprintf(pFile, ",%.3f", dDou);
				fprintf(pFile, ",%n", nTmpValue);
			}
			else // ��Ϊ�������ǰ�����ģ��󿪹ص�˳�����
			{
				unCurrentData = *(pBinaryBuffer + nIndex);

				for (int n = 0; n < 16; ++n)
				{
					int nBitValue = unCurrentData >> n & 0x01;
					fprintf(pFile, ",%d", nBitValue);
				}
				nBinaryIndex++;
			}


		}

		nStepIndex++;

		if (nStepIndex >= nStepPoints)
		{
			nStepIndex = 0;
			////g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_SAVE_RECORDFILE, 0, MAKELONG(nStep, nSteps));
			nStep++;
		}

		dwIndex++;

		fprintf(pFile, "\n");
	}
	//////////////////////////

	fclose(pFile);
	pFile = NULL;
}

void CRcdComtradeFile::SaveBinaryDatDataFile(const CString& strFilePath)
{
	long nIndex = 0;

	long nSteps = 20;
	long nStepPoints = m_nTotalPoints / nSteps;
	long nStep = 0;

	if (nStepPoints > 65536)
	{
		nStepPoints = 65536;
		nStepPoints = m_nTotalPoints / nSteps;
		nSteps = m_nTotalPoints / nStepPoints + 1;
	}

	if (nStepPoints * nSteps < m_nTotalPoints)
	{
		nSteps++;
	}

	long nStepIndex = 0;

	FILE* pFile = NULL;
	CString strDatFilePath;
	//strDatFilePath.Format(_T("%s.%s"),strFilePath,g_pszKeyDat);
	strDatFilePath = strFilePath;

	CString strTempKey = CString(g_pszKeyDat);
	strDatFilePath = ChangeFilePostfix(strFilePath, _T("Bpdat"));

	CString strTemp;
	char pszDatFilePath[MAX_PATH];
	CString_to_char(strDatFilePath, pszDatFilePath);
	pFile = fopen(pszDatFilePath, "wb");
	unsigned short unCurrentData = 0;
	CComtradeDataBase* pObj = NULL;
	POS pos = NULL;
	long nBinaryIndex = 0;//����ͨ������
	WORD wBinaryValue = 0;

	if (pFile == NULL)
		return;

	DWORD dwIndex = 1;
	DWORD dwmTimestamp = 0xFFFFFFFF; //������ʱ���ˣ���Ϊ�����ʺ͸����������µĵ�������
	nIndex = 0;
	unsigned short unCurBinaryData = 0;//zhouhj ��Ϊֻ�е�һ��������ͨ����¼������������16��ͨ����״ֵ̬���轫���¼
	double dDou = 0.0f;
	/////// ��������	
	//		if (m_nBufLength1 > 0)
	for (nIndex = 0; nIndex < m_nTotalPoints; nIndex += m_nSaveGap)
	{
		dwmTimestamp = GetCurPointTimeStamp(nIndex);
		// 		fwrite(&dwIndex,4,1,pFile);
		// 		fwrite(&dwmTimestamp,4,1,pFile);
		fprintf(pFile, "%lu,%lu", dwIndex, dwmTimestamp);
		nBinaryIndex = 0;
		wBinaryValue = 0;
		unCurBinaryData = 0;
		pos = GetHeadPosition();

		while (pos != NULL)
		{
			pObj = (CComtradeDataBase*)GetNext(pos);

			if (pObj->GetClassID() == GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}

			unsigned short* pBuffer = pObj->GetBuffer();

			//���ڿ�����ͨ���ǹ���buffer������ͨ��û��ʵ�ʻ�����,����Խ���ж�
			if (pObj->m_nTotalPoints <= 0)
			{
				continue;
			}

			unCurrentData = *(pBuffer + nIndex);

			if (pObj->IsAnalogData())
			{
				CComtradeAnalogData *p = (CComtradeAnalogData *)pObj;
				if (unCurrentData == 0x8000)//0x8000 ����
				{
					unCurrentData = 0x8001;
				}

				p->CalValue(unCurrentData, dDou);
				fprintf(pFile, ",%lu", unCurrentData);//����ǰ����
// 				fprintf(pFile, ",%.3f", dDou);//���������
			}
			else // ��Ϊ�������ǰ�����ģ��󿪹ص�˳�����
			{
				unCurrentData = *(pBuffer + nIndex);

				for (int n = 0; n < 16; ++n)
				{
					int nBitValue = unCurrentData >> n & 0x01;
					fprintf(pFile, ",%d", nBitValue);
				}
				nBinaryIndex++;

			}
		}

		nStepIndex++;

		if (nStepIndex >= nStepPoints)
		{
			nStepIndex = 0;
			////g_theRecordApp.FireSysOptrMsg(MR1200_SYSOPTR_SAVE_RECORDFILE, 0, MAKELONG(nStep, nSteps));
			nStep++;
		}

		dwIndex++;
		fprintf(pFile, "\n", unCurrentData);
	}
	fclose(pFile);
	pFile = NULL;


}

int CRcdComtradeFile::FindPointIndexByDataPoints( int nPos, long *pdDataPoints, int &nDistance)
{
	if (pdDataPoints == NULL) 
			{
		return -1;  
		}

	int nDataPointIndex = 0;
	int nPreviousIndex = 0;
	for (int nIndex = 0; nIndex < m_nSamAmount; ++nIndex) 
	{
		if(nIndex == 0)
		{
			nDataPointIndex = pdDataPoints[nIndex] -1;//����ҿ�
		}
		else
		{
			nDataPointIndex += pdDataPoints[nIndex];
		}
		if (nPos < nDataPointIndex) 
		{
			nDistance = nPos - nPreviousIndex; // ���ò�ֵ
			return nIndex;  // ���ضε�����
		}

		nPreviousIndex = nDataPointIndex;
	}
	return -1;  // ���nPos�������жΣ��򷵻�-1
}

void CRcdComtradeFile::UpdateSamDateAfterDelete( int nBeginPos, int nEndPos )
{
	int nBeginDistance = 0 , nEndDistance = 0;

	int nBeginIndex = FindPointIndexByDataPoints(nBeginPos, m_pnDataPoints, nBeginDistance);
	int nEndIndex = FindPointIndexByDataPoints(nEndPos, m_pnDataPoints, nEndDistance);
	int nDeleteLength = nEndPos - nBeginPos;
	if(nBeginIndex == -1 || nEndIndex == -1 || nEndIndex < nBeginIndex)
	{
		return;
	}

	//���ɾ���ĵ�,��ʼ�ͽ���λ����ͬһ���������£���ֻ��Ҫ�ı�ò������µ��ܵ�������
	if (nBeginIndex == nEndIndex)
	{
		//���µ�ǰ�β�������
		m_pnDataPoints[nBeginIndex] -= nDeleteLength;
		UpdateSmpRatesList();
		return;
	}

	int nDeleteSegNum = nEndIndex - nBeginIndex;
	int nNewSamAmount = m_nSamAmount - nDeleteSegNum; // �����߽��ɾ��
	float *pdNewSamRate = NULL;
	long *pnNewDataPoints  = NULL;

	if ((nEndPos+1) == m_nTotalPoints)//���������λ���ڲ������,������ʼλ�õĵ�,ɾ������λ�õ�
	{
		pdNewSamRate = new float[nNewSamAmount];
		pnNewDataPoints  = new long[nNewSamAmount];

		for (int nIndex = 0; nIndex < m_nSamAmount; nIndex++)
		{
			if (nIndex < nBeginIndex)//С����ʼ������ʱ��ֱ�ӿ���
			{
				pnNewDataPoints[nIndex] = m_pnDataPoints[nIndex];
				pdNewSamRate[nIndex] = m_pdSamRate[nIndex];
			}
			else
			{
				pnNewDataPoints[nIndex] = (nBeginDistance + 1);
				pdNewSamRate[nIndex] = m_pdSamRate[nIndex];
				break;
			}
		}
	} 
	else//����ɾ����ʼλ�õĵ�,��������λ�õ�
			{
		if (nBeginDistance != 0)//���ɾ������ʼλ��,���Ǹò������µĵ�һ����,��������������һ��
				{
			nNewSamAmount++;
			pdNewSamRate = new float[nNewSamAmount];
		pnNewDataPoints  = new long[nNewSamAmount];
				}

		int nNewIndex = 0; // �����������

		for (int nIndex = 0; nIndex < m_nSamAmount; nIndex++)
		{
			if ((nIndex < nBeginIndex) || (nIndex > nEndIndex))//С����ʼ������ʱ��ֱ�ӿ���
				{
				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
					nNewIndex++;
				}
			else if (nIndex == nBeginIndex)//������ʼ������ʹ����ʼλ��
			{
				if (nBeginDistance != 0)
				{
					pnNewDataPoints[nNewIndex] = nBeginDistance;
					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
					nNewIndex++;
				}
			}
			else if (nIndex < nEndIndex)//������ʼ������С�ڽ���������,����
				{
					continue;
				}
			else if (nIndex == nEndIndex)//���ڽ���������,��ֱ��
				{
					pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nEndDistance;
					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
					nNewIndex++;
				}
			}
		}

	delete[] m_pnDataPoints;
	delete[] m_pdSamRate;
	// ���º�Ĳ���������������
	m_nSamAmount = nNewSamAmount;

	// ���·��������С����Ӧ�ϲ���Ĳ�������
	m_pnDataPoints = pnNewDataPoints;
	m_pdSamRate = pdNewSamRate;
	UpdateSmpRatesList();


// 	if(nBeginIndex != nEndIndex)//����ͬһ������  //zhouhj 2025.3.15 �Ż������߼�
// 	{
// 		int nDeleteSegNum = nEndIndex - nBeginIndex;
// 		int nNewSamAmount = m_nSamAmount - nDeleteSegNum; // �����߽��ɾ��
// 		float *pdNewSamRate = NULL;
// 		long *pnNewDataPoints = NULL;
// 
// 		pdNewSamRate = new float[nNewSamAmount];
// 		pnNewDataPoints = new long[nNewSamAmount];
// 
// 		int nNewIndex = 0; // �����������
// 
// 		for (int nIndex = 0; nIndex < m_nSamAmount; nIndex++)
// 		{
// 			if (nIndex < nBeginIndex)//С����ʼ������ʱ��ֱ�ӿ���
// 			{
// 				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 				nNewIndex++;
// 				continue;
// 			}
// 			else if (nIndex == nBeginIndex)//������ʼ������ʹ����ʼλ��
// 			{
// 				pnNewDataPoints[nNewIndex] = nBeginDistance + 1;
// 				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 				nNewIndex++;
// 				continue;
// 			}
// 			else if (nIndex<nEndIndex)//������ʼ������С�ڽ���������,����
// 			{
// 				continue;
// 			}
// 			else if (nIndex == nEndIndex)//���ڽ���������,��ֱ��
// 			{
// 				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nEndDistance;
// 				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 				nNewIndex++;
// 				continue;
// 			}
// 
// 			pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 			pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 			nNewIndex++;
// 
// // 			if (nIndex < nBeginIndex || nIndex > nEndIndex)
// // 			{
// // 				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// // 				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// // 				nNewIndex++;
// // 			}
// // 			else if (nIndex == nBeginIndex)
// // 			{
// // 				if (nBeginDistance == 0)
// // 				{
// // 					continue;
// // 				}
// // 				else
// // 				{
// // 					pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nBeginDistance;
// // 					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// // 					nNewIndex++;
// // 				}
// // 
// // 			}
// // 			else if (nIndex == nEndIndex)
// // 			{
// // 				if (nEndDistance == 0)
// // 				{
// // 					nNewIndex -= 1;
// // 					continue;
// // 				}
// // 				else
// // 				{
// // 					pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nEndDistance;
// // 					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// // 					nNewIndex++;
// // 				}
// // 			}
// 		}
// 
// 		delete[] m_pnDataPoints;
// 		delete[] m_pdSamRate;
// 		// ���º�Ĳ���������������
// 		m_nSamAmount = nNewSamAmount;
// 
// 		// ���·��������С����Ӧ�ϲ���Ĳ�������
// 		m_pnDataPoints = pnNewDataPoints;
// 		m_pdSamRate = pdNewSamRate;
// 		UpdateSmpRatesList();
// //		UpdateSampleRaes(nNewSamAmount, pdNewSamRate, pnNewDataPoints);
// 
// // 		delete[] pdNewSamRate;
// // 		pdNewSamRate = NULL;
// // 		delete[] pnNewDataPoints;
// // 		pnNewDataPoints = NULL;
// 	}
// 	else
// 	{
// 		//���µ�ǰ�β�������
// 		m_pnDataPoints[nBeginIndex] -= nDeleteLength;
// 	}
}

void CRcdComtradeFile::UpdateSamDateAfterInsert( int nBeginPos, int nEndPos, int nInsertPos, int nCycNum )
{
	int nBeginDistance = 0, nEndDistance = 0, nInsertDistance = 0;

	int nBeginIndex = FindPointIndexByDataPoints(nBeginPos, m_pnDataPoints, nBeginDistance);
	int nEndIndex = FindPointIndexByDataPoints(nEndPos, m_pnDataPoints, nEndDistance);
	int nInsertIndex = FindPointIndexByDataPoints(nInsertPos, m_pnDataPoints, nInsertDistance);


	if (nBeginIndex == -1 || nEndIndex == -1 || nInsertIndex == -1 || nEndIndex < nBeginIndex)
	{
		return;
	}

	if(nBeginIndex == nEndIndex)//��ͬһ������ֱ���������
				{
		m_pnDataPoints[nBeginIndex] += (nEndPos - nBeginPos) * nCycNum;
		return;
				}

	int nSamAmount = 0;
	int nInsertSegNum = nEndIndex - nBeginIndex + 1;
	int nNewSamAmount = m_nSamAmount + nInsertSegNum * nCycNum + 1;//// �и���ʱ�ǶԵģ����ǽضϵ�ʱ��Ӧ��+1
	float *pdNewSamRate = new float[nNewSamAmount];
		long *pnNewDataPoints = new long[nNewSamAmount];
	int nNewIndex = 0; // �����������

		// ����ԭ�����ǰ�벿��
		for (int nIndex = 0; nIndex <= nInsertIndex; ++nIndex)
		{
			if (nIndex == nInsertIndex)//��������ǰ����
		{
				if (nInsertDistance == 0)  // �����Ϊ���Σ��������Ʋ����
				{
					break;  // ֱ���˳�ѭ�������ٸ��Ʋ���������
				}
				else
			{
				pnNewDataPoints[nNewIndex] = nInsertDistance;
				}

				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
			}
			else
			{
				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
			}
		nNewIndex++;			
			}

	//���벿��
		for (int nCycIndex = 0; nCycIndex < nCycNum; nCycIndex++)
		{
		for (int nIndex = nBeginIndex; nIndex <= nEndIndex; ++nIndex)
			{
			if (nIndex == nBeginIndex)
			{
				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nBeginDistance;
			}
			else if (nIndex == nEndIndex)
			{
				if (nEndDistance == 0) 
					break;
				pnNewDataPoints[nNewIndex] = nEndDistance;
			}
			else
			{
				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
		}

			pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];

			// ���кϲ���飨��ǰ `pdNewSamRate` �Ƿ��ǰһ����ͬ��
			if (nNewIndex > 0 && pdNewSamRate[nNewIndex] == pdNewSamRate[nNewIndex - 1])
		{
				pnNewDataPoints[nNewIndex - 1] += pnNewDataPoints[nNewIndex];  // �ϲ���������
		}
		else
		{
				nNewIndex++;  // ֻ���ڲ��ϲ�ʱ�ŵ���
			}

		}
	}


	//��벿��
// 	int nLastIndex = nInsertIndex + nInsertSegNum * nCycNum + 1;
// 	if (bCover) { nInsertIndex += 1; }

		for (int nIndex = nInsertIndex; nIndex < m_nSamAmount; ++nIndex)
		{

		if (nIndex == nInsertIndex)
			{
				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
			pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nInsertDistance;
			}
			else
			{
					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
						pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
					}

		if (nNewIndex > 0 && pdNewSamRate[nNewIndex] == pdNewSamRate[nNewIndex - 1])
					{
			pnNewDataPoints[nNewIndex - 1] += pnNewDataPoints[nNewIndex];  // �ϲ���������
					}
		else 
					{
			nNewIndex++;  // ֻ���ڲ��ϲ�ʱ�ŵ���
					}
				}
		m_nSamAmount = nNewIndex;
 		for (int n = 0; n < nNewSamAmount; n++)
				{
//  			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����%d:�ʣ�%.3f"), n, pdNewSamRate[n]);
//  			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����%d:������%d"), n, pnNewDataPoints[n]);
#ifdef _PSX_IDE_QT_ 

			qDebug()<< n << ":��"<<pdNewSamRate[n];
			qDebug()<< n << ":����"<< pnNewDataPoints[n];
#endif
				}

		delete []m_pnDataPoints;
		delete []m_pdSamRate;

		m_pnDataPoints = pnNewDataPoints;
		m_pdSamRate = pdNewSamRate;

		UpdateSmpRatesList();

	//2025-3-18 wuxinyi �Ż�
//************************************************************************/
// 	if (nBeginIndex != nEndIndex)//����ͬһ������
// 	{
		//��Ҫ�Ķ���
// 		int nInsertSegNum = nEndIndex - nBeginIndex + 1;
// 		double *pdInsertSamRate = new double[nInsertSegNum];
// 		long *pnInsertDataPoints = new long[nInsertSegNum];
// 		int nNewIndex = 0; // �����������
// 
// 		for (int nIndex = nBeginIndex; nIndex <= nEndIndex; nIndex++)
// 		{
// 			// 			if(nIndex >= nBeginIndex && nIndex <= nEndIndex)
// 			{
// 				if (nIndex == nBeginIndex)
// 				{
// 					if (nBeginDistance == 0)//���������Ϊ0ʱ����ζ�ŵ�nNewIndex����Ϊ����
// 					{
// 						pnInsertDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 					}
// 					else
// 					{
// 						pnInsertDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nBeginDistance;
// 					}
// 
// 				}
// 				else if (nIndex == nEndIndex)
// 				{
// 					if (nEndDistance == 0)
// 					{
// 						break;
// 					}
// 
// 					pnInsertDataPoints[nNewIndex] = nEndDistance;
// 				}
// 				else
// 				{
// 					pnInsertDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 
// 				}
// 			}
// 					pdInsertSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 					nNewIndex++;
// 				}
// 
// 		//����ʹ��
// 		// 		for (int n = 0; n < nInsertSegNum; n++)
// 		// 		{
// 		// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����%d:�ʣ�%.3f"), n, pdInsertSamRate[n]);
// 		// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("����%d:������%d"), n, pnInsertDataPoints[n]);
// 		// 		}
// 
// 		//����Ϊһ������
// 		int nNewSamAmount = m_nSamAmount + nInsertSegNum * nCycNum/* +1*/;
// 		double *pdNewSamRate = new double[nNewSamAmount];
// 		long *pnNewDataPoints = new long[nNewSamAmount];
// 		nNewIndex = 0; // �����������
// 		bool bCover = false;
// 
// 		// ����ԭ�����ǰ�벿��
// 		for (int nIndex = 0; nIndex <= nInsertIndex; ++nIndex)
// 		{
// 			if (nIndex == nInsertIndex)//��������ǰ����
// 		{
// 				if (nInsertDistance == 0)  // �����Ϊ���Σ��������Ʋ����
// 				{
// 					break;  // ֱ���˳�ѭ�������ٸ��Ʋ���������
// 				}
// 				else
// 				{
// 					pnNewDataPoints[nNewIndex] = nInsertDistance;
// 
// 					if (nInsertDistance == m_pnDataPoints[nInsertIndex])
// 					{
// 						//���غ�,���һ��Ϊ֮��Ķ���
// 						bCover = true;
// 					}
// 				}
// 
// 				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 			}
// 			else
// 			{
// 				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 			}
// 				nNewIndex++;
// 			}
// 
// 		// ����������
// 		for (int nCycIndex = 0; nCycIndex < nCycNum; nCycIndex++)
// 		{
// 			for (int nIndex = 0; nIndex < nInsertSegNum; ++nIndex)
// 			{
// 				pdNewSamRate[nNewIndex] = pdInsertSamRate[nIndex];
// 				pnNewDataPoints[nNewIndex] = pnInsertDataPoints[nIndex];
// 				nNewIndex++;
// 			}
// 		}
// 
// 		int nLastIndex = nInsertIndex + nInsertSegNum * nCycNum + 1;
// 
// 		if (bCover)
// 		{
// 			nInsertIndex += 1;
// 		}
// 		else
// 		{
// 			nNewSamAmount += 1;
// 		}
// 
// 
// 		for (int nIndex = nInsertIndex; nIndex < m_nSamAmount; ++nIndex)
// 		{
// 			if (bCover)
// 			{
// 				pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 				pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 			}
// 			else
// 			{
// 				if (nNewIndex == nLastIndex)
// 				{
// 					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 					if (nInsertDistance == 0)
// 					{
// 						pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 					}
// 					else if (m_pnDataPoints[nIndex] == nInsertDistance)
// 					{
// 						continue;
// 					}
// 					else
// 					{
// 						pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex] - nInsertDistance;
// 					}
// 				}
// 				else
// 				{
// 					pdNewSamRate[nNewIndex] = m_pdSamRate[nIndex];
// 					pnNewDataPoints[nNewIndex] = m_pnDataPoints[nIndex];
// 				}
// 
// 			}
// 
// 			nNewIndex++;
// 		}
// 
// 		// 		for (int n = 0; n < nNewSamAmount; n++)
// 		// 		{
// 		// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%d:�ʣ�%.3f"), n, pdNewSamRate[n]);
// 		// 			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%d:������%d"), n, pnNewDataPoints[n]);
// 		// 		}

// 		UpdateSampleRaes(nNewSamAmount, pdNewSamRate, pnNewDataPoints);

		// �ͷ��ڴ�
// 		if (!pdInsertSamRate)
// 		{
// 			delete[] pdInsertSamRate;
// 			pdInsertSamRate = NULL;
// 		}
// 
// 		if (!pnInsertDataPoints)
// 		{
// 			delete[]  pnInsertDataPoints;
// 			pnInsertDataPoints = NULL;
// 		}

// 		if (!pdNewSamRate)
// 		{
// 			delete[]  pdNewSamRate;
// 			pdNewSamRate = NULL;
// 		}
// 
// 		if (!pnNewDataPoints)
// 		{
// 			delete[]  pnNewDataPoints;
// 			pnNewDataPoints = NULL;
// 		}

// 	}
// 	else
// 	{
// 		m_pnDataPoints[nBeginIndex] += (nEndPos - nBeginPos) * nCycNum;
// 	}

}

CComtradeBinaryData * CRcdComtradeFile::FindBinaryDataByChID( const CString &strID )
{
	POS pos = m_listBinary.GetHeadPosition();
	CComtradeBinaryData *pCurObj = NULL;
	CComtradeBinaryData *pBinaryChFind = NULL;

	while(pos)
	{
		pCurObj = (CComtradeBinaryData*)m_listBinary.GetNext(pos);

		if (pCurObj->m_strID == strID)
		{
			pBinaryChFind = pCurObj;
			break;
		}
	}
	return pBinaryChFind;
}

CComtradeBinaryData* CRcdComtradeFile::GetBinaryDataByIndex( long nIndex )
{
	return (CComtradeBinaryData*)m_listBinary.GetAtIndex(nIndex);
}

//////////////////////////////////////////////////////////////////////////
//
CRcdComtradeFileMngr* CRcdComtradeFileMngr::g_pCComtradeMngr = NULL;
long CRcdComtradeFileMngr::g_nComtradeMngrRef = 0;
const CString CRcdComtradeFileMngr::g_strComtradeFileFilter = _T("COMTRADE File(*.cfg)|*.cfg|COMTRADE File(*.dat)|*.dat||");

CRcdComtradeFileMngr::CRcdComtradeFileMngr()
{

}

CRcdComtradeFileMngr::~CRcdComtradeFileMngr()
{

}


CRcdComtradeFileMngr* CRcdComtradeFileMngr::Create()
{
	g_nComtradeMngrRef++;

	if (g_nComtradeMngrRef == 1)
	{
		g_pCComtradeMngr = new CRcdComtradeFileMngr();

	}

	// 	g_pCComtradeMngr->m_bCreateBuffer = bCreateBuffer;

	return g_pCComtradeMngr;
}

void CRcdComtradeFileMngr::Release()
{
	g_nComtradeMngrRef--;

	if (g_nComtradeMngrRef == 0)
	{
		delete g_pCComtradeMngr;
		g_pCComtradeMngr = NULL;
	}
}

BOOL CRcdComtradeFileMngr::PopOpenComtradeFile(CString &strFile)
{
	//xxy
#ifndef _PSX_IDE_QT_
	BOOL b = PopupOpenFileDialog(AfxGetMainWnd(), strFile, g_strComtradeFileFilter, _T("cfg"), _T("COMTRADE file"));
#endif

	return TRUE;
}

CRcdComtradeFile* CRcdComtradeFileMngr::OpenComtradeFile()
{
	//xxy
#ifndef _PSX_IDE_QT_
	CString strFile;

	if (! PopOpenComtradeFile(strFile))
	{
		return NULL;
	}
	else
	{
		return OpenComtradeFile(strFile);
	}
#endif
	return NULL;
}

CRcdComtradeFile* CRcdComtradeFileMngr::NewComtradeFile()
{
	CRcdComtradeFile *pFile = new CRcdComtradeFile(TRUE);
	g_pCComtradeMngr->AddNewChild(pFile);

	return pFile;
}

void CRcdComtradeFileMngr::AddNewComtradeFileChild(CRcdComtradeFile *pChild)
{
	g_pCComtradeMngr->AddNewChild(pChild);
}

CRcdComtradeFile* CRcdComtradeFileMngr::OpenComtradeFile(const CString &strFile)
{
	CRcdComtradeFile *pFile = (CRcdComtradeFile*)g_pCComtradeMngr->FindByID(strFile);

	if (pFile != NULL)
	{
		return pFile;
	}

	pFile = new CRcdComtradeFile(TRUE);
	pFile->ReadComtradeFile(strFile);
	g_pCComtradeMngr->AddNewChild(pFile);

	return pFile;
}

CRcdComtradeFile* CRcdComtradeFileMngr::FindComtradeFile(const CString &strFile)
{
	CRcdComtradeFile *pFile = (CRcdComtradeFile*)g_pCComtradeMngr->FindByID(strFile);

	return pFile;
}
CRcdComtradeFile* CRcdComtradeFileMngr::GetComtradeFile(long nIndex)
{
	if (g_pCComtradeMngr == NULL)
	{
		return NULL;
	}

	return (CRcdComtradeFile*)g_pCComtradeMngr->GetAtIndex(nIndex);
}

BOOL CRcdComtradeFileMngr::CloseComtradeFile(const CString &strFile)
{
	CRcdComtradeFile *pFile = (CRcdComtradeFile*)g_pCComtradeMngr->FindByPath(strFile);

	if (pFile == NULL)
	{
		return TRUE;
	}

	g_pCComtradeMngr->Delete(pFile);

	return TRUE;
}

BOOL CRcdComtradeFileMngr::CloseComtradeFile(CRcdComtradeFile *pComtradeFile)
{
	return g_pCComtradeMngr->Delete(pComtradeFile);
}

long CRcdComtradeFileMngr::GetComtradeFileCount()
{
	return g_pCComtradeMngr->GetCount();
}
void CRcdComtradeFileMngr::SaveThisXml( CString &strPath )
{
	CRcdComtradeFile *pFile = (CRcdComtradeFile*)g_pCComtradeMngr->FindByPath(strPath);

	if (pFile==NULL)
	{
		return;
	}

	CString strDatFilePath = ChangeFilePostfix(strPath, _T("xml"));
	pFile->SaveXmlFile(strDatFilePath, CComtradeFileXmlRWKeys::g_pXmlKeys);
}

CExBaseObject *CRcdComtradeFileMngr::FindByPath(CString strPath)
{
	POS pos = GetHeadPosition();

	while (pos)
	{
		CRcdComtradeFile *pObj = (CRcdComtradeFile *)GetNext(pos);
		if (pObj->m_strComtradeFile == strPath)
		{
			return pObj;
		}
	}
	return NULL;
}
