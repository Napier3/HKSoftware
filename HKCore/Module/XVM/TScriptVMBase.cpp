// TScriptVMBase.cpp: implementation of the CTScriptVMBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TScriptVMBase.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define _use_malloc_

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTScriptVMBase::CTScriptVMBase()
{
	Init();
	ZeroMemory(m_chReturn, XVM_RETURN_BUFFER_LEN*XVM_RETURN_BUFFER_COUNT);
	m_nChReturnIndex = 0;
	m_pRefData = NULL;
}

CTScriptVMBase::~CTScriptVMBase()
{
	
}

void CTScriptVMBase::Init()
{
	// ---- Initialize the host API
	for ( int iCurrHostAPIFunc = 0; iCurrHostAPIFunc < MAX_HOST_API_SIZE; ++ iCurrHostAPIFunc )
	{
		g_HostAPI [ iCurrHostAPIFunc ].iIsActive = FALSE;
		g_HostAPI [ iCurrHostAPIFunc ].iThreadIndex = 0;
		g_HostAPI [ iCurrHostAPIFunc ].pstrName = NULL;
	}	
}

void CTScriptVMBase::FreeBase()
{
	// ---- Free the host API's function name strings
	for ( int iCurrHostAPIFunc = 0; iCurrHostAPIFunc < MAX_HOST_API_SIZE; ++ iCurrHostAPIFunc )
	{
		if ( g_HostAPI [ iCurrHostAPIFunc ].pstrName )
		{
			free ( g_HostAPI [ iCurrHostAPIFunc ].pstrName );
		}
	}
	
}

void CTScriptVMBase::InitScript(Script *pScript)
{
	pScript->iIsActive = FALSE;
	pScript->iIsRunning = FALSE;
	pScript->iIsMainFuncPresent = FALSE;
	pScript->iIsPaused = FALSE;
	pScript->iGlobalDataSize = 0;
	pScript->iMainFuncIndex = 0;
	pScript->uiPauseEndTime = 0;
	pScript->uiTimesliceDuration = 0;
	
	pScript->_RetVal.iType = -1;
	pScript->_RetVal.fFloatLiteral = 0;
	pScript->_RetVal.iStackIndex = 0;
	
	pScript->m_oInstrStream.m_pInstrs = NULL;
	pScript->m_oInstrStream.iSize = 0;
	pScript->m_oInstrStream.iCurrInstr = 0;
	
	pScript->Stack.pElmnts = NULL;
	pScript->Stack.iFrameIndex = 0;
	pScript->Stack.iSize = 0;
	pScript->Stack.iTopIndex = 0;
	
	pScript->m_oFuncTable.m_pFuncs = NULL;
	pScript->m_oFuncTable.iSize = 0;
	
	pScript->m_oHostAPICallTable.m_ppstrCalls = NULL;
	pScript->m_oHostAPICallTable.iSize = 0;

	pScript->m_oExportSymbols.iSize = 0;
	pScript->m_oExportSymbols.m_pExportSymbols = NULL;
}

int CTScriptVMBase::LoadScript ( char *pstrFilename, Script *pScript, int iThreadTimeslice )
{
	CString strFile;
	strFile = pstrFilename;
	CWSerializeBuff oBuffer;
	if (!oBuffer.ReadFromFile(strFile))
	{
		return TS_LOAD_ERROR_FILE_IO;
	}

	return LoadScriptFromBuffer(oBuffer, pScript, iThreadTimeslice);
}

int  CTScriptVMBase::LoadScriptFromBuffer ( char *pBuffer, long nBufferLen, Script *pScript, int iThreadTimeslice )
{
	CWSerializeBuff oBuffer;
	oBuffer.AttachBuffer(pBuffer, nBufferLen);
	return LoadScriptFromBuffer(oBuffer, pScript, iThreadTimeslice);
}

int CTScriptVMBase::Load_ScriptFileHead(CWSerializeBuff  &oWBuffer)
{
	// ---- Read the header
	char  pstrIDString[5];
	// Read the string (4 bytes) and append a null terminator
	oWBuffer.Char(&pstrIDString[0]) ;//( pstrIDString, 4, 1, pScriptFile );
	oWBuffer.Char(&pstrIDString[1]);
	oWBuffer.Char(&pstrIDString[2]);
	oWBuffer.Char(&pstrIDString[3]);
	pstrIDString [ strlen ( TSE_ID_STRING ) ] = '\0';

	// Compare the data read from the file to the ID string and exit on an error if they don't
	// match
	if ( strcmp ( pstrIDString, TSE_ID_STRING ) != 0 )
	{
		return TS_LOAD_ERROR_INVALID_XSE;
	}

	// Read the script version (2 bytes total)
	int iMajorVersion = oWBuffer.ReadChar();//fread ( & iMajorVersion, 1, 1, pScriptFile );
	int iMinorVersion = oWBuffer.ReadChar();//fread ( & iMinorVersion, 1, 1, pScriptFile );

	// Validate the version, since this prototype only supports version 0.8 scripts
	if ( iMajorVersion != 1 || iMinorVersion != 0 )
	{
		return TS_LOAD_ERROR_UNSUPPORTED_VERS;
	}

	return TS_LOAD_OK;
}


int CTScriptVMBase::Load_ScriptHeader(CWSerializeBuff  &oWBuffer, Script *pScript)
{
	// Read the stack size (4 bytes)
	oWBuffer.Int(&pScript->Stack.iSize);//fread ( &pScript->Stack.iSize, sizeof(int), 1, pScriptFile );
	
	// Read the global data size (4 bytes)
	oWBuffer.Int( &pScript->iGlobalDataSize);//fread ( &pScript->iGlobalDataSize, sizeof(int), 1, pScriptFile );

	// Check for presence of _Main () (1 byte)
	pScript->iIsMainFuncPresent = oWBuffer.ReadChar();//fread ( &pScript->iIsMainFuncPresent, sizeof(char), 1, pScriptFile );

	// Read _Main ()'s function index (4 bytes)
	oWBuffer.Int(& pScript->iMainFuncIndex);//fread ( & pScript->iMainFuncIndex, sizeof(int), 1, pScriptFile );

	// Read the priority type (1 byte)
	int iPriorityType = oWBuffer.ReadByte();//fread ( & iPriorityType, sizeof(unsigned char), 1, pScriptFile );

	// Read the user-defined priority (4 bytes)
	pScript->uiTimesliceDuration = oWBuffer.ReadInt();//fread ( & pScript->uiTimesliceDuration, sizeof(unsigned int), 1, pScriptFile );

	// Check for a default stack size request
	if ( pScript->Stack.iSize == 0 )
	{
		pScript->Stack.iSize = DEF_STACK_SIZE;
	}

	// Allocate the runtime stack
	int iBufferLen = pScript->Stack.iSize * sizeof ( Value );

#ifdef _use_malloc_
	pScript->Stack.pElmnts = (Value *) malloc ( iBufferLen );
#else
	pScript->Stack.pElmnts = (Value *) new BYTE[ iBufferLen];
#endif

	if ( pScript->Stack.pElmnts == NULL )
	{
		return TS_LOAD_ERROR_OUT_OF_MEMORY;
	}

	//初始化堆栈
	memset(pScript->Stack.pElmnts, 0, iBufferLen);


	// Override the script-specified priority if necessary
// 	if ( iThreadTimeslice != TS_THREAD_PRIORITY_USER )
// 	{
// 		iPriorityType = TS_THREAD_PRIORITY_USER;
// 	}

	// If the priority type is not set to user-defined, fill in the appropriate timeslice
	// duration
	switch ( iPriorityType )
	{
	case TS_THREAD_PRIORITY_LOW:
		pScript->uiTimesliceDuration = THREAD_PRIORITY_DUR_LOW;
		break;

	case TS_THREAD_PRIORITY_MED:
		pScript->uiTimesliceDuration = THREAD_PRIORITY_DUR_MED;
		break;

	case TS_THREAD_PRIORITY_HIGH:
		pScript->uiTimesliceDuration = THREAD_PRIORITY_DUR_HIGH;
		break;
	}

	return TS_LOAD_OK;
}

// ---- Read the instruction stream  
int CTScriptVMBase::Load_Instructions(CWSerializeBuff  &oWBuffer, Script *pScript)
{
	InstrStream *pInstrStream = &pScript->m_oInstrStream;
	// Read the instruction count (4 bytes)
	oWBuffer.Int(&pInstrStream->iSize);//fread ( &pInstrStream->iSize, sizeof(int), 1, pScriptFile );

	// Allocate the stream
	int iBufferLen = pInstrStream->iSize * sizeof ( Instr );

#ifdef _use_malloc_
	pInstrStream->m_pInstrs = ( Instr * ) malloc ( iBufferLen );
#else
	pInstrStream->m_pInstrs = ( Instr * ) new BYTE[iBufferLen ];
#endif

	memset(pInstrStream->m_pInstrs, 0, iBufferLen);
	int iCurrInstrIndex = 0;

	if ( pInstrStream->m_pInstrs == NULL )
	{
		return TS_LOAD_ERROR_OUT_OF_MEMORY;
	}

	// Read the instruction data

	for ( iCurrInstrIndex = 0; iCurrInstrIndex < pInstrStream->iSize;  )
	{
		Instr *pInstr = &pInstrStream->m_pInstrs[iCurrInstrIndex];

		// Read the opcode (2 bytes)
		pInstr->iOpcode = oWBuffer.ReadShort();//fread ( &pInstr->iOpcode, sizeof(unsigned short), 1, pScriptFile );

		// Read the operand count (1 byte)
		pInstr->iOpCount = oWBuffer.ReadByte();//fread ( & pInstr->iOpCount, sizeof(unsigned char), 1, pScriptFile );
		int iOpCount = pInstr->iOpCount;

		// Allocate space for the operand list in a temporary pointer
		iBufferLen = pInstr->iOpCount * sizeof ( Value );
		if (iBufferLen > 0)
		{
#ifdef _use_malloc_
			pInstr->pOpList = ( Value * ) malloc ( iBufferLen );
#else
			pInstr->pOpList = ( Value * ) new BYTE[ iBufferLen ];
#endif

			if ( pInstr->pOpList == NULL )
			{
				return TS_LOAD_ERROR_OUT_OF_MEMORY;
			}

			memset(pInstr->pOpList, 0, iBufferLen);
		}
		else
		{
			pInstr->pOpList = NULL;
		}

		// Read in the operand list (N bytes)
		for ( int iCurrOpIndex = 0; iCurrOpIndex < iOpCount; ++iCurrOpIndex )
		{
			Value &oValue = pInstr->pOpList[iCurrOpIndex];

			// Read in the operand type (1 byte)
			oValue.iType = oWBuffer.ReadByte();//fread ( & oValue.iType, sizeof(unsigned char), 1, pScriptFile );

			// Depending on the type, read in the operand data
			switch ( oValue.iType )
			{
				// Integer literal
			case OPERAND_TYPE_INT:
				oWBuffer.Int(&oValue.iIntLiteral);//fread ( & oValue.iIntLiteral, sizeof ( int ), 1, pScriptFile );
				break;

				// Floating-point literal
			case OPERAND_TYPE_FLOAT:
				oWBuffer.Float(& oValue.fFloatLiteral);//fread ( & oValue.fFloatLiteral, sizeof ( float ), 1, pScriptFile );
				break;

				// String/String index
			case OPERAND_TYPE_STRING:
				// Since there's no field in the Value structure for string table
				// indices, read the index into the integer literal field and set
				// its type to string index
				oWBuffer.Int(&oValue.iIntLiteral);//fread ( & oValue.iIntLiteral, sizeof ( int ), 1, pScriptFile );
				oValue.iType = OPERAND_TYPE_STRING;//多余的代码
				break;

				// Instruction index
			case OPERAND_TYPE_INSTRUCT_INDEX:
				oWBuffer.Int(&oValue.iInstrIndex);//fread ( & oValue.iInstrIndex, sizeof ( int ), 1, pScriptFile );
				break;

				// Absolute stack index
			case OPERAND_TYPE_ABS_STACK_INDEX:
				oWBuffer.Int(&oValue.iStackIndex);//fread ( & oValue.iStackIndex, sizeof ( int ), 1, pScriptFile );
				break;

				// Relative stack index
			case OPERAND_TYPE_REL_STACK_INDEX:
				oWBuffer.Int(&oValue.iStackIndex);//fread ( & oValue.iStackIndex, sizeof ( int ), 1, pScriptFile );
				oWBuffer.Int(&oValue.iOffsetIndex);//fread ( & oValue.iOffsetIndex, sizeof ( int ), 1, pScriptFile );
				break;

				// Function index
			case OPERAND_TYPE_FUNC_INDEX:
				oWBuffer.Int(&oValue.iFuncIndex);//fread ( & oValue.iFuncIndex, sizeof ( int ), 1, pScriptFile );
				break;

				// Host API call index
			case OPERAND_TYPE_HOST_API_CALL_INDEX:
				oWBuffer.Int(&oValue.iHostAPICallIndex);//fread ( & oValue.iHostAPICallIndex, sizeof ( int ), 1, pScriptFile );
				break;

				// Register
			case OPERAND_TYPE_REG:
				oWBuffer.Int(&oValue.iReg);//fread ( & oValue.iReg, sizeof ( int ), 1, pScriptFile );
				break;

			default:
				return TS_LOAD_ERROR_FILE_DATA_INVALID;
				break;
			}
		}

		++ iCurrInstrIndex;
	}


	return TS_LOAD_OK;
}

int CTScriptVMBase::Load_StringTable(CWSerializeBuff  &oWBuffer, Script *pScript)
{
	// Read the table size (4 bytes)
	int iStringTableSize = oWBuffer.ReadInt();//fread ( &iStringTableSize, sizeof(unsigned short), 1, pScriptFile );

	// If the string table exists, read it
	if ( iStringTableSize <= 0 )
	{
		return TS_LOAD_OK;
	}
	
	// Allocate a string table of this size
#ifdef _use_malloc_
	char** ppstrStringTable = ( char** ) malloc ( iStringTableSize * sizeof ( char*) );
#else
	char** ppstrStringTable = ( char** ) new BYTE[( iStringTableSize * sizeof ( char*) )];
#endif

	if ( ppstrStringTable == NULL )
	{
		return TS_LOAD_ERROR_OUT_OF_MEMORY;
	}

	memset(ppstrStringTable, 0, iStringTableSize * sizeof ( char*));

	// Read in each string
	int iStringIndex = 0;
	char *pstrCurrString = NULL;
	char *pstrStringCopy = NULL;;
	int iStringSize = 0;
	int iCurrInstrIndex = 0;
	int iOpCount = 0;
	int iCurrOpIndex = 0;

	for ( iStringIndex = 0; iStringIndex < iStringTableSize; ++ iStringIndex )
	{
		// Read in the string size (4 bytes)
		iStringSize = oWBuffer.ReadInt();//fread ( & iStringSize, sizeof(unsigned int), 1, pScriptFile );

		// Allocate space for the string plus a null terminator
#ifdef _use_malloc_
		pstrCurrString = ( char * ) malloc ( iStringSize + 1 );
#else
		pstrCurrString = ( char * ) new BYTE[( iStringSize + 1 )] ;
#endif

		if ( pstrCurrString == NULL )
		{
			return TS_LOAD_ERROR_OUT_OF_MEMORY;
		}

		// Read in the string data (N bytes) and append the null terminator
		oWBuffer.String(pstrCurrString, iStringSize);//fread ( pstrCurrString, iStringSize, 1, pScriptFile );
		pstrCurrString [ iStringSize ] = '\0';

		// Assign the string pointer to the string table
		ppstrStringTable [ iStringIndex ] = pstrCurrString;
	}

	// Run through each operand in the instruction stream and assign copies of string
	// operand's corresponding string literals
	for ( iCurrInstrIndex = 0; iCurrInstrIndex < pScript->m_oInstrStream.iSize; ++ iCurrInstrIndex )
	{
		Instr *pInstr = &pScript->m_oInstrStream.m_pInstrs[iCurrInstrIndex];

		// Get the instruction's operand count and a copy of it's operand list
		iOpCount = pInstr->iOpCount;			

		// Loop through each operand
		for ( iCurrOpIndex = 0; iCurrOpIndex < iOpCount; ++ iCurrOpIndex )
		{
			Value &oValue = pInstr->pOpList[iCurrOpIndex];

			// If the operand is a string index, make a local copy of it's corresponding
			// string in the table
			if ( oValue.iType == OPERAND_TYPE_STRING )
			{
				// Get the string index from the operand's integer literal field
				iStringIndex = oValue.iIntLiteral;
#ifdef _use_malloc_
				pstrStringCopy = ( char * ) malloc ( strlen ( ppstrStringTable [ iStringIndex ] ) + 1 );
#else
				pstrStringCopy = ( char * ) new BYTE[ ( strlen ( ppstrStringTable [ iStringIndex ] ) + 1 ) ];
#endif

				// Allocate a new string to hold a copy of the one in the table
				if ( pstrStringCopy == NULL )
				{
					return TS_LOAD_ERROR_OUT_OF_MEMORY;
				}

				// Make a copy of the string
				strcpy ( pstrStringCopy, ppstrStringTable [ iStringIndex ] );

				// Save the string pointer in the operand list
				pInstr->pOpList [ iCurrOpIndex ].pstrStringLiteral = pstrStringCopy;
			}
		}
	}

	// ---- Free the original strings
	for ( iStringIndex = 0; iStringIndex < iStringTableSize; ++ iStringIndex )
	{
		if (ppstrStringTable [ iStringIndex ] != NULL)
		{
			free ( ppstrStringTable [ iStringIndex ] );
		}
	}

	// ---- Free the string table itself
	if (ppstrStringTable != NULL)
	{
		free ( ppstrStringTable );
	}

	return TS_LOAD_OK;
}

int CTScriptVMBase::Load_FuncTable(CWSerializeBuff  &oWBuffer, Script *pScript)
{
	// Read the function count (4 bytes)
	int iFuncTableSize = oWBuffer.ReadInt();//fread ( & iFuncTableSize, sizeof(unsigned int), 1, pScriptFile );
	pScript->m_oFuncTable.iSize = iFuncTableSize;


	// Allocate the table
	if (iFuncTableSize > 0)
	{
#ifdef _use_malloc_
		pScript->m_oFuncTable.m_pFuncs = ( Func * ) malloc ( iFuncTableSize * sizeof ( Func ) );
#else
		pScript->m_oFuncTable.m_pFuncs = ( Func * ) new BYTE[ ( iFuncTableSize * sizeof ( Func ) )];
#endif
	}
	else
	{
		pScript->m_oFuncTable.m_pFuncs = NULL;
	}

	if ( pScript->m_oFuncTable.m_pFuncs == NULL )
	{
		return TS_LOAD_ERROR_OUT_OF_MEMORY;
	}

	// Read each function
	int iCurrFuncIndex = 0;
	int iEntryPoint = 0;
	unsigned char ucParamCount = 0;
	int iLocalDataSize = 0;
	int iStackFrameSize = 0;
	int iFuncNameLength  =0;

	for ( iCurrFuncIndex = 0; iCurrFuncIndex < iFuncTableSize; ++ iCurrFuncIndex )
	{
		// Read the entry point (4 bytes)
		oWBuffer.Int(&iEntryPoint);//fread ( & iEntryPoint, sizeof(int), 1, pScriptFile );

		// Read the parameter count (1 byte)
		ucParamCount = oWBuffer.ReadByte();//fread ( & ucParamCount, sizeof(unsigned char), 1, pScriptFile );

		// Read the local data size (4 bytes)
		oWBuffer.Int(&iLocalDataSize);//fread ( & iLocalDataSize, sizeof(int), 1, pScriptFile );

		// Calculate the stack size
		iStackFrameSize = ucParamCount + 1 + iLocalDataSize;

		// Read the function name length (1 byte)
		oWBuffer.Int(&iFuncNameLength);//fread ( & iFuncNameLength, sizeof(unsigned char), 1, pScriptFile );

		// Read the function name (N bytes) and append a null-terminator
		//fread ( & pScript->m_oFuncTable.m_pFuncs[iCurrFuncIndex].pstrName, iFuncNameLength, 1, pScriptFile );
		oWBuffer.String(pScript->m_oFuncTable.m_pFuncs[iCurrFuncIndex].pstrName, iFuncNameLength);
		pScript->m_oFuncTable.m_pFuncs[iCurrFuncIndex].pstrName [ iFuncNameLength ] = '\0';

		// Write everything to the function table
		pScript->m_oFuncTable.m_pFuncs[iCurrFuncIndex].iEntryPoint = iEntryPoint;
		pScript->m_oFuncTable.m_pFuncs[iCurrFuncIndex].m_ucParamCount = ucParamCount;
		pScript->m_oFuncTable.m_pFuncs[iCurrFuncIndex].iLocalDataSize = iLocalDataSize;
		pScript->m_oFuncTable.m_pFuncs[iCurrFuncIndex].iStackFrameSize = iStackFrameSize;
	}

	return TS_LOAD_OK;
}

int CTScriptVMBase::Load_HostAPICallTable(CWSerializeBuff  &oWBuffer, Script *pScript)
{

	// Read the host API call count
	int iHostAPICallTables = oWBuffer.ReadInt();//fread ( & iHostAPICallTables, sizeof(unsigned short), 1, pScriptFile );
	pScript->m_oHostAPICallTable.iSize = iHostAPICallTables;

	// Allocate the table
#ifdef _use_malloc_
	char **ppstrCalls = ( char ** ) malloc ( iHostAPICallTables * sizeof ( char * ) ) ;
#else
	char **ppstrCalls = ( char ** ) new BYTE[( iHostAPICallTables * sizeof ( char * ) ) ] ;
#endif

	if ( ppstrCalls == NULL )
	{
		return TS_LOAD_ERROR_OUT_OF_MEMORY;
	}

	pScript->m_oHostAPICallTable.m_ppstrCalls = ppstrCalls;

	// Read each host API call
	for ( int iCurrCallIndex = 0; iCurrCallIndex < iHostAPICallTables; ++ iCurrCallIndex )
	{
		// Read the host API call string size (1 byte)
		int iCallLength = oWBuffer.ReadInt();//fread ( & iCallLength, sizeof(unsigned int), 1, pScriptFile );

		// Allocate space for the string plus the null terminator in a temporary pointer
#ifdef _use_malloc_
		char *pstrCurrCall = ( char * ) malloc ( iCallLength + 1 );
#else
		char *pstrCurrCall = ( char * ) new BYTE[( iCallLength + 1) ] ;
#endif

		if ( pstrCurrCall == NULL )
		{
			return TS_LOAD_ERROR_OUT_OF_MEMORY;
		}

		// Read the host API call string data and append the null terminator
		//fread ( pstrCurrCall, iCallLength, 1, pScriptFile );
		oWBuffer.String(pstrCurrCall, iCallLength);
		pstrCurrCall [ iCallLength ] = '\0';

		// Assign the temporary pointer to the table
		ppstrCalls [ iCurrCallIndex ] = pstrCurrCall;
	}

	return TS_LOAD_OK;
}

int CTScriptVMBase::Load_ExportSymbols(CWSerializeBuff  &oWBuffer, Script *pScript)
{
	// Read the export symbol count
	int iExportSymbols = oWBuffer.ReadInt();//fread ( & iExportSymbols, sizeof(unsigned short), 1, pScriptFile );
	pScript->m_oExportSymbols.iSize = iExportSymbols;

	// Allocate the table
	ExportSymbol* pExportSymbols = NULL;

	if (iExportSymbols <= 0)
	{
		pScript->m_oExportSymbols.m_pExportSymbols = NULL;
		return TS_LOAD_OK;
	}

#ifdef _use_malloc_
	pExportSymbols = ( ExportSymbol* ) malloc ( iExportSymbols * sizeof ( ExportSymbol ) ) ;
#else
	pExportSymbols = ( ExportSymbol* ) new BYTE[ ( iExportSymbols * sizeof ( ExportSymbol ) )] ;
#endif

	if ( pExportSymbols == NULL )
	{
		return TS_LOAD_ERROR_OUT_OF_MEMORY;
	}

	pScript->m_oExportSymbols.m_pExportSymbols = pExportSymbols;

	// Read each export symbols call
	for ( int iExportSymbolIndex = 0; iExportSymbolIndex < iExportSymbols; ++ iExportSymbolIndex )
	{
		ExportSymbol &oSymbol = pExportSymbols[iExportSymbolIndex];

		// Read the stack index
		oWBuffer.Int(& oSymbol.iStackIndex);//fread ( & oSymbol.iStackIndex, sizeof(int), 1, pScriptFile );

		// Read the Symbol name length
		int iCallLength = oWBuffer.ReadInt();//fread ( & iCallLength, sizeof(unsigned short), 1, pScriptFile );

		// Allocate space for the string plus the null terminator in a temporary pointer
#ifdef _use_malloc_
		oSymbol.pstrName = ( char * ) malloc ( iCallLength + 1 );
#else
		oSymbol.pstrName = ( char * ) new BYTE[ ( iCallLength + 1 )];
#endif

		if ( oSymbol.pstrName == NULL )
		{
			return TS_LOAD_ERROR_OUT_OF_MEMORY;
		}

		// Read the host API call string data and append the null terminator
		//fread ( oSymbol.pstrName, iCallLength, 1, pScriptFile );
		oWBuffer.String(oSymbol.pstrName, iCallLength);
		oSymbol.pstrName [ iCallLength ] = '\0';
	}

	return TS_LOAD_OK;
}



int  CTScriptVMBase::LoadScriptFromBuffer ( CWSerializeBuff  &oWBuffer, Script *pScript, int iThreadTimeslice )
{
	int iLoadScriptState = TS_LOAD_OK;

	oWBuffer.ResetBufferPointer();
	
	//File Head
	iLoadScriptState = Load_ScriptFileHead(oWBuffer);

	if (TS_LOAD_OK != iLoadScriptState)
	{
		return iLoadScriptState;
	}

	//Read Script Header
	iLoadScriptState = Load_ScriptHeader(oWBuffer, pScript);

	if (TS_LOAD_OK != iLoadScriptState)
	{
		return iLoadScriptState;
	}

	// ---- Read the instruction stream
	iLoadScriptState = Load_Instructions(oWBuffer, pScript);

	if (TS_LOAD_OK != iLoadScriptState)
	{
		return iLoadScriptState;
	}

	int iCurrInstrIndex = oWBuffer.Tell();//ftell(pScriptFile);

	// ---- Read the string table
	iLoadScriptState = Load_StringTable(oWBuffer, pScript);

	if (TS_LOAD_OK != iLoadScriptState)
	{
		return iLoadScriptState;
	}

	// ---- Read the function table
	iLoadScriptState = Load_FuncTable(oWBuffer, pScript);

	if (TS_LOAD_OK != iLoadScriptState)
	{
		return iLoadScriptState;
	}
	
	// ---- Read the host API call table
	iLoadScriptState = Load_HostAPICallTable(oWBuffer, pScript);

	if (TS_LOAD_OK != iLoadScriptState)
	{
		return iLoadScriptState;
	}

	// Read export symbols
	iLoadScriptState = Load_ExportSymbols(oWBuffer, pScript);

	if (TS_LOAD_OK != iLoadScriptState)
	{
		return iLoadScriptState;
	}

	// The script is fully loaded and ready to go, so set the active flag
	pScript->iIsActive = TRUE;

	// Reset the script
	ResetScript ( pScript );

	return TS_LOAD_OK;
}

void CTScriptVMBase::UnloadScript ( Script *pScript )
{
	if ( ! pScript->iIsActive )
	{
		return;
	}
	
	// ---- Free The instruction stream
	int iCount = pScript->m_oInstrStream.iSize;
	Instr *pInstrs = pScript->m_oInstrStream.m_pInstrs;
	Instr *pInstr = NULL;
	Value *pValue = NULL;
	Value *pValues = NULL;

	// First check to see if any instructions have string operands, and free them if they do
	for ( int iCurrInstrIndex = 0; iCurrInstrIndex < iCount; ++ iCurrInstrIndex )
	{
		// Make a local copy of the operand count and operand list
		//int iOpCount = pScript->m_oInstrStream.m_pInstrs[ iCurrInstrIndex ].iOpCount;
		pInstr = &(pInstrs[ iCurrInstrIndex ]);
		int iOpCount = pInstr->iOpCount;
		
		// Loop through each operand and free its string pointer		
		for ( int iCurrOpIndex = 0; iCurrOpIndex < iOpCount; ++ iCurrOpIndex )
		{
			//pValue = & (pInstr->pOpList [ iCurrOpIndex ]);
			FreeValue(pInstr->pOpList [ iCurrOpIndex ]);
		}
#ifdef _use_malloc_
		free (pInstr->pOpList);
#else
		delete (pInstr->pOpList);
#endif
	}
	
	// Now free the stream itself
	
	if ( pInstrs != NULL)
	{
#ifdef _use_malloc_
		free ( pInstrs );
#else
		delete ( pInstrs );
#endif
	}
	
	// ---- Free the runtime stack
	
	// Free any strings that are still on the stack
	iCount = pScript->Stack.iSize;
	pValues = pScript->Stack.pElmnts;

	for ( int iCurrElmtnIndex = 0; iCurrElmtnIndex < iCount; ++ iCurrElmtnIndex )
	{
		pValue = &(pValues[iCurrElmtnIndex]); 
	
		if ( pValue->iType == OPERAND_TYPE_STRING )
		{
#ifdef _use_malloc_
			free ( pValue->pstrStringLiteral );
#else
			delete ( pValue->pstrStringLiteral );
#endif
		}
	}
	
	// Now free the stack itself
	if ( pValues != NULL)
	{
#ifdef _use_malloc_
		free ( pValues );
#else
		delete ( pValues );
#endif
	}

	// ---- Free the function table
	if ( pScript->m_oFuncTable.m_pFuncs )
	{
#ifdef _use_malloc_
		free ( pScript->m_oFuncTable.m_pFuncs );
#else
		delete ( pScript->m_oFuncTable.m_pFuncs );
#endif
	}
	
	// --- Free the host API call table
	
	// First free each string in the table individually
	char **ppstrCalls = pScript->m_oHostAPICallTable.m_ppstrCalls;
	iCount = pScript->m_oHostAPICallTable.iSize;
	
	for ( int iCurrCallIndex = 0; iCurrCallIndex < iCount; ++ iCurrCallIndex )
	{
		if ( ppstrCalls [ iCurrCallIndex ] != NULL )
		{
#ifdef _use_malloc_
			free ( ppstrCalls [ iCurrCallIndex ] );
#else
			delete ( ppstrCalls [ iCurrCallIndex ] );
#endif
		}
	}

	// Now free the table itself
	if ( ppstrCalls )
	{
#ifdef _use_malloc_
		free ( ppstrCalls );
#else
		delete ( ppstrCalls );
#endif
	}

	 pScript->m_oHostAPICallTable.m_ppstrCalls = NULL;
	 pScript->m_oHostAPICallTable.iSize = 0;
		
	//free export symbols
	ExportSymbols &oSymbols = pScript->m_oExportSymbols;
	ExportSymbol *pSymbol = NULL;
	iCount = oSymbols.iSize;

	for (int iIndex = 0; iIndex < iCount; iIndex++)
	{
		pSymbol = &(oSymbols.m_pExportSymbols[iIndex]);
#ifdef _use_malloc_
		free(pSymbol->pstrName);
#else
		delete (pSymbol->pstrName);
#endif
	}

	//free symbols
	if (oSymbols.m_pExportSymbols != NULL)
	{
#ifdef _use_malloc_
		free(oSymbols.m_pExportSymbols);
#else
		delete (oSymbols.m_pExportSymbols);
#endif
	}

	FreeValue(pScript->_RetVal);
}

void CTScriptVMBase::ResetScript ( Script *pScript )
{
	// Get _Main ()'s function index in case we need it
	int iMainFuncIndex = pScript->iMainFuncIndex;
	
	// If the function table is present, set the entry point
	if ( pScript->m_oFuncTable.m_pFuncs != NULL )
	{
		// If _Main () is present, read _Main ()'s index of the function table to get its
		// entry point
		if ( pScript->iIsMainFuncPresent )
		{
			pScript->m_oInstrStream.iCurrInstr = pScript->m_oFuncTable.m_pFuncs[ iMainFuncIndex ].iEntryPoint;
		}
	}
	
	// Clear the stack
	
	pScript->Stack.iTopIndex = 0;
	pScript->Stack.iFrameIndex = 0;
	Value *pValues = pScript->Stack.pElmnts;
	long  iStack_Size = pScript->Stack.iSize;

	// Set the entire stack to null
	for ( int iCurrElmntIndex = 0; iCurrElmntIndex < iStack_Size; ++ iCurrElmntIndex )
	{
		FreeValue(pValues[iCurrElmntIndex], OPERAND_TYPE_NULL);
		//pScript->Stack.pElmnts[ iCurrElmntIndex ].iType = OPERAND_TYPE_NULL;
	}
	
	// Unpause the script
	pScript->iIsPaused = FALSE;
	pScript->m_iScriptState = SCRIPT_STATE_NORMAL;
	
	// Allocate space for the globals
	PushFrame ( pScript, pScript->iGlobalDataSize );
	
	// If _Main () is present, push its stack frame (plus one extra stack element to
	// compensate for the function index that usually sits on top of stack frames and
	// causes indices to start from -2)
	PushFrame ( pScript, pScript->m_oFuncTable.m_pFuncs [ iMainFuncIndex ].iLocalDataSize + 1 );		
}

void CTScriptVMBase::RunScript ( Script *pScript, unsigned int uiTimesliceDuration ,unsigned int &uiCurrTime, int &iExitExecLoop)
{
	// Begin a loop that runs until a keypress. The instruction pointer has already been
	// initialized with a prior call to ResetScripts (), so execution can begin
	
	// Create a flag that instructions can use to break the execution loop
	iExitExecLoop = FALSE;
	
	// Create a variable to hold the time at which the main timeslice started
#ifdef _xvm_use_time_
	unsigned int iMainTimesliceStartTime = GetCurrTime ();
	
	// Is the script currently paused?
	if ( pScript->iIsPaused )
	{
		// Has the pause duration elapsed yet?
		if ( uiCurrTime >= pScript->uiPauseEndTime )
		{
			// Yes, so unpause the script
			pScript->iIsPaused = FALSE;
		}
		else
		{
			// No, so skip this iteration of the execution cycle
			return;
		}
	}
#endif

	// Make a copy of the instruction pointer to compare later
	int iCurrInstr = pScript->m_oInstrStream.iCurrInstr;
	
	if (iCurrInstr < 0 || iCurrInstr > pScript->m_oInstrStream.iSize)
	{
		pScript->iIsActive = FALSE;
		pScript->iIsRunning = FALSE;
		pScript->m_iScriptState = SCRIPT_STATE_ERROR;
		return;
	}
	
	// Get the current opcode
	int iOpcode = pScript->m_oInstrStream.m_pInstrs [ iCurrInstr ].iOpcode;
	
  		// Execute the current instruction based on its opcode, as long as we aren't
	// currently paused
#ifdef _debug_out_source
	_debug_output(pScript, &(pScript->m_oInstrStream.m_pInstrs [ iCurrInstr ]));
#endif
	Value Dest;

	switch ( iOpcode )
	{
		// ---- Binary Operations
		
		// All of the binary operation instructions (move, arithmetic, and bitwise)
		// are combined into a single case that keeps us from having to rewrite the
		// otherwise redundant operand resolution and result storage phases over and
		// over. We then use an additional switch block to determine which operation
		// should be performed.
		
		// Move
		
	case INSTRUCT_MOV:
		// Arithmetic Operations
		
	case INSTRUCT_ADD:
	case INSTRUCT_SUB:
	case INSTRUCT_MUL:
	case INSTRUCT_DIV:
	case INSTRUCT_MOD:
	case INSTRUCT_EXP:
		
		// Bitwise Operations
	case INSTRUCT_AND:
	case INSTRUCT_OR:
	case INSTRUCT_XOR:
	case INSTRUCT_SHL:
	case INSTRUCT_SHR:

		// Math  Operations
	case INSTRUCT_ABS:
	case INSTRUCT_SQRT:
	case INSTRUCT_LOG10:
	case INSTRUCT_LOG:
	case INSTRUCT_SIN:
	case INSTRUCT_COS:
	case INSTRUCT_TAN:
	case INSTRUCT_CTAN:
	case INSTRUCT_ASIN:
	case INSTRUCT_ACOS:
	case INSTRUCT_ATAN:
	case INSTRUCT_CEIL:
	case INSTRUCT_FLOOR:
	case INSTRUCT_ATOF:
	case INSTRUCT_ATOL:
	case INSTRUCT_FTOA:
	case INSTRUCT_LTOA:
		
		{
			// Get a local copy of the destination operand (operand index 0)
			Dest = ResolveOpValue (pScript, 0 );
			
			// Get a local copy of the source operand (operand index 1)
			Value Source = ResolveOpValue (pScript, 1 );
			
			// Depending on the instruction, perform a binary operation
			switch ( iOpcode )
			{
				// Move
			case INSTRUCT_MOV:
				// Skip cases where the two operands are the same
				if ( ResolveOpPntr (pScript, 0 ) == ResolveOpPntr (pScript, 1 ) )
				{
					break;
				}
				
				// Copy the source operand into the destination
				CopyValue ( & Dest, Source, FALSE );
				
				break;
				
				// The arithmetic instructions only work with destination types that
				// are either integers or floats. They first check for integers and
				// assume that anything else is a float. Mod only works with integers.
				
				// Add
				
			case INSTRUCT_ADD:
				
				ChangeType(&Dest, Source);

				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral += ResolveOpAsInt (pScript, 1 );
				}
				else
				{
					Dest.fFloatLiteral += ResolveOpAsFloat (pScript, 1 );
				}
				
				break;
				
				// Subtract
				
			case INSTRUCT_SUB:
				
				ChangeType(&Dest, Source);

				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral -= ResolveOpAsInt (pScript, 1 );
				}
				else
				{
					Dest.fFloatLiteral -= ResolveOpAsFloat (pScript, 1 );
				}
				
				break;
				
				// Multiply
				
			case INSTRUCT_MUL:
				
				ChangeType(&Dest, Source);

				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral *= ResolveOpAsInt (pScript, 1 );
				}
				else
				{
					Dest.fFloatLiteral *= ResolveOpAsFloat (pScript, 1 );
				}
				
				break;
				
				// Divide
				
			case INSTRUCT_DIV:
				
				ChangeType(&Dest, Source);

				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral /= ResolveOpAsInt (pScript, 1 );
				}
				else
				{
					Dest.fFloatLiteral /= ResolveOpAsFloat (pScript, 1 );
				}
				
				break;
				
				// Modulus
				
			case INSTRUCT_MOD:
				
				// Remember, Mod works with integers only
				
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral %= ResolveOpAsInt (pScript, 1 );
				}
				
				break;
				
				// Exponentiate
				
			case INSTRUCT_EXP:
				
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral = ( int ) pow ( (double)Dest.iIntLiteral, (double)ResolveOpAsInt (pScript, 1 ) );
				}
				else
				{
					Dest.fFloatLiteral = ( float ) pow ( (double)Dest.fFloatLiteral, (double)ResolveOpAsFloat (pScript, 1 ) );
				}
				
				break;
				
				// The bitwise instructions only work with integers. They do nothing
				// when the destination data type is anything else.
				
				// And
				
			case INSTRUCT_AND:
				
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral &= ResolveOpAsInt (pScript, 1 );
				}
				
				break;
				
				// Or
				
			case INSTRUCT_OR:
				
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral |= ResolveOpAsInt (pScript, 1 );
				}
				
				break;
				
				// Exclusive Or
				
			case INSTRUCT_XOR:
				
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral ^= ResolveOpAsInt (pScript, 1 );
				}
				
				break;
				
				// Shift Left
				
			case INSTRUCT_SHL:
				
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral <<= ResolveOpAsInt (pScript, 1 );
				}
				
				break;
				
				// Shift Right
				
			case INSTRUCT_SHR:
				
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral >>= ResolveOpAsInt (pScript, 1 );
				}
				
				break;

				// Math  Operations
			case INSTRUCT_ABS:
				if ( Dest.iType == OPERAND_TYPE_INT )
				{
					Dest.iIntLiteral = ( int ) (abs ( CoerceValueToInt ( Source ) ));
				}
				else if ( Dest.iType == OPERAND_TYPE_FLOAT )
				{
					Dest.fFloatLiteral = ( float ) fabs ( CoerceValueToFloat ( Source ) );
				}
				else
				{
					FreeValue(Dest, OPERAND_TYPE_FLOAT);
					Dest.fFloatLiteral = 0;
				}
				break;
			case INSTRUCT_SQRT:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) sqrt ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_LOG10:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) log10 ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_LOG:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) log ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_SIN:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) sin ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_COS:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) cos ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_TAN:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) tan ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_CTAN:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = 1.0f / ( float ) tan ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_ASIN:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) asin ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_ACOS:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) acos ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_ATAN:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) atan ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_CEIL:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) ceil ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_FLOOR:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);
				Dest.fFloatLiteral = ( float ) floor ( CoerceValueToFloat ( Source ) );
				break;
			case INSTRUCT_ATOF:
				FreeValue(Dest, OPERAND_TYPE_FLOAT);

				if (Source.iType == OPERAND_TYPE_STRING)
				{
					Dest.fFloatLiteral = ( float ) atof ( Source.pstrStringLiteral );
				}

				break;
			case INSTRUCT_ATOL:
				FreeValue(Dest, OPERAND_TYPE_INT);
				
				if (Source.iType == OPERAND_TYPE_STRING)
				{
					Dest.iIntLiteral = ( int ) atol ( Source.pstrStringLiteral );
				}
				
				break;
			case INSTRUCT_FTOA:
			case INSTRUCT_LTOA:
				{
					FreeValue(Dest, OPERAND_TYPE_STRING);
					static char pszBuff[40];
					
					if (Source.iType == OPERAND_TYPE_FLOAT)
					{
						sprintf(pszBuff, "%f", Source.fFloatLiteral);
					}
					else if (Source.iType == OPERAND_TYPE_INT)
					{
						sprintf(pszBuff, "%d", Source.iIntLiteral);
					}
					else
					{
						pszBuff[0] = 0;
					}

					CopyValue(Dest, pszBuff);
				}					
				break;
			default:
				break;
			}
				
            // Use ResolveOpPntr (pScript,) to get a pointer to the destination Value structure and
            // move the result there
			
			//* ResolveOpPntr (pScript, 0 ) = Dest;
			ResolveOpPntr (pScript,0, Dest);
			
			break;
		}
		
        // ---- Unary Operations
		
        // These instructions work much like the binary operations in the sense that
        // they only work with integers and floats (except Not, which works with
        // integers only). Any other destination data type will be ignored.
		
        case INSTRUCT_NEG:
        case INSTRUCT_NOT:
        case INSTRUCT_INC:
        case INSTRUCT_DEC:
			{
				// Get the destination type (operand index 0)
				
				int iDestStoreType = GetOpType (pScript, 0 );
				
				// Get a local copy of the destination itself
				
				Dest = ResolveOpValue (pScript, 0 );
				
				switch ( iOpcode )
				{
					// Negate
					
                case INSTRUCT_NEG:
					
                    if ( Dest.iType == OPERAND_TYPE_INT )
                        Dest.iIntLiteral = -Dest.iIntLiteral;
                    else
                        Dest.fFloatLiteral = -Dest.fFloatLiteral;
					
                    break;
					
					// Not
					
                case INSTRUCT_NOT:
					
                    if ( Dest.iType == OPERAND_TYPE_INT )
                        Dest.iIntLiteral = ~Dest.iIntLiteral;
					
                    break;
					
					// Increment
					
                case INSTRUCT_INC:
					
                    if ( Dest.iType == OPERAND_TYPE_INT )
                        ++ Dest.iIntLiteral;
                    else
                        ++ Dest.fFloatLiteral;
					
                    break;
					
					// Decrement
					
                case INSTRUCT_DEC:
					
                    if ( Dest.iType == OPERAND_TYPE_INT )
                        -- Dest.iIntLiteral;
                    else
                        -- Dest.fFloatLiteral;
					
                    break;
				}
				
				// Move the result to the destination
				//* ResolveOpPntr (pScript, 0 ) = Dest;
				ResolveOpPntr (pScript,0, Dest);
				
				break;
			}
			
			// ---- String Processing
			
        case INSTRUCT_CONCAT:
			{
				// Get a local copy of the destination operand (operand index 0)
				Dest = ResolveOpValue (pScript, 0 );
				
				// Get a local copy of the source string (operand index 1)
				char * pstrSourceString = ResolveOpAsString (pScript, 1 );
				
				// If the destination isn't a string, do nothing
				if ( Dest.iType != OPERAND_TYPE_STRING )
					break;
				
				// Determine the length of the new string and allocate space for it (with a
				// null terminator)
				int iNewStringLength = strlen ( Dest.pstrStringLiteral ) + strlen ( pstrSourceString );
#ifdef _use_malloc_
				char * pstrNewString = ( char * ) malloc ( iNewStringLength + 1 );
#else
				char * pstrNewString = ( char * ) new BYTE[ ( iNewStringLength + 1 )];
#endif

				// Copy the old string to the new one
				strcpy ( pstrNewString, Dest.pstrStringLiteral );
				
				// Concatenate the destination with the source
				strcat ( pstrNewString, pstrSourceString );
				
				// Free the existing string in the destination structure and replace it
				// with the new string
				free ( Dest.pstrStringLiteral );
				Dest.pstrStringLiteral = pstrNewString;
				
				// Copy the concatenated string pointer to its destination
				//* ResolveOpPntr (pScript, 0 ) = Dest;
				ResolveOpPntr (pScript,0, Dest);

				break;
			}
			
		case INSTRUCT_GETCHAR:
			{
				// Get a local copy of the destination operand (operand index 0)
				Dest = ResolveOpValue (pScript, 0 );
				
				// Get a local copy of the source string (operand index 1)
				char * pstrSourceString = ResolveOpAsString (pScript, 1 );
				
				// Find out whether or not the destination is already a string
				char * pstrNewString;
				if ( Dest.iType == OPERAND_TYPE_STRING )
				{
					// If it is, we can use it's existing string buffer as long as it's at
					// least 1 character
					if ( strlen ( Dest.pstrStringLiteral ) >= 1 )
					{
						pstrNewString = Dest.pstrStringLiteral;
					}
					else
					{
						free ( Dest.pstrStringLiteral );
						pstrNewString = ( char * ) malloc ( 2 );
					}
				}
				else
				{
					// Otherwise allocate a new string and set the type
					pstrNewString = ( char * ) malloc ( 2 );
					Dest.iType = OPERAND_TYPE_STRING;
				}
				
				// Get the index of the character (operand index 2)
				int iSourceIndex = ResolveOpAsInt (pScript, 2 );
				
				// Copy the character and append a null-terminator
				pstrNewString [ 0 ] = pstrSourceString [ iSourceIndex ];
				pstrNewString [ 1 ] = '\0';
				
				// Set the string pointer in the destination Value structure
				Dest.pstrStringLiteral = pstrNewString;
				
				// Copy the concatenated string pointer to its destination
				//* ResolveOpPntr (pScript, 0 ) = Dest;
				ResolveOpPntr (pScript,0, Dest);

				break;
			}
			
		case INSTRUCT_SETCHAR:
			{
				// Get the destination index (operand index 1)
				int iDestIndex = ResolveOpAsInt (pScript, 1 );
				
				// If the destination isn't a string, do nothing
				if ( ResolveOpType (pScript, 0 ) != OPERAND_TYPE_STRING )
					break;
				
				// Get the source character (operand index 2)
				char * pstrSourceString = ResolveOpAsString (pScript, 2 );
				
				// Set the specified character in the destination (operand index 0)
				//ResolveOpPntr (pScript, 0 )->pstrStringLiteral [ iDestIndex ] = pstrSourceString [ 0 ];
				ResolveOpPntr (pScript,0, iDestIndex, pstrSourceString [ 0 ]);

				break;
			}
			
			// ---- Conditional Branching
			
		case INSTRUCT_JMP:
			{
				// Get the index of the target instruction (opcode index 0)
				int iTargetIndex = ResolveOpAsInstrIndex (pScript, 0 );
				
				// Move the instruction pointer to the target
				pScript->m_oInstrStream.iCurrInstr = iTargetIndex;
				
				break;
			}
			
		case INSTRUCT_JE:
		case INSTRUCT_JNE:
		case INSTRUCT_JG:
		case INSTRUCT_JL:
		case INSTRUCT_JGE:
		case INSTRUCT_JLE:
			{
				// Get the two operands
				Value Op0 = ResolveOpValue (pScript, 0 );
				Value Op1 = ResolveOpValue (pScript, 1 );
				
				// Get the index of the target instruction (opcode index 2)
				int iTargetIndex = ResolveOpAsInstrIndex (pScript, 2 );
				
				// Perform the specified comparison and jump if it evaluates to true
				int iJump = FALSE;
				
				switch ( iOpcode )
				{
					// Jump if Equal
                case INSTRUCT_JE:
					{
						switch ( Op0.iType )
						{
                        case OPERAND_TYPE_INT:
                            if ( Op0.iIntLiteral == Op1.iIntLiteral )
                                iJump = TRUE;
                            break;
							
                        case OPERAND_TYPE_FLOAT:
                            if ( Op0.fFloatLiteral == Op1.fFloatLiteral )
                                iJump = TRUE;
                            break;
							
                        case OPERAND_TYPE_STRING:
                            if ( strcmp ( Op0.pstrStringLiteral, Op1.pstrStringLiteral ) == 0 )
                                iJump = TRUE;
                            break;
						}
						break;
					}
					
					// Jump if Not Equal
					
                case INSTRUCT_JNE:
					{
						switch ( Op0.iType )
						{
                        case OPERAND_TYPE_INT:
                            if ( Op0.iIntLiteral != Op1.iIntLiteral )
                                iJump = TRUE;
                            break;
							
                        case OPERAND_TYPE_FLOAT:
                            if ( Op0.fFloatLiteral != Op1.fFloatLiteral )
                                iJump = TRUE;
                            break;
							
                        case OPERAND_TYPE_STRING:
                            if ( strcmp ( Op0.pstrStringLiteral, Op1.pstrStringLiteral ) != 0 )
                                iJump = TRUE;
                            break;
						}
						break;
					}
					
					// Jump if Greater
					
                case INSTRUCT_JG:
					
                    if ( Op0.iType == OPERAND_TYPE_INT )
                    {
                        if ( Op0.iIntLiteral > Op1.iIntLiteral )
                            iJump = TRUE;
					}
                    else
                    {
                        if ( Op0.fFloatLiteral > Op1.fFloatLiteral )
                            iJump = TRUE;
					}
					
                    break;
					
					// Jump if Less
					
                case INSTRUCT_JL:
					
                    if ( Op0.iType == OPERAND_TYPE_INT )
                    {
                        if ( Op0.iIntLiteral < Op1.iIntLiteral )
                            iJump = TRUE;
					}
                    else
                    {
                        if ( Op0.fFloatLiteral < Op1.fFloatLiteral )
                            iJump = TRUE;
					}
					
                    break;
					
					// Jump if Greater or Equal
					
                case INSTRUCT_JGE:
					
                    if ( Op0.iType == OPERAND_TYPE_INT )
                    {
                        if ( Op0.iIntLiteral >= Op1.iIntLiteral )
                            iJump = TRUE;
					}
                    else
                    {
                        if ( Op0.fFloatLiteral >= Op1.fFloatLiteral )
                            iJump = TRUE;
					}
					
                    break;
					
					// Jump if Less or Equal
					
                case INSTRUCT_JLE:
					
                    if ( Op0.iType == OPERAND_TYPE_INT )
                    {
                        if ( Op0.iIntLiteral <= Op1.iIntLiteral )
                            iJump = TRUE;
					}
                    else
                    {
                        if ( Op0.fFloatLiteral <= Op1.fFloatLiteral )
                            iJump = TRUE;
					}
					
                    break;
            }
			
            // If the comparison evaluated to TRUE, make the jump
			
            if ( iJump )
                pScript->m_oInstrStream.iCurrInstr = iTargetIndex;
			
			break;
        }
		
        // ---- The Stack Interface
		
		case INSTRUCT_PUSH:
			{
				// Get a local copy of the source operand (operand index 0)
				
				Value Source = ResolveOpValue (pScript, 0 );
				
				// Push the value onto the stack
				
				Push ( pScript, Source );
				
				break;
			}
			
		case INSTRUCT_POP:
			{
				// Pop the top of the stack into the destination
				
				//* ResolveOpPntr (pScript, 0 ) = Pop (pScript );
				Value oValue = Pop ( pScript );
				ResolveOpPntr (pScript,0, oValue);
				//FreeValue(oValue);
				break;
			}
			
			// ---- The Function Call Interface
			
		case INSTRUCT_CALL:
			{
				// Get a local copy of the function index
				int iFuncIndex = ResolveOpAsFuncIndex (pScript, 0 );
				
				// Advance the instruction pointer so it points to the instruction
				// immediately following the call
				++ pScript->m_oInstrStream.iCurrInstr;
				
				// Call the function
				CallFunc ( pScript, iFuncIndex );
				
				break;
			}
			
		case INSTRUCT_RET:
			{
				// Get the current function index off the top of the stack and use it to get
				// the corresponding function structure
				Value FuncIndex = Pop (pScript );
				
				// Check for the presence of a stack base marker
				if ( FuncIndex.iType == OPERAND_TYPE_STACK_BASE_MARKER )
				{
					iExitExecLoop = TRUE;
				}
				
				// Get the previous function index
				Func CurrFunc = GetFunc ( pScript, FuncIndex.iFuncIndex );
				int iFrameIndex = FuncIndex.iOffsetIndex;
				
				// Read the return address structure from the stack, which is stored one
				// index below the local data
				Value ReturnAddr = GetStackValue ( pScript, pScript->Stack.iTopIndex - ( CurrFunc.iLocalDataSize + 1 ) );
				
				// Pop the stack frame along with the return address
				PopFrame ( pScript, CurrFunc.iStackFrameSize );
				
				// Restore the previous frame index
				pScript->Stack.iFrameIndex = iFrameIndex;
				
				// Make the jump to the return address
				pScript->m_oInstrStream.iCurrInstr = ReturnAddr.iInstrIndex;
				
				break;
			}
			
		case INSTRUCT_CALLHOST:
			{
				// Use operand zero to index into the host API call table and get the
				// host API function name
				Value HostAPICall = ResolveOpValue (pScript, 0 );
				int iHostAPICallIndex = HostAPICall.iHostAPICallIndex;
				int iHostAPIFuncIndex = 0;
				
				// Get the name of the host API function
				char * pstrFuncName = GetHostAPICall ( pScript, iHostAPICallIndex );
				
				// Search through the host API until the matching function is found
				int iMatchFound = FALSE;
				for ( iHostAPIFuncIndex = 0; iHostAPIFuncIndex < MAX_HOST_API_SIZE; ++ iHostAPIFuncIndex )
				{
					// Get a pointer to the name of the current host API function
					char * pstrCurrHostAPIFunc = g_HostAPI [ iHostAPIFuncIndex ].pstrName;
					
					if (pstrCurrHostAPIFunc != NULL)
					{
						// If it equals the requested name, it might be a match
						if ( stricmp ( pstrFuncName, pstrCurrHostAPIFunc ) == 0 )
						{
							// Make sure the function is visible to the current thread
							int iThreadIndex = g_HostAPI [ iHostAPIFuncIndex ].iThreadIndex;
							if ( iThreadIndex == pScript->m_iThreadIndex || iThreadIndex == TS_GLOBAL_FUNC )
							{
								iMatchFound = TRUE;
								break;
							}
						}
					}
				}
				
				// If a match was found, call the host API funcfion and pass the current
				// thread index
				if ( iMatchFound )
				{
					//g_HostAPI [ iHostAPIFuncIndex ].fnFunc ( pScript->m_iThreadIndex );
					g_HostAPI [ iHostAPIFuncIndex ].fnFunc ( this );
				}
				
				break;
			}
			
			// ---- Misc
			
		case INSTRUCT_PAUSE:
			{
				// Get the pause duration
				int iPauseDuration = ResolveOpAsInt (pScript, 0 );
				
				// Determine the ending pause time
				pScript->uiPauseEndTime = uiCurrTime + iPauseDuration;
				
				// Pause the script
				pScript->iIsPaused = TRUE;
				
				break;
			}
			
        case INSTRUCT_EXIT:
			{
				// Resolve operand zero to find the exit code
				Value ExitCode = ResolveOpValue (pScript, 0 );
				
				// Get it from the integer field
				int iExitCode = ExitCode.iIntLiteral;
				
				// Tell the XVM to stop executing the script
				pScript->iIsRunning = FALSE;
				
				break;
			}

			//Math Operations
		case INSTRUCT_POW:
		case INSTRUCT_ATAN2:
		case INSTRUCT_MIN:
		case INSTRUCT_MAX:
		case INSTRUCT_HYPOT:
		case INSTRUCT_FMOD:
		case INSTRUCT_DIGIT:
		case INSTRUCT_BINARY:
		case INSTRUCT_CMP:
		case INSTRUCT_CMPE:
		case INSTRUCT_CMPNE:
		case INSTRUCT_CMPG:
		case INSTRUCT_CMPL:
		case INSTRUCT_CMPGE:
		case INSTRUCT_CMPLE:				
			{
				// Get a local copy of the destination operand (operand index 0)
				Dest = ResolveOpValue (pScript, 0 );
				
				// Get a local copy of the source operand (operand index 1)
				Value Source1 = ResolveOpValue (pScript, 1 );
				
				// Get a local copy of the source operand (operand index 2)
				Value Source2 = ResolveOpValue (pScript, 2 );

				switch ( iOpcode )
				{
				case INSTRUCT_POW:
					FreeValue(Dest, OPERAND_TYPE_FLOAT);

					if (IsValueNumber(Source1) && IsValueNumber(Source2))
					{
						Dest.fFloatLiteral = ( float ) pow ( CoerceValueToFloat(Source1), CoerceValueToFloat(Source2) );
					}

					break;
				case INSTRUCT_ATAN2:
					FreeValue(Dest, OPERAND_TYPE_FLOAT);
					
					if (IsValueNumber(Source1) && IsValueNumber(Source2))
					{
						Dest.fFloatLiteral = ( float ) atan2 ( CoerceValueToFloat(Source1), CoerceValueToFloat(Source2) );
					}
					break;
				case INSTRUCT_MIN:
					FreeValue(Dest, OPERAND_TYPE_FLOAT);
					
					if (IsValueNumber(Source1) && IsValueNumber(Source2))
					{
                        Dest.fFloatLiteral = ( float ) min ( CoerceValueToFloat(Source1), CoerceValueToFloat(Source2) );
					}
					break;
				case INSTRUCT_MAX:
					FreeValue(Dest, OPERAND_TYPE_FLOAT);
					
					if (IsValueNumber(Source1) && IsValueNumber(Source2))
					{
                        Dest.fFloatLiteral = ( float ) max ( CoerceValueToFloat(Source1), CoerceValueToFloat(Source2) );
					}
					break;
				case INSTRUCT_HYPOT:
					FreeValue(Dest, OPERAND_TYPE_FLOAT);
					
					if (IsValueNumber(Source1) && IsValueNumber(Source2))
					{
						Dest.fFloatLiteral = ( float ) hypot ( CoerceValueToFloat(Source1), CoerceValueToFloat(Source2) );
					}
					break;
				case INSTRUCT_FMOD:
					FreeValue(Dest, OPERAND_TYPE_FLOAT);
					
					if (IsValueNumber(Source1) && IsValueNumber(Source2))
					{
						Dest.fFloatLiteral = ( float ) fmod ( CoerceValueToFloat(Source1), CoerceValueToFloat(Source2) );
					}
					break;
				case INSTRUCT_DIGIT:
					{
						FreeValue(Dest, OPERAND_TYPE_INT);

						if (IsValueNumber(Source1) && IsValueNumber(Source2))
						{
							int nIndex = CoerceValueToInt(Source2);
							double dVal = CoerceValueToFloat(Source1);
							double dVal2 = pow(10.0, (double)nIndex);
							Dest.iIntLiteral  = (int)(dVal / dVal2);
						}
					}
					break;
				case INSTRUCT_BINARY:
					{
						FreeValue(Dest, OPERAND_TYPE_INT);
						
						if (IsValueNumber(Source1) && IsValueNumber(Source2))
						{
							int nIndex = CoerceValueToInt(Source2);
							Dest.iIntLiteral = CoerceValueToInt(Source1);

							if (nIndex < 0)
							{
								nIndex = 0;
							}
							
							Dest.iIntLiteral = (Dest.iIntLiteral >> nIndex) & 0x01;
						}
					}
					break;
				case INSTRUCT_CMP:
				case INSTRUCT_CMPE:
				case INSTRUCT_CMPNE:
				case INSTRUCT_CMPG:
				case INSTRUCT_CMPL:
				case INSTRUCT_CMPGE:
				case INSTRUCT_CMPLE:
					{		
						if (Dest.iType == OPERAND_TYPE_STRING && Source1.iType == OPERAND_TYPE_STRING)
						{
							Dest.iType = OPERAND_TYPE_INT;
							Dest.fFloatLiteral = 0;
						}
						else
						{
							FreeValue(Dest, OPERAND_TYPE_INT);
						}

						if (IsValueString(Source1) && IsValueString(Source2))
						{
							char *pstr1 = CoerceValueToString(Source1);
							char *pstr2 = CoerceValueToString(Source2);
							
							Dest.iIntLiteral = strcmp(pstr1, pstr2);
						}
						else// if (IsValueNumber(Source1) && IsValueNumber(Source2))
						{
							float fVal1 = CoerceValueToFloat(Source1);
							float fVal2 = CoerceValueToFloat(Source2);
							
							if (fVal1 > fVal2)
							{
								Dest.iIntLiteral = 1;
							}
							else if (fVal1 == fVal2)
							{
								Dest.iIntLiteral = 0;
							}
							else
							{
								Dest.iIntLiteral = -1;
							}
						}


						switch(iOpcode)
						{
						case INSTRUCT_CMPE:
							Dest.iIntLiteral = (Dest.iIntLiteral == 0);
							break;
						case INSTRUCT_CMPNE:
							Dest.iIntLiteral = (Dest.iIntLiteral != 0);
							break;
						case INSTRUCT_CMPG:
							Dest.iIntLiteral = (Dest.iIntLiteral > 0);
							break;
						case INSTRUCT_CMPL:
							Dest.iIntLiteral = (Dest.iIntLiteral < 0);
							break;
						case INSTRUCT_CMPGE:
							Dest.iIntLiteral = (Dest.iIntLiteral >= 0);
							break;
						case INSTRUCT_CMPLE:
							Dest.iIntLiteral = (Dest.iIntLiteral <= 0);
							break;
						default:
							break;
						}
					}
					
					break;
				}

				//* ResolveOpPntr (pScript, 0 ) = Dest;
				ResolveOpPntr (pScript,0, Dest);
			}
			break;
	}
	
#ifdef _debug_out_source
	printf("   ####   ");
	_debug_output(Dest);
	printf("\n");
#endif
	
    // If the instruction pointer hasn't been changed by an instruction, increment it
    if ( iCurrInstr == pScript->m_oInstrStream.iCurrInstr )
	{
		++ pScript->m_oInstrStream.iCurrInstr;
	}
	
    // If we aren't running indefinitely, check to see if the main timeslice has ended
#ifdef _xvm_use_time_
	if ( uiTimesliceDuration != TS_INFINITE_TIMESLICE )
	{
		if ( uiCurrTime > iMainTimesliceStartTime + uiTimesliceDuration )
		{
			return;
		}
	}
#endif

	// Exit the execution loop if the script has terminated
	if ( iExitExecLoop )
	{
		return;
	}
}


CTScriptVMBase::ExportSymbol* CTScriptVMBase::FindExportSymbol( Script *pScript, const char* pstrName)
{
	ExportSymbols &oSymbols = pScript->m_oExportSymbols;
		
	ExportSymbol *p = NULL;
	ExportSymbol *pFind = NULL;

	int iCount = oSymbols.iSize;
	int iIndex = 0;

	for (iIndex=0; iIndex<iCount; iIndex++)
	{
		p = &(oSymbols.m_pExportSymbols[iIndex]);

		if (strcmp(p->pstrName, pstrName) == 0)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CTScriptVMBase::ExportSymbol* CTScriptVMBase::FindExportSymbol( Script *pScript, int iIndex)
{
	ExportSymbols &oSymbols = pScript->m_oExportSymbols;

	if (iIndex >= 0 && iIndex <= oSymbols.iSize)
	{
		return &(oSymbols.m_pExportSymbols[iIndex]);
	}
	else
	{
		return NULL;
	}
}

int CTScriptVMBase::GetExportValueCount ( Script *pScript)
{
	return pScript->m_oExportSymbols.iSize;
}

bool  CTScriptVMBase::GetExportValue ( Script *pScript , const char* pstrName, int &iValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);

	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		Value v = pScript->Stack.pElmnts[pSymbol->iStackIndex];
		iValue = CoerceValueToInt(v);
		return true;
	}
}

bool CTScriptVMBase::GetExportValue ( Script *pScript , const char* pstrName, float &fValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		Value v = pScript->Stack.pElmnts[pSymbol->iStackIndex];
		fValue = CoerceValueToFloat(v);
		return true;
	}
}

bool CTScriptVMBase::GetExportValue ( Script *pScript , const char* pstrName, char* &pstrValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		Value v = pScript->Stack.pElmnts[pSymbol->iStackIndex];
		CoerceValueToString(v, pstrValue);
		return true;
	}
}

bool CTScriptVMBase::IsExportValueInt ( Script *pScript , const char* pstrName)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		return (pScript->Stack.pElmnts[pSymbol->iStackIndex].iType == OPERAND_TYPE_INT);
	}	
}

bool CTScriptVMBase::IsExportValueFloat ( Script *pScript , const char* pstrName)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		return (pScript->Stack.pElmnts[pSymbol->iStackIndex].iType == OPERAND_TYPE_FLOAT);
	}	
}

bool CTScriptVMBase::IsExportValueString ( Script *pScript , const char* pstrName)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		return (pScript->Stack.pElmnts[pSymbol->iStackIndex].iType == OPERAND_TYPE_STRING);
	}	
}


bool CTScriptVMBase::GetExportValue ( Script *pScript , int iIndex, char* pstrName, int &iValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		strcpy(pstrName, pSymbol->pstrName);
		Value v = pScript->Stack.pElmnts[pSymbol->iStackIndex];
		iValue = CoerceValueToInt(v);
		return true;
	}
}

bool CTScriptVMBase::GetExportValue ( Script *pScript , int iIndex, char* pstrName, float &fValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		strcpy(pstrName, pSymbol->pstrName);
		Value v = pScript->Stack.pElmnts[pSymbol->iStackIndex];
		fValue = CoerceValueToFloat(v);
		return true;
	}
}

bool CTScriptVMBase::GetExportValue ( Script *pScript , int iIndex, char* pstrName, char* &pstrValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		strcpy(pstrName, pSymbol->pstrName);
		Value v = pScript->Stack.pElmnts[pSymbol->iStackIndex];
		CoerceValueToString(v, pstrValue);
		return true;
	}
}

bool CTScriptVMBase::SetExportValue ( Script *pScript , const char* pstrName, int &iValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		ChangeValue(pScript->Stack.pElmnts[pSymbol->iStackIndex], iValue);
		return true;
	}
}

bool CTScriptVMBase::SetExportValue ( Script *pScript , const char* pstrName, float &fValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		ChangeValue(pScript->Stack.pElmnts[pSymbol->iStackIndex], fValue);
		return true;
	}
}

bool CTScriptVMBase::SetExportValue ( Script *pScript , const char* pstrName, char* &pstrValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, pstrName);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		ChangeValue(pScript->Stack.pElmnts[pSymbol->iStackIndex], pstrValue);
		return true;
	}
}

bool CTScriptVMBase::SetExportValue ( Script *pScript , int iIndex, int &iValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		ChangeValue(pScript->Stack.pElmnts[pSymbol->iStackIndex], iValue);
		return true;
	}
}

bool CTScriptVMBase::SetExportValue ( Script *pScript , int iIndex, float &fValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		ChangeValue(pScript->Stack.pElmnts[pSymbol->iStackIndex], fValue);
		return true;
	}
}

bool CTScriptVMBase::SetExportValue ( Script *pScript , int iIndex, char* &pstrValue)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		ChangeValue(pScript->Stack.pElmnts[pSymbol->iStackIndex], pstrValue);
		return true;
	}
}

bool CTScriptVMBase::IsExportValueInt ( Script *pScript , int iIndex)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		return (pScript->Stack.pElmnts[pSymbol->iStackIndex].iType == OPERAND_TYPE_INT);
		return true;
	}
}

bool CTScriptVMBase::IsExportValueFloat ( Script *pScript , int iIndex)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		return (pScript->Stack.pElmnts[pSymbol->iStackIndex].iType == OPERAND_TYPE_FLOAT);
		return true;
	}
}

bool CTScriptVMBase::IsExportValueString ( Script *pScript , int iIndex)
{
	ExportSymbol *pSymbol = FindExportSymbol(pScript, iIndex);
	
	if (pSymbol == NULL)
	{
		return false;
	}
	else
	{
		return (pScript->Stack.pElmnts[pSymbol->iStackIndex].iType == OPERAND_TYPE_STRING);
		return true;
	}
}

/******************************************************************************************
*
*   CallFunc ()
*
*   Calls a function based on its index.
*/
void CTScriptVMBase::CallFunc ( Script *pScript, int iFuncIndex )
{
	Func DestFunc = GetFunc ( pScript, iFuncIndex );
	
	// Save the current stack frame index
	int iFrameIndex = pScript->Stack.iFrameIndex;
	
	// Push the return address, which is the current instruction
	Value ReturnAddr;
	ReturnAddr.iInstrIndex = pScript->m_oInstrStream.iCurrInstr;
	Push ( pScript, ReturnAddr );
	
	// Push the stack frame + 1 (the extra space is for the function index
	// we'll put on the stack after it)
	PushFrame ( pScript, DestFunc.iLocalDataSize + 1 );
	
	// Write the function index and old stack frame to the top of the stack
	Value FuncIndex;
	FuncIndex.iFuncIndex = iFuncIndex;
	FuncIndex.iOffsetIndex = iFrameIndex;
	SetStackValue ( pScript, pScript->Stack.iTopIndex - 1, FuncIndex );
	
	// Let the caller make the jump to the entry point
	pScript->m_oInstrStream.iCurrInstr = DestFunc.iEntryPoint;
}




/******************************************************************************************
*
*   CoereceValueToInt ()
*
*   Coerces a Value structure from it's current type to an integer value.
*/

int CTScriptVMBase::CoerceValueToInt ( Value &Val )
{
	// Determine which type the Value currently is
	switch ( Val.iType )
	{
	case OPERAND_TYPE_INT:// It's an integer, so return it as-is
		return Val.iIntLiteral;

	case OPERAND_TYPE_FLOAT:// It's a float, so cast it to an integer
		return ( int ) Val.fFloatLiteral;

	case OPERAND_TYPE_STRING:// It's a string, so convert it to an integer
		return atoi ( Val.pstrStringLiteral );
		
	default:// Anything else is invalid
		return 0;
	}
}


/******************************************************************************************
*
*   CoereceValueToFloat ()
*
*   Coerces a Value structure from it's current type to an float value.
*/
float CTScriptVMBase::CoerceValueToFloat ( Value &Val )
{
	// Determine which type the Value currently is
	switch ( Val.iType )
	{
		// It's an integer, so cast it to a float
	case OPERAND_TYPE_INT:
		return ( float ) Val.iIntLiteral;
		
		// It's a float, so return it as-is
	case OPERAND_TYPE_FLOAT:
		return Val.fFloatLiteral;
		
		// It's a string, so convert it to an float
	case OPERAND_TYPE_STRING:
		return ( float ) atof ( Val.pstrStringLiteral );
		
		// Anything else is invalid
	default:
		return 0;
	}
}

/******************************************************************************************
*
*   CoereceValueToString ()
*
*   Coerces a Value structure from it's current type to a string value.
*/

char* CTScriptVMBase::CoerceValueToString ( Value &Val )
{
// 	char * pstrCoercion;
// 	if ( Val.iType != OPERAND_TYPE_STRING )
// 		pstrCoercion = m_chReturn;( char * ) malloc ( MAX_COERCION_STRING_SIZE + 1 );
	
	// Determine which type the Value currently is
	switch ( Val.iType )
	{
		// It's an integer, so convert it to a string
	case OPERAND_TYPE_INT:
		//当字符串类型的参数为空字符串时，解析到的类型为整型，这个是编译的问题；
		//暂时先用这个判断进行规避，20200908  shaolei
		IncreaseChReturn();
		if (Val.iIntLiteral == 0)
		{
			m_chReturn[m_nChReturnIndex][0] = 0;
		}
		else
		{
			itoa ( Val.iIntLiteral, m_chReturn[m_nChReturnIndex], 10 );
		}
		
		return m_chReturn[m_nChReturnIndex];
		
		// It's a float, so use sprintf () to convert it since there's no built-in function
		// for converting floats to strings
	case OPERAND_TYPE_FLOAT:
		IncreaseChReturn();
		sprintf ( m_chReturn[m_nChReturnIndex], "%f", Val.fFloatLiteral );
		return m_chReturn[m_nChReturnIndex];
		
		// It's a string, so return it as-is
	case OPERAND_TYPE_STRING:
		return Val.pstrStringLiteral;
		
		// Anything else is invalid
	default:
		return NULL;
	}
}

char* CTScriptVMBase::CoerceValueToString ( Value &Val , char *pValue)
{
	// Determine which type the Value currently is
	switch ( Val.iType )
	{
		// It's an integer, so convert it to a string
	case OPERAND_TYPE_INT:
		itoa ( Val.iIntLiteral, pValue, 10 );
		break;
		
		// It's a float, so use sprintf () to convert it since there's no built-in function
		// for converting floats to strings
	case OPERAND_TYPE_FLOAT:
		sprintf ( pValue, "%f", Val.fFloatLiteral );
		break;
		
		// It's a string, so return it as-is
	case OPERAND_TYPE_STRING:
		strcpy(pValue, Val.pstrStringLiteral);
		break;
		
		// Anything else is invalid
	default:
		*pValue = 0;
		break;
	}

	return pValue;
}

/******************************************************************************************
*
*   CopyValue ()
*
*   Copies a value structure to another, taking strings into account.
*/
void CTScriptVMBase::CopyValue ( Value * pDest, Value &Source, BOOL bFree )
{
	if( (pDest->iType == OPERAND_TYPE_STRING && Source.iType == OPERAND_TYPE_STRING)
		&& (pDest->pstrStringLiteral == Source.pstrStringLiteral) )
	{
		ASSERT(FALSE);
		return;
	}

	// If the destination already contains a string, make sure to free it first
	if (pDest->iType == OPERAND_TYPE_STRING ) 
	{
		if (bFree)
		{
			free ( pDest->pstrStringLiteral );
		}
	}
		
	// Make a physical copy of the source string, if necessary
	if ( Source.iType == OPERAND_TYPE_STRING )
	{
		ASSERT (Source.pstrStringLiteral != NULL);

		if (Source.pstrStringLiteral != NULL)
		{
#ifdef _use_malloc_
			pDest->pstrStringLiteral = ( char * ) malloc ( strlen ( Source.pstrStringLiteral ) + 1 );
#else
			pDest->pstrStringLiteral = ( char * ) new BYTE[( strlen ( Source.pstrStringLiteral ) + 1 ) ];
#endif
			strcpy ( pDest->pstrStringLiteral, Source.pstrStringLiteral );
		}
		else
		{
			pDest->pstrStringLiteral = ( char * ) new BYTE[2];
			*pDest->pstrStringLiteral = 0;
		}

		pDest->iType = Source.iType;
		pDest->iOffsetIndex = Source.iOffsetIndex;
	}
	else
	{
		// Copy the object
		* pDest = Source;
	}
}

void CTScriptVMBase::ChangeType(Value * pDest, Value &Source)
{
	if (pDest->iType == Source.iType)
	{
		return;
	}

	if (Source.iType == OPERAND_TYPE_FLOAT)
	{
		if (pDest->iType == OPERAND_TYPE_INT)
		{
			int nVal = pDest->iIntLiteral;
			pDest->iType = OPERAND_TYPE_FLOAT;
			pDest->fFloatLiteral = nVal;
		}
	}
}

/******************************************************************************************
*
*   XS_RegisterHostAPIFunc ()
*
*   Registers a function with the host API.
*/

void CTScriptVMBase::RegisterHostAPIFunc ( int iThreadIndex, char * pstrName, HostAPIFuncPntr *fnFunc )
{
	 int iCurrHostAPIFunc = 0;

	// Loop through each function in the host API until a free index is found
	for ( iCurrHostAPIFunc = 0; iCurrHostAPIFunc < MAX_HOST_API_SIZE; ++ iCurrHostAPIFunc )
	{
		// If the current index is free, use it
		if ( ! g_HostAPI [ iCurrHostAPIFunc ].iIsActive )
		{
			// Set the function's parameters
			g_HostAPI [ iCurrHostAPIFunc ].iThreadIndex = iThreadIndex;
			g_HostAPI [ iCurrHostAPIFunc ].pstrName = ( char * ) malloc ( strlen ( pstrName ) + 1 );
			strcpy ( g_HostAPI [ iCurrHostAPIFunc ].pstrName, pstrName );
			//strupr ( g_HostAPI [ iCurrHostAPIFunc ].pstrName );
			g_HostAPI [ iCurrHostAPIFunc ].fnFunc = fnFunc;
			
			// Set the function to active
			g_HostAPI [ iCurrHostAPIFunc ].iIsActive = TRUE;

			break;
		}
	}

	ASSERT (iCurrHostAPIFunc < MAX_HOST_API_SIZE);
}



void CTScriptVMBase::_debug_output(Script *pScript, Instr *pInstr)
{
	int iOpcode = pInstr->iOpcode;
	Value Dest;
	
	switch ( iOpcode )
	{
		// Move
	case INSTRUCT_MOV:
		
		// Arithmetic Operations
	case INSTRUCT_ADD:
	case INSTRUCT_SUB:
	case INSTRUCT_MUL:
	case INSTRUCT_DIV:
	case INSTRUCT_MOD:
	case INSTRUCT_EXP:
		
		// Bitwise Operations
	case INSTRUCT_AND:
	case INSTRUCT_OR:
	case INSTRUCT_XOR:
	case INSTRUCT_SHL:
	case INSTRUCT_SHR:
		
		// Math  Operations
	case INSTRUCT_ABS:
	case INSTRUCT_SQRT:
	case INSTRUCT_LOG10:
	case INSTRUCT_LOG:
	case INSTRUCT_SIN:
	case INSTRUCT_COS:
	case INSTRUCT_TAN:
	case INSTRUCT_CTAN:
	case INSTRUCT_ASIN:
	case INSTRUCT_ACOS:
	case INSTRUCT_ATAN:
	case INSTRUCT_CEIL:
	case INSTRUCT_FLOOR:
	case INSTRUCT_ATOF:
	case INSTRUCT_ATOL:
	case INSTRUCT_FTOA:
	case INSTRUCT_LTOA:
		{
			// Get a local copy of the destination operand (operand index 0)
			Dest = ResolveOpValue (pScript, 0 );
			
			// Get a local copy of the source operand (operand index 1)
			Value Source = ResolveOpValue (pScript, 1 );
			
			// Depending on the instruction, perform a binary operation
			switch ( iOpcode )
			{
				// Move
			case INSTRUCT_MOV:
				printf("mov ");
				
				break;
				
				// The arithmetic instructions only work with destination types that
				// are either integers or floats. They first check for integers and
				// assume that anything else is a float. Mod only works with integers.
				
				// Add
				
			case INSTRUCT_ADD:
				printf("add ");
				break;
				
				// Subtract
				
			case INSTRUCT_SUB:
				printf("sub ");
				break;
				
				// Multiply
				
			case INSTRUCT_MUL:
				printf("mul ");
				break;
				
				// Divide
				
			case INSTRUCT_DIV:
				printf("div ");
				break;
				
				// Modulus
				
			case INSTRUCT_MOD:
				printf("mod ");
				break;
				
				// Exponentiate
				
			case INSTRUCT_EXP:
				printf("exp ");
				
				break;
				
				// The bitwise instructions only work with integers. They do nothing
				// when the destination data type is anything else.
				
				// And
				
			case INSTRUCT_AND:
				printf("and ");
				break;
				
				// Or
				
			case INSTRUCT_OR:
				printf("or ");
				break;
				
				// Exclusive Or
				
			case INSTRUCT_XOR:
				printf("xor ");
				
				break;
				
				// Shift Left
				
			case INSTRUCT_SHL:
				printf("shl ");
				break;
				
				// Shift Right
				
			case INSTRUCT_SHR:
				printf("shr ");
				break;
				
				// Math  Operations
			case INSTRUCT_ABS:
				printf("abs ");
				break;
			case INSTRUCT_SQRT:
				printf("sqrt ");
				break;
			case INSTRUCT_LOG10:
				printf("log10 ");
				break;
			case INSTRUCT_LOG:
				printf("log ");
				break;
			case INSTRUCT_SIN:
				printf("sin ");
				break;
			case INSTRUCT_COS:
				printf("cos ");
				break;
			case INSTRUCT_TAN:
				printf("tan ");
				break;
			case INSTRUCT_CTAN:
				printf("ctan ");
				break;
			case INSTRUCT_ASIN:
				printf("asin ");
				break;
			case INSTRUCT_ACOS:
				printf("acos ");
				break;
			case INSTRUCT_ATAN:
				printf("atan ");
				break;
			case INSTRUCT_CEIL:
				printf("ceil ");
				break;
			case INSTRUCT_FLOOR:
				printf("fllor ");
				break;
			case INSTRUCT_ATOF:
				printf("atof ");
				break;
			case INSTRUCT_ATOL:
				printf("atol ");
				break;
			case INSTRUCT_FTOA:
				printf("ftoa ");
				break;
			case INSTRUCT_LTOA:
				printf("ltoa ");					
				break;
			default:
				break;
			}

		_debug_output(Dest);
		_debug_output(Source);
		break;
		}
				
				// ---- Unary Operations
				
				// These instructions work much like the binary operations in the sense that
				// they only work with integers and floats (except Not, which works with
				// integers only). Any other destination data type will be ignored.
				
		case INSTRUCT_NEG:
		case INSTRUCT_NOT:
		case INSTRUCT_INC:
		case INSTRUCT_DEC:
			{
				// Get the destination type (operand index 0)
				
				int iDestStoreType = GetOpType (pScript, 0 );
				
				// Get a local copy of the destination itself
				
				Dest = ResolveOpValue (pScript, 0 );
				
				switch ( iOpcode )
				{
					// Negate
					
				case INSTRUCT_NEG:
					printf("neg ");
					break;
					
					// Not
					
				case INSTRUCT_NOT:
					printf("not ");
					break;
					
					// Increment
					
				case INSTRUCT_INC:
					printf("inc ");
					break;
					
					// Decrement
					
				case INSTRUCT_DEC:
					printf("dec ");
					break;
				}
				
				_debug_output(Dest);
				break;
			}
		
		// ---- String Processing
		
	case INSTRUCT_CONCAT:
		{
			printf("concat ");
			Dest = ResolveOpValue (pScript, 0 );
			Value Source = ResolveOpValue (pScript, 1 );
			_debug_output(Dest);
			_debug_output(Source);
			
			break;
		}
		
	case INSTRUCT_GETCHAR:
		{
			printf("getchar ");
			Dest = ResolveOpValue (pScript, 0 );
			Value Source = ResolveOpValue (pScript, 1 );
			Value Source2 = ResolveOpValue (pScript, 2 );
			_debug_output(Dest);
			_debug_output(Source);
			_debug_output(Source2);
			
			break;
		}
		
	case INSTRUCT_SETCHAR:
		{
			printf("setchar ");
			Dest = ResolveOpValue (pScript, 0 );
			Value Source = ResolveOpValue (pScript, 1 );
			Value Source2 = ResolveOpValue (pScript, 2 );
			_debug_output(Dest);
			_debug_output(Source);
			_debug_output(Source2);
			
			break;
		}
		
		// ---- Conditional Branching
		
	case INSTRUCT_JMP:
		{
			printf("jmp ");
			Value Source = ResolveOpValue (pScript, 0 );
			_debug_output(Source);
			break;
		}
		
	case INSTRUCT_JE:
	case INSTRUCT_JNE:
	case INSTRUCT_JG:
	case INSTRUCT_JL:
	case INSTRUCT_JGE:
	case INSTRUCT_JLE:
		{
			switch ( iOpcode )
			{
				// Jump if Equal
			case INSTRUCT_JE:
				{
					printf("je ");
					break;
				}
				
				// Jump if Not Equal
				
			case INSTRUCT_JNE:
				{
					printf("jne ");
					break;
				}
				
				// Jump if Greater
				
			case INSTRUCT_JG:
				printf("jg ");
				
				break;
				
				// Jump if Less
				
			case INSTRUCT_JL:
				printf("jl ");
				
				break;
				
				// Jump if Greater or Equal
				
			case INSTRUCT_JGE:
				printf("jge ");
				
				break;
				
				// Jump if Less or Equal
				
			case INSTRUCT_JLE:
				printf("jle ");
				
				break;
			}
			
			// If the comparison evaluated to TRUE, make the jump
			Dest = ResolveOpValue (pScript, 0 );
			Value Source = ResolveOpValue (pScript, 1 );
			Value Source2 = ResolveOpValue (pScript, 2 );
			_debug_output(Dest);
			_debug_output(Source);
			_debug_output(Source2);				
			
			break;
		}
		
		// ---- The Stack Interface
	case INSTRUCT_PUSH:
		{
			printf("push ");
			Value Source = ResolveOpValue (pScript, 0 );
			_debug_output(Source);
			break;
		}
		
	case INSTRUCT_POP:
		{
			printf("pop ");
			Value Source = ResolveOpValue (pScript, 0 );
			_debug_output(Source);
			break;
		}
		
		// ---- The Function Call Interface
		
	case INSTRUCT_CALL:
		{
			printf("call ");
			Value Source = ResolveOpValue (pScript, 0 );
			_debug_output(Source);
			break;
		}
		
	case INSTRUCT_RET:
		{
			printf("ret ");
			
			break;
		}
		
	case INSTRUCT_CALLHOST:
		{
			printf("callhost ");
			Value Source = ResolveOpValue (pScript, 0 );
			_debug_output(Source);
			break;
		}
		
		// ---- Misc
		
	case INSTRUCT_PAUSE:
		{
			printf("pause ");
			Value Source = ResolveOpValue (pScript, 0 );
			_debug_output(Source);
			break;
		}
		
	case INSTRUCT_EXIT:
		{
			printf("exit ");
			Value Source = ResolveOpValue (pScript, 0 );
			_debug_output(Source);
			
			break;
		}
		
		//Math Operations
	case INSTRUCT_POW:
	case INSTRUCT_ATAN2:
	case INSTRUCT_MIN:
	case INSTRUCT_MAX:
	case INSTRUCT_HYPOT:
	case INSTRUCT_FMOD:
	case INSTRUCT_DIGIT:
	case INSTRUCT_BINARY:
	case INSTRUCT_CMP:
	case INSTRUCT_CMPE:
	case INSTRUCT_CMPNE:
	case INSTRUCT_CMPG:
	case INSTRUCT_CMPL:
	case INSTRUCT_CMPGE:
	case INSTRUCT_CMPLE:				
		{
			switch ( iOpcode )
			{
			case INSTRUCT_POW:
				printf("pow ");
				break;
			case INSTRUCT_ATAN2:
				printf("atan2 ");
				break;
			case INSTRUCT_MIN:
				printf("min ");
				break;
			case INSTRUCT_MAX:
				printf("max ");
				break;
			case INSTRUCT_HYPOT:
				printf("hypot ");
				break;
			case INSTRUCT_FMOD:
				printf("fmod ");
				break;
			case INSTRUCT_DIGIT:
				printf("digit ");
				break;
			case INSTRUCT_BINARY:
				printf("binary ");
				break;
			case INSTRUCT_CMP:
				printf("cmp ");
				break;
			case INSTRUCT_CMPE:
				printf("cmpe ");
				break;
			case INSTRUCT_CMPNE:
				printf("cmpne ");
				break;
			case INSTRUCT_CMPG:
				printf("cmpg ");
				break;
			case INSTRUCT_CMPL:
				printf("cmpl ");
				break;
			case INSTRUCT_CMPGE:
				printf("cmpge ");
				break;
			case INSTRUCT_CMPLE:
				printf("cmple ");
				break;
			}
			
			// If the comparison evaluated to TRUE, make the jump
			Dest = ResolveOpValue (pScript, 0 );
			Value Source = ResolveOpValue (pScript, 1 );
			Value Source2 = ResolveOpValue (pScript, 2 );
			_debug_output(Dest);
			_debug_output(Source);
			_debug_output(Source2);				
			
			
		}
		break;
		}
}


void CTScriptVMBase::_debug_output(const Value &oVal)
{
	switch(oVal.iType) 
	{
	case OPERAND_TYPE_INT:
		printf("(int)%d ",oVal.iIntLiteral);
		break;
	case OPERAND_TYPE_FLOAT:
		printf("(float)%f ",oVal.fFloatLiteral);
		break;
	case OPERAND_TYPE_STRING:
		printf("(string)%s ",oVal.pstrStringLiteral);
		break;
	case OPERAND_TYPE_ABS_STACK_INDEX:
		printf("(absstk)%d ",oVal.iStackIndex);
		break;
	case OPERAND_TYPE_REL_STACK_INDEX:
		printf("(relstk)%d$%d ",oVal.iStackIndex, oVal.iOffsetIndex);
		break;
	case OPERAND_TYPE_INSTRUCT_INDEX:
		printf("(instr)%d ",oVal.iInstrIndex);
		break;
	case OPERAND_TYPE_FUNC_INDEX:
		printf("(func)%d ",oVal.iFuncIndex);
		break;
	case OPERAND_TYPE_HOST_API_CALL_INDEX:
		printf("(host)%d ",oVal.iHostAPICallIndex);
		break;
	default:
		printf("(null) ");
		break;
	}	
}


/******************************************************************************************
*
*   PassIntParam ()
*
*   Passes an integer parameter from the host to a script function.
*/

void CTScriptVMBase::PassIntParam ( Script *pScript, int iInt )
{
	// Create a Value structure to encapsulate the parameter
	Value Param;
	Param.iType = OPERAND_TYPE_INT;
	Param.iIntLiteral = iInt;
	
	// Push the parameter onto the stack
	Push ( pScript, Param );
}

/******************************************************************************************
*
*   PassFloatParam ()
*
*   Passes a floating-point parameter from the host to a script function.
*/

void CTScriptVMBase::PassFloatParam ( Script *pScript, float fFloat )
{
	// Create a Value structure to encapsulate the parameter
	Value Param;
	Param.iType = OPERAND_TYPE_FLOAT;
	Param.fFloatLiteral = fFloat;
	
	// Push the parameter onto the stack
	Push ( pScript, Param );
}

/******************************************************************************************
*
*   PassStringParam ()
*
*   Passes a string parameter from the host to a script function.
*/

void CTScriptVMBase::PassStringParam ( Script *pScript, char * pstrString )
{
	// Create a Value structure to encapsulate the parameter
	Value Param;
	Param.iType = OPERAND_TYPE_STRING;
	Param.pstrStringLiteral = ( char * ) malloc ( strlen ( pstrString ) + 1 );
	strcpy ( Param.pstrStringLiteral, pstrString );
	
	// Push the parameter onto the stack
	Push ( pScript, Param );
}


/******************************************************************************************
*
*   GetFuncIndexByName ()
*
*   Returns the index into the function table corresponding to the specified name.
*/

int CTScriptVMBase::GetFuncIndexByName ( Script *pScript, char * pstrName )
{
	// Loop through each function and look for a matching name
	int iSize = pScript->m_oFuncTable.iSize;

	for ( int iFuncIndex = 0; iFuncIndex < iSize; ++ iFuncIndex )
	{
		// If the names match, return the index
		
		if ( stricmp ( pstrName, pScript->m_oFuncTable.m_pFuncs [ iFuncIndex ].pstrName ) == 0 )
		{
			return iFuncIndex+1;
		}
	}
	
	// A match wasn't found, so return -1
	return -1;
}

/******************************************************************************************
*
*	XS_GetReturnValueAsInt ()
*
*	Returns the last returned value as an integer.
*/

int  CTScriptVMBase::GetReturnValueAsInt ( Script *pScript )
{
	// Make sure the thread index is valid and active
	if ( ! pScript->iIsActive )
	{
		return 1;
	}
	
	// Return _RetVal's integer field
	if (pScript->_RetVal.iType == OPERAND_TYPE_INT)
	{
		return pScript->_RetVal.iIntLiteral;	
	}
	else if (pScript->_RetVal.iType == OPERAND_TYPE_STRING)
	{
		return atol(pScript->_RetVal.pstrStringLiteral);
	}
	else if (pScript->_RetVal.iType == OPERAND_TYPE_FLOAT)
	{
		return (int)pScript->_RetVal.fFloatLiteral;
	}
	else
	{
		return 1;
	}
}

/******************************************************************************************
*
*	XS_GetReturnValueAsFloat ()
*
*	Returns the last returned value as an float.
*/

float CTScriptVMBase::GetReturnValueAsFloat ( Script *pScript )
{
	// Make sure the thread index is valid and active
	if ( ! pScript->iIsActive )
	{
		return 0;
	}
	
	// Return _RetVal's integer field
	return pScript->_RetVal.fFloatLiteral;
}


/******************************************************************************************
*
*	XS_GetReturnValueAsString ()
*
*	Returns the last returned value as an string.
*/

char* CTScriptVMBase::GetReturnValueAsString ( Script *pScript )
{
	// Make sure the thread index is valid and active
	if ( ! pScript->iIsActive )
	{
		return 0;
	}
	
	// Return _RetVal's integer field
	return pScript->_RetVal.pstrStringLiteral;
}

void CTScriptVMBase::ToString( Script *pScript, int iParamIndex, char *pszBuffer )
{
	RuntimeStack &oStack = pScript->Stack;

	// Get the current top element
	int iTopIndex = oStack.iTopIndex;
	Value *pParam = &oStack.pElmnts [ iTopIndex - ( iParamIndex + 1 ) ];

	switch (pParam->iType )
	{
	case OPERAND_TYPE_INT:// It's an integer, so return it as-is
		itoa(pParam->iIntLiteral, pszBuffer, 10);
		break;

	case OPERAND_TYPE_FLOAT:// It's a float, so cast it to an integer
		sprintf(pszBuffer, "%f", pParam->fFloatLiteral);
		break;

	case OPERAND_TYPE_STRING:// It's a string, so convert it to an integer
		strcpy(pszBuffer, pParam->pstrStringLiteral );
		break;

	default:// Anything else is invalid
		break;
	}
}

/******************************************************************************************
*
*   XS_GetParamAsInt ()
*
*   Returns the specified integer parameter to a host API function.
*/

int   CTScriptVMBase::GetParamAsInt ( Script *pScript, int iParamIndex )
{
	RuntimeStack &oStack = pScript->Stack;

	// Get the current top element
	int iTopIndex = oStack.iTopIndex;
	Value Param = oStack.pElmnts [ iTopIndex - ( iParamIndex + 1 ) ];
	
	// Coerce the top element of the stack to an integer
	return CoerceValueToInt ( Param );
}

/******************************************************************************************
*
*   XS_GetParamAsFloat ()
*
*   Returns the specified floating-point parameter to a host API function.
*/

float CTScriptVMBase::GetParamAsFloat( Script *pScript, int iParamIndex )
{
	RuntimeStack &oStack = pScript->Stack;
	
	// Get the current top element
	int iTopIndex = oStack.iTopIndex;
	Value Param = oStack.pElmnts [ iTopIndex - ( iParamIndex + 1 ) ];
	
	// Coerce the top element of the stack to an integer
	return CoerceValueToFloat ( Param );
}

char* CTScriptVMBase::GetParamAsString ( Script *pScript, int iParamIndex )
{
	RuntimeStack &oStack = pScript->Stack;
	
	// Get the current top element
	int iTopIndex = oStack.iTopIndex;
	Value Param = oStack.pElmnts [ iTopIndex - ( iParamIndex + 1 ) ];
	
	// Coerce the top element of the stack to an integer
	return CoerceValueToString ( Param );	
}

void CTScriptVMBase::FreeStackWhenReturn( Script *pScript, int iParamCount )
{
	long nIndex = pScript->Stack.iTopIndex;

	while (iParamCount > 0)
	{
		FreeValue(pScript->Stack.pElmnts[nIndex], OPERAND_TYPE_NULL);
		iParamCount--;
	}
}

/******************************************************************************************
*
*   XS_ReturnFromHost ()
*
*   Returns from a host API function.
*/

void CTScriptVMBase::ReturnFromHost ( Script *pScript, int iParamCount )
{
	FreeStackWhenReturn(pScript, iParamCount);
	pScript->Stack.iTopIndex -= iParamCount;	
}

/******************************************************************************************
*
*   XS_ReturnIntFromHost ()
*
*   Returns an integer from a host API function.
*/

void CTScriptVMBase::ReturnIntFromHost ( Script *pScript, int iParamCount, int iInt )
{
	FreeStackWhenReturn(pScript, iParamCount);
	// Clear the parameters off the stack
	pScript->Stack.iTopIndex -= iParamCount;
	
	// Put the return value and type in _RetVal
	FreeValue(pScript->_RetVal);
	pScript->_RetVal.iType = OPERAND_TYPE_INT;
	pScript->_RetVal.iIntLiteral = iInt;
}

/******************************************************************************************
*
*   XS_ReturnFloatFromHost ()
*
*   Returns a float from a host API function.
*/

void CTScriptVMBase::ReturnFloatFromHost ( Script *pScript, int iParamCount, float fFloat )
{
	FreeStackWhenReturn(pScript, iParamCount);
	// Clear the parameters off the stack
	pScript->Stack.iTopIndex -= iParamCount;
	
	// Put the return value and type in _RetVal
	FreeValue(pScript->_RetVal);
	pScript->_RetVal.iType = OPERAND_TYPE_FLOAT;
	pScript->_RetVal.fFloatLiteral = fFloat;
}

/******************************************************************************************
*
*   XS_ReturnStringFromHost ()
*
*   Returns a string from a host API function.
*/

void CTScriptVMBase::ReturnStringFromHost ( Script *pScript, int iParamCount, const char * pstrString )
{
	FreeStackWhenReturn(pScript, iParamCount);
	// Clear the parameters off the stack
	pScript->Stack.iTopIndex -= iParamCount;
	
	// Put the return value and type in _RetVal
	Value ReturnValue;
	ReturnValue.iType = OPERAND_TYPE_STRING;
	ReturnValue.pstrStringLiteral = (char*)pstrString;

	CopyValue ( & pScript->_RetVal, ReturnValue );	
}



//////////////////////////////////////////////////////////////////////////
//Host API

void CTScriptVMBase::RegisterHostAPIFuncs()
{
	RegisterHostAPIFunc (-1, "strformat", xvm_str_format );
	RegisterHostAPIFunc (-1, "logprint", xvm_logprint );
	RegisterHostAPIFunc (-1, "tostring", xvm_tostring );
	RegisterHostAPIFunc (-1, "strlength", xvm_strlength);
	RegisterHostAPIFunc (-1, "str_char_to_utf8", xvm_str_to_utf8);
	//RegisterHostAPIFunc (-1, "abs", xvm_abs );
}

void CTScriptVMBase::SerializeHostAPIFuncs(CStringSerializeBuffer &oBuffer)
{
	for ( int iCurrHostAPIFunc = 0; iCurrHostAPIFunc < MAX_HOST_API_SIZE; ++ iCurrHostAPIFunc )
	{
		// If the current index is free, use it
		if ( g_HostAPI [ iCurrHostAPIFunc ].iIsActive )
		{
			oBuffer << "host ";
			oBuffer << g_HostAPI [ iCurrHostAPIFunc ].pstrName;
			oBuffer << "();\r\n";
		}
	}
}

