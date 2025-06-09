/*
	用于解析pqdif文件
	yp.w wangyp@youdiantech.com
*/

#include "stdafx.h"
#include "pqdiftool.h"
#include "misc.h"
#include "names.h"
#include "validate.h"

stPqdifTotalData g_stdFormat;
stPqdifTotalData g_pqTotalData;
STRUCT_QueryTotalData g_queryTotalData;


CPqdifTool::CPqdifTool()
{
	doSomeInit();

	InitNames();
	BOOL ret = Valid_Init(_P_GetConfigPath());

    if( ! ret )
    {
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,   "PQDIF解析模块初始化失败" );
		return;
	}
}

CPqdifTool::~CPqdifTool()
{
	freeStdFormatData();
	freePqTotalData();
	freeQueryData();

	Valid_Destroy();
}

int CPqdifTool::setStdXml( const CString &xml )
{
	doSomeInit();

	if( parseStdXml( xml ) < 0 )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "标准XML文件导入失败,请检查文件或路径，并重新导入");
		return -1;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "标准XML文件导入完成");
		VerifyStdXmlOfRepeat();
		return 0;
	}	

	return -1;
}

int CPqdifTool::openPqdifFile( const char *file )
{
// 	g_fileNum = 0;
// 	g_obserNum = 0;
	freePqTotalData();//打开新的PQDIF之前，将之前的数据清空  zhouhj 20201127
	freeQueryData();

	CWSerializeBuff oBuffer;
	CString strFile;
	strFile = file;

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "文件%s 开始解析", file);

 	if (oBuffer.ReadFromFile(strFile))
	{
		BOOL bTrue = TRUE;

		try
		{
			bTrue = parseFile( oBuffer );
	
			if( !bTrue )
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,   "文件%s 解析失败", file);
				freeDataInOneFile();
				return -1;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,  "文件%s 解析完成", file);
				freeDataInOneFile();
				return 0;
			}
		}
		catch (...)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,   "文件%s 解析失败", file);
		}
	}
	else  //zhow：文件不存在或打开失败
		return -1;

	return 0;
}

void CPqdifTool::queryData( time_t time )
{
	freeQueryData();
	queryData_ByTimestamp( time );
}

void CPqdifTool::InitQueryData( )
{
	freeQueryData();
}

void CPqdifTool::GetQueryDatas(CDvmDataset *pDataset, float fCT, float fPT)
{
	POS pos = g_queryTotalData.GetHeadPosition();
	CDvmData *pData = NULL;
	double VAL_MIN = -100000000.0, VAL_MAX = 100000000.0;
	CDvmData *pSelFind = NULL;
	CDvmValue *pValue = NULL;
	double dRate = 1;

	while( pos != NULL )
	{
		STRUCT_QueryNodeData *pQueryNode = (STRUCT_QueryNodeData*)g_queryTotalData.GetNext( pos );
		
		if (pQueryNode->idQuantityMeasured == ID_QM_VOLTAGE)
		{
			dRate = 1.0 / fPT;
		}
		else if (pQueryNode->idQuantityMeasured == ID_QM_CURRENT)
		{
			dRate = 1.0 / fCT;
		}
		else
		{
			dRate = 1;
		}
// 		pSelFind = FindPqdifSelectConfig(pQueryNode->channelName);
// 
// 		if (pSelFind == NULL)
// 		{
// 			continue;;
// 		}

		pData = new CDvmData();
		pData->m_strName = pQueryNode->channelName;
		pData->m_strID = pData->m_strName;
		pDataset->AddNewChild(pData);

// 		pValue = new CDvmValue();
// 		pValue->m_strName = _T("Freq");
// 		pValue->m_strID = pValue->m_strName;
// 		pData->AddNewChild(pValue);
// 		if( pQueryNode->freqVal >= 0.0 && pQueryNode->freqVal < VAL_MAX )
// 		{
// 			pValue->m_strValue.Format(_T("%f"), pQueryNode->freqVal);
// 		}
// 		else
// 		{
// 			pValue->m_strValue = _T("0");;
// 		}

		UINT4 stdDataSrcIndex = pQueryNode->stdDataSrcIndex;
		CStoreSeriesInfo_Node *pNodeInfo = (CStoreSeriesInfo_Node *)g_StoreSeriesInfo.FindNode( stdDataSrcIndex );
		int MIN_INDEX = 0, MAX_INDEX = 5;
	
		pValue = new CDvmValue();
		pValue->m_strName = _T("MaxVal");
		pValue->m_strID = pValue->m_strName;
		pData->AddNewChild(pValue);

		if( pNodeInfo->indexMax >= MIN_INDEX && pNodeInfo->indexMax <= MAX_INDEX )
		{
			if( pQueryNode->maxVal > VAL_MIN && pQueryNode->maxVal < VAL_MAX )
			{
				pValue->m_strValue.Format(_T("%f"), pQueryNode->maxVal * dRate);
				pData->m_strMax = pValue->m_strValue;
			}
		}

		pValue = new CDvmValue();
		pValue->m_strName = _T("MinVal");
		pValue->m_strID = pValue->m_strName;
		pData->AddNewChild(pValue);

		if( pNodeInfo->indexMin >= MIN_INDEX && pNodeInfo->indexMin <= MAX_INDEX )
		{
			if( pQueryNode->minVal > VAL_MIN && pQueryNode->minVal < VAL_MAX )
			{
				pValue->m_strValue.Format(_T("%f"), pQueryNode->minVal * dRate);
				pData->m_strMin = pValue->m_strValue;
			}
		}

		pValue = new CDvmValue();
		pValue->m_strName = _T("AvgVal");
		pValue->m_strID = pValue->m_strName;
		pData->AddNewChild(pValue);
		if( pNodeInfo->indexAvg >= MIN_INDEX && pNodeInfo->indexAvg <= MAX_INDEX )
		{
			if( pQueryNode->avgVal > VAL_MIN && pQueryNode->avgVal < VAL_MAX )
			{
				pValue->m_strValue.Format(_T("%f"), pQueryNode->avgVal * dRate);
				pData->m_strValue = pValue->m_strValue;
			}
		}

// 		pValue = new CDvmValue();
// 		pValue->m_strName = _T("Cp95Val");
// 		pValue->m_strID = pValue->m_strName;
// 		pData->AddNewChild(pValue);
// 		if( pNodeInfo->indexCp95 >= MIN_INDEX && pNodeInfo->indexCp95 <= MAX_INDEX )
// 		{
// 			if( pQueryNode->cp95Val > VAL_MIN && pQueryNode->cp95Val < VAL_MAX )
// 			{
// 				pValue->m_strValue.Format(_T("%f"), pQueryNode->cp95Val);
// 			}
// 		}
	}
}


CDvmData* CPqdifTool::FindPqdifSelectConfig(const CString &strName)
{
	POS pos = m_oPqdifSelectConfig.GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)m_oPqdifSelectConfig.GetNext(pos);

		if (pData->m_strID == strName)
		{
			pFind = pData;
			break;
		}
	}

	return pFind;
}


void CPqdifTool::OpenPqdifSelectConfig()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("PqdifSelectConfig.xml");
	m_oPqdifSelectConfig.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CDvmData* CPqdifTool::AddPqdifError()
{
	long nCount = m_oPqdifError.GetCount();
	CDvmData *pValue = new CDvmData();
	pValue->m_strID.Format(_T("V%d"), nCount);
	pValue->m_strName = pValue->m_strID;
	m_oPqdifError.AddNewChild(pValue);

	return pValue;
}

void CPqdifTool::AddPqdifErrorString(const CString &strError)
{
	CDvmData *pValue = AddPqdifError();
	pValue->m_strValue = strError;
}

void CPqdifTool::AddPqdifErrorString(const char *strError)
{
	CDvmData *pValue = AddPqdifError();
	pValue->m_strValue = strError;
}


CString CPqdifTool::GetPqdifErrorString()
{
	CString strError;

// 	POS pos = m_oPqdifError.GetHeadPosition();
// 	CDvmData *pValue = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pValue = (CDvmData *)m_oPqdifError.GetNext(pos);
// 		strError.AppendFormat(_T("%s\r\n"), pValue->m_strValue);
// 	}

	m_oPqdifError.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strError);

	return strError;
}

//////////////////////////////////////////////////////////////////////////

CPqdifConfig::CPqdifConfig()
{
	m_nFtpType = 0;
	m_nPqdifTimeLocal = 1;
	 m_fPT = 350;
	 m_fCT = 1;
}

CPqdifConfig::~CPqdifConfig()
{

}

CString CPqdifConfig::GetFtpServerRootPath()
{
	CString strPath = m_strFtpServerRootPath;

	if (strPath.Right(1) != _T("/"))
	{
		strPath += _T("/");
	}

	return strPath;
}

long CPqdifConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strLocalFtpServerIP);
		BinarySerializeCalLen(oBinaryBuffer, m_strUser);
		BinarySerializeCalLen(oBinaryBuffer, m_strPSW);
		BinarySerializeCalLen(oBinaryBuffer, m_strServerPath);
		BinarySerializeCalLen(oBinaryBuffer, m_nFtpType);
		BinarySerializeCalLen(oBinaryBuffer, m_strRemoteFtpServerIP);
		BinarySerializeCalLen(oBinaryBuffer, m_strStdFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strFtpServerRootPath);
		BinarySerializeCalLen(oBinaryBuffer, m_nPqdifTimeLocal);
		BinarySerializeCalLen(oBinaryBuffer, m_fPT);
		BinarySerializeCalLen(oBinaryBuffer, m_fCT);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strLocalFtpServerIP);
		BinarySerializeWrite(oBinaryBuffer,m_strUser);
		BinarySerializeWrite(oBinaryBuffer,m_strPSW);
		BinarySerializeWrite(oBinaryBuffer,m_strServerPath);
		BinarySerializeWrite(oBinaryBuffer,m_nFtpType);
		BinarySerializeWrite(oBinaryBuffer,m_strRemoteFtpServerIP);
		BinarySerializeWrite(oBinaryBuffer,m_strStdFile);
		BinarySerializeWrite(oBinaryBuffer,m_strFtpServerRootPath);
		BinarySerializeWrite(oBinaryBuffer,m_nPqdifTimeLocal);
		BinarySerializeWrite(oBinaryBuffer,m_fPT);
		BinarySerializeWrite(oBinaryBuffer,m_fCT);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strLocalFtpServerIP);
		BinarySerializeRead(oBinaryBuffer, m_strUser);
		BinarySerializeRead(oBinaryBuffer, m_strPSW);
		BinarySerializeRead(oBinaryBuffer, m_strServerPath);
		BinarySerializeRead(oBinaryBuffer, m_nFtpType);
		BinarySerializeRead(oBinaryBuffer, m_strRemoteFtpServerIP);
		BinarySerializeRead(oBinaryBuffer, m_strStdFile);
		BinarySerializeRead(oBinaryBuffer, m_strFtpServerRootPath);

		BinarySerializeRead(oBinaryBuffer, m_nPqdifTimeLocal);
		BinarySerializeRead(oBinaryBuffer, m_fPT);
		BinarySerializeRead(oBinaryBuffer, m_fCT);

		if (m_fPT <= 0.01)
		{
			m_fPT = 350;
		}

		if (m_fCT <= 0.01)
		{
			m_fCT = 1;
		}
	}

	return 0;
}

BOOL CPqdifConfig::OpenConfigFile()
{
	CString strFile = GetConfigFile();
	CBinarySerialBuffer oBuffer;
//	Gb_InitPqdifFileVersion(oBuffer.m_chPrefix, oBuffer.m_dwVersion);

	if (oBuffer.OpenFromFile(strFile))
	{
		oBuffer.SetReadMode();
//		oBuffer.ReadVersion();

		try
		{
			Serialize(oBuffer);
		}
		catch (...)
		{		
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CPqdifConfig::SaveConfigFile()
{
	CString strFile = GetConfigFile();
	CBinarySerialBuffer oBuffer;
//	Gb_InitPqdifFileVersion(oBuffer.m_chPrefix, oBuffer.m_dwVersion);

	oBuffer.SetCalSizeMode();
	Serialize(oBuffer);
//	oBuffer.WriteVersion();
	oBuffer.AllocBuffer();

	oBuffer.SetWriteMode();
//	oBuffer.WriteVersion();
	Serialize(oBuffer);

	oBuffer.SaveToFile(strFile);
}

void CPqdifConfig::Init()
{
	m_strUser = _T("admin");
	m_strPSW = _T("admin");
	m_strServerPath = _P_GetSystemPath();
	m_strServerPath += _T("PQDIF\\");

	CreateAllDirectories(m_strServerPath);
}

CString CPqdifConfig::GetConfigFile()
{
	CString strFile;

	strFile = _P_GetConfigPath();
	strFile += _T("PqdifServerConfig.xcfg");

	return strFile;
}

