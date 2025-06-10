//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_Cell.h  CRptTemp_Cell

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "../../Module/DataMngr/DataGroup.h"

class CRptTemp_TestMacroUiRptDef;

class CRptTemp_Cell : public CExBaseObject
{
public:
	CRptTemp_Cell();
	virtual ~CRptTemp_Cell();


	long  m_nRow_Span;
	long  m_nCol_Span;
	CString  m_strText;
	CString  m_strData_Path;  //������Ŀ�����·��������Ϊһ�������·����������һ��ģ������һ���̻�����ʱʵ�֡�
	CString  m_strType;  //������Դ���Ͷ��壺data-id��text��test-index����CRptTemp_ColDef��m_strType����
    CString  m_strHAlignType; //�ı�ˮƽ���뷽ʽ AlignLeft�Ϳ�ֵ:����� AlignRight���Ҷ��� AlignCenter��ˮƽ���� //ftt 2024.12.20
    CString  m_strVAlignType; //�ı���ֱ���뷽ʽ AlignTop�Ϳ�ֵ:���˶��� AlignCenter����ֱ���� AlignBottom���׶˶��� //ftt 2024.12.24

	//2023-11-14������ң����ԣ�ͬһ�е����ݿ��ܰ�����ѹ�����������ʡ���˲�������Ϊ��λ�����б������ݴ������Լ��
	//������Ԫ��ı������ݴ������Լ��
	CString  m_strProcess;
	CString  m_strPrecision;
	long  m_nPrecision;

	//���ڿ��Խ��Data_Path����չΪdata-id-path�����������row������Ŀ�������Ŀ��·��������ʵ��ͬһ�е��������Բ�ͬ��Ŀ
	CString m_strDataID; //�󶨵����ݵ�ID���������ݻ����ݽӿڣ�
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_CELL;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_CellKey();     }
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
	CDataGroup* GetItemsTec();
	CDataGroup* GetItemsTec(CRptTemp_TestMacroUiRptDef *pRptTempUiDef);
	BOOL UpdatePrecision();
	BOOL UpdatePrecision(CRptTemp_TestMacroUiRptDef *pRptTempUiDef);
};

