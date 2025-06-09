//SttLicenseApi.cpp

#include "stdafx.h"
#include "SttLicenseApi.h"

#include "../../../Module/SttGlobalDef.h"
#include "../../../AtsService/AtsXDes/atsxdes.h"
#include "../../../../Module/API/GlobalConfigApi.h"

AtsXDes *g_pAtsXDes = 0;

bool SttLicenseInit()
{
    if (g_pAtsXDes == 0)
    {
        g_pAtsXDes = new AtsXDes();
        SttLicenseOpen();
    }

    return true;
}

bool SttLicenseOpen()
{
    if (g_pAtsXDes == 0)
    {
        return false;
    }

    char pszFile[1024];
    strcpy(pszFile, _P_GetConfigPath());
    strcat(pszFile, STT_SYS_License_File);
    return g_pAtsXDes->OpenLicenseFile(pszFile);
}

void SttLicenseExit()
{
    if (g_pAtsXDes != 0)
    {
        delete g_pAtsXDes;
        g_pAtsXDes = 0;
    }
}


bool SttLicenseCanUse(char *strSN, char *strModuleID
                      , int nCurrYear, int nCurrMonth, int nCurrDay
                      , int nCurrTimes)
{
    if (g_pAtsXDes == 0)
    {
        return false;
    }

    return g_pAtsXDes->IsValid(strSN, strModuleID, nCurrYear, nCurrMonth, nCurrDay, nCurrTimes);
}

