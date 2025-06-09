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
	//帧变量的定义
	CBbVariables *m_pDataInterface;
	CBbVariables *m_pTtVariables;
	CByteBlocks *m_pTtHead;
	CByteBlocks *m_pTtTail;

	long m_nPkgLen;
	long m_nPkgNum;
	long m_nParseRef;   //被解析桢引用的的计数

	//关联的报文帧		即使用此模板帧（报文头、报文尾）的帧
	CExBaseList m_listPackages;

	/*
	2010-12-06 添加
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
	//字节块的解析		具体的解析在派生类中执行解析
	virtual long Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//字节块的匹配		主要用于解析
	virtual DWORD MatchHeadAndTail(PACKAGEBUFFERPOS &oPkgBufPos);
	BOOL IsWholeMatch()		{		return m_bIsWholeMatch;		}

	//匹配报文		遍历解析帧进行匹配
	CExBaseObject* MatchPackge(PACKAGEBUFFERPOS &oPkgBufPos);

	//管理与TtPackage关联的全部ParsePackage
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

	//全部变量相关的接口
	CExBaseList* GetAllVariables()		{		return &m_oAllVariables;		}
	CBbVariable* FindVariableByName(const CString &strName);
	CBbVariable* FindVariableByID(const CString &strID);

};

