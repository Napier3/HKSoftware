// Equation.h : CEquation ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "EquationKey.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CEquation

class ATL_NO_VTABLE CEquation :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEquation, &CLSID_Equation>,
	public IDispatchImpl<IEquation, &IID_IEquation, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CEquation()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EQUATION)


BEGIN_COM_MAP(CEquation)
	COM_INTERFACE_ENTRY(IEquation)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CCOMOBJECT_METHODS(CEquation,IEquation)

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	CWEquationBuffer m_oEquation;

	static CWEquationBuffer* FromIDispatch(IDispatch* pDisp)
	{
		if (pDisp == NULL)
		{
			return NULL;
		}

		CEquation *pCEquation = NULL;
		IEquation *pIEquation = NULL;

		pDisp->QueryInterface(IID_IEquation, (void**)&pIEquation);

		if (pIEquation == NULL)
		{
			return NULL;
		}

#ifdef _ATL_DEBUG_INTERFACES
		_QIThunk *pThunk = (_QIThunk*)pIEquation;
		pCEquation = (CEquation*)pThunk->m_pUnk;
#else
		pCEquation = (CEquation*)pIEquation;
#endif
		pIEquation->Release();
		return &(pCEquation->m_oEquation);
	}

public:

	STDMETHOD(GetCount)(LONG* pnCount);
	STDMETHOD(GetItem)(LONG nIndex, IDispatch** pIEquationKey);
	STDMETHOD(GetKeyValue)(LONG nIndex, BSTR* pbstrValue);
	STDMETHOD(SetKeyValue)(LONG nIndex, BSTR bstrValue);
	STDMETHOD(GetLong)(BSTR bstrKeyName, LONG nDefaultVal, LONG* pnVal);
	STDMETHOD(GetFloat)(BSTR bstrKeyName, FLOAT fDefaultVal, FLOAT* pfVal);
	STDMETHOD(GetString)(BSTR bstrKeyName, BSTR bstrDefaultVal, BSTR* pbstrVal);
	STDMETHOD(GetDouble)(BSTR bstrKeyName, DOUBLE dDefaultVal, DOUBLE* pdVal);
	STDMETHOD(SetEquation)(BSTR bstrEquation, LONG* pnCount);
	STDMETHOD(GetEquation)(BSTR* pbstrEquation);
	STDMETHOD(SetKeyValueByName)(BSTR bstrKeyName, BSTR bstrKeyValue, LONG AddNew);
	STDMETHOD(SetKeyValueByEquation)(BSTR bstrEquation, LONG nAddNew);
	STDMETHOD(FreeAllKeys)(void);
	STDMETHOD(IsKeyExist)(BSTR bstrKeyName, LONG* pnExist);
	STDMETHOD(StringSerialize)(IDispatch* pIStringBuffer);
	STDMETHOD(BinarySerialize)(IDispatch* pIBinaryBuffer);
};

OBJECT_ENTRY_AUTO(__uuidof(Equation), CEquation)
