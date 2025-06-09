//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguage.h  CXLanguage

#pragma once

#include "XLanguageGlobal.h"


#include "XLangItem.h"

class CXLanguage : public CExBaseList
{
public:
	CXLanguage();
	virtual ~CXLanguage();

	static CString g_strLanguageStrError;
	void CloseFile();

//重载函数
public:
	virtual UINT GetClassID() {    return LGUGCLASSID_CLANGUAGE;   }
	virtual BSTR GetXmlElementKey()  {      return CXLanguageXmlRWKeys::CXLanguageKey();     }
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

	virtual CXLangItem* AddString(const CString &strID, const CString &strString);	
	virtual CXLangItem* AddString(const CString &strID, CString *pstrString);	

//私有成员变量
protected:
	CString m_strXLangFile;

//私有成员变量访问方法
public:
	BOOL SaveLanguagegResourceFile_Chinese(const CString &strFileName, BOOL bUseLangCommonPath);
	BOOL SaveLanguagegResourceFile();
	BOOL SaveLanguagegResourceFile(const CString &strFileName);
	BOOL SaveLanguagegResourceFileEx(const CString &strFileName);
	BOOL HasOpenXLangFile();
	BOOL OpenXLangFile(const CString &strFilePath);
	BOOL LoadLanguagegResourceFile(const CString &strFileName);
	BOOL LoadLanguagegResourceFileEx(const CString &strFileName);
	BOOL InitResourceByLangFile(CXLanguage *pLangConstResource, BOOL bIsDebug);
	BOOL InsertNoExist(CXLanguage *pLangSrc);
// 	BOOL InitByResource(CXLanguage *pLangResource);

	BOOL xlang_GetLgugStr(const CString &strID, CString &strLanguageString);
	const CString& xlang_GetLgugStr(const CString &strID);
	BOOL RegisterString(const CString &strID, const CString &strString);

public:
	CXLangItem* FindBySrcText(const CString &strSrcText);
	CXLangItem* FindBySrcTextAndID(const CString &strID, const CString &strSrcText);
	void xlang_GetID(const CString &strObjId, CString &strXLangID);
	void xlang_GetID_Ex(CExBaseObject *pObj, CExBaseObject *pParent, CString &strXLangID, long &nIndex);
	void xlang_GetID_Ex(CExBaseObject *pObj, CExBaseObject *pParent, CString &strXLangID);
	void xlang_Buid(CExBaseList *pList);
	void xlang_BuidEx(CExBaseList *pList);
	void xlang_Translate(CExBaseList *pList);
	void xlang_TranslateEx(CExBaseList *pList, CExBaseList *pListErr);
};

