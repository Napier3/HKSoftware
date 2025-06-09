//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MqttPpPrase.h  CMqttPpPrase

#pragma once

#include "MqttPpCfgGlobal.h"

#include "../../../Module/DataMngr/DvmDataset.h"
#include "MqttPpPkg.h"


class CMqttPpPrase : public CDvmDataset
{
public:
	CMqttPpPrase();
	virtual ~CMqttPpPrase();


	CString  m_strDs_Optr;
//���غ���
public:
	virtual UINT GetClassID() {    return MQTTCLASSID_CMQTTPPPRASE;   }
	virtual BSTR GetXmlElementKey()  {      return CMqttPpCfgXmlRWKeys::CMqttPpPraseKey();     }
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
	CMqttPpPkg *m_ppkg;

//˽�г�Ա�������ʷ���
public:
	CMqttPpPkg* Getpkg()	{	return m_ppkg;	}

//���Ա������ʷ���
public:
	void UpdateParaValue(CDvmDataset *pSrcDataset);
	BOOL IsModelOptr_Write(){return m_strDs_Optr == _T("write");}
	CString GetDsID();
};

