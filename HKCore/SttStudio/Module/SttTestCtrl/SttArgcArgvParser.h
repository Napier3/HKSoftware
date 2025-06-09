#ifndef __CSttArgcArgvParser_H
#define __CSttArgcArgvParser_H

#include "../../../Module/MemBuffer/EquationBuffer.h"
#include "../Main/SttMainArgvDef.h"


class CSttArgcArgvParser : public CEquationBuffer
{
public:
    CSttArgcArgvParser();
    virtual ~CSttArgcArgvParser();

	CString m_strCmdID;     //命令ID
	CString m_strMacroID;   //测试功能ID
	CString m_strDialogID;   //弹出对话框的ID
	long  m_nUseIec;          //是否使用IEC
	long  m_nUseMeasServer;  //是否使用MEAS-Server
	long  m_nWaitingTime;//在Linux下,防止刚开机,MainCore程序还未初始化完毕,刚开机时,等待几秒再与其通讯

	//2022-12-01  LIJUNQING
	CString m_strAssistID;

	//2022-12-6
	CString m_strMacroFile;//对应的测试功能文件
	CString m_strSsclFilePath;//sscl文件路径

public:
	void Parser(int argc, char *argv[]);

};


#endif // __CSttArgcArgvParser_H
