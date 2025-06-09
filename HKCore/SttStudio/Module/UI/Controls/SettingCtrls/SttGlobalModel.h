#pragma once

#include "../../../../../Module/DataMngr/DvmData.h"

#define	HL_REPACE_FULLPATH_HEAD  "HLHeadRepaceHeadPath"

class CSttGlobalModel 
{
public:
	CSttGlobalModel(void);
	virtual ~CSttGlobalModel(void);

	//20240806 huangliang 解析定值关联路径,包含表达式解析
	static bool AnalysisPath(const QString &strSrcPath, QString *strName, QString *strValue);

	static BOOL FindNameFromDeviceModel(const CString &strPath, QString *strName, QString *strValue);

	static CExBaseObject * FindObjectFromDeviceModel(const CString &strPath);

protected:
	//从模型数据中查找对应名称	
	static BOOL GetNameByPath(const CString &strPath);
	static long MatchID(CExBaseObject *pCurrItem, const CString &strPath);
	static CExBaseObject* FindRptDataByPath(CExBaseList *pCurrItem, const CString &strPath);
};

extern CExBaseList* g_pDvmDevice_AttachSetting;			//模板