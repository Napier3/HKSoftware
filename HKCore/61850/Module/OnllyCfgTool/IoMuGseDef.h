#ifndef IO_MU_GSE_DEF_H
#define IO_MU_GSE_DEF_H

/*-----------------------------------------------------------------------*/
/* Correspondence between drive number and physical drive                */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define DRV_NAND         0
#define DRV_SDRAM        1
#define DRV_SPIFLASH     2

//设备型号定义
//UNKNOWN
#define DEV_TYPE_UNKNOWN     0x00000000
//F66D-25M--最早的版本 20110624前
#define DEV_TYPE_F66_00      0xF6600000
//F66D-25M=20120624  ~  50M=20110801 ~  100M=20111130
#define DEV_TYPE_F66D_00     0x0F660D00
//F66D-25M
#define DEV_TYPE_F66D_25     0x0f66d019
//F66D-50M
#define DEV_TYPE_F66D_50     0x0f66d032
//F66D-100M
#define DEV_TYPE_F66D_100    0x0f66d064
//F66D-100M-X数据线交叉
#define DEV_TYPE_F66D_100X   0x0f66d164
//F66DS-100M-6光口
#define DEV_TYPE_F66DS_100   0x0f66d964


//F0610-100M-
#define DEV_TYPE_F0610_100   0x0f6a0064
//F0610a-100M-
#define DEV_TYPE_F0610A_100  0x0f6aa064
//F0810-100M-
#define DEV_TYPE_F0810_100   0x0f8a0064
//F0810a-100M-
#define DEV_TYPE_F0810A_100  0x0f8aa064
//F1010-100M-
#define DEV_TYPE_F1010_100   0x0faa0064
//F1010a-100M-
#define DEV_TYPE_F1010A_100  0x0faaa064
//F1210-100M-
#define DEV_TYPE_F1210_100   0x0fca0064
//F1210A-100M
#define DEV_TYPE_F1210A_100  0x0fcaa064
//F1210A-100M-1改进型号
#define DEV_TYPE_F1210A1_100 0x0fcaa164

//F1210B-100M
#define DEV_TYPE_F1210B_100  0x0fcab064

//PS821-100M
#define DEV_TYPE_PS821_100   0x0f23b164

#define DEV_TYPE(lan,ft3,type,subtype,fre)   (0x0f000000+((lan)<<20)+((ft3)<<16)+((type)<<12)+((subtype)<<8)+(fre))

//======================================升级相关====================================
//IO821 升级文件名
#define FILENAME_IO821_UPG 	"IO821.BIN"
//FPGA 升级文件名
#define FILENAME_FPGA_UPG 	"FPGA821.BIN"
//应用程序相关信息
#define FILENAME_APP_INFO 	"ApInfoTb.BIN"

//io821文件最小长度  256KB
#define MIN_IO821_FILE_SIZE (256*1024)

//PC IO821 协助版本号
/*
1、修改Goose out.t 取值方式，下载配置后第一次goose out使用当前系统时间，之后取变位时时间
2、新增Gse测试、Mu幅值测试功能
3、GseOut测试增加参数Para4/para5
4、光数字测试，下载通道UI时，指明是否相角连续 ONLLYDEV_TSTMUCFG
*/
#define PC_IO821_SHARE_VER  4

//************************机器故障定义(machine error state)***************************
//Nand Flash not found
#define MES_NF_NOT_FOUND	0x1
//Nand Flash 初始化失败
#define MES_NF_INIT		 	0x2
//Nand Flash 文件系统建立失败
#define MES_NF_FS		 	0x4
//DM9000 初始化失败
#define MES_DM9000_INIT	 	0x8
//Loader CRC32自校验失败
#define MES_SELF_CHECKSUM 	0x10
//APP CRC32自校验失败
#define MES_APP_CHECKSUM 	0x20
//FPGA程序不存在
#define MES_FPGA_MISFILE 	0x40
//FPGA程序加载失败
#define MES_FPGA_LOADFAIL 	0x80
//DataFlash 文件系统建立失败
#define MES_DF_FS		 	0x100
//缺少板件配置信息
#define MES_CMP_CFG_MIS     0x200
//板件配置信息 读取失败
#define MES_CMP_CFG_RDFAIL  0x400
//板件配置信息 没有足够的内存载入
#define MES_CMP_CFG_NOBUFF  0x800
//板件配置信息 crc校验错误
#define MES_CMP_CFG_CRCERR  0x100000
//不支持的FPGA频率
#define MES_FPGA_FRE_ERR    0x200000

//DM9000的索引
#define MES_DM9000_0     	0x1000
//DM9000的索引
#define MES_DM9000_1     	0x2000
//DM9000的索引
#define MES_DM9000_2     	0x4000
//DM9000的索引
#define MES_DM9000_3     	0x8000


//*********************** bin文件自校验CRC32相关 ***********************
//CRC长度为4
#define BIN_CRC32_SIZE	(4)
//CRC填充位置(相对于文件头)
#define BIN_CRC32_POS	(0x100)
//软件功能信息起始
#define ADDR_BIN_SWFINFO (BIN_CRC32_POS + BIN_CRC32_SIZE)
//CRC校验范围，文件起始 ~ 结束(代码使用时为程序起始，长度为BIN_CRC32_RANGE)
#define BIN_CRC32_RANGE	(0x40000)


//配置文件加载选择
//正常的配置文件
#define CFG_FILE_NORMAL		0	
//测试的配置文件
#define CFG_FILE_TEST		1	

//**********************标记定义*********************************
#define TAG_START					0x80
//MU
#define TAG_MU_VERSION				0x80

#define TAG_MU_SAMPLERATE			0x90
#define TAG_MU_MODE1588				0x91
#define TAG_MU_TXRATEFT3			0x92
//异步FT3校验停止位设置：低16位=校验方式，高16位=停止位个数（放大10倍）
#define TAG_MU_TXFT3CFG 			0x93
//采样异步
#define TAG_MU_SAMPLE_ASYNC   		0x94
#define TAG_MU_SAMPCNT_RESET_VAL    0x95
#define TAG_MU_CFGNUM				0x9F

#define TAG_MU_CFG_START			0xA0
#define TAG_MU_CFG_USED				0xA1
#define TAG_MU_CFG_LANNO			0xA2
#define TAG_MU_CFG_SAMPLETYPE		0xA3
#define TAG_MU_CFG_ASDUNUM			0xA4
#define TAG_MU_CFG_ASDULEN			0xA5
#define TAG_MU_CFG_CURRENTA			0xA6
#define TAG_MU_CFG_CURRENTSCP		0xA7
#define TAG_MU_CFG_CURRENTNEUT		0xA8
#define TAG_MU_CFG_VOLTA			0xA9
#define TAG_MU_CFG_CTBITRATE		0xAA
#define TAG_MU_CFG_PTBITRATE		0xAB
#define TAG_MU_CFG_PACKETDATA		0xAC
#define TAG_MU_CFG_FILLSET_NUM		0xAD
//测试控制
//测试类型
#define TAG_MU_CFG_TEST_TYPE		0xAE
//普通测试时，代表延迟帧数；Gse触发时，bit31=1代表逻辑与，其他位代表开入ABCDRabcdr
#define TAG_MU_CFG_TEST_START		0xAF
#define TAG_MU_CFG_TEST_LIMIT		0xB0
#define TAG_MU_CFG_TEST_COUNT		0xB1
#define TAG_MU_CFG_TEST_SETNUM		0xB2
#define TAG_MU_CFG_TEST_PARA1		0xB3
#define TAG_MU_CFG_TEST_PARA2		0xB4
#define TAG_MU_CFG_TEST_PARA3		0xB5
//0：帧计数启动；1：Goose In触发
#define TAG_MU_CFG_TEST_ACTTYPE		0xB6
//通道延时
#define TAG_MU_CFG_CHN_DELAY		0xB7
//MU同步标志自动设置
#define TAG_MU_SYNC_AUTOSET 		0xB8
//MU同步标志 长度(16bit)+位置(16bit)
#define TAG_MU_SYNC_CTRL    		0xB9


#define TAG_MU_CFG_FILLSET_START	0xC0
#define TAG_MU_CFG_FILLSET_TYPE		0xC1
#define TAG_MU_CFG_FILLSET_CTRL		0xC2

//测试配置项
#define TAG_MU_CFG_TESTSET_START	0xC8
#define TAG_MU_CFG_TESTSET_VAL		0xC9
#define TAG_MU_CFG_TESTSET_CTRL		0xCA

//===============================================================
//GSE
#define TAG_GSE_VERSION				0x80

#define TAG_GSEIN_NUM				0x91
#define TAG_GSEOUT_NUM				0x92

#define TAG_GSEIN_CFG_START			0xA0
#define TAG_GSEIN_CFG_USED			0xA1
#define TAG_GSEIN_CFG_CHKMASK		0xA2
#define TAG_GSEIN_CFG_GOCBREF		0xA3
#define TAG_GSEIN_CFG_GOID			0xA4
#define TAG_GSEIN_CFG_DATASET		0xA5
#define TAG_GSEIN_CFG_CONFREV		0xA6
#define TAG_GSEIN_CFG_NDSCOM		0xA7
#define TAG_GSEIN_CFG_MACADDR		0xA8
#define TAG_GSEIN_CFG_APPID			0xA9
#define TAG_GSEIN_CFG_T0			0xAA
#define TAG_GSEIN_CFG_T1			0xAB
#define TAG_GSEIN_CFG_T2			0xAC
#define TAG_GSEIN_CFG_T3			0xAD
#define TAG_GSEIN_CFG_TMULT			0xAE
#define TAG_GSEIN_CFG_TEST			0xAF
#define TAG_GSEIN_CFG_MAP_BINNUM	0xB0

#define TAG_GSEIN_CFG_MAP_START		0xC0
#define TAG_GSEIN_CFG_MAP_BINORDER	0xC1
#define TAG_GSEIN_CFG_MAP_BINTYPE	0xC2
#define TAG_GSEIN_CFG_MAP_MAPTYPE	0xC3
//--------GOOSE OUT
#define TAG_GSEOUT_CFG_START		0xD0
#define TAG_GSEOUT_CFG_USED			0xD1
#define TAG_GSEOUT_CFG_LANNO		0xD2
#define TAG_GSEOUT_CFG_T0			0xD3
#define TAG_GSEOUT_CFG_T1			0xD4
#define TAG_GSEOUT_CFG_T2			0xD5
#define TAG_GSEOUT_CFG_T3			0xD6
#define TAG_GSEOUT_CFG_TMULT		0xD7
#define TAG_GSEOUT_CFG_PACKETDATA	0xD8
#define TAG_GSEOUT_CFG_MAP_BINNUM	0xD9

//设定 TTL
#define FLAG_FIX_GO_TTL             1
//设定 时间品质
#define FLAG_FIX_GO_TIME_QUALITY    2
//固定字段标志，32位按位使用，参考 FLAG_FIX_GO_XXX 定义
#define TAG_GSEOUT_CFG_FIX_FLAGS	0xDA
#define TAG_GSEOUT_CFG_TIME_QUALITY	0xDB

//测试控制
//测试类型
#define TAG_GSEOUT_CFG_TEST_TYPE	0xC0
//普通测试时，代表延迟帧数；Gse触发时，bit31=1代表逻辑与，其他位代表开入ABCDRabcdr
#define TAG_GSEOUT_CFG_TEST_START	0xC1
#define TAG_GSEOUT_CFG_TEST_LIMIT	0xC2
#define TAG_GSEOUT_CFG_TEST_COUNT	0xC3
#define TAG_GSEOUT_CFG_TEST_SETNUM	0xC4
#define TAG_GSEOUT_CFG_TEST_PARA1	0xC5
#define TAG_GSEOUT_CFG_TEST_PARA2	0xC6
#define TAG_GSEOUT_CFG_TEST_PARA3	0xC7
#define TAG_GSEOUT_CFG_TEST_PARA4	0xC8
#define TAG_GSEOUT_CFG_TEST_PARA5	0xC9
//启动方式，参考TEST_ACTTYPE_xxx定义  0：帧计数启动；1：Goose In触发
#define TAG_GSEOUT_CFG_TEST_ACTTYPE	0xCC


#define TAG_GSEOUT_CFG_MAP_START	0xE0
#define TAG_GSEOUT_CFG_MAP_BINTYPE	0xE1
#define TAG_GSEOUT_CFG_MAP_MAPTYPE	0xE2
#define TAG_GSEOUT_CFG_MAP_FILLTYPE	0xE3

//测试配置项
#define TAG_GSEOUT_CFG_TESTSET_START    0xE9
#define TAG_GSEOUT_CFG_TESTSET_VAL		0xEA
#define TAG_GSEOUT_CFG_TESTSET_CTRL		0xEB

//*************数据来源编号定义(Data Source Type Def)************

//bit[30-31]=数据录入方式
//数据录入方式 掩码 11b<<30
#define DST_MASK_INPUT_TYPE (3<<30)
//手动录入数据 01b<<30
#define DST_IT_MANUAL		(01<<30)
//系统内置数据 00b<<30
#define DST_IT_SYSTEM		(00<<30)

//生成 手动 编码
#define MAKE_DST_MANUAL(x) (DST_IT_MANUAL+(x))
//生成 系统 编码
#define MAKE_DST_SYSTEM(x) (DST_IT_SYSTEM+(x))

//===============================================================
//手动数据定义
//A、bit[5-29]=保留
//B、bit[0-4]=分类型定义
//布尔						
#define DST_MAN_BOOLEAN		MAKE_DST_MANUAL(0)
//整形(32bit)
#define DST_MAN_INTEGER		MAKE_DST_MANUAL(1)
//浮点(32bit)
#define DST_MAN_FLOAT		MAKE_DST_MANUAL(2)
//位串
#define DST_MAN_BITSTRING	MAKE_DST_MANUAL(3)
//BTime
#define DST_MAN_BTIME		MAKE_DST_MANUAL(4)
//UTC
#define DST_MAN_UTC			MAKE_DST_MANUAL(5)

//===============================================================
//系统内置数据定义
//A、bit[27-29]=填充次序
//填充次序 掩码 111b<27
#define DST_MASK_FILL_ORDER	(7<<27)
//000b 填充1
#define DST_FO_1			(0<<27)
//001b 填充2
#define DST_FO_2			(1<<27)
//其他保留

//生成 系统 填充1 的编码
#define MAKE_DST_SYS_FO1(x)	MAKE_DST_SYSTEM((DST_FO_1+(x)))
//生成 系统 填充2 的编码
#define MAKE_DST_SYS_FO2(x)	MAKE_DST_SYSTEM((DST_FO_2+(x)))

//B、bit[26]:CRC相关
//掩码
#define DST_MASK_CRC_OTHER	(1<<26)

//-------------------------------------------------
//bit[26]=0 CRC相关数据
#define DST_CO_CRC			(0<<26)

//生成 系统 填充2 CRC 的编码
#define MAKE_DST_SYS_FO2_CO0(x)	MAKE_DST_SYS_FO2((DST_CO_CRC+(x)))

//a、bit[22-25]=CRC计算方式
//CRC计算方式 掩码 1111b<<22
#define DST_MASK_CRC_CALCTYPE	(0xF<<22)

//CRC计算方式：0000=CRC16,多项式=0x3D65
#define DST_CRC_CALC16_0X3D65	(0<<22)
//其他保留

//b、bit[11-21]:CRC计算起始位置,相对于报文头(0-2047)
// 111 1111 1111b<<11
#define DST_MASK_CRC_START		(0x7ff<<11)
//c、bit[0-10]:CRC计算数据长度(0-2047)
// 111 1111 1111b<<0
#define DST_MASK_CRC_LENGTH		(0x7ff<<0)

#define DST_TYPE_CRC(x)		()

//CRC的起始位置(0~起始)
#define CRC_START_POS(x) 	(((x) & DST_MASK_CRC_START)>>11)
//CRC的计算长度
#define CRC_CALC_LEN(x)		((x) & DST_MASK_CRC_LENGTH)

//CRC 数据
#define DST_SYS_CRC16_0X3D65(start,len)	MAKE_DST_SYS_FO2_CO0((DST_CRC_CALC16_0X3D65+((start&0x7ff)<<11)+((len&0x7ff)<<0)))


//-------------------------------------------------
//bit[26]=1 其他数据
#define DST_CO_OTHER			(1<<26)

//生成 系统 填充1 oth 的编码
#define MAKE_DST_SYS_FO1_CO1(x)	MAKE_DST_SYS_FO1((DST_CO_OTHER+(x)))

//a、bit[18-25]:保留 1111 1111b<<18
#define DST_MASK_CO_OTHER_RSW	(0xff<<18)
//b、bit[16-17]: 模拟通道相关
//掩码 11b<16
#define DST_MASK_ANALOG_OTHER	(3<<16)

//掩码[0-17] 11 1111 1111 1111 1111b<<0
#define DST_MASK_BIT0TO17		(0x3ffff<<0)

//-------------------------------------------------
//bit[16-17]=00 模拟通道相关
#define	DST_AO_ANALOG			(0<<16)

//生成 系统 填充1 CO1 analog 的编码
#define MAKE_DST_SYS_FO1_CO1_ANA(x)	MAKE_DST_SYS_FO1_CO1((DST_AO_ANALOG+(x)))


//a、bit[12-15]=计算模型
//掩码 1111b<<12
#define DST_MASK_CALC_MODEL		(0xf<<12)
//bit[12-15]=0000 相
#define DST_CM_PHASE			(0<<12)
//bit[12-15]=0001 零序
#define DST_CM_SEQ_ZERO			(1<<12)

//生成 系统 填充1 CO1 analog phase 的编码
#define MAKE_DST_SYS_FO1_CO1_ANA_PHA(x)	MAKE_DST_SYS_FO1_CO1_ANA((DST_CM_PHASE+(x)))

//生成 系统 填充1 CO1 analog seq_zero 的编码
#define MAKE_DST_SYS_FO1_CO1_ANA_SZ(x)	MAKE_DST_SYS_FO1_CO1_ANA((DST_CM_SEQ_ZERO+(x)))

//b、bit[10-11] 通道类型
//掩码 11b<<10
#define DST_MASK_CHN_TYPE		(3<<10)

//----------------------------------------------
//bit[10-11]=00 电压
#define DST_CT_U				(0<<10)
//a、bit[8-9]:保留
#define DST_MASK_CT_U_RSW		(3<<8)
//b、bit[0-7]:具体
#define DST_MASK_BIT0TO7		(0xff<<0)
//Ua							
#define	DST_SYS_UA				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+0)
#define	DST_SYS_UB				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+1)
#define	DST_SYS_UC				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+2)
#define	DST_SYS_UX				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+3)
#define	DST_SYS_UY				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+4)
#define	DST_SYS_UZ				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+5)
#define	DST_SYS_UU				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+6)
#define	DST_SYS_UV				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+7)
#define	DST_SYS_UW				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+8)
#define	DST_SYS_UR				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+9)
#define	DST_SYS_US				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+10)
#define	DST_SYS_UT				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_U+11)

//3U0=Ua+Ub+Uc					
#define	DST_SYS_UABC			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_U+0)
#define	DST_SYS_UXYZ			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_U+1)
#define	DST_SYS_UUVW			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_U+2)
#define	DST_SYS_URST			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_U+3)

//----------------------------------------------
//bit[10-11]=01 电流
#define DST_CT_I				(1<<10)

//a、bit[8-9]:保护测量
//掩码
#define DST_MASK_PROTECT_MEASURE
//bit[8-9]=00保护
#define DST_PM_PROTECT			(0<<8)
//bit[8-9]=01测量
#define DST_PM_MEASURE			(1<<8)

//b、bit[0-7]:具体

//Ia(保护)						
#define	DST_SYS_IA				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+0)
#define	DST_SYS_IB				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+1)
#define	DST_SYS_IC				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+2)
#define	DST_SYS_IX				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+3)
#define	DST_SYS_IY				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+4)
#define	DST_SYS_IZ				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+5)
#define	DST_SYS_IU				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+6)
#define	DST_SYS_IV				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+7)
#define	DST_SYS_IW				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+8)
#define	DST_SYS_IR				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+9)
#define	DST_SYS_IS				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+10)
#define	DST_SYS_IT				MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_PROTECT+11)

//3I0(保护)=Ia+Ib+Ic			
#define	DST_SYS_IABC			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_PROTECT+0)
#define	DST_SYS_IXYZ			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_PROTECT+1)
#define	DST_SYS_IUVW			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_PROTECT+2)
#define	DST_SYS_IRST			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_PROTECT+3)

//Ia(测量)						
#define	DST_SYS_IA_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+0)
#define	DST_SYS_IB_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+1)
#define	DST_SYS_IC_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+2)
#define	DST_SYS_IX_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+3)
#define	DST_SYS_IY_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+4)
#define	DST_SYS_IZ_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+5)
#define	DST_SYS_IU_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+6)
#define	DST_SYS_IV_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+7)
#define	DST_SYS_IW_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+8)
#define	DST_SYS_IR_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+9)
#define	DST_SYS_IS_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+10)
#define	DST_SYS_IT_M			MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_I+DST_PM_MEASURE+11)

//3I0(测量)=Ia+Ib+Ic			
#define	DST_SYS_IABC_M			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_MEASURE+0)
#define	DST_SYS_IXYZ_M			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_MEASURE+1)
#define	DST_SYS_IUVW_M			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_MEASURE+2)
#define	DST_SYS_IRST_M			MAKE_DST_SYS_FO1_CO1_ANA_SZ(DST_CT_I+DST_PM_MEASURE+3)

//----------------------------------------------
//bit[10-11]=10 虚拟通道
#define DST_CT_VCHN				(2<<10)

//bit[7-9]保留

//生成虚拟通道编码 CHN:0~127
#define MAKE_DST_SYS_VCHN(x)	MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_VCHN+x)
//第一虚拟通道
#define MAKE_DST_SYS_VCHN_MIN	MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_VCHN+0)
//最后虚拟通道
#define MAKE_DST_SYS_VCHN_MAX	MAKE_DST_SYS_FO1_CO1_ANA_PHA(DST_CT_VCHN+127)

//-------------------------------------------------
//bit[16-17]=01 杂项
#define	DST_AO_OTHER			(1<<16)

//生成 系统 填充1 CO1 AO1 的编码
#define MAKE_DST_SYS_FO1_CO1_AO1(x)	MAKE_DST_SYS_FO1_CO1((DST_AO_OTHER+(x)))

//a、bit[11-15]保留
//b、bit[8-10] 开入、开出 其他
#define DST_MASK_INPUT_OUTPUT_OTHER	(7<<8)

//-------------------------------------------------
//bit[8-10]=000 开入
#define	DST_IO_INPUT			(0<<8)

//生成 系统 填充1 CO1 AO1 input 的编码
#define MAKE_DST_SYS_FO1_CO1_AO1_IN(x)	MAKE_DST_SYS_FO1_CO1_AO1((DST_IO_INPUT+(x)))

//获取Output的索引
#define DST_INDEX_INPUT(dstInput)	(dstInput & DST_MASK_BIT0TO7)

//开入1							
#define	DST_SYS_INPUT1			MAKE_DST_SYS_FO1_CO1_AO1_IN(0)
#define	DST_SYS_INPUT2			MAKE_DST_SYS_FO1_CO1_AO1_IN(1)
#define	DST_SYS_INPUT3			MAKE_DST_SYS_FO1_CO1_AO1_IN(2)
#define	DST_SYS_INPUT4			MAKE_DST_SYS_FO1_CO1_AO1_IN(3)
#define	DST_SYS_INPUT5			MAKE_DST_SYS_FO1_CO1_AO1_IN(4)
#define	DST_SYS_INPUT6			MAKE_DST_SYS_FO1_CO1_AO1_IN(5)
#define	DST_SYS_INPUT7			MAKE_DST_SYS_FO1_CO1_AO1_IN(6)
#define	DST_SYS_INPUT8			MAKE_DST_SYS_FO1_CO1_AO1_IN(7)

//-------------------------------------------------
//bit[8-10]=001 开出
#define	DST_IO_OUTPUT			(1<<8)

//生成 系统 填充1 CO1 AO1 output 的编码
#define MAKE_DST_SYS_FO1_CO1_AO1_OUT(x)	MAKE_DST_SYS_FO1_CO1_AO1((DST_IO_OUTPUT+(x)))

//获取Output的索引
#define DST_INDEX_OUTPUT(dstOutput)	(dstOutput & DST_MASK_BIT0TO7)

//开出1							
#define	DST_SYS_OUTPUT1		MAKE_DST_SYS_FO1_CO1_AO1_OUT(0)
#define	DST_SYS_OUTPUT2		MAKE_DST_SYS_FO1_CO1_AO1_OUT(1)
#define	DST_SYS_OUTPUT3		MAKE_DST_SYS_FO1_CO1_AO1_OUT(2)
#define	DST_SYS_OUTPUT4		MAKE_DST_SYS_FO1_CO1_AO1_OUT(3)
#define	DST_SYS_OUTPUT5		MAKE_DST_SYS_FO1_CO1_AO1_OUT(4)
#define	DST_SYS_OUTPUT6		MAKE_DST_SYS_FO1_CO1_AO1_OUT(5)
#define	DST_SYS_OUTPUT7		MAKE_DST_SYS_FO1_CO1_AO1_OUT(6)
#define	DST_SYS_OUTPUT8		MAKE_DST_SYS_FO1_CO1_AO1_OUT(7)

//-------------------------------------------------
//bit[8-10]=010 杂项
#define	DST_IO_OTHER			(2<<8)

//生成 系统 填充1 CO1 AO1 IO2 的编码
#define MAKE_DST_SYS_FO1_CO1_AO1_IO2(x)	MAKE_DST_SYS_FO1_CO1_AO1((DST_IO_OTHER+(x)))

//a、bit[6-7]：保留
//b、bit[0-5]：具体
//采样计数器smpCnt				
#define	DST_SYS_SMPCNT			MAKE_DST_SYS_FO1_CO1_AO1_IO2(0)
//Time allow To Live=TTL
#define	DST_SYS_TTL				MAKE_DST_SYS_FO1_CO1_AO1_IO2(1)
//UTC time
#define	DST_SYS_UTC				MAKE_DST_SYS_FO1_CO1_AO1_IO2(2)
//stNum
#define	DST_SYS_STNUM			MAKE_DST_SYS_FO1_CO1_AO1_IO2(3)
//sqNum
#define	DST_SYS_SQNUM			MAKE_DST_SYS_FO1_CO1_AO1_IO2(4)
//GOOSE t字段
#define	DST_SYS_GSE_T			MAKE_DST_SYS_FO1_CO1_AO1_IO2(5)

//==================================================================================
//报文最大长度
#define MAX_PACKET_SIZE		1536


//======================================MU 相关====================================
//Mu最大启用个数
#define MAX_MU_USE_NUM		8
//填充项 最大个数
#define MAX_FILL_SET_NUM	128
#define MAX_MU_CHN			MAX_FILL_SET_NUM
//最大1s采样点数
#define MAX_SAMPLE_RATE		12800
//最小1s采样点数 F66D/S
#define MIN_SAMPLE_RATE		1600
//最小1s采样点数 F1210A/B
#define MIN_SAMPLE_RATE_AB	1200

//通道延时--最大延时采样点数
#define MAX_DELAY_SAMP_CNT  20
//Mu测试序列最大个数
#define MAX_TEST_ITEM_CNT    30

//MU smv采样配置
#define FILENAME_MU			"IOMU.CFG"
//MU 幅值测试配置
#define FILENAME_MU_TST		"IOMUTST.CFG"


//生成填充控制
#define MAKE_FILLSET(pos,len)	((pos&0xffff) | ((len&0xffff) << 16))
//获取填充控制 pos
#define DST_FILL_POS(fillSet)	(fillSet & 0xffff)
//获取填充控制 len
#define DST_FILL_LEN(fillSet)	((fillSet >> 16) & 0xffff)

//采样类型
#define SAMPLE_TYPE_9_1		0x0000
#define SAMPLE_TYPE_9_1_EX	0x0001
#define SAMPLE_TYPE_9_2		0x0100
//同步FT3
#define SAMPLE_TYPE_FT3		0x0200
#define SAMPLE_TYPE_FT3_EX	0x0201
//异步FT3
#define SAMPLE_TYPE_FT3_ASYN 0x0300

//同步FT3？
#define IsSynFT3(x)			(((x)>>8)==0x02)
//异步FT3？
#define IsAsynFT3(x)		(((x)>>8)==0x03)
//FT3
#define IsFT3(x)			(IsSynFT3(x) || IsAsynFT3(x))
//非FT3
#define IsNotFT3(x)			(((x)>>8)<0x02)
//9-2采样
#define IsSmv92(x)			(((x)>>8)==0x01)


//=================== 测试控制 相关 ======================
//----------------- 测试类型
//-----不虚特殊处理的
//无测试
#define TEST_TYPE_NONE			0
//同步标志
#define TEST_TYPE_SYNC_FLAG		1
//品质测试
#define TEST_TYPE_QUALITY		2
//飞点测试
#define TEST_TYPE_FLYPOINT		3
//品质位测试
#define TEST_TYPE_QUAL_ALL		4


//----需写代码 特殊处理 从 0x8000 起始
//序号偏差
#define TEST_TYPE_ORDER_DRIFT	0x8000
//丢帧
#define TEST_TYPE_FRAME_DROP	0x8001
//序号跳变
#define TEST_TYPE_ORDER_JUMP	0x8002
//错值测试
#define TEST_TYPE_BAD_VAL		0x8003
//报文抖动
#define TEST_TYPE_TIME_DRIFT	0x8004
//翻转序号 para1=翻转值
#define TEST_TYPE_SMPCNT_MAXVAL	0x8005

//测试类型的未处理起始，即当PC机用新程序时，IO821程序需更新才能支持
#define TEST_TYPE_NOT_SUPPORT	0x8006

//--------- 错值测试相关   --------------------------------------------------
//	VAL*2
#define TF_BV_MULTI_2			1
//	VAL*4
#define TF_BV_MULTI_4			2
//	VAL/2
#define TF_BV_DIV_2				0x81
//	VAL/4
#define TF_BV_DIV_4				0x82

//----------------- 触发类型    ---------------------------------------------
//帧计数启动
#define TEST_ACTTYPE_NORMAL			0
//goose in启动
#define TEST_ACTTYPE_GOOSE			1
//goose 变位触发
#define TEST_ACTTYPE_GOOSE_TRIG		2



//======================================GSE 相关====================================
//GseIn 启用最大数目
#define MAX_GSE_IN_NUM	20
//GseOut 启用最大数目
#define MAX_GSE_OUT_NUM	20

#define MAX_GOCBREF_LEN 64
#define MAX_GOID_LEN	64
#define MAX_DATASET_LEN	64
#define MAX_MACADDR_LEN 6
//GSE最大最小虚端子数
#define MAX_MAP_BIN_NUM	512
#define MIN_MAP_BIN_NUM	1

//Gse 配置
#define FILENAME_GSE	"IOGSE.CFG"
//Gse 通道测试配置
#define FILENAME_GSE_TST "IOGSETST.CFG"


//Goose In check mask define 匹配检查项
#define GICM_BIT_GOCBREF	(1<<0)
#define GICM_BIT_GOID		(1<<1)
#define GICM_BIT_DATASET	(1<<2)
#define GICM_BIT_CONFREV	(1<<3)
#define GICM_BIT_NDSCOM		(1<<4)
#define GICM_BIT_MACADDR	(1<<5)
#define GICM_BIT_APPID		(1<<6)
#define GICM_BIT_TTL		(1<<7)
#define GICM_BIT_TEST		(1<<8)
#define GICM_BIT_GSEINDROP	(1<<9)

//===================GSE 测试控制 相关 ======================
#define MAX_GSEOUT_TESTSET_NUM 300
//----------------- 测试类型   GseOut Test Type -> GOTT
//-----不虚特殊处理的
//无测试
#define GOTT_NONE			0
//Goose 检修位测试          setNum=1 setVal=1 para1=20 para2=5
#define GOTT_TEST_BIT    	0x0001

//----需写代码 特殊处理 从 0x8000 起始
//丢帧                      para1=20 para2=5
#define GOTT_FRAME_DROP 	0x8000
//stNum异常                 para1=20 para2=5 para3=偏差
#define GOTT_STNUM_DRIFT	0x8001
//心跳异常                  para1=偏差时间
#define GOTT_TTL_DRIFT   	0x8002
//丢失同步                  para1=20 para2=5
#define GOTT_SYNC_FLAG		0x8003
//TTL无效                   para1=20 para2=5
#define GOTT_TTL_INVALID	0x8004
//时间品质                  para1=20 para2=5 para3=时间品质
#define GOTT_TIME_QUALITY  	0x8005
//SqNum错序                 para1=20 para2=5 para3=偏差
#define GOTT_SQNUM_DRIFT  	0x8006

//SqNum保持不变
#define FLAG_GOTT_STSQ_PERIOD_SQ_HOLD    1
//StNum保持不变
#define FLAG_GOTT_STSQ_PERIOD_ST_HOLD    2
//StNum每帧变化
#define FLAG_GOTT_STSQ_PERIOD_ST_INC     4

//StNum、SqNum定时发送      para1=20 para2=5 para3=标志位(FLAG_GOTT_STSQ_PERIOD_XXX) para4=定时时间(0无效)
#define GOTT_STSQ_PERIOD  	0x8007
//StNum、SqNum设定值 定时发送  para1=20 para2=5 para3=StNum para4=SqNum para5=定时时间(0无效)
#define GOTT_STSQSET_PERIOD 0x8008


//测试类型的未处理起始，即当PC机用新程序时，IO821程序需更新才能支持
#define GOTT_TYPE_NOT_SUPPORT	0x8009

#endif
