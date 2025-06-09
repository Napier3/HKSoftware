// TScriptVMBase.h: interface for the CTScriptVMBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSCRIPTVMBASE_H__4F93ED95_A4C8_4824_83A8_C6200408C7FE__INCLUDED_)
#define AFX_TSCRIPTVMBASE_H__4F93ED95_A4C8_4824_83A8_C6200408C7FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

#include "TAsmGlobal.h"
#include "VmHostGlobalApi.h"
#include "../BaseClass/StringSerializeBuffer.h"
#include "../BaseClass/WSerializeBuff.h"

// The following Windows-specific includes are only here to implement GetCurrTime (); these
// can be replaced when implementing the XVM on non-Windows platforms.

#define WIN32_LEAN_AND_MEAN
// #include <windows.h>

// ---- Script Loading Error Codes --------------------------------------------------------

#define TS_LOAD_OK					    0		// Load successful
#define TS_LOAD_ERROR_FILE_IO  	        1		// File I/O error (most likely a file
// not found error
#define TS_LOAD_ERROR_INVALID_XSE	    2		// Invalid .XSE structure
#define TS_LOAD_ERROR_UNSUPPORTED_VERS	3		// The format version is unsupported
#define TS_LOAD_ERROR_OUT_OF_MEMORY	    4		// Out of memory
#define TS_LOAD_ERROR_OUT_OF_THREADS	5		// Out of threads
#define TS_LOAD_ERROR_FILE_DATA_INVALID	6		// File data invalid

// ---- Threading -------------------------------------------------------------------------

#define TS_THREAD_PRIORITY_USER         0       // User-defined priority
#define TS_THREAD_PRIORITY_LOW          1       // Low priority
#define TS_THREAD_PRIORITY_MED          2       // Medium priority
#define TS_THREAD_PRIORITY_HIGH         3       // High priority

#define TS_INFINITE_TIMESLICE          -1       // Allows a thread to run indefinitely

// ---- The Host API ----------------------------------------------------------------------

#define TS_GLOBAL_FUNC                 -1       // Flags a host API function as being

// ---- Data Structures -----------------------------------------------------------------------
typedef void (HostAPIFuncPntr ) ( LPVOID pXvm );  // Host API function pointer


// ---- Constants -----------------------------------------------------------------------------

// ---- Script Loading --------------------------------------------------------------------

#define EXEC_FILE_EXT			    ".tse"	    // Executable file extension

// static const char* TSE_ID_STRING              = "TSE0";      // Used to validate an .XSE executable

#define MAX_THREAD_COUNT		    1024        // The maximum number of scripts that
// can be loaded at once. Change this
// to support more or less.

// ---- Operand/Value Types ---------------------------------------------------------------
#include "TAsmGlobal.h"
//In TasmGlobal.h
// #define OPERAND_TYPE_NULL                -1          // Uninitialized/Null data
// #define OPERAND_TYPE_INT                 0           // Integer literal value
// #define OPERAND_TYPE_FLOAT               1           // Floating-point literal value
// #define OPERAND_TYPE_STRING		         2           // String literal value
// #define OPERAND_TYPE_ABS_STACK_INDEX     3           // Absolute array index
// #define OPERAND_TYPE_REL_STACK_INDEX     4           // Relative array index
// #define OPERAND_TYPE_INSTRUCT_INDEX      5           // Instruction index
// #define OPERAND_TYPE_FUNC_INDEX          6           // Function index
// #define OPERAND_TYPE_HOST_API_CALL_INDEX 7           // Host API call index
// #define OPERAND_TYPE_REG                 8           // Register
// 
// #define OPERAND_TYPE_STACK_BASE_MARKER   9           // Marks a stack base

// ---- Instruction Opcodes ---------------------------------------------------------------

#define INSTRUCT_MOV                   0

#define INSTRUCT_ADD                   1
#define INSTRUCT_SUB                   2
#define INSTRUCT_MUL                   3
#define INSTRUCT_DIV                   4
#define INSTRUCT_MOD                   5
#define INSTRUCT_EXP                   6
#define INSTRUCT_NEG                   7
#define INSTRUCT_INC                   8
#define INSTRUCT_DEC                   9

#define INSTRUCT_AND                   10
#define INSTRUCT_OR                    11
#define INSTRUCT_XOR                   12
#define INSTRUCT_NOT                   13
#define INSTRUCT_SHL                   14
#define INSTRUCT_SHR                   15

#define INSTRUCT_CONCAT                16
#define INSTRUCT_GETCHAR               17
#define INSTRUCT_SETCHAR               18

#define INSTRUCT_JMP                   19
#define INSTRUCT_JE                    20
#define INSTRUCT_JNE                   21
#define INSTRUCT_JG                    22
#define INSTRUCT_JL                    23
#define INSTRUCT_JGE                   24
#define INSTRUCT_JLE                   25

#define INSTRUCT_PUSH                  26
#define INSTRUCT_POP                   27

#define INSTRUCT_CALL                  28
#define INSTRUCT_RET                   29
#define INSTRUCT_CALLHOST              30

#define INSTRUCT_PAUSE                 31
#define INSTRUCT_EXIT                  32

//math instruct 
#define INSTRUCT_ABS                   33     //abs    dest, s1
#define INSTRUCT_POW                   34     //pow    dest, s1, s2
#define INSTRUCT_SQRT                  35     //sqrt   dest, s1
#define INSTRUCT_LOG10                 36     //log10  dest, s1
#define INSTRUCT_LOG                   37     //log    dest, s1
#define INSTRUCT_SIN                   38     //sin    dest, s1
#define INSTRUCT_COS                   39     //cos    dest, s1
#define INSTRUCT_TAN                   40     //tan    dest, s1
#define INSTRUCT_CTAN                  41     //ctan   dest, s1
#define INSTRUCT_ASIN                  42     //sain   dest, s1
#define INSTRUCT_ACOS                  43     //acos   dest, s1
#define INSTRUCT_ATAN                  44     //atan   dest, s1
#define INSTRUCT_ATAN2                 45     //atan2  dest, s1, s2
#define INSTRUCT_MIN                   46     //min    dest, s1, s2
#define INSTRUCT_MAX                   47     //max    dest, s1, s2
#define INSTRUCT_CEIL                  48     //ceil   dest, s1
#define INSTRUCT_FLOOR                 49     //floor  dest, s1
#define INSTRUCT_HYPOT                 50     //hypot  dest, s1, s2
#define INSTRUCT_FMOD                  51     //fmod   dest, s1, s2
#define INSTRUCT_DIGIT                 52     //digit  dest, s1, s2
#define INSTRUCT_BINARY                53     //binary dest, s1, s2
#define INSTRUCT_ATOF                  54     //atof   dest, s1
#define INSTRUCT_ATOL                  55     //atol   dest, s1
#define INSTRUCT_FTOA                  56     //ftoa   dest, s1
#define INSTRUCT_LTOA                  57     //ltoa   dest, s1
#define INSTRUCT_CMP                   58     //cmp    dest, s1, s2
#define INSTRUCT_CMPE                  59     //cmpe   dest, s1, s2
#define INSTRUCT_CMPNE                 60     //cmpne  dest, s1, s2
#define INSTRUCT_CMPG                  61     //cmpg   dest, s1, s2
#define INSTRUCT_CMPL                  62     //cmpl   dest, s1, s2
#define INSTRUCT_CMPGE                 63     //cmpge  dest, s1, s2
#define INSTRUCT_CMPLE                 64     //cmple  dest, s1, s2

// ---- Stack -----------------------------------------------------------------------------

#define DEF_STACK_SIZE			    1024	    // The default stack size

// ---- Coercion --------------------------------------------------------------------------

#define MAX_COERCION_STRING_SIZE    64          // The maximum allocated space for a
// string coercion

// ---- Multithreading --------------------------------------------------------------------

#define THREAD_MODE_MULTI           0           // Multithreaded execution
#define THREAD_MODE_SINGLE          1           // Single-threaded execution

#define THREAD_PRIORITY_DUR_LOW     20          // Low-priority thread timeslice
#define THREAD_PRIORITY_DUR_MED     40          // Medium-priority thread timeslice
#define THREAD_PRIORITY_DUR_HIGH    80          // High-priority thread timeslice

// ---- The Host API ----------------------------------------------------------------------

#define MAX_HOST_API_SIZE           1024        // Maximum number of functions in the
// host API

// ---- Functions -------------------------------------------------------------------------

#define MAX_NAME_SIZE               256         // Maximum size of a function's name

#define SCRIPT_STATE_NORMAL         0
#define SCRIPT_STATE_EXIT           1
#define SCRIPT_STATE_ERROR          2

#define XVM_RETURN_BUFFER_LEN  1024
#define XVM_RETURN_BUFFER_COUNT  10

class CTScriptVMBase  
{
public:
	CTScriptVMBase();
	virtual ~CTScriptVMBase();
	void Init();
	void FreeBase();

	//关联和绑定的数据对象
	LPVOID m_pRefData;

	char *GetChReurn()	{	m_chReturn[m_nChReturnIndex][0] = 0;	return m_chReturn[m_nChReturnIndex];	}
	LPVOID GetRefData()	{	return m_pRefData;	}
	void SetRefData(LPVOID pRefData)	{	m_pRefData = pRefData;	}
	
	void IncreaseChReturn()
	{
		m_nChReturnIndex++;
		if (m_nChReturnIndex >= XVM_RETURN_BUFFER_COUNT)
		{
			m_nChReturnIndex = 0;
		}
	}

protected:
	//用于返回字符串的临时缓存
	char m_chReturn[XVM_RETURN_BUFFER_COUNT][XVM_RETURN_BUFFER_LEN];
	long m_nChReturnIndex;
	
	// ---- Data Structures -----------------------------------------------------------------------
	
	// ---- Runtime Value ---------------------------------------------------------------------
	typedef struct _Value							// A runtime value
	{
		int iType;                                  // Type
		union                                       // The value
		{
			int iIntLiteral;                        // Integer literal
			float fFloatLiteral;                    // Float literal
			char * pstrStringLiteral;				// String literal
			int iStackIndex;                        // Stack Index
			int iInstrIndex;                        // Instruction index
			int iFuncIndex;                         // Function index
			int iHostAPICallIndex;                  // Host API Call index
			int iReg;                               // Register code
		};
		int iOffsetIndex;                           // Index of the offset
		int nIsRef;                                 // Is Ref Value for string 2023-12-16  lijunqing

// 	public:
		_Value()
		{
			iType = OPERAND_TYPE_NULL;
			pstrStringLiteral = NULL;
			iOffsetIndex = 0;
			nIsRef = 0;
		}
	}	Value;
	
	// ---- Runtime Stack ---------------------------------------------------------------------
	typedef struct _RuntimeStack					// A runtime stack
	{
		Value * pElmnts;							// The stack elements
		int iSize;									// The number of elements in the stack
		
		int iTopIndex;								// The top index
		int iFrameIndex;                            // Index of the top of the current
		// stack frame.
	}	RuntimeStack;
	
	// ---- Functions -------------------------------------------------------------------------
	typedef struct _Func							// A function
	{
		int iEntryPoint;							// The entry point
		unsigned char m_ucParamCount;							// The parameter count
		int iLocalDataSize;							// Total size of all local data
		int iStackFrameSize;						// Total size of the stack frame
		char pstrName [ MAX_NAME_SIZE + 1 ];   // The function's name
	}Func;
	
    // ---- Instructions ----------------------------------------------------------------------
	typedef struct _Instr                           // An instruction
	{
		unsigned short iOpcode;                                // The opcode
		int iOpCount;                               // The number of operands
		Value * pOpList;                            // The operand list
	}Instr;
	
	typedef struct _InstrStream                     // An instruction stream
	{
		Instr * m_pInstrs;							// The instructions themselves
		int iSize;                                  // The number of instructions in the
		// stream
		int iCurrInstr;                             // The instruction pointer
	}	InstrStream;
	
    // ---- Function Table --------------------------------------------------------------------
	typedef struct _FuncTable                       // A function table
	{
		Func* m_pFuncs;                              // Pointer to the function array
		int iSize;                                  // The number of functions in the array
	}	FuncTable;
	
	// ---- Host API Call Table ---------------------------------------------------------------
	typedef struct _HostAPICallTable				// A host API call table
	{
		char ** m_ppstrCalls;							// Pointer to the call array
		int iSize;									// The number of calls in the array
	}	HostAPICallTable;
	
	typedef struct _ExportSymbol
	{
		char *pstrName;                         // The symbol's name
		int  iStackIndex;
	}  ExportSymbol;
	typedef struct _ExportSymbols
	{
		ExportSymbol *m_pExportSymbols;   // The function's name
		int  iSize;
	}  ExportSymbols;
	
	// ---- Scripts ---------------------------------------------------------------------------
	typedef struct _Script							// Encapsulates a full script
	{
		int iIsActive;								// Is this script structure in use?
		
		// Header data
		int iGlobalDataSize;						// The size of the script's global data
		int iIsMainFuncPresent;                     // Is _Main () present?
		int iMainFuncIndex;							// _Main ()'s function index
		
		// Runtime tracking
		int iIsRunning;								// Is the script running?
		int iIsPaused;								// Is the script currently paused?
		unsigned int uiPauseEndTime;			    // If so, when should it resume?
		int m_iThreadIndex;                         // Script thread index
		int m_iScriptState;                         //Script state:0=normal; 1=error;
		
		// Threading
		unsigned int uiTimesliceDuration;                          // The thread's timeslice duration
		
		// Register file
		Value _RetVal;								// The _RetVal register
		
		// Script data
		InstrStream m_oInstrStream;                    // The instruction stream
		RuntimeStack Stack;                         // The runtime stack
		FuncTable m_oFuncTable;                        // The function table
		HostAPICallTable m_oHostAPICallTable;			// The host API call table
		ExportSymbols m_oExportSymbols;
	}	Script;
	
    // ---- Host API --------------------------------------------------------------------------
	typedef struct _HostAPIFunc                     // Host API function
	{
		int iIsActive;                              // Is this slot in use?
		
		int iThreadIndex;                           // The thread to which this function
		// is visible
		char * pstrName;                            // The function name
		HostAPIFuncPntr *fnFunc;                     // Pointer to the function definition
	} HostAPIFunc;

	// ---- The Host API ----------------------------------------------------------------------
	HostAPIFunc g_HostAPI [ MAX_HOST_API_SIZE ];    // The host API
	
protected:
	int Load_ScriptFileHead(CWSerializeBuff  &oWBuffer);
	int Load_ScriptHeader(CWSerializeBuff  &oWBuffer, Script *pScript);
	int Load_Instructions(CWSerializeBuff  &oWBuffer, Script *pScript);
	int Load_StringTable(CWSerializeBuff  &oWBuffer, Script *pScript);
	int Load_FuncTable(CWSerializeBuff  &oWBuffer, Script *pScript);
	int Load_HostAPICallTable(CWSerializeBuff  &oWBuffer, Script *pScript);
	int Load_ExportSymbols(CWSerializeBuff  &oWBuffer, Script *pScript);

public:
	void InitScript(Script *pScript);
	int  LoadScript ( char *pstrFilename, Script *pScript, int iThreadTimeslice );
	int  LoadScriptFromBuffer ( char *pBuffer, long nBufferLen, Script *pScript, int iThreadTimeslice );
	int  LoadScriptFromBuffer ( CWSerializeBuff  &oWBuffer, Script *pScript, int iThreadTimeslice );
	void UnloadScript ( Script *pScript );
	void ResetScript ( Script *pScript );
	void RunScript ( Script *pScript, unsigned int uiTimesliceDuration , unsigned int &uiCurrTime, int &iExitExecLoop);
	void RegisterHostAPIFunc ( int iThreadIndex, char * pstrName, HostAPIFuncPntr *fnFunc );
	
	ExportSymbol* FindExportSymbol( Script *pScript, const char* pstrName);
	ExportSymbol* FindExportSymbol( Script *pScript, int iIndex);
	
protected:
	void _debug_output(Script *pScript, Instr *pInstr);
	void _debug_output(const Value &oVal);
	
	//export symbols////////////////////////////////////////////////////////////////////////
	int  GetExportValueCount ( Script *pScript);
	bool GetExportValue ( Script *pScript , const char* pstrName, int &iValue);
	bool GetExportValue ( Script *pScript , const char* pstrName, float &fValue);
	bool GetExportValue ( Script *pScript , const char* pstrName, char* &pstrValue);
	bool GetExportValue ( Script *pScript , int iIndex, char* pstrName, int &iValue);
	bool GetExportValue ( Script *pScript , int iIndex, char* pstrName, float &fValue);
	bool GetExportValue ( Script *pScript , int iIndex, char* pstrName, char* &pstrValue);
	bool IsExportValueInt ( Script *pScript , const char* pstrName);
	bool IsExportValueFloat ( Script *pScript , const char* pstrName);
	bool IsExportValueString ( Script *pScript , const char* pstrName);
	
	bool SetExportValue ( Script *pScript , const char* pstrName, int &iValue);
	bool SetExportValue ( Script *pScript , const char* pstrName, float &fValue);
	bool SetExportValue ( Script *pScript , const char* pstrName, char* &pstrValue);
	bool SetExportValue ( Script *pScript , int iIndex, int &iValue);
	bool SetExportValue ( Script *pScript , int iIndex, float &fValue);
	bool SetExportValue ( Script *pScript , int iIndex, char* &pstrValue);
	bool IsExportValueInt ( Script *pScript , int iIndex);
	bool IsExportValueFloat ( Script *pScript , int iIndex);
	bool IsExportValueString ( Script *pScript , int iIndex);
	
protected:
	int ResolveStackIndex( Script *pScript, int iIndex );
	BOOL IsValidThreadIndex( int iIndex );
	BOOL IsThreadActive( Script *pScript, int iIndex );
	
	// ---- Operand Interface -----------------------------------------------------------------
	int CoerceValueToInt ( Value &Val );
	float CoerceValueToFloat ( Value &Val );
	char* CoerceValueToString ( Value &Val );
	char* CoerceValueToString ( Value &Val , char *pValue);
	void CopyValue ( Value * pDest, Value &Source, BOOL bFree=TRUE );
	void ChangeType(Value * pDest, Value &Source);
	int  GetOpType ( Script *pScript, int iOpIndex );
	int ResolveOpStackIndex (Script *pScript,  int iOpIndex );
	int ResolveOpStackIndex ( Script *pScript,  Value &val );
	Value ResolveOpValue ( Script *pScript, int iOpIndex );
	int ResolveOpType ( Script *pScript, int iOpIndex );
	int ResolveOpAsInt ( Script *pScript, int iOpIndex );
	float ResolveOpAsFloat ( Script *pScript, int iOpIndex );
	char * ResolveOpAsString ( Script *pScript, int iOpIndex );
	int ResolveOpAsInstrIndex ( Script *pScript, int iOpIndex );
	int ResolveOpAsFuncIndex ( Script *pScript, int iOpIndex );
	char * ResolveOpAsHostAPICall ( Script *pScript, int iOpIndex );
	Value * ResolveOpPntr ( Script *pScript, int iOpIndex );
	void ResolveOpPntr ( Script *pScript, int iOpIndex, Value &Val );
	void ResolveOpPntr ( Script *pScript, int iOpIndex, int iCharIndex, char ch );
	
	// ---- Runtime Stack Interface -----------------------------------------------------------
	Value GetStackValue ( Script *pScript, int iIndex );
	void SetStackValue ( Script *pScript, int iIndex, Value Val );
	void Push ( Script *pScript, Value &Val );
	Value Pop ( Script *pScript );
	void PushFrame ( Script *pScript, int iSize );
	void PopFrame ( Script *pScript, int iSize );

	// ---- Function Table Interface ----------------------------------------------------------
	Func GetFunc ( Script *pScript, int iIndex );
	
	// ---- Host API Call Table Interface -----------------------------------------------------
	char * GetHostAPICall ( Script *pScript, int iIndex );
	
	// ---- Time Abstraction ------------------------------------------------------------------
	int GetCurrTime ();
	
	// ---- Functions -------------------------------------------------------------------------
	void CallFunc ( Script *pScript, int iFuncIndex );
	
	void PassIntParam ( Script *pScript, int iInt );
	void PassFloatParam ( Script *pScript, float fFloat );
	void PassStringParam ( Script *pScript, char * pstrString );
	int  GetFuncIndexByName ( Script *pScript, char * pstrName );
	int  GetReturnValueAsInt ( Script *pScript );
	float GetReturnValueAsFloat ( Script *pScript );
	char* GetReturnValueAsString ( Script *pScript );
	
	void ToString( Script *pScript, int iParamIndex, char *pszBuffer );
	int   GetParamAsInt ( Script *pScript, int iParamIndex );
	float GetParamAsFloat( Script *pScript, int iParamIndex );
	char* GetParamAsString ( Script *pScript, int iParamIndex );
	
	void ReturnFromHost ( Script *pScript, int iParamCount );
	void ReturnIntFromHost ( Script *pScript, int iParamCount, int iInt );
	void ReturnFloatFromHost ( Script *pScript, int iParamCount, float fFloat );
	void ReturnStringFromHost ( Script *pScript, int iParamCount, const char * pstrString );
	void FreeStackWhenReturn( Script *pScript, int iParamCount );
	
	//Free Value
	void FreeValue(Value &val, int iNewType = OPERAND_TYPE_FLOAT)
	{
		if (val.iType == OPERAND_TYPE_STRING)
		{
			if (val.nIsRef == 0)
			{//2023-12-16  lijunqing
				free(val.pstrStringLiteral);
			}

			val.nIsRef = 0;
			val.pstrStringLiteral = NULL;
		}
		
		val.iType = iNewType;
		val.fFloatLiteral = 0;
	}
	
	void ChangeValue(Value &val, int iVal)
	{
		if (val.iType == OPERAND_TYPE_STRING)
		{
			if (val.nIsRef == 0)
			{//2023-12-16  lijunqing
				free(val.pstrStringLiteral);
			}

			val.nIsRef = 0;
			val.pstrStringLiteral = NULL;
		}
		
		val.iType = OPERAND_TYPE_INT;
		val.iIntLiteral = iVal;
	}
	
	void ChangeValue(Value &val, float fVal)
	{
		if (val.iType == OPERAND_TYPE_STRING)
		{
			if (val.nIsRef == 0)
			{//2023-12-16  lijunqing
				free(val.pstrStringLiteral);
			}

			val.nIsRef = 0;
			val.pstrStringLiteral = NULL;
		}
		
		val.iType = OPERAND_TYPE_FLOAT;
		val.fFloatLiteral = fVal;
	}
	
	
	void ChangeValue(Value &val, char *pstrVal)
	{
		if (val.iType == OPERAND_TYPE_STRING)
		{
			if (val.nIsRef == 0)
			{//2023-12-16  lijunqing
				free(val.pstrStringLiteral);
			}

			val.nIsRef = 0;
			val.pstrStringLiteral = NULL;
		}
		
		int nLen = strlen(pstrVal);
		val.iType = OPERAND_TYPE_STRING;
		val.pstrStringLiteral = new char [nLen+1];
		strcpy(val.pstrStringLiteral, pstrVal);
	}
	
	void CopyValue(Value &val, const char *pstrVal)
	{
		if (pstrVal != NULL)
		{
			int nLen = strlen(pstrVal);
			val.iType = OPERAND_TYPE_STRING;
			val.pstrStringLiteral = new char [nLen+1];
			strcpy(val.pstrStringLiteral, pstrVal);
		}
	}
	
	bool IsValueNumber(Value &val)
	{
		return (val.iType == OPERAND_TYPE_INT || val.iType == OPERAND_TYPE_FLOAT);
	}
	bool IsValueString(Value &val)
	{
		return (val.iType == OPERAND_TYPE_STRING);
	}
	
//////////////////////////////////////////////////////////////////////////
//Host API
public:
	virtual void RegisterHostAPIFuncs();
	virtual void SerializeHostAPIFuncs(CStringSerializeBuffer &oBuffer);
};


/******************************************************************************************
*
*	ResolveStackIndex ()
*
*	Resolves a stack index by translating negative indices relative to the top of the
*	stack, to positive ones relative to the bottom.
*/
inline int CTScriptVMBase::ResolveStackIndex( Script *pScript, int iIndex )
{
	return ( iIndex < 0 ? iIndex += pScript->Stack.iFrameIndex : iIndex );
}

inline BOOL CTScriptVMBase::IsValidThreadIndex( int iIndex )
{
	return ( iIndex < 0 || iIndex > MAX_THREAD_COUNT ? FALSE : TRUE );
}

inline BOOL CTScriptVMBase::IsThreadActive( Script *pScript, int iIndex )
{
	return ( IsValidThreadIndex ( iIndex ) && pScript->iIsActive ? TRUE : FALSE );
}


/******************************************************************************************
*
*	GetOpType ()
*
*	Returns the type of the specified operand in the current instruction.
*/
inline int CTScriptVMBase::GetOpType ( Script *pScript, int iOpIndex )
{
	// Get the current instruction
	int iCurrInstr = pScript->m_oInstrStream.iCurrInstr;
	
	// Return the type
	return pScript->m_oInstrStream.m_pInstrs [ iCurrInstr ].pOpList [ iOpIndex ].iType;
}
/******************************************************************************************
*
*   ResolveOpStackIndex ()
*
*   Resolves an operand's stack index, whether it's absolute or relative.
*/
inline int CTScriptVMBase::ResolveOpStackIndex ( Script *pScript, int iOpIndex )
{
	// Get the current instruction
	int iCurrInstr = pScript->m_oInstrStream.iCurrInstr;
	
	// Get the operand type type
	Value OpValue = pScript->m_oInstrStream.m_pInstrs [ iCurrInstr ].pOpList [ iOpIndex ];
	
	// Resolve the stack index based on its type
	switch ( OpValue.iType )
	{
		// It's an absolute index so return it as-is
	case OPERAND_TYPE_ABS_STACK_INDEX:
		return OpValue.iStackIndex;
		
		// It's a relative index so resolve it
	case OPERAND_TYPE_REL_STACK_INDEX:
		{
			// First get the base index
			int iBaseIndex = OpValue.iStackIndex;
			
			// Now get the index of the variable
			int iOffsetIndex = OpValue.iOffsetIndex;
			
			// Get the variable's value
			Value StackValue = GetStackValue ( pScript, iOffsetIndex );
			
			// Now add the variable's integer field to the base index to produce the
			// absolute index
			return iBaseIndex - StackValue.iIntLiteral;
		}
		
		// Return zero for everything else, but we shouldn't encounter this case
	default:
		return 0;
	}
}

inline int CTScriptVMBase::ResolveOpStackIndex ( Script *pScript, Value &val )
{
	// Resolve the stack index based on its type
	switch ( val.iType )
	{
		// It's an absolute index so return it as-is
	case OPERAND_TYPE_ABS_STACK_INDEX:
		return val.iStackIndex;
		
		// It's a relative index so resolve it
	case OPERAND_TYPE_REL_STACK_INDEX:
		{
			// First get the base index
			int iBaseIndex = val.iStackIndex;
			
			// Now get the index of the variable
			int iOffsetIndex = val.iOffsetIndex;
			
			// Get the variable's value
			Value StackValue = GetStackValue ( pScript, iOffsetIndex );
			
			// Now add the variable's integer field to the base index to produce the
			// absolute index
			return iBaseIndex + StackValue.iIntLiteral;
		}
		
		// Return zero for everything else, but we shouldn't encounter this case
	default:
		return 0;
	}
}
/******************************************************************************************
*
*	ResolveOpValue ()
*
*	Resolves an operand and returns it's associated Value structure.
*/

inline CTScriptVMBase::Value CTScriptVMBase::ResolveOpValue (Script *pScript,  int iOpIndex )
{
	// Get the current instruction
	int iCurrInstr = pScript->m_oInstrStream.iCurrInstr;
	
	// Get the operand type
	Value OpValue = pScript->m_oInstrStream.m_pInstrs [ iCurrInstr ].pOpList [ iOpIndex ];
	OpValue.nIsRef = 1; //2023-12-16  lijunqing
	
	// Determine what to return based on the value's type
	switch ( OpValue.iType )
	{
		// It's a stack index so resolve it
	case OPERAND_TYPE_ABS_STACK_INDEX:
	case OPERAND_TYPE_REL_STACK_INDEX:
		{
			// Resolve the index and use it to return the corresponding stack element
			int iAbsIndex = ResolveOpStackIndex ( pScript, iOpIndex );
			OpValue = GetStackValue ( pScript, iAbsIndex );
			OpValue.nIsRef = 1; //2023-12-16  lijunqing
			return OpValue;
		}
		
		// It's in _RetVal
	case OPERAND_TYPE_REG:
		return pScript->_RetVal;
		
		// Anything else can be returned as-is
	default:
		return OpValue;
	}
}

/******************************************************************************************
*
*	ResolveOpType ()
*
*	Resolves the type of the specified operand in the current instruction and returns the
*	resolved type.
*/

inline int CTScriptVMBase::ResolveOpType ( Script *pScript, int iOpIndex )
{
	// Resolve the operand's value
	
	Value OpValue = ResolveOpValue ( pScript, iOpIndex );
	
	// Return the value type
	
	return OpValue.iType;
}

/******************************************************************************************
*
*	ResolveOpAsInt ()
*
*	Resolves and coerces an operand's value to an integer value.
*/

inline int CTScriptVMBase::ResolveOpAsInt (Script *pScript,  int iOpIndex )
{
	// Resolve the operand's value
	CTScriptVMBase::Value OpValue = ResolveOpValue (pScript, iOpIndex );
	
	// Coerce it to an int and return it
	int iInt = CoerceValueToInt ( OpValue );
	return iInt;
}

/******************************************************************************************
*
*	ResolveOpAsFloat ()
*
*	Resolves and coerces an operand's value to a floating-point value.
*/

inline float CTScriptVMBase::ResolveOpAsFloat (Script *pScript,  int iOpIndex )
{
	// Resolve the operand's value
	Value OpValue = ResolveOpValue ( pScript, iOpIndex );
	
	// Coerce it to a float and return it
	float fFloat = CoerceValueToFloat ( OpValue );
	return fFloat;
}

/******************************************************************************************
*
*	ResolveOpAsString ()
*
*	Resolves and coerces an operand's value to a string value, allocating the space for a
*   new string if necessary.
*/

inline char* CTScriptVMBase::ResolveOpAsString ( Script *pScript, int iOpIndex )
{
	// Resolve the operand's value
	Value OpValue = ResolveOpValue ( pScript, iOpIndex );
	
	// Coerce it to a string and return it
	char * pstrString = CoerceValueToString ( OpValue );
	return pstrString;
}

/******************************************************************************************
*
*	ResolveOpAsInstrIndex ()
*
*	Resolves an operand as an intruction index.
*/

inline int CTScriptVMBase::ResolveOpAsInstrIndex (Script *pScript,  int iOpIndex )
{
	// Resolve the operand's value
	Value OpValue = ResolveOpValue ( pScript, iOpIndex );
	
	// Return it's instruction index
	return OpValue.iInstrIndex;
}

/******************************************************************************************
*
*	ResolveOpAsFuncIndex ()
*
*	Resolves an operand as a function index.
*/

inline int CTScriptVMBase::ResolveOpAsFuncIndex (Script *pScript,  int iOpIndex )
{
	// Resolve the operand's value
	Value OpValue = ResolveOpValue ( pScript, iOpIndex );
	
	// Return the function index
	return OpValue.iFuncIndex;
}

/******************************************************************************************
*
*	ResolveOpAsHostAPICall ()
*
*	Resolves an operand as a host API call
*/

inline char* CTScriptVMBase::ResolveOpAsHostAPICall ( Script *pScript, int iOpIndex )
{
	// Resolve the operand's value
	Value OpValue = ResolveOpValue ( pScript, iOpIndex );
	
	// Get the value's host API call index
	int iHostAPICallIndex = OpValue.iHostAPICallIndex;
	
	// Return the host API call
	return GetHostAPICall ( pScript, iHostAPICallIndex );
}

/******************************************************************************************
*
*   ResolveOpPntr ()
*
*   Resolves an operand and returns a pointer to its Value structure.
*/

inline CTScriptVMBase::Value* CTScriptVMBase::ResolveOpPntr ( Script *pScript, int iOpIndex )
{
	// Get the method of indirection
	int iIndirMethod = GetOpType ( pScript, iOpIndex );
	
	// Return a pointer to wherever the operand lies
	switch ( iIndirMethod )
	{
		// It's on the stack
	case OPERAND_TYPE_ABS_STACK_INDEX:
	case OPERAND_TYPE_REL_STACK_INDEX:
		{
			int iStackIndex = ResolveOpStackIndex (pScript, iOpIndex );
			return & pScript->Stack.pElmnts [ ResolveStackIndex ( pScript, iStackIndex ) ];
		}
		
		// It's _RetVal
	case OPERAND_TYPE_REG:
		return & pScript->_RetVal;
	}
	
	// Return NULL for anything else
	return NULL;
}

inline void CTScriptVMBase::ResolveOpPntr ( Script *pScript, int iOpIndex, Value &Val )
{
	Value *Dest = ResolveOpPntr(pScript, iOpIndex);

	if (Dest == NULL)
	{
		//????????????????????????????????????????????? //error process
	}
	else
	{
		FreeValue(*Dest);
		*Dest = Val;
	}
}

inline void CTScriptVMBase::ResolveOpPntr ( Script *pScript, int iOpIndex, int iCharIndex, char ch)
{
	Value *Dest = ResolveOpPntr(pScript, iOpIndex);
	
	if (Dest == NULL)
	{
		//????????????????????????????????????????????? //error process
	}
	else
	{
		int nLen = strlen(Dest->pstrStringLiteral);

		if (iCharIndex >= nLen)
		{
			//????????????????????????????????????????????? //error process
		}
		else
		{
			Dest->pstrStringLiteral[iCharIndex] = ch;
		}
	}
}

/******************************************************************************************
*
*	GetStackValue ()
*
*	Returns the specified stack value.
*/

inline CTScriptVMBase::Value CTScriptVMBase::GetStackValue ( Script *pScript, int iIndex )
{
	// Use ResolveStackIndex () to return the element at the specified index
	return pScript->Stack.pElmnts [ ResolveStackIndex ( pScript, iIndex ) ];
}

/******************************************************************************************
*
*	SetStackValue ()
*
*	Sets the specified stack value.
*/

inline void CTScriptVMBase::SetStackValue ( Script *pScript, int iIndex, Value Val )
{
	// Use ResolveStackIndex () to set the element at the specified index
	//pScript->Stack.pElmnts [ ResolveStackIndex ( pScript, iIndex ) ] = Val;

	iIndex = ResolveStackIndex ( pScript, iIndex );
	CopyValue(pScript->Stack.pElmnts +iIndex, Val);
}

/******************************************************************************************
*
*	Push ()
*
*	Pushes an element onto the stack.
*/

inline void CTScriptVMBase::Push ( Script *pScript, CTScriptVMBase::Value &Val )
{
	// Get the current top element
	int iTopIndex = pScript->Stack.iTopIndex;
	
	// Put the value into the current top index
	CopyValue ( & pScript->Stack.pElmnts [ iTopIndex ], Val );
	
	// Increment the top index
	++ pScript->Stack.iTopIndex;
}

/******************************************************************************************
*
*	Pop ()
*
*	Pops the element off the top of the stack.
*/

inline CTScriptVMBase::Value CTScriptVMBase::Pop ( Script *pScript )
{
	// Decrement the top index to clear the old element for overwriting
	-- pScript->Stack.iTopIndex;
	
	// Get the current top element
	int iTopIndex = pScript->Stack.iTopIndex;
	
	// Use this index to read the top element
	CTScriptVMBase::Value Val;
	CopyValue ( & Val, pScript->Stack.pElmnts [ iTopIndex ] );
	
	// Return the value to the caller
	return Val;
}

/******************************************************************************************
*
*	PushFrame ()
*
*	Pushes a stack frame.
*/

inline void CTScriptVMBase::PushFrame ( Script *pScript, int iSize )
{
	// Increment the top index by the size of the frame
	pScript->Stack.iTopIndex += iSize;
	
	// Move the frame index to the new top of the stack
	pScript->Stack.iFrameIndex = pScript->Stack.iTopIndex;
}

/******************************************************************************************
*
*	PopFrame ()
*
*	Pops a stack frame.
*/

inline void CTScriptVMBase::PopFrame ( Script *pScript, int iSize )
{
	// Decrement the top index by the size of the frame
	// Move the frame index to the new top of the stack
	pScript->Stack.iTopIndex -= iSize;
}

/******************************************************************************************
*
*	GetFunc ()
*
*	Returns the function corresponding to the specified index.
*/

inline CTScriptVMBase::Func CTScriptVMBase::GetFunc ( Script *pScript, int iIndex )
{
	return pScript->m_oFuncTable.m_pFuncs [ iIndex - 1 ];
}

/******************************************************************************************
*
*	GetHostAPICall ()
*
*	Returns the host API call corresponding to the specified index.
*/

inline char* CTScriptVMBase::GetHostAPICall (Script *pScript, int iIndex )
{
	return pScript->m_oHostAPICallTable.m_ppstrCalls [ iIndex ];
}

/******************************************************************************************
*
*   GetCurrTime ()
*
*   Wrapper for the system-dependant method of determining the current time in
*   milliseconds.
*/

inline int CTScriptVMBase::GetCurrTime ()
{
	// This function is currently implemented with the WinAPI function GetTickCount ().
	// Change this line to make it compatible with other systems.
	return GetTickCount ();
}


#endif // !defined(AFX_TSCRIPTVMBASE_H__4F93ED95_A4C8_4824_83A8_C6200408C7FE__INCLUDED_)
