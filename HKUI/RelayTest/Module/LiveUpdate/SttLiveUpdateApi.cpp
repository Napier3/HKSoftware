// SttLiveUpdateApi.cpp
//

#include "stdafx.h"
#include "SttLiveUpdateApi.h"
#include "../SttGlobalDef.h"

#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "SttNativeConfig/SttNativeCfgMngr.h"
#include "SttLiveUpdateDef.h"

bool stt_validate_cmd_liveupdate(CDataGroup *pParas)
{
    CDvmData *pPara;

	if(pParas->m_strID != UPDATEPARAS_TYPE_REQUEST) //更新请求
    {
        return false;
    }

    //解读SttNativeCfg.xml
    CSttNativeCfgMngr oNativeCfg;

    if(!oNativeCfg.Open())
    {
        oNativeCfg.InitAfterRead();
        oNativeCfg.Save();
    }

    CSttNativeCfgLiveUpdate* pNativeLiveUpdate = oNativeCfg.GetCfgLiveUpdate();
    CSttNativeCfgHisVer* pNativeHisVer = pNativeLiveUpdate->GetCfgHisVer();
    pPara = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSID);

    if (pPara == NULL)
    {
        return false;
    }

    if(pPara->m_strValue != pNativeLiveUpdate->m_strID_System)
    {
        return false;
    }

    CDvmData *pParaIndex = (CDvmData*)pParas->FindByID(STT_CMD_PARA_LIVEUPDATE_SYSINDEX);

    if(pParaIndex != NULL)
    {
        pNativeLiveUpdate->m_nIndex_System = CString_To_long(pParaIndex->m_strValue);
     }

    oNativeCfg.Save();

    return true;
}

bool stt_process_cmd_liveupdate(CDataGroup *pParas)
{
    Sleep(2000);
    exit(0);

    return true;
}

