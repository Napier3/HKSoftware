#include "SttArgcArgvParser.h"

/************************************************************************/
//  ������õ���ģʽ�µ������в�����
//       ��Ŀ����  --     ��������   ----   ����   --    �������
/*   �����в���˵����
	macrotest macro_id=#;iec=1/0;meas_svr=1/0;dialog_id=#;assist=#;macro_file=#;sscl_path=#;
	
һ���������࣬���붨��ĵ�һ���������������macrotest��open_file��open_dialog
	1.1 macrotest�����ܲ��ԡ�
	          ���붨��macro_id����ʾ���Թ��ܵ�ID
			  ���Թ���ID�μ�Config/test-macro-ui-mngr.xml�ļ�
	1.2 open_file���򿪵Ĳ��Թ��ܲ����ļ���Ŀǰ��û��ʵ��
	1.3 open_dialog������������Ϣ�Ի���
	          ���붨��dialog_id
			  ���庬��μ�QSttTestCntrFrameBase::OpenDialog(const CString &strDialogID)
����macro_file�����������ʾ���Թ��ܵ������ļ��������������ϵͳ���ö���Ӧ�÷����ϵͳ
	���磺�̵籣�������������������ȣ���ͬӦ�÷���֧�ֵĹ����ǲ�һ�µ�
	�̵籣�����Թ��������ļ�Ϊ��Config/test-macro-ui-mngr.xml�ļ���ϵͳĬ��
����iec����������Ƿ���iec�������ܣ��û�61850�ɼ����֣��ϲ���Ԫ���ԣ�
�ġ�meas_svr���Ƿ���Ϊ�����˷����������Ų�������
	����ϲ���Ԫ�Զ�����ʱ����Ϊ�Զ����Եķ����
�塢assist���������ֵĽű�ģ�顣Ŀǰ��������ֻΪ���ܲ��Կ��š�����������������
����sscl_path�������򿪵�SCL�ļ�

�ߡ�����ʾ����
	7.1�����Բ��Թ��ܽ��棺
		�ֶ����Թ��ܣ�macrotest macro_id=ManualTest;
		״̬���й��ܣ�macrotest macro_id=StateTest;
	7.2�������ļ�������
		open_dialog dialog_id=FileMngr;
	7.3������U����������
		open_dialog dialog_id=ULiveupdate;
	7.4������iec��������
		macrotest macro_id=ManualTest;iec=1;
*/
/************************************************************************/

CSttArgcArgvParser::CSttArgcArgvParser()
{
	m_nUseIec = 0;
	m_nUseMeasServer = 0;
	m_nWaitingTime = 0;
}

CSttArgcArgvParser::~CSttArgcArgvParser()
{

}

////macrotest macro_id=XXXX;iec=1/0;meas_svr=1/0;
void CSttArgcArgvParser::Parser(int argc, char *argv[])
{
	if (argc <= 1)
	{
		m_strCmdID = ARGV_CMD_ID_MACROTEST;//����δ������������
		return;
	}

	if (argc == 2)
	{//�����ϰ汾������ID
		m_strMacroID = argv[1];

		if (!m_strMacroID.IsEmpty())//�ϰ汾����IDΪ��ʱ,�����ж�
		{
			m_strCmdID = ARGV_CMD_ID_MACROTEST;
		}

		return;
	}

	m_strCmdID = argv[1];
	char *pBegin =  argv[2];
	char *pEnd = pBegin + strlen(pBegin);
	InitBuffer(pBegin, pEnd);

	ParseString(ARGV_CMD_PARA_ID_MACROID, m_strMacroID);
	ParseString(ARGV_CMD_PARA_ID_DIALOGID, m_strDialogID);
	ParseLong(ARGV_CMD_PARA_ID_IEC, &m_nUseIec);
	ParseLong(ARGV_CMD_PARA_ID_MEASSERVER, &m_nUseMeasServer);
	ParseLong(ARGV_CMD_PARA_ID_waiting_time, &m_nWaitingTime);
	ParseString(ARGV_CMD_PARA_ID_ASSIST, m_strAssistID);  //2022-12-01  lijunqing

	ParseString(ARGV_CMD_PARA_ID_macro_file, m_strMacroFile);  
	ParseString(ARGV_CMD_PARA_ID_sscl_path, m_strSsclFilePath);  
}

