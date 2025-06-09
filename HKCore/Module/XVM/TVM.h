// TVM.h: interface for the CTVM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TVM_H__)
#define _TVM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TScriptVMBase.h"

class CTScriptVM : public CTScriptVMBase
{
public:
	CTScriptVM();
	virtual ~CTScriptVM();

//////////////////////////////////////////////////////////////////////////
public:
	// ---- Globals -------------------------------------------------------------------------------
	
	// ---- Scripts ---------------------------------------------------------------------------
	Script g_Scripts [ MAX_THREAD_COUNT ];		    // The script array
	
    // ---- Threading -------------------------------------------------------------------------
	int g_iCurrThreadMode;                          // The current threading mode
	int g_iCurrThread;								// The currently running thread
	Script *g_ScriptCurr;
	int g_iCurrThreadActiveTime;					// The time at which the current thread was activated
	
protected:
	int TS_FindNoActiveThread();

public:
	
	// ---- Function Prototypes -------------------------------------------------------------------
	// ---- Main ------------------------------------------------------------------------------
	void TS_Init ();
	void TS_ShutDown ();
	
	// ---- Script Interface ------------------------------------------------------------------
	int  TS_LoadScript ( char* pstrFilename, int & iScriptIndex, int iThreadTimeslice = TS_THREAD_PRIORITY_USER );
	int  TS_LoadScriptFromBuffer ( char *pBuffer, long nBufferLen,  int &iThreadIndex, int iThreadTimeslice = TS_THREAD_PRIORITY_USER  );
	int  TS_LoadScriptFromBuffer ( CWSerializeBuff  &oWBuffer, int &iThreadIndex, int iThreadTimeslice = TS_THREAD_PRIORITY_USER );
	void TS_UnloadScript ( int iThreadIndex );
	void TS_ResetScript ( int iThreadIndex );
	
	void TS_RunScripts ( unsigned int uiTimesliceDur );
	
	void TS_StartScript ( int iThreadIndex );
	void TS_StopScript ( int iThreadIndex );
	void TS_PauseScript ( int iThreadIndex, int iDur );
	void TS_UnpauseScript ( int iThreadIndex );
	
	void TS_PassIntParam ( int iThreadIndex, int iInt );
	void TS_PassFloatParam ( int iThreadIndex, float fFloat );
	void TS_PassStringParam ( int iThreadIndex, char * pstrString );
	int GetFuncIndexByName ( int iThreadIndex, char * pstrName );
	void TS_CallScriptFunc ( int iThreadIndex, char * pstrName );
	void TS_InvokeScriptFunc ( int iThreadIndex, char * pstrName );
	int  TS_GetReturnValueAsInt ( int iThreadIndex );
	float TS_GetReturnValueAsFloat ( int iThreadIndex );
	char* TS_GetReturnValueAsString ( int iThreadIndex );

	//export symbols////////////////////////////////////////////////////////////////////////
	int  TS_GetExportValueCount ( int iThreadIndex);
	bool TS_GetExportValue ( int iThreadIndex , const char* pstrName, int &iValue);
	bool TS_GetExportValue ( int iThreadIndex , const char* pstrName, float &fValue);
	bool TS_GetExportValue ( int iThreadIndex , const char* pstrName, char* &pstrValue);
	bool TS_GetExportValue ( int iThreadIndex , int iIndex, char* pstrName, int &iValue);
	bool TS_GetExportValue ( int iThreadIndex , int iIndex, char* pstrName, float &fValue);
	bool TS_GetExportValue ( int iThreadIndex , int iIndex, char* pstrName, char* &pstrValue);
	bool TS_IsExportValueInt ( int iThreadIndex , const char* pstrName);
	bool TS_IsExportValueFloat ( int iThreadIndex , const char* pstrName);
	bool TS_IsExportValueString ( int iThreadIndex , const char* pstrName);

	bool TS_SetExportValue ( int iThreadIndex , const char* pstrName, int &iValue);
	bool TS_SetExportValue ( int iThreadIndex , const char* pstrName, float &fValue);
	bool TS_SetExportValue ( int iThreadIndex , const char* pstrName, char* &pstrValue);
	bool TS_SetExportValue ( int iThreadIndex , int iIndex, int &iValue);
	bool TS_SetExportValue ( int iThreadIndex , int iIndex, float &fValue);
	bool TS_SetExportValue ( int iThreadIndex , int iIndex, char* &pstrValue);
	bool TS_IsExportValueInt ( int iThreadIndex , int iIndex);
	bool TS_IsExportValueFloat ( int iThreadIndex , int iIndex);
	bool TS_IsExportValueString ( int iThreadIndex , int iIndex);
	
    // ---- Host API Interface ----------------------------------------------------------------
	void TS_RegisterHostAPIFunc ( int iThreadIndex, char * pstrName, HostAPIFuncPntr *fnFunc);
	
	int   TS_GetParamAsInt ( int iThreadIndex, int iParamIndex );
	float TS_GetParamAsFloat( int iThreadIndex, int iParamIndex );
	char* TS_GetParamAsString ( int iThreadIndex, int iParamIndex );
	
	void TS_ReturnFromHost ( int iThreadIndex, int iParamCount );
	void TS_ReturnIntFromHost ( int iThreadIndex, int iParamCount, int iInt );
	void TS_ReturnFloatFromHost ( int iThreadIndex, int iParamCount, float fFloat );
	void TS_ReturnStringFromHost ( int iThreadIndex, int iParamCount, char * pstrString );

	void TS_Return( int iThreadIndex, int iParamCount )         
    {                                                      
		TS_ReturnFromHost ( iThreadIndex, iParamCount );   
		return;                                            
    }
	
	void TS_ReturnInt( int iThreadIndex, int iParamCount, int iInt )        
    {                                                              
		TS_ReturnIntFromHost ( iThreadIndex, iParamCount, iInt );  
		return;                                                    
    }
	
	void TS_ReturnFloat( int iThreadIndex, int iParamCount, float fFloat )        
    {                                                                  
		TS_ReturnFloatFromHost ( iThreadIndex, iParamCount, fFloat );  
		return;                                                        
    }
	
	void TS_ReturnString( int iThreadIndex, int iParamCount, char* pstrString )       
    {                                                                      
		TS_ReturnStringFromHost ( iThreadIndex, iParamCount, pstrString ); 
		return;                                                            
    }
	
protected:
	BOOL IsValidThreadIndex( int iIndex );
	BOOL IsThreadActive( int iIndex );

	ExportSymbol* FindExportSymbol( int iThreadIndex, const char* pstrName);
	ExportSymbol* FindExportSymbol( int iThreadIndex, int iIndex);
};

inline BOOL CTScriptVM::IsValidThreadIndex( int iIndex )
{
	return ( iIndex < 0 || iIndex > MAX_THREAD_COUNT ? FALSE : TRUE );
}

inline BOOL CTScriptVM::IsThreadActive( int iIndex )
{
	return ( IsValidThreadIndex ( iIndex ) && g_Scripts [ iIndex ].iIsActive ? TRUE : FALSE );
}



#endif // !defined(_TVM_H__)
