//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementTestPoint.cpp  CCharElementTestPoint


#include "stdafx.h"
#include "CharElementTestPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL CalIOwnDefXYExpression(const CString &strExpress, double &dValue)
{
	if (strExpress.GetLength() == 0)
	{
		return FALSE;
	}

	CEpExpression oEpExp;

	if (oEpExp.ChangeEpExpression(strExpress) == -1)
	{
#ifndef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("���ʽ��%s�� ����")*/
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("���ʽ��%s�� ����")
#endif
			, strExpress.GetString());
		return FALSE;
	}

	oEpExp.Value(dValue);

	return TRUE;
}

CCharElementTestPoint::CCharElementTestPoint()
{
	//��ʼ������
	m_strX = _T("");
	m_strY = _T("");
}

CCharElementTestPoint::~CCharElementTestPoint()
{
}

void CCharElementTestPoint::InitAfterRead()
{
}

BOOL CCharElementTestPoint::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementTestPoint *p = (CCharElementTestPoint*)pObj;

	if(m_strX != p->m_strX)
	{
		return FALSE;
	}

	if(m_strY != p->m_strY)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementTestPoint::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementTestPoint *p = (CCharElementTestPoint*)pDest;

	p->m_strX = m_strX;
	p->m_strY = m_strY;
	p->m_fX = m_fX;
	p->m_fY = m_fY;

	return TRUE;
}

CBaseObject* CCharElementTestPoint::Clone()
{
	CCharElementTestPoint *p = new CCharElementTestPoint();
	Copy(p);
	return p;
}

void CCharElementTestPoint::CalByExpression(BOOL bCalLines)
{
	//������������
	if(!CalIOwnDefXYExpression(m_strX, m_fX))
	{
		m_strX = _T("0.0");
		m_fX = 0.0;
	}

	if(!CalIOwnDefXYExpression(m_strY, m_fY))
	{
		m_strY = _T("0.0");
		m_fY = 0.0;
	}
}

CCharElementTestPoints::CCharElementTestPoints()
{
	//��ʼ������
}

CCharElementTestPoints::~CCharElementTestPoints()
{
}

void CCharElementTestPoints::InitPoints(const CString &strPoints) //����strPoints��ȡ�����ַ��������浽�����
{
	char scPoints[MAXPOINTCOUNT] = {'\0'};
	CString_to_char(strPoints, scPoints);
	const char *delim = " ,{,,}";
	char *point[MAXPOINTCOUNT] = {""};
	int nCount = 0; 
	char *pTemp = strtok(scPoints,delim);
	while(pTemp)
	{
		point[nCount] = pTemp;
		nCount++;
		pTemp=strtok(NULL,delim);
	}

	for(int i = 0;i<nCount;i=i+2)
	{
		CCharElementTestPoint *pObj = new CCharElementTestPoint;
		pObj->m_strX = point[i];
		pObj->m_strY = point[i + 1];
		AddNewChild(pObj);
	}
}

void CCharElementTestPoints::GetPointsString(CString &strPoints) //�������еĵ������ת��Ϊ�ַ���
{
	POS pos = GetHeadPosition();
	CCharElementTestPoint *pObj = NULL;

	strPoints = _T(""); //����ַ���
	while(pos!=NULL)
	{
		pObj = (CCharElementTestPoint *)GetNext(pos);
		strPoints += _T("{") + pObj->m_strX + _T(",") + pObj->m_strY + _T("}");
	}
}

void CCharElementTestPoints::CalByExpression(BOOL bCalLines)
{
	POS pos = GetHeadPosition();
	CCharElementTestPoint *pObj = NULL;

	while(pos!=NULL)
	{
		pObj = (CCharElementTestPoint *)GetNext(pos);
		pObj->CalByExpression(bCalLines);
	}
}

CCharElementTestPoint* CCharElementTestPoints::FindObj(CCharElementTestPoint *pSel)
{
	CCharElementTestPoint *pFind = NULL;
	POS pos = GetHeadPosition();
	CCharElementTestPoint *pObj = NULL;

	while(pos!=NULL)
	{
		pObj = (CCharElementTestPoint *)GetNext(pos);
		
		if((pObj->m_strX == pSel->m_strX) && (pObj->m_strY == pSel->m_strY))
		{
			pFind = pObj;
			return pFind;
		}
	}

	return pFind;
}

POS CCharElementTestPoints::GetPos(CCharElementTestPoint *pSel)
{
	POS pos = GetHeadPosition();
	POS prevPos = NULL; //pos��ǰһ��λ��
	CCharElementTestPoint *pObj = NULL;

	while(pos!=NULL)
	{
		prevPos = pos;
		pObj = (CCharElementTestPoint *)GetNext(pos);

		if(pObj == pSel)
		{
			return prevPos;
		}
	}

	return NULL;
}