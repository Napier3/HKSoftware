// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#ifndef _Yun_Interface_h__
#define _Yun_Interface_h__

namespace Yun
{
	// IYunApp 包装类

	class IYunApp : public COleDispatchDriver
	{
	public:
		IYunApp(){} // 调用 COleDispatchDriver 默认构造函数
		IYunApp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IYunApp(const IYunApp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IYunApp 方法
	public:
		long Login(LPCTSTR bstrConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrConfig);
			return result;
		}
		long Logout()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long Config(LPCTSTR bstrConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrConfig);
			return result;
		}
		CString GetConfig()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH CreateYunFileFind()
		{
			LPDISPATCH result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH CreateYunOper()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH CreateTasks()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long AttachMsgRcv(long hMsgRcvWnd, long nMsg)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMsgRcvWnd, nMsg);
			return result;
		}

		// IYunApp 属性
	public:

	};


	class IYunFileFind : public COleDispatchDriver
	{
	public:
		IYunFileFind(){} // 调用 COleDispatchDriver 默认构造函数
		IYunFileFind(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IYunFileFind(const IYunFileFind& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IYunFileFind 方法
	public:
		long FindFile(LPCTSTR strPath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPath);
			return result;
		}
		long Close()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long GetNextFile()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString GetFileName()
		{
			CString result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetFilePath()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetRoot()
		{
			CString result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		DATE GetLastWriteTime()
		{
			DATE result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DATE, (void*)&result, NULL);
			return result;
		}
		long IsDots()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long IsDirectory()
		{
			long result;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long IsArchived()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long GetFileSize()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IYunFileFind 属性
	public:

	};

	class IYunOper : public COleDispatchDriver
	{
	public:
		IYunOper(){} // 调用 COleDispatchDriver 默认构造函数
		IYunOper(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IYunOper(const IYunOper& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IYunOper 方法
	public:
		long DownloadFile(LPCTSTR bstrLocalFile, LPCTSTR bstrYunFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrLocalFile, bstrYunFile);
			return result;
		}
		long DownloadFolder(LPCTSTR bstrLocalFolder, LPCTSTR bstrYunFolder, long bSubFolder)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrLocalFolder, bstrYunFolder, bSubFolder);
			return result;
		}
		long UploadFile(LPCTSTR bstrLocalFile, LPCTSTR bstrYunFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrLocalFile, bstrYunFile);
			return result;
		}
		long UploadFolder(LPCTSTR bstrLocalFolder, LPCTSTR bstrYunFolder, long bSubFolder)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrLocalFolder, bstrYunFolder, bSubFolder);
			return result;
		}
		long CreateFolder(LPCTSTR bstrYunFolder)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrYunFolder);
			return result;
		}
		long DelFile(LPCTSTR bstrYunFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrYunFile);
			return result;
		}
		long DelFolder(LPCTSTR bstrYunFolder)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrYunFolder);
			return result;
		}
		long SetBatchMode(long bBatchMode, long hWndRcvMsg, long nOperRsltMsg)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bBatchMode, hWndRcvMsg, nOperRsltMsg);
			return result;
		}
		unsigned long BatchOper(long nBatchOper)
		{
			unsigned long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, nBatchOper);
			return result;
		}

		// IYunOper 属性
	public:

	};

	class IXDbTasks : public COleDispatchDriver
	{
	public:
		IXDbTasks(){} // 调用 COleDispatchDriver 默认构造函数
		IXDbTasks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		IXDbTasks(const IXDbTasks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IXDbTasks 方法
	public:
		long PopTasksSelWnd(LPCTSTR strPara, long nPara)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_I4 ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPara, nPara);
			return result;
		}
		CString GetTasksXml(LPCTSTR bstrPara)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, bstrPara);
			return result;
		}
		long SetTasksXml(LPCTSTR bstrTasksXml)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrTasksXml);
			return result;
		}
		CString DownLoad(LPCTSTR bstrPara)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, bstrPara);
			return result;
		}

		// IXDbTasks 属性
	public:

	};

}


#endif

