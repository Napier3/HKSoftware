// FuncTable.h: interface for the CFuncTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FUNCTABLE_H__)
#define _FUNCTABLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory.h>
#include "ICode.h"

// A function table node
class CFuncNode : public CTLinkList<CICodeNode>
{
public:
	CFuncNode(const char* pstrName, int iIsHostAPI, int iIndex)
	{
		strcpy(m_strName, pstrName);
		m_iIndex      = iIndex;
		m_iIsHostAPI  = iIsHostAPI;
		m_iParamCount = 0;
	}

	virtual ~CFuncNode()
	{
	}

public:
	int  m_iIndex;									    // Index
	char m_strName [ MAX_IDENT_SIZE ];               // Name
	int  m_iIsHostAPI;                                 // Is this a host API function?
	int  m_iParamCount;                                // The number of accepted parameters
	//CTLinkList<CICodeNode> m_oICodeStream;                         // Local I-code stream

private:
	CFuncNode()
	{
	}
};

class CFuncTable  : public CTLinkList<CFuncNode>
{
public:
	CFuncTable();
	virtual ~CFuncTable();

	//CTLinkListEx<CFuncNode> m_oFunctions;
	
public:
	CFuncNode* GetFuncByIndex(int iIndex)
	{
		//return GetAt(iIndex);
		CFuncNode *pFunc = NULL;
		CFuncNode *pFind = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pFunc = GetNext(pos);

			if (pFunc->m_iIndex == iIndex)
			{
				pFind = pFunc;
				break;
			}
		}

		return pFind;
	}

	CFuncNode* GetFuncByName(const char* pstrName)
	{
		CFuncNode *p = NULL, *pFind = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			p = GetNext(pos);

			if (strcmp(pstrName , p->m_strName) == 0)
			{
				pFind = p;
				break;
			}
		}

		return pFind;
	}

	int GetFuncIndexByName(char* pstrName, bool bWithHost)
	{
		int iFuncIndex = -1;
		int iIndex = 1;
		CFuncNode *pFunc = NULL;

		POS pos = GetHeadPosition();
		while (pos != NULL)
		{
			pFunc = (CFuncNode*)GetNext(pos);

			if (bWithHost)
			{
				if ( strcmp(pFunc->m_strName, pstrName) == 0)
				//if (pFunc->m_strName == pstrName)
				{
					iFuncIndex = iIndex;
					break;
				}
			}
			else
			{
				if ( strcmp(pFunc->m_strName, pstrName) == 0 && pFunc->m_iIsHostAPI != 1)
				//if ( pFunc->m_strName == pstrName == 0 && pFunc->m_iIsHostAPI != 1)
				{
					iFuncIndex = iIndex;
					break;
				}
			}

			iIndex++;
		}

		return iFuncIndex;
	}
	
	int AddFunc( const char * pstrName, int iIsHostAPI , bool &bMainFunc)
	{
		if (GetFuncByName(pstrName) != NULL)
		{
			return -1;
		}

		CFuncNode* pNew = new CFuncNode(pstrName, iIsHostAPI, GetCount()+1);
		AddNode(pNew);

		if (stricmp(pstrName, MAIN_FUNC_NAME) == 0)
		{
			bMainFunc = true;
		}

		return  GetCount();
	}

	void SetFuncParamCount ( int iFuncIndex, int iParamCount )
	{
		CFuncNode* pFunc = GetFuncByIndex(iFuncIndex);

		if (pFunc != NULL)
		{
			pFunc->m_iParamCount = iParamCount;
		}
	}

	CICodeNode * GetICodeNodeByImpIndex ( int iFuncIndex, int iInstrIndex );
	void AddICodeSourceLine ( int iFuncIndex, char * pstrSourceLine );
	int AddICodeInstr ( int iFuncIndex, int iOpcode );	
	
	void AddICodeOp ( int iFuncIndex, int iInstrIndex, CICodeOperand *pValue );
	void AddIntICodeOp ( int iFuncIndex, int iInstrIndex, int iValue );
    void AddFloatICodeOp ( int iFuncIndex, int iInstrIndex, float fValue );
    void AddStringICodeOp ( int iFuncIndex, int iInstrIndex, int iStringIndex );
    void AddVarICodeOp ( int iFuncIndex, int iInstrIndex, int iSymbolIndex );
    void AddArrayIndexAbsICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffset );
    void AddArrayIndexVarICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffsetSymbolIndex );
    void AddFuncICodeOp ( int iFuncIndex, int iInstrIndex, int iOpFuncIndex );
    void AddRegICodeOp ( int iFuncIndex, int iInstrIndex, int iRegCode );
    void AddJumpTargetICodeOp ( int iFuncIndex, int iInstrIndex, int iTargetIndex );	
    void AddICodeJumpTarget ( int iFuncIndex, int iTargetIndex );
	
};

#endif // !defined(_FUNCTABLE_H__)
