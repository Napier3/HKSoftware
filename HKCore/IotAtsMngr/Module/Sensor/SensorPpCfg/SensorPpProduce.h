//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SensorPpProduce.h  CSensorPpProduce

#pragma once

#include "PpCfgGlobal.h"

#include "SensorPpPrase.h"


class CSensorPpProduce : public CSensorPpPrase
{
public:
	CSensorPpProduce();
	virtual ~CSensorPpProduce();


//重载函数
public:
	virtual UINT GetClassID() {    return PPCFGCLASSID_CSENSORPPPRODUCE;   }
	virtual BSTR GetXmlElementKey()  {      return CPpCfgXmlRWKeys::CSensorPpProduceKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

