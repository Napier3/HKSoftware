//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGooseChDataTypeMngr.h  CIecGooseChDataTypeMngr

#pragma once

#include "IecGlobalDataMngrGlobal.h"


// 
// static const CString g_strAppChID_TRUE = _T("TRUE");
// static const CString g_strAppChID_FALSE = _T("FALSE");
// static const CString g_strAppChID_None = _T("none");
// static const CString g_strAppChID_Zero = _T("zero");
// static const CString g_strAppChID_TDelay = _T("t-delay");
// 
// static const CString g_strChTypeDT_Voltage = _T("voltage");
// static const CString g_strChTypeDT_prot = _T("prot");
// static const CString g_strChTypeDT_measure = _T("measure");
// 
// static const CString g_strGsChDtID_goose_ch_type       = _T("goose-ch-type");
// static const CString g_strGsChDtID_goose_in_ch         = _T("goose-in-ch");
// static const CString g_strGsChDtID_goose_out_ch_single = _T("goose-out-ch-single");
// static const CString g_strGsChDtID_goose_out_ch_double = _T("goose-out-ch-double");
// 
// 
// /*
// 		data_type	data_len	data_value
// SPS		0x01[x83]	0x01		0x00 or 0x01
// DPS		0x02[0x84]	0x02		0x06 + 1 byte (0x00, 0x40, 0x80, 0xC0)
// Quality	0x84		0x03		0x03 + 2 bytes
// Integer	0x85		0x04		4 bytes (integer value High byte…Low byte)
// Float	0x87		0x05		0x08 + 4 bytes (float value High byte…low byte)
// String	0x8a		<=65		string
// Time	0x03[0x91]	0x08		0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00
// */
// static const CString g_strGooseChType_Single       = _T("single");
// static const CString g_strGooseChType_Double       = _T("double");
// static const CString g_strGooseChType_Time         = _T("time");
// static const CString g_strGooseChType_Quality      = _T("quality");
// static const CString g_strGooseChType_Float        = _T("float");
// static const CString g_strGooseChType_String       = _T("string");
// static const CString g_strGooseChType_Struct       = _T("struct");
// static const CString g_strGooseChType_Integer       = _T("integer");
// 
// #define  DT_GooseChType_Single   0x01
// #define  DT_rGooseChType_Double  0x02
// #define  DT_rGooseChType_Time    0x03
// #define  DT_rGooseChType_Quality 0x84
// #define  DT_rGooseChType_Integer 0x85
// #define  DT_rGooseChType_Float   0x87
// #define  DT_rGooseChType_String  0x8a
// #define  DT_rGooseChType_Struct  0x8b

class CIecGooseChDataTypeMngr : public CDataTypes
{
public:
	CIecGooseChDataTypeMngr();
	virtual ~CIecGooseChDataTypeMngr();

	CDataType *m_pGooseChType;
	CDataType *m_pGooseInCh;
	CDataType *m_pGooseOutChSingle;
	CDataType *m_pGooseOutChDouble;

//重载函数
public:
	virtual UINT GetClassID() {    return STGCLASSID_CIecGooseCHDATATYPEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CIecGlobalDataMngrXmlRWKeys::CIecGooseChDataTypeMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

