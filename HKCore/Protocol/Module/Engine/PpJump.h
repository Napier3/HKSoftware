#pragma once
#include "../../../module/baseclass/exbaseobject.h"
#include "PpScript.h"
#include "PpScript.h"
#include "PpPackageDetail.h"

class CPpNode;

class CPpJump :	public CExBaseList
{
public:
	CPpJump(void);
	CPpJump(const CString &strJumpType);
	virtual ~CPpJump(void);

//����
public:
	CString m_strJumpTo;       //��ת���Ľڵ㣬�ڵ�Ϊ���ͽڵ�
	CPpScript* m_pJumpScript;
	CPpNode* m_pJumpToNode;  //������½��ڵ㣬����Ҫ����˽ڵ㵽�ļ�

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPJUMP; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpJumpKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	CPpNode* RunJump(CPpPackageDetail *pPkgDetail);

};
