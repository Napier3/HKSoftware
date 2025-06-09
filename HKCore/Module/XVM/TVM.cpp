// TVM.cpp: implementation of the CTScriptVM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TVM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTScriptVM::CTScriptVM()
{

}

CTScriptVM::~CTScriptVM()
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
void CTScriptVM::TS_Init ()
{
	// ---- Initialize the script array
	for ( int iCurrScriptIndex = 0; iCurrScriptIndex < MAX_THREAD_COUNT; ++ iCurrScriptIndex )
	{
		InitScript(&g_Scripts [ iCurrScriptIndex ]);
	}
	
	Init();

	// ---- Set up the threads
	g_iCurrThreadMode = THREAD_MODE_MULTI;
	g_iCurrThread = 0;
	g_ScriptCurr = NULL;
}

/******************************************************************************************
*
*	TS_ShutDown ()
*
*	Shuts down the runtime environment.
*/
void CTScriptVM::TS_ShutDown ()
{
	// ---- Unload any scripts that may still be in memory
	for ( int iCurrScriptIndex = 0; iCurrScriptIndex < MAX_THREAD_COUNT; ++ iCurrScriptIndex )
	{
		TS_UnloadScript ( iCurrScriptIndex );
	}
	
	FreeBase();
}


// ---- Script Interface ------------------------------------------------------------------
int CTScriptVM::TS_FindNoActiveThread()
{
	int iThreadIndex = -1;
	int iFreeThreadFound = FALSE;

	for ( int iCurrThreadIndex = 0; iCurrThreadIndex < MAX_THREAD_COUNT; ++ iCurrThreadIndex )
	{
		// If the current thread is not in use, use it
		if ( ! g_Scripts [ iCurrThreadIndex ].iIsActive )
		{
			iThreadIndex = iCurrThreadIndex;
			iFreeThreadFound = TRUE;
			break;
		}
	}

	return iThreadIndex;
}

/******************************************************************************************
*
*	TS_LoadScript ()
*
*	Loads an .XSE file into memory.
*   return current active thread index
*/
int  CTScriptVM::TS_LoadScript ( char *pstrFilename, int &iThreadIndex, int iThreadTimeslice )
{
	// ---- Find the next free script index
	int iFreeThreadFound = TS_FindNoActiveThread();

	// If a thread wasn't found, return an out of threads error
	if ( ! iFreeThreadFound < 0)
	{
		return TS_LOAD_ERROR_OUT_OF_THREADS;
	}

	return LoadScript(pstrFilename, &g_Scripts [ iThreadIndex ], iThreadTimeslice);
}

int  CTScriptVM::TS_LoadScriptFromBuffer ( char *pBuffer, long nBufferLen,  int &iThreadIndex, int iThreadTimeslice )
{
	// ---- Find the next free script index
	int iFreeThreadFound = TS_FindNoActiveThread();

	// If a thread wasn't found, return an out of threads error
	if ( ! iFreeThreadFound < 0)
	{
		return TS_LOAD_ERROR_OUT_OF_THREADS;
	}

	return LoadScriptFromBuffer(pBuffer, nBufferLen, &g_Scripts [ iThreadIndex ], iThreadTimeslice);
}

int  CTScriptVM::TS_LoadScriptFromBuffer ( CWSerializeBuff  &oWBuffer, int &iThreadIndex, int iThreadTimeslice )
{
	// ---- Find the next free script index
	int iFreeThreadFound = TS_FindNoActiveThread();

	// If a thread wasn't found, return an out of threads error
	if ( ! iFreeThreadFound < 0)
	{
		return TS_LOAD_ERROR_OUT_OF_THREADS;
	}

	return LoadScriptFromBuffer(oWBuffer, &g_Scripts [ iThreadIndex ], iThreadTimeslice);
}



/******************************************************************************************
*
*	TS_UnloadScript ()
*
*	Unloads a script from memory.
*/

void CTScriptVM::TS_UnloadScript ( int iThreadIndex )
{
	UnloadScript(&g_Scripts [ iThreadIndex ]);
}

/******************************************************************************************
*
*	TS_ResetScript ()
*
*	Resets the script. This function accepts a thread index rather than relying on the
*	currently active thread, because scripts can (and will) need to be reset arbitrarily.
*/

void CTScriptVM::TS_ResetScript ( int iThreadIndex )
{
	ResetScript(&g_Scripts [ iThreadIndex ]);
}

void CTScriptVM::TS_RunScripts ( unsigned int uiTimesliceDuration )
{
	// Begin a loop that runs until a keypress. The instruction pointer has already been
	// initialized with a prior call to ResetScripts (), so execution can begin
	
	// Create a flag that instructions can use to break the execution loop
	int iExitExecLoop = FALSE;
	
	// Create a variable to hold the time at which the main timeslice started
	unsigned int iMainTimesliceStartTime = GetCurrTime ();
	
	// Create a variable to hold the current time
	unsigned int uiCurrTime;
	
	while ( TRUE )
	{
		// Check to see if all threads have terminated, and if so, break the execution
		// cycle
		int iIsStillActive = FALSE;
		
		for ( int iCurrThreadIndex = 0; iCurrThreadIndex < MAX_THREAD_COUNT; ++ iCurrThreadIndex )
		{
			if ( g_Scripts [ iCurrThreadIndex ].iIsActive && g_Scripts [ iCurrThreadIndex ].iIsRunning )
			{
				iIsStillActive = TRUE;
				break;
			}
		}
		
		if ( ! iIsStillActive )
		{
			break;
		}
		
		// Update the current time
		uiCurrTime = GetCurrTime ();
		
		// Check for a context switch if the threading mode is set for multithreading
		if ( g_iCurrThreadMode == THREAD_MODE_MULTI )
		{
			// If the current thread's timeslice has elapsed, or if it's terminated switch
			// to the next valid thread
			if ( uiCurrTime > g_iCurrThreadActiveTime + g_Scripts [ g_iCurrThread ].uiTimesliceDuration ||
				! g_Scripts [ g_iCurrThread ].iIsRunning )
			{
				// Loop until the next thread is found
				while ( TRUE )
				{
					// Move to the next thread in the array
					++ g_iCurrThread;
					
					// If we're past the end of the array, loop back around
					if ( g_iCurrThread >= MAX_THREAD_COUNT )
					{
						g_iCurrThread = 0;
						g_ScriptCurr = &(g_Scripts [ g_iCurrThread ]);
					}
					
					// If the thread we've chosen is active and running, break the loop
					if ( g_Scripts [ g_iCurrThread ].iIsActive && g_Scripts [ g_iCurrThread ].iIsRunning )
					{
						break;
					}
				}
				
				// Reset the timeslice
				g_iCurrThreadActiveTime = uiCurrTime;
			}
		}
		
		g_ScriptCurr = &(g_Scripts [ g_iCurrThread ]);
		
		RunScript(g_ScriptCurr, uiTimesliceDuration, uiCurrTime, iExitExecLoop);

		// If we aren't running indefinitely, check to see if the main timeslice has ended
        if ( uiTimesliceDuration != TS_INFINITE_TIMESLICE )
        {
			if ( uiCurrTime > iMainTimesliceStartTime + uiTimesliceDuration )
			{
				break;
			}
		}
		
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

void CTScriptVM::TS_StartScript ( int iThreadIndex )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( iThreadIndex ) )
		return;
	
	// Set the thread's execution flag
	g_Scripts [ iThreadIndex ].iIsRunning = TRUE;
	
	// Set the current thread to the script
	g_iCurrThread = iThreadIndex;
	g_ScriptCurr = &(g_Scripts [ g_iCurrThread ]);
	
	// Set the activation time for the current thread to get things rolling
	g_iCurrThreadActiveTime = GetCurrTime ();
}

/******************************************************************************************
*
*	TS_StopScript ()
*
*   Stops the execution of a script.
*/

void CTScriptVM::TS_StopScript ( int iThreadIndex )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( iThreadIndex ) )
	{
		return;
	}
	
	// Clear the thread's execution flag
	g_Scripts [ iThreadIndex ].iIsRunning = FALSE;
}

/******************************************************************************************
*
*	TS_PauseScript ()
*
*   Pauses a script for a specified duration.
*/

void CTScriptVM::TS_PauseScript ( int iThreadIndex, int iDur )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( iThreadIndex ) )
		return;
	
	// Set the pause flag
	g_Scripts [ iThreadIndex ].iIsPaused = TRUE;
	
	// Set the duration of the pause
	g_Scripts [ iThreadIndex ].uiPauseEndTime = GetCurrTime () + iDur;	
}

/******************************************************************************************
*
*	TS_UnpauseScript ()
*
*   Unpauses a script.
*/

void CTScriptVM::TS_UnpauseScript ( int iThreadIndex )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( iThreadIndex ) )
		return;
	
	// Clear the pause flag
	g_Scripts [ iThreadIndex ].iIsPaused = FALSE;
}

/******************************************************************************************
*
*   TS_PassIntParam ()
*
*   Passes an integer parameter from the host to a script function.
*/

void CTScriptVM::TS_PassIntParam ( int iThreadIndex, int iInt )
{
	PassIntParam ( &g_Scripts [ iThreadIndex ], iInt );
}

/******************************************************************************************
*
*   TS_PassFloatParam ()
*
*   Passes a floating-point parameter from the host to a script function.
*/

void CTScriptVM::TS_PassFloatParam ( int iThreadIndex, float fFloat )
{
	PassFloatParam ( &g_Scripts [ iThreadIndex ], fFloat );
}

/******************************************************************************************
*
*   TS_PassStringParam ()
*
*   Passes a string parameter from the host to a script function.
*/

void CTScriptVM::TS_PassStringParam ( int iThreadIndex, char * pstrString )
{
	PassStringParam( &g_Scripts [ iThreadIndex ], pstrString );
}

/******************************************************************************************
*
*   GetFuncIndexByName ()
*
*   Returns the index into the function table corresponding to the specified name.
*/

int CTScriptVM::GetFuncIndexByName ( int iThreadIndex, char * pstrName )
{
	return CTScriptVMBase::GetFuncIndexByName(&g_Scripts [ iThreadIndex ], pstrName);
}

/******************************************************************************************
*
*   TS_CallScriptFunc ()
*
*   Calls a script function from the host application.
*/

void CTScriptVM::TS_CallScriptFunc ( int iThreadIndex, char * pstrName )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( iThreadIndex ) )
		return;

	// Get the function's index based on it's name
	int iFuncIndex = GetFuncIndexByName ( iThreadIndex, pstrName );
	
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
	
	// Set the active thread to the one specified
	g_iCurrThread = iThreadIndex;
	g_ScriptCurr = &(g_Scripts [ g_iCurrThread ]);
	
	// Call the function
	CallFunc ( &g_Scripts [ iThreadIndex ], iFuncIndex );
	
	// Set the stack base
	Value StackBase = GetStackValue ( g_ScriptCurr, g_Scripts [ g_iCurrThread ].Stack.iTopIndex - 1 );
	StackBase.iType = OPERAND_TYPE_STACK_BASE_MARKER;
	SetStackValue ( g_ScriptCurr, g_Scripts [ g_iCurrThread ].Stack.iTopIndex - 1, StackBase );
	
	// Allow the script code to execute uninterrupted until the function returns
	TS_RunScripts ( TS_INFINITE_TIMESLICE );
	
	// ---- Handling the function return
	// Restore the VM state
	g_iCurrThreadMode = iPrevThreadMode;
	g_iCurrThread = iPrevThread;
	g_ScriptCurr = &(g_Scripts [ g_iCurrThread ]);
}

/******************************************************************************************
*
*   XS_InvokeScriptFunc ()
*
*   Invokes a script function from the host application, meaning the call executes in sync
*   with the script.
*/

void CTScriptVM::TS_InvokeScriptFunc ( int iThreadIndex, char * pstrName )
{
	// Make sure the thread index is valid and active
	if ( ! IsThreadActive ( iThreadIndex ) )
		return;
	
	// Get the function's index based on its name
	int iFuncIndex = GetFuncIndexByName ( iThreadIndex, pstrName );
	
	// Make sure the function name was valid
	if ( iFuncIndex == -1 )
	{
		g_Scripts [ iThreadIndex ].iIsActive = FALSE;
		g_Scripts [ iThreadIndex ].iIsRunning = FALSE;
		printf("Thread %d : function %s not exist\n", iThreadIndex, pstrName);
		return;
	}
	
	// Call the function
	CallFunc ( &g_Scripts [ iThreadIndex ], iFuncIndex );	
}

/******************************************************************************************
*
*	XS_GetReturnValueAsInt ()
*
*	Returns the last returned value as an integer.
*/

int  CTScriptVM::TS_GetReturnValueAsInt ( int iThreadIndex )
{
	return GetReturnValueAsInt(&g_Scripts [ iThreadIndex ]);	
}

/******************************************************************************************
*
*	XS_GetReturnValueAsFloat ()
*
*	Returns the last returned value as an float.
*/

float CTScriptVM::TS_GetReturnValueAsFloat ( int iThreadIndex )
{
	return GetReturnValueAsFloat(&g_Scripts [ iThreadIndex ]);	
}


/******************************************************************************************
*
*	XS_GetReturnValueAsString ()
*
*	Returns the last returned value as an string.
*/

char* CTScriptVM::TS_GetReturnValueAsString ( int iThreadIndex )
{
	return GetReturnValueAsString(&g_Scripts [ iThreadIndex ]);	
}

CTScriptVM::ExportSymbol* CTScriptVM::FindExportSymbol( int iThreadIndex, const char* pstrName)
{
	return CTScriptVMBase::FindExportSymbol(&g_Scripts [ iThreadIndex ], pstrName);
}

CTScriptVM::ExportSymbol* CTScriptVM::FindExportSymbol( int iThreadIndex, int iIndex)
{
	return CTScriptVMBase::FindExportSymbol(&g_Scripts [ iThreadIndex ], iIndex);	
}

int CTScriptVM::TS_GetExportValueCount ( int iThreadIndex)
{
	return g_Scripts [ iThreadIndex ].m_oExportSymbols.iSize;
}

bool  CTScriptVM::TS_GetExportValue ( int iThreadIndex , const char* pstrName, int &iValue)
{
	return GetExportValue(&g_Scripts [ iThreadIndex ], pstrName, iValue);
}

bool CTScriptVM::TS_GetExportValue ( int iThreadIndex , const char* pstrName, float &fValue)
{
	return GetExportValue(&g_Scripts [ iThreadIndex ], pstrName, fValue);	
}

bool CTScriptVM::TS_GetExportValue ( int iThreadIndex , const char* pstrName, char* &pstrValue)
{
	return GetExportValue(&g_Scripts [ iThreadIndex ], pstrName, pstrValue);	
}

bool CTScriptVM::TS_IsExportValueInt ( int iThreadIndex , const char* pstrName)
{
	return IsExportValueInt(&g_Scripts [ iThreadIndex ], pstrName);
}

bool CTScriptVM::TS_IsExportValueFloat ( int iThreadIndex , const char* pstrName)
{
	return IsExportValueFloat(&g_Scripts [ iThreadIndex ], pstrName);
}

bool CTScriptVM::TS_IsExportValueString ( int iThreadIndex , const char* pstrName)
{
	return IsExportValueString(&g_Scripts [ iThreadIndex ], pstrName);
}


bool CTScriptVM::TS_GetExportValue ( int iThreadIndex , int iIndex, char* pstrName, int &iValue)
{
	return GetExportValue(&g_Scripts [ iThreadIndex ], iIndex, pstrName, iValue);
}

bool CTScriptVM::TS_GetExportValue ( int iThreadIndex , int iIndex, char* pstrName, float &fValue)
{
	return GetExportValue(&g_Scripts [ iThreadIndex ], iIndex, pstrName, fValue);
}

bool CTScriptVM::TS_GetExportValue ( int iThreadIndex , int iIndex, char* pstrName, char* &pstrValue)
{
	return GetExportValue(&g_Scripts [ iThreadIndex ], iIndex, pstrName, pstrValue);
	
}

bool CTScriptVM::TS_SetExportValue ( int iThreadIndex , const char* pstrName, int &iValue)
{
	return SetExportValue(&g_Scripts [ iThreadIndex ], pstrName, iValue);
}

bool CTScriptVM::TS_SetExportValue ( int iThreadIndex , const char* pstrName, float &fValue)
{
	return SetExportValue(&g_Scripts [ iThreadIndex ], pstrName, fValue);
}

bool CTScriptVM::TS_SetExportValue ( int iThreadIndex , const char* pstrName, char* &pstrValue)
{
	return SetExportValue(&g_Scripts [ iThreadIndex ], pstrName, pstrValue);	
}

bool CTScriptVM::TS_SetExportValue ( int iThreadIndex , int iIndex, int &iValue)
{
	return SetExportValue(&g_Scripts [ iThreadIndex ], iIndex, iValue);
}

bool CTScriptVM::TS_SetExportValue ( int iThreadIndex , int iIndex, float &fValue)
{
	return SetExportValue(&g_Scripts [ iThreadIndex ], iIndex, fValue);
}

bool CTScriptVM::TS_SetExportValue ( int iThreadIndex , int iIndex, char* &pstrValue)
{
	return SetExportValue(&g_Scripts [ iThreadIndex ], iIndex, pstrValue);
}

bool CTScriptVM::TS_IsExportValueInt ( int iThreadIndex , int iIndex)
{
	return IsExportValueInt(&g_Scripts [ iThreadIndex ], iIndex);
}

bool CTScriptVM::TS_IsExportValueFloat ( int iThreadIndex , int iIndex)
{
	return IsExportValueFloat(&g_Scripts [ iThreadIndex ], iIndex);
}

bool CTScriptVM::TS_IsExportValueString ( int iThreadIndex , int iIndex)
{
	return IsExportValueString(&g_Scripts [ iThreadIndex ], iIndex);	
}


// ---- Host API Interface ----------------------------------------------------------------

/******************************************************************************************
*
*   XS_RegisterHostAPIFunc ()
*
*   Registers a function with the host API.
*/

void CTScriptVM::TS_RegisterHostAPIFunc ( int iThreadIndex, char * pstrName, HostAPIFuncPntr *fnFunc )
{
	RegisterHostAPIFunc(iThreadIndex, pstrName, fnFunc);
}

/******************************************************************************************
*
*   XS_GetParamAsInt ()
*
*   Returns the specified integer parameter to a host API function.
*/

int   CTScriptVM::TS_GetParamAsInt ( int iThreadIndex, int iParamIndex )
{
	return GetParamAsInt( &g_Scripts [ g_iCurrThread ], iParamIndex);
}

/******************************************************************************************
*
*   XS_GetParamAsFloat ()
*
*   Returns the specified floating-point parameter to a host API function.
*/

float CTScriptVM::TS_GetParamAsFloat( int iThreadIndex, int iParamIndex )
{
	return GetParamAsFloat( &g_Scripts [ g_iCurrThread ], iParamIndex);
}

char* CTScriptVM::TS_GetParamAsString ( int iThreadIndex, int iParamIndex )
{
	return GetParamAsString( &g_Scripts [ g_iCurrThread ], iParamIndex);	
}

/******************************************************************************************
*
*   XS_ReturnFromHost ()
*
*   Returns from a host API function.
*/

void CTScriptVM::TS_ReturnFromHost ( int iThreadIndex, int iParamCount )
{
	ReturnFromHost(&g_Scripts [ iThreadIndex ], iParamCount);	
}

/******************************************************************************************
*
*   XS_ReturnIntFromHost ()
*
*   Returns an integer from a host API function.
*/

void CTScriptVM::TS_ReturnIntFromHost ( int iThreadIndex, int iParamCount, int iInt )
{
	ReturnIntFromHost( &g_Scripts [ iThreadIndex ], iParamCount, iInt);
}

/******************************************************************************************
*
*   XS_ReturnFloatFromHost ()
*
*   Returns a float from a host API function.
*/

void CTScriptVM::TS_ReturnFloatFromHost ( int iThreadIndex, int iParamCount, float fFloat )
{
	ReturnFloatFromHost( &g_Scripts [ iThreadIndex ], iParamCount, fFloat);	
}

/******************************************************************************************
*
*   XS_ReturnStringFromHost ()
*
*   Returns a string from a host API function.
*/

void CTScriptVM::TS_ReturnStringFromHost ( int iThreadIndex, int iParamCount, char * pstrString )
{
	ReturnStringFromHost( &g_Scripts [ iThreadIndex ], iParamCount, pstrString);	
}
