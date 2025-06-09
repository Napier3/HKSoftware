//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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


//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CLOGCTRL;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CLogCtrlKey();     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};

//////////////////////////////////////////////////////////////////////////
