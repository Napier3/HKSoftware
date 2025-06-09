#ifndef STTRECORDANDBINTEST_H
#define STTRECORDANDBINTEST_H

#include "../Common/tmt_record.h"
#include "../../SttTestBase/SttTestBase.h"

class CSttRecordAndBinTest : public CSttTestBase, public tmt_RecordParas
{
public:
	CSttRecordAndBinTest(void);
	virtual ~CSttRecordAndBinTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;
	static CSttTestBase* CreateTest()
	{
		return new CSttRecordAndBinTest();
	}
public:
	virtual void Init();
	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void StartTest();
	virtual void Stop();
	virtual BOOL EventProcess();
	virtual bool NeedCheckHeartbeat()	{	return false;		}
	virtual void TtmToDrv();
};

#endif // STTRECORDANDBINTEST_H
