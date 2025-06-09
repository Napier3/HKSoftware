#pragma once

#include "../../ReportMap/RptBaseFill.h"
#include "../../../../../Module/xml/XmlRW_Pugi.h"

typedef		pugi::xml_node					BDNode;
typedef		pugi::xml_attribute				BDAttB;
typedef		pugi::xml_attribute_struct		BDAttr;


class CXmlRptFill : public CRptBaseFill
{
public:
	CXmlRptFill(void); 
	virtual ~CXmlRptFill(void);
	
protected:
	pugi::xml_document m_oXmlDoc;

	void Cal(BDNode *xmlNode);
	void Cal_Attribute(BDNode *xmlNode);

	//重载父类成员虚函数
public:
	virtual CString GetReportFillClassID(){	return REPORTFILL_PROGID_XML;	};
	virtual long OpenRptTemplateFile(const CString  &strReportFile);
	virtual long SaveRptFile(const CString &strRptFile);
	virtual long FillRpt(CGuideBook* pGuideBook);
};
