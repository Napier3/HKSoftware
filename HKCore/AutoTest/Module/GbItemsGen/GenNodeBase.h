//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenNode.h  CGenNodeBase

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenEnable.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenNameAdd.h"
#include "ItemsGenCommCmd.h"
#include "ItemsGenSysParaEdit.h"
#include "ItemsGenSafety.h"

/*
ģ�����ɽڵ���Ļ��ࣻ��Ƕ��
������ʹ������������ӳ�䡢��Ŀ���ƹ���
*/
class CGenNodeBase : public CExBaseList
{
public:
	CGenNodeBase();
	virtual ~CGenNodeBase();


	CString  m_strType;
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CGENNODEBASE;   }
	virtual BSTR GetXmlElementKey()  {	ASSERT(FALSE);     return NULL;     }
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
	CItemsGenEnable *m_pItemsGenEnable;
	CItemsGenParasMap *m_pItemsGenParaMap;
	CItemsGenNameAdd *m_pItemsGenNameAdd;

	CItemsGenParasMap *m_pItemsGenParaMap_BK;   //һ��node������Ϊ���inst��ʵ��������Ϊÿһ��inst����ʱ������ӳ��Ӧ�����ָ���ԭʼ״̬

	CItemsGenCommCmd *m_pItemsGenCommCmd;
	CItemsGenSafety *m_pItemsGenSafety;
	CItemsGenSysParaEdit *m_pItemsGenSysParaEdit;

//˽�г�Ա�������ʷ���
public:
	CItemsGenEnable* GetItemsGenEnable()	{	return m_pItemsGenEnable;	}
	void SetItemsGenEnable(CItemsGenEnable* pItemsGenEnable)	{	m_pItemsGenEnable = pItemsGenEnable;	}
	CItemsGenParasMap* GetItemsGenParaMap()	{	return m_pItemsGenParaMap;	}
	void SetItemsGenParaMap(CItemsGenParasMap* pItemsGenParaMap)	{	m_pItemsGenParaMap = pItemsGenParaMap;	}
	CItemsGenNameAdd* GetItemsGenNameAdd()	{	return m_pItemsGenNameAdd;	}
	void SetItemsGenNameAdd(CItemsGenNameAdd* pItemsGenNameAdd)	{	m_pItemsGenNameAdd = pItemsGenNameAdd;	}

	CItemsGenParasMap* GetItemsGenParaMap_BK()	{	return m_pItemsGenParaMap_BK;	}

	CItemsGenCommCmd* GetItemsGenCommCmd()	{	return m_pItemsGenCommCmd;	}
	void SetItemsGenEnable(CItemsGenCommCmd* pItemsGenCommCmd)	{	m_pItemsGenCommCmd = pItemsGenCommCmd;	}
	CItemsGenSafety* GetItemsGenSafety()	{	return m_pItemsGenSafety;	}
	void SetItemsGenSafety(CItemsGenSafety* pItemsGenSafety)	{	m_pItemsGenSafety = pItemsGenSafety;	}
	CItemsGenSysParaEdit* GetItemsGenSysParaEdit()	{	return m_pItemsGenSysParaEdit;	}
	void SetItemsGenNameAdd(CItemsGenSysParaEdit* pItemsGenSysParaEdit)	{	m_pItemsGenSysParaEdit = pItemsGenSysParaEdit;	}

	void LogParasMapError();

//���Ա������ʷ���
public:
	virtual CString GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual CString GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	virtual BOOL IsEnable(CItemsGenInterface *pInterface);
	virtual CItemsGenInterface* GetGenInterface();
	virtual CItemsGenInterface* GetGenInterface_BK();
	virtual void InitParasMapByUIParas(CDataGroup *pUIParas);
	virtual void InitParasMapByInterface(CItemsGenInterface *pInterface);
	virtual void GetAllParasMap(CExBaseList &listParasMap);
	//����Interface��������Ҫ�������ʽ�Ĳ�������
	virtual void InitParasMapByInterface_Ex(CItemsGenInterface *pInterface);
	virtual void ResetParasMap();
};

