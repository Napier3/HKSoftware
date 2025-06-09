#ifndef _SttStyleSheetGlobalDefine_H__
#define _SttStyleSheetGlobalDefine_H__

//助手消息显示样式
#define STT_StyleSheet_AssistMsgTips                 "background-color:rgb(255,242,204); color:rgb(0,0,0); border-radius:6px; border:2px rgb(0,0,255);border-style:outset; "
//助手闪烁样式
#define STT_StyleSheet_AssistFlashStyle1             "background-color:rgb(192,192,192); color:rgb(0,0,0); border-radius:1px; border-style:outset;"
#define STT_StyleSheet_AssistFlashStyle2             "background-color:rgb(1, 196, 202); color:rgb(0,0,0); border-radius:10px; border:3px rgb(48,128,20);border-style:outset; "

//通用控件被按下时的样式表
#define STT_StyleSheet_Common_Ctrls_Pressed          "background-color:rgb(1, 196, 202); border-radius:10px; "

//表格类,在非使能状态下,颜色为灰色,使能状态下颜色为黑色
#define STT_StyleSheet_QTableWidgetItem_Enabled      "QTableWidget::item { ""color:rgb(0,0,0); ""} QTableWidget::item:!enabled{ ""color:rgb(127,127,127); ""}"

static const CString g_strQToolButtonStyleSheet = _T("QToolButton { ""background-color:rgb(192,192,192);"
													 "color:rgb(0,0,0); "//字体颜色
													 "border-radius:5px; "
													 "border-style:outset; "

													 "} QToolButton:!enabled{ "
													 "background-color:rgb(205,205,205);"
													 "color:rgb(127,127,127); "//字体颜色

													 "} QToolButton:focus{ "
													 "background-color:rgb(1, 196, 202);"
													 "color:rgb(0,0,0); "//字体颜色
													 "border-radius:10px; "
													 "border:3px rgb(48,128,20); "
													 "border-style:outset; ""}");

#endif // _SttStyleSheetGlobalDefine_H__
