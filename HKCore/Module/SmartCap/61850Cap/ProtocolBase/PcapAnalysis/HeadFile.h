

#define ABNORMAL_LOSTPOINT  0x01  //����
#define ABNORMAL_ERRORNUM   0x02//����/�ظ�
#define ABNORMAL_LOSTSMSYNC 0x03 //ʧȥͬ���ź�
#define ABNORMAL_MULTIMUNOSYNC 0x08
#define ABNORMAL_SMVFACTORCHANGE 0x09
#define ABNORMAL_SMVFLYPOINT 0x10011

#define GOOSE_SQREPEAT      0x04
#define GOOSE_SQNUMLOST     0x05
#define GOOSE_STNUMLOST     0x06//STNum����
#define GOOSE_BITCHANGESTNUMLOST     0x066
#define GOOSE_BITCHANGE     0x07
#define GOOSE_VITRUALBITCHANGE     0x0707//���λ
#define GOOSE_EQURESTART     0x10// װ������
#define GOOSE_SQNUMFIRSTVALUE     0x111// SQNum��ֵ����


#define GOOSE_TIMELIVEEQUAL0     0x11// timeAllowedtoLive =0;
#define GOOSE_TIMEDELAY			 0x12// GOOSE��ʱ
#define GOOSE_BREAK				 0x13// GOOSE�ж�

#define GOOSE_CLOCKUPSYNC        0x14// ʱ��δͬ��
#define GOOSE_CLOCKERROR		 0x15// ʱ�ӹ���
#define GOOSE_CLOCKABNORMAL		 0x16// ʱ���쳣

#define MMS_COMUNCATION		 0x100//�������ݶ�
#define MMS_COTPDATA		 0x50//COTP���ݶ�
#define MMS_CLIENTINIT       0x51//�ͻ��˳�ʼ��MMS����
#define MMS_SEVERRECV	     0x52//������ȷ�ϳ�ʼ��MMS
#define MMS_GETIEDSTRUCT     0x53//��ȡIED�������Խṹ��
#define MMS_RETURNIEDSTRUCT  0x54//����IED�������Խṹ��
#define MMS_UPLOADREPORT	 0x55//������ϴ�����
#define MMS_REQUESTOVERMMS   0x56//�������MMS����
#define MMS_COMFIRMOVERMMS	 0x57//ȷ�Ͻ���MMS����


#define MMS_READREPORT  	     0x58//��ȡ������ƿ�

#define MMS_READREPORT_SGCB			0x581 //GetSGCBValues Request ����ֵ���ֵ������
#define MMS_READREPORT_SG			0x582 //GetSGValues Request   ������ֵ��ֵ������
#define MMS_READREPORT_GETDATA		0x583 //GetDataValues Request;
#define MMS_READREPORT_RPURCB		0x584 //GetURCBValues Request;
#define MMS_READREPORT_RPBRCB		0x585 //GetBRCBValues Request;
#define MMS_READREPORT_GETDATASET   0x586 //GetDataSetValues Request;


#define MMS_READREPORTFINSHED		0x59//���ر�����ƿ�
#define MMS_READREPORTFINSHED_SGCB			0x591 //GetSGCBValues Response+ ����ֵ���ֵ������
#define MMS_READREPORTFINSHED_SG			0x592 //GetSGValues Response+   ������ֵ��ֵ������
#define MMS_READREPORTFINSHED_GETDATA		0x593 //GetDataValues Response+;
#define MMS_READREPORTFINSHED_RPURCB		0x594 //GetURCBValues Response+;
#define MMS_READREPORTFINSHED_RPBRCB		0x595 //GetBRCBValues Response+;
#define MMS_READREPORTFINSHED_GETDATASET	0x596 //GetDataSetValues Response+;

#define MMS_READREPORTFINSHED_ERROR			0x599 //GetDataSetValues Response-;

#define MMS_GETNAMEDATTRISTRUCT 0x60 //��ȡ�����������б����Խṹ��
#define MMS_RETNAMEDATTRISTRUCT 0x62 //���������������б����Խṹ��

#define MMS_GETIEDLIST			0x61//��ȡIED�����б�
#define MMS_RETIEDLIST			0x63//����IED�����б�

#define MMS_GETIEDLISTEX			0x611//��ȡ������IED�����б�
#define MMS_RETIEDLISTEX			0x631//���ط�����IED�����б�

#define MMS_GETVARIABLEACCESSATTRIBUTES    0x64 //��ȡIED�������Խṹ��
#define MMS_RETURNVARIABLEACCESSATTRIBUTES 0x65 //����IED�������Խṹ��

#define  MMS_WRITEREPORT        0x66 //д������ƿ����


#define  MMS_WRITEREPORT_ACTSG                  0x661 //SelectActiveSG ����
#define  MMS_WRITEREPORT_EDITSG                 0x662 //SelectEditSG ����
#define	 MMS_WRITEREPORT_SETSGVALUES			0x663 //SetSGValues ����
#define  MMS_WRITEREPORT_CONFIRMEDITSGVALUES    0x664 //ConfirmEditSGValues ����
#define  MMS_WRITEREPORT_SELVAL					0x665 //SelectWithValue Request
#define  MMS_WRITEREPORT_CONTRALOPER            0x666 //Operate Request
#define  MMS_WRITEREPORT_CANCEL                 0x667 //Cancel Request
#define  MMS_WRITEREPORT_SETDATA				0x668 //ȡ��ģ�ͣ�SetDataValues Request
#define  MMS_WRITEREPORT_RPURCB					0x669 //SetURCBDValues Request
#define  MMS_WRITEREPORT_RPBRCB					0x670 //SetURCBDValues Request

#define  MMS_WRITEREPORTFINSHED 0x67 //д������ƿ����

#define  MMS_WRITEREPORTFINSHED_ACTSG                  0x671 //SelectActiveSG Response+
#define  MMS_WRITEREPORTFINSHED_EDITSG                 0x672 //SelectEditSG  Response+
#define	 MMS_WRITEREPORTFINSHED_SETSGVALUES			   0x673 //SetSGValues Response+
#define  MMS_WRITEREPORTFINSHED_CONFIRMEDITSGVALUES    0x674 //ConfirmEditSGValues  Response+
#define  MMS_WRITEREPORTFINSHED_SELVAL				   0x675 //SelectWithValue  Response+
#define  MMS_WRITEREPORTFINSHED_CONTRALOPER            0x676 //Operate  Response+
#define  MMS_WRITEREPORTFINSHED_CANCEL                 0x677 //Cancel  Response+
#define  MMS_WRITEREPORTFINSHED_SETDATA				   0x678 //ȡ��ģ�ͣ�SetDataValues  Response+
#define  MMS_WRITEREPORTFINSHED_RPURCB				   0x679 //SetURCBDValues  Response+
#define  MMS_WRITEREPORTFINSHED_RPBRCB				   0x680 //SetURCBDValues  Response+

#define  MMS_WRITEREPORTFINSHED_ERROR				   0x6800 //�񶨲���  Operate  Response-

#define MMS_CLIENTREUESTREALSE 0x68 //�ͻ��������ͷ�����
#define MMS_CLIENCOMFIRMREALSE 0x69 //������ȷ���ͷ�����

#define  MMS_OPENFILE        0x700 //���ļ�����
#define  MMS_OPENFILEFINSHED 0x701 //���ļ����

#define  MMS_FILEDEL         0x702 //ɾ���ļ�����
#define  MMS_FILEDELFINSHED  0x703 //ɾ���ļ����

#define  MMS_FILEDIR         0x704 //�ļ�Ŀ¼����
#define  MMS_FILEDIRFINSHED  0x705 //�ļ����

#define  MMS_FILEREAD        0x706 //���ļ���ɲ��� 
#define  MMS_FILEREADFINSHED 0x707 //���ļ���� 

#define  MMS_FILECLOSE        0x708 //���ļ���ɲ��� 
#define  MMS_FILECLOSEFINSHED 0x709 //���ļ���� 

#define  MMS_FILEOBTAIN        0x710 //��ȡ�ļ����� 
#define  MMS_FILEOBTAINFINSHED 0x711 //��ȡ�ļ���� 



#define MMS_COMUNICATEERROR 0x72 //mms����ʧ��

#define MMS_COMUNICATEERROR_GETNAMELIST		0x721 //GetLogicalNodeDirectory Response-
#define MMS_COMUNICATEERROR_GETNAMEDVARLISTATTR 0x722 //GetNamedVariableListAttributes Response-
#define MMS_COMUNICATEERROR_SELACTIVESG 0x723 //SelectActiveSG Response-
#define MMS_COMUNICATEERROR_REPORTERROR 0x724 //Report(LastAppError) 
#define MMS_COMUNICATEERROR_GETSERVERFILEERROR 0x725 //GetServerDirectory(File) Response-



#define IEC_SMV91 1
#define IEC_SMV92 2
#define IEC_GOOSE 3
#define PRO_TCP 4
#define PRO_UDP 5
#define PRO_ARP 6
#define PRO_MMS 7
#define PRO_1588 8
#define PRO_Combine 9
#define PRO_OTHER -1

#define  WM_SEND_PACPPATH WM_USER+1160
#define ID_SPLITER_CONTENTUPDOWN 2012100101
#define ID_SPLITER_HEXLEFTRIGHT  2012100102
#define ID_SPLITER_MAINLEFTRIGHT 2012100103

