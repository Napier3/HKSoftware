// TVMSingle.h: interface for the CTScriptSingleVM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TVM_SINGLE_H__)
#define _TVM_SINGLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TScriptVMBase.h"

//#define _xvm_use_time_

class CTScriptSingleVM  : public CTScriptVMBase
{
public:
	CTScriptSingleVM();
	virtual ~CTScriptSingleVM();

//////////////////////////////////////////////////////////////////////////
public:
	// ---- Globals -------------------------------------------------------------------------------
	
	// ---- Scripts ---------------------------------------------------------------------------
	Script m_Script;		    // The script array
	
    // ---- Threading -------------------------------------------------------------------------
	int g_iCurrThreadMode;                          // The current threading mode
	int g_iCurrThread;								// The currently running thread
	int g_iCurrThreadActiveTime;					// The time at which the current thread was activated
	
public:
	
	// ---- Function Prototypes -------------------------------------------------------------------
	// ---- Main ------------------------------------------------------------------------------
	void TS_Init ();
	void TS_ShutDown ();
	
	// ---- Script Interface ------------------------------------------------------------------
	int  TS_LoadScript ( char* pstrFilename, int iThreadTimeslice );
	int  TS_LoadScriptFromBuffer ( char *pBuffer, long nBufferLen,  int iThreadTimeslice = TS_THREAD_PRIORITY_USER  );
	int  TS_LoadScriptFromBuffer ( CWSerializeBuff  &oWBuffer, int iThreadTimeslice = TS_THREAD_PRIORITY_USER );
	void TS_UnloadScript ( );
	void TS_ResetScript ( );
	
	void TS_RunScripts ( unsigned int uiTimesliceDur );
	
	void TS_StartScript ( );
	void TS_StopScript ( );
	void TS_PauseScript (int iDur );
	void TS_UnpauseScript ( );
	
	void TS_PassIntParam (int iInt );
	void TS_PassFloatParam (float fFloat );
	void TS_PassStringParam (char * pstrString );
	int GetFuncIndexByName (char * pstrName );
	void TS_CallScriptFunc (char * pstrName );
	void TS_InvokeScriptFunc (char * pstrName );
	int  TS_GetReturnValueAsInt ( );
	float TS_GetReturnValueAsFloat ( );
	char* TS_GetReturnValueAsString ( );

	//export symbols////////////////////////////////////////////////////////////////////////
	int  TS_GetExportValueCount ();
	bool TS_GetExportValue ( const char* pstrName, int &iValue);
	bool TS_GetExportValue ( const char* pstrName, float &fValue);
	bool TS_GetExportValue ( const char* pstrName, char* &pstrValue);
	bool TS_GetExportValue ( int iIndex, char* pstrName, int &iValue);
	bool TS_GetExportValue ( int iIndex, char* pstrName, float &fValue);
	bool TS_GetExportValue ( int iIndex, char* pstrName, char* &pstrValue);
	bool TS_IsExportValueInt ( const char* pstrName);
	bool TS_IsExportValueFloat ( const char* pstrName);
	bool TS_IsExportValueString ( const char* pstrName);

	bool TS_SetExportValue ( const char* pstrName, int &iValue);
	bool TS_SetExportValue ( const char* pstrName, float &fValue);
	bool TS_SetExportValue ( const char* pstrName, char* &pstrValue);
	bool TS_SetExportValue ( int iIndex, int &iValue);
	bool TS_SetExportValue ( int iIndex, float &fValue);
	bool TS_SetExportValue ( int iIndex, char* &pstrValue);
	bool TS_IsExportValueInt ( int iIndex);
	bool TS_IsExportValueFloat ( int iIndex);
	bool TS_IsExportValueString ( int iIndex);
	
    // ---- Host API Interface ----------------------------------------------------------------
	void TS_RegisterHostAPIFunc (char * pstrName, HostAPIFuncPntr *fnFunc);
	
	void   TS_ToString (int iParamIndex, char *pszBuffer);
	int   TS_GetParamAsInt (int iParamIndex );
	float TS_GetParamAsFloat(int iParamIndex );
	char* TS_GetParamAsString (int iParamIndex );
	
	void TS_ReturnFromHost (int iParamCount );
	void TS_ReturnIntFromHost (int iParamCount, int iInt );
	void TS_ReturnFloatFromHost (int iParamCount, float fFloat );
	void TS_ReturnStringFromHost (int iParamCount, const char * pstrString );

	void TS_Return(int iParamCount )         
    {                                                      
		TS_ReturnFromHost ( iParamCount );   
		return;                                            
    }
	
	void TS_ReturnInt(int iParamCount, int iInt )        
    {                                                              
		TS_ReturnIntFromHost ( iParamCount, iInt );  
		return;                                                    
    }
	
	void TS_ReturnFloat(int iParamCount, float fFloat )        
    {                                                                  
		TS_ReturnFloatFromHost ( iParamCount, fFloat );  
		return;                                                        
    }
	
	void TS_ReturnString(int iParamCount, const char* pstrString )       
    {                                                                      
		TS_ReturnStringFromHost ( iParamCount, pstrString ); 
		return;                                                            
    }
	
protected:
	BOOL IsValidThreadIndex( int iIndex );
	BOOL IsThreadActive( int iIndex );

	ExportSymbol* FindExportSymbol(const char* pstrName);
	ExportSymbol* FindExportSymbol(int iIndex);
};

inline BOOL CTScriptSingleVM::IsValidThreadIndex( int iIndex )
{
	return ( iIndex < 0 || iIndex > MAX_THREAD_COUNT ? FALSE : TRUE );
}

inline BOOL CTScriptSingleVM::IsThreadActive( int iIndex )
{
    if (! IsValidThreadIndex ( iIndex ))
    {
        return FALSE;
    }

    return (m_Script.iIsActive ? TRUE : FALSE );
}

#endif // !defined(_TVM_SINGLE_H__)

