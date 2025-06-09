//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ExecResult.h  CExecResult

#pragma once

#include "CmdExecGlobal.h"

#include "../../../Module/DataMngr/DvmDataset.h"

class CExecResult : public CDvmDataset
{
public:
	CExecResult();
	virtual ~CExecResult();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEXECRESULT;   }
	virtual BSTR GetXmlElementKey()  {      return CCmdExecXmlRWKeys::CExecResultKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

