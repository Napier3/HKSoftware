#include "SttTimeMeasureTest.h"
#include "IEC61850CfgMngr.h"

CString CSttTimeMeasureTest::m_strMacroName = " ±º‰≤‚¡ø≤‚ ‘";
CString CSttTimeMeasureTest::m_strMacroID = ("SttTimeMeasureTest");
CString CSttTimeMeasureTest::m_strFilePostFix = "stttst";
CString CSttTimeMeasureTest::m_strMacroVer ="1.0";

CSttTimeMeasureTest::CSttTimeMeasureTest()
{
	m_pszBuff=stt_test_init_global_buff();
	m_pszResultBuff=stt_test_init_result_buff();
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	Init(MAX_STATETEST_COUNT);
	m_Start=FALSE;
}

CSttTimeMeasureTest::~CSttTimeMeasureTest()
{
	m_pszBuff=NULL;
	m_pszResultBuff=NULL;
}

void CSttTimeMeasureTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oTimeMeasureParas,pXmlSerialize);
	AfterSetParameter();
}

void CSttTimeMeasureTest::StartTest()
{	
	CSttStateTest::StartTest();
}

void CSttTimeMeasureTest::EventProcess()
{	
	memset(m_pszResultBuff,0,sizeof(structResultNew));
	int nret = CSttDriverOper::readStateResult(m_pszResultBuff);
	if(nret <=0)
	{
		return;
	}

	int nLen = sizeof(structResultItemNew);
	qDebug()<<"the Read nSize is"<<nret<<"the struct size"<<nLen;
	structResultNew* pResult= (structResultNew*)(m_pszResultBuff);

	int val=0;
	for(int i=0;i<nret/nLen;i++)
	{
		qDebug()<<"pResult nVal1"<<pResult->result[i].nBi.item[0].nVal1;
		double dTime=pResult->result[i].nSec+pResult->result[i].nNanoSec*0.000000001;

		if(pResult->result[i].nType==TestStart)
		{
			nPreBinVal=pResult->result[i].nBi.item[0].nVal1;
			AddEventBuf(pResult->result[i].nType,0,0,0,dTime);
			m_Start=true;
		}
		else if(pResult->result[i].nType==TestStop)
		{
			if(m_Start)
			{
				AddEventBuf(pResult->result[i].nType,0,0,0,dTime);
				m_Start=false;
				CSttStateTest::Stop();
			}
		}
		else if(pResult->result[i].nType==4)
		{
			for(int j=0;j<8;j++)
			{
				int nPreSta=nPreBinVal&(1<<j);
				int nSta=pResult->result[i].nBi.item[0].nVal1&(1<<j);
				if(nPreSta!=nSta)
				{
					qDebug()<<"nSta "<<(nSta>>j);
					AddEventBuf(pResult->result[i].nType,0,j+1,nSta>>j,dTime);
				}
			}
			nPreBinVal=pResult->result[i].nBi.item[0].nVal1;
		}
	}
}

void CSttTimeMeasureTest::Init(long nStateNums)
{
	tmt_StateTest::init(nStateNums);
	CSttTestBase::Init();
	m_nCurStateIndex = -1;
}

void CSttTimeMeasureTest::AfterSetParameter()
{
	Init(m_oTimeMeasureParas.m_nStateCount);
	//CSttStateTest::AfterSetParameter();
}

void CSttTimeMeasureTest::TtmToDrv()
{
	CIEC61850CfgMngr::g_pIEC61850CfgMngr->InitGooseSub();

	structStateParamNew para;
	memset(&para,0,sizeof(structStateParamNew));
	para.nStateCount = m_oTimeMeasureParas.m_nStateCount;
	para.nIsLoop = 0;
	para.nbiRef = 0;

	structBIStatus gooseInit;
	memset(&gooseInit,0,sizeof(structBIStatus));
	para.oGooseInit = gooseInit;
	CSttDriverOper::setStatePara((char*)&para,sizeof(structStateParamNew),0);

	int nSize = sizeof(structStateItem)*para.nStateCount;
	memset(m_pszBuff,0,40*1024*1024);

	structModuleParam modulepara;
	memset(&modulepara,0,sizeof(structModuleParam));
	modulepara.nAlgCnt = 1;
	//modulepara.nAlgTable[0] = CSttDevice::g_pSttDevice->m_nDrv_DIGITALBoard.pos[0];
	modulepara.nAlgTable[0] = CSttDevice::g_pSttDevice->m_oDeviceInfo->digitalmodule[0].pos;

	modulepara.nbIntCnt = 2;
	modulepara.nbITable[0] = 0x8000;
	modulepara.nbITable[1] =0; //Device::g_Device->getModuleNum(SWITCH,0);
	//modulepara.nbITable[2] =0; //Device::g_Device->getModuleNum(SWITCH,1);
	modulepara.nBoCnt = 1;
	modulepara.nBoTable[0] = 0x8000;
	//modulepara.nBoTable[1] =0; //Device::g_Device->getModuleNum(SWITCH,0);
	//modulepara.nBoTable[2] =0; //Device::g_Device->getModuleNum(SWITCH,1);
	CSttDriverOper::SetModuleInfo((char*)&modulepara,sizeof(structModuleParam));

	for(int i=0;i<para.nStateCount;i++)
	{
		structStateItem state;
		memset(&state,0,sizeof(structStateItem));
		state.nTirpType = 0x100;
		state.oTm.oTime.nMsec =m_oTimeMeasureParas.m_oTimeMeasurePara[i].m_nOutputTime;

		for (int nIndex = 0;nIndex<8;nIndex++)
		{
			state.oStBo.boStatus.item[0].nVal1 += ((!m_oTimeMeasureParas.m_oTimeMeasurePara[i].m_binOut[nIndex].nState)*(1<<nIndex));
		}

		//state.oStBo.nHoldDelay = state.oTm.oTime.nMsec;
		memcpy(m_pszBuff+sizeof(structStateItem)*i,&state,sizeof(structStateItem));
	}

	CSttDriverOper::setStatePara(m_pszBuff,nSize,1);
}
