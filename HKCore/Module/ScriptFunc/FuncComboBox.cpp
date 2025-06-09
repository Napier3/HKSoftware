#include "StdAfx.h"
#include "FuncComboBox.h"

CFuncComboBox::CFuncComboBox(void)
{
	PFUNCDATA fData = new FUNCDATA;
	fData->strFunc = L"SetRsltJdg(\"\",);";
	fData->strname = L"SetRsltJdg";
	fData->strMsg = L"设置结果参数，参数1为路径，参数2为值。\r\n实例：SetRsltJdg(\"\",1);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"GetRsltJdg(\"\");";
	fData->strname = L"GetRsltJdg";
	fData->strMsg = L"获取结果参数，参数1为路径\r\n实例：local RsltJdg = GetRsltJdg(\"\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"SetPara(\"\",\"\",);";
	fData->strname = L"SetPara";
	fData->strMsg = L"设置Item参数，参数1为路径，参数2为参数ID值，参数3为待设置值,\r\n实例：SetPara(\"\",\"_Ua\",57);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"SetParaStr(\"\",\"\");";
	fData->strname = L"SetParaStr";
	fData->strMsg = L"设置Item参数，参数1为路径，参数2为参数ID值，参数3为待设置值,\r\n实例：SetPara(\"\",\"_Ua\",\"57\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc = L"GetPara(\"\",\"\");";
	fData->strname = L"GetPara";
	fData->strMsg = L"获取Item参数，参数1为路径，参数2为参数ID值，返回系统参数值\r\n实例：local _Ua = GetPara(\"\",\"_Ua\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetParaStr(\"\");";
	fData->strname = L"GetParaStr";
	fData->strMsg = L"获取测试参数，参数1为参数ID值，返回字符串结果";
	m_listFunc.push_back(fData);

// 	fData = new FUNCDATA;
// 	fData->strFunc =L"SetSysPara(\"\",);";
// 	fData->strname = L"SetSysPara";
// 	fData->strMsg = L"设置系统参数，参数1为参数ID值，参数2为待设置值\r\n实例：SetSysPara(\"_Un\",57);";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetSysPara(\"\");";
// 	fData->strname = L"GetSysPara";
// 	fData->strMsg = L"获取系统参数，参数1为参数ID值，返回系统参数值\r\n实例：local _Un = GetSysPara(\"_Un\");";
// 	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetShow(\"\");";
	fData->strname = L"GetShow";
	fData->strMsg = L"获取显示参数，参数1为参数ID值，返回显示参数值\r\n实例：GetShow(\"\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetShow(\"\",);";
	fData->strname = L"SetShow";
	fData->strMsg = L"设置显示参数，参数1为参数ID值，参数2为待设置值\r\n实例：SetShow(\"\",1);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetEnable(\"\");";
	fData->strname = L"GetEnable";
	fData->strMsg = L"获取Enable参数，参数1为参数ID值，返回显示参数值\r\n实例：GetEnable(\"\");";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetEnable(\"\",);";
	fData->strname = L"SetEnable";
	fData->strMsg = L"设置Enable参数，参数1为参数ID值，参数2为待设置值\r\n实例：SetEnable(\"\",1);";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetSelect(\"\");";
	fData->strname = L"GetSelect";
	fData->strMsg = L"获取Select属性，参数1为参数ID值，返回显示参数值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetSelect(\"\",);";
	fData->strname = L"SetSelect";
	fData->strMsg = L"设置Select属性，参数1为参数ID值，参数2为待设置值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetName(\"\");";
	fData->strname = L"GetName";
	fData->strMsg = L"获取名称参数，参数1为参数ID值，返回显示参数值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetName(\"\",);";
	fData->strname = L"SetName";
	fData->strMsg = L"设置名称参数，参数1为参数ID值，参数2为待设置值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetReportValue(\"\",\"\");";
	fData->strname = L"GetReportValue";
	fData->strMsg = L"获取报告值，参数1为路径，参数2为参数ID值，返回浮点数报告值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValL(\"\",\"\");";
	fData->strname = L"GetRptValL";
	fData->strMsg = L"获取报告值，参数1为路径，参数2为参数ID值，返回整数报告值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValStr(\"\",\"\");";
	fData->strname = L"GetRptValStr";
	fData->strMsg = L"获取报告值，参数1为路径，参数2为参数ID值，返回字符串报告值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetReportValue(\"\",\"\",);";
	fData->strname = L"SetReportValue";
	fData->strMsg = L"设置报告值，参数1为路径，参数2为ID值，参数3为待设置值(浮点数)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetReportValStr(\"\",\"\",);";
	fData->strname = L"SetReportValStr";
	fData->strMsg = L"设置报告值，参数1为路径，参数2为ID值，参数3为待设置值(字符串)";
	m_listFunc.push_back(fData);


	fData = new FUNCDATA;
	fData->strFunc =L"GetReportValueEx(\"\",\"\", );";
	fData->strname = L"GetReportValueEx";
	fData->strMsg = L"获取报告值，参数1为路径，参数2为参数ID值，参数3为报告编号，返回浮点数报告值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValLEx(\"\",\"\", );";
	fData->strname = L"GetRptValLEx";
	fData->strMsg = L"获取报告值，参数1为路径，参数2为参数ID值，参数3为报告编号，返回整数报告值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptValStrEx(\"\",\"\", );";
	fData->strname = L"GetRptValStrEx";
	fData->strMsg = L"获取报告值，参数1为路径，参数2为参数ID值，参数3为报告编号，返回字符串报告值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptCount(\"\");";
	fData->strname = L"GetRptCount";
	fData->strMsg = L"获取报告个数，参数1为路径，返回报告的个数（测试的次数）";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ClearReports(\"\");";
	fData->strname = L"ClearReports";
	fData->strMsg = L"清空项目或者项目分类下全部项目的报告，参数1为路径";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataValue(\"\");";
	fData->strname = L"GetDsDataValue";
	fData->strMsg = L"获取数据集数据值，参数1为参数ID路径，返回结果(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataValue(\"\",);";
	fData->strname = L"SetDsDataValue";
	fData->strMsg = L"设置数据集数据值，参数1为参数ID路径，参数2为待设置值(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataStr(\"\");";
	fData->strname = L"GetDsDataStr";
	fData->strMsg = L"获取数据集数据值，参数1为参数ID路径，返回结果(字符串)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataStr(\"\",);";
	fData->strname = L"SetDsDataStr";
	fData->strMsg = L"设置数据集数据值，参数1为参数ID路径，参数2为待设置值(字符串)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataValueEx(-1,\"\");";
	fData->strname = L"GetDsDataValueEx";
	fData->strMsg = L"获取数据集数据值，参数1为设备数据模型的编号，参数2为参数ID路径，返回结果(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataAttr(\"\", \"\");";
	fData->strname = L"GetDsDataAttr";
	fData->strMsg = L"获取数据集数据属性值，参数1为设备数据ID，参数2为参数属性，返回结果(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataValueEx(-1,\"\",);";
	fData->strname = L"SetDsDataValueEx";
	fData->strMsg = L"设置数据集数据值，参数1为设备数据模型的编号，参数2参数ID路径，参数3为待设置值(double)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDsDataStrEx(-1,\"\");";
	fData->strname = L"GetDsDataStrEx";
	fData->strMsg = L"获取数据集数据值，参数1为设备数据模型的编号，参数2参数ID路径，返回结果(字符串)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDsDataStrEx(-1,\"\",);";
	fData->strname = L"SetDsDataStrEx";
	fData->strMsg = L"设置数据集数据值，参数1为设备数据模型的编号，参数2参数ID路径，参数3为待设置值(字符串)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinError(\"\", , , );";
	fData->strname = L"CalAinError";
	fData->strMsg = L"计算遥测量的误差，返回结果判断（0/1）。参数1：遥测量的ID；参数2：遥测量的基准值；参数3：绝对误差限；参数4：相对误差限";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinErrorEx(\"\", , , );";
	fData->strname = L"CalAinErrorEx";
	fData->strMsg = L"计算遥测量的误差，返回结果判断（0/1）。参数1：实际值乘的比例；参数2：遥测量的ID；参数3：遥测量的基准值；参数4：绝对误差限；参数5：相对误差限";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinErrorNom(\"\", , , , );";
	fData->strname = L"CalAinErrorNom";
	fData->strMsg = L"计算遥测量的误差，返回结果判断（0/1）。参数1：实际值乘的比例；参数2：遥测量的ID；参数3：遥测量的基准值；参数4：计算误差的标准值；参数5：绝对误差限；参数6：相对误差限";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinStdError(, \"\", , , );";
	fData->strname = L"CalAinStdError";
	fData->strMsg = L"计算遥测量的标准差误差，返回结果判断（0/1）。参数1：要测量数据乘的比例系数；参数2：遥测量的ID；参数3：遥测量的基准值；参数4：绝对误差限；参数5：相对误差限；";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinStdError2(\"\", \"\", , , );";
	fData->strname = L"CalAinStdError2";
	fData->strMsg = L"计算遥测量的标准差误差，返回结果判断（0/1）。参数1：要测量数据乘的比例系数；参数2：遥测量的ID；参数3：遥测量的基准值；参数4：绝对误差限；参数5：相对误差限；";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalAinError2(\"\", \"\", , , );";
	fData->strname = L"CalAinError2";
	fData->strMsg = L"计算遥测量的误差，返回结果判断（0/1）。参数1：遥测量ID；参数2：遥测量基准ID；参数3：比例基准值；参数4：绝对误差限；参数5：相对误差限";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalVariation( , , , );";
	fData->strname = L"CalVariation";
	fData->strMsg = L"计算变差。参数1：实测值；参数2：理论值；参数3：基准值；参数4：比例";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalVariationErr( , , , , );";
	fData->strname = L"CalVariationErr";
	fData->strMsg = L"计算变差。参数1：实测值；参数2：理论值；参数3：基准值；参数4：比例；参数5：误差限；返回值：变差值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalVariationErrEx(\"\" ,\"\" ,\"\" ,\"\" , \"\", 1);";
	fData->strname = L"CalVariationErrEx";
	fData->strMsg = L"计算变差。参数1：实测值ID；参数2：理论值ID；参数3：基准值ID（测试参数）；参数4：变差计算结果保存量ID；参数5：误差限（测试参数）；参数6：比例；返回值：变差值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltCalErrMax(\"\", \"\",\"\", , , );";
	fData->strname = L"FltCalErrMax";
	fData->strMsg = L"计算报文数据的误差，返回结果判断（0/1）。参数1：数据ID；参数2：绝对误差值ID；参数3：相对误差值ID；参数4：基准值；参数5：绝对误差限；参数6：相对误差限";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltCalErrMin(\"\", \"\",\"\", , , );";
	fData->strname = L"FltCalErrMin";
	fData->strMsg = L"计算报文数据的误差，返回结果判断（0/1）。参数1：数据ID；参数2：绝对误差值ID；参数3：相对误差值ID；参数4：基准值；参数5：绝对误差限；参数6：相对误差限";
	m_listFunc.push_back(fData);

// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetSetValue(\"\");";
// 	fData->strname = L"GetSetValue";
// 	fData->strMsg = L"获取定值值，参数1为参数ID值，返回结果";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"SetSetValue(\"\",);";
// 	fData->strname = L"SetSetValue";
// 	fData->strMsg = L"设置定值值，参数1为参数ID值，参数2为待设置值";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetSftValue(\"\");";
// 	fData->strname = L"GetSftValue";
// 	fData->strMsg = L"获取软压板值，参数1为参数ID值，返回结果";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"SetSftValue(\"\",);";
// 	fData->strname = L"SetSftValue";
// 	fData->strMsg = L"设置软压板值，参数1为参数ID值，参数2为待设置值";
// 	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetTestPara(\"\");";
	fData->strname = L"GetTestPara";
	fData->strMsg = L"获取测试参数，参数1为参数ID值，返回浮点数结果";
	m_listFunc.push_back(fData);
	
	fData = new FUNCDATA;
	fData->strFunc =L"GetTestParaStr(\"\");";
	fData->strname = L"GetTestParaStr";
	fData->strMsg = L"获取测试参数，参数1为参数ID值，返回字符串结果";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetTestPara(\"\",);";
	fData->strname = L"SetTestPara";
	fData->strMsg = L"设置测试参数，参数1为参数ID值，参数2为待设置值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetTestParaStr(\"\",\"\");";
	fData->strname = L"SetTestParaStr";
	fData->strMsg = L"设置测试参数，参数1为参数ID值，参数2为待设置值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GotoItem(\"\");";
	fData->strname = L"GotoItem";
	fData->strMsg = L"转到Item项";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtExcuteCmd(\"\", \"\");";
	fData->strname = L"MtExcuteCmd";
	fData->strMsg = L"调用测试仪器控制接口，执行测试命令，参数1：字符串，命令ID；参数2：字符串，命令参数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtRegistPpDataMsg(\"\");";
	fData->strname = L"MtRegistPpDataMsg";
	fData->strMsg = L"向规约引擎程序注册测试仪器控制接口程序外部消息，执行测试命令，参数1：字符串，规约引擎数据对象路径";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtUnRegistPpDataMsg(\"\");";
	fData->strname = L"MtUnRegistPpDataMsg";
	fData->strMsg = L"取消规约引擎程序注册测试仪器控制接口程序外部消息，参数1：字符串，规约引擎数据对象路径";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtRegistCmdMsg(\"\", 0, 1, 1);";
	fData->strname = L"MtRegistCmdMsg";
	fData->strMsg = L"向规约引擎程序注册测试仪器控制接口程序外部消息，执行测试命令，参数1：字符串，通讯命令；参数2：命令状态，0为通讯前，1只命令完成后；参数3：消息的wParam；参数4：lParam";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"MtUnRegistCmdMsg(\"\");";
	fData->strname = L"MtUnRegistCmdMsg";
	fData->strMsg = L"取消规约引擎程序注册测试仪器控制接口程序外部消息，参数1：字符串，通讯命令ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"BreakLoop();";
	fData->strname = L"BreakLoop";
	fData->strMsg = L"进行重复多次测试时，结束重复测试";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"BreakItems();";
	fData->strname = L"BreakItems";
	fData->strMsg = L"跳出项目分类的测试，从下一个分类开始测试，参数：项目分类的层次，0表示跳出当前分类，1表示跳出上一级分类，依次类推";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetUploadRptFile();";
	fData->strname = L"SetUploadRptFile";
	fData->strMsg = L"设置测试完成后，自动导出报告文件的文件名";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ShowMsg(\"\");";
	fData->strname = L"ShowMsg";
	fData->strMsg = L"显示信息";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"PlayMusicFile(\"\", );";
	fData->strname = L"PlayMusicFile";
	fData->strMsg = L"播放音乐";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExVal( , );";
	fData->strname = L"GetRptExVal";
	fData->strMsg = L"获得报告数据属性的值，第一个参数：报告数据索引，第二个参数：报告数据属性ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExValD( , );";
	fData->strname = L"GetRptExValD";
	fData->strMsg = L"获得报告数据属性的值，第一个参数：报告数据ID，第二个参数：报告数据属性ID；返回浮点数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExValL( , );";
	fData->strname = L"GetRptExValL";
	fData->strMsg = L"获得报告数据属性的值，第一个参数：报告数据ID，第二个参数：报告数据属性ID；返回整数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExValS( , );";
	fData->strname = L"GetRptExValS";
	fData->strMsg = L"获得报告数据属性的值，第一个参数：报告数据ID，第二个参数：报告数据属性ID；返回字符串";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRptExCount();";
	fData->strname = L"GetRptExCount";
	fData->strMsg = L"获取报告数据的个数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTmGap(, , \"\");";
	fData->strname = L"CalTmGap";
	fData->strMsg = L"计算报告数据两个数据之间的时间间隔，数据属性必须为时间对象,参数1和2表示两个报告数据的ID，第3个参数表示数据属性ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTmGapEx(, , \"\", \"\");";
	fData->strname = L"CalTmGapEx";
	fData->strMsg = L"计算报告数据两个数据之间的时间间隔，数据属性必须为时间对象,参数1和2表示两个报告数据的ID，第3、4个参数表示数据属性ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTmGapEx2(, , \"\", \"\");";
	fData->strname = L"CalTmGapEx2";
	fData->strMsg = L"计算报告数据两个数据之间的时间间隔，数据属性必须为时间对象,参数1和2表示两个报告数据的ID，第3、4个参数表示数据索引（从0开始）";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetTestIndex();";
	fData->strname = L"GetTestIndex";
	fData->strMsg = L"获取重复测试时的次数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalRptValMax(\"\", \"\", );";
	fData->strname = L"CalRptValMax";
	fData->strMsg = L"计算报告数据的最大值，参数1：项目的路径，可以为测试项目，也可以为项目分类；参数2：参数的ID；参数3：缺省值；返回值：如果“参数ID”的数据存在，则返回最大值，否则返回缺省值";
	m_listFunc.push_back(fData);
	
	fData = new FUNCDATA;
	fData->strFunc =L"CalRptValMin(\"\", \"\", );";
	fData->strname = L"CalRptValMin";
	fData->strMsg = L"计算报告数据的最小值，参数1：项目的路径，可以为测试项目，也可以为项目分类；参数2：参数的ID；参数3：缺省值；返回值：如果“参数ID”的数据存在，则返回最小值，否则返回缺省值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalRptValAvg(\"\", \"\", );";
	fData->strname = L"CalRptValAvg";
	fData->strMsg = L"计算报告数据的平均值，参数1：项目的路径，可以为测试项目，也可以为项目分类；参数2：参数的ID；参数3：缺省值；返回值：如果“参数ID”的数据存在，则返回平均值，否则返回缺省值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExEqL( \"\", );";
	fData->strname = L"FilterRptExEqL";
	fData->strMsg = L"过滤扩展报告数据，参数1：扩展报告数据的属性ID，参数2：扩展报告数据的属性值（整数）";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptInit( );";
	fData->strname = L"FilterRptInit";
	fData->strMsg = L"初始化报告过滤，清除过滤的结果";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExEqStr( \"\", \"\");";
	fData->strname = L"FilterRptExEqStr";
	fData->strMsg = L"过滤扩展报告数据，参数1：扩展报告数据的属性ID，参数2：扩展报告数据的属性值（字符串）";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExHasStr( \"\", \"\");";
	fData->strname = L"FilterRptExHasStr";
	fData->strMsg = L"过滤扩展报告数据，参数1：扩展报告数据的属性ID，参数2：扩展报告数据的属性值包含的字符串";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterRptExNoStr( \"\", \"\");";
	fData->strname = L"FilterRptExNoStr";
	fData->strMsg = L"过滤扩展报告数据，参数1：扩展报告数据的属性ID，参数2：扩展报告数据的属性值不能包含的字符串";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FilterCombine( \"\", \"\",  \"\");";
	fData->strname = L"FilterCombine";
	fData->strMsg = L"拼接过滤后的扩展报告数据，参数1：扩展报告数据的属性ID，参数2：拼接后数据保存的报告数据ID，参数3：拼接的分隔符号，缺省为\";\"";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExQuery( \"\");";
	fData->strname = L"FltRptExQuery";
	fData->strMsg = L"从过滤后的报告数据中查询满足条件的一个数据，参数1：条件，格式为 name=瞬时电流速断动作;item-index=49;group-index=72";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetCount( );";
	fData->strname = L"FltRptExGetCount";
	fData->strMsg = L"从过滤后的报告数据中获取数据继数量";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetLong( , \"\");";
	fData->strname = L"FltRptExGetLong";
	fData->strMsg = L"从过滤后的报告数据中获取一个数据对象的属性值，返回整数，参数1：数据继中的索引； 参数2：属性id";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetStr( , \"\");";
	fData->strname = L"FltRptExGetStr";
	fData->strMsg = L"从过滤后的报告数据中获取一个数据对象的属性值，返回字符串，参数1：数据集中的索引； 参数2：属性id";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetDouble( , \"\");";
	fData->strname = L"FltRptExGetDouble";
	fData->strMsg = L"从过滤后的报告数据中获取一个数据对象的属性值，返回浮点数，参数1：数据继中的索引； 参数2：属性id";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValCount( );";
	fData->strname = L"FltRptExGetValCount";
	fData->strMsg = L"从过滤后的报告数据中获取第n个数据“数值”的数量，参数1：第n个数据的索引，从0开始编号；返回“数值”的数量";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValLong( , \"\");";
	fData->strname = L"FltRptExGetValLong";
	fData->strMsg = L"从过滤后的报告数据中获取第n个数据的“数值”的值，返回整数；参数1：第n个数据的索引； 参数2：“数值”的索引，数字表示按编号索引，字符串表示按ID索引";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValStr( , \"\");";
	fData->strname = L"FltRptExGetValStr";
	fData->strMsg = L"从过滤后的报告数据中获取第n个数据的“数值”的值，返回字符串；参数1：第n个数据的索引； 参数2：“数值”的索引，数字表示按编号索引，字符串表示按ID索引";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExGetValDouble( , \"\");";
	fData->strname = L"FltRptExGetValDouble";
	fData->strMsg = L"从过滤后的报告数据中获取第n个数据的“数值”的值，返回浮点数double；参数1：第n个数据的索引； 参数2：“数值”的索引，数字表示按编号索引，字符串表示按ID索引";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExCalValError( , \"\");";
	fData->strname = L"FltRptExCalValError";
	fData->strMsg = L"过滤后的报告数据中，判断第n个数据的“数值”的值是否满足误差要求，返回结论，0表示不满足，1表示满足；参数1：第n个数据的索引； 参数2：“数值”的索引，数字表示按编号索引，字符串表示按ID索引；参数3：参考数值；参数4：绝对误差；参数5：相对误差";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"FltRptExCalValErrEx(\"\", \"\", , , );";
	fData->strname = L"FltRptExCalValErrEx";
	fData->strMsg = L"在所有的报告数据中，判断第数据的“数值”的值是否满足误差要求，返回结论，0表示不满足，1表示满足；参数1：DataID； 参数2：“数值”ID；参数3：参考数值；参数4：绝对误差；参数5：相对误差";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CreateDevice( );";
	fData->strname = L"CreateDevice";
	fData->strMsg = L"创建规约引擎设备，参数1：规约模板，参数2：设备电表文件；参数3：设备名称";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ReleaseDevice( );";
	fData->strname = L"ReleaseDevice";
	fData->strMsg = L"释放规约引擎设备，参数1：设备名称";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDeviceAttrStr( );";
	fData->strname = L"GetDeviceAttr";
	fData->strMsg = L"规约引擎设备数据模型的属性数据，参数1：属性ID，例如“nane”";
	m_listFunc.push_back(fData);
	
	fData = new FUNCDATA;
	fData->strFunc =L"GetDeviceAttrL(\"\");";
	fData->strname = L"GetDeviceAttrL";
	fData->strMsg = L"规约引擎设备数据模型的属性数据，参数1：属性ID，例如“nane”";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDeviceAttrL( );";
	fData->strname = L"SetDeviceAttrL";
	fData->strMsg = L"设置规约引擎设备数据模型的属性数据，参数1：属性ID，例如“value”；参数2：数据值，整数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDeviceAttrStr( );";
	fData->strname = L"SetDeviceAttrStr";
	fData->strMsg = L"设置规约引擎设备数据模型的属性数据，参数1：属性ID，例如“value”；参数2：数据值字符串";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptGetDevieNodeDatas( );";
	fData->strname = L"RptGetDevieNodeDatas";
	fData->strMsg = L"规约引擎设备数据模型的数据节点数据，参数1：路径，例如“CPU=1\\\\xYC=4”";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DeleteAllNodeData( );";
	fData->strname = L"DeleteAllNodeData";
	fData->strMsg = L"删除设备数据节点的全部数据，参数1：路径，例如“SOE”、“YX”";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"IsProtocol(\"MmsEngine\");";
	fData->strname = L"IsProtocol";
	fData->strMsg = L"判断测试使用的规约类型。MMS规范为MmsEngine，传统规约为规约模板文件名，不带后缀";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptGetDeviceAttrs( );";
	fData->strname = L"RptGetDeviceAttrs";
	fData->strMsg = L"规约引擎设备数据模型的数据节点数据，无参数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetDevieNodeDataAttr( );";
	fData->strname = L"GetDevieNodeDataAttr";
	fData->strMsg = L"获取规约引擎设备数据模型的数据节点数据属性，参数1：路径，例如“CPU=1\\\\xYC=4\\\\item-index=2”，参数2：属性ID，例如“nane”";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetDevieNodeDataAttr( );";
	fData->strname = L"SetDevieNodeDataAttr";
	fData->strMsg = L"设置规约引擎设备数据模型的数据节点数据属性，参数1：路径，例如“CPU=1\\\\xYC=4\\\\item-index=2”，参数2：属性ID，例如“nane”；参数3：数据";
	m_listFunc.push_back(fData);

// 	fData = new FUNCDATA;
// 	fData->strFunc =L"RecordPkg( );";
// 	fData->strname = L"RecordPkg";
// 	fData->strMsg = L"设置规约引擎录波规约帧，参数1表示规约帧的ID";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"UnRecordPkg();";
// 	fData->strname = L"UnRecordPkg";
// 	fData->strMsg = L"取消规约引擎录波规约帧，参数1表示规约帧的ID";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetPckgPcTm( , , );";
// 	fData->strname = L"GetPckgPcTm";
// 	fData->strMsg = L"得到规约帧的发送/接受时间，参数1表示规约帧的ID，参数2表示存储的变量的数据ID，参数3表示获取的是第一个或者是最后一个数据";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetGpsPcTmMap(,);";
// 	fData->strname = L"GetGpsPcTmMap";
// 	fData->strMsg = L"从标准源获取GPS时间与PC时间的对应关系，参数1:存储GPS时间的变量; 参数2：存储PC时间的变量";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"GetOutGpsTm( );";
// 	fData->strname = L"GetOutGpsTm";
// 	fData->strMsg = L"获取标准源输出时刻的GPS时间. 参数1:存储时间的变量ID";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"CalGpsPcTmGap(,);";
// 	fData->strname = L"CalGpsPcTmGap";
// 	fData->strMsg = L"计算两个时间的间隔,返回毫秒数，参数1表示第一个时间的变量，参数2表示第二个时间的变量";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"RdMacroTest();";
// 	fData->strname = L"RdMacroTest";
// 	fData->strMsg = L"读取标准源的结果数据";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"CrtGpsDtTm();";
// 	fData->strname = L"CrtGpsDtTm";
// 	fData->strMsg = L"创建一个GPS时间对象，包括年、月、日、时、分、秒、毫秒、微秒";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"CrtGpsTm();";
// 	fData->strname = L"CrtGpsTm";
// 	fData->strMsg = L"创建一个GPS时间对象，包括时、分、秒、毫秒、微秒";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"LGetRptDatas(, , );";
// 	fData->strname = L"LGetRptDatas";
// 	fData->strMsg = L"获取满足条件的报告数据的个数，参数1：项目的路径；参数2：数据的ID；参数3：数据的值";
// 	m_listFunc.push_back(fData);
// 
// 	fData = new FUNCDATA;
// 	fData->strFunc =L"DownMacroPara();";
// 	fData->strname = L"DownMacroPara";
// 	fData->strMsg = L"重新下载电气量测试项目的参数数据（试验中的通讯命令调用）";
// 	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SelectItem();";
	fData->strname = L"SelectItem";
	fData->strMsg = L"选择某个项目，参数1：项目的路径";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptCnt();";
	fData->strname = L"GtItmRptCnt";
	fData->strMsg = L"获得当前选择的项目的报告的个数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SelItemRpt();";
	fData->strname = L"SelItemRpt";
	fData->strMsg = L"选择项目的报告对象，参数1：项目的报告的索引";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptVal();";
	fData->strname = L"GtItmRptVal";
	fData->strMsg = L"获得项目的指定的报告的数据：浮点数，参数1：值的ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValL();";
	fData->strname = L"GtItmRptValL";
	fData->strMsg = L"获得项目的指定的报告的数据：整数，参数1：值的ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValS();";
	fData->strname = L"GtItmRptValS";
	fData->strMsg = L"获得项目的指定的报告的数据：字符串，参数1：值的ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptVCnt();";
	fData->strname = L"GtItmRptVCnt";
	fData->strMsg = L"获得项目的指定的报告的数据个数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptVal2();";
	fData->strname = L"GtItmRptVal2";
	fData->strMsg = L"获得项目的指定的报告的数据：浮点数，参数1：值索引编号，从0开始编号";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValL2();";
	fData->strname = L"GtItmRptValL2";
	fData->strMsg = L"获得项目的指定的报告的数据：整数，参数1：值索引编号，从0开始编号";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptValS2();";
	fData->strname = L"GtItmRptValS2";
	fData->strMsg = L"获得项目的指定的报告的数据：字符串，参数1：值索引编号，从0开始编号";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDCnt();";
	fData->strname = L"GtItmRptDCnt";
	fData->strMsg = L"获得项目扩展报告的数据个数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDVal();";
	fData->strname = L"GtItmRptDVal";
	fData->strMsg = L"获得项目扩展报告数据，浮点数，参数1：报告数据的索引，参数2：报告数据的参数ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDValL();";
	fData->strname = L"GtItmRptDValL";
	fData->strMsg = L"获得项目扩展报告数据，整数，参数1：报告数据的索引，参数2：报告数据的参数ID";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GtItmRptDValS();";
	fData->strname = L"GtItmRptDValS";
	fData->strMsg = L"获得项目扩展报告数据，字符串，参数1：报告数据的索引，参数2：报告数据的参数ID";
	m_listFunc.push_back(fData);

// 	luabind::def("CalIEC", &GBS_IEC),
// 		luabind::def("CalIEEE", &GBS_IEEE),
// 		luabind::def("CalIAC", &GBS_IAC),
// 		luabind::def("CalI2T", &GBS_I2T)

	fData = new FUNCDATA;
	fData->strFunc =L"CalIEC( , , , );";
	fData->strname = L"CalIEC";
	fData->strMsg = L"IEC(double dValue, double dTp, double dK, double dAlpha)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CmpDouble(  ,  ,  );";
	fData->strname = L"CmpDouble";
	fData->strMsg = L"double浮点数比较，第三个参数为比较精度CmpDouble(strVa1, strVal2, strPrecision)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalRelErr(  ,  );";
	fData->strname = L"CalRelErr";
	fData->strMsg = L"计算相对误差，参数1：绝对误差数值，参数2：基准数据值";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RunExe( \"\" , \"\" );";
	fData->strname = L"RunExe";
	fData->strMsg = L"运行Exe程序，参数1：Exe程序的绝对路径，例如“D:\\\\Program Files\\\\EPOTO\\\\e-Report\\\\Bin\\\\CommCmdTest.exe”，参数2：程序的命令行参数";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ExitExe( \"\" );";
	fData->strname = L"ExitExe";
	fData->strMsg = L"结束进程，参数：Exe程序的名字，例如“CommCmdTest.exe”";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalIEEE( , , , , , , , );";
	fData->strname = L"CalIEEE";
	fData->strMsg = L"CalIEEE(double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalIAC( , , , , , , , );";
	fData->strname = L"CalIAC";
	fData->strMsg = L"CalIAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalI2T( , , );";
	fData->strname = L"CalI2T";
	fData->strMsg = L"CalI2T(double dValue, double dTp, double dA)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTimeGap( , );";
	fData->strname = L"CalTimeGap";
	fData->strMsg = L"CalTimeGap(string strTime1, string strTime2)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalTimeGapCurr( );";
	fData->strname = L"CalTimeGapCurr";
	fData->strMsg = L"CalTimeGapCurr(string strTime1)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"AddLocalTime( );";
	fData->strname = L"AddLocalTime";
	fData->strMsg = L"AddLocalTime(nHour, nMinute, mSecond)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SubLocalTime( );";
	fData->strname = L"SubLocalTime";
	fData->strMsg = L"SubLocalTime(nHour, nMinute, mSecond)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetCount( );";
	fData->strname = L"RptExDsGetCount";
	fData->strMsg = L"RptExDsGetCount(string strPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetValueD( );";
	fData->strname = L"RptExDsGetValueD";
	fData->strMsg = L"RptExDsGetValueD(string strPath, long nIndex)";
	m_listFunc.push_back(fData);


	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetValueL( );";
	fData->strname = L"RptExDsGetValueL";
	fData->strMsg = L"RptExDsGetCount(string strPath, long nIndex)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RptExDsGetValueStr( );";
	fData->strname = L"RptExDsGetValueStr";
	fData->strMsg = L"RptExDsGetValueStr(string strPath, long nIndex)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvClear( );";
	fData->strname = L"DsvClear";
	fData->strMsg = L"DsvClear()";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvAddElement( );";
	fData->strname = L"DsvAddElement";
	fData->strMsg = L"DsvAddElement(string strText, long nOption, long nUnbound)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvAddEChoice( );";
	fData->strname = L"DsvAddEChoice";
	fData->strMsg = L"DsvAddEChoice(string strText, long nOption, long nUnbound)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"DsvValid( );";
	fData->strname = L"DsvValid";
	fData->strMsg = L"DsvValid(long nValidateHead)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RecordCmd(\"\", \"\");";
	fData->strname = L"RecordCmd";
	fData->strMsg = L"RecordCmd(string strCmdID, string strCmdPara)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"AdjustWord( 0 );";
	fData->strname = L"AdjustWord";
	fData->strMsg = L"AdjustWord(long nPopDlg)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeTime(\"\", \"\", \"\");";
	fData->strname = L"CalSoeTime";
	fData->strMsg = L"CalSoeTime(char *pszRptID, char *pszSoe1Attr, char *pszSoe2Attr)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeTimeEx(\"\", \"\", \"\");";
	fData->strname = L"CalSoeTimeEx";
	fData->strMsg = L"CalSoeTime(char *pszRptID, char *pszSoe1Attr,char *pszVal1, char *pszSoe2Attr,char *pszVal2)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeTripDesc(\"\", \"\");";
	fData->strname = L"CalSoeTripDesc";
	fData->strMsg = L"CalSoeTripDesc(char *pszRptID, char *pszSoeID)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetItemTestTime(\"\");";
	fData->strname = L"GetItemTestTime";
	fData->strMsg = L"GetItemTestTime(const char* pszPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeError( , \"\" , \"\" , \"\", , , );";
	fData->strname = L"CalSoeError";
	fData->strMsg = L"CalSoeError(double dRate, char* pszPath, char *pszRptID, char *pszAbsErrID, char* pszRelErrID, double dStdVal, double dAbsErr, double dRelErr)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"CalSoeError2( , \"\" , \"\" , \"\", , , , );";
	fData->strname = L"CalSoeError2";
	fData->strMsg = L"CalSoeError2(double dRate, char* pszPath, char *pszRptID, char *pszAbsErrID, char* pszRelErrID, double dStdVal, double dRelCalStdVal, double dAbsErr, double dRelErr)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RcdSelect(\"\");";
	fData->strname = L"RcdSelect";
	fData->strMsg = L"RcdSelect(const char* pszPara)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RcdConfig();";
	fData->strname = L"RcdConfig";
	fData->strMsg = L"RcdConfig()";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"RcdValidate(\"\");";
	fData->strname = L"RcdValidate";
	fData->strMsg = L"RcdValidate(const char* pszRsltID)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRepeatTimes(\"\");";
	fData->strname = L"GetRepeatTimes";
	fData->strMsg = L"GetRepeatTimes(const char* pszItemPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"GetRepeatSuccTimes(\"\");";
	fData->strname = L"GetRepeatSuccTimes";
	fData->strMsg = L"GetRepeatSuccTimes(const char* pszItemPath)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"SetCmdZoneIndex( );";
	fData->strname = L"SetCmdZoneIndex";
	fData->strMsg = L"SetCmdZoneIndex(long nZoneIndex)";
	m_listFunc.push_back(fData);

	fData = new FUNCDATA;
	fData->strFunc =L"ValidBeginEndValRange(\"BeginVal\",\"EndVal\", \"Step\", 0.1, 0.001, 10, 200, 0);";
	fData->strname = L"ValidBeginEndValRange";
	fData->strMsg = L"SetCmdZoneIndex(char *pBeginValID, char *pEndValID, char *pStepID, double dMinRange, double dMinStep, long nMinSteps, long nMaxSteps, long nUseNeg)";
	m_listFunc.push_back(fData);
}

void CFuncComboBox::DeleteAll()
{
	LISTFUNC::const_iterator iter = m_listFunc.begin();
	for (;iter != m_listFunc.end();iter++)
	{
		PFUNCDATA pData = *iter;
		delete pData;
	}
}

CFuncComboBox::~CFuncComboBox(void)
{
	DeleteAll();
}
BEGIN_MESSAGE_MAP(CFuncComboBox, CComboBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CFuncComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CFuncComboBox::PreSubclassWindow()
{
	LISTFUNC::const_iterator iter = m_listFunc.begin();
	for (;iter != m_listFunc.end();iter++)
	{
		PFUNCDATA pData = *iter;
		AddString(pData->strname);
	}

	CComboBox::PreSubclassWindow();
}

CString CFuncComboBox::GetSelectedstrFunc()
{
	PFUNCDATA pData = GetSelectedData();
	if (pData == NULL)
	{
		return L"";
	}
	return pData->strFunc;

}

struct FuncData;

PFUNCDATA CFuncComboBox::GetSelectedData()
{
	int nIndex = GetCurSel();
	if (nIndex ==-1)
	{
		return NULL;
	}

	CString strName;
	GetLBText(nIndex,strName);
	PFUNCDATA pData = NULL;

	LISTFUNC::const_iterator iter = m_listFunc.begin();
	for (;iter != m_listFunc.end();iter++)
	{
		pData = *iter;
		if (pData->strname == strName)
		{
			break;
		}
	}

	return pData;
}

CString CFuncComboBox::GetSelectedstrMsg()
{
	PFUNCDATA pData = GetSelectedData();

	return pData->strMsg;
}