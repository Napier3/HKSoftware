// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "D:\\Program Files\\EPOTO\\Common\\Bin\\FtpServer.exe" no_namespace
// COAFtpSvrExeCom ��װ��

class COAFtpSvrExeCom : public COleDispatchDriver
{
public:
	COAFtpSvrExeCom(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	COAFtpSvrExeCom(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COAFtpSvrExeCom(const COAFtpSvrExeCom& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IOAFtpSvrExeCom ����
public:
	long StartFtpServer(LPCTSTR strPath, long nType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPath, nType);
		return result;
	}

	// IOAFtpSvrExeCom ����
public:

};
