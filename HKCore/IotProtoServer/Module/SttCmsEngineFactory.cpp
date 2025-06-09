#include "stdafx.h"
#include "../../SttStudio/Module/SttCmd/SttSysState.h"
#include "SttCmsEngineFactory.h"
#include "SttCmsEngineDevice.h"

#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
#include "../../../61850/Module/PoCmsEngine/PoCmsEngine.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttCmsEngineFactory::CSttCmsEngineFactory()
{
#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
	m_strEngineProgID = STT_IOT_PP_TYPE_CmsEngine;
#endif
	m_strID = m_strEngineProgID;
}

CSttCmsEngineFactory::~CSttCmsEngineFactory()
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
CIotPxEngineDeviceBase* CSttCmsEngineFactory::CreateDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
	CSttIotCmd *pIotCmd = oDrvIotCmd.SttIotCmd();
	CSttCmsEngineDevice *pNew = new CSttCmsEngineDevice();
	pNew->SetParent(this);

	CString strDeviceSN, strDvmFile, strPpXmlFile;
	pIotCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	pIotCmd->GetParasDataValueByID(STT_CMD_PARA_DvmFile, strDvmFile);
	pIotCmd->GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpXmlFile);

	pNew->m_strID = strDeviceSN;
	pNew->m_pCmsDevice = g_theCmsEngine->CreateDevice(strPpXmlFile, strDvmFile, strDeviceSN);
	pNew->Process_Cmd_IOT_CreateDevice(pPxCommChn, oDrvIotCmd);

	return pNew;
#else
    return NULL;
#endif//#ifdef IOT_PROTOCOL_SERVER_HAS_CMS
}

void CSttCmsEngineFactory::CloseDevice(CIotPxCommChannelInterface *pPxCommChn, CSttIotCmdDriver &oDrvIotCmd)
{
	//在实际的对象中实现Close
}

