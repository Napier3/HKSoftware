//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//FuncParas.h  CFuncParas

#pragma once

#include "DllCallGlobal.h"

#include "..\..\..\Module\DataMngr\DvmData.h"


class CFuncParas : public CDvmData
{
public:
	CFuncParas();
	virtual ~CFuncParas();


//���غ���
public:
	virtual UINT GetClassID() {    return DLCLCLASSID_CFUNCPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CDllCallXmlRWKeys::CFuncParasKey();     }
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void InitByString_Equation(const CString &strParas);
};

