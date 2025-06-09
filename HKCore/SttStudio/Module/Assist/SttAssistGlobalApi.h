//SttAssistGlobalApi.h
#ifndef _SttAssistGlobalApi_H__
#define _SttAssistGlobalApi_H__

#include "SttAppWndAssistInterface.h"
#include <QWidget>

#define STT_AssistID_MUTEST                       "mutest"
#define STT_AssistID_ADMUTEST                     "admutest"

//�ܵĽӿں���
//����ȫ�ֶ���CSttAssistEngine���г�ʼ�����ͷ�
bool assist_create(const CString &strAssistID);
bool assist_release();

//��������
//��ʾ�������ֵĲ˵�
void assist_show_menu();

//���ò�������ͼ�갴ť���ڶ��󣬿��Բ��ã�ͨ��assist_find_widget�������롰Assist���ҵ����ְ�ť
void assist_set_entry_wnd(void *pEntryWnd);

//���������ڶ�����ʱ���ã�ʹ��ȫ�ֿ��ָ�����g_theTestCntrFrame
void assist_set_main_wnd(CSttWndAssistInterface *pSttMainWnd);

//��ʱ����
void assist_set_app(CSttAppAssistInterface *pApp);

//ִ�����ֽű���������չ�á�����������ƽ̨������£��˺�����������
bool assist_run_script(const CString &strScriptFile);
bool assist_close_script(const CString &strScriptFile);

//�¼���غ���
//������ʾ��һ��������ʾ�ڽ��棬������Դ˴��ڽ��в������������������ڿؼ�������ʾ��ʾ��Ϣ
//����ֻ���ڵ�ǰ��ʾ�Ĵ�����ȥ������صĴ���ID��
//QT�У�����ؼ����Ǵ�ui�ļ��д����ģ��Ƕ�̬�����ģ���Ҫָ���ؼ���ObjectName�����磺
/*
��һ�������ÿؼ���ObjectName
QSttAssistIecCbSelWidget::QSttAssistIecCbSelWidget(QWidget *parent)
	m_pGridIecCb->setObjectName("AstSttIecCbGrid");
�ڶ�����ʹ�ÿؼ�
void CSttAssistWzd_MuTest::assist_init()
	g_theAssistWndDynEffExecTool->ShowMsgEx("AstSttIecCbGrid", "�ڿ��ƿ�����ѡ������Ŀ��ƿ�", 0);
*/
void assist_wnd_show(const CString &strWndID, CSttWndAssistInterface *pWnd, bool bShow);
void assist_widget_show(const CString &strWndID, QWidget *pWidget, bool bShow);

//������Ϣ�����������ֽ��н�����Ϣ�Ĵ�����ʱ����
void assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas);

//���ݷ����ı䣬�������ֽ�����ص���Ϊ����ʱ���ã�ƽ̨����ʹ��
void assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue);

//Ӧ�ó����¼����������ֽ��д���
bool assist_event(const CString &strEventID, CExBaseObject *pSttParas);

//��Ϣ��ʾ���
//���������strWndID�����ҿؼ����ڣ��ڿؼ��ܱ���ʾ��ʾ��Ϣ����������ڣ�����ϵͳ���½���ʾ��ʾ��Ϣ
void assist_show_msg(const CString &strMsg, long nShowTimeLong);
void assist_show_msg_ex(const CString &strWndID, const CString &strMsg, long nShowTimeLong);
void assist_show_result(CDataGroup *pDatas); //����

#endif//_SttAssistGlobalApi_H__
