#ifndef __CSttArgcArgvParser_H
#define __CSttArgcArgvParser_H

#include "../../../Module/MemBuffer/EquationBuffer.h"
#include "../Main/SttMainArgvDef.h"


class CSttArgcArgvParser : public CEquationBuffer
{
public:
    CSttArgcArgvParser();
    virtual ~CSttArgcArgvParser();

	CString m_strCmdID;     //����ID
	CString m_strMacroID;   //���Թ���ID
	CString m_strDialogID;   //�����Ի����ID
	long  m_nUseIec;          //�Ƿ�ʹ��IEC
	long  m_nUseMeasServer;  //�Ƿ�ʹ��MEAS-Server
	long  m_nWaitingTime;//��Linux��,��ֹ�տ���,MainCore����δ��ʼ�����,�տ���ʱ,�ȴ�����������ͨѶ

	//2022-12-01  LIJUNQING
	CString m_strAssistID;

	//2022-12-6
	CString m_strMacroFile;//��Ӧ�Ĳ��Թ����ļ�
	CString m_strSsclFilePath;//sscl�ļ�·��

public:
	void Parser(int argc, char *argv[]);

};


#endif // __CSttArgcArgvParser_H
