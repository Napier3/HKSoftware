//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmFaultParas.h  CTmFaultParas

#pragma once

#include "TestMacroGlobal.h"


class CTmFaultParas : public CShortDatas
{
public:
	CTmFaultParas();
	virtual ~CTmFaultParas();


//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMFAULTPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmFaultParasKey();     }
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

