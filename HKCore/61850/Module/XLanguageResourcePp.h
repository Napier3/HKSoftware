//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
