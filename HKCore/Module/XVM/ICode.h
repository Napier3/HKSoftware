// ICode.h: interface for the CICode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ICODE_H__)
#define _ICODE_H__

#include "../BaseClass/TLinkList.h"
#include "Globals.h"

class CICodeOperand                                  // An I-code operand
{
public:
	CICodeOperand()
	{
		m_iType = 0;
		m_fFloatLiteral = 0;
		m_iOffset = 0;
		m_iOffsetSymbolIndex = 0;
	}
	
	virtual ~CICodeOperand()
	{
	}
	
public:
	int m_iType;                                      // Type
	union                                           // The value
	{
		int   m_iIntLiteral;                            // Integer literal
		float m_fFloatLiteral;                        // Float literal
		int   m_iStringIndex;                           // String table index
		int   m_iSymbolIndex;                           // Symbol table index
		int   m_iJumpTargetIndex;                       // Jump target index
		int   m_iFuncIndex;                             // Function index
		int   m_iRegCode;                               // Register code
	};
	int m_iOffset;                                    // Immediate offset
	int m_iOffsetSymbolIndex;                         // Offset symbol index

	const CICodeOperand& operator = (const CICodeOperand& oDest)
	{
		if (this == &oDest)
		{
			return *this;
		}

		m_iType = oDest.m_iType;
		m_iOffset = oDest.m_iOffset;
		m_iOffsetSymbolIndex = oDest.m_iOffsetSymbolIndex;

		if (m_iType == OPERAND_TYPE_FLOAT)
		{
			m_fFloatLiteral = oDest.m_fFloatLiteral;
		}
		else
		{
			m_iIntLiteral = oDest.m_iIntLiteral;
		}

		return *this;
	}
};

// An I-code instruction
class CICodeInstruction : public CTLinkList<CICodeOperand>
{
public:
	CICodeInstruction(int iOpCode)
	{
		m_iOpCode = iOpCode;
	}
	
	virtual ~CICodeInstruction()
	{
	}
	
public:
	int m_iOpCode;                                    // Opcode
	//CTLinkList<CICodeOperand> m_oOpList;                              // Operand list

private:
	CICodeInstruction()
	{
	}

public:
	void AddIntICodeOp ( int iFuncIndex, int iInstrIndex, int iValue );
    void AddFloatICodeOp ( int iFuncIndex, int iInstrIndex, float fValue );
    void AddStringICodeOp ( int iFuncIndex, int iInstrIndex, int iStringIndex );
    void AddVarICodeOp ( int iFuncIndex, int iInstrIndex, int iSymbolIndex );
    void AddArrayIndexAbsICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffset );
    void AddArrayIndexVarICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffsetSymbolIndex );
    void AddFuncICodeOp ( int iFuncIndex, int iInstrIndex, int iOpFuncIndex );
    void AddRegICodeOp ( int iFuncIndex, int iInstrIndex, int iRegCode );
    void AddJumpTargetICodeOp ( int iFuncIndex, int iInstrIndex, int iTargetIndex );	
};

// An I-code node
class CICodeNode                          
{
public:
	CICodeNode(int iType, char* pstrSourceLine)
	{
		m_iCreateSourceLine = 0;
		m_iType = iType;
		m_pstrSourceLine = pstrSourceLine;
	}
	CICodeNode(int iType, int iOpCode)
	{
		m_iCreateSourceLine = 0;
		m_iType = iType;
		m_pInstruction = new CICodeInstruction(iOpCode);
	}
	CICodeNode(int iType)
	{
		m_iCreateSourceLine = 0;
		m_iType = iType;
		m_pInstruction = NULL;
	}
	
	virtual ~CICodeNode()
	{
		Free();
	}
	
	int m_iType;                                      // The node type
	union
	{
		// The I-code instruction
		CICodeInstruction *m_pInstruction;                           
		
		// The source line with which this instruction is annotated
		char* m_pstrSourceLine;	
		
		// The jump target index
		int m_iJumpTargetIndex;							
	};

private:
	CICodeNode()
	{
	}

	int  m_iCreateSourceLine;
	void Free();

public:
	CICodeOperand * GetICodeOpByIndex (int iOpIndex );
	void ChangeToSourceLine(char *pstrSourceLine);
	void ChangeType(int iType);
};


#endif // !defined(_ICODE_H__)
