//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_RpeortDef.h  CRptTemp_Group

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_Group.h"
#include "../../../Module/DataMngr/DataGroup.h"

class CRptTemp_Group : public CDataGroup
{
public:
	CRptTemp_Group();
	virtual ~CRptTemp_Group();

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_GROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CDataGroupKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

