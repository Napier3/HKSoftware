//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmSysParas.h  CTmSysParas

#pragma once

#include "TestMacroGlobal.h"



class CTmSysParas : public CShortDatas
{
public:
	CTmSysParas();
	virtual ~CTmSysParas();


//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMSYSPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmSysParasKey();     }
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

