//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_Grid.h  CRptTemp_Grid

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_Head.h"
#include "RptTemp_Row.h"
#include "RptTemp_Col.h"

class CRptTemp_Grid : public CExBaseList
{
public:
	CRptTemp_Grid();
	virtual ~CRptTemp_Grid();

	//�����дģʽ����ͬ����дģʽ����ȡ�л��е�����ʱ��������һ��
	/*1��row-item����Ϊ������Ŀ����Ե�����ԣ�һ�ж�Ӧһ��������Ŀ����������macrotest����
	  2��col-item����Ϊ������Ŀ�����ݲ�ʵ�֣�
	  3��row-rpt����Ϊ���Ա��档����ظ����ԣ�һ�ж�Ӧһ��report-def
	  4��col-rpt����Ϊ���Ա��档���ݲ�ʵ�֣�
	*/
	CString  m_strData_Mode;
	long m_nShowBorders;  //�Ƿ���ʾ�߿�

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_GRID;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_GridKey();     }
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
	long GetRowsCount();
	long GetColsCount();

	long GetRowsCount_RowMode();
	long GetColsCount_RowMode();
	long GetRowsCount_ColMode();
	long GetColsCount_ColMode();

	long GetHeadCount();

	BOOL IsDataMode_Row(); //�Ƿ�������дģʽ
	BOOL IsDataMode_Col(); //�Ƿ�������дģʽ
};

