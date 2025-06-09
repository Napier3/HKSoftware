/*
* Copyright (c) 2005,
* All rights reserved.
* 
* ժ    Ҫ��COM��������ص�ȫ�ֺ���
*           
* ��ǰ�汾��1.0
* ��    �ߣ����
* ������ڣ�2005��5��17��
*
* ȡ���汾��
* ԭ����  ��
* ������ڣ�
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



//����SafeArray��������
void CreateAndSetSafeArray_I1(long nArrayLen,char *pszValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_I2(long nArrayLen,short *pshortValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_I4(long nArrayLen,long *plValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_UI1(long nArrayLen,BYTE *pbyteValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_UI2(long nArrayLen,WORD *pwValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_UI4(long nArrayLen,DWORD *pdwValBuff,VARIANT *pvarBuff);
void CreateAndSetSafeArray_R4(long nArrayLen,float *pfValBuff,VARIANT *pvarBuff);

//��VARIANT�л�ȡ���ݣ����ػ�ȡ�������ݵĳ���
long GetDataFromSafeArray_I1(char **ppszValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_I2(short **ppshortValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_I4(long **pplValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_UI1(BYTE **ppbyteValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_UI2(WORD **ppwValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_UI4(DWORD **ppdwValBuff,VARIANT *pvarBuff);
long GetDataFromSafeArray_R4(float **ppfValBuff,VARIANT *pvarBuff);

//////////////////////////////////////////////////////////////////////////
//2022-6011  LIJUNQING
// ���� bMultiInstance ��������Ϊ TRUE    ���ݸ� COleObjectFactory ���캯��֮�⣬
// �˺��� IMPLEMENT_OLECREATE ��ͬ
// �����Զ����������������ÿһ���Զ����������,
// ��Ҫ�ֱ�����һ����Ӧ�ó����ʵ����
#ifndef IMPLEMENT_OLECREATE_MULTI
#define IMPLEMENT_OLECREATE_MULTI(class_name, external_name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
	RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
	const AFX_DATADEF GUID class_name::guid = \
{ l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };
#endif // IMPLEMENT_OLECREATE_MULTI

/*
>>>>>>��COMע�������������Ϊ��
//   IMPLEMENT_OLECREATE_FLAGS  (CXEngine, "ComTest.XEngine", afxRegApartmentThreading, 0xcd51b285, 0x7cec, 0x46d6, 0xb5, 0xac, 0xbf, 0x7f, 0x2a, 0x8a, 0x4c, 0x4d)
//   IMPLEMENT_OLECREATE_MULTI  (CXEngine, "ComTest.XEngine",                                       0xcd51b285, 0x7cec, 0x46d6, 0xb5, 0xac, 0xbf, 0x7f, 0x2a, 0x8a, 0x4c, 0x4d)
*/


#endif
