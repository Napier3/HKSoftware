#pragma once

#include "..\..\..\Module\FilterText\FilterTextComboBox.h"

class CSttTestDebugComboBox : public CFilterTextComboBox
{
public:
	CSttTestDebugComboBox();
	virtual ~CSttTestDebugComboBox();

public:
	void InitSttTestDebugComboBox();
	void GetSttTestDebugParaText(CString &strParaText);

private:
	CFilterTextMngr *m_pFilterTextMngr;
};


void stt_InitSysCmdCmboBox(CComboBox *pComboBox);

void Stt_GetSttTestDebugParaText(const CString &strFileName,CString &strParaText);
