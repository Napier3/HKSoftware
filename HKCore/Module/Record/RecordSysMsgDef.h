// RECORDSysMsgDef.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RECORDSYSMSGDEF_H__)
#define _RECORDSYSMSGDEF_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// 系统消息定义

//UIWndDescartesAxis
#define WM_DRAW_DESCARTES						(WM_USER + 1)
#define WM_SET_CURVES_SHOWHIDE					(WM_USER + 2)

//UIWndGenShortTestDescartesAxis
#define WM_DRAW_GENSHORTDESCARTES   			(WM_USER + 3)
#define WM_SYSOPTR_GENSHORTDESCARTES_CONFIG     (WM_USER + 4)
#define WM_SYSOPTR_ADVANCESPOTPOINT				(WM_USER + 5)

//UIWndPage
#define WM_DELETE_PAGE							(WM_USER + 6)
#define WM_RECORD								(WM_USER + 7)

//UIWndGenShortTestGrid
#define WM_SHOWGENSHORTGRID						(WM_USER + 8)
#define WM_SHOWADVANCESTOPPOINT					(WM_USER + 9)

//MrDraw(DrawGlobalDef)
#define WM_RECORD_TIMER_DRAW					(WM_USER + 89)
#define WM_DRAW									(WM_USER + 90)
#define WM_INVALIDATE_RANGESTATEAXIS		    (WM_USER + 91)
#define WM_VARIABLE_SIZE_CHANGED				(WM_USER + 92)
#define WM_VARIABLE_POS_CHANGED					(WM_USER + 93)
#define WM_VARIABLE_SELECT_CHANGED				(WM_USER + 94)
#define WM_TIMEAXIS_CHANGED						(WM_USER + 95)
#define WM_TIMECURSOR_POS_CHANGE				(WM_USER + 96)
#define WM_TIMECURSOR_SELECT_CHANGE				(WM_USER + 97)
#define WM_TIME_CHANGED							(WM_USER + 98)

//MrOnlineServer
//#define USER_PROGRESS_STEP						(WM_USER + 98)
//#define USER_PROGRESS							(WM_USER + 99)
#define WM_ALARMSENDING							(WM_USER + 100)

//远程在线分析的
// #define WM_ALARMCALLING							(WM_USER + 101)
// #define WM_CLOSE_HARM_ANALYSE					(WM_USER + 102)
// #define WM_CLOSE_FREQUENCY_ANALYSE				(WM_USER + 103)
// #define WM_CLOSE_SEQUENCE_ANALYSE				(WM_USER + 104)
// #define WM_CLOSE_VECTOR_ANALYSE					(WM_USER + 105)
// #define WM_CLOSE_POWER_ANALYSE					(WM_USER + 106)
// #define WM_SHOW_ANALYSE_STATE					(WM_USER + 1009)
// #define WM_SHOW_RECORD_TIME						(WM_USER + 9010)

//MrOnlineThread
#define WM_BEGINWRITE							(WM_USER + 1001)

////校准时的系统时间消息(UIWndAdjustGrid)
#define WM_UPDATE_ADJUSTSPY_DATA				(WM_USER + 1002)

//UIWndRadioBox
#define WM_WND_RADIOBOX_CLICK					(WM_USER + 1003)

//录波文件的操作
#define WM_RTFILE_SELECTCURR					(WM_USER + 1004)
#define WM_RTFILE_SELECTALL						(WM_USER + 1005)
#define WM_RTFILE_DELETESEL						(WM_USER + 1006)
#define WM_RTFILE_MOVETO						(WM_USER + 1007)
#define WM_RTFILE_COPYTO						(WM_USER + 1008)

// 系统操作消息(RECORDGlobalDefine)
#define WM_FINISH_RECORD						(WM_USER + 1010)
#define WM_START_RECORD							(WM_USER + 1011)	
#define WM_DRAW_VARIABLESEL						(WM_USER + 1012)
#define WM_SAVERECORDFILE						(WM_USER + 1013)
#define WM_READRECORDFILE						(WM_USER + 1014)
#define WM_SETVARIABLEAXISRANGE					(WM_USER + 1015)
#define WM_EXITINSTANCE							(WM_USER + 1016)
#define WM_SETSEDIT_FINISHED					(WM_USER + 1017)//定值信息修改

//RECORDTestCalThread
#define WM_BEGIN_CALVALUES						(WM_USER + 1018)

//CUIWndVariableSpyGrid 
#define WM_UPDATE_VARIABLESPY_CONFIG			(WM_USER + 1019)
#define WM_UPDATE_VARIABLESPY_DATA				(WM_USER + 1020)

//CUIWndAttrSpyGrid
#define WM_UPDATEATTRSPY						(WM_USER + 1021)
#define WM_UPDATE_ATTRSPY_DATA					(WM_USER + 1022)

//CUIWndPolorAxis && UIWndVectorGrid
#define WM_UPDATE_VECTOR_SHOW					(WM_USER + 1023)

//CUIWndPolorAxis
#define WM_UPDATE_VECTOR_REDRAW					(WM_USER + 1024)

//CUIWndVectorGrid
#define WM_UPDATE_VECTOR_DATA					(WM_USER + 1025)

//CMrOnlineServerThread
#define WM_SHOW_ONLINERECORDINFOR				(WM_USER + 1026)

//CUIWndAttrDraw
#define WM_DRAW_ATTRSEL							(WM_USER + 1027)

//录波参数监视时钟消息
#define WM_RECORD_PARASPY                       (WM_USER + 1028)

//波形分析界面，当前选中用于分析的波形数据改变
#define WM_ANALYSE_RECORD_VIEWMAP_CHANGED       (WM_USER + 1029)

//在线录波数据存储完成
#define WM_ONLINERECORDEX_WRITEFINISHED         (WM_USER + 1030)

//试验功能选择界面
#define WM_SHOW_RECORDTEST_PAGE                 (WM_USER + 1031)

//在线录波数据拷贝过程消息
#define WM_ONLINERECORD_DATA_COPY               (WM_USER + 1032)

//CMrTcpProtocol
//创建服务器
#define WM_CREATE_SERVER						(WM_USER + 2002)
#define WM_CREATE_SERVER_FINISHED				(WM_USER + 2003)

//链接在线录波服务器端
#define WM_CONNECT_MRONLINE_SERVER				(WM_USER + 2004)
#define WM_CONNECT_MRONLINE_SERVER_FINISHED		(WM_USER + 2005)

//链接远程控制服务器端
#define WM_CONNECT_REMOTECTRL_SERVER			(WM_USER + 2006)
#define WM_CONNECT_REMOTECTRL_SERVER_FINISHED	(WM_USER + 2007)

//召唤RECORDTestInfor
#define WM_CALL_RECORDTESTINFOR					(WM_USER + 2008)
#define WM_CALL_RECORDTESTINFOR_FINISHED		(WM_USER + 2009)
//召唤启动信息
#define WM_CALL_STARTUPS						(WM_USER + 2010)
#define WM_CALL_STARTUPS_FINISHED				(WM_USER + 2011)
//召唤录波、监视数据索引
#define WM_CALL_RECORD_ATTR_INDEX				(WM_USER + 2012)
#define WM_CALL_RECORD_ATTR_INDEX_FINISHED		(WM_USER + 2013)
//召唤属性数据
#define WM_CALL_ATTR_DATAS						(WM_USER + 2014)
#define WM_CALL_ATTR_DATAS_FINISHED				(WM_USER + 2015)
//召唤录波数据
#define WM_CALL_RECORD_DATAS					(WM_USER + 2016)
#define WM_CALL_RECORD_DATAS_FINISHED			(WM_USER + 2017)
//发送数据
#define WM_SEND_DATA							(WM_USER + 2018)
//通讯异常消息
#define WM_MRSKT_ERROR							(WM_USER + 2019)
//召唤服务器状态
#define WM_CALL_SERVERSTATE						(WM_USER + 2020)
#define WM_CALL_SERVERSTATE_FINISHED			(WM_USER + 2021)
//召唤在下录波数据区名称
#define WM_CALL_DATAAREAINFO					(WM_USER + 2022)
#define WM_CALL_DATAAREAINFO_FINISHED			(WM_USER + 2023)
//打开选中的在线录波数据区
#define WM_CALL_OPENDATAAREA					(WM_USER + 2024)
#define WM_CALL_OPENDATAAREA_FINISHED			(WM_USER + 2025)

//RECORDTest选择
#define WM_RECORDTEST_SELECT_CHANGED			(WM_USER + 2026)

//系统信息窗口单独定义的消息，CUIWndSystemInfor
#define WM_UPDATE_WNDSYSTEMINFOR				(WM_USER + 2027)

//系统信息窗口单独定义的消息，CUIWndSystemInfor
#define WM_UPDATE_TRACE_SYSINFOR				(WM_USER + 2028)

#define WM_RECORD_HOLD_STATE_CHANGE				(WM_USER + 2029)

//RECORDBaseApp
#define WM_CREATE_UIB_GEN_CLIENT				(WM_USER + 2030)

//HDMrDevice
#define WM_FIFO_FULLFILL						(WM_USER + 2031)

//UIBGenShareMemDefine
#define WM_UIB_GENERATOR						(WM_USER + 2032)

//坐标系统窗口最大最小值的设置(UIGlobalDefine)
#define WM_AXISWND_SETMINMAXVALUE				(WM_USER + 2033)

//处理指令的通用消息(VmScript)
#define WM_PROCESS_INSTRUCT						(WM_USER + 2034)

//通道谐波监视消息     2010.7.3    LIJQ
#define WM_CH_HARM_ANALYSE                      (WM_USER + 2035)

//更新谐波监视表格显示值
#define WM_UPDATE_HARMGRIG_VALUE                (WM_USER + 2036)

//更新在线时间区域选择
#define WM_UPDATE_ONLINETIMEAREASEL             (WM_USER + 2037)

//恢复校准数据之后，更新校准界面
#define WM_UPDATE_RESETADJUST					(WM_USER + 2038)

//通过波形设置、触发通道等更新窗口显示的内容
#define WM_DRAWSET_CHANGED						(WM_USER + 2039)

//更新连续记录文件的相关信息
#define WM_UPDATE_ONLINE_DATAAREAINFO			(WM_USER + 2040)

//更新定值设置
#define WM_UPDATE_RESETSETS						(WM_USER + 2041)

//单次触发消息
#define WM_HOLD_BY_SINGLETRIG					(WM_USER + 2042)

//单次触发消息
#define WM_ONLINERECORD_WRITEFINISHED			(WM_USER + 2043)

//连续记录录波数据文件删除完成的消息
#define WM_RTFILE_DELETESEL_FINISH				(WM_USER + 2044)

//连续记录文件创建完成的消息
#define WM_CREATEONLINEDATAAREA_FINISH          (WM_USER + 2045)

//发变组短/开路试验坐标改变的操作消息
#define WM_UPDATE_GENTESTAXISCHANGE				(WM_USER + 2046)

//文件焦点切换消息
#define WM_UPDATE_WNDFILEINFOR					(WM_USER + 2047)

//响应发变组实验通道设置改变
#define WM_UPDATE_GENTESTCHANNALSET				(WM_USER + 2048)
/////////////////////////////////////////////////////////////////////////
//系统操作定义
//RECORDGlobalDefine
#define RECORD_SYSOPTR_ANALYSE_TIMERCURRSOR_MOVE    0X0001 //波形分析操作：移动时间光标
#define RECORD_SYSOPTR_OPEN_RECORDFILE				0X0002 //打开录波波形文件
#define RECORD_SYSOPTR_RTFILE_SELECTCURR            0X0004 //选中当前录波文件 
#define RECORD_SYSOPTR_RTFILE_SELECTALL             0X0005 //选中全部录波文件 
#define RECORD_SYSOPTR_RTFILE_DELETESEL             0X0006 //删除选中录波文件 
#define RECORD_SYSOPTR_RTFILE_MOVETO                0X0008 //移动选中文件 
#define RECORD_SYSOPTR_RTFILE_COPYTO                0X0009 //拷贝选中文件 
#define RECORD_SYSOPTR_FINISH_RECORD                0X000A //录波结束
#define RECORD_SYSOPTR_START_RECORD                 0X000B //录波开始
#define RECORD_SYSOPTR_DRAWSET_CHANGED				0X000C //通过波形设置、触发通道等更新窗口显示的内容
#define RECORD_SYSOPTR_RECORDMAP_CHANGED            0X000D //示波在线录波分析时。映射的区域改变
#define RECORD_SYSOPTR_ONLINERECORDEX_CHANGED       0X000E //在线录波数据改变
#define RECORD_SYSOPTR_ONLINERECORDEX_WRITEFINISHED 0X000F //在线录波数据存储完成

#define RECORD_SYSOPTR_SETSEDIT_FINISHED            0X0010 //定值修改系统消息
#define RECORD_SYSOPTR_ONLINE_RECORD_DATA_COPY      0X0011 //在线录波数据拷贝

#define RECORD_SYSOPTR_RECORD_HOLD					0X0012 //示波时保持/运行对应的系统操作

#define RECORD_SYSOPTR_USERADJUST_RESET				0X0013 //校准数据恢复
#define RECORD_SYSOPTR_SETS_RESET					0X0014 //定值设置恢复
#define RECORD_SYSOPTR_TRACE_SYSINFOR               0X0015 //显示系统消息
#define RECORD_SYSOPTR_SAVE_RECORDFILE              0X0016 //保存COMTRADE波形数据文件，正常信息显示在波形分析界面中

#define RECORD_SYSOPTR_ONLINERECORD_WRITE           0X0017 //在线录波数据写操作

#define RECORD_SYSOPTR_RTFILE_DELETESEL_FINISH      0X0018 //(在线)录波文件删除完成的操作
#define RECORD_SYSOPTR_RECORD_WRITE                 0X0017 //录波数据写操作
#define RECORD_SYSOPTR_CREATEONLINEDATAAREA_FINISH  0X0018 //创建连续记录数据文件成功

#define RECORD_SYSOPTR_GENTESTAXISCHANGE			0X0019 //发变组短/开路试验坐标改变的操作
#define RECORD_SYSOPTR_FILEFOCUSCHANGE				0X0020 //文件焦点切换改变的操作
#define RECORD_SYSOPTR_TRIGVARIABLECHANGE			0X0021 //触发通道改变，fdp add 2010.10.11
#define RECORD_SYSOPTR_TRIGELECTRICCHANGE			0X0022 //触发电平改变，fdp add 2010.10.11
#define RECORD_SYSOPTR_GENTESTCHANNALSET			0X0023 //发变组实验通道设置改变 qhy 2010.10.12

//系统操作相关的参数定义
#define SYSOPTRPARA_ONLINERECORDDATACOPY_BEGIN      0   //开始拷贝数据
#define SYSOPTRPARA_ONLINERECORDDATACOPY_COPY       1   //拷贝数据
#define SYSOPTRPARA_ONLINERECORDDATACOPY_FINISH     2   //拷贝完成
#define SYSOPTRPARA_ONLINERECORDDATACOPY_READDATA   3   //读文件

//恢复校准数据的状态
#define SYSOPTRPARA_RESETADJUST_BEGIN               0   //开始恢复
#define SYSOPTRPARA_RESETADJUST_FINISH              1   //恢复完成

//波形显示改变的操作相关参数
#define UPDATE_WAVESHOW_VARSHOW                     0   //处理来自通道显示的消息
#define UPDATE_WAVESHOW_TRIGVAR                     1   //处理来自触发通道设置的消息
#define UPDATE_WAVESHOW_TRIGMODE                    2   //处理来自触发方式设置的消息
#define UPDATE_WAVESHOW_POS_MIDLINE                 3   //处理来自自动调整、中心线显示的消息

//处理来自自动调整、中心线显示的消息的相关参数
#define DRAW_WAVEPOS								0	//表示调整位置
#define DRAW_WAVEMIDLINE_SHOW						1	//表示零线显示
#define DRAW_WAVEMIDLINE_GET						3	//获取零线状态

//RECORD_SYSOPTR_TRACE_SYSINFOR               0X0015 //显示系统消息
//系统操作相关的系统消息的种类
#define TRACE_SYSINFOR_NORMAL_MESSAGE               0  //普通消息
#define TRACE_SYSINFOR_ERROR_MESSAGE                1  //异常、错误消息


//在线录波数据写操作种类
#define RECORD_ONLINERECORD_WRITE_BEGIN            0 //在线录波数据写操作开始
#define RECORD_ONLINERECORD_WRITE_CH_FINISH        1 //在线录波一个通道数据写操作结束
#define RECORD_ONLINERECORD_WRITE_FINISH           2 //在线录波数据写操作结束

//发变组坐标设置参数类型
#define GENTESTAXISCHANGE_SATATORVARIABLE			0//改变定子电流（定子电压）
#define GENTESTAXISCHANGE_ROTORAXIS					1//改变转子坐标
#define GENTESTAXISCHANGE_STATORAXIS				2//改变定子坐标

//发变组实验通道设置改变参数类型
#define GENTESTCHANNALSET_ROTORVARIABLE				0//改变转子电流通道设置

//波形对比相关的消息
#define WM_RECORD_CMP_BEGIN        (WM_USER + 2100)
#define WM_RECORD_CMP_CLEAR        (WM_USER + 2101)

#endif // !defined(_RECORDSYSMSGDEF_H__)
