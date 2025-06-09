//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenDefine.h  CItemsGenDefine

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenNode.h"
#include "ItemsGenBase.h"
#include "ItemsGenInst.h"

/*
ģ�����ɹ����ģ���࣬Ϊģ������ʵ����ģ��
�������ݽӿڡ�ʹ�ܹ��򡢲���ӳ������ɽڵ�
���ඨ������ɽڵ������Ϊ��CIemsGenNode��ģ�����ɹ���Ľṹ��ģ��ṹһ��
*/
class CItemsGenDefine : public CItemsGenBase
{
public:
	CItemsGenDefine();
	virtual ~CItemsGenDefine();


//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenDefineKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CItemsGenInst* m_pCurrInst;  //��ǰ����ִ�����ɵ�Instʵ��

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	virtual CItemsGenInst* GetCurrentInst();
	void SetCurrentInst(CItemsGenInst* pInst);
};

