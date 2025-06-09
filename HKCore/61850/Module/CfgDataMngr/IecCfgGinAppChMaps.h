//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChsGin.h  CIecCfgChsGin

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfgGinAppChMap.h"
#include "IecCfgGinData.h"

class CIecCfgGinAppChMaps : public CExBaseList
{
public:
	CIecCfgGinAppChMaps();
	virtual ~CIecCfgGinAppChMaps();


//重载函数
public:

//私有成员变量
private:

//私有成员变量访问方法
public:
	void InitDataTypes();
	void ReleaseMaps();
	CIecCfgGinAppChMap* Bind(const CString &strBin, CIecCfgGinCh *pGinCh);
	void InitMaps(CExBaseList *pGinDatas);
	
private:
	void InitMaps(CIecCfgGinData *pGinData);
	void InitMaps(CIecCfgGinData *pGinData, CIecCfgGinCh *pGinCh);
};

