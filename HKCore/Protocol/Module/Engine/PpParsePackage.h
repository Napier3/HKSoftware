#pragma once
#include "PpPackage.h"


class CPpParsePackage :	public CPpPackage
{
public:
	CPpParsePackage(void);
	virtual ~CPpParsePackage(void);

	CExBaseObject *m_pPackageDetailRef;
	PPACKAGEBUFFERPOS m_pBufferPos;
	long m_nRequiredLen;  //ƥ��ʱ�����ڼ����ձ��Ļ������Ƿ����㹻�ı�������

public:
	virtual UINT GetClassID() {        return PPCLASSID_PPPARSEPACKGE;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRPackageKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//�ֽڿ��ƥ��		��Ҫ���ڽ���
	virtual DWORD Match(PACKAGEBUFFERPOS &oPkgBufPos);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	void CloneAppendInterfaceVariable(CExBaseList &oDestList);
	
};
