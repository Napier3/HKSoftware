/*
* Copyright (c) 2005,
* All rights reserved.
* 
* 摘    要：COM组件编程相关的全局函数
*           
* 当前版本：1.0
* 作    者：李俊庆
* 完成日期：2005年5月17日
*
* 取代版本：
* 原作者  ：
* 完成日期：
*/

#ifndef _COMGLOBALDEFINE_H__
#define _COMGLOBALDEFINE_H__

#include <comdef.h>

long AnsiStrToBSTR(const char *pszAnsi,BSTR *pbstr);

long BSTRToAnsiStr(BSTR *pbstr,char *pszAnsi);
long BSTRToAnsiStr(BSTR *pbstr,CString &strAnsi);
long BSTRToAnsiStr(BSTR bstr,char *pszAnsi);
long BSTRToAnsiStr(BSTR bstr,char **pszAnsi);
long BSTRToAnsiStr(BSTR bstr,CString &strAnsi);



//创建SafeArray数据数组
void CreateAndSetSafeArray_I1(long nArrayLen,char *pszValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_I2(long nArrayLen,short *pshortValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_I4(long nArrayLen,long *plValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_UI1(long nArrayLen,BYTE *pbyteValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_UI2(long nArrayLen,WORD *pwValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_UI4(long nArrayLen,DWORD *pdwValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_R4(long nArrayLen,float *pfValBuff,VARIANT *pvarBuff);

//从VARIANT中获取数据，返回获取到的数据的长度
long GetDataFromSafeArray_I1(char **ppszValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_I2(short **ppshortValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_I4(long **pplValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_UI1(BYTE **ppbyteValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_UI2(WORD **ppwValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_UI4(DWORD **ppdwValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_R4(float **ppfValBuff,VARIANT *pvarBuff);

//////////////////////////////////////////////////////////////////////////
//2022-6011  LIJUNQING
// 除将 bMultiInstance 参数设置为 TRUE    传递给 COleObjectFactory 构造函数之外，
// 此宏与 IMPLEMENT_OLECREATE 相同
// 对于自动化控制器所请求的每一个自动化代理对象,
// 需要分别启动一个该应用程序的实例。
#ifndef IMPLEMENT_OLECREATE_MULTI
#define IMPLEMENT_OLECREATE_MULTI(class_name, external_name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
	RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
	const AFX_DATADEF GUID class_name::guid = \
{ l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };
#endif // IMPLEMENT_OLECREATE_MULTI

/*
>>>>>>将COM注册声明处代码改为：
//   IMPLEMENT_OLECREATE_FLAGS  (CXEngine, "ComTest.XEngine", afxRegApartmentThreading, 0xcd51b285, 0x7cec, 0x46d6, 0xb5, 0xac, 0xbf, 0x7f, 0x2a, 0x8a, 0x4c, 0x4d)
//   IMPLEMENT_OLECREATE_MULTI  (CXEngine, "ComTest.XEngine",                                       0xcd51b285, 0x7cec, 0x46d6, 0xb5, 0xac, 0xbf, 0x7f, 0x2a, 0x8a, 0x4c, 0x4d)
*/


#endif
