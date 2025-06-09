//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementPoint.cpp  CCharElementPoint


#include "stdafx.h"
#include "CharElementPoint.h"

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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ExpressionError.GetString()/*_T("表达式【%s】 错误")*/
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("表达式【%s】 错误")
#endif
			, strExpress.GetString());
		return FALSE;
	}

	oEpExp.Value(dValue);

	return TRUE;
}

CCharElementPoint::CCharElementPoint()
{
	//初始化属性
	m_strX = _T("");
	m_strY = _T("");
	m_nZoneType = -1;
	m_nFaultType = -1;
	m_nTestState = -1;
}

CCharElementPoint::~CCharElementPoint()
{
}

void CCharElementPoint::InitAfterRead()
{
}

BOOL CCharElementPoint::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementPoint *p = (CCharElementPoint*)pObj;

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

BOOL CCharElementPoint::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementPoint *p = (CCharElementPoint*)pDest;

	p->m_strX = m_strX;
	p->m_strY = m_strY;
	p->m_fX = m_fX;
	p->m_fY = m_fY;

	return TRUE;
}

CBaseObject* CCharElementPoint::Clone()
{
	CCharElementPoint *p = new CCharElementPoint();
	Copy(p);
	return p;
}

void CCharElementPoint::CalByExpression(BOOL bCalLines)
{
	//计算自身数据
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
void CCharElementPoint::SetTestPoint(CString strIDPath, float fX, float fY, int  nFaultType, int nTestState, int  nZoneType)
{//20240822 luozibing 设置测试点参数
	m_strID = strIDPath;
	m_nZoneType = nZoneType;
	m_nFaultType = nFaultType;
	//	if ((fabs(m_fX - fX)>0.0001f) || (fabs(m_fY - fY)>0.0001f))//测试项坐标改变
	{
		m_fX = fX;
		m_fY = fY;
	}

	// 	if (nTestState == -1)
	// 	{
	// 		return;
	// 	}
	m_nTestState = nTestState;
}
long CCharElementPoint::GetXDrawElement(CXDrawList *pDrawList)
{
	CXDrawPoint *pXPoint = new CXDrawPoint();
	pXPoint->m_fX = m_fX;
	pXPoint->m_fY = m_fY;
	pXPoint->m_dwDrawStyle = 0;
	pXPoint->m_crForeColor = RGB(255, 0, 0);
	pDrawList->AddNewChild(pXPoint);
	pXPoint->m_pXDrawDataRef = this;
	return 1;
}
CCharElementPoints::CCharElementPoints()
{
	//初始化属性
}

CCharElementPoints::~CCharElementPoints()
{
}

void CCharElementPoints::InitPoints(const CString &strPoints) //根据strPoints提取坐标字符串，保存到点对象
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
		CCharElementPoint *pObj = new CCharElementPoint;
		pObj->m_strX = point[i];
		pObj->m_strY = point[i + 1];
		AddNewChild(pObj);
	}
}

void CCharElementPoints::GetPointsString(CString &strPoints) //将链表中的点的坐标转换为字符串
{
	POS pos = GetHeadPosition();
	CCharElementPoint *pObj = NULL;

	strPoints = _T(""); //清空字符串
	while(pos!=NULL)
	{
		pObj = (CCharElementPoint *)GetNext(pos);
		strPoints += _T("{") + pObj->m_strX + _T(",") + pObj->m_strY + _T("}");
	}
}

void CCharElementPoints::CalByExpression(BOOL bCalLines)
{
	POS pos = GetHeadPosition();
	CCharElementPoint *pObj = NULL;

	while(pos!=NULL)
	{
		pObj = (CCharElementPoint *)GetNext(pos);
		pObj->CalByExpression(bCalLines);
	}
}

CCharElementPoint* CCharElementPoints::FindObj(CCharElementPoint *pSel)
{
	CCharElementPoint *pFind = NULL;
	POS pos = GetHeadPosition();
	CCharElementPoint *pObj = NULL;

	while(pos!=NULL)
	{
		pObj = (CCharElementPoint *)GetNext(pos);
		
		if((pObj->m_strX == pSel->m_strX) && (pObj->m_strY == pSel->m_strY))
		{
			pFind = pObj;
			return pFind;
		}
	}

	return pFind;
}

POS CCharElementPoints::GetPos(CCharElementPoint *pSel)
{
	POS pos = GetHeadPosition();
	POS prevPos = NULL; //pos的前一个位置
	CCharElementPoint *pObj = NULL;

	while(pos!=NULL)
	{
		prevPos = pos;
		pObj = (CCharElementPoint *)GetNext(pos);

		if(pObj == pSel)
		{
			return prevPos;
		}
	}

	return NULL;
}