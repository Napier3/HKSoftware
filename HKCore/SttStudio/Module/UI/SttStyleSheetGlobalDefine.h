#ifndef _SttStyleSheetGlobalDefine_H__
#define _SttStyleSheetGlobalDefine_H__

//������Ϣ��ʾ��ʽ
#define STT_StyleSheet_AssistMsgTips                 "background-color:rgb(255,242,204); color:rgb(0,0,0); border-radius:6px; border:2px rgb(0,0,255);border-style:outset; "
//������˸��ʽ
#define STT_StyleSheet_AssistFlashStyle1             "background-color:rgb(192,192,192); color:rgb(0,0,0); border-radius:1px; border-style:outset;"
#define STT_StyleSheet_AssistFlashStyle2             "background-color:rgb(1, 196, 202); color:rgb(0,0,0); border-radius:10px; border:3px rgb(48,128,20);border-style:outset; "

//ͨ�ÿؼ�������ʱ����ʽ��
#define STT_StyleSheet_Common_Ctrls_Pressed          "background-color:rgb(1, 196, 202); border-radius:10px; "

//�����,�ڷ�ʹ��״̬��,��ɫΪ��ɫ,ʹ��״̬����ɫΪ��ɫ
#define STT_StyleSheet_QTableWidgetItem_Enabled      "QTableWidget::item { ""color:rgb(0,0,0); ""} QTableWidget::item:!enabled{ ""color:rgb(127,127,127); ""}"

static const CString g_strQToolButtonStyleSheet = _T("QToolButton { ""background-color:rgb(192,192,192);"
													 "color:rgb(0,0,0); "//������ɫ
													 "border-radius:5px; "
													 "border-style:outset; "

													 "} QToolButton:!enabled{ "
													 "background-color:rgb(205,205,205);"
													 "color:rgb(127,127,127); "//������ɫ

													 "} QToolButton:focus{ "
													 "background-color:rgb(1, 196, 202);"
													 "color:rgb(0,0,0); "//������ɫ
													 "border-radius:10px; "
													 "border:3px rgb(48,128,20); "
													 "border-style:outset; ""}");

#endif // _SttStyleSheetGlobalDefine_H__
