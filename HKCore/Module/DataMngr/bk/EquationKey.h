// EquationKey.h : CEquationKey ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "..\..\Module\AtlMemBuffer\WEquationBuffer.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CEquationKey

class ATL_NO_VTABLE CEquationKey :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEquationKey, &CLSID_EquationKey>,
	public IDispatchImpl<IEquationKey, &IID_IEquationKey, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CEquationKey()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EQUATIONKEY)


BEGIN_COM_MAP(CEquationKey)
	COM_INTERFACE_ENTRY(IEquationKey)
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

	CWEqtnKey *m_pEqtnKey;

	void AttachEqtnKey(CWEqtnKey *pKey)  
	{
		m_pEqtnKey = pKey;
	}
public:

	STDMETHOD(get_Name)(BSTR* pVal);
	STDMETHOD(get_Value)(BSTR* pVal);
	STDMETHOD(put_Value)(BSTR newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(EquationKey), CEquationKey)
