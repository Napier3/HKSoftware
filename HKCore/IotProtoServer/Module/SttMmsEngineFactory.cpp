#include "stdafx.h"
#include "../../SttStudio/Module/SttCmd/SttSysState.h"
#include "SttMmsEngineFactory.h"

#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
#include "SttMmsEngineDevice.h"
#include "../../../61850/Module/PoEngine/PoMmsEngine.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttMmsEngineFactory::CSttMmsEngineFactory()
{
#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
	m_strEngineProgID = STT_IOT_PP_TYPE_MmsEngine;
#endif
	m_strID = m_strEngineProgID;
}

CSttMmsEngineFactory::~CSttMmsEngineFactory()
{

}

/*
<iot-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="ppxml-file" data-type="" value="SZNR-TTU.ppxml"/>
		<data name="" id="dvm-file" data-type="" value="SZNR-TTU.xml"/>
		<data name="" id="cmm-cfg-file" data-type="" value="SZNR-TTU202012131700"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
	</paras>
</iot-cmd>
*/
CIotPxEngineDeviceBase* CSttMmsEngineFactory::CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
#ifdef IOT_PROTOCOL_SERVER_HAS_MMS
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	CSttMmsEngineDevice *pNew = new CSttMmsEngineDevice();
	pNew->SetParent(this);

	CString strDeviceSN, strDvmFile, strPpXmlFile;
	pIotCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pIotCmd->GetParasDataValueByID(STT_CMD_PARA_DvmFile, strDvmFile);
	pIotCmd->GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpXmlFile);

	pNew->m_strID = strDeviceSN;
	pNew->m_pMmsDevice = g_theMmsEngine->CreateDevice(strPpXmlFile, strDvmFile, strDeviceSN);
	pNew->m_pMmsDevice->AttachProgress(pNew);
	pNew->Process_Cmd_IOT_CreateDevice(pPxCommChn, oDrvIotCmd);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Mms:CreateDevice:  DvmFile=[%s]"), strDvmFile.GetString());

	return pNew;
#else
    return NULL;
#endif
}

void CSttMmsEngineFactory::CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
	//在实际的对象中实现Close
}

