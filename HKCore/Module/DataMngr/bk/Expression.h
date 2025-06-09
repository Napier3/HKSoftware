// Expression.h : CExpression ������

#pragma once
#include "resource.h"       // ������

#include "SystemTool_i.h"
#include "..\..\Module\AtlMemBuffer\AtlExpression.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif



// CExpression

class ATL_NO_VTABLE CExpression :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExpression, &CLSID_Expression>,
	public IDispatchImpl<IExpression, &IID_IExpression, &LIBID_SystemTool, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CExpression()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_EXPRESSION)


BEGIN_COM_MAP(CExpression)
	COM_INTERFACE_ENTRY(IExpression)
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

	CAtlExpression m_oExpression;
public:

	STDMETHOD(SetExpression)(BSTR bstrExpression, LONG* pnReturn);
	STDMETHOD(GetSyntaxs)(BSTR* pbstrSyntaxs);
	STDMETHOD(GetSyntaxsCount)(LONG* pnSyntaxs);
	STDMETHOD(GetResult)(DOUBLE* pdResult);
	STDMETHOD(AttachConstVariables)(IDispatch* pVariables, LONG* pnReturn);
	STDMETHOD(AttachVariables)(IDispatch* pVariables, LONG* pnReturn);
};

OBJECT_ENTRY_AUTO(__uuidof(Expression), CExpression)
