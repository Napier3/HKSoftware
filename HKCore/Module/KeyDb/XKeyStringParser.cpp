//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XKeyBase.cpp  CXKeyBase


#include "stdafx.h"
#include "XKeyStringParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct xkey_number_pick
{
	long nBeginPos;
	long nEndPos;
	long nArabic;
	CString *pStringRef;
}XKEY_NUMBER_PICK, *PXKEY_NUMBER_PICK;


BOOL xkey_IsCharNumChar(wchar_t xChar)
{
	if ('0' <= xChar && xChar <= '9')
	{
		return TRUE;
	}

	return FALSE;
}

BOOL xchar_CanOffset(wchar_t xChar);

//返回一个字符
//非UNICODE模式下，区分ASCII和汉字，返回wchar_t
wchar_t xkey_get_x_char(const CString &strText, long nPos)
{
#ifdef _UNICODE
	return strText.GetAt(nPos);
#else
	wchar_t wch, wch2;

#ifdef _PSX_IDE_QT_
	if (strText.GetLength() > nPos)
	{
	wch = strText.GetAt(nPos);
	}
	else
	{
		wch = 0;
	}
#else
	wch = (unsigned char)strText.GetAt(nPos);
	
	if (wch > 128 )
	{
		wch2 =  (unsigned char)strText.GetAt(nPos + 1);
		//wch = wch | (wch2 << 8);
		wch = wch2 | (wch << 8); //lijunqing 2022-6-27  高字节在前，低字节在后
	}
#endif

	return wch;
#endif
}

//判断是否为数字
long xkey_is_wchar_arab(const CString &strText, long &nPos)
{
	long nArabic = -1;
	long nIndex = 0;
	wchar_t wch = xkey_get_x_char(strText, nPos);

	if ('0' <= wch && wch <= '9')
	{
		nArabic = wch - '0';

#ifdef _UNICODE
		nPos += 2;
#else
		nPos++;
#endif
	}

	return nArabic;
}


long xkey_is_wchar_chn(const CString &strText, long &nPos)
{
	//00000000h: C1E3 D2BB B6FE C8FD CBC4 CEE5 C1F9 C6DF ; 零一二三四五六七
	//00000010h: B0CB BEC5 CAAE B0D9                         ; 八九十百
	
	// //lijunqing 2022-6-27  高字节在前，低字节在后
	//static wchar_t g_ChnNum[20] = {0xE3C1, 0XBBD2, 0XFEB6, 0XFDC8, 0XC4CB, 0XCEE5, 0XF9C1, 0XDFC6, 0XCBB0, 0XC5BE, 0XAECA, 0XD9B0 };
	//static wchar_t g_ChnNum[20] = {'零', '一', '二', '三', '四', '五', '六', '七', '八', '九', '十', '百' };
	wchar_t  *pChnNum = CXCharNumConfig::GetChn(); 

	long nArabic = -1;
	long nIndex = 0;
	wchar_t wch = xkey_get_x_char(strText, nPos);

	for (nIndex= 0; nIndex<12; nIndex++)
	{
		if (wch == pChnNum[nIndex])
		{
			nArabic = nIndex;
			break;
		}
	}

	if (nArabic >= 0)
	{
		if (nArabic == 10)
		{
			nArabic = 10;
		}
		else if (nArabic == 11)
		{
			nArabic = 100;
		}

#ifdef _UNICODE
		nPos++;
#else
		nPos += 2;
#endif
	}

	return nArabic;
}

long xkey_is_wchar_roma(const CString &strText, long &nPos)
{
	wchar_t* pRomaNum = CXCharNumConfig::GetRoma();
	long nArabic = -1;
	long nIndex = 0;
	wchar_t wch = xkey_get_x_char(strText, nPos);

	for (nIndex= 0; nIndex<10; nIndex++)
	{
		if (wch == pRomaNum[nIndex])
		{
			nArabic = nIndex+1;

#ifdef _UNICODE
			nPos++;
#else
			nPos += 2;
#endif

			break;
		}
	}

	return nArabic;
}

long xkey_is_wchar_roma_err(const CString &strText, long &nPos)
{
	static const wchar_t g_RomaNumErr[10][5]      = {L"III", L"II",  L"IV", L"IX",L"I", L"VIII", L"VII", L"VI", L"V", L"X"};
	static const long      g_RomaNumErrLen[10]     = {3,      2,       2,       2,       1,     4,       3,        2,      1,      1};
	static const long      g_RomaNumErrVal[10]      = {3,      2,       4,       9,       1,     8,       7,        6,       5,     10};
	long nArabic = -1;
	long nIndex = 0;
	wchar_t wch = xkey_get_x_char(strText, nPos);
	long nCharIndex = 0;
	BOOL bMatch = TRUE;

	for (nIndex= 0; nIndex<10; nIndex++)
	{
		bMatch = TRUE;

		for (nCharIndex=0; nCharIndex < g_RomaNumErrLen[nIndex]; nCharIndex++)
		{
			wch = xkey_get_x_char(strText, nPos+nCharIndex);

			if (wch != g_RomaNumErr[nIndex][nCharIndex])
			{
				bMatch = FALSE;
				break;
			}
		}
		
		if (bMatch)
		{
			nArabic = g_RomaNumErrVal[nIndex];
			nPos += g_RomaNumErrLen[nIndex];
			break;
		}
	}

	return nArabic;
}

//获得阿拉伯数字字符串代表的数字
long xkey_get_arabic_from_arabic(const CString &strText, long nBeginPos, long nEndPos, PXKEY_NUMBER_PICK pXkeyNumPick)
{
	long nPos = nBeginPos;
	long nArabic = xkey_is_wchar_arab(strText, nPos);

	if (nArabic  < 0 )
	{
		return nArabic;
	}

	pXkeyNumPick->nArabic = nArabic;

	while (nPos <= nEndPos)
	{
		nArabic = xkey_is_wchar_arab(strText, nPos);

		if (nArabic < 0)
		{
			break;
		}

		pXkeyNumPick->nArabic *= 10;
		pXkeyNumPick->nArabic += nArabic;
	}

	return pXkeyNumPick->nArabic;
}

//获得中文数字字符代表的数字
long xkey_get_arabic_from_chn(const CString &strText, long &nPos)
{
	long nArabic = xkey_is_wchar_chn(strText, nPos);

	if (nArabic  < 0 )
	{
		return nArabic;
	}

	if (nArabic >= 10)
	{
		return nArabic;
	}

	long nArabic2 = xkey_is_wchar_chn(strText, nPos);

	if (nArabic2 < 0)
	{
		return nArabic;
	}
	else
	{
		return nArabic * nArabic2;
	}
}

//获得中文数字字符串代表的数字
long xkey_get_arabic_from_chn(const CString &strText, long nBeginPos, long nEndPos, PXKEY_NUMBER_PICK pXkeyNumPick)
{
	long nPos = nBeginPos;
	long nArabic = xkey_get_arabic_from_chn(strText, nPos);

	if (nArabic  < 0 )
	{
		return nArabic;
	}

	pXkeyNumPick->nArabic = nArabic;

	while (nPos <= nEndPos)
	{
		nArabic = xkey_get_arabic_from_chn(strText, nPos);

		if (nArabic < 0)
		{
			break;
		}

		pXkeyNumPick->nArabic += nArabic;
	}
	
	return pXkeyNumPick->nArabic;
}

//获得罗马数字字符串代表的数字
long xkey_get_arabic_from_roma(const CString &strText, long nBeginPos, long nEndPos, PXKEY_NUMBER_PICK pXkeyNumPick)
{
	long nPos = nBeginPos;
	long nArabic = xkey_is_wchar_roma(strText, nPos);

	if (nArabic  < 0 )
	{
		return nArabic;
	}

	pXkeyNumPick->nArabic = nArabic;

	return pXkeyNumPick->nArabic;
}

//获得错误罗马数字字符串代表的数字
long xkey_get_arabic_from_roma_err(const CString &strText, long nBeginPos, long nEndPos, PXKEY_NUMBER_PICK pXkeyNumPick)
{
	long nPos = nBeginPos;
	long nArabic = xkey_is_wchar_roma_err(strText, nPos);

	if (nArabic  < 0 )
	{
		return nArabic;
	}

	pXkeyNumPick->nArabic = nArabic;

	return pXkeyNumPick->nArabic;
}


BOOL xchar_CanOffset(wchar_t xChar)
{
    static const wchar_t g_ChnOffset[20] = {'号'};
	long nIndex = 0;

	for (nIndex=0; nIndex<1; nIndex++)
	{
		if (xChar == g_ChnOffset[nIndex])
		{
			return TRUE;
		}
	}

	return FALSE;
}

long xchar_Offset(const CString &strText, long &nPos)
{
	wchar_t wch = xkey_get_x_char(strText, nPos);

	if (xchar_CanOffset(wch))
	{
#ifdef _UNICODE
		nPos++;
#else
		nPos += 2;
#endif
		return 1;
	}
	else
	{
		return 0;
	}
}

//获得数字字符串代表的数字
long CXKeyStringParser::xkey_get_arabic_number(const CString &strText, long nBeginPos, long nEndPos)
{
	if (nEndPos < nBeginPos)
	{
		return 0;
	}

	long nPos = nBeginPos;
	long nArabic = -1;
	long nArabicCal =0;
	CXKeyStringNumberBlock *pNumBlock = NULL;
	long nPosPrev = nPos;

	while (nPos <= nEndPos)
	{
		nPosPrev = nPos;

		//错误罗马数字
		nArabic = xkey_is_wchar_roma_err(strText, nPos);

		if (nArabic >= 0)
		{
			nArabicCal *=10;
			nArabicCal += nArabic;
			xchar_Offset(strText, nPos);
			//AddNumberBlock(nPosPrev, nPos, nArabic);
			continue;
		}

		//罗马数字
		nArabic = xkey_is_wchar_roma(strText, nPos);

		if (nArabic >= 0)
		{
			nArabicCal *=10;
			nArabicCal += nArabic;
			xchar_Offset(strText, nPos);
			//AddNumberBlock(nPosPrev, nPos, nArabic);
			continue;
		}

		//中文数字
		nArabic = xkey_is_wchar_chn(strText, nPos);

		if (nArabic >= 0)
		{
			xchar_Offset(strText, nPos);
			nArabicCal *=10;
			nArabicCal += nArabic;
			//AddNumberBlock(nPosPrev, nPos, nArabic);
			continue;
		}

		//数字
		nArabic = xkey_is_wchar_arab(strText, nPos);

		if (nArabic >= 0)
		{
			xchar_Offset(strText, nPos);
			nArabicCal *=10;
			nArabicCal += nArabic;
			//AddNumberBlock(nPosPrev, nPos, nArabic);
			continue;
		}

		if (nArabic < 0 && nArabicCal > 0)
		{
			AddNumberBlock(nPosPrev, nPos-1, nArabicCal);
			nArabicCal = 0;
		}

		nPos++;
	}


	if (nArabicCal > 0)
	{
		AddNumberBlock(nPosPrev, nPos-1, nArabicCal);
		nArabicCal = 0;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//CStringParser
CXKeyStringBlock::CXKeyStringBlock()
{
	m_nBeginPos=-1;
	m_nEndPos=-1;
	m_pKeyRef=NULL;
	m_nType=-1;
	m_nNumber=-1;
	m_nSubscriptUsed=0;
}

CXKeyStringBlock::~CXKeyStringBlock()
{
}

void CXKeyStringBlock::SetKeyArrayIndex(long nNumber)
{
	ASSERT (m_pKeyRef != NULL);
	m_pKeyRef->m_nArrayIndex = nNumber;
}

BOOL CXKeyStringBlock::IsSubBlock(CXKeyStringBlock *pBlock)
{
	if (pBlock->m_nBeginPos >= m_nBeginPos && pBlock->m_nEndPos <= m_nEndPos
		&& pBlock->GetLength() < GetLength())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

long CXKeyStringBlock::GetLength()
{
	return m_nEndPos - m_nBeginPos + 1;
}

BOOL CXKeyStringBlock::IsArrayKey()
{
	if (m_pKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pKeyRef->IsArrayKey();
}

BOOL CXKeyStringBlock::IsArrayTypeBefore()
{
	if (m_pKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pKeyRef->IsArrayTypeBefore();
}

BOOL CXKeyStringBlock::IsArrayTypeAfter()
{
	if (m_pKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pKeyRef->IsArrayTypeAfter();
}

BOOL CXKeyStringBlock::IsArrayTypeAll()
{
	if (m_pKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pKeyRef->IsArrayTypeAll();
}


CXKeyStringNumberBlock::CXKeyStringNumberBlock()
{
	m_nBeginPos = -1;
	m_nEndPos = -1;
	m_nNumber = -1;
}

CXKeyStringNumberBlock::CXKeyStringNumberBlock(long  nBeginPos, long  nEndPos, long nNumber)
{
	m_nBeginPos = nBeginPos;
	m_nEndPos = nEndPos;
	m_nNumber = nNumber;
}

CXKeyStringNumberBlock::~CXKeyStringNumberBlock()
{
	m_nBeginPos = -1;
	m_nEndPos = -1;
	m_nNumber = -1;
}

//////////////////////////////////////////////////////////////////////////
//
bool CXKeyStringParser::g_bRemoveSubKeys = 1;

CXKeyStringParser::CXKeyStringParser()
{
}

CXKeyStringParser::~CXKeyStringParser()
{
}

void CXKeyStringParser::QueryKey(const CString &strText, CXKeyBase *pXKey, CXKeyMatchRefList *pListKeys)
{
	CXKeyMatchRef *pXKeyRef = NULL;
	long nPos = 0;
	CXKeyStringBlock *pStringKeyBlock = NULL;

	while (TRUE)
	{
		nPos = xkey_find_string_pos(strText, pXKey->m_strName, nPos);

		if (nPos < 0)//zhouhj 20220217 将<=改为 <  ,在等于0时代表从第一个字符开始相同的
		{
			break;
		}

		if (pXKeyRef == NULL)
		{
			pXKeyRef = pListKeys->AddKey(pXKey);
		}

		pStringKeyBlock=new CXKeyStringBlock;
		pStringKeyBlock->m_pKeyRef=pXKeyRef;
		pStringKeyBlock->m_nBeginPos=nPos;
		nPos += pXKey->m_strName.GetLength();
		pStringKeyBlock->m_nEndPos=nPos-1;
		pStringKeyBlock->m_nType=0;
		AddTail(pStringKeyBlock);
	}
}

void CXKeyStringParser::ParseKey(CXKeyMatchRef *pXKeyRef,  const CString &strText)
{
	long nPos = 0;
	CXKeyStringBlock *pStringKeyBlock = NULL;

	while (TRUE)
	{
		nPos = xkey_find_string_pos(strText, pXKeyRef->m_pXKeyRef->m_strName, nPos);

		if (nPos < 0)
		{
			break;
		}

		pStringKeyBlock=new CXKeyStringBlock;
		pStringKeyBlock->m_pKeyRef=pXKeyRef;
		pStringKeyBlock->m_nBeginPos=nPos;
		nPos += pXKeyRef->m_pXKeyRef->m_strName.GetLength();
		pStringKeyBlock->m_nEndPos=nPos-1;
		pStringKeyBlock->m_nType=0;
		AddTail(pStringKeyBlock);
	}
}

void CXKeyStringParser::ParseKeys(CXKeyMatchRefList *pListKeys,  const CString &strText)
{
	CXKeyMatchRef *pXKeyRef;
	POS  KeysPos=pListKeys->GetHeadPosition();

	while (KeysPos != NULL)
	{
		pXKeyRef = (CXKeyMatchRef*)pListKeys->GetNext(KeysPos);
		ParseKey(pXKeyRef, strText);
	}
}

void CXKeyStringParser::SortByPosition()
{
	POS pos = GetHeadPosition();
	CXKeyStringBlock *p = NULL;
	CXKeyStringBlock *pSort = NULL;
	CXKeyStringParser oListTemp;

	while (pos != NULL)
	{
		p = (CXKeyStringBlock *)GetNext(pos);
		POS posSort = oListTemp.GetHeadPosition();
		BOOL bSort = FALSE;

		if (posSort == NULL)
		{
			oListTemp.AddHead(p);
			continue;
		}

		while (posSort != NULL)
		{
			pSort = (CXKeyStringBlock *)oListTemp.GetAt(posSort);

			if (p->m_nBeginPos <= pSort->m_nBeginPos)
			{
				oListTemp.InsertBefore(posSort, p);
				bSort = TRUE;
				break;
			}

			oListTemp.GetNext(posSort);
		}

		if (!bSort)
		{
			oListTemp.AddTail(p);
		}
	}

	RemoveAll();
	POS posTemp = oListTemp.GetHeadPosition();

	while (posTemp != NULL)
	{
		p = (CXKeyStringBlock *)GetNext(posTemp);
		AddTail(p);
	}

	oListTemp.RemoveAll();
}


void CXKeyStringParser::RemoveSubBlock()
{
	POS pos = GetHeadPosition();
	POS posPrev = pos;
	CXKeyStringBlock *pBlock = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		pBlock = (CXKeyStringBlock *)GetNext(pos);

		if (IsSubBlock(pBlock))
		{
			Delete(pBlock);
		}
	}
}

BOOL CXKeyStringParser::IsSubBlock(CXKeyStringBlock *pStringKeyBlock)
{
	POS pos = GetHeadPosition();
	CXKeyStringBlock *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p ==pStringKeyBlock)
		{
			continue;
		}

		if (p->IsSubBlock(pStringKeyBlock))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CXKeyStringParser::InitNumberBlocks(const CString &strText)
{
	POS pos = GetHeadPosition();
	CXKeyStringBlock *pBlock = NULL, *pPrev = NULL;
	CXKeyStringBlock *pNew = NULL;

	if (pos == NULL)
	{
		return;
	}

	long nLen = strText.GetLength();
	pBlock = (CXKeyStringBlock*)GetNext(pos);
	pPrev = pBlock;

	if (pBlock->m_nBeginPos > 0)
	{
		xkey_get_arabic_number(strText, 0, pBlock->m_nBeginPos - 1);
	}

	while (pos != NULL)
	{
		pPrev = pBlock;
		pBlock = (CXKeyStringBlock*)GetNext(pos);

		if (pBlock->m_nBeginPos == pPrev->m_nEndPos + 1)
		{
			continue;
		}

		xkey_get_arabic_number(strText, pPrev->m_nEndPos + 1, pBlock->m_nBeginPos - 1);
	}

	if (pBlock->m_nEndPos < nLen-1)
	{
		xkey_get_arabic_number(strText, pPrev->m_nEndPos + 1, nLen - 1);
	}
}

void CXKeyStringParser::AddNumberBlock(long nBeginPos, long nEndPos, long nNumber)
{
	CXKeyStringBlock *pNew = new CXKeyStringBlock();
	pNew->m_nBeginPos = nBeginPos;
	pNew->m_nEndPos = nEndPos-1;
	pNew->m_nNumber = nNumber;
	AddTail(pNew);
}

// long CStringParser::GetNumber(const CString &strText, long nBeginPos, long nEndPos, CString &strNumber)
// {
// 	
// }

BOOL CXKeyStringParser::SetArrayIndex(CXKeyStringBlock *pNumber, CXKeyStringBlock *pKey)
{
	if (pNumber == NULL)
	{
		return FALSE;
	}

	if (pNumber->IsNumber() && pNumber->IsNumberNoUse())
	{
		pKey->SetKeyArrayIndex(pNumber->m_nNumber);
		pNumber->SetNumberUse(TRUE);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CXKeyStringParser::InitArrayKeyIndex()
{
	POS pos = GetHeadPosition();
	POS posPrev = pos;
	CXKeyStringBlock *pCurr = NULL, *pPrev = NULL;
	CXKeyStringBlock *pNumber = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		pPrev = pCurr;
		pCurr = (CXKeyStringBlock *)GetNext(pos);

		//数字
		if (pCurr->IsNumber())
		{
			continue;
		}

		if (!pCurr->IsArrayKey())
		{
			continue;
		}

		if (pCurr->IsArrayTypeBefore())
		{
			SetArrayIndex(pPrev, pCurr);
			continue;
		}

		if (pCurr->IsArrayTypeAfter())
		{
			if (pos != NULL)
			{
				pNumber = (CXKeyStringBlock *)GetAt(pos);
				SetArrayIndex(pNumber, pCurr);
			}
			continue;
		}

		//if (pCurr->IsArrayTypeBefore())
		if (pCurr->IsArrayTypeAll()) //xujinqiang 2019/12/12 修改，原代码应该是写错了
		{
			if (!SetArrayIndex(pPrev, pCurr))
			{
				if (pos != NULL)
				{
					pNumber = (CXKeyStringBlock *)GetAt(pos);
					SetArrayIndex(pNumber, pCurr);
				}
			}

			continue;
		}
	}
}

void CXKeyStringParser::Parser(const CString &strText, CXKeyMatchRefList *pListKeys)
{
	//ParseKeys(pListKeys, strText);
	SortByPosition();
	if (g_bRemoveSubKeys)
	{
	RemoveSubBlock();
	}

	InitNumberBlocks(strText);
	//ParseGapBlockNumber(strText);
	SortByPosition();
	InitArrayKeyIndex();

	if (g_bRemoveSubKeys)
	{
	RemoveSubKeys(pListKeys);
	}

	AddNumberXKeys(pListKeys);
}

void CXKeyStringParser::RemoveSubKeys(CXKeyMatchRefList *pListKeys)
{
	POS pos = pListKeys->GetHeadPosition();
	CXKeyMatchRef *pXKeyRef;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		pXKeyRef = (CXKeyMatchRef*)pListKeys->GetNext(pos);

		if (FindByXKeyMatchRef(pXKeyRef) == NULL)
		{
			pListKeys->DeleteAt(posPrev);
		}
	}
}

CXKeyStringBlock* CXKeyStringParser::FindByXKeyMatchRef(CXKeyMatchRef *pXKeyRef)
{
	POS pos = GetHeadPosition();
	CXKeyStringBlock *p = NULL;

	while (pos != NULL)
	{
		p = (CXKeyStringBlock *)GetNext(pos);

		if (p->m_pKeyRef == pXKeyRef)
		{
			return p;
		}
	}

	return NULL;
}

void CXKeyStringParser::AddNumberXKeys(CXKeyMatchRefList *pListKeys)
{
	POS pos = GetHeadPosition();
	CXKeyStringBlock *p = NULL;

	while (pos != NULL)
	{
		p = (CXKeyStringBlock *)GetNext(pos);

		if (p->m_pKeyRef == NULL)
		{
			if (p->IsNumberNoUse())
			{
				CXKeyMatchRef *pNew = new CXKeyMatchRef();
				pNew->m_nArrayIndex = p->m_nNumber;
				pListKeys->AddTail(pNew);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CXCharNumConfig
#include "../API/GlobalConfigApi.h"

CXCharNumConfig* CXCharNumConfig::g_pXCharNumConfig = NULL;
long CXCharNumConfig::g_nXCharNumConfigRef = 0;

void CXCharNumConfig::Create()
{
	g_nXCharNumConfigRef++;

	if (g_nXCharNumConfigRef == 1)
	{
		g_pXCharNumConfig = new CXCharNumConfig();
		g_pXCharNumConfig->OpenXKeyNumConfigFile();
	}
}

void CXCharNumConfig::Release()
{
	g_nXCharNumConfigRef--;

	if (g_nXCharNumConfigRef == 0)
	{
		delete g_pXCharNumConfig;
		g_pXCharNumConfig = NULL;
	}
}

wchar_t* CXCharNumConfig::GetRoma()
{
	return g_pXCharNumConfig->m_strRomaKey;
}

wchar_t* CXCharNumConfig::GetChn()
{
	return g_pXCharNumConfig->m_strChnKey;
}

CXCharNumConfig::CXCharNumConfig()
{
#ifdef _PSX_IDE_QT_
#ifdef _PSX_QT_LINUX_    //zhouhj  2024.3.7 Linux下不支持特殊字符，会导致段错误
    memset(m_strRomaKey,0,40);
    memset(m_strChnKey,0,40);
#else
    wcscpy(m_strRomaKey, (wchar_t*)"ⅠⅡⅢⅣⅤⅥⅦⅧⅨⅩ");
    wcscpy(m_strChnKey, (wchar_t*)"零一二三四五六七八九十百");
#endif
#else
	wcscpy(m_strRomaKey, L"ⅠⅡⅢⅣⅤⅥⅦⅧⅨⅩ");
	wcscpy(m_strChnKey, L"零一二三四五六七八九十百");
#endif
}

CXCharNumConfig::~CXCharNumConfig()
{

}

void CXCharNumConfig::InitAfterRead()
{
	CXKeyBase *p = (CXKeyBase*)FindByID(_T("roma"));

	if (p != NULL)
	{
		CString_to_wchar(p->m_strName, m_strRomaKey);
	}

	p = (CXKeyBase*)FindByID(_T("chn"));

	if (p != NULL)
	{
		CString_to_wchar(p->m_strName, m_strChnKey);
	}
}

void CXCharNumConfig::OpenXKeyNumConfigFile()
{
	CString strFile;
	strFile = _P_GetCommonLibraryPath();
	strFile += _T("XKeyNumConfig.xml");

	OpenXmlFile(strFile, CKeyDbXmlRWKeys::CXKeyMngrKey(), CKeyDbXmlRWKeys::g_pXmlKeys);
}

