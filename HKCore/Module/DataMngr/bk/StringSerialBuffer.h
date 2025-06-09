// StringSerialBuffer.h : CStringSerialBuffer ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CStringSerialBuffer

class ATL_NO_VTABLE CStringSerialBuffer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStringSerialBuffer, &CLSID_StringSerialBuffer>,
	public IDispatchImpl<IStringSerialBuffer, &IID_IStringSerialBuffer, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CStringSerialBuffer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STRINGSERIALBUFFER)


BEGIN_COM_MAP(CStringSerialBuffer)
	COM_INTERFACE_ENTRY(IStringSerialBuffer)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(get_VBuffer)(VARIANT* pVal);
	STDMETHOD(put_VBuffer)(VARIANT newVal);
	STDMETHOD(get_String)(BSTR* pVal);
	STDMETHOD(put_String)(BSTR newVal);
	STDMETHOD(AddBufferLength)(LONG nLen);
	STDMETHOD(SetBufferLength)(LONG nLen, LONG* pnReturn);
	STDMETHOD(AllocBuffer)(LONG* pnReturn);
	STDMETHOD(SetReadMode)(void);
	STDMETHOD(SetWriteMode)(void);
	STDMETHOD(SetCalSizeMode)(void);
	STDMETHOD(IsReadMode)(LONG* pnReturn);
	STDMETHOD(IsWriteMode)(LONG* pnReturn);
	STDMETHOD(IsCalSizeMode)(LONG* pnReturn);
	STDMETHOD(WriteString)(BSTR bstrWrite);
	STDMETHOD(SaveToFile)(BSTR bstrFile, LONG* pnReturn);
	STDMETHOD(OpenFromFile)(BSTR bstrFile, LONG* pnReturn);
};

OBJECT_ENTRY_AUTO(__uuidof(StringSerialBuffer), CStringSerialBuffer)
