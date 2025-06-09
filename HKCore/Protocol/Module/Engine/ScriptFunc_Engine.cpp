#include "StdAfx.h"
#include "ScriptFunc_Engine.h"
#include <math.h>

#include "../../../Module/API/HexTransApi.h"

#include "../XLanguageResourcePp.h"
// #ifndef _PP_DEV_MODE_

#include "PpEngineBaseApp.h"
#include "PpEngineDataMngrCntr.h"
#include "../../../Module/MemBuffer/EquationBuffer.h"

extern long g_bLogBindQueryErrorInfor;
// #else
// 
// #include "PpDevBaseApp.h"
// 
// #endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//2021-12-30  lijunqing
BOOL script_IsEncoding_UTF8(CTScriptSingleVM *pXvm)
{
	CPpEngineData *pEngineData = (CPpEngineData*)pXvm->m_pRefData;
	ASSERT( pEngineData != NULL );
	return pEngineData->m_pTemplate->IsEncoding_UTF8();
}


CExBaseList* script_GetDvmDevice(CTScriptSingleVM *pXvm)
{
	CPpEngineData *pEngineData = (CPpEngineData*)pXvm->m_pRefData;
	ASSERT( pEngineData != NULL );
	return pEngineData->m_pTemplate->GetDevice();

}

CDvmDataset* script_GetDsDataset_IndexPath(CExBaseList *pDevice, const char* pszPath)
{
	long nLdIndex, nDsIndex;
	CBufferBase oBuffer;
	oBuffer.InitBuffer(pszPath);
	oBuffer.FormatBuffer('$', 0);
	char *pStr = oBuffer.GetString();

	if (pStr == NULL)
		return NULL;

	nLdIndex = atol(pStr);
	oBuffer.NextString();
	pStr = oBuffer.GetString();

	if (pStr == NULL)
		return NULL;

	nDsIndex = atol(pStr);

	CDvmLogicDevice *pLdevice = ((CDvmDevice*)pDevice)->FindByIndex(nLdIndex);
	if (pLdevice == NULL)
		return NULL;

	CDvmDataset *pDataset = pLdevice->FindByIndex(nDsIndex);

	return pDataset;
}


CDvmDataset* script_FindDvmDatasetByIndex(CExBaseList *pDevice, long nIndex)
{
	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmDataset *pFind = NULL;

	if (pDevice->GetClassID() == DVMCLASSID_CDVMDEVICE)
	{
		POS pos = pDevice->GetHeadPosition();
		CDvmLogicDevice *pLDevice = NULL;
		CString strIndex;
		strIndex.Format(_T("%d"), nIndex);

		while (pos != NULL)
		{
			pLDevice = (CDvmLogicDevice *)pLDevice->GetNext(pos);
			pFind = (CDvmDataset*)pLDevice->FindByIndex(nIndex);

			if (pFind != NULL)
			{
				break;
			}

			pFind = (CDvmDataset*)pLDevice->FindByID(strIndex);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CDvmDataset* script_GetDsDataset(CTScriptSingleVM *pXvm, const char* pszPath)
{
	if (pszPath[0] == '\0')
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorPath/*_T("系统错误(路径为空)")*/ );
		return NULL;
	}

	CExBaseList *pDevice =script_GetDvmDevice(pXvm);;

	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmDataset *pFind = NULL;
	CString strPath;
	strPath = pszPath;

	//绝对全路径
	if (strchr(pszPath, '$') > 0)
	{
		if ('0' <= pszPath[0] && pszPath[0] <= '9')
		{
			pFind = script_GetDsDataset_IndexPath(pDevice, pszPath);
		}
		else
		{
			pFind = (CDvmDataset*)pDevice->SelectData(strPath);
		}

		if (pFind != NULL)
		{
			if (pFind->GetClassID() != DVMCLASSID_CDVMDATASET)
			{
				pFind = NULL;
			}
		}
	}
	else
	{//单一索引编号
		long nIndex = 0;

		if ('0' <= pszPath[0] && pszPath[0] <= '9')
		{
			nIndex = atol(pszPath);
		}
		else
		{
			nIndex = script_GetGlobal(pXvm, pszPath);
		}

		pFind = script_FindDvmDatasetByIndex(pDevice, nIndex);
	}

	if (pFind == NULL && g_bLogBindQueryErrorInfor)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_SystemErrorData8.GetString()/*_T("系统错误(路径【%s】对应的数据不存在)")*/
                 , strPath.GetString() );
	}

	return pFind;
}

CPpTemplate* script_GetPpTemplate(CTScriptSingleVM *pXvm)
{
	CPpEngineData *pEngineData = (CPpEngineData *)pXvm->GetRefData();
	CPpTemplate *pFind = NULL;

	pFind = (CPpTemplate*)pEngineData->m_pTemplate;//->GetAncestor(PPCLASSID_PPTEMPLATE);

	return pFind;
}

inline CPpPackageDetail* PPS_GetPackageDetail(CTScriptSingleVM *pXvm)
{
	char *pszReturn = pXvm->GetChReurn();
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CPpParsePackage *pParsePkg = NULL;

	pParsePkg = (CPpParsePackage*)pObj->GetAncestor(PPCLASSID_PPPARSEPACKGE);

	if (pParsePkg == NULL)
	{
		return NULL;
	}

	return (CPpPackageDetail*)pParsePkg->m_pPackageDetailRef;
}


inline CBaseObject* PPS_GetBbdata(CTScriptSingleVM *pXvm)
{
	char *pszReturn = pXvm->GetChReurn();
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CBaseObject *pBbData = NULL;

	pBbData = pObj->GetAncestor(PPCLASSID_RBBDATA);

	if (pBbData == NULL)
	{
		pBbData = pObj->GetAncestor(PPCLASSID_WBBDATA);
	}

	return pBbData;
}

CPpProcedure* script_GetPpProcedure(CTScriptSingleVM *pXvm)
{
	char *pszReturn = pXvm->GetChReurn();
	CBaseObject *pScript = PPS_GetPpScript(pXvm);;
	CPpProcedure *pFind = NULL;

	pFind = (CPpProcedure*)pScript->GetAncestor(PPCLASSID_PPPROCEDURE);

	return pFind;
}

//报告处理
CDvmDataset* script_GetReportDataset(CExBaseList *pDevice, const CString &strDatasetID)
{
	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmDataset *pDataset = NULL;

	if (pDevice->GetClassID() == DVMCLASSID_CDVMDEVICE)
	{
		CDvmLogicDevice *pLdevice = (CDvmLogicDevice*)pDevice->FindByID(g_strReportLogicDeviceID);

		if (pLdevice == NULL)
		{
			pLdevice = new CDvmLogicDevice();
			pLdevice->m_strID = g_strReportLogicDeviceID;
			pLdevice->m_strName = g_strReportLogicDeviceID;
			pLdevice->m_nIndex = 65535;
			pDevice->AddNewChild(pLdevice);
		}

		pDataset = (CDvmDataset*)pLdevice->FindByID(strDatasetID);

		if (pDataset == NULL)
		{
			pDataset = new CDvmDataset();
			pDataset->m_strID = strDatasetID;
			pDataset->m_strName = strDatasetID;
			pDataset->m_nIndex = 65535;
			pLdevice->AddNewChild(pDataset);
		}
	}
	
	return pDataset;
}



CDvmDataset* script_GetReportDataset(CTScriptSingleVM *pXvm, const CString &strDatasetID)
{
	CExBaseList *pDevice = script_GetDvmDevice(pXvm);;
	return script_GetReportDataset(pDevice, strDatasetID);
}



//设置绑定关系:设置
//ItemIndex
long script_BindItemIndex(CTScriptSingleVM *pXvm, long nItemIndex)
{
	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);

	if (pBbData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallErrorBind/*L"函数BindItemIndex调用错误"*/);
		}

		return 0;
	}

	CExBaseObject *pDvNodeData = pBbData->BindItemIndex(nItemIndex);

	if (pDvNodeData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_FctnSError.GetString()/*L"函数SBindItemIndex绑定错误"*/);
		}

		return 0;
	}

	if (pDvNodeData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,  g_sLangTxt_FctnSError.GetString()/*L"函数SBindItemIndex绑定错误"*/);
		}

		return 0;
	}
	else
	{
		return 1;
	}
}

//////////////////////////////////////////////////////////////////////////
// 获取关联数据指针
CByteBlock* PPS_GetByteBlock(CExBaseObject *pEngineData)
{
	//CPpDevBaseApp* pApp = g_thePpDevBaseApp;
	CPpEngineData *p = (CPpEngineData*)pEngineData;
	ASSERT (p != NULL);
	ASSERT( p->GetClassID() == PPCLASSID_PPENGINEDATA);

	CBaseObject *pObj = p->GetPpScript()->GetParent();

	if (pObj == NULL)
	{
		return NULL;
	}
	UINT nClassID = pObj->GetClassID();

	if ( (nClassID & PPCLASSID_BYTEBLOCK) == PPCLASSID_BYTEBLOCK)
	{
		return (CByteBlock*)pObj;
	}

	if (nClassID == PPCLASSID_BYTEBLOCK || nClassID == PPCLASSID_RBYTEBLOCK || nClassID == PPCLASSID_WBYTEBLOCK || nClassID == PPCLASSID_RDATABYTEBLOCK)
	{
		return (CByteBlock*)pObj;
	}
	else
	{
		return NULL;
	}
}

CPpScript* PPS_GetPpScript(CTScriptSingleVM *pXvm)
{
	CPpEngineData *p = (CPpEngineData*)pXvm->GetRefData();
	return p->GetPpScript();
}

//////////////////////////////////////////////////////////////////////////
//data
//获取当前关联的数据的数据类型
long script_GetCurrValueDataType(CTScriptSingleVM *pXvm)
{
	//CByteBlock *pByteBlock = GetByteBlock();
	//pByteBlock->m_strDataType;
	return 0;
}

//获取当前关联的数据的数据长度
long script_GetCurrValueDataLength(CTScriptSingleVM *pXvm)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return 0;
	}

	return pByteBlock->GetByteBlockLength();
}

//////////////////////////////////////////////////////////////////////////
//Byte/long
long script_GetBbValLong10(CTScriptSingleVM *pXvm, long nIndex,long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return 0;
	}

	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nBytes <= nLength)
	{
		for(long nIndexEx=0; nIndexEx<nBytes; nIndexEx++)
		{
			int nTemp = pByteBlock->m_pBuffer[nIndex+nIndexEx];
			nReturn += ((nTemp/16)*10 + nTemp%16) * _Pow_int(100,nBytes-nIndexEx-1);
		}
	}

	return nReturn;
}

void script_SetBbValLong10(CTScriptSingleVM *pXvm, long nIndex,long nValue,long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if (nBytes > 0 && (nIndex+nBytes) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				//memcpy(pByteBlock->m_pBuffer+nIndex, &nValue, nBytes);
				int nTemp = nValue;
				for(int i=0;i<nBytes;i++)
				{
					nTemp = nTemp/(_Pow_int(100,nBytes-i-1));
					memcpy(pByteBlock->m_pBuffer+i,&nTemp,1);	//先设置高字节
					nTemp = nTemp%(_Pow_int(100,nBytes-i-1));
				}
				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=%d")
            , pByteBlock->m_strID.GetString(), nIndex, nBytes, nLength);
	}
}

long script_GetBbCurrValue(CTScriptSingleVM *pXvm, long nIndex,long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	DWORD nReturn = 0;
	DWORD nTemp = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nBytes <= nLength)
	{
		for (long nIndexEx=0; nIndexEx<nBytes; nIndexEx++)
		{
			nTemp = pByteBlock->m_pBuffer[nIndex+nIndexEx];
			nTemp = nTemp << (8*nIndexEx);
			nReturn += nTemp;//(pByteBlock->m_pBuffer[nIndex+nIndexEx]<<(8*nIndexEx));
		}
	}
	
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%d"), nReturn);
	return nReturn;
}

//时间转换函数
const char* script_GetTimeStr1970(CTScriptSingleVM *pXvm, long nSeconds);
const char* script_GetTimeStr1970_ms(CTScriptSingleVM *pXvm, __int64 n64Ms);
long script_GetTimeLong1970(const char *pszTime);

const char* script_GetBbCurrValueTimeStr1970(CTScriptSingleVM *pXvm, long nIndex,long nBytes)
{
	long nValue = script_GetBbCurrValue(pXvm, nIndex, nBytes);
	return script_GetTimeStr1970(pXvm, nValue);
}

const char* script_GetBbCurrValueTimeStr1970_ms(CTScriptSingleVM *pXvm, long nIndex,long nBytes)
{
	long n1 = 0;
	long k = nBytes - 1;
	__int64 n64Ms = 0;

	while (k >= 0)
	{
		n64Ms = n64Ms << 8;
		n1 = script_GetBbCurrValue(pXvm, nIndex+k, 1);
		n64Ms += n1;
		k--;
	}
	
	return script_GetTimeStr1970_ms(pXvm, n64Ms);
}

long script_GetBbCurrValue1(CTScriptSingleVM *pXvm, long nIndex)
{
	long nVal = script_GetBbCurrValue(pXvm, nIndex, 2);
	short nRet =(nVal >> 8) & 0xFF;
	nRet += (nVal & 0xFF) << 8;

	return nRet;
}

long script_GetBbCurrValue2(CTScriptSingleVM *pXvm, long nIndex)
{
	long nVal = script_GetBbCurrValue(pXvm, nIndex, 4);
	long nRet = 0;

	nRet =  ( nVal >> 24) & 0xFF;
	nRet += ((nVal >> 16) & 0xFF) << 8;
	nRet += ((nVal >> 8)  & 0xFF) << 16;
	nRet += ( nVal &     0xFF)    << 24;

	return nRet;
}

//设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号
void script_SetBbCurrValue(CTScriptSingleVM *pXvm, long nIndex, long nValue, long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if (nBytes > 0 && (nIndex+nBytes) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				memcpy(pByteBlock->m_pBuffer+nIndex, &nValue, nBytes);
				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DataErrorIndex.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex, nBytes, nLength);
	}
}

void script_SetBbCurrValue2(CTScriptSingleVM *pXvm, long nIndex, long nValue)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if ((nIndex+4) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				pByteBlock->m_pBuffer[nIndex]   = (nValue >> 24) & 0xFF;
				pByteBlock->m_pBuffer[nIndex+1] = (nValue >> 16) & 0xFF;
				pByteBlock->m_pBuffer[nIndex+2] = (nValue >> 8) & 0xFF;
				pByteBlock->m_pBuffer[nIndex+3] =  nValue & 0xFF;
				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DataErrorIndex2.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=4"*/
            , pByteBlock->m_strID.GetString(), nIndex, nLength);
	}
}

void script_SetBbCurrValue1(CTScriptSingleVM *pXvm, long nIndex, long nValue)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if ((nIndex+2) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				pByteBlock->m_pBuffer[nIndex] = (nValue >> 8) & 0xFF;
				pByteBlock->m_pBuffer[nIndex+1] = nValue & 0xFF;
				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DataErrorIndex2.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=4"*/
            , pByteBlock->m_strID.GetString(), nIndex, nLength);
	}
}
//////////////////////////////////////////////////////////////////////////
//string
void script_SetBbCurrValueString(CTScriptSingleVM *pXvm, long nIndex, const char* pString, long nBytes)
{
	if (pString == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_GetBbEmpty.GetString()/*L"SetBbValStr：字符串参数指针为空"*/);
		return;
	}

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if (nBytes > 0 && (nIndex+nBytes) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				memset(pByteBlock->m_pBuffer + nIndex, 0, nBytes);
				//memcpy(pByteBlock->m_pBuffer+nIndex, pString, strlen(pString));

#ifndef _PSX_QT_LINUX_
				//2021-12-31  lijunqing 
				if (script_IsEncoding_UTF8(pXvm))
				{
					long nSrcLen = strlen(pString);
					long nDestLen = 0;
					char *pszUtf8 = NULL;
					charGBK_to_charUtf8((char*)pString, nSrcLen, &pszUtf8, nDestLen);
					memcpy(pByteBlock->m_pBuffer+nIndex, pszUtf8, nBytes);
					delete pszUtf8;
				}
				else
#endif
				{
					memcpy(pByteBlock->m_pBuffer+nIndex, pString, nBytes);
				}

				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
            , g_sLangTxt_DataErrorIndex.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex, nBytes, nLength);
	}
}

void script_SetBbCurrValueStringUtf8(CTScriptSingleVM *pXvm, long nIndex, const char* pUft8String, long nBytes)
{
	if (pUft8String == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_GetBbEmpty.GetString()/*L"SetBbValStr：字符串参数指针为空"*/);
		return;
	}

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if (nBytes > 0 && (nIndex+nBytes) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				memset(pByteBlock->m_pBuffer + nIndex, 0, nBytes);
				memcpy(pByteBlock->m_pBuffer+nIndex, pUft8String, nBytes);

				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR
			, g_sLangTxt_DataErrorIndex.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=%d"*/
			, pByteBlock->m_strID.GetString(), nIndex, nBytes, nLength);
	}
}

const char* script_GetBbCurrValueString(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nBytesCopy = nBytes;
	char *pszReturn = pXvm->GetChReurn();
	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex < 0)
	{
		nIndex = 0;
	}

	if (nBytesCopy + nIndex >= nLength)
	{
		nBytesCopy = nLength - nIndex;
	}

	if (nBytesCopy < 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , g_sLangTxt_GetBbError.GetString()/*_T("%s(%s)：GetBbValStr(%d,%d)错误")*/
                , pByteBlock->m_strName.GetString(), pByteBlock->m_strID.GetString(), nIndex, nBytes);
		nBytesCopy = 0;
	}

	if (nBytesCopy > 0)
	{
#ifndef _PSX_QT_LINUX_
        //2021-12-31  lijunqing
		if (script_IsEncoding_UTF8(pXvm))
		{
			char *pszBytesCopy = new char [ nBytesCopy + 2];
			memcpy(pszBytesCopy, (pByteBlock->m_pBuffer+nIndex), nBytesCopy);
			pszBytesCopy[nBytesCopy] = 0;
			long nSrcLen = nBytesCopy;
			long nDestLen = 0;
			charUtf8_to_charGBK(pszBytesCopy, nSrcLen, pszReturn, nDestLen);
			delete pszBytesCopy;
		}
		else
#endif
		{
			memcpy(pszReturn, (pByteBlock->m_pBuffer+nIndex), nBytesCopy);
		}
	}

	pszReturn[nBytesCopy] = '\0';
	
	return pszReturn;
}

const char* script_GetBbCurrValueStringEx(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nBytesCopy = nBytes;
	char *pszReturn = pXvm->GetChReurn();
	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex < 0)
	{
		nIndex = 0;
	}

	if (nBytesCopy + nIndex >= nLength)
	{
		nBytesCopy = nLength - nIndex;
	}

	if (nBytesCopy < 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                 , g_sLangTxt_GetBbError.GetString()/*_T("%s(%s)：GetBbValStr(%d,%d)错误")*/
                 , pByteBlock->m_strName.GetString(), pByteBlock->m_strID.GetString(), nIndex, nBytes);
		nBytesCopy = 0;
	}

	if (nBytesCopy > 0)
	{
		memcpy(pszReturn, (pByteBlock->m_pBuffer+nIndex), nBytesCopy);
	}

	pszReturn[nBytesCopy] = '\0';

	// 	CString strPrefix= CString(pszReturn);
	// 	nLength = WideCharToMultiByte(CP_UTF8, 0, strPrefix, strPrefix.GetLength(), NULL, 0, NULL, NULL);
	// 	char *prefix = new char[nLength + 1];
	// 	WideCharToMultiByte(CP_UTF8, 0, strPrefix, strPrefix.GetLength(), prefix, nLength, NULL, NULL);
	// 	prefix[nLength]  = 0;
#ifndef _PSX_IDE_QT_
	int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
		0,
		pszReturn,
		-1,
		NULL,
		0 );  
	wchar_t *  pUnicode;  
	pUnicode = new wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar(CP_UTF8,
		0,
		pszReturn,
		-1,
		(LPWSTR)pUnicode,
		unicodeLen );  

	BSTR_to_char(pUnicode, pszReturn);
#endif
// 	CString  rt;  
// 	rt = ( wchar_t* )pUnicode;
// 	delete  pUnicode; 
// 	char prefix[350000];
// 	CString_to_char(rt,prefix);

	return pszReturn;
}

//////////////////////////////////////////////////////////////////////////
//byte
void script_SetBbCurrValueByte(CTScriptSingleVM *pXvm, long nIndex, const char* pString, long nBytes)
{
	if (pString == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_GetBbEmpty.GetString()/*L"SetBbValStr：字符串参数指针为空"*/);
		return;
	}

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if (pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if (nBytes > 0 && (nIndex + nBytes) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				memset(pByteBlock->m_pBuffer + nIndex, 0, nBytes);
				HexToValue(pString, pByteBlock->m_pBuffer + nIndex);
				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
            , g_sLangTxt_DataErrorIndex.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex, nBytes, nLength);
	}
}

const char* script_GetBbCurrValueByte(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if (pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nBytesCopy = nBytes;
	char *pszReturn = pXvm->GetChReurn();
	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex < 0)
	{
		nIndex = 0;
	}

	if (nBytesCopy + nIndex >= nLength)
	{
		nBytesCopy = nLength - nIndex;
	}

	if (nBytesCopy < 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                   , g_sLangTxt_GetBbError.GetString()/*_T("%s(%s)：GetBbValStr(%d,%d)错误")*/
                   , pByteBlock->m_strName.GetString(), pByteBlock->m_strID.GetString(), nIndex, nBytes);
		nBytesCopy = 0;
	}

	BYTE* pBuffer = pByteBlock->m_pBuffer + nIndex;
	BYTE* pEnd = pByteBlock->m_pBuffer + nIndex + nBytesCopy;
	char* pBegin = pszReturn;
	while (pBuffer < pEnd)
	{
		ValueToHex(*pBuffer, *pBegin, *(pBegin + 1));
		pBegin += 2;
		*pBegin = ' ';
		pBegin++;
		pBuffer++;
	}
	*pBegin = 0;

	return pszReturn;
}

void script_BbTranspos(CTScriptSingleVM *pXvm, long nIndex1, long nIndex2)
{
	if (nIndex1 == nIndex2)
	{
		return;
	}

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if (pByteBlock == NULL)
	{
		return ;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return ;
	}

	long nLength = pByteBlock->GetByteBlockLength();
	
	if ((0 <= nIndex1 && nIndex1 < nLength) && (0 <= nIndex2 && nIndex2 < nLength))
	{
		BYTE byteTemp = pByteBlock->m_pBuffer[nIndex1];
		 pByteBlock->m_pBuffer[nIndex1] =  pByteBlock->m_pBuffer[nIndex2];
		  pByteBlock->m_pBuffer[nIndex2] =  byteTemp;
	}
}

const char* script_GetBbFormatDataString(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	char *pszReturn = pXvm->GetChReurn();
	pszReturn[0] = 0;

	if(pByteBlock == NULL)
	{
		return pszReturn;
	}

	if (!pByteBlock->IsDataTypeText())
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_FctnDataCall.GetString()/*_T("%s::GetBbDataStr函数必须在“格式文本”数据字节快中被调用")*/
                 , pByteBlock->m_strID.GetString());
		return pszReturn;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return pszReturn;
	}

	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();
	CFormatTextBuffer *pFormatBuffer = pByteBlock->GetFormatTextBuffer();

	nReturn = pFormatBuffer->GetData(nIndex, (BYTE*)(pszReturn) );
	pszReturn[nReturn] = 0;

	return pszReturn;
}

double script_GetBbFormatDataFloat(CTScriptSingleVM *pXvm, long nIndex)
{
	const char* pszRet = script_GetBbFormatDataString(pXvm, nIndex);

	return atof(pszRet);
}

long script_GetBbFormatDataLong(CTScriptSingleVM *pXvm, long nIndex)
{
	const char* pszRet = script_GetBbFormatDataString(pXvm, nIndex);

	return atol(pszRet);
}

BOOL PPS_IsValueTag(const CString &strAttrID)
{
	CString strTagID = strAttrID;

	strTagID.MakeLower();

	if (strTagID == _T("value"))
	{
		return TRUE;
	}

	if (strTagID == _T("val"))
	{
		return TRUE;
	}

	if (strTagID == _T("v"))
	{
		return TRUE;
	}

	return FALSE;
}

//获取数据绑定的数据的属性
//返回绑定的数据的值：
//pszAttrID：值得数据ID
//strValue：返回数据
BOOL PPS_GetBindData(CTScriptSingleVM *pXvm, const char* pszAttrID, CString &strValue)
{
	CDvmData *pData = (CDvmData*)PPS_GetBindDeviceNodeData(pXvm, pszAttrID);

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetBindData error...") );
		return FALSE;
	}

	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return FALSE;
	}

	CString strAttrID(pszAttrID);

	if (pData->GetValueByID(strAttrID, strValue))
	{
		if (PPS_IsValueTag(strAttrID))
		{
#ifdef UNICODE
			PPS_CalBindData(pXvm, pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt);
#else
			PPS_CalBindData(pXvm, pData, strValue, CString(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt) );
#endif
		}

		return TRUE;
	}
// 	strValue = pData->FindTag(strAttrID);
// 
// 	if (strValue.GetLength() > 0)
// 	{
// 		if (PPS_IsValueTag(strAttrID))
// 		{
// 		//获取数据，取得数据对象的值，只要经过发送公式进行计算
// 			PPS_CalBindData(pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSndspt);
// 		}
// 
// 		return TRUE;
// 	}
	else
	{
		return FALSE;
	}
}

BOOL PPS_GetWBindData(CTScriptSingleVM *pXvm, long nIndex,const char* pszAttrID, CString &strValue)
{
	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);

	if (pBbData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData error...") );
		return FALSE;
	}

	if (pBbData->GetClassID() != PPCLASSID_WBBDATA)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData error...") );
		return FALSE;
	}

	CWBbData *pWBbData = (CWBbData*)pBbData;
	
	if (pWBbData->m_pDeviceBindData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData: DataNode is null...") );
		return FALSE;
	}

	CDvmData *pData = NULL;
	CExBaseObject *pWBbDeviceBindData = pWBbData->m_pDeviceBindData;
	UINT nClassID = pWBbDeviceBindData->GetClassID();

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pData = (CDvmData*)pWBbDeviceBindData;
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		CDvmDataset *pNode = (CDvmDataset*)pWBbDeviceBindData;
		pData = (CDvmData*)pNode->GetAt(nIndex);

	}

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData: Data is null...") );
		return FALSE;
	}

	CString strAttrID(pszAttrID);

	if (pData->GetValueByID(strAttrID, strValue))
	{
		if (PPS_IsValueTag(strAttrID))
		{
#ifdef UNICODE
			PPS_CalBindData(pXvm, pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt);
#else
			PPS_CalBindData(pXvm, pData, strValue, CString(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt));
#endif
		}

		return TRUE;
	}
// 	strValue = pData->FindTag(strAttrID);
// 
// 	if (strValue.GetLength() > 0)
// 	{
// 		if (PPS_IsValueTag(strAttrID))
// 		{
// 		//获取数据，取得数据对象的值，只要经过发送公式进行计算
// 			PPS_CalBindData(pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSndspt);
// 		}
// 
// 		return TRUE;
// 	}
	else
	{
		return FALSE;
	}
}
//获取数据绑定的数据的属性
BOOL PPS_SetBindData(CTScriptSingleVM *pXvm, const char* pszAttrID, CString &strValue)
{
	CDvmData *pData = (CDvmData*)PPS_GetBindDeviceNodeData(pXvm, pszAttrID);
	CString strAttrID(pszAttrID);

	if (pData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                     , g_sLangTxt_DataUnExist.GetString()/*L"绑定的数据[%s]=[%s]不存在"*/
                                       , pszAttrID, strValue.GetString());
		}
		return FALSE;
	}
	else
	{
		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			return FALSE;
		}

		if (pData->HasValueID(strAttrID))
		{
			if (PPS_IsValueTag(strAttrID))
			{
#ifdef UNICODE
				PPS_CalBindData(pXvm, pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt);
#else
				PPS_CalBindData(pXvm, pData, strValue, CString(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt));
#endif
			}

			pData->SetAttr(strAttrID, strValue);

			return TRUE;
		}
// 		strValue = pData->FindTag(strAttrID);
// 
// 		if (strValue.GetLength())
// 		{
// 			//设置数据，设置数据对象的值，只要经过接受公式进行计算
// 			if (PPS_IsValueTag(strAttrID))
// 			{
// 				PPS_CalBindData(pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt);
// 			}
// 
// 			pData->SetAttr(strAttrID, strValue);
// 			//pTag->m_strValue = strValue;
// 
// 			//数据改变,触发数据改变消息
// 			return TRUE;
// 		}
		else
		{
			if (g_bLogBindQueryErrorInfor)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                    , g_sLangTxt_FctnConDataError.GetString()/*L"函数SetBindDataL:绑定关系数据属性\"%s\"错误"*/
                    , strAttrID.GetString());
			}

			return FALSE;
		}
	}	
}

BOOL PPS_SetWBindData(CTScriptSingleVM *pXvm, long nIndex,const char* pszAttrID, CString &strValue)
{
	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;

	if (pBbData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData error...") );
		return FALSE;
	}

	if (pBbData->GetClassID() != PPCLASSID_WBBDATA)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData error..."));
		return FALSE;
	}

	CWBbData *pWBbData = (CWBbData*)pBbData;

	if (pWBbData->m_pDeviceBindData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData: DataNode is null...") );
		return FALSE;
	}

	CDvmData *pData = NULL;
	CExBaseObject *pWBbDeviceBindData = pWBbData->m_pDeviceBindData;
	UINT nClassID = pWBbDeviceBindData->GetClassID();

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pData = (CDvmData*)pWBbDeviceBindData;
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		CDvmDataset *pNode = (CDvmDataset*)pWBbDeviceBindData;
		pData = (CDvmData*)pNode->GetAt(nIndex);

	}

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("GetWBindData: Data is null...") );
		return FALSE;
	}

	CString strAttrID(pszAttrID);

	if (pData->HasValueID(strAttrID))
	{
		if (PPS_IsValueTag(strAttrID))
		{
#ifdef UNICODE
			PPS_CalBindData(pXvm, pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt);
#else
			PPS_CalBindData(pXvm, pData, strValue, CString(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt));
#endif
		}

		pData->SetAttr(strAttrID, strValue);

		return TRUE;
	}
// 	strValue = pData->FindTag(strAttrID);
// 
// 	if (strValue.GetLength() > 0)
// 	{
// 		//strValue = pTag->m_strValue;
// 
// 		if (PPS_IsValueTag(strAttrID))
// 		{
// 			//获取数据，取得数据对象的值，只要经过发送公式进行计算
// 			PPS_CalBindData(pData, strValue, CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRcvspt);
// 		}
// 
// 		//pTag->m_strValue = strValue;
// 		pData->SetAttr(strAttrID, strValue);
// 
// 		return TRUE;
// 	}
	else
	{
		return FALSE;
	}
}

void PPS_CalBindData(CTScriptSingleVM *pXvm, CExBaseObject *pDvNodeData, CString &strValue, const CString &strScriptID)
{
	if (pDvNodeData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	CDvmData *pData = (CDvmData*)pDvNodeData;
	CDvmDevice *pDevice = (CDvmDevice*)pData->GetAncestor(DVMCLASSID_CDVMDEVICE);

	if (pDevice->IsFormatUseMode_Val())
	{
		return;
	}
	
	//通过绑定关系找到一个数据pData
	//数据返回之前要做计算，计算的公式为“属性＝rcv-scpt”的值
	//在此创建一个LUA对象，根据公式计算值，例如：V*2047/120
	//V＝pTag->m_strValue;
	//LUA脚本的构建   
	/*
	V＝pTag->m_strValue;
	V = V*2047/120;
	*/
	CString strScpt = pData->m_strFormat;
	
	//if (pData->GetValueByID(strScriptID, strScpt))
	if (strScpt.GetLength() > 3)
	{
		CPpDevBaseApp* pApp = g_thePpDevBaseApp;
		char *pszReturn = pXvm->GetChReurn();

		if (pDevice != NULL)
		{
			pApp->CalExpression(strValue, strScpt, pDevice->m_pDeviceAttr);
		}
		else
		{
			pApp->CalExpression(strValue, strScpt, NULL);
		}
	}
}

//拷贝数据到链表，数据列表
/*
<device-model>
	<device>
		<cpu>
		</cpu>
		<SOE>
			<tags>
				<id>SOE</id>
			</tags>
		</SOE>
	</device>
</device-model>
*/
void script_AdBindDataList(CTScriptSingleVM *pXvm, const char *pszListID)
{
	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;

	if (pBbData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallError/*L"函数AdBindDataList调用错误"*/);
		return;
	}

	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSysError4/*L"函数AdBindDataList调用:系统错误(没有关联的设备数据模型)"*/);
		return;
	}

	CExBaseList *pDevice = pTemplate->GetDevice();

	if (pDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSysError4/*L"函数AdBindDataList调用:系统错误(没有关联的设备数据模型)"*/);
		return;
	}

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallData/*L"函数AdBindDataList调用:数据绑定错误"*/);
		}

		return  ;
	}

	CDvmData *pDvNodeData = (CDvmData*)pBbData->QueryByBind(FALSE);
	
	if (pDvNodeData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallData/*L"函数AdBindDataList调用:数据绑定错误"*/);
		}

		return;
	}

	if (pDvNodeData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallData/*L"函数AdBindDataList调用:数据绑定错误"*/);
		}

		return;
	}

	CString strListID(pszListID);
	CDvmDataset *pNode = script_GetReportDataset(pDevice, strListID);

	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);

#ifndef _PP_DEV_MODE_
	if (!pTemplate->IsDvmDataCanAddToReport(pDvNodeData))
	{
		return;
	}
#endif

	if (pNode != NULL)
	{
		CDvmData *pNewNodeData = pNode->AddNewData(pDvNodeData);//pNode->CreateData(pDvNodeData);
	
		CString strTime;
		SYSTEMTIME tm;
		::GetLocalTime(&tm);
		strTime.Format(_T("%d-%d-%d %d:%d:%d"), tm.wYear, tm.wMonth
			, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
		pNewNodeData->SetAttr(_T("tmlocal"), strTime);

		Pp_PostDeviceBindListMsg((WPARAM)pNode, (LPARAM)pNewNodeData);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_FctnCallNode.GetString()/*L"函数AdBindDataList调用:节点\"%s\" 不存在"*/
                 , strListID.GetString());
	}
}

//数据改变消息
void script_FireDataChangeMessage(CTScriptSingleVM *pXvm, long wPara, long lPara)
{
	CDvmData *pData = (CDvmData*)PPS_GetBindDeviceNodeData(pXvm, NULL);
	
	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnFireCallError/*L"函数FireDataMsg调用错误"*/);
	}
	else
	{
		if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			return;
		}

		CPpDevBaseApp* pApp = g_thePpDevBaseApp;
		char *pszReturn = pXvm->GetChReurn();
		pApp->OnPpDeviceDataChanged(pData, wPara, lPara);

		//节点数据改变消息
		CDvmDataset *pNode = (CDvmDataset*)pData->GetParent();
		pApp->OnPpDeviceDataChanged(pNode, wPara, lPara);
	}
}

void script_SetDataID(CDvmData *pData,  const CString &strID)
{
	if (pData == NULL)
	{
		return;
	}

	pData->m_strID = strID;
// 	CPpTag *pTag = pData->FindTag(_T("id"));
// 
// 	if (pTag == NULL)
// 	{
// 		pTag = pData->FindTag(_T("ID"));
// 	}
// 
// 	if (pTag == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pTag->m_strValue.GetLength() < 1)
// 	{
// 		pTag->m_strValue = strID;
// 	}
}


long script_ClearDsDatas(CTScriptSingleVM *pXvm, const char* pszPath)
{
	CDvmDataset *pDvmDataset = script_GetDsDataset(pXvm, pszPath);

	if (pDvmDataset == NULL)
	{
		return 0;
	}

	pDvmDataset->DeleteAll();

	return 0;
}

long script_GetDsDataCount(CTScriptSingleVM *pXvm, const char* pszPath)
{
	if (pszPath[0] == '\0')
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorPath/*_T("系统错误(路径为空)")*/ );
		return NULL;
	}


	CExBaseList *pDevice =script_GetDvmDevice(pXvm);;

	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmDataset *pFind = NULL;
	CString strPath;
	strPath = pszPath;

	//据对全路径
	if (strchr(pszPath, '$') > 0)
	{
		pFind = (CDvmDataset*)pDevice->SelectData(strPath);

		if (pFind != NULL)
		{
			if (pFind->GetClassID() != DVMCLASSID_CDVMDATASET)
			{
				pFind = NULL;
			}
		}
	}
	else
	{//单一索引编号
		long nIndex = atol(pszPath);
		pFind = script_FindDvmDatasetByIndex(pDevice, nIndex);
	}

	if (pFind == NULL)
	{
		return 0;
	}
	else
	{
		return pFind->GetCount();
	}
}

long script_InsertDsData(CDvmDataset *pDataNode, long nTableRowIndex, long nItemIndex)
{
	if (pDataNode == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist4/*L"InsertDsData:数据节点不存在"*/);
		return FALSE;
	}

	CDvmData *pData = (CDvmData*)pDataNode->GetAt(nTableRowIndex);

	if (pData == NULL)
	{
		pData = pDataNode->AddNewData();

		if (pData != NULL)
		{
			pData->SetIndex(nItemIndex);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist3/*L"InsertBindData:数据节点不存在"*/);
		}
	}
	else
	{
		pData->SetIndex(nItemIndex);
	}

	if (pData != NULL)
	{
		CString strID;

		if (pDataNode->m_strDataType.GetLength() > 0)
		{
            strID.Format(_T("%s%03d"), pDataNode->m_strDataType.GetString(), nTableRowIndex);
		}
		else
		{
            strID.Format(_T("%s%03d"), pDataNode->m_strID.GetString(), nTableRowIndex);
		}

		script_SetDataID(pData, strID);
	}

	return 0;
}

void script_InsertToTreeCtrl(CExBaseObject *pData, CExBaseObject *pParent)
{
#ifndef _PSX_IDE_QT_
	if (pData->m_dwItemData != 0)
	{
		return;
	}
	
	CPpEngineData *pPpEngineData = (CPpEngineData*)pData->GetAncestor(PPCLASSID_PPENGINEDATA);

	if (pPpEngineData->m_pRefTreeCtrl != NULL && pParent->m_dwItemData != 0)
	{
		HTREEITEM hItem = pPpEngineData->m_pRefTreeCtrl->InsertItem(pData->m_strID, (HTREEITEM)pParent->m_dwItemData);
		pData->m_dwItemData = (DWORD)hItem;
		pPpEngineData->m_pRefTreeCtrl->SetItemData(hItem, (DWORD)pData);
	}
#endif
}

long script_InsertDataset(CDvmLogicDevice *pDataNode, long nTableRowIndex, long nItemIndex)
{
	if (pDataNode == NULL)
	{
        CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist2.GetString()/*L"InsertDataset:数据节点不存在"*/);
		return FALSE;
	}

	if (pDataNode->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		return FALSE;

	CDvmDataset *pData = (CDvmDataset*)pDataNode->GetAt(nTableRowIndex);

	if (pData == NULL)
	{
		pData = pDataNode->AddNewDataset();

		if (pData != NULL)
		{
			pData->SetIndex(nItemIndex);
		}
		else
		{
            CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist2.GetString()/*L"InsertDataset:数据节点不存在"*/);
		}
	}
	else
	{
		pData->SetIndex(nItemIndex);
	}

	if (pData != NULL)
	{
		CString strID;
        strID.Format(_T("%sGroup%03d"), pDataNode->m_strID.GetString(), nTableRowIndex);
		pData->m_strID = strID;

		script_InsertToTreeCtrl(pData, pDataNode);
	}

	return 0;
}

long script_InsertLogicDevice(CDvmDevice *pDataNode, long nTableRowIndex, long nItemIndex)
{
	if (pDataNode == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist/*L"script_InsertLogicDevice:数据节点不存在"*/);
		return FALSE;
	}

	if (pDataNode->GetClassID() != DVMCLASSID_CDVMDEVICE)
		return FALSE;

	CDvmLogicDevice *pData = (CDvmLogicDevice*)pDataNode->GetAt(nTableRowIndex);

	if (pData == NULL)
	{
		pData = pDataNode->AddNewLogicDevice();

		if (pData != NULL)
		{
			pData->SetIndex(nItemIndex);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist2/*L"InsertDataset:数据节点不存在"*/);
		}
	}
	else
	{
		pData->SetIndex(nItemIndex);
	}

	if (pData != NULL)
	{
		CString strID;
        strID.Format(_T("Device%sCPU%d"), pDataNode->m_strID.GetString(), nTableRowIndex);

		pData->m_strID = strID;

		script_InsertToTreeCtrl(pData, pDataNode);
	}

	return 0;
}


long script_InsertDsDataEx(CDvmDataset *pDataNode, const char *pszName, long nItemIndex)
{
	if (pDataNode == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist4/*L"InsertDsData:数据节点不存在"*/);
		return FALSE;
	}

	if (pszName[0] == 0)
	{
		return FALSE;
	}

	CString strName;
	strName = pszName;
	CDvmData *pData = (CDvmData*)pDataNode->FindByIndex(nItemIndex);

	if (pData == NULL)
	{
		pData = pDataNode->AddNewData();

		if (pData != NULL)
		{
			pData->SetIndex(nItemIndex);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist3/*L"InsertBindData:数据节点不存在"*/);
		}
	}
	else
	{
		pData->SetIndex(nItemIndex);
	}

	if (pData != NULL)
	{
		CString strID;
		pData->m_strName = strName;

		if (pDataNode->m_strDataType.GetLength() > 0)
		{
            strID.Format(_T("%s%03d"), pDataNode->m_strDataType.GetString(), nItemIndex);
		}
		else
		{
            strID.Format(_T("%s%03d"), pDataNode->m_strID.GetString(), nItemIndex);
		}

		script_SetDataID(pData, strID);
	}

	return 0;
}

long script_InsertDatasetEx(CDvmLogicDevice *pDataNode, const char *pszName, long nItemIndex)
{
	if (pDataNode == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist2/*L"InsertDataset:数据节点不存在"*/);
		return FALSE;
	}

	if (pszName[0] == 0)
	{
		return FALSE;
	}

	if (pDataNode->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		return FALSE;

	CString strName;
	strName = pszName;
	CDvmDataset *pDataset2 = (CDvmDataset*)pDataNode->FindByName(strName);
	CDvmDataset *pDataset = (CDvmDataset*)pDataNode->FindByIndex(nItemIndex);

	if (pDataset != pDataset2)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Name=%s  Index=%d  不一致"), strName.GetString(), nItemIndex);
	}

	if (pDataset == NULL)
	{
		pDataset = pDataNode->AddNewDataset();
		pDataset->m_strName = strName;
		pDataset->m_strID = strName;
		pDataset->SetIndex(nItemIndex);
	}
	else
	{
		pDataset->m_strName = strName;
		pDataset->m_strID = strName;
		pDataset->SetIndex(nItemIndex);
	}

	if (pDataset != NULL)
	{
		CString strID;
        strID.Format(_T("%sGroup%03d"), pDataNode->m_strID.GetString(), nItemIndex);

		pDataset->m_strID = strID;

		script_InsertToTreeCtrl(pDataset, pDataNode);
	}

	return 0;
}

long script_InsertLogicDeviceEx(CDvmDevice *pDataNode, const char *pszName, long nItemIndex)
{
	if (pDataNode == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist/*L"script_InsertLogicDevice:数据节点不存在"*/);
		return FALSE;
	}

	if (pszName[0] == 0)
	{
		return FALSE;
	}

	if (pDataNode->GetClassID() != DVMCLASSID_CDVMDEVICE)
		return FALSE;

	CString strName;
	strName = pszName;
	CDvmLogicDevice *pData = (CDvmLogicDevice*)pDataNode->FindByName(strName);

	if (pData == NULL)
	{
		pData = pDataNode->AddNewLogicDevice();

		if (pData != NULL)
		{
			pData->m_strName = strName;
			pData->m_strID = strName;
			pData->SetIndex(nItemIndex);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_DataNodeUnExist2/*L"InsertDataset:数据节点不存在"*/);
		}
	}
	else
	{
		pData->m_strName = strName;
		pData->m_strID = strName;
		pData->SetIndex(nItemIndex);
	}

	if (pData != NULL)
	{
		CString strID;
        strID.Format(_T("Device%sCPU%d"), pDataNode->m_strID.GetString(), nItemIndex);

		pData->m_strID = strID;

		script_InsertToTreeCtrl(pData, pDataNode);
	}

	return 0;
}


long script_InsertBindData(CTScriptSingleVM *pXvm, long nTableRowIndex)
{
	CDvmDataset *pDataNode = (CDvmDataset*)PPS_GetBindDeviceDataNode(pXvm);

	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;
	long nItemIndex = pBbData->GetBindItemIndex();

	return script_InsertDsData(pDataNode, nTableRowIndex, nItemIndex);
// 	if (pDataNode == NULL)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, L"InsertBindData:数据节点不存在");
// 		return FALSE;
// 	}
// 
// 	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;
// 	long nItemIndex = pBbData->GetBindItemIndex();
// 
// 	if (nItemIndex == -1)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, L"InsertBindData:数据节点不存在");
// 		return FALSE;
// 	}
// 
// 	CDvmData *pData = (CDvmData*)pDataNode->GetAt(nTableRowIndex);
// 
// 	if (pData == NULL)
// 	{
// 		pData = pDataNode->AddNewData();
// 
// 		if (pData != NULL)
// 		{
// 			pData->SetIndex(nItemIndex);
// 		}
// 		else
// 		{
// 			CLogPrint::LogString(XLOGLEVEL_ERROR, L"InsertBindData:数据节点不存在");
// 		}
// 	}
// 	else
// 	{
// 		pData->SetIndex(nItemIndex);
// 	}
// 
// 	if (pData != NULL)
// 	{
// 		CString strID;
// 		strID.Format(_T("%s%03d"), pDataNode->m_strDataType, nTableRowIndex);
// 		script_SetDataID(pData, strID);
// 	}
//
//	return 0;
}

long script_InsertBindDataset(CTScriptSingleVM *pXvm, long nTableRowIndex)
{
	CDvmLogicDevice *pDataNode = (CDvmLogicDevice*)PPS_GetBindDeviceDataNode(pXvm);

	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;
	long nItemIndex = pBbData->GetBindItemIndex();

	return script_InsertDataset(pDataNode, nTableRowIndex, nItemIndex);
}

long script_InsertBindLogicDevice(CTScriptSingleVM *pXvm, long nTableRowIndex)
{
	CDvmDevice *pDataNode = (CDvmDevice*)PPS_GetBindDeviceDataNode(pXvm);

	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;
	long nItemIndex = pBbData->GetBindItemIndex();

	return script_InsertLogicDevice(pDataNode, nTableRowIndex, nItemIndex);
}

long script_GetBindDataL(CTScriptSingleVM *pXvm, const char* pszAttrID)
{
	CString strVal;
	if (PPS_GetBindData(pXvm, pszAttrID, strVal) )
	{
#ifdef UNICODE
		long nVal = _wtol(strVal);
#else
        long nVal = atol(strVal.GetString());
#endif
		return nVal;
	}
	else
	{
		return 0;
	}
}

double script_GetBindDataD(CTScriptSingleVM *pXvm, const char* pszAttrID)
{
	CString strVal;
	if (PPS_GetBindData(pXvm, pszAttrID, strVal) )
	{
#ifdef UNICODE
		return _wtof(strVal);
#else
        return atof(strVal.GetString());
#endif
	}
	else
	{
		return 0;
	}
}

char* script_GetBindDataStr(CTScriptSingleVM *pXvm, const char* pszAttrID)
{
	CString strVal;
	if (PPS_GetBindData(pXvm, pszAttrID, strVal))
	{
		char *pszReturn = pXvm->GetChReurn();
		CString_to_char(strVal, pszReturn);
		return pszReturn;
	}
	else
	{
		return 0;
	}
}

long script_GetWBindDataL(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID)
{
	CString strVal;
	if (PPS_GetWBindData(pXvm, nIndex, pszAttrID, strVal) )
	{
#ifdef UNICODE
		long nVal = _wtol(strVal);
#else
        long nVal = atol(strVal.GetString());
#endif
		return nVal;
	}
	else
	{
		return 0;
	}
}

double script_GetWBindDataD(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID)
{
	CString strVal;
	if (PPS_GetWBindData(pXvm, nIndex, pszAttrID, strVal) )
	{
#ifdef UNICODE
		return _wtof(strVal);
#else
        return atof(strVal.GetString());
#endif
	}
	else
	{
		return 0;
	}
}

char* script_GetWBindDataStr(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID)
{
	CString strVal;
	if (PPS_GetWBindData(pXvm, nIndex, pszAttrID, strVal))
	{
		char *pszReturn = pXvm->GetChReurn();
		CString_to_char(strVal, pszReturn);
		return pszReturn;
	}
	else
	{
		return 0;
	}
}

CExBaseObject* PPS_GetBindDeviceNodeData(CTScriptSingleVM *pXvm, const char* pszAttrID)
{
	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;

	if (pBbData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnGetCallError/*L"函数GetBindDataL调用错误"*/);
		return NULL;
	}

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return NULL;
	}

	CExBaseObject *pDvNodeData = pBbData->QueryByBind(FALSE);

	if (pDvNodeData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_FctnSetError.GetString()/*L"函数SetBindDataL:字节块\"%s\"中绑定错误"*/
                , pByteBlock->m_strName.GetString());
		}
		return NULL;
	}

	//$$ 20160414
	if (pDvNodeData->GetClassID() != DVMCLASSID_CDVMDATA && pDvNodeData->GetClassID() != DVMCLASSID_CDVMDATASET && pDvNodeData->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_FctnBindSet.GetString()/*L"函数SetBindDataL:字节块\"%s\"中绑定数据集"*/
                , pByteBlock->m_strName.GetString());
		}

		/************************************************************************/
		/* 
		2011-06-14 by zah
		*/
		/************************************************************************/
		//CDvmDataset *pNode = (CDvmDataset*)pDvNodeData;
		//CExBaseObject *pData = pNode->GetItem(0);
		//return pData;
		
		return NULL;
	}
	else
	{
		return pDvNodeData;
	}
}

CExBaseObject* PPS_GetBindDeviceDataNode(CTScriptSingleVM *pXvm)
{
	CBbData *pBbData = (CBbData*)PPS_GetBbdata(pXvm);;

	if (pBbData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnBindCallError/*L"函数###BindData###调用错误"*/);
		return NULL;
	}

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return NULL;
	}

	CExBaseObject *pDvDataNode = pBbData->QueryByBind(TRUE);

	if (pDvDataNode == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_FctnGetError.GetString()/*L"函数GetBindDeviceDataNode:字节块\"%s\"中绑定错误"*/
                , pByteBlock->m_strName.GetString());
		}
		return NULL;
	}

	//$$ 20160414
	if (pDvDataNode->GetClassID() != DVMCLASSID_CDVMDATASET && pDvDataNode->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE && pDvDataNode->GetClassID() != DVMCLASSID_CDVMDEVICE)
	{
		if (g_bLogBindQueryErrorInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_FctnDataSet.GetString()/*L"函数GetBindDeviceDataNode:字节块\"%s\"中绑定数据集"*/
                , pByteBlock->m_strName.GetString());
		}

		return NULL;
	}
	else
	{
		return pDvDataNode;
	}
}

CDvmDataset* script_GetDeviceDataNode(CTScriptSingleVM *pXvm, const char* pszPath)
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CPpTemplate *pTemplate = NULL;

	pTemplate = (CPpTemplate*)pObj->GetAncestor(PPCLASSID_PPTEMPLATE);

	if (pTemplate == NULL)
	{
		return NULL;
	}

	CExBaseList *pDevice = pTemplate->GetDevice();

	if (pDevice == NULL)
	{
		return NULL;
	}

	CExBaseObject *p = pDevice->SelectData(CString(pszPath));

	if (p == NULL)
	{
		return NULL;
	}

	if (p->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return NULL;
	}
	else
	{
		return (CDvmDataset*)p;
	}
}

CString script_GetDeviceNodeDataAttrValueString(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, long nItemIndex)
{
	CDvmDataset *pNode = script_GetDeviceDataNode(pXvm, pszPath);

	if (pNode == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_PathNoData.GetString()/*_T("path[%s]没有对应的数据节点")*/, pszPath);
		return _T("0");
	}

	CExBaseObject *p = NULL;
	CDvmData *pData = NULL;
	pData = pNode->FindByIndex(nItemIndex);

	if (pData == NULL)
	{
		return _T("0");
	}
	else
	{
#ifdef UNICODE
		return pData->m_strValue;
#else
		return CString(pData->m_strValue);
#endif
	}
}

double script_GetDeviceNodeDataAttrValueD(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, long nItemIndex)
{
	CString strValue = script_GetDeviceNodeDataAttrValueString(pXvm, pszPath, pszAttrID, nItemIndex);
	return CString_To_double(strValue);
}

long script_GetDeviceNodeDataAttrValueL(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, long nItemIndex)
{
	CString strValue = script_GetDeviceNodeDataAttrValueString(pXvm, pszPath, pszAttrID, nItemIndex);
	return CString_To_long(strValue);
}

long script_GetNextDeviceNodeDataByAttrValue(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, double dValue, long nCurrIndex)
{
	CDvmDataset *pNode = script_GetDeviceDataNode(pXvm, pszPath);

	if (pNode == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                  , g_sLangTxt_PathNoData.GetString()/*_T("path[%s]没有对应的数据节点")*/, pszPath);
		return -1;
	}

	CExBaseObject *p = NULL;
	CDvmData *pData = NULL;
	CDvmData *pDataFind = NULL;
	POS pos = NULL;
	long nIndexFind = nCurrIndex;

	if (nCurrIndex == -1)
	{
		pos = pNode->GetHeadPosition();
	}
	else
	{
		pData = pNode->FindByIndex(nCurrIndex);

		if (pData == NULL)
		{
			return -1;
		}

		pos = pNode->Find(pData);
		pNode->GetNext(pos);
	}

	CString strValue;
	CString strAttrID(pszAttrID);

	while (pos != NULL)
	{
		p = pNode->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)p;
			
			if (pData->GetValueByID(strAttrID, strValue))
			{
				double d = CString_To_long(strValue);

				if (fabs(d - dValue) <= 0.001)
				{
					pDataFind = pData;
					break;
				}
			}
		}
	}

	if (pDataFind == NULL)
	{
		return -1;
	}
	else
	{
		return pDataFind->m_nIndex;
	}
	
}

void script_SetDeviceNodeDataAttrs(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, double dValue)
{
	CDvmDataset *pNode = script_GetDeviceDataNode(pXvm, pszPath);

	if (pNode == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                  , g_sLangTxt_PathNoData.GetString()/*_T("path[%s]没有对应的数据节点")*/
                  , pszPath);
		return;
	}

// 	if (!pNode->IsDataNode())
// 	{
// 		return;
// 	}

	CExBaseObject *p = NULL;
	CDvmData *pData = NULL;
	POS pos = pNode->GetHeadPosition();
	CString strValue;
	strValue.Format(_T("%f"), dValue);
	CString strAttrID(pszAttrID);

	while (pos != NULL)
	{
		p = pNode->GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)p;
			pData->SetAttr(strAttrID, strValue);
		}
	}
}

void script_SetDeviceNodeDataAttr(CTScriptSingleVM *pXvm, const char* pszPath, const char* pszAttrID, double dValue)
{
// 	CDvmDataset *pNode = script_GetDeviceDataNode(pszPath);
// 
// 	if (!pNode->IsDataNode())
// 	{
// 		return;
// 	}
// 
// 	CExBaseObject *p = NULL;
// 	CDvmData *pData = NULL;
// 	POS pos = pNode->GetHeadPosition();
// 	CString strValue;
// 	strValue.Format(_T("%f"), dValue);
// 	CString strAttrID(pszAttrID);
// 
// 	while (pos != NULL)
// 	{
// 		p = pNode->GetNext(pos);
// 
// 		if (p->GetClassID() == DMCLASSID_DEVICENODEDATA)
// 		{
// 			pData = (CDvmData *)p;
// 			pData->SetAttribute(strAttrID, strValue);
// 		}
// 	}
}

//设置数据绑定的数据的属性值
void script_SetBindDataL(CTScriptSingleVM *pXvm, const char* pszAttrID, long nValue)
{
	CString strVal;
	strVal.Format(_T("%d"), nValue);

	PPS_SetBindData(pXvm, pszAttrID, strVal);
}

void script_SetBindDataD(CTScriptSingleVM *pXvm, const char* pszAttrID, double dValue)
{
	CString strVal;
	strVal.Format(_T("%f"), dValue);

	PPS_SetBindData(pXvm, pszAttrID, strVal);
}

void script_SetWBindDataL(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID, long nValue)
{
	CString strVal;
	strVal.Format(_T("%d"), nValue);

	PPS_SetWBindData(pXvm, nIndex, pszAttrID, strVal);
}

void script_SetWBindDataD(CTScriptSingleVM *pXvm, long nIndex, const char* pszAttrID, double dValue)
{
	CString strVal;
	strVal.Format(_T("%f"), dValue);

	PPS_SetWBindData(pXvm, nIndex, pszAttrID, strVal);
}

void script_SetBindDataStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char* pszValue)
{
	CString strVal(pszValue);

	PPS_SetBindData(pXvm, pszAttrID, strVal);
}

//////////////////////////////////////////////////////////////////////////
//float
void script_SetBbCurrValueFloat(CTScriptSingleVM *pXvm, long nIndex, float nValue) //4 bytes
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	int nBytes = 4;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if (nBytes > 0 && (nIndex+nBytes) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				memcpy(pByteBlock->m_pBuffer+nIndex, &nValue, nBytes);
				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
            , g_sLangTxt_DataErrorIndex.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Bytes=%d Length=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex, nBytes, nLength);
	}
}

float script_GetBbCurrValueFloat(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	int nBytes = 4;
	if(pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nBytes <= nLength)
	{
		for (long nIndexEx=0; nIndexEx<nBytes; nIndexEx++)
		{
			nReturn += (pByteBlock->m_pBuffer[nIndex+nIndexEx]<<(8*nIndexEx));
		}
	}

	float nValue ;
	memcpy(&nValue,&nReturn,4);

	return nValue;
}


// DM05系列数字表取数
float script_GetBbCurrValueFloatDM05(CTScriptSingleVM *pXvm)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	int nBytes = 5;
	if(pByteBlock == NULL)
	{
		return 0;
	}

	char fValue[7] = {0};
	long nLength = pByteBlock->GetByteBlockLength();
	if (nLength<6)
	{
		return 0;
	}

	for (int i=0;i<7;i++)
	{
		fValue[i] = pByteBlock->m_pBuffer[i];
	}

	float nValue = atof(fValue);

	return nValue;
}

long script_GetBbCurrValueLongFromASCII(CTScriptSingleVM *pXvm)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return 0;
	}

	long nvt = 0;
	long nLength = pByteBlock->GetByteBlockLength();
	for (int i=nLength;i>0;i--)
	{
		long nValue = pByteBlock->m_pBuffer[nLength-i];
		nValue = nValue-48;
		nvt += nValue*pow(double(16),(double)(i-1));
	}

	return nvt;
}

//2个字节
void script_SetBbCurrValueLongToASCII(CTScriptSingleVM *pXvm, long nValue)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	BYTE nbValue = nValue/16;
	nbValue = nbValue + 48;
	
	memcpy(pByteBlock->m_pBuffer, &nbValue, 1);
	nbValue = nValue%16;
	nbValue = nbValue + 48;

	memcpy(pByteBlock->m_pBuffer+1, &nbValue, 1);
	
}

//////////////////////////////////////////////////////////////////////////
//byteblock
void script_SetByteBlockEnable(CTScriptSingleVM *pXvm, const char *pszBbID, long nShow)
{

}

long script_SetByteBlockEnable2(CTScriptSingleVM *pXvm, const char *pszBbID)
{
	return 0;
}

void script_SetByteBlockLength(CTScriptSingleVM *pXvm, const char *pszBbID, long nLen)
{

}

long script_GetByteBlockLength(CTScriptSingleVM *pXvm, const char *pszBbID)
{
	return 0;
}



//////////////////////////////////////////////////////////////////////////
// 获取变量值
CBbVariable* PPS_GetBbVariable(CTScriptSingleVM *pXvm, const char* pszVariableID)
{
	char *pszReturn = pXvm->GetChReurn();
	CPpScript *pScript = PPS_GetPpScript(pXvm);;
	CString strID;
	strID = pszVariableID;

    return PpFindVariableByID(pScript, strID);
}

long script_GetValue(CTScriptSingleVM *pXvm, const char *pszVariableID)
{
	CBbVariable* pVar = PPS_GetBbVariable(pXvm, pszVariableID);

	if (pVar == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_SetVariUnExist.GetString()/*L"GetValue:变量\"%s\"不存在"*/
                 , pszVariableID);
		return 0;
	}

#ifdef UNICODE
	return _wtol(pVar->m_strValue);
#else
    return atol(pVar->m_strValue.GetString());
#endif
}

const char* script_GetValueString(CTScriptSingleVM *pXvm, const char *pszVariableID)
{
	CBbVariable* pVar = PPS_GetBbVariable(pXvm, pszVariableID);

	if (pVar == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_SetVariUnExist.GetString()/*L"GetValue:变量\"%s\"不存在"*/
                 , pszVariableID);
		return 0;
	}

	CString strValue = pVar->m_strValue;
	strValue.Replace(_T("\""), _T(""));

	char *pszReturn = pXvm->GetChReurn();

	CString_to_char(strValue, pszReturn);
	return pszReturn;
}

void script_SetValueLong(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue)
{
	CBbVariable* pVar = PPS_GetBbVariable(pXvm, pszVariableID);

	if (pVar == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                  , _T("SetValueLong: %s not exist")
                  , pszVariableID);
		return ;
	}
	
	pVar->m_strValue.Format(_T("%d"), nValue);
}

void script_SetValueDouble(CTScriptSingleVM *pXvm, const char *pszVariableID, double nValue)
{
	CBbVariable* pVar = PPS_GetBbVariable(pXvm, pszVariableID);

	if (pVar == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_SetLongVariUnExist.GetString()/*L"SetValueLong:变量\"%s\"不存在"*/, pszVariableID);
		return ;
	}

	pVar->m_strValue.Format(_T("%f"), nValue);
}

double script_GetValueDouble(CTScriptSingleVM *pXvm, const char *pszVariableID)
{
	CBbVariable* pVar = PPS_GetBbVariable(pXvm, pszVariableID);

	if (pVar == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_SetVariUnExist.GetString()/*L"GetValueDouble:变量\"%s\"不存在"*/, pszVariableID);
		return 0;
	}
	
	return CString_To_double(pVar->m_strValue);
}

void script_SetValueString(CTScriptSingleVM *pXvm, const char *pszVariableID, const char *pszValue)
{
	CBbVariable* pVar = PPS_GetBbVariable(pXvm, pszVariableID);

	if (pVar == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_SetLongVariUnExist.GetString()/*L"SetValueLong:变量\"%s\"不存在"*/, pszVariableID);
		return ;
	}

	pVar->m_strValue = pszValue;
}

void script_SetPkgLen(CTScriptSingleVM *pXvm, long nLen)
{
	ASSERT (FALSE);
	CPpDevBaseApp *pApp = g_thePpDevBaseApp;
	pApp->ScriptSetPkgLen(nLen);
}

void script_SetPkgRequiredLen(CTScriptSingleVM *pXvm, long nLen)
{
	CPpScript *pScript = PPS_GetPpScript(pXvm);;

	CPpParsePackage *pPackage = NULL;

	pPackage = (CPpParsePackage *)pScript->GetAncestor(PPCLASSID_PPPARSEPACKGE);

	if (pPackage == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetPkgRequiredLen: not in parse package..."));
		return;
	}

	pPackage->m_nRequiredLen = nLen;
}

void script_SetPkgValid(CTScriptSingleVM *pXvm, long nValid)
{
	char *pszReturn = pXvm->GetChReurn();
	CPpScript *pScript = PPS_GetPpScript(pXvm);;

	CPpPackage *pPackage = NULL;

	pPackage = (CPpPackage *)pScript->GetAncestor(PPCLASSID_PPPARSEPACKGE);

	if (pPackage == NULL)
	{
		pPackage = (CPpPackage *)pScript->GetAncestor(PPCLASSID_PPPRODUCEPACKGE);
	}

	if (pPackage == NULL)
	{
		return;
	}

	pPackage->m_bValid = nValid;
}

long script_GetPkgLen(CTScriptSingleVM *pXvm )
{
	char *pszReturn = pXvm->GetChReurn();
	CBaseObject *pScript = PPS_GetPpScript(pXvm);;
	CBaseObject *pFind = NULL;

	pFind = pScript->GetAncestor(PPCLASSID_PPTTPACKAGE);

	if (pFind != NULL)
	{
		CPpTtPackage *pPkg = (CPpTtPackage*)pFind;
		return pPkg->m_nPkgLen;
	}
	else
	{
		pFind = pScript->GetAncestor(PPCLASSID_PPPRODUCEPACKGE);

		if (pFind != NULL)
		{
			CPpParsePackage *pPkg = (CPpParsePackage*)pFind;
			return pPkg->m_nPkgLen;
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_GetFctnCallErrorLen/*L"GetPkgLen函数调用错误"*/);
				return 0;
			return 0;
		}
	}
}

//当前规约支持的最大长度
long script_GetPkgMaxLen(CTScriptSingleVM *pXvm )
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		return 0;
	}
	else
	{
		return pTemplate->m_nPackageMaxLength;
	}
}

long script_GetPkgNum(CTScriptSingleVM *pXvm)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return 0;
	}

	long nReturn = 0;

	if (pByteBlock == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_GetFctnCallErrorPkg/*L"GetPkgNum函数调用错误"*/);
		return 0;
	}

	long nLength = pByteBlock->GetByteBlockLength();
	CBaseObject *pObj = NULL;

	pObj = pByteBlock->GetAncestor(PPCLASSID_PPTTPACKAGE);
	if (pObj != NULL)
	{
		CPpTtPackage *pPkg = (CPpTtPackage*)pObj;
		return pPkg->m_nPkgNum;
	}
	else
	{
		pObj = pByteBlock->GetAncestor(PPCLASSID_PPPRODUCEPACKGE);
		if (pObj != NULL)
		{
			CPpParsePackage *pPkg = (CPpParsePackage*)pObj;
			return pPkg->m_nPkgNum;
		}
		else
		{
			return 0;
		}
	}
}

long script_GetPkgParsePos(CTScriptSingleVM *pXvm)
{
	CPpPackageDetail *pDetail = PPS_GetPackageDetail(pXvm);

	if (pDetail == NULL)
	{
		return 0;
	}
	
	return pDetail->GetTotalLen();
}

long script_GetPkgCurrBufVal(CTScriptSingleVM *pXvm, long nOffset)
{
	CPpPackageDetail *pDetail = PPS_GetPackageDetail(pXvm);

	if (pDetail == NULL)
	{
		return 0;
	}

	return pDetail->GetPkgCurrBufVal(nOffset);
}

void script_AddGlobal(CPpTemplate *pTemplate, const char *pszVariableID, long nValue)
{


	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_AddFctnCallError/*L"AddGlobal函数调用错误"*/);
	}
	else
	{
		CString strVariableID(pszVariableID);
		CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);

		if (pVariable != NULL)
		{
#ifdef UNICODE
			long nTempValue = _wtol(pVariable->m_strValue) + nValue;
#else
            long nTempValue = atol(pVariable->m_strValue.GetString()) + nValue;
#endif
			pVariable->m_strValue.Format(_T("%d"), nTempValue);
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"AddGlobal函数，变量\"%s\"=%s", strVariableID, pVariable->m_strValue);
		}
		else
		{
			pVariable = pTemplate->m_pDataInterface->AddVariable(strVariableID,_T(""));
			pVariable->m_strValue.Format(_T("%d"), nValue);
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"AddGlobal，变量\"%s\"=%s", strVariableID, pVariable->m_strValue);
		}
	}
}

void script_AddGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	script_AddGlobal(pTemplate, pszVariableID, nValue);
}

//增加浮点型全局变量
void script_AddGlobalDouble(CPpTemplate *pTemplate, const char *pszVariableID, double nValue)
{


	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("AddGlobalDouble函数调用错误"));
	}
	else
	{
		CString strVariableID(pszVariableID);
		CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);

		if (pVariable != NULL)
		{
			//long nTempValue = _wtol(pVariable->m_strValue) + nValue;
			//pVariable->m_strValue.Format(L"%d", nTempValue);
#ifdef UNICODE
			double nTempValue = _wtof(pVariable->m_strValue) + nValue;
#else
            double nTempValue = atof(pVariable->m_strValue.GetString()) + nValue;
#endif
			pVariable->m_strValue.Format(_T("%f"), nTempValue);
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"AddGlobal函数，变量\"%s\"=%s", strVariableID, pVariable->m_strValue);
		}
		else
		{
			pVariable = pTemplate->m_pDataInterface->AddVariable(strVariableID, _T(""));
			pVariable->m_strValue.Format(_T("%f"), nValue);
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"AddGlobal，变量\"%s\"=%s", strVariableID, pVariable->m_strValue);
		}
	}
}

void script_AddGlobalDouble(CTScriptSingleVM *pXvm, const char *pszVariableID, double nValue)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	script_AddGlobalDouble(pTemplate, pszVariableID, nValue);
}

void script_SubGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_AddFctnCallError/*L"AddGlobal函数调用错误"*/);
	}
	else
	{
		CString strVariableID(pszVariableID);
		CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);

		if (pVariable != NULL)
		{
#ifdef UNICODE
			long nTempValue = _wtol(pVariable->m_strValue) - nValue;
#else
            long nTempValue = atol(pVariable->m_strValue.GetString()) - nValue;
#endif
			pVariable->m_strValue.Format(_T("%d"), nTempValue);
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"AddGlobal函数，变量\"%s\"=%s", strVariableID, pVariable->m_strValue);
		}
		else
		{
			pVariable = pTemplate->m_pDataInterface->AddVariable(strVariableID,_T(""));
			pVariable->m_strValue.Format(_T("%d"), nValue);
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"AddGlobal，变量\"%s\"=%s", strVariableID, pVariable->m_strValue);
		}
	}
}

long script_GetGlobal(CPpTemplate *pTemplate, const char *pszVariableID)
{
	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_GetFctnCallError/*L"GetGlobal函数调用错误"*/);
		return 0;
	}
	else
	{
		CString strVariableID(pszVariableID);
		CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);

		if (pVariable == NULL)
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"GetGlobal函数调用错误，变量\"%s\"不存在，调用AddGlobal", strVariableID);
			script_AddGlobal(pTemplate, pszVariableID, 0);
			return 0;
		}
		else
		{
#ifdef UNICODE
			return _wtol(pVariable->m_strValue);
#else
            return atol(pVariable->m_strValue.GetString());
#endif
		}
	}
}

long script_GetGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	return script_GetGlobal(pTemplate, pszVariableID);
}

//获取浮点型全局变量
double script_GetGlobalDouble(CPpTemplate *pTemplate, const char *pszVariableID)
{
	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_GetFctnCallError/*L"GetGlobal函数调用错误"*/);
		return 0;
	}
	else
	{
		CString strVariableID(pszVariableID);
		CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);

		if (pVariable == NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("GetGlobal函数调用错误，变量\"%s\"不存在，调用AddGlobal"), strVariableID.GetString());
			//script_AddGlobal(pTemplate, pszVariableID, 0);
			return 0;
		}
		else
		{
			//return _wtol(pVariable->m_strValue);
#ifdef UNICODE
			return _wtof(pVariable->m_strValue);
#else
            return atof(pVariable->m_strValue.GetString());
#endif
		}
	}
}

double script_GetGlobalDouble(CTScriptSingleVM *pXvm, const char *pszVariableID)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	return script_GetGlobalDouble(pTemplate, pszVariableID);
}

long script_GetGlobalEx(const CString &strVariableID, CPpTemplate *pTemplate)
{
	CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);

	if (pVariable == NULL)
	{
		pVariable = pTemplate->m_pDataInterface->AddVariable(strVariableID,_T(""));
		pVariable->m_strValue = _T("0");

		return 0;
	}
	else
	{
#ifdef UNICODE
		return _wtol(pVariable->m_strValue);
#else
        return atol(pVariable->m_strValue.GetString());
#endif
	}
}

long script_GetGlobalEx(const CString &strVariableID, CExBaseObject *pPpObj)
{
	CPpTemplate *pTemplate = (CPpTemplate*)pPpObj->GetAncestor(PPCLASSID_PPTEMPLATE);

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_GetFctnCallError/*L"GetGlobal函数调用错误"*/);
		return 0;
	}
	else
	{
		return script_GetGlobalEx(strVariableID, pTemplate);
	}
}

long script_GetGlobalEx(const char *pszVariableID, CExBaseObject *pPpObj)
{
	CString strVariableID(pszVariableID);
	return script_GetGlobalEx(strVariableID, pPpObj);
}

void script_SetGlobal(CTScriptSingleVM *pXvm, const char *pszVariableID, long nValue)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SetFctnCallError/*L"SetGlobal函数调用错误"*/);
	}
	else
	{
		CString strVariableID(pszVariableID);
		CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);
		if (pVariable == NULL)
		{
			script_AddGlobal(pXvm, pszVariableID, nValue);
		}
		else
		{
			pVariable->m_strValue.Format(_T("%d"), nValue);
		}

		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"AddGlobal函数，变量\"%s\"=%d", strVariableID, nValue);

	}
}


void script_SetGlobalDouble(CTScriptSingleVM *pXvm, const char *pszVariableID, double nValue)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SetFctnCallError/*L"SetGlobal函数调用错误"*/);
	}
	else
	{
		CString strVariableID(pszVariableID);
		CBbVariable *pVariable = (CBbVariable*)pTemplate->m_pDataInterface->FindByID(strVariableID);
		if (pVariable == NULL)
		{
			script_AddGlobalDouble(pXvm, pszVariableID, nValue);
		}
		else
		{
			pVariable->m_strValue.Format(_T("%f"), nValue);
		}

		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"AddGlobal函数，变量\"%s\"=%d", strVariableID, nValue);

	}
}

long script_IsProcedureExist(CTScriptSingleVM *pXvm, const char *pszProcedureID)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSysError3/*L"函数Run调用:系统错误"*/);
		return 1;
	}

	// #ifndef _PP_DEV_MODE_
	CPpEngineBaseApp *pApp = g_pTheEngineApp;
	CPpEngineThreadBase *pEngineThread = pApp->FindEngineThread(pTemplate);
	return pEngineThread->IsProcedureExist(CString(pszProcedureID));
}

//引擎执行部分
void script_Run(CTScriptSingleVM *pXvm, const char *pszProcedureID)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSysError3/*L"函数Run调用:系统错误"*/);
		return;
	}

// #ifndef _PP_DEV_MODE_
	CPpEngineBaseApp *pApp = g_pTheEngineApp;
	CPpEngineThreadBase *pEngineThread = pApp->FindEngineThread(pTemplate);
	pEngineThread->RunProcedure(CString(pszProcedureID), NULL, FALSE);
// #endif
}

void script_SetPpRunState(CTScriptSingleVM *pXvm, long nRunState)
{
	CPpProcedure *pProcedure = script_GetPpProcedure(pXvm);

	if (pProcedure == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSysError2/*L"函数SetPpRunState调用:系统错误"*/);
		return;
	}

	pProcedure->m_dwRunState = nRunState;
}

void script_SetPpValid(CTScriptSingleVM *pXvm, long nValid)
{
	CPpProcedure *pProcedure = script_GetPpProcedure(pXvm);

	if (pProcedure == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSysError/*L"函数SetPpValid调用:系统错误"*/);
		return;
	}

	pProcedure->m_bValid = nValid;
}

void script_Connect(CTScriptSingleVM *pXvm )
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSystem/*L"函数Connect调用:系统错误(没有关联的设备数据模型)"*/);
		return;
	}

// #ifndef _PP_DEV_MODE_
	CPpEngineBaseApp *pApp = g_pTheEngineApp;
	CPpEngineThreadBase *pEngineThread = pApp->FindEngineThread(pTemplate);

#ifndef _PSX_IDE_QT_
	CWnd *pMainWnd = AfxGetMainWnd();
	pMainWnd->PostMessage(WM_SCRIPT_CONNECT_DEVICE, (WPARAM)pEngineThread ,(LPARAM)pEngineThread);
#endif
// #endif
}

void script_DisConnect(CTScriptSingleVM *pXvm )
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSysError4/*L"函数AdBindDataList调用:系统错误(没有关联的设备数据模型)"*/);
		return;
	}

// #ifndef _PP_DEV_MODE_
	CPpEngineBaseApp *pApp = g_pTheEngineApp;
	CPpEngineThreadBase *pEngineThread = pApp->FindEngineThread(pTemplate);

#ifndef _PSX_IDE_QT_
    CWnd *pMainWnd = AfxGetMainWnd();
	pMainWnd->PostMessage(WM_SCRIPT_DISCONNECT_DEVICE, (WPARAM)pEngineThread ,(LPARAM)pEngineThread);
#endif
// #endif
}

/************************************************************************/
/* 
2011-03-12 by zah
*/
/************************************************************************/
void script_CrcClear(CTScriptSingleVM *pXvm )
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	pTemplate->m_vecCRC.clear();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CrcClear"));
}

void script_CrcPushbackBb(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		script_CrcPushback(pXvm, *(pByteBlock->m_pBuffer+nIndex));
		bTrue = TRUE;
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
            , g_sLangTxt_DataIndexError.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d Length=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex, nLength);
	}
}

void script_CrcPushback(CTScriptSingleVM *pXvm, BYTE ch)
{
	CPpTemplate* pTemplate = script_GetPpTemplate(pXvm);;
	pTemplate->m_vecCRC.push_back(ch);
}

BYTE crc_cdt(std::vector<BYTE>::iterator buff,int len) 
{ 
	int q=0,r=0; 
	int crc=0; 
	int i; 

	while(q<len)
	{ 
		if(buff[q]&(0x80>>r)) 
		{
			crc|=0x01; 
		}

		if(crc>=0x100) 
		{
			crc^=0x107; 
		}

		crc<<=1; 
		r++; 

		if(r==8) 
		{ 
			r=0; 
			q++; 
		} 
	} 

	for(i=0;i<8;i++) 
	{ 
		if(crc>=0x100) 
		{
			crc^=0x107; 
		}

		crc<<=1; 
	} 

	crc>>=1; 
	crc=(~crc); 

	return (unsigned char)crc; 
} 

WORD crc_sf_word(std::vector<BYTE>::iterator buff,int len) 
{ 
	WORD r2,r3;
	WORD r01=0;
	int bz,k=0;

	do
	{
		r2=buff[k];
		r3=8;
BBB:
		bz=r2&0x80;
		r2<<=1;

		if(bz)
		{
			bz=r01&0x8000;
			if(bz) r01<<=1;
			else
			{
				r01^=0x810;
				r01<<=1;
				r01|=0x1;
			}
		}
		else
		{
			bz=r01&0x8000;
			if(!bz) r01<<=1;
			else
			{
				r01^=0x810;
				r01<<=1;
				r01|=0x1;
			}
		}
		r3--;
		if(r3!=0)  goto BBB;
		else k++;
	}while(k < len);

	CString strHex;
	BYTE byteValue;
	char byteHex[4];
	byteHex[3] = 0;

	for (k=0;k<len;k++)
	{
		byteValue = buff[k];
		ValueToHex(byteValue, byteHex, TRUE, FALSE);
		strHex += byteHex;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SF2000CRC"));
	CLogPrint::LogString(XLOGLEVEL_TRACE, strHex);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%X"), r01);


	return r01;
} 

BYTE script_CrcCDT(CTScriptSingleVM *pXvm )
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	int nLen = pTemplate->m_vecCRC.size();

	return crc_cdt(pTemplate->m_vecCRC.begin(),nLen);
}

WORD script_CrcSfWord(CTScriptSingleVM *pXvm)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	int nLen = pTemplate->m_vecCRC.size();

	return crc_sf_word(pTemplate->m_vecCRC.begin(),nLen);
}

long crc_modbus(std::vector<BYTE>& vec, unsigned int len, unsigned int nInitValue) 
{
	char *buf = new char[len];
	unsigned int i = 0, j = 0;;

	for(i=0;i<len;i++)
	{
		buf[i] =  vec[i];
	}

	unsigned int c, crc = nInitValue;

	for (i = 0; i < len; i++)
	{
		c = *(buf+i) & 0x00FF;
		crc^=c;

		for(j=0;j<8;j++)
		{
			if (crc & 0x0001)
			{
				crc>>=1;
				crc^=0xA001;
			}
			else
			{
				crc>>=1;
			}
		}
	}

	return(crc);
}

long script_CrcModbus16(CTScriptSingleVM *pXvm)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	int nLen = pTemplate->m_vecCRC.size();

	return crc_modbus(pTemplate->m_vecCRC,nLen, 0xFFFF);
}

long script_CrcModbus1600(CTScriptSingleVM *pXvm)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;
	int nLen = pTemplate->m_vecCRC.size();

	return crc_modbus(pTemplate->m_vecCRC,nLen, 0);
}


long script_XOrVector(CTScriptSingleVM *pXvm)
{
	CPpTemplate* pTemplate = script_GetPpTemplate(pXvm);
	int nLen = pTemplate->m_vecCRC.size();
	
	BYTE b1 = 0;
	BYTE bn = 0;
	long nRet = 0;

	if(nLen >= 1)
	{
		nRet = b1 = pTemplate->m_vecCRC[0];
	}

	for(int i=1;i<nLen;++i)
	{
		bn = pTemplate->m_vecCRC[i];
		nRet = nRet ^ bn;
	}

	return nRet;

}

long script_PostConnectFinishedMsg(CTScriptSingleVM *pXvm, long bConnectFinished)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnCallSystem/*L"函数Connect调用:系统错误(没有关联的设备数据模型)"*/);
		return  0;
	}

	// #ifndef _PP_DEV_MODE_
	CPpEngineBaseApp *pApp = g_pTheEngineApp;
	CPpEngineThreadBase *pEngineThread = pApp->FindEngineThread(pTemplate);
	pEngineThread->OnDeviceConnectFinish(bConnectFinished);
	return 0;
}



//数据集操作函数
char g_pszEngineDsPath[MAX_PATH];

void script_CombineDsPathStr(const char *pszValue)
{
	strcat(g_pszEngineDsPath, pszValue);
	strcat(g_pszEngineDsPath, "$");
}

void script_CombineDsPathL(long nValue)
{
	char pszValue[20];
	sprintf(pszValue, "%d", nValue);
	strcat(g_pszEngineDsPath, pszValue);
	strcat(g_pszEngineDsPath, "$");
}

void script_ClearDsPath()
{
	g_pszEngineDsPath[0] = 0;
}

char* script_GetDsPath()
{
	long nLen = strlen(g_pszEngineDsPath);

	if (nLen > 0)
	{
		if (g_pszEngineDsPath[nLen - 1] == '$')
		{
			g_pszEngineDsPath[nLen - 1] = 0;
		}
	}

	return g_pszEngineDsPath;
}


CDvmData* script_FindDvmDataByIndex(CDvmLogicDevice *pLDevice, long nIndex)
{
	POS pos = pLDevice->GetHeadPosition();
	CDvmData *pFind = NULL;
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pLDevice->GetNext(pos);
		pFind = pDataset->FindByIndex(nIndex);

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

CDvmData* script_FindDvmDataByIndex(CExBaseList *pDevice, long nIndex)
{
	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmData *pFind = NULL;

	if (pDevice->GetClassID() == DVMCLASSID_CDVMDEVICE)
	{
		POS pos = pDevice->GetHeadPosition();
		CDvmLogicDevice *pLDevice = NULL;

		while (pos != NULL)
		{
			pLDevice = (CDvmLogicDevice *)pLDevice->GetNext(pos);
			pFind = script_FindDvmDataByIndex(pLDevice, nIndex);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}


CDvmData* script_GetDsData_IndexPath(CExBaseList *pDevice, const char* pszPath)
{
	long nLdIndex, nDsIndex, nDataIndex;

#if 0
	CBufferBase oBuffer;
	oBuffer.InitBuffer(pszPath);
	oBuffer.FormatBuffer('$', 0);

	char *pStr = oBuffer.GetString();
	if (pStr == NULL)
		return NULL;
	nLdIndex = atol(pStr);

	oBuffer.NextString();
	pStr = oBuffer.GetString();
	if (pStr == NULL)
		return NULL;
	nDsIndex = atol(pStr);

	oBuffer.NextString();
	pStr = oBuffer.GetString();
	if (pStr == NULL)
		return NULL;
	nDataIndex = atol(pStr);
#else
	const char *pTemp = pszPath;
	nLdIndex = atol(pTemp);
	pTemp = strchr(pszPath, '$');

	if (pTemp == NULL)
		return NULL;

	pTemp++;
	nDsIndex = atol(pTemp);
	pTemp = strchr(pTemp, '$');

	if (pTemp == NULL)
		return NULL;

	pTemp++;
	nDataIndex = atol(pTemp);

#endif
	CDvmLogicDevice *pLdevice = ((CDvmDevice*)pDevice)->FindByIndex(nLdIndex);
	if (pLdevice == NULL)
		return NULL;

	CDvmDataset *pDataset = pLdevice->FindByIndex(nDsIndex);
	if (pDataset == NULL)
		return NULL;

	CDvmData *pData = pDataset->FindByIndex(nDataIndex);

	return pData;
}



CDvmData* script_GetDsData(CExBaseList *pDevice, CPpTemplate *pTemplate, const char* pszPath)
{
	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmData *pFind = NULL;
	CString strPath;
	strPath = pszPath;

	//绝对全路径
	if (strchr(pszPath, '$') > 0)
	{
		if ('0' <= pszPath[0] && pszPath[0] <= '9')
		{
			pFind = script_GetDsData_IndexPath(pDevice, pszPath);
		}
		else
		{
			pFind = (CDvmData*)pDevice->SelectData(strPath);
		}

		if (pFind != NULL)
		{
			if (pFind->GetClassID() != DVMCLASSID_CDVMDATA)
			{
				pFind = NULL;
			}
		}
	}
	else
	{//单一索引编号
		long nIndex = 0;

		if ('0' <= pszPath[0] && pszPath[0] <= '9')
		{
			nIndex = atol(pszPath);
		}
		else
		{
			nIndex = script_GetGlobal(pTemplate, pszPath);
		}

		pFind = script_FindDvmDataByIndex(pDevice, nIndex);
	}

	return pFind;
}

CDvmData* script_GetDsData(CTScriptSingleVM *pXvm, const char* pszPath)
{
	if (pszPath[0] == '\0')
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorPath/*_T("系统错误(路径为空)")*/ );
		return NULL;
	}

	CExBaseList *pDevice =script_GetDvmDevice(pXvm);
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);
	return script_GetDsData(pDevice, pTemplate, pszPath);
}
// 
// 
// CDvmDataset* script_GetDsDataset(const char* pszPath)
// {
// 	if (pszPath[0] == '\0')
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("系统错误(路径为空)") );
// 		return NULL;
// 	}
// 
// 	CExBaseList *pDevice =script_GetDvmDevice(pXvm);;
// 
// 	if (pDevice == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CDvmDataset *pFind = NULL;
// 	CString strPath;
// 	strPath = pszPath;
// 
// 	//绝对全路径
// 	if (strchr(pszPath, '$') > 0)
// 	{
// 		pFind = (CDvmDataset*)pDevice->SelectData(strPath);
// 
// 		if (pFind != NULL)
// 		{
// 			if (pFind->GetClassID() != DVMCLASSID_CDVMDATASET)
// 			{
// 				pFind = NULL;
// 			}
// 		}
// 	}
// 
// 	if (pFind == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("系统错误(路径【%s】对应的设备数据集不存在)"), strPath );
// 	}
// 
// 	return pFind;
// }

CDvmLogicDevice* script_GetLogicDevice(CTScriptSingleVM *pXvm, const char* pszPath)
{
	if (pszPath[0] == '\0')
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorPath/*_T("系统错误(路径为空)")*/);
		return NULL;
	}

	CExBaseList *pDevice = script_GetDvmDevice(pXvm);;

	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmLogicDevice *pFind = NULL;
	CString strPath;
	strPath = pszPath;

	//绝对全路径
	if (strchr(pszPath, '$') >= 0)
	{
		pFind = (CDvmLogicDevice*)pDevice->SelectData(strPath);

		if (pFind != NULL)
		{
			if (pFind->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
			{
				pFind = NULL;
			}
		}
	}

	if (pFind == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
           , g_sLangTxt_SystemErrorData7.GetString()/*_T("系统错误(路径【%s】对应的逻辑设备不存在)")*/
           , strPath.GetString());
	}

	return pFind;
}

CDvmDevice* script_GetDevice(CTScriptSingleVM *pXvm, const char* pszPath)
{
	if (pszPath[0] == '\0')
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorPath/*_T("系统错误(路径为空)")*/);
		return NULL;
	}

	CExBaseList *pDevice = script_GetDvmDevice(pXvm);;

	if (pDevice == NULL)
	{
		return NULL;
	}

	CDvmDevice *pFind = NULL;
	CString strPath;
	strPath = pszPath;

	if (pDevice->GetClassID() == DVMCLASSID_CDVMDEVICE)
	{
		pFind = (CDvmDevice*)pDevice;
	}
	else if(pDevice->GetClassID() == DVMCLASSID_CDVMDEVICES)
	{
		pFind = (CDvmDevice*)pDevice->SelectData(strPath);

		if (pFind != NULL)
		{
			if (pFind->GetClassID() != DVMCLASSID_CDVMDEVICE)
			{
				pFind = NULL;
			}
		}
	}

	if (pFind == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
               , g_sLangTxt_SystemErrorData6.GetString()/*_T("系统错误(路径【%s】对应的设备不存在)")*/
               , strPath.GetString());
	}

	return pFind;
}

long script_InsertDsData(CTScriptSingleVM *pXvm, const char* pszPath,long nTableRowIndex, long nItemIndex)
{
	CDvmDataset *pDvmDataset = script_GetDsDataset(pXvm, pszPath);

	return script_InsertDsData(pDvmDataset, nTableRowIndex, nItemIndex);
}

long script_InsertDataset(CTScriptSingleVM *pXvm, const char* pszPath, long nTableRowIndex, long nItemIndex)
{
	CDvmLogicDevice *pDvmLogicDevice = script_GetLogicDevice(pXvm, pszPath);

	return script_InsertDataset(pDvmLogicDevice, nTableRowIndex, nItemIndex);
}

long script_InsertLogicDevice(CTScriptSingleVM *pXvm, const char* pszPath, long nTableRowIndex, long nItemIndex)
{
	CDvmDevice *pDvmDevice = script_GetDevice(pXvm, pszPath);

	return script_InsertLogicDevice(pDvmDevice, nTableRowIndex, nItemIndex);
}

long script_InsertDevice(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszDeviceName)
{
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (pTemplate == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorData5/*_T("系统错误(没有关联的设备数据模型)")*/);
		return FALSE;
	}

	if (!pTemplate->IsMultiDeviceMode())
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorData4/*_T("系统错误(不是多设备数据模型)")*/);
		return FALSE;
	}

	CDvmDevices *pDevices = (CDvmDevices*)(pTemplate->GetDevice());

	if (pDevices == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_SystemErrorData5/*_T("系统错误(没有关联的设备数据模型)")*/);
		return NULL;
	}

	CDvmDevice *pDevice = pDevices->FindByIndex(nDeviceIndex);
	
	if (NULL == pDevice)
	{
		pDevice = pDevices->AddNewDevice();
	}

	CString strDeviceIndex;
	strDeviceIndex.Format(_T("%ld"), nDeviceIndex);
	pDevice->m_strID = strDeviceIndex;
	pDevice->m_strName = pszDeviceName;

	script_InsertToTreeCtrl(pDevice, pDevices);

	return TRUE;
}


long script_InsertDsDataEx(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszName, long nItemIndex)
{
	CDvmDataset *pDvmDataset = script_GetDsDataset(pXvm, pszPath);

	return script_InsertDsDataEx(pDvmDataset, pszName, nItemIndex);
}

long script_InsertDatasetEx(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszName, long nItemIndex)
{
	CDvmLogicDevice *pDvmLogicDevice = script_GetLogicDevice(pXvm, pszPath);

	return script_InsertDatasetEx(pDvmLogicDevice, pszName, nItemIndex);
}

long script_InsertLogicDeviceEx(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszName, long nItemIndex)
{
	CDvmDevice *pDvmDevice = script_GetDevice(pXvm, pszPath);

	return script_InsertLogicDeviceEx(pDvmDevice, pszName, nItemIndex);
}


void script_SetDsDataValue(CDvmData *pDvmData, const CString &strAttrID, const CString &strValue)
{
	if (g_bLogBindQueryErrorInfor)
	{
		if (!pDvmData->HasValueID(strAttrID))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                     , g_sLangTxt_SystemErrorData3.GetString()/*_T("系统错误(数据【%s】没有属性【%s】)")*/
                     ,pDvmData->m_strName.GetString(), strAttrID.GetString());
		}
	}

	pDvmData->SetAttr(strAttrID, strValue);

// 	char *pszReturn = pXvm->GetChReurn();
// 	CBaseObject *pScript = PPS_GetPpScript(pXvm);;
// 	CPpEngineData *pEngineData = (CPpEngineData*)pScript->GetAncestor(PPCLASSID_PPENGINEDATA);

	//$$ 20160414
	//if ( pEngineData->m_pPpRecordMngr->CanRecordPackage() )
	//{
	//	CPpParsePackage *pParsePkg = NULL;

	//	pParsePkg = (CPpParsePackage*)pScript->GetAncestor(PPCLASSID_PPPARSEPACKGE);

	//	if (pParsePkg != NULL)
	//	{
	//		CPpPackageDetail *pDetail = (CPpPackageDetail*)pParsePkg->m_pPackageDetailRef;

	//		if (pDetail != NULL)
	//		{
	//			pDetail->AddDvmValue(pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strValue);
	//		}
	//	}
	//}
}

void script_SetDatasetValue(CDvmDataset *pDvmDataset, const CString &strAttrID, const CString &strValue)
{
	if (g_bLogBindQueryErrorInfor)
	{
		if (!pDvmDataset->HasValueID(strAttrID))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                     , g_sLangTxt_SystemErrorData2.GetString()/*_T("系统错误(数据集【%s】没有属性【%s】)")*/
                     , pDvmDataset->m_strName.GetString(), strAttrID.GetString());
			return;
		}
	}

	pDvmDataset->SetAttr(strAttrID, strValue);
}

void script_SetLogicDeviceValue(CDvmLogicDevice *pDvmLogicDevice, const CString &strAttrID, const CString &strValue)
{
	if (g_bLogBindQueryErrorInfor)
	{
		if (!pDvmLogicDevice->HasValueID(strAttrID))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                     , g_sLangTxt_SystemErrorData.GetString()/*_T("系统错误(逻辑设备【%s】没有属性【%s】)")*/
                     , pDvmLogicDevice->m_strName.GetString(), strAttrID.GetString());
			return;
		}
	}

	pDvmLogicDevice->SetAttr(strAttrID, strValue);
}

void script_SetBindDatasetStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char* pszValue)
{
	CString strVal(pszValue);

	CDvmDataset *pDataset = (CDvmDataset*)PPS_GetBindDeviceNodeData(pXvm, pszAttrID);
	CString strAttrID(pszAttrID);

	script_SetDatasetValue(pDataset, strAttrID, strVal);
}

void script_SetBindLogicDeviceStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char* pszValue)
{
	CString strVal(pszValue);

	CDvmLogicDevice *pLogicDevice = (CDvmLogicDevice*)PPS_GetBindDeviceNodeData(pXvm, pszAttrID);
	CString strAttrID(pszAttrID);

	script_SetLogicDeviceValue(pLogicDevice, strAttrID, strVal);
}

void script_SetDsDataL(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, long nValue)
{
	CDvmData *pDvmData = script_GetDsData(pXvm, pszPath);

	if (pDvmData != NULL)
	{
		CString strValue;
		strValue.Format(_T("%d"), nValue);
		CString strAttrID;
		strAttrID = pszAttrID;

		script_SetDsDataValue(pDvmData, strAttrID, strValue);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SetDsDataL(%s:%s=%s)"), CString(pszPath), strAttrID, strValue);
	}
	else
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_SystemErrorData8.GetString()/*_T("系统错误(路径【%s】对应的数据不存在)")*/
                , pszPath );
		}
	}
}

void script_SetDsDataD(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, double dValue)
{
	CDvmData *pDvmData = script_GetDsData(pXvm, pszPath);

	if (pDvmData == NULL)
	{
		return;
	}

	CString strAttrID;
	CString strValue;
	strAttrID = pszAttrID;
	strValue.Format(_T("%f"), dValue);

	if (pDvmData->m_strFormat.GetLength() < 3)
	{
		script_SetDsDataValue(pDvmData, strAttrID, strValue);
		return;
	}
	
	CPpDevBaseApp* pApp = g_thePpDevBaseApp;
	char *pszReturn = pXvm->GetChReurn();
	CDvmDevice *pDevice = (CDvmDevice*)pDvmData->GetAncestor(DVMCLASSID_CDVMDEVICE);

	if (pDevice->IsFormatUseMode_Expr())
	{
		pApp->CalExpression(strValue, pDvmData->m_strFormat, pDevice->m_pDeviceAttr);
	}

	script_SetDsDataValue(pDvmData, strAttrID, strValue);
}

void script_SetDsDataDEx(CTScriptSingleVM *pXvm, long nDvIndex, const char* pszPath, const char *pszAttrID, double dValue)
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CPpEngineDataMngrCntr *pMngr = pApp->GetPpEngineDataMngrCntr();
	CPpEngineData *pEngineData = (CPpEngineData*)pMngr->GetAtIndex(nDvIndex);

	if (pEngineData == NULL)
	{
		return;
	}

	CExBaseList *pDevice = pEngineData->m_pTemplate->GetDevice();
	CDvmData *pDvmData = script_GetDsData(pDevice, pEngineData->m_pTemplate, pszPath);

	if (pDvmData != NULL)
	{
		CString strValue;
		strValue.Format(_T("%f"), dValue);
		CString strAttrID;
		strAttrID = pszAttrID;

		script_SetDsDataValue(pDvmData, strAttrID, strValue);
	}
}

void script_SetDsDataDBatch(CTScriptSingleVM *pXvm, const char* pszDatasetID, const char* pszDataID, const char *pszAttrID, double dValue)
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CPpEngineDataMngrCntr *pMngr = pApp->GetPpEngineDataMngrCntr();

	CString strDatasetID;
	strDatasetID = pszDatasetID;
	CDvmData oData;
	oData.m_strName = pszDataID;
	oData.m_strID = oData.m_strName;

#ifdef _DVM_VALUE_USE_CHAR_
	swprintf(oData.m_strValue,  L"%f", dValue);
#else
	oData.m_strValue.Format(_T("%f"), dValue);
#endif

	pMngr->BatchEditData(&oData, strDatasetID);
}

void script_SetDsDataStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue)
{
	CDvmData *pDvmData = script_GetDsData(pXvm, pszPath);

	if (pDvmData != NULL)
	{
		CString strValue;
		strValue = pszValue;
		CString strAttrID;
		strAttrID = pszAttrID;

		script_SetDsDataValue(pDvmData, strAttrID, strValue);
	}
}

void script_SetDatasetStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue)
{
	CDvmDataset *pDvmDataset = script_GetDsDataset(pXvm, pszPath);

	if (pDvmDataset != NULL)
	{
		CString strValue;
		strValue = pszValue;
		CString strAttrID;
		strAttrID = pszAttrID;

		script_SetDatasetValue(pDvmDataset, strAttrID, strValue);
	}
}

void script_SetLogicDeviceStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue)
{
	CDvmLogicDevice *pDvmLogicDevice = script_GetLogicDevice(pXvm, pszPath);

	if (pDvmLogicDevice != NULL)
	{
		CString strValue;
		strValue = pszValue;
		CString strAttrID;
		strAttrID = pszAttrID;

		script_SetLogicDeviceValue(pDvmLogicDevice, strAttrID, strValue);
	}
}

BOOL script_GetDsDataValue(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, CString &strValue)
{
	CDvmData *pDvmData = script_GetDsData(pXvm, pszPath);

	if (pDvmData != NULL)
	{
		CString strAttrID;
		strAttrID = pszAttrID;

		if (g_bLogBindQueryErrorInfor)
		{
			if (!pDvmData->HasValueID(strAttrID))
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                         , g_sLangTxt_SystemErrorData3.GetString()/*_T("系统错误(数据【%s】没有属性【%s】)")*/
                         , pszPath , strAttrID.GetString());
			}
		}

		return pDvmData->GetValueByID(strAttrID, strValue);
	}
	else
	{
		return FALSE;
	}
}

long script_GetSequenceDsDatas(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue, const char* pszBeginIndexVar, const char* pszEndIndexVar, long nMaxCount)
{
	CDvmDataset *pDataset = script_GetDsDataset(pXvm, pszPath);

	if (pDataset == NULL)
	{
		return 0;
	}

	long nBeginIndex = script_GetGlobal(pXvm, pszBeginIndexVar);
	long nEndIndex = 0;
	CString strAttrID, strValue;
	strAttrID = pszAttrID;
	strValue = pszValue;
	long nCount = 0;
	CDvmData *pData = NULL;

	POS pos = pDataset->FindIndex(nBeginIndex);

	if (pos == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Path{%s} BeginIndex{%s}=%d Error....", pszPath, pszBeginIndexVar, nBeginIndex);
		return 0;
	}

	long nIndex = nBeginIndex;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);

		if (pData->GetValueByID(strAttrID) == strValue)
		{
			if (nCount == 0)
			{
				nBeginIndex = nIndex;
			}

			nCount++;

			if (nCount > nMaxCount)
			{
				nEndIndex = nIndex;
				break;
			}
		}
		else
		{
			if (nCount > 1)
			{
				nEndIndex = nIndex;
				break;
			}
			else
			{
				nCount = 0;
				nBeginIndex = nIndex;
			}
		}

		nIndex++;
	}

	if (nCount > 1)
	{
		if (nEndIndex <= 1)
		{
			nEndIndex = pDataset->GetCount() - 1;
		}

		script_SetGlobal(pXvm, pszBeginIndexVar, nBeginIndex);
		script_SetGlobal(pXvm, pszEndIndexVar, nEndIndex);
	}

	return nCount;
}

long script_CountDsData(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, const char* pszValue)
{
	CDvmDataset *pDataset = script_GetDsDataset(pXvm, pszPath);

	if (pDataset == NULL)
	{
		return 0;
	}

	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strAttrID, strValue;
	strAttrID = pszAttrID;
	strValue = pszValue;
	long nCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);

		if (pData->GetValueByID(strAttrID) == strValue)
		{
			nCount++;
		}
	}

	return nCount;
}

long script_CountDsDataEx(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszExprs)
{
	CDvmDataset *pDataset = script_GetDsDataset(pXvm, pszPath);

	if (pDataset == NULL)
	{
		return 0;
	}
	
	CEquationBuffer oBuffer;
	oBuffer.InitBuffer(pszExprs, pszExprs + strlen(pszExprs));
	CEquationKey *pKey = NULL;
	POS posKey = oBuffer.GetHeadPosition();

	if (posKey == NULL)
	{
		return 0;
	}

	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strAttrID, strValue;
	long nCount = 0;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);

		posKey = oBuffer.GetHeadPosition();
		bTrue = TRUE;

		while (posKey != NULL)
		{
			pKey = (CEquationKey *)oBuffer.GetNext(posKey);

			if (pData->GetValueByID(pKey->GetKeyName()) != pKey->GetKeyValue())
			{
				bTrue = FALSE;
				break;
			}
		}
		
		if (bTrue)
		{
			nCount++;
		}
	}

	return nCount;
}

long script_GetDsDataL(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID)
{
	CString strValue("0");

	script_GetDsDataValue(pXvm, pszPath, pszAttrID, strValue);

#ifdef _UNICODE
	return _wtol(strValue);
#else
    return atol(strValue.GetString());
#endif
}

double script_GetDsDataD(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID)
{
	CString strValue("0");

	script_GetDsDataValue(pXvm, pszPath, pszAttrID, strValue);

#ifdef _UNICODE
	return _wtof(strValue);
#else
    return atof(strValue.GetString());
#endif
}

double script_GetDsDataDEx(CTScriptSingleVM *pXvm, long nDvIndex, const char* pszPath, const char *pszAttrID)
{
	CString strValue("0");
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CPpEngineDataMngrCntr *pMngr = pApp->GetPpEngineDataMngrCntr();
	CPpEngineData* pEngineData = (CPpEngineData*)pMngr->GetAtIndex(nDvIndex);

	if (pEngineData == NULL)
	{
		return 0;
	}

	CExBaseList *pDevice = pEngineData->m_pTemplate->GetDevice();
	CDvmData *pDvmData = script_GetDsData(pDevice, pEngineData->m_pTemplate, pszPath);

	CString strAttrID;
	strAttrID = pszAttrID;

	if (pDvmData != NULL)
	{
		pDvmData->GetValueByID(strAttrID, strValue) ;
	}

#ifdef _UNICODE
	return _wtof(strValue);
#else
    return atof(strValue.GetString());
#endif
}

char* script_GetDsDataStr(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID)
{
	CString strValue;

	script_GetDsDataValue(pXvm, pszPath, pszAttrID, strValue);
	char *pszReturn = pXvm->GetChReurn();
	
	CString_to_char(strValue, pszReturn);
	return pszReturn;
}

double script_SumDsDataD(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszAttrID, long nBeginDvIndex, long nEndDvIndex)
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CPpEngineDataMngrCntr *pMngr = pApp->GetPpEngineDataMngrCntr();
	POS posBegin = NULL, posEnd = NULL;
	
	if (nBeginDvIndex <= 0)
	{
		posBegin = pMngr->GetHeadPosition();
	}
	else
	{
		posBegin = pMngr->FindIndex(nBeginDvIndex);
	}

	if (nEndDvIndex < 0)
	{
		posEnd = pMngr->GetTailPosition();
	}
	else
	{
		posEnd = pMngr->FindIndex(nEndDvIndex);
	}

	if (posBegin == NULL || posEnd == NULL)
	{
		return 0;
	}

	POS pos = posBegin;
	CPpEngineData *pEngineData = NULL;
	CExBaseList *pDevice = NULL;
	CDvmData *pDvmData = NULL;
	CString strValue;
	CString strAttrID;
	strAttrID = pszAttrID;
	double dSum = 0;
	long nIndex=0;
	long nCount = nEndDvIndex - nBeginDvIndex + 1;

	while (TRUE)
	{
		if (pos == NULL)
		{
			break;
		}

		pEngineData = (CPpEngineData *)pMngr->GetNext(pos);

		if (nIndex >= nCount)
		{
			break;
		}

		pDevice = pEngineData->m_pTemplate->GetDevice();
		pDvmData = script_GetDsData(pDevice, pEngineData->m_pTemplate, pszPath);

		if (pDvmData != NULL)
		{
			if (pDvmData->GetValueByID(strAttrID, strValue))
			{
#ifdef _UNICODE
				dSum += _wtof(strValue);
#else
                dSum += atof(strValue.GetString());
#endif
			}
		}

		nIndex++;
	}

	return dSum;
}

void script_AdDsDataList(CTScriptSingleVM *pXvm, const char* pszPath, const char *pszListID)
{
	CDvmData *pDvNodeData = script_GetDsData(pXvm, pszPath);

	if (pDvNodeData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnDataErrorDsData/*L"函数AdDsDataList调用:数据绑定错误"*/);
		}

		return;
	}

	if (pDvNodeData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnDataErrorDsData/*L"函数AdDsDataList调用:数据绑定错误"*/);
		}

		return;
	}

	CString strListID(pszListID);

	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);

#ifndef _PP_DEV_MODE_
	CPpTemplate *pTemplate = script_GetPpTemplate(pXvm);;

	if (!pTemplate->IsDvmDataCanAddToReport(pDvNodeData))
	{//如果没有注册报告，则不能添加

		if (g_bLogEngineDebugInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                , g_sLangTxt_FctnCallNoReport.GetString()/*_T("函数AdDsDataList调用:【%s】数据集没有启动报告")*/
                , ((CExBaseList*)pDvNodeData->GetParent())->m_strID.GetString());
		}

		return;
	}
#endif

	CDvmDataset *pNode = script_GetReportDataset(pXvm, strListID);

	if (pNode != NULL)
	{
		CDvmData *pNewNodeData = pNode->AddNewData(pDvNodeData);//pNode->CreateData(pDvNodeData);
		CDvmDataset *pDs = (CDvmDataset *)pDvNodeData->GetParent();
		CDvmLogicDevice *pLd = (CDvmLogicDevice *)pDs->GetParent();
		//pNewNodeData->m_strFormat.Format(_T("%s$%s"), pLd->m_strID, pDs->m_strID);
		pNewNodeData->m_strFormat = pLd->m_strID;

		CString strTime;
		SYSTEMTIME tm;
		::GetLocalTime(&tm);
		strTime.Format(_T("%d-%d-%d %d:%d:%d"), tm.wYear, tm.wMonth
			, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
		pNewNodeData->SetAttr(_T("tmlocal"), strTime);

		Pp_PostDeviceBindListMsg((WPARAM)pNode, (LPARAM)pNewNodeData);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_FctnCallPoint.GetString()/*L"函数AdDsDataList调用:节点\"%s\" 不存在"*/
                 , strListID.GetString());
	}
}

void script_AdDsPkgDetail(CTScriptSingleVM *pXvm, const char* pszPath)
{
	CPpPackageDetail *pDetail = PPS_GetPackageDetail(pXvm);

#ifndef _PP_DEV_MODE_
	if (pDetail == NULL && g_bLogBindQueryErrorInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnDataErrorDsPkg/*L"函数AdDsPkgDetail调用:数据绑定错误"*/);
		return;
	}
#endif
	
	CDvmData *pDvNodeData = script_GetDsData(pXvm, pszPath);

	if (pDvNodeData == NULL)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnDataErrorDsPkg/*L"函数AdDsPkgDetail调用:数据绑定错误"*/);
		}

		return;
	}

	if (pDvNodeData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		if (g_bLogBindQueryErrorInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnDataErrorDsPkg/*L"函数AdDsPkgDetail调用:数据绑定错误"*/);
		}

		return;
	}

	if (pDetail == NULL)
	{
#ifdef UNICODE
		pDetail->AddDvmValue(pDvNodeData->m_strName, pDvNodeData->m_strID, pDvNodeData->m_strValue);
#else
		pDetail->AddDvmValue(pDvNodeData->m_strName, pDvNodeData->m_strID, CString(pDvNodeData->m_strValue) );
#endif
	}
}

void script_AdValPkgDetail(CTScriptSingleVM *pXvm, const char* pszName, const char *pszID, const char *pszValue)
{
	CPpPackageDetail *pDetail = PPS_GetPackageDetail(pXvm);

#ifndef _PP_DEV_MODE_
	if (pDetail == NULL && g_bLogBindQueryErrorInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, g_sLangTxt_FctnDataErrorVal/*L"函数AdValPkgDetail调用:数据绑定错误"*/);
		return;
	}
#endif

	if (pDetail != NULL)
	{
		CString strName, strID, strValue;
		strName = pszName;
		strID   = pszID;
		strValue = pszValue;
		pDetail->AddDvmValue(strName, strID, strValue);
	}
}



//字节1 基数F（16 位无符号整数）低
//字节2 基数F（16 位无符号整数）高
//字节3 符号S 26 指数E(7位二进制补码,bit6 符号位) 20
//浮点数的数值计算公式如下：数值＝(-1)S x pow(2,E-16) x F

/*
nValue1 = GetBbValLong(0,2)
nValue2 = GetBbValLong(2,1)
S1 = GetBitInLong16(nValue2,7) --符号位
S2 = GetBitInLong16(nValue2,6) --符号位
nValue3 = LAnd(0x7F,nValue2) --7位二进制数
if S2==1 then
	E =(128-nValue3)*(-1)  --，符号位为1参与运算求补码
else
	E = nValue3 --符号位为0，补码为原码
end
nValue = (-1)^S1*2^(E-16)*nValue1
SetBindDataD("value",nValue)  
nItem = GetValue("nItemIndex")
nItem = nItem + 1
SetValueLong("nItemIndex",nItem)
*/
float script_SF_GetANA24Float(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	
	if(pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (3 > nLength)
	{
		return 0;
	}

	BYTE byteV1 = pByteBlock->m_pBuffer[nIndex];
	BYTE byteV2 = pByteBlock->m_pBuffer[nIndex+1];
	BYTE byteS  = pByteBlock->m_pBuffer[nIndex+2];
	double fValue = 0;
	long nValue = byteV1 + byteV2 * 256;
	
	BYTE byteFlag1 = byteS & 0x80;
	BYTE byteFlag2 = byteS & 0x40;
	long byteE = byteS & 0X7F;

	if (byteFlag2 > 0)
	{
		//符号位为1参与运算求补码
		byteE =(128-byteE)*(-1);
	}

	long dE =byteE  - 16;
	fValue = pow(2.0, dE) * nValue;

	if (byteFlag1 > 0)
	{
		fValue = -fValue;
	}

	return (float)fValue;
}

float script_SF_GetANA32Float(CTScriptSingleVM *pXvm, long nIndex)
{
	return 0;
}


float script_SF_GetBcd24Float(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (3+nIndex > nLength)
	{
		return 0;
	}

	BYTE byteV1 = pByteBlock->m_pBuffer[nIndex];
	BYTE byteV2 = pByteBlock->m_pBuffer[nIndex+1];
	BYTE byteV3  = pByteBlock->m_pBuffer[nIndex+2];
	BYTE byteS = byteV1 & 0x40;
	BYTE byteW =( byteV1 & 0x30) >> 4;

	BYTE byteB1 = byteV1 & 0x0F;
	BYTE byteB2 = (byteV2 >> 4) & 0x0F;
	BYTE byteB3 = byteV2 & 0x0F;
	BYTE byteB4 = (byteV3 >> 4) & 0x0F;
	BYTE byteB5 = byteV3 & 0x0F;

	double dValue = byteB5 + byteB4 * 10 + byteB3 * 100 + byteB2 * 1000 + byteB1 * 10000;
	dValue /= pow(10.0, byteW);

	return (float)dValue;
}


WORD sf_HexBcd(WORD h)
{
	WORD b,t;
	if(h>9999)return 0x9999;
	t=h;
	b=t/1000*0x1000,t%=1000;
	b+=t/100*0x100,t%=100;
	b+=t/10*0x10+t%10;
	return b;
}

bool sf_Float2Set( float fData, BYTE *pByteBuf )
{
	BYTE dotbit=0;
	DWORD dTemp;
	WORD wTemp;

	if( fData<0 )
	{
		fData=-fData;
		dotbit=0x80;
	}

	if( fData>9999.5 ) 
		fData = 9999.5;

	if( fData>=999.95 )
	{
		dTemp=(DWORD)(fData+0.5);
	}
	else if( fData>=99.995 )
	{
		dotbit|=0x10;
		dTemp=(DWORD)((fData+0.05)*10);
	}
	else if( fData>=9.9995 )
	{
		dotbit|=0x20;
		dTemp=(DWORD)((fData+0.005)*100);
	}
	else
	{
		dotbit|=0x30;
		dTemp=(DWORD)((fData+0.0005)*1000);
	}

	dotbit |= 0x80;
	pByteBuf[0]= dotbit;

	wTemp=sf_HexBcd( (WORD)dTemp );

	pByteBuf[2]= (BYTE)wTemp;
	pByteBuf[1]= (BYTE)(wTemp>>8);

	return true;
}


bool sf_Float2SetEx( float fData, BYTE *pByteBuf )
{
	BYTE dotbit=0;
	DWORD dTemp;

	if( fData<0 )
	{
		fData=-fData;
		dotbit=0x80;
	}

	if( fData<=99.9995 )
	{
		dotbit|=0x30;
		dTemp=(DWORD)((fData+0.00005)*1000);
	}
	else if( fData<=999.995 )
	{
		dotbit|=0x20;
		dTemp=(DWORD)((fData+0.0005)*100);
	}
	else  if( fData<=9999.95 )
	{
		dotbit|=0x10;
		dTemp=(DWORD)((fData+0.005)*10);
	}
	else  if( fData<=99999.5 )
	{
		dotbit|=0x00;
		dTemp=(DWORD)fData;
	}
	else
	{
		dotbit|=0x00;
		dTemp=99999;
	}

	dotbit |= 0x80;
	pByteBuf[0]= dotbit;

	pByteBuf[2] = dTemp % 10;
	dTemp /= 10;
	pByteBuf[2] |=( dTemp % 10) << 4;
	dTemp /= 10;

	pByteBuf[1] = dTemp % 10;
	dTemp /= 10;
	pByteBuf[1] |=( dTemp % 10) << 4;
	dTemp /= 10;
	pByteBuf[0] |= dTemp % 10;

	return true;
}

void script_SF_SetBcd24Float(CTScriptSingleVM *pXvm, float fValue, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return ;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return ;
	}

	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex < 0)
	{
		nIndex = 0;
	}

	if (3+nIndex > nLength)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_FctnCallLength.GetString()/*L"函数SetBcd24Float调用:缓冲区长度(%d)不够"*/, nLength);
		return ;
	}

	BYTE *byteBuffer = pByteBlock->m_pBuffer + nIndex;
	byteBuffer[0]=byteBuffer[1]=byteBuffer[2]=0;
	sf_Float2Set(fValue, byteBuffer);
}

void script_SF_SetBcd24FloatEx(CTScriptSingleVM *pXvm, float fValue, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if(pByteBlock == NULL)
	{
		return ;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return ;
	}

	long nReturn = 0;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex < 0)
	{
		nIndex = 0;
	}

	if (3+nIndex > nLength)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("函数SetBcd24Float调用:缓冲区长度(%d)不够"), nLength);
		return ;
	}

	BYTE *byteBuffer = pByteBlock->m_pBuffer + nIndex;
	byteBuffer[0]=byteBuffer[1]=byteBuffer[2]=0;
	sf_Float2SetEx(fValue, byteBuffer);
}


//发送报文、接收报文的时间间隔函数
long script_GetSendIdle(CTScriptSingleVM *pXvm)
{
	char *pszReturn = pXvm->GetChReurn();
	CBaseObject *pScript = PPS_GetPpScript(pXvm);;
	CPpEngineData *pEngineData = (CPpEngineData*)pScript->GetAncestor(PPCLASSID_PPENGINEDATA);

	if (pEngineData == NULL)
	{
		return 0;
	}

	return pEngineData->GetSendTickLong();
}


long script_GetRcvIdle(CTScriptSingleVM *pXvm)
{
	char *pszReturn = pXvm->GetChReurn();
	CBaseObject *pScript = PPS_GetPpScript(pXvm);;
	CPpEngineData *pEngineData = (CPpEngineData*)pScript->GetAncestor(PPCLASSID_PPENGINEDATA);

	if (pEngineData == NULL)
	{
		return 0;
	}

	return pEngineData->GetRecvTickLong();
}
//lili-wang  2017-11-21 字符串查找函数
long script_StrFind(const char *pszVariableID, const char *pszVariableID0)
{
	if (pszVariableID == NULL)
	{
		return 0;
	}
	CString str(pszVariableID); 
	CString str0(pszVariableID0);
	int n = str.Find(str0);
	
	if (n>=0)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
	
	
}
