#pragma once

#include"../../SttTestBase/SttTestBase.h"

#define SPI_FLAG_EREASE_FINISH		0x01
#define SPI_FLAG_IN_WRITING			0x02
#define SPI_FLAG_WRITE_FINISH		0x03
#define SPI_FLAG_EREASE_FAILED     	0x1001
#define SPI_FLAG_IN_WRITING_FAILED  0x1002

class CSttUpdateFPGA: public CSttTestBase
{
public:
    CSttUpdateFPGA();
    virtual ~CSttUpdateFPGA(void);
	static CString m_strMacroID;
	static CString m_strMacroName;

	static CSttTestBase* CreateTest()
	{
        return new CSttUpdateFPGA();
	}

public:
	virtual void StartTest();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
//    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void Stop(){}
	virtual BOOL EventProcessEx();

private:
    long m_nModuleIndex;
    CString m_strFileName;
    int m_nfd;
    long m_nUpdateIndex;
    void SendUpdateIndex();
    char* m_pChar;
};
