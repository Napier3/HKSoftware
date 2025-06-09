//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StateWord.cpp  CIecCfg91StateWord


#include "stdafx.h"
#include "IecCfg91StateWord.h"

CIecCfg91StateWord::CIecCfg91StateWord()
{
	//初始化属性

	//初始化成员变量
}

CIecCfg91StateWord::~CIecCfg91StateWord()
{
}

long CIecCfg91StateWord::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfg91StateWord::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CIecCfg91StateWord::InitAfterRead()
{
}

BOOL CIecCfg91StateWord::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfg91StateWord *p = (CIecCfg91StateWord*)pObj;

	return TRUE;
}

BOOL CIecCfg91StateWord::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg91StateWord *p = (CIecCfg91StateWord*)pDest;

	return TRUE;
}

CBaseObject* CIecCfg91StateWord::Clone()
{
	CIecCfg91StateWord *p = new CIecCfg91StateWord();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg91StateWord::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfg91StateWordBitKey)
	{
		pNew = new CIecCfg91StateWordBit();
	}

	return pNew;
}

CExBaseObject* CIecCfg91StateWord::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFG91STATEWORDBIT)
	{
		pNew = new CIecCfg91StateWordBit();
	}

	return pNew;
}

void CIecCfg91StateWord::SetWord(DWORD dwStateWord)
{
	long nIndex = 0;
	long nVal = 0;
	CIecCfg91StateWordBit *pBit = NULL;
	ASSERT (GetCount() == 32);

	for (nIndex=0;nIndex<32; nIndex++)
	{
		nVal = dwStateWord & 0x00000001;
		pBit = (CIecCfg91StateWordBit *)GetAtIndex(nIndex);

		if (pBit == NULL)
		{
			break;
		}

		pBit->m_strValue.Format(_T("%d"), nVal);
		dwStateWord = dwStateWord >> 1;
	}
}

DWORD CIecCfg91StateWord::GetWord()
{
	DWORD dwStateWord = 0;
	ASSERT (GetCount() == 32);
	CIecCfg91StateWordBit *pBit = NULL;
	POS pos = GetHeadPosition();
	long nIndex = 0;
	DWORD dwVal = 0;

	while (pos != NULL)
	{
		pBit = (CIecCfg91StateWordBit *)GetNext(pos);
		dwVal = CString_To_long(pBit->m_strValue);
		dwStateWord += ((dwVal & 0x01) << nIndex);
		nIndex++;
	}

	return dwStateWord;
}

