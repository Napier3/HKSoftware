//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


//���غ���
public:

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void InitDataTypes();
	void ReleaseMaps();
	CIecCfgGinAppChMap* Bind(const CString &strBin, CIecCfgGinCh *pGinCh);
	void InitMaps(CExBaseList *pGinDatas);
	
private:
	void InitMaps(CIecCfgGinData *pGinData);
	void InitMaps(CIecCfgGinData *pGinData, CIecCfgGinCh *pGinCh);
};

