//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbItemsGen.h  CGbItemsGen

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"


#include "MacroItemsGen.h"
#include "MacroSelfDefGen.h"

class CGbItemsGen : public CExBaseList
{
public:
	CGbItemsGen();
	virtual ~CGbItemsGen();

	//�Ƿ�����CItems�ڵ㣬�������ܸ������Ƿ�Ϊ1�����̶�����һ��Type = rootnode��CItems�ڵ�   20220403  shaolei
	long  m_nNewItems;
	CString m_strEngineProgID;
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CGBITEMSGEN;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CGbItemsGenKey();     }
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

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	void InitParasMapByUIParas(CDataGroup *pUIParas);
	CString GetGbxmlName();
};

