//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmData.h  CLogCtrl

#pragma once

#include "DataMngrGlobal.h"


//////////////////////////////////////////////////////////////////////////
//CLogCtrl
class CLogCtrl : public CExBaseObject
{
public:
	CLogCtrl();
	virtual ~CLogCtrl();

	CString m_strDatSet;
	long m_nIntgPd;
	CString m_strLogName;
	long m_nLogEna;
	long m_nReasonCode;
	long m_nTrgOps;


//���غ���
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CLOGCTRL;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CLogCtrlKey();     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};

//////////////////////////////////////////////////////////////////////////
