//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DsvInDataset.h  CDsvInDataset

#pragma once

#include "DsvSequence.h"

class CDsvInDataset : public CDsvSequence
{
public:
	CDsvInDataset();
	virtual ~CDsvInDataset();


//���غ���
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDSVINDATASET;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDsvInDatasetKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
// 	CDsvElement* AddElement(const CString &strText, long nOption, long nUnbound);
// 
// 	virtual BOOL DsValidate(CDvmDataset *pDataset, BOOL bValidateHead=TRUE);
// 	virtual BOOL DsValidate(CDvmDataset *pDataset, POS &posDataset, CDsvBase *pPrevAnlyDsvObj=NULL);
};

