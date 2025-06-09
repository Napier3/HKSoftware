// TAsmParser.h: interface for the CTAsmParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TASM_H__)
#define _TASM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "../../Module/System/AtlFile.h"
#include "../BaseClass/TLinkList.h"
#include "TSyntax.h"
#include "TAsmGlobal.h"
#include "../BaseClass/WSerializeBuff.h"
#include "XvmBuffer.h"
#include "InstructionLookup.h"

// ---- Lexer -----------------------------------------------------------------------------
#define LEX_STATE_NO_STRING         0           // Lexemes are scanned as normal
#define LEX_STATE_IN_STRING         1           // Lexemes are scanned as strings
#define LEX_STATE_END_STRING        2           // Lexemes are scanned as normal, and the

// ---- Error Strings ---------------------------------------------------------------------
// The following macros are used to represent assembly-time error strings

static const char*  ERROR_ASMMSG_INVALID_INPUT               = "Invalid input";
static const char*  ERROR_ASMMSG_LOCAL_SETSTACKSIZE          = "SetStackSize can only appear in the global scope";
static const char*  ERROR_ASMMSG_LOCAL_SETPRIORITY           = "SetPriority can only appear in the global scope";
static const char*  ERROR_ASMMSG_INVALID_STACK_SIZE          = "Invalid stack size";
static const char*  ERROR_ASMMSG_MULTIPLE_SETSTACKSIZES      = "Multiple instances of SetStackSize illegal";
static const char*  ERROR_ASMMSG_MULTIPLE_SETPRIORITYS       = "Multiple instances of SetPriority illegal";
static const char*  ERROR_ASMMSG_INVALID_STACK_LINE          = "Invalid SetStackSize line";
static const char*  ERROR_MSSG_INVALID_PRIORITY           = "Invalid SetPriority line";
static const char*  ERROR_ASMMSG_IDENT_EXPECTED              = "Identifier expected";
static const char*  ERROR_ASMMSG_INVALID_ARRAY_SIZE          = "Invalid array size";
static const char*  ERROR_ASMMSG_IDENT_REDEFINITION          = "Identifier redefinition";
static const char*  ERROR_ASMMSG_UNDEFINED_IDENT             = "Undefined identifier";
static const char*  ERROR_ASMMSG_NESTED_FUNC                 = "Nested functions illegal";
static const char*  ERROR_ASMMSG_FUNC_REDEFINITION           = "Function redefinition";
static const char*  ERROR_ASMMSG_UNDEFINED_FUNC              = "Undefined function";
static const char*  ERROR_ASMMSG_GLOBAL_PARAM                = "Parameters can only appear inside functions";
static const char*  ERROR_ASMMSG_MAIN_PARAM                  = "_Main () function cannot accept parameters";
static const char*  ERROR_ASMMSG_GLOBAL_LINE_LABEL           = "Line labels can only appear inside functions";
static const char*  ERROR_ASMMSG_LINE_LABEL_REDEFINITION     = "Line label redefinition";
static const char*  ERROR_ASMMSG_UNDEFINED_LINE_LABEL        = "Undefined line label";
static const char*  ERROR_ASMMSG_GLOBAL_INSTRUCT             = "Instructions can only appear inside functions";
static const char*  ERROR_ASMMSG_INVALID_INSTRUCT            = "Invalid instruction";
static const char*  ERROR_ASMMSG_INVALID_OPERAND             = "Invalid operand";
static const char*  ERROR_ASMMSG_INVALID_STRING	          = "Invalid string";
static const char*  ERROR_ASMMSG_INVALID_ARRAY_NOT_INDEXED   = "Arrays must be indexed";
static const char*  ERROR_ASMMSG_INVALID_ARRAY	              = "Invalid array";
static const char*  ERROR_ASMMSG_INVALID_ARRAY_INDEX	      = "Invalid array index";
static const char*  ERROR_ASMMSG_EXPORT_IN_FUNC              = "can not export a local variable in function";
static const char*  ERROR_ASMMSG_CANNT_EXPORT_ARRAY	      = "Can not export array";



#define TASM_TOKEN_TYPE_INT              0           // An integer literal
#define TASM_TOKEN_TYPE_FLOAT            1           // An floating-point literal
#define TASM_TOKEN_TYPE_STRING           2           // An string literal
#define TASM_TOKEN_TYPE_QUOTE            3           // A double-quote
#define TASM_TOKEN_TYPE_IDENT            4           // An identifier
#define TASM_TOKEN_TYPE_COLON            5           // A colon
#define TASM_TOKEN_TYPE_OPEN_BRACKET     6           // An openening bracket
#define TASM_TOKEN_TYPE_CLOSE_BRACKET    7           // An closing bracket
#define TASM_TOKEN_TYPE_COMMA            8           // A comma
#define TASM_TOKEN_TYPE_OPEN_BRACE       9           // An openening curly brace
#define TASM_TOKEN_TYPE_CLOSE_BRACE      10          // An closing curly brace
#define TASM_TOKEN_TYPE_NEWLINE          11          // A newline
#define TASM_TOKEN_TYPE_INSTRUCT			12			// An instruction
#define TASM_TOKEN_TYPE_SETSTACKSIZE     13          // The SetStackSize directive
#define TASM_TOKEN_TYPE_SETPRIORITY      14          // The SetPriority directive
#define TASM_TOKEN_TYPE_VAR              15          // The Var/Var [] directives
#define TASM_TOKEN_TYPE_FUNC             16          // The Func directives
#define TASM_TOKEN_TYPE_PARAM            17          // The Param directives
#define TASM_TOKEN_TYPE_REG_RETVAL       18          // The _RetVal directives
#define TASM_TOKEN_TYPE_INVALID          19          // Error code for invalid tokens
#define TASM_TOKEN_TYPE_EXPORT           20          // Error code for invalid tokens
#define END_OF_TASM_TOKEN_STREAM         255         // The end of the stream has been

// ---- Data Structures -----------------------------------------------------------------------


class CLexer                           // The lexical analyzer/tokenizer
{
public:
	CLexer()
	{
		ResetLexer();
		Backup();
	}
	virtual ~CLexer()
	{
	}

	void ResetLexer ()
	{
		memset(m_pstrCurrLexeme, 0, MAX_LEXEME_SIZE);
		memset(m_pstrCurrLexemeOrigin, 0, MAX_LEXEME_SIZE);
		memset(m_pstrCurrLexeme_2, 0, MAX_LEXEME_SIZE);
		
		// Set the current line to the start of the file
		m_iCurrSourceLine = 0;
		
		// Set both indices to point to the start of the string
		m_iIndex0 = 0;
		m_iIndex1 = 0;
		
		// Set the token type to invalid, since a token hasn't been read yet
		m_CurrToken = TASM_TOKEN_TYPE_INVALID;
		
		// Set the lexing state to no strings
		m_iCurrLexState = LEX_STATE_NO_STRING;	
	}
	
	int m_iCurrSourceLine;                        // Current line in the source
	unsigned int m_iIndex0;                       // Indices into the string
	unsigned int m_iIndex1;
	
	Token m_CurrToken;                            // Current token
	char m_pstrCurrLexeme [ MAX_LEXEME_SIZE ];    // Current lexeme
	int m_iCurrLexState;                          // The current lex state
	char m_pstrCurrLexemeOrigin [ MAX_LEXEME_SIZE ];    // Current lexeme

	void Backup()
	{
		strcpy(m_pstrCurrLexeme_2, m_pstrCurrLexeme);
		m_iCurrSourceLine_2 = m_iCurrSourceLine;
		m_iIndex0_2 = m_iIndex0;
		m_iIndex1_2 = m_iIndex1;
		m_CurrToken_2 = m_CurrToken;
		m_iCurrLexState_2 = m_iCurrLexState;	
	}

	void Restore()
	{
		strcpy(m_pstrCurrLexeme, m_pstrCurrLexeme_2);
		m_iCurrSourceLine = m_iCurrSourceLine_2;
		m_iIndex0 = m_iIndex0_2;
		m_iIndex1 = m_iIndex1_2;
		m_CurrToken = m_CurrToken_2;
		m_iCurrLexState = m_iCurrLexState_2;	
	}

private:
	int m_iCurrSourceLine_2;                        // Current line in the source
	unsigned int m_iIndex0_2;                       // Indices into the string
	unsigned int m_iIndex1_2;
	
	Token m_CurrToken_2;                            // Current token
	char m_pstrCurrLexeme_2 [ MAX_LEXEME_SIZE ];    // Current lexeme
	int m_iCurrLexState_2;                          // The current lex state
	
};

// ---- Script ----------------------------------------------------------------------------
class CScriptHeader                    // Script header data
{
public:
	CScriptHeader()
	{
		m_iStackSize = 0;
		m_iGlobalDataSize = 0;
		m_iIsMainFuncPresent  =0;
		m_iMainFuncIndex = 0;
	}
	virtual ~CScriptHeader()
	{
	}

	int  m_iStackSize;                             // Requested stack size
	int  m_iGlobalDataSize;						// The size of the script's global data
	unsigned char m_iIsMainFuncPresent;                     // Is _Main () present?
	int  m_iMainFuncIndex;							// _Main ()'s function index

	unsigned char m_ucPriorityType;                          // The thread priority type
    int m_uiTimesliceDuration;                          // The user-defined priority (if any)
	
//	BOOL Write(CFile *pFile)
//	{
//		pFile->Write(&m_iStackSize, sizeof(int));
//		pFile->Write(&m_iGlobalDataSize, sizeof(int));
//		pFile->Write(&m_iIsMainFuncPresent, sizeof(char));
//		pFile->Write(&m_iMainFuncIndex, sizeof(int));
//		pFile->Write(&m_ucPriorityType, sizeof(unsigned char));
//		pFile->Write(&m_uiTimesliceDuration, sizeof(unsigned int));
//		
//		return TRUE;
//	}

	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  m_iStackSize;
			oBBuffer <<  m_iGlobalDataSize;
			oBBuffer <<  m_iIsMainFuncPresent;
			oBBuffer <<  m_iMainFuncIndex;
			oBBuffer <<  m_ucPriorityType;
			oBBuffer <<  m_uiTimesliceDuration;
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(4*sizeof(long) * 4*sizeof(BYTE));
		}
		else
		{
		}
		return TRUE;
	}
};
// 
// class  CTInstruct                     // An instruction lookup
// {
// public:
// 	char m_pstrInstruct[MAX_INSTRUCT_MNEMONIC_SIZE];  // Mnemonic string
// 	unsigned short m_nOpcode;                                // Opcode
// 	unsigned char  m_nOpCount;                               // Number of operands
// 	OperandTypes *m_OpList;                           // Pointer to operand list
// 	
// 	CTInstruct()
// 	{
// 		memset(m_pstrInstruct, 0, MAX_INSTRUCT_MNEMONIC_SIZE*sizeof(char));
// 		m_nOpcode = 0;
// 		m_nOpCount = NULL;
// 		m_OpList = NULL;
// 	}
// 	
// 	virtual ~CTInstruct()
// 	{
// 	}
// 	
// 	//Sets the operand type for the specified operand in the specified instruction.
// 	void SetOpType (int iOpIndex, OperandTypes iOpType )
// 	{
// 		m_OpList[ iOpIndex ] = iOpType;
// 	}
// 
// 	void SetOpCount(int iOpCount)
// 	{
// 		m_nOpCount = iOpCount;
// 		long nLen = iOpCount * sizeof ( OperandTypes );
// 		m_OpList = ( OperandTypes * ) malloc ( nLen );
// 		ZeroMemory(m_OpList, nLen);
// 	}
// };

class CTAsmInstructs : public CTInstructs
{
private:
	CTAsmInstructs();
	virtual ~CTAsmInstructs();


	virtual void InitInstructTable();

protected:
	static long m_nRefCount;
	static CTAsmInstructs* g_pAsmInstructs;

public:
	static CTAsmInstructs* Create();
	static void Release();

public:
	static CTInstruct* Find(const char *pstrName);
	static BOOL IsInstructExist (const char *pstrName);

};
 

// ---- Assembled Instruction Stream ------------------------------------------------------
class COperand                              // An assembled operand
{
public:
	COperand()
	{
		m_nType = 0;
		m_fFloatLiteral = 0;
		m_iIntLiteral = 0;
		m_iOffsetIndex = 0;
	}
	virtual ~COperand()
	{
	}

public:
	unsigned char m_nType;                                  // Type
	union     //OperandData                                  // The value
	{
		int   m_iIntLiteral;                        // Integer literal
		float m_fFloatLiteral;                      // Float literal
		int   m_iStringTableIndex;                  // String table index
		int   m_iStackIndex;                        // Stack index
		int   m_iInstructIndex;                        // Instruction index
		int   m_iFuncIndex;                         // Function index
		int   m_iHostAPICallIndex;                  // Host API Call index
		int   m_iReg;                               // Register code
	};//m_oData;
	
	int m_iOffsetIndex;                             // Index of the offset

//	BOOL Write(CFile *pFile)
//	{
//		pFile->Write(&m_nType, sizeof(unsigned char));
//
//		switch(m_nType)
//		{
//		case OPERAND_TYPE_INT:
//			pFile->Write(&m_iIntLiteral, sizeof(int));
//			break;
//		case OPERAND_TYPE_FLOAT:
//			pFile->Write(&m_fFloatLiteral, sizeof(float));
//			break;
//		case OPERAND_TYPE_STRING_INDEX:
//			pFile->Write(&m_iStringTableIndex, sizeof(int));
//			break;
//		case OPERAND_TYPE_ABS_STACK_INDEX:
//			pFile->Write(&m_iStackIndex, sizeof(int));
//			break;
//		case OPERAND_TYPE_REL_STACK_INDEX:
//			pFile->Write(&m_iStackIndex, sizeof(int));
//			pFile->Write(&m_iOffsetIndex, sizeof(int));
//			break;
//		case OPERAND_TYPE_INSTRUCT_INDEX:
//			pFile->Write(&m_iInstructIndex, sizeof(int));
//			break;
//		case OPERAND_TYPE_FUNC_INDEX:
//			pFile->Write(&m_iFuncIndex, sizeof(int));
//			break;
//		case OPERAND_TYPE_HOST_API_CALL_INDEX:
//			pFile->Write(&m_iHostAPICallIndex, sizeof(int));
//			break;
//		case OPERAND_TYPE_REG:
//			pFile->Write(&m_iReg, sizeof(int));
//			break;
//		default:
//			break;
//		}
//
//		return TRUE;
//	}

	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  m_nType;
			
			switch(m_nType)
			{
			case OPERAND_TYPE_INT:
				oBBuffer <<  m_iIntLiteral;
				break;
			case OPERAND_TYPE_FLOAT:
				oBBuffer << m_fFloatLiteral;
				break;
			case OPERAND_TYPE_STRING_INDEX:
				oBBuffer <<  m_iStringTableIndex;
				break;
			case OPERAND_TYPE_ABS_STACK_INDEX:
				oBBuffer <<  m_iStackIndex;
				break;
			case OPERAND_TYPE_REL_STACK_INDEX:
				oBBuffer <<  m_iStackIndex;
				oBBuffer <<  m_iOffsetIndex;
				break;
			case OPERAND_TYPE_INSTRUCT_INDEX:
				oBBuffer <<  m_iInstructIndex;
				break;
			case OPERAND_TYPE_FUNC_INDEX:
				oBBuffer <<  m_iFuncIndex;
				break;
			case OPERAND_TYPE_HOST_API_CALL_INDEX:
				oBBuffer <<  m_iHostAPICallIndex;
				break;
			case OPERAND_TYPE_REG:
				oBBuffer <<  m_iReg;
				break;
			default:
				break;
			}
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(BYTE) + sizeof(long)*2+sizeof(float));
		}
		else
		{
		}
		
		return TRUE;
	}
};

class COperands : public CTLinkList<COperand>
{
public:
	COperands()
	{
	}

	virtual ~COperands()
	{
	}

	//CTLinkList<COperand> m_listChild;	
	
	int Add(int iType, int iVal)
	{
		COperand *p = new COperand();
		AddNode(p);
		p->m_nType = iType;
		p->m_iIntLiteral = iVal;
		return (GetCount()-1);
	}

	void Create(int iOperands)
	{
		DeleteAll();
		int iIndex = 0;
		COperand *p = NULL;

		for (iIndex=0; iIndex<iOperands; iIndex++)
		{
			p = new COperand();
			AddNode(p);
		}
	}

	COperand* operator[](long nIndex)
	{
		COperand *p = GetAtIndex(nIndex);
		return p;
	}
	
//	BOOL Write(CFile *pFile)
//	{
//		unsigned char nCount = (unsigned char)GetCount();
//		unsigned char nIndex = 0;
//		COperand *p = NULL;
//		pFile->Write(&nCount, sizeof(unsigned char));
//
//		for (nIndex=0; nIndex<nCount; nIndex++)
//		{
//			p = GetAtIndex(nIndex);
//			p->Write(pFile);
//		}
//
//		return TRUE;
//	}
	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		unsigned char nCount = (unsigned char)GetCount();
		unsigned char nIndex = 0;
		COperand *p = NULL;
		
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  nCount;
			
			for (nIndex=0; nIndex<nCount; nIndex++)
			{
				p = GetAtIndex(nIndex);
				p->Write(oBBuffer);
			}
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(BYTE));

			for (nIndex=0; nIndex<nCount; nIndex++)
			{
				p = GetAtIndex(nIndex);
				p->Write(oBBuffer);
			}
		}
		else
		{
		}

		return TRUE;
	}
};

class CInstruction                           // An instruction
{
public:
	CInstruction()
	{
		m_nOpcode = 0;
		//m_nOpCount = 0;
		//m_pOpList = NULL;
	}
	virtual ~CInstruction()
	{
	}

	unsigned short m_nOpcode;                                // Opcode
//	int m_nOpCount;                               // Number of operands
	COperands m_oOperands;                          // Pointer to operand list

//	BOOL Write(CFile *pFile)
//	{
//		pFile->Write(&m_nOpcode, sizeof(unsigned short));
//		m_oOperands.Write(pFile);
//
//		return TRUE;
//	}
	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer << m_nOpcode;
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(short));
		}
		else
		{
		}
		
		m_oOperands.Write(oBBuffer);
		
		return TRUE;
	}
};

class CInstructions : public CTLinkList<CInstruction>
{
public:
	CInstructions()
	{
		m_nInstructs = 0;
	}

	virtual ~CInstructions()
	{
		DeleteAll();
	}

//	CTLinkList<CInstruction> m_listChild;	
	
	int m_nInstructs;
	void Create()
	{
		DeleteAll();
		int nIndex = 0;
		CInstruction *p = NULL;
		for (nIndex=0; nIndex<m_nInstructs; nIndex++)
		{
			p = new CInstruction();
			AddNode(p);
		}
	}

	CInstruction* operator[](long nIndex)
	{
		CInstruction *p = GetAtIndex(nIndex);
		return p;
	}

//	BOOL Write(CFile *pFile)
//	{
//		pFile->Write(&m_nInstructs, sizeof(int));
//		int nIndex = 0;
//		CInstruction *p = NULL;
//		
//		for (nIndex=0; nIndex<m_nInstructs; nIndex++)
//		{
//			p = GetAtIndex(nIndex);
//			p->Write(pFile);
//		}
//
//		return TRUE;
//	}

	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		int nIndex = 0;
		CInstruction *p = NULL;

		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  m_nInstructs;
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(long));
		}
		else
		{
		}
		
		for (nIndex=0; nIndex<m_nInstructs; nIndex++)
		{
			p = GetAtIndex(nIndex);
			p->Write(oBBuffer);
		}
		
		return TRUE;
	}	
};

// ---- Function Table --------------------------------------------------------------------
class CFunction                        // A function table node
{
public:
	CFunction(char * pstrName, int iEntryPoint, int iIndex)
	{
		m_iIndex = iIndex;									// Index
		memset(m_pstrName, 0, MAX_IDENT_SIZE);           // Name
		strcpy(m_pstrName, pstrName);
		m_iEntryPoint = iEntryPoint;                            // Entry point
		m_ucParamCount = 0;                            // Param count
		m_iLocalDataSize = 0;                         // Local data size
	}
	CFunction()
	{
		m_iIndex = 0;									// Index
		memset(m_pstrName, 0, MAX_IDENT_SIZE);           // Name
		m_iEntryPoint = 0;                            // Entry point
		m_ucParamCount = 0;                            // Param count
		m_iLocalDataSize = 0;                         // Local data size
	}
	virtual ~CFunction()
	{
	}

	int m_iIndex;									// Index
	char m_pstrName [ MAX_IDENT_SIZE ];           // Name
	int m_iEntryPoint;                            // Entry point
	unsigned char m_ucParamCount;                            // Param count
	int m_iLocalDataSize;                         // Local data size
	
//	BOOL Write(CFile *pFile)
//	{
//		int nLen = strlen(m_pstrName);
//		pFile->Write(&m_iEntryPoint, sizeof(int));
//		pFile->Write(&m_ucParamCount, sizeof(unsigned char));
//		pFile->Write(&m_iLocalDataSize, sizeof(int));
//		pFile->Write(&nLen, sizeof(unsigned char));
//		pFile->Write(m_pstrName, nLen);
//
//		return TRUE;
//	}

	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  m_iEntryPoint;
			oBBuffer <<  m_ucParamCount;
			oBBuffer <<  m_iLocalDataSize;
			oBBuffer .WriteBufferEx(m_pstrName, strlen(m_pstrName));
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(long)*3 + strlen(m_pstrName)+1);
		}
		else
		{
		}
		
		return TRUE;
	}
};

class CFunctions : public CTLinkList<CFunction>
{
public:
	CFunctions()
	{
	}

	virtual ~CFunctions()
	{
	}

	//CTLinkList<CFunction> m_listChild;	
	CFunction* Find ( char * pstrName )
	{
		long nIndex = 0;
		long nCount = GetCount();
		CFunction *p = NULL;
		CFunction *pFind = NULL;
		
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			p = GetAtIndex(nIndex);
			
			if ( strcmp ( p->m_pstrName, pstrName ) == 0 )
			{
				pFind = p;
				break;
			}
		}
		
		return pFind;
	}
		
	int Add(char * pstrName, int iEntryPoint)
	{
		// If a function already exists with the specified name, exit and return an invalid
		// index
		if ( Find ( pstrName ) != NULL )
			return -1;
		
		// Create a new function node
		CFunction * pNewFunc = new CFunction(pstrName, iEntryPoint, GetCount()+1);
		
		// Add the function to the list and get its index
		AddNode(pNewFunc);
		
		// Return the new function's index
		return (GetCount()/* -1*/);
	}

	void SetFunInfo(char * pstrName, int iParamCount, int iLocalDataSize)
	{
		CFunction * pFunc = Find ( pstrName );
		
		if (pFunc != NULL)
		{
			// Set the remaining fields
			pFunc->m_ucParamCount = iParamCount;
			pFunc->m_iLocalDataSize = iLocalDataSize;
		}
	}

//	BOOL Write(CFile *pFile)
//	{
//		unsigned int nCount = (unsigned int)GetCount();
//		unsigned int nIndex = 0;
//		CFunction *p = NULL;
//
//		pFile->Write(&nCount, sizeof(unsigned int));
//
//		for (nIndex=0; nIndex<nCount; nIndex++)
//		{
//			p = GetAtIndex(nIndex);
//			p->Write(pFile);
//		}
//
//		return TRUE;
//	}
	
	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
        int nCount = (unsigned int)GetCount();
        int nIndex = 0;
		CFunction *p = NULL;
		
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  nCount;
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(long));
		}
		else
		{
		}

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			p = GetAtIndex(nIndex);
			p->Write(oBBuffer);
		}
		
		return TRUE;
	}
	
};

// ---- Label Table -----------------------------------------------------------------------

class CLabelNode                       // A label table node
{
public:
	CLabelNode(char * pstrLabel, int iTargetIndex, int iFuncIndex, int iIndex)
	{
		memset(m_pstrLabel, 0, MAX_IDENT_SIZE);
		strcpy(m_pstrLabel, pstrLabel);
		m_iIndex = iIndex;
		m_iTargetIndex = iTargetIndex;
		m_iFuncIndex = iFuncIndex;
	}
	
	virtual ~CLabelNode()
	{
	}

	int  m_iIndex;								   // Index
	char m_pstrLabel [ MAX_IDENT_SIZE ];           // Identifier
	int  m_iTargetIndex;                           // Index of the target instruction
	int  m_iFuncIndex;                             // Function in which the label resides
	
private:
	CLabelNode()
	{
	}

};


// A label table node
class CLabelNodes : public CTLinkList<CLabelNode>
{
public:
	CLabelNodes()
	{
	}

	virtual ~CLabelNodes()
	{
	}

//	CTLinkList<CLabelNode> m_listChild;	
	
public:
	CLabelNode* Find(char * pstrLabel, int iFuncIndex)
	{
		long nIndex = 0;
		long nCount = GetCount();
		CLabelNode *p = NULL;
		CLabelNode *pFind = NULL;
		
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			p = GetAtIndex(nIndex);
			
			if ( stricmp ( p->m_pstrLabel, pstrLabel ) == 0 && p->m_iFuncIndex == iFuncIndex)
			{
				pFind = p;
				break;
			}
		}
		
		return pFind;
	}

	int Add(char * pstrLabel, int iTargetIndex, int iFuncIndex)
	{
		if ( Find ( pstrLabel, iFuncIndex ) )
			return -1;
		
		// Create a new label node
		CLabelNode * pNewLabel = new CLabelNode(pstrLabel, iTargetIndex, iFuncIndex, GetCount());
		AddNode(pNewLabel);
		
		return (GetCount() - 1);
	}
};

// ---- Symbol Table ----------------------------------------------------------------------

class CTasmSymbol                      // A symbol table node
{
public:
	CTasmSymbol(char * pstrSymbol, int iSize, int iStackIndex, int iFuncIndex, int iIndex)
	{
        strcpy ( m_pstrSymbol, pstrSymbol );
        m_iSize = iSize;
        m_iStackIndex = iStackIndex;
        m_iFuncIndex = iFuncIndex;
		m_iIndex = iIndex;
	}
	virtual ~CTasmSymbol()
	{
	}

private:
	CTasmSymbol()
	{
		m_iIndex = 0;
		memset(m_pstrSymbol, 0, MAX_IDENT_SIZE);
		m_iSize = 0;
		m_iStackIndex = 0;
		m_iFuncIndex = 0;
	}

public:
	int m_iIndex;									// Index
	char m_pstrSymbol [ MAX_IDENT_SIZE ];          // Identifier
	int m_iSize;                                  // Size (1 for variables, N for arrays)
	int m_iStackIndex;                            // The stack index to which the symbol
	// points
	int m_iFuncIndex;                             // Function in which the symbol resides
};

class CTasmSymbols : public CTLinkList<CTasmSymbol>
{
public:
	CTasmSymbols()
	{
	}

	virtual ~CTasmSymbols()
	{
	}

	//CTLinkList<CTasmSymbol> m_listChild;

	CTasmSymbol* Find(char * pstrIdent, int iFuncIndex)
	{
		long nIndex = 0;
		long nCount = GetCount();
		CTasmSymbol *p = NULL;
		CTasmSymbol *pFind = NULL;

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			p = GetAtIndex(nIndex);
			
			if ( strcmp ( p->m_pstrSymbol, pstrIdent ) == 0 )
			{
				if ( p->m_iFuncIndex == iFuncIndex || p->m_iStackIndex >= 0 )
				{
					pFind = p;
					break;
				}
			}
		}

		return pFind;
	}
	int Add(char * pstrSymbol, int iSize, int iStackIndex, int iFuncIndex)
	{
		// If a label already exists
		if ( Find ( pstrSymbol, iFuncIndex ) )
			return -1;
		
		// Create a new symbol node
		CTasmSymbol * pNewSymbol = new CTasmSymbol(pstrSymbol, iSize, iStackIndex, iFuncIndex, GetCount());
		AddNode(pNewSymbol);
		
		return (GetCount()-1);
	}
};


// ---- Symbol Table ----------------------------------------------------------------------

class CExportSymbolNode                      // A symbol table node
{
public:
	CExportSymbolNode(char * pstrSymbol, int iStackIndex)
	{
        strcpy ( m_pstrSymbol, pstrSymbol );
        m_iStackIndex = iStackIndex;
	}
	virtual ~CExportSymbolNode()
	{
	}
	
private:
	CExportSymbolNode()
	{
		memset(m_pstrSymbol, 0, MAX_IDENT_SIZE);
		m_iStackIndex = 0;
	}
	
public:
	char m_pstrSymbol [ MAX_IDENT_SIZE ];          // Identifier
	int m_iStackIndex;                            // The stack index to which the symbol

//	BOOL Write(CFile *pFile)
//	{
//		pFile->Write(&m_iStackIndex, sizeof(int));
//		unsigned short nStringLen = strlen(m_pstrSymbol);
//		
//		pFile->Write(&nStringLen, sizeof(unsigned short));
//		pFile->Write(m_pstrSymbol, nStringLen);
//		
//		return TRUE;
//	}

	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  m_iStackIndex;
			oBBuffer.WriteBufferEx(m_pstrSymbol, strlen(m_pstrSymbol));
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(long) + strlen(m_pstrSymbol)+1);
		}
		else
		{
		}
		
		return TRUE;
	}
};

class CExportSymbolNodes : public CTLinkList<CExportSymbolNode>
{
public:
	CExportSymbolNodes()
	{
	}
	
	virtual ~CExportSymbolNodes()
	{
	}
	
	//CTLinkList<CExportSymbolNode> m_listChild;
	
	CExportSymbolNode* Find(char * pstrIdent)
	{
		long nIndex = 0;
		long nCount = GetCount();
		CExportSymbolNode *p = NULL;
		CExportSymbolNode *pFind = NULL;
		
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			p = GetAtIndex(nIndex);
			
			if ( strcmp ( p->m_pstrSymbol, pstrIdent ) == 0 )
			{
				pFind = p;
				break;
			}
		}
		
		return pFind;
	}

	int Add(char * pstrSymbol, int iStackIndex)
	{
		// If a label already exists
		if ( Find ( pstrSymbol ) )
			return -1;
		
		// Create a new symbol node
		CExportSymbolNode * pNewSymbol = new CExportSymbolNode(pstrSymbol, iStackIndex);
		AddNode(pNewSymbol);
		
		return (GetCount()-1);
	}

//	BOOL Write(CFile *pFile)
//	{
//		unsigned int nCount = (unsigned int)GetCount();
//		unsigned int nIndex = 0;
//		CExportSymbolNode *pNode = NULL;
//		
//		pFile->Write(&nCount, sizeof(unsigned short));
//		
//		for (nIndex=0; nIndex< nCount; nIndex++)
//		{
//			pNode = GetAtIndex(nIndex);
//			pNode->Write(pFile);
//		}
//		
//		return TRUE;
//	}
	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
        int nCount = (unsigned int)GetCount();
        int nIndex = 0;
		CExportSymbolNode *pNode = NULL;
		
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer << nCount;
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(short));
		}
		else
		{
		}
		
		for (nIndex=0; nIndex< nCount; nIndex++)
		{
			pNode = GetAtIndex(nIndex);
			pNode->Write(oBBuffer);
		}
		
		return TRUE;
	}
};

class CStringTable : public CTLinkList<char>
{
public:
	CStringTable()
	{
	}

	virtual ~CStringTable()
	{
		DeleteAll();
	}

	//CTLinkList<char> m_listChild;

	int Find(const char *pString)
	{
		long nIndex = 0;
		long nCount = GetCount();
		int nFind = -1;
		char *p = NULL;
		
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			p = GetAtIndex(nIndex);
			
			if ( strcmp ( p, pString ) == 0 )
			{
				nFind = nIndex;
				break;
			}
		}
		
		return nFind;
	}
	int Add(char *pString)
	{
		int iIndex = Find(pString);
		int iLen = strlen(pString);

		if (iIndex == -1)
		{
			char *p = new char[iLen + 1];
			strcpy(p, pString);
			AddNode(p);
			iIndex = GetCount()-1;
		}
		
		return iIndex;
	}

//	BOOL Write(CFile *pFile)
//	{
//		unsigned int nCount = (unsigned int)GetCount();
//		unsigned int nIndex = 0;
//		unsigned int nStringLen = 0;
//		char *pString = NULL;
//
//		pFile->Write(&nCount, sizeof(unsigned short));
//		
//		for (nIndex=0; nIndex< nCount; nIndex++)
//		{
//			pString = GetAtIndex(nIndex);
//			nStringLen = strlen(pString);
//
//			pFile->Write(&nStringLen, sizeof(unsigned int));
//			pFile->Write(pString, nStringLen);
//		}
//		
//		return TRUE;
//	}

	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
        int nCount = (unsigned int)GetCount();
        int nIndex = 0;
        int nStringLen = 0;
		char *pString = NULL;
		
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer << nCount;
			
			for (nIndex=0; nIndex< nCount; nIndex++)
			{
				pString = GetAtIndex(nIndex);
				oBBuffer.WriteBufferEx( pString, strlen(pString));
			}
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(sizeof(long));
			
			for (nIndex=0; nIndex< nCount; nIndex++)
			{
				pString = GetAtIndex(nIndex);
				oBBuffer.AddBufferLength(strlen(pString)+1);
			}
		}
		else
		{
		}
		
		
		return TRUE;
	}
};

class CTAsmData
{
public:
	CTAsmData()
	{
		m_iIsSetStackSizeFound = 0;
		m_cVersionMajor = VERSION_MAJOR;
		m_cVersionMinor = VERSION_MINOR;
		CTAsmInstructs::Create();
	}

	virtual ~CTAsmData()
	{
		CTAsmInstructs::Release();
	}

public:
	unsigned char m_cVersionMajor;
	unsigned char m_cVersionMinor;

	CScriptHeader m_oScriptHeader;          // Script header data
	int m_iIsSetStackSizeFound;             // Has the SetStackSize directive been
	int m_iIsSetPriorityFound;              // Has the SetPriority directive been

	CInstructions m_oInstructions;                  // Pointer to a dynamically allocated
	CFunctions   m_oFuncTable;                         // The function table
	CLabelNodes  m_oLabelTable;                        // The label table
	CTasmSymbols m_oSymbolTable;                       // The symbol table
	CStringTable m_oStringTable;                       // The string table
	CStringTable m_oHostAPICallTable;                  // The host API call table
	CExportSymbolNodes m_oExportSymbols;

//	BOOL Write(CFile *pFile)
//	{
//		pFile->Write(TSE_ID_STRING, TSE_ID_STRING_LEN);
//		pFile->Write(&m_cVersionMajor, sizeof(unsigned char));
//		pFile->Write(&m_cVersionMinor, sizeof(unsigned char));
//
//		m_oScriptHeader.Write(pFile);
//		m_oInstructions.Write(pFile);
//		int iPos = pFile->GetPosition();
//		m_oStringTable.Write(pFile);
//		m_oFuncTable.Write(pFile);
//		m_oHostAPICallTable.Write(pFile);
//		m_oExportSymbols.Write(pFile);
//		
//		return TRUE;
//	}
	BOOL Write(CWSerializeBuff  &oBBuffer)
	{
		if (oBBuffer.IsWriteMode())
		{
			oBBuffer <<  TSE_ID_STRING[0];
			oBBuffer <<  TSE_ID_STRING[1];
			oBBuffer <<  TSE_ID_STRING[2];
			oBBuffer <<  TSE_ID_STRING[3];
			oBBuffer <<  m_cVersionMajor;
			oBBuffer <<  m_cVersionMinor;
		}
		else if (oBBuffer.IsCalSizeMode())
		{
			oBBuffer.AddBufferLength(6);
		}
		
		m_oScriptHeader.Write(oBBuffer);
		m_oInstructions.Write(oBBuffer);
		m_oStringTable.Write(oBBuffer);
		m_oFuncTable.Write(oBBuffer);
		m_oHostAPICallTable.Write(oBBuffer);
		m_oExportSymbols.Write(oBBuffer);
		
		return TRUE;
	}

	BOOL Write(const CString &strFile)
	{
		CWSerializeBuff  oBBuffer;
		
// 		oBBuffer.SetCalSizeMode();
// 		Write(oBBuffer);
// 		oBBuffer.AllocBuffer(10);
// 		oBBuffer.SetWriteMode();
// 		Write(oBBuffer);
		WriteToBuffer(oBBuffer);

		return oBBuffer.WriteToFile(strFile);
	}

	void WriteToBuffer(CWSerializeBuff &oBuffer)
	{
		oBuffer.SetCalSizeMode();
		Write(oBuffer);
		oBuffer.AllocBuffer(10);
		oBuffer.SetWriteMode();
		Write(oBuffer);
	}
};

class CTAsmParser  : public CTAsmData, public CXvmBuffer
{
public:
	CTAsmParser();
	virtual ~CTAsmParser();
	void FreeParser();

protected:
	void AllocMemBuffer(long nBufferLen);
	
public:
	virtual BOOL ReadFromFile(const CString &strFile);
	virtual BOOL WriteToFile(const CString &strFile);

	//初始化缓冲区
	void InitBuffer(BSTR strBuff);
	void InitBuffer(char* strBuff);

	void InitBuffer(CWSerializeBuff &oBuffer)
	{
		FreeParser();
		char *pBuffer = oBuffer.Buffer();
		long nLen = oBuffer.Tell();
		AllocMemBuffer(nLen);
		memcpy(m_pBuffer, pBuffer, nLen);
	}

	void BuildTSE (const CString &strFile);
	void BuildTSE ();
	
public:
	CLexer m_oLexer;                        // The lexer
	char **m_ppstrSourceCode;               // Pointer to dynamically allocated
	int m_iSourceCodeLines;                 // Number of source lines
    char m_strSourceFilename[MAX_PATH];           // Source code filename
    char m_strExecFilename[MAX_PATH];             // Source code filename

	int m_iInstructStreamSize;                         // The number of instructions
	int m_iCurrInstructIndex;                          // The current instruction's index
	
	CTSyntaxs m_oTSyntaxs;
private:
	// ---- String Processing -----------------------------------------------------------------
	int IsCharWhitespace ( char cChar );
	int IsCharNumeric ( char cChar );
	int IsCharIdent ( char cChar );
	int IsCharDelimiter ( char cChar );
	void TrimWhitespace ( char ** pstrString );
	int IsStringWhitespace ( char * pstrString );
	int IsStringIdent ( char * pstrString );
	int IsStringInteger ( char * pstrString );
	int IsStringFloat( char * pstrString );
	void StripComments ( char * pstrSourceLine );
	
	void InitSourceCodeLines();

	//////////////////////////////////////////////////////////////////////////
	// define temp variables
	int  m_iIsFuncActive;
	char m_pstrIdentTemp [ MAX_IDENT_SIZE ];
	int  m_iCurrFuncIndex;
	char m_pstrFuncNameTemp [ MAX_IDENT_SIZE ];
	int  m_iCurrFuncParamCount;
	int  m_iCurrFuncLocalDataSize;
	CFunction * m_pCurrFuncTemp;
	
	void Assemble ();
	void Assemble_FirstPass_SetStackSize();
	void Assemble_FirstPass_SetPriority();
	void Assemble_FirstPass_Var();
	void Assemble_FirstPass_Func();
	void Assemble_FirstPass_ClosingBrace();
	void Assemble_FirstPass_Param();
	void Assemble_FirstPass_Instruction();
	void Assemble_FirstPass_Identifier();
	void Assemble_FirstPass();
	
	void Assemble_SecondPass_Func();
	void Assemble_SecondPass_ClosingBrace();
	void Assemble_SecondPass_Param();
	void Assemble_SecondPass_Instruction();
	void Assemble_SecondPass_Instruction_Int(OperandTypes CurrOpTypes, COperand *pOperand);
	void Assemble_SecondPass_Instruction_Float(OperandTypes CurrOpTypes, COperand *pOperand);
	void Assemble_SecondPass_Instruction_Quote(OperandTypes CurrOpTypes, COperand *pOperand);
	void Assemble_SecondPass_Instruction_Retval(OperandTypes CurrOpTypes, COperand *pOperand);
	void Assemble_SecondPass_Instruction_Identifier(OperandTypes CurrOpTypes, COperand *pOperand);
	void Assemble_SecondPass();

	// ---- Lexical Analysis ------------------------------------------------------------------
	Token GetNextToken (BOOL bCanSkipToNextLine = TRUE);
	char * GetCurrLexeme ();
	char GetLookAheadChar ();
	int SkipToNextLine ();
	int SkipWitespace(char *pString, unsigned int &nIndex)
	{
		// If the current character is not whitespace, exit the loop because the lexeme
		// is starting.
		while (  IsCharWhitespace ( pString[ nIndex ] ) )
		{
			nIndex++;
		}
		return nIndex;
	}

	void AddCodeError(const char* pszError, BOOL bSkipToNextLine = TRUE)
	{
		m_oTSyntaxs.AddSyntax(pszError, m_oLexer.m_iCurrSourceLine);
	}
	void AddCharExpectedError(char ch)
	{
		static const char *g_pszErrorMsgFormat = "'%c' expected";
		m_oTSyntaxs.AddSyntax(g_pszErrorMsgFormat, ch);
	}

	int AddSymbol ( char * pstrSymbol, int iSize, int iStackIndex, int iFuncIndex )
	{
		return m_oSymbolTable.Add(pstrSymbol, iSize, iStackIndex, iFuncIndex);
	}

	CTasmSymbol * FindSymbol ( char * pstrSymbol, int iFuncIndex );
	int GetStackIndex ( char * pstrSymbol, int iFuncIndex );
	int GetSize ( char * pstrIdent, int iFuncIndex );
	
	int AddFunc ( char * pstrName, int iEntryPoint );
	CFunction * GetFuncByName ( char * pstrName );
	void SetFuncInfo ( char * pstrName, int iParamCount, int iLocalDataSize );
	
	int AddLabel ( char * pstrLabel, int iTargetIndex, int iFuncIndex );
	CLabelNode* FindLabel ( char * pstrLabel, int iFuncIndex );
	
};



inline CTasmSymbol* CTAsmParser::FindSymbol ( char * pstrSymbol, int iFuncIndex )
{
	CTasmSymbol *pFind = m_oSymbolTable.Find(pstrSymbol, iFuncIndex);

	if (pFind == NULL && iFuncIndex > 0)
	{//如果按照函数索引没有找到，则在全局变量中查找
		pFind = m_oSymbolTable.Find(pstrSymbol, 0);
	}

	return pFind;
}

inline char* CTAsmParser::GetCurrLexeme ()
{
	return m_oLexer.m_pstrCurrLexeme;
}

/******************************************************************************************
*
*   GetFuncByName ()
*
*   Returns a CFunction structure pointer corresponding to the specified name.
*/

inline CFunction * CTAsmParser::GetFuncByName ( char * pstrName )
{
	return m_oFuncTable.Find(pstrName);;
}

/******************************************************************************************
*
*   AddFunc ()
*
*   Adds a function to the function table.
*/

inline int CTAsmParser::AddFunc ( char * pstrName, int iEntryPoint )
{
	return m_oFuncTable.Add(pstrName, iEntryPoint);
}

/******************************************************************************************
*
*   SetFuncInfo ()
*
*   Fills in the remaining fields not initialized by AddFunc ().
*/

inline void CTAsmParser::SetFuncInfo ( char * pstrName, int iParamCount, int iLocalDataSize )
{
	m_oFuncTable.SetFunInfo(pstrName, iParamCount, iLocalDataSize);
}
	
/******************************************************************************************
*
*   AddLabel ()
*
*   Adds a label to the label table.
*/

inline int CTAsmParser::AddLabel ( char * pstrLabel, int iTargetIndex, int iFuncIndex )
{
	return m_oLabelTable.Add(pstrLabel, iTargetIndex, iFuncIndex);
}

/******************************************************************************************
*
*   FindLabel ()
*
*   Returns a pointer to the label structure corresponding to the identifier and function
*   index.
*/
inline CLabelNode* CTAsmParser::FindLabel ( char * pstrLabel, int iFuncIndex )
{
	return m_oLabelTable.Find(pstrLabel, iFuncIndex);
}


/******************************************************************************************
*
*	GetStackIndex ()
*
*	Returns a symbol's stack index based on its identifier and function index.
*/

inline int CTAsmParser::GetStackIndex ( char * pstrSymbol, int iFuncIndex )
{
	// Get the symbol's information
	CTasmSymbol *pSymbol = FindSymbol ( pstrSymbol, iFuncIndex );
	
	// Return its stack index
	if (pSymbol == NULL)
	{
		return -2;
	}
	else
	{
		return pSymbol->m_iStackIndex;
	}
}

/******************************************************************************************
*
*	GetSizeByIndent ()
*
*	Returns a variable's size based on its identifier.
*/

inline int CTAsmParser::GetSize ( char * pstrIdent, int iFuncIndex )
{
	// Get the symbol's information
	CTasmSymbol * pSymbol = FindSymbol ( pstrIdent, iFuncIndex );
	
	// Return its size
	return pSymbol->m_iSize;
}


#endif // !defined(_TASM_H__)
