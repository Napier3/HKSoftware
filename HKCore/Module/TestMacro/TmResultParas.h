//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmResultParas.h  CTmResultParas

#pragma once

#include "TestMacroGlobal.h"


class CTmResultParas : public CShortDatas
{
public:
	CTmResultParas();
	virtual ~CTmResultParas();


//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMRESULTPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmResultParasKey();     }
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


class CTmSearchResultParas : public CShortDatas
{
public:
	CTmSearchResultParas();
	virtual ~CTmSearchResultParas();


//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMSEARCHRESULTPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmSearchResultParasKey();     }
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

