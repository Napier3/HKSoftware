#pragma once

//2022-10-5  lijunqing
#define ARGV_CMD_ID_MACROTEST      _T("macrotest")
#define ARGV_CMD_ID_OPENFILE       _T("open_file")
#define ARGV_CMD_ID_OPENDIALOG     _T("open_dialog")//��linux��������ʾ�Ի���  20221224 zhouhj
#define ARGV_CMD_ID_OPENMACROEXE   _T("open_macroexe")//�򿪲��Թ��ܿ�ִ�г���(��Ҫָ��6.3���Թ���exe)

#define ARGV_CMD_ID_NEWTEST		   _T("NewTest")
#define ARGV_CMD_ID_OPENGBRPT      _T("OpenGbrpt")
#define ARGV_CMD_ID_OPENGBXML      _T("OpenGbxml")

#define ARGV_CMD_PARA_ID_MACROID          _T("macro_id")
#define ARGV_CMD_PARA_ID_DIALOGID         _T("dialog_id")
#define ARGV_CMD_PARA_ID_IEC              _T("iec")
#define ARGV_CMD_PARA_ID_MEASSERVER       _T("meas_svr")
//2022-12-3 zhouhj ���ڲ��Թ�������
#define ARGV_CMD_PARA_ID_macro_file      _T("macro_file")
//sscl�ļ�·��
#define ARGV_CMD_PARA_ID_sscl_path       _T("sscl_path")
#define ARGV_CMD_PARA_ID_waiting_time    _T("waiting_time")

//2022-12-01  lijunqing 
#define ARGV_CMD_PARA_ID_ASSIST          _T("assist")


#define TOOL_TEST_SET		_T("App_Set")
#define TOOL_TEST_APP_UPDATE	_T("App_Update")
#define TOOL_TEST_TESTER_UPDATE	_T("Tester_Update")
#define TOOL_TEST_SUPPORT	_T("App_Support")
#define TOOL_TEST_POWERSET	_T("App_PowerSet")
#define TOOL_TEST_VERSION	_T("App_VersionInfo")

#define AUTOTEST_IP			_T("AutoTest_IP")
#define AUTOTEST_PORT		_T("AutoTest_Port")
#define AUTOTEST_DEVTYPE	_T("AutoTest_DevType")
#define AUTOTEST_ENGINE		_T("AutoTest_Engine")
#define AUTOTEST_XML		_T("AutoTest_Xml")
#define AUTOTEST_TIME		_T("AutoTest_Time")

//20230-01-03 wuxinyi �л�����ģ��
#define STT_UPDATE_TESTMACRO_SM_SIZE		1048							//TestMacroSM�����ڴ��С			
#define STT_UPDATE_TESTMACRO_SM_ID			_T("TestMacroSM")				//TestMacroSM�����ڴ�ID
#define STT_UPDATE_TESTMACRO_TPLID			_T("UpdateTestMacroTplID")		//��������ģ���tpl_id
#define STT_UPDATE_TEST_XML_POSTFIX			_T("tplxml")					//��������ģ��ģ���ļ���׺
#define ARGV_CMD_PARA_ID_TmpPath			_T("TmpPath")					//ģ���ļ�·��

//״̬���С�sv�쳣ģ��
#define STATE_ABNORMAL_TYPE				_T("abnormal_type")		//sv�쳣ģ�������abnormal
#define SMVABNTEST_TPL_ID				_T("abnormal")	   		//sv�쳣ģ�����tpl_id
