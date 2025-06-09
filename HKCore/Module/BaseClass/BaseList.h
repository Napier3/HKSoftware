// BaseList.h: interface for the CBaseList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BASELIST_H__)
#define _BASELIST_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseObject.h"
#include "TLinkList.h"

typedef CTLinkList<CBaseObject> CLinkBaseList;

class CBaseList : public CBaseObject  , public CTLinkList<CBaseObject>
{
public:
	CBaseList();
	virtual ~CBaseList();

//属性定义
public:

//方法
public:
	virtual void Append(CBaseList &oListSrc);
	virtual void AppendClone(CBaseList &oListSrc);
	virtual void Append(CBaseList *pListSrc)			{	Append(*pListSrc);			}
	virtual void AppendClone(CBaseList *pListSrc)		{	AppendClone(*pListSrc);		}

	virtual CBaseObject* CreateNewChild(CXmlRWNodeBase &oNode, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	{
// 		CString strNodeName;
// 		_bstr_t bstr = oNode->GetnodeName();
// 		strNodeName = bstr;
// 		return CreateNewChild(strNodeName, bAddToTail, pXmlRWKeys);
// 	}
	virtual CBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/) ;
	virtual CBaseObject* AddNew(long nClassID);

	virtual UINT GetClassID()                             {      return CLASSID_LISTCLASS;               }
	
	//ReadXml
	virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys);

	//WriteXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	
	//缓冲区串行化
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);
	
public:
	virtual BOOL CopyChildren(CBaseObject* pDest)	;
	virtual BOOL IsEqualChildren(CBaseObject* pObj);

	virtual BOOL CanPaste(UINT nClassID);
	virtual BOOL CanPaste(CBaseObject *pObj);
	virtual BOOL CanPaste(CBaseList *pList);
	virtual CBaseObject* Paste(CBaseObject *pObj);
	virtual CBaseObject* Paste(CBaseList *pList);

	CBaseObject* AddNew(const CString &strName, const CString &strID);
	virtual CBaseObject* Clone();

	CBaseObject* AddNewChild(CBaseObject *pNew);
	virtual CBaseObject* FindByClassID(DWORD dwClassID);
};

#endif // !defined(_BASELIST_H__)
