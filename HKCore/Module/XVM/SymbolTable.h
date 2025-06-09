// SymbolTable.h: interface for the CSymbolTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMBOLTABLE_H__B1404257_B2CF_412A_A46B_5CFE39D86E2A__INCLUDED_)
#define AFX_SYMBOLTABLE_H__B1404257_B2CF_412A_A46B_5CFE39D86E2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include "Globals.h"
#include "../BaseClass/TLinkList.h"

// ---- Symbol Types ----------------------------------------------------------------------

#define SYMBOL_TYPE_VAR                 0x0000       // Variable
#define SYMBOL_TYPE_PARAM               0x0001       // Parameter
#define SYMBOL_TYPE_EXPORT_VAR          0x0002       // Variable EXPORT
#define SYMBOL_TYPE_LONG_VAR            0x1000       // Variable EXPORT
#define SYMBOL_TYPE_STRING_VAR          0x2000       // Variable EXPORT
#define SYMBOL_TYPE_FLOAT_VAR           0x4000       // Variable EXPORT

class CSymbolNode
{
public:
	CSymbolNode(const char *pstrName, int iSize, int iScope, int iType, int iIndex)
	{
		m_iIndex = iIndex;
		strcpy(m_strName, pstrName);
		m_iSize = iSize;
		m_iScope = iScope;
		m_iType = iType;
	}
	virtual ~CSymbolNode()
	{
	}

	int  m_iIndex;					// Index
	char m_strName [ MAX_IDENT_SIZE ]; // Identifier
	int  m_iSize;      // Size (1 for variables, N for arrays)
	int  m_iScope;     // Scope (0 for globals, N for locals' function index)
	int  m_iType;      // Symbol type (parameter or variable)
	
private:
	CSymbolNode()
	{
	}
};

class CSymbolTable  : public CTLinkList<CSymbolNode>
{
public:
	CSymbolTable();
	virtual ~CSymbolTable();

	//CTLinkList<CSymbolNode> m_oList;

public:
	CSymbolNode * GetSymbolByIndex ( int iIndex );
    CSymbolNode * GetSymbolByIdent (const  char * pstrName, int iScope );
    int GetSizeByIdent (const  char * pstrName, int iScope );
    int AddSymbol (const  char * pstrName, int iSize, int iScope, int iType );
	
};

#endif // !defined(AFX_SYMBOLTABLE_H__B1404257_B2CF_412A_A46B_5CFE39D86E2A__INCLUDED_)
