//////////////////////////////////////////////////////////////////////////
//ProtocolEngineClass.h
//规约引擎组件的接口定义和扩展文件

#ifndef _ProtocolEngine_CLASS_H__
#define _ProtocolEngine_CLASS_H__

namespace PpEngine
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

	class CValue : public COleDispatchDriver
	{
	public:
		CValue(){} // 调用 COleDispatchDriver 默认构造函数
		CValue(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CValue(const CValue& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IValue 方法
	public:

		// IValue 属性
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
		CString GetDataType()
		{
			CString result;
			GetProperty(0x3, VT_BSTR, (void*)&result);
			return result;
		}
		void SetDataType(CString propVal)
		{
			SetProperty(0x3, VT_BSTR, propVal);
		}
		CString GetValue()
		{
			CString result;
			GetProperty(0x4, VT_BSTR, (void*)&result);
			return result;
		}
		void SetValue(CString propVal)
		{
			SetProperty(0x4, VT_BSTR, propVal);
		}
		CString GetUnit()
		{
			CString result;
			GetProperty(0x5, VT_BSTR, (void*)&result);
			return result;
		}
		void SetUnit(CString propVal)
		{
			SetProperty(0x5, VT_BSTR, propVal);
		}

	};


	class CData : public COleDispatchDriver
	{
	public:
		CData(){} // 调用 COleDispatchDriver 默认构造函数
		CData(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CData(const CData& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IData 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long RegisterDataChangedWndMsg(unsigned long hWnd, unsigned long nWMsgID)
		{
			long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWnd, nWMsgID);
			return result;
		}
		long UnRegisterDataChangedWndMsg()
		{
			long result;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IData 属性
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
		CString GetDataType()
		{
			CString result;
			GetProperty(0x3, VT_BSTR, (void*)&result);
			return result;
		}
		void SetDataType(CString propVal)
		{
			SetProperty(0x3, VT_BSTR, propVal);
		}
		CString GetValue()
		{
			CString result;
			GetProperty(0x4, VT_BSTR, (void*)&result);
			return result;
		}
		void SetValue(CString propVal)
		{
			SetProperty(0x4, VT_BSTR, propVal);
		}
		CString GetUnit()
		{
			CString result;
			GetProperty(0x5, VT_BSTR, (void*)&result);
			return result;
		}
		void SetUnit(CString propVal)
		{
			SetProperty(0x5, VT_BSTR, propVal);
		}
		CString GetMinValue()
		{
			CString result;
			GetProperty(0x6, VT_BSTR, (void*)&result);
			return result;
		}
		void SetMinValue(CString propVal)
		{
			SetProperty(0x6, VT_BSTR, propVal);
		}
		CString GetMaxValue()
		{
			CString result;
			GetProperty(0x7, VT_BSTR, (void*)&result);
			return result;
		}
		void SetMaxValue(CString propVal)
		{
			SetProperty(0x7, VT_BSTR, propVal);
		}
	};


	class CDataSet : public COleDispatchDriver
	{
	public:
		CDataSet(){} // 调用 COleDispatchDriver 默认构造函数
		CDataSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CDataSet(const CDataSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IDataSet 方法
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
		long DeleteAllDatas()
		{
			long result;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		// IDataSet 属性
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


	class CLogicDevice : public COleDispatchDriver
	{
	public:
		CLogicDevice(){} // 调用 COleDispatchDriver 默认构造函数
		CLogicDevice(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CLogicDevice(const CLogicDevice& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ILogicDevice 方法
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
		LPDISPATCH FindDataSet(LPCTSTR strDatasetPath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDatasetPath);
			return result;
		}
		LPDISPATCH FindData(LPCTSTR strPath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strPath);
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

		// ILogicDevice 属性
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



	class CDevice : public COleDispatchDriver
	{
	public:
		CDevice(){} // 调用 COleDispatchDriver 默认构造函数
		CDevice(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CDevice(const CDevice& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IDevice 方法
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
		CString SetXmlDataEx(LPCTSTR strDatasetPath, LPCTSTR strXmlData)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDatasetPath, strXmlData);
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
			InvokeHelper(0x1A, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCommConfig);
			return result;
		}
		CString GetCommConfig(LPCTSTR strCommConfig)
		{
			CString result;
			InvokeHelper(0x1B, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetXmlDataLD()
		{
			CString result;
			InvokeHelper(0x1C, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetLogsXml()
		{
			CString result;
			InvokeHelper(0x1D, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString QueryRecord(LPCTSTR strBeginTime, LPCTSTR strEndTime, LPCTSTR strRcdFileName)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR;
			InvokeHelper(0x1E, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strBeginTime, strEndTime, strRcdFileName);
			return result;
		}
		long SetRecordPath(LPCTSTR strRcdPath)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1F, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strRcdPath);
			return result;
		}

		// IDevice 属性
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



	class CProtocolEngine : public COleDispatchDriver
	{
	public:
		CProtocolEngine(){} // 调用 COleDispatchDriver 默认构造函数
		CProtocolEngine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CProtocolEngine(const CProtocolEngine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
		LRESULT CreateInstance(const CString &strProgID)
		{
			return CreateDispatch(strProgID);
		}

		// 属性
	public:

		// 操作
	public:


		// IProtocolEngine 方法
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
		long ConfigEngine(LPCTSTR strDvmFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xA, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDvmFile);
			return result;
		}
		long AttatchLogWnd(unsigned long hWnd)
		{
			long result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0xB, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWnd);
			return result;
		}

		// IProtocolEngine 属性
	public:

	};

	// typedef CVtag IVtagPtr;
	// typedef CVtags IVtagsPtr;
	// typedef CDeviceNodeData IDeviceNodeDataPtr;
	typedef CValue IValuePtr;
	typedef CDataSet IDataSetPtr;
	typedef CData IDataPtr;
	typedef CLogicDevice ILogicDevicePtr;
	typedef CDevice IDevicePtr;
	typedef CProtocolEngine IPpEnginePtr;
};

#endif
