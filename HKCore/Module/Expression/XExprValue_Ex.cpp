//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XExprValueRslt.cpp  CXExprValueRslt


#include "stdafx.h"
#include "XExprValue_Ex.h"

CXExprValueRslt::CXExprValueRslt()
{
	//��ʼ������
	m_strValue = _T("δ����");
	//��ʼ����Ա����
}

CXExprValueRslt::~CXExprValueRslt()
{
}

CBaseObject* CXExprValueRslt::Clone()
{
	CXExprValueRslt *p = new CXExprValueRslt();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValue1::CXExprValue1()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValue1::~CXExprValue1()
{
}

CBaseObject* CXExprValue1::Clone()
{
	CXExprValue1 *p = new CXExprValue1();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValue2::CXExprValue2()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValue2::~CXExprValue2()
{
}

CBaseObject* CXExprValue2::Clone()
{
	CXExprValue2 *p = new CXExprValue2();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueMax::CXExprValueMax()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueMax::~CXExprValueMax()
{
}

CBaseObject* CXExprValueMax::Clone()
{
	CXExprValueMax *p = new CXExprValueMax();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueMin::CXExprValueMin()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueMin::~CXExprValueMin()
{
}

CBaseObject* CXExprValueMin::Clone()
{
	CXExprValueMin *p = new CXExprValueMin();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueStd::CXExprValueStd()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueStd::~CXExprValueStd()
{
}

CBaseObject* CXExprValueStd::Clone()
{
	CXExprValueStd *p = new CXExprValueStd();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueError::CXExprValueError()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueError::~CXExprValueError()
{
}

CBaseObject* CXExprValueError::Clone()
{
	CXExprValueError *p = new CXExprValueError();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueErrorRel::CXExprValueErrorRel()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueErrorRel::~CXExprValueErrorRel()
{
}

CBaseObject* CXExprValueErrorRel::Clone()
{
	CXExprValueErrorRel *p = new CXExprValueErrorRel();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueErrorAbs::CXExprValueErrorAbs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueErrorAbs::~CXExprValueErrorAbs()
{
}

CBaseObject* CXExprValueErrorAbs::Clone()
{
	CXExprValueErrorAbs *p = new CXExprValueErrorAbs();
	Copy(p);
	return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRslt   ��������� = ����õ������ֵ
CXExprValueErrorRslt::CXExprValueErrorRslt()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueErrorRslt::~CXExprValueErrorRslt()
{
}

CBaseObject* CXExprValueErrorRslt::Clone()
{
	CXExprValueErrorRslt *p = new CXExprValueErrorRslt();
	Copy(p);
	return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRelRslt   ������������ = ����õ���������ֵ
CXExprValueErrorRelRslt::CXExprValueErrorRelRslt()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueErrorRelRslt::~CXExprValueErrorRelRslt()
{
}

CBaseObject* CXExprValueErrorRelRslt::Clone()
{
	CXExprValueErrorRelRslt *p = new CXExprValueErrorRelRslt();
	Copy(p);
	return p;
}

void CXExprValueErrorRelRslt::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	//SetRelCalVal(TRUE);
	CXExprValue::ExprRsltBind(pExprParent, pCalInterface);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorAbsRslt   ������������� = ����õ��ľ������ֵ
CXExprValueErrorAbsRslt::CXExprValueErrorAbsRslt()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueErrorAbsRslt::~CXExprValueErrorAbsRslt()
{
}

CBaseObject* CXExprValueErrorAbsRslt::Clone()
{
	CXExprValueErrorAbsRslt *p = new CXExprValueErrorAbsRslt();
	Copy(p);
	return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueCalRslt   ���������������������ݶ������������㣨+��-��*���£��Ľ������
CXExprValueCalRslt::CXExprValueCalRslt()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXExprValueCalRslt::~CXExprValueCalRslt()
{
}

CBaseObject* CXExprValueCalRslt::Clone()
{
	CXExprValueCalRslt *p = new CXExprValueCalRslt();
	Copy(p);
	return p;
}