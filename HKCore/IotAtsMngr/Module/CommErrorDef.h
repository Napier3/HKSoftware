#ifndef _IOT_CMM_ERROR_DEFINES_H__
#define _IOT_CMM_ERROR_DEFINES_H__

//打开通讯端口失败
#define COMMERROR_OPEN_DEVICE_FAILD		0X00000001

//读取数据失败
#define COMMERROR_READ_DATA_FAILED		0X00000002

//下载数据失败
#define COMMERROR_WRITE_DATA_FAILD		0X00000004

//数据异常
#define COMMERROR_DATA_EXCEPTION		0X00000008

//联机失败
#define COMMERROR_CONNECT_FAILED			0X00000010

//测试仪型号不支持当前选择的测试功能
#define COMMERROR_MACRO_NOT_SUPPORT	0X00000020

//通讯配置中
#define COMMERROR_IN_CMM_CONFIGING 	    0X00000040

//电压电流越限
#define COMMERROR_UI_LIMIT 	    0X00000080

//设备正在测试   //2014-12-29  lijq
#define COMMERROR_DEVICE_INTESTTING 	    0X00000100

//其他的错误
#define COMMERROR_OTHER		 	       0X08000000


//通讯相关函数返回值的处理部分
inline bool COMM_Error(DWORD nResult)
{
	return ((nResult & 0xF0000000) > 0);
}

inline DWORD COMM_GetError(DWORD nResult)
{
	return (nResult & 0x0FFFFFFF);
}

inline DWORD COMM_SetError(DWORD nData)
{
	return (nData | 0xF0000000);
}

#endif//_IOT_CMM_ERROR_DEFINES_H__
