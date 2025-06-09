#pragma once

namespace AtsSysSvr 
{
	class CExeModule : public COleDispatchDriver
	{
	public:
		CExeModule(){} // 调用 COleDispatchDriver 默认构造函数
		CExeModule(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CExeModule(const CExeModule& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IExeModule 方法
	public:
		unsigned long PostWndMessage(LPCTSTR strModuleID, LPCTSTR strMsgID, LPCTSTR strMsgPara)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strModuleID, strMsgID, strMsgPara);
			return result;
		}
		long GetCount()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long AddPara(LPCTSTR strName, LPCTSTR strID, LPCTSTR strPara)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, strID, strPara);
			return result;
		}
		long DeletePara(LPCTSTR strID, LPCTSTR strPara)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strID, strPara);
			return result;
		}
		long PostSysMsg(long nSysMsgIndex)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nSysMsgIndex);
			return result;
		}
		long IsParaExist(LPCTSTR strID, LPCTSTR strPara)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strID, strPara);
			return result;
		}

		// IExeModule 属性
	public:
		CString GetID()
		{
			CString result;
			GetProperty(0x1, VT_BSTR, (void*)&result);
			return result;
		}
		void SetID(CString propVal)
		{
			SetProperty(0x1, VT_BSTR, propVal);
		}
		CString GetName()
		{
			CString result;
			GetProperty(0x2, VT_BSTR, (void*)&result);
			return result;
		}
		void SetName(CString propVal)
		{
			SetProperty(0x2, VT_BSTR, propVal);
		}
		unsigned long GetMsgRcvWnd()
		{
			unsigned long result;
			GetProperty(0x3, VT_UI4, (void*)&result);
			return result;
		}
		void SetMsgRcvWnd(unsigned long propVal)
		{
			SetProperty(0x3, VT_UI4, propVal);
		}
		unsigned long GetMsgRcvThreadID()
		{
			unsigned long result;
			GetProperty(0x4, VT_UI4, (void*)&result);
			return result;
		}
		void SetMsgRcvThreadID(unsigned long propVal)
		{
			SetProperty(0x4, VT_UI4, propVal);
		}
		unsigned long GetWM_MsgID()
		{
			unsigned long result;
			GetProperty(0x5, VT_UI4, (void*)&result);
			return result;
		}
		void SetWM_MsgID(unsigned long propVal)
		{
			SetProperty(0x5, VT_UI4, propVal);
		}

	};

	// CSysData 包装类

	class CSysData : public COleDispatchDriver
	{
	public:
		CSysData(){} // 调用 COleDispatchDriver 默认构造函数
		CSysData(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CSysData(const CSysData& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ISysData 方法
	public:

		// ISysData 属性
	public:
		CString GetID()
		{
			CString result;
			GetProperty(0x1, VT_BSTR, (void*)&result);
			return result;
		}
		void SetID(CString propVal)
		{
			SetProperty(0x1, VT_BSTR, propVal);
		}
		CString GetName()
		{
			CString result;
			GetProperty(0x2, VT_BSTR, (void*)&result);
			return result;
		}
		void SetName(CString propVal)
		{
			SetProperty(0x2, VT_BSTR, propVal);
		}
		CString GetValue()
		{
			CString result;
			GetProperty(0x3, VT_BSTR, (void*)&result);
			return result;
		}
		void SetValue(CString propVal)
		{
			SetProperty(0x3, VT_BSTR, propVal);
		}

	};

	// CSysMsg 包装类

	class CSysMsg : public COleDispatchDriver
	{
	public:
		CSysMsg(){} // 调用 COleDispatchDriver 默认构造函数
		CSysMsg(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CSysMsg(const CSysMsg& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ISysMsg 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long AddSysData(LPCTSTR strName, LPCTSTR strID, LPCTSTR strValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strName, strID, strValue);
			return result;
		}
		CString FindParaByID(LPCTSTR strID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strID);
			return result;
		}

		// ISysMsg 属性
	public:
		unsigned long GetMsgIndex()
		{
			unsigned long result;
			GetProperty(0x1, VT_UI4, (void*)&result);
			return result;
		}
		void SetMsgIndex(unsigned long propVal)
		{
			SetProperty(0x1, VT_UI4, propVal);
		}
		CString GetMsgID()
		{
			CString result;
			GetProperty(0x2, VT_BSTR, (void*)&result);
			return result;
		}
		void SetMsgID(CString propVal)
		{
			SetProperty(0x2, VT_BSTR, propVal);
		}
		CString GetMsgPara()
		{
			CString result;
			GetProperty(0x3, VT_BSTR, (void*)&result);
			return result;
		}
		void SetMsgPara(CString propVal)
		{
			SetProperty(0x3, VT_BSTR, propVal);
		}

	};

	// CSysSvrApp 包装类

	class CSysSvrApp : public COleDispatchDriver
	{
	public:
		CSysSvrApp(){} // 调用 COleDispatchDriver 默认构造函数
		CSysSvrApp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CSysSvrApp(const CSysSvrApp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ISysSvrApp 方法
	public:
		LPDISPATCH RegisterModule(LPCTSTR strName, LPCTSTR strID, unsigned long nMsgWnd, unsigned long nMsgThreadID, unsigned long nMsgID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strName, strID, nMsgWnd, nMsgThreadID, nMsgID);
			return result;
		}
		unsigned long FindModule(LPCTSTR strID)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strID);
			return result;
		}
		unsigned long OpenModule(LPCTSTR strModuleID, LPCTSTR strPara)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strModuleID, strPara);
			return result;
		}
		unsigned long UnRegisterModule(LPCTSTR strModule)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strModule);
			return result;
		}
		LPDISPATCH GetSysMsg(long nMsgIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nMsgIndex);
			return result;
		}
		unsigned long DeleteSysMsg(long nMsgIndex)
		{
			unsigned long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, nMsgIndex);
			return result;
		}
		unsigned long RegModuleOptrMsgSend(LPCTSTR strID, LPCTSTR strOptrID, unsigned long nMsgWnd, unsigned long nMsgThreadID, unsigned long nMsgID)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strID, strOptrID, nMsgWnd, nMsgThreadID, nMsgID);
			return result;
		}
		unsigned long UnRegModuleOptrMsgSend(LPCTSTR strID, LPCTSTR strOptrID, unsigned long nMsgWnd, unsigned long nMsgThreadID, unsigned long nMsgID)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strID, strOptrID, nMsgWnd, nMsgThreadID, nMsgID);
			return result;
		}
		unsigned long PostModuleOptrMsg(LPCTSTR strModuleID, LPCTSTR bstrOptrID, long nSysMsgIndex)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strModuleID, bstrOptrID, nSysMsgIndex);
			return result;
		}
		LPDISPATCH GetModuleByID(LPCTSTR strModuleID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strModuleID);
			return result;
		}
		LPDISPATCH CreateNewSysMsg(LPCTSTR strMsgID, LPCTSTR strMsgPara)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strMsgID, strMsgPara);
			return result;
		}
		long OpenModuleEx(LPCTSTR strModuleID, long nSysMsgIndex)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strModuleID, nSysMsgIndex);
			return result;
		}
		long WriteFlag(LPCTSTR bstrFlagID, LPCTSTR bstrFlagValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrFlagID, bstrFlagValue);
			return result;
		}
		CString GetFlag(LPCTSTR strFlagID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strFlagID);
			return result;
		}
		// ISysSvrApp 属性
	public:

	};
}