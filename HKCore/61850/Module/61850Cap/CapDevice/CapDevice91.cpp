//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDevice91.cpp  CCapDevice91


#include "stdafx.h"
#include "CapDevice91.h"

CCapDevice91::CCapDevice91()
{
	//��ʼ������
//	m_nPriority = 0;
	m_dwVersion = 1;
//	m_dwAppID = 0;
	m_dwVID = 0;
	m_dwDataSet = 0;
	m_nAsduNum = 1;
	m_dwVersion = 1;
	m_dwLNName = 0;
	m_dwLDName = 0;
	m_dwStateWord = 0;
	m_dwINomPh = 1200;
	m_dwINomNeutral =100;
	m_dwUNomPh = 110;
	m_dwDelayTime = 0;
	m_dwSmpCnt = 0;

	//��ʼ����Ա����

}

CCapDevice91::~CCapDevice91()
{
}
