//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenNameAdd.h  CItemsGenNameAdd

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"


#include "ItemsGenNameItem.h"
#include "ItemsGenParasMap.h"

/*
���ɲ�����Ŀʱ������Ŀ�����Ķ���
���������ı�����Ŀ����ͷ����Ŀ����β����Ŀ���ƹ����Ĳ���
���й�������ʱ����Ҫע������������������ͣ�Ӧ����format��ʽ�Ķ��屣��һ�£������ַ�������
*/
class CItemsGenNameAdd : public CExBaseList
{
public:
	CItemsGenNameAdd();
	virtual ~CItemsGenNameAdd();


	//CString  m_strText;
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenNameAddKey();     }
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
	CString GetNameAdd_Name(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
	CString GetNameAdd_ID(CItemsGenParasMap *pParasMap, CDataGroup *pDataGroup);
};

