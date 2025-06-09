//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenDataMap.h  CItemsGenDataMap

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/Expression/EpExpression.h"


/**************************
CItemsGenDataMap������ӳ������ݶ���
m_strID_MapΪӳ��Ĳ���ID����Ӧ���������ID��
�����������������ӳ��ʱ��m_strIDΪ��������Ŀ������ID
����ʹ�����ݽӿ�ӳ��ʱ��m_strIDΪʹ�ܽӿ����ݵ�ID
��ӳ��Ĳ���ID��Ϊ��ʱ��m_strValueȡֵ��ӳ��Ĳ���
*/
class CItemsGenDataMap : public CExBaseObject
{
public:
	CItemsGenDataMap();
	virtual ~CItemsGenDataMap();


	CString  m_strID_Map;
	CString  m_strValue;

	//2022-3-1  lijunqing  �Ƿ�ӳ��ɹ����������Ͽ���m_nIsMap���������Ƿ�Ϊӳ�䣬����Succ����߿ɶ���
	long m_nIsMapSucc;   //ӳ���Ƿ�ɹ���������id-mapӳ��������Ƿ���ڡ������ڵ�ӳ����������������������Ŀ������
	long m_nKeepExpr;  //ģ������ʱ����������Ŀ�����Ƿ�ֵ����Ϊ���ʽ
//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenDataMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL GetValue_String(CString &strValue, CDataGroup *pDataGroup);
	BOOL GetValue_Long(long &nValue, CDataGroup *pDataGroup);
	BOOL GetValue_Float(float &fValue, CDataGroup *pDataGroup);

	//ͨ�����ʽ�����в���ӳ���ʼ��
	BOOL InitParaByExpression(CDataGroup *pUIParas);
	BOOL InitParaByExpression(CEpExpression *pEpEpr, CDataGroup *pUIParas);

	//���ݱ��ʽ�����в���ӳ�䡣ӳ��������ʽ
	BOOL InitParasMapByInterface_Ex(CExBaseList *pInterface);

	//ͨ�����ʽ�����в���ӳ���ʼ����ӳ��������ʽ��ֵ
	BOOL InitParaByInterface_Expression(CExBaseList *pInterfac);
	BOOL InitParaByInterface_Expression(CEpExpression *pEpEpr, CExBaseList *pInterfac);
};


/////////////////////////////////////////////////////////////////////////////////////////////////
//�������ڸ�ͨѶ�������ɽڵ㣬���ͨѶ����ʹ�ã���interfaceӳ��
class CItemsGenDataset : public CItemsGenDataMap
{
public:
	CItemsGenDataset();
	virtual ~CItemsGenDataset();

	//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENDATASET;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenDatasetKey();     }
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

};