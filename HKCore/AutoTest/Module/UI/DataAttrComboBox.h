#pragma once

#include "..\GuideBook\ReportMap\ReportTemplateConfig\CommCmdStrcutAttrs.h"
// CDataAttrComboBox

class CDataAttrComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CDataAttrComboBox)

public:
	CDataAttrComboBox();
	virtual ~CDataAttrComboBox();

	void InitDataAttrIDComboBox();
	CString GetDataAttrID();
	void InitCommCmdDataAttrs(const CString &strDataType);

	void SetCommCmdDataAttrs(CCommCmdStrcutAttrs *pAttrs)
	{
		m_pCommCmdStrcutAttrs = pAttrs;
	}

private:
	CCommCmdStrcutAttrs *m_pCommCmdStrcutAttrs;
	CString m_strCurrDataType;

protected:
	DECLARE_MESSAGE_MAP()
};


