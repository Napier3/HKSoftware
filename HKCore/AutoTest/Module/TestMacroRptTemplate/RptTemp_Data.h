//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_DATA;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CDvmDataKey();     }
	virtual void InitAfterRead();
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CRptTemp_Enable *m_pEnable;

//˽�г�Ա�������ʷ���
public:
	CRptTemp_Enable* GetEnable()	{	return m_pEnable;	}
	void SetEnable(CRptTemp_Enable *pEnable);

//���Ա������ʷ���
public:
	BOOL IsEnable(CExBaseList *pParas);
	void DeleteEnable();
};

