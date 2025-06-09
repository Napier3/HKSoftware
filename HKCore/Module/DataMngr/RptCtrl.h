//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmData.h  CRptCtrl

#pragma once

#include "DataMngrGlobal.h"


//////////////////////////////////////////////////////////////////////////
//CRptCtrl
class CRptCtrl : public CExBaseObject
{
public:
	CRptCtrl();
	virtual ~CRptCtrl();

	CString m_strDatSet;
	long m_nIntgPd;
	long m_nConfRev;
	long m_nBuffered;
	long m_nBufTime;
	long m_nTrgOps;
	long m_nOptFields;
	long m_nRptEnabled;


//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CRPTCTRL;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CRptCtrlKey();     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};

//////////////////////////////////////////////////////////////////////////
