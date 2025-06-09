#pragma once

#include "../../../Module/MemBuffer/CycleMemBuffer.h"
#include "../../../module/baseclass/exbaselist.h"
#include "PpPkgSpyInterface.h"

#define  PP_RELEASE_FLAG

#define PPCLASSID_BASECLASS         (CLASSID_BASECLASS    + 0X00110000)
#define PPCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00110000)


//////////////////////////////////////////////////////////////////////////
//���classid����
#define PPCLASSID_DEVICEMODELS                   (PPCLASSID_EXLISTCLASS+0x00000001)
#define PPCLASSID_DEVICEMODEL						(PPCLASSID_EXLISTCLASS+0x00000002)
#define PPCLASSID_DMNODETYPE						(PPCLASSID_EXLISTCLASS+0x00000003)

//manager classid define
#define PPCLASSID_PPDEVICEMAP						(PPCLASSID_BASECLASS+0x00000004)
#define PPCLASSID_PPPACKAGEDETAIL				(PPCLASSID_EXLISTCLASS+0x00000005)
#define PPCLASSID_PPPACKAGESENDMNGR		(PPCLASSID_BASECLASS+0x00000006)
#define PPCLASSID_RUNTIMER							(PPCLASSID_BASECLASS+0x00000007)
#define PPCLASSID_RUNTIMERMNGR					(PPCLASSID_EXLISTCLASS+0x00000008)

//Package classid define
#define PPCLASSID_BYTEBLOCK							(PPCLASSID_EXLISTCLASS+0x01000000)
#define PPCLASSID_BYTEBLOCKS						(PPCLASSID_EXLISTCLASS+0x03000000)
#define PPCLASSID_RBYTEBLOCK						(PPCLASSID_BYTEBLOCK+0x0000000B)
#define PPCLASSID_WBYTEBLOCK						(PPCLASSID_BYTEBLOCK+0x0000000C)

//DataBind classid define
#define PPCLASSID_PPDATABIND						(PPCLASSID_BASECLASS+0x0000000D)
#define PPCLASSID_PPDATABINDS						(PPCLASSID_EXLISTCLASS+0x0000000E)

//Datasetbase classid define
#define PPCLASSID_BBDATA 			     				(PPCLASSID_BYTEBLOCKS+0x0000000F)
#define PPCLASSID_BBDATASET			     			(PPCLASSID_BYTEBLOCKS+0x00000010)
#define PPCLASSID_BBDATASETS		     			(PPCLASSID_BYTEBLOCKS+0x00000011)
#define PPCLASSID_DATABYTEBLOCK					(PPCLASSID_BYTEBLOCK+0x00000012)

//DataSetr classid define
#define PPCLASSID_RBBDATA 			     			(PPCLASSID_BYTEBLOCKS+0x00000013)
#define PPCLASSID_RBBDATASET			     		(PPCLASSID_BYTEBLOCKS+0x00000014)
#define PPCLASSID_RBBDATASETS			     		(PPCLASSID_BYTEBLOCKS+0x00000015)
#define PPCLASSID_RDATABYTEBLOCK			    (PPCLASSID_BYTEBLOCK+0x00000016)

//DataSetw classid define 
#define PPCLASSID_WBBDATA 			     			(PPCLASSID_BYTEBLOCKS+0x00000017)
#define PPCLASSID_WBBDATASET			     		(PPCLASSID_BYTEBLOCKS+0x00000018)
#define PPCLASSID_WBBDATASETS			     		(PPCLASSID_BYTEBLOCKS+0x00000019)
#define PPCLASSID_WDATABYTEBLOCK			    (PPCLASSID_BYTEBLOCK+0x0000001A)

//Datatype classid define
#define PPCLASSID_BBDATARANGE					(PPCLASSID_BASECLASS+0x0000001B)
#define PPCLASSID_BBDATARANGES			        (PPCLASSID_EXLISTCLASS+0x0000001C)
#define PPCLASSID_DVDATATYPE						(PPCLASSID_BASECLASS+0x0000001D)
#define PPCLASSID_DVDATATYPES					(PPCLASSID_EXLISTCLASS+0x0000001E)


//PpPackage classid define
#define PPCLASSID_PPPAKAGE							(PPCLASSID_EXLISTCLASS+0x0000001F)
#define PPCLASSID_PPPAKAGES							(PPCLASSID_EXLISTCLASS+0x00000020)
#define PPCLASSID_PPPARSEPACKGE					(PPCLASSID_EXLISTCLASS+0x00000021)
#define PPCLASSID_PPPRODUCEPACKGE				(PPCLASSID_EXLISTCLASS+0x00000022)
#define PPCLASSID_PPTTPACKAGE    					(PPCLASSID_EXLISTCLASS+0x00000023)

//Variable classid define
#define PPCLASSID_BBVARIABLE						(PPCLASSID_BASECLASS+0x00000024)
#define PPCLASSID_BBVARIABLES    					(PPCLASSID_EXLISTCLASS+0x00000025)

//Procedure classid define 
#define PPCLASSID_PPJUMP	    						(PPCLASSID_EXLISTCLASS+0x00000026)
#define PPCLASSID_PPJUMPS	    						(PPCLASSID_EXLISTCLASS+0x00000027)
#define PPCLASSID_PPTIMER       						(PPCLASSID_EXLISTCLASS+0x00000028)
#define PPCLASSID_PPTIMERS       					(PPCLASSID_EXLISTCLASS+0x00000029)
#define PPCLASSID_PPDATABINDMAP				(PPCLASSID_BASECLASS+0x0000002A)
#define PPCLASSID_PPDATABINDMAPS				(PPCLASSID_EXLISTCLASS+0x0000002B)
#define PPCLASSID_PPNODE	    						(PPCLASSID_EXLISTCLASS+0x0000002C)
#define PPCLASSID_PPNODES	    					(PPCLASSID_EXLISTCLASS+0x0000002D)
#define PPCLASSID_PPPROCEDURE    				(PPCLASSID_EXLISTCLASS+0x0000002E)
#define PPCLASSID_PPPROCEDURES    				(PPCLASSID_EXLISTCLASS+0x0000002F)
#define PPCLASSID_PPPACKAGEREF    				(PPCLASSID_EXLISTCLASS+0x00000030)
#define PPCLASSID_PPDATAINTERFACE    				(PPCLASSID_BASECLASS+0x00000031)

//Template
#define PPCLASSID_PPTEMPLATE    					(PPCLASSID_EXLISTCLASS+0x00000032)
#define PPCLASSID_PPPROCEDUREREF    			(PPCLASSID_BASECLASS+0x00000033)
#define PPCLASSID_PPPROCEDUREREFS    			(PPCLASSID_EXLISTCLASS+0x00000034)

//Script classid define
#define PPCLASSID_PPSCRIPT       						(PPCLASSID_EXLISTCLASS+0x00000035)

#define PPCLASSID_PPENGINEDATA       						(CLASSID_EXLISTCLASS+0x00000036)
#define PPCLASSID_PPPAKAGE_TEXT       						(PPCLASSID_BASECLASS+0x00000036)
#define PPCLASSID_PPPAKAGE_TEXTS       						(CLASSID_EXLISTCLASS+0x00000037)

#define PPCLASSID_PPPACKAGEREFS       						(CLASSID_EXLISTCLASS+0x00000038)

#define PPNODE_TYPE_EMPTY       0
#define PPNODE_TYPE_PRODUCE    1
#define PPNODE_TYPE_RESPONSE   2
#define PPNODE_TYPE_PROCESS     3
#define PPNODE_TYPE_ENDNODE    4

//////////////////////////////////////////////////////////////////////////
//��������ض���
typedef struct PackageBufferPos
{
	BYTE *pBuffer;
	long nBuffer1BeginPos;
	long nBuffer1EndPos;
	long nBuffer2BeginPos;
	long nBuffer2EndPos;
	long nIndex;		//��ǰ���ʵ�����
}PACKAGEBUFFERPOS, *PPACKAGEBUFFERPOS;

long PpGetLengthFromCurr(PACKAGEBUFFERPOS &oBuffPos);
long PpOffsetCurrBuffer(PACKAGEBUFFERPOS &oBuffPos, long nOffsetLen);

//���������е�״̬����
#define PPS_ERROR                       0X80000000
#define PPS_HAS_NO_PACKAGE     0X00000001
#define PPS_NOT_WHOLE_MATCH  0X00000002
#define PPS_NO_DEFINE_PACKAGE 0X00000004
#define PPS_LOOP_BREAK 0X00000008

//2024-7-8  LIJUNQING ���Ļ��������Ȳ���
#define PPS_BUF_NOT_ENOUGH 0X00000010

//�����Ƿ����
inline BOOL IsPpParseError(DWORD dwResult)
{
	return ( (dwResult & PPS_ERROR) == PPS_ERROR);
}
inline BOOL PpParseError()
{
	return ( PPS_ERROR );
}

//�Ƿ����������package
inline BOOL IsPpParseHasPakage(DWORD dwResult)
{
	return ( (dwResult & PPS_HAS_NO_PACKAGE) == 0);
}

inline DWORD PpParseHasNoPackage()
{
	return (PPS_ERROR | PPS_HAS_NO_PACKAGE);
}


//�Ƿ���ȫƥ��
inline DWORD IsPpParseWholeMatch(DWORD dwResult)
{
	return ( (dwResult & PPS_NOT_WHOLE_MATCH) == 0);
}
inline DWORD IsPpParseMatch(DWORD dwResult)
{
	return ( (dwResult & PPS_NOT_WHOLE_MATCH) == 0);
}

inline DWORD IsPpParseLoopBreak(DWORD dwResult)
{
	return ( (dwResult & PPS_LOOP_BREAK) == 0);
}

inline DWORD PpParseNotWholeMatch()
{
	return (PPS_ERROR | PPS_NOT_WHOLE_MATCH);
}

inline DWORD IsPpParseBufNotEnough(DWORD dwResult)
{
	return ( (dwResult & PPS_BUF_NOT_ENOUGH) == PPS_BUF_NOT_ENOUGH);
}

inline DWORD PpParseBufNotEnough()
{
	return (PPS_ERROR | PPS_BUF_NOT_ENOUGH);
}

inline DWORD PpParseWholeMatch()
{
	return (0);
}

inline DWORD PpParseMatch()
{
	return (0);
}

//û�ж���ı���֡
inline DWORD IsPpParseNoDefinePackage(DWORD dwResult)
{
	return ( (dwResult & PPS_NO_DEFINE_PACKAGE) == PPS_NO_DEFINE_PACKAGE);
	
}

inline DWORD PpParseNoDefinePackage()
{
	return (PPS_ERROR | PPS_NO_DEFINE_PACKAGE);
}

//��������е�״̬����
#define PPR_FINISH				0X00000000
#define PPR_ERROR				0X00000001
#define PPR_NOT_FINISH			0X00000002

//�����Ƿ�ȫ�����
inline BOOL IsPpProduceFinish(DWORD dwResult)
{
	return ( (dwResult & PPR_FINISH) == PPR_FINISH);
}

inline DWORD PpProduceFinish()
{
	return ( PPR_FINISH );
}

//�����Ƿ��д�
inline BOOL IsPpProduceError(DWORD dwResult)
{
	return ( (dwResult & PPR_ERROR) == PPR_ERROR);
}

inline DWORD PpProduceError()
{
	return ( PPR_ERROR );
}

//�����Ƿ����һ����
inline BOOL IsPpProduceNotFinish(DWORD dwResult)
{
	return ( (dwResult & PPR_NOT_FINISH) == PPR_NOT_FINISH);
}

inline DWORD PpProduceNotFinish()
{
	return ( PPR_NOT_FINISH );
}

inline BOOL PpIsByteBlock(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	return (PPCLASSID_BYTEBLOCK == (nClassID & PPCLASSID_BYTEBLOCK));
}

inline BOOL PpIsByteBlock(UINT nClassID)
{
	return (PPCLASSID_BYTEBLOCK == nClassID
		|| PPCLASSID_RBYTEBLOCK == nClassID		|| PPCLASSID_RDATABYTEBLOCK == nClassID
		|| PPCLASSID_WBYTEBLOCK == nClassID		|| PPCLASSID_WDATABYTEBLOCK == nClassID
		|| PPCLASSID_DATABYTEBLOCK == nClassID);
}

inline BOOL PpIsByteBlocks(UINT nClassID)
{
	return (PPCLASSID_BYTEBLOCKS == nClassID
		|| PPCLASSID_BBDATA == nClassID
		|| PPCLASSID_RBBDATA == nClassID
		|| PPCLASSID_WBBDATA == nClassID);
}

inline BOOL PpIsByteBlocks(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	return (PPCLASSID_BYTEBLOCKS == (nClassID & PPCLASSID_BYTEBLOCKS));
}

//////////////////////////////////////////////////////////////////////////
//��������
static const CString PPRANGE_CONST_LONG			= _T("long");
static const CString PPRANGE_CONST_HEX			= _T("hex");
static const CString PPRANGE_CONST_TEXT			= _T("txt");

//�ֽڿ��������Ͷ���
const CString g_strBbDataTypeConstName = _T("����");
const CString g_strBbDataTypeConst = _T("const");
const CString g_strBbDataTypeListName = _T("�����б�");
const CString g_strBbDataTypeList = _T("list");
const CString g_strBbDataTypeRangeName = _T("��Χ");
const CString g_strBbDataTypeRang = _T("range");
const CString g_strBbDataTypeTextName = _T("��ʽ�ı�");
const CString g_strBbDataTypeText = _T("text");

//У��
const CString g_strBbDataTypeSumCheckName = _T("��У��");
const CString g_strBbDataTypeSumCheck = _T("sumcheck");

const CString g_strBbDataTypeCrcCheckName = _T("CRCУ��(��ʼֵ0)");
const CString g_strBbDataTypeCrcCheck = _T("crccheck");

const CString g_strBbDataTypeCrcCheckFFName = _T("CRCУ��(��ʼֵ0xFFFF)");
const CString g_strBbDataTypeCrcCheckFF = _T("crccheckff");

const CString g_strBbDataTypeCrcCheckTableName = _T("CRCУ��(���)");
const CString g_strBbDataTypeCrcCheckTable = _T("crcchecktb");

const CString g_strBbDataTypeVariableName = _T("�ű�");
const CString g_strBbDataTypeVariable = _T("variable");

//////////////////////////////////////////////////////////////////////////
//�ֽڿ����������
#define BbDataType_NULL     0
#define BbDataType_Const    1
#define BbDataType_Variable  2

const CString g_strSystemVariableID = _T("sys-var");
const CString g_strSystemVariableName = _T("ϵͳ����");
const CString g_strPackageVariableLocalID = _T("pkg-var-local");
const CString g_strPackageVariableLocalName = _T("֡����");
const CString g_strPackageVariableGlobalID = _T("pkg-var-global");
const CString g_strPackageVariableGlobalName = _T("ȫ�ֱ���");

const CString g_strVariableDataTypeFloatID = _T("double");
const CString g_strVariableDataTypeFloatName = _T("������");
const CString g_strVariableDataTypeIntegerID = _T("Long");
const CString g_strVariableDataTypeIntegerName    = _T("����");
const CString g_strVariableDataTypeStringID = _T("string");
const CString g_strVariableDataTypeStringName = _T("�ַ�����");


const CString g_strVariableDataTypeItemIndexID    = _T("item-index");
const CString g_strVariableDataTypeItemIndexID2   = _T("index");
const CString g_strVariableDataTypeCPUName        = _T("CPU��");
const CString g_strVariableDataTypeCPUID          = _T("CPU");
const CString g_strVariableDataTypeGROUPName      = _T("�������");
const CString g_strVariableDataTypeGROUPID        = _T("GROUP");
const CString g_strVariableDataTypeItemIndexName  = _T("��Ŀ��");
const CString g_strVariableDataTypeInfoIndexID    = _T("infor-index");
const CString g_strVariableDataTypeInfoIndexName  = _T("��Ϣ���");
const CString g_strVariableDataTypeDeviceAddrID   = _T("device_addr");
const CString g_strVariableDataTypeDeviceAddrName = _T("�豸��ַ");

const CString g_strSystemVariableInforIndex = _T("nInforIndex");
const CString g_strSystemVariableItemIndex = _T("nItemIndex");

//////////////////////////////////////////////////////////////////////////
//֡����ģʽ
const CString g_strEncodeModeNone = _T("none");
const CString g_strEncodeModeSend = _T("send");
const CString g_strEncodeModeReceive = _T("receive");
const CString g_strEncodeModeSAndR = _T("send-and-receive");
const CString g_strEncodeModeSOrR = _T("send-or-receive");

const CString g_strEncodeModeNoneName = _T("������");
const CString g_strEncodeModeSendName = _T("֡����(����)");
const CString g_strEncodeModeReceiveName = _T("֡����(����)");
const CString g_strEncodeModeSAndRName = _T("֡����(���ͽ���ͳһ)");
const CString g_strEncodeModeSOrRName = _T("֡����(���ͽ��ն���)");

///////////////////////////////////////////////////////////////////////////
//֡������������
const CString g_strEncodeModeDataTypeSendName = _T("֡����(����)");
const CString g_strEncodeModeDataTypeSendID = _T("encode-send");

const CString g_strEncodeModeDataTypeReceiveName = _T("֡����(����)");
const CString g_strEncodeModeDataTypeReceiveID = _T("encode-receive");

const CString g_strEncodeModeDataTypeEncodeName = _T("֡����");
const CString g_strEncodeModeDataTypeEncodeID = _T("encode");


const CString g_strNoneCodeModeKey = _T("��");
const CString g_strSendCodeModeKey = _T("���ͱ��루���ܲ����룩");
const CString g_strReceiveCodeModeKey = _T("���ܱ��루���Ͳ����룩");
const CString g_strBothRespectCodeModeKey = _T("���ͽ��ն�������");
const CString g_strBothTeamCodeModeKey = _T("���ͽ���ͳһ����");
const CString g_strPackageCodeKey = _T("֡����");
const CString g_strSenderCodeKey = _T("֡���루���ͣ�");
const CString g_strReceiverCodeKey = _T("֡���루���ܣ�");
const CString g_strSumCheckKey = _T("��У��");
const CString g_strCRCCheckKey = _T("CRCУ��");
const CString g_strCRCSfKey = _T("CRCУ�飨�ķ���");

static const CString g_strPpFileFilter = _T("ppxml");
static const CString g_strPpFilePostfix = _T(".ppxml");
static const CString g_strPpFilePostfixDes = _T("��Լģ���ļ�");



extern CLogBase* g_pLogTracePrint;
extern CLogBase* g_pLogPkgSendPrint;
extern CLogBase* g_pLogPkgReceivePrint;
extern CPpPkgSpyInterface* g_pLogPkgSpy;   //���ļ��ӣ�����˷����ͻ���

extern long g_bLogBindQueryErrorInfor;
extern long g_bLogPackageInfor;
extern long g_bLogEngineDebugInfor;

void PpLogProtocol(char *pszPpLogProtocol, CYCLEMEMBUFFERPOS &oBufPos, CString &strMsg);
void LogReceivePackage(char *pszPpLogProtocol, BYTE* buffer, long len);
CString Pp_GetPoProjectPath();


#define PPTEMPLATE_DEVICEMODE_SINGLE   0
#define PPTEMPLATE_DEVICEMODE_MULTI    1
#define PPTEMPLATE_DEVICEMODE_NONE     -1

#define PPTEMPLATE_DATASETMODE_TREE     0
#define PPTEMPLATE_DATASETMODE_LIST     1

CString pp_GetDeviceModeModeString(UINT nMode);


//2015-7-5
#define  ENGINE_VERSION_1_0   0x0002000

#define  ENGINE_VERSION       ENGINE_VERSION_1_0

#define WM_PROCEDURE_END_MSG  (WM_USER + 956)
#define WM_SYSTEM_MSG  (WM_USER + 957)
//2023-1-29  lijunqing ͨ�Ź��̲�����Ϣ
#define WM_PROCEDURE_STEP_MSG  (WM_USER + 958)
//2023-2-1 LIJUNQING 
#define WM_EVENT_MSG  (WM_USER + 959)
//2023-3-5 LIJUNQING 
#define WM_MMS_REPORT_MSG  (WM_USER + 960)

//2023-01-27  lijunqing
//  for m_nProtoPkgProcess
#define  PROTO_PKG_PROCESS_MODE_NOMAL      0
#define  PROTO_PKG_PROCESS_MODE_DNP          1

#define  PROTO_PKG_PROCESS_MODEID_DNP          "dnp"
