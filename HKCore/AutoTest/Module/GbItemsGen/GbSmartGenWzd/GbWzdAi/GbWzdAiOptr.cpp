#include "StdAfx.h"
#include "GbWzdAiOptr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//And
CGbAiOptrAnd::CGbAiOptrAnd(void)
{
	m_strName = _T("And");
	m_strID= _T("And");
}

CGbAiOptrAnd::~CGbAiOptrAnd(void)
{
}

CBaseObject* CGbAiOptrAnd::Clone()
{
	CGbAiOptrAnd* pGbWzdAiDataOptr = new CGbAiOptrAnd();
	Copy(pGbWzdAiDataOptr);

	return pGbWzdAiDataOptr;
}

DWORD CGbAiOptrAnd::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	//��������ÿ�����󣬴����Ч�ʽǶ���˵����һ��Ҫִ�������У������Ľ�
	CGbAiOptrBase::ScptCal(pXMatchObj, TRUE, pSttGuideBook);

	POS pos = GetHeadPosition();
	CGbAiOptrInterface *pScptObj = NULL;
	m_dwValue = 1;

	while (pos != NULL)
	{
		pScptObj = (CGbAiOptrInterface *)GetNext(pos);
		
		if (pScptObj->m_dwValue < 1)
		{//�в����������ģ���Ϊ0
			m_dwValue = 0;
			break;
		}
	}

	return m_dwValue;
}

//Or
CGbAiOptrOr::CGbAiOptrOr(void)
{
	m_strName = _T("Or");
	m_strID= _T("Or");
}

CGbAiOptrOr::~CGbAiOptrOr(void)
{
}

CBaseObject* CGbAiOptrOr::Clone()
{
	CGbAiOptrOr* pGbWzdAiDataOptr = new CGbAiOptrOr();
	Copy(pGbWzdAiDataOptr);

	return pGbWzdAiDataOptr;
}


DWORD CGbAiOptrOr::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	//��������ÿ�����󣬴����Ч�ʽǶ���˵�������������ģ������أ������Ľ�
	CGbAiOptrBase::ScptCal(pXMatchObj, TRUE, pSttGuideBook);

	POS pos = GetHeadPosition();
	CGbAiOptrInterface *pScptObj = NULL;
	m_dwValue = 0;

	while (pos != NULL)
	{
		pScptObj = (CGbAiOptrInterface *)GetNext(pos);

		if (pScptObj->m_dwValue >= 1)
		{
			m_dwValue = 1;
			break;
		}
	}

	return m_dwValue;
}


//Not
CGbAiOptrNot::CGbAiOptrNot(void)
{
	m_strName = _T("Not");
	m_strID= _T("Not");
}

CGbAiOptrNot::~CGbAiOptrNot(void)
{
}

CBaseObject* CGbAiOptrNot::Clone()
{
	CGbAiOptrNot* pGbWzdAiDataOptr = new CGbAiOptrNot();
	Copy(pGbWzdAiDataOptr);

	return pGbWzdAiDataOptr;
}


DWORD CGbAiOptrNot::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	CGbAiOptrBase::ScptCal(pXMatchObj, TRUE, pSttGuideBook);

	POS pos = GetHeadPosition();
	CGbAiOptrInterface *pScptObj = NULL;
	m_dwValue = 0;

	while (pos != NULL)
	{
		pScptObj = (CGbAiOptrInterface *)GetNext(pos);

		if (pScptObj->m_dwValue >= 1)
		{
			m_dwValue = 1;
			break;
		}
	}

	return m_dwValue;
}

