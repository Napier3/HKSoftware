//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ExecResult.h  CExecResult

#pragma once

#include "CmdExecGlobal.h"

#include "../../../Module/DataMngr/DvmDataset.h"

class CExecResult : public CDvmDataset
{
public:
	CExecResult();
	virtual ~CExecResult();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEXECRESULT;   }
	virtual BSTR GetXmlElementKey()  {      return CCmdExecXmlRWKeys::CExecResultKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

