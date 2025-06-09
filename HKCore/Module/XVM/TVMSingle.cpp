// TVMSingle.cpp: implementation of the CTScriptSingleVM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TVMSingle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTScriptSingleVM::CTScriptSingleVM()
{

}

CTScriptSingleVM::~CTScriptSingleVM()
{
	
}

// ---- Function Prototypes -------------------------------------------------------------------
// ---- Main ------------------------------------------------------------------------------

/******************************************************************************************
*
*	TS_Init ()
*
*	Initializes the runtime environment.
*/
void CTScriptSingleVM::TS_Init ()
{
	InitScript(&m_Script);
	
	Init();

	// ---- Set up the threads
	g_iCurrThreadMode = THREAD_MODE_MULTI;
	g_iCurrThread = 0;
}

/******************************************************************************************
*
*	TS_ShutDown ()
*
*	Shuts down the runtime environment.
*/
void CTScriptSingleVM::TS_ShutDown ()
{
	// ---- Unload any scripts that may still be in memory
	TS_UnloadScript (  );
	
	FreeBase();
}


// ---- Script Interface ------------------------------------------------------------------
/******************************************************************************************
*
*	TS_LoadScript ()
*
*	Loads an .XSE file into memory.
*   return current active thread index
*/
int  CTScriptSingleVM::TS_LoadScript ( char *pstrFilename, int iThreadTimeslice )
{
	// ---- Find the next free script index
	return LoadScript(pstrFilename, &m_Script, iThreadTimeslice);
}


int  CTScriptSingleVM::TS_LoadScriptFromBuffer ( char *pBuffer, long nBufferLen, int iThreadTimeslice )
{
	return LoadScriptFromBuffer(pBuffer, nBufferLen, &m_Script, iThreadTimeslice);
}

int  CTScriptSingleVM::TS_LoadScriptFromBuffer ( CWSerializeBuff  &oWBuffer, int iThreadTimeslice )
{
	int iErrorCode = LoadScriptFromBuffer(oWBuffer, &m_Script, iThreadTimeslice);

	if ( iErrorCode != TS_LOAD_OK )
	{
		switch ( iErrorCode )
		{
		case TS_LOAD_ERROR_FILE_IO:
            CLogPrint::LogString(XLOGLEVEL_ERROR, _T("File I/O error") );
			break;

		case TS_LOAD_ERROR_INVALID_XSE:
            CLogPrint::LogString(XLOGLEVEL_ERROR, _T ( "Invalid .XSE file" ));
			break;

		case TS_LOAD_ERROR_UNSUPPORTED_VERS:
            CLogPrint::LogString(XLOGLEVEL_ERROR,  _T ( "Unsupported .XSE version" ));
			break;

		case TS_LOAD_ERROR_OUT_OF_MEMORY:
            CLogPrint::LogString(XLOGLEVEL_ERROR,  _T ( "Out of memory" ));
			break;

		case TS_LOAD_ERROR_OUT_OF_THREADS:
            CLogPrint::LogString(XLOGLEVEL_ERROR, _T ( "Out of threads" ));
			break;

        case TS_LOAD_ERROR_FILE_DATA_INVALID:
            CLogPrint::LogString(XLOGLEVEL_ERROR, _T ( "File data invalid" ));
            break;
        }

		return FALSE;
	}

	return iErrorCode;
}
/******************************************************************************************
*
*	TS_UnloadScript ()
*
*	Unloads a script from memory.
*/

void CTScriptSingleVM::TS_UnloadScript ( )
{
	UnloadScript(&m_Script);
}

/******************************************************************************************
*
*	TS_ResetScript ()
*
*	Resets the script. This function accepts a thread index rather than relying on the
*	currently active thread, because scripts can (and will) need to be reset arbitrarily.
*/

void CTScriptSingleVM::TS_ResetScript ( )
{
	ResetScript(&m_Script);
}

void CTScriptSingleVM::TS_RunScripts ( unsigned int uiTimesliceDuration )
{
	// Begin a loop that runs until a keypress. The instruction pointer has already been
	// initialized with a prior call to ResetScripts (), so execution can begin
	
	// Create a flag that instructions can use to break the execution loop
	int iExitExecLoop = FALSE;
	
	// Create a variable to hold the time at which the main timeslice started
#ifdef _xvm_use_time_
	unsigned int iMainTimesliceStartTime = GetCurrTime ();
#endif
	
	// Create a variable to hold the current time
	unsigned int uiCurrTime;
	
	while ( TRUE )
	{
#ifdef _xvm_use_time_
		if (! (m_Script.iIsActive && m_Script.iIsRunning))
		{
			break;
		}
#endif
		
		// Update the current time
#ifdef _xvm_use_time_
		uiCurrTime = GetCurrTime ();
#endif
		
		RunScript(&m_Script, uiTimesliceDuration, uiCurrTime, iExitExecLoop);

		// If we aren't running indefinitely, check to see if the main timeslice has ended
#ifdef _xvm_use_time_
		if ( uiTimesliceDuration != TS_INFINITE_TIMESLICE )
		{
			if ( uiCurrTime > iMainTimesliceStartTime + uiTimesliceDuration )
			{
				break;
			}
		}
#endif
		
		// Exit the execution loop if the script has terminated
		if ( iExitExecLoop )
		{
			break;
		}
	}
}

/******************************************************************************************
*
*	TS_StartScript ()
*
*   Starts the execution of a script.
*/

void CTScriptSingleVM::TS_StartScript ( )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( 0 ) )
		return;
	
	// Set the thread's execution flag
	m_Script.iIsRunning = TRUE;
	m_Script.iIsActive = TRUE;
	
	// Set the activation time for the current thread to get things rolling
#ifdef _xvm_use_time_
	g_iCurrThreadActiveTime = GetCurrTime ();
#endif
}

/******************************************************************************************
*
*	TS_StopScript ()
*
*   Stops the execution of a script.
*/

void CTScriptSingleVM::TS_StopScript ( )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( 0 ) )
	{
		return;
	}
	
	// Clear the thread's execution flag
	m_Script.iIsRunning = FALSE;
}

/******************************************************************************************
*
*	TS_PauseScript ()
*
*   Pauses a script for a specified duration.
*/

void CTScriptSingleVM::TS_PauseScript (int iDur )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( 0 ) )
		return;
	
	// Set the pause flag
	m_Script.iIsPaused = TRUE;
	
	// Set the duration of the pause
#ifdef _xvm_use_time_
	m_Script.uiPauseEndTime = GetCurrTime () + iDur;	
#endif
}

/******************************************************************************************
*
*	TS_UnpauseScript ()
*
*   Unpauses a script.
*/

void CTScriptSingleVM::TS_UnpauseScript ( )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( 0 ) )
		return;
	
	// Clear the pause flag
	m_Script.iIsPaused = FALSE;
}

/******************************************************************************************
*
*   TS_PassIntParam ()
*
*   Passes an integer parameter from the host to a script function.
*/

void CTScriptSingleVM::TS_PassIntParam (int iInt )
{
	PassIntParam ( &m_Script, iInt );
}

/******************************************************************************************
*
*   TS_PassFloatParam ()
*
*   Passes a floating-point parameter from the host to a script function.
*/

void CTScriptSingleVM::TS_PassFloatParam (float fFloat )
{
	PassFloatParam ( &m_Script, fFloat );
}

/******************************************************************************************
*
*   TS_PassStringParam ()
*
*   Passes a string parameter from the host to a script function.
*/

void CTScriptSingleVM::TS_PassStringParam (char * pstrString )
{
	PassStringParam( &m_Script, pstrString );
}

/******************************************************************************************
*
*   GetFuncIndexByName ()
*
*   Returns the index into the function table corresponding to the specified name.
*/

int CTScriptSingleVM::GetFuncIndexByName (char * pstrName )
{
	return CTScriptVMBase::GetFuncIndexByName(&m_Script, pstrName);
}

/******************************************************************************************
*
*   TS_CallScriptFunc ()
*
*   Calls a script function from the host application.
*/

void CTScriptSingleVM::TS_CallScriptFunc (char * pstrName )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( 0 ) )
		return;

	// Get the function's index based on it's name
	int iFuncIndex = GetFuncIndexByName (  pstrName );
	
	// Make sure the function name was valid
	if ( iFuncIndex == -1 )
	{
		return;
	}
		
	// ---- Calling the function
	
	// Preserve the current state of the VM
	int iPrevThreadMode = g_iCurrThreadMode;
	int iPrevThread = g_iCurrThread;
	
	// Set the threading mode for single-threaded execution
	g_iCurrThreadMode = THREAD_MODE_SINGLE;
	
	// Call the function
	CallFunc ( &m_Script, iFuncIndex );
	
	// Set the stack base
	Value StackBase = GetStackValue ( &m_Script, m_Script.Stack.iTopIndex - 1 );
	StackBase.iType = OPERAND_TYPE_STACK_BASE_MARKER;
	SetStackValue ( &m_Script, m_Script.Stack.iTopIndex - 1, StackBase );
	
  //  CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("TS_RunScripts"));

	// Allow the script code to execute uninterrupted until the function returns
	TS_RunScripts ( TS_INFINITE_TIMESLICE );
	
	// ---- Handling the function return
	// Restore the VM state
	g_iCurrThreadMode = iPrevThreadMode;
	g_iCurrThread = iPrevThread;
}

/******************************************************************************************
*
*   XS_InvokeScriptFunc ()
*
*   Invokes a script function from the host application, meaning the call executes in sync
*   with the script.
*/

void CTScriptSingleVM::TS_InvokeScriptFunc (char * pstrName )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( 0 ) )
		return;
	
	// Get the function's index based on its name
	int iFuncIndex = GetFuncIndexByName ( pstrName );
	
	// Make sure the function name was valid
	if ( iFuncIndex == -1 )
	{
		m_Script.iIsActive = FALSE;
		m_Script.iIsRunning = FALSE;
		printf("function %s not exist\n", pstrName);
		return;
	}
	
	// Call the function
	CallFunc ( &m_Script, iFuncIndex );	
}

/******************************************************************************************
*
*	XS_GetReturnValueAsInt ()
*
*	Returns the last returned value as an integer.
*/

int  CTScriptSingleVM::TS_GetReturnValueAsInt ( )
{
	return GetReturnValueAsInt(&m_Script);	
}

/******************************************************************************************
*
*	XS_GetReturnValueAsFloat ()
*
*	Returns the last returned value as an float.
*/

float CTScriptSingleVM::TS_GetReturnValueAsFloat ( )
{
	return GetReturnValueAsFloat(&m_Script);	
}


/******************************************************************************************
*
*	XS_GetReturnValueAsString ()
*
*	Returns the last returned value as an string.
*/

char* CTScriptSingleVM::TS_GetReturnValueAsString ( )
{
	return GetReturnValueAsString(&m_Script);	
}

CTScriptSingleVM::ExportSymbol* CTScriptSingleVM::FindExportSymbol(const char* pstrName)
{
	return CTScriptVMBase::FindExportSymbol(&m_Script, pstrName);
}

CTScriptSingleVM::ExportSymbol* CTScriptSingleVM::FindExportSymbol(int iIndex)
{
	return CTScriptVMBase::FindExportSymbol(&m_Script, iIndex);	
}

int CTScriptSingleVM::TS_GetExportValueCount ()
{
	return m_Script.m_oExportSymbols.iSize;
}

bool  CTScriptSingleVM::TS_GetExportValue ( const char* pstrName, int &iValue)
{
	return GetExportValue(&m_Script, pstrName, iValue);
}

bool CTScriptSingleVM::TS_GetExportValue ( const char* pstrName, float &fValue)
{
	return GetExportValue(&m_Script, pstrName, fValue);	
}

bool CTScriptSingleVM::TS_GetExportValue ( const char* pstrName, char* &pstrValue)
{
	return GetExportValue(&m_Script, pstrName, pstrValue);	
}

bool CTScriptSingleVM::TS_IsExportValueInt ( const char* pstrName)
{
	return IsExportValueInt(&m_Script, pstrName);
}

bool CTScriptSingleVM::TS_IsExportValueFloat ( const char* pstrName)
{
	return IsExportValueFloat(&m_Script, pstrName);
}

bool CTScriptSingleVM::TS_IsExportValueString ( const char* pstrName)
{
	return IsExportValueString(&m_Script, pstrName);
}


bool CTScriptSingleVM::TS_GetExportValue ( int iIndex, char* pstrName, int &iValue)
{
	return GetExportValue(&m_Script, iIndex, pstrName, iValue);
}

bool CTScriptSingleVM::TS_GetExportValue ( int iIndex, char* pstrName, float &fValue)
{
	return GetExportValue(&m_Script, iIndex, pstrName, fValue);
}

bool CTScriptSingleVM::TS_GetExportValue ( int iIndex, char* pstrName, char* &pstrValue)
{
	return GetExportValue(&m_Script, iIndex, pstrName, pstrValue);
	
}

bool CTScriptSingleVM::TS_SetExportValue ( const char* pstrName, int &iValue)
{
	return SetExportValue(&m_Script, pstrName, iValue);
}

bool CTScriptSingleVM::TS_SetExportValue ( const char* pstrName, float &fValue)
{
	return SetExportValue(&m_Script, pstrName, fValue);
}

bool CTScriptSingleVM::TS_SetExportValue ( const char* pstrName, char* &pstrValue)
{
	return SetExportValue(&m_Script, pstrName, pstrValue);	
}

bool CTScriptSingleVM::TS_SetExportValue ( int iIndex, int &iValue)
{
	return SetExportValue(&m_Script, iIndex, iValue);
}

bool CTScriptSingleVM::TS_SetExportValue ( int iIndex, float &fValue)
{
	return SetExportValue(&m_Script, iIndex, fValue);
}

bool CTScriptSingleVM::TS_SetExportValue ( int iIndex, char* &pstrValue)
{
	return SetExportValue(&m_Script, iIndex, pstrValue);
}

bool CTScriptSingleVM::TS_IsExportValueInt ( int iIndex)
{
	return IsExportValueInt(&m_Script, iIndex);
}

bool CTScriptSingleVM::TS_IsExportValueFloat ( int iIndex)
{
	return IsExportValueFloat(&m_Script, iIndex);
}

bool CTScriptSingleVM::TS_IsExportValueString ( int iIndex)
{
	return IsExportValueString(&m_Script, iIndex);	
}


// ---- Host API Interface ----------------------------------------------------------------

/******************************************************************************************
*
*   XS_RegisterHostAPIFunc ()
*
*   Registers a function with the host API.
*/

void CTScriptSingleVM::TS_RegisterHostAPIFunc (char * pstrName, HostAPIFuncPntr *fnFunc )
{
	RegisterHostAPIFunc(-1, pstrName, fnFunc);
}

void   CTScriptSingleVM::TS_ToString (int iParamIndex, char *pszBuffer )
{
	ToString( &m_Script, iParamIndex, pszBuffer);
}

/******************************************************************************************
*
*   XS_GetParamAsInt ()
*
*   Returns the specified integer parameter to a host API function.
*/

int   CTScriptSingleVM::TS_GetParamAsInt (int iParamIndex )
{
	return GetParamAsInt( &m_Script, iParamIndex);
}

/******************************************************************************************
*
*   XS_GetParamAsFloat ()
*
*   Returns the specified floating-point parameter to a host API function.
*/

float CTScriptSingleVM::TS_GetParamAsFloat(int iParamIndex )
{
	return GetParamAsFloat( &m_Script, iParamIndex);
}

char* CTScriptSingleVM::TS_GetParamAsString (int iParamIndex )
{
	return GetParamAsString( &m_Script, iParamIndex);	
}

/******************************************************************************************
*
*   XS_ReturnFromHost ()
*
*   Returns from a host API function.
*/

void CTScriptSingleVM::TS_ReturnFromHost (int iParamCount )
{
	ReturnFromHost(&m_Script, iParamCount);	
}

/******************************************************************************************
*
*   XS_ReturnIntFromHost ()
*
*   Returns an integer from a host API function.
*/

void CTScriptSingleVM::TS_ReturnIntFromHost (int iParamCount, int iInt )
{
	ReturnIntFromHost( &m_Script, iParamCount, iInt);
}

/******************************************************************************************
*
*   XS_ReturnFloatFromHost ()
*
*   Returns a float from a host API function.
*/

void CTScriptSingleVM::TS_ReturnFloatFromHost (int iParamCount, float fFloat )
{
	ReturnFloatFromHost( &m_Script, iParamCount, fFloat);	
}

/******************************************************************************************
*
*   XS_ReturnStringFromHost ()
*
*   Returns a string from a host API function.
*/

void CTScriptSingleVM::TS_ReturnStringFromHost (int iParamCount, const char * pstrString )
{
	ReturnStringFromHost( &m_Script, iParamCount, pstrString);	
}
