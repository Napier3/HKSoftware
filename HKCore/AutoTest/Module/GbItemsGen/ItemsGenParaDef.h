//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenParaDef.h  CItemsGenParaDef

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenPara.h"

/*
����ģ����Ŀ���ɽڵ��ඨ��Ĳ���������
���ඨ���˸���Ŀ���ɽڵ㣨CParasGenNode�����ɵ���Ŀ�Ĳ�����Լ����Χ
����Ŀ���ɽڵ������Ŀ���ɽڵ㣬����Ĳ���ӳ���еĲ��������ó���CItemsGenParaDef��Լ����Χ
*/
class CItemsGenParaDef : public CExBaseList
{
public:
	CItemsGenParaDef();
	virtual ~CItemsGenParaDef();


//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENPARADEF;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenParaDefKey();     }
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
};

