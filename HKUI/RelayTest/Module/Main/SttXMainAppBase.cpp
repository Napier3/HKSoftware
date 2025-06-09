#include "SttXMainAppBase.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../UI/Module/PopupDialog/SttFileMngrTool.h"
#include "../../../61850/Module/XLanguageResourcePp_Mms.h"

CSttXMainAppBase *g_pTheSttXMainApp = NULL;

CSttXMainAppBase::CSttXMainAppBase()
{
   g_pTheSttXMainApp = this;
}

CSttXMainAppBase::~CSttXMainAppBase()
{


}

void CSttXMainAppBase::InitSttXMainApp(CXLanguageResourceBase *pLanguage)
{
	_P_InitSystemPath();

	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(pLanguage, TRUE);
	CXLanguageMngr::xlang_AddXLanguageRerouce(new CXLanguageResourcePp_Mms(), TRUE);

    CDataMngrXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CSclFileMngrXmlRWKeys::Create();
	g_oXSclFileMngr.OpenSclFileMngrCfg();
	g_oFileMngrTool.OpenConfigFile();
}
void CSttXMainAppBase::ExitSttXMainApp()
{
	CSclFileMngrXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CXLanguageMngr::Release();
	CXLanguageXmlRWKeys::Release();
}

void CSttXMainAppBase::OnCmd_StartSttXMain()
{

}

void CSttXMainAppBase::OnCmd_StopSttXMain()
{

}

