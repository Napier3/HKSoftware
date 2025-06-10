#include "SttBiSyncTest.h"

CString CSttBiSyncTest::m_strMacroName = "快速开入同步性测试";
CString CSttBiSyncTest::m_strMacroID = ("SttBiSyncTest");
CString CSttBiSyncTest::m_strFilePostFix = "stttst";
CString CSttBiSyncTest::m_strMacroVer ="1.0";

CSttBiSyncTest::CSttBiSyncTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	Init(MAX_STATETEST_COUNT);
}

CSttBiSyncTest::~CSttBiSyncTest()
{

}


void CSttBiSyncTest::Init(long nStateNums)
{
	tmt_StateTest::init(nStateNums);
	CSttTestBase::Init();
	m_nCurStateIndex = -1;
}

void CSttBiSyncTest::AfterSetParameter()
{
	Init(1);
	//CSttStateTest::AfterSetParameter();
}

void CSttBiSyncTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oBiSyncPara,pXmlSerialize);
	AfterSetParameter();
}

void CSttBiSyncTest::StartTest()
{
	InitEventBuf();
	CSttStateTest::StartTest();
}

void CSttBiSyncTest::EventProcess()
{
	int nSize = sizeof(structResultNew);
	char* pbuff = new char [nSize];
	int nret = CSttDriverOper::readStateResult(pbuff);
	if(nret <=0)
	{
		return;
	}

	int nLen = sizeof(structResultItemNew);
	qDebug()<<"the Read nSize is"<<nret<<"the struct size"<<nLen;
	structResultNew* pResult;
	pResult = (structResultNew*)(pbuff);

	int val=0;
	for(int i=0;i<nret/nLen;i++)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].nType=%d"), i,  pResult->result[i].nType);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].nBi=%d"), i,  pResult->result[i].nBi.item[0].nVal2);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].nSec=%d"), i,  pResult->result[i].nSec);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Result[%d].nNanoSec=%d"), i,  pResult->result[i].nNanoSec);

		qDebug()<<"pResult nVal1"<<pResult->result[i].nBi.item[0].nVal1;
		double dTime=pResult->result[i].nSec+pResult->result[i].nNanoSec*0.000000001;

		if(pResult->result[i].nType==TestStart)
		{
			nPreBinVal=pResult->result[i].nBi.item[0].nVal1;
			AddEventBuf(pResult->result[i].nType,0,0,0,dTime);
		}
		else if(pResult->result[i].nType==TestStop)
		{
			AddEventBuf(pResult->result[i].nType,0,0,0,dTime);
			m_Start=false;
		}
		else
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

void CSttBiSyncTest::TtmToDrv()
{
	structStateParamNew para;
	memset(&para,0,sizeof(structStateParamNew));
	para.nStateCount = 1;
	para.nIsLoop = 0;
	para.nbiRef = 0;
	structBIStatus gooseInit;
	memset(&gooseInit,0,sizeof(structBIStatus));
	para.oGooseInit = gooseInit;
	CSttDriverOper::setStatePara((char*)&para,sizeof(structStateParamNew),0);

	int nSize = sizeof(structStateItem)*para.nStateCount;
	char* pChar =(char *)malloc(nSize);

	structModuleParam modulepara;
	memset(&modulepara,0,sizeof(structModuleParam));
	modulepara.nAlgCnt = 1;
	modulepara.nAlgTable[0] = CSttDevice::g_pSttDevice->m_nDrv_DIGITALBoard.pos[0];

	modulepara.nbIntCnt = 2;
	modulepara.nbITable[0] = 0x8000;
	modulepara.nbITable[1] =0; //Device::g_Device->getModuleNum(SWITCH,0);
	//modulepara.nbITable[2] =0; //Device::g_Device->getModuleNum(SWITCH,1);
	modulepara.nBoCnt = 2;
	modulepara.nBoTable[0] = 0x8000;
	modulepara.nBoTable[1] =0; //Device::g_Device->getModuleNum(SWITCH,0);
	//modulepara.nBoTable[2] =0; //Device::g_Device->getModuleNum(SWITCH,1);
	CSttDriverOper::SetModuleInfo((char*)&modulepara,sizeof(structModuleParam));

	structStateItem state;
	memset(&state,0,sizeof(structStateItem));
	state.nTirpType = 0x100;
	state.oTm.oTime.nMsec =m_oBiSyncPara.m_nOutputTime*1000;
	memcpy(pChar,&state,sizeof(structStateItem));

	CSttDriverOper::setStatePara(pChar,nSize,1);
	free(pChar);
}
