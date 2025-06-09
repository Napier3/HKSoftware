#ifndef TMT_ADJUST_SYS_PARA_TRANS_H
#define TMT_ADJUST_SYS_PARA_TRANS_H


#include "../../../../Module/DataMngr/DataTypes.h"

extern CDataTypes *g_pSttAdjSysParaDataTypes;

void stt_tmt_adj_para_trans_to_string(long nSrcValue, const char *pszDataType, char *pszDestValue);
void stt_tmt_adj_para_trans_to_long(const char *pszSrcValue, const char *pszDataType, long &nDestValue);

//2021-5-5  lijunqing  多出地方出现获取文件的代码，严重违反面向对象和模块化思路，股增加此函数
CString stt_get_adj_sys_para_file_path();

class CSttAdjSysParaDataTypes : public CDataTypes
{
public:
	CSttAdjSysParaDataTypes();
	virtual ~CSttAdjSysParaDataTypes();
	

public:

	void InitAdjSysParaDataType_ModuleType();
	void InitAdjSysParaDataType_WorkMode();
	void InitAdjSysParaDataType_EeType();
	void InitAdjSysParaDataType_ModulePower();
	void InitAdjSysParaDataType_CurrentModuleMerge();
	void InitAdjSysParaDataTypes();
};

// CSttAdjSysParaDataTypes g_oSttAdjSysParaDataTypes;

#endif // TMT_ADJUST_SYS_PARAMETER_H

