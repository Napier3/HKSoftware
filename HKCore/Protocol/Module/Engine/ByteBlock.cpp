#include "StdAfx.h"
#include "ByteBlock.h"
#include "BbDataRanges.h"
#include "PpScript.h"
#include "bbvariables.h"
#include "BbDataRange.h"
#include "PpParsePackage.h"
#include "PpProducePackage.h"
#include "PpTemplate.h"

#define PP_BYTEBLOCK_DEFAULT_LENGTH  8

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CByteBlock::CByteBlock(void)
{
	m_nPackOrder=0;
	m_nIsKey = 0;
	m_nLength = 1;
	m_strLength = L"1";
	m_strDataType = g_strBbDataTypeConst;
	m_pRanges = NULL;
	m_pMatchScript = NULL;
	m_pScript = NULL;
	m_pVariables = NULL;
	m_pSrcByteBlock = NULL;

	m_bAttchBuffer = FALSE;
	m_pBuffer = NULL;
	
// #ifdef _PP_DEV_MODE_
	AllocBuffer(PP_BYTEBLOCK_DEFAULT_LENGTH);
// #endif

	m_nBufferPos = 0;
	m_pFormatTextBuffer = NULL;
	m_nDataLength = 0;
	m_nBufferLength = 0;
}

void CByteBlock::AllocBuffer(long nLen)
{
	//ASSERT (nLen > 0);

	if (nLen <= 0)
	{
		nLen = 10;
	}

	if (nLen > 4096)
	{
		FreeBuffer();
		return;
	}

	FreeBuffer();
	m_pBuffer = new BYTE[nLen+2];
	m_nBufferLength = nLen;

// 	if (m_pBuffer == NULL)
// 	{
// 		m_pBuffer = new BYTE[nLen+2];
// 	}
}

void CByteBlock::AttachBuffer(BYTE *pBuffer)
{
	FreeBuffer();
	m_bAttchBuffer = TRUE;
	m_pBuffer = pBuffer;
}

void CByteBlock::SetBuffer(BYTE *pBuffer)
{
	FreeBuffer();
	m_pBuffer = pBuffer;
}

BYTE* CByteBlock::DetachBuffer()
{
	BYTE *pBuffer = m_pBuffer;
	m_bAttchBuffer = FALSE;
	m_pBuffer = NULL;
	return pBuffer;
}

void CByteBlock::FreeBuffer()
{
	if (m_bAttchBuffer)
	{
		DetachBuffer();
	}
	else
	{
		if (m_pBuffer != NULL)
		{
			delete []m_pBuffer;
			m_pBuffer = NULL;
		}
		else
		{
		}
	}
}

long CByteBlock::SetBufferData(const CString &strData)
{
	return 0;
}

void CByteBlock::InitByHexString(const CString &strData)
{
	long nLen = strData.GetLength();
	nLen = min(m_nLength*2, nLen);

	long nIndex = 0;
	long nBufferIndex = 0;
	WCHAR chH;
	WCHAR chL;
	BYTE *pBuffer = m_pBuffer;

	for (nIndex=0; nIndex<nLen; )
	{
		chH = strData.GetAt(nIndex);
		nIndex++;
		chL = strData.GetAt(nIndex);
		nIndex++;
		*pBuffer = HexToValue(chH, chL);
		pBuffer++;
	}
}

void CByteBlock::InitByTextString(const CString &strData)
{
	long nLen = strData.GetLength();
	nLen = min(m_nLength, nLen);

	long nIndex = 0;
	BYTE *pBuffer = m_pBuffer;

	for (nIndex=0; nIndex<nLen; )
	{
		*pBuffer = strData.GetAt(nIndex);
		
		pBuffer++;
		nIndex++;
	}

	*pBuffer = 0;
}

CByteBlock::~CByteBlock(void)
{
	FreeBuffer();

	if (m_pFormatTextBuffer != NULL)
	{
		delete m_pFormatTextBuffer;
		m_pFormatTextBuffer = NULL;
	}
}

long CByteBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strIsKeyKey, oNode, m_nIsKey);
	xml_GetAttibuteValue(pKeys->m_strDataTypeKey,oNode,m_strDataType);
	xml_GetAttibuteValue(pKeys->m_strLengthKey,oNode,m_strLength);
	xml_GetAttibuteValue(pKeys->m_strOrderKey,oNode,m_nPackOrder);

	if (m_strDataType == g_strBbDataTypeConst)
	{
		m_dwDataType = BbDataType_Const;
	}
	else if (m_strDataType == g_strBbDataTypeVariable)
	{
		m_dwDataType = BbDataType_Variable;
	}
	else
	{
		m_dwDataType = BbDataType_NULL;
	}

	return 0;
}

long CByteBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKeys->m_strIsKeyKey, oElement, m_nIsKey);
	xml_SetAttributeValue(pKeys->m_strDataTypeKey,oElement,m_strDataType);
	xml_SetAttributeValue(pKeys->m_strLengthKey,oElement,m_strLength);//xml_SetAttributeValue(pKeys->m_strLengthKey,oElement,m_nLength);
	xml_SetAttributeValue(pKeys->m_strOrderKey, oElement, m_nPackOrder);

	return 0;
}

long CByteBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CByteBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRangesKey)
	{
		m_pRanges = new CBbDataRanges();
		return m_pRanges;
		//return new CBbDataRanges();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)
	{
		m_pScript = new CPpScript(strClassID);
		return m_pScript;
		//return new CPpScript(strClassID);
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strMatchScriptKey)
	{
		m_pMatchScript = new CPpScript(strClassID);
		return m_pMatchScript;
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVarialblesKey)
	{
		m_pVariables = new CBbVariables(strClassID);
		return m_pVariables;
		//return new CBbVariables(strClassID);
	}

	return NULL;
}

 void CByteBlock::InitAfterRead()
 {
	 POS pos = GetHeadPosition();
	 CExBaseObject *p = NULL;

	 while (pos != NULL)
	 {
		 p = GetNext(pos);

		 if (p->GetClassID() == PPCLASSID_BBVARIABLES)
		 {
			 m_pVariables = (CBbVariables *)p;
		 }

		 if (p->GetClassID() == PPCLASSID_BBDATARANGES)
		 {
			 m_pRanges = (CBbDataRanges*)p;
		 }

		 if (p->GetClassID() == PPCLASSID_PPSCRIPT)
		 {
			 CPpScript *pScript = (CPpScript*)p;
			 if (pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)
			 {
				 m_pScript = pScript;
			 }
			 if (pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strMatchScriptKey)
			 {
				 m_pMatchScript = pScript;
			 }
			 //m_pScript = (CPpScript*)p;
		 }
	 }
 }


CExBaseObject* CByteBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
DWORD CByteBlock::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	DWORD nResult = 0;

	if (IsDataTypeText())
	{
		nResult = ParseFormat(oPkgBufPos, pDetail);
	}
	else
	{
		nResult = ParseNormal(oPkgBufPos, pDetail);
	}

	return nResult;
}


//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
DWORD CByteBlock::ParseNormal(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	DWORD nResult = 0;

	// ��ȡ�ֽڿ��ֽڳ���
	m_nLength = GetByteBlockLength();
	AllocBuffer(m_nLength);
	//ASSERT (m_pBuffer != NULL);

	if (m_nLength <= 0)
	{//����ֽڿ�ĳ���Ϊ0,ִֻ�нű�
		if (m_pScript != NULL)
		{
			m_pScript->Run();
		}

		return 0;
	}

	if (m_pBuffer == NULL)
	{
		return 0;
	}

	//BYTE *byData = new BYTE[m_nLength];	

	// �ӻ�������ȡ����
	nResult = GetByteBlockData(oPkgBufPos, /*byData*/m_pBuffer);

	if (IsPpParseError(nResult))
	{
		//delete []byData;
		FreeBuffer();
		return nResult;
	}

	// ����ɹ���ȡ2���ƻ���������
	//m_pBuffer = byData;

	// �������ֽڿ�����
	if (m_strDataType == g_strBbDataTypeConst)
	{// ����ǳ���
// 		CBbDataRange *pRange;
// 		pRange = (CBbDataRange*)m_pRanges->GetAtIndex(0);
// 		ASSERT (pRange != NULL);
// 
// 		if(pRange != NULL)
// 		{
// 			if (pRange->m_strType == PPRANGE_CONST_LONG)
// 			{// ����������ʮ���Ƴ���
// 				long nValue = _wtol(pRange->m_strValue);
// 				memcpy(m_pBuffer, &nValue, m_nLength);
// 			}
// 			else if (pRange->m_strType == PPRANGE_CONST_HEX)
// 			{
// 				InitByHexString(pRange->m_strValue);
// 			}
// 			else if (pRange->m_strType == PPRANGE_CONST_TEXT)
// 			{
// 				InitByTextString(pRange->m_strValue);
// 			}
// 		}
		if (m_pScript != NULL)
		{
			m_pScript->Run();
		}
	}
	else if (m_strDataType == g_strBbDataTypeVariable)
	{// ����Ǳ�����ͨ���ű���ֵ���ֽڿ����
		if (m_pScript != NULL)
		{
			m_pScript->Run();

			//if (m_pScript->m_dwReturn == 0)
			//{// ����ű���������
			//	FreeBuffer();
			//	return PpParseError();
			//}
		}
	}

	// ��¡������
	CByteBlock *pByteBlock = NULL;
	pByteBlock = (CByteBlock*)Clone();
	pByteBlock->SetBuffer(DetachBuffer());

	// ����������ӵ�pDetail��
	pByteBlock->SetParent(pDetail);
	pDetail->AddTail(pByteBlock);

	return nResult;
}

//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
DWORD CByteBlock::ParseFormat(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	DWORD nResult = 0;

	// ��ȡ�ֽڿ��ֽڳ���
	m_nDataLength = PpGetLengthFromCurr(oPkgBufPos);

	//���仺��������
	AllocBuffer(m_nDataLength);
	
	if (m_pBuffer == NULL)
	{
		return 0;
	}

	//���ݻ�����λ��
	PACKAGEBUFFERPOS oBack = oPkgBufPos;

	// �ӻ�������ȡ����
	nResult = GetByteBlockData(oPkgBufPos, /*byData*/m_pBuffer, m_nDataLength);

	if (IsPpParseError(nResult))
	{
		//delete []byData;
		FreeBuffer();
		return nResult;
	}

	CFormatTextBuffer *pFtb = GetFormatTextBuffer();

	pFtb->ParseFormatBuffer(m_pBuffer, m_nDataLength);

	if (m_pScript != NULL)
	{
		m_pScript->Run();
	}

	long nLength = pFtb->GetLength();
	BYTE *pTemp = new BYTE[nLength + 2];
	memcpy(pTemp, m_pBuffer, nLength);
	FreeBuffer();
	m_pBuffer = pTemp;
	m_nDataLength = nLength;
	PpOffsetCurrBuffer(oBack, m_nDataLength);
	oPkgBufPos = oBack;

	// ��¡������
	CByteBlock *pByteBlock = NULL;
	pByteBlock = (CByteBlock*)Clone();
	pByteBlock->SetBuffer(DetachBuffer());

	// ����������ӵ�pDetail��
	pByteBlock->SetParent(pDetail);
	pDetail->AddTail(pByteBlock);

	return nResult;
}

//�ֽڿ��ƥ��		��Ҫ���ڽ���
DWORD CByteBlock::Match(PACKAGEBUFFERPOS &oPkgBufPos)
{
	DWORD nResult = 0;
	m_nLength = GetByteBlockLength();

	if (m_nIsKey == 0)
	{
		OffsetByteBlockData(oPkgBufPos, NULL);
		return nResult;
	}

	if (m_dwDataType == BbDataType_Const || m_dwDataType == BbDataType_Variable)
	{
	}
	else
	{
		return nResult;
	}

	// �����жϸ��ֽڿ��Ӧ��������2���ƻ��������Ƿ����
	// ��ȡ�ֽڿ��ֽڳ���
	//BYTE *byData = new BYTE[m_nLength];
	AllocBuffer(m_nLength);

	// �ӻ�������ȡ����
	nResult = GetByteBlockData(oPkgBufPos, m_pBuffer);

	if (!IsPpParseMatch(nResult))
	{
		//delete []byData;
		FreeBuffer();
		return nResult;
	}

	if (m_dwDataType == BbDataType_Const)
	{
		nResult = MatchConst();
	}
	else if (m_dwDataType == BbDataType_Variable)
	{
		nResult = MacthVariable();
	}

	FreeBuffer();

	return nResult;
}

DWORD CByteBlock::MatchConst()
{
	if (m_pRanges == NULL)
	{
		return PpParseNotWholeMatch();
	}

	if (m_pRanges->GetCount() == 0)
	{
		return PpParseNotWholeMatch();
	}

	DWORD nResult = 0;
	CBbDataRange *pRange;
	pRange = (CBbDataRange*)m_pRanges->GetAtIndex(0);

	if (pRange->m_strType == PPRANGE_CONST_LONG)
	{// ����������ʮ���Ƴ���
		return MatchConstLong(pRange);
	}
	else if (pRange->m_strType == PPRANGE_CONST_HEX)
	{
		return MatchConstHex(pRange);
	}
	else if (pRange->m_strType == PPRANGE_CONST_TEXT)
	{
		return MatchConstText(pRange);
	}

	return nResult;
}

DWORD CByteBlock::MatchConstLong(CBbDataRange *pRange)
{
	DWORD nResult = 0;

#ifdef UNICODE
	long nValue = _wtol(pRange->m_strValue);
#else
    long nValue = atol(pRange->m_strValue.GetString());
#endif

	long nValueOfBuff = 0;
	memcpy(&nValueOfBuff, m_pBuffer, m_nLength);

	if (nValue != nValueOfBuff)
	{
		nResult = PpParseNotWholeMatch();
	}

	return nResult;
}

DWORD CByteBlock::MatchConstHex(CBbDataRange *pRange)
{
	DWORD nResult = 0;

	BYTE *pValBuf = NULL;
	long nLen = 0;

	pValBuf = pRange->GetValueBuffer(nLen);

	if (pValBuf == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("range GetValueBuffer failed"));
		return nResult;
	}

	//CString strValue = pRange->m_strValue;
	
	if (memcmp(pValBuf, m_pBuffer, nLen) != 0)
	{
		nResult = PpParseNotWholeMatch();
	}

	return nResult;
}

DWORD CByteBlock::MatchConstText(CBbDataRange *pRange)
{
	DWORD nResult = 0;

	BYTE *pValBuf = NULL;
	long nLen = 0;

	pValBuf = pRange->GetValueBuffer(nLen);

	if (pValBuf == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("range GetValueBuffer failed"));
		return nResult;
	}
//	CString strValue = pRange->m_strValue;

	if (memcmp(pValBuf, m_pBuffer, nLen) != 0)
	{
		nResult = PpParseNotWholeMatch();
	}

	return nResult;
}

DWORD CByteBlock::MacthVariable()
{
	DWORD nResult = 0;

	if (m_pMatchScript != NULL)
	{
		m_pMatchScript->Run();

		if (m_pMatchScript->m_dwReturn == 0)
		{
			nResult = PpParseNotWholeMatch();
		}
	}

	return nResult;
}

DWORD CByteBlock::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	
{
	DWORD nResult = 0;
	CBbDataRange *pRange = NULL;

	// ��ȡ�ֽڿ��ֽڳ���
	m_nLength = GetByteBlockLength();

	if (m_nLength <= 0)
	{
		return PpProduceError();
	}

	AllocBuffer(m_nLength);

	// ������ֽڿ�����
	if (m_strDataType == g_strBbDataTypeConst)
	{// ����ǳ���
		if (m_pRanges->GetCount() <= 0)
		{
			return PpProduceError();
		}
		
		pRange = (CBbDataRange*)m_pRanges->GetAtIndex(0);
		
		if (pRange->m_strType == PPRANGE_CONST_LONG)
		{// ����������ʮ���Ƴ���
#ifdef UNICODE
			long nValue = _wtol(pRange->m_strValue);
#else
            long nValue = atol(pRange->m_strValue.GetString());
#endif
			memcpy(m_pBuffer, &nValue, m_nLength);
		}
		else if (pRange->m_strType == PPRANGE_CONST_HEX)
		{
			InitByHexString(pRange->m_strValue);
		}
		else if (pRange->m_strType == PPRANGE_CONST_TEXT)
		{
			InitByTextString(pRange->m_strValue);
		}
	}
	else if (m_strDataType == g_strBbDataTypeText)
	{// ����ǳ���
// 		if (m_pRanges->GetCount() <= 0)
// 		{
// 			return PpProduceError();
// 		}
// 		
// 		pRange = (CBbDataRange*)m_pRanges->GetAtIndex(0);
// 		
// 		InitByTextString(pRange->m_strValue);
	}
	else if (m_strDataType == g_strBbDataTypeVariable)
	{// ����Ǳ�����ͨ���ű���ֵ���ֽڿ����
		if (m_pScript != NULL)
		{
			m_pScript->Run();

			//20170303  XVM�ű��Ľ�����
			//if (m_pScript->m_dwReturn == 0)
			//{// ����ű��������
			//	FreeBuffer();
			//	return PpProduceError();
			//}
		}	

	}
	else if (IsDataTypeEncode())
	{
		CPpTemplate *pTemplate = (CPpTemplate*)GetAncestor(PPCLASSID_PPTEMPLATE);
		DWORD dwEncode = 0;

		if (pTemplate != NULL)
		{
			dwEncode = pTemplate->PkgEncoded(m_strDataType);
		}

		if (m_nLength == 1)
		{
			*m_pBuffer = (BYTE)dwEncode;
		}
		else if (m_nLength == 2)
		{
			*((WORD*)m_pBuffer) = (WORD)dwEncode;
		}
		else if (m_nLength == 3)
		{
			*m_pBuffer = (BYTE)(dwEncode >> 16);
			*(m_pBuffer+1) = (BYTE)(dwEncode >> 8);
			*(m_pBuffer+2) = (BYTE)dwEncode;
		}
		else if (m_nLength == 4)
		{
			*((DWORD*)m_pBuffer) = dwEncode;
		}
		else
		{
			memset(m_pBuffer, 0, m_nLength);
		}
	}
	// �����������������������
	//memcpy(oPkgBufPos.pBuffer+oPkgBufPos.nBuffer1BeginPos+oPkgBufPos.nIndex, m_pBuffer, m_nLength*sizeof(BYTE));
	oPkgBufPos.nIndex += m_nLength;

	// ��¡������
	CByteBlock *pByteBlock = NULL;
	pByteBlock = (CByteBlock*)Clone();
	pByteBlock->SetBuffer(DetachBuffer());

	// ����������ӵ�pDetail��
	pByteBlock->SetParent(pDetail);
	pDetail->AddTail(pByteBlock);

	return nResult;
}

DWORD CByteBlock::ProduceLastOrder()	
{
	DWORD nResult = 0;

	// ��ȡ�ֽڿ��ֽڳ���
	m_pSrcByteBlock->m_nLength = m_nLength;

	if (m_nLength <= 0)
	{
		return PpProduceError();
	}

	BYTE *pSrcBuffer = m_pSrcByteBlock->DetachBuffer();
	m_pSrcByteBlock->AttachBuffer(m_pBuffer);

	if (m_strDataType == g_strBbDataTypeVariable)
	{// ����Ǳ�����ͨ���ű���ֵ���ֽڿ����
		if (m_pSrcByteBlock->m_pScript != NULL)
		{
			m_pSrcByteBlock->m_pScript->Run();

			if (m_pSrcByteBlock->m_pScript->m_dwReturn == 0)
			{// ����ű���������
				//ִ����ű����ָ�m_pSrcByteBlock������
				nResult = PpProduceError();
			}
		}		
	}

	//ִ����ű����ָ�m_pSrcByteBlock������
	m_pSrcByteBlock->DetachBuffer();
	m_pSrcByteBlock->SetBuffer(pSrcBuffer);

	return nResult;
}

DWORD CByteBlock::GetByteBlockData(PACKAGEBUFFERPOS &oPkgBufPos, BYTE *byData, long nDataLength)
{
	if (nDataLength < 0)
	{
		nDataLength = m_nLength;
	}

	if (nDataLength <= 0)
	{
		return 0;
	}

	ASSERT (m_nBufferLength >= nDataLength);

	DWORD nResult = 0;
	m_nBufferPos = oPkgBufPos.nIndex;
	int iCurrentPos = oPkgBufPos.nIndex;

	if (byData == NULL)
	{
		return PpParseError();
	}

	if (iCurrentPos >= oPkgBufPos.nBuffer1BeginPos && iCurrentPos <= oPkgBufPos.nBuffer1EndPos)
	{// �α�λ�ڵ�һ�λ�����
		if ((iCurrentPos+nDataLength) <= oPkgBufPos.nBuffer1EndPos)
		{// ��һ�λ������㹻ʹ��
			memcpy(byData, oPkgBufPos.pBuffer+iCurrentPos, nDataLength);//*sizeof(BYTE));
			iCurrentPos += nDataLength;
		}
		else
		{// ��һ�λ���������ʹ��
			int iTemp = iCurrentPos+nDataLength-oPkgBufPos.nBuffer1EndPos;

			if (iTemp > (oPkgBufPos.nBuffer2EndPos - oPkgBufPos.nBuffer2BeginPos))
			{// ������ȳ����ڶ��λ��������ݣ�����Ϊ���ֽڿ����ݶ�Ӧ2���������ݲ���
				return PpParseHasNoPackage();
			}
			else
			{
				//2019-12-2
				// ��һ�λ�����ʣ�ಿ��
				long nLen1 = oPkgBufPos.nBuffer1EndPos - iCurrentPos;
				long nLen2 = nDataLength - nLen1;
				memcpy(byData, oPkgBufPos.pBuffer+iCurrentPos, nLen1);//*sizeof(BYTE));

				// �ڶ��λ���������
				memcpy(byData+nLen1, oPkgBufPos.pBuffer, nLen2*sizeof(BYTE));

				iCurrentPos = nLen2;
			}
		}
	}
	else if (iCurrentPos >= oPkgBufPos.nBuffer2BeginPos && iCurrentPos <= oPkgBufPos.nBuffer2EndPos)
	{// �α�λ�ڵڶ��λ�����
		if ((iCurrentPos+nDataLength) <= oPkgBufPos.nBuffer2EndPos)
		{// �ڶ��λ������㹻ʹ��
			memcpy(byData, oPkgBufPos.pBuffer+iCurrentPos, nDataLength*sizeof(BYTE));
			iCurrentPos += nDataLength;
		}
		else
		{// ������ȳ����ڶ��λ��������ݣ�����Ϊ���ֽڿ����ݶ�Ӧ2���������ݲ���
			return PpParseHasNoPackage();
		}
	}

	// ȷ��2���ƻ����������㹻��������α��ƶ�
	oPkgBufPos.nIndex = iCurrentPos;

	return nResult;
}

DWORD CByteBlock::OffsetByteBlockData(PACKAGEBUFFERPOS &oPkgBufPos, BYTE *byData, long nDataLength)
{
	if (nDataLength < 0)
	{
		nDataLength = m_nLength;
	}

	if (nDataLength <= 0)
	{
		return 0;
	}

	DWORD nResult = 0;
	m_nBufferPos = oPkgBufPos.nIndex;
	int iCurrentPos = oPkgBufPos.nIndex;

	if (iCurrentPos >= oPkgBufPos.nBuffer1BeginPos && iCurrentPos <= oPkgBufPos.nBuffer1EndPos)
	{// �α�λ�ڵ�һ�λ�����
		if ((iCurrentPos+nDataLength) <= oPkgBufPos.nBuffer1EndPos)
		{// ��һ�λ������㹻ʹ��
			iCurrentPos += nDataLength;
		}
		else
		{// ��һ�λ���������ʹ��
			int iTemp = iCurrentPos+nDataLength-oPkgBufPos.nBuffer1EndPos;
			if (iTemp > (oPkgBufPos.nBuffer2EndPos - oPkgBufPos.nBuffer2BeginPos))
			{// ������ȳ����ڶ��λ��������ݣ�����Ϊ���ֽڿ����ݶ�Ӧ2���������ݲ���
				return PpParseHasNoPackage();
			}
			else
			{
				iCurrentPos = oPkgBufPos.nBuffer2BeginPos+iTemp;
			}
		}
	}
	else if (iCurrentPos >= oPkgBufPos.nBuffer2BeginPos && iCurrentPos <= oPkgBufPos.nBuffer2EndPos)
	{// �α�λ�ڵڶ��λ�����
		if ((iCurrentPos+nDataLength) <= oPkgBufPos.nBuffer2EndPos)
		{// �ڶ��λ������㹻ʹ��
			iCurrentPos += nDataLength;
		}
		else
		{// ������ȳ����ڶ��λ��������ݣ�����Ϊ���ֽڿ����ݶ�Ӧ2���������ݲ���
			return PpParseHasNoPackage();
		}
	}

	// ȷ��2���ƻ����������㹻��������α��ƶ�
	oPkgBufPos.nIndex = iCurrentPos;

	return nResult;
}

unsigned long CByteBlock::GetBufferSum()
{
	unsigned long nReturn = 0;

	if (m_pBuffer != NULL)
	{
		for (long nIndex=0; nIndex<m_nLength; nIndex++)
		{
			nReturn += m_pBuffer[nIndex];
		}
	}
	
	return nReturn;
}

long CByteBlock::GetByteBlockLength2()
{
	if (IsDataTypeText())
	{
		if (m_nDataLength > 0)
		{
			return m_nDataLength;
		}
	}

	return m_nLength;
}

long CByteBlock::GetByteBlockLength()
{
	long nLengthRet = -1;

	if (IsDataTypeText())
	{
		if (m_nDataLength > 0)
		{
			nLengthRet = m_nDataLength;
		}
	}

#ifdef UNICODE
	m_nLength = _wtol(m_strLength);
#else
    m_nLength = atol(m_strLength.GetString());
#endif

	if (m_nLength == 0)
	{
		CBbVariable* pVar = NULL;
		CPpParsePackage* pParsePkg = (CPpParsePackage*)GetAncestor(PPCLASSID_PPPARSEPACKGE);
		CPpProducePackage* pProducePkg = (CPpProducePackage*)GetAncestor(PPCLASSID_PPPRODUCEPACKGE);
		CPpTtPackage* pTtPkg = (CPpTtPackage*)GetAncestor(PPCLASSID_PPTTPACKAGE);

		if (pParsePkg != NULL)
		{
			pVar = (CBbVariable*)pParsePkg->FindVariableByID(m_strLength);

			if (pVar == NULL)
			{
				if (pParsePkg->m_pTtPackage == NULL)
				{
					m_nLength = 0;
					return 0;
				}

				pVar = (CBbVariable*)pParsePkg->m_pTtPackage->FindVariableByID(m_strLength);
				if (pVar == NULL)
				{
					m_nLength = 0;
					return 0;
				}
			}
		}
		else if (pProducePkg != NULL)
		{
			pVar = (CBbVariable*)pProducePkg->FindVariableByID(m_strLength);
			if (pVar == NULL)
			{
				if (pProducePkg->m_pTtPackage == NULL)
				{
					m_nLength = 0;
					return 0;
				}
				pVar = (CBbVariable*)pProducePkg->m_pTtPackage->FindVariableByID(m_strLength);
				if (pVar == NULL)
				{
					m_nLength = 0;
					return 0;
				}
			}
		}
		else if(pTtPkg != NULL)
		{
			pVar = (CBbVariable*)pTtPkg->FindVariableByID(m_strLength);
			if(pVar == NULL)
			{
				m_nLength = 0;
			}
		}
		else
		{
			m_nLength = 0;
			return 0;
		}

#ifdef UNICODE
		m_nLength = _wtol(pVar->m_strValue);
#else
        m_nLength = atol(pVar->m_strValue.GetString());
#endif
	}
	
	if (nLengthRet < 0)
	{
		nLengthRet = m_nLength;
	}
	
	return nLengthRet;
}

DWORD CByteBlock::AddBufferData(long &nIndex, BYTE *pByte)
{
	DWORD nResult = 0;

	if (m_pBuffer == NULL || m_nLength <= 0)
	{
		return PpProduceError();
	}

	memcpy(pByte+nIndex, m_pBuffer, m_nLength*sizeof(BYTE));
	nIndex += m_nLength;

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//���� ��¡ �Ա�
BOOL CByteBlock::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_nIsKey != ((CByteBlock*)pObj)->m_nIsKey)
	{
		return FALSE;
	}

	if (m_nEnable != ((CByteBlock*)pObj)->m_nEnable)
	{
		return FALSE;
	}

	if (m_nLength != ((CByteBlock*)pObj)->m_nLength)
	{
		return FALSE;
	}

	if (m_strDataType != ((CByteBlock*)pObj)->m_strDataType)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CByteBlock::Clone()
{
	CByteBlock* pNew = new CByteBlock();
	Copy(pNew);
	return pNew;
}

BOOL CByteBlock::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CByteBlock*)pDest)->m_nPackOrder = m_nPackOrder;
	((CByteBlock*)pDest)->m_nIsKey = m_nIsKey;
	((CByteBlock*)pDest)->m_nEnable = m_nEnable;
	((CByteBlock*)pDest)->m_nLength = m_nLength;
	((CByteBlock*)pDest)->m_nDataLength = m_nDataLength;
	((CByteBlock*)pDest)->m_strDataType = m_strDataType;
	((CByteBlock*)pDest)->m_strLength = m_strLength;
	((CByteBlock*)pDest)->m_pSrcByteBlock = this;

	return CExBaseObject::CopyOwn(pDest);
}

void CByteBlock::GetAllVariables(CExBaseList &oDestList)
{
	if (m_pVariables != NULL)
	{
		m_pVariables->Append(oDestList);
	}
}

void CByteBlock::SetDataRanges(long nCount)
{
	if (m_pRanges == NULL)
	{
		m_pRanges = new CBbDataRanges();
		m_pRanges->SetParent(this);
		AddTail(m_pRanges);
	}

	m_pRanges->SetCount(nCount);
}

CBbDataRanges* CByteBlock::GetBbDataRanges()
{
	if (m_pRanges == NULL)
	{
		SetDataRanges(0);
	}
	else
	{
	}

	return m_pRanges;
}

BOOL CByteBlock::IsDataTypeConst()	
{	
	return (m_strDataType == g_strBbDataTypeConst);	
}

BOOL CByteBlock::IsDataTypeText()	
{	
	return (m_strDataType == g_strBbDataTypeText);	
}

BOOL Pp_IsDataTypeCheck(const CString &strDataType)
{
	return ( (strDataType == g_strBbDataTypeSumCheck)
		|| (strDataType == g_strBbDataTypeCrcCheck) 
		|| (strDataType == g_strBbDataTypeCrcCheckFF)
		|| (strDataType == g_strBbDataTypeCrcCheckTable)
		);
}

BOOL CByteBlock::IsDataTypeCheck()	
{	
	return Pp_IsDataTypeCheck(m_strDataType);
}

BOOL CByteBlock::IsDataTypeEncode()
{
	return ( (m_strDataType == g_strEncodeModeSend)
		|| (m_strDataType == g_strEncodeModeReceive)
		|| (m_strDataType == g_strEncodeModeSAndR) 
		|| (m_strDataType == g_strEncodeModeSOrR) 

		|| (m_strDataType == g_strEncodeModeDataTypeSendID) 
		|| (m_strDataType == g_strEncodeModeDataTypeReceiveID) 
		|| (m_strDataType == g_strEncodeModeDataTypeEncodeID) 
		
		);
}

void CByteBlock::GetBufferPos(long &nBegin, long &nEnd)
{
	nBegin = m_nBufferPos;
	nEnd = nBegin + m_nLength - 1;
}

CFormatTextBuffer* CByteBlock::GetFormatTextBuffer()
{
	if (!IsDataTypeText())
	{
		return NULL;
	}

	if (m_pRanges == NULL)
	{
		return NULL;
	}

	CBbDataRange *pRange = (CBbDataRange*)m_pRanges->GetHead();

	if (pRange == NULL)
	{
		return NULL;
	}

	if (m_pFormatTextBuffer == NULL)
	{
		m_pFormatTextBuffer = new CFormatTextBuffer();
		InitFormatTextBuffer();
	}

	return m_pFormatTextBuffer;
}

void CByteBlock::InitFormatTextBuffer()
{
	if (!IsDataTypeText())
	{
		return;
	}

	if (m_pRanges == NULL)
	{
		return;
	}

	CBbDataRange *pRange = (CBbDataRange*)m_pRanges->GetHead();

	if (pRange == NULL)
	{
		return;
	}

	if (m_pFormatTextBuffer != NULL)
	{
		m_pFormatTextBuffer->InitBuffer(pRange->m_strValue);
	}
}

DWORD CByteBlock::RunScript()
{
	if (m_pScript == NULL)
	{
		return 0;
	}

	m_pScript->Run();

	if (m_pScript->m_dwReturn == 0)
	{// ����ű��������
		FreeBuffer();
		return PpProduceError();
	}

	return 0;
}

