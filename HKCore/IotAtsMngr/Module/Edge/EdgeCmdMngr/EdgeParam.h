//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeParam.h  CEdgeParam

#pragma once

#include "EdgeCmdMngrGlobal.h"


#include "EdgeData.h"
#include "EdgeParas.h"

class CEdgeParam : public CEdgeGroup
{
public:
	CEdgeParam();
	virtual ~CEdgeParam();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CEDGEPARAM;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeParamKey();     }
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
	CEdgeParas *m_pEdgeParas;

//˽�г�Ա�������ʷ���
public:
	CEdgeParas* GetEdgeParas()	{	return m_pEdgeParas;	}

//���Ա������ʷ���
public:
};

