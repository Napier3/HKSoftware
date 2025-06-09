#include "StdAfx.h"
#include "WzdFile.h"

CWzdFile::CWzdFile(void)
{
	m_pFile = NULL;
}

CWzdFile::~CWzdFile(void)
{
}

BOOL CWzdFile::ProssData(CString sParentPath)
{
	CString strValue = m_strName;
	CString strZZMS=_T("_"), strZZXH=_T("_"), strJYSJ=_T("_");	

	////只显示gbrpt文件
	int p = strValue.Find(_T(".gbrpt"));
	if(p == -1)
		return FALSE;

	//测试描述
	p = strValue.Find(_T("_"));
	if(p == -1)
		return FALSE;
	strZZMS = strValue.Left(p);
	strValue = strValue.Right(strValue.GetLength() - p - 1);

	//测试型号
	p = strValue.Find(_T("_"));
	if(p == -1)
		return FALSE;
	strZZXH = strValue.Left(p);
	strValue = strValue.Right(strValue.GetLength() - p - 1);

	//测试报告
	p = strValue.Find(_T("_"));
	if(p == -1)
		return FALSE;
	strValue = strValue.Right(strValue.GetLength() - p - 1);

	//检验时间
	p = strValue.Find(_T("."));
	if(p == -1)
		return FALSE;
	strJYSJ = strValue.Left(p);
	strJYSJ.Replace(_T("$"), _T(":"));
	strValue = strValue.Right(strValue.GetLength() - p - 1);
	COleDateTime time;
	time.ParseDateTime(strJYSJ);

	m_strName = sParentPath + m_strID;
	m_strFileName = strZZMS;
	m_strFileType = strZZXH;
	time.GetAsSystemTime(m_tmYun);
	return TRUE;
}

long CWzdFile::ValCmp(CBaseObject* pRightObj)
{
	if(pRightObj == NULL)
		return 0;

	CXFile* pObj = (CXFile*)pRightObj;
	if(pObj == NULL)
		return 0;

	if(m_tmYun.wYear <= 0 || pObj->m_tmYun.wYear <= 0)
		return 0;

	COleDateTime time1(m_tmYun);
	COleDateTime time2(pObj->m_tmYun);
	if(time1 > time2)
		return 1;
	if(time1 == time2)
		return 0;
	return -1;
}

BOOL CWzdFile::CheckValue(CString sZZMS, CString sZZXH)
{
	if(sZZMS != _T(""))
	{
		int p = m_strFileName.Find(sZZMS);
		if(p == -1)
			return FALSE;
	}
	if(sZZXH != _T(""))
	{
		int p = m_strFileType.Find(sZZXH);
		if(p == -1)
			return FALSE;
	}
	return TRUE;
}
BOOL CWzdFile::CheckTime(COleDateTime sTime, COleDateTime eTime)
{
	COleDateTime time1(m_tmYun);
	if(sTime <= time1 && time1 <= eTime)
		return TRUE;

	return FALSE;
}