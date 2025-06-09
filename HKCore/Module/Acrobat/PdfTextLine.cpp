//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfTextLine.cpp  CPdfTextLine


#include "stdafx.h"
#include "PdfTextLine.h"
#include "../MemBuffer/BufferBase.h"

CPdfTextLine::CPdfTextLine()
{
	m_pBeginPos = NULL;
	m_pEndPos = NULL;
}

CPdfTextLine::CPdfTextLine(char *pszLine)
{
	m_pBeginPos = pszLine;
	m_pEndPos = pszLine + strlen(pszLine);
}

CPdfTextLine::~CPdfTextLine()
{
}


void CPdfTextLine::FormatBuffer(char *pBuffBegin,char *pBuffEnd,char ch,char chReplace)
{
	//��ʽ��
	char *pTemp = pBuffBegin;
	char *p = NULL;

	while(pTemp<=pBuffEnd)
	{
		if (*pTemp == ch)
		{
			if (pTemp > pBuffBegin && pTemp < pBuffEnd - 1)
			{
				//2021.1.1 10:10  �Ƿ�Ϊʱ���ʽ  ����ô�򵥴��� lijunqing  2021-5-30
				if ( isdigit(*(pTemp-1)) &&  isdigit(*(pTemp+1)) )
				{
					p = pTemp + 1;

					while (isdigit(*p))
					{
						p++;
					}

					if (*p ==':')
					{
						pTemp++;
						continue;
					}
				}

				*pTemp = chReplace;
			}
		}

		pTemp++;
	}
}

void CPdfTextLine::Formart()
{
	FormatBuffer(m_pBeginPos, m_pEndPos, '\t', 0);
	FormatBuffer(m_pBeginPos, m_pEndPos, ' ', 0);
	char *pString = m_pBeginPos;
	CPdfTextData *pData = NULL;
	pString = GetString(pString, m_pEndPos);

	while (pString != NULL)
	{
		pData = new CPdfTextData(pString);
		AddNewChild(pData);
		pString = NextString(pString, m_pEndPos);
	}
}

