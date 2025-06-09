// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "D:\\Program Files\\EPOTO\\Common\\Bin\\FtpServer.exe" no_namespace
// COAFtpSvrExeCom 包装类

class COAFtpSvrExeCom : public COleDispatchDriver
{
public:
	COAFtpSvrExeCom(){} // 调用 COleDispatchDriver 默认构造函数
	COAFtpSvrExeCom(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COAFtpSvrExeCom(const COAFtpSvrExeCom& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 属性
public:

	// 操作
public:


	// IOAFtpSvrExeCom 方法
public:
	long StartFtpServer(LPCTSTR strPath, long nType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strPath, nType);
		return result;
	}

	// IOAFtpSvrExeCom 属性
public:

};
