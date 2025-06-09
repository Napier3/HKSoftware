#pragma once

#include "VerUpdateHisMngrGlobal.h"

class CVerUpdateHisVer : public CExBaseObject
{
public:
	CVerUpdateHisVer();
	virtual ~CVerUpdateHisVer();

	CString m_strDateTime;
	long m_nCurrVerIdx;
	long m_nPrevVerIdx;
	CString m_strCurrVer;
	CString m_strPrevVer;

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return VERUPDATEHISCLASSID_VER;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateHisXmlRWKeys::VersionKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);

	void Init(int nLocalVerIdx,int nDestVerIdx,const CString& strLocalVer,const CString& strDestVer,const CString& strDateTime=_T(""));
};


