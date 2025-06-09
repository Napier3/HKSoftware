//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchToolBase.h  CXMatchToolBase

#pragma once

#include "KeyDbGlobal.h"
#include "XMatchToolBase.h"

#include "XKeyDB.h"
#include "XMatchList.h"
#include "XMatchConfig.h"
#include "../XLanguage/XLanguageResource.h"

class CXMatchToolBase : public CExBaseList
{
public:
	CXMatchToolBase();
	virtual ~CXMatchToolBase();

	virtual BOOL IsMatchValid();
	virtual BOOL IsXMatchValid_LEqual_1();
	virtual void Match(CXKeyDB *m_pKeyDB, CExBaseList *pSrcRefList, CExBaseList *pDstRefList, long nMatchRatio=20, CThreadProgressInterface *pThradProgress=NULL);
	virtual void MatchRead(CXMatchDatarefs *pXMatchDatarefs, CExBaseList *pListSrcRefList, CExBaseList *pDstRefList, UINT nRootClassID);
	virtual void MatchReadSingle(CXMatchDatarefs *pXMatchDatarefs, CExBaseList *pSrcRefList, CExBaseList *pDstRefList, UINT nRootClassID);

//重载函数
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXMATCHTOOLBASE;   }

//私有成员变量
private:
	CXKeyDB *m_pKeyDB;
	CXMatchList m_listSrc;
	CXMatchList m_listDst;
	CExBaseList *m_pSrcRefList;

//私有成员变量访问方法
public:
	CXMatchList* GetSrcMatchList()	{	return &m_listSrc;	}
	CXMatchList* GetDstMatchList()	{	return &m_listDst;	}
	CExBaseList* GetSrcRefList()	{	return m_pSrcRefList;	}

};

static const CString g_strGbXMatchFilePostFix = _T("gbxmc");
static const CString g_strGbXMatchFileName =_T("模板设备数据模型替换映射配置文件");// g_sLangTxt_TemDataFileChange;//_T("模板设备数据模型替换映射配置文件")
CString wzd_GetXMatchFilePath();
CString wzd_GetXMatchFileDlgFilter();
