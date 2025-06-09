// RECORDSysMsgDef.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RECORDSYSMSGDEF_H__)
#define _RECORDSYSMSGDEF_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ϵͳ��Ϣ����

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

//Զ�����߷�����
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

////У׼ʱ��ϵͳʱ����Ϣ(UIWndAdjustGrid)
#define WM_UPDATE_ADJUSTSPY_DATA				(WM_USER + 1002)

//UIWndRadioBox
#define WM_WND_RADIOBOX_CLICK					(WM_USER + 1003)

//¼���ļ��Ĳ���
#define WM_RTFILE_SELECTCURR					(WM_USER + 1004)
#define WM_RTFILE_SELECTALL						(WM_USER + 1005)
#define WM_RTFILE_DELETESEL						(WM_USER + 1006)
#define WM_RTFILE_MOVETO						(WM_USER + 1007)
#define WM_RTFILE_COPYTO						(WM_USER + 1008)

// ϵͳ������Ϣ(RECORDGlobalDefine)
#define WM_FINISH_RECORD						(WM_USER + 1010)
#define WM_START_RECORD							(WM_USER + 1011)	
#define WM_DRAW_VARIABLESEL						(WM_USER + 1012)
#define WM_SAVERECORDFILE						(WM_USER + 1013)
#define WM_READRECORDFILE						(WM_USER + 1014)
#define WM_SETVARIABLEAXISRANGE					(WM_USER + 1015)
#define WM_EXITINSTANCE							(WM_USER + 1016)
#define WM_SETSEDIT_FINISHED					(WM_USER + 1017)//��ֵ��Ϣ�޸�

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

//¼����������ʱ����Ϣ
#define WM_RECORD_PARASPY                       (WM_USER + 1028)

//���η������棬��ǰѡ�����ڷ����Ĳ������ݸı�
#define WM_ANALYSE_RECORD_VIEWMAP_CHANGED       (WM_USER + 1029)

//����¼�����ݴ洢���
#define WM_ONLINERECORDEX_WRITEFINISHED         (WM_USER + 1030)

//���鹦��ѡ�����
#define WM_SHOW_RECORDTEST_PAGE                 (WM_USER + 1031)

//����¼�����ݿ���������Ϣ
#define WM_ONLINERECORD_DATA_COPY               (WM_USER + 1032)

//CMrTcpProtocol
//����������
#define WM_CREATE_SERVER						(WM_USER + 2002)
#define WM_CREATE_SERVER_FINISHED				(WM_USER + 2003)

//��������¼����������
#define WM_CONNECT_MRONLINE_SERVER				(WM_USER + 2004)
#define WM_CONNECT_MRONLINE_SERVER_FINISHED		(WM_USER + 2005)

//����Զ�̿��Ʒ�������
#define WM_CONNECT_REMOTECTRL_SERVER			(WM_USER + 2006)
#define WM_CONNECT_REMOTECTRL_SERVER_FINISHED	(WM_USER + 2007)

//�ٻ�RECORDTestInfor
#define WM_CALL_RECORDTESTINFOR					(WM_USER + 2008)
#define WM_CALL_RECORDTESTINFOR_FINISHED		(WM_USER + 2009)
//�ٻ�������Ϣ
#define WM_CALL_STARTUPS						(WM_USER + 2010)
#define WM_CALL_STARTUPS_FINISHED				(WM_USER + 2011)
//�ٻ�¼����������������
#define WM_CALL_RECORD_ATTR_INDEX				(WM_USER + 2012)
#define WM_CALL_RECORD_ATTR_INDEX_FINISHED		(WM_USER + 2013)
//�ٻ���������
#define WM_CALL_ATTR_DATAS						(WM_USER + 2014)
#define WM_CALL_ATTR_DATAS_FINISHED				(WM_USER + 2015)
//�ٻ�¼������
#define WM_CALL_RECORD_DATAS					(WM_USER + 2016)
#define WM_CALL_RECORD_DATAS_FINISHED			(WM_USER + 2017)
//��������
#define WM_SEND_DATA							(WM_USER + 2018)
//ͨѶ�쳣��Ϣ
#define WM_MRSKT_ERROR							(WM_USER + 2019)
//�ٻ�������״̬
#define WM_CALL_SERVERSTATE						(WM_USER + 2020)
#define WM_CALL_SERVERSTATE_FINISHED			(WM_USER + 2021)
//�ٻ�����¼������������
#define WM_CALL_DATAAREAINFO					(WM_USER + 2022)
#define WM_CALL_DATAAREAINFO_FINISHED			(WM_USER + 2023)
//��ѡ�е�����¼��������
#define WM_CALL_OPENDATAAREA					(WM_USER + 2024)
#define WM_CALL_OPENDATAAREA_FINISHED			(WM_USER + 2025)

//RECORDTestѡ��
#define WM_RECORDTEST_SELECT_CHANGED			(WM_USER + 2026)

//ϵͳ��Ϣ���ڵ����������Ϣ��CUIWndSystemInfor
#define WM_UPDATE_WNDSYSTEMINFOR				(WM_USER + 2027)

//ϵͳ��Ϣ���ڵ����������Ϣ��CUIWndSystemInfor
#define WM_UPDATE_TRACE_SYSINFOR				(WM_USER + 2028)

#define WM_RECORD_HOLD_STATE_CHANGE				(WM_USER + 2029)

//RECORDBaseApp
#define WM_CREATE_UIB_GEN_CLIENT				(WM_USER + 2030)

//HDMrDevice
#define WM_FIFO_FULLFILL						(WM_USER + 2031)

//UIBGenShareMemDefine
#define WM_UIB_GENERATOR						(WM_USER + 2032)

//����ϵͳ���������Сֵ������(UIGlobalDefine)
#define WM_AXISWND_SETMINMAXVALUE				(WM_USER + 2033)

//����ָ���ͨ����Ϣ(VmScript)
#define WM_PROCESS_INSTRUCT						(WM_USER + 2034)

//ͨ��г��������Ϣ     2010.7.3    LIJQ
#define WM_CH_HARM_ANALYSE                      (WM_USER + 2035)

//����г�����ӱ����ʾֵ
#define WM_UPDATE_HARMGRIG_VALUE                (WM_USER + 2036)

//��������ʱ������ѡ��
#define WM_UPDATE_ONLINETIMEAREASEL             (WM_USER + 2037)

//�ָ�У׼����֮�󣬸���У׼����
#define WM_UPDATE_RESETADJUST					(WM_USER + 2038)

//ͨ���������á�����ͨ���ȸ��´�����ʾ������
#define WM_DRAWSET_CHANGED						(WM_USER + 2039)

//����������¼�ļ��������Ϣ
#define WM_UPDATE_ONLINE_DATAAREAINFO			(WM_USER + 2040)

//���¶�ֵ����
#define WM_UPDATE_RESETSETS						(WM_USER + 2041)

//���δ�����Ϣ
#define WM_HOLD_BY_SINGLETRIG					(WM_USER + 2042)

//���δ�����Ϣ
#define WM_ONLINERECORD_WRITEFINISHED			(WM_USER + 2043)

//������¼¼�������ļ�ɾ����ɵ���Ϣ
#define WM_RTFILE_DELETESEL_FINISH				(WM_USER + 2044)

//������¼�ļ�������ɵ���Ϣ
#define WM_CREATEONLINEDATAAREA_FINISH          (WM_USER + 2045)

//�������/��·��������ı�Ĳ�����Ϣ
#define WM_UPDATE_GENTESTAXISCHANGE				(WM_USER + 2046)

//�ļ������л���Ϣ
#define WM_UPDATE_WNDFILEINFOR					(WM_USER + 2047)

//��Ӧ������ʵ��ͨ�����øı�
#define WM_UPDATE_GENTESTCHANNALSET				(WM_USER + 2048)
/////////////////////////////////////////////////////////////////////////
//ϵͳ��������
//RECORDGlobalDefine
#define RECORD_SYSOPTR_ANALYSE_TIMERCURRSOR_MOVE    0X0001 //���η����������ƶ�ʱ����
#define RECORD_SYSOPTR_OPEN_RECORDFILE				0X0002 //��¼�������ļ�
#define RECORD_SYSOPTR_RTFILE_SELECTCURR            0X0004 //ѡ�е�ǰ¼���ļ� 
#define RECORD_SYSOPTR_RTFILE_SELECTALL             0X0005 //ѡ��ȫ��¼���ļ� 
#define RECORD_SYSOPTR_RTFILE_DELETESEL             0X0006 //ɾ��ѡ��¼���ļ� 
#define RECORD_SYSOPTR_RTFILE_MOVETO                0X0008 //�ƶ�ѡ���ļ� 
#define RECORD_SYSOPTR_RTFILE_COPYTO                0X0009 //����ѡ���ļ� 
#define RECORD_SYSOPTR_FINISH_RECORD                0X000A //¼������
#define RECORD_SYSOPTR_START_RECORD                 0X000B //¼����ʼ
#define RECORD_SYSOPTR_DRAWSET_CHANGED				0X000C //ͨ���������á�����ͨ���ȸ��´�����ʾ������
#define RECORD_SYSOPTR_RECORDMAP_CHANGED            0X000D //ʾ������¼������ʱ��ӳ�������ı�
#define RECORD_SYSOPTR_ONLINERECORDEX_CHANGED       0X000E //����¼�����ݸı�
#define RECORD_SYSOPTR_ONLINERECORDEX_WRITEFINISHED 0X000F //����¼�����ݴ洢���

#define RECORD_SYSOPTR_SETSEDIT_FINISHED            0X0010 //��ֵ�޸�ϵͳ��Ϣ
#define RECORD_SYSOPTR_ONLINE_RECORD_DATA_COPY      0X0011 //����¼�����ݿ���

#define RECORD_SYSOPTR_RECORD_HOLD					0X0012 //ʾ��ʱ����/���ж�Ӧ��ϵͳ����

#define RECORD_SYSOPTR_USERADJUST_RESET				0X0013 //У׼���ݻָ�
#define RECORD_SYSOPTR_SETS_RESET					0X0014 //��ֵ���ûָ�
#define RECORD_SYSOPTR_TRACE_SYSINFOR               0X0015 //��ʾϵͳ��Ϣ
#define RECORD_SYSOPTR_SAVE_RECORDFILE              0X0016 //����COMTRADE���������ļ���������Ϣ��ʾ�ڲ��η���������

#define RECORD_SYSOPTR_ONLINERECORD_WRITE           0X0017 //����¼������д����

#define RECORD_SYSOPTR_RTFILE_DELETESEL_FINISH      0X0018 //(����)¼���ļ�ɾ����ɵĲ���
#define RECORD_SYSOPTR_RECORD_WRITE                 0X0017 //¼������д����
#define RECORD_SYSOPTR_CREATEONLINEDATAAREA_FINISH  0X0018 //����������¼�����ļ��ɹ�

#define RECORD_SYSOPTR_GENTESTAXISCHANGE			0X0019 //�������/��·��������ı�Ĳ���
#define RECORD_SYSOPTR_FILEFOCUSCHANGE				0X0020 //�ļ������л��ı�Ĳ���
#define RECORD_SYSOPTR_TRIGVARIABLECHANGE			0X0021 //����ͨ���ı䣬fdp add 2010.10.11
#define RECORD_SYSOPTR_TRIGELECTRICCHANGE			0X0022 //������ƽ�ı䣬fdp add 2010.10.11
#define RECORD_SYSOPTR_GENTESTCHANNALSET			0X0023 //������ʵ��ͨ�����øı� qhy 2010.10.12

//ϵͳ������صĲ�������
#define SYSOPTRPARA_ONLINERECORDDATACOPY_BEGIN      0   //��ʼ��������
#define SYSOPTRPARA_ONLINERECORDDATACOPY_COPY       1   //��������
#define SYSOPTRPARA_ONLINERECORDDATACOPY_FINISH     2   //�������
#define SYSOPTRPARA_ONLINERECORDDATACOPY_READDATA   3   //���ļ�

//�ָ�У׼���ݵ�״̬
#define SYSOPTRPARA_RESETADJUST_BEGIN               0   //��ʼ�ָ�
#define SYSOPTRPARA_RESETADJUST_FINISH              1   //�ָ����

//������ʾ�ı�Ĳ�����ز���
#define UPDATE_WAVESHOW_VARSHOW                     0   //��������ͨ����ʾ����Ϣ
#define UPDATE_WAVESHOW_TRIGVAR                     1   //�������Դ���ͨ�����õ���Ϣ
#define UPDATE_WAVESHOW_TRIGMODE                    2   //�������Դ�����ʽ���õ���Ϣ
#define UPDATE_WAVESHOW_POS_MIDLINE                 3   //���������Զ���������������ʾ����Ϣ

//���������Զ���������������ʾ����Ϣ����ز���
#define DRAW_WAVEPOS								0	//��ʾ����λ��
#define DRAW_WAVEMIDLINE_SHOW						1	//��ʾ������ʾ
#define DRAW_WAVEMIDLINE_GET						3	//��ȡ����״̬

//RECORD_SYSOPTR_TRACE_SYSINFOR               0X0015 //��ʾϵͳ��Ϣ
//ϵͳ������ص�ϵͳ��Ϣ������
#define TRACE_SYSINFOR_NORMAL_MESSAGE               0  //��ͨ��Ϣ
#define TRACE_SYSINFOR_ERROR_MESSAGE                1  //�쳣��������Ϣ


//����¼������д��������
#define RECORD_ONLINERECORD_WRITE_BEGIN            0 //����¼������д������ʼ
#define RECORD_ONLINERECORD_WRITE_CH_FINISH        1 //����¼��һ��ͨ������д��������
#define RECORD_ONLINERECORD_WRITE_FINISH           2 //����¼������д��������

//�������������ò�������
#define GENTESTAXISCHANGE_SATATORVARIABLE			0//�ı䶨�ӵ��������ӵ�ѹ��
#define GENTESTAXISCHANGE_ROTORAXIS					1//�ı�ת������
#define GENTESTAXISCHANGE_STATORAXIS				2//�ı䶨������

//������ʵ��ͨ�����øı��������
#define GENTESTCHANNALSET_ROTORVARIABLE				0//�ı�ת�ӵ���ͨ������

//���ζԱ���ص���Ϣ
#define WM_RECORD_CMP_BEGIN        (WM_USER + 2100)
#define WM_RECORD_CMP_CLEAR        (WM_USER + 2101)

#endif // !defined(_RECORDSYSMSGDEF_H__)
