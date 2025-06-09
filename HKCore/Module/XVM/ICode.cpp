// ICode.cpp: implementation of the CICode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ICode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/******************************************************************************************
*
*   GetICodeOpByIndex ()
*
*   Returns an I-code instruction's operand at the specified index.
*/

CICodeOperand* CICodeNode::GetICodeOpByIndex (int iOpIndex )
{
//	if (m_pInstruction->GetCount() == 0)
//	{
//		return NULL;
//	}
//
	return m_pInstruction->GetAt(iOpIndex);
}

void CICodeNode::Free()
{
	if (ICODE_NODE_SOURCE_LINE == m_iType)
	{
		if (m_iCreateSourceLine == 1 && m_pstrSourceLine != NULL)
		{
			delete m_pstrSourceLine;
			m_pstrSourceLine = NULL;
		}
	}
	else if (ICODE_NODE_INSTR == m_iType)
	{
		delete m_pInstruction;
		m_pInstruction = NULL;
	}
}

void CICodeNode::ChangeToSourceLine(char *pstrSourceLine)
{
	if (m_pInstruction != NULL)
	{
		delete m_pInstruction;
		m_pInstruction = NULL;
	}

	m_iType = ICODE_NODE_SOURCE_LINE;
	int nLen = strlen(pstrSourceLine);
	m_pstrSourceLine = new char[nLen+1];
	strcpy(m_pstrSourceLine, pstrSourceLine);
}

void CICodeNode::ChangeType(int iType)
{
	if (m_iType == iType)
	{
		return;
	}

	if (iType == ICODE_NODE_NONE)
	{
		Free();
	}

	m_iType = iType;
}

