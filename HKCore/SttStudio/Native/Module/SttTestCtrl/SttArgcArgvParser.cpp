#include "SttArgcArgvParser.h"

/************************************************************************/
//  如何设置调试模式下的命令行参数：
//       项目属性  --     配置属性   ----   调试   --    命令参数
/*   命令行参数说明：
	macrotest macro_id=#;iec=1/0;meas_svr=1/0;dialog_id=#;assist=#;macro_file=#;sscl_path=#;
	
一、功能种类，必须定义的第一个命令参数，包括macrotest、open_file、open_dialog
	1.1 macrotest：功能测试。
	          必须定义macro_id，表示测试功能的ID
			  测试功能ID参见Config/test-macro-ui-mngr.xml文件
	1.2 open_file：打开的测试功能参数文件，目前还没有实现
	1.3 open_dialog：弹出配置信息对话框
	          必须定义dialog_id
			  具体含义参见QSttTestCntrFrameBase::OpenDialog(const CString &strDialogID)
二、macro_file命令参数：表示测试功能的配置文件，这个参数用于系统内置多种应用方向的系统
	例如：继电保护、配网、电能质量等，不同应用方向支持的功能是不一致的
	继电保护测试功能配置文件为：Config/test-macro-ui-mngr.xml文件，系统默认
三、iec命令参数：是否开启iec分析功能，用户61850采集部分（合并单元测试）
四、meas_svr：是否作为测量端服务器，开放测量服务
	例如合并单元自动测试时，作为自动测试的服务端
五、assist：测试助手的脚本模块。目前测试助手只为功能测试开放。后续完善其他方面
六、sscl_path：关联打开的SCL文件

七、典型示例：
	7.1：调试测试功能界面：
		手动测试功能：macrotest macro_id=ManualTest;
		状态序列功能：macrotest macro_id=StateTest;
	7.2：调试文件管理功能
		open_dialog dialog_id=FileMngr;
	7.3：调试U盘升级更新
		open_dialog dialog_id=ULiveupdate;
	7.4：调试iec分析功能
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
		m_strCmdID = ARGV_CMD_ID_MACROTEST;//兼容未传入参数的情况
		return;
	}

	if (argc == 2)
	{//兼容老版本，功能ID
		m_strMacroID = argv[1];

		if (!m_strMacroID.IsEmpty())//老版本功能ID为空时,增加判断
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

