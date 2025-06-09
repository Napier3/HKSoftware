//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MacroItemsGen.h  CMacroItemsGen

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"


#include "ItemsGenClass.h"
#include "ItemsGenInst.h"
#include "ItemsGenParasMap.h"
#include "ItemsGenDefine.h"

class CMacroItemsGen : public CExBaseList
{
public:
	CMacroItemsGen();
	virtual ~CMacroItemsGen();

	CString  m_strMacroID;
	long  m_nNewItems;
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CMACROITEMSGEN;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CMacroItemsGenKey();     }
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
	CItemsGenParasMap *m_pItemsGenParasMap;
	CItemsGenClass *m_pItemsGenClass;
	CItemsGenDefine *m_pItemsGenDefine;

//˽�г�Ա�������ʷ���
public:
	CItemsGenParasMap* GetItemsGenParasMap()	{	return m_pItemsGenParasMap;	}
	void SetItemsGenParasMap(CItemsGenParasMap* pItemsGenParasMap)	{	m_pItemsGenParasMap = pItemsGenParasMap;	}
	CItemsGenClass* GetItemsGenClass()	{	return m_pItemsGenClass;	}
	void SetItemsGenClass(CItemsGenClass* pItemsGenClass)	{	m_pItemsGenClass = pItemsGenClass;	}
	CItemsGenDefine* GetItemsGenDefine()	{	return m_pItemsGenDefine;	}
	void SetItemsGenDefine(CItemsGenDefine* pItemsGenDefine)	{	m_pItemsGenDefine = pItemsGenDefine;	}

//���Ա������ʷ���
public:
	void InitParasMapByUIParas(CDataGroup *pUIParas);
};

