//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_Head.h  CRptTemp_Head

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_Cell.h"

class CRptTemp_Head : public CExBaseList
{
public:
	CRptTemp_Head();
	virtual ~CRptTemp_Head();

	//�����кϲ����ϲ����к���Ҫ�ݼ�
	//��¼�Ѿ��ϲ����е�����
	long m_nMergeCol;   

    float m_fHeadHeight;  //��������и�  //ftt 2024.12.23
    float m_fColWidth;   //���̶��п�����������п���ͬ   //ftt 2024.12.23

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_HEAD;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_HeadKey();     }
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
};

