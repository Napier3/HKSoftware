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

//û���õ�������������������Ŀ���Ƿ��仺�棬����ʹ�õ�����CRtBufferConfig
class CRtAttrBuffer : public CExBaseObject
{
public:
	CRtAttrBuffer();
	virtual ~CRtAttrBuffer();
	
public:
	
//����
public:
	//�ؼ�������
	static const char *g_pszKeyAttrBuffer;
	static const char *g_pszKeyBufferID;
	static const char *g_pszKeyAttrID;

	CString m_strBufferID;
	CString m_strAttrID;

//����
public:
	//���صķ���
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

//����
public:
	//�ؼ�������
// 	static const char *g_pszKeyAllocBuffer;
// 	static const char *g_pszKeyRecordBufferID;
// 	static const char *g_pszKeyRecordBufferUse;
// 	static const char *g_pszKeySpyBufferID;
// 	static const char *g_pszKeySpyBufferUse;

	//��������
	CString m_strRecordBufferID;
	long     m_nRecordBufferUse;
	CString m_strSpyBufferID;
	long     m_nSpyBufferUse;

//����
public:
	//���صķ���
	virtual UINT GetClassID()                {  return RTCLASSID_ALLOCBUFFER;  };
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
	virtual CExBaseObject* CreateNewChild()					{	return NULL;    }
	virtual CExBaseObject* CreateNewChild(long nClassID)	{	return NULL;    }
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
#endif

	//���οؼ���صĲ���
// 	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter = TVI_LAST);
	
};

#endif // !defined(_RtAllocBuffer_h__)
