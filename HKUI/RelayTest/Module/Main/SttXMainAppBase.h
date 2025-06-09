#ifndef _SttXMainAppBase_h__
#define _SttXMainAppBase_h__

#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"

class CSttXMainAppBase
{
public:
    CSttXMainAppBase();
    virtual ~CSttXMainAppBase();

	virtual void InitSttXMainApp(CXLanguageResourceBase *pLanguage=NULL);
	virtual void ExitSttXMainApp();

public:

public:

//////////////////////////////////////////////////////////////////////////
//OnSttXMainCtrlCntrCmd
public:
	void OnCmd_StartSttXMain();
	void OnCmd_StopSttXMain();
};

extern CSttXMainAppBase *g_pTheSttXMainApp;

#endif // _SttXMainAppBase_h__
