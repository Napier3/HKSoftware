//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//WzdMatchFilterKeys.h  CWzdMatchFilterKeys

#pragma once

#include "..\..\..\Module\FilterText\FilterTextMngr.h"


class CWzdMatchFilterKeys : public CFilterTextMngr
{
protected:
	CWzdMatchFilterKeys();
	virtual ~CWzdMatchFilterKeys();

	static CWzdMatchFilterKeys *g_pFilterTextMngr;
	static long m_nFilterTextMngrRef;

public:
	static CWzdMatchFilterKeys* Create();
	static CWzdMatchFilterKeys* GetWzdMatchFilterKeys();
	static void Release();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

