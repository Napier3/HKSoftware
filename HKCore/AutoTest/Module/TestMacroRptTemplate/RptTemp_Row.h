//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_Row.h  CRptTemp_Row

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_Cell.h"

class CRptTemp_Row : public CExBaseList
{
public:
	CRptTemp_Row();
	virtual ~CRptTemp_Row();

	//�����кϲ����ϲ����к���Ҫ�ݼ�
	//��¼�Ѿ��ϲ����е�����
	long m_nMergeCol; 

	//ͬһ�е�����������ͬ����Ŀ������Ҫʵ��ͬһ�в�ͬ��Ԫ����������Բ�ͬ��Ŀ������cell����չ��¼��Ŀ�����·��
	CString m_strItemPath;  //�󶨵Ĳ�����Ŀ��·����Ϣ
	void *m_pGbItemBase;  //�󶨵Ĳ�����Ŀ��CGbItemBase����CSttItemBase��

    float m_fRowHeight;  //�и� //ftt 2024.12.23


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_ROW;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_RowKey();     }
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
	CRptTemp_Cell* AddNewCell(const CString &strText);

//���Ա������ʷ���
public:
};

