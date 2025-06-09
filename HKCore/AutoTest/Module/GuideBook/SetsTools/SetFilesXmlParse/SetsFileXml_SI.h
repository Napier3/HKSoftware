//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_SI.h  CSetsFileXml_SI

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_Val.h"
#include "..\..\..\..\..\Module\DataMngr\DvmDataset.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"

class CSetsFileXml_SI : public CExBaseList
{
public:
	CSetsFileXml_SI();
	virtual ~CSetsFileXml_SI();


	pugi::xml_node *m_pNode;
	CString  m_strDesc;
	CString  m_strType;
	CString  m_strUnit;
	CString  m_strMin;
	CString  m_strMax;
	CString  m_strStep;
	CString  m_strRef;

	BOOL m_bHasUnit;
	BOOL m_bHasMin;
	BOOL m_bHasMax;
	BOOL m_bHasStep;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_SI;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_SIKey();     }
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
	void SetModifyedFlag(BOOL bFlag);
	void UpdateVal(CSetsFileXml_SI *pSrcSI);
	void AppendByModify(CSetsFileXml_SI *pModifySI);
	BOOL IsModifyed_Grp(long nGrp); //ָ����ֵ������ֵ�����Ƿ񱻱༭

//���Ա������ʷ���
public:
	void ParseToDvm(CDvmDataset *pDataset, long nGrp);
	CSetsFileXml_Val* GetValByGrp(long nGrp);
	CString GetValByGrp_String(long nGrp);  //���ڶ�����ֵ��ͨ�����Ż�ȡ
	CString GetVal_String(); //���ڵ�����ֵ��ֱ�ӻ�ȡ
	CString GetLd();
};

