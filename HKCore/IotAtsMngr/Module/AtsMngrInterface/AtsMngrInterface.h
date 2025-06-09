#ifndef _ATS_MNGR_INTERFACE_H_
#define _ATS_MNGR_INTERFACE_H_

namespace AtsMngrInterface
{
	class CPoDataInterface : public COleDispatchDriver
	{
	public:
		CPoDataInterface(){} // 调用 COleDispatchDriver 默认构造函数
		CPoDataInterface(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CPoDataInterface(const CPoDataInterface& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IPoDataInterface 方法
	public:
		long Reset()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long AddData(LPCTSTR bstrID, LPCTSTR bstrValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrID, bstrValue);
			return result;
		}

		// IPoDataInterface 属性
	public:

	};

	class CPoDataSet : public COleDispatchDriver
	{
	public:
		CPoDataSet(){} // 调用 COleDispatchDriver 默认构造函数
		CPoDataSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CPoDataSet(const CPoDataSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IPoDataSet 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		LPDISPATCH FindDataByID(LPCTSTR strDataID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDataID);
			return result;
		}
		LPDISPATCH FindDataByName(LPCTSTR strName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strName);
			return result;
		}
		CString GetXmlData()
		{
			CString result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long SetXmlData(LPCTSTR strXmlData)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strXmlData);
			return result;
		}
		CString GetXmlDataEx()
		{
			CString result;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}

		// IPoDataSet 属性
	public:
		CString GetName()
		{
			CString result;
			GetProperty(0x1, VT_BSTR, (void*)&result);
			return result;
		}
		void SetName(CString propVal)
		{
			SetProperty(0x1, VT_BSTR, propVal);
		}
		CString GetID()
		{
			CString result;
			GetProperty(0x2, VT_BSTR, (void*)&result);
			return result;
		}
		void SetID(CString propVal)
		{
			SetProperty(0x2, VT_BSTR, propVal);
		}

	};

	class CPoDevice : public COleDispatchDriver
	{
	public:
		CPoDevice(){} // 调用 COleDispatchDriver 默认构造函数
		CPoDevice(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CPoDevice(const CPoDevice& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IPoDevice 方法
	public:
		long CommConfig(LPCTSTR strCmmConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCmmConfig);
			return result;
		}
		long IsConnectSuccessful()
		{
			long result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long GetCount()
		{
			long result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		LPDISPATCH FindDataSet(LPCTSTR strDataSetName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDataSetName);
			return result;
		}
		LPDISPATCH FindData(LPCTSTR strPath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strPath);
			return result;
		}
		long RunProcedure(LPCTSTR strProcedureID, LPCTSTR strDatasetPath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProcedureID, strDatasetPath);
			return result;
		}
		long RunProcedureEx(LPCTSTR strProcedureScript)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProcedureScript);
			return result;
		}
		long AttachSystemWndMsg(unsigned long hWnd, unsigned long nMsgID)
		{
			long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWnd, nMsgID);
			return result;
		}
		long RegisterProcedureWndMsg(LPCTSTR strProcedureID, unsigned long hWnd, unsigned long nMsgID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProcedureID, hWnd, nMsgID);
			return result;
		}
		long UnRegisterProcedureWndMsg(LPCTSTR strProcedureID, unsigned long hWnd, unsigned long nMsgID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProcedureID, hWnd, nMsgID);
			return result;
		}
		long RegisterDataChangedWndMsg(LPCTSTR strDataPath, unsigned long hWnd, unsigned long nWMsgID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDataPath, hWnd, nWMsgID);
			return result;
		}
		long UnRegisterDataChangedWndMsg(LPCTSTR strDataPath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDataPath);
			return result;
		}
		long UnLoad()
		{
			long result;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString GetXmlData()
		{
			CString result;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long SetXmlData(LPCTSTR bstrXmlData)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrXmlData);
			return result;
		}
		CString GetXmlDataEx(LPCTSTR strDatasetPath)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDatasetPath);
			return result;
		}
		long SetXmlDataEx(LPCTSTR strDatasetPath, LPCTSTR strXmlData)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDatasetPath, strXmlData);
			return result;
		}
		LPDISPATCH GetDataInterface()
		{
			LPDISPATCH result;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long ConnectDevice()
		{
			long result;
			InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		CString GetAttrByID(LPCTSTR strAttrID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strAttrID);
			return result;
		}
		long SetAttrByID(LPCTSTR strAttrID, LPCTSTR strValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strAttrID, strValue);
			return result;
		}
		long SaveDvmFile(LPCTSTR strDvmFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDvmFile);
			return result;
		}
		long SetCommConfig(LPCTSTR strCommConfig)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCommConfig);
			return result;
		}
		CString GetCommConfig()
		{
			CString result;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetXmlDataLD()
		{
			CString result;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetLogsXml()
		{
			CString result;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}

		// IPoDevice 属性
	public:
		CString GetName()
		{
			CString result;
			GetProperty(0x1, VT_BSTR, (void*)&result);
			return result;
		}
		void SetName(CString propVal)
		{
			SetProperty(0x1, VT_BSTR, propVal);
		}
		CString GetID()
		{
			CString result;
			GetProperty(0x2, VT_BSTR, (void*)&result);
			return result;
		}
		void SetID(CString propVal)
		{
			SetProperty(0x2, VT_BSTR, propVal);
		}

	};
	class CPoEngine : public COleDispatchDriver
	{
	public:
		CPoEngine(){} // 调用 COleDispatchDriver 默认构造函数
		CPoEngine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CPoEngine(const CPoEngine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IPoEngine 方法
	public:
		CString GetVersion()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH CreateDevice(LPCTSTR strTemplateFile, LPCTSTR strDeviceFile, LPCTSTR strDeviceID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strTemplateFile, strDeviceFile, strDeviceID);
			return result;
		}
		long GetCount()
		{
			long result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long ShowSpyWnd(long nShow)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nShow);
			return result;
		}
		long ReleaseDevice(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long ReleaseAllDevice()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long CreateProject(LPCTSTR strProjectFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProjectFile);
			return result;
		}
		long SetProtocolParse(long nStopFlag)
		{
			long result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nStopFlag);
			return result;
		}

		// IPoEngine 属性
	public:

	};
};

class CAtsMngrInterface
{
private://全局唯一对象，构造函数、析构函数，必须是私有或者保护的
	CAtsMngrInterface();
	virtual ~CAtsMngrInterface();

	static long g_nInterfaceRef;
	static CAtsMngrInterface* g_pAtsMngrInterface;

	AtsMngrInterface::CPoEngine m_oXAtsEngine;
public:
	static CAtsMngrInterface* Create();
	static void Release();

	static long CreateDevice(const CString &strTemplateFile,const CString &strDeviceFile,const CString &strDeviceID);

protected:
	BOOL InitAtsMngrInterface();
	void OnRelease();
};

#endif