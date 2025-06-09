#pragma once
#include "GbItemsGenRuleDefMngrGlobal.h"

#define MACRO_CHAR_TEST_AXISMODE_XY       _T("x-y")
#define MACRO_CHAR_TEST_AXISMODE_RANGLE   _T("r-angle")
#define MACRO_CHAR_TEST_LINEDEF_POINT     _T("point")
#define MACRO_CHAR_TEST_LINEDEF_LINE      _T("line")

class CItemsGenCharItemLine :public CExBaseObject
{
public:
	CItemsGenCharItemLine(void);
	~CItemsGenCharItemLine(void);

	CString  m_strType;
	CString  m_strAxisMode;   //Axis mode:x-y; r-angle
	CString  m_strParaIdXb;
	CString  m_strParaIdYb;
	CString  m_strParaIdXe;
	CString  m_strParaIdYe;
	CString  m_strParaIdXset;
	CString  m_strParaIdYset;
	CString  m_strParaIdXact;
	CString  m_strParaIdYact;
	CString  m_strParaIdFlagAct;

	CString  m_strParaIdSearchXb;
	CString  m_strParaIdSearchYb;
	CString  m_strParaIdSearchActb;
	CString  m_strParaIdSearchXe;
	CString  m_strParaIdSearchYe;
	CString  m_strParaIdSearchActe;
	CString  m_strParaIdSearchXc;
	CString  m_strParaIdSearchYc;


public:
	virtual UINT GetClassID() {    return GBITEMSGENMNGRCLASSID_CITEMSGENCHARITEMLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbItemsGenRuleDefMngrXmlRWKeys::CItemsGenCharItemLineKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	BOOL IsAxisMode_x_y();
	BOOL IsAxisMode_r_angle();
};
