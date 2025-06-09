//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ValuesParse.cpp  CValuesParse


#include "stdafx.h"
#include "ValuesParse.h"

CValuesParse::CValuesParse()
{
	//初始化属性
	InitFlags();

	//初始化成员变量
}

CValuesParse::CValuesParse(const CString &strText)
{
	InitFlags();
	Parse(strText);
}

CValuesParse::~CValuesParse()
{
}

void CValuesParse::InitFlags()
{
	m_charValFlag = ',';
	m_charLeftFlag = '(';
	m_charRightFlag = ')';
}

void CValuesParse::Parse(const CString &strText)
{
	if (strText.GetLength() < 3)
	{
		return;
	}

	char *pszTextBuffer = NULL;

	CString_to_char(strText, &pszTextBuffer);
	char *pCurr = pszTextBuffer;
	CValue *pNew = NULL;
	char* pLeft_ID = NULL, *pRight_ID = NULL, *pLeft_Val = NULL;

	while (*pCurr != 0)
	{
		switch(*pCurr)
		{
		case '(':
			pCurr++;
			pLeft_ID = pCurr;
			break;

		case ')':
			*pCurr = 0;
			if (pLeft_ID != NULL && pLeft_Val != NULL && pRight_ID != NULL)
			{
				pNew = new CValue();
				pNew->m_strID = pLeft_ID;
				pNew->m_strValue = pLeft_Val;
				AddNewChild(pNew);
			}

			pLeft_ID = NULL;
			pRight_ID = NULL;
			pLeft_Val = NULL;
			pCurr++;
			break;

		case ',':
			if (pLeft_Val == NULL)
			{
				pRight_ID = pCurr-1;
				*pCurr = 0;
				pCurr++;
				pLeft_Val = pCurr;
			}
			else
			{
				pCurr++;
			}
			break;

		default:
			pCurr++;
			break;
		}
	}

	delete pszTextBuffer;
}

void CValuesParse::Skip(char **ppPos)
{
	char *pCurr = *ppPos;

	while (*pCurr == VK_SPACE || *pCurr == VK_TAB)
	{
		pCurr++;

		if (*pCurr == 0)
		{
			break;
		}
	}

	*ppPos = pCurr;
}

