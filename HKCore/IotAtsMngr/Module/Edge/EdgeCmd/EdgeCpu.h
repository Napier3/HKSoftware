//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeCpu.h  CEdgeCpu

#pragma once

#include "EdgeCmdMngrGlobal.h"
#include "EdgeCmdErrorMngr.h"



class CEdgeCpu : public CEdgeCmdErrorMngr
{
public:
	CEdgeCpu();
	virtual ~CEdgeCpu();

	long  m_nCpus;
	double  m_fFrequency;
	long  m_nCache;
	CString  m_strArch;
	long  m_nCpuLmt;

//���غ���
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGECPU;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeCpuKey();     }
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

