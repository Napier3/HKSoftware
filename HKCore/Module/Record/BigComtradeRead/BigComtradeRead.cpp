#include "StdAfx.h"
#include "BigComtradeRead.h"
#include "../../API/FileApi.h"

CBigComtradeRead::CBigComtradeRead(void)
{
	m_pFileReadBuffer = NULL;
	m_nCurTotalByteLength = 0;
	m_nFileReadLength = 0;
	m_fUMax = 0;
	m_fIMin = 0;
	m_fUMax = 0;
	m_fIMin = 0;

	m_bReadFileFinish = TRUE;
	m_bAnalysisFinish = TRUE;
	m_nInsertFreq = 50000;
	m_nCurBeginPointIndex = 0;
	m_nCurPointNum = 0;
//	m_nTotalLenth = 0;
	m_bHasOpenDataFile = FALSE;
	m_nSamAmount = 0;
	m_pdSamRate = NULL;
	m_pnDataPoints = NULL;
	m_oBigComtradeFile.SetCreateBuffer(FALSE);
}

CBigComtradeRead::~CBigComtradeRead(void)
{
	BufferClear();
}

BOOL CBigComtradeRead::OpenBigComtradeFile(const CString &strComtradeFile)
{
	m_oBigComtradeFile.Init();

	if (!m_oBigComtradeFile.ReadCFGFile(strComtradeFile))
	{
		return FALSE;
	}

	ReadBigDataFile(strComtradeFile);
	return TRUE;
}

long CBigComtradeRead::ReadBigDataFile(const CString& strComtradeFile)
{
	BOOL bRet = FALSE;

	if (m_oBigComtradeFile.m_nDataFileType == 0)
	{
		bRet = ReadBigDataAsASIIMode(strComtradeFile);
	}
	else
	{
		bRet = ReadBigDataAsBINARYMode(strComtradeFile);
	}

	return bRet;
}

long CBigComtradeRead::ReadBigDataAsBINARYMode(const CString& strComtradeFile)
{
	CString strTemp = CString(m_oBigComtradeFile.g_pszKeyDat);
	CString strDatFilePath = ChangeFilePostfix(strComtradeFile, strTemp);
	// 	char pszDatFilePath[MAX_PATH];
	// 	CString_to_char(strDatFilePath, pszDatFilePath);

	if (m_bHasOpenDataFile)
	{
		m_oFileRead.Close();
		m_bHasOpenDataFile = FALSE;
	}

	m_bHasOpenDataFile = m_oFileRead.Open(strDatFilePath,CFile::modeRead);

	if (!m_bHasOpenDataFile)
	{
		return FALSE;
	}

	BufferClear();
	SetTotalSmpRates();
	m_nTotalPointsNum = m_oBigComtradeFile.GetTotalPoints();

	long nSinglePointLength = m_oBigComtradeFile.GetBinarySinglePointLength();
	long nActTotalPointsNum = m_oFileRead.GetLength()/nSinglePointLength;

	if (nActTotalPointsNum<m_nTotalPointsNum)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("当前CFG文件中标识的总点数(%ld),与DAT文件中的大小(%ld),实际总点数(%ld)不一致."), m_nTotalPointsNum, m_oFileRead.GetLength(),nActTotalPointsNum);
		m_nTotalPointsNum = nActTotalPointsNum;
	}

	m_nCurBeginPointIndex = 0;
	m_nCurPointNum = 0;
	GenerateComtradeChDataFromDataFile();
	return 0;
}

long CBigComtradeRead::GetCurReadPointsNum()
{
	long nSinglePointLength = m_oBigComtradeFile.GetBinarySinglePointLength();

	if ((m_nTotalPointsNum-m_nCurBeginPointIndex)*nSinglePointLength<BIG_COMTRADE_BINARY_READ_LENGTH)
	{
		return m_nTotalPointsNum-m_nCurBeginPointIndex;
	}

	return BIG_COMTRADE_BINARY_READ_LENGTH/nSinglePointLength;
}

long CBigComtradeRead::ReadBigDataAsASIIMode(const CString& strComtradeFile)
{
	
	return 0;
}

void CBigComtradeRead::BufferClear()
{
	if (m_pFileReadBuffer != NULL)
	{
		delete m_pFileReadBuffer;
		m_pFileReadBuffer = NULL;
	}

	if (m_pdSamRate != NULL)
	{
		delete m_pdSamRate;
		m_pdSamRate = NULL;
	}

	if (m_pnDataPoints != NULL)
	{
		delete m_pnDataPoints;
		m_pnDataPoints = NULL;
	}
}

void CBigComtradeRead::SetTotalSmpRates()
{
	if (m_pnDataPoints != NULL)
	{
		delete m_pnDataPoints;
	}

	if (m_pdSamRate != NULL)
	{
		delete m_pdSamRate;
	}

	m_nSamAmount = m_oBigComtradeFile.m_nSamAmount;
	m_pnDataPoints = new long[m_nSamAmount];
	m_pdSamRate    = new float[m_nSamAmount];

	for (int nIndex = 0;nIndex<m_nSamAmount;nIndex++)
	{
		m_pnDataPoints[nIndex] = m_oBigComtradeFile.m_pnDataPoints[nIndex];
		m_pdSamRate[nIndex] = m_oBigComtradeFile.m_pdSamRate[nIndex];
	}
}

BOOL CBigComtradeRead::GenerateComtradeChDataFromDataFile()
{
	m_nCurBeginPointIndex += m_nCurPointNum;
	long nCurPointsNum = GetCurReadPointsNum();
	long nCurTotalLength = m_oBigComtradeFile.GetBinarySinglePointLength()*nCurPointsNum;
	m_nCurPointNum = nCurPointsNum;
	m_oBigComtradeFile.m_nTotalPoints = m_nCurPointNum;
	m_oBigComtradeFile.InitChsAllocBuffer();

	if (m_pFileReadBuffer == NULL)
	{
		m_nCurTotalByteLength = nCurTotalLength;
		m_pFileReadBuffer = new BYTE[m_nCurTotalByteLength +8];
	}
	else if (nCurTotalLength>m_nCurTotalByteLength)
	{
		delete m_pFileReadBuffer;
		m_nCurTotalByteLength = nCurTotalLength;
		m_pFileReadBuffer = new BYTE[m_nCurTotalByteLength +8];
	}

	memset(m_pFileReadBuffer,0,m_nCurTotalByteLength+8);
	long nReadLenth = m_oFileRead.Read(m_pFileReadBuffer,nCurTotalLength);

	if (nReadLenth<0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("读取指定长度的大文件内容失败."));
		return FALSE;
	}
	else if (nReadLenth != nCurTotalLength)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("nReadLenth=%ls;nCurTotalLength=%ld;(nReadLenth != nCurTotalLength)"), nReadLenth,nCurTotalLength);
		return FALSE;
	}

	unsigned short* pnBuffer = NULL;
	unsigned short* pnTemp = NULL;
	int  nSize = (int)(ceil(m_oBigComtradeFile.m_nBinarys / 16.0));
	nSize += (2 + 2 + m_oBigComtradeFile.m_nAnalogs);
	pnBuffer = (unsigned short*)m_pFileReadBuffer;
	CComtradeDataBase* pObj = NULL;
	long nBinaryIndex = 0;
	long nAnalogIndex = 0;
	unsigned short* pBuffer = NULL;

	for (long nIndex = 0; nIndex < m_nCurPointNum; nIndex++)
	{
		pnTemp = pnBuffer + 4;//4是时间和索引所占的4个字
		POS pos = m_oBigComtradeFile.GetHeadPosition();
		nBinaryIndex = 0;
		nAnalogIndex = 0;

		while (pos != NULL)
		{
			pObj = (CComtradeDataBase*)m_oBigComtradeFile.GetNext(pos);
			pBuffer = pObj->GetBuffer();

			if (pObj->IsAnalogData())
			{			
				pBuffer[nIndex] = *pnTemp;
				pnTemp++;			
				nAnalogIndex++;
			}
			else if(pObj->GetClassID()==GLOBALCLASSID_CCOMTRADERATEDATA)
			{
				continue;
			}
			else 
			{
				if (nBinaryIndex % 16 == 0)//每16个状态一个short
				{
					pBuffer[nIndex] = *pnTemp;
					pnTemp++;
				}
			
				nBinaryIndex++;
			}
		}

		pnBuffer += nSize;
	}

	m_oBigComtradeFile.UpdateAllChsTotalPointsNum();
	return TRUE;
}