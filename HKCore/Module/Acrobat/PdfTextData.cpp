//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PdfTextData.cpp  CPdfTextData


#include "stdafx.h"
#include "PdfTextData.h"

CPdfTextData::CPdfTextData()
{
	//��ʼ������

	//��ʼ����Ա����
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
	if (m_strName.Right(1) == _T("��"))
	{
		m_strName = m_strName.Left(m_strName.GetLength() - 1);
	}
#else
	if (m_strName.Right(2) == _T("��"))
	{
		m_strName = m_strName.Left(m_strName.GetLength() - 2);
	}
#endif
}
