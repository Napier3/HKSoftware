// RtAllocBuffer.h: interface for the CRtAllocBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RtAllocBuffer_h__)
#define _RtAllocBuffer_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../../../Module/BASECLASS/ExBaseList.h"
#include "RecordTestClassDef.h"

//没有用到，当初设计这两个类的目的是分配缓存，现在使用的类是CRtBufferConfig
class CRtAttrBuffer : public CExBaseObject
{
public:
	CRtAttrBuffer();
	virtual ~CRtAttrBuffer();
	
public:
	
//属性
public:
	//关键字属性
	static const char *g_pszKeyAttrBuffer;
	static const char *g_pszKeyBufferID;
	static const char *g_pszKeyAttrID;

	CString m_strBufferID;
	CString m_strAttrID;

//方法
public:
	//重载的方法
	virtual UINT GetClassID()                {  return RTCLASSID_ATTRBUFFER;  };
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
#endif
	
};

class CRtAllocBuffer : public CExBaseList  
{
public:
	CRtAllocBuffer();
	virtual ~CRtAllocBuffer();

//属性
public:
	//关键字属性
// 	static const char *g_pszKeyAllocBuffer;
// 	static const char *g_pszKeyRecordBufferID;
// 	static const char *g_pszKeyRecordBufferUse;
// 	static const char *g_pszKeySpyBufferID;
// 	static const char *g_pszKeySpyBufferUse;

	//自身属性
	CString m_strRecordBufferID;
	long     m_nRecordBufferUse;
	CString m_strSpyBufferID;
	long     m_nSpyBufferUse;

//方法
public:
	//重载的方法
	virtual UINT GetClassID()                {  return RTCLASSID_ALLOCBUFFER;  };
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
	virtual CExBaseObject* CreateNewChild()					{	return NULL;    }
	virtual CExBaseObject* CreateNewChild(long nClassID)	{	return NULL;    }
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
#endif

	//树形控件相关的操作
// 	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter = TVI_LAST);
	
};

#endif // !defined(_RtAllocBuffer_h__)
