//////////////////////////////////////////////////////////////////////////
//PpEngineClass.h
//规约引擎组件的接口定义和扩展文件

#ifndef _PPENGINE_CLASS_H__
#define _PPENGINE_CLASS_H__

namespace PpEngine
{
	// CVtag 包装类

	class CVtag : public COleDispatchDriver
	{
	public:
		CVtag(){} // 调用 COleDispatchDriver 默认构造函数
		CVtag(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVtag(const CVtag& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVtag 方法
	public:

		// IVtag 属性
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
		CString GetValue()
		{
			CString result;
			GetProperty(0x2, VT_BSTR, (void*)&result);
			return result;
		}
		void SetValue(CString propVal)
		{
			SetProperty(0x2, VT_BSTR, propVal);
		}

	};



	class CVtags : public COleDispatchDriver
	{
	public:
		CVtags(){} // 调用 COleDispatchDriver 默认构造函数
		CVtags(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CVtags(const CVtags& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IVtags 方法
	public:
		unsigned long GetCount()
		{
			unsigned long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		LPDISPATCH FindTag(LPCTSTR strTagID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strTagID);
			return result;
		}

		// IVtags 属性
	public:

	};



	class CDeviceNodeData : public COleDispatchDriver
	{
	public:
		CDeviceNodeData(){} // 调用 COleDispatchDriver 默认构造函数
		CDeviceNodeData(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CDeviceNodeData(const CDeviceNodeData& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IDeviceNodeData 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		LPDISPATCH FindTag(LPCTSTR strTagID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strTagID);
			return result;
		}
		CString GetAttribute(LPCTSTR strTagID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strTagID);
			return result;
		}
		unsigned long SetAttribute(LPCTSTR strTagID, LPCTSTR strValue)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strTagID, strValue);
			return result;
		}
		long GetDmIndex()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}

		// IDeviceNodeData 属性
	public:
		long GetIndex()
		{
			long result;
			GetProperty(0x1, VT_I4, (void*)&result);
			return result;
		}
		void SetIndex(long propVal)
		{
			SetProperty(0x1, VT_I4, propVal);
		}

	};



	class CDeviceNode : public COleDispatchDriver
	{
	public:
		CDeviceNode(){} // 调用 COleDispatchDriver 默认构造函数
		CDeviceNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CDeviceNode(const CDeviceNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// IDeviceNode 方法
	public:
		long GetCount()
		{
			long result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		LPDISPATCH GetVtags()
		{
			LPDISPATCH result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		unsigned long IsDataNode()
		{
			unsigned long result;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		CString GetNodeName()
		{
			CString result;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetNodeData(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		LPDISPATCH FindNode(LPCTSTR strNodeName)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strNodeName);
			return result;
		}
		LPDISPATCH FindNodeEx(LPCTSTR strNodeName, LPCTSTR strAttrTagID, LPCTSTR strAttrValue)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strNodeName, strAttrTagID, strAttrValue);
			return result;
		}
		LPDISPATCH FindData(LPCTSTR strDataAttrID, LPCTSTR strDataAttrValue)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strDataAttrID, strDataAttrValue);
			return result;
		}
		long GetDmIndex()
		{
			long result;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH FindByDmIndex(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		unsigned long DeleteAllNodeData()
		{
			unsigned long result;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		CString GetXmlData()
		{
			CString result;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long SetXmlData(LPCTSTR bstrXmlData)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrXmlData);
			return result;
		}

		// IDeviceNode 属性
	public:

	};



	class CCommConfig : public COleDispatchDriver
	{
	public:
		CCommConfig(){} // 调用 COleDispatchDriver 默认构造函数
		CCommConfig(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CCommConfig(const CCommConfig& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

		// 属性
	public:

		// 操作
	public:


		// ICommConfig 方法
	public:

		// ICommConfig 属性
	public:

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
		LPDISPATCH GetVtags()
		{
			LPDISPATCH result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		CString GetTemplateFile()
		{
			CString result;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetDeviceFile()
		{
			CString result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		long LoadTemplateFile(LPCTSTR strTemplateFile, LPCTSTR strDeviceFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strTemplateFile, strDeviceFile);
			return result;
		}
		long CommConfig(LPDISPATCH pCmmConfig)
		{
			long result;
			static BYTE parms[] = VTS_DISPATCH ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCmmConfig);
			return result;
		}
		LPDISPATCH GetDeviceModelDefine()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetDeviceModelTemplate()
		{
			LPDISPATCH result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		unsigned long GetDeviceNodeCount()
		{
			unsigned long result;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetDeviceNode(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		LPDISPATCH FindDeviceNodeByPath(LPCTSTR strNodePath)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strNodePath);
			return result;
		}
		long AddProcedureDataInterface(LPCTSTR strID, LPCTSTR strValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strID, strValue);
			return result;
		}
		long ResetProcedureDataInterface()
		{
			long result;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long RunProcedure(LPCTSTR strProcedureID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strProcedureID);
			return result;
		}
		long RegisterDataChangedWndMsg(unsigned long hWnd, unsigned long nWMsgID, unsigned long nNodeIndex, unsigned long wParam, unsigned long lParam)
		{
			long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWnd, nWMsgID, nNodeIndex, wParam, lParam);
			return result;
		}
		long UnRegisterDataChangedWndMsg(unsigned long hWnd, unsigned long nWMsgID, unsigned long nNodeIndex, unsigned long wParam, unsigned long lParam)
		{
			long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, hWnd, nWMsgID, nNodeIndex, wParam, lParam);
			return result;
		}
		unsigned long RegisterProcedureWndMsg(LPCTSTR strProcedureID, unsigned long hWnd, unsigned long nMsgID, unsigned long wParam, unsigned long lParam)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strProcedureID, hWnd, nMsgID, wParam, lParam);
			return result;
		}
		unsigned long UnRegisterProcedureWndMsg(LPCTSTR strProcedureID, unsigned long hWnd, unsigned long nMsgID, unsigned long wParam, unsigned long lParam)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strProcedureID, hWnd, nMsgID, wParam, lParam);
			return result;
		}
		LPDISPATCH FindByDmIndex(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		long SetTemplateFile(LPCTSTR strPpTemplateFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPpTemplateFile);
			return result;
		}
		long SetDeviceFile(LPCTSTR strDeviceFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceFile);
			return result;
		}
		unsigned long AttachSystemWndMsg(unsigned long hWnd, unsigned long nMsgID, unsigned long wParam, unsigned long lParam)
		{
			unsigned long result;
			static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x15, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, hWnd, nMsgID, wParam, lParam);
			return result;
		}
		unsigned long IsValid()
		{
			unsigned long result;
			InvokeHelper(0x16, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		unsigned long IsConnectSuccessful()
		{
			unsigned long result;
			InvokeHelper(0x17, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		unsigned long UnLoad()
		{
			unsigned long result;
			InvokeHelper(0x18, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		long RecordPackage(LPCTSTR strPkgID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPkgID);
			return result;
		}
		long UnRecordPackage(LPCTSTR strPkgID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPkgID);
			return result;
		}
		LPDISPATCH GetReacordPackags()
		{
			LPDISPATCH result;
			InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long GetAllTagCount()
		{
			long result;
			InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long GetAllTagName(VARIANT * pvTagName)
		{
			long result;
			static BYTE parms[] = VTS_PVARIANT ;
			InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pvTagName);
			return result;
		}
		long SetStringData(long nCount, VARIANT * pvTagPars, VARIANT * pvData)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PVARIANT ;
			InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nCount, pvTagPars, pvData);
			return result;
		}
		long GetStringData(long nCount, VARIANT * pvTagPars, VARIANT * pvData)
		{
			long result;
			static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PVARIANT ;
			InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nCount, pvTagPars, pvData);
			return result;
		}
		unsigned long RunProcedureWithPara(LPCTSTR strProcedureID, unsigned long nItemIndex, unsigned long nValue)
		{
			unsigned long result;
			static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 ;
			InvokeHelper(0x20, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, strProcedureID, nItemIndex, nValue);
			return result;
		}
		CString GetDeviceAttr(LPCTSTR strAttrID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x21, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strAttrID);
			return result;
		}
		CString GetDeviceAttrs()
		{
			CString result;
			InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		CString GetDevieNodeDataAttr(LPCTSTR strDataPath, LPCTSTR strAttrID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x23, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDataPath, strAttrID);
			return result;
		}
		long SetDevieNodeDataAttr(LPCTSTR strDataPath, LPCTSTR strAttrID, LPCTSTR strValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDataPath, strAttrID, strValue);
			return result;
		}
		long SetDeviceAttr(LPCTSTR strAttrID, LPCTSTR strValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strAttrID, strValue);
			return result;
		}

		// IDevice 属性
	public:

	};



	class CPpEngine : public COleDispatchDriver
	{
	public:
		CPpEngine(){} // 调用 COleDispatchDriver 默认构造函数
		CPpEngine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
		CPpEngine(const CPpEngine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
		LRESULT CreateInstance(const CString &strProgID)
		{
			return CreateDispatch(strProgID);
		}

		// 属性
	public:

		// 操作
	public:


		// IPpEngine 方法
	public:
		CString GetVersion()
		{
			CString result;
			InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH CreateDevice(LPCTSTR strPpTemplateFile, LPCTSTR strPpDeviceFile)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strPpTemplateFile, strPpDeviceFile);
			return result;
		}
		unsigned long GetCount()
		{
			unsigned long result;
			InvokeHelper(0x3, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH GetItem(long nIndex)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_I4 ;
			InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, nIndex);
			return result;
		}
		unsigned long ShowSpyWnd(unsigned long nShow)
		{
			unsigned long result;
			static BYTE parms[] = VTS_UI4 ;
			InvokeHelper(0x5, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, nShow);
			return result;
		}
		LPDISPATCH NewDevice()
		{
			LPDISPATCH result;
			InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long SetCommConfig()
		{
			long result;
			InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		LPDISPATCH AddNewDevice()
		{
			LPDISPATCH result;
			InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
			return result;
		}
		long SetPackageVariableValue(LPCTSTR strPackageID, LPCTSTR strVariableID, LPCTSTR strValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPackageID, strVariableID, strValue);
			return result;
		}
		long SavePpTemplateFile(LPCTSTR strFileName)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFileName);
			return result;
		}
		CString PpGetDeviceAttr(LPCTSTR strDeviceID, LPCTSTR strAttrID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID, strAttrID);
			return result;
		}
		CString PpGetDeviceAttrs(LPCTSTR strDeviceID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0xc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID);
			return result;
		}
		CString PpGetDevieNodeDatas(LPCTSTR strDeviceID, LPCTSTR strPath)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID, strPath);
			return result;
		}
		CString PpGetDevieNodeDataAttr(LPCTSTR strDeviceID, LPCTSTR strDataPath, LPCTSTR strAttrID)
		{
			CString result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, strDeviceID, strDataPath, strAttrID);
			return result;
		}
		long PpSetDevieNodeDataAttr(LPCTSTR strDeviceID, LPCTSTR strDataPath, LPCTSTR strAttrID, LPCTSTR strValue)
		{
			long result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID, strDataPath, strAttrID, strValue);
			return result;
		}
		LPDISPATCH CreateDeviceEx(LPCTSTR strPpFile, LPCTSTR strDeviceFile, LPCTSTR strDeviceID)
		{
			LPDISPATCH result;
			static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
			InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, strPpFile, strDeviceFile, strDeviceID);
			return result;
		}
		long ReleaseDevice(LPCTSTR strDeviceID)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strDeviceID);
			return result;
		}
		long ReleaseAllDevice()
		{
			long result;
			InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
			return result;
		}
		long SelectDevice(LPCTSTR bstrDeviceFile)
		{
			long result;
			static BYTE parms[] = VTS_BSTR ;
			InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bstrDeviceFile);
			return result;
		}

		// IPpEngine 属性
	public:

	};
	
	
	enum tagEnginePpRunStateDefine
	{
		enginePpRunStateNormal = 0,
		enginePpRunStateError = 1,
		enginePpRunStateReset = 2
	} ;
	
	
	enum tagEngineSystemDefine
	{
		engineConnectDeviceFailed=0,
		engineConnectDeviceSuccessful=1,
		engineCommError = 2
	} ;

typedef CVtag IVtagPtr;
typedef CVtags IVtagsPtr;
typedef CDeviceNodeData IDeviceNodeDataPtr;
typedef CDeviceNode IDeviceNodePtr;
typedef CDevice IDevicePtr;
typedef CPpEngine IPpEnginePtr;
};

#endif
