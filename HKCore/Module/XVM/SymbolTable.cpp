// SymbolTable.cpp: implementation of the CSymbolTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SymbolTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSymbolTable::CSymbolTable()
{
	
}

CSymbolTable::~CSymbolTable()
{
	
}


/******************************************************************************************
*
*   GetSymbolByIndex ()
*
*   Returns a pointer to the symbol structure corresponding to the index.
*/

CSymbolNode* CSymbolTable::GetSymbolByIndex ( int iIndex )
{
	return GetAt(iIndex);
}

/******************************************************************************************
*
*   GetSymbolByIdent ()
*
*   Returns a pointer to the symbol structure corresponding to the identifier and scope.
*/

CSymbolNode* CSymbolTable::GetSymbolByIdent (const  char * pstrName, int iScope )
{
	// Local symbol node pointer
	CSymbolNode *pSymbol = NULL;
	CSymbolNode *pFind = NULL;
	POS pos = GetHeadPosition();
	
	// Loop through each symbol in the table to find the match
	while (pos != NULL)
	{
		pSymbol = GetNext(pos);

		if (pSymbol != NULL)
		{
			if ( (pSymbol->m_iScope == iScope )
				&& (strcmp(pSymbol->m_strName, pstrName) == 0) )
			{
				pFind = pSymbol;
				break;
			}
		}

	}
	
	return pFind;
}

/******************************************************************************************
*
*	GetSizeByIndent ()
*
*	Returns a variable's size based on its identifier.
*/

int CSymbolTable::GetSizeByIdent (const  char * pstrName, int iScope )
{
	// Get the symbol's information
	CSymbolNode * pSymbol = GetSymbolByIdent ( pstrName, iScope );
	
	// Return its size
	return pSymbol->m_iSize;
}

/******************************************************************************************
*
*   AddSymbol ()
*
*   Adds a symbol to the symbol table.
*/

int CSymbolTable::AddSymbol (const  char * pstrName, int iSize, int iScope, int iType )
{
	// If a label already exists
	if ( GetSymbolByIdent ( pstrName, iScope ) )
		return -1;
	
	// Create a new symbol node
	int iIndex = GetCount();
	CSymbolNode * pNewSymbol = new CSymbolNode(pstrName, iSize, iScope, iType, iIndex);
	AddNode(pNewSymbol);
	
	// Return the new symbol's index
	return iIndex;
}

