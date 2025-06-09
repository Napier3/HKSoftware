#ifndef _IecConfigInterface_h__
#define _IecConfigInterface_h__

namespace Iec61850Config 
{
	// CTestAppMngr 包装类
	class CTestEngine : public COleDispatchDriver
	{
	public:
		CTestEngine(){} // 调用 COleDispatchDriver 默认构造函数
		CTestEngine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CTestEngine(const CTestEngine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// Iec61850Config 方法
	public:
		long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID)
		{
			long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMainWnd, nMsgID);
			return result;
		}
		long OpenSCDFile(LPCTSTR strScdFilePath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strScdFilePath);
			return result;
		}
		long OpenTscdFile(LPCTSTR strTscdFilePath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTscdFilePath);
			return result;
		}
		long SetDestPath(LPCTSTR strDestPath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDestPath);
			return result;
		}
		long NewIecfgFile(LPCTSTR strIedName,LPCTSTR strSrcIecfgFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIedName, strSrcIecfgFile);
			return result;
		}
		long EditIecfgFile(LPCTSTR strIecfgFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIecfgFile);
			return result;
		}
		long SaveIecfgFile(LPCTSTR strIecfgFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIecfgFile);
			return result;
		}
		long CloseIecfgFile(LPCTSTR strIecfgFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIecfgFile);
			return result;
		}
// 		ULONG NewCfgFile(LPCTSTR strTsdFilePath, LPCTSTR strIEDName, LPCTSTR strSavePath)
// 		{
// 			long result;
// 			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
// 			InvokeHelper(0x2, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strTsdFilePath, strIEDName,strSavePath);
// 			return result;
// 		}
// 		ULONG EditCfgFile(LPCTSTR strCfgFilePath)
// 		{
// 			long result;
// 			static BYTE parms[] = VTS_BSTR ;
// 			InvokeHelper(0x3, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strCfgFilePath);
// 			return result;
// 		}
		ULONG ExitEngine()
		{
			long result;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}

		// ITestAppMngr 属性
	public:
	};
};
#endif // _DvmTestInterface_h__

