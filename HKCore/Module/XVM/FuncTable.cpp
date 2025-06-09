// FuncTable.cpp: implementation of the CFuncTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FuncTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFuncTable::CFuncTable()
{
	
}

CFuncTable::~CFuncTable()
{

}

/******************************************************************************************
*
*   GetICodeInstrByImpIndex ()
*
*   Returns an I-code instruction structure based on its implicit index.
*/
CICodeNode* CFuncTable::GetICodeNodeByImpIndex ( int iFuncIndex, int iInstrIndex )
{
	CFuncNode *pFunc = GetFuncByIndex ( iFuncIndex );

	if (pFunc == NULL)
	{//error
		return NULL;
	}

	if (pFunc->GetCount() == 0)
	{
		return NULL;
	}

	return pFunc->GetAt(iInstrIndex);
}

/******************************************************************************************
*
*   AddICodeSourceLine ()
*
*   Adds a line of source code annotation to the I-code stream of the specified function.
*/

void CFuncTable::AddICodeSourceLine ( int iFuncIndex, char * pstrSourceLine )
{
	// Get the function to which the source line should be added
	CFuncNode * pFunc = GetFuncByIndex ( iFuncIndex );
	
	// Create an I-code node structure to hold the line
	CICodeNode * pSourceLineNode = new CICodeNode(ICODE_NODE_SOURCE_LINE, pstrSourceLine);
	
	// Add the instruction node to the list and get the index
	if (pFunc != NULL)
	{
		pFunc->AddNode(pSourceLineNode);
	}
}

/******************************************************************************************
*
*   AddICodeInstr ()
*
*   Adds an instruction to the local I-code stream of the specified function.
*/

int CFuncTable::AddICodeInstr ( int iFuncIndex, int iOpcode )
{
	// Get the function to which the source line should be added
	CFuncNode * pFunc = GetFuncByIndex ( iFuncIndex );

	if (pFunc == NULL)
	{//error
		return 0;
	}
	
	// Create an I-code node structure to hold the line
	CICodeNode * pSourceLineNode = new CICodeNode(ICODE_NODE_INSTR, iOpcode);
	
	// Add the instruction node to the list and get the index
	pFunc->AddNode(pSourceLineNode);

	return pFunc->GetCount() - 1;
}


/******************************************************************************************
*
*   AddICodeOp ()
*
*   Adds an operand to the specified I-code instruction.
*/

void CFuncTable::AddICodeOp ( int iFuncIndex, int iInstrIndex, CICodeOperand *pValue )
{
	// Get the I-code node
	CICodeNode *pInstr = GetICodeNodeByImpIndex ( iFuncIndex, iInstrIndex );

	if (pInstr == NULL)
	{
		return;
	}
	
	// Add the instruction
	pInstr->m_pInstruction->AddNode(pValue);
}

/******************************************************************************************
*
*   AddIntICodeOp ()
*
*   Adds an integer literal operand to the specified I-code instruction.
*/

void  CFuncTable::AddIntICodeOp ( int iFuncIndex, int iInstrIndex, int iValue )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to integer and store the value
	
	pValue->m_iType = OPERAND_TYPE_INT;
	pValue->m_iIntLiteral = iValue;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddFloatICodeOp ()
*
*   Adds a float literal operand to the specified I-code instruction.
*/

void  CFuncTable::AddFloatICodeOp ( int iFuncIndex, int iInstrIndex, float fValue )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to float and store the value
	
	pValue->m_iType = OPERAND_TYPE_FLOAT;
	pValue->m_fFloatLiteral = fValue;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddStringICodeOp ()
*
*   Adds a string literal operand to the specified I-code instruction.
*/

void  CFuncTable::AddStringICodeOp ( int iFuncIndex, int iInstrIndex, int iStringIndex )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to string index and store the index
	
	pValue->m_iType = OPERAND_TYPE_STRING_INDEX;
	pValue->m_iStringIndex = iStringIndex;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddVarICodeOp ()
*
*   Adds a variable operand to the specified I-code instruction.
*/

void  CFuncTable::AddVarICodeOp ( int iFuncIndex, int iInstrIndex, int iSymbolIndex )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to variable and store the symbol index
	
	pValue->m_iType = OPERAND_TYPE_VAR;
	pValue->m_iSymbolIndex = iSymbolIndex;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddArrayIndexAbsICodeOp ()
*
*   Adds an array indexed with a literal integer value operand to the specified I-code
*   instruction.
*/

void  CFuncTable::AddArrayIndexAbsICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffset )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to array index absolute and store the indices
	
	pValue->m_iType = OPERAND_TYPE_ARRAY_INDEX_ABS;
	pValue->m_iSymbolIndex = iArraySymbolIndex;
	pValue->m_iOffset = iOffset;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddArrayIndexVarICodeOp ()
*
*   Adds an array indexed with a variable operand to the specified I-code
*   instruction.
*/

void  CFuncTable::AddArrayIndexVarICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffsetSymbolIndex )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to array index variable and store the indices
	
	pValue->m_iType = OPERAND_TYPE_ARRAY_INDEX_VAR;
	pValue->m_iSymbolIndex = iArraySymbolIndex;
	pValue->m_iOffsetSymbolIndex = iOffsetSymbolIndex;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddFuncICodeOp ()
*
*   Adds a function operand to the specified I-code instruction.
*/

void  CFuncTable::AddFuncICodeOp ( int iFuncIndex, int iInstrIndex, int iOpFuncIndex )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to function index and store the index
	
	pValue->m_iType = OPERAND_TYPE_FUNC_INDEX;
	pValue->m_iFuncIndex = iOpFuncIndex;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddRegICodeOp ()
*
*   Adds a register operand to the specified I-code instruction.
*/

void  CFuncTable::AddRegICodeOp ( int iFuncIndex, int iInstrIndex, int iRegCode )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to register and store the code (even though we'll ignore it)
	
	pValue->m_iType = OPERAND_TYPE_REG;
	pValue->m_iRegCode = iRegCode;
	
	// Add the operand to the instruction
	
	CFuncTable::AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddJumpTargetICodeOp ()
*
*   Adds a jump target operand to the specified I-code instruction.
*/

void  CFuncTable::AddJumpTargetICodeOp ( int iFuncIndex, int iInstrIndex, int iTargetIndex )
{
	// Create an operand structure to hold the new value
	
	CICodeOperand *pValue = new CICodeOperand();;
	
	// Set the operand type to register and store the code (even though we'll ignore it)
	
	pValue->m_iType = OPERAND_TYPE_JUMP_TARGET_INDEX;
	pValue->m_iJumpTargetIndex = iTargetIndex;
	
	// Add the operand to the instruction
	
	AddICodeOp ( iFuncIndex, iInstrIndex, pValue );
}

/******************************************************************************************
*
*   AddICodeJumpTarget ()
*
*   Adds a jump target to the I-code stream.
*/

void  CFuncTable::AddICodeJumpTarget ( int iFuncIndex, int iTargetIndex )
{
	// Get the function to which the source line should be added
	CFuncNode * pFunc = GetFuncByIndex ( iFuncIndex );

	if (pFunc == NULL)
	{
		return;
	}
	
	// Create an I-code node structure to hold the line
	CICodeNode * pSourceLineNode = new CICodeNode(ICODE_NODE_JUMP_TARGET);
	
	// Set the jump target
	pSourceLineNode->m_iJumpTargetIndex = iTargetIndex;
	
	// Add the instruction node to the list and get the index
	pFunc->AddNode(pSourceLineNode);
}

