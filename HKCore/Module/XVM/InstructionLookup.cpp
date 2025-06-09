// InstructionLookup.cpp: implementation of the CInstructionLookup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InstructionLookup.h"
#include "Globals.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//CTInstructs Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTInstructs::CTInstructs()
{
	m_nInstructCount = 0;
	long nIndex = 0;
	for (nIndex=0; nIndex<MAX_INSTRUCT_LOOKUP_COUNT; nIndex++)
	{
		g_InstrTable[nIndex] = NULL;
	}

}

CTInstructs:: ~CTInstructs()
{
	long nIndex = 0;

	for (nIndex=0; nIndex<m_nInstructCount; nIndex++)
	{
		if (g_InstrTable[nIndex] != NULL)
		{
			delete g_InstrTable[nIndex];
			g_InstrTable[nIndex] = NULL;
		}
	}
}


CTInstruct* CTInstructs::In_Find(const char *pstrName)
{
	CTInstruct *p = NULL;
	CTInstruct *pFind = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<m_nInstructCount; nIndex++)
	{
		if (stricmp(pstrName, (g_InstrTable[nIndex])->m_pstrInstruct) == 0)
		{
			pFind = g_InstrTable[nIndex];
			break;
		}
	}

	return pFind;
}

BOOL CTInstructs::In_IsInstructExist (const char *pstrName)
{
	CTInstruct *pFind = In_Find(pstrName);
	return (pFind != NULL);
}

CTInstruct* CTInstructs::AddInstructLookup (const char *pstrMemonic, int iOpcode, int iOpCount )
{
	CTInstruct* p = In_Find(pstrMemonic);

	if (p != NULL)
	{
		return p;
	}

	g_InstrTable [ m_nInstructCount ] = new CTInstruct();
	p = g_InstrTable [ m_nInstructCount ];
    //ATLASSERT(m_nInstructCount < MAX_INSTRUCT_LOOKUP_COUNT);

	// Make sure we haven't run out of instruction indices	
	if ( m_nInstructCount >= MAX_INSTRUCT_LOOKUP_COUNT)
		return NULL;

	// Set the mnemonic, opcode and operand count fields	
	strcpy ( p->m_pstrInstruct, pstrMemonic );
	//strupr ( p->m_pstrInstruct );
	p->m_nOpcode = iOpcode;
	p->m_nOpCount = iOpCount;

	// Allocate space for the operand list
	p->SetOpCount(iOpCount);//m_OpList = ( OperandTypes * ) malloc ( iOpCount * sizeof ( OperandTypes ) );
	m_nInstructCount++;

	return p;
}
