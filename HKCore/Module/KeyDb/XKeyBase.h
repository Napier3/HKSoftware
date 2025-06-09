//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XKeyBase.h  CXKeyBase

#pragma once

#include "KeyDbGlobal.h"

class CXKeyBase;
class CXMultiKeyBase;

class CXKeyMatchRef
{
public:
	CXKeyMatchRef();
	virtual ~CXKeyMatchRef();

	static CXKeyMatchRef* New(CXKeyBase *pKey)
	{
		CXKeyMatchRef *pNew = new CXKeyMatchRef();
		pNew->Init(pKey);
		return pNew;
	}

	CXKeyMatchRef* Clone();
	void Init(CXKeyBase *pKey);
public:
	CXKeyBase *m_pXKeyRef;
	long  m_nArrayIndex;

public:
	BOOL Match(CXKeyMatchRef *pXKeyMatchRef);
	long GetImportance();
	BOOL IsSubKey(CXKeyMatchRef *pXKeyRef);
	BOOL IsArrayKey();
	BOOL IsArrayTypeBefore();
	BOOL IsArrayTypeAfter();
	BOOL IsArrayTypeAll();
	BOOL IsNumber();
};

class CXKeyMatchRefList : public CTLinkListEx<CXKeyMatchRef>
{
public:
	CXKeyMatchRefList()				{}
	virtual ~CXKeyMatchRefList()	{}

public:
	CXKeyMatchRef* AddKey(CXKeyBase *pXKey, long nArrayIndex=-1);
	BOOL IsSubKey(CXKeyMatchRef *pXKeyRef,CString strText);
	BOOL Match(CXKeyMatchRef *pXKeyRef);
	void RemoveKey(CXKeyMatchRef *pXKeyRef);  //2022-5-10   lijunqing
	long XFindIndex(CXKeyMatchRef *pXKeyRef);

	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

	CXKeyBase* FindByName(const CString &strName);
	CXKeyBase* FindByID(const CString &strID);
	virtual BOOL Match(CXKeyMatchRefList *pDstXKeys, long &nMatchRatio);
	virtual BOOL IsSubKey(CXKeyMatchRef *pXKey, long &nImportance);

	//2023-2-6  lijunqing 判断是否为子集
	virtual BOOL IsSubset(CXKeyMatchRefList *pKeysSub);

};


class CXKeyBase : public CExBaseList
{
public:
	CXKeyBase();
	virtual ~CXKeyBase();

	long  m_nImportance;
	long  m_nIsArray;

	long m_dwMultiKeyArray;
	DWORD *m_pMultiKeyArray;

	//重载函数
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXKEYBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXKeyBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual BOOL Query(const CString &strText, CXKeyMatchRefList *pListKeys);
	virtual BOOL Match(CXKeyBase *pKey);
	virtual BOOL IsSubKey(CXKeyBase *pXKeyRef);

	BOOL IsArrayKey();
	BOOL IsArrayTypeBefore();
	BOOL IsArrayTypeAfter();
	BOOL IsArrayTypeAll();
	
public:
	void InitMultiKeyArray(CExBaseList &listMultiKey);
	CXMultiKeyBase* GetXMultiKeyBase(long nArrayIndex);

//私有成员变量
private:

//私有成员变量访问方法
public:

protected:
	BOOL QueryString(const CString &strText, const CString &strKey);


	//long GetArrayIndex_Before(const CString &strText, long nPos);
	//long GetArrayIndex_After(const CString &strText, long nPos);
// 	long FindPos(const CString &strText);
// 	BOOL CmpAscii(const CString &strText, long nPos, long nCmpLen);

	//void OffsetAfter(const CString &strText, long &nPos);
	//void OffsetBefore(const CString &strText, long &nPos);
};


//////////////////////////////////////////////////////////////////////////
//CXKeyMngr
class CXKeyMngr : public CExBaseList
{
public:
	CXKeyMngr();
	virtual ~CXKeyMngr();

	//重载函数
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXKEYMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXKeyMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

};


long xkey_find_string_pos(const CString &strText, const CString &strKey, long nPos);
#ifdef _UNICODE
long xkey_find_string_pos(const wchar_t *strText, const wchar_t *strKey, long nPos);
#else
long xkey_find_string_pos(const char *strText, const char *strKey, long nPos);
#endif

CXMultiKeyBase* xkey_Get_XMultiKeyBase(long nArrayIndex, CXKeyBase *pXKey);