//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_GROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CDataGroupKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

