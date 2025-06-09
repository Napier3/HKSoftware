//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenClass.h  CItemsGenClass

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ParasGenNode.h"
#include "ItemsGenBase.h"

/*
ģ�����ɹ����ģ���࣬Ϊģ������ʵ����ģ��
�������ݽӿڡ�ʹ�ܹ��򡢲���ӳ������ɽڵ�
���ඨ������ɽڵ������Ϊ��CParasGenNode��ģ�����ɹ���Ľṹ��ģ��ṹ��һ��
*/

class CItemsGenClass : public CItemsGenBase
{
public:
	CItemsGenClass();
	virtual ~CItemsGenClass();


//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENCLASS;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenClassKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
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

