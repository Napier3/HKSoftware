// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

// CFtpSvrCom ��װ��
#pragma once

class CFtpSvrCom : public COleDispatchDriver
{
public:
	CFtpSvrCom(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CFtpSvrCom(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFtpSvrCom(const CFtpSvrCom& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IFtpSvrCom ����
public:
	long InitFtpServer(LPCTSTR strPath, long nType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPath, nType);
		return result;
	}
	long StartFtpServer(LPCTSTR strPath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPath);
		return result;
	}

	// IFtpSvrCom ����
public:

};
