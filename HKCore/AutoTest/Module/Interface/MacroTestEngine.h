// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IMacroTestEngine wrapper class

#ifndef _macrotestengine_h__
#define _macrotestengine_h__

namespace MacroTest 
{

	class IMacroTestEngine : public COleDispatchDriver
	{
	public:
		IMacroTestEngine() {}		// Calls COleDispatchDriver default constructor
		IMacroTestEngine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMacroTestEngine(const IMacroTestEngine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Attributes
	public:

		// Operations
	public:
		LPDISPATCH CreateMacroTest(LPCTSTR bstrConfig)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, bstrConfig);
			return result;
		}
		long ExitEngine()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long ExcuteCmd(LPCTSTR strCmdID, LPCTSTR strCmdParameter)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCmdID, strCmdParameter);
			return result;
		}
		long ShowSpyWnd(long nShow)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nShow);
			return result;
		}
		long BioExtendTest(LPCTSTR bstrPara)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, bstrPara);
			return result;
		}
		long ConfigEngine()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long AttatchLogWnd(unsigned long hWnd)
		{
			long result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWnd);
			return result;
		}

	};
	/////////////////////////////////////////////////////////////////////////////
	// IMacroTest wrapper class

	class IMacroTest : public COleDispatchDriver
	{
	public:
		IMacroTest() {}		// Calls COleDispatchDriver default constructor
		IMacroTest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IMacroTest(const IMacroTest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// Attributes
	public:

		// Operations
	public:
		long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID)
		{
			long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMainWnd, nMsgID);
			return result;
		}
		CString GetConfig()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long SetConfig(LPCTSTR bstrConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrConfig);
			return result;
		}
		long Test(LPCTSTR strMacroID, LPCTSTR strParameter)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strMacroID, strParameter);
			return result;
		}
		CString GetReport()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long StopTest()
		{
			long result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long CloseDevice()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString GetSearchReport()
		{
			CString result;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long FinishTest(long nState)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nState);
			return result;
		}
		long ExcuteCmd(LPCTSTR strCmdID, LPCTSTR strCmdParameter)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCmdID, strCmdParameter);
			return result;
		}
		long TestEx(LPCTSTR strMacroID, LPCTSTR strParameter, LPCTSTR strTestMode)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strMacroID, strParameter, strTestMode);
			return result;
		}
		unsigned long GetExternMsgRcvWnd()
		{
			unsigned long result;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		unsigned long GetExternMsgID()
		{
			unsigned long result;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		unsigned long StopDevice(void)
		{
			unsigned long result;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}

	};

//2020-10-17  定义改到  SttStudio\Module\SmartTestInterface\MacroTestInterface.h
// 	enum MtSpyWndShow
// 	{
// 		TmtSpyShow_Hide = 0,
// 		TmtSpyShow_Show = 1,
// 		TmtSpyShow_MinSize = 2,
// 		TmtSpyShow_MaxSize = 3,
// 		TmtSpyShow_Close = 4,
// 		TmtSpyShow_ShowCenter = 5
// 	};
// 
// 	enum MtMessageID
// 	{
// 		MTMSG_ConnectSuccess=0,
// 		MTMSG_ConnectFaild=1,
// 		MTMSG_ConnectConfig=2,
// 		MTMSG_TestBegin=3,
// 		MTMSG_TestFinished=4, 
// 		MTMSG_SearchPointFinished=5, 
// 		MTMSG_CommError=6,
// 		MTMSG_Not_Surport=7,
// 		MTMSG_ManualTestBegin=8,
// 		MTMSG_ManualTestReturn=9,
// 		MTMSG_ManualTestStop=10,
// 		MTMSG_ShowCurItem=11,
// 		MTMSG_TestOverTime=12,
// 		MTMSG_AppWarning=13,
// 		MTMSG_AppError=14
// 	};

}

#endif
