#pragma once

#include "..\CfgDataMngr\IecCfgDatasMngr.h"
#include "OnllyF66FileRead.h"

class COnllyCfgFileTool
{
public:
	COnllyCfgFileTool(void);
	~COnllyCfgFileTool(void);


	BOOL ReadF66File(const CString &strFile, CIecCfgDatasMngr *pIecCfgFileMngr);

private:
	CIecCfgDatasMngr *m_pIecCfgFileMngr;

	void ReadSmv(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting);
	void ReadSmv(MU_SETTING &mu);
	void ReadSmv_92(MU_SETTING &mu, MU_GENERALSETTTING &m_mugersetting);
	void ReadSmv_91(MU_SETTING &mu, MU_GENERALSETTTING &m_mugersetting);
	void ReadSmv_ft3(MU_SETTING &mu, MU_GENERALSETTTING &m_mugersetting);

	void ReadGin(vector<GSECFG>& GseCfg);
	void ReadGin(GSECFG &gsecfg);

	void ReadGout(vector<GSECFG>& GseCfg);
	void ReadGout(GSECFG &gsecfg);
};

class CIecCfgFileTool
{
public:
	CIecCfgFileTool(void);
	~CIecCfgFileTool(void);


	BOOL ReadIecCfgFile(LPCTSTR strPath,MU_GENERALSETTTING& mu_gset, vector<MU_SETTING>& muset, GSEUI& gseui);

private:
	CIecCfgDatasMngr *m_pIecCfgFileMngr;

	void ReadSmv(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting);
	void ReadSmv(MU_SETTING &mu);
	void ReadSmv_92(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting, long nIndex);
	void ReadSmv_91(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting, long nIndex);
	void ReadSmv_ft3(vector<MU_SETTING>& mu_setting, MU_GENERALSETTTING &m_mugersetting, long nIndex);

	void ReadGin(vector<GSECFG>& GseCfg);
	void ReadGin(vector<GSECFG>& GseCfg, long nIndex);

	void ReadGout(vector<GSECFG>& GseCfg);
	void ReadGout(vector<GSECFG>& GseCfg, long nIndex);
};
