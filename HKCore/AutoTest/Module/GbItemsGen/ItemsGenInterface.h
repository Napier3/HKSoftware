//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenInterface.h  CItemsGenInterface

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "ItemsGenData.h"
#include "ItemsGenParasMap.h"

/*
����ģ�����ɵ����ݽӿ��࣬�������е����ݽӿ�
���ݽӿڶ�Ӧÿһ��ʵ������
ģ������ʵ���ж���Ĳ���ӳ����еĲ�����Ӧ��Լ�������ݽӿڶ�����������ݵķ�Χ֮��
*/
class CItemsGenInterface : public CExBaseList
{
public:
	CItemsGenInterface();
	virtual ~CItemsGenInterface();


//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENINTERFACE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenInterfaceKey();     }
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
	void InitDataValue(CItemsGenParasMap *pParasMap);
};

