// BaseObject.h: interface for the CBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BASEOBJECT_H__)
#define _BASEOBJECT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//2022-3-25  ����޸�
//���пպ��������ŵ�CPP�У���ΪQT�������ᱨ�ܶ�ܶ��warning

#define CLASSID_BASECLASS       0x00000000	//�������
#define CLASSID_LISTCLASS       0x10000000	//�б�
#define CLASSID_MNGRCLASS       0x30000000	//����������
#define CLASSID_EXLISTCLASS     0x50000000	//��չ�б�
#define CLASSID_EXMNGRCLASS     0xD0000000	//��չ����������
#define CLASSID_BASEORLISTMASK     0xF0000000	//��չ����������

#include "BinarySerialInterface.h"
#include "../xml/XmlRWInterface.h"

//XML�ļ���д�ؼ��ֶ���
//��ʽ
/*
 * <keys name="guidebook">
 *	  <key string="name" key="nm"/>
 *    <key string="name" key="id"/>
 * </keys>
 */

class CXmlRWKeys
{
public:
	CXmlRWKeys()
	{
		m_strNameKey = L"name";
		m_strIDKey   = L"id";
		m_strLangIDKey   = L"xlang";
	}

	virtual ~CXmlRWKeys()
	{
	}

	//��XML�ڵ��ж�ȡ�ؼ���
	long ReadFromXmlFile(const CString &strFile);
	
public:
    BSTR m_strNameKey;
    BSTR m_strIDKey;
    BSTR m_strLangIDKey;

	static const char* g_pszNameKeyString;
	static const char* g_pszIDKeyString;
};

class CBaseObject  
{
public:
	CBaseObject();
	virtual ~CBaseObject();

protected:
	CBaseObject *m_pParent;

//����
public:
	CBaseObject* GetParent()                {    return m_pParent;    }
	void SetParent(CBaseObject *pParent)    {    m_pParent = pParent; }

	CBaseObject* GetAncestor(UINT nClassID);
	CBaseObject* GetAncestorEx(UINT nClassID);
	CBaseObject* GetAncestorByDepth(long nDepth);
	long GetDepth();
	CBaseObject* GetRoot();
	BOOL HasParent(CBaseObject *pParent);

	virtual UINT GetClassID() {        return CLASSID_BASECLASS;                               }
	virtual UINT GetOwnClassID()      {        return GetClassID() & 0x0FFFFF;                         }
	virtual UINT GetBaseClassID()     {        return GetClassID() & 0xF00000;                         }
	bool IsBaseObject()       {        return ( (GetClassID() & CLASSID_BASEORLISTMASK) == CLASSID_BASECLASS);      };
	bool IsBaseList()         {        return ( (GetClassID() & CLASSID_LISTCLASS) == CLASSID_LISTCLASS);      };
	bool IsBaseMngr()         {        return ( (GetClassID() & CLASSID_MNGRCLASS) == CLASSID_MNGRCLASS);      };

	//ReadXML
	virtual long XmlRead(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)	;

	//WriteXML
	virtual BSTR GetXmlElementKey()  {      return NULL;     }
	virtual long XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, BSTR pszElementKey, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWrite(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, CXmlRWKeys *pXmlRWKeys); 
	virtual long XmlWriteEx(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, CXmlRWKeys *pXmlRWKeys, CXmlRWElementBase* &pRetElement);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//���������л�
	virtual long Serialize(CBinarySerialBuffer &oBinaryBuffer);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead(){}
	
public:
	virtual long SerializeRead(char *pBuffer, long nLen); 
	virtual long SerializeRead(CBinarySerialBuffer &oBinaryBuffer); 
	virtual long SerializeWrite(CBinarySerialBuffer &oBinaryBuffer); 
#ifdef _DBLIB_USE_SHAREMEM_
	virtual long SerializeWrite(CShareMemSerialize *pBinaryBuffer); 
#endif
	virtual BOOL BinarySerializeReadFromFile(const CString &strFile);
	virtual BOOL BinarySerializeWriteToFile(const CString &strFile);

public:
	//2019-08-25
	virtual long ValCmp(CBaseObject* pRightObj);
	virtual long ValCmp(CBaseObject* pRightObj, DWORD dwAttrID);
	virtual long ValCmp(CBaseObject* pRightObj, const CString &strAttrID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL IsEqualChildren(CBaseObject* pObj);
	virtual BOOL Copy(CBaseObject* pDest)				{		CopyOwn(pDest); CopyChildren(pDest); pDest->InitAfterRead(); return TRUE;}
	virtual BOOL CopyEx(CBaseObject* pDest, BOOL bCopyOwn,BOOL bCopyChildren);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL CopyChildren(CBaseObject* pDest);
	virtual CBaseObject* Clone()						{		return NULL;												}

	//�������ݶ���
	virtual BOOL Update(CBaseObject* pDest)				{		UpdateOwn(pDest); UpdateChildren(pDest); return TRUE;		}
	virtual BOOL UpdateOwn(CBaseObject* pDest);
	virtual BOOL UpdateChildren(CBaseObject* pDest);
	virtual BOOL IsSame(CBaseObject* pObj);
	virtual CBaseObject* FindSame(CBaseObject* pObj);
	

public:
	virtual BOOL OpenXmlFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual BOOL OpenXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual BOOL SaveXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);

    virtual BSTR GetXml(CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
    virtual void GetXml(CXmlRWKeys *pXmlRWKeys, CString &bstrXml,const long &nXmlRWType = _PUGI_XML_TYPE_);
	//2019-12-28  lijunqing
	virtual long GetXml(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset=0,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual long GetXml_UTF8(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset=0,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual long GetXml_ASCII(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset=0,const long &nXmlRWType = _PUGI_XML_TYPE_);

	virtual BOOL SetXml(BSTR strXml,BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);

#ifndef _PSX_IDE_QT_
	virtual BOOL SetXml(_bstr_t &strXml,BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
#endif

	virtual BOOL SetXml(BSTR strXml, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual BOOL SetXml(const CString &strXml, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
#ifndef _PSX_IDE_QT_
    virtual BOOL SetXml(_bstr_t &strXml, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
#endif

    //2020-5-31  lijunqing
    virtual BOOL SetXml(CXmlRWDocBase *pRWDoc, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys);
    virtual BOOL SetXml_ASCII(char *strXml, long nLen,CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual BOOL SetXml_UTF8(char *strXml,long nLen, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);

	static bool IsBaseObject(UINT nClassID)       {        return ( (nClassID & CLASSID_BASEORLISTMASK) == CLASSID_BASECLASS);      };
	static bool IsBaseList(UINT nClassID)         {        return ( (nClassID & CLASSID_LISTCLASS) == CLASSID_LISTCLASS);      };

	//2020-10-13  lijunqing
	virtual void SetModifiedFlag(BOOL bModified=TRUE);
	virtual BOOL GetModifiedFlagOwn();
	virtual void SaveBaseObject();
	virtual BOOL GetModifiedFlag(BOOL bRoot=TRUE); //2021-5-5  lijunqing

protected:
	virtual void SetModifiedFlagOwn(BOOL bModified=TRUE);
};




#endif // !defined(_BASEOBJECT_H__)
