//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetsFileXml_InfoGrp.h  CSetsFileXml_InfoGrp

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_SI.h"
#include "..\..\..\..\..\Module\DataMngr\DvmDataset.h"

class CSetsFileXml_InfoGrp : public CExBaseList
{
public:
	CSetsFileXml_InfoGrp();
	virtual ~CSetsFileXml_InfoGrp();


	CString  m_strDesc;
	long  m_nSetGrpNum;
	long  m_nItemNum;
	long  m_nRemote;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_INFOGRP;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_InfoGrpKey();     }
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
	void UpdateVal(CSetsFileXml_InfoGrp *pSrcInfoGrp);
	void AppendByModify(CSetsFileXml_InfoGrp *pModifyInfoGrp);
	CSetsFileXml_SI* FindSIByDesc(const CString &strDesc);
	BOOL IsModifyed_Grp(long nGrp); //ָ����ֵ������ֵ�����Ƿ񱻱༭
	CSetsFileXml_SI* FindSIByRef(const CString &strRef);

//���Ա������ʷ���
public:
	void ParseToDvm(CDvmDataset *pDataset, long nGrp);
	void GetValStringTotal(long nGrp, CString &strVal);
	void GetValStringTotal_V110(long nGrp, CString &strVal); //���ڶ�����ֵ����ȡָ�����Ķ�ֵ���ݵĴ��ı�
	char* GetValStringTotal_V110(long nGrp);
	void GetValStringTotal_V110_Single(CString &strVal); //���ڵ�����ֵ����ȡ��ֵ���ݵĴ��ı�
};

