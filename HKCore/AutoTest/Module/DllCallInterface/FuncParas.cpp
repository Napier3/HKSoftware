//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FuncParas.cpp  CFuncParas


#include "stdafx.h"
#include "FuncParas.h"
#include "..\..\..\Module\MemBuffer\EquationBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFuncParas::CFuncParas()
{
	//初始化属性

	//初始化成员变量
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

