// RtVariables.cpp: implementation of the CRtVariables class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtVariables.h"
#include "../MR1200BaseApp.h"
#include "../../API/MathApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strWriteRecordData_VariableID;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// const char *CRtVariables::g_pszKeyVariables			= "variables";
// const char *CRtVariables::g_pszKeyRefVariable		= "ref-variable";

CRtVariables::CRtVariables()
{
	m_nDataLenStartuptoFirstData = 0;
	m_nStartupPos   = 0;
	m_nFirstDataPos = 0;
	m_strName = "RtVariables";
	m_strID = m_strName;
	m_pAttrTimeBuffer = NULL;
#ifdef _CAL_USE_REF_VARIABLE_
	m_nXFrequencyCalBeginPos = 0xFFFFFFFF;                         //频率计算的起始位置 ,0
	m_nXAttrCalBeginPos      = 0xFFFFFFFF;                 //属性计算的起始位置
	m_nXRefBufLen			= 0;
	m_nXRefBufFillBeginPos	= 0;
	m_nXRefBufDataLen		= 0;
#endif

	m_pRefVariable = NULL;
	g_nRecordStartup = 0;

	m_n64AttrReadBeginPos	= 0;
	m_dwReadBeginPos		= 0;
	m_dwReadEndPos			= 0;
	m_dwTimeReadBeginPos	= 0;
	m_dwTimeReadEndPos		= 0;
	m_pUSourceVariable		= NULL;
	m_pISourceVariable		= NULL;
	m_pUdcSourceVariable	= NULL;
	m_pIdcSourceVariable	= NULL;
	m_pBSourceVariable		= NULL;

	m_pRefBuffer		    = NULL;
	memset(m_pdwAttrCalPosition, 0, MAX_FREQ_ZERO_POS_BUFFER * sizeof(DWORD));

	memset(m_paVariables, 0, MAX_RTVARIABLES * sizeof(DWORD));

	for (long nIndex = 0; nIndex < AUTO_MULTI_CH_NAME_COUNT; nIndex++)
	{
		//m_pszAutoMultiChsName[nIndex] = NULL;
		m_pszAutoMultiChsName[nIndex] = new char[CH_NAME_MAX_WIDTH];
		memset(m_pszAutoMultiChsName[nIndex],0, CH_NAME_MAX_WIDTH * sizeof(char));
	}

	m_pClone = NULL;
	m_bRefVariableChanged = FALSE;
	m_pRtMemBufferMngr = NULL;
}

void CRtVariables::ResetCalPos()
{
	m_nDataLenStartuptoFirstData = 0;
	m_nStartupPos			= 0;
	m_nFirstDataPos			= 0;
#ifdef _CAL_USE_REF_VARIABLE_
	m_nXFrequencyCalBeginPos = 0xFFFFFFFF;                         //频率计算的起始位置
	m_nXAttrCalBeginPos      = 0xFFFFFFFF;                 //属性计算的起始位置
#endif
	g_nRecordStartup = 0;

	m_n64AttrReadBeginPos	= 0;
	m_dwReadBeginPos		= 0;
	m_dwReadEndPos			= 0;
	m_dwTimeReadBeginPos	= 0;
	m_dwTimeReadEndPos		= 0;

#ifdef _CAL_USE_REF_VARIABLE_
	m_nXRefBufLen			= 0;
	m_nXRefBufFillBeginPos	= 0;
	m_nXRefBufDataLen		= 0;
#endif
}

CRtVariables::~CRtVariables()
{	
	if (m_pUSourceVariable != NULL)
	{
		delete m_pUSourceVariable;
		m_pUSourceVariable		= NULL;
	}
	
	if (m_pISourceVariable != NULL)
	{
		delete m_pISourceVariable;
		m_pISourceVariable		= NULL;
	}
	
	if (m_pUdcSourceVariable != NULL)
	{
		delete m_pUdcSourceVariable;
		m_pUdcSourceVariable		= NULL;
	}
	
	if (m_pIdcSourceVariable != NULL)
	{
		delete m_pIdcSourceVariable;
		m_pIdcSourceVariable		= NULL;
	}

	if (m_pBSourceVariable != NULL)
	{
		delete m_pBSourceVariable;
		m_pBSourceVariable		= NULL;
	}

#ifdef _CAL_USE_REF_VARIABLE_
	m_nXRefBufLen			= 0;
	m_nXRefBufFillBeginPos	= 0;
	m_nXRefBufDataLen		= 0;
#endif
	m_pRefBuffer		    = NULL;

	m_listAnalogAttrs.RemoveAll();
	m_listBinaryInstAttrs.RemoveAll();
	m_listAnalogInstAttrs.RemoveAll();

	m_oListAnologVariable.RemoveAll();
	m_oListBinaryVariable.RemoveAll();
	m_oListACVariable_U.RemoveAll();
	m_oListACVariable_I.RemoveAll();


	for (long nIndex = 0; nIndex < AUTO_MULTI_CH_NAME_COUNT; nIndex++)
	{
		if (m_pszAutoMultiChsName[nIndex] != NULL)
		{
			delete []m_pszAutoMultiChsName[nIndex];
			m_pszAutoMultiChsName[nIndex] = NULL;
		}
	}

	m_pClone = NULL;
}

CRtSingleVariable* CRtVariables::FindVariable(const CString &strID)
{
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	CRtSingleVariable *pSingle = NULL;
	CString strCmbID;

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);

		if (pVariable->GetClassID() != RTCLASSID_SINGLEVARIABLE)
		{
			continue;
		}

		pSingle = (CRtSingleVariable *)pVariable;
		strCmbID = pSingle->CmbVariableID();

		if (strCmbID == strID)
		{
			return pSingle;
		}
	}

	return NULL;
}

CRtVariable* CRtVariables::FindByRefRecordData(CExBaseObject *pRefRecordData)
{
	CRtVariable *pVariable = NULL;
	CRtVariable *pFind = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);

		if (pVariable->m_pRefRecordData == pRefRecordData)
		{
			pFind = pVariable;
			break;
		}
	}

	return pFind;
}

long CRtVariables::GetCountByPhaseID(const CString &strPhaseID, const CString &strType)
{
	long nCount = 0;
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	CRtSingleVariable *pSingle = NULL;

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		
		if (pVariable->GetClassID() == RTCLASSID_SINGLEVARIABLE)
		{
			pSingle = (CRtSingleVariable *)pVariable;

			if (pSingle->m_strUnit.Find(strType) < 0)
			{
				continue;
			}

			if (pSingle->m_strPhaseID.Find(strPhaseID) >= 0)
			{
				nCount++;
			}
		}
	}

	return nCount;
}

void CRtVariables::ResetUseAndSpy()
{
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		pVariable->ResetUseAndSpy();
	}

	m_pClone = NULL;
}

//重载的方法
UINT CRtVariables::GetClassID()
{
	return RTCLASSID_VARIABLES;
}
// 
// long CRtVariables::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	if (!xml_GetAttibuteValue(g_pszKeyRefVariable, oNode, m_strRefVariable))
// 	{
// 		debug_trace("\nGet AttibuteValue-RefVariable of CRtVariables failed!\n");
// 	}
// 	return 0;
// }
// 
// CExBaseObject* CRtVariables::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CRtVariable *pVariableTemp = NULL;
// 	
// 	if (strcmp(CRtMultiVariable::g_pszKeyMultiVariable, pszClassID) ==0) 
// 	{
// 		pVariableTemp  = new CRtMultiVariable();
// 	}
// 	else if(strcmp(CRtBinaryVariable::g_pszKeyBinaryVariable, pszClassID) == 0)
// 	{
// 		pVariableTemp  = new CRtBinaryVariable();
// 	}
// 	else if(strcmp(CRtComplexVariable::g_pszKeyComplexVariable, pszClassID) == 0)
// 	{
// 		pVariableTemp  = new CRtComplexVariable();
// 	}
// 	else if(strcmp(CRtSingleVariable::g_pszKeySingleVariable, pszClassID) == 0)
// 	{
// 		pVariableTemp  = new CRtSingleVariable();
// 	}
// 	else
// 	{
// 		debug_trace("\nCRtVariables Create NewChild failed!\n");
// 	}
// 	
// 	return pVariableTemp;
// }
// 
// const char* CRtVariables::GetXmlElementKey()
// {
// 	return g_pszKeyVariables;
// }
// 
// long CRtVariables::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	if (m_strRefVariable.GetLength() > 0)
// 	{
// 		oElement->setAttribute(_bstr_t(g_pszKeyRefVariable), _bstr_t(m_strRefVariable));
// 	}
// 	return 0;
// }

CRtVariable* CRtVariables::FindByIDForRdSets(const CString& strID, const CString& strTanModel)
{
	CRtVariable *pVariable =  NULL;
	CRtVariable *pFind =  NULL;

	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		ASSERT(pVariable != NULL);

		if (strID == pVariable->m_strID )
		{
			if (pVariable->IsRtBinaryVariable() || pVariable->IsRtComplexVariable() || pVariable->IsRtMultiVariable())
			{
				if (pVariable->m_bReadSets == FALSE)
				{
					pFind = pVariable;
					break;
				}			
			}
			else if(pVariable->IsRtSingleVariable())
			{
				if ((pVariable->m_strTranModel == strTanModel) && (pVariable->m_bReadSets == FALSE))
				{
					pFind = pVariable;
					break;
				}			
			}
			else
			{
			}
		}
	}

	return pFind;
}
// 
// //试验相关的方法
// BOOL CRtVariables::ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes)
// {
// 	int nCount = oNodes->Getlength();
// 	MSXML::IXMLDOMNodePtr oNode = NULL;	
// 	CString strVaribleID, strTanModel;
// 	CRtVariable *pVarible = NULL;
// 	CRecordTest *pRecordTest = (CRecordTest *)GetParent();
// 	ASSERT(pRecordTest != NULL);
// 
// 	for(int nIndex = 0; nIndex < nCount; nIndex++)
// 	{
// 		oNode = oNodes->Getitem(nIndex);
// 		xml_GetAttibuteValue(CRtVariable::g_pszKeyID, oNode, strVaribleID);	
// 		
// 		if (pRecordTest->IsRecordTestAutofit())
// 		{
// 			strTanModel = "";
// 			xml_GetAttibuteValue(CRtVariable::g_pszKeyTranModel, oNode, strTanModel);	
// 
// 			pVarible = (CRtVariable *)FindByIDForRdSets(strVaribleID, strTanModel);
// 		}
// 		else
// 		{
// 			pVarible = (CRtVariable *)FindByID(strVaribleID);
// 		}
// 
// 		if (pVarible != NULL)
// 		{
// 			pVarible->ReadSetsValueXml(oNode);
// 
// 			if (pRecordTest->IsRecordTestAutofit())
// 			{
// 				//pVarible->m_bReadSets = TRUE;
// 			}
// 		}
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CRtVariables::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oVariables;
// 	oVariables = oXMLDoc->createElement(_bstr_t(g_pszKeyVariables));
// 
// 	CRtVariable *pVariable = NULL;
// 	POS pos  = GetHeadPosition();
// 	
// 	while (pos != NULL)
// 	{
// 		pVariable = (CRtVariable *)GetNext(pos);
// 
// 		if (pVariable != NULL)
// 		{
// 			pVariable->WriteSetsValueXml(oXMLDoc, oVariables);
// 		}
// 		
// 	}
// 	
// 	oParent->appendChild(oVariables);
// 
// 	return TRUE;
// }


//ok
long GetLenFromCurrPosToFillPos(long nCurrPos, long nDataFillPos, long nDataLen, long nBufferLen)
{
	long nLen = 0;

	if (nDataLen == nBufferLen)
	{
		if (nDataFillPos >= nCurrPos)
		{
			nLen = nDataFillPos - nCurrPos;
		}
		else
		{
			nLen = nDataFillPos + nBufferLen - nCurrPos - 1;
		}
	}
	else
	{
		nLen = nDataFillPos - nCurrPos;
	}

	return nLen;
}

BOOL CRtVariables::GetFrequencyCalPos2(PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len,long nBegin)
{
	//ASSERT (FALSE);   //2021-3-9  lijunqing
#ifdef _CAL_USE_REF_VARIABLE_
	nCalBuffer1Pos = -1;
	nCalBuffer2Pos = -1;
	nCalBuffer1Len = -1;
	nCalBuffer2Len = -1;

	if (m_nXRefBufDataLen < pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN) //nDataLen
	{
		return FALSE;
	}
		
	if (m_nXRefBufDataLen == m_nXRefBufLen)
	{
		if (nBegin < (long)m_nXRefBufFillBeginPos)//计算的起点在缓存新的数据段
		{
			if (nBegin + pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN < (long)m_nXRefBufFillBeginPos)
			{
				nCalBuffer1Pos = nBegin;
				nCalBuffer1Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;
			} 
			else
			{
			//	nCalBuffer1Pos = nBegin;
			//	nCalBuffer1Len = m_nRefBufFillBeginPos - nBegin;
				return FALSE; // 数据不够计算，返回
			}
		} 
		else//计算的起点在缓存旧的数据段
		{
			nCalBuffer1Pos = nBegin;

			long nEnd = nBegin + pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;

			if (nEnd > (long)m_nXRefBufLen)
			{
				nCalBuffer1Len = m_nXRefBufLen - nBegin;
				nCalBuffer2Pos = 0;
				nCalBuffer2Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN - nCalBuffer1Len;
			} 
			else
			{
				nCalBuffer1Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;
			}
		}
	} 
	else
	{
		if (nBegin + pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN < (long)m_nXRefBufFillBeginPos)
		{
			nCalBuffer1Pos = nBegin;
			nCalBuffer1Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;
		} 
		else
		{
		//	nCalBuffer1Pos = nBegin;
		//	nCalBuffer1Len = m_nRefBufFillBeginPos - nBegin;
			return FALSE; // 数据不够计算，返回
		}
	}

	if (nCalBuffer2Len > pCalLenPara->USE_RT_FILTER_BUFFER_LEN)
	{
		nCalBuffer2Len -= pCalLenPara->USE_RT_FILTER_BUFFER_LEN;
	}
	else
	{
		if (nCalBuffer2Pos < 0)
		{
			nCalBuffer1Len -= pCalLenPara->USE_RT_FILTER_BUFFER_LEN;
		}
		else
		{
			nCalBuffer2Pos = -1;
			nCalBuffer1Len = nCalBuffer1Len - (pCalLenPara->USE_RT_FILTER_BUFFER_LEN - nCalBuffer2Len );
			nCalBuffer2Len = 0;
		}
	}

#endif
	return TRUE;
}

//ok
BOOL GetFrequencyCalPos(PRECORD_CAL_LEN_PARA pCalLenPara
						, long nFrequencyCalBeginPos, long nRefBufFillBeginPos, long nRefBufLen, long nRefBufDataLen
						, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len, BOOL bCalUseRecordBuffer)
{
	//计算缓冲区的位置和长度
	nCalBuffer1Pos = -1;
	nCalBuffer2Pos = -1;
	nCalBuffer1Len = -1;
	nCalBuffer2Len = -1;

	if (nRefBufDataLen < pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN) //nDataLen
	{
		return FALSE;
	}

	long nLenCal = 0;

	if (nRefBufLen == nRefBufDataLen)//nDataLen == nBufferLen
	{
		nLenCal = GetLenFromCurrPosToFillPos(nFrequencyCalBeginPos, nRefBufFillBeginPos
			, nRefBufDataLen, nRefBufLen);

		if (nLenCal < pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN)
		{//如果从开始位置算起，不够长度，则返回
			return FALSE;
		}

		//下一次计算，从本次计算开始位置开始计算
		nCalBuffer1Pos = nFrequencyCalBeginPos;

		if (nRefBufFillBeginPos > nFrequencyCalBeginPos) //nFillBeginPos
		{//填充位置大于从上一次的计算位置，表示数据只有一段
			nCalBuffer1Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;
		}
		else
		{
			if (nFrequencyCalBeginPos+pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN < nRefBufLen)//nBufferLen
			{//从当前位置到缓冲区末尾足够计算长度
				nCalBuffer1Pos = nFrequencyCalBeginPos;
				nCalBuffer1Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;
			}
			else
			{
				//填充位置小于从上一次的计算位置，表示数据只有二段
				//第一段从本次计算开始位置到缓冲区末尾
				//				nCalBuffer1Len = nBufferLen - nCalBuffer1Pos; 
				nCalBuffer1Len = nRefBufLen - nCalBuffer1Pos; 
				//第二段从缓冲区开头开始
				nCalBuffer2Pos = 0;
				nCalBuffer2Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN - nCalBuffer1Len;
			}
		}
	}
	else
	{
		if (nFrequencyCalBeginPos == 0xFFFFFFFF)
		{//第一次计算，从第0点数据开始计算
			nCalBuffer1Pos = 0;//nFillBeginPos - RTATTRIBUTECAL_MIN_BUFFER_LEN;
			nCalBuffer1Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;  //lijq 2010.5.15
			//nCalBuffer1Len = m_nRefBufFillBeginPos; //nFillBeginPos
		}
		else
		{//下一次计算，从本次计算开始位置开始计算
			nLenCal = GetLenFromCurrPosToFillPos(nFrequencyCalBeginPos, nRefBufFillBeginPos
				, nRefBufDataLen, nRefBufLen);

			if (nLenCal < pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN)
			{//如果从开始位置算起，不够长度，则返回
				return FALSE;
			}

			nCalBuffer1Pos = nFrequencyCalBeginPos;//nFillBeginPos - RTATTRIBUTECAL_MIN_BUFFER_LEN;
			nCalBuffer1Len = pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;
		}
	}

	if (nCalBuffer2Len > pCalLenPara->USE_RT_FILTER_BUFFER_LEN)
	{
		nCalBuffer2Len -= pCalLenPara->USE_RT_FILTER_BUFFER_LEN;
	}
	else
	{
		if (nCalBuffer2Pos < 0)
		{
			nCalBuffer1Len -= pCalLenPara->USE_RT_FILTER_BUFFER_LEN;
		}
		else
		{
			nCalBuffer2Pos = -1;
			nCalBuffer1Len = nCalBuffer1Len - (pCalLenPara->USE_RT_FILTER_BUFFER_LEN - nCalBuffer2Len );
			nCalBuffer2Len = 0;
		}
	}

	return TRUE;
}

//ok
BOOL GetFrequencyCalPos(CRtVariable *pRtVariable, PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len, BOOL bCalUseRecordBuffer)
{
	ASSERT (pRtVariable != NULL);
	//计算缓冲区的位置和长度
	nCalBuffer1Pos = -1;
	nCalBuffer2Pos = -1;
	nCalBuffer1Len = -1;
	nCalBuffer2Len = -1;

	if (bCalUseRecordBuffer)
	{
		if (!pRtVariable->HasChannelBuffer())
		{
			return FALSE;
		}
	}

	return  GetFrequencyCalPos(pCalLenPara
		, pRtVariable->m_nFrequencyCalBeginPos, pRtVariable->m_nRefBufFillBeginPos, pRtVariable->m_nRefBufLen, pRtVariable->m_nRefBufDataLen
		, nCalBuffer1Pos, nCalBuffer1Len , nCalBuffer2Pos,nCalBuffer2Len, bCalUseRecordBuffer);
}

BOOL GetAttrCalPos(long nBeginPos, long nEndPos, long nBufferDataLen
								 , long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len)
{
	nCalBuffer1Pos = -1;
	nCalBuffer2Pos = -1;
	nCalBuffer1Len = -1;
	nCalBuffer2Len = -1;

	if (nEndPos > nBeginPos)
	{
		nCalBuffer1Pos = nBeginPos;

		//第一个过零点到第二个过零点之前的一个点
		nCalBuffer1Len = nEndPos - nBeginPos;// - 1;
	}
	else
	{
		//第一个过零点到缓冲区末尾
		nCalBuffer1Pos = nBeginPos;
		nCalBuffer1Len = nBufferDataLen - nBeginPos;

		//缓冲区开头到第二个过零点
		nCalBuffer2Pos = 0;
		nCalBuffer2Len = nEndPos;// - 1;
	}

	return TRUE;
}

BOOL GetAttrCalPos(long nBeginPos, long nEndPos, long nBufferLen, long nDataLen
								 , long nDataFillBeginPos, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos)
{
	GetAttrCalPos(nBeginPos, nEndPos, nDataLen
		, pRtAttrCalBufPos->nBuffer1Pos, pRtAttrCalBufPos->nBuffer1Len
		, pRtAttrCalBufPos->nBuffer2Pos, pRtAttrCalBufPos->nBuffer2Len);

	//fdp add 2010.5.12
	pRtAttrCalBufPos->nDftBuffer1Pos = pRtAttrCalBufPos->nBuffer1Pos;
	pRtAttrCalBufPos->nDftBuffer1Len = pRtAttrCalBufPos->nBuffer1Len;
	pRtAttrCalBufPos->nDftBuffer2Pos = pRtAttrCalBufPos->nBuffer2Pos;
	pRtAttrCalBufPos->nDftBuffer2Len = pRtAttrCalBufPos->nBuffer2Len;

	pRtAttrCalBufPos->nDataLength = nDataLen;
	pRtAttrCalBufPos->nBufferLength = nBufferLen;
	
	return TRUE;
}

BOOL CRtVariables::AttrCalPosInFrequencyCalRage(DWORD dwAttrCalBeginPos, DWORD dwAttrCalPoints)
{
#ifdef _CAL_USE_REF_VARIABLE_
	PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);
	DWORD *pdwRefFreqZeroPositionEnd = NULL;
	UINT nCount = *pCalPara->pnRefFreqZeroPosCount - 1;

	DWORD dwRefBegin = m_nXFrequencyCalBeginPos;//*(pCalPara->pdwRefFreqZeroPosition);
	DWORD dwRefEnd   = *(pCalPara->pdwRefFreqZeroPosition+nCount);

	if (dwRefEnd < dwRefBegin)
	{
		dwRefEnd += m_nXRefBufLen; //nBufferLen
	}
	
	//刚开始的时候，两者相等
	if (dwAttrCalBeginPos < dwRefBegin)
	{
		dwAttrCalBeginPos += m_nXRefBufLen; //nBufferLen
	}

	if (dwRefBegin <= dwAttrCalBeginPos && dwAttrCalBeginPos + dwAttrCalPoints < dwRefEnd)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
#endif
	return FALSE;
}


BOOL CRtVariables::AttrCalPosInFrequencyCalRage2(DWORD dwAttrCalBegin, DWORD dwAttrCalEnd)
{
#ifdef _CAL_USE_REF_VARIABLE_
	PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);
	DWORD *pdwRefFreqZeroPositionEnd = NULL;
	UINT nCount = *pCalPara->pnRefFreqZeroPosCount - 1;
	
	DWORD dwRefBegin = m_nXFrequencyCalBeginPos;//*(pCalPara->pdwRefFreqZeroPosition);
	DWORD dwRefEnd   = *(pCalPara->pdwRefFreqZeroPosition + nCount);
	DWORD dwAttrCalBeginPos = m_nXAttrCalBeginPos;

	if (dwRefEnd < dwRefBegin)
	{
		dwRefEnd += m_nXRefBufLen; //nBufferLen
	}
	
	if (dwAttrCalBeginPos < dwRefBegin)
	{
		dwAttrCalBeginPos += m_nXRefBufLen;//nBufferLen
	}
	
	//刚开始的时候，两者相等
	if (dwAttrCalBegin < dwRefBegin)
	{
		dwAttrCalBegin += m_nXRefBufLen; //nBufferLen
	}

	if (dwAttrCalEnd < dwAttrCalBegin)
	{
		dwAttrCalEnd += m_nXRefBufLen; //nBufferLen
	}
	
	if ( (dwAttrCalBeginPos <= dwAttrCalBegin)
		&& (dwRefBegin <= dwAttrCalBegin && dwAttrCalBegin < dwRefEnd)
		&& (dwRefBegin < dwAttrCalEnd && dwAttrCalEnd <= dwRefEnd) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
#endif
	return FALSE;
}

/*
 *	计算的总入口
 *  频率计算：至少保证有RTATTRIBUTECAL_MIN_BUFFER_LEN长度个点，所以刚开始录波时直到满足
 *  RTATTRIBUTECAL_MIN_BUFFER_LEN长度点时才开始计算，以后依次往后推
 *  
 *  属性数据计算，必须保证频率计算成功才能计算，计算的方法是根据频率来计算每个周勃的点数
 *  每周波计算一次属性数据。
 */
void CRtVariables::CalValuesRealTime(PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	if (m_bRefVariableChanged)
	{
		InitDataAttributeCalFunc(TRUE);
		m_bRefVariableChanged = FALSE;
	}

	//g_bCalUseRecordBuffer = TRUE;
	ASSERT (m_pRefVariable != NULL);

	if (m_pRefVariable == NULL || m_pRefVariable->m_pChannelBuffer == NULL)
	{
		return;
	}
	
#ifdef _USE_RECORD_BUFFER_TO_CAL
	m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
#else
	m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetSpyMemBuffer();
#endif
	
	m_nXRefBufLen			= m_pRefBuffer->GetBufferLength();
	m_nXRefBufFillBeginPos	= m_pRefBuffer->GetDataFillBeginPosition();
	m_nXRefBufDataLen		= m_pRefBuffer->GetDataLength();

lbl_CalValues:
	long nCalBuffer1Pos = -1;
	long nCalBuffer2Pos = -1;
	long nCalBuffer1Len = -1;
	long nCalBuffer2Len = -1;
	long nDataLen = 0;
	long nStartup = 0;
	g_bAddDataToBuffer = TRUE;

	//ok
	if (!GetFrequencyCalPos(m_pRefVariable, pCalLenPara, nCalBuffer1Pos, nCalBuffer1Len, nCalBuffer2Pos, nCalBuffer2Len, TRUE))
	{//获取计算长度失败，表示数据长度不够
		return;
	}
	
	//缓冲区参数
	RTATTRIBUTECALBUFFERPOS oRtAttrCalBufPos;
	memset(&oRtAttrCalBufPos, 0, sizeof(RTATTRIBUTECALBUFFERPOS));
	oRtAttrCalBufPos.nBuffer1Pos = nCalBuffer1Pos;
	oRtAttrCalBufPos.nBuffer1Len = nCalBuffer1Len;
	oRtAttrCalBufPos.nBuffer2Pos = nCalBuffer2Pos;
	oRtAttrCalBufPos.nBuffer2Len = nCalBuffer2Len;
	oRtAttrCalBufPos.nBufferLength = m_nXRefBufLen;
	oRtAttrCalBufPos.nDataLength = m_nXRefBufDataLen;

	//计算频率
	CalFrequncy(&oRtAttrCalBufPos, TRUE);

	//保存频率计算位置：获取参考通道的频率属性计算参数
	PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);

	if (pCalPara == NULL)
	{
		return;
	}
		
	//用于计算属性值的点数，以及频率计算的偏移量
	DWORD dwCalUsePoints = 0;
	
	DWORD dwAttrCalCount = 0;

	dwAttrCalCount   = GetAttrCalPosition2(m_pdwAttrCalPosition , pCalPara); // fdp add 2010.4.15
	
	long nZeroCount = *(pCalPara->pnFreqZeroPosCount);

	DWORD *pIndexBegin = m_pdwAttrCalPosition;
	DWORD *pIndexEnd = m_pdwAttrCalPosition + dwAttrCalCount;//  -1;
	
	long nStartOld = g_nRecordStartup;

	while (pIndexBegin < pIndexEnd)
	{
		GetAttrCalPos(*pIndexBegin, *(pIndexBegin+1), m_nXRefBufLen, m_nXRefBufDataLen, m_nXRefBufFillBeginPos, &oRtAttrCalBufPos);

#ifdef _USE_RECORD_BUFFER_TO_CAL
		m_pRtMemBufferMngr->m_n64CurrCalIndex = m_pRtMemBufferMngr->m_n64RecordHeadIndex + *pIndexBegin;
#else
		m_pRtMemBufferMngr->m_n64CurrCalIndex = m_pRtMemBufferMngr->m_n64SpyHeadIndex + *pIndexBegin;
#endif

		//计算静态属性数据
		CalStaticValues(&oRtAttrCalBufPos, (pIndexBegin != m_pdwAttrCalPosition), TRUE);

		//计算其他属性数据
		CalOtherValues(&oRtAttrCalBufPos, TRUE);
		AddTimeValue(oRtAttrCalBufPos);
	
		//判断启动
		JudgeStartupAnalog(nStartup);

		if (g_nRecordStartup == 0)
		{
			g_nRecordStartup = nStartup;

			if (g_nRecordStartup != nStartOld)
			{
				m_nStartupPos = *pIndexBegin;
			}
		}

		if (g_nRecordStartup == 0)
		{
			JudgeStartupAnalogInst(&oRtAttrCalBufPos, g_nRecordStartup);
		}

		if (g_nRecordStartup == 0)
		{
			JudgeStartupBinaryInst(&oRtAttrCalBufPos, g_nRecordStartup);
		}

		if (nStartOld != g_nRecordStartup)
		{
			CalBeginPosByStartupPos(m_nStartupPos, nSampleGap, dwSampleRate);
			
#ifdef _USE_HD_DEVICE
			g_theRecordApp.m_pHDMrDevice->TurnOnRecordLight();
#endif
		}

		if (bCalPointByPoint)
		{
			pIndexBegin++;
		}
		else
		{
			pIndexBegin +=  pCalLenPara->RTATTRIBUTECAL_MIN_BUFFER_LEN;
		}
	}

	m_nXAttrCalBeginPos = *pIndexEnd;

	if (GetFrequencyCalPos(m_pRefVariable, pCalLenPara, nCalBuffer1Pos, nCalBuffer1Len, nCalBuffer2Pos, nCalBuffer2Len, TRUE))
	{//获取计算长度失败，表示数据长度不够
		goto lbl_CalValues;
	}	
#endif
}

double CRtVariables::CalAngleOffset(long nRefPos, long nCurrPos, long nBuffLen, long nSampleRate)
{
	long nOffset = 0;
	long nLen, nLenCycle;

	if (nCurrPos == nRefPos)
	{
		return 0;
	}
	
	if (nRefPos > nCurrPos)
	{
		nLen = nRefPos - nCurrPos;
		nLenCycle = nCurrPos + nBuffLen - nRefPos - 1;

		if (nLen > nLenCycle)
		{
			nOffset = -nLenCycle;
		}
		else
		{
			nOffset = nLen;
		}
	}
	else
	{
		nLen = nCurrPos - nRefPos;
		nLenCycle = nRefPos + nBuffLen - nCurrPos - 1;

		if (nLen > nLenCycle)
		{
			nOffset = nLenCycle;
		}
		else
		{
			nOffset = -nLen;
		}
	}

	double dAngle = 360 * 50;
	dAngle /= nSampleRate;
	dAngle *= nOffset;


	return dAngle;
}

void CalValuesRealTimeEx_Adj_Ang(double dValue, double &dPhase)
{
	if (math_IsEqual(dValue, 0))
	{
		//幅值为0，相位 为 0
		dPhase = 0;
	}
	else
	{
		MakeAngleTo180(dPhase);
	}
}

void CRtVariables::CalValuesRealTimeEx(PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint)
{
	DWORD *pdVariable = m_paVariables;


	long nPrevHdIndex = -1, nCurrHdIndex = 0;
	long nCalBeginPos = 0;
	CRtVariable *pVariable = NULL,*pVariableRef = NULL;
	double dAngleOffset = 0;
	long nBufferLen = 0;
// 	pVariableRef = (CRtVariable*)(m_paVariables[6]);
// 	nCalBeginPos = pVariableRef->m_nFrequencyCalBeginPos;

	while (*pdVariable != 0)
	{
		pVariable = (CRtVariable*)(*pdVariable);
	
		if (!pVariable->CanCal())
		{
			pdVariable++;
			continue;
		}

		nCurrHdIndex = pVariable->Get_HdIndex();

		if (pVariable->m_pRefRtVariable == NULL) //如果不存在参考相,还按原有模式处理
		{
			if (nCurrHdIndex != nPrevHdIndex)
			{
				nCalBeginPos = pVariable->m_nFrequencyCalBeginPos;
				nPrevHdIndex = nCurrHdIndex;
				pVariable->m_dAngleOffset = 0;
			}
			else
			{
				dAngleOffset = CalAngleOffset(nCalBeginPos, pVariable->m_nFrequencyCalBeginPos, pVariable->m_nRefBufLen, pCalLenPara->g_dwSampleRate);
				pVariable->m_dAngleOffset = dAngleOffset;
			}
		}
		else//如果存在参考相,按参考相处理
		{
			if (pVariableRef != pVariable->m_pRefRtVariable)
			{
				pVariableRef = pVariable->m_pRefRtVariable;
				nCalBeginPos = pVariableRef->m_nFrequencyCalBeginPos;
			}

			if (pVariable->m_pRefRtVariable == pVariable)
			{
				nPrevHdIndex = nCurrHdIndex;
				pVariable->m_dAngleOffset = 0;
			}
			else
			{
				dAngleOffset = CalAngleOffset(nCalBeginPos, pVariable->m_nFrequencyCalBeginPos, pVariable->m_nRefBufLen, pCalLenPara->g_dwSampleRate);
				pVariable->m_dAngleOffset = dAngleOffset;
			}
		}

		pdVariable++;
	}

	//初始化位置
	pdVariable = m_paVariables;
	long nRefBufLen = -1, nRefBufFillBeginPos = -1, RefBufDataLen = -1;

	while (*pdVariable != 0)
	{
		pVariable = (CRtVariable*)(*pdVariable);

		if (pVariable->CanCal())
		{
			if (nRefBufLen > 0)
			{
				pVariable->InitCalPos(nRefBufLen, nRefBufFillBeginPos, RefBufDataLen);
			}
			else
			{
				pVariable->InitCalPos();
				nRefBufLen =pVariable->m_nRefBufLen;
				nRefBufFillBeginPos = pVariable->m_nRefBufFillBeginPos;
				RefBufDataLen = pVariable->m_nRefBufDataLen;
			}
		}

		pdVariable++;
	}

	pdVariable = m_paVariables;
	while (*pdVariable != 0)
	{
		((CRtVariable*)(*pdVariable))->m_oPrevValue =( (CRtVariable*)(*pdVariable))->m_oCurrValue;
		CalValuesRealTimeEx((CRtVariable*)(*pdVariable), pCalLenPara, nSampleGap, dwSampleRate, bCalPointByPoint);
		pdVariable++;
	}

	//调整通道角度
	pdVariable = m_paVariables;
	double dAngle = 0;
	double dAngle2 = 0;
	nPrevHdIndex = -1;

	//2022-4-23  lijunqing 缓冲计算结果数据
	PSTTVARIABLESRTVALUES pSttRtVarValues = g_oStttVariablesRtValueBuffer.GetCurrForWrite();
	pSttRtVarValues->nCount=0;
	pVariableRef = NULL;
// 	dAngle = pVariableRef->m_oCurrValue.dFundPhase;
// 	dAngle2 = pVariableRef->m_oCurrValue.dEffecPhase;


	while (*pdVariable != 0)
	{
		pVariable = (CRtVariable*)(*pdVariable);

		if (!pVariable->CanCal())
		{
			pdVariable++;
			continue;
		}

		nCurrHdIndex = pVariable->Get_HdIndex();
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("pVariable->m_oCurrValue.dEffecPhase=%lf(调整前),dAngle=%lf;dAngle2=%lf(nCurrHdIndex=%ld;nPrevHdIndex=%ld).")
// 			,pVariable->m_oCurrValue.dEffecPhase,dAngle,dAngle2,nCurrHdIndex,nPrevHdIndex);

		if (pVariable->m_pRefRtVariable == NULL)//如果不存在参考相,还按原有模式处理
		{
			if (nCurrHdIndex != nPrevHdIndex)
			{
				nPrevHdIndex = nCurrHdIndex;
				dAngle = pVariable->m_oCurrValue.dFundPhase;
				dAngle2 = pVariable->m_oCurrValue.dEffecPhase;
				pVariable->m_oCurrValue.dFundPhase = 0;
				pVariable->m_oCurrValue.dEffecPhase = 0;
			}
			else
			{
				pVariable->m_oCurrValue.dFundPhase -= dAngle;
				pVariable->m_oCurrValue.dEffecPhase -= dAngle2;
			}
		} 
		else//如果存在参考相,按参考相处理
		{
			if (pVariableRef != pVariable->m_pRefRtVariable)
			{
				pVariableRef = pVariable->m_pRefRtVariable;
				dAngle = pVariableRef->m_oCurrValue.dFundPhase;
				dAngle2 = pVariableRef->m_oCurrValue.dEffecPhase;
			}

			if (pVariable->m_pRefRtVariable == pVariable)
			{
				nPrevHdIndex = nCurrHdIndex;
				pVariable->m_oCurrValue.dFundPhase = 0;
				pVariable->m_oCurrValue.dEffecPhase = 0;
			}
			else
			{
				pVariable->m_oCurrValue.dFundPhase -= dAngle;
				pVariable->m_oCurrValue.dEffecPhase -= dAngle2;

				if (nCurrHdIndex == 0)//时间通道相位为0
				{
					pVariable->m_oCurrValue.dFundPhase = 0;
					pVariable->m_oCurrValue.dEffecPhase = 0;
				}
			}
		}

//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("pVariable->m_oCurrValue.dEffecPhase=%lf(调整后)."),pVariable->m_oCurrValue.dEffecPhase);
		CalValuesRealTimeEx_Adj_Ang(pVariable->m_oCurrValue.dFundValue, pVariable->m_oCurrValue.dFundPhase);
		CalValuesRealTimeEx_Adj_Ang(pVariable->m_oCurrValue.dEffecValue, pVariable->m_oCurrValue.dEffecPhase);

		//2022-5-4  lijunqing  总有效值相位暂时等于基波相位
		//pVariable->m_oCurrValue.dEffecPhase = pVariable->m_oCurrValue.dFundPhase;

		if (pSttRtVarValues->nCount < XCYCLE_VARS_COUNT)
		{
			pSttRtVarValues->oRtValues[pSttRtVarValues->nCount] = pVariable->m_oCurrValue;
			pSttRtVarValues->nCount++;
		}

		pdVariable++;
	}

	//最后更新写入的位置，降低起冲突的可能性
	g_oStttVariablesRtValueBuffer.NextForWrite();
}

BOOL GetAttrCalPos(long nBeginPos, long nBufferLen, long nDataLen, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, double dFrequency)
{
// #ifdef not_use_FreqCalFix50Hz//2023.7.14 zhouhj 默认采用固定50Hz方式，修改兼容非50Hz的情况
// 	long nPoints = pRtAttrCalBufPos->dwSampleRate / 50; //dFrequency;  //2020-06028
// 
// 	if (dFrequency>1.0f)
// 	{
// 		nPoints = pRtAttrCalBufPos->dwSampleRate / dFrequency; 
// 	}
// #else
// 	long nPoints = pRtAttrCalBufPos->dwSampleRate / 50; //dFrequency;  //2020-06028
// #endif

	long nPoints = pRtAttrCalBufPos->dwSampleRate / g_dFixFreqCalValue;
	//zhouhj 2024.9.12 去除原not_use_FreqCalFix50Hz宏,该值小于1时,采用实时获取频率的方式
	if (g_dFixFreqCalValue <= 1.0f)
	{
		nPoints = pRtAttrCalBufPos->dwSampleRate / 50; //dFrequency;  //2020-06028

		if (dFrequency>1.0f)
		{
			nPoints = pRtAttrCalBufPos->dwSampleRate / dFrequency; 
		}
	}

	if (nBeginPos + nPoints >= nDataLen)
	{
		pRtAttrCalBufPos->nDftBuffer1Pos = nBeginPos;
		pRtAttrCalBufPos->nDftBuffer1Len = nBeginPos + nPoints - nDataLen - 1;
		pRtAttrCalBufPos->nDftBuffer2Pos = 0;
		pRtAttrCalBufPos->nDftBuffer2Len = nPoints - pRtAttrCalBufPos->nDftBuffer1Len;
	}
	else
	{
		pRtAttrCalBufPos->nDftBuffer1Pos = nBeginPos;
		pRtAttrCalBufPos->nDftBuffer1Len = nPoints;
		pRtAttrCalBufPos->nDftBuffer2Pos = -1;
		pRtAttrCalBufPos->nDftBuffer2Len = 0;
	}

	return TRUE;
}

void CRtVariables::CalValuesRealTimeEx(CRtVariable * pdVariable, PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint)
{
	ASSERT (pdVariable != NULL);

	if (pdVariable == NULL)
	{
		return;
	}

	if (!pdVariable->CanCal())
	{
		return;
	}

	if (g_nEnableCal_Root == 0)
	{//2022-5-3  lijunqing 不计算任何参数数据
		pdVariable->m_nAttrCalBeginPos = pdVariable->m_nRefBufFillBeginPos;
		pdVariable->m_nFrequencyCalBeginPos = pdVariable->m_nRefBufFillBeginPos;
		return;
	}
	
	//2022-4-22  lijunqing
	//计算的同时，缓冲区还在填充，会导致不同的通道数据计算时不对齐
	//pdVariable->InitCalPos();

	long nCalBuffer1Pos = -1;
	long nCalBuffer2Pos = -1;
	long nCalBuffer1Len = -1;
	long nCalBuffer2Len = -1;
	long nDataLen = 0;
	long nStartup = 0;
	g_bAddDataToBuffer = TRUE;

	//ok
	if (!GetFrequencyCalPos(pdVariable, pCalLenPara, nCalBuffer1Pos, nCalBuffer1Len, nCalBuffer2Pos, nCalBuffer2Len, TRUE))
	{//获取计算长度失败，表示数据长度不够
		//pdVariable->ZeroCalValues();
		return;
	}
	
	//缓冲区参数
	RTATTRIBUTECALBUFFERPOS oRtAttrCalBufPos;
	memset(&oRtAttrCalBufPos, 0, sizeof(RTATTRIBUTECALBUFFERPOS));
	oRtAttrCalBufPos.nBuffer1Pos = nCalBuffer1Pos;
	oRtAttrCalBufPos.nBuffer1Len = nCalBuffer1Len;
	oRtAttrCalBufPos.nBuffer2Pos = nCalBuffer2Pos;
	oRtAttrCalBufPos.nBuffer2Len = nCalBuffer2Len;
	oRtAttrCalBufPos.nBufferLength = pdVariable->m_nRefBufLen;
	oRtAttrCalBufPos.nDataLength = pdVariable->m_nRefBufDataLen;
	oRtAttrCalBufPos.nBufFillIndex = pdVariable->m_nRefBufFillBeginPos;

	if (g_strWriteRecordData_VariableID.GetLength() > 0)
	{
		if (pdVariable->m_strID == g_strWriteRecordData_VariableID)
		{
			int i=0;
		}
	}
	//计算频率
	pdVariable->CalFrequncy( &oRtAttrCalBufPos, TRUE);

	//保存频率计算位置：获取参考通道的频率属性计算参数
	PRTATTRIBUTECALFUNCPARA pCalPara = pdVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);

	if (pCalPara == NULL)
	{
		return;
	}
		
	//用于计算属性值的点数，以及频率计算的偏移量
	DWORD dwCalUsePoints = 0;
	DWORD dwAttrCalCount = 0;
	dwAttrCalCount   = GetAttrCalPosition2(pdVariable , pCalPara); // fdp add 2010.4.15
	
	long nZeroCount = *(pCalPara->pnFreqZeroPosCount);

	DWORD *pIndexBegin = pdVariable->m_dwAttrCalPosition;
	DWORD *pIndexEnd = pdVariable->m_dwAttrCalPosition + dwAttrCalCount;//  -1;
	oRtAttrCalBufPos.dwSampleRate = pCalLenPara->g_dwSampleRate;
	long nStartOld = g_nRecordStartup;
	pCalPara->nBufFillIndex = pdVariable->m_nRefBufFillBeginPos;

	//while (pIndexBegin < pIndexEnd)
	{
		GetAttrCalPos(pdVariable->m_nAttrCalBeginPos, pdVariable->m_nRefBufLen, pdVariable->m_nRefBufDataLen, &oRtAttrCalBufPos, pdVariable->m_oCurrValue.dFrequency);

		if (m_pRtMemBufferMngr != NULL)
		{
#ifdef _USE_RECORD_BUFFER_TO_CAL
			m_pRtMemBufferMngr->m_n64CurrCalIndex = m_pRtMemBufferMngr->m_n64RecordHeadIndex + *pIndexBegin;
#else
			m_pRtMemBufferMngr->m_n64CurrCalIndex = m_pRtMemBufferMngr->m_n64SpyHeadIndex + *pIndexBegin;
#endif
		}

		//计算静态属性数据
		pdVariable->CalStaticValues(&oRtAttrCalBufPos, (pIndexBegin != pdVariable->m_dwAttrCalPosition), TRUE);

		//计算其他属性数据
		pdVariable->CalValues(&oRtAttrCalBufPos, TRUE);//CalOtherValues(&oRtAttrCalBufPos, TRUE);

		pIndexBegin++;

		//break;
	}

	//角度偏移修正
	pdVariable->m_oCurrValue.dFundPhase += pdVariable->m_dAngleOffset;
	MakeAngleTo180(pdVariable->m_oCurrValue.dFundPhase);

	if ( pdVariable->m_oCurrValue.dFundPhase > 180 || pdVariable->m_oCurrValue.dFundPhase < -180)
	{
		int i = 0;
	}

	//pdVariable->m_nAttrCalBeginPos = (*pIndexBegin + *pIndexEnd) / 2;
	pdVariable->m_nAttrCalBeginPos = pdVariable->m_nRefBufFillBeginPos;
	pdVariable->m_nFrequencyCalBeginPos = pdVariable->m_nRefBufFillBeginPos;

	if (GetFrequencyCalPos(pdVariable, pCalLenPara, nCalBuffer1Pos, nCalBuffer1Len, nCalBuffer2Pos, nCalBuffer2Len, TRUE))
	{//获取计算长度失败，表示数据长度不够
		//goto lbl_CalValues;
	}	

#ifndef _PSX_IDE_QT_
	if (g_strWriteRecordData_VariableID.GetLength() > 0)
	{
		if (pdVariable->m_strID == g_strWriteRecordData_VariableID)
		{
			CString strFile;
			CString strData;
			CFile file;
			strFile = _P_GetLibraryPath();
			strFile.AppendFormat(_T("%s.txt"), g_strWriteRecordData_VariableID);
			g_strWriteRecordData_VariableID.Empty();
			
			if (!file.Open(strFile, CFile::modeWrite | CFile::modeCreate))
			{
				return;
			}

			CMemBuffer_Long *pLong= (CMemBuffer_Long*)pdVariable->GetChannelBuffer();
			long *pDatas = (long*)pLong->GetBuffer_long();
			long nCount = pLong->GetDataLength();
			long nIndex = 0;

			for (nIndex=0; nIndex<nCount; nIndex++)
			{
				strData.Format(_T("%d\r\n"), *pDatas);
				pDatas++;
				file.Write(strData, strData.GetLength());
			}

			file.Close();
		}
	}
#endif
}

BOOL CRtVariables::ValidateVariableRecordBuffer(BOOL bCalUseRecordBuffer)
{
	POS pos  = GetHeadPosition();
	CRtVariable *pVariable = NULL;
	CMemBufferInterface *pBuffer = NULL;
	BOOL bValid = TRUE;

	while (pos != NULL)
	{
		pVariable = (CRtVariable*)GetNext(pos);
		pBuffer = NULL;

		if (pVariable->IsRtSingleVariable())
		{
			if (bCalUseRecordBuffer)
			{
				pBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
			}
			else
			{
				pBuffer = m_pRefVariable->m_pAttachRecordBuffer;
			}

			if (pBuffer == NULL)
			{
				bValid = FALSE;
				break;
			}
		}
	}

	return bValid;
}


BOOL CRtVariables::CalValues(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate, BOOL bCalUseRecordBuffer, BOOL bCalOtherValues)
{
//lbl_CalValues:
	//ASSERT (FALSE);   //2021-3-9  lijunqing
#ifdef _CAL_USE_REF_VARIABLE_
	if (m_pRefVariable == NULL)
	{
		InitRefVariable();
	}

	long nCalBuffer1Pos = -1;
	long nCalBuffer2Pos = -1;
	long nCalBuffer1Len = -1;
	long nCalBuffer2Len = -1;

	if (bCalUseRecordBuffer)
	{
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
		m_pRefBuffer = m_pRefVariable->m_pAttachRecordBuffer;
	}

	m_nXFrequencyCalBeginPos = nBeginPos;  //从此位置开始计算
	m_nXAttrCalBeginPos = nBeginPos;

	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}
	
	//关联的变量的缓冲区有效性判断，如果有变量的缓冲区为空，则不计算
	if (!ValidateVariableRecordBuffer(bCalUseRecordBuffer))
	{
		return FALSE;
	}

	m_nXRefBufLen			= m_pRefBuffer->GetBufferLength();
	m_nXRefBufFillBeginPos	= m_pRefBuffer->GetDataFillBeginPosition();
	m_nXRefBufDataLen		= m_pRefBuffer->GetDataLength();

	//ok
	if (!GetFrequencyCalPos2(pCalLenPara, nCalBuffer1Pos, nCalBuffer1Len, nCalBuffer2Pos, nCalBuffer2Len,nBeginPos))
	{//获取计算长度失败，表示数据长度不够
		CalInstValue(nBeginPos,bCalUseRecordBuffer);//只计算瞬时值
		return FALSE;
	}
	
	//缓冲区参数
	RTATTRIBUTECALBUFFERPOS oRtAttrCalBufPos;
	memset(&oRtAttrCalBufPos, 0, sizeof(RTATTRIBUTECALBUFFERPOS));
	oRtAttrCalBufPos.nBuffer1Pos = nCalBuffer1Pos;
	oRtAttrCalBufPos.nBuffer1Len = nCalBuffer1Len;
	oRtAttrCalBufPos.nBuffer2Pos = nCalBuffer2Pos;
	oRtAttrCalBufPos.nBuffer2Len = nCalBuffer2Len;

	//fdp add 
	oRtAttrCalBufPos.nBufferLength = m_nXRefBufLen;
	oRtAttrCalBufPos.nDataLength = m_nXRefBufDataLen;

	//////////////////////////////////////////////////////////////////////////
	//计算频率
	CalFrequncy(&oRtAttrCalBufPos, bCalUseRecordBuffer);
	
	//实时显示时是使用过零点计算参数的，事后分析的时候使用定长计算参数
	PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);

	if (pCalPara == NULL)
	{
		return FALSE;
	}

	if (pCalPara->pnFreqZeroPosCount == NULL)
	{
		return FALSE;
	}

	m_nXAttrCalBeginPos = nBeginPos;
	long nZeroCount = *(pCalPara->pnFreqZeroPosCount);
	long nBegin = nBeginPos;
	long nEnd = nBeginPos + pCalLenPara->Analyse_Cal_Length;
	
	if (nZeroCount < 2 || nZeroCount >= MAX_FREQ_ZERO_POS_COUNT)
	{
		if (nEnd >= (long)m_nXRefBufLen)
		{
			nEnd -= (long)m_nXRefBufLen;
		}
	}
	else
	{
		DWORD dwAttrCalUsePoints = rcd_CalCyclePoints(dwSampleRate, *pCalPara->pRefFrequency, g_bCarry_For_AttrCalUsePoints);
		nBegin = m_nXAttrCalBeginPos;
		nEnd = m_nXAttrCalBeginPos + dwAttrCalUsePoints;

		if (nEnd >= (long)m_nXRefBufLen)
		{
			nEnd -= (long)m_nXRefBufLen;
		}
	}
	
	GetAttrCalPos(nBegin, nEnd, m_nXRefBufLen, m_nXRefBufDataLen, m_nXRefBufFillBeginPos, &oRtAttrCalBufPos);

	//计算静态属性数据
	CalStaticValues(&oRtAttrCalBufPos, FALSE, bCalUseRecordBuffer);
	
	//计算其他属性数据
	if (bCalOtherValues)
	{
		CalOtherValues(&oRtAttrCalBufPos, bCalUseRecordBuffer);
	}
#endif

	return TRUE;
}

BOOL CRtVariables::CalValuesFnom(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate, BOOL bCalUseRecordBuffer, BOOL bCalOtherValues)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	ASSERT (m_pRefVariable != NULL);
	long nCalBuffer1Pos = -1;
	long nCalBuffer2Pos = -1;
	long nCalBuffer1Len = -1;
	long nCalBuffer2Len = -1;

	if (bCalUseRecordBuffer)
	{
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
		m_pRefBuffer = m_pRefVariable->m_pAttachRecordBuffer;
	}

	m_nXFrequencyCalBeginPos = nBeginPos;  //从此位置开始计算
	m_nXAttrCalBeginPos = nBeginPos;

	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}
	
	//关联的变量的缓冲区有效性判断，如果有变量的缓冲区为空，则不计算
	if (!ValidateVariableRecordBuffer(bCalUseRecordBuffer))
	{
		return FALSE;
	}

	m_nXRefBufLen			= m_pRefBuffer->GetBufferLength();
	m_nXRefBufFillBeginPos	= m_pRefBuffer->GetDataFillBeginPosition();
	m_nXRefBufDataLen		= m_pRefBuffer->GetDataLength();

	//缓冲区参数
	RTATTRIBUTECALBUFFERPOS oRtAttrCalBufPos;
	memset(&oRtAttrCalBufPos, 0, sizeof(RTATTRIBUTECALBUFFERPOS));
	oRtAttrCalBufPos.nBuffer1Pos = 0;
	oRtAttrCalBufPos.nBuffer1Len = nCalBuffer1Len;
	oRtAttrCalBufPos.nBuffer2Pos = -1;
	oRtAttrCalBufPos.nBuffer2Len = 0;

	//fdp add 
	oRtAttrCalBufPos.nBufferLength = m_nXRefBufLen;
	oRtAttrCalBufPos.nDataLength = m_nXRefBufDataLen;
	
	//实时显示时是使用过零点计算参数的，事后分析的时候使用定长计算参数
	PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);

	if (pCalPara == NULL)
	{
		return FALSE;
	}

	m_nXAttrCalBeginPos = nBeginPos;
	long nZeroCount = *(pCalPara->pnFreqZeroPosCount);
	long nBegin = nBeginPos;
	long nEnd = nBeginPos + pCalLenPara->Analyse_Cal_Length;
	
	//double dAttrCalUsePoints = dwSampleRate / 50.0;//(*pCalPara->pRefFrequency);
	DWORD dwAttrCalUsePoints = rcd_CalCyclePoints(dwSampleRate, 50, g_bCarry_For_AttrCalUsePoints);
	nBegin = m_nXAttrCalBeginPos;
	nEnd = m_nXAttrCalBeginPos + dwAttrCalUsePoints;

	if (nEnd >= m_nXRefBufDataLen)
	{//最后几个点进行计算
		nEnd = m_nXRefBufDataLen - 1;
		nBegin = nEnd - dwAttrCalUsePoints;
		//return FALSE;
	}
	
	GetAttrCalPos(nBegin, nEnd, m_nXRefBufLen, m_nXRefBufDataLen, m_nXRefBufFillBeginPos, &oRtAttrCalBufPos);

	//计算静态属性数据
	CalStaticValues(&oRtAttrCalBufPos, FALSE, bCalUseRecordBuffer);
	
	//计算其他属性数据
	if (bCalOtherValues)
	{
		CalOtherValues(&oRtAttrCalBufPos, bCalUseRecordBuffer);
	}
#endif

	return TRUE;
}

BOOL CRtVariables::CalValuesFnom_Quick(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate, BOOL bCalUseRecordBuffer, BOOL bCalOtherValues)
{
//	ASSERT (FALSE);
//#ifdef _CAL_USE_REF_VARIABLE_
	ASSERT (m_pRefVariable != NULL);
	long nCalBuffer1Pos = -1;
	long nCalBuffer2Pos = -1;
	long nCalBuffer1Len = -1;
	long nCalBuffer2Len = -1;

	if (bCalUseRecordBuffer)
	{
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
		m_pRefBuffer = m_pRefVariable->m_pAttachRecordBuffer;
	}

	//2020-12-19  lijunqing  开放Qucik计算的功能，修改SmartCap的时候屏蔽的
#ifndef _CAL_USE_REF_VARIABLE_
	DWORD m_nXRefBufLen;
	DWORD m_nXRefBufFillBeginPos;
	DWORD m_nXRefBufDataLen;
	DWORD m_nXFrequencyCalBeginPos;          //频率计算的起始位置
	DWORD m_nXAttrCalBeginPos;               //属性计算的起始位置
#endif

	m_nXFrequencyCalBeginPos = nBeginPos;  //从此位置开始计算
	m_nXAttrCalBeginPos = nBeginPos;

	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}
	
	//关联的变量的缓冲区有效性判断，如果有变量的缓冲区为空，则不计算
	if (!ValidateVariableRecordBuffer(bCalUseRecordBuffer))
	{
		return FALSE;
	}

	m_nXRefBufLen			= m_pRefBuffer->GetBufferLength();
	m_nXRefBufFillBeginPos	= m_pRefBuffer->GetDataFillBeginPosition();
	m_nXRefBufDataLen		= m_pRefBuffer->GetDataLength();

	//缓冲区参数
	RTATTRIBUTECALBUFFERPOS oRtAttrCalBufPos;
	memset(&oRtAttrCalBufPos, 0, sizeof(RTATTRIBUTECALBUFFERPOS));
	oRtAttrCalBufPos.nBuffer1Pos = 0;
	oRtAttrCalBufPos.nBuffer1Len = nCalBuffer1Len;
	oRtAttrCalBufPos.nBuffer2Pos = -1;
	oRtAttrCalBufPos.nBuffer2Len = 0;

	//fdp add 
	oRtAttrCalBufPos.nBufferLength = m_nXRefBufLen;
	oRtAttrCalBufPos.nDataLength = m_nXRefBufDataLen;
	
	//实时显示时是使用过零点计算参数的，事后分析的时候使用定长计算参数
	PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);

	if (pCalPara == NULL)
	{
		return FALSE;
	}

	m_nXAttrCalBeginPos = nBeginPos;
	long nZeroCount = *(pCalPara->pnFreqZeroPosCount);
	long nBegin = nBeginPos;
	long nEnd = nBeginPos + pCalLenPara->Analyse_Cal_Length;
	
	DWORD dwAttrCalUsePoints = rcd_CalCyclePoints(dwSampleRate, 50, g_bCarry_For_AttrCalUsePoints);
	nBegin = m_nXAttrCalBeginPos;
	nEnd = m_nXAttrCalBeginPos + dwAttrCalUsePoints;

	if (nEnd >= m_nXRefBufDataLen)
	{//最后几个点进行计算
		nEnd = m_nXRefBufDataLen - 1;
		nBegin = nEnd - dwAttrCalUsePoints;
		//return FALSE;
	}
	
	//计算静态属性数据
	GetAttrCalPos(nBegin, nEnd, m_nXRefBufLen, m_nXRefBufDataLen, m_nXRefBufFillBeginPos, &oRtAttrCalBufPos);
	oRtAttrCalBufPos.dwSampleRate = dwSampleRate;
	CalStaticValues_Quick(&oRtAttrCalBufPos, FALSE, bCalUseRecordBuffer);
	
// 	//计算其他属性数据
// 	if (bCalOtherValues)
// 	{
// 		CalOtherValues(&oRtAttrCalBufPos, bCalUseRecordBuffer);
// 	}
//#endif

	return TRUE;
}

BOOL CRtVariables::CalValues_PeakVellay(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, long nUseLength, DWORD dwSampleRate, BOOL bCalUseRecordBuffer, BOOL bCalOtherValues)
{
	//ASSERT (FALSE);   //2021-3-9  lijunqing
#ifdef _CAL_USE_REF_VARIABLE_
	if (bCalUseRecordBuffer)
	{
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
		m_pRefBuffer = m_pRefVariable->m_pAttachRecordBuffer;
	}

	m_nXRefBufLen			= m_pRefBuffer->GetBufferLength();
	m_nXRefBufFillBeginPos	= m_pRefBuffer->GetDataFillBeginPosition();
	m_nXRefBufDataLen		= m_pRefBuffer->GetDataLength();

	//缓冲区参数
	RTATTRIBUTECALBUFFERPOS oRtAttrCalBufPos;
	memset(&oRtAttrCalBufPos, 0, sizeof(RTATTRIBUTECALBUFFERPOS));
	oRtAttrCalBufPos.nBuffer1Pos = nBeginPos;
	oRtAttrCalBufPos.nBuffer1Len = min(nUseLength, m_nXRefBufLen);
	oRtAttrCalBufPos.nBuffer2Pos = -1;
	oRtAttrCalBufPos.nBuffer2Len = 0;
	oRtAttrCalBufPos.nBufferLength = m_nXRefBufLen;
	oRtAttrCalBufPos.nDataLength = m_nXRefBufDataLen;
	oRtAttrCalBufPos.dwSampleRate = dwSampleRate;
	
	CalValues_PeakVellay(&oRtAttrCalBufPos, FALSE, bCalUseRecordBuffer);
#endif

	return TRUE;
}

void CRtVariables::CalOtherValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer)
{
	DWORD *pdVariable = m_paVariables;

	while (*pdVariable != 0)
	{
		((CRtVariable*)(*pdVariable))->CalValues(pRtAttrCalBufPos, bCalUseRecordBuffer);
		pdVariable++;
	}
}

void CRtVariables::CalStaticValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	m_pRefVariable->CalStaticValues(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);

	DWORD *pdVariable = m_paVariables;

	while (*pdVariable != 0)
	{
		if ((DWORD)m_pRefVariable != *pdVariable)
		{
			((CRtVariable*)(*pdVariable))->CalStaticValues(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);
		}

		pdVariable++;
	}
}

void CRtVariables::CalStaticValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	m_pRefVariable->CalStaticValues_Quick(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);

	DWORD *pdVariable = m_paVariables;

	while (*pdVariable != 0)
	{
		if ((DWORD)m_pRefVariable != *pdVariable)
		{
			((CRtVariable*)(*pdVariable))->CalStaticValues_Quick(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);
		}

		pdVariable++;
	}
}

void CRtVariables::CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer)
{
	DWORD *pdVariable = m_paVariables;

	while (*pdVariable != 0)
	{
		((CRtVariable*)(*pdVariable))->CalValues_PeakVellay(pRtAttrCalBufPos, bAddFrequency, bCalUseRecordBuffer);
		pdVariable++;
	}
}

void CRtVariables::CalFrequncy(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer)
{
	m_pRefVariable->CalFrequncy(pRtAttrCalBufPos, bCalUseRecordBuffer);
	
	DWORD *pdVariable = m_paVariables;

	while (*pdVariable != 0)
	{
		if ((DWORD)m_pRefVariable != *pdVariable)
		{
			((CRtVariable*)(*pdVariable))->CalFrequncy(pRtAttrCalBufPos, bCalUseRecordBuffer);
		}
		
		pdVariable++;
	}
}

void CRtVariables::CalFrequncy(CRtVariable * pdVariable, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer)
{
	pdVariable->CalFrequncy(pRtAttrCalBufPos, bCalUseRecordBuffer);
}

void CRtVariables::AddAttrValue()
{
	CRtVariable * pdVariable = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pdVariable = (CRtVariable *)GetNext(pos);
		pdVariable->AddAttrValue();	
	}
}


void CRtVariables::CalFaultValues(long nBeginPos, long nLen, long nCyclePoints)
{
	CRtVariable * pdVariable = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pdVariable = (CRtVariable *)GetNext(pos);
		pdVariable->CalFaultValues(nBeginPos, nLen, nCyclePoints);	
	}
}


BOOL CRtVariables::JudgeStartupAnalogInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	if (g_nRecordStartup == 1)
	{
		return FALSE;
	}

	CRtDataAttribute *pAttr = NULL;
	nStartup = 0;

	if (m_nXRefBufDataLen < RTATTRIBUTECAL_MIN_STARTUP_BUFLEN)//>
	{
		return TRUE;
	}
	
	
	
	if (!g_theRecordApp.CanJudgeStartup())
	{
		return TRUE;
	}

	POS pos  = NULL;
	pos = m_listAnalogInstAttrs.GetHeadPosition();

	while (pos != NULL)
	{
		pAttr = (CRtDataAttribute *)m_listAnalogInstAttrs.GetNext(pos);
		ASSERT(pAttr != NULL);
		pAttr->JudgeStartupAnalogInst(pRtAttrCalBufPos, nStartup);

		if (nStartup)
		{
			break;
		}
	}
#endif

	return TRUE;
}

BOOL CRtVariables::JudgeStartupBinaryInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	if (g_nRecordStartup == 1)
	{
		return FALSE;
	}

	CRtDataAttribute *pAttr = NULL;
	nStartup = 0;
	
	if (m_nXRefBufDataLen < RTATTRIBUTECAL_MIN_STARTUP_BUFLEN)//>
	{
		return TRUE;
	}
	
	
	
	if (!g_theRecordApp.CanJudgeStartup())
	{
		return TRUE;
	}
	
	POS pos  = NULL;
	pos = m_listBinaryInstAttrs.GetHeadPosition();
	
	while (pos != NULL)
	{
		pAttr = (CRtDataAttribute *)m_listBinaryInstAttrs.GetNext(pos);
		ASSERT(pAttr != NULL);
		pAttr->JudgeStartupBinaryInst(pRtAttrCalBufPos, nStartup);

		if (nStartup)
		{
			break;
		}
	}
#endif

	return TRUE;
}


BOOL CRtVariables::JudgeStartupAnalog(long &nStartup)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	CRtDataAttribute *pAttr = NULL;
	nStartup = 0;
	
	if (m_nXRefBufDataLen < RTATTRIBUTECAL_MIN_STARTUP_BUFLEN)//>
	{
		return TRUE;
	}

	
	
	if (!g_theRecordApp.CanJudgeStartup())
	{
		return TRUE;
	}

	POS pos  = NULL;
	pos = m_listAnalogAttrs.GetHeadPosition();
	
	while (pos != NULL)
	{
		pAttr = (CRtDataAttribute *)m_listAnalogAttrs.GetNext(pos);
		
		if (pAttr != NULL)
		{
			pAttr->JudgeStartup(nStartup);
			
			if (nStartup)
			{
				break;
			}
		}
	}
#endif
	
	return TRUE;
}

CRtVariables* CRtVariables::GetSingleAndBinaryVariables()
{
	CRtVariables *pVariables = NULL;

	return pVariables;
}

double* CRtVariables::GetValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	CRtVariable * pdVariable = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pdVariable = (CRtVariable *)GetNext(pos);
		pdValue = pdVariable->GetValueRefByID(strID);

		if (pdValue != NULL)
		{
			break;
		}

	}

	return pdValue;
}
double* CRtVariables::GetAttrValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	CRtVariable * pdVariable = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pdVariable = (CRtVariable *)GetNext(pos);
		pdValue = pdVariable->GetAttrValueRefByID(strID);
		
		if (pdValue != NULL)
		{
			break;
		}		
	}
	
	return pdValue;
}
double* CRtVariables::GetMutationValueRefByID(const CString &strID)
{
	double *pdValue = NULL;
	CRtVariable * pdVariable = NULL;
	POS pos  = NULL;
	pos = GetHeadPosition();
	
	while (pos != NULL)
	{
		pdVariable = (CRtVariable *)GetNext(pos);
		pdValue = pdVariable->GetValueRefByID(strID);
		
		if (pdValue != NULL)
		{
			break;
		}		
	}
	
	return pdValue;
}

void CRtVariables::AdjustStaticAttrs()
{
	CRtVariable *pVarible = NULL;
	POS pos  = GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		pVarible->AdjustStaticAttrs();

		m_paVariables[nIndex] = (DWORD)pVarible;
		nIndex++;
	}
}

BOOL CRtVariables::BuildExpression()
{	
	CRtVariable *pVarible = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->BuildExpression()) 
		{
			//break;		
		}
		else
		{
			debug_trace("CRtVariables Build Expression failed!");
		}
	}
	
	return TRUE;
}

void CRtVariables::InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr)
{
	m_pRtMemBufferMngr = pRtMemBufferMngr;
	m_pAttrTimeBuffer = (CMemBuffer_UShort*)pRtMemBufferMngr->FindBufferByBufferID(g_pszAttrTimeBufferID);

	CRtVariable *pVarible = NULL;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		pVarible->InitBufferMngr(pRtMemBufferMngr);

		if (pVarible->m_strID == m_strRefVariable)
		{
			m_pRefVariable = pVarible;
		}
	}

	if (m_pRefVariable == NULL)
	{
		m_pRefVariable = (CRtVariable *)GetHead();
	}

	ASSERT (m_pRefVariable != NULL);
	
	if (m_pRefVariable == NULL)
	{
		debug_trace("not define refrence variable!!");
	}
	else
	{
#ifdef _USE_RECORD_BUFFER_TO_CAL
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
#else
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetSpyMemBuffer();
#endif
	}
	
}

void CRtVariables::InitAttrsBuffer(long nPoints)
{
	CRtVariable *pVarible = NULL;
	POS pos  =GetHeadPosition();

	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		pVarible->InitAttrsBuffer(nPoints);
	}
}

void CRtVariables::UpdateRefVariableByVariableUse()
{
	ASSERT(m_pRefVariable != NULL);

	if(m_pRefVariable->GetVariableUseState() == 1)
	{
		return;
	}

	CRtVariable *pVarible = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if ((pVarible->IsRtSingleVariable() || pVarible->IsRtBinaryVariable()) && (pVarible->GetVariableUseState() == 1))
		{
			m_pRefVariable = pVarible;
			break;
		}
	}
	
	ASSERT (m_pRefVariable != NULL);
	
	if (m_pRefVariable == NULL)
	{
		debug_trace("not define refrence variable!!");
	}
	else
	{
#ifdef _USE_RECORD_BUFFER_TO_CAL
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
#else
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetSpyMemBuffer();
#endif
	}
}

void CRtVariables::InitRefVariable()
{
	CRtVariable *pVarible = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);

		if ((pVarible->IsRtSingleVariable() || pVarible->IsRtBinaryVariable()) && (pVarible->GetVariableUseState() == 1))
		{
			m_pRefVariable = pVarible;
			break;
		}
	}
}

BOOL CRtVariables::InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer)
{
	//清空各种属性链表
	m_listAnalogAttrs.RemoveAll();
	m_listBinaryInstAttrs.RemoveAll();
	m_listAnalogInstAttrs.RemoveAll();

	//初始化属性计算函数、关联各种属性链表
	CRtVariable *pVarible = NULL;
	POS pos  =GetHeadPosition();

	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);

		if (pVarible->GetVariableUseState() >= 1)
		{
			pVarible->InitDataAttributeCalFunc(bCalUseRecordBuffer);
		}
	}
	
	//初始化模拟、开关通道链表
	InitAnologBinaryVariableList();

	//初始化交流模拟电压、交流模拟电流链表,发变组实验专用
	InitACAnologVariableList();

	if (m_pClone != NULL)
	{
		m_pClone->InitDataAttributeCalFunc(TRUE);
	}

	return TRUE;
}

void CRtVariables::InitVariablesFIFOIndex()
{
	CRtVariable *pVarible = NULL;
	POS pos  =GetHeadPosition();
	UINT nClassID = 0;
	long nIndex = 0;
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		nClassID = pVarible->GetClassID();

		if (nClassID == RTCLASSID_SINGLEVARIABLE || nClassID == RTCLASSID_BINARYVARIABLE )
		{
			g_pChannelFIFOIndex[nIndex] = (unsigned short)pVarible->Get_ChIndex();
			nIndex++;
		}
	}
}

long CRtVariables::GetACUSingleVariableCount()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable() && pVarible->IsVariableType_U())			
		{
			CRtSingleVariable *pSingle = (CRtSingleVariable *)pVarible;

			if (pSingle->IsACDCVariable() || pSingle->IsACVariable())
			{
				nCount++;
			}
		}
	}
	
	return nCount;
}

long CRtVariables::GetACISingleVariableCount()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable() && pVarible->IsVariableType_I())			
		{
			CRtSingleVariable *pSingle = (CRtSingleVariable *)pVarible;
			
			if (pSingle->IsACDCVariable() || pSingle->IsACVariable())
			{
				nCount++;
			}
		}
	}
	
	return nCount;
}

long CRtVariables::GetSingleVariableCount()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable())			
		{
			nCount++;
		}
	}

	return nCount;
}

long CRtVariables::GetBinaryVariableCount()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtBinaryVariable())			
		{
			nCount++;
		}
	}
	
	return nCount;
}

long CRtVariables::GetComplexVariableCount()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtComplexVariable())			
		{
			nCount++;
		}
	}
	
	return nCount;
}

long CRtVariables::GetMultiVariableCount()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtMultiVariable())			
		{
			nCount++;
		}
	}	
	return nCount;
}

long CRtVariables::GetVariableCountWithRecordBuffer()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable())
		{
			if (pVarible->IsUserecordBuffer() && pVarible->IsVariableUse())			
			{
				nCount++;
			}
		}
	}
	
	pos =GetHeadPosition();

	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtBinaryVariable())
		{
			if (pVarible->IsUserecordBuffer() && pVarible->IsVariableUse())			
			{
				nCount++;
				break;
			}
		}
	}

	return nCount;
}

CRtVariable* CRtVariables::FindByVariableID(const char* pstrAttrID)
{
	CRtVariable* pObj = NULL;
	CRtVariable* pFind = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pObj = (CRtVariable*)GetNext(pos);
		
		if (pObj != NULL)
		{
			if (_stricmp(pObj->m_strID.GetString(), pstrAttrID) == 0)
			{
				pFind = pObj;
				break;
			}
		}
	}
	
	return pFind;
}

CRtVariable* CRtVariables::FindByAttrBufferID(const char* pstrAttrBufferID)
{
	CRtVariable* pObj = NULL;
	CRtVariable* pFind = NULL;
	CRtDataAttributes *pAttrs =  NULL;			
	CRtDataAttribute *pAttr =  NULL;
	POS posTemp = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pObj = (CRtVariable*)GetNext(pos);
		
		if (pObj != NULL)
		{
			pAttrs = pObj->m_pDataAttrs;
			posTemp = pAttrs->GetHeadPosition();

			while (posTemp != NULL) 
			{
				pAttr = (CRtDataAttribute *)pAttrs->GetNext(posTemp);

				if (pAttr != NULL)
				{
					if (_stricmp(pAttr->m_strBufferID.GetString(), pstrAttrBufferID) == 0)
					{
						pFind = pObj;
						break;
					}
				}
			}
			
			if (pFind == pObj) 
			{
				break;
			}
		}
	}
	
	return pFind;	
}

CRtVariable* CRtVariables::FindByRecordBufferID(const char* pstrRecordBufferID)
{
	CRtVariable* pObj = NULL;
	CRtVariable* pFind = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pObj = (CRtVariable*)GetNext(pos);
		
		if (pObj != NULL)
		{			
			if (_stricmp(pObj->m_strRecordBufferID.GetString(), pstrRecordBufferID) == 0)
			{
				pFind = pObj;
				break;
			}
		}
	}
	
	return pFind;		
}

CRtVariable* CRtVariables::FindByBufferID(const char* pstrBufferID)
{
	CRtVariable* pFind = NULL;
	pFind = FindByRecordBufferID(pstrBufferID);

	if (pFind == NULL)
	{
		pFind = FindByAttrBufferID(pstrBufferID);
	}

	return pFind;
}

CRtVariable* CRtVariables::FindByHDChIndex(int nHDChIndex)
{
	CRtVariable* pObj = NULL;
	CRtVariable* pFind = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pObj = (CRtVariable*)GetNext(pos);
		
		if (pObj != NULL)
		{			
			if (pObj->Get_ChIndex() == nHDChIndex)
			{
				pFind = pObj;
				break;
			}
		}
	}
	
	return pFind;		
}

BOOL CRtVariables::IsPosInRange(long nPos, long nBegin, long nEnd)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	if (nEnd > nBegin)
	{//表示数据区只有一段
		return (nBegin <= nPos && nPos <= nEnd);
	}
	else
	{
		return ( (nBegin <= nPos && nPos <= (long)m_nXRefBufLen) || (0 <= nPos && nPos <= nEnd) );
	}
#endif
	return FALSE;
}

BOOL CRtVariables::IsPosInRange(CRtVariable * pdVariable, long nPos, long nBegin, long nEnd)
{
	if (nEnd > nBegin)
	{//表示数据区只有一段
		return (nBegin <= nPos && nPos <= nEnd);
	}
	else
	{
		return ( (nBegin <= nPos && nPos <= (long)pdVariable->m_nRefBufLen) || (0 <= nPos && nPos <= nEnd) );
	}

	return FALSE;
}

//获取异常属性计算位置。从上次计算的位置开始算起
//增加RTATTRIBUTECAL_MIN_BUFFER_LEN - USE_RT_FILTER_BUFFER_LEN长度
long CRtVariables::GetExceptionalAttrCalPos(DWORD* pdwAttrCalPos/*,DWORD dwFillBeginPos*/)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	//第一个过零点，起始位置
	if (m_nXAttrCalBeginPos == m_nXRefBufFillBeginPos)
	{
		return 0;
	}

	*pdwAttrCalPos = m_nXAttrCalBeginPos;
	pdwAttrCalPos++;

	//第二个过零点，终止位置，及填充的开始位置
	*pdwAttrCalPos = m_nXRefBufFillBeginPos;
	
	//下次计算的位置
	m_nXFrequencyCalBeginPos = *pdwAttrCalPos;

//	m_nAttrCalBeginPos = *pdwAttrCalPos;
#endif
	return 1;	
}

long CRtVariables::GetExceptionalAttrCalPos(CRtVariable * pdVariable, DWORD* pdwAttrCalPos/*,DWORD dwFillBeginPos*/)
{
	//第一个过零点，起始位置
	if (pdVariable->m_nAttrCalBeginPos == pdVariable->m_nRefBufFillBeginPos)
	{
		return 0;
	}

	*pdwAttrCalPos = pdVariable->m_nAttrCalBeginPos;
	pdwAttrCalPos++;

	//第二个过零点，终止位置，及填充的开始位置
	*pdwAttrCalPos = pdVariable->m_nRefBufFillBeginPos;
	
	//下次计算的位置
	pdVariable->m_nFrequencyCalBeginPos = *pdwAttrCalPos;

//	m_nAttrCalBeginPos = *pdwAttrCalPos;
	return 1;	
}

long CRtVariables::GetNormalAttrCalPos(DWORD* pBegin, DWORD* pEnd, DWORD* pdwAttrCalPos, double dFreqValue, PRTATTRIBUTECALFUNCPARA pCalPara)
{
#ifdef _USE_RECORD_BUFFER_TO_CAL
	double dAttrCalUsePoints = (double)g_dwSampleRate / dFreqValue;
#else
	double dAttrCalUsePoints = (double)pCalPara->dwSampleRate / dFreqValue;	
#endif


	long nCount = 0;
	DWORD* pTemp = pBegin;
	DWORD dwAttrCalUsePoints = rcd_CalCyclePoints(dAttrCalUsePoints, g_bCarry_For_AttrCalUsePoints);
	
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	while(pTemp <= pEnd)
	{
		*pdwAttrCalPos = *pTemp;
		pTemp++;
		pdwAttrCalPos++;

		nCount++;
	}

	if (nCount > 0)
	{
		nCount--;
	}
	
	//移位下一次计算频率的起点
	m_nXFrequencyCalBeginPos = *pCalPara->pdwFreqZeroPosition + dwAttrCalUsePoints * 2 / 3;
	
	if (m_nXFrequencyCalBeginPos >= m_nXRefBufLen)
	{
		m_nXFrequencyCalBeginPos -= m_nXRefBufLen;
	}
	
#endif
	return nCount;
}

long CRtVariables::GetNormalAttrCalPos(CRtVariable * pdVariable,DWORD* pBegin, DWORD* pEnd, DWORD* pdwAttrCalPos, double dFreqValue, PRTATTRIBUTECALFUNCPARA pCalPara)
{
#ifdef _USE_RECORD_BUFFER_TO_CAL
	double dAttrCalUsePoints = (double)g_dwSampleRate / dFreqValue;
#else
	double dAttrCalUsePoints = (double)pCalPara->dwSampleRate / dFreqValue;	
#endif

	long nCount = 0;
	DWORD* pTemp = pBegin;
	DWORD dwAttrCalUsePoints = rcd_CalCyclePoints(dAttrCalUsePoints, g_bCarry_For_AttrCalUsePoints);
	
	while(pTemp <= pEnd)
	{
		*pdwAttrCalPos = *pTemp;
		pTemp++;
		pdwAttrCalPos++;

		nCount++;
	}

	if (nCount > 0)
	{
		nCount--;
	}
	
	//移位下一次计算频率的起点
	pdVariable->m_nFrequencyCalBeginPos = *pCalPara->pdwFreqZeroPosition + dwAttrCalUsePoints * 2 / 3;
	
	if (pdVariable->m_nFrequencyCalBeginPos >= pdVariable->m_nRefBufLen)
	{
		pdVariable->m_nFrequencyCalBeginPos -= pdVariable->m_nRefBufLen;
	}
	
	return nCount;
}

BOOL CRtVariables::IsHaveSameNameVariable(CRtVariable* pVariable)
{
	if (pVariable == NULL)
	{
		return FALSE;
	}

	BOOL bHaveSameNameVar = FALSE;
	POS pos  = GetHeadPosition();

	while(pos != NULL)
	{
		CRtVariable* pVar = (CRtVariable*)GetNext(pos);

		if (pVar != NULL)
		{
			if (pVar != pVariable)
			{
				if (pVar->m_strName == pVariable->m_strName)
				{
					bHaveSameNameVar = TRUE;
					break;
				}
			}
		}
	}

	return bHaveSameNameVar;
}

//初始化参考通道
void CRtVariables::ValidateRefVariable(BOOL bCalUseRecordBuffer)
{
	if (m_pRefVariable == NULL)//fdp add 2010.8.31
	{
		return;
	}

	if (m_pRefVariable->GetVariableUseState() == 1)
	{
		return;
	}

	POS pos  = GetHeadPosition();
	
	while(pos != NULL)
	{
		CRtVariable* pVar = (CRtVariable*)GetNext(pos);
		
		if (pVar->GetVariableUseState() == 1)
		{
			m_pRefVariable = pVar;
			break;
		}
	}

	if (bCalUseRecordBuffer)
	{
		m_pRefBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
	}
	else
	{
		m_pRefBuffer = m_pRefVariable->m_pAttachRecordBuffer;
	}

}

//判断上次计算的终点m_nAttrCalBeginPos（即本次计算的起点）是否是这次找到的过零点中的一个，如果不是，传出偏移量nOffSet
//如果是的话，pBegin是m_nAttrCalBeginPos对应的过零点在数组的指针
BOOL CRtVariables::IsAttrCalBeginPosInRefZeroPos(DWORD** pBegin,DWORD* pEnd,long& nOffSet)
{
	BOOL bIsZeroPos = FALSE;
	nOffSet = 0;
	DWORD* pTemp = *pBegin;
	long nTemp = *pTemp;
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	
	while(pTemp <= pEnd)
	{
		if(*pTemp == m_nXAttrCalBeginPos)
		{
			*pBegin = pTemp;
			bIsZeroPos = TRUE;
			break;
		}
		
		pTemp++;
	}
	
	if(!bIsZeroPos)
	{
		//nOffSet = nTemp - m_nAttrCalBeginPos;
		
		//fdp changed 2010.5.15
		if (nTemp >= (long)m_nXAttrCalBeginPos) 
		{
			nOffSet = nTemp - m_nXAttrCalBeginPos;
		}
		else
		{
			nOffSet = m_nXRefBufLen + nTemp;
			nOffSet -= m_nXAttrCalBeginPos;
		}
	}	
#endif
	
	return bIsZeroPos;
	
}

BOOL CRtVariables::IsAttrCalBeginPosInRefZeroPos(CRtVariable * pdVariable, DWORD** pBegin,DWORD* pEnd,long& nOffSet)
{
	BOOL bIsZeroPos = FALSE;
	nOffSet = 0;
	DWORD* pTemp = *pBegin;
	long nTemp = *pTemp;
	
	while(pTemp <= pEnd)
	{
		if(*pTemp == pdVariable->m_nAttrCalBeginPos)
		{
			*pBegin = pTemp;
			bIsZeroPos = TRUE;
			break;
		}
		
		pTemp++;
	}
	
	if(!bIsZeroPos)
	{
		//nOffSet = nTemp - m_nAttrCalBeginPos;
		
		//fdp changed 2010.5.15
		if (nTemp >= (long)pdVariable->m_nAttrCalBeginPos) 
		{
			nOffSet = nTemp - pdVariable->m_nAttrCalBeginPos;
		}
		else
		{
			nOffSet = pdVariable->m_nRefBufLen + nTemp;
			nOffSet -= pdVariable->m_nAttrCalBeginPos;
		}
	}	
	
	return bIsZeroPos;
	
}
//////////////////////////////
DWORD CRtVariables::GetAttrCalPosition2 (DWORD *pdwAttrCalPosition,PRTATTRIBUTECALFUNCPARA pCalPara)
{	
	DWORD dwCount = 0;
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_

	UINT nCount = *pCalPara->pnRefFreqZeroPosCount;//获得过零点个数

	DWORD* pdwRefBegin  = pCalPara->pdwRefFreqZeroPosition;
	DWORD* pdwRefEnd    = pCalPara->pdwRefFreqZeroPosition + nCount - 1;
	DWORD* pAttrCalPos = pdwAttrCalPosition;

	if(nCount < 2 || nCount >= MAX_FREQ_ZERO_POS_COUNT)//没有一个完整的周期
	{
		if (m_nXAttrCalBeginPos == 0xFFFFFFFF)
		{
			m_nXAttrCalBeginPos    = 0;
			m_n64AttrReadBeginPos = 0;
		}
		
		//异常处理，从当前位置往后6000点
		dwCount = GetExceptionalAttrCalPos(pAttrCalPos/*, m_nRefBufFillBeginPos*/);
	}
	else // 有一个完整的周期
	{
		if (m_nXAttrCalBeginPos == 0xFFFFFFFF)
		{//如果是第一次计算，则从第0个数据开始
			m_nXAttrCalBeginPos	  = 0;
			m_n64AttrReadBeginPos = 0;
			*pAttrCalPos = 0;    //从第一个点开始计算
			*pdwRefBegin = 0;    //强制修改第一个值，表示从第一个开始计算
			dwCount = GetNormalAttrCalPos(pdwRefBegin ,pdwRefEnd, pAttrCalPos ,*(pCalPara->pRefFrequency), pCalPara);
		}
		else
		{//不是第一次计算，从上次计算的终止位置开始
			//判断参数计算位置是否是一个过零点
			long nOffSet = 0;
			DWORD* pBegin = pdwRefBegin;
			
			//判断是否是过零点，如果是过零点知道是哪一个过零点，不是获得和上一个计算点的距离
			//pBegin表示返回的过零点的起始位置
			BOOL bIsZeroPos = IsAttrCalBeginPosInRefZeroPos(&pBegin ,pdwRefEnd ,nOffSet);
			
			if(bIsZeroPos)
			{
				//pdwRefEnd为最后的位置，不是过零点，pdwRefEnd    = pCalPara->pdwRefFreqZeroPosition + nCount;
				//pdwRefEnd的前一个点才是过零点，及最后一个过零点不是上次计算的终点
				if(m_nXAttrCalBeginPos != *pdwRefEnd)//说明新获得数据中有一个完整的周期
				{
					dwCount = GetNormalAttrCalPos(pBegin ,pdwRefEnd, pAttrCalPos ,*(pCalPara->pRefFrequency), pCalPara);	
				}
				else
				{
					//上次计算的位置为最后一个过零点，可能是正常波形后，出现异常波形
					//此种情况下，如果从m_nAttrCalBeginPos到计算的终止位置长度够长
					//则算确定为一次属性计算的点
					dwCount = GetExceptionalAttrCalPos(pAttrCalPos/*,m_nRefBufFillBeginPos*/);
				}
			}
			else
			{
				//dwCount = GetExceptionalAttrCalPos(pAttrCalPos/*,m_nRefBufFillBeginPos*/);
				//上次计算的数据点位于这批过零点的中间，说明数据毛刺很大
				if (IsPosInRange(m_nXAttrCalBeginPos, *pdwRefBegin, *pdwRefEnd))
				{//此种情况下的处理，从上次计算的点到数据的终点，按照异常处理
					dwCount = GetExceptionalAttrCalPos(pAttrCalPos/*,m_nRefBufFillBeginPos*/);
				}
				else
				{//上次计算的数据点位于这批过零点的中间，认为m_nAttrCalBeginPos在这批数据的前面，这种情况可能出现吗？
					*pdwRefBegin = m_nXAttrCalBeginPos;
					pBegin = pdwRefBegin;
					dwCount = GetNormalAttrCalPos(pBegin ,pdwRefEnd, pAttrCalPos ,*(pCalPara->pRefFrequency), pCalPara);		
				}
			}	
		}
	}

	//根据缓存是否循环，设置m_n64RecordReadBeginPos和m_n64AttrReadBeiginPos
	SetReadBeginPos();//pBuffer
#endif
	return dwCount;	
}

DWORD CRtVariables::GetAttrCalPosition2 (CRtVariable * pdVariable,PRTATTRIBUTECALFUNCPARA pCalPara)
{	
	DWORD dwCount = 0;

	UINT nCount = *pCalPara->pnRefFreqZeroPosCount;//获得过零点个数

	DWORD* pdwRefBegin  = pCalPara->pdwRefFreqZeroPosition;
	DWORD* pdwRefEnd    = pCalPara->pdwRefFreqZeroPosition + nCount - 1;
	DWORD* pAttrCalPos = pdVariable->m_dwAttrCalPosition;

	if(nCount < 2 || nCount >= MAX_FREQ_ZERO_POS_COUNT)//没有一个完整的周期
	{
		if (pdVariable->m_nAttrCalBeginPos == 0xFFFFFFFF)
		{
			pdVariable->m_nAttrCalBeginPos    = 0;
			pdVariable->m_n64AttrReadBeginPos = 0;
		}
		
		//异常处理，从当前位置往后6000点
		dwCount = GetExceptionalAttrCalPos(pdVariable, pAttrCalPos/*, m_nRefBufFillBeginPos*/);
	}
	else // 有一个完整的周期
	{
		if (pdVariable->m_nAttrCalBeginPos == 0xFFFFFFFF)
		{//如果是第一次计算，则从第0个数据开始
			pdVariable->m_nAttrCalBeginPos	  = 0;
			pdVariable->m_n64AttrReadBeginPos = 0;
			*pAttrCalPos = 0;    //从第一个点开始计算
			*pdwRefBegin = 0;    //强制修改第一个值，表示从第一个开始计算
			dwCount = GetNormalAttrCalPos(pdVariable, pdwRefBegin ,pdwRefEnd, pAttrCalPos ,*(pCalPara->pRefFrequency), pCalPara);
		}
		else
		{//不是第一次计算，从上次计算的终止位置开始
			//判断参数计算位置是否是一个过零点
			long nOffSet = 0;
			DWORD* pBegin = pdwRefBegin;
			
			//判断是否是过零点，如果是过零点知道是哪一个过零点，不是获得和上一个计算点的距离
			//pBegin表示返回的过零点的起始位置
			BOOL bIsZeroPos = IsAttrCalBeginPosInRefZeroPos(pdVariable, &pBegin ,pdwRefEnd ,nOffSet);
			
			if(bIsZeroPos)
			{
				//pdwRefEnd为最后的位置，不是过零点，pdwRefEnd    = pCalPara->pdwRefFreqZeroPosition + nCount;
				//pdwRefEnd的前一个点才是过零点，及最后一个过零点不是上次计算的终点
				if(pdVariable->m_nAttrCalBeginPos != *pdwRefEnd)//说明新获得数据中有一个完整的周期
				{
					dwCount = GetNormalAttrCalPos(pdVariable, pBegin ,pdwRefEnd, pAttrCalPos ,*(pCalPara->pRefFrequency), pCalPara);	
				}
				else
				{
					//上次计算的位置为最后一个过零点，可能是正常波形后，出现异常波形
					//此种情况下，如果从m_nAttrCalBeginPos到计算的终止位置长度够长
					//则算确定为一次属性计算的点
					dwCount = GetExceptionalAttrCalPos(pdVariable, pAttrCalPos/*,m_nRefBufFillBeginPos*/);
				}
			}
			else
			{
				//dwCount = GetExceptionalAttrCalPos(pAttrCalPos/*,m_nRefBufFillBeginPos*/);
				//上次计算的数据点位于这批过零点的中间，说明数据毛刺很大
				if (IsPosInRange(pdVariable, pdVariable->m_nAttrCalBeginPos, *pdwRefBegin, *pdwRefEnd))
				{//此种情况下的处理，从上次计算的点到数据的终点，按照异常处理
					dwCount = GetExceptionalAttrCalPos(pdVariable, pAttrCalPos/*,m_nRefBufFillBeginPos*/);
				}
				else
				{//上次计算的数据点位于这批过零点的中间，认为m_nAttrCalBeginPos在这批数据的前面，这种情况可能出现吗？
					*pdwRefBegin = pdVariable->m_nAttrCalBeginPos;
					pBegin = pdwRefBegin;
					dwCount = GetNormalAttrCalPos(pdVariable, pBegin ,pdwRefEnd, pAttrCalPos ,*(pCalPara->pRefFrequency), pCalPara);		
				}
			}	
		}
	}

	//根据缓存是否循环，设置m_n64RecordReadBeginPos和m_n64AttrReadBeiginPos
	SetReadBeginPos(pdVariable);//pBuffer

	return dwCount;	
}

//pBuffer指向的是SpyBuffer缓存，之所以不使用RecordBuffer，是因为参数计算是根据SpyBuffer的数据
//而SpyBuffer和RecordBuffer之间有个Gap的关系，如果每次除以Gap，会产生较大的偏差
//因为偏差会累积
long CRtVariables::SetReadBeginPos(/*CMemBuffer_UnsignedShort *pBuffer*/)
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	if (m_pAttrTimeBuffer == NULL)
	{
		return 0;
	}

	if(m_nXRefBufLen > m_nXRefBufDataLen) // 不循环 nBufferLen > nDataLen
	{
		m_n64AttrReadBeginPos = 0;
	}
	else
	{
// 		if(m_dwReadBeginPos != 0) // 原来丢弃数据的缓存被覆盖
// 		{
// 			if(nFillBeginPos > m_dwReadBeginPos )
// 			{
// 				m_dwReadBeginPos = 0;	
// 			}
// 		}
		
		//因为参数缓存对应的采样数据一般  比录波缓存保存的数据要大
		//判断时间缓存是否循环
		DWORD dwTimeFillBeginPos = m_pAttrTimeBuffer->GetDataFillBeginPosition();
		DWORD dwBufferLen = m_pAttrTimeBuffer->GetBufferLength();
		DWORD dwDataLen = m_pAttrTimeBuffer->GetDataLength();
		unsigned short* pTimeBuffer = m_pAttrTimeBuffer->GetBuffer();

		if(dwBufferLen > dwDataLen)
		{
		}
		else //时间缓存循环
		{
			m_n64AttrReadBeginPos += pTimeBuffer[dwTimeFillBeginPos];
		}
	}

#endif
	return 0;
}
long CRtVariables::SetReadBeginPos(CRtVariable * pdVariable/*CMemBuffer_UnsignedShort *pBuffer*/)
{

	if(pdVariable->m_nRefBufLen > pdVariable->m_nRefBufDataLen) // 不循环 nBufferLen > nDataLen
	{
		pdVariable->m_n64AttrReadBeginPos = 0;
	}
	else
	{
// 		if(m_dwReadBeginPos != 0) // 原来丢弃数据的缓存被覆盖
// 		{
// 			if(nFillBeginPos > m_dwReadBeginPos )
// 			{
// 				m_dwReadBeginPos = 0;	
// 			}
// 		}
		if (m_pAttrTimeBuffer == NULL)
		{
			return 0;
		}
		
		//因为参数缓存对应的采样数据一般  比录波缓存保存的数据要大
		//判断时间缓存是否循环
		DWORD dwTimeFillBeginPos = m_pAttrTimeBuffer->GetDataFillBeginPosition();
		DWORD dwBufferLen = m_pAttrTimeBuffer->GetBufferLength();
		DWORD dwDataLen = m_pAttrTimeBuffer->GetDataLength();
		unsigned short* pTimeBuffer = m_pAttrTimeBuffer->GetBuffer();

		if(dwBufferLen > dwDataLen)
		{
		}
		else //时间缓存循环
		{
			m_n64AttrReadBeginPos += pTimeBuffer[dwTimeFillBeginPos];
		}
	}

	return 0;
}


void CRtVariables::SetFinalDataPos()
{
	return;

// 	DWORD dwTimeFillBeginPos = m_pAttrTimeBuffer->GetDataFillBeginPosition();
// 	DWORD dwTimeBufferLen = m_pAttrTimeBuffer->GetBufferLength();
// 	DWORD dwTimeDataLen = m_pAttrTimeBuffer->GetDataLength();
// 	unsigned short* pTime = m_pAttrTimeBuffer->GetBuffer();
// 	
// 	PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);
// 	CMemBuffer_UnsignedShort *pBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
// 	DWORD nFillBeginPos = pBuffer->GetDataFillBeginPosition();
// 	DWORD nBufferLen = pBuffer->GetBufferLength();
// 	DWORD nDataLen = pBuffer->GetDataLength();
// 	//m_n64AttrReadBeginPos是相对于监视缓存而言的，将录波缓存的也转换到建设缓存
// 	__int64 n64BufferLen = nBufferLen;
// 	__int64 n64BeginPos  = pBuffer->m_n64BeginPos * g_nSampleGap;
// 	__int64 n64FirstDataPos = n64BeginPos - n64BufferLen * g_nSampleGap;
// 	if(m_n64AttrReadBeginPos > 0) // 说明循环了，之所以不用dwTimeBufferLen == dwTimeDataLen的方式，是因为如果缓存正好满的时候也是这种情况
// 	{		
// 		//比较录波缓存的起点和属性缓存第一个点哪个更早
// 	
// 		if(n64BufferLen < n64BeginPos)//说明缓存循环了,而且应该循环了，原因是属性缓存对应的时间比录波缓存要大
// 		{
// 			//比较属性的和录波的那个早，以录波缓存的第一个点为相对零点
// 			if(n64FirstDataPos < m_n64AttrReadBeginPos)
// 			{
// 				//说明录波缓存比属性缓存早,这种可能应该不会出现，因为如果出现这种情况，就表明录波缓存对应
// 				//的录波数据长度比属性缓存对应的录波数据长度大			
// 			}
// 			else // 属性缓存比录波缓存早
// 			{
// 				//先判断属性缓存是否循环 
// 				if(dwTimeBufferLen > dwTimeDataLen) //时间缓存一定循环，不然m_n64AttrReadBeginPos为0
// 				{
// 				}
// 				else
// 				{
// 					//查找属性缓存读取的起点位置，同时修改录波缓存读取的起点位置，和属性缓存相同
// 					BOOL bFind = SetFinalDataRange(pTime,(long)dwTimeFillBeginPos,(long)dwTimeBufferLen,m_n64AttrReadBeginPos,n64FirstDataPos,m_dwTimeReadBeginPos);
// 					m_dwTimeReadEndPos = dwTimeFillBeginPos; // 都是不能取到的，是指向最后一个点的下一个点
// 					m_dwReadEndPos = nFillBeginPos;
// 					if(!bFind)
// 					{
// 						bFind = SetFinalDataRange(pTime,(long)0,(long)dwTimeFillBeginPos,m_n64AttrReadBeginPos,n64FirstDataPos,m_dwTimeReadBeginPos);
// 					}
// 					
// 				}
// 			}
// 		}
// 		else
// 		{
// 		}
// 	}
// 	else
// 	{	
// 		//查找属性缓存读取的起点位置，同时修改录波缓存读取的起点位置，和属性缓存相同
// 		if(nBufferLen > nDataLen )//都没有循环
// 		{
// 			m_dwReadEndPos = nFillBeginPos;
// 			m_dwTimeReadBeginPos = 0;
// 			m_dwTimeReadEndPos = dwTimeFillBeginPos;
// 			//m_dwReadBeginPos的值是第一个过零点的位置，已经设置过了
// 		}		
// 		else // 属性缓存没有循环，录波缓存循环
// 		{
// 			//m_dwReadBeginPos已经设置过了
// 			m_dwReadEndPos = nFillBeginPos;
// 			m_dwTimeReadEndPos = dwTimeFillBeginPos;
// 			BOOL bFind = SetFinalDataRange(pTime,(long)0,(long)dwTimeFillBeginPos,m_n64AttrReadBeginPos,n64FirstDataPos,m_dwTimeReadBeginPos);
// 		}
// 	}	
}

//由于属性缓存对应的时间一般比录波缓存对应的要长，所以在停止时需要根据录波缓存第一个点对应的时间查找属性缓存的第一个点
BOOL CRtVariables::SetFinalDataRange(unsigned short* pTimeBuffer,long nBegin,long nEnd,__int64 n64AtttrFirst,__int64 n64RecordFirst,DWORD& dwTimeBufferBegin)
{
	unsigned short* pBegin = pTimeBuffer + nBegin;
	unsigned short* pEnd   = pTimeBuffer + nEnd;
	BOOL bFind = FALSE;
	__int64 n64Temp = n64AtttrFirst;

	while(pBegin < pEnd)
	{
		n64Temp += *pBegin;

		if(n64Temp >= n64RecordFirst)
		{
			bFind = TRUE;
			break;
		}

		pBegin++;
		
	}

	if(bFind)
	{
		dwTimeBufferBegin = pBegin - pTimeBuffer;
		PRTATTRIBUTECALFUNCPARA pCalPara = m_pRefVariable->GetAttrCalFuncPara(SingleVariableAttrID_Frequancy);
		CMemBufferInterface *pBuffer = m_pRefVariable->m_pChannelBuffer->GetRecordMemBuffer();
		DWORD nBufferLen = pBuffer->GetBufferLength();
		m_dwReadBeginPos = (DWORD)(n64Temp % nBufferLen);
	}
	else
	{
	}
	
	return bFind;
	
}

// long CRtVariables::AddAbNormalValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos)
// {
// 	CRtVariable* pVarible = NULL;
// 	POS pos  = GetHeadPosition();
// 	
// 	while (pos != NULL) 
// 	{
// 		pVarible = (CRtVariable*)GetNext(pos);
// 		AddAbNormalValue(pVarible,pRtAttrCalBufPos);
// 	}
// 
// 	return 0;
// }
// 
// long CRtVariables::AddAbNormalValue(CRtVariable* pRtVarible,PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos)
// {
// 	ASSERT(pRtVarible != NULL);
// 	CRtDataAttribute *pDataAttr = NULL;
// 	POS pos  = NULL;
// 	CRtDataAttributes* pDataAttrs = pRtVarible->m_pDataAttrs;
// 	pos = pDataAttrs->GetHeadPosition();
// 	
// 	while (pos != NULL)
// 	{
// 		pDataAttr = (CRtDataAttribute*)pDataAttrs->GetNext(pos);
// 		AddAbNormalValue(pDataAttr,pRtAttrCalBufPos);
// 	}
// 	
// 	return 0;
// }
// 
// long CRtVariables::AddAbNormalValue(CRtDataAttribute* pRtDataAttr,PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos)
// {
// 	ASSERT(pRtDataAttr != NULL);
// 	UINT nAttrID = pRtDataAttr->m_nAttributeID;
// 	CMemBuffer_Float* pAttrBuffer = pRtDataAttr->m_pAttrBuffer;
// 	//在不正常的时候，只需要计算有效值和最值，平均值的，其它的直接为0，频率的已经计算过了
// 	switch(nAttrID)
// 	{
// 	case SingleVariableAttrID_Frequancy:
// 		break;
// 	case SingleVariableAttrID_EffecValue:
// 		{ 
// 			pRtDataAttr->CalValues(pRtAttrCalBufPos);
// 		}
// 		break;
// 	case SingleVariableAttrID_EffecPhase:
// 		break;
// 	case SingleVariableAttrID_FundValue:		
// 	case SingleVariableAttrID_FundPhase:
// 		{
// 			AddAbNormalValue(pAttrBuffer);
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dFundValue = 0;
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dFundPhase = 0;
// 		}
// 		break;
// 	case SingleVariableAttrID_PeakValue:
// 		{
// 			pRtDataAttr->CalValues(pRtAttrCalBufPos);
// 		}
// 		break;
// 	case SingleVariableAttrID_VellayValue:
// 		{
// 			pRtDataAttr->CalValues(pRtAttrCalBufPos);
// 		}
// 		break;
// 	case SingleVariableAttrID_InstValue:
// 		{
// 			pRtDataAttr->CalValues(pRtAttrCalBufPos);
// 		}
// 		break;
// 	case SingleVariableAttrID_AverageValue:
// 		{
// 			pRtDataAttr->CalValues(pRtAttrCalBufPos);
// 		}
// 		break;
// 	case  SingleVariableAttrID_Harm02Value:
// 	case  SingleVariableAttrID_Harm03Value:
// 	case  SingleVariableAttrID_Harm04Value:
// 	case  SingleVariableAttrID_Harm05Value:
// 	case  SingleVariableAttrID_Harm06Value:
// 	case  SingleVariableAttrID_Harm07Value:
// 	case  SingleVariableAttrID_Harm08Value:
// 	case  SingleVariableAttrID_Harm09Value:
// 	case  SingleVariableAttrID_Harm10Value:
// 	case  SingleVariableAttrID_Harm11Value:
// 	case  SingleVariableAttrID_Harm12Value:
// 	case  SingleVariableAttrID_Harm13Value:
// 	case  SingleVariableAttrID_Harm14Value:
// 	case  SingleVariableAttrID_Harm15Value:
// 	case  SingleVariableAttrID_Harm16Value:
// 	case  SingleVariableAttrID_Harm17Value:
// 	case  SingleVariableAttrID_Harm18Value:
// 	case  SingleVariableAttrID_Harm19Value:
// 	case  SingleVariableAttrID_Harm20Value:
// 	case  SingleVariableAttrID_Harm21Value:
// 	case  SingleVariableAttrID_Harm22Value:
// 	case  SingleVariableAttrID_Harm23Value:
// 	case  SingleVariableAttrID_Harm24Value:
// 	case  SingleVariableAttrID_Harm25Value:
// 		{
// 			long nHarValuePos = nAttrID - SingleVariableAttrID_Harm02Value;
// 			AddAbNormalValue(pAttrBuffer);
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dHarmValue[nHarValuePos] = 0;
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dHarmPhase[nHarValuePos] = 0;
// 		}
// 		break;
// 	case  SingleVariableAttrID_Harm02Phase:
// 	case  SingleVariableAttrID_Harm03Phase:
// 	case  SingleVariableAttrID_Harm04Phase:
// 	case  SingleVariableAttrID_Harm05Phase:
// 	case  SingleVariableAttrID_Harm06Phase:
// 	case  SingleVariableAttrID_Harm07Phase:
// 	case  SingleVariableAttrID_Harm08Phase:
// 	case  SingleVariableAttrID_Harm09Phase:
// 	case  SingleVariableAttrID_Harm10Phase:
// 	case  SingleVariableAttrID_Harm11Phase:
// 	case  SingleVariableAttrID_Harm12Phase:
// 	case  SingleVariableAttrID_Harm13Phase:
// 	case  SingleVariableAttrID_Harm14Phase:
// 	case  SingleVariableAttrID_Harm15Phase:
// 	case  SingleVariableAttrID_Harm16Phase:
// 	case  SingleVariableAttrID_Harm17Phase:
// 	case  SingleVariableAttrID_Harm18Phase:
// 	case  SingleVariableAttrID_Harm19Phase:
// 	case  SingleVariableAttrID_Harm20Phase:
// 	case  SingleVariableAttrID_Harm21Phase:
// 	case  SingleVariableAttrID_Harm22Phase:
// 	case  SingleVariableAttrID_Harm23Phase:
// 	case  SingleVariableAttrID_Harm24Phase:
// 	case  SingleVariableAttrID_Harm25Phase:
// 		break;
// 	case  MultiVariableAttrID_Impedance:
// 		{
// 			pRtDataAttr->CalValues(pRtAttrCalBufPos);
// 		}
// 		break;
// 	case  MultiVariableAttrID_PositiveSequence:
// 		{
// 			AddAbNormalValue(pAttrBuffer);
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dPositiveSequence = 0;
// 		}
// 		break;
// 	case  MultiVariableAttrID_NegativeSequence:
// 		{
// 			AddAbNormalValue(pAttrBuffer);
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dNegativeSequence = 0;
// 		}
// 		break;
// 	case  MultiVariableAttrID_ZeroSequence:
// 		{
// 			AddAbNormalValue(pAttrBuffer);
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dZeroSequence = 0;
// 		}
// 		break;
// 	case  MultiVariableAttrID_ActivePower:
// 		{
// 			double dFundValue1  = pRtDataAttr->m_oCalFuncPara.pRtChanAttr[0]->dEffecValue;
// 			double dFundValue2  = pRtDataAttr->m_oCalFuncPara.pRtChanAttr[1]->dEffecValue;
// 			double dValue = dFundValue1 * dFundValue2;
// 			
// 			if (pAttrBuffer != NULL)
// 			{
// 				pAttrBuffer->AddValue((float)dValue);
// 			}
// 			
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dActivePower = dValue;
// 		}
// 		break;
// 	case  MultiVariableAttrID_ReactivePower:
// 		{
// 			AddAbNormalValue(pAttrBuffer);
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dReactivePower = 0;
// 		}
// 		break;
// 	case  MultiVariableAttrID_ApparentPower:
// 		{
// 			double dFundValue1  = pRtDataAttr->m_oCalFuncPara.pRtChanAttr[0]->dEffecValue;
// 			double dFundValue2  = pRtDataAttr->m_oCalFuncPara.pRtChanAttr[1]->dEffecValue;
// 			double dValue = dFundValue1 * dFundValue2;
// 			
// 			if (pAttrBuffer != NULL)
// 			{
// 				pAttrBuffer->AddValue((float)dValue);
// 			}
// 			
// 			pRtDataAttr->m_oCalFuncPara.pRtChAttrVal->dActivePower = dValue;
// 		}
// 		break;
// 	default:
// 		break;
// 	}
// 
// 	return 0;
// 
// 
// }
// 
// void CRtVariables::AddAbNormalValue(CMemBuffer_Float* pAttrBuffer)
// {
// 	if (g_bAddDataToBuffer)
// 	{
// 		if (pAttrBuffer != NULL)
// 		{
// 			float fValue = 0;			
// 			pAttrBuffer->AddValue(fValue);
// 		}
// 	}	
// }

void CRtVariables::AddTimeValue(RTATTRIBUTECALBUFFERPOS& oRtAttrCalBufPos)
{
	if (m_pAttrTimeBuffer != NULL)
	{
		if (oRtAttrCalBufPos.nBuffer2Len > 0 && oRtAttrCalBufPos.nBuffer2Pos >= 0)
		{
			m_pAttrTimeBuffer->AddValue((unsigned short)(oRtAttrCalBufPos.nBuffer2Len + oRtAttrCalBufPos.nBuffer1Len));
		}
		else
		{
			m_pAttrTimeBuffer->AddValue((unsigned short)oRtAttrCalBufPos.nBuffer1Len);
		}
	}
}

void CRtVariables::AddFirstAttrData()
{
	ASSERT (FALSE);
#ifdef _CAL_USE_REF_VARIABLE_
	if (m_nXAttrCalBeginPos == 0xFFFFFFFF)//判断是否是第一个属性值
	{
		CRtVariable* pVarible = NULL;
		POS pos  = GetHeadPosition();
		
		while (pos != NULL) 
		{
			pVarible = (CRtVariable*)GetNext(pos);
			AddFirstAttrData(pVarible);
		}
	}
#endif
}

void CRtVariables::AddFirstAttrData(CRtVariable* pRtVarible)
{
	ASSERT(pRtVarible != NULL);
	CRtDataAttribute *pDataAttr = NULL;
	POS pos  = NULL;
	CRtDataAttributes* pDataAttrs = pRtVarible->m_pDataAttrs;
	pos = pDataAttrs->GetHeadPosition();
	
	while (pos != NULL)
	{
		pDataAttr = (CRtDataAttribute*)pDataAttrs->GetNext(pos);
		AddFirstAttrData(pDataAttr);
	}
}
void CRtVariables::AddFirstAttrData(CRtDataAttribute* pRtDataAttr)
{
	ASSERT(pRtDataAttr != NULL);
	CMemBuffer_Float* pAttrBuffer = pRtDataAttr->m_pAttrBuffer;

	if (pAttrBuffer != NULL)
	{
		float dValue = 0;
		pAttrBuffer->AddValue(dValue);
	}
}

//自适应功能,备份克隆通道源,删除原来的子对象
void CRtVariables::BackCloneSources()
{
	long nCount = GetCount();
	CRtVariable *pVariable = NULL;

	for(long nIndex = 0; nIndex < nCount; nIndex++)
	{
		pVariable = (CRtVariable *)GetAt(nIndex);
		ASSERT(pVariable != NULL);
		UINT nClassID = pVariable->GetClassID();

		if (nClassID == RTCLASSID_SINGLEVARIABLE)
		{
			CRtSingleVariable *pSingle = (CRtSingleVariable *)pVariable;

			if (pSingle->IsACVariable() || pSingle->IsACDCVariable())
			{
				if (RT_IsVariableTypeU(pVariable->m_nType))
				{
					m_pUSourceVariable = pSingle;
				}
				else if (RT_IsVariableTypeI(pVariable->m_nType))
				{
					m_pISourceVariable = pSingle;
				}
				else
				{
				}
			}
			else if (pSingle->IsDCVariable())
			{
				if (RT_IsVariableTypeU(pVariable->m_nType))
				{
					m_pUdcSourceVariable = pSingle;
				}
				else if (RT_IsVariableTypeI(pVariable->m_nType))
				{
					m_pIdcSourceVariable = pSingle;
				}
				else
				{
				}
			}
			else
			{
			}

		}
		else if (nClassID == RTCLASSID_BINARYVARIABLE)
		{
			CRtBinaryVariable *pBinary = (CRtBinaryVariable *)pVariable;
			m_pBSourceVariable = pBinary;
		}
		else
		{
		}
	}

	RemoveAll();
}

long CRtVariables::RTUpdateOwnByAutofit(HDINFO &oHDInfo)
{
	CRtSingleVariable *pVariable = (CRtSingleVariable *)GetAtIndex(0);

	if (pVariable != NULL)
	{
		m_strRefVariable = pVariable->m_strName;
	}

	return 0;
}

void CRtVariables::AutofitCreateMultiVariable()
{
	AutofitCreateMultiVariable_3U();
	AutofitCreateMultiVariable_3I();
	AutofitCreateMultiVariable_UI();
}

void CRtVariables::AutofitCreateMultiVariable_3U()
{
	long nUCount = GetACUSingleVariableCount();

	if (nUCount > 3)
	{
		InitAutofitMultiVariable_ChName(U3);

		CRtMultiVariable *pNew = new CRtMultiVariable();

		if (pNew != NULL)
		{
			pNew->SetParent(this);
			AddTail(pNew);

			pNew->m_strID = U3;
			pNew->m_strName = U3;
			pNew->m_strDCAC = "";
			pNew->m_strRecordBufferID = "";
			pNew->m_strSpyBufferID = "";
			pNew->m_nSpyBufferUse = 0;
			pNew->m_nRecordBufferUse = 0;
			pNew->SetVariableUseState(1);
			pNew->SetVariableType(RTVARIABLE_TYPE_U);
			pNew->AutofitCreateMultiNewChild(U3, m_pszAutoMultiChsName);
			pNew->UpdateStrNameByChannels();
		}
	}
	else
	{}
}

void CRtVariables::AutofitCreateMultiVariable_3I()
{
	long nICount = GetACISingleVariableCount();
	
	if (nICount > 3)
	{
		InitAutofitMultiVariable_ChName(I3);

		CRtMultiVariable *pNew = new CRtMultiVariable();
		
		if (pNew != NULL)
		{
			pNew->SetParent(this);
			AddTail(pNew);

			pNew->m_strID = I3;
			pNew->m_strName = I3;
			pNew->m_strDCAC = "";
			pNew->m_strRecordBufferID = "";
			pNew->m_strSpyBufferID = "";
			pNew->m_nSpyBufferUse = 0;
			pNew->m_nRecordBufferUse = 0;
			pNew->SetVariableUseState(1);
			pNew->SetVariableType(RTVARIABLE_TYPE_I);
			pNew->AutofitCreateMultiNewChild(I3, m_pszAutoMultiChsName);
			pNew->UpdateStrNameByChannels();
		}
	}
	else
	{
	}
}

void CRtVariables::AutofitCreateMultiVariable_UI()
{
	long nICount = GetACISingleVariableCount();
	long nUCount = GetACUSingleVariableCount();

	
	if ((nICount > 0) && (nUCount > 0))
	{
		InitAutofitMultiVariable_ChName(UI);

		CRtMultiVariable *pNew = new CRtMultiVariable();
		
		if (pNew != NULL)
		{
			pNew->SetParent(this);
			AddTail(pNew);

			pNew->m_strID = UI;
			pNew->m_strName = UI;
			pNew->m_strDCAC = "";
			pNew->m_strRecordBufferID = "";
			pNew->m_strSpyBufferID = "";
			pNew->m_nSpyBufferUse = 0;
			pNew->m_nRecordBufferUse = 0;
			pNew->SetVariableUseState(1);
			pNew->SetVariableType(RTVARIABLE_TYPE_NONE);
			pNew->AutofitCreateMultiNewChild(UI, m_pszAutoMultiChsName);
			pNew->UpdateStrNameByChannels();
		}
	}
	else
	{
	}
}

void CRtVariables::InitAutofitMultiVariable_ChName(const CString &strName)
{
	long nLen = 0;
	nLen = strName.GetLength();

	if (nLen == 0)
	{
		return;
	}

	if (_stricmp(strName.GetString(), U3) == 0)
	{
		InitAutoMultiVariable_3U_ChName();
	}
	else if (_stricmp(strName.GetString(), I3) == 0)
	{
		InitAutoMultiVariable_3I_ChName();
	}
	else if (_stricmp(strName.GetString(), UI) == 0)
	{
		InitAutoMultiVariable_UI_ChName();
	}
	else
	{
	}
}

void CRtVariables::InitAutoMultiVariable_3U_ChName()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable() && pVarible->IsVariableType_U())			
		{
			strcpy(m_pszAutoMultiChsName[nCount], pVarible->m_strID.GetString());
			nCount++;

			if (nCount == AUTO_MULTI_CH_NAME_COUNT)
			{
				break;
			}
		}
	}
}

void CRtVariables::InitAutoMultiVariable_3I_ChName()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  =GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable() && pVarible->IsVariableType_I())			
		{
			strcpy(m_pszAutoMultiChsName[nCount], pVarible->m_strID.GetString());
			nCount++;

			if (nCount == AUTO_MULTI_CH_NAME_COUNT)
			{
				break;
			}
		}
	}
}

void CRtVariables::InitAutoMultiVariable_UI_ChName()
{
	CRtVariable *pVarible = NULL;
	long nCount = 0;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable() && pVarible->IsVariableType_U())			
		{
			strcpy(m_pszAutoMultiChsName[nCount], pVarible->m_strID.GetString());
			break;
		}
	}

	pos = GetHeadPosition();

	nCount++;
	while (pos != NULL) 
	{
		pVarible = (CRtVariable *)GetNext(pos);
		
		if (pVarible->IsRtSingleVariable() && pVarible->IsVariableType_I())			
		{
			strcpy(m_pszAutoMultiChsName[nCount], pVarible->m_strID.GetString());			
			break;
		}
	}
}

void CRtVariables::SetRefVariable(CRtVariable* pVariable)		
{
//	ASSERT(pVariable != NULL);
	if (pVariable != NULL)
	{
		m_pRefVariable	= pVariable;	
		CRtMemBufferChannel *pChannelBuffer = pVariable->m_pChannelBuffer;
		
		if (pChannelBuffer != NULL)
		{
			m_pRefBuffer = pChannelBuffer->GetRecordMemBuffer();
		}
	}
	
	if (m_pClone != NULL)
	{
		m_pClone->SetRefVariable(m_pRefVariable->m_pClone);
	}

}

void CRtVariables::SetVariable(CRtVariable* pVariable,long nIndex)
{
	m_paVariables[nIndex] = (DWORD)pVariable;
}

long CRtVariables::GetSingleVariableCountUsed()
{
	long nCount = 0;
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		ASSERT(pVariable != NULL);
		
		if ((pVariable->GetClassID() == RTCLASSID_SINGLEVARIABLE) && (pVariable->GetVariableUseState() == 1))
		{
			nCount++;
		}
	}

	return nCount;
}

long CRtVariables::GetBinaryVariableCountUsed()
{
	long nCount = 0;
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		ASSERT(pVariable != NULL);
		
		if ((pVariable->GetClassID() == RTCLASSID_BINARYVARIABLE) && (pVariable->GetVariableUseState() == 1))
		{
			nCount++;
		}
	}
	
	return nCount;
}

long CRtVariables::GetVariableCountUsed()
{
	long nCount = 0;
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		ASSERT(pVariable != NULL);

		if (pVariable->GetVariableUseState() == 1)
		{
			nCount++;
		}
	}
	
	return nCount;
}

BOOL CRtVariables::IsChannelInUse(const CString &strChID)
{
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	BOOL bUse = FALSE;
	
	if (rcd_IsBinaryChannelID(strChID))
	{
		long nBinaryChID = rcd_GetBinaryChannelID(strChID);
		long nVarID1 = nBinaryChID*16;
		long nVarID2 = nVarID1 + 16;

		while (pos != NULL)
		{
			pVariable = (CRtVariable *)GetNext(pos);
			ASSERT(pVariable != NULL);
			
			if (pVariable->GetClassID() == RTCLASSID_BINARYVARIABLE)
			{
				CRtBinaryVariable *pBinary = (CRtBinaryVariable*)pVariable;

				if (nVarID1 <= pBinary->m_nIndex && pBinary->m_nIndex < nVarID2)
				{
					if (pVariable->GetVariableUseState() == 1)
					{
						bUse = TRUE;
						break;
					}
				}
			}
		}
	}
	else
	{
		while (pos != NULL)
		{
			pVariable = (CRtVariable *)GetNext(pos);
			ASSERT(pVariable != NULL);
			
			if (pVariable->m_strID == strChID)
			{
				if (pVariable->GetVariableUseState() == 1)
				{
					bUse = TRUE;
					break;
				}
			}
		}
	}

	return bUse;
}


//////////////////////////////////////////////////////////////////////////
//系统分析管理
void CRtVariables::InitByAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr)
{
	long nVariableCount = GetCount();
	CRtVariable *pVar = NULL;
	CRtDataAttribute *pAttr = NULL;
	CRtDataAttributes *pAttrs = NULL;

	for (long nIndex = 0; nIndex < nVariableCount; nIndex++)
	{
		pVar = (CRtVariable*)GetAt(nIndex);
		ASSERT(pVar != NULL);
		pAttrs = pVar->m_pDataAttrs;

		if (pAttrs != NULL)
		{
			long AttrCount = pAttrs->GetCount();
			
			for (long nAttrIndex = 0; nAttrIndex < AttrCount; nAttrIndex++)
			{
				pAttr = (CRtDataAttribute *)pAttrs->GetAt(nAttrIndex);

				pAttr->SetSpyState(oMR1200SysAnalyseMngr.oAttrSpy.nAttrState[nIndex][pAttr->m_nAttributeID]);
			}
		}
	}
}

void CRtVariables::InitByAttrDedfault(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr)
{
	long nVariableCount = GetCount();
	CRtVariable *pVar = NULL;
	CRtDataAttribute *pAttr = NULL;
	CRtDataAttributes *pAttrs = NULL;
	
	for (long nIndex = 0; nIndex < nVariableCount; nIndex++)
	{
		pVar = (CRtVariable*)GetAt(nIndex);
		ASSERT(pVar != NULL);
		pAttrs = pVar->m_pDataAttrs;
		
		if (pAttrs != NULL)
		{
			long AttrCount = pAttrs->GetCount();
			
			for (long nAttrIndex = 0; nAttrIndex < AttrCount; nAttrIndex++)
			{
				pAttr = (CRtDataAttribute *)pAttrs->GetAt(nAttrIndex);
				
				pAttr->SetSpyState(oMR1200SysAnalyseMngr.oAttrDefault.nAttrState[nIndex][nAttrIndex]);
			}
		}
	}
}

void CRtVariables::SaveAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr)
{
	long nVariableCount = GetCount();
	CRtVariable *pVar = NULL;
	CRtDataAttribute *pAttr = NULL;
	CRtDataAttributes *pAttrs = NULL;
	
	for (long nIndex = 0; nIndex < nVariableCount; nIndex++)
	{
		pVar = (CRtVariable*)GetAt(nIndex);
		ASSERT(pVar != NULL);
		pAttrs = pVar->m_pDataAttrs;
		
		if (pAttrs != NULL)
		{
			long AttrCount = pAttrs->GetCount();
			
			for (long nAttrIndex = 0; nAttrIndex < AttrCount; nAttrIndex++)
			{
				pAttr = (CRtDataAttribute *)pAttrs->GetAt(nAttrIndex);
				
				oMR1200SysAnalyseMngr.oAttrSpy.nAttrState[nIndex][pAttr->m_nAttributeID] = (short)pAttr->GetSpyState();
			}
		}
	}
}

void CRtVariables::InitByHarmAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr)
{
	PHARMHISTOGRAM pCfg = &oMR1200SysAnalyseMngr.oHarmHistogram;
	long nVariables = m_oListAnologVariable.GetCount();
	//ASSERT (nVariables > 0);
	
	if (nVariables <= 0)
	{
		return;
	}
	
	//当前通道的索引验证
	if (pCfg->nChIndex < 0 || pCfg->nChIndex >= nVariables)
	{
		pCfg->nChIndex = 0;
	}

	CRtVariable* pVariable = (CRtVariable*)m_oListAnologVariable.GetAt(pCfg->nChIndex);
	ASSERT(pVariable != NULL);

	if (pVariable != NULL)
	{
		long nIndex = 0;
		BOOL* pHarmShow = oMR1200SysAnalyseMngr.oHarmHistogram.bHarmShow;
		CRtDataAttribute *pAttr = NULL;
		POS pos  = pVariable->m_pDataAttrs->GetHeadPosition();
		
		while (pos != NULL)
		{
			pAttr = (CRtDataAttribute*)pVariable->m_pDataAttrs->GetNext(pos);
			if (pAttr->IsHarmValueAttr())
			{
				pAttr->SetSpyState(pHarmShow[nIndex]);
				nIndex++;
			}
		}
	}

}

void CRtVariables::SetAttrSpyStateByVariableSpyConfig(const CString & strAttrID, long nAttrSpyState)
{
	CRtVariable *pVar = NULL;
	CRtDataAttribute *pAttr = NULL;

	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pVar = (CRtVariable *)GetNext(pos);
		ASSERT(pVar != NULL);

		if (pVar->IsRtSingleVariable() || (pVar->GetVariableUseState() == 1))
		{
			pAttr = pVar->m_pDataAttrs->FindByAttrID(strAttrID.GetString());

			if(pAttr != NULL)
			{
				pAttr->SetSpyState(nAttrSpyState);
			}
		}
	}
}

void CRtVariables::InitAnologBinaryVariableList()
{	
	m_oListBinaryVariable.RemoveAll();
	m_oListAnologVariable.RemoveAll();
	
	POS pos  = GetHeadPosition();
	while(pos != NULL)
	{
		CRtVariable* pVar = (CRtVariable*)GetNext(pos);
		ASSERT(pVar != NULL);
		
		if (pVar->IsRtBinaryVariable())
		{
			m_oListBinaryVariable.AddTail(pVar);
		}
		else if (pVar->IsRtSingleVariable())
		{
			m_oListAnologVariable.AddTail(pVar);
		}
		else
		{
		}
	}
}

void CRtVariables::InitACAnologVariableList()
{
	m_oListACVariable_U.RemoveAll();
	m_oListACVariable_I.RemoveAll();

	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		CRtVariable *pVariable = (CRtVariable *)GetNext(pos);
		
		if (pVariable->IsRtSingleVariable())
		{
			CRtSingleVariable *pSingle = (CRtSingleVariable *)pVariable;
			
			if (pSingle->IsACVariable() || pSingle->IsACDCVariable())
			{
				if (pSingle->IsVariableType_U())
				{
					m_oListACVariable_U.AddTail(pSingle);
				}
				else if (pSingle->IsVariableType_I())
				{
					m_oListACVariable_I.AddTail(pSingle);
				}
				else
				{
				}
			}
		}
		else if (pVariable->IsRtMultiVariable())
		{
			CRtMultiVariable *pMulti = (CRtMultiVariable *)pVariable;
			
			if (pMulti->IsACVariable() || pMulti->IsACDCVariable())
			{
				if (pMulti->IsVariableType_U())
				{
					m_oListACVariable_U.AddTail(pMulti);
				}
				else if (pMulti->IsVariableType_I())
				{
					m_oListACVariable_I.AddTail(pMulti);
				}
				else
				{
				}
			}
		}
		else
		{
		}		
	}
}

CRtSingleVariable* CRtVariables::GetSingleVariableByTranChannelIndex(int nAttachedTranCHIndex)
{
	CRtSingleVariable *pFind = NULL;
	CRtSingleVariable *pVar = NULL;
	POS pos  = m_oListAnologVariable.GetHeadPosition();
	
	while (pos != NULL)
	{
		pVar = (CRtSingleVariable *)m_oListAnologVariable.GetNext(pos);
		ASSERT(pVar != NULL);
		
		if (pVar->m_nAttachedTranChannelIndex == nAttachedTranCHIndex)
		{
			pFind = pVar;
			break;
		}
	}

	return pFind;
}

CRtSingleVariable* CRtVariables::GetSingleVariableByHDIndex(int nHDIndex)
{
	CRtSingleVariable *pFind = NULL;
	CRtSingleVariable *pVar = NULL;
	POS pos  = m_oListAnologVariable.GetHeadPosition();
	
	while (pos != NULL)
	{
		pVar = (CRtSingleVariable *)m_oListAnologVariable.GetNext(pos);
		ASSERT(pVar != NULL);
		
		if (pVar->Get_ChIndex() == nHDIndex)
		{
			pFind = pVar;
			break;
		}
	}
	
	return pFind;
}

void CRtVariables::CloneVariables(CRtVariables* pSrc,CMemBuffer_UShort** pAttachBuffer)
{
	pSrc->m_pClone = this;
	long nIndex = 0;
	long nVarIndex = 0;
	POS pos  = pSrc->GetHeadPosition();
	CMemBuffer_UShort* pBuffer = NULL;
	CRtVariable* pNew = NULL;

	while(pos != NULL)
	{
		pNew = NULL;
		CRtVariable* pVar = (CRtVariable*)pSrc->GetNext(pos);
		ASSERT (pVar != NULL);
		UINT nClassID = pVar->GetClassID();
	
		//创建子对象
		switch (nClassID)
		{
		case RTCLASSID_SINGLEVARIABLE:
			pNew = new CRtSingleVariable();
			break;
		case RTCLASSID_BINARYVARIABLE:
			//pNew = new CRtBinaryVariable();
			break;
		case RTCLASSID_COMPLEXVARIABLE:
			//pNew = new CRtComplexVariable();
			break;
		case RTCLASSID_MULTIVARIABLE:
			//pNew = new CRtMultiVariable();
			break;
		}
		
		if (pNew != NULL)
		{
			//添加入链表
			pNew->SetParent(this);
			AddTail(pNew);
			
			//关联的缓存
			if (pAttachBuffer != NULL)
			{
				pBuffer = pAttachBuffer[nIndex];
				nIndex++;
			}
			else
			{
				pBuffer = NULL;
			}
			
			m_paVariables[nVarIndex] = (DWORD)pNew;
			nVarIndex++;
			//子对象Clone
			pNew->CloneVariable(pVar,pBuffer);
		}
	}

	//设置默认的参考通道
	CRtVariable* pCurrRef = pSrc->GetRefVariable();
	m_pRefVariable = pCurrRef->m_pClone; 
	//根据源的参考通道设置当前的参考通道

}

CRtSingleVariable* CRtVariables::GetFirstSingleWithUseState()
{
	CRtSingleVariable *pSingle = NULL;
	CRtSingleVariable *pFind = NULL;

	POS pos  = m_oListAnologVariable.GetHeadPosition();

	while (pos != NULL)
	{
		pSingle = (CRtSingleVariable *)m_oListAnologVariable.GetNext(pos);
		ASSERT(pSingle != NULL);

		if (pSingle->GetVariableUseState() == 1)
		{
			pFind = pSingle;
			break;
		}
	}

	return pFind;
}

void CRtVariables::CalBeginPosByStartupPos(long nStartupPos, DWORD nSampleGap, DWORD dwSampleRate)
{
	//ASSERT (FALSE);   //2021-3-9  lijunqing
#ifdef _CAL_USE_REF_VARIABLE_
	m_nStartupPos = nStartupPos;
	
	ASSERT(g_pCurrRecordTest->m_pStartup != NULL);

	//获得追忆点数
	long nLookBackDataLen = (long)(g_pCurrRecordTest->m_pStartup->m_dTimeLookBack * dwSampleRate);

#ifndef _USE_RECORD_BUFFER_TO_CAL
	nLookBackDataLen = g_pCurrRecordTest->m_pStartup->m_dTimeLookBack * dwSampleRate;
#endif

	//计算第一个点的位置和启动点到第一个点的距离
	long nFirstDataPos = nStartupPos - nLookBackDataLen;
	m_nDataLenStartuptoFirstData = nLookBackDataLen;
	__int64 n64FirstIndex = 0;

#ifdef _USE_RECORD_BUFFER_TO_CAL
	n64FirstIndex = g_theRecordApp.m_pRtMemBufferMngr->m_n64RecordHeadIndex + nFirstDataPos;
#else
	ASSERT(FALSE);
	n64FirstIndex = 0;//(g_theRecordApp.m_pRtMemBufferMngr->m_n64SpyHeadIndex + nFirstDataPos) / nSampleGap;
#endif

	//修正计算的位置
	if (m_nXRefBufDataLen == m_nXRefBufLen)
	{
		if (nFirstDataPos < 0)
		{
			nFirstDataPos += m_nXRefBufLen;
		}

		m_nFirstDataPos = n64FirstIndex;

		if (m_nFirstDataPos < 0)
		{
			m_nFirstDataPos = 0;

			//因为追忆时间太长了
#ifdef _USE_RECORD_BUFFER_TO_CAL
			m_nDataLenStartuptoFirstData = 0;
#else
			m_nDataLenStartuptoFirstData = 0;
#endif
		}
	}
	else
	{
		if (nFirstDataPos < 0)
		{
			nFirstDataPos = 0;
			m_nFirstDataPos = 0;

#ifdef _USE_RECORD_BUFFER_TO_CAL
			m_nDataLenStartuptoFirstData = nStartupPos;
#else
			m_nDataLenStartuptoFirstData = nStartupPos / nSampleGap;
#endif
		}
	}

//	m_nStartupPos = m_nDataLenStartuptoFirstData + m_nFirstDataPos;
	g_theRecordApp.SetOnlineExWriteBeginPos(nFirstDataPos * 2);
#endif
}

void CRtVariables::AdjustRefVariable(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr)
{
	CString str = oMR1200SysAnalyseMngr.szRefVariable;
	m_pRefVariable = NULL;

	if (str.IsEmpty())
	{
	}
	else
	{		
		SetRefVariableByVariableName(oMR1200SysAnalyseMngr.szRefVariable);//szTrigVariable
	}
	
	if (m_pRefVariable != NULL)
	{
		return;
	}

	POS pos  = GetHeadPosition();

	if (m_pRefVariable == NULL)
	{
		while(pos != NULL)
		{
			CRtVariable* pVar = (CRtVariable*)GetNext(pos);
			
			if ((pVar->IsRtSingleVariable()) && (pVar->GetVariableUseState() == 1))
			{
				m_pRefVariable = pVar;

				memcpy(oMR1200SysAnalyseMngr.szRefVariable,pVar->m_strName.GetString(),20);
				break;
			}
		}

		if (m_pRefVariable != NULL && m_pClone != NULL)
		{
			m_pClone->SetRefVariable(m_pRefVariable->m_pClone);
		}
		return;
	}

	if (m_pRefVariable->GetVariableUseState() == 0)
	{
		
		m_pRefVariable = NULL;
		
		while(pos != NULL)
		{
			CRtVariable* pVar = (CRtVariable*)GetNext(pos);
			
			if ((pVar->IsRtSingleVariable()) && (pVar->GetVariableUseState() == 1))
			{
				m_pRefVariable = pVar;
				memcpy(oMR1200SysAnalyseMngr.szRefVariable,pVar->m_strName.GetString(),20);
				break;
			}
		}
	}

	if (m_pRefVariable != NULL && m_pClone != NULL)
	{
		m_pClone->SetRefVariable(m_pRefVariable->m_pClone);
	}
}

void CRtVariables::SetRefVariableByVariableName(const CString& strName)
{
	POS pos  = m_oListAnologVariable.GetHeadPosition();
	CRtSingleVariable* pFind = NULL;

	while (pos != NULL)
	{
		CRtSingleVariable* pVar = (CRtSingleVariable*)m_oListAnologVariable.GetNext(pos);

		if (pVar->m_strName == strName)
		{
			pFind = pVar;
			break;
		}
	}

	if (pFind != NULL) 
	{
		m_strRefVariable = strName;
		SetRefVariable(pFind);
	}
	
	

	if (g_theRecordApp.IsAdStart())
	{
		m_bRefVariableChanged = TRUE;
	}
	else
	{
		InitDataAttributeCalFunc(TRUE);
	}
}

BOOL CRtVariables::IsAllSingleVariableNoUse()
{
	BOOL bTrue = TRUE;

	CRtSingleVariable *pSingle = NULL;
	POS pos  = m_oListAnologVariable.GetHeadPosition();

	while (pos != NULL)
	{
		pSingle = (CRtSingleVariable *)m_oListAnologVariable.GetNext(pos);
		ASSERT(pSingle != NULL);

		if (pSingle->GetVariableUseState() == 1)
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

void CRtVariables::ResetAttrSpyState()
{
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();
	
	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		pVariable->ResetAttrSpyState();
	}
}

long CRtVariables::GetAnalogIndex(CRtSingleVariable* pVar)
{
	long nFind = -1;
	nFind = m_oListAnologVariable.FindIndex(pVar);

	return nFind;
}

long CRtVariables::GetBinaryIndex(CRtBinaryVariable* pVar)
{
	long nFind = -1;
	nFind = m_oListBinaryVariable.FindIndex(pVar);
	
	return nFind;
}

void CRtVariables::CalInstValue(long nBegin,BOOL bCalUseRecordBuffer)
{
	RTATTRIBUTECALBUFFERPOS oRtAttrCalBufPos;
	memset(&oRtAttrCalBufPos, 0, sizeof(RTATTRIBUTECALBUFFERPOS));
	oRtAttrCalBufPos.nBuffer1Pos = nBegin;
	oRtAttrCalBufPos.nBuffer1Len = 1;
	oRtAttrCalBufPos.nBuffer2Pos = -1;
	oRtAttrCalBufPos.nBuffer2Len = -1;
	
	DWORD *pdVariable = m_paVariables;

	while (*pdVariable != 0)
	{
		((CRtVariable*)(*pdVariable))->CalInstValue(&oRtAttrCalBufPos,bCalUseRecordBuffer);
		pdVariable++;
	}
}

void CRtVariables::SetAttrUse(UINT nAttrID, long nUse)
{
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		pVariable->SetAttrUse(nAttrID, nUse);
	}
}

void CRtVariables::ResetValueCal()
{
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		pVariable->ResetValueCal();
	}
}

void CRtVariables::ResetValuesByHdIndex(long nHdIndex)
{
	CRtVariable *pVariable = NULL;
	POS pos  = GetHeadPosition();

	g_oStttVariablesRtValueBuffer.ResetAllValues();

	while (pos != NULL)
	{
		pVariable = (CRtVariable *)GetNext(pos);
		
		if (pVariable->Get_HdIndex() == nHdIndex)
		{
			pVariable->ZeroAllCalValues();
		}
	}
}

void CRtVariables::InitRtCalVariables()
{
	memset(m_paVariables, 0, MAX_RTVARIABLES * sizeof(DWORD));
}

void CRtVariables::InitCalFuncPara(long nChIndex)
{
	CRtVariable *pVariable = (CRtVariable*)GetAtIndex(nChIndex);

	if (pVariable == NULL)
	{
		return;
	}

	pVariable->InitCalFuncPara();
}

long CRtVariables::GetChIndexByID(const CString &strChID)
{
	CRtVariable *pVariable = (CRtVariable*)FindByID(strChID);

	if (pVariable == NULL)
	{
		return -1;
	}

	return pVariable->Get_ChIndex();
}

//////////////////////////////////////////////////////////////////////////
//CStttVariablesRtValueBuffer
CStttVariablesRtValueBuffer g_oStttVariablesRtValueBuffer;

CStttVariablesRtValueBuffer::CStttVariablesRtValueBuffer()
{
	m_nWritePos = 0;
	m_nBufferCount = 0;
	memset(m_oSttVarsVals, 0, sizeof(m_oSttVarsVals));
}

CStttVariablesRtValueBuffer::~CStttVariablesRtValueBuffer()
{
}

void CStttVariablesRtValueBuffer::ResetAllValues()
{
	long k = 0;

	for (k=0; k<XCYCLE_MAX_COUNT; k++)
	{
		PSTTVARIABLESRTVALUES p = &m_oSttVarsVals[k];
		memset(p->oRtValues, 0, sizeof(p->oRtValues));
	}
}

PSTTVARIABLESRTVALUES CStttVariablesRtValueBuffer::GetNextForWrite()
{
	PSTTVARIABLESRTVALUES pRet = &m_oSttVarsVals[m_nWritePos];

	m_nWritePos++;

	if (m_nBufferCount < XCYCLE_MAX_COUNT)
	{
		m_nBufferCount = m_nWritePos;
	}

	if (m_nWritePos >= XCYCLE_MAX_COUNT)
	{
		m_nWritePos = 0;
	}

	return pRet;
}

PSTTVARIABLESRTVALUES CStttVariablesRtValueBuffer::GetCurrForWrite()
{
	PSTTVARIABLESRTVALUES pRet = &m_oSttVarsVals[m_nWritePos];

	return pRet;
}

void CStttVariablesRtValueBuffer::NextForWrite()
{
	m_nWritePos++;

	if (m_nBufferCount < XCYCLE_MAX_COUNT)
	{
		m_nBufferCount = m_nWritePos;
	}

	if (m_nWritePos >= XCYCLE_MAX_COUNT)
	{
		m_nWritePos = 0;
	}
}

PSTTVARIABLESRTVALUES CStttVariablesRtValueBuffer::GetLast()
{
	if (m_nBufferCount == 0)
	{
		return &m_oSttVarsVals[0];
	}

	long nPos = m_nWritePos - 1;

	if (nPos < 0)
	{
		nPos = XCYCLE_MAX_COUNT-1;
	}

	return  &m_oSttVarsVals[nPos];
}

void CStttVariablesRtValueBuffer::GetLast(STTVARIABLESRTVALUES &oSttValues)
{
	PSTTVARIABLESRTVALUES p = GetLast();
	oSttValues = *p;
}
