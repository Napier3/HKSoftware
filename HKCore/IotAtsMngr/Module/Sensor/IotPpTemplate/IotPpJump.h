//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IotPpJump.h  CIotPpJump

#pragma once

#include "IOTPPGlobal.h"

class CIotPpNode;
class CDvmDataset;

class CIotPpJump : public CExBaseList
{
public:
	CIotPpJump();
	virtual ~CIotPpJump();


	CString  m_strJump_To;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPJUMP;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpJumpKey();     }
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
	CIotPpNode *m_pIotPpNode;

//˽�г�Ա�������ʷ���
public:
	CIotPpNode* GetIotPpNode()	{	return m_pIotPpNode;	}

//���Ա������ʷ���
public:
	void UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface);
};

