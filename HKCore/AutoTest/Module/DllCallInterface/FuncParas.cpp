//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//FuncParas.cpp  CFuncParas


#include "stdafx.h"
#include "FuncParas.h"
#include "..\..\..\Module\MemBuffer\EquationBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFuncParas::CFuncParas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CFuncParas::~CFuncParas()
{
}

CBaseObject* CFuncParas::Clone()
{
	CFuncParas *p = new CFuncParas();
	Copy(p);
	return p;
}

void CFuncParas::InitByString_Equation(const CString &strParas)
{
	CEquationBuffer oBuffer;
	oBuffer.InitBuffer(strParas);
	POS pos = oBuffer.GetHeadPosition();
	CEquationKey *pKey = NULL;
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pKey = (CEquationKey *)oBuffer.GetNext(pos);
		pValue = (CDvmValue *)FindByID(pKey->GetKeyName());

		if (pValue != NULL)
		{
			pValue->m_strValue = pKey->GetKeyValue();
		}
	}
}

