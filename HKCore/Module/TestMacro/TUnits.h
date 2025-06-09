//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TUnits.h

#pragma once

#include "../DataMngr/DataTypes.h"
#include "../XLanguage/XLanguageMngr.h"

class CTUnits : public CDataTypes
{
private:
	CTUnits();
	virtual ~CTUnits();
	static long g_nTMRef;

public:
	static CTUnits* g_pTUnits;
	static CTUnits* Create();
	static void Release();
	static const CString g_strCTUnits_xml_file;

public:
	static CString unit_xlang_TranslateUnit(const CString &strUnit);

private:
	CXLanguage m_oXLanguage;
};

