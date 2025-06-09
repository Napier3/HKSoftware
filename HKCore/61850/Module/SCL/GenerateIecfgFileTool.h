#pragma once
#include "../IecCfgTool/IecCfgFile.h"

class CGenerateIecfgFileTool
{
public:
	CGenerateIecfgFileTool(void);
	virtual ~CGenerateIecfgFileTool(void);

	BOOL Generate(CIecCfgDevice *pIecfgDevice,const CString &strIedName);

	BOOL GenerateLineProtIecfg_220kV(CIecCfgDevice *pIecfgDevice);
	BOOL GenerateLineProtIecfg_110kV(CIecCfgDevice *pIecfgDevice);

protected:
	BOOL GenerateSMV_LineProt(CIecCfgDatasSMV *pSmvMngr);
	BOOL GenerateGout_Common(CIecCfgGoutDatas* pGoutMngr);
};
