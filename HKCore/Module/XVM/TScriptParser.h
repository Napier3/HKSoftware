// CTScriptParser.h: interface for the CTScriptParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TSCRIPTPARSER_H__)
#define _TSCRIPTPARSER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BaseClass/WSerializeBuff.h"
#include "TSyntax.h"
#include "../System/XStack.h"
#include "SymbolTable.h"
#include "FuncTable.h"
#include "InstructionLookup.h"
#include "TAsmParser.h"


#define SCOPE_GLOBAL                    0       // Global scope

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
// };

class CTScriptInstructs : public CTInstructs
{
private:
	CTScriptInstructs();
	virtual ~CTScriptInstructs();
	
	virtual void InitInstructTable();
	
protected:
	static long m_nRefCount;
	static CTScriptInstructs* p_pTScriptInstructs;

public:
	static CTScriptInstructs* Create();
	static void Release();
	
	static CTInstruct* Find(const char *pstrName);
	static BOOL IsInstructExist (const char *pstrName);
};

class CTScriptParser  :  public CXvmBuffer
{
public:
	CTScriptParser();
	virtual ~CTScriptParser();

protected:
	int m_iSourceCodeLines;
	CTLinkList<char> m_oSourceCodeLines;               // Pointer to dynamically allocated	
	
	void AllocMemBuffer(long nBufferLen);

	void FreeParser();
	void InitSourceCodeLines();
	
	char g_pstrSourceFile [ MAX_FILENAME_SIZE ];
	char m_pstrOutputFile [ MAX_FILENAME_SIZE ];
	char m_pszCurrFuncName[MAX_PATH];

	long Parse(const char *pszWriteFileName);
	void OptimizeCode_Only();
	void OptimizeCode_EmitCodeFile(const char *pszWriteFileName);
public:
	virtual long ParseText(const CString &strScript, const CString &strWriteFileName);
	virtual long ParseText(const char *strScript, const char *pszWriteFileName);
	virtual long ParseAsm(CTAsmParser *pTasmParser);
	virtual BOOL ParseFile(const CString &strFile, const char *pszWriteFileName);
	virtual BOOL ReadFromFile(const CString &strFile);
	virtual BOOL WriteToFile(const CString &strFile);
	
	//³õÊ¼»¯»º³åÇø
	void InitBuffer(BSTR strBuff);
	void InitBuffer(char* strBuff);
	void InitBuffer(const CString &strBuff);

	int _RegisterHostApiFunc(const char *pstrName, int iParamCount)
	{
		int iIndex = AddFunc(pstrName, TRUE);
		SetFuncParamCount(iIndex, iParamCount);
		return iIndex;
	}
	
	void CompileSourceFile ();
	CTSyntaxs* GetTSyntaxs ()
	{
		return &m_oTSyntaxs;
	}
	long GetTSyntaxsCount ()
	{
		return m_oTSyntaxs.GetCount();
	}
	
	CTSyntaxs m_oTSyntaxs;	

private:
	void PreprocessSourceFile ();
//////////////////////////////////////////////////////////////////////////
////////////////Lexical analyzer module///////////////////////////////////
public:
    typedef struct _LexerState                      // The lexer's state
    {
        int   m_iCurrLineIndex;                     // Current line index
        char* m_pCurrLine;                          // Current line node pointer
		int    m_nCurrLineLen;                      //Current line node string length
        Token m_CurrToken;                          // Current token
        char  m_pstrCurrLexeme [ MAX_LEXEME_SIZE ]; // Current lexeme
        int   m_iCurrLexemeStart;                   // Current lexeme's starting index
        int   m_iCurrLexemeEnd;                     // Current lexeme's ending index
        int   m_iCurrOp;                            // Current operator
		POS m_posCurrLine;                        //Curr Node Position in source code line
    }LexerState;
	
    typedef struct _OpState                         // Operator state
    { 
        char m_cChar;                               // State character
        int  m_iSubStateIndex;                      // Index into sub state array where sub
        int  m_iSubStateCount;                      // Number of substates
        int  m_iIndex;                              // Operator index
    }OpState;
	
	
	LexerState m_oCurrLexerState;                    // The current lexer state
	LexerState m_oPrevLexerState;                    // The previous lexer state (used for
	
	CSymbolTable m_oSymbolTable;
	CFuncTable   m_oFuncTable;
	CTLinkList<char> m_oStringTable;
	
//	static const OpState m_OpChars0 [ MAX_OP_STATE_COUNT ];
//	static const OpState m_OpChars1 [ MAX_OP_STATE_COUNT ];
//	static const OpState m_OpChars2 [ MAX_OP_STATE_COUNT ];
//	static const char m_cDelims [ MAX_DELIM_COUNT ];
	int m_iTempVar0SymbolIndex;
	int m_iTempVar1SymbolIndex;
	int m_iTempVar2SymbolIndex;
	
private:
	// ---- Script ----------------------------------------------------------------------------
	typedef struct _ScriptHeader                    // Script header data
	{
		int m_iStackSize;                             // Requested stack size
		
		int m_iIsMainFuncPresent;                     // Is _Main () present?
		int m_iMainFuncIndex;							// _Main ()'s function index
		
		int m_iPriorityType;                          // The thread priority type
		int m_iUserPriority;                          // The user-defined priority (if any)
	}	ScriptHeader;
	
	ScriptHeader m_ScriptHeader;

private:
	// ---- Function Prototypes -------------------------------------------------------------------
    void ResetLexer ();
    void CopyLexerState ( LexerState & pDestState, LexerState & pSourceState );
	
    int GetOpStateIndex ( char cChar, int iCharIndex, int iSubStateIndex, int iSubStateCount );
    int IsCharOpChar ( char cChar, int iCharIndex, int iCurrLexState );
    OpState GetOpState ( int iCharIndex, int iStateIndex );
    int IsCharDelim ( char cChar );
    int IsCharWhitespace ( char cChar );
    int IsCharNumeric ( char cChar );
    int IsCharIdent ( char cChar );
	
    char GetNextChar (BOOL &bChangLine);
    Token GetNextToken ();
	Token TokenReservedKey();
    void RewindTokenStream ();
    Token GetCurrToken ();
    char * GetCurrLexeme ();
    void CopyCurrLexeme ( char * pstrBuffer );
    int GetCurrOp ();
    char GetLookAheadChar ();
	
	int SkipToNextLine ();
	int SkipToNextStatement ()
	{
		return SkipToNextLine();
	}

	char * GetCurrSourceLine ();
    int GetCurrSourceLineIndex ();
    int GetLexemeStartIndex ();

//////////////////////////////////////////////////////////////////////////
//////////////////Parser module///////////////////////////////////////////
private:
	// ---- Data Structures -----------------------------------------------------------------------
    typedef struct _Expression                                // Expression instance
    {
        int m_iStackOffset;                               // The current offset of the stack
    }Expression;
	
    typedef struct Loop                                 // Loop instance
    {
        int m_iStartTargetIndex;                          // The starting jump target
        int m_iEndTargetIndex;                            // The ending jump target
    } Loop;
	
	int m_iCurrScope;                               // The current scope
    CXStackP<Loop> m_oLoopStack;                              // Loop handling stack

private:
	// ---- Function Prototypes -------------------------------------------------------------------
	BOOL ReadToken ( Token ReqToken );
	
    int IsOpRelational ( int iOpType )
	{
		if ( 
			iOpType != OP_TYPE_EQUAL &&
			iOpType != OP_TYPE_NOT_EQUAL &&
			iOpType != OP_TYPE_LESS &&
			iOpType != OP_TYPE_GREATER &&
			iOpType != OP_TYPE_LESS_EQUAL &&
			iOpType != OP_TYPE_GREATER_EQUAL )
			return FALSE;
		else
			return TRUE;
	}
	int IsOpLogical ( int iOpType )
	{
		if ( iOpType != OP_TYPE_LOGICAL_AND &&
			iOpType != OP_TYPE_LOGICAL_OR &&
			iOpType != OP_TYPE_LOGICAL_NOT )
			return FALSE;
		else
			return TRUE;
	}
	
    BOOL ParseSourceCode ();
	
    BOOL ParseStatement ();
    BOOL ParseBlock ();
	
    BOOL ParseVar ();
    BOOL ParseHost ();
    BOOL ParseFunc ();
	
    BOOL ParseExpr (/*int iTrIndex*/);
    BOOL ParseSubExpr (/*int iTrIndex*/);
    BOOL ParseTerm (/*int iTrIndex*/);
    BOOL ParseFactor (/*int iTrIndex*/);
	
    BOOL ParseIf ();
    BOOL ParseWhile ();
    BOOL ParseFor ();
    BOOL ParseBreak ();
    BOOL ParseContinue ();
    BOOL ParseReturn ();
	
    BOOL ParseAssign ();
    BOOL ParseFuncCall ();

	BOOL ParseMathFunc(/*int iTrIndex*/);
	void AddCodeSyntaxError(const char *pstrError, const char *pstrMsg, long nType=TSYNTAX_TYPE_ERROR)
	{
		CTSyntax *pSyntax = m_oTSyntaxs.AddSyntax(pstrError, pstrMsg, m_oCurrLexerState.m_iCurrLineIndex, nType);
		pSyntax->SetFuncName(m_pszCurrFuncName);
		//SkipToNextLine();
	}
	void AddCodeSyntaxError(const char *pstrError, long nType=TSYNTAX_TYPE_ERROR)
	{
		CTSyntax *pSyntax = m_oTSyntaxs.AddSyntax(pstrError, m_oCurrLexerState.m_iCurrLineIndex, nType);
		pSyntax->SetFuncName(m_pszCurrFuncName);
		//SkipToNextLine();
	}
	void AddCodeSyntaxError2(const char *pstrTokenType, long nType=TSYNTAX_TYPE_ERROR)
	{
		CTSyntax *pSyntax = m_oTSyntaxs.AddSyntax("%s  expected", pstrTokenType, m_oCurrLexerState.m_iCurrLineIndex, nType);
		pSyntax->SetFuncName(m_pszCurrFuncName);
		//SkipToNextLine();
	}
	

private:
	CSymbolNode * GetSymbolByIndex ( int iIndex )
	{
		return m_oSymbolTable.GetSymbolByIndex(iIndex);
	}
	
    CSymbolNode * GetSymbolByIdent (const  char * pstrName, int iScope )
	{
		CSymbolNode *pSymbol = m_oSymbolTable.GetSymbolByIdent(pstrName, iScope);

		if (pSymbol == NULL)
		{
			if (iScope != SCOPE_GLOBAL)
			{
				pSymbol = m_oSymbolTable.GetSymbolByIdent(pstrName, SCOPE_GLOBAL);
			}
		}

		return pSymbol;
	}
	
	int GetSizeByIdent (const  char * pstrName, int iScope )
	{
		return m_oSymbolTable.GetSizeByIdent(pstrName, iScope);
	}
	
	int AddSymbol (const  char * pstrName, int iSize, int iScope, int iType )
	{
		return m_oSymbolTable.AddSymbol(pstrName, iSize, iScope, iType);
	}
   
	CFuncNode * GetFuncByIndex ( int iIndex )
	{
		return m_oFuncTable.GetFuncByIndex(iIndex);
	}

    CFuncNode * GetFuncByName ( char * pstrName )
	{
		return m_oFuncTable.GetFuncByName(pstrName);
	}

    int GetFuncIndexByName ( char * pstrName , bool bWithHost)
	{
		return m_oFuncTable.GetFuncIndexByName(pstrName, bWithHost);
	}
	
    int AddFunc ( const char * pstrName, int iIsHostAPI )
	{
		int iIndex = 0;
		bool bMainFunc = false;

		iIndex = m_oFuncTable.AddFunc(pstrName, iIsHostAPI, bMainFunc);

		if (bMainFunc)
		{
			m_ScriptHeader.m_iIsMainFuncPresent = TRUE;
            m_ScriptHeader.m_iMainFuncIndex = iIndex;
		}

		return iIndex;
	}
	
	void SetFuncParamCount ( int iIndex, int iParamCount )
	{
		m_oFuncTable.SetFuncParamCount(iIndex, iParamCount);
	}
	
	void AddICodeSourceLine ( int iFuncIndex, char * pstrSourceLine )
	{
		m_oFuncTable.AddICodeSourceLine(iFuncIndex, pstrSourceLine);
	}
	int AddICodeInstr ( int iFuncIndex, int iOpcode )	
	{
		return m_oFuncTable.AddICodeInstr(iFuncIndex, iOpcode);
	}
	
	void AddICodeOp ( int iFuncIndex, int iInstrIndex, CICodeOperand *pValue )
	{
		m_oFuncTable.AddICodeOp(iFuncIndex, iInstrIndex, pValue);
	}
	void AddIntICodeOp ( int iFuncIndex, int iInstrIndex, int iValue )
	{
		m_oFuncTable.AddIntICodeOp(iFuncIndex, iInstrIndex, iValue);
	}
    void AddFloatICodeOp ( int iFuncIndex, int iInstrIndex, float fValue )
	{
		m_oFuncTable.AddFloatICodeOp(iFuncIndex, iInstrIndex, fValue);
	}
    void AddStringICodeOp ( int iFuncIndex, int iInstrIndex, int iStringIndex )
	{
		m_oFuncTable.AddStringICodeOp(iFuncIndex, iInstrIndex, iStringIndex);
	}
    void AddVarICodeOp ( int iFuncIndex, int iInstrIndex, int iSymbolIndex )
	{
		m_oFuncTable.AddVarICodeOp(iFuncIndex, iInstrIndex, iSymbolIndex);
	}
    void AddArrayIndexAbsICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffset )
	{
		m_oFuncTable.AddArrayIndexAbsICodeOp(iFuncIndex, iInstrIndex, iArraySymbolIndex, iOffset);
	}
    void AddArrayIndexVarICodeOp ( int iFuncIndex, int iInstrIndex, int iArraySymbolIndex, int iOffsetSymbolIndex )
	{
		m_oFuncTable.AddArrayIndexVarICodeOp(iFuncIndex, iInstrIndex, iArraySymbolIndex, iOffsetSymbolIndex);
	}
    void AddFuncICodeOp ( int iFuncIndex, int iInstrIndex, int iOpFuncIndex )
	{
		m_oFuncTable.AddFuncICodeOp(iFuncIndex, iInstrIndex, iOpFuncIndex);
	}
    void AddRegICodeOp ( int iFuncIndex, int iInstrIndex, int iRegCode )
	{
		m_oFuncTable.AddRegICodeOp(iFuncIndex, iInstrIndex, iRegCode);
	}
    void AddJumpTargetICodeOp ( int iFuncIndex, int iInstrIndex, int iTargetIndex )	
	{
		m_oFuncTable.AddJumpTargetICodeOp(iFuncIndex, iInstrIndex, iTargetIndex);
	}
    void AddICodeJumpTarget ( int iFuncIndex, int iTargetIndex )
	{
		m_oFuncTable.AddICodeJumpTarget(iFuncIndex, iTargetIndex);
	}
	CICodeNode * GetICodeNodeByImpIndex ( int iFuncIndex, int iInstrIndex )
	{
		return m_oFuncTable.GetICodeNodeByImpIndex(iFuncIndex, iInstrIndex);
	}
	int AddString(const char* pstrData);

public:
	void OptimizeCode();
	void OptimizeCode_Pop_Push();
	void OptimizeCode_Mov();
	void OptimizeCode_Mov_Instr();

public:
	void EmitCode_Buffer ();
	void EmitCode_File (const CString &strFileName);
	CWSerializeBuff* GetAsmBuffer()		{	return &m_oAnsiTasmBuffer;	}
	
protected:
	void EmitHeader_Buffer ();
	void EmitDirectives_Buffer ();
	void EmitScopeSymbols_Buffer ( int iScope, int iType );
	void EmitFunc_Buffer ( CFuncNode * pFunc );
	void EmitInstruct_Buffer(char *pstrInstr, CICodeNode *pICode);
	void EmitInstruct_Buffer(CString &strText, CICodeNode *pICode);
	CWSerializeBuff m_oAnsiTasmBuffer;	
	
	static const char m_ppstrInsctructs [][ 12 ];
};

#endif // !defined(_TSCRIPTPARSER_H__)
