#ifndef _CSttModuleHtmlRptGenBase_H
#define _CSttModuleHtmlRptGenBase_H

#include <QWidget>
#include "SttXHtmlRptGenInterface.h"

class CSttModuleHtmlRptGenBase : public CSttXHtmlRptGenInterface
{
public:
    CSttModuleHtmlRptGenBase();
    virtual ~CSttModuleHtmlRptGenBase();

	CExpandMemBuf  m_oHtmlBuffer;

	//��Ա����
	bool m_bHtmlGened;							//���Ա���HTML�ı��Ƿ񹹳�

public:	
	bool IsHtmlGend() {	return m_bHtmlGened; }
	void OpenDataTypesFile(const CString &strFile);

protected:
	BOOL m_bDataTypesCreate;
	void FreeDataTypes();
};


#endif // _CSttModuleHtmlRptGenBase_H
