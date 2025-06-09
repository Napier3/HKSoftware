// RtMemBufferMngr.cpp: implementation of the CRtMemBufferMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "RtMemBufferMngr.h"

#include "..\MR1200BaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CRtMemBufferMngr::g_pszKeyRtBuffer   = "RtBuffer";
const char* CRtMemBufferMngr::g_pszKeyMaxBuffer  = "MaxBuffer";
const char* CRtMemBufferMngr::g_pszKeyFileFormat = "FileFormat";
const char* CRtMemBufferMngr::g_pszKeyTimeGap    = "TimeGap";

long CRtMemBufferMngr::g_nRtMemBufferRefCount    = 0;
CRtMemBufferMngr* CRtMemBufferMngr::g_pRtMemBufferMngr = NULL;


CRtMemBufferMngr* CRtMemBufferMngr::CreateRtMemBufferMngr()
{
	g_nRtMemBufferRefCount++;

	if (g_nRtMemBufferRefCount == 1)
	{
		g_pRtMemBufferMngr = new CRtMemBufferMngr();
	}

	return g_pRtMemBufferMngr;
}

long CRtMemBufferMngr::Release()
{
	if (g_nRtMemBufferRefCount > 0)
	{
		g_nRtMemBufferRefCount--;
		
		if (g_nRtMemBufferRefCount == 0)
		{
			delete g_pRtMemBufferMngr;
			g_pRtMemBufferMngr = NULL;
		}
	}

	return g_nRtMemBufferRefCount;
}

CExBaseObject* CRtMemBufferMngr::FindBufferByBufferID(LPCTSTR pszBufferID)
{
	if (g_pRtMemBufferMngr == NULL)
	{
		return NULL;
	}
	else
	{
		return g_pRtMemBufferMngr->FindByBufferID(pszBufferID);
	}
}

float* rt_GetMemValueFloatRefByID(char *pszID)
{
	return NULL;
}

unsigned short* rt_GetMemValueUnsingedShortRefByID(char *pszID)
{
	if (CRtMemBufferMngr::g_pRtMemBufferMngr == NULL)
	{
		return NULL;
	}

	return CRtMemBufferMngr::g_pRtMemBufferMngr->FindUShortByBufferID(pszID);
}

long rt_GetMemValueFIFOIndexByID(char *pszID)
{
	if (CRtMemBufferMngr::g_pRtMemBufferMngr == NULL)
	{
		return -1;
	}
	
	return CRtMemBufferMngr::g_pRtMemBufferMngr->GetMemIndexByBufferID(pszID);
}

CRtMemBufferMngr::CRtMemBufferMngr()
{
	long nIndex = 0;

	for (nIndex = 0; nIndex< MAX_MR1200_CHANNELS; nIndex++)
	{
		m_ppRtMemBufferMngr[nIndex] = NULL;
	}
	
	for (nIndex = 0; nIndex< MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		m_ppVariableAttrBuffer[nIndex] = NULL;
	}

	m_nChannels			       = 0;
	m_nComplexChannels         = 0;
	m_bHasGPS			       = FALSE;
	m_pHdMemBuffer		       = NULL;
	m_nMaxSpyBuffer			   = 0;
	m_nMaxRecordBuffer		   = 0;
	m_nMaxAttrBuffer		   = 0;
	m_nMaxHdBuffer			   = 0;
	m_nCurrHdBufferCopyPos	   = 0;

	m_n64RecordHeadIndex = 0;
	m_n64SpyHeadIndex    = 0;
	m_n64CurrCalIndex    = 0;
	m_pHdMemBuffer = new CMemBuffer_UnsignedShort();
	m_pAttrTimeBuffer = new CMemBuffer_UnsignedShort();
	m_pAttrTimeBuffer->m_strBufferID = g_pszAttrTimeBufferID;
#ifdef _debug_complex_channel
	m_pComplexChannel = NULL;
#endif
}

CRtMemBufferMngr::~CRtMemBufferMngr()
{
	Free();
}

CMemBuffer_UnsignedShort* CRtMemBufferMngr::GetMemBuffer(long nChannenIndex)
{
	CMemBuffer_UnsignedShort* pBuffer = NULL;
	CRtMemBufferChannel* pChannel = NULL;
	
	pChannel = m_ppRtMemBufferMngr[nChannenIndex];
	
	if (pChannel) 
	{
		pBuffer = pChannel->GetRecordMemBuffer();
	}

	return pBuffer;
}

unsigned short* CRtMemBufferMngr::GetBuffer(long nChannenIndex)
{
	unsigned short* pBuffer = NULL;
	CRtMemBufferChannel* pChannel = NULL;
	
	pChannel=m_ppRtMemBufferMngr[nChannenIndex];
	
	if (pChannel) 
	{
		pBuffer = pChannel->GetRecordMemBuffer2();
	}
	
	return pBuffer;
}

long CRtMemBufferMngr::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
{
	return 0;
}

//后面的和缓存大小有关的参数都是实际使用的缓存大小
//lMaxBuffer需要是nFIFOUnitSize的整数倍
//nMaxRecordBuffer需要是nGap的整数倍
void CRtMemBufferMngr::Init(long nMaxSpyBuffer, long nMaxRecordBuffer, long nMaxAttrBuffer, long nMaxHdBuffer)
{
	nMaxHdBuffer /= 2;   //unsigned short == 2 byte
	//hd buffer
	long nTemp = nMaxHdBuffer % g_nFIFOUnitSize;
	nMaxHdBuffer = nMaxHdBuffer + g_nFIFOUnitSize - nTemp;
	m_nMaxHdBuffer = nMaxHdBuffer;
	ASSERT (nMaxHdBuffer % g_nFIFOUnitSize == 0);
	
	long nBuffers = 0;
	
	//spy buffer
	nBuffers = GetSpyBuffers();

	if (nBuffers > 0)
	{
		m_nMaxSpyBuffer = nMaxSpyBuffer / nBuffers;
		m_nMaxSpyBuffer /= 2;   //unsigned short == 2 byte
	}

	//record buffer
	nBuffers = GetRecordBuffers();

	if (nBuffers > 0)
	{
		m_nMaxRecordBuffer = nMaxRecordBuffer / nBuffers;
		m_nMaxRecordBuffer /= 2;   //unsigned short == 2 byte
	}

	//attr buffer
	nBuffers = GetAttrBuffers();

	if (nBuffers > 0)
	{
		m_nMaxAttrBuffer = nMaxAttrBuffer / nBuffers;
		m_nMaxAttrBuffer /= 4;   //unsigned short == 2 byte
	}

	AllocBuffers();
	InitComplexChScript();
}

void CRtMemBufferMngr::InitBuffers()
{
	long nIndex=0;
	long nSpyBuffer = m_nMaxSpyBuffer;

	FreeBuffer();
	InitPara();

	long nRtChannels = m_nChannels;

	if (m_bHasGPS)
	{
		nRtChannels--;
	}
	
	for (nIndex=0; nIndex<nRtChannels; nIndex++)
	{
		m_ppRtMemBufferMngr[nIndex] = new CRtMemBufferChannel();
		m_ppRtMemBufferMngr[nIndex]->SetUseRecordBuffer();
		m_ppRtMemBufferMngr[nIndex]->SetUseSpyBuffer();
		m_ppRtMemBufferMngr[nIndex]->Init();
	}
	
	if (m_bHasGPS)
	{
		m_ppRtMemBufferMngr[nIndex] = new CRtMemBufferChannel();
		m_ppRtMemBufferMngr[nIndex]->SetUseRecordBuffer();
		m_ppRtMemBufferMngr[nIndex]->SetUseSpyBuffer();
		m_ppRtMemBufferMngr[nIndex]->Init();
	}

	long nChannel = 0;
	for (nIndex=0; nIndex<m_nComplexChannels; nIndex++)
	{
		nChannel = m_nChannels + nIndex;
		m_ppRtMemBufferMngr[nChannel] = new CRtMemBufferChannel();
		m_ppRtMemBufferMngr[nChannel]->SetRtChTypeComplex();
		m_ppRtMemBufferMngr[nChannel]->SetUseRecordBuffer();
		m_ppRtMemBufferMngr[nChannel]->SetUseSpyBuffer();
		m_ppRtMemBufferMngr[nIndex]->Init();

#ifdef _debug_complex_channel
		m_pComplexChannel = m_ppRtMemBufferMngr[nChannel];
#endif
	}
}

void CRtMemBufferMngr::AllocBuffers()
{
	long nIndex=0;
	UINT nChIndex = 0;

	InitPara();
	m_pHdMemBuffer->SetBufferLength(m_nMaxHdBuffer);

	//spy and record buffer
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			m_ppRtMemBufferMngr[nIndex]->SetMemBufferLength(m_nMaxRecordBuffer, m_nMaxSpyBuffer);
			m_ppRtMemBufferMngr[nIndex]->SetChIndex(nChIndex);
		}
	}

	//attr buffer
	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			m_ppVariableAttrBuffer[nIndex]->SetBufferLength(m_nMaxAttrBuffer);
		}
	}

	m_pAttrTimeBuffer->SetBufferLength(m_nMaxAttrBuffer);

#ifdef _USE_DEBUG_SPY_
	CMR1200BaseApp *theApp = (CMR1200BaseApp *)AfxGetApp();
	CDebugDataOnline *pDebugData = theApp->CreateOnlineDebugData(0, 11);
	pDebugData->m_nRecordBufLen = m_nMaxRecordBuffer;
	pDebugData->m_nRecordDataLen = m_nMaxSpyBuffer;
	pDebugData->m_nRecordFillBeginPos = m_nMaxAttrBuffer;
	pDebugData->m_nAttrBufLen = -1;
	pDebugData->m_nAttrDataLen = -1;
	pDebugData->m_nAttrFillBeginPos = -1;
	pDebugData->m_nRecordWriteLen = -1;
	pDebugData->m_nAttrWriteLen = -1;
	pDebugData->m_nRecordBufLen = -1;
#endif
	
	
}

CMemBuffer_UnsignedShort* CRtMemBufferMngr::GetSpyMemBuffer(long nChannenIndex)
{
	CMemBuffer_UnsignedShort* pBuffer = NULL;
	CRtMemBufferChannel* pChannel = NULL;
	
	pChannel=m_ppRtMemBufferMngr[nChannenIndex];
	
	if (pChannel) 
	{
		pBuffer = pChannel->GetSpyMemBuffer();
	}
	
	return pBuffer;
}

unsigned short* CRtMemBufferMngr::GetSpyBuffer(long nChannenIndex)
{
	unsigned short* pBuffer = NULL;
	CRtMemBufferChannel* pChannel = NULL;
	
	pChannel=m_ppRtMemBufferMngr[nChannenIndex];
	
	if (pChannel) 
	{
		pBuffer = pChannel->GetSpyMemBuffer2();
	}
	
	return pBuffer;
}

long CRtMemBufferMngr::AppendHDBufferData(unsigned short *pHDData, long nLength)
{
	long nPos =m_pHdMemBuffer->CopyBuffer(pHDData, nLength);
	CopyHdBufferToSpyBuffer();
	CopySpyBufferToRecordBuffer(g_nSampleGap);

	return nPos;
}

//现在没有用到
void CRtMemBufferMngr::SetZeroValue(double *pdValue, double *pdCoef)
{
	for(long i = 0 ; i < m_nChannels ; i++)
	{
		g_pZeroValue[i] = pdValue[i];
		g_pCoefValue[i] = pdCoef[i];
	}
}

void CRtMemBufferMngr::CopyHdBufferToSpyBuffer()
{
	long nHdDataFillBeginPos = m_pHdMemBuffer->GetDataFillBeginPosition();
	long nHdBufferLength = m_pHdMemBuffer->GetBufferLength();  
	long nLenCopy = 0;
	
	if(nHdDataFillBeginPos > m_nCurrHdBufferCopyPos)
	{//此次拷贝只需要拷贝一次缓冲区
		nLenCopy = nHdDataFillBeginPos - m_nCurrHdBufferCopyPos;//总长度
		//nLenCopy = nLenCopy - nLenCopy % g_nFIFOUnitSize ;     //去掉不完整的FIFO数据，得到此次需要拷贝的数据长度 //????
		nLenCopy = nLenCopy - nLenCopy % g_nFIFOUnitSize;     //得到此次需要拷贝的数据长度，通道的倍数
		CopyHdBufferToSpyBuffer(m_nCurrHdBufferCopyPos, nLenCopy + m_nCurrHdBufferCopyPos );
		m_nCurrHdBufferCopyPos += nLenCopy;
	}
	else
	{//此次拷贝需要拷贝两次缓冲区
		//第一次，当前拷贝位置到HdBuffer缓冲区末尾，因为HdBuffer缓冲区分配为g_nFIFOUnitSize的整数倍
		//所以，不需要再去掉不完整的FIFO数据，但调试的时候，增加着一个限制的判断
		nLenCopy = nHdBufferLength - m_nCurrHdBufferCopyPos;
		ASSERT (nLenCopy % g_nFIFOUnitSize == 0);  //调试的时候，增加着一个限制的判断
		CopyHdBufferToSpyBuffer(m_nCurrHdBufferCopyPos, nLenCopy + m_nCurrHdBufferCopyPos);
		
		//第二次拷贝，缓冲区头到HdBuffer填充的位置
		nLenCopy = nHdDataFillBeginPos;//总长度
		nLenCopy = nLenCopy - nLenCopy % g_nFIFOUnitSize ;

		if (nLenCopy > 0)
		{
			CopyHdBufferToSpyBuffer(0, nLenCopy );//2009.10.13 fdp modified
		}
		
		m_nCurrHdBufferCopyPos = nLenCopy;
	}
}

void CRtMemBufferMngr::CopyHdBufferToSpyBuffer(long nHdBufferBegin, long nHdBufferEnd)
{
	short nZeroValue = 0;
	long nPos1Begin = -1;
	long nPos1End = -1;
	long nPos2Begin = -1;
	long nPos2End = -1;
	long nLengthCopy = (nHdBufferEnd - nHdBufferBegin) / g_nFIFOUnitSize;

	CMemBuffer_UnsignedShort *pSpyMemBuffer = m_ppRtMemBufferMngr[0]->GetSpyMemBuffer();

	long nSpyBufferFillBeginPos1 = pSpyMemBuffer->GetDataFillBeginPosition();
	
	//获得拷贝数据的起始位置和终止位置,第三个参数是FLASE是由于我们只是获得地址而不是改变地址
	pSpyMemBuffer->CopyBuffer(nLengthCopy, 1, FALSE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);
	
	ASSERT ( (nPos1Begin >= 0) && ( 0 < nPos1End && nPos1End >= nPos1Begin));//当只有最后一个时相等
	
	unsigned short *pHdBuffer = m_pHdMemBuffer->GetBuffer();
	unsigned short *pHdTemp = NULL;
	unsigned short *pHdEnd = NULL;
	long nChannel = 0;
	unsigned short *pnSpyMemBuffer = NULL;
	unsigned short *pDest = NULL;
	unsigned short *pDestEnd = NULL;
	pHdEnd = pHdBuffer + nHdBufferEnd;

	//外层循环小，内层循环大，提高程序运行的速度
	for (nChannel=0; nChannel<MAX_MR1200_CHANNELS; nChannel++)
	{
		if (m_ppRtMemBufferMngr[nChannel] == NULL)
		{
			break;
		}
		
		//如果是复合通道,跳出本次循环
		if (m_ppRtMemBufferMngr[nChannel]->IsRtChTypeComplex() )
		{
			continue;
		}

		pnSpyMemBuffer = m_ppRtMemBufferMngr[nChannel]->GetSpyMemBuffer2();

		if (pnSpyMemBuffer == NULL)
		{
			continue;
		}
		
		//拷贝的起始位置：从HdBuffer开始拷贝的位置+当前通道在FIFO中的相对位置
		pHdTemp = pHdBuffer + nHdBufferBegin + g_pChannelFIFOIndex[nChannel];

		//第一次拷贝目标位置：起始位置和结束位置
		pDest = pnSpyMemBuffer + nPos1Begin;
		pDestEnd = pnSpyMemBuffer + nPos1End;
		
		//拷贝：拷贝的循环条件可以使用HDBuffer，也可以使用SpyBuffer
		//此处可能会有两处SpyBuffer需要拷贝，所以使用SpyBuffer作条件
		
		if (g_pChannelFIFOIndex[nChannel] == 12 || g_pChannelFIFOIndex[nChannel] == 13)
		{
			while (pDest < pDestEnd)//去掉原来的等于号，nPos1Begin到nPos1End-1
			{			
				//*pDest = 0 - (short)*pHdTemp;
				*pDest = *pHdTemp;
				pDest++;
				pHdTemp += g_nFIFOUnitSize;
				
			}
			
			//第二次拷贝目标位置：起始位置和结束位置
			
			if (nPos2Begin >= 0)
			{
				pDest = pnSpyMemBuffer + nPos2Begin;
				pDestEnd = pnSpyMemBuffer + nPos2End;
				
				//拷贝：拷贝的循环条件可以使用HDBuffer，也可以使用SpyBuffer
				//此处可能会有两处SpyBuffer需要拷贝，所以使用SpyBuffer作条件
				while (pDest < pDestEnd)
				{
					//*pDest = 0 - (short)*pHdTemp;
					*pDest = *pHdTemp;
					pDest++;
					pHdTemp += g_nFIFOUnitSize;			
				}	
			}
		}
		else
		{
			while (pDest < pDestEnd)//去掉原来的等于号，nPos1Begin到nPos1End-1
			{			
				*pDest = 0 - (short)*pHdTemp;
				//			*pDest = *pHdTemp;
				pDest++;
				pHdTemp += g_nFIFOUnitSize;
				
			}
			
			//第二次拷贝目标位置：起始位置和结束位置
			
			if (nPos2Begin >= 0)
			{
				pDest = pnSpyMemBuffer + nPos2Begin;
				pDestEnd = pnSpyMemBuffer + nPos2End;
				
				//拷贝：拷贝的循环条件可以使用HDBuffer，也可以使用SpyBuffer
				//此处可能会有两处SpyBuffer需要拷贝，所以使用SpyBuffer作条件
				while (pDest < pDestEnd)
				{
					*pDest = 0 - (short)*pHdTemp;
					//				*pDest = *pHdTemp;
					pDest++;
					pHdTemp += g_nFIFOUnitSize;			
				}	
			}
		}
	}
	
	//移动SpyMemBuffer位置,这个地方的用处，目的是修改起点地址，而不是获得地址，所以第三个参数是TURE
	for (nChannel=0; nChannel<MAX_MR1200_CHANNELS; nChannel++)
	{
		if (m_ppRtMemBufferMngr[nChannel] == NULL)
		{
			break;
		}
		
		pSpyMemBuffer = m_ppRtMemBufferMngr[nChannel]->GetSpyMemBuffer();

		if (pSpyMemBuffer != NULL)
		{
			pSpyMemBuffer->CopyBuffer(nLengthCopy, 1, TRUE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);
		}
	}

	//更新监视缓存的头索引
	pSpyMemBuffer = m_ppRtMemBufferMngr[0]->GetSpyMemBuffer();
	long nSpyBufferFillBeginPos2 = pSpyMemBuffer->GetDataFillBeginPosition();

	if (nSpyBufferFillBeginPos2 < nSpyBufferFillBeginPos1)
	{
		m_n64SpyHeadIndex += pSpyMemBuffer->GetBufferLength();
	}
	
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//计算ComplexBuffer起始位置-终止位置之间的数据
	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	long nChannels = m_nChannels + m_nComplexChannels;
#ifdef COMPLEXVARIABLE_USE_FLOAT
	CMemBuffer_Float *pLSpyMemBuffer = NULL;
#else
	CMemBuffer_Long *pLSpyMemBuffer = NULL;
#endif

	for (nChannel=0; nChannel<MAX_MR1200_CHANNELS; nChannel++)
	{
		if (m_ppRtMemBufferMngr[nChannel] == NULL)
		{
			break;
		}

		if (!m_ppRtMemBufferMngr[nChannel]->IsRtChTypeComplex())
		{
			continue;
		}
		
		pLSpyMemBuffer = m_ppRtMemBufferMngr[nChannel]->GetLSpyMemBuffer();

		if (pLSpyMemBuffer != NULL)
		{
			pLSpyMemBuffer->CopyBuffer(nLengthCopy, 1, FALSE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);
			pLSpyMemBuffer->ExecScript(nPos1Begin, nPos1End, nPos2Begin, nPos2End);
			pLSpyMemBuffer->CopyBuffer(nLengthCopy, 1, TRUE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);
		}
	}
}

void CRtMemBufferMngr::CopySpyBufferToRecordBuffer(long nGap)
{
	long nChannels = m_nChannels;
	long nIndex = 0;
	CRtMemBufferChannel* pChannel = NULL;

	if (m_bHasGPS)
	{
		nChannels--;
	}

	CMemBuffer_UnsignedShort* pRecordMemBuffer = NULL;
	long nRecordBufferFillBeginPos1 = -1;

	for(nIndex = 0; nIndex < MAX_MR1200_CHANNELS ; nIndex++)
	{
		pChannel = m_ppRtMemBufferMngr[nIndex];
		
		if (pChannel != NULL)
		{
			pRecordMemBuffer = pChannel->GetRecordMemBuffer();
			
			if (pRecordMemBuffer != NULL)
			{
				nRecordBufferFillBeginPos1 = pRecordMemBuffer->GetDataFillBeginPosition();
				break;
			}
		}
		else
		{
			break;
		}
	}	

	for(nIndex = 0; nIndex < MAX_MR1200_CHANNELS ; nIndex++)
	{
		pChannel = m_ppRtMemBufferMngr[nIndex];

		if (pChannel != NULL)
		{
			pChannel->CopySpyMemBufferToRecordBuffer(nGap);
		}
		else
		{
			break;
		}
	}

	if (pRecordMemBuffer != NULL)
	{
		long nRecordBufferFillBeginPos2 = pRecordMemBuffer->GetDataFillBeginPosition();
		
		if (nRecordBufferFillBeginPos2 < nRecordBufferFillBeginPos1)
		{
			m_n64RecordHeadIndex += pRecordMemBuffer->GetBufferLength();
		}
	}
}


void CRtMemBufferMngr::Free()
{
//	AfxMessageBox("CRtMemBufferMngr::Free()1");
/*	m_bHasGPS = FALSE;
	long nIndex=0;
	

	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			delete m_ppRtMemBufferMngr[nIndex];
			m_ppRtMemBufferMngr[nIndex] = NULL;
		}
	}	
	
	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			delete m_ppVariableAttrBuffer[nIndex];
			m_ppVariableAttrBuffer[nIndex] = NULL;
		}
	}	*/

	FreeBuffer();

//	AfxMessageBox("CRtMemBufferMngr::Free()2");

	if (m_pHdMemBuffer != NULL)
	{
		m_pHdMemBuffer->FreeBuffer();
		delete m_pHdMemBuffer;
		m_pHdMemBuffer = NULL;
	}
	
//	AfxMessageBox("CRtMemBufferMngr::Free()3");	

	if (m_pAttrTimeBuffer != NULL)
	{
		m_pAttrTimeBuffer->FreeBuffer();
		delete m_pAttrTimeBuffer;
		m_pAttrTimeBuffer = NULL;
	}
	
//	AfxMessageBox("CRtMemBufferMngr::Free()4");
}

void CRtMemBufferMngr::FreeBuffer()
{
	m_bHasGPS = FALSE;
	m_nChannels = 0;
	m_n64RecordHeadIndex = 0;
	m_n64SpyHeadIndex = 0;
	m_n64CurrCalIndex = 0;
	m_nComplexChannels = 0;
	long nIndex = 0;

//	AfxMessageBox("CRtMemBufferMngr::FreeBuffer()1");
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			delete m_ppRtMemBufferMngr[nIndex];
			m_ppRtMemBufferMngr[nIndex] = NULL;
		}
	}	
	
//	AfxMessageBox("CRtMemBufferMngr::FreeBuffer()2");

	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			delete m_ppVariableAttrBuffer[nIndex];
			m_ppVariableAttrBuffer[nIndex] = NULL;
		}
	}

}

void CRtMemBufferMngr::InitPara()
{
	m_nCurrHdBufferCopyPos	   = 0;

	if (m_pHdMemBuffer)
	{
		m_pHdMemBuffer->Init();
	}

	for(long i = 0 ; i< m_nChannels ; i++)
	{
		CRtMemBufferChannel* pChannel = m_ppRtMemBufferMngr[i];

		if (pChannel)
		{
			pChannel->Init();
		}
	}
}

void CRtMemBufferMngr::InitDataPos()
{
	m_nCurrHdBufferCopyPos	   = 0;
	
	if (m_pAttrTimeBuffer != NULL)
	{
		m_pAttrTimeBuffer->Init();
	}

	if (m_pHdMemBuffer != NULL)
	{
		m_pHdMemBuffer->Init();
	}
	
	long nIndex = 0;

	for(nIndex = 0 ; nIndex< MAX_MR1200_CHANNELS ; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			m_ppRtMemBufferMngr[nIndex]->InitDataPos();
		}
		else
		{
			break;
		}
	}
	
	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			m_ppVariableAttrBuffer[nIndex]->Init();
		}
	}

}

//缓冲区的查找
CExBaseObject* CRtMemBufferMngr::FindByBufferID(LPCTSTR pszBufferID)
{
	CExBaseObject *pFind = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			pFind = (m_ppRtMemBufferMngr[nIndex])->FindByBufferID(pszBufferID);
			
			if (pFind != NULL)
			{
				break;
			}
		}
	}

	if (pFind != NULL)
	{
		return pFind;
	}

	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			if (m_ppVariableAttrBuffer[nIndex]->m_strBufferID == pszBufferID)
			{
				pFind = m_ppVariableAttrBuffer[nIndex];
				break;
			}
		}
	}

	if (m_pAttrTimeBuffer->m_strBufferID == pszBufferID)
	{
		pFind = m_pAttrTimeBuffer;
	}

	return pFind;
}

unsigned short* CRtMemBufferMngr::FindUShortByBufferID(LPCTSTR pszBufferID)
{
	CExBaseObject *pFind = NULL;
	pFind = FindByBufferID(pszBufferID);

	UINT nClassID = pFind->GetClassID();

	if (nClassID == MEMCLASSID_COMPLEXUSHORT || nClassID == MEMCLASSID_USHORT)
	{
		return ((CMemBuffer_UnsignedShort*)pFind)->GetBuffer();
	}
	else
	{
		return NULL;
	}
}

long CRtMemBufferMngr::GetMemIndexByBufferID(LPCTSTR pszBufferID)
{
	CExBaseObject *pFind = NULL;
	
	long nIndex = 0;
	long nFind = -1;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			pFind = (m_ppRtMemBufferMngr[nIndex])->FindByBufferID(pszBufferID);
			
			if (pFind != NULL)
			{
				nFind = nIndex;
				break;
			}
		}
	}
	
	
	return nFind;
}


long CRtMemBufferMngr::GetAttrMemIndexByBufferID(LPCTSTR pszBufferID)
{
	CExBaseObject *pFind = NULL;
	
	long nIndex = 0;
	long nFind = -1;
	
	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			if (stricmp(m_ppVariableAttrBuffer[nIndex]->m_strBufferID, pszBufferID) == 0)
			{
				nFind = nIndex;
				break;
			}
		}
	}
	
	return nFind;
}

long* CRtMemBufferMngr::FindLongByBufferID(LPCTSTR pszBufferID)
{
	CExBaseObject *pFind = NULL;
	pFind = FindByBufferID(pszBufferID);
	
	UINT nClassID = pFind->GetClassID();
	
	if (nClassID == MEMCLASSID_COMPLEXLONG || nClassID == MEMCLASSID_LONG)
	{
		return ((CMemBuffer_Long*)pFind)->GetBuffer();
	}
	else
	{
		return NULL;
	}	
}

float* CRtMemBufferMngr::FindFloatByBufferID(LPCTSTR pszBufferID)
{
	CExBaseObject *pFind = NULL;
	pFind = FindByBufferID(pszBufferID);
	
	UINT nClassID = pFind->GetClassID();
	
	if (nClassID == MEMCLASSID_COMPLEXFLOAT || nClassID == MEMCLASSID_FLOAT)
	{
		return ((CMemBuffer_Float*)pFind)->GetBuffer();
	}
	else
	{
		return NULL;
	}		
}

double* CRtMemBufferMngr::FindDoubleByBufferID(LPCTSTR pszBufferID)
{
	CExBaseObject *pFind = NULL;
	pFind = FindByBufferID(pszBufferID);
	
	UINT nClassID = pFind->GetClassID();
	
	if (nClassID == MEMCLASSID_COMPLEXDOUBLE || nClassID == MEMCLASSID_DOUBLE)
	{
		return ((CMemBuffer_Double*)pFind)->GetBuffer();
	}
	else
	{
		return NULL;
	}	
}

CRtMemBufferChannel* CRtMemBufferMngr::FindMemBufferChannel(const CString &strChID)
{
	CRtMemBufferChannel *pFind = NULL;
	long nIndex = 0;
	
	for (nIndex=0; nIndex<m_nChannels; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			if (m_ppRtMemBufferMngr[nIndex]->m_strID == strChID)
			{
				pFind = m_ppRtMemBufferMngr[nIndex];
				break;
			}
		}
	}
	
	return pFind;
}

long CRtMemBufferMngr::GetSpyBuffers()
{
	long nBuffers = 0;
	long nIndex = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			if (m_ppRtMemBufferMngr[nIndex]->IsRtChTypeNormal() && m_ppRtMemBufferMngr[nIndex]->IsUseSpyBuffer())
			{
				nBuffers++;
			}
			else if (m_ppRtMemBufferMngr[nIndex]->IsRtChTypeComplex() && m_ppRtMemBufferMngr[nIndex]->IsUseSpyBuffer())
			{
				nBuffers += 2;
			}
			else if (m_ppRtMemBufferMngr[nIndex]->IsRtChTypeGPS() && m_ppRtMemBufferMngr[nIndex]->IsUseSpyBuffer())
			{
				nBuffers++;
			}
			else
			{
			}
		}
	}
	
	return nBuffers;
}

long CRtMemBufferMngr::GetRecordBuffers()
{
	long nBuffers = 0;
	long nIndex = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			if (m_ppRtMemBufferMngr[nIndex]->IsUseRecordBuffer())
			{
				if (m_ppRtMemBufferMngr[nIndex]->IsRtChTypeNormal())
				{
					nBuffers++;
				}
				else if (m_ppRtMemBufferMngr[nIndex]->IsRtChTypeComplex())
				{
					nBuffers += 2;
				}
				else
				{
				}
			}
		}
	}
	
	return nBuffers;
}

long CRtMemBufferMngr::GetAttrBuffers()
{
	long nBuffers = 0;
	long nIndex = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			nBuffers++;
		}
		else
		{
		}
	}
	
	return nBuffers;
}

long CRtMemBufferMngr::_GetRecordDataLength()
{
	long nIndex = 0;
	UINT nClassID = 0;
	long nRecordDataLength = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			nRecordDataLength = m_ppRtMemBufferMngr[nIndex]->GetRecordDataLength();
			
			if (nRecordDataLength > 0)//
			{
				break;
			}
		}
	}	

	if (nRecordDataLength < 0)
	{
		nRecordDataLength = 0;
	}

	return nRecordDataLength;
}

long CRtMemBufferMngr::GetEmptyChannelIndex()
{
	long nIndex = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] == NULL)
		{
			break;
		}
	}
	
	return nIndex;
}

CExBaseObject* CRtMemBufferMngr::ValidateBufferID(const CString &strBufferID)
{
	CExBaseObject *pFind = FindByBufferID(strBufferID);
	return pFind;
}

CRtMemBufferChannel* CRtMemBufferMngr::_AddMR1200Channel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID)
{
	if (!bUseRecordBuf && !bUseSpyBuf)
	{
		return NULL;
	}
	
	long nIndex = GetEmptyChannelIndex();

	if (nIndex == MAX_MR1200_CHANNELS)
	{
		return NULL;
	}

	CExBaseObject *pRecord = ValidateBufferID(strRecordBufID);
	CExBaseObject *pSpy = ValidateBufferID(strSpyBufID);
	
	m_nChannels++;
	m_ppRtMemBufferMngr[nIndex] = new CRtMemBufferChannel();
	m_ppRtMemBufferMngr[nIndex]->SetRtChTypeNormal();
	m_ppRtMemBufferMngr[nIndex]->Init(strChannelID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID); 

	return m_ppRtMemBufferMngr[nIndex];
}

CRtMemBufferChannel* CRtMemBufferMngr::_AddMR1200BinaryChannel(UINT nID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID)
{
	if (!bUseRecordBuf && !bUseSpyBuf)
	{
		return NULL;
	}
	
	CString strChannelID;
	MR_GetBinaryChannelID(nID, strChannelID);

	CRtMemBufferChannel *pFind = FindMemBufferChannel(strChannelID);


	if (pFind != NULL)
	{
		return pFind;
	}

	long nIndex = GetEmptyChannelIndex();
	
	if (nIndex == MAX_MR1200_CHANNELS)
	{
		return NULL;
	}
	
	CExBaseObject *pRecord = ValidateBufferID(strRecordBufID);
	CExBaseObject *pSpy = ValidateBufferID(strSpyBufID);
	
	m_nChannels++;
	m_ppRtMemBufferMngr[nIndex] = new CRtMemBufferChannel();
	m_ppRtMemBufferMngr[nIndex]->SetRtChTypeNormal();
	m_ppRtMemBufferMngr[nIndex]->Init(strChannelID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID); 
	
	return m_ppRtMemBufferMngr[nIndex];
}

CRtMemBufferChannel* CRtMemBufferMngr::_AddMR1200ComplexChannel(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID, CRtScriptBase *pScript)
{
	if (!bUseRecordBuf && !bUseSpyBuf)
	{
		return NULL;
	}
	
	long nIndex = GetEmptyChannelIndex();
	
	if (nIndex == MAX_MR1200_CHANNELS)
	{
		return NULL;
	}

	m_nComplexChannels++;
	m_ppRtMemBufferMngr[nIndex] = new CRtMemBufferChannel();
	m_ppRtMemBufferMngr[nIndex]->SetRtChTypeComplex();
	m_ppRtMemBufferMngr[nIndex]->Init(strChannelID, bUseRecordBuf, strRecordBufID, bUseSpyBuf, strSpyBufID); 

	//初始化
	m_ppRtMemBufferMngr[nIndex]->Init();
#ifdef COMPLEXVARIABLE_USE_FLOAT
	CComplexMemBuffer_Float *pBuffer = (CComplexMemBuffer_Float*)m_ppRtMemBufferMngr[nIndex]->GetLSpyMemBuffer();
#else
	CComplexMemBuffer_Long *pBuffer = (CComplexMemBuffer_Long*)m_ppRtMemBufferMngr[nIndex]->GetLSpyMemBuffer();
#endif
	pScript->Clone(pBuffer->m_pScript);
	
	return m_ppRtMemBufferMngr[nIndex];
}

CRtMemBufferChannel* CRtMemBufferMngr::_AddMR1200GPSChannel(const CString &strChannelID, const CString &strSpyBufID)
{
	ASSERT (m_bHasGPS == FALSE);
	if (m_bHasGPS)
	{
		return m_ppRtMemBufferMngr[m_nChannels-1];
	}

	long nIndex = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] == NULL)
		{
			break;
		}
	}

	if (nIndex == MAX_MR1200_CHANNELS)
	{
		return NULL;
	}

	m_nChannels++;
	m_bHasGPS = TRUE;
	m_ppRtMemBufferMngr[nIndex] = new CRtMemBufferChannel();
	m_ppRtMemBufferMngr[nIndex]->m_strID = strChannelID;
	m_ppRtMemBufferMngr[nIndex]->SetUseRecordBuffer(FALSE);
	m_ppRtMemBufferMngr[nIndex]->SetUseSpyBuffer(TRUE);
	m_ppRtMemBufferMngr[nIndex]->SetRtChTypeGPS();

	//初始化
	m_ppRtMemBufferMngr[nIndex]->Init();

	return m_ppRtMemBufferMngr[nIndex];
}

CMemBuffer_Float* CRtMemBufferMngr::_AddMR1200AttrBuffer(const CString &strBufID)
{
	long nIndex = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] == NULL)
		{
			break;
		}
	}
	
	if (nIndex == MAX_MR1200_VARIABLE_ATTR_BUFFERS)
	{
		return NULL;
	}

	m_ppVariableAttrBuffer[nIndex] = new CMemBuffer_Float();
	m_ppVariableAttrBuffer[nIndex]->m_strBufferID = strBufID;
	m_ppVariableAttrBuffer[nIndex]->m_nMemBufferTypeID = CreateMemBufferTypeIDAttr();

	return m_ppVariableAttrBuffer[nIndex];
}


void CRtMemBufferMngr::InitComplexChScript()
{
	long nIndex = 0;
	UINT nClassID = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			if (m_ppRtMemBufferMngr[nIndex]->IsRtChTypeComplex())
			{
				m_ppRtMemBufferMngr[nIndex]->BuildComplexBufferScript();
			}
		}
	}	
	
	for (nIndex=0; nIndex<MAX_MR1200_VARIABLE_ATTR_BUFFERS; nIndex++)
	{
		if (m_ppVariableAttrBuffer[nIndex] != NULL)
		{
			m_ppVariableAttrBuffer[nIndex]->BuildComplexBufferScript();
		}
	}
}

void CRtMemBufferMngr::BuildComplexChScript()
{
	long nIndex = 0;
	UINT nClassID = 0;
	
	for (nIndex=0; nIndex<MAX_MR1200_CHANNELS; nIndex++)
	{
		if (m_ppRtMemBufferMngr[nIndex] != NULL)
		{
			if (m_ppRtMemBufferMngr[nIndex]->IsRtChTypeComplex())
			{
				m_ppRtMemBufferMngr[nIndex]->BuildExpNodeCoef();
			}
		}
	}	
}

