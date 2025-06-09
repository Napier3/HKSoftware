//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageMngr.h  CXLanguageMngr

#pragma once

#include "XLanguageGlobal.h"


#include "XLanguageResource.h"

class CXLanguageMngr : public CExBaseList
{
private:
	CXLanguageMngr();
	virtual ~CXLanguageMngr();

	static long g_nXLanguageMngrRef;
	static BOOL g_bXInLanguageEditState;

public:
	static CXLanguageMngr *g_pXLanguageMngr;
	static CXLanguageMngr* Create(CXLanguageResourceBase *pXLanguageResoure, const CString &strFileName);
	static CXLanguageMngr* Create(CXLanguageResourceBase *pXLanguageResoure, BOOL bUseCommonPath);
	static void Release();
	static BOOL IsInLanguageEditState()	{	return g_bXInLanguageEditState;	}
	static void SetInLanguageEditState(BOOL b)	{	g_bXInLanguageEditState = b;	}
	static BOOL xlang_IsCurrXLanguageChinese();
	static CString xlang_GetLangConfigPath(BOOL bCommon);
	static CString xlang_GetLanguagePath();
	static BOOL xlang_IsUseXLangCommonPath();

    //2022-3-25  lijunqing
    static void xlang_AddXLanguageRerouce(CXLanguageResourceBase *pXLanguageResoure, BOOL bUseCommonPath);

public:
	CString m_strCurrLanguage;
	long    m_nDebugState;
	CString m_strLangConfigFile;
	BOOL    m_bUseLangCommonPath;

	BOOL OpenXLangConfigFile(BOOL bUseCommonPath);
	BOOL SaveXLangConfigFile();

#ifdef _DEBUG
protected:
	CFile *m_pXLangSourceFile;
	BOOL  m_bXLangSourceFile;
	CExBaseList m_listXLangSourceCode;

	void CreateXLangSourceFile();
	void WriteXLangSourceFile();
#endif

//重载函数
public:
	virtual UINT GetClassID() {    return LGUGCLASSID_CLANGUAGEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CXLanguageXmlRWKeys::CXLanguageMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CXLanguage *m_pCurrLanguage;
	CXLanguageResourceBase *m_pXLanguageResoure;

    //2022-3-25  lijunqing 对于集成了通信规约、测试仪配置等各种功能的自动测试
    //需要多种资源对象，即同时夹在多种资源，虽然有点浪费，但是暂时这么处理
    CExBaseList m_listXLanguageResoure;

//私有成员变量访问方法
public:
	void InitCurrLanguage(const CString &strFileName);
	void InitCurrLanguage();

	CXLanguage* GetCurrLanguageResource()
	{
		return m_pXLanguageResoure;
	}

    BOOL xlang_GetLgugStr(const CString &strID, CString &strLanguageString);
    const CString& xlang_GetLgugStr(const CString &strID);

	void xlang_AddString(const CString &strID, const CString &strLanguageString);
	void xlang_Save();
	void xlang_SetCurrLanguageID(const CString &strID);
	CString xlang_FindLandidByLangTxt(const CString &strText);
	CString xlang_FindLandTransByLangTxt(const CString &strText);
	BOOL xlang_IsLandidExist(const CString &strXlangID);
};

const CString& xlang_GetCurrLanguageID();
void xlang_SetCurrLanguageID(const CString &strID);
CString xlang_GetCurrLanguagePath(const CString &strFileName);

BOOL xlang_IsCurrXLanguageChinese();
BOOL xlang_GetLgugStr(const CString &strID, CString &strLanguageString);
const CString& xlang_GetLgugStr(const CString &strID);
BOOL xlang_ParseLanguageStr(CString &strLanguageString);
BOOL xlang_InitByLgugStr(const CString &strID, CWnd *pWnd);
void xlang_AddString(const CString &strID, const CString &strLanguageString);
void xlang_Save();
BOOL xlang_IsInDebugState();
void xlang_WriteResourceFile(CExBaseList *pObjRcFile, const CString &strRcFile, CXmlRWKeys *pXmlKeys);
void xlang_TranslateByResourceFile(CExBaseList *pObjRcFile, const CString &strRcFile, BOOL bUseCommon);
void xlang_TranslateByResourceFileEx(CExBaseList *pObjRcFile, const CString &strRcFile, BOOL bUseCommon);
void xlang_TranslateByResourceFile(CExBaseList *pObjRcFile, const CString &strRcFile);
void xlang_TranslateByResourceFileEx(CExBaseList *pObjRcFile, const CString &strRcFile);
void xlang_TranslateByResourceFileEx_NoWrite(CExBaseList *pObjRcFile, const CString &strRcFile);

inline BOOL xlang_IsInLanguageEditState()			{	return CXLanguageMngr::IsInLanguageEditState();		}
inline void xlang_SetInLanguageEditState(BOOL b)	{	return CXLanguageMngr::SetInLanguageEditState(b);	}
inline BOOL xlang_IsUseXLangCommonPath()			{	return CXLanguageMngr::xlang_IsUseXLangCommonPath();		}

#ifndef _PSX_IDE_QT_
void xlang_SetFrameDocTitle(CFrameWnd *pFrameWnd, const CString &strTitle);
#endif
CString xlang_FindLandidByLangTxt(const CString &strText);
CString xlang_FindLandTransByLangTxt(const CString &strText);
BOOL xlang_IsLandidExist(const CString &strXlangID);

// void xlang_LogString(long nLevel, const CString &strXLangID);
// void xlang_LogString(LPVOID pPara, long nLevel, const CString &strXLangID);
// 
// void xlang_LogFormatString(long nLevel, const wchar_t *strXLangID, ...);
// void xlang_LogFormatString(LPVOID pPara, long nLevel, const wchar_t *strXLangID, ...);
// void xlang_LogFormatString(long nLevel, const char *strXLangID, ...);
// void xlang_LogFormatString(LPVOID pPara, long nLevel, const char *strXLangID, ...);
#ifndef _PSX_IDE_QT_
void xlang_AppendMenu(CMenu &menu, UINT nID, const CString &strXlangText);
#endif
