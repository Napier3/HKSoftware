//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenParasMap.h  CItemsGenParasMap

#pragma once

#include "GbItemsGenRuleDefMngrGlobal.h"


#include "ItemsGenDataMap.h"
class CItemsGenInterface;

//����ӳ������
/*
//����ӳ��������֣�
1������������ӳ�䣬�����ж�ʹ��
2����������Ŀ������ӿڲ���֮���ӳ��
*/
#define PARAMAP_LOG_LEVEL_UIPARAS 0
#define PARAMAP_LOG_LEVEL_INTERFACE 1

//CItemsGenParasMap��Ϊ����������γɵ�CDataGroup���󣩣����������Ŀ����֮���ӳ��
class CItemsGenParasMap : public CExBaseList
{
public:
	CItemsGenParasMap();
	virtual ~CItemsGenParasMap();


//���غ���
public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenParasMapKey();     }
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
	BOOL GetParaValueByID(const CString &strID, CDataGroup *pDataGroup, CString &strValue);
	void InitParaValueByUIParas(CDataGroup *pUIParas);
	CDvmData* GetDataByIDPath_Sort(CDataGroup *pUIParas, const CString &strIDPath);
	CDvmData* GetDataByIDPath(CDataGroup *pUIParas, const CString &strIDPath);
	CDvmData* GetDataByIDPathEx(CDataGroup *pUIParas, CDataGroup *pGrp, const CString &strIDPath);
	void InitParasMapByInterface(CItemsGenInterface *pInterface);
	void InitParasMapByInterface_Ex(CItemsGenInterface *pInterface);
	void LogParasMapError(UINT nLogLevel = PARAMAP_LOG_LEVEL_UIPARAS);
};

