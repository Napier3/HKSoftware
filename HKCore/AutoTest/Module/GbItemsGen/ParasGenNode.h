//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ParasGenNode.h  CParasGenNode

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "GenNodeBase.h"
#include "ItemsGenParaDef.h"

/*
����ģ�����ɶ�������ɽڵ��࣬�ڵ������Ƕ��
���ݲ�ͬ����Ŀ��֧�����磺���Ϸ��������򣩡��������A��B��C����������0.95,1.05,1.2��1.0�����ֱ�Ƕ�׶�����Ե����ɽڵ㣻
���ڲ�ͬ����Ŀ��֧�����ݸ��Զ�������ɽڵ㣬Ӧ���ҵ���ײ�����ɽڵ㣨Ҷ�����ɽڵ㣩�����Գ˷�ȥ���ɶ�Ӧ�ĵ�������Ŀ
��������Ŀ������ = ����֧��Ҷ�����ɽڵ�����ˣ����磺2*3*4
*/
class CParasGenNode : public CGenNodeBase
{
public:
	CParasGenNode();
	virtual ~CParasGenNode();

	long  m_nNewItems;
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CPARASGENNODE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CParasGenNodeKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CItemsGenParaDef *m_pItemsGenParaDef;

//˽�г�Ա�������ʷ���
public:
	CItemsGenParaDef* GetItemsGenParaDef()	{	return m_pItemsGenParaDef;	}
	void SetItemsGenParaDef(CItemsGenParaDef* pItemsGenParaDef)	{	m_pItemsGenParaDef = pItemsGenParaDef;	}

//���Ա������ʷ���
public:
	virtual CString GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CString GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CItemsGenInterface* GetGenInterface();
	virtual CItemsGenInterface* GetGenInterface_BK();
};

