//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PdfTextData.cpp  CPdfTextData


#include "stdafx.h"
#include "PdfTextData.h"

CPdfTextData::CPdfTextData()
{
	//初始化属性

	//初始化成员变量
}

CPdfTextData::CPdfTextData(char *pszData)
{
	m_strName = pszData;
}

CPdfTextData::~CPdfTextData()
{
}

void CPdfTextData::TrimRight()
{
	if (m_strName.Right(1) == _T(":"))
	{
		m_strName = m_strName.Left(m_strName.GetLength() - 1);
		return;
	}

#ifdef _UNICODE
	if (m_strName.Right(1) == _T("："))
	{
		m_strName = m_strName.Left(m_strName.GetLength() - 1);
	}
#else
	if (m_strName.Right(2) == _T("："))
	{
		m_strName = m_strName.Left(m_strName.GetLength() - 2);
	}
#endif
}
