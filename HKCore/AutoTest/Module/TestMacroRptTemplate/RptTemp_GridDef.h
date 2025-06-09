//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_GridDef.h  CRptTemp_GridDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_ColsDef.h"
#include "RptTemp_RowsDef.h"
#include "RptTemp_Head.h"
#include "RptTemp_Row.h"
#include "RptTemp_Col.h"
#include "RptTemp_MacroTest.h"
#include "RptTemp_Enable.h"
class CRptTemp_MacroTest;

class CRptTemp_GridDef : public CExBaseList
{
public:
	CRptTemp_GridDef();
	virtual ~CRptTemp_GridDef();

	//�����дģʽ��
	/*1��row-item����Ϊ������Ŀ����Ե�����ԣ�һ�ж�Ӧһ��������Ŀ����������macrotest����
	  2��col-item����Ϊ������Ŀ�����ݲ�ʵ�֣�
	  3��row-rpt����Ϊ���Ա��档����ظ����ԣ�һ�ж�Ӧһ��report-def
	  4��col-rpt����Ϊ���Ա��档���ݲ�ʵ�֣�
	*/
	CString  m_strData_Mode;
	long m_nShowBorders;  //�Ƿ���ʾ�߿�
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_GRIDDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_GridDefKey();     }
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
	CRptTemp_Enable *m_pEnable;
//˽�г�Ա�������ʷ���
public:
	CRptTemp_Enable* GetEnable()	{	return m_pEnable;	}

//���Ա������ʷ���
public:
	long GetRowsCount();
	long GetRowsCount_RowItem();
	long GetRowsCount_ColItem();
	long GetRowsCount_RowRpt();
	long GetRowsCount_ColRpt();

	long GetColsCount();
	long GetColsCount_RowItem();
	long GetColsCount_ColItem();
	long GetColsCount_RowRpt();
	long GetColsCount_ColRpt();

	long GetHeadCount();

	BOOL IsDataMode_Row(); //�Ƿ�������дģʽ
	BOOL IsDataMode_Col(); //�Ƿ�������дģʽ

	CRptTemp_MacroTest* GetMacroTest(long nIndex);
	BOOL IsEnable(CExBaseList *pParas);
};

