#include "stdafx.h"
#include "SttPowerTestEngineBase.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/FilterText/FilterTextGlobal.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../SttSystemConfig/SttSystemConfigGlobal.h"
#include "../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../SttSystemConfig/SttSystemConfig.h"

#include "../SttTestSysGlobalPara.h"
// TMT_SYSTEM_DEFAULT_OUTPUT_PARAS g_oDefaultOutputPara;
// STT_SystemParas g_oSystemParas;
// tmt_PtPara g_oPTTestPara;
bool g_bPrintLog = FALSE;
bool g_bSaveFile = FALSE;
//long g_nSttLogServerSpyAllCmd = 1;//zhouhj 20210826解决编译问题

#ifdef STT_NOT_TESTCNTRFRAME
CSttTestAppConfigTool g_oSttTestAppConfigTool;
CSttTestAppCfg g_oSttTestAppCfg;//zhouhj 20210823  李工因为兼容物联网多配置文件问题已修改相关功能类,在单机软件中只会有一台测试仪,故此处采用全局唯一对象
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double CalcSpanTime(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd)
{
	CGpsPcTimeSpan oSpan;
	CGpsPcTime tm1 = tmStart;
	CGpsPcTime tm2 = tmEnd;

	oSpan = tm2 - tm1;
	DWORD nSpanMs = oSpan.GetTotalMilliseconds();
	return (double)nSpanMs*0.001;
}

/*  移动到GpsPcTime.cpp  shaolei 2022-1-11
void ep_cap_timeval_to_systime(const struct timeval &ts, SYSTEMTIME &tmSys)
{
	int i,year,month,day,hour,minute,second;
	long tmp;
	int dyr[12]={31,29,31,30,31,30,31,31,30,31,30,31}; //闰年月份
	int dyp[12]={31,28,31,30,31,30,31,31,30,31,30,31}; //平年
	bool flag=0;
	long t = ts.tv_sec;
	int *pdy = NULL;
	int days=0;

	for(year=1970; ;year++)
	{
		if((year%400==0)||(year%4==0 && year%100!=0)) //润年
		{
			days = 366;
			pdy = dyr;
		}
		else
		{
			days = 365;
			pdy = dyp;
		}

		tmp=days*24*60*60;

		if(t >= tmp)
		{
			t = t - tmp;
		}
		else
		{

			for(i=0;i<12;i++)
			{
				tmp=pdy[i]*24*60*60;

				if(t>=tmp)
				{
					t=t-tmp;
				}
				else
				{
					month=i+1;
					day=t/(24*60*60)+1;
					t=t-(day-1)*24*60*60;
					hour=t/(60*60);
					t=t-hour*60*60;
					minute=t/60;
					second=t%60;
					flag=1;
					break;
				}
			}
		}

		if(flag) 
		{
			break;
		}
	}

	tmSys.wYear = year;
	tmSys.wMonth = month;
	tmSys.wDay = day;
	tmSys.wHour = hour;
	tmSys.wMinute = minute;
	tmSys.wSecond = second;

	CGpsPcTime ctime(tmSys);
	CGpsPcTimeSpan tmSpan(0, 8, 0, 0,0,0);
	ctime += tmSpan;
	ctime.GetSysTime(tmSys);

	tmSys.wMinute = minute;
	tmSys.wSecond = second;
	tmSys.wMilliseconds = ts.tv_usec / 1000;
}
*/
//////////////////////////////////////////////////////////////////////////
//CSttPowerTestEngineBase
CSttPowerTestEngineBase::CSttPowerTestEngineBase()
{
	m_pXClientEngine = NULL;
	m_pLastEventResult = NULL;

	m_bLockFlag = 0;//yyj add 20211019

	m_bStarted = false;
	m_bUpdateRtData = TRUE;

}

CSttPowerTestEngineBase::~CSttPowerTestEngineBase()
{
	
}

void CSttPowerTestEngineBase::OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType)
{
//	CLogPrint::LogString(XLOGLEVEL_TRACE, pszCmdID);
}

CEventResult *CSttPowerTestEngineBase::InitEvent(const CString &strEventID,double fTime,double fRealTime,const CString &strTimeStr) //yyj modify 20210902
{
	CEventResult *pEventInfo = NULL;
	SYSTEMTIME tmEvent;

	if (strEventID != SYS_STATE_EVENT_OnTestStoped)
	{
		struct timeval ts;
		ts.tv_sec = (long)fTime;   //秒
		double dNs = fTime - ts.tv_sec;  //纳秒
		ts.tv_usec = dNs * 1000000;
		ep_cap_timeval_to_systime(ts,tmEvent);
	}
	
	if (strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		pEventInfo = (CEventResult *)m_oCurrEventResult.Clone();

		pEventInfo->m_tmStart = tmEvent;
		pEventInfo->m_fActStart = 0;
		pEventInfo->m_nCurrStateIndex = 0;
	}
	else
	{
		if (m_pLastEventResult == NULL)
		{
			m_pLastEventResult = &m_oCurrEventResult;
		}

		pEventInfo = (CEventResult *)m_pLastEventResult->Clone();	
	}

	if (strEventID == SYS_STATE_REPORT_OnStateChanged)
	{
		pEventInfo->m_fActStart = pEventInfo->m_fActTime;
//		pEventInfo->m_nCurrStateIndex = pEventInfo->m_nCurrStateIndex;
	}

	pEventInfo->m_fActTime = 0;
	pEventInfo->m_tmEvent = tmEvent;
	pEventInfo->m_fTime = fTime;//20230614 zhouhj 新增用于状态图更新
	pEventInfo->m_strTimeStr = strTimeStr;
	pEventInfo->m_strEventID = strEventID;
/*yyj delete 20210902
	if (bUpdateLastResult)
	{
		m_pLastEventResult = pEventInfo;
	}
*/	
	return pEventInfo;
}
CDataGroup* Global_FindByID_LastGroup(CDataGroup *pParas,const CString &strID)
{
	if (pParas == NULL)
	{
		return NULL;
	}

	CExBaseObject *pCurrObj = NULL;
	POS pos = pParas->GetTailPosition();

	while(pos)
	{
		pCurrObj = pParas->GetPrev(pos);

		if (pCurrObj->m_strID == strID)
		{
			return (CDataGroup*)pCurrObj;
		}
	}

	return NULL;
}

void CSttPowerTestEngineBase::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)
{
	double fTime = 0,fRealTime = 0;
	CString strTimeStr;
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

	CEventResult *pEventInfo = InitEvent(SYS_STATE_EVENT_OnTestStarted,fTime,fRealTime,strTimeStr);

	//处理初始开入、开出状态
	CDataGroup *pEventBinGroup = Global_FindByID_LastGroup(pParas,SYS_STATE_XEVENT_EVENTID_BIN);
	CDataGroup *pEventBoutGroup = Global_FindByID_LastGroup(pParas,SYS_STATE_XEVENT_EVENTID_BOUT);

	if ((pEventBinGroup == NULL) && (pEventBoutGroup == NULL)&&(m_pLastEventResult != NULL))
	{
		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pEventInfo->m_BinIn[nIndex] = m_pLastEventResult->m_BinIn[nIndex];
			pEventInfo->m_BinOut[nIndex] = m_pLastEventResult->m_BinOut[nIndex];
		}
	}

	if (pEventBinGroup || pEventBoutGroup)
	{
		OnTestInitialize(pEventInfo,pParas);

		//2023.6.13 zhouhj  收到开始测试命令后,对开入开出进行初始化同步
		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			m_oCurrEventResult.m_BinIn[nIndex] = pEventInfo->m_BinIn[nIndex];
			m_oCurrEventResult.m_BinOut[nIndex] = pEventInfo->m_BinOut[nIndex];
		}
	}

	//2023.6.13 zhouhj  在数据更新完再添加进链表
	m_pLastEventResult = pEventInfo;
//	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("OnTestStarted[Bin1=%ld]."),m_pLastEventResult->m_BinIn[0]);
	AppenEventInfo(pEventInfo);
}

void CSttPowerTestEngineBase::OnTestStoped(const CString &strMacroID, CDataGroup *pParas)
{
	CEventResult *pEventInfo = InitEvent(SYS_STATE_EVENT_OnTestStoped,0,0,_T(""));
	AppenEventInfo(pEventInfo);
}

void CSttPowerTestEngineBase::OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{
	if (!m_bStarted)
	{
		return;
	}
	double fTime = 0,fRealTime = 0;
	CString strTimeStr;
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

	CEventResult *pEventInfo = InitEvent(SYS_STATE_EVENT_OnTestFinished,fTime,fRealTime,strTimeStr);
	m_pLastEventResult = pEventInfo;
	AppenEventInfo(pEventInfo);

	//处理返回结果
	if (pResults != NULL && pResults->GetCount()>0)
	{
		OnTestResults(pResults);
/*
		SYSTEMTIME tm;
  		::GetLocalTime(&tm);
  		CString strTmpPath = _P_GetLibraryPath();
  		strTmpPath.AppendFormat(_T("OnTestResult%d-%d-%d %d-%d-%d.%d.xml"), tm.wYear, tm.wMonth, tm.wDay
  			, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);
  		pResults->SaveXmlFile(strTmpPath,CDataMngrXmlRWKeys::g_pXmlKeys);
*/
	}
}

void CSttPowerTestEngineBase::OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)
{
	double fTime = 0,fRealTime = 0;
	CString strTimeStr;
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

	CDataGroup *pEventGroup = (CDataGroup *)pParas->FindByID(_T("Event"));

	CEventResult *pEventInfo = InitEvent(SYS_STATE_EVENT_OnSearchPointReport,fTime,fRealTime,strTimeStr);
	m_pLastEventResult = pEventInfo;
	AppenEventInfo(pEventInfo);
}

void CSttPowerTestEngineBase::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
{
}

/*******************************
<paras name="" id="">
	<data name="ExecStatus" id="ExecStatus" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="同步" id="Sync" unit="" data-type="long" default="0" value="0" />
	<data name="UTC-秒" id="Utc_s" unit="" data-type="long" default="1441103021" value="1441103021" />
	<data name="UTC-纳秒" id="Utc_ns" unit="" data-type="long" default="154343280" value="154343280" />
	<data name="高温停止实验" id="StopByHighT" unit="" data-type="long" default="0" value="0" />
	<data name="模拟量模块数" id="AnalogCount" unit="" data-type="long" default="2" value="2" />
	<group name="模块1" id="Module0" data-type="Module">
		<data name="电源电压-1" id="VoltDc1" unit="V" data-type="float" default="15.297655" value="15.2976551" />
		<data name="电源电压-2" id="VoltDc2" unit="V" data-type="float" default="-15.234961" value="-15.2349606" />
		<data name="电源电压-3" id="VoltDc3" unit="V" data-type="float" default="223.652344" value="223.652344" />
		<data name="电源电压-4" id="VoltDc4" unit="V" data-type="float" default="-226.660156" value="-226.660156" />
		<data name="温度-1" id="T1" unit="deg" data-type="long" default="31" value="31" />
		<data name="温度-2" id="T2" unit="deg" data-type="long" default="26" value="26" />
		<data name="温度-3" id="T3" unit="deg" data-type="long" default="0" value="0" />
		<data name="电压过热" id="IsVoltHot" unit="" data-type="long" default="0" value="0" />
		<data name="直流过热" id="IsDCHot" unit="" data-type="long" default="0" value="0" />
		<data name="电压告警" id="IsVoltWarining" unit="" data-type="long" default="0" value="0" />
		<data name="丢失告警" id="IsMissWarining" unit="" data-type="long" default="0" value="0" />
		<data name="模块类型" id="ModuleType" unit="" data-type="ModuleType" default="0" value="0" />
		<data name="模块位置" id="ModulePos" unit="" data-type="long" default="2" value="2" />
		<group name="通道1" id="Channel0" data-type="Channel">
			<data name="最大电压" id="VoltMax" unit="V" data-type="float" default="249.877930" value="249.87793" />
			<data name="最小电压" id="VoltMin" unit="V" data-type="float" default="249.877930" value="249.87793" />
			<data name="过载" id="IsOverLoad" unit="" data-type="long" default="0" value="0" />
		</group>
		<group name="通道2" id="Channel1" data-type="Channel">
			<data name="最大电压" id="VoltMax" unit="V" data-type="float" default="249.877930" value="249.87793" />
			<data name="最小电压" id="VoltMin" unit="V" data-type="float" default="249.877930" value="249.87793" />
			<data name="过载" id="IsOverLoad" unit="" data-type="long" default="0" value="0" />
		</group>
		<group name="通道3" id="Channel2" data-type="Channel">
			<data name="最大电压" id="VoltMax" unit="V" data-type="float" default="6.713867" value="6.71386719" />
			<data name="最小电压" id="VoltMin" unit="V" data-type="float" default="-8.178711" value="-8.17871094" />
			<data name="过载" id="IsOverLoad" unit="" data-type="long" default="0" value="0" />
		</group>
		<group name="通道4" id="Channel3" data-type="Channel">
			<data name="最大电压" id="VoltMax" unit="V" data-type="float" default="7.324219" value="7.32421875" />
			<data name="最小电压" id="VoltMin" unit="V" data-type="float" default="-8.544922" value="-8.54492188" />
			<data name="过载" id="IsOverLoad" unit="" data-type="long" default="0" value="0" />
		</group>
		<group name="通道5" id="Channel4" data-type="Channel">
			<data name="最大电压" id="VoltMax" unit="V" data-type="float" default="7.934570" value="7.93457031" />
			<data name="最小电压" id="VoltMin" unit="V" data-type="float" default="-9.033203" value="-9.03320312" />
			<data name="过载" id="IsOverLoad" unit="" data-type="long" default="0" value="0" />
		</group>
		<group name="通道6" id="Channel5" data-type="Channel">
			<data name="最大电压" id="VoltMax" unit="V" data-type="float" default="7.446289" value="7.44628906" />
			<data name="最小电压" id="VoltMin" unit="V" data-type="float" default="-8.789062" value="-8.7890625" />
			<data name="过载" id="IsOverLoad" unit="" data-type="long" default="0" value="0" />
		</group>
	</group>
	<group name="模块2" id="Module1" data-type="Module">
	……
	</group>
</paras>
*******************************/
void CSttPowerTestEngineBase::OnException(CDataGroup *pParas)
{
	POS pos = pParas->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *p1 = NULL;
	CDataGroup *pModule = NULL;
	CDataGroup *pCh = NULL;
	POS posCh = NULL;

	BOOL bIsHot = FALSE,bIsUOverLoad = FALSE,bIsIOverLoad = FALSE;
	
	while(pos != NULL)
	{
		p = pParas->GetNext(pos);

		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pModule = (CDataGroup *)p;

		if (pModule->m_strDataType != _T("Module"))
		{
			continue;
		}

/*yyj 后期处理
		long nIsVoltHot = 0,nIsDCHot = 0,nIsVoltWarining = 0;
		stt_GetDataValueByID(pModule, _T("IsVoltHot"), nIsVoltHot);
		stt_GetDataValueByID(pModule, _T("IsDCHot"), nIsDCHot);
		stt_GetDataValueByID(pModule, _T("IsVoltWarining"), nIsVoltWarining);

		if (nIsVoltHot || nIsDCHot)
		{
			bIsHot = TRUE;
		}
*/
		CString strModuleType;
		stt_GetDataValueByID(pModule, _T("ModuleType"), strModuleType);

		//解析温度上、中、下
		float fT1 = 0.0,fT2 = 0.0,fT3 = 0.0;
		stt_GetDataValueByID(pModule, _T("T1"), fT1);
		stt_GetDataValueByID(pModule, _T("T2"), fT2);
		stt_GetDataValueByID(pModule, _T("T3"), fT3);

		if (fT1 > 75)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_EXCEPTION,_T("模块(%s,%s)的温度(上)值(%f)超限值75°"),pModule->m_strName.GetString()
				,strModuleType.GetString(),fT1);
			bIsHot = TRUE;
		}

		if (fT2 > 75)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_EXCEPTION,_T("模块(%s,%s)的温度(下)值(%f)超限值75°"),pModule->m_strName.GetString()
				,strModuleType.GetString(),fT2);
			bIsHot = TRUE;
		}

		if (fT3 > 75)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_EXCEPTION,_T("模块(%s,%s)的温度(中)值(%f)超限值75°"),pModule->m_strName.GetString()
				,strModuleType.GetString(),fT3);
			bIsHot = TRUE;
		}

		posCh = pModule->GetHeadPosition();
		while(posCh != NULL)
		{
			p1 = pModule->GetNext(posCh);

			if (p1->m_strID == _T("DisableType"))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s被禁用(%s),模块类型(%s)."),pModule->m_strName.GetString(),p1->m_strName.GetString(),strModuleType.GetString());
			}

			if (p1->GetClassID() != DTMCLASSID_CDATAGROUP)
			{
				continue;
			}

			pCh = (CDataGroup *)p1;

			if (pCh->m_strDataType != _T("Channel"))
			{
				continue;
			}

			long nIsOverLoad = 0;
			stt_GetDataValueByID(pCh, _T("IsOverLoad"), nIsOverLoad);

			if (nIsOverLoad)
			{
				if (strModuleType == STT_MODULE_TYPE_VOLT_ID)
				{
					bIsUOverLoad = TRUE;
				}
				else
				{
					bIsIOverLoad = TRUE;
				}	
			}
		}
	}

	long nUdc = 0;
	stt_GetDataValueByID(pParas, STT_SYS_STATE_ID_Udc, nUdc);
//	UpdateIBreakUShortOverHeat(bIsIOverLoad,bIsUOverLoad,bIsHot);

	if (m_pLastEventResult == NULL)
	{
		m_pLastEventResult = &m_oCurrEventResult;
	}
	
	if((m_pLastEventResult->m_nUOverLoad != (long)bIsUOverLoad)
		|| (m_pLastEventResult->m_nIOverLoad != (long)bIsIOverLoad)
		|| (m_pLastEventResult->m_nOverHeat != (long)bIsHot)
		||(m_pLastEventResult->m_nUdc != nUdc))
	{
		CEventResult *pEventInfo = (CEventResult *)m_pLastEventResult->Clone();
		pEventInfo->m_nUOverLoad = bIsUOverLoad;
		pEventInfo->m_nIOverLoad = bIsIOverLoad;
		pEventInfo->m_nOverHeat = bIsHot;
		pEventInfo->m_nUdc = nUdc;

// 		long nSecond = 0,nNSecend = 0;
// 		stt_GetDataValueByID(pParas, _T("Utc_s"), nSecond);
// 		stt_GetDataValueByID(pParas, _T("Utc_ns"), nNSecend);

// 		SYSTEMTIME tmException;
// 		struct timeval ts;
// 		ts.tv_sec = nSecond;   //秒
// 		ts.tv_usec = nNSecend/1000;
// 		ep_cap_timeval_to_systime(ts,tmException);
// 		pEventInfo->m_tmEvent = tmException;

		if (bIsHot || bIsUOverLoad || bIsIOverLoad)
		{
			pEventInfo->m_strEventID = SYS_STATE_EXCEPTION;
		}
		else
		{
			pEventInfo->m_strEventID = SYS_STATE_UNEXCEPTION;
		}
		
		m_pLastEventResult = pEventInfo;

		AppenEventInfo(pEventInfo);
	}
}

void CSttPowerTestEngineBase::UpdateIBreakUShortOverHeat(long nIBreak,long nUShort,long nOverHeat)
{
	if (m_pXClientEngine == NULL)
	{
		return;
	}

	CExBaseList* pTestGlobalParas = m_pXClientEngine->GetTestGlobalParas();
	CString strValue;

	if (stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_IBreak, -1) != nIBreak)
	{
		strValue.Format(_T("%ld"),nIBreak);
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_IBreak, strValue); 
	}

	if (stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_UShort, -1) != nUShort)
	{
		strValue.Format(_T("%ld"),nUShort);
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_UShort, strValue); 
	}

	if (stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_OverHeat, -1) != nOverHeat)
	{
		strValue.Format(_T("%ld"),nOverHeat);
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_OverHeat, strValue); 
	}
}

void CSttPowerTestEngineBase::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{
	//yyj 20210809 
	if (g_bSaveFile)
	{
		SYSTEMTIME tm;
		::GetLocalTime(&tm);
		CString strTmpPath = _P_GetLibraryPath();
		strTmpPath.AppendFormat(_T("OnTestState%d-%d-%d %d-%d-%d.%d.xml"), tm.wYear, tm.wMonth, tm.wDay
			, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);
		pParas->SaveXmlFile(strTmpPath,CDataMngrXmlRWKeys::g_pXmlKeys);
	}
  	
	double fTime = 0,fRealTime = 0;
	CString strTimeStr;
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

// 	CDataGroup *pEventGroup = (CDataGroup *)pParas->FindByID(_T("Event"));
// 	if ((pEventGroup == NULL) 
// 		|| (pEventGroup->GetClassID() != DTMCLASSID_CDATAGROUP))
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("OnTestState:not find EventGroup"));
// 		return;
// 	}

	BOOL bRetIn = FALSE;
	BOOL bRetInEx = FALSE;
	BOOL bRetOut = FALSE; 
	BOOL bRetOutEx = FALSE;

	CString strTemp,strTmpTime;
	SYSTEMTIME tm;
	char strName[10];
	long nVal = 0;
	int i=0;

	CEventResult *pEventInfo = NULL;

	//处理开入变位
	if (pParas->m_strID == SYS_STATE_XEVENT_EVENTID_BIN)
	{
		if (!m_bLockFlag && fRealTime==0)
		{ 
			//开入(事件ID用参数更新)
			pEventInfo = InitEvent(SYS_STATE_RETTYPE_UPDATE,fTime,fRealTime,strTimeStr);
			for (i=1; i<=MAX_BINARYIN_COUNT; i++)
			{
				sprintf(strName,"Bin%03d",i);
				if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinIn[i-1]))
				{
					bRetIn = TRUE;
				}
			}

			if(bRetIn)
			{
				m_pLastEventResult = pEventInfo;
				AppenEventInfo(pEventInfo);
			}
			else
			{
				delete pEventInfo;
			}
			
			return;
		}

		pEventInfo = InitEvent(SYS_STATE_REPORT_OnSwichInChanged,fTime,fRealTime,strTimeStr);
		
		for (i=1; i<=MAX_BINARYIN_COUNT; i++)
		{
			sprintf(strName,"Bin%03d",i);
			if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinIn[i-1]))
			{
				bRetIn = TRUE;
			}
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BinEx%03d",i);
			if(stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinInEx[i-1]))
			{
				bRetInEx = TRUE;

				tm = pEventInfo->m_tmEvent;
				strTmpTime.Format(_T("%d-%d-%d %d-%d-%d.%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);

				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("扩展开入%d 状态：%d，变位时间：%s"),i,pEventInfo->m_BinInEx[i-1],strTmpTime.GetString());
			}
		}

		stt_GetDataValueByID(pParas, "BinActTime", pEventInfo->m_fActTime);	//取得开入动作时间

		if(bRetIn/*||bRetInEx*/)
		{
			m_pLastEventResult = pEventInfo;
			AppenEventInfo(pEventInfo);
		}
		else
		{
			delete pEventInfo;
		}
	}
	else if(pParas->m_strID == SYS_STATE_XEVENT_EVENTID_BOUT)
	{
		if (!m_bLockFlag && fRealTime==0)
		{ 
			//开出(事件ID用参数更新)
			pEventInfo = InitEvent(SYS_STATE_RETTYPE_UPDATE,fTime,fRealTime,strTimeStr);
			for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
			{
				sprintf(strName,"Bout%03d",i);
				if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinOut[i-1]))
				{
					bRetOut = TRUE;
				}
			}

			if(bRetOut)
			{
				m_pLastEventResult = pEventInfo;
				AppenEventInfo(pEventInfo);
			}
			else
			{
				delete pEventInfo;
			}

			return;
		}

		pEventInfo = InitEvent(SYS_STATE_REPORT_OnSwichOutChanged,fTime,fRealTime,strTimeStr);
		for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
		{
			sprintf(strName,"Bout%03d",i);
			if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinOut[i-1]))
			{
				bRetOut = TRUE;
			}
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BoutEx%03d",i);
			if(stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinOutEx[i-1]))
			{
				bRetOutEx = TRUE;

				tm = pEventInfo->m_tmEvent;
				strTmpTime.Format(_T("%d-%d-%d %d-%d-%d.%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);

//				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("扩展开出%d 状态：%d，变位时间：%s"),i,pEventInfo->m_BinOutEx[i-1],strTmpTime.GetString());
			}
		}

		if(bRetOut/*||bRetOutEx*/)
		{
			m_pLastEventResult = pEventInfo;
			AppenEventInfo(pEventInfo);
		}
		else
		{
			delete pEventInfo;
		}
	}
	else//如果没有开入、开出变位，则认为是状态切换或直流输出事件
	{
		if (stt_GetDataValueByID(pParas, STT_SYS_STATE_ID_StateChange, nVal))
		{
			if (nVal >= 0)
			{
				CEventResult *pEventInfo = InitEvent(SYS_STATE_REPORT_OnStateChanged,fTime,fRealTime,strTimeStr);
				pEventInfo->m_nCurrStateIndex = nVal;

				m_pLastEventResult = pEventInfo;
				AppenEventInfo(pEventInfo);
			}	
		}
	}
}

void CSttPowerTestEngineBase::OnReport(CDataGroup *pParas)
{
	if (pParas->m_strID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
		if (!m_bStarted)//zhouhj 2023.12.1 防止测试过程中，另外一台电脑连接机器,返回此信息
		{
			OnReport_ReadDevice(STT_CMD_TYPE_ADJUST_ReadDeviceParameter,pParas);
		}
	} 
}

void CSttPowerTestEngineBase::OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("OnReport"));

	if (pParas->m_strID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
		if (!m_bStarted)
		{
			OnReport_ReadDevice(STT_CMD_TYPE_ADJUST_ReadDeviceParameter,pParas);
		}
	} 
	else
	{
		CSttSysState *pSysState = (CSttSysState*)pParas->GetAncestor(STTCMDCLASSID_CSTTSYSSTATE);

		if (pSysState != NULL)
		{
			CSttMacro *pSttMacro = pSysState->GetSttMacro();
			CSttResults *pSttResults = pSttMacro->GetResults();

			if (pSttResults != NULL && pSttResults->GetCount()>0)
			{
				OnTestResults(pSttResults);
			}
		}
	}
}

void CSttPowerTestEngineBase::OnReport_ReadDevice(const CString &strMacroID, CDataGroup *pParas)
{

}

long CSttPowerTestEngineBase::OnUpdate(CSttParas *pParas)
{
	return 1;
}

//2022-10-6  lijunqing  美化OnRtData函数
void OnRtData_SttGlobalRtDataMngr(CDataGroup *pRtDataGroup)
{
	CSttGlobalRtDataMngr *pRtDataMngr = &g_oSttTestResourceMngr.m_oRtDataMngr;
	double dTime = 0,dRealTime = 0;
	dTime = 0,dRealTime = 0;

	if (!stt_GetDataValueByID(pRtDataGroup, TMT_RESULT_ID_Time, dTime))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取实时数据绝对时间失败."));
	}

	if (!stt_GetDataValueByID(pRtDataGroup, TMT_RESULT_ID_RealTime, dRealTime))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取实时数据相对时间失败."));
		return;
	}

	if (pRtDataMngr->m_nMode == STT_RT_DATA_MODE_SYN)
	{
		ASSERT(pRtDataMngr->m_pMacroChannels);
		CSttMacroChannels *pMacroChs = pRtDataMngr->m_pMacroChannels;
		CSttMacroChannel *pMacroCh = NULL;
		CDataGroup *pDataGroup = NULL;

		pMacroChs->m_oHisTimesBuf.AppendBuffer(&dTime,1);
		pMacroChs->m_oHisRealTimesBuf.AppendBuffer(&dRealTime,1);
		POS pos = pMacroChs->GetHeadPosition();

		//2023-12-25 zhouyangyong 故障通道特殊处理
		pDataGroup = (CDataGroup*)pRtDataGroup->FindByID("Uf");
		if (pDataGroup != NULL)
		{
			stt_GetDataValueByID(pDataGroup,_T("mag"), pMacroChs->m_oUfCh.m_oRtDataCh.m_fMag);
			stt_GetDataValueByID(pDataGroup,_T("ang"), pMacroChs->m_oUfCh.m_oRtDataCh.m_fAng);
			stt_GetDataValueByID(pDataGroup,_T("freq"), pMacroChs->m_oUfCh.m_oRtDataCh.m_fFreq);
			pMacroChs->m_oUfCh.m_oHisDataBuf.AppendBuffer(&pMacroChs->m_oUfCh.m_oRtDataCh,1);
		}
		pDataGroup = (CDataGroup*)pRtDataGroup->FindByID("If");
		if (pDataGroup != NULL)
		{
			stt_GetDataValueByID(pDataGroup,_T("mag"), pMacroChs->m_oIfCh.m_oRtDataCh.m_fMag);
			stt_GetDataValueByID(pDataGroup,_T("ang"), pMacroChs->m_oIfCh.m_oRtDataCh.m_fAng);
			stt_GetDataValueByID(pDataGroup,_T("freq"), pMacroChs->m_oIfCh.m_oRtDataCh.m_fFreq);
			pMacroChs->m_oUfCh.m_oHisDataBuf.AppendBuffer(&pMacroChs->m_oUfCh.m_oRtDataCh,1);
		}
		while(pos)
		{
			pMacroCh = (CSttMacroChannel *)pMacroChs->GetNext(pos);
			pDataGroup = (CDataGroup*)pRtDataGroup->FindByID(pMacroCh->m_strID);

			if (pDataGroup == NULL)
			{
				//					pMacroCh->m_oRtDataCh.m_fMag = 0;
				//					pMacroCh->m_oHisMagBuf.AppendBuffer(&pMacroCh->m_oRtDataCh.m_fMag,1);//yyj delete 2021-08-25
				pMacroCh->m_oHisDataBuf.AppendBuffer(&pMacroCh->m_oRtDataCh,1);	//yyj add 2021-08-25
				//					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("实时数据中缺少(name=%s;id=%s;)通道."),pMacroCh->m_strName.GetString(),pMacroCh->m_strID.GetString());
				continue;
			}

			stt_GetDataValueByID(pDataGroup,_T("mag"), pMacroCh->m_oRtDataCh.m_fMag);
			stt_GetDataValueByID(pDataGroup,_T("ang"), pMacroCh->m_oRtDataCh.m_fAng);
			stt_GetDataValueByID(pDataGroup,_T("freq"), pMacroCh->m_oRtDataCh.m_fFreq);
			//				pMacroCh->m_oHisMagBuf.AppendBuffer(&pMacroCh->m_oRtDataCh.m_fMag,1);//yyj delete 2021-08-25
			pMacroCh->m_oHisDataBuf.AppendBuffer(&pMacroCh->m_oRtDataCh,1);	//yyj add 2021-08-25
		}

		pRtDataMngr->FireRtDataChangeEvent(); //yyj add 20211108
	}
	else if (pRtDataMngr->m_nMode == STT_RT_DATA_MODE_ASYN)
	{
	}
	else
	{
		
	}
}

long CSttPowerTestEngineBase::OnRtData(CSttParas *pParas)
{
	CExBaseObject *pChildObj = NULL;
	POS pos = pParas->GetHeadPosition();
	CDataGroup *pRtDataGroup = NULL;

	while(pos)
	{
		pChildObj = pParas->GetNext(pos);

		if (pChildObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pRtDataGroup = (CDataGroup *)pChildObj;

		if (pRtDataGroup->m_strID == XPARA_ID_IEC_CB)
		{
			//m_pAtsEventRcv->On_IecDetect(pRtDataGroup);
			On_IecDetect(pRtDataGroup);
			continue;
		}

		if (pRtDataGroup->m_strID == SYS_STATE_XEVENT_EVENTID_SYNCTIME)
		{
			CDataGroup* pCopy = (CDataGroup*)pRtDataGroup->Clone();
			OnUpdateSyncTime(pCopy);
			continue;
		}


		if (m_bUpdateRtData)
		{

		//2022-10-6  lijunqing  美化OnRtData
		OnRtData_SttGlobalRtDataMngr(pRtDataGroup);  //美化函数
	}

	}
	
	return 1;
}

long CSttPowerTestEngineBase::OnDisConnect()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("OnDisConnect"));
	return 1;
}

long CSttPowerTestEngineBase::SendStartCmd()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	GenerateTestCmdFromParas(oSttCmd,true);

	//yyj 20210809 
	if (g_bSaveFile)
	{
		SYSTEMTIME tm;
		::GetLocalTime(&tm);
		CString strTmpPath = _P_GetLibraryPath();
		strTmpPath.AppendFormat(_T("StartCmd%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
			, tm.wHour, tm.wMinute, tm.wSecond);
		oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	}

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
//		m_oEventResultList.DeleteAll();
		m_oFlushEventList.DeleteAll();
		m_pLastEventResult = NULL;

		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendStopCmd()
{
	long nRet = 0;
	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		CSttTestCmd oSttCmd;
		oSttCmd.m_strID = STT_CMD_TYPE_TEST_StopTest;

		//yyj 20210809 
		if (g_bSaveFile)
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			CString strTmpPath = _P_GetLibraryPath();
			strTmpPath.AppendFormat(_T("Test_StopTest%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
				, tm.wHour, tm.wMinute, tm.wSecond);
			oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		}

		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}

	m_bStarted = false;
	return nRet;
}

long CSttPowerTestEngineBase::SendDefaultOutputCmd()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	GenerateTestCmdFromDefaultOutput(oSttCmd);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		//yyj 20210809 
		if (g_bSaveFile)
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			CString strTmpPath = _P_GetLibraryPath();
			strTmpPath.AppendFormat(_T("DefaultOutput%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
				, tm.wHour, tm.wMinute, tm.wSecond);
			oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		}

		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendUpdateParameter()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	UpdateTestCmdFromParas(oSttCmd,true);

	//yyj 20210809 
	if (g_bSaveFile)
	{
		SYSTEMTIME tm;
		::GetLocalTime(&tm);
		CString strTmpPath = _P_GetLibraryPath();
		strTmpPath.AppendFormat(_T("UpdateParameter%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
			, tm.wHour, tm.wMinute, tm.wSecond);
		oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	}

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendTrigger()
{
	long nRet = 0;
	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		nRet = m_pXClientEngine->Test_SendTrigger();
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendSystemParaCmd()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	GenerateTestCmdFromSystemParas(oSttCmd);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		//yyj 20210809 
		if (g_bSaveFile)
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			CString strTmpPath = _P_GetLibraryPath();
			strTmpPath.AppendFormat(_T("SystemParas%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
				, tm.wHour, tm.wMinute, tm.wSecond);
			oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		}
		
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendAuxDCOutputCmd()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	GenerateTestCmdFromAuxDCOutput(oSttCmd);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendModulesGearSwitchCmd()
{
	long nRet = 0;
	//读取命令参数
	CSttTestCmd oSttCmd;
	GenerateTestCmdFromModulesGearSwitch(oSttCmd);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendChMapsConfig()
{
	long nRet = 0;
	//读取命令参数
	CSttParas oParas;
	GenerateTestCmdFromChMaps(oParas);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		//yyj 20210809 
		if (g_bSaveFile)
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			CString strTmpPath = _P_GetLibraryPath();
			strTmpPath.AppendFormat(_T("ChMapsConfig%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
				, tm.wHour, tm.wMinute, tm.wSecond);
			oParas.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		}

		nRet = m_pXClientEngine->Test_SetParameter(_T("ChMapsConfig"),&oParas);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendIECParaCmd()
{
	long nRet = 0;

	CSttParas oParas;
	GenerateTestCmdFromIEC(oParas);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		//yyj 20210809 
		if (g_bSaveFile)
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			CString strTmpPath = _P_GetLibraryPath();
			strTmpPath.AppendFormat(_T("IEC61850CONFIG%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
				, tm.wHour, tm.wMinute, tm.wSecond);
			oParas.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		}

		nRet = m_pXClientEngine->Test_SetParameter(_T("Iec61850Config"), &oParas);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	oParas.RemoveAll();
	return nRet;
}

void CSttPowerTestEngineBase::GenerateTestCmdFromChMaps(CSttParas &oSttParas)
{
	CSttChMaps *pChMaps = (CSttChMaps*)g_oSttTestResourceMngr.m_oChMaps.Clone();
	oSttParas.AddNewChild(pChMaps);
}

long CSttPowerTestEngineBase::SendPTTestParaCmd()
{
	long nRet = 0;

	CSttTestCmd oSttCmd;
	GenerateTestCmdFromPTTestParas(oSttCmd);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		//yyj 20210809 
		if (g_bSaveFile)
		{
			SYSTEMTIME tm;
			::GetLocalTime(&tm);
			CString strTmpPath = _P_GetLibraryPath();
			strTmpPath.AppendFormat(_T("PTTestParas%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
				, tm.wHour, tm.wMinute, tm.wSecond);
			oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
		}
		
		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendReadDeviceParameter()
{
	long nRet = 0;

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		CStringArray astrType;
		astrType.Add(STT_CMD_PARA_DeviceAttrs);
		astrType.Add(STT_CMD_PARA_BoutTrunOnValueDef);
		astrType.Add(STT_CMD_PARA_ModuleAttrs);
		astrType.Add(STT_CMD_PARA_HdGears);
		astrType.Add(STT_CMD_PARA_ChMapDef);//zhouhj 20211006 增加用于上送混合插件的通道映射信息
		nRet = m_pXClientEngine->Adjust_ReadDeviceParameter(astrType);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

long CSttPowerTestEngineBase::SendDebugLogCmd(long nValue)
{
	long nRet = 0;

	CSttDebugCmd oDebugCmd;
	oDebugCmd.m_strID = STT_CMD_TYPE_DEBUG_ConfigDebug;
	oDebugCmd.AddNewParasData(STT_CMD_PARA_LogServerDebugInfor, nValue);
	oDebugCmd.AddNewParasData(STT_CMD_PARA_LogDebugInfor, nValue);

	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		nRet = m_pXClientEngine->Debug_ConfigDebug(&oDebugCmd);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
	}

	return nRet;
}

BOOL CSttPowerTestEngineBase::connectTestApp(const CString &strIP,long nPort,const CString &strSoftID)
{
	//连接登录
	CLogPrint::LogString(XLOGLEVEL_TRACE, "正在连接测试仪......");

	g_oSttTestAppConfigTool.m_pSttTestMsgViewInterface = this;
	BOOL bRet = g_oSttTestAppConfigTool.Local_ConnectServer(&g_oSttTestAppCfg,strIP,nPort,strSoftID);

	if(bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "测试仪连接成功");

		g_oSttTestAppCfg.SetTestAppIP(strIP);
		g_oSttTestAppCfg.SetTestServerPort(nPort);
	
		g_oSttTestAppConfigTool.GetSttTestEngineClientData(&m_pXClientEngine);//联机成功后，从Tool中获取Client对象
		m_pXClientEngine->SetTestEventInterface(this);
		SendReadDeviceParameter();//zhouhj 20210504 第一次联机成功后，固定读取装置的Device参数
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "连接测试仪失败，请检查网络链路是否连通，IP地址及端口配置是否正确；然后点击网络连接按钮重新连接");
	}

	return bRet;
}


//suyang 20230628 报文探测
#ifdef _PSX_IDE_QT_
void CSttPowerTestEngineBase::SendIecDetect(long bEnable,long nFT3_CrcType,long nIecType,QList<QVector<int>> oPkgLengthList)
{
	CDataGroup oGroup;
	oGroup.AddNewData(_T("Enable"), bEnable);
	oGroup.AddNewData(_T("Ft3_CRCType"), nFT3_CrcType);
	oGroup.AddNewData(_T("IecType"), nIecType);
	if(nFT3_CrcType == 1)
	{
		for(int i =0;i<oPkgLengthList.size();i++)
		{
			QVector<int> vectorAtFirst = oPkgLengthList.at(i);
			int first = vectorAtFirst[0];  // 1
			long nPkgLength = vectorAtFirst[1];
			CString strPkgName;
			strPkgName.Format(_T("Ft3_PkgLength%d"),first);
			oGroup.AddNewData(strPkgName, nPkgLength);//光口1 通道字节数相加，末尾校验
		}
		
	}
	
	m_pXClientEngine->Test_SetParameter(_T("IecDetect"), &oGroup);
}
#endif

void CSttPowerTestEngineBase::SendIecRecord(CDataGroup *pIecRecordParas)
{
	m_pXClientEngine->Test_SetParameter(_T("IecRecord"), pIecRecordParas);
}


//////

void CSttPowerTestEngineBase::FreeXClientEngine()
{
	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->PrepareFreeClientEngine();
//		m_pXClientEngine->DisConnect();
		delete m_pXClientEngine;
		m_pXClientEngine = NULL;
	}
}

void CSttPowerTestEngineBase::InitXmlKeys()
{
	_P_InitSystemPath();

	CSttSystemConfigXmlRWKeys::Create();
	CMacroXmlKeys::Create();
	CDataMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();

	CCfgDataMngrConstGlobal::Create();
	CFilterTextXmlRWKeys::Create();
	CSttCmdOverTimeTool::Create();
	CDeviceModelXmlKeys::Create();
}

void CSttPowerTestEngineBase::ReleaseXmlKeys()
{
	CSttSystemConfigXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CMacroXmlKeys::Release();

	CCfgDataMngrConstGlobal::Release();
	CFilterTextXmlRWKeys::Release();
	CSttCmdOverTimeTool::Release();
	CDeviceModelXmlKeys::Release();
}

void CSttPowerTestEngineBase::AppenEventInfo(CEventResult *pEventInfo)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	if (pEventInfo->m_strEventID.IsEmpty())
	{
		int nIndex = 0;
		nIndex++;
		pEventInfo->m_strEventID = _T("");
	}

	m_oFlushEventList.AddTail(pEventInfo);
}

void CSttPowerTestEngineBase::GetEventInfo(CExBaseList &oEventInfoList)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	oEventInfoList.AppendEx(m_oFlushEventList);
	m_oFlushEventList.RemoveAll();
}

void CSttPowerTestEngineBase::GenerateTestCmdFromDefaultOutput(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(TRUE,TRUE);
	pMacro->m_strID = MACROID_SttSystemDefaultOutput;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetParas();


	//序列化参数
	stt_xml_serialize(&g_oDefaultOutputPara, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.GetSttMacro()->DeleteAll();
	oSttTestCmd.GetSttMacro()->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(oSttTestCmd.GetSttMacro());

	CString strFile = _P_GetConfigPath();
	strFile += _T("SysOutputPara.sttxml");

	pMacro = oSttTestCmd.GetSttMacro();
	pMacro->SaveXmlFile(strFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CSttPowerTestEngineBase::GenerateTestCmdFromAuxDCOutput(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_SetParameter;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(TRUE,TRUE);
	pMacro->m_strID = STT_MACRO_ID_AuxDCOutput;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetParas();

	//序列化参数
	stt_xml_serialize_AuxDC(&g_oSystemParas, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.GetSttMacro()->DeleteAll();
	oSttTestCmd.GetSttMacro()->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(oSttTestCmd.GetSttMacro());
}

void CSttPowerTestEngineBase::GenerateTestCmdFromModulesGearSwitch(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_SetParameter;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(TRUE,TRUE);
	pMacro->m_strID = STT_MACRO_ID_ModulesGearSwitch;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetParas();

	//序列化参数
	stt_xml_serialize_ModulesGearSwitch(&g_oSystemParas, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.GetSttMacro()->DeleteAll();
	oSttTestCmd.GetSttMacro()->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(oSttTestCmd.GetSttMacro());
}

BOOL CSttPowerTestEngineBase::OpenSysOutputParaFile()
{
	CString strFile = _P_GetConfigPath();
	strFile += _T("SysOutputPara.sttxml");
	if(!IsFileExist(strFile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("稳态输出参数文件【%s】不存在"),strFile.GetString());
		return FALSE;
	}

	CSttTestCmd oSttCmd;
	CSttMacro *pSttMacro = oSttCmd.GetSttMacro(TRUE,TRUE);

	CSttXmlSerializeTool oSttXmlSerializeTool;
	if (oSttXmlSerializeTool.CreateXmlSerializeRead(pSttMacro, strFile) == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析稳态输出文件【%s】失败"),strFile.GetString());
		return FALSE;
	}

	pSttMacro->SetCreateMacroChild(TRUE);
	oSttXmlSerializeTool.SttXmlSerializeRead(pSttMacro);

	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();

	//解析生成结构体
	stt_xml_serialize(&g_oDefaultOutputPara, pMacroParas);

	//解析文件后，默认不输出
	g_oDefaultOutputPara.m_bUseSysOutput = FALSE;

	return TRUE;
}

// BOOL CSttPowerTestEngineBase::OpenSystemParasFile()
// {
// 	CString strFile = _P_GetConfigPath();
// 	strFile += _T("SystemParas.sysxml");
// 	if(!IsFileExist(strFile))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("系统参数文件【%s】不存在"),strFile);
// 		return FALSE;
// 	}
// 
// 	CSttTestCmd oSttCmd;
// 	CSttMacro *pSttMacro = oSttCmd.GetSttMacro(TRUE,TRUE);
// 
// 	CSttXmlSerializeTool oSttXmlSerializeTool;
// 	if (oSttXmlSerializeTool.CreateXmlSerializeRead(pSttMacro, strFile) == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析系统参数文件失败【%s】"),strFile);
// 		return 0;
// 	}
// 
// 	pSttMacro->SetCreateMacroChild(TRUE);
// 	oSttXmlSerializeTool.SttXmlSerializeRead(pSttMacro);
// 
// 	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();
// 
// 	//解析生成结构体
// 	stt_xml_serialize(&g_oSystemParas, pMacroParas);
// 
// 	return 1;
// }

void CSttPowerTestEngineBase::GenerateTestCmdFromSystemParas(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_SetParameter;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttMacro *pMacro = oSttTestCmd.GetSttMacro(TRUE,TRUE);
	pMacro->m_strID = MACROID_SttSystemPara;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetParas();

	//序列化参数
	stt_xml_serialize_SystemParas(&g_oSystemParas, pMacroParas);
	stt_xml_serialize_ModulesGearSwitch(&g_oSystemParas, pMacroParas);//zhouhj 2024.2.1 下发系统参数时,增加档位设置,防止测试仪底层档位与上位机不一致

	//根据pDoc生成对象
	oSttTestCmd.GetSttMacro()->DeleteAll();
	oSttTestCmd.GetSttMacro()->SetCreateMacroChild(true);
	oSttXmlSerializeTool.SttXmlSerializeRead(oSttTestCmd.GetSttMacro());

	//yyj 20210809 
	if (g_bSaveFile)
	{
		CString strFile = _P_GetConfigPath();
		strFile += _T("SystemParas.sysxml");
		oSttTestCmd.GetSttMacro()->SaveXmlFile(strFile,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	}
}

void CSttPowerTestEngineBase::GenerateTestCmdFromPTTestParas(CSttTestCmd &oSttTestCmd)
{
	oSttTestCmd.m_strID = STT_CMD_TYPE_TEST_StartTest;
	oSttTestCmd.m_strTestor = STT_SOFT_ID_TEST;

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->m_strID = MACROID_PTTestPara;

	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase* pMacroParas = oSttXmlSerializeTool.GetMacroParas();

	//序列化参数
	stt_xml_serialize(&g_oPTTestPara, pMacroParas);

	//根据pDoc生成对象
	oSttTestCmd.DeleteAll();
	oSttXmlSerializeTool.SttXmlSerializeRead(&oSttTestCmd);
}

//yyj 20210809
long CSttPowerTestEngineBase::Process_SysState_Log(CSttSysState &oSysState)
{
// 	if (!g_bPrintLog)
// 	{
// 		return 0;
// 	}

	CSttMsgs *pMsgs = oSysState.GetSttMsgs();
	POS pos = pMsgs->GetHeadPosition();
	CSttMsg *pData = NULL;
	CString strLog;

	while (pos != NULL)
	{
		pData = (CSttMsg *)pMsgs->GetNext(pos);

		//zhouhj 2023.9.15 测试服务上送的log信息,提取错误信息进行错误显示
		if (pData->m_strMsg.Find("[error]") != -1)
		{
			strLog = pData->m_strMsg;
			strLog.Replace("[error]","[tester error]");
			CLogPrint::LogString(XLOGLEVEL_ERROR, strLog);
		}
		else if (!m_bStarted)
		{
			return 0;
		}
		else
		{
			if (g_oSttSystemConfig.GetLogPrintValue())
			{
				strLog = _T("*********************");
				strLog += pData->m_strMsg;
				CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
			}
			
		}
	}

	return 0;
}
////////////////////////////////////
void InitDefaultSystemParas()
{
	g_oSystemParas.init();
}

void InitDefaultPtTestPara()
{
	g_oPTTestPara.init();
}

void InitDefualtSysOutputPara()
{
	g_oDefaultOutputPara.m_uiVOL[0].init(true, 57.735, 0, 50);
	g_oDefaultOutputPara.m_uiVOL[1].init(true, 57.735, -120, 50);
	g_oDefaultOutputPara.m_uiVOL[2].init(true, 57.735, 120, 50);
	g_oDefaultOutputPara.m_uiVOL[3].init(true, 57.735, 0, 50);
	g_oDefaultOutputPara.m_uiVOL[4].init(true, 57.735, -120, 50);
	g_oDefaultOutputPara.m_uiVOL[5].init(true, 57.735, 120, 50);

	g_oDefaultOutputPara.m_uiCUR[0].init(true, 1, 0, 50);
	g_oDefaultOutputPara.m_uiCUR[1].init(true, 1, -120, 50);
	g_oDefaultOutputPara.m_uiCUR[2].init(true, 1, 120, 50);
	g_oDefaultOutputPara.m_uiCUR[3].init(true, 1, 0, 50);
	g_oDefaultOutputPara.m_uiCUR[4].init(true, 1, -120, 50);
	g_oDefaultOutputPara.m_uiCUR[5].init(true, 1, 120, 50);
}

void stt_xml_serialize_write_SysOutput()
{
// 	TMT_SYSTEM_DEFAULT_OUTPUT_PARAS oSysOutput;
// 	oSysOutput.init();
// 	CSttXmlSerializeTool oSttXmlSerializeTool;
// 	CSttTestCmd oSttTestCmd;
// 	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
// 	pMacro->GetParas();
// 	pMacro->GetResults();
// 	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
// 	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
// 	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
// 	stt_xml_serialize(&oSysOutput, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("SysOutputPara.sttxml");
//  pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 
// 	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pRootMacro = NULL, *pParas = NULL;
	pRootMacro = oSttXmlSerializeTool.CreateXmlSerializeRegister(stt_TestMacroKey());
	pParas = pRootMacro->xml_serialize("paras", "paras", "paras", stt_ParasKey());
	stt_xml_serialize(&g_oDefaultOutputPara, pParas);
	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
