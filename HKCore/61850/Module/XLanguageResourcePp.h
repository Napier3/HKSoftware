//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"


class CXLanguageResourcePpBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourcePpBase();
	virtual ~CXLanguageResourcePpBase();
	
	void InitLangFileForDebug(const CString &strModule);

public:
	virtual void RegisterLanguageResource();

public:
	static CString g_sLangID_Home;
	static CString g_sLangTxt_Home;
	
};
