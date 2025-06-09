//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttItems.h  CSttItems

#pragma once

#include "../SttCmdDefineGlobal.h"

#include "SttItemBase.h"

#include "SttMacroTest.h"
#include "SttSafety.h"
#include "SttCommCmd.h"
#include "SttSysParaEdit.h"
#include "SttMacroCharItems.h"

#include "../../../../AutoTest/Module/GuideBook/GuideBookDefine.h"
#include "SttTestMacroCharParas.h"


class CSttMacroCharItemLineDef : public CExBaseObject
{
public:
	CSttMacroCharItemLineDef();
	virtual ~CSttMacroCharItemLineDef();

	CString  m_strType;  //Test Type,SearchLine,AreaTestPoint
	CString  m_strAxisMode;   //Axis mode:x-y; r-angle
	CString  m_strParaIdXb;
	CString  m_strParaIdYb;
	CString  m_strParaIdXe;
	CString  m_strParaIdYe;
	CString  m_strParaIdXset;
	CString  m_strParaIdYset;
	CString  m_strParaIdXact;
	CString  m_strParaIdYact;
	CString  m_strParaIdFlagAct;

	CString  m_strParaIdSearchXb;
	CString  m_strParaIdSearchYb;
	CString  m_strParaIdSearchActb;
	CString  m_strParaIdSearchXe;
	CString  m_strParaIdSearchYe;
	CString  m_strParaIdSearchActe;
	CString  m_strParaIdSearchXc;
	CString  m_strParaIdSearchYc;

	double m_fXb;
	double m_fYb;
	double m_fXe;
	double m_fYe;
	double m_fXset;
	double m_fYset;
	double m_fXact;
	double m_fYact;
	long m_nFlagAct;  //2022-7-25  lijunqing

	double m_fSearchXb;
	double m_fSearchYb;
	long   m_nSearchActb;
	double m_fSearchXe;
	double m_fSearchYe;
	long   m_nSearchActe;
	double m_fSearchXc;
	double m_fSearchYc;

public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_MACROCHARITEMLINEDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCMacroCharItemLineDefKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	BOOL IsAxisMode_x_y();
	BOOL IsAxisMode_r_angle();

	void InitSearchValues(CValues *pSearchReport);
	void GetSearchValues(CValues *pSearchLine);
	void ChangeValueXY(double &dX, double &dY);
};


//////////////////////////////////////////////////////////////////////////
//CSttItems
class CSttItems : public CSttItemBase
{
public:
	CSttItems();
	virtual ~CSttItems();


	CString  m_strType;
	CString  m_strCharacteristicID;
	CString  m_strstxmlFile;
	CString  m_strWzdMapFile;
	CString  m_strActLogic;
	//�ʼ��������ظ����������Ϊ���Դ���������ٴΣ��Ͳ���ٴ�
	long     m_nTestTimes;  //shaolei 2023-3-17 
	//shaolei  2023-6-20 
	long m_nRptTitle;  //�Ƿ���Ϊword�������
	long m_nTitleLevel;  //��ΪWORD�������ʱ������ȼ�

//���غ���
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTITEMS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttItemsKey();     }
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

	//2022-10-14  lijunqing
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	//2023-3-21 zhouhj ���������߷���������
//	void CloneCharacteristics(CExBaseList *pCharacteristics);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CSttMacroCharItemLineDef* GetMacroCharItemLineDef();
	BOOL IsTypeNone();
	BOOL IsTypeRootNode();
	BOOL IsTypeItems();
	CSttTestMacroUiParas* GetSttTestMacroUiParas(BOOL bCreate = TRUE);
	CSttTestMacroCharParas* GetSttTestMacroCharParas(BOOL bCreate = TRUE);
	virtual long GetItemTestCount();

protected:
	virtual long SelectChildrenItems(const CString &strPath, CExBaseList &oListDest);

};

class CSttItemsEmpty : public CSttItems
{
public:
	CSttItemsEmpty();
	virtual ~CSttItemsEmpty();

public:
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};


//2022-3-28  lijunqing
CSttItems* stt_gb_new_items(CExBaseList *pParent, const CString &strName, const CString &strID);

//2022-7-25  lijunqing ����������߽ڵ�Items
CSttItems* stt_gb_get_ancestor_items_has_char(CExBaseObject *pItem);
