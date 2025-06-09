#include "stdafx.h"
#include "SttPIP150Test.h"
#include "../../../SttDevice/SttDeviceBase.h"

CString CSttPIP150Test::m_strMacroName = "PIP150测试";
CString CSttPIP150Test::m_strMacroID = "PIP150Test";
CString CSttPIP150Test::m_strFilePostFix = "sttptt";
CString CSttPIP150Test::m_strMacroVer ="1.0";

CSttPIP150Test::CSttPIP150Test()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

CSttPIP150Test::~CSttPIP150Test(void)
{

}

void CSttPIP150Test::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	long nModulePos = 0;
	unsigned int nStatus[3] = {0};
	unsigned int nVolt[3] = {0};
	pXmlSerialize->xml_serialize("模块光纤接口号(1-12)", "ModulePos", "", "long", nModulePos);
	pXmlSerialize->xml_serialize("电源A幅值", "PowerA", "", "long", nVolt[0]);
	pXmlSerialize->xml_serialize("电源B幅值", "PowerB", "", "long", nVolt[1]);
	pXmlSerialize->xml_serialize("电源C幅值", "PowerC", "", "long", nVolt[2]);
	if(nVolt[0] == 0)
	{
		nStatus[0] = 0;
	}
	else
	{
		nStatus[0] = 1;
	}
	if(nVolt[1] == 0)
	{
		nStatus[1] = 0;
	}
	else
	{
		nStatus[1] = 1;
	}
	if(nVolt[2] == 0)
	{
		nStatus[2] = 0;
	}
	else
	{
		nStatus[2] = 1;
	}

	int nFd = CSttDeviceBase::g_pSttDeviceBase->m_nCommfd;
	Drv_ComData oComData;
	oComData.nModule = ModuleIndexTransToDrv(nModulePos) << 16;
	oComData.dat[0] = 0x05640564;
	oComData.dat[1] = 4;
	oComData.dat[2] = 0x3002;
	float fVal = 0;
	fVal = nVolt[0]/150.0;
	fVal = fVal*2500;
	oComData.dat[3] = fVal;
	fVal = nVolt[1]/150.0;
	fVal = fVal*2500;
	oComData.dat[4] = fVal;
	fVal = nVolt[2]/150.0;
	fVal = fVal*2500;
	oComData.dat[5] = fVal;
	if(oComData.dat[3] > 2500)
	{
		oComData.dat[3] = 2500;
	}
	if(oComData.dat[4] > 2500)
	{
		oComData.dat[4] = 2500;
	}
	if(oComData.dat[5] > 2500)
	{
		oComData.dat[5] = 2500;
	}
	ioctl(nFd, 0x322, 0);
	write(nFd, (char*)&oComData, sizeof(Drv_ComData));
	Sleep(100);

	oComData.dat[1] = 5;
	oComData.dat[2] = 0x3001;
	oComData.dat[3] = 0;
	oComData.dat[4] = 0;
	oComData.dat[5] = 0;
	oComData.dat[6] = 0;

	if(nStatus[0] == 1)
	{
		oComData.dat[3] |= 1<<12;
	}	

	if(nStatus[1] == 1)
	{
		oComData.dat[3] |= 1<<13;
	}	

	if(nStatus[2] == 1)
	{
		oComData.dat[3] |= 1<<14;
	}

	ioctl(nFd, 0x322, 0);
	write(nFd, (char*)&oComData, sizeof(Drv_ComData));

	ReturnTestStateEvent_TestFinish(0,0,FALSE);
}
