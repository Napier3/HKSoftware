

#define ABNORMAL_LOSTPOINT  0x01  //丢点
#define ABNORMAL_ERRORNUM   0x02//错序/重复
#define ABNORMAL_LOSTSMSYNC 0x03 //失去同步信号
#define ABNORMAL_MULTIMUNOSYNC 0x08
#define ABNORMAL_SMVFACTORCHANGE 0x09
#define ABNORMAL_SMVFLYPOINT 0x10011

#define GOOSE_SQREPEAT      0x04
#define GOOSE_SQNUMLOST     0x05
#define GOOSE_STNUMLOST     0x06//STNum错误
#define GOOSE_BITCHANGESTNUMLOST     0x066
#define GOOSE_BITCHANGE     0x07
#define GOOSE_VITRUALBITCHANGE     0x0707//虚变位
#define GOOSE_EQURESTART     0x10// 装置重启
#define GOOSE_SQNUMFIRSTVALUE     0x111// SQNum初值错误


#define GOOSE_TIMELIVEEQUAL0     0x11// timeAllowedtoLive =0;
#define GOOSE_TIMEDELAY			 0x12// GOOSE延时
#define GOOSE_BREAK				 0x13// GOOSE中断

#define GOOSE_CLOCKUPSYNC        0x14// 时钟未同步
#define GOOSE_CLOCKERROR		 0x15// 时钟故障
#define GOOSE_CLOCKABNORMAL		 0x16// 时钟异常

#define MMS_COMUNCATION		 0x100//交互数据段
#define MMS_COTPDATA		 0x50//COTP数据段
#define MMS_CLIENTINIT       0x51//客户端初始化MMS服务
#define MMS_SEVERRECV	     0x52//服务器确认初始化MMS
#define MMS_GETIEDSTRUCT     0x53//获取IED变量属性结构体
#define MMS_RETURNIEDSTRUCT  0x54//返回IED变量属性结构体
#define MMS_UPLOADREPORT	 0x55//服务端上传报告
#define MMS_REQUESTOVERMMS   0x56//请求结束MMS服务
#define MMS_COMFIRMOVERMMS	 0x57//确认结束MMS服务


#define MMS_READREPORT  	     0x58//获取报告控制块

#define MMS_READREPORT_SGCB			0x581 //GetSGCBValues Request 读定值组块值请求报文
#define MMS_READREPORT_SG			0x582 //GetSGValues Request   读定定值组值请求报文
#define MMS_READREPORT_GETDATA		0x583 //GetDataValues Request;
#define MMS_READREPORT_RPURCB		0x584 //GetURCBValues Request;
#define MMS_READREPORT_RPBRCB		0x585 //GetBRCBValues Request;
#define MMS_READREPORT_GETDATASET   0x586 //GetDataSetValues Request;


#define MMS_READREPORTFINSHED		0x59//返回报告控制块
#define MMS_READREPORTFINSHED_SGCB			0x591 //GetSGCBValues Response+ 读定值组块值请求报文
#define MMS_READREPORTFINSHED_SG			0x592 //GetSGValues Response+   读定定值组值请求报文
#define MMS_READREPORTFINSHED_GETDATA		0x593 //GetDataValues Response+;
#define MMS_READREPORTFINSHED_RPURCB		0x594 //GetURCBValues Response+;
#define MMS_READREPORTFINSHED_RPBRCB		0x595 //GetBRCBValues Response+;
#define MMS_READREPORTFINSHED_GETDATASET	0x596 //GetDataSetValues Response+;

#define MMS_READREPORTFINSHED_ERROR			0x599 //GetDataSetValues Response-;

#define MMS_GETNAMEDATTRISTRUCT 0x60 //获取已命名变量列表属性结构体
#define MMS_RETNAMEDATTRISTRUCT 0x62 //返回已命名变量列表属性结构体

#define MMS_GETIEDLIST			0x61//获取IED变量列表
#define MMS_RETIEDLIST			0x63//返回IED变量列表

#define MMS_GETIEDLISTEX			0x611//获取服务器IED变量列表
#define MMS_RETIEDLISTEX			0x631//返回服务器IED变量列表

#define MMS_GETVARIABLEACCESSATTRIBUTES    0x64 //获取IED变量属性结构体
#define MMS_RETURNVARIABLEACCESSATTRIBUTES 0x65 //返回IED变量属性结构体

#define  MMS_WRITEREPORT        0x66 //写报告控制块操作


#define  MMS_WRITEREPORT_ACTSG                  0x661 //SelectActiveSG 服务
#define  MMS_WRITEREPORT_EDITSG                 0x662 //SelectEditSG 服务
#define	 MMS_WRITEREPORT_SETSGVALUES			0x663 //SetSGValues 服务
#define  MMS_WRITEREPORT_CONFIRMEDITSGVALUES    0x664 //ConfirmEditSGValues 服务
#define  MMS_WRITEREPORT_SELVAL					0x665 //SelectWithValue Request
#define  MMS_WRITEREPORT_CONTRALOPER            0x666 //Operate Request
#define  MMS_WRITEREPORT_CANCEL                 0x667 //Cancel Request
#define  MMS_WRITEREPORT_SETDATA				0x668 //取代模型，SetDataValues Request
#define  MMS_WRITEREPORT_RPURCB					0x669 //SetURCBDValues Request
#define  MMS_WRITEREPORT_RPBRCB					0x670 //SetURCBDValues Request

#define  MMS_WRITEREPORTFINSHED 0x67 //写报告控制块完成

#define  MMS_WRITEREPORTFINSHED_ACTSG                  0x671 //SelectActiveSG Response+
#define  MMS_WRITEREPORTFINSHED_EDITSG                 0x672 //SelectEditSG  Response+
#define	 MMS_WRITEREPORTFINSHED_SETSGVALUES			   0x673 //SetSGValues Response+
#define  MMS_WRITEREPORTFINSHED_CONFIRMEDITSGVALUES    0x674 //ConfirmEditSGValues  Response+
#define  MMS_WRITEREPORTFINSHED_SELVAL				   0x675 //SelectWithValue  Response+
#define  MMS_WRITEREPORTFINSHED_CONTRALOPER            0x676 //Operate  Response+
#define  MMS_WRITEREPORTFINSHED_CANCEL                 0x677 //Cancel  Response+
#define  MMS_WRITEREPORTFINSHED_SETDATA				   0x678 //取代模型，SetDataValues  Response+
#define  MMS_WRITEREPORTFINSHED_RPURCB				   0x679 //SetURCBDValues  Response+
#define  MMS_WRITEREPORTFINSHED_RPBRCB				   0x680 //SetURCBDValues  Response+

#define  MMS_WRITEREPORTFINSHED_ERROR				   0x6800 //否定操作  Operate  Response-

#define MMS_CLIENTREUESTREALSE 0x68 //客户端请求释放连接
#define MMS_CLIENCOMFIRMREALSE 0x69 //服务器确定释放连接

#define  MMS_OPENFILE        0x700 //打开文件操作
#define  MMS_OPENFILEFINSHED 0x701 //打开文件完成

#define  MMS_FILEDEL         0x702 //删除文件操作
#define  MMS_FILEDELFINSHED  0x703 //删除文件完成

#define  MMS_FILEDIR         0x704 //文件目录操作
#define  MMS_FILEDIRFINSHED  0x705 //文件完成

#define  MMS_FILEREAD        0x706 //读文件完成操作 
#define  MMS_FILEREADFINSHED 0x707 //读文件完成 

#define  MMS_FILECLOSE        0x708 //读文件完成操作 
#define  MMS_FILECLOSEFINSHED 0x709 //读文件完成 

#define  MMS_FILEOBTAIN        0x710 //获取文件操作 
#define  MMS_FILEOBTAINFINSHED 0x711 //获取文件完成 



#define MMS_COMUNICATEERROR 0x72 //mms交互失败

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

