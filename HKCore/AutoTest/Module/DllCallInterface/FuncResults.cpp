//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//FuncResults.cpp  CFuncResults


#include "stdafx.h"
#include "FuncResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFuncResults::CFuncResults()
{
	//��ʼ������

	//��ʼ����Ա����
}

CFuncResults::~CFuncResults()
{
}

CBaseObject* CFuncResults::Clone()
{
	CFuncResults *p = new CFuncResults();
	Copy(p);
	return p;
}

