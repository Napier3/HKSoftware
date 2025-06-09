//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXMATCHTOOLBASE;   }

//˽�г�Ա����
private:
	CXKeyDB *m_pKeyDB;
	CXMatchList m_listSrc;
	CXMatchList m_listDst;
	CExBaseList *m_pSrcRefList;

//˽�г�Ա�������ʷ���
public:
	CXMatchList* GetSrcMatchList()	{	return &m_listSrc;	}
	CXMatchList* GetDstMatchList()	{	return &m_listDst;	}
	CExBaseList* GetSrcRefList()	{	return m_pSrcRefList;	}

};

static const CString g_strGbXMatchFilePostFix = _T("gbxmc");
static const CString g_strGbXMatchFileName =_T("ģ���豸����ģ���滻ӳ�������ļ�");// g_sLangTxt_TemDataFileChange;//_T("ģ���豸����ģ���滻ӳ�������ļ�")
CString wzd_GetXMatchFilePath();
CString wzd_GetXMatchFileDlgFilter();
