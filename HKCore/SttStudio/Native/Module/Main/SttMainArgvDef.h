#pragma once

//2022-10-5  lijunqing
#define ARGV_CMD_ID_MACROTEST      _T("macrotest")
#define ARGV_CMD_ID_OPENFILE       _T("open_file")
#define ARGV_CMD_ID_OPENDIALOG     _T("open_dialog")//在linux程序中显示对话框  20221224 zhouhj
#define ARGV_CMD_ID_OPENMACROEXE   _T("open_macroexe")//打开测试功能可执行程序(主要指打开6.3测试功能exe)

#define ARGV_CMD_ID_NEWTEST		   _T("NewTest")
#define ARGV_CMD_ID_OPENGBRPT      _T("OpenGbrpt")
#define ARGV_CMD_ID_OPENGBXML      _T("OpenGbxml")

#define ARGV_CMD_PARA_ID_MACROID          _T("macro_id")
#define ARGV_CMD_PARA_ID_DIALOGID         _T("dialog_id")
#define ARGV_CMD_PARA_ID_IEC              _T("iec")
#define ARGV_CMD_PARA_ID_MEASSERVER       _T("meas_svr")
//2022-12-3 zhouhj 用于测试功能配置
#define ARGV_CMD_PARA_ID_macro_file      _T("macro_file")
//sscl文件路径
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

//20230-01-03 wuxinyi 切换测试模块
#define STT_UPDATE_TESTMACRO_SM_SIZE		1048							//TestMacroSM共享内存大小			
#define STT_UPDATE_TESTMACRO_SM_ID			_T("TestMacroSM")				//TestMacroSM共享内存ID
#define STT_UPDATE_TESTMACRO_TPLID			_T("UpdateTestMacroTplID")		//各个测试模块的tpl_id
#define STT_UPDATE_TEST_XML_POSTFIX			_T("tplxml")					//新增测试模块模板文件后缀
#define ARGV_CMD_PARA_ID_TmpPath			_T("TmpPath")					//模板文件路径

//状态序列、sv异常模拟
#define STATE_ABNORMAL_TYPE				_T("abnormal_type")		//sv异常模拟参数：abnormal
#define SMVABNTEST_TPL_ID				_T("abnormal")	   		//sv异常模拟参数tpl_id
