// CTScriptParser.cpp: implementation of the CTScriptParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TScriptParser.h"
//#include "../../Module/System/AtlFile.h"
#include "../AtlMemBuffer/AnsiStringPrintf.h"
#include "../API/FileApi.h"
#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long CTScriptInstructs::m_nRefCount = 0;
CTScriptInstructs* CTScriptInstructs::p_pTScriptInstructs = NULL;

CTScriptInstructs::CTScriptInstructs()
{
	InitInstructTable();
}

CTScriptInstructs:: ~CTScriptInstructs()
{

}

void CTScriptInstructs::Release()
{
	m_nRefCount--;

	if (m_nRefCount == 0)
	{
		delete p_pTScriptInstructs;
		p_pTScriptInstructs = NULL;
	}
}

void CTScriptInstructs::InitInstructTable()
{
	int iInstrIndex = 0;
	CTInstruct* p = NULL;

	//////////////////////////////////////////////////////////////////////////
	//math instructions
	// abs          Destination, Source   [abs val, 5]
	p = AddInstructLookup ( g_pstrScriptKey_Func_ABS, TOKEN_TYPE_RSRVD_FUNC_ABS, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// pow          Destination, Source, Source   [pow val, 5, 2]
	p = AddInstructLookup ( g_pstrScriptKey_Func_POW, TOKEN_TYPE_RSRVD_FUNC_POW, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);		
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// sqrt          Destination, Source   [sqrt val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_SQRT, TOKEN_TYPE_RSRVD_FUNC_SQRT, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// log10          Destination, Source   [log10 val, 5]
	p = AddInstructLookup ( g_pstrScriptKey_Func_LOG10, TOKEN_TYPE_RSRVD_FUNC_LOG10, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// log          Destination, Source   [log val, 5]
	p = AddInstructLookup ( g_pstrScriptKey_Func_LOG, TOKEN_TYPE_RSRVD_FUNC_LOG, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// sin          Destination, Source   [sin val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_SIN, TOKEN_TYPE_RSRVD_FUNC_SIN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// cos          Destination, Source   [cos val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_COS, TOKEN_TYPE_RSRVD_FUNC_COS, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// tan          Destination, Source   [tan val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_TAN, TOKEN_TYPE_RSRVD_FUNC_TAN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// ctan          Destination, Source   [ctan val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_CTAN, TOKEN_TYPE_RSRVD_FUNC_CTAN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// asin          Destination, Source   [asin val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_ASIN, TOKEN_TYPE_RSRVD_FUNC_ASIN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// acos          Destination, Source   [acos val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_ACOS, TOKEN_TYPE_RSRVD_FUNC_ACOS, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// atan          Destination, Source   [atan val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_ATAN, TOKEN_TYPE_RSRVD_FUNC_ATAN, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// atan2          Destination, Source, Source   [atan2 val, 0.707, 1]
	p = AddInstructLookup ( g_pstrScriptKey_Func_ATAN2, TOKEN_TYPE_RSRVD_FUNC_ATAN2, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// min          Destination, Source, Source   [min val, 0.707, 2]
	p = AddInstructLookup ( g_pstrScriptKey_Func_MIN, TOKEN_TYPE_RSRVD_FUNC_MIN, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// max          Destination, Source, Source   [max val, 0.707, 2]
	p = AddInstructLookup ( g_pstrScriptKey_Func_MAX, TOKEN_TYPE_RSRVD_FUNC_MAX, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// ceil          Destination, Source   [ceil val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_CEIL, TOKEN_TYPE_RSRVD_FUNC_CEIL, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// floor          Destination, Source   [floor val, 0.707]
	p = AddInstructLookup ( g_pstrScriptKey_Func_FLOOR, TOKEN_TYPE_RSRVD_FUNC_FLOOR, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// hypot          Destination, Source, Source   [hypot val, 0.707, 2]
	p = AddInstructLookup ( g_pstrScriptKey_Func_HYPOT, TOKEN_TYPE_RSRVD_FUNC_HYPOT, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// fmod          Destination, Source, Source   [fmod val, 2.5, 1.2]
	p = AddInstructLookup ( g_pstrScriptKey_Func_FMOD, TOKEN_TYPE_RSRVD_FUNC_FMOD, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// digit          Destination, Source, Source   [digit val, 2.5, 1.2]
	p = AddInstructLookup ( g_pstrScriptKey_Func_DIGIT, TOKEN_TYPE_RSRVD_FUNC_DIGIT, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
	
	// binary          Destination, Source, Source   [binary val, 32, 5]
	p = AddInstructLookup ( g_pstrScriptKey_Func_BINARY, TOKEN_TYPE_RSRVD_FUNC_BINARY, 3 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF);
	p->SetOpType (1, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// atof          Destination, Source   [atof val, "10"]
	p = AddInstructLookup ( g_pstrScriptKey_Func_ATOF, TOKEN_TYPE_RSRVD_FUNC_ATOF, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// atol          Destination, Source   [atol val, "10"]
	p = AddInstructLookup ( g_pstrScriptKey_Func_ATOL, TOKEN_TYPE_RSRVD_FUNC_ATOL, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_STRING |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// ftoa          Destination, Source   [ftoa val, 10.5]
	p = AddInstructLookup ( g_pstrScriptKey_Func_FTOA, TOKEN_TYPE_RSRVD_FUNC_FTOA, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
		
	// ltoa          Destination, Source   [ltoa val, 10.5]
	p = AddInstructLookup ( g_pstrScriptKey_Func_LTOA, TOKEN_TYPE_RSRVD_FUNC_LTOA, 2 );
	p->SetOpType (0, OPERAND_FLAG_TYPE_INT |
		OPERAND_FLAG_TYPE_FLOAT |
		OPERAND_FLAG_TYPE_MEM_REF);
}

CTInstruct* CTScriptInstructs::Find(const char *pstrName)
{
	ASSERT (p_pTScriptInstructs != NULL);

	return p_pTScriptInstructs->In_Find(pstrName);
}

BOOL CTScriptInstructs::IsInstructExist (const char *pstrName)
{
	ASSERT (p_pTScriptInstructs != NULL);

	return p_pTScriptInstructs->In_IsInstructExist(pstrName);
}

CTScriptInstructs* CTScriptInstructs::Create()
{
	m_nRefCount++;

	if (m_nRefCount == 1)
	{
		p_pTScriptInstructs = new CTScriptInstructs();
	}
	
	return p_pTScriptInstructs;
}

// ---- Operators -------------------------------------------------------------------------

// ---- First operator characters
static const CTScriptParser::OpState g_OpChars0 [ MAX_OP_STATE_COUNT ] =	
{ 
	{ '+', 0,  2, 0  },  { '-', 2,  2, 1  }, { '*', 4, 1,  2  }, { '/', 5, 1, 3   },
	{ '%', 6,  1, 4  },  { '^', 7,  1, 5  }, { '&', 8, 2,  6  }, { '|', 10, 2, 7  },
	{ '#', 12, 1, 8  },  { '~', 0,  0, 9  }, { '!', 13, 1, 10 }, { '=', 14, 1, 11 },
	{ '<', 15, 2, 12 },  { '>', 17, 2, 13 }, { '$', 19, 1, 35 } 
};

// ---- Second operator characters

static const CTScriptParser::OpState g_OpChars1 [ MAX_OP_STATE_COUNT ] = 
{ 
	{ '=', 0, 0, 14 }, { '+', 0, 0, 15 },     // +=, ++
	{ '=', 0, 0, 16 }, { '-', 0, 0, 17 },     // -=, --
	{ '=', 0, 0, 18 },                        // *=
	{ '=', 0, 0, 19 },                        // /=
	{ '=', 0, 0, 20 },                        // %=
	{ '=', 0, 0, 21 },                        // ^=
	{ '=', 0, 0, 22 }, { '&', 0, 0, 23 },     // &=, &&
	{ '=', 0, 0, 24 }, { '|', 0, 0, 25 },     // |=, ||
	{ '=', 0, 0, 26 },                        // #=
	{ '=', 0, 0, 27 },                        // !=
	{ '=', 0, 0, 28 },                        // ==
	{ '=', 0, 0, 29 }, { '<', 0, 1, 30 },     // <=, <<
	{ '=', 0, 0, 31 }, { '>', 1, 1, 32 },     // >=, >>
	{ '=', 0, 0, 36 }                        // $=
};

// ---- Third operator characters

static const CTScriptParser::OpState g_OpChars2 [ MAX_OP_STATE_COUNT ] = 
{ 
	{ '=', 0, 0, 33 }, // <<=
	{ '=', 0, 0, 34 }  // >>=
};

// ---- Delimiters ------------------------------------------------------------------------

static const char g_cDelims [ MAX_DELIM_COUNT ] = { ',', '(', ')', '[', ']', '{', '}', ';' };

#define TAB_STOP_WIDTH                      8       // The width of a tab stop in

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTScriptParser::CTScriptParser()
{
	CTScriptInstructs::Create();
	memset(g_pstrSourceFile, 0, MAX_FILENAME_SIZE);
	memset(m_pstrOutputFile, 0, MAX_FILENAME_SIZE);
	
	m_iSourceCodeLines = 0;

	m_iTempVar0SymbolIndex = 0;
	m_iTempVar1SymbolIndex = 0;
	m_iTempVar2SymbolIndex = 0;

	memset(&m_ScriptHeader, 0, sizeof(ScriptHeader));
	m_pszCurrFuncName[0] = 0;
}

CTScriptParser::~CTScriptParser()
{
	FreeParser();
	CTScriptInstructs::Release();
}

void CTScriptParser::FreeParser()
{
	m_oSourceCodeLines.RemoveAll();
	m_oTSyntaxs.DeleteAll();
	m_oSymbolTable.DeleteAll();
	m_oFuncTable.DeleteAll();
	m_oStringTable.DeleteAll();
	m_oLoopStack.Empty();
	
	Release();
	
	//	m_iSourceCodeLines = 0;
	//	m_iInstructStreamSize = 0;
	//	m_iCurrInstructIndex = 0;
}


void CTScriptParser::OptimizeCode_Only()
{
	OptimizeCode_Pop_Push();
	OptimizeCode_Mov();
	OptimizeCode_Mov_Instr();
	OptimizeCode_Mov_Instr();
}

void CTScriptParser::OptimizeCode_EmitCodeFile(const char *pszWriteFileName)
{
	CString strPath;
	strPath = _P_GetLibraryPath();
	strPath += _T("XVM");
	CreateAllDirectories(strPath);
	strPath += _P_FOLDER_PATH_SEPARATOR_;
	strPath += pszWriteFileName;
	CString strFile;

	strFile = strPath + _T("_0.tasm");
	EmitCode_File(strFile);

	OptimizeCode_Pop_Push();
	strFile = strPath + _T("_1.tasm");
	EmitCode_File(strFile);

	return;

	OptimizeCode_Mov();
	strFile = strPath + _T("_2.tasm");
	EmitCode_File(strFile);

	OptimizeCode_Mov_Instr();
	strFile = strPath + _T("_3.tasm");
	EmitCode_File(strFile);

	OptimizeCode_Mov_Instr();
	strFile = strPath + _T(".tasm");
	EmitCode_File(strFile);
}

long CTScriptParser::Parse(const char *pszWriteFileName)
{
	CompileSourceFile();

	long nErrors = m_oTSyntaxs.GetErrorCount();

	if (nErrors == 0)
	{
		if (pszWriteFileName == NULL)
		{
			OptimizeCode_Only();
			return 0;
		}

		if (strlen(pszWriteFileName) < 1)
		{
			OptimizeCode_Only();
			return 0;
		}

		OptimizeCode_EmitCodeFile(pszWriteFileName);
	}
	else
	{
		m_oTSyntaxs.Log();
	}

	return nErrors;
}

long CTScriptParser::ParseText(const CString &strScript, const CString &strWriteFileName)
{
	FreeParser();
	InitBuffer(strScript);
	char *pszWriteFileName = NULL;
	CString_to_char(strWriteFileName, &pszWriteFileName);
	long nRet = Parse(pszWriteFileName);
	delete pszWriteFileName;

	return nRet;
}

long CTScriptParser::ParseText(const char *strScript, const char *pszWriteFileName)
{
	if (pszWriteFileName != NULL)
	{
		if (strlen (pszWriteFileName) > 1)
		{
			CString strFile;
			strFile = _P_GetLibraryPath();
			strFile += _T("XVM\\");
			strFile += pszWriteFileName;
			strFile += _T(".tss");

			CFile file;

			if (file.Open(strFile, CFile::modeCreate | CFile::modeWrite))
			{
				file.Write(strScript, strlen(strScript));
				file.Close();
			}
		}
	}

	FreeParser();
	InitBuffer((char*)strScript);
	return Parse(pszWriteFileName);
}

long CTScriptParser::ParseAsm(CTAsmParser *pTasmParser)
{
	ASSERT (pTasmParser != NULL);
	pTasmParser->InitBuffer(m_oAnsiTasmBuffer);
	pTasmParser->BuildTSE();

	long nErrors = pTasmParser->m_oTSyntaxs.GetCount();

	if (nErrors > 0)
	{
        m_oTSyntaxs.XAppend(pTasmParser->m_oTSyntaxs);
		pTasmParser->m_oTSyntaxs.RemoveAll();
	}		

	return nErrors;
}

BOOL CTScriptParser::ParseFile(const CString &strFile, const char *pszWriteFileName)
{
	if (!ReadFromFile(strFile))
	{
		return FALSE;
	}

	Parse(pszWriteFileName);

	return TRUE;
}

//*********************************************************************
//ReadFromFile				public
//*********************************************************************
//描述：	从文件中获取数据
//参数：	strFile：文件名称
//返回：	无
BOOL CTScriptParser::ReadFromFile(const CString &strFile)
{
	FreeParser();
	
	CFile file;
	BOOL bTrue = file.Open(strFile, CFile::modeRead);
	
	if(bTrue)
	{
		m_nLength = file.GetLength();
		AllocMemBuffer(m_nLength);
		file.Read(m_pBuffer,m_nLength*sizeof(char));
		m_pBuffer[m_nLength] = 0;
		file.Close();

		CString_to_char(strFile, g_pstrSourceFile);
		CString_to_char(strFile, m_pstrOutputFile);
		int iPos = strlen(m_pstrOutputFile);
		strcpy(m_pstrOutputFile + iPos - 4, FILE_EXT_TASM);
	}
	
	return bTrue;
}

void CTScriptParser::InitBuffer(BSTR strBuff)
{
#ifndef _PSX_QT_LINUX_
    long nLen = 2*(wcslen(strBuff)+1);
	
	AllocMemBuffer(nLen);
	WideCharToMultiByte(CP_ACP, 0, strBuff, -1, m_pBuffer, nLen, NULL,NULL);
#endif
}

void CTScriptParser::InitBuffer(char* strBuff)
{
	memset(g_pstrSourceFile, 0, MAX_FILENAME_SIZE);
	memset(m_pstrOutputFile, 0, MAX_FILENAME_SIZE);
	
	long nLen = strlen(strBuff);
	
	AllocMemBuffer(nLen);
	strcpy(m_pBuffer,strBuff);
}

void CTScriptParser::InitBuffer(const CString &strBuff)
{
	memset(g_pstrSourceFile, 0, MAX_FILENAME_SIZE);
	memset(m_pstrOutputFile, 0, MAX_FILENAME_SIZE);

	long nLen = 0;

#ifdef _UNICODE
	nLen = strBuff.GetLength() * 2;
#else
	nLen = strBuff.GetLength();
#endif
	
	AllocMemBuffer(nLen);

	CString_to_char(strBuff, m_pBuffer);
}

/******************************************************************************************
*
*   CompileSourceFile ()
*
*   Compiles the high-level source file to its XVM assembly equivelent.
*/

void CTScriptParser::CompileSourceFile ()
{
	// Add two temporary variables for evaluating expressions
	m_iTempVar0SymbolIndex = AddSymbol ( TEMP_VAR_0, 1, SCOPE_GLOBAL, SYMBOL_TYPE_VAR );
	m_iTempVar1SymbolIndex = AddSymbol ( TEMP_VAR_1, 1, SCOPE_GLOBAL, SYMBOL_TYPE_VAR );
	m_iTempVar2SymbolIndex = AddSymbol ( TEMP_VAR_2, 1, SCOPE_GLOBAL, SYMBOL_TYPE_VAR );
	
	InitSourceCodeLines();

	PreprocessSourceFile();

	// Parse the source file to create an I-code representation
	ParseSourceCode ();
}

/******************************************************************************************
*
*   PreprocessSourceFile ()
*
*   Preprocesses the source file to expand preprocessor directives and strip comments.
*/

void CTScriptParser::PreprocessSourceFile ()
{
	// Are we inside a block comment?
	int iInBlockComment = FALSE;
	
	// Are we inside a string?
	int iInString = FALSE;
	
	// Node to traverse list
	POS pos = m_oSourceCodeLines.GetHeadPosition();
	int nLen = 0;
	
	while ( pos != NULL )
	{
		// Create local copy of the current line
		char * pstrCurrLine = m_oSourceCodeLines.GetNext(pos);
		nLen = strlen(pstrCurrLine);
		
		// ---- Scan for comments
		for ( int iCurrCharIndex = 0; iCurrCharIndex < nLen; ++ iCurrCharIndex )
		{
			// If the current character is a quote, toggle the in string flag
			if ( pstrCurrLine [ iCurrCharIndex ] == '"' )
			{
				if ( iInString )
					iInString = FALSE;
				else
					iInString = TRUE;
			}
			
			// Check for a single-line comment, and terminate the rest of the line if one is
			// found
			if ( pstrCurrLine [ iCurrCharIndex ] == '/' &&
				pstrCurrLine [ iCurrCharIndex + 1 ] == '/' &&
				! iInString && ! iInBlockComment )
			{
				//pstrCurrLine [ iCurrCharIndex ] = '\n';
				//pstrCurrLine [ iCurrCharIndex + 1 ] = '\0';
				memset(pstrCurrLine+iCurrCharIndex, 0, nLen - iCurrCharIndex);
				break;
			}
			
			// Check for a block comment
			
			if ( pstrCurrLine [ iCurrCharIndex ] == '/' &&
				pstrCurrLine [ iCurrCharIndex + 1 ] == '*' &&
				! iInString && ! iInBlockComment )
			{
				iInBlockComment = TRUE;
			}
			
			// Check for the end of a block comment
			if ( pstrCurrLine [ iCurrCharIndex ] == '*' &&
				pstrCurrLine [ iCurrCharIndex + 1 ] == '/' &&
				iInBlockComment )
			{
				//pstrCurrLine [ iCurrCharIndex ] = ' ';
				//pstrCurrLine [ iCurrCharIndex + 1 ] = ' ';
				pstrCurrLine [ iCurrCharIndex ] = 0;
				pstrCurrLine [ iCurrCharIndex + 1 ] = 0;
				iInBlockComment = FALSE;
			}
			
			// If we're inside a block comment, replace the current character with
			// whitespace
			
			if ( iInBlockComment )
			{
			//	if ( pstrCurrLine [ iCurrCharIndex ] != '\n' )
			//		pstrCurrLine [ iCurrCharIndex ] = ' ';
				pstrCurrLine [ iCurrCharIndex ] = 0;
			}
		}
	}
	
	/*
	Implementation of the #include and #define preprocessor directives could go here
	*/
}

BOOL CTScriptParser::WriteToFile(const CString &strFile)
{
	CFile file;
    BOOL bOpen = file.Open(strFile, CFile::modeCreate|CFile::modeWrite);
	
	if (bOpen)
	{
		file.Write(m_pBuffer,m_nLength*sizeof(char));
		file.Close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void CTScriptParser::AllocMemBuffer(long nBufferLen)
{
	CXvmBuffer::InitBuffer(nBufferLen);
}


void CTScriptParser::InitSourceCodeLines()
{
	char *p = m_pBuffer;
	char *pEnd = m_pBuffer + m_nLength;
	
	m_iSourceCodeLines = 0;
	m_oSourceCodeLines.RemoveAll();
	char *pCurrLine = p;
	
	while (p <= pEnd)
	{
		if (*p == '\n')
		{
			m_iSourceCodeLines++;
			*p = 0;
			m_oSourceCodeLines.AddNode(pCurrLine);	
			p++;
			pCurrLine = p;
		}
		else if (*p == '\r')
		{
			*p = 0;
		}
		else
		{
			p++;
		}
	}
	
	m_iSourceCodeLines++;
	m_oSourceCodeLines.AddNode(pCurrLine);
}

//////////////////////////////////////////////////////////////////////////
//////////////// Lexer ///////////////////////////////////////////////////
/******************************************************************************************
*
*   ResetLexer ()
*
*   Resets the lexer.
*/

void CTScriptParser::ResetLexer ()
{
	// Set the current line of code to the new line
	m_oCurrLexerState.m_iCurrLineIndex = 0;
	m_oCurrLexerState.m_pCurrLine = m_pBuffer;
	
	// Reset the start and end of the current lexeme to the beginning of the source
	m_oCurrLexerState.m_iCurrLexemeStart = 0;
	m_oCurrLexerState.m_iCurrLexemeEnd = 0;
	
	// Reset the current operator
	m_oCurrLexerState.m_iCurrOp = 0;
	m_oCurrLexerState.m_posCurrLine = m_oSourceCodeLines.GetHeadPosition();
	m_oCurrLexerState.m_pCurrLine = m_oSourceCodeLines.GetAt(m_oCurrLexerState.m_posCurrLine);

	if (m_oCurrLexerState.m_pCurrLine != NULL)
	{
		m_oCurrLexerState.m_nCurrLineLen = strlen(m_oCurrLexerState.m_pCurrLine);
	}

	m_oCurrLexerState.m_pstrCurrLexeme[0] = 0;
	m_oCurrLexerState.m_CurrToken = -1;
}

/******************************************************************************************
*
*   CopyLexerState ()
*
*   Copies one lexer state structure into another.
*/

void CTScriptParser::CopyLexerState ( LexerState &pDestState, LexerState &pSourceState )
{
	// Copy each field individually to ensure a safe copy
	pDestState.m_iCurrLineIndex = pSourceState.m_iCurrLineIndex;
	pDestState.m_pCurrLine      = pSourceState.m_pCurrLine;
	pDestState.m_nCurrLineLen      = pSourceState.m_nCurrLineLen;
	pDestState.m_CurrToken      = pSourceState.m_CurrToken;
	strcpy ( pDestState.m_pstrCurrLexeme, pSourceState.m_pstrCurrLexeme );
	pDestState.m_iCurrLexemeStart = pSourceState.m_iCurrLexemeStart;
	pDestState.m_iCurrLexemeEnd   = pSourceState.m_iCurrLexemeEnd;
	pDestState.m_iCurrOp          = pSourceState.m_iCurrOp;
	pDestState.m_posCurrLine      = pSourceState.m_posCurrLine;
}

/******************************************************************************************
*
*   GetOpStateIndex ()
*
*   Returns the index of the operator state associated with the specified character and
*   character index.
*/

int CTScriptParser::GetOpStateIndex ( char cChar, int iCharIndex, int iSubStateIndex, int iSubStateCount )
{
	int iStartStateIndex;
	int iEndStateIndex;
	
	// Is the character index is zero?
	if ( iCharIndex == 0 )
	{
		// Yes, so there's no substates to worry about
		iStartStateIndex = 0;
		iEndStateIndex = MAX_OP_STATE_COUNT;
	}
	else
	{
		//  No, so save the substate information
		iStartStateIndex = iSubStateIndex;
		iEndStateIndex = iStartStateIndex + iSubStateCount;
	}
	
	// Loop through each possible substate and look for a match
	
	for ( int iCurrOpStateIndex = iStartStateIndex; iCurrOpStateIndex < iEndStateIndex; ++ iCurrOpStateIndex )
	{
		// Get the current state at the specified character index
		char cOpChar;

		switch ( iCharIndex )
		{
		case 0:
			cOpChar = g_OpChars0 [ iCurrOpStateIndex ].m_cChar;
			break;
			
		case 1:
			cOpChar = g_OpChars1 [ iCurrOpStateIndex ].m_cChar;
			break;
			
		case 2:
			cOpChar = g_OpChars2 [ iCurrOpStateIndex ].m_cChar;
			break;
		}
		
		// If the character is a match, return the index
		if ( cChar == cOpChar )
		{
			return iCurrOpStateIndex;
		}
	}
	
	// Return -1 if no match is found
	return -1;
}

/******************************************************************************************
*
*   IsCharOpChar ()
*
*   Determines if the specified character is an operator character.
*/

int CTScriptParser::IsCharOpChar ( char cChar, int iCharIndex, int iCurrLexState )
{
	if (iCurrLexState == LEX_STATE_STRING)
	{
		return FALSE;
	}

	// Loop through each state in the specified character index and look for a match	
	for ( int iCurrOpStateIndex = 0; iCurrOpStateIndex < MAX_OP_STATE_COUNT; ++ iCurrOpStateIndex )
	{
		// Get the current state at the specified character index
		char cOpChar;

		switch ( iCharIndex )
		{
		case 0:
			cOpChar = g_OpChars0 [ iCurrOpStateIndex ].m_cChar;
			break;
			
		case 1:
			cOpChar = g_OpChars1 [ iCurrOpStateIndex ].m_cChar;
			break;
			
		case 2:
			cOpChar = g_OpChars2 [ iCurrOpStateIndex ].m_cChar;
			break;
		}
		
		// If the character is a match, return TRUE
		if ( cChar == cOpChar )
		{
			return TRUE;
		}
	}
	
	// Return FALSE if no match is found
	return FALSE;
}

/******************************************************************************************
*
*   GetOpState ()
*
*   Returns the operator state associated with the specified index and state.
*/

CTScriptParser::OpState CTScriptParser::GetOpState ( int iCharIndex, int iStateIndex )
{
	OpState State;
	
	// Save the specified state at the specified character index	
	switch ( iCharIndex )
	{
	case 0:
		State = g_OpChars0 [ iStateIndex ];
		break;
		
	case 1:
		State = g_OpChars1 [ iStateIndex ];
		break;
		
	case 2:
		State = g_OpChars2 [ iStateIndex ];
		break;
	}
	
	return State;
}

/******************************************************************************************
*
*   IsCharDelim ()
*
*   Determines whether a character is a delimiter.
*/

int CTScriptParser::IsCharDelim ( char cChar )
{
	// Loop through each delimiter in the array and compare it to the specified character
	for ( int iCurrDelimIndex = 0; iCurrDelimIndex < MAX_DELIM_COUNT; ++ iCurrDelimIndex )
	{
		// Return TRUE if a match was found
		if ( cChar == g_cDelims [ iCurrDelimIndex ] )
		{
			return TRUE;
		}
	}
	
	// The character is not a delimiter, so return FALSE
	return FALSE;
}

/******************************************************************************************
*
*	IsCharWhitespace ()
*
*	Returns a nonzero if the given character is whitespace, or zero otherwise.
*/

int CTScriptParser::IsCharWhitespace ( char cChar )
{
	// Return true if the character is a space or tab.
	if ( cChar == ' ' || cChar == '\t' || cChar == '\n' )
		return TRUE;
	else
		return FALSE;
}

/******************************************************************************************
*
*	IsCharNumeric ()
*
*	Returns a nonzero if the given character is numeric, or zero otherwise.
*/

int CTScriptParser::IsCharNumeric ( char cChar )
{
	// Return true if the character is between 0 and 9 inclusive.
	
	if ( cChar >= '0' && cChar <= '9' )
		return TRUE;
	else
		return FALSE;
}

/******************************************************************************************
*
*	IsCharIdent ()
*
*	Returns a nonzero if the given character is part of a valid identifier, meaning it's an
*	alphanumeric or underscore. Zero is returned otherwise.
*/

int CTScriptParser::IsCharIdent ( char cChar )
{
	// Return true if the character is between 0 or 9 inclusive or is an uppercase or
	// lowercase letter or underscore
	
	if ( ( cChar >= '0' && cChar <= '9' ) ||
		( cChar >= 'A' && cChar <= 'Z' ) ||
		( cChar >= 'a' && cChar <= 'z' ) ||
		cChar == '_' )
		return TRUE;
	else
		return FALSE;
}

/******************************************************************************************
*
*   GetNextChar ()
*
*   Returns the next character in the source buffer.
*/

char CTScriptParser::GetNextChar (BOOL &bChangLine)
{
	// Make a local copy of the string pointer, unless we're at the end of the source code
	char *pstrCurrLine = NULL;
	char chReturn = 0;
	
	if ( m_oCurrLexerState.m_pCurrLine )
	{
		pstrCurrLine = ( char * ) m_oCurrLexerState.m_pCurrLine;

		// If the current lexeme end index is beyond the length of the string, we're past the
		// end of the line	
		//2017-2-24 lijq 避免每次都计算字符串的长度，提高效率
		if ( m_oCurrLexerState.m_iCurrLexemeEnd >= m_oCurrLexerState.m_nCurrLineLen)//( int ) strlen ( pstrCurrLine ) )
		{
			// Move to the next node in the source code list
			if ( !SkipToNextLine())
			{
				chReturn = '\0' ;
			}
			else
			{
				bChangLine = TRUE;
				pstrCurrLine = m_oCurrLexerState.m_pCurrLine;
				m_oCurrLexerState.m_iCurrLexemeStart = 0;
				m_oCurrLexerState.m_iCurrLexemeEnd = 0;
				chReturn = pstrCurrLine [ m_oCurrLexerState.m_iCurrLexemeEnd  ];
				m_oCurrLexerState.m_iCurrLexemeEnd ++;
			}
		}
		else
		{
			chReturn = pstrCurrLine [ m_oCurrLexerState.m_iCurrLexemeEnd  ];
			m_oCurrLexerState.m_iCurrLexemeEnd ++;
		}
	}
	else
	{
		chReturn = '\0';
	}
	
	return chReturn;
}

/******************************************************************************************
*
*   GetNextToken ()
*
*   Returns the next token in the source buffer.
*/

Token CTScriptParser::GetNextToken ()
{
	// Save the current lexer state for future rewinding
	CopyLexerState ( m_oPrevLexerState, m_oCurrLexerState );
	
	// Start the new lexeme at the end of the last one
	m_oCurrLexerState.m_iCurrLexemeStart = m_oCurrLexerState.m_iCurrLexemeEnd;
	
	// Set the initial state to the start state
	int iCurrLexState = LEX_STATE_START;
	int iPrevLexState = LEX_STATE_START;
	
	// Set the current operator state
	int iCurrOpCharIndex = 0;
	int iCurrOpStateIndex = 0;
	OpState oCurrOpState;
	
	// Flag to determine when the lexeme is done
	int iLexemeDone = FALSE;
	
	// ---- Loop until a token is completed
	
	// Current character
	char cCurrChar;
	
	// Current position in the lexeme string buffer
	int iNextLexemeCharIndex = 0;
	
	// Should the current character be included in the lexeme?
	int iAddCurrChar;

	//Is Next Line
	BOOL bChangeLine = FALSE;
	
	// Begin the loop
	while ( TRUE )
	{
		bChangeLine = FALSE;
		// Read the next character, and exit if the end of the source has been reached
		cCurrChar = GetNextChar (bChangeLine);
		
		if ( cCurrChar == '\0' )
			break;
		
		// Assume the character will be added to the lexeme
		iAddCurrChar = TRUE;
		
		// Depending on the current state of the lexer, handle the incoming character
		switch ( iCurrLexState )
		{
			// If an unknown state occurs, the token is invalid, so exit
		case LEX_STATE_UNKNOWN:
			iLexemeDone = TRUE;
			break;
			
			// The start state
		case LEX_STATE_START:
			if ( IsCharWhitespace ( cCurrChar ) )
			{// Just loop past whitespace, and don't add it to the lexeme
				++ m_oCurrLexerState.m_iCurrLexemeStart;
				iAddCurrChar = FALSE;
			}
			else if ( IsCharNumeric ( cCurrChar ) )
			{// An integer is starting
				iCurrLexState = LEX_STATE_INT;
			}
			else if ( cCurrChar == '.' )
			{// A float is starting
				iCurrLexState = LEX_STATE_FLOAT;
			}
			else if ( IsCharIdent ( cCurrChar ) )
			{// An identifier is starting
				iCurrLexState = LEX_STATE_IDENT;
			}
			else if ( IsCharDelim ( cCurrChar ) )
			{// A delimiter has been read
				iCurrLexState = LEX_STATE_DELIM;
			}
			else if ( IsCharOpChar ( cCurrChar, 0, iCurrLexState ) )
			{// An operator is starting
				// Get the index of the initial operand state
				iCurrOpStateIndex = GetOpStateIndex ( cCurrChar, 0, 0, 0 );
				
				if ( iCurrOpStateIndex == -1 )
				{
					return TOKEN_TYPE_INVALID;
				}
				
				// Get the full state structure
				oCurrOpState = GetOpState ( 0, iCurrOpStateIndex );
				
				// Move to the next character in the operator (1)
				iCurrOpCharIndex = 1;
				
				// Set the current operator
				m_oCurrLexerState.m_iCurrOp = oCurrOpState.m_iIndex;
				
				iCurrLexState = LEX_STATE_OP;
			}
			else if ( cCurrChar == '"' )
			{// A string is starting, but don't add the opening quote to the lexeme
				iAddCurrChar = FALSE;
				iCurrLexState = LEX_STATE_STRING;
			}
			else
			{// It's invalid
				iCurrLexState = LEX_STATE_UNKNOWN;
				iLexemeDone = TRUE;
				iAddCurrChar = FALSE;
			}
			
			break;
			
			// Integer
		case LEX_STATE_INT:
			if ( IsCharNumeric ( cCurrChar ) )
			{// If a numeric is read, keep the state as-is
				iCurrLexState = LEX_STATE_INT;
			}
			else if ( cCurrChar == '.' )
			{// If a radix point is read, the numeric is really a float
				iCurrLexState = LEX_STATE_FLOAT;
			}
			else if ( IsCharWhitespace ( cCurrChar ) || IsCharDelim ( cCurrChar ) )
			{// If whitespace or a delimiter is read, the lexeme is done
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
			}
			else if (IsCharOpChar ( cCurrChar, 0 , iCurrLexState))
			{//########################
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
			}
			else
			{// Anything else is invalid
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
				iCurrLexState = LEX_STATE_UNKNOWN;
			}
			
			break;
			
			// Floating-point
		case LEX_STATE_FLOAT:
			if ( IsCharNumeric ( cCurrChar ) )
			{// If a numeric is read, keep the state as-is
				iCurrLexState = LEX_STATE_FLOAT;
			}
			else if ( IsCharWhitespace ( cCurrChar ) || IsCharDelim ( cCurrChar ) )
			{// If whitespace or a delimiter is read, the lexeme is done
				iLexemeDone = TRUE;
				iAddCurrChar = FALSE;
			}
			else if (IsCharOpChar ( cCurrChar, 0, iCurrLexState ))
			{//########################
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
			}
			else
			{// Anything else is invalid
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
				iCurrLexState = LEX_STATE_UNKNOWN;
			}
			
			break;
			
			// Identifier
		case LEX_STATE_IDENT:
			if ( IsCharIdent ( cCurrChar ) || cCurrChar == '.')
			{
				// If an identifier character is read, keep the state as-is
				// "."考虑复合型变量
				iCurrLexState = LEX_STATE_IDENT;
			}
			else if ( IsCharWhitespace ( cCurrChar ) || IsCharDelim ( cCurrChar ) )
			{// If whitespace or a delimiter is read, the lexeme is done
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
			}
			else if (IsCharOpChar ( cCurrChar, 0, iCurrLexState ))
			{//########################
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
			}
			else
			{// Anything else is invalid
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
				iCurrLexState = LEX_STATE_UNKNOWN;
			}
			
			break;
			
			// Operator
		case LEX_STATE_OP:
			if ( oCurrOpState.m_iSubStateCount == 0 )
			{// If the current character within the operator has no substates, we're done
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
				break;
			}

			if ( IsCharOpChar ( cCurrChar, iCurrOpCharIndex, iCurrLexState ) )                   
			{// Otherwise, find out if the new character is a possible substate
				// Get the index of the next substate
				iCurrOpStateIndex = GetOpStateIndex ( cCurrChar, iCurrOpCharIndex, oCurrOpState.m_iSubStateIndex, oCurrOpState.m_iSubStateCount );
				
				if ( iCurrOpStateIndex == -1 )
				{
					iAddCurrChar = FALSE;
					iLexemeDone = TRUE;
					iCurrLexState = LEX_STATE_UNKNOWN;
				}
				else
				{
					// Get the next operator structure
					oCurrOpState = GetOpState ( iCurrOpCharIndex, iCurrOpStateIndex );
					
					// Move to the next character in the operator
					++ iCurrOpCharIndex;
					
					// Set the current operator
					m_oCurrLexerState.m_iCurrOp = oCurrOpState.m_iIndex;
				}
			}
			else
			{// If not, the lexeme is done
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
			}
			
			break;
			
			// Delimiter
		case LEX_STATE_DELIM:
			// Don't add whatever comes after the delimiter to the lexeme, because
			// it's done
			iAddCurrChar = FALSE;
			iLexemeDone = TRUE;
			
			break;
			
			// String
		case LEX_STATE_STRING:
			if ( cCurrChar == '"' )
			{// If the current character is a closing quote, finish the lexeme
				iAddCurrChar = FALSE;
				iCurrLexState = LEX_STATE_STRING_CLOSE_QUOTE;
			}
			else if ( cCurrChar == '\n' )
			{// If it's a newline, the string token is invalid
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
				iCurrLexState = LEX_STATE_UNKNOWN;
			}
			else if ( cCurrChar == '\\' )
			{// If it's an escape sequence, switch to the escape state and don't add the backslash to the lexeme
				iAddCurrChar = FALSE;
				iCurrLexState = LEX_STATE_STRING_ESCAPE;
			}
			else if (IsCharOpChar ( cCurrChar, 0, iCurrLexState ))
			{//########################
				iAddCurrChar = FALSE;
				iLexemeDone = TRUE;
			}
			else
			{
			}
			// Anything else gets added to the string
			break;
			
			// Escape sequence
		case LEX_STATE_STRING_ESCAPE:
			// Immediately switch back to the string state, now that the character's
			// been added
			iCurrLexState = LEX_STATE_STRING;
			
			break;
			
			// String closing quote
		case LEX_STATE_STRING_CLOSE_QUOTE:
			// Finish the string lexeme
			iAddCurrChar = FALSE;
			iLexemeDone = TRUE;
			
			break;
			
		}

		if (bChangeLine)
		{
			if (iNextLexemeCharIndex > 0)
			{
				break;
			}
		}
		
		// Add the next character to the lexeme and increment the index
		if ( iAddCurrChar )
		{
			m_oCurrLexerState.m_pstrCurrLexeme [ iNextLexemeCharIndex ] = cCurrChar;
			++ iNextLexemeCharIndex;
		}
		
		if (iCurrLexState != LEX_STATE_UNKNOWN)
		{
			iPrevLexState = iCurrLexState;
		}
		
		// If the lexeme is complete, exit the loop
		if ( iLexemeDone )
		{
			break;
		}
   }
   
   // Complete the lexeme string
   m_oCurrLexerState.m_pstrCurrLexeme [ iNextLexemeCharIndex ] = '\0';
   
   // Retract the lexeme end index by one
   -- m_oCurrLexerState.m_iCurrLexemeEnd;
   
   // Determine the token type
   Token TokenType;
   switch ( iCurrLexState )
   {
	   // Unknown
   case LEX_STATE_UNKNOWN:
	   TokenType = TOKEN_TYPE_INVALID;
	   break;
	   
	   // Integer
   case LEX_STATE_INT:
	   TokenType = TOKEN_TYPE_INT;
	   break;
	   
	   // Float
   case LEX_STATE_FLOAT:
	   TokenType = TOKEN_TYPE_FLOAT;
	   break;
	   
	   // Identifier/Reserved Word
   case LEX_STATE_IDENT:
	   
	   // Set the token type to identifier in case none of the reserved words match
	   TokenType = TokenReservedKey();	   
	   break;
	   
	   // Delimiter
   case LEX_STATE_DELIM:
	   // Determine which delimiter was found
	   switch ( m_oCurrLexerState.m_pstrCurrLexeme [ 0 ] )
	   {
	   case ',':
		   TokenType = TOKEN_TYPE_DELIM_COMMA;
		   break;
		   
	   case '(':
		   TokenType = TOKEN_TYPE_DELIM_OPEN_PAREN;
		   break;
		   
	   case ')':
		   TokenType = TOKEN_TYPE_DELIM_CLOSE_PAREN;
		   break;
		   
	   case '[':
		   TokenType = TOKEN_TYPE_DELIM_OPEN_BRACE;
		   break;
		   
	   case ']':
		   TokenType = TOKEN_TYPE_DELIM_CLOSE_BRACE;
		   break;
		   
	   case '{':
		   TokenType = TOKEN_TYPE_DELIM_OPEN_CURLY_BRACE;
		   break;
		   
	   case '}':
		   TokenType = TOKEN_TYPE_DELIM_CLOSE_CURLY_BRACE;
		   break;
		   
	   case ';':
		   TokenType = TOKEN_TYPE_DELIM_SEMICOLON;
		   break;
	   default:
		   TokenType = TOKEN_TYPE_INVALID;
		   break;
	   }
	   
	   break;
	   
	   // Operators
	   case LEX_STATE_OP:
		   TokenType = TOKEN_TYPE_OP;
		   break;
		   
		   // Strings
		   
	   case LEX_STATE_STRING_CLOSE_QUOTE:
		   TokenType = TOKEN_TYPE_STRING;
		   break;
		   
		   // All that's left is whitespace, which means the end of the stream
	   default:
		   TokenType = TOKEN_TYPE_END_OF_STREAM;
    }
	
    // Return the token type and set the global copy
    m_oCurrLexerState.m_CurrToken = TokenType;
    return TokenType;
}

Token CTScriptParser::TokenReservedKey()
{
	Token TokenType = TOKEN_TYPE_IDENT;
	
	// ---- Determine if the "identifier" is actually a reserved word
	if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_var ) == 0 )
	{// var/var []
		TokenType = TOKEN_TYPE_RSRVD_VAR;
	}
//	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_long ) == 0 )
//	{// var/var []
//		TokenType = TOKEN_TYPE_RSRVD_LONG;
//	}
//	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_string ) == 0 )
//	{// var/var []
//		TokenType = TOKEN_TYPE_RSRVD_STRING;
//	}
//	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_float ) == 0 )
//	{// var/var []
//		TokenType = TOKEN_TYPE_RSRVD_FLOAT;
//	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_export ) == 0 )
	{// true
		TokenType = TOKEN_TYPE_RSRVD_EXPORT;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_true ) == 0 )
	{// true
		TokenType = TOKEN_TYPE_RSRVD_TRUE;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_false ) == 0 )
	{// false
		TokenType = TOKEN_TYPE_RSRVD_FALSE;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_if ) == 0 )
	{// else if
		TokenType = TOKEN_TYPE_RSRVD_IF;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_else ) == 0 )
	{// else
		TokenType = TOKEN_TYPE_RSRVD_ELSE;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_break ) == 0 )
	{// break
		TokenType = TOKEN_TYPE_RSRVD_BREAK;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_continue ) == 0 )
	{// continue
		TokenType = TOKEN_TYPE_RSRVD_CONTINUE;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_for ) == 0 )
	{// for
		TokenType = TOKEN_TYPE_RSRVD_FOR;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_while ) == 0 )
	{// while
		TokenType = TOKEN_TYPE_RSRVD_WHILE;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_func ) == 0 )
	{// func
		TokenType = TOKEN_TYPE_RSRVD_FUNC;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_return ) == 0 )
	{// return
		TokenType = TOKEN_TYPE_RSRVD_RETURN;
	}
	else if ( stricmp ( m_oCurrLexerState.m_pstrCurrLexeme, g_pstrScriptKey_host ) == 0 )
	{// host
		TokenType = TOKEN_TYPE_RSRVD_HOST;
	}
	else
	{
		CTInstruct *pFind = CTScriptInstructs::Find(m_oCurrLexerState.m_pstrCurrLexeme);
		if (pFind != NULL)
		{
			TokenType = pFind->m_nOpcode;
		}
	}
	
	return TokenType;
}

/******************************************************************************************
*
*   RewindTokenStream ()
*
*   Moves the lexer back one token.
*/

void CTScriptParser::RewindTokenStream ()
{
	CopyLexerState ( m_oCurrLexerState, m_oPrevLexerState );
}

/******************************************************************************************
*
*   GetCurrToken ()
*
*   Returns the current token.
*/

Token CTScriptParser::GetCurrToken ()
{
	return m_oCurrLexerState.m_CurrToken;
}

/******************************************************************************************
*
*   GetCurrLexeme ()
*
*   Returns a pointer to the current lexeme.
*/

char* CTScriptParser::GetCurrLexeme ()
{
	return m_oCurrLexerState.m_pstrCurrLexeme;
}

/******************************************************************************************
*
*   CopyCurrLexeme ()
*
*   Makes a physical copy of the current lexeme into the specified string buffer.
*/

void CTScriptParser::CopyCurrLexeme ( char * pstrBuffer )
{
	strcpy ( pstrBuffer, m_oCurrLexerState.m_pstrCurrLexeme );
}

/******************************************************************************************
*
*   GetCurrOp ()
*
*   Returns the current operator.
*/

int CTScriptParser::GetCurrOp ()
{
	return m_oCurrLexerState.m_iCurrOp;
}

/******************************************************************************************
*
*   GetLookAheadChar ()
*
*   Returns the first character of the next token.
*/

char CTScriptParser::GetLookAheadChar ()
{
	// Save the current lexer state
	LexerState PrevLexerState;
	CopyLexerState ( PrevLexerState, m_oCurrLexerState );
	
	// Skip any whitespace that may exist and return the first non-whitespace character
	char cCurrChar;
	BOOL bChangeLine = FALSE;
	
	while ( TRUE )
	{
		cCurrChar = GetNextChar (bChangeLine);

		if ( ! IsCharWhitespace ( cCurrChar ) )
		{
			break;
		}
	}
	
	// Restore the lexer state
	CopyLexerState ( m_oCurrLexerState, PrevLexerState );
	
	// Return the look-ahead character
	return cCurrChar;
}


/******************************************************************************************
*
*   GetCurrSourceLine ()
*
*   Returns a pointer to the current source line string.
*/
int CTScriptParser::SkipToNextLine ()
{
	BOOL bTrue = TRUE;
	
	while (TRUE)
	{
		// Increment the current line
		m_oCurrLexerState.m_iCurrLineIndex++;
		
		if (m_oCurrLexerState.m_iCurrLineIndex >= (int)m_oSourceCodeLines.GetCount())
		{
			m_oCurrLexerState.m_pCurrLine = NULL;
			m_oCurrLexerState.m_posCurrLine = NULL;
			bTrue = FALSE; 
			break;
		}
		else
		{
			//move to next line position
			m_oSourceCodeLines.GetNext(m_oCurrLexerState.m_posCurrLine);
			
			if (m_oCurrLexerState.m_posCurrLine == NULL)
			{
				bTrue = FALSE; 
				break;
			}

			//get the current line 
			m_oCurrLexerState.m_pCurrLine = m_oSourceCodeLines.GetAt(m_oCurrLexerState.m_posCurrLine);
			
			if (m_oCurrLexerState.m_pCurrLine == NULL)
			{
				bTrue = FALSE; 
				break;
			}

			//if the line is not empty, break the loop
			if (*(m_oCurrLexerState.m_pCurrLine) != '\0')
			{
				m_oCurrLexerState.m_nCurrLineLen = strlen(m_oCurrLexerState.m_pCurrLine);
				break;
			}
			else//continue
			{
			}
		}
		
	}
	
	return bTrue;
}

/******************************************************************************************
*
*   GetCurrSourceLine ()
*
*   Returns a pointer to the current source line string.
*/

char* CTScriptParser::GetCurrSourceLine ()
{
	if ( m_oCurrLexerState.m_pCurrLine )
		return ( char * ) m_oCurrLexerState.m_pCurrLine;
	else
		return NULL;
}


/******************************************************************************************
*
*   GetCurrSourceLineIndex ()
*
*   Returns the current source line number.
*/

int CTScriptParser::GetCurrSourceLineIndex ()
{
	return m_oCurrLexerState.m_iCurrLineIndex;
}

/******************************************************************************************
*
*   GetLexemeStartIndex ()
*
*   Returns the pointer to the start of the current lexeme
*/

int CTScriptParser::GetLexemeStartIndex ()
{
	return m_oCurrLexerState.m_iCurrLexemeStart;
}


//////////////////////////////////////////////////////////////////////////
//////////////////Parser module///////////////////////////////////////////
/******************************************************************************************
*
*   ReadToken ()
*
*   Attempts to read a specific token and prints an error if its not found.
*/

BOOL CTScriptParser::ReadToken ( Token ReqToken )
{
	BOOL bHasError = FALSE;

	// Determine if the next token is the required one
	if ( GetNextToken() != ReqToken )
	{
		bHasError = TRUE;

		// If not, exit on a specific error
		switch ( ReqToken )
		{
			// Integer
		case TOKEN_TYPE_INT:
			AddCodeSyntaxError2( "Integer" );
			break;
			
			// Float
		case TOKEN_TYPE_FLOAT:
			AddCodeSyntaxError2( "Float" );
			break;
			
			// Identifier
		case TOKEN_TYPE_IDENT:
			AddCodeSyntaxError2( "Identifier" );
			break;
			
			// var
		case TOKEN_TYPE_RSRVD_VAR:
			AddCodeSyntaxError2( "var" );
			break;
			
			// true
		case TOKEN_TYPE_RSRVD_TRUE:
			AddCodeSyntaxError2( "true" );
			break;
			
			// false
		case TOKEN_TYPE_RSRVD_FALSE:
			AddCodeSyntaxError2( "false" );
			break;
			
			// if
		case TOKEN_TYPE_RSRVD_IF:
			AddCodeSyntaxError2( "if" );
			break;
			
			// else
		case TOKEN_TYPE_RSRVD_ELSE:
			AddCodeSyntaxError2( "else" );
			break;
			
			// break
		case TOKEN_TYPE_RSRVD_BREAK:
			AddCodeSyntaxError2( "break" );
			break;
			
			// continue
		case TOKEN_TYPE_RSRVD_CONTINUE:
			AddCodeSyntaxError2( "continue" );
			break;
			
			// for
		case TOKEN_TYPE_RSRVD_FOR:
			AddCodeSyntaxError2( "for" );
			break;
			
			// while
		case TOKEN_TYPE_RSRVD_WHILE:
			AddCodeSyntaxError2( "while" );
			break;
			
			// func
		case TOKEN_TYPE_RSRVD_FUNC:
			AddCodeSyntaxError2( "func" );
			break;
			
			// return
		case TOKEN_TYPE_RSRVD_RETURN:
			AddCodeSyntaxError2( "return" );
			break;
			
			// host
		case TOKEN_TYPE_RSRVD_HOST:
			AddCodeSyntaxError2( "host" );
			break;
			
			// Operator
		case TOKEN_TYPE_OP:
			AddCodeSyntaxError2( "Operator" );
			break;
			
			// Comma
		case TOKEN_TYPE_DELIM_COMMA:
			AddCodeSyntaxError2( "," );
			break;
			
			// Open parenthesis
		case TOKEN_TYPE_DELIM_OPEN_PAREN:
			AddCodeSyntaxError2( "(" );
			break;
			
			// Close parenthesis
		case TOKEN_TYPE_DELIM_CLOSE_PAREN:
			AddCodeSyntaxError2( ")" );
			break;
			
			// Open brace
		case TOKEN_TYPE_DELIM_OPEN_BRACE:
			AddCodeSyntaxError2( "[" );
			break;
			
			// Close brace
		case TOKEN_TYPE_DELIM_CLOSE_BRACE:
			AddCodeSyntaxError2( "]" );
			break;
			
			// Open curly brace
		case TOKEN_TYPE_DELIM_OPEN_CURLY_BRACE:
			AddCodeSyntaxError2( "{" );
			break;
			
			// Close curly brace
		case TOKEN_TYPE_DELIM_CLOSE_CURLY_BRACE:
			AddCodeSyntaxError2( "}" );
			break;
			
			// Semicolon
		case TOKEN_TYPE_DELIM_SEMICOLON:
			AddCodeSyntaxError2( ";" );
			break;
			
			// String
		case TOKEN_TYPE_STRING:
			AddCodeSyntaxError2( "String" );
			break;
		default:
			break;
		}
	}

	return bHasError;
}


/******************************************************************************************
*
*   ParseSourceCode ()
*
*   Parses the source code from start to finish, generating a complete I-code
*   representation.
*/

BOOL CTScriptParser::ParseSourceCode ()
{
	BOOL bHasError = FALSE;
	// Reset the lexer
	ResetLexer ();
	
	// Initialize the loop stack
	m_oLoopStack.Empty();
	
	// Set the current scope to global
	m_iCurrScope = SCOPE_GLOBAL;
	
	// Parse each line of code
	while ( TRUE )
	{
		// Parse the next statement and ignore an end of file marker
		ParseStatement ();
		
		// If we're at the end of the token stream, break the parsing loop
		
		if ( GetNextToken () == TOKEN_TYPE_END_OF_STREAM )
		{
			break;
		}
		else
		{
			RewindTokenStream ();
		}
	}
	
	// Free the loop stack
	m_oLoopStack.Empty();

	return bHasError;
}
	
/******************************************************************************************
*
*   ParseStatement ()
*
*   Parses a statement.
*/

BOOL CTScriptParser::ParseStatement ()
{
	BOOL bHasError = FALSE;

	// If the next token is a semicolon, the statement is empty so return
	if ( GetLookAheadChar () == ';' )
	{
		ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );
		return bHasError;
	}
	
	// Determine the initial token of the statement
	Token InitToken = GetNextToken ();
	
	// Branch to a parse function based on the token	
	switch ( InitToken )
	{
		// Unexpected end of file
	case TOKEN_TYPE_END_OF_STREAM:
		AddCodeSyntaxError ( ERROR_MSG_UNEXPECTED_END_OF_FILE );
		bHasError = TRUE;
		break;
		
		// Block
	case TOKEN_TYPE_DELIM_OPEN_CURLY_BRACE: // 
		ParseBlock ();
		break;
		
		// Variable/array declaration
	case TOKEN_TYPE_RSRVD_VAR:  // var
		ParseVar ();
		break;
		
		// Host API function import
	case TOKEN_TYPE_RSRVD_HOST:
		ParseHost ();
		break;
		
		// Function definition
	case TOKEN_TYPE_RSRVD_FUNC:
		ParseFunc ();
		break;
		
		// if block
	case TOKEN_TYPE_RSRVD_IF:
		ParseIf ();
		break;
		
		// while loop block
	case TOKEN_TYPE_RSRVD_WHILE:
		ParseWhile ();
		break;
		
		// for loop block
	case TOKEN_TYPE_RSRVD_FOR:
		ParseFor ();
		break;
		
		// break
	case TOKEN_TYPE_RSRVD_BREAK:
		ParseBreak ();
		break;
		
		// continue
	case TOKEN_TYPE_RSRVD_CONTINUE:
		ParseContinue ();
		break;
		
		// return
	case TOKEN_TYPE_RSRVD_RETURN:
		ParseReturn ();
		break;
		
		// Assignment or Function Call
	case TOKEN_TYPE_IDENT:
		{
			// What kind of identifier is it?
			if ( GetSymbolByIdent ( GetCurrLexeme (), m_iCurrScope ) )
			{
				// It's an identifier, so treat the statement as an assignment
				ParseAssign ();
			}
			else if ( GetFuncByName ( GetCurrLexeme () ) )
			{
				// It's a function
				// Annotate the line and parse the call
				AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
				ParseFuncCall ();
				
				// Verify the presence of the semicolon
				ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );
			}
			else
			{
				// It's invalid
				AddCodeSyntaxError ( ERROR_MSG_INVALID_IDENTIFIER , GetCurrLexeme() , TSYNTAX_TYPE_WARNING);
				//bHasError = TRUE;

				//2020-6-2  lijunqing  从LUA转换为XVM，部分局部变量没有定义，处理这种异常情况。
				Token tok = GetNextToken ();
				int nOp = GetCurrOp ();

				if ( tok != TOKEN_TYPE_OP &&
					( nOp != OP_TYPE_ASSIGN &&
					nOp != OP_TYPE_ASSIGN_ADD &&
					nOp != OP_TYPE_ASSIGN_SUB &&
					nOp != OP_TYPE_ASSIGN_MUL &&
					nOp != OP_TYPE_ASSIGN_DIV &&
					nOp != OP_TYPE_ASSIGN_MOD &&
					nOp != OP_TYPE_ASSIGN_EXP &&
					nOp != OP_TYPE_ASSIGN_CONCAT &&
					nOp != OP_TYPE_ASSIGN_AND &&
					nOp != OP_TYPE_ASSIGN_OR &&
					nOp != OP_TYPE_ASSIGN_XOR &&
					nOp != OP_TYPE_ASSIGN_SHIFT_LEFT &&
					nOp != OP_TYPE_ASSIGN_SHIFT_RIGHT ) )
				{
					bHasError = TRUE;
				}
				else
				{
					RewindTokenStream();
					int nSymbol  =  AddSymbol ( GetCurrLexeme (), 1, m_iCurrScope, SYMBOL_TYPE_VAR );
					ParseAssign ();
				}
			}

			break;
		}
		
		// Anything else is invalid
	default:
		AddCodeSyntaxError ( ERROR_MSG_UNEXPECTED_INPUT );
		bHasError = TRUE;
		break;
	}
	
	return bHasError;
}
	
/******************************************************************************************
*
*   ParseBlock ()
*
*   Parses a code block.
*
*       { <Statement-List> }
*/

BOOL CTScriptParser::ParseBlock ()
{
	BOOL bHasError = FALSE;
	
	// Make sure we're not in the global scope
	if ( m_iCurrScope == SCOPE_GLOBAL )
	{
		AddCodeSyntaxError ( ERROR_MSG_CODE_IN_GLOBAL );
	}
	
	// Read each statement until the end of the block
	while ( GetLookAheadChar () != '}' )
	{
		bHasError = ParseStatement ();

		if (bHasError)
		{
			SkipToNextStatement();
		}

		if (TOKEN_TYPE_END_OF_STREAM == m_oCurrLexerState.m_CurrToken)
		{
			break;
		}
	}
	
	// Read the closing curly brace
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_CURLY_BRACE );

	if (bHasError)
	{
		RewindTokenStream ();
	}

	return bHasError;
}

/******************************************************************************************
*
*   ParseVar ()
*
*   Parses the declaration of a variable or array and adds it to the symbol table.
*
*       var <Identifier>;
*       var <Identifier> [ <Integer> ];
*/

BOOL CTScriptParser::ParseVar ()
{
	BOOL bHasError = FALSE;
	
	// Read an identifier token
	bHasError = ReadToken ( TOKEN_TYPE_IDENT );

	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	
	// Copy the current lexeme into a local string buffer to save the variable's identifier
	char pstrIdent [ MAX_LEXEME_SIZE ];
	CopyCurrLexeme ( pstrIdent );
	
	// Set the size to 1 for a variable (an array will update this value)
	int iSize = 1;
	
	// Is the look-ahead character an open brace?
	if ( GetLookAheadChar () == '[' )
	{
		// Verify the open brace
		ReadToken ( TOKEN_TYPE_DELIM_OPEN_BRACE );
		
		// If so, read an integer token
		bHasError = ReadToken ( TOKEN_TYPE_INT );

		if (bHasError)
		{
			SkipToNextStatement();
			return bHasError;
		}
		
		// Convert the current lexeme to an integer to get the size
		iSize = atoi ( GetCurrLexeme () );
		
		// Read the closing brace
		bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_BRACE );
		
		if (bHasError)
		{
			SkipToNextStatement();
			return bHasError;
		}
	}
	
	int iType = SYMBOL_TYPE_VAR;
	
	//if var is export var
	if (GetNextToken() == TOKEN_TYPE_RSRVD_EXPORT)
	{
		if (m_iCurrScope != SCOPE_GLOBAL)
		{
			AddCodeSyntaxError ( ERROR_MSG_EXPORT_IN_FUNC );
		}

		if (iSize > 1)
		{
			AddCodeSyntaxError ( ERROR_MSG_CANNT_EXPORT_ARRAY );
		}

		iType = SYMBOL_TYPE_EXPORT_VAR;
	}
	else
	{
		RewindTokenStream();
	}
	
	// Add the identifier and size to the symbol table
	int nSymbol  =  AddSymbol ( pstrIdent, iSize, m_iCurrScope, iType );

	if (nSymbol == -1 )
	{
		AddCodeSyntaxError ( ERROR_MSG_IDENTIFIER_REDEFINE , GetCurrLexeme(), TSYNTAX_TYPE_WARNING);
	}

	 //LexerState oCurrLexerState;
	 //CopyLexerState(oCurrLexerState, m_oCurrLexerState);
	// Read the semicolon
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );

	if (bHasError)
	{
		if (nSymbol == -1)
		{
			SkipToNextStatement();
		}
		else
		{
			bHasError = FALSE;
			RewindTokenStream();
			//CopyLexerState(m_oCurrLexerState, oCurrLexerState);
		}
	}
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseHostAPIFuncImport ()
*
*   Parses the importing of a host API function.
*
*       host <Identifier> ();
*/

BOOL CTScriptParser::ParseHost ()
{
	BOOL bHasError = FALSE;
	
	// Read the host API function name
	bHasError = ReadToken ( TOKEN_TYPE_IDENT );
	
	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	
	// Add the function to the function table with the host API flag set
	if ( AddFunc ( GetCurrLexeme (), TRUE ) == -1 )
	{
		AddCodeSyntaxError ( ERROR_MSG_FUNC_REDEFINE , GetCurrLexeme());
	}
	
	// Make sure the function name is followed with ()
	ReadToken ( TOKEN_TYPE_DELIM_OPEN_PAREN );
	ReadToken ( TOKEN_TYPE_DELIM_CLOSE_PAREN );
	
	// Read the semicolon
	ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseFunc ()
*
*   Parses a function.
*
*       func <Identifier> ( <Parameter-List> ) <Statement>
*/

BOOL CTScriptParser::ParseFunc ()
{
	BOOL bHasError = FALSE;
	
	// Make sure we're not already in a function
	
	if ( m_iCurrScope != SCOPE_GLOBAL )
	{
		AddCodeSyntaxError ( ERROR_MSG_NESTED_FUNCTIONS );
	}
	
	// Read the function name
	bHasError = ReadToken ( TOKEN_TYPE_IDENT );
	
	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	
	// Add the non-host API function to the function table and get its index
	int iFuncIndex = -1;
	strcpy(m_pszCurrFuncName, GetCurrLexeme ());
	iFuncIndex = GetFuncIndexByName(m_pszCurrFuncName, true);

	if (iFuncIndex != -1)
	{
		iFuncIndex = GetFuncIndexByName(m_pszCurrFuncName, false);

		if (iFuncIndex != -1) 
		{
			AddCodeSyntaxError ( ERROR_MSG_FUNC_REDEFINE , m_pszCurrFuncName);
		}
		else
		{
			AddCodeSyntaxError ( ERROR_MSG_FUNC_REDEFINE_HOST , m_pszCurrFuncName);
			iFuncIndex = AddFunc ( m_pszCurrFuncName, FALSE );
		}
	}
	else
	{
		iFuncIndex = AddFunc (m_pszCurrFuncName , FALSE );
	}

	// Check for a function redefinition
	if ( iFuncIndex == -1 )
	{
		AddCodeSyntaxError ( ERROR_MSG_FUNC_REDEFINE , GetCurrLexeme());
	}
	
	// Set the scope to the function
	m_iCurrScope = iFuncIndex;
	
	// Read the opening parenthesis
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_OPEN_PAREN );

	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Use the look-ahead character to determine if the function takes parameters
	if ( GetLookAheadChar () != ')' )
	{
		// If the function being defined is _Main (), flag an error since _Main ()
		// cannot accept paraemters
		if ( m_ScriptHeader.m_iIsMainFuncPresent &&
			m_ScriptHeader.m_iMainFuncIndex == iFuncIndex )
		{
			AddCodeSyntaxError ( ERROR_MSG_MAIN_ACCEPT_PARA );
		}
		
		// Start the parameter count at zero
		int iParamCount = 0;
		
		// Crete an array to store the parameter list locally
		char ppstrParamList [ MAX_FUNC_DECLARE_PARAM_COUNT ][ MAX_IDENT_SIZE ];
		
		// Read the parameters
		while ( TRUE )
		{
			// Read the identifier
			bHasError = ReadToken ( TOKEN_TYPE_IDENT );
			if (bHasError)
			{
				SkipToNextStatement();
				break;
			}
			
			// Copy the current lexeme to the parameter list array
			CopyCurrLexeme ( ppstrParamList [ iParamCount ] );
			
			// Increment the parameter count
			++ iParamCount;
			
			// Check again for the closing parenthesis to see if the parameter list is done
			if ( GetLookAheadChar () == ')' )
			{
				break;
			}
			
			// Otherwise read a comma and move to the next parameter
			bHasError = ReadToken ( TOKEN_TYPE_DELIM_COMMA );
		
			if (bHasError)
			{
				SkipToNextStatement();
				break;
			}
		}
		
		// Set the final parameter count
		SetFuncParamCount ( m_iCurrScope, iParamCount );
		
		// Write the parameters to the function's symbol table in reverse order, so they'll
		// be emitted from right-to-left
		while ( iParamCount > 0 )
		{
			-- iParamCount;
			
			// Add the parameter to the symbol table
			if (GetSymbolByIdent(ppstrParamList [ iParamCount ], m_iCurrScope) != NULL)
			{
				AddCodeSyntaxError ( ERROR_MSG_IDENTIFIER_REDEFINE,  ppstrParamList [ iParamCount ], TSYNTAX_TYPE_WARNING);
			}
			AddSymbol ( ppstrParamList [ iParamCount ], 1, m_iCurrScope, SYMBOL_TYPE_PARAM );
		}
	}
	
	// Read the closing parenthesis
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_PAREN );

	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Read the opening curly brace
	ReadToken ( TOKEN_TYPE_DELIM_OPEN_CURLY_BRACE );
	
	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Parse the function's body
	bHasError = ParseBlock ();
	
	// Return to the global scope
	m_iCurrScope = SCOPE_GLOBAL;
	
	m_pszCurrFuncName[0] = 0;
	return bHasError;
}

/******************************************************************************************
*
*   ParseExpr ()
*
*   Parses an expression.
*/

BOOL CTScriptParser::ParseExpr (/*int iTrIndex*/)
{
	BOOL bHasError = FALSE;
	
	int iInstrIndex;
	
	// The current operator type
	int iOpType;
	
	// Parse the subexpression
	bHasError = ParseSubExpr ();

	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	
	// Parse any subsequent relational or logical operators
	while ( TRUE )
	{
		// Get the next token
		if ( GetNextToken () != TOKEN_TYPE_OP ||
			( ! IsOpRelational ( GetCurrOp () ) &&
			! IsOpLogical ( GetCurrOp () ) ) )
		{
			RewindTokenStream ();
			break;
		}
		
		// Save the operator
		iOpType = GetCurrOp ();
		
		// Parse the second term
		bHasError = ParseSubExpr (); 
		if (bHasError)
		{
			SkipToNextStatement();
			return bHasError;
		}
		
		// Pop the first operand into _T1
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
		
		// Pop the second operand into _T0
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		
		// ---- Perform the binary operation associated with the specified operator
		// Determine the operator type
		if ( IsOpRelational ( iOpType ) )
		{
			// It's a relational operator
			switch ( iOpType )
			{
				// Equal
			case OP_TYPE_EQUAL:
				{
					// Generate a JE instruction
					//iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JE );
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_CMPE );
					break;
				}
				
				// Not Equal
			case OP_TYPE_NOT_EQUAL:
				{
					// Generate a JNE instruction
					//iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JNE );
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_CMPNE );
					break;
				}
				
				// Greater
			case OP_TYPE_GREATER:
				{
					// Generate a JG instruction
					//iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JG );
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_CMPG );
					break;
				}
				
				// Less
			case OP_TYPE_LESS:
				{
					// Generate a JL instruction
					//iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JL );
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_CMPL );
					break;
				}
				
				// Greater or Equal
			case OP_TYPE_GREATER_EQUAL:
				{
					// Generate a JGE instruction
					//iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JGE );
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_CMPGE );
					break;
				}
				
				// Less Than or Equal
			case OP_TYPE_LESS_EQUAL:
				{
					// Generate a JLE instruction
					//iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JLE );
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_CMPLE );
					break;
				}
			}
		
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
			
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		}
		else
		{
			// It must be a logical operator
			switch ( iOpType )
			{
				// And
			case OP_TYPE_LOGICAL_AND:
				{
					// Get a pair of free jump target indices
					//and _T0, _T1
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_AND );
					AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
					AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );

					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
					AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );					
					
					break;
				}
				
				// Or
			case OP_TYPE_LOGICAL_OR:
				{
					// Get a pair of free jump target indices
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_OR );
					AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
					AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
					
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
					AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );					
					
					break;
				}
			}
		}
	}
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseSubExpr ()
*
*   Parses a sub expression.
*/

BOOL CTScriptParser::ParseSubExpr (/*int iTrIndex*/)
{
	BOOL bHasError = FALSE;
	
	int iInstrIndex;
	
	// The current operator type
	int iOpType;
	
	// Parse the first term
	bHasError = ParseTerm (); 

	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	
	// Parse any subsequent +, - or $ operators	
	while ( TRUE )
	{
		// Get the next token
		
		if ( GetNextToken () != TOKEN_TYPE_OP ||
			( GetCurrOp () != OP_TYPE_ADD &&
			GetCurrOp () != OP_TYPE_SUB &&
			GetCurrOp () != OP_TYPE_CONCAT ) )
		{
			RewindTokenStream ();
			break;
		}
		
		// Save the operator
		iOpType = GetCurrOp ();
		
		// Parse the second term
		bHasError = ParseTerm ();
		
		if (bHasError)
		{
			SkipToNextStatement();
			break;
		}
		
		// Pop the first operand into _T1
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
		
		// Pop the second operand into _T0
		
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );

		
		// Perform the binary operation associated with the specified operator
		int iOpInstr;
		switch ( iOpType )
		{
			// Binary addition
		case OP_TYPE_ADD:
			iOpInstr = INSTRUCT_ADD;
			break;
			
			// Binary subtraction
		case OP_TYPE_SUB:
			iOpInstr = INSTRUCT_SUB;
			break;
			
			// Binary string concatenation			
		case OP_TYPE_CONCAT:
			iOpInstr = INSTRUCT_CONCAT;
			break;
		}
		
		iInstrIndex = AddICodeInstr ( m_iCurrScope, iOpInstr );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
		
		// Push the result (stored in _T0)		
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );	
	}
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseTerm ()
*
*   Parses a term.
*/

BOOL CTScriptParser::ParseTerm (/*int iTrIndex*/)
{
	BOOL bHasError = FALSE;
	
	int iInstrIndex;
	
	// Parse the first factor
	bHasError = ParseFactor ();
	
	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	
	// The current operator type
	int iOpType = GetCurrOp ();
	Token tok;
	
	// Parse any subsequent *, /, %, ^, &, |, #, << and >> operators
	while ( TRUE )
	{
		tok = GetNextToken();
		iOpType = GetCurrOp ();
		
		// Get the next token
		if ( tok != TOKEN_TYPE_OP ||
			( iOpType != OP_TYPE_MUL &&
			iOpType != OP_TYPE_DIV &&
			iOpType != OP_TYPE_MOD &&
			iOpType != OP_TYPE_EXP &&
			iOpType != OP_TYPE_BITWISE_AND &&
			iOpType != OP_TYPE_BITWISE_OR &&
			iOpType != OP_TYPE_BITWISE_XOR &&
			iOpType != OP_TYPE_BITWISE_SHIFT_LEFT &&
			iOpType != OP_TYPE_BITWISE_SHIFT_RIGHT ) )
		{
			RewindTokenStream ();
			break;
		}
		
		// Save the operator
		iOpType = GetCurrOp ();
		
		// Parse the second factor
		bHasError = ParseFactor ();
		if (bHasError)
		{
			SkipToNextStatement();
			break;
		}
		
		// Pop the first operand into _T1
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
		
		// Pop the second operand into _T0
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		
		// Perform the binary operation associated with the specified operator
		int iOpInstr;
		switch ( iOpType )
		{
			// Binary multiplication
		case OP_TYPE_MUL:
			iOpInstr = INSTRUCT_MUL;
			break;
			
			// Binary division
		case OP_TYPE_DIV:
			iOpInstr = INSTRUCT_DIV;
			break;
			
			// Binary modulus
		case OP_TYPE_MOD:
			iOpInstr = INSTRUCT_MOD;
			break;
			
			// Binary exponentiation
		case OP_TYPE_EXP:
			iOpInstr = INSTRUCT_EXP;
			break;
			
			// Binary bitwise AND
		case OP_TYPE_BITWISE_AND:
			iOpInstr = INSTRUCT_AND;
			break;
			
			// Binary bitwise OR
		case OP_TYPE_BITWISE_OR:
			iOpInstr = INSTRUCT_OR;
			break;
			
			// Binary bitwise XOR
		case OP_TYPE_BITWISE_XOR:
			iOpInstr = INSTRUCT_XOR;
			break;
			
			// Binary bitwise shift left
		case OP_TYPE_BITWISE_SHIFT_LEFT:
			iOpInstr = INSTRUCT_SHL;
			break;
			
			// Binary bitwise shift left
		case OP_TYPE_BITWISE_SHIFT_RIGHT:
			iOpInstr = INSTRUCT_SHR;
			break;
		}
		
		iInstrIndex = AddICodeInstr ( m_iCurrScope, iOpInstr );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
		
		// Push the result (stored in _T0)
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
	}
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseFactor ()
*
*   Parses a factor.
*/

BOOL CTScriptParser::ParseFactor (/*int iTrIndex*/)
{
	BOOL bHasError = FALSE;
	
	int iInstrIndex;
	int iUnaryOpPending = FALSE;
	Token tok = GetNextToken();
	int iOpType = GetCurrOp ();
	
	// First check for a unary operator
	if ( tok == TOKEN_TYPE_OP &&
		( iOpType == OP_TYPE_ADD ||
		iOpType == OP_TYPE_SUB ||
		iOpType == OP_TYPE_BITWISE_NOT ||
		iOpType == OP_TYPE_LOGICAL_NOT ) )
	{
		// If it was found, save it and set the unary operator flag
		iUnaryOpPending = TRUE;
	}
	else
	{
		// Otherwise rewind the token stream
		RewindTokenStream ();
	}
	
	// Determine which type of factor we're dealing with based on the next token
	Token nToken = GetNextToken();

	switch ( nToken/*GetNextToken ()*/ )
	{
		// It's a true or false constant, so push either 0 and 1 onto the stack
	case TOKEN_TYPE_RSRVD_TRUE:
	case TOKEN_TYPE_RSRVD_FALSE:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
		AddIntICodeOp ( m_iCurrScope, iInstrIndex, GetCurrToken () == TOKEN_TYPE_RSRVD_TRUE ? 1 : 0 );
		break;
		
		// It's an integer literal, so push it onto the stack
	case TOKEN_TYPE_INT:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
		AddIntICodeOp ( m_iCurrScope, iInstrIndex, atoi ( GetCurrLexeme () ) );
		break;
		
		// It's a float literal, so push it onto the stack
	case TOKEN_TYPE_FLOAT:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
		AddFloatICodeOp ( m_iCurrScope, iInstrIndex, ( float ) atof ( GetCurrLexeme () ) );

		break;
		
		// It's a string literal, so add it to the string table and push the resulting
		// string index onto the stack
	case TOKEN_TYPE_STRING:
		{
			int iStringIndex = AddString ( GetCurrLexeme () );
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
			AddStringICodeOp ( m_iCurrScope, iInstrIndex, iStringIndex );
			break;
		}
		
		// It's an identifier
	case TOKEN_TYPE_IDENT:
		{
			// First find out if the identifier is a variable or array
			CSymbolNode * pSymbol = GetSymbolByIdent ( GetCurrLexeme (), m_iCurrScope );
			if ( pSymbol )
			{
				// Does an array index follow the identifier?
				if ( GetLookAheadChar () == '[' )
				{
					// Ensure the variable is an array
					if ( pSymbol->m_iSize == 1 )
					{
						AddCodeSyntaxError ( ERROR_MSG_INVALID_ARRAY );
					}
					
					// Verify the opening brace
					ReadToken ( TOKEN_TYPE_DELIM_OPEN_BRACE );
					
					// Make sure an expression is present
					if ( GetLookAheadChar () == ']' )
					{
						AddCodeSyntaxError ( ERROR_MSG_INVALID_EXPRESSION );
					}
					
					// Parse the index as an expression recursively
					bHasError = ParseExpr ();
					
					// Make sure the index is closed
					ReadToken ( TOKEN_TYPE_DELIM_CLOSE_BRACE );
					
					// Pop the resulting value into _T0 and use it as the index variable
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
					AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
					
					// Push the original identifier onto the stack as an array, indexed
					// with _T0
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
					AddArrayIndexVarICodeOp ( m_iCurrScope, iInstrIndex, pSymbol->m_iIndex, m_iTempVar0SymbolIndex );
				}
				else
				{
					// If not, make sure the identifier is not an array, and push it onto
					// the stack
					if ( pSymbol->m_iSize == 1 )
					{
						iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
						AddVarICodeOp ( m_iCurrScope, iInstrIndex, pSymbol->m_iIndex );
					}
					else
					{
						AddCodeSyntaxError ( ERROR_MSG_ARRAY_MUST_BE_INDEXED );
					}
				}
			}
			else
			{
				// The identifier wasn't a variable or array, so find out if it's a
				// function
				if ( GetFuncByName ( GetCurrLexeme () ) )
				{
					// It is, so parse the call
					ParseFuncCall ();
					
					// Push the return value
					iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
					AddRegICodeOp ( m_iCurrScope, iInstrIndex, REG_CODE_RETVAL );
				}
				else 
				{
					AddCodeSyntaxError ( ERROR_MSG_INVALID_IDENTIFIER , GetCurrLexeme());
				}
			}
			break;
		}
		
		// It's a nested expression, so call ParseExpr () recursively and validate the
		// presence of the closing parenthesis
	case TOKEN_TYPE_DELIM_OPEN_PAREN:
		ParseExpr ();
		ReadToken ( TOKEN_TYPE_DELIM_CLOSE_PAREN );
		break;
		
	case TOKEN_TYPE_RSRVD_FUNC_ABS:
	case TOKEN_TYPE_RSRVD_FUNC_SQRT:
	case TOKEN_TYPE_RSRVD_FUNC_LOG10:
	case TOKEN_TYPE_RSRVD_FUNC_LOG:
	case TOKEN_TYPE_RSRVD_FUNC_SIN:
	case TOKEN_TYPE_RSRVD_FUNC_COS:
	case TOKEN_TYPE_RSRVD_FUNC_TAN:
	case TOKEN_TYPE_RSRVD_FUNC_CTAN:
	case TOKEN_TYPE_RSRVD_FUNC_ASIN:
	case TOKEN_TYPE_RSRVD_FUNC_ACOS:
	case TOKEN_TYPE_RSRVD_FUNC_ATAN:
	case TOKEN_TYPE_RSRVD_FUNC_CEIL:
	case TOKEN_TYPE_RSRVD_FUNC_FLOOR:
	case TOKEN_TYPE_RSRVD_FUNC_ATOF:
	case TOKEN_TYPE_RSRVD_FUNC_ATOL:
	case TOKEN_TYPE_RSRVD_FUNC_FTOA:
	case TOKEN_TYPE_RSRVD_FUNC_LTOA:
	case TOKEN_TYPE_RSRVD_FUNC_POW:
	case TOKEN_TYPE_RSRVD_FUNC_ATAN2:
	case TOKEN_TYPE_RSRVD_FUNC_MIN:
	case TOKEN_TYPE_RSRVD_FUNC_MAX:
	case TOKEN_TYPE_RSRVD_FUNC_HYPOT:
	case TOKEN_TYPE_RSRVD_FUNC_FMOD:
	case TOKEN_TYPE_RSRVD_FUNC_DIGIT:
	case TOKEN_TYPE_RSRVD_FUNC_BINARY:
		{
			CTInstruct *pFind = CTScriptInstructs::Find(GetCurrLexeme ());
			
			if (pFind != NULL)
			{
				ParseMathFunc();
			}
			else
			{
				AddCodeSyntaxError ( ERROR_MSG_INVALID_IDENTIFIER , GetCurrLexeme());
			}
		}
		break;
		// Anything else is invalid
	default:
		{
			AddCodeSyntaxError ( ERROR_MSG_INVALID_INPUT );
		}
	}
	
	// Is a unary operator pending?
	if ( iUnaryOpPending )
	{
		/*
		 *	pop _t0
		 */
		// If so, pop the result of the factor off the top of the stack
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );

		// Perform the unary operation
		if ( iOpType == OP_TYPE_LOGICAL_NOT )
		{
			// Get a pair of free jump target indices
			/*
			 *	mov  _t1, 0
			 *  sub  _t1, _t0
			 *  push _t1
			 */
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_MOV );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
			AddIntICodeOp ( m_iCurrScope, iInstrIndex, 0 );
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_SUB );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
		}
		else
		{
			int iOpIndex;
			switch ( iOpType )
			{
				// Negation
			case OP_TYPE_SUB:
				iOpIndex = INSTRUCT_NEG;
				break;
				
				// Bitwise not
			case OP_TYPE_BITWISE_NOT:
				iOpIndex = INSTRUCT_NOT;
				break;
			}
			iInstrIndex = AddICodeInstr ( m_iCurrScope, iOpIndex );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
			
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		}
	}
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseIf ()
*
*   Parses an if block.
*
*       if ( <Expression> ) <Statement>
*       if ( <Expression> ) <Statement> else <Statement>
*/

BOOL CTScriptParser::ParseIf ()
{
	BOOL bHasError = FALSE;
	
	int iInstrIndex;
	
	// Make sure we're inside a function
	if ( m_iCurrScope == SCOPE_GLOBAL )
		AddCodeSyntaxError ( ERROR_MSG_IF_IN_GLOBAL );
	
	// Annotate the line
	AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
	
	// Create a jump target to mark the beginning of the false block
	int iFalseJumpTargetIndex = GetNextJumpTargetIndex ();
	
	// Read the opening parenthesis
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_OPEN_PAREN );
	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Parse the expression and leave the result on the stack
	bHasError = ParseExpr ();
	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	// Read the closing parenthesis
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_PAREN );
	if (bHasError)
	{
		SkipToNextStatement();
	}
	
	// Pop the result into _T0 and compare it to zero
	iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
	AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );

	// If the result is zero, jump to the false target
	iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JE );
	AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
	AddIntICodeOp ( m_iCurrScope, iInstrIndex, 0 );
	AddJumpTargetICodeOp ( m_iCurrScope, iInstrIndex, iFalseJumpTargetIndex );
	
	// Parse the true block
	bHasError = ParseStatement ();
	
	// Look for an else clause
	if ( GetNextToken () == TOKEN_TYPE_RSRVD_ELSE )
	{
		// If it's found, append the true block with an unconditional jump past the false
		// block
		int iSkipFalseJumpTargetIndex = GetNextJumpTargetIndex ();
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JMP );
		AddJumpTargetICodeOp ( m_iCurrScope, iInstrIndex, iSkipFalseJumpTargetIndex );
		
		// Place the false target just before the false block
		AddICodeJumpTarget ( m_iCurrScope, iFalseJumpTargetIndex );
		
		// Parse the false block
		bHasError = ParseStatement ();
		
		// Set a jump target beyond the false block
		AddICodeJumpTarget ( m_iCurrScope, iSkipFalseJumpTargetIndex );
	}
	else
	{
		// Otherwise, put the token back
		RewindTokenStream ();
		
		// Place the false target after the true block
		AddICodeJumpTarget ( m_iCurrScope, iFalseJumpTargetIndex );
	}
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseWhile ()
*
*   Parses a while loop block.
*
*       while ( <Expression> ) <Statement>
*/

BOOL CTScriptParser::ParseWhile ()
{
	BOOL bHasError = FALSE;
	
	int iInstrIndex;
	
	// Make sure we're inside a function	
	if ( m_iCurrScope == SCOPE_GLOBAL )
	{
		AddCodeSyntaxError ( ERROR_MSG_STATEMENT_IN_GLOBAL );
	}
	
	// Annotate the line	
	AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
	
	// Get two jump targets; for the top and bottom of the loop
	int iStartTargetIndex = GetNextJumpTargetIndex (),
		iEndTargetIndex = GetNextJumpTargetIndex ();
	
	// Set a jump target at the top of the loop
	AddICodeJumpTarget ( m_iCurrScope, iStartTargetIndex );
	
	// Read the opening parenthesis
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_OPEN_PAREN );

	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Parse the expression and leave the result on the stack
	bHasError = ParseExpr ();
	
	// Read the closing parenthesis
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_PAREN );
	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Pop the result into _T0 and jump out of the loop if it's nonzero
	iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
	AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
	
	iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JE );
	AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
	AddIntICodeOp ( m_iCurrScope, iInstrIndex, 0 );
	AddJumpTargetICodeOp ( m_iCurrScope, iInstrIndex, iEndTargetIndex );
	
	// Create a new loop instance structure
	Loop * pLoop = ( Loop * ) malloc ( sizeof ( Loop ) );
	
	// Set the starting and ending jump target indices
	pLoop->m_iStartTargetIndex = iStartTargetIndex;
	pLoop->m_iEndTargetIndex   = iEndTargetIndex;
	
	// Push the loop structure onto the stack
	//Push ( & m_oLoopStack, pLoop );
	m_oLoopStack.Push(pLoop );
	
	// Parse the loop body
	bHasError = ParseStatement ();
	
	// Pop the loop instance off the stack
	//Pop ( & m_oLoopStack );
	m_oLoopStack.Pop();
	
	// Unconditionally jump back to the start of the loop
	iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JMP );
	AddJumpTargetICodeOp ( m_iCurrScope, iInstrIndex, iStartTargetIndex );
	
	// Set a jump target for the end of the loop
	AddICodeJumpTarget ( m_iCurrScope, iEndTargetIndex );
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseFor ()
*
*   Parses a for loop block.
*
*       for ( <Initializer>; <Condition>; <Perpetuator> ) <Statement>
*/

BOOL CTScriptParser::ParseFor ()
{
	BOOL bHasError = FALSE;
	
	if ( m_iCurrScope == SCOPE_GLOBAL )
		AddCodeSyntaxError ( ERROR_MSG_FOR_IN_GLOBAL );
	
	// Annotate the line
	
	AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
	
	/*
	A for loop parser implementation could go here
	*/
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseBreak ()
*
*   Parses a break statement.
*/

BOOL CTScriptParser::ParseBreak ()
{
	BOOL bHasError = FALSE;
	
	// Make sure we're in a loop
	
	if ( m_oLoopStack.IsEmpty() )
	{
		AddCodeSyntaxError ( ERROR_MSG_BREAK_OUTSIDE_LOOP );
	}
	
	// Annotate the line
	AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
	
	// Attempt to read the semicolon
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );

	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Get the jump target index for the end of the loop
	int iTargetIndex = ( ( Loop * ) m_oLoopStack.Peek () )->m_iEndTargetIndex;
	
	// Unconditionally jump to the end of the loop
	int iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JMP );
	AddJumpTargetICodeOp ( m_iCurrScope, iInstrIndex, iTargetIndex );
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseContinue ()
*
*   Parses a continue statement.
*/

BOOL CTScriptParser::ParseContinue ()
{
	BOOL bHasError = FALSE;
	
	// Make sure we're inside a function
	
	if ( m_oLoopStack.IsEmpty ( ) )
	{
		AddCodeSyntaxError ( ERROR_MSG_CONTINUE_OUTSIDE_LOOP );
	}
	
	// Annotate the line	
	AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
	
	// Attempt to read the semicolon	
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );
	if(bHasError)
	{
		RewindTokenStream();
	}

	// Get the jump target index for the start of the loop
	
	int iTargetIndex = ( ( Loop * ) m_oLoopStack.Peek ( ) )->m_iStartTargetIndex;	
	// Unconditionally jump to the end of the loop
	
	int iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_JMP );
	AddJumpTargetICodeOp ( m_iCurrScope, iInstrIndex, iTargetIndex );
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseReturn ()
*
*   Parses a return statement.
*
*   return;
*   return <expr>;
*/

BOOL CTScriptParser::ParseReturn ()
{
	BOOL bHasError = FALSE;
	
	int iInstrIndex;
	
	// Make sure we're inside a function
	if ( m_iCurrScope == SCOPE_GLOBAL )
	{
		AddCodeSyntaxError ( ERROR_MSG_RETURN_IN_GLOBAL );
	}
	
	// Annotate the line
	AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
	
	// If a semicolon doesn't appear to follow, parse the expression and place it in
	// _RetVal
	
	if ( GetLookAheadChar () != ';' )
	{
		// Parse the expression to calculate the return value and leave the result on the stack.
		bHasError = ParseExpr ();
		
		// Determine which function we're returning from
		if ( m_ScriptHeader.m_iIsMainFuncPresent &&
			m_ScriptHeader.m_iMainFuncIndex == m_iCurrScope )
		{
			// It is _Main (), so pop the result into _T0
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		}
		else
		{
			// It's not _Main, so pop the result into the _RetVal register
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
			AddRegICodeOp ( m_iCurrScope, iInstrIndex, REG_CODE_RETVAL );
		}
	}
	else
	{
		// Clear _T0 in case we're exiting _Main ()
		if ( m_ScriptHeader.m_iIsMainFuncPresent &&
			m_ScriptHeader.m_iMainFuncIndex == m_iCurrScope )
		{
			
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_MOV );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
			AddIntICodeOp ( m_iCurrScope, iInstrIndex, 0 );
		}
	}
	
	if ( m_ScriptHeader.m_iIsMainFuncPresent &&
		m_ScriptHeader.m_iMainFuncIndex == m_iCurrScope )
	{
		// It's _Main, so exit the script with _T0 as the exit code
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_EXIT );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
	}
	else
	{
		// It's not _Main, so return from the function
		AddICodeInstr ( m_iCurrScope, INSTRUCT_RET );
	}
	
	// Validate the presence of the semicolon
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );
	if (bHasError)
	{
		RewindTokenStream();
	}

	return bHasError;
}

/******************************************************************************************
*
*   ParseAssign ()
*
*   Parses an assignment statement.
*
*   <Ident> <Assign-CICodeOperand> <Expr>;
*/

BOOL CTScriptParser::ParseAssign ()
{
	BOOL bHasError = FALSE;
	
	// Make sure we're inside a function
	if ( m_iCurrScope == SCOPE_GLOBAL )
	{
		AddCodeSyntaxError ( ERROR_MSG_ASSIGNMENT_IN_GLOBAL );
	}
	
	int iInstrIndex;
	
	// Assignment operator
	int iAssignOp;
	
	// Annotate the line
	AddICodeSourceLine ( m_iCurrScope, GetCurrSourceLine () );
	
	// ---- Parse the variable or array
	CSymbolNode * pSymbol = GetSymbolByIdent ( GetCurrLexeme (), m_iCurrScope );
	
	// Does an array index follow the identifier?
	int iIsArray = FALSE;
	if ( GetLookAheadChar () == '[' )
	{
		// Ensure the variable is an array
		if ( pSymbol->m_iSize == 1 )
		{
			AddCodeSyntaxError ( ERROR_MSG_INVALID_ARRAY );
		}
		
		// Verify the opening brace
		bHasError = ReadToken ( TOKEN_TYPE_DELIM_OPEN_BRACE );
		
		// Make sure an expression is present
		if ( GetLookAheadChar () == ']' )
		{
			AddCodeSyntaxError ( ERROR_MSG_INVALID_EXPRESSION );
		}
		
		// Parse the index as an expression
		bHasError = ParseExpr ();
		
		// Make sure the index is closed
		bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_BRACE );

		if (bHasError)
		{
			RewindTokenStream();
		}
		
		// Set the array flag
		iIsArray = TRUE;
	}
	else
	{
		// Make sure the variable isn't an array
		if ( pSymbol->m_iSize > 1 )
		{
			AddCodeSyntaxError ( ERROR_MSG_ARRAY_MUST_BE_INDEXED );
		}
	}
	
	// ---- Parse the assignment operator
	
	if ( GetNextToken () != TOKEN_TYPE_OP &&
		( GetCurrOp () != OP_TYPE_ASSIGN &&
		GetCurrOp () != OP_TYPE_ASSIGN_ADD &&
		GetCurrOp () != OP_TYPE_ASSIGN_SUB &&
		GetCurrOp () != OP_TYPE_ASSIGN_MUL &&
		GetCurrOp () != OP_TYPE_ASSIGN_DIV &&
		GetCurrOp () != OP_TYPE_ASSIGN_MOD &&
		GetCurrOp () != OP_TYPE_ASSIGN_EXP &&
		GetCurrOp () != OP_TYPE_ASSIGN_CONCAT &&
		GetCurrOp () != OP_TYPE_ASSIGN_AND &&
		GetCurrOp () != OP_TYPE_ASSIGN_OR &&
		GetCurrOp () != OP_TYPE_ASSIGN_XOR &&
		GetCurrOp () != OP_TYPE_ASSIGN_SHIFT_LEFT &&
		GetCurrOp () != OP_TYPE_ASSIGN_SHIFT_RIGHT ) )
	{
		AddCodeSyntaxError ( ERROR_MSG_ILLEGAL_ASSIGNMENT_OPTR );
	}
	else
	{
		iAssignOp = GetCurrOp ();
	}
	
	// ---- Parse the value expression
	
	bHasError = ParseExpr ();
	
	// Validate the presence of the semicolon
	
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_SEMICOLON );

	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Pop the value into _T0
	
	iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
	AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
	
	// If the variable was an array, pop the top of the stack into _T1 for use as the index
	
	if ( iIsArray )
	{
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
	}
	
	// ---- Generate the I-code for the assignment instruction
	
	switch ( iAssignOp )
	{
		// =
		
	case OP_TYPE_ASSIGN:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_MOV );
		break;
		
		// +=
		
	case OP_TYPE_ASSIGN_ADD:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_ADD );
		break;
		
		// -=
		
	case OP_TYPE_ASSIGN_SUB:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_SUB );
		break;
		
		// *=
		
	case OP_TYPE_ASSIGN_MUL:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_MUL );
		break;
		
		// /=
		
	case OP_TYPE_ASSIGN_DIV:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_DIV );
		break;
		
		// %=
		
	case OP_TYPE_ASSIGN_MOD:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_MOD );
		break;
		
		// ^=
		
	case OP_TYPE_ASSIGN_EXP:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_EXP );
		break;
		
		// $=
		
	case OP_TYPE_ASSIGN_CONCAT:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_CONCAT );
		break;
		
		// &=
		
	case OP_TYPE_ASSIGN_AND:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_AND );
		break;
		
		// |=
		
	case OP_TYPE_ASSIGN_OR:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_OR );
		break;
		
		// #=
		
	case OP_TYPE_ASSIGN_XOR:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_XOR );
		break;
		
		// <<=
		
	case OP_TYPE_ASSIGN_SHIFT_LEFT:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_SHL );
		break;
		
		// >>=
		
	case OP_TYPE_ASSIGN_SHIFT_RIGHT:
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_SHR );
		break;
	}
	
	// Generate the destination operand
	
	if ( iIsArray )
		AddArrayIndexVarICodeOp ( m_iCurrScope, iInstrIndex, pSymbol->m_iIndex, m_iTempVar1SymbolIndex );
	else
		AddVarICodeOp ( m_iCurrScope, iInstrIndex, pSymbol->m_iIndex );
	
	// Generate the source
	
	AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseFuncCall ()
*
*   Parses a function call
*
*   <Ident> ( <Expr>, <Expr> );
*/

BOOL CTScriptParser::ParseFuncCall ()
{
	BOOL bHasError = FALSE;
	
	// Get the function by it's identifier
	
	CFuncNode * pFunc = GetFuncByName ( GetCurrLexeme () );
	
	// It is, so start the parameter count at zero
	
	int iParamCount = 0;
	
	// Attempt to read the opening parenthesis
	
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_OPEN_PAREN );
	if (bHasError)
	{
		SkipToNextStatement();
		return bHasError;
	}
	
	// Parse each parameter and push it onto the stack	
	while ( TRUE )
	{
		// Find out if there's another parameter to push
		
		if ( GetLookAheadChar () != ')' )
		{
			// There is, so parse it as an expression
			
			bHasError = ParseExpr ();
			
			if (bHasError)
			{
				SkipToNextStatement();
				break;
			}
			// Increment the parameter count and make sure it's not greater than the amount
			// accepted by the function (unless it's a host API function
			++ iParamCount;

			if (( ! pFunc->m_iIsHostAPI) && iParamCount > pFunc->m_iParamCount )
			{
				AddCodeSyntaxError ( ERROR_MSG_TOO_MANY_PARAMETERS );
			}
			
			// Unless this is the final parameter, attempt to read a comma
			
			if ( GetLookAheadChar () != ')' )
			{
				ReadToken ( TOKEN_TYPE_DELIM_COMMA );
			}
		}
		else
		{
			// There isn't, so break the loop and complete the call
			
			break;
		}
	}
	
	// Attempt to read the closing parenthesis
	
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_PAREN );

	if (bHasError)
	{
		RewindTokenStream();
	}
	
	// Make sure the parameter wasn't passed too few parameters (unless
	// it's a host API function)
	
	if ( (! pFunc->m_iIsHostAPI) && iParamCount < pFunc->m_iParamCount )
	{
		AddCodeSyntaxError ( ERROR_MSG_TOO_MANY_PARAMETERS );
	}
	

	// Call the function, but make sure the right call instruction is used
	int iInstrIndex = 0;

	int iCallInstr = INSTRUCT_CALL;
	if ( pFunc->m_iIsHostAPI )
	{
		iCallInstr = INSTRUCT_CALLHOST;

		//参数个数
		iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
		AddIntICodeOp ( m_iCurrScope, iInstrIndex, iParamCount );	
	}
	
	iInstrIndex = AddICodeInstr ( m_iCurrScope, iCallInstr );
	AddFuncICodeOp ( m_iCurrScope, iInstrIndex, pFunc->m_iIndex );
	
	return bHasError;
}

/******************************************************************************************
*
*   ParseMathFunc ()
*
*   Parses a math function call
*
*   <Ident> ( <Expr>[, <Expr>, ... ] );
*/

BOOL CTScriptParser::ParseMathFunc(/*int iTrIndex*/)
{
	BOOL bHasError = FALSE;
	
	// Make sure we're inside a function
	if ( m_iCurrScope == SCOPE_GLOBAL )
	{
		AddCodeSyntaxError ( ERROR_MSG_MATH_FUNC_IN_GLOBAL );
	}
	
	int iInstrIndex = 0;
	
	// Assignment operator
	int iAssignOp = 0;
	
	CTInstruct *pMathInstr = CTScriptInstructs::Find(m_oCurrLexerState.m_pstrCurrLexeme);
	
	switch(pMathInstr->m_nOpcode) 
	{
		/*
		 *	<Ident> ( <Expr>)  ==>>   Ident _T0, _T1
		 *  pop _T1
		 *  Ident _T0,   _T1
		 *  push _T0
		 */
	case TOKEN_TYPE_RSRVD_FUNC_ABS:
	case TOKEN_TYPE_RSRVD_FUNC_SQRT:
	case TOKEN_TYPE_RSRVD_FUNC_LOG10:
	case TOKEN_TYPE_RSRVD_FUNC_LOG:
	case TOKEN_TYPE_RSRVD_FUNC_SIN:
	case TOKEN_TYPE_RSRVD_FUNC_COS:
	case TOKEN_TYPE_RSRVD_FUNC_TAN:
	case TOKEN_TYPE_RSRVD_FUNC_CTAN:
	case TOKEN_TYPE_RSRVD_FUNC_ASIN:
	case TOKEN_TYPE_RSRVD_FUNC_ACOS:
	case TOKEN_TYPE_RSRVD_FUNC_ATAN:
	case TOKEN_TYPE_RSRVD_FUNC_CEIL:
	case TOKEN_TYPE_RSRVD_FUNC_FLOOR:
	case TOKEN_TYPE_RSRVD_FUNC_ATOF:
	case TOKEN_TYPE_RSRVD_FUNC_ATOL:
	case TOKEN_TYPE_RSRVD_FUNC_FTOA:
	case TOKEN_TYPE_RSRVD_FUNC_LTOA:
		{
			// Read the opening parenthesis
			bHasError = ReadToken ( TOKEN_TYPE_DELIM_OPEN_PAREN );

			if (bHasError)
			{
				RewindTokenStream();
			}
			
			// Parse the expression and leave the result on the stack
			bHasError = ParseExpr ();
			
			//Add pop instruction
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );

			//Add pop instruction
			iInstrIndex = AddICodeInstr ( m_iCurrScope
				, TOKEN_TYPE_RSRVD_FUNC_to_INSTRUCT( pMathInstr->m_nOpcode ) );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
			
			//Add pop instruction
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
		}
		break;
	case TOKEN_TYPE_RSRVD_FUNC_POW:
	case TOKEN_TYPE_RSRVD_FUNC_ATAN2:
	case TOKEN_TYPE_RSRVD_FUNC_MIN:
	case TOKEN_TYPE_RSRVD_FUNC_MAX:
	case TOKEN_TYPE_RSRVD_FUNC_HYPOT:
	case TOKEN_TYPE_RSRVD_FUNC_FMOD:
	case TOKEN_TYPE_RSRVD_FUNC_DIGIT:
	case TOKEN_TYPE_RSRVD_FUNC_BINARY:
		{
			// Read the opening parenthesis
			bHasError = ReadToken ( TOKEN_TYPE_DELIM_OPEN_PAREN );

			if (bHasError)
			{
				RewindTokenStream();
			}
			
			// Parse the expression and leave the result on the stack
			bHasError = ParseExpr ();
			
			// Read the opening parenthesis
			bHasError = ReadToken ( TOKEN_TYPE_DELIM_COMMA );
			if (bHasError)
			{
				RewindTokenStream();
			}

			// Parse the expression and leave the result on the stack
			bHasError = ParseExpr ();

			//Add pop instruction
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_POP );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar2SymbolIndex );
			
			//Add pop instruction
			iInstrIndex = AddICodeInstr ( m_iCurrScope
				, TOKEN_TYPE_RSRVD_FUNC_to_INSTRUCT( pMathInstr->m_nOpcode ) );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar1SymbolIndex );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar2SymbolIndex );
			
			//Add pop instruction
			iInstrIndex = AddICodeInstr ( m_iCurrScope, INSTRUCT_PUSH );
			AddVarICodeOp ( m_iCurrScope, iInstrIndex, m_iTempVar0SymbolIndex );			
		}
		break;
	default:
		break;
	}

	// Read the opening parenthesis
	bHasError = ReadToken ( TOKEN_TYPE_DELIM_CLOSE_PAREN );

	if (bHasError)
	{
		RewindTokenStream();
	}
	
	return bHasError;
}

int CTScriptParser::AddString(const char* pstrData)
{
	POS pos = m_oStringTable.GetHeadPosition();
	char *pString = NULL;
	int  iTemp = 0;
	bool bFind = false;

	while (pos != NULL)
	{
		pString = m_oStringTable.GetNext(pos);

		if (strcmp(pstrData, pString) == 0)
		{
			bFind = true;
			break;
		}
		
		iTemp++;
	}

	if (!bFind)
	{
		iTemp = strlen(pstrData);
		pString = new char [iTemp+1];
		strcpy(pString, pstrData);
		m_oStringTable.AddNode(pString);
		iTemp = m_oStringTable.GetCount()-1;
	}

	return iTemp;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ---- Instruction Mnemonics -------------------------------------------------------------

// These mnemonics are mapped to each I-code instruction, allowing the emitter to
// easily translate I-code to XVM assembly

const char CTScriptParser::m_ppstrInsctructs [][ 12 ] =
{
	"Mov",
	"Add", "Sub", "Mul", "Div", "Mod", "Exp", "Neg", "Inc", "Dec",
	"And", "Or", "XOr", "Not", "ShL", "ShR",
	"Concat", "GetChar", "SetChar",
	"Jmp", "JE", "JNE", "JG", "JL", "JGE", "JLE",
	"Push", "Pop",
	"Call", "Ret", "CallHost",
	"Pause", "Exit",
	"abs", "pow", "sqrt", "log10", "log", "sin", "cos", "tan", "ctan", "asin", "acos",
	"atan", "atan2", "min", "max", "ceil", "floor", "hypot", "fmod", "digit", "binary",
	"atof", "atol", "ftoa", "ltoa", "cmp", "cmpe", "cmpne", "cmpg", "cmpl", "cmpge", "cmple"
};

// ---- Functions -----------------------------------------------------------------------------


/******************************************************************************************
*
*   EmitHeader ()
*
*   Emits the script's header comments.
*/

void CTScriptParser::EmitHeader_Buffer ()
{
	// Emit the filename	
	m_oAnsiTasmBuffer.sprintf("; %s\r\r\n", m_pstrOutputFile );
	
	// Emit the rest of the header	
	m_oAnsiTasmBuffer.sprintf("; Source File: %s\r\n", g_pstrSourceFile );
	m_oAnsiTasmBuffer.sprintf("; XSC Version: %d.%d\r\n", VERSION_MAJOR, VERSION_MINOR );
}


/******************************************************************************************
*
*   EmitDirectives ()
*
*   Emits the script's directives.
*/

void CTScriptParser::EmitDirectives_Buffer ()
{
	// If directives were emitted, this is set to TRUE so we remember to insert extra line
	// breaks after them
	int iAddNewline = FALSE;
	
	// If the stack size has been set, emit a SetStackSize directive
	if ( m_ScriptHeader.m_iStackSize )
	{
		m_oAnsiTasmBuffer.sprintf("SetStackSize %d\r\n", m_ScriptHeader.m_iStackSize );
		iAddNewline = TRUE;
	}
	
	// If the priority has been set, emit a SetPriority directive
	if ( m_ScriptHeader.m_iPriorityType != PRIORITY_NONE )
	{
		m_oAnsiTasmBuffer.sprintf("SetPriority " );
		switch ( m_ScriptHeader.m_iPriorityType )
		{
			// Low rank
		case PRIORITY_LOW:
			m_oAnsiTasmBuffer.sprintf(PRIORITY_LOW_KEYWORD );
			break;
			
			// Medium rank
		case PRIORITY_MED:
			m_oAnsiTasmBuffer.sprintf(PRIORITY_MED_KEYWORD );
			break;
			
			// High rank
		case PRIORITY_HIGH:
			m_oAnsiTasmBuffer.sprintf(PRIORITY_HIGH_KEYWORD );
			break;
			
			// User-defined timeslice
		case PRIORITY_USER:
			m_oAnsiTasmBuffer.sprintf("%d", m_ScriptHeader.m_iUserPriority );
			break;
		}
		m_oAnsiTasmBuffer.sprintf("\r\n" );
		
		iAddNewline = TRUE;
	}
	
	// If necessary, insert an extra line break
	
	if ( iAddNewline )
		m_oAnsiTasmBuffer.sprintf("\r\n" );
}


/******************************************************************************************
*
*   EmitScopeSymbols ()
*
*   Emits the symbol declarations of the specified scope
*/

void CTScriptParser::EmitScopeSymbols_Buffer ( int iScope, int iType )
{
	// If declarations were emitted, this is set to TRUE so we remember to insert extra
	// line breaks after them
	int iAddNewline = FALSE;
	
	// Local symbol node pointer
	CSymbolNode * pCurrSymbol;
	
	// Loop through each symbol in the table to find the match
	int nNodeCount = m_oSymbolTable.GetCount();
	
	for ( int iCurrSymbolIndex = 0; iCurrSymbolIndex < nNodeCount; ++ iCurrSymbolIndex )
	{
		// Get the current symbol structure
		pCurrSymbol = GetSymbolByIndex ( iCurrSymbolIndex );
		
		// If the scopes and parameter flags match, emit the declaration
		if ( pCurrSymbol->m_iScope == iScope && pCurrSymbol->m_iType == iType )
		{
			if (iScope > 0)
			{
				m_oAnsiTasmBuffer.sprintf("\t" );
			}
			
			// Print one tab stop for global declarations, and two for locals
			if ( iScope != SCOPE_GLOBAL )
				m_oAnsiTasmBuffer.sprintf("" );
			
			// Is the symbol a parameter?
			if ( pCurrSymbol->m_iType == SYMBOL_TYPE_PARAM )
			{
				m_oAnsiTasmBuffer.sprintf("Param %s", pCurrSymbol->m_strName );
			}
			else if ( pCurrSymbol->m_iType == SYMBOL_TYPE_VAR )
			{// Is the symbol a variable?
				m_oAnsiTasmBuffer.sprintf("%s %s", g_pstrScriptKey_var, pCurrSymbol->m_strName );
				
				// If the variable is an array, add the size declaration
				if ( pCurrSymbol->m_iSize > 1 )
				{
					m_oAnsiTasmBuffer.sprintf(" [ %d ]", pCurrSymbol->m_iSize );
				}
			}
			else if ( pCurrSymbol->m_iType == SYMBOL_TYPE_EXPORT_VAR )
			{// Is the symbol a variable?
				m_oAnsiTasmBuffer.sprintf("%s %s %s",g_pstrScriptKey_var, pCurrSymbol->m_strName, g_pstrScriptKey_export );
				
				// If the variable is an array, add the size declaration
				if ( pCurrSymbol->m_iSize > 1 )
				{
					m_oAnsiTasmBuffer.sprintf(" [ %d ]", pCurrSymbol->m_iSize );
				}
			}
			{
			}
			
			m_oAnsiTasmBuffer.sprintf("\r\n" );
			iAddNewline = TRUE;
		}
	}
	
	// If necessary, insert an extra line break
	
	if ( iAddNewline )
	{
		m_oAnsiTasmBuffer.sprintf("\r\n" );
	}
}

void CTScriptParser::EmitInstruct_Buffer(char *pstrInstr, CICodeNode *pICode)
{
	switch ( pICode->m_iType)
	{
		// Source code annotation
	case ICODE_NODE_SOURCE_LINE:
		{
			// Make a local copy of the source line
			char * pstrSourceLine = pICode->m_pstrSourceLine;
			
			// If the last character of the line is a line break, clip it
			int iLastCharIndex = strlen ( pstrSourceLine ) - 1;

			if ( pstrSourceLine [ iLastCharIndex ] == '\n' )
			{
				pstrSourceLine [ iLastCharIndex ] = '\0';
			}

			CAnsiStringPrintf oPrintf(pstrInstr);			
			oPrintf.sprintf ( "\t; %s\r\n", pstrSourceLine );
			pstrInstr += strlen(pstrInstr);
		}
		break;
		
		// An I-code instruction
	case ICODE_NODE_INSTR:
		{
			// Emit the opcode
			CAnsiStringPrintf oBuffer(pstrInstr);
			oBuffer.sprintf ( "\t%s", m_ppstrInsctructs [ pICode->m_pInstruction->m_iOpCode ] );
			pstrInstr += strlen(pstrInstr);
			
			// Determine the number of operands
			int iOpCount = pICode->m_pInstruction->GetCount();
			
			// If there are operands to emit, follow the instruction with some space
			if ( iOpCount )
			{
				// All instructions get at least one tab
				//sprintf ( pstrInstr, "" );
				CAnsiStringPrintf oBuffer(pstrInstr);
				oBuffer.sprintf ( "" );
				pstrInstr += strlen(pstrInstr);
				
				// If it's less than a tab stop's width in characters, however, they get a
				// second
				if ( strlen ( m_ppstrInsctructs [ pICode->m_pInstruction->m_iOpCode ] ) < TAB_STOP_WIDTH )
				{
					//sprintf ( pstrInstr, "" );
					CAnsiStringPrintf oBuffer(pstrInstr);
					oBuffer.sprintf("");
					pstrInstr += strlen(pstrInstr);
				}
			}
			
			// Emit each operand
			for ( int iCurrOpIndex = 0; iCurrOpIndex < iOpCount; ++ iCurrOpIndex )
			{
				// Get a pointer to the operand structure
				CICodeOperand * pOp = pICode->GetICodeOpByIndex ( iCurrOpIndex );
				CAnsiStringPrintf oBuffer(pstrInstr);
				
				// Emit the operand based on its type
				switch ( pOp->m_iType )
				{
					// Integer literal
				case OPERAND_TYPE_INT:
					oBuffer.sprintf(" %d", pOp->m_iIntLiteral );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// Float literal
				case OPERAND_TYPE_FLOAT:
					oBuffer.sprintf(" %f", pOp->m_fFloatLiteral );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// String literal
				case OPERAND_TYPE_STRING_INDEX:
					//oBuffer.sprintf("\"%s\"", GetStringByIndex ( & g_StringTable, pOp->m_iStringIndex ) );
					oBuffer.sprintf(" \"%s\"", m_oStringTable.GetAtIndex( pOp->m_iStringIndex ) );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// Variable
				case OPERAND_TYPE_VAR:
					oBuffer.sprintf(" %s", GetSymbolByIndex ( pOp->m_iSymbolIndex )->m_strName );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// Array index absolute
				case OPERAND_TYPE_ARRAY_INDEX_ABS:
					oBuffer.sprintf(" %s [ %d ]", GetSymbolByIndex ( pOp->m_iSymbolIndex )->m_strName,
						pOp->m_iOffset );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// Array index variable
				case OPERAND_TYPE_ARRAY_INDEX_VAR:
					oBuffer.sprintf(" %s [ %s ]", GetSymbolByIndex ( pOp->m_iSymbolIndex )->m_strName,
						GetSymbolByIndex ( pOp->m_iOffsetSymbolIndex )->m_strName );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// Function
				case OPERAND_TYPE_FUNC_INDEX:
					oBuffer.sprintf(" %s", GetFuncByIndex ( pOp->m_iSymbolIndex )->m_strName );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// Register (just _RetVal for now)
				case OPERAND_TYPE_REG:
					oBuffer.sprintf(" _RetVal" );
					pstrInstr += strlen(pstrInstr);
					break;
					
					// Jump target index
				case OPERAND_TYPE_JUMP_TARGET_INDEX:
					oBuffer.sprintf(" _L%d", pOp->m_iJumpTargetIndex );
					pstrInstr += strlen(pstrInstr);
					break;
				}
				
				// If the operand isn't the last one, append it with a comma and space
				if ( iCurrOpIndex != iOpCount - 1 )
				{
					oBuffer.sprintf(", " );
					pstrInstr += strlen(pstrInstr);
				}
			}
			
			// Finish the line
			//oBuffer.sprintf("\r\n" );
			strcpy(pstrInstr, "\r\n" );
			pstrInstr += strlen(pstrInstr);
		}
		
		break;
		// A jump target
	case ICODE_NODE_JUMP_TARGET:
		{
			// Emit a label in the format _LX, where X is the jump target
			CAnsiStringPrintf oBuffer(pstrInstr);
			oBuffer.sprintf ( " _L%d:\r\n", pICode->m_iJumpTargetIndex );
			pstrInstr += strlen(pstrInstr);
		}
	default:
		break;
	}
}

void CTScriptParser::EmitInstruct_Buffer(CString &strText, CICodeNode *pICode)
{
	char pszTextBuffer[4096];
	ZeroMemory(pszTextBuffer, 4096);
	EmitInstruct_Buffer(pszTextBuffer, pICode);

	strText = pszTextBuffer;
}


/******************************************************************************************
*
*   EmitFunc ()
*   
*   Emits a function, its local declarations, and its code.
*/

void CTScriptParser::EmitFunc_Buffer ( CFuncNode * pFunc )
{
	// Emit the function declaration name and opening brace
	m_oAnsiTasmBuffer.sprintf("Func %s\r\n", pFunc->m_strName );
	m_oAnsiTasmBuffer.sprintf("{\r\n" );
	
	// Emit parameter declarations
	EmitScopeSymbols_Buffer ( pFunc->m_iIndex, SYMBOL_TYPE_PARAM );
	
	// Emit local variable declarations
	EmitScopeSymbols_Buffer ( pFunc->m_iIndex, SYMBOL_TYPE_VAR );
	
	// Does the function have an I-code block?
	int iNodeCount = pFunc->GetCount();
	
	if ( iNodeCount > 0 )
	{
		// Used to determine if the current line is the first
		int iIsFirstSourceLine = TRUE;
		
		// Yes, so loop through each I-code node to emit the code
		for ( int iCurrInstrIndex = 0; iCurrInstrIndex < iNodeCount; ++ iCurrInstrIndex )
		{
			// Get the I-code instruction structure at the current node
			CICodeNode * pICode = GetICodeNodeByImpIndex ( pFunc->m_iIndex, iCurrInstrIndex );
			
			// Determine the node type
			switch ( pICode->m_iType)
			{
				// Source code annotation
			case ICODE_NODE_SOURCE_LINE:
				{
					// Make a local copy of the source line
					char * pstrSourceLine = pICode->m_pstrSourceLine;
					
					// If the last character of the line is a line break, clip it
					int iLastCharIndex = strlen ( pstrSourceLine ) - 1;
					if ( pstrSourceLine [ iLastCharIndex ] == '\n' )
					{
						pstrSourceLine [ iLastCharIndex ] = '\0';
					}
					
					while (*pstrSourceLine == '\t' || *pstrSourceLine == ' ')
					{
						pstrSourceLine++;
					}
					// Emit the comment, but only prepend it with a line break if it's not the
					// first one
					if ( ! iIsFirstSourceLine )
					{
						m_oAnsiTasmBuffer.sprintf("\r\n" );
					}
					
					m_oAnsiTasmBuffer.sprintf("\t; %s\r\n", pstrSourceLine );
				}
				break;
				
				// An I-code instruction
			case ICODE_NODE_INSTR:
				{
					// Emit the opcode
					m_oAnsiTasmBuffer.sprintf("\t%s\t", m_ppstrInsctructs [ pICode->m_pInstruction->m_iOpCode ] );
					
					// Determine the number of operands
					int iOpCount = pICode->m_pInstruction->GetCount();
					
					// If there are operands to emit, follow the instruction with some space
					if ( iOpCount )
					{
						// All instructions get at least one tab
						m_oAnsiTasmBuffer.sprintf("" );
						
						// If it's less than a tab stop's width in characters, however, they get a
						// second
						if ( strlen ( m_ppstrInsctructs [ pICode->m_pInstruction->m_iOpCode ] ) < TAB_STOP_WIDTH )
							m_oAnsiTasmBuffer.sprintf("" );
					}
					
					// Emit each operand
					for ( int iCurrOpIndex = 0; iCurrOpIndex < iOpCount; ++ iCurrOpIndex )
					{
						// Get a pointer to the operand structure
						CICodeOperand * pOp = pICode->GetICodeOpByIndex ( iCurrOpIndex );
						
						// Emit the operand based on its type
						switch ( pOp->m_iType )
						{
							// Integer literal
						case OPERAND_TYPE_INT:
							m_oAnsiTasmBuffer.sprintf("%d", pOp->m_iIntLiteral );
							break;
							
							// Float literal
						case OPERAND_TYPE_FLOAT:
							m_oAnsiTasmBuffer.sprintf("%f", pOp->m_fFloatLiteral );
							break;
							
							// String literal
						case OPERAND_TYPE_STRING_INDEX:
							//m_oAnsiTasmBuffer.sprintf("\"%s\"", GetStringByIndex ( & g_StringTable, pOp->m_iStringIndex ) );
							{
								char *pString = m_oStringTable.GetAtIndex( pOp->m_iStringIndex );
								m_oAnsiTasmBuffer.Char('\"');
								m_oAnsiTasmBuffer.Append(pString, strlen(pString));
								m_oAnsiTasmBuffer.Char('\"');
							}
							break;
							
							// Variable
						case OPERAND_TYPE_VAR:
							m_oAnsiTasmBuffer.sprintf("%s", GetSymbolByIndex ( pOp->m_iSymbolIndex )->m_strName );
							break;
							
							// Array index absolute
						case OPERAND_TYPE_ARRAY_INDEX_ABS:
							m_oAnsiTasmBuffer.sprintf("%s [ %d ]", GetSymbolByIndex ( pOp->m_iSymbolIndex )->m_strName,
								pOp->m_iOffset );
							break;
							
							// Array index variable
						case OPERAND_TYPE_ARRAY_INDEX_VAR:
							m_oAnsiTasmBuffer.sprintf("%s [ %s ]", GetSymbolByIndex ( pOp->m_iSymbolIndex )->m_strName,
								GetSymbolByIndex ( pOp->m_iOffsetSymbolIndex )->m_strName );
							break;
							
							// Function
						case OPERAND_TYPE_FUNC_INDEX:
							m_oAnsiTasmBuffer.sprintf("%s", GetFuncByIndex ( pOp->m_iSymbolIndex )->m_strName );
							break;
							
							// Register (just _RetVal for now)
						case OPERAND_TYPE_REG:
							m_oAnsiTasmBuffer.sprintf("_RetVal" );
							break;
							
							// Jump target index
						case OPERAND_TYPE_JUMP_TARGET_INDEX:
							m_oAnsiTasmBuffer.sprintf("_L%d", pOp->m_iJumpTargetIndex );
							break;
						}
						
						// If the operand isn't the last one, append it with a comma and space
						if ( iCurrOpIndex != iOpCount - 1 )
						{
							m_oAnsiTasmBuffer.sprintf(", " );
						}
					}
					
					// Finish the line
					m_oAnsiTasmBuffer.sprintf("\r\n" );
				}
				
				break;
				// A jump target
			case ICODE_NODE_JUMP_TARGET:
				{
					// Emit a label in the format _LX, where X is the jump target
					m_oAnsiTasmBuffer.sprintf("_L%d:\r\n", pICode->m_iJumpTargetIndex );
				}
			default:
				break;
			}
			
			// Update the first line flag
			if ( iIsFirstSourceLine )
			{
				iIsFirstSourceLine = FALSE;
			}
		}
	}
	else
	{
		// No, so emit a comment saying so
		m_oAnsiTasmBuffer.sprintf("\t; (No code)\r\n" );
	}
	
	// Emit the closing brace
	m_oAnsiTasmBuffer.sprintf("}" );
}


/******************************************************************************************
*
*   EmitCode ()
*
*   Translates the I-code representation of the script to an ASCII-foramtted XVM assembly
*   file.
*/

void CTScriptParser::EmitCode_Buffer ()
{
	m_oAnsiTasmBuffer.SetBufferLength(m_nLength*2+1024);
	// ---- Emit the header
	EmitHeader_Buffer ();
	
	// ---- Emit directives
	m_oAnsiTasmBuffer.sprintf("; ---- Directives ------------------------------\r\n" );
	EmitDirectives_Buffer ();
	
	// ---- Emit global variable declarations
	m_oAnsiTasmBuffer.sprintf("; ---- Global Variables ------------------------------\r\n" );
	
	// Emit local variable declarations
	EmitScopeSymbols_Buffer ( SCOPE_GLOBAL, SYMBOL_TYPE_EXPORT_VAR );
		
	// Emit the globals by printing all non-parameter symbols in the global scope
	EmitScopeSymbols_Buffer ( SCOPE_GLOBAL, SYMBOL_TYPE_VAR );
	
	// ---- Emit functions
	m_oAnsiTasmBuffer.sprintf("; ---- Functions -------------------------------------------\r\n" );
	
	// Local function node pointer
	CFuncNode * pCurrFunc;
	
	// Pointer to hold the _Main () function, if it's found
	CFuncNode * pMainFunc = NULL;
	
	// Loop through each function and emit its declaration and code, if functions exist
	
	POS pos = m_oFuncTable.GetHeadPosition();

	while (pos != NULL)
	{
		pCurrFunc = m_oFuncTable.GetNext(pos);

		if ( ! pCurrFunc->m_iIsHostAPI )
		{
			// Is the current function _Main ()?
			
			//if ( stricmp ( pCurrFunc->m_strName, MAIN_FUNC_NAME ) == 0 )
			if (pCurrFunc->m_strName == MAIN_FUNC_NAME)
			{
				// Yes, so save the pointer for later (and don't emit it yet)
				pMainFunc = pCurrFunc;
			}
			else
			{
				// No, so emit it
				EmitFunc_Buffer ( pCurrFunc );
				m_oAnsiTasmBuffer.sprintf("\r\n" );
			}
		}
	}
	
	// ---- Emit _Main ()
	// If the last pass over the functions found a _Main () function. emit it
	if ( pMainFunc )
	{
		m_oAnsiTasmBuffer.sprintf("; ---- Main ------------------------\r\n" );
		EmitFunc_Buffer( pMainFunc );
	}	
}


/******************************************************************************************
*
*   EmitCode ()
*
*   Translates the I-code representation of the script to an ASCII-foramtted XVM assembly
*   file.
*/

void CTScriptParser::EmitCode_File (const CString &strFileName)
{
	CString strFile;

	if (strFileName.GetLength() == 0)
	{
		strFile = m_pstrOutputFile;
	}
	else
	{
		strFile = strFileName;
	}

	EmitCode_Buffer();
	m_oAnsiTasmBuffer.WriteToFile(strFile);
}

//////////////////////////////////////////////////////////////////////////
void CTScriptParser::OptimizeCode()
{
	OptimizeCode_Pop_Push();
	OptimizeCode_Mov();
}

void CTScriptParser::OptimizeCode_Pop_Push()
{
	CTLinkList<CICodeNode> oListPush, oListPop;
	CFuncNode * pFunc = NULL;
	
	// Loop through each function and emit its declaration and code, if functions exist
	POS pos = m_oFuncTable.GetHeadPosition();
	
	while (pos != NULL)
	{
		pFunc = m_oFuncTable.GetNext(pos);
		
		if ( pFunc->m_iIsHostAPI )
		{
			continue;
		}

		//clear temp push, pop ICode list
		oListPush.RemoveAll();
		oListPop.RemoveAll();

		// Does the function have an I-code block?
		int iNodeCount = pFunc->GetCount();

		if ( iNodeCount > 0 )
		{
			CICodeNode *pPop = NULL;
			CICodeNode * pICode = NULL;
			CICodeNode *pPush = NULL;
			int nPushIndex = 0;
			int nPopIndex = 0;
			int nPushCount = 0;
			int nPopCount = 0;
			int nCodeIndex = 0;
			CICodeOperand * pOpPop = NULL;
			CICodeOperand * pOpPush = NULL;
//			char pszBuffer[MAX_IDENT_SIZE];

			// Yes, so loop through each I-code node to emit the code
			for ( int iCurrInstrIndex = 0; iCurrInstrIndex < iNodeCount; ++ iCurrInstrIndex )
			{
				// Get the I-code instruction structure at the current node
				pICode = GetICodeNodeByImpIndex ( pFunc->m_iIndex, iCurrInstrIndex );
				
				// Determine if the node type is ICODE_NODE_INSTR
				if ( pICode->m_iType == ICODE_NODE_INSTR) 
				{
					if (pICode->m_pInstruction->m_iOpCode == INSTRUCT_PUSH)
					{
						oListPush.AddNode(pICode);
					}
					else if (pICode->m_pInstruction->m_iOpCode == INSTRUCT_POP)
					{
						oListPop.AddNode(pICode);
					}
					else
					{
						//进行优化
						nPushIndex = oListPush.GetCount() - 1;
						nPopIndex = 0;
						nPopCount = oListPop.GetCount();

						for (nPopIndex=0; nPopIndex<nPopCount; nPopIndex++)
						{
							pPop = oListPop.GetAtIndex(nPopIndex);
							pPush = oListPush.GetAtIndex(nPushIndex);

							if (pPush != NULL)
							{
								pOpPop = pPop->m_pInstruction->GetAtIndex(0);
								pOpPush = pPush->m_pInstruction->GetAtIndex(0);

								switch (pOpPop->m_iType)
								{
								case OPERAND_TYPE_VAR:
									if (pOpPop->m_iSymbolIndex == pOpPush->m_iSymbolIndex 
										&& pOpPop->m_iType == pOpPush->m_iType)
									{//pop,push指令的操作数是同一个变量
//										EmitInstruct(pszBuffer, pPop);
//										pPop->ChangeToSourceLine(pszBuffer);
//										EmitInstruct(pszBuffer, pPush);
//										pPush->ChangeToSourceLine(pszBuffer);
										pPush->ChangeType(ICODE_NODE_NONE);//pPush->m_iType = ICODE_NODE_NONE;
										pPop->ChangeType(ICODE_NODE_NONE);//pPop->m_iType = ICODE_NODE_NONE;
									}
									else
									{//pop,push一对一对应
//										EmitInstruct(pszBuffer, pPush);
//										char *pTemp = pszBuffer + strlen(pszBuffer);
//										pTemp--;
//										EmitInstruct(pTemp, pPop);
										pPop->m_pInstruction->RemoveAll();
										pPush->m_pInstruction->RemoveAll();
										pPop->m_pInstruction->AddNode(pOpPop);
										pPop->m_pInstruction->AddNode(pOpPush);
//										pPush->ChangeToSourceLine(pszBuffer);
										pPop->m_pInstruction->m_iOpCode = INSTRUCT_MOV;
										pPush->ChangeType(ICODE_NODE_NONE);//pPush->m_iType = ICODE_NODE_NONE;
									}
									break;
								default:
									break;
								}
							}
							else
							{
								break;
							}
							nPushIndex--;
						}
						oListPush.RemoveAll();
						oListPop.RemoveAll();						
					}
				}//end of if ( pICode->m_iType == ICODE_NODE_INSTR) 
			}//end For ICode loop
		}// end of if ( iNodeCount > 0 )
	}//end of while
}


void CTScriptParser::OptimizeCode_Mov()
{
	CTLinkList<CICodeNode> oListMov;
	CFuncNode * pFunc = NULL;
	
	// Loop through each function and emit its declaration and code, if functions exist
	POS pos = m_oFuncTable.GetHeadPosition();
	
	while (pos != NULL)
	{
		pFunc = m_oFuncTable.GetNext(pos);
		
		if ( pFunc->m_iIsHostAPI )
		{
			continue;
		}

		//clear temp push, pop ICode list
		oListMov.RemoveAll();

		// Does the function have an I-code block?
		int iNodeCount = pFunc->GetCount();

		if ( iNodeCount > 0 )
		{
			CICodeNode *pCurr = NULL;
			CICodeNode * pICode = NULL;
			CICodeNode *pPrev = NULL;
			int nIndex = 0;
			int nCount = 0;
			CICodeOperand * pOpCurr1 = NULL;
			CICodeOperand * pOpCurr2 = NULL;
			CICodeOperand * pOpPrev1 = NULL;
			CICodeOperand * pOpPrev2 = NULL;

			// Yes, so loop through each I-code node to emit the code
			for ( int iCurrInstrIndex = 0; iCurrInstrIndex < iNodeCount; ++ iCurrInstrIndex )
			{
				// Get the I-code instruction structure at the current node
				pICode = GetICodeNodeByImpIndex ( pFunc->m_iIndex, iCurrInstrIndex );
				
				// Determine if the node type is ICODE_NODE_INSTR
				if ( pICode->m_iType == ICODE_NODE_INSTR ||  pICode->m_iType == ICODE_NODE_JUMP_TARGET ) 
				{
					bool bOptinize = FALSE;

					if (pICode->m_iType == ICODE_NODE_INSTR)
					{
						if (pICode->m_pInstruction->m_iOpCode == INSTRUCT_MOV)
						{
							oListMov.AddNode(pICode);
						}
						else
						{
							bOptinize = true;
						}
					}
					else
					{
						bOptinize = true;
					}
					
					if (bOptinize)
					{
						//进行优化
						if (oListMov.GetCount() >= 2)
						{
							nCount = oListMov.GetCount();
							pPrev = oListMov.GetAtIndex(0);

							for (nIndex=1; nIndex < nCount; nIndex++)
							{
								/*
								*           Mov		_T0, 0
								*           Mov		count, _T0
								*/
								pCurr = oListMov.GetAtIndex(nIndex);
								pOpPrev1 = pPrev->m_pInstruction->GetAtIndex(0);
								pOpCurr2 = pCurr->m_pInstruction->GetAtIndex(1);
								
								if (pOpPrev1->m_iSymbolIndex == pOpCurr2->m_iSymbolIndex 
									&& pOpPrev1->m_iType == pOpCurr2->m_iType)
								{
									pOpPrev2 = pPrev->m_pInstruction->GetAtIndex(1);
									pOpCurr1 = pCurr->m_pInstruction->GetAtIndex(0);

									*pOpCurr2 = *pOpPrev2;

									pOpPrev1 =  pCurr->m_pInstruction->GetAtIndex(1);
									pPrev->ChangeType(ICODE_NODE_NONE);//pPrev->m_iType = ICODE_NODE_NONE;
								}

								pPrev = pCurr;
							}		
						}

						oListMov.RemoveAll();
					}//end of else
				}//end of if ( pICode->m_iType == ICODE_NODE_INSTR) 
			}//end For ICode loop
		}// end of if ( iNodeCount > 0 )
	}//end of while

	oListMov.RemoveAll();
}


void CTScriptParser::OptimizeCode_Mov_Instr()
{
	CTLinkList<CICodeNode> oListMov;
	CFuncNode * pFunc = NULL;
	
	// Loop through each function and emit its declaration and code, if functions exist
	POS pos = m_oFuncTable.GetHeadPosition();
	
	while (pos != NULL)
	{
		pFunc = m_oFuncTable.GetNext(pos);
		
		if ( pFunc->m_iIsHostAPI )
		{
			continue;
		}

		//clear temp push, pop ICode list
		oListMov.RemoveAll();

		// Does the function have an I-code block?
		int iNodeCount = pFunc->GetCount();

		if ( iNodeCount == 0 )
		{
			continue;
		}

		CICodeNode *pMov = NULL;
		CICodeNode * pICode = NULL;
		int nIndex = 0;
		int nCount = 0;
		CICodeOperand * pOpMov1 = NULL;
		CICodeOperand * pOpMov2 = NULL;
		CICodeOperand * pOpICode1 = NULL;
		CICodeOperand * pOpICode2 = NULL;
		CICodeOperand * pOpICode3 = NULL;

		// Yes, so loop through each I-code node to emit the code
		for ( int iCurrInstrIndex = 0; iCurrInstrIndex < iNodeCount; ++ iCurrInstrIndex )
		{
			// Get the I-code instruction structure at the current node
			pICode = GetICodeNodeByImpIndex ( pFunc->m_iIndex, iCurrInstrIndex );

			// Determine if the node type is ICODE_NODE_INSTR
			if ( pICode->m_iType == ICODE_NODE_INSTR ||  pICode->m_iType == ICODE_NODE_JUMP_TARGET ) 
			{
				bool bOptinize = FALSE;

				if (pICode->m_iType == ICODE_NODE_INSTR)
				{
					if (pICode->m_pInstruction->m_iOpCode == INSTRUCT_MOV)
					{
						oListMov.AddNode(pICode);
					}
					else
					{
						bOptinize = true;
					}
				}
				else
				{
					oListMov.RemoveAll();
				}

				//进行优化
				if (bOptinize)
				{
					nCount = oListMov.GetCount() - 1;

					if (nCount >= 0 && pICode->m_pInstruction->GetCount() >= 2)
					{
						pMov = oListMov.GetAtIndex(nCount);
						pOpMov1 = pMov->m_pInstruction->GetAtIndex(0); 
						pOpMov2 = pMov->m_pInstruction->GetAtIndex(1);
						pOpICode1 = pICode->m_pInstruction->GetAtIndex(0);
						pOpICode2 = pICode->m_pInstruction->GetAtIndex(1);
						pOpICode3 = pICode->m_pInstruction->GetAtIndex(2);

						CString strMove, strICode;
						EmitInstruct_Buffer(strMove, pMov);
						EmitInstruct_Buffer(strICode, pICode);

						if (pOpICode3 == NULL)
						{
							if ( (pOpMov1->m_iSymbolIndex == pOpICode2->m_iSymbolIndex 
								&& pOpMov1->m_iType == pOpICode2->m_iType) )
							{
								*pOpICode2 = *pOpMov2;
								pMov->ChangeType(ICODE_NODE_NONE);//pMov->m_iType = ICODE_NODE_NONE;
							}
						}
						else
						{
							if ( (pOpMov1->m_iSymbolIndex == pOpICode2->m_iSymbolIndex 
								&& pOpMov1->m_iType == pOpICode2->m_iType) 
								|| (pOpMov1->m_iSymbolIndex == pOpICode3->m_iSymbolIndex 
								&& pOpMov1->m_iType == pOpICode3->m_iType) )
							{
								if ( (pOpMov1->m_iSymbolIndex == pOpICode2->m_iSymbolIndex 
									&& pOpMov1->m_iType == pOpICode2->m_iType) )
								{
									*pOpICode2 = *pOpMov2;
								}

								if ( (pOpMov1->m_iSymbolIndex == pOpICode3->m_iSymbolIndex 
									&& pOpMov1->m_iType == pOpICode3->m_iType) )
								{
									*pOpICode3 = *pOpMov2;
								}

								pMov->ChangeType(ICODE_NODE_NONE);//pMov->m_iType = ICODE_NODE_NONE;
							}
						}
					}

					oListMov.RemoveAll();
				}//end of else
			}//end of if ( pICode->m_iType == ICODE_NODE_INSTR) 
		}//end For ICode loop
	}//end of while


	oListMov.RemoveAll();
}

