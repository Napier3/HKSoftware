//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WndChildCtrlsAdjustGlobal.h

#pragma once

#include "ExBaseList.h"

#define WCCACLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define WCCACLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define WCCACLASSID_CWNDADJCELL       (WCCACLASSID_EXLISTCLASS + 0X00000000)
#define WCCACLASSID_CWNDADJCELLLIST       (WCCACLASSID_EXLISTCLASS + 0X00000001)
#define WCCACLASSID_CWNDADJROW       (WCCACLASSID_EXLISTCLASS + 0X00000002)
#define WCCACLASSID_CWNDADJCOL       (WCCACLASSID_EXLISTCLASS + 0X00000003)
#define WCCACLASSID_CWNDADJTOOL       (WCCACLASSID_EXLISTCLASS + 0X00000004)

class CWndChildCtrlsAdjustXmlRWKeys : public CXmlRWKeys
{
protected:
	CWndChildCtrlsAdjustXmlRWKeys();
	virtual ~CWndChildCtrlsAdjustXmlRWKeys();
	static long g_nWCCARef;

public:
	static CWndChildCtrlsAdjustXmlRWKeys* g_pXmlKeys;
	static CWndChildCtrlsAdjustXmlRWKeys* Create();
	static void Release();

public:

public:
};



class CWndChildCtrlsAdjustConstGlobal
{
private:
	CWndChildCtrlsAdjustConstGlobal();
	virtual ~CWndChildCtrlsAdjustConstGlobal();

public:
	static CWndChildCtrlsAdjustConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CWndChildCtrlsAdjustConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};
