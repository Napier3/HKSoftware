#ifndef _IecConfigInterface_h__
#define _IecConfigInterface_h__

#include <ActiveQt/QAxObject>
#include <activeqt/qaxwidget>

#define _DISP_MODE_NORMAL            0
#define _DISP_MODE_AT02D             1
#define _DISP_MODE_PNI302            2
#define _DISP_MODE_PN466             3

namespace Iec61850Config 
{
	// CTestAppMngr 包装类
	class CTestEngine : public QAxObject
	{
	public:
		CTestEngine(){} // 调用 COleDispatchDriver 默认构造函数
// 		CTestEngine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
// 		CTestEngine(const CTestEngine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// Iec61850Config 方法
	public:
		long SetWndMsg(unsigned int hMainWnd, unsigned int nMsgID)
		{
			long result;
			result = dynamicCall("SetWndMsg(unsigned int,unsigned int)",hMainWnd,nMsgID).toInt();
// 			static BYTE parms[] = VTS_UI4 VTS_UI4 ;
// 			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hMainWnd, nMsgID);
			return result;
		}
		long OpenSCDFile(const QString &strScdFilePath)
		{
			long result;
			result = dynamicCall("OpenSCDFile(const QString &)",strScdFilePath).toInt();
// 			static BYTE parms[] = VTS_BSTR ;
// 			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strScdFilePath);
			return result;
		}
		long OpenTscdFile(const QString &strTscdFilePath)
		{
			long result;
			result = dynamicCall("OpenTscdFile(const QString &)",strTscdFilePath).toInt();
// 			static BYTE parms[] = VTS_BSTR ;
// 			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTscdFilePath);
			return result;
		}
		long SetDestPath(const QString &strDestPath)
		{
			long result;
			result = dynamicCall("SetDestPath(const QString &)",strDestPath).toInt();
// 			static BYTE parms[] = VTS_BSTR ;
// 			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDestPath);
			return result;
		}
		long NewIecfgFile(const QString &strIedName,const QString &strSrcIecfgFile)
		{
			long result;
			result = dynamicCall("NewIecfgFile(const QString &,const QString &)",strIedName,strSrcIecfgFile).toInt();
// 			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
// 			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIedName, strSrcIecfgFile);
			return result;
		}
		long EditIecfgFile(const QString &strIecfgFile)
		{
			long result;
			result = dynamicCall("EditIecfgFile(const QString &)",strIecfgFile).toInt();
// 			static BYTE parms[] = VTS_BSTR ;
// 			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIecfgFile);
			return result;
		}
		long SaveIecfgFile(const QString &strIecfgFile)
		{
			long result;
			result = dynamicCall("SaveIecfgFile(const QString &)",strIecfgFile).toInt();
// 			static BYTE parms[] = VTS_BSTR ;
// 			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIecfgFile);
			return result;
		}
		long CloseIecfgFile(const QString &strIecfgFile)
		{
			long result;
			result = dynamicCall("CloseIecfgFile(const QString &)",strIecfgFile).toInt();
// 			static BYTE parms[] = VTS_BSTR ;
// 			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIecfgFile);
			return result;
		}
		unsigned int ExitEngine()
		{
 			unsigned int result;
			result = dynamicCall("ExitEngine(void)").toUInt();
// 			InvokeHelper(0x9, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		long ExportAt02dFiles(const QString &strDesIecfgPath,const QString &strCbXml)
		{
			long result;
			result = dynamicCall("ExportAt02dFiles(const QString &,const QString &)",strDesIecfgPath,strCbXml).toInt();
// 			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
// 			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strIedName, strSrcIecfgFile);
			return result;
		}

		void SetDispMode(int nMode)
		{
			dynamicCall("SetDispMode(int)",nMode);
		}

		long CommConfig(const QString &strCmmConfig)
		{
			long result;
			result = dynamicCall("CommConfig(const QString &)",strCmmConfig).toInt();
			return result;
		}

		// ITestAppMngr 属性
	public:
	};
};
#endif // _DvmTestInterface_h__

