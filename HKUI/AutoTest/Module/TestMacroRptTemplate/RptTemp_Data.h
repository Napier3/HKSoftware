//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_RpeortDef.h  CRptTemp_Data

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "../../../Module/DataMngr/DvmData.h"
#include "RptTemp_Enable.h"

class CRptTemp_Data : public CDvmData
{
public:
	CRptTemp_Data();
	virtual ~CRptTemp_Data();

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_DATA;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CDvmDataKey();     }
	virtual void InitAfterRead();
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CRptTemp_Enable *m_pEnable;

//私有成员变量访问方法
public:
	CRptTemp_Enable* GetEnable()	{	return m_pEnable;	}
	void SetEnable(CRptTemp_Enable *pEnable);

//属性变量访问方法
public:
	BOOL IsEnable(CExBaseList *pParas);
	void DeleteEnable();
};

