//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_ReportsDef.h  CRptTemp_ReportsDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_RpeortDef.h"
#include "RptTemp_ValueDef.h"

class CRptTemp_ReportsDef : public CExBaseList
{
public:
	CRptTemp_ReportsDef();
	virtual ~CRptTemp_ReportsDef();

	//������Ŀ�����·��������Ϊһ�������·����������һ��ģ������һ���̻�����ʱʵ�֡�
	//����ң�����飬�������ݾ����ڵ�����������Ŀ��ͨѶ������
	CString  m_strData_Path;  
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_REPORTSDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ReportsDefKey();     }
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
	CRptTemp_ReportDef *m_pRpeortDef;

//˽�г�Ա�������ʷ���
public:
	CRptTemp_ReportDef* GetRpeortDef()	{	return m_pRpeortDef;	}

//���Ա������ʷ���
public:
};

