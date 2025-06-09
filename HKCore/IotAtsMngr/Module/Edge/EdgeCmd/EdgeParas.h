//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeParas.h  CEdgeParas

#pragma once

#include "EdgeCmdMngrGlobal.h"

#include "EdgeParaDatas.h"

#include "EdgeBody.h"
#include "EdgeDirResp.h"

class CEdgeParas : public CEdgeParaDatas
{
public:
	CEdgeParas();
	virtual ~CEdgeParas();


//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGEPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeParasKey();     }
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
	CEdgeBody *m_pEdgeBody;
	CEdgeDirResp *m_pEdgeDirResp;

	CJSON* m_pDirRespJson;
//˽�г�Ա�������ʷ���
public:
	CEdgeBody* GetEdgeBody()	{	return m_pEdgeBody;	}
	void SetEdgeBody(CEdgeBody* pEdgeBody)	{	m_pEdgeBody = pEdgeBody;AddTail(pEdgeBody);	}
	CEdgeDirResp* GetEdgeDirResp()	{	return m_pEdgeDirResp;	}
	void SetEdgeDirResp(CEdgeDirResp* pDirResp)	{	m_pEdgeDirResp = pDirResp;AddTail(pDirResp);	}
	CJSON* GetDirRespJson()	{	return m_pDirRespJson;	}
//���Ա������ʷ���
public:
};

