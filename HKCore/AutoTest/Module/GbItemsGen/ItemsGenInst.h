//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenInst.h  CItemsGenInst

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenNameAdd.h"
#include "ItemsGenInterface.h"

/*
��Ŀ����ʵ����
ÿ����Ŀ����ʵ�����������˲���ӳ����ò���ӳ�����Ĳ���ӳ�䣬Ӧ����������Ŀ����ģ���ж�������ݽӿڶ�����������ݣ�����Ŀ���ƶ���
ÿ����Ŀ����ʵ������Ӧ�ñ�����Ŀ����ģ���ж������Ŀ���ɽڵ㣬�����Ŀ����

ͨ��paras-map���ӽ�������л�ȡ����ʵ��ֵ������ʵ��ֵ��ֵ��ģ���ඨ���interface
*/
class CItemsGenInst : public CExBaseList
{
public:
	CItemsGenInst();
	virtual ~CItemsGenInst();


	long  m_nNewItems;
	CString  m_strClass;
	CString  m_strCharacteristic;    //���ڱ߽���ԣ������Լ�¼Ϊ�������ߵ�ID
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENINST;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenInstKey();     }
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
	CItemsGenNameAdd *m_pItemsGenNameAdd;
	CItemsGenParasMap *m_pItemsGenParasMap;

//˽�г�Ա�������ʷ���
public:
	CItemsGenNameAdd* GetItemsGenNameAdd()	{	return m_pItemsGenNameAdd;	}
	void SetItemsGenNameAdd(CItemsGenNameAdd* pItemsGenNameAdd)	{	m_pItemsGenNameAdd = pItemsGenNameAdd;	}
	CItemsGenParasMap* GetItemsGenParasMap()	{	return m_pItemsGenParasMap;	}
	void SetItemsGenParasMap(CItemsGenParasMap* pItemsGenParasMap)	{	m_pItemsGenParasMap = pItemsGenParasMap;	}

//���Ա������ʷ���
public:
	BOOL IsClassMode_Class()	{	return m_strClass == GB_ITEMS_GEN_INST_CLASS_CLASS;		}
	BOOL IsClassMode_Define()	{	return m_strClass == GB_ITEMS_GEN_INST_CLASS_DEFINE;	}
	BOOL IsEnable(CDataGroup *pDataGroup);
	void InitInterfaceByUIParas(CDataGroup *pUIParas);
	CItemsGenInterface* GetInterface();
	CString GetNameAdd_Name(CDataGroup *pDataGroup);
	CString GetNameAdd_ID(CDataGroup *pDataGroup);
};

