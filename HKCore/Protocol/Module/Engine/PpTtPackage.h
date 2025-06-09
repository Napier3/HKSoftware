#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "ByteBlocks.h"
#include "BbVariables.h"

class CPpTtPackage :	public CExBaseList
{
public:
	CPpTtPackage(void);
	virtual ~CPpTtPackage(void);

public:
	//֡�����Ķ���
	CBbVariables *m_pDataInterface;
	CBbVariables *m_pTtVariables;
	CByteBlocks *m_pTtHead;
	CByteBlocks *m_pTtTail;

	long m_nPkgLen;
	long m_nPkgNum;
	long m_nParseRef;   //�����������õĵļ���

	//�����ı���֡		��ʹ�ô�ģ��֡������ͷ������β����֡
	CExBaseList m_listPackages;

	/*
	2010-12-06 ���
	*/
	BOOL AddSystemVariables();

private:
	CExBaseList m_oAllVariables;
		
public:
	virtual UINT GetClassID()				{        return PPCLASSID_PPTTPACKAGE;                               }
	virtual BSTR GetXmlElementKey()		{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strTPackageKey;     }

// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	
	virtual void InitAfterRead();

public:
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual long Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//�ֽڿ��ƥ��		��Ҫ���ڽ���
	virtual DWORD MatchHeadAndTail(PACKAGEBUFFERPOS &oPkgBufPos);
	BOOL IsWholeMatch()		{		return m_bIsWholeMatch;		}

	//ƥ�䱨��		��������֡����ƥ��
	CExBaseObject* MatchPackge(PACKAGEBUFFERPOS &oPkgBufPos);

	//������TtPackage������ȫ��ParsePackage
	CExBaseList* GetParsePackages()					{	return &m_listPackages;				}
	void AddParsePackage(CExBaseObject *pPkg)	{	m_listPackages.AddTail(pPkg);		}
	void EmptyParsePackages()							{	m_listPackages.RemoveAll();		}

protected:
	BOOL m_bIsWholeMatch;

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	void GetAllVariables(CExBaseList &oDestList);
	void GetDataInterface(CExBaseList &oDestList);
	long InitOwnAllVariables();

	//ȫ��������صĽӿ�
	CExBaseList* GetAllVariables()		{		return &m_oAllVariables;		}
	CBbVariable* FindVariableByName(const CString &strName);
	CBbVariable* FindVariableByID(const CString &strID);

};

