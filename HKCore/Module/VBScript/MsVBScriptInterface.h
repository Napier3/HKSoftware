//MsVBScriptInterface

#pragma once

// CScriptProcedure ��װ��
class CScriptProcedure : public COleDispatchDriver
{
public:
	CScriptProcedure(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CScriptProcedure(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CScriptProcedure(const CScriptProcedure& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IScriptProcedure ����
public:
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_NumArgs()
	{
		long result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_HasReturnValue()
	{
		BOOL result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}

	// IScriptProcedure ����
public:

};

// CScriptProcedureCollection ��װ��
class CScriptProcedureCollection : public COleDispatchDriver
{
public:
	CScriptProcedureCollection(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CScriptProcedureCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CScriptProcedureCollection(const CScriptProcedureCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IScriptProcedureCollection ����
public:
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}

	// IScriptProcedureCollection ����
public:

};

// CScriptModule ��װ��
class CScriptModule : public COleDispatchDriver
{
public:
	CScriptModule(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CScriptModule(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CScriptModule(const CScriptModule& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IScriptModule ����
public:
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CodeObject()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Procedures()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void AddCode(LPCTSTR Code)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Code);
	}
	VARIANT Eval(LPCTSTR Expression)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Expression);
		return result;
	}
	void ExecuteStatement(LPCTSTR Statement)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Statement);
	}
	VARIANT Run(LPCTSTR ProcedureName, SAFEARRAY * * Parameters)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_UNKNOWN ;
		InvokeHelper(0x7d3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, ProcedureName, Parameters);
		return result;
	}

	// IScriptModule ����
public:

};

// CScriptModuleCollection ��װ��
class CScriptModuleCollection : public COleDispatchDriver
{
public:
	CScriptModuleCollection(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CScriptModuleCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CScriptModuleCollection(const CScriptModuleCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IScriptModuleCollection ����
public:
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Add(LPCTSTR Name, VARIANT * Object)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Name, Object);
		return result;
	}

	// IScriptModuleCollection ����
public:

};

// CScriptError ��װ��
class CScriptError : public COleDispatchDriver
{
public:
	CScriptError(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CScriptError(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CScriptError(const CScriptError& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IScriptError ����
public:
	long get_Number()
	{
		long result;
		InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_Source()
	{
		CString result;
		InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_Description()
	{
		CString result;
		InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_HelpFile()
	{
		CString result;
		InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_HelpContext()
	{
		long result;
		InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(DISPID_TEXT, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_Line()
	{
		long result;
		InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Column()
	{
		long result;
		InvokeHelper(0xfffffdef, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void Clear()
	{
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IScriptError ����
public:

};

// CScriptControl ��װ��
class CScriptControl : public COleDispatchDriver
{
public:
	CScriptControl(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CScriptControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CScriptControl(const CScriptControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IScriptControl ����
public:
	CString get_Language()
	{
		CString result;
		InvokeHelper(0x5dc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Language(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_State()
	{
		long result;
		InvokeHelper(0x5dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_State(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_SitehWnd(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SitehWnd()
	{
		long result;
		InvokeHelper(0x5de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Timeout()
	{
		long result;
		InvokeHelper(0x5df, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Timeout(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AllowUI()
	{
		BOOL result;
		InvokeHelper(0x5e0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AllowUI(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_UseSafeSubset()
	{
		BOOL result;
		InvokeHelper(0x5e1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_UseSafeSubset(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Modules()
	{
		LPDISPATCH result;
		InvokeHelper(0x5e2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Error()
	{
		LPDISPATCH result;
		InvokeHelper(0x5e3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CodeObject()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Procedures()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void _AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddObject(LPCTSTR Name, LPDISPATCH Object, BOOL AddMembers)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0x9c4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name, Object, AddMembers);
	}
	void Reset()
	{
		InvokeHelper(0x9c5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddCode(LPCTSTR Code)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Code);
	}
	VARIANT Eval(LPCTSTR Expression)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Expression);
		return result;
	}
	void ExecuteStatement(LPCTSTR Statement)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Statement);
	}
	VARIANT Run(LPCTSTR ProcedureName, SAFEARRAY * * Parameters)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_UNKNOWN ;
		InvokeHelper(0x7d3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, ProcedureName, Parameters);
		return result;
	}

	// IScriptControl ����
public:

};

// CDScriptControlSource ��װ��
class CDScriptControlSource : public COleDispatchDriver
{
public:
	CDScriptControlSource(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CDScriptControlSource(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDScriptControlSource(const CDScriptControlSource& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// DScriptControlSource ����
public:
	void Error()
	{
		InvokeHelper(0xbb8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Timeout()
	{
		InvokeHelper(0xbb9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// DScriptControlSource ����
public:

};
