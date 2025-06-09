//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"

class CXLanguageResourcePpBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourcePpBase();
	virtual ~CXLanguageResourcePpBase();
	
	void InitLangFileForDebug(const CString &strModule);

private:
	CXLanguage m_oXLangRsPpBase;

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	

	virtual void InitLangRsByFile();
	virtual void RegisterLanguageResource();

	virtual void InitLangTxt();

};

	extern CString  g_strXLangRsPpBaseFile;
	extern CString g_sLangID_PrtcEngine;     //��Լ�������
	extern CString g_sLangTxt_PrtcEngine;
	extern CString g_sLangID_FrameSend;     //֡\"%s\"û��ָ������ͨ��
	extern CString g_sLangTxt_FrameSend;
	extern CString g_sLangID_OpenXMLFail;     //��XML�ļ�ʧ�ܣ�
	extern CString g_sLangTxt_OpenXMLFail;
	extern CString g_sLangID_SaveSetFileFail;     //����ͨѶ�����ļ�ʧ�ܣ�
	extern CString g_sLangTxt_SaveSetFileFail;
	extern CString g_sLangID_DataRltnshipError;     //���ݰ󶨶������
	extern CString g_sLangTxt_DataRltnshipError;
	extern CString g_sLangID_DataRltnshipError2;     //���ݰ󶨶������
	extern CString g_sLangTxt_DataRltnshipError2;
	extern CString g_sLangID_DataRltnshipError3;     //%s : ���ݰ󶨶������
	extern CString g_sLangTxt_DataRltnshipError3;
	extern CString g_sLangID_SureValueASDU;     //��Ӧ��ȷ��д��ֵASDU10
	extern CString g_sLangTxt_SureValueASDU;

	extern CString g_sLangID_PrcsFrameUnExist;     //���̽ڵ�[%s]������֡[%s]������
	extern CString g_sLangTxt_PrcsFrameUnExist;
	extern CString g_sLangID_PointFrameUnExist;     //�ڵ�\"%s\"����������֡\"%s\"������
	extern CString g_sLangTxt_PointFrameUnExist;
	extern CString g_sLangID_PointNotFrame;     //�ڵ�\"%s\"������\"%s\"��������֡
	extern CString g_sLangTxt_PointNotFrame;
	extern CString g_sLangID_PrcsNoData;     //����\"%s\"û�ж������ݽӿ�\"%s\"
	extern CString g_sLangTxt_PrcsNoData;
	extern CString g_sLangID_DataBufferError;     //�ֽڿ�[%s]���ݻ������nIndex=%d
	extern CString g_sLangTxt_DataBufferError;

	extern CString g_sLangID_FctnCallErrorBind;     //����BindItemIndex���ô���
	extern CString g_sLangTxt_FctnCallErrorBind;
	extern CString g_sLangID_FctnSError;     //����SBindItemIndex�󶨴���
	extern CString g_sLangTxt_FctnSError;
	extern CString g_sLangID_DataErrorIndex;     //�ֽڿ�[%s]���ݻ������nIndex=%d Bytes=%d Length=%d
	extern CString g_sLangTxt_DataErrorIndex;
	extern CString g_sLangID_DataErrorIndex2;     //�ֽڿ�[%s]���ݻ������nIndex=%d Bytes=%d Length=4
	extern CString g_sLangTxt_DataErrorIndex2;
	extern CString g_sLangID_GetBbEmpty;     //SetBbValStr���ַ�������ָ��Ϊ��
	extern CString g_sLangTxt_GetBbEmpty;
	extern CString g_sLangID_GetBbError;     //%s(%s)��GetBbValStr(%d,%d)����
	extern CString g_sLangTxt_GetBbError;
	extern CString g_sLangID_FctnDataCall;     //%s::GetBbDataStr���������ڡ���ʽ�ı��������ֽڿ��б�����
	extern CString g_sLangTxt_FctnDataCall;
	extern CString g_sLangID_DataUnExist;     //�󶨵�����[%s]=[%s]������
	extern CString g_sLangTxt_DataUnExist;
	extern CString g_sLangID_FctnConDataError;     //����SetBindDataL:�󶨹�ϵ��������\"%s\"����
	extern CString g_sLangTxt_FctnConDataError;
	extern CString g_sLangID_FctnCallError;     //����AdBindDataList���ô���
	extern CString g_sLangTxt_FctnCallError;
	extern CString g_sLangID_FctnCallSysError4;     //����AdBindDataList����:ϵͳ����(û�й������豸����ģ��)
	extern CString g_sLangTxt_FctnCallSysError4;
	extern CString g_sLangID_FctnCallData;     //����AdBindDataList����:���ݰ󶨴���
	extern CString g_sLangTxt_FctnCallData;
	extern CString g_sLangID_FctnCallNode;     //����AdBindDataList����:�ڵ�\"%s\" ������
	extern CString g_sLangTxt_FctnCallNode;
	extern CString g_sLangID_FctnFireCallError;     //����FireDataMsg���ô���
	extern CString g_sLangTxt_FctnFireCallError;
	extern CString g_sLangID_SystemErrorPath;     //ϵͳ����(·��Ϊ��)
	extern CString g_sLangTxt_SystemErrorPath;
	extern CString g_sLangID_DataNodeUnExist4;     //InsertDsData:���ݽڵ㲻����
	extern CString g_sLangTxt_DataNodeUnExist4;
	extern CString g_sLangID_DataNodeUnExist3;     //InsertBindData:���ݽڵ㲻����
	extern CString g_sLangTxt_DataNodeUnExist3;
	extern CString g_sLangID_DataNodeUnExist2;     //InsertDataset:���ݽڵ㲻����
	extern CString g_sLangTxt_DataNodeUnExist2;
	extern CString g_sLangID_DataNodeUnExist;     //script_InsertLogicDevice:���ݽڵ㲻����
	extern CString g_sLangTxt_DataNodeUnExist;
	extern CString g_sLangID_FctnGetCallError;     //����GetBindDataL���ô���
	extern CString g_sLangTxt_FctnGetCallError;
	extern CString g_sLangID_FctnSetError;     //����SetBindDataL:�ֽڿ�\"%s\"�а󶨴���
	extern CString g_sLangTxt_FctnSetError;
	extern CString g_sLangID_FctnBindSet;     //����SetBindDataL:�ֽڿ�\"%s\"�а����ݼ�
	extern CString g_sLangTxt_FctnBindSet;
	extern CString g_sLangID_FctnBindCallError;     //����###BindData###���ô���
	extern CString g_sLangTxt_FctnBindCallError;
	extern CString g_sLangID_FctnGetError;     //����GetBindDeviceDataNode:�ֽڿ�\"%s\"�а󶨴���
	extern CString g_sLangTxt_FctnGetError;
	extern CString g_sLangID_FctnDataSet;     //����GetBindDeviceDataNode:�ֽڿ�\"%s\"�а����ݼ�
	extern CString g_sLangTxt_FctnDataSet;
	extern CString g_sLangID_PathNoData;     //path[%s]û�ж�Ӧ�����ݽڵ�
	extern CString g_sLangTxt_PathNoData;
	extern CString g_sLangID_SetVariUnExist;     //GetValue:����\"%s\"������
	extern CString g_sLangTxt_SetVariUnExist;
	extern CString g_sLangID_SetLongVariUnExist;     //SetValueLong:����\"%s\"������
	extern CString g_sLangTxt_SetLongVariUnExist;
	extern CString g_sLangID_GetFctnCallErrorLen;     //GetPkgLen�������ô���
	extern CString g_sLangTxt_GetFctnCallErrorLen;
	extern CString g_sLangID_GetFctnCallErrorPkg;     //GetPkgNum�������ô���
	extern CString g_sLangTxt_GetFctnCallErrorPkg;
	extern CString g_sLangID_AddFctnCallError;     //AddGlobal�������ô���
	extern CString g_sLangTxt_AddFctnCallError;
	extern CString g_sLangID_GetFctnCallError;     //GetGlobal�������ô���
	extern CString g_sLangTxt_GetFctnCallError;
	extern CString g_sLangID_SetFctnCallError;     //SetGlobal�������ô���
	extern CString g_sLangTxt_SetFctnCallError;
	extern CString g_sLangID_FctnCallSysError3;     //����Run����:ϵͳ����
	extern CString g_sLangTxt_FctnCallSysError3;
	extern CString g_sLangID_FctnCallSysError2;     //����SetPpRunState����:ϵͳ����
	extern CString g_sLangTxt_FctnCallSysError2;
	extern CString g_sLangID_FctnCallSysError;     //����SetPpValid����:ϵͳ����
	extern CString g_sLangTxt_FctnCallSysError;
	extern CString g_sLangID_DataIndexError;     //�ֽڿ�[%s]���ݻ������nIndex=%d Length=%d
	extern CString g_sLangTxt_DataIndexError;
	extern CString g_sLangID_FctnCallSystem;     //����Connect����:ϵͳ����(û�й������豸����ģ��)
	extern CString g_sLangTxt_FctnCallSystem;
	extern CString g_sLangID_SystemErrorData8;     //ϵͳ����(·����%s����Ӧ�����ݲ�����)
	extern CString g_sLangTxt_SystemErrorData8;
	extern CString g_sLangID_SystemErrorData7;     //ϵͳ����(·����%s����Ӧ���߼��豸������)
	extern CString g_sLangTxt_SystemErrorData7;
	extern CString g_sLangID_SystemErrorData6;     //ϵͳ����(·����%s����Ӧ���豸������)
	extern CString g_sLangTxt_SystemErrorData6;
	extern CString g_sLangID_SystemErrorData5;     //ϵͳ����(û�й������豸����ģ��)
	extern CString g_sLangTxt_SystemErrorData5;
	extern CString g_sLangID_SystemErrorData4;     //ϵͳ����(���Ƕ��豸����ģ��)
	extern CString g_sLangTxt_SystemErrorData4;
	extern CString g_sLangID_SystemErrorData3;     //ϵͳ����(���ݡ�%s��û�����ԡ�%s��)
	extern CString g_sLangTxt_SystemErrorData3;
	extern CString g_sLangID_SystemErrorData2;     //ϵͳ����(���ݼ���%s��û�����ԡ�%s��)
	extern CString g_sLangTxt_SystemErrorData2;
	extern CString g_sLangID_SystemErrorData;     //ϵͳ����(�߼��豸��%s��û�����ԡ�%s��)
	extern CString g_sLangTxt_SystemErrorData;
	extern CString g_sLangID_FctnDataErrorDsData;     //����AdDsDataList����:���ݰ󶨴���
	extern CString g_sLangTxt_FctnDataErrorDsData;
	extern CString g_sLangID_FctnCallNoReport;     //����AdDsDataList����:��%s�����ݼ�û����������
	extern CString g_sLangTxt_FctnCallNoReport;
	extern CString g_sLangID_FctnCallPoint;     //����AdDsDataList����:�ڵ�\"%s\" ������
	extern CString g_sLangTxt_FctnCallPoint;
	extern CString g_sLangID_FctnDataErrorDsPkg;     //����AdDsPkgDetail����:���ݰ󶨴���
	extern CString g_sLangTxt_FctnDataErrorDsPkg;
	extern CString g_sLangID_FctnDataErrorVal;     //����AdValPkgDetail����:���ݰ󶨴���
	extern CString g_sLangTxt_FctnDataErrorVal;
	extern CString g_sLangID_FctnCallLength;     //����SetBcd24Float����:����������(%d)����
	extern CString g_sLangTxt_FctnCallLength;
	
	extern CString g_sLangID_Constant;     //����
	extern CString g_sLangTxt_Constant;
	extern CString g_sLangID_DataList;     //�����б�
	extern CString g_sLangTxt_DataList;
	extern CString g_sLangID_FormatText;     //��ʽ�ı�
	extern CString g_sLangTxt_FormatText;
	extern CString g_sLangID_SumCheck;     //��У��
	extern CString g_sLangTxt_SumCheck;
	extern CString g_sLangID_CRCCheck;     //CRCУ��(��ʼֵ0)
	extern CString g_sLangTxt_CRCCheck;
	extern CString g_sLangID_CRCCheck2;     //CRCУ��(��ʼֵ0xFFFF)
	extern CString g_sLangTxt_CRCCheck2;
	extern CString g_sLangID_CRCCheck3;     //CRCУ��(���)
	extern CString g_sLangTxt_CRCCheck3;
	extern CString g_sLangID_Script;     //�ű�
	extern CString g_sLangTxt_Script;
	extern CString g_sLangID_EncodeModeNoneName;     //������
	extern CString g_sLangTxt_EncodeModeNoneName;
	extern CString g_sLangID_EncodeModeSendName;     //֡����(����)
	extern CString g_sLangTxt_EncodeModeSendName;
	extern CString g_sLangID_EncodeModeReceiveName;     //֡����(����)
	extern CString g_sLangTxt_EncodeModeReceiveName;
	extern CString g_sLangID_EncodeModeSAndRName;     //֡����(���ͽ���ͳһ)
	extern CString g_sLangTxt_EncodeModeSAndRName;
	extern CString g_sLangID_EncodeModeSOrRName;     //֡����(���ͽ��ն���)
	extern CString g_sLangTxt_EncodeModeSOrRName;
	extern CString g_sLangID_EncodeName;     //֡����
	extern CString g_sLangTxt_EncodeName;
	extern CString g_sLangID_Receive;     //����
	extern CString g_sLangTxt_Receive;
	extern CString g_sLangID_SingDev;     //��һ�豸
	extern CString g_sLangTxt_SingDev;
	extern CString g_sLangID_MultDev;     //���豸
	extern CString g_sLangTxt_MultDev;
	extern CString g_sLangID_NoDevDataModel;     //û��ָ���豸����ģ��ģʽ
	extern CString g_sLangTxt_NoDevDataModel;
	extern CString g_sLangID_ErrorMessage;     //������:(Begin=%d      Len=%d)
	extern CString g_sLangTxt_ErrorMessage;
	extern CString g_sLangID_Send;     //����
	extern CString g_sLangTxt_Send;
	extern CString g_sLangID_CommunPathUnExist;     //ģ�嶨���ͨ��ͨ��������
	extern CString g_sLangTxt_CommunPathUnExist;
	extern CString g_sLangID_CommunPathUnExist2;     //ģ�嶨���ͨ��ͨ��\"%s\"������
	extern CString g_sLangTxt_CommunPathUnExist2;
	extern CString g_sLangID_CommunPathUnExist3;     //�ڵ�\"%s\"�����ͨ��ͨ��\"%s\"������
	extern CString g_sLangTxt_CommunPathUnExist3;
	extern CString g_sLangID_ProcessClose;     //----------����\"%s\"����----------
	extern CString g_sLangTxt_ProcessClose;
	extern CString g_sLangID_ProcessRun;     //����\"%s\"�Ѿ�����
	extern CString g_sLangTxt_ProcessRun;
	extern CString g_sLangID_PrtcPrcsDfn;     //��Լ���̶���
	extern CString g_sLangTxt_PrtcPrcsDfn;
	extern CString g_sLangID_PrtcTempName;     //��Լģ������
	extern CString g_sLangTxt_PrtcTempName;
	extern CString g_sLangID_PrtcTempDiff;     //��Լģ���ģ��ģʽ��%s�������ļ���ģ��ģʽ��%s����һ��
	extern CString g_sLangTxt_PrtcTempDiff;
	extern CString g_sLangID_DataBindRlship;     //���ݰ󶨹�ϵ��
	extern CString g_sLangTxt_DataBindRlship;
	extern CString g_sLangID_NoCorrespondingData;     //û�ж�Ӧ������
	extern CString g_sLangTxt_NoCorrespondingData;
	extern CString g_sLangID_LasterTestUnFinsh;     //    +++++++++++�ϴζ˿ڲ���û����: %s
	extern CString g_sLangTxt_LasterTestUnFinsh;
	extern CString g_sLangID_ChannelTest;     //ͨ�����ԣ��رղ���ͨ����ʱ%d
	extern CString g_sLangTxt_ChannelTest;
	extern CString g_sLangID_PointListEditor;     //���༭��PpDeviceModelEdit.dll������!
	extern CString g_sLangTxt_PointListEditor;
	extern CString g_sLangID_EditDevDataModel;     //[%s] ����������Ч����༭�豸����ģ��
	extern CString g_sLangTxt_EditDevDataModel;
	extern CString g_sLangID_ScriptCallError;     //�ű�����SetPkgLen���ô���:��Ӧ��ģ�岻����
	extern CString g_sLangTxt_ScriptCallError;
	extern CString g_sLangID_UnDefinScript;     //��ת�ڵ�\"%s\"û�ж���ű�
	extern CString g_sLangTxt_UnDefinScript;
	extern CString g_sLangID_NoJumpNode;     //[%s]����ת�ڵ�
	extern CString g_sLangTxt_NoJumpNode;
	extern CString g_sLangID_JumpNodeNoValue;     //��ת�ڵ�\"%s\"�ű���%s��û�з���ֵ��ʹ��\"return\"����
	extern CString g_sLangTxt_JumpNodeNoValue;
	extern CString g_sLangID_PrtcTempFileError;     //��Լģ���ļ�\"%s\"  ����
	extern CString g_sLangTxt_PrtcTempFileError;
	extern CString g_sLangID_CreatDevFail;     //�����豸����ʧ�ܣ��豸����ļ�\"%s\"����
	extern CString g_sLangTxt_CreatDevFail;
	extern CString g_sLangID_RptDataSetUnExist;     //Reset:�������ݼ������ڡ�%s��
	extern CString g_sLangTxt_RptDataSetUnExist;
	extern CString g_sLangID_RptDataSet;     //Reset:�������ݼ���%d��=>>0
	extern CString g_sLangTxt_RptDataSet;
	extern CString g_sLangID_ResetMessage;     //Reset:����ץ����%d��=>>0
	extern CString g_sLangTxt_ResetMessage;
	extern CString g_sLangID_ParaBoundsGet;     //GetBitInLong16����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsGet;
	extern CString g_sLangID_ParaBoundsSet;     //SetBitInLong16����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsSet;
	extern CString g_sLangID_ParaBoundsClear;     //ClearBitInLong16����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsClear;
	extern CString g_sLangID_ParaBoundsGet2;     //GetBitInLong32����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsGet2;
	extern CString g_sLangID_ParaBoundsSet2;     //SetBitInLong32����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsSet2;
	extern CString g_sLangID_ParaBoundsClear2;     //ClearBitInLong32����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsClear2;
	extern CString g_sLangID_ParaBoundsGet3;     //GetBitInLong8����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsGet3;
	extern CString g_sLangID_ParaBoundsSet3;     //SetBitInLong8����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsSet3;
	extern CString g_sLangID_ParaBoundsClear3;     //ClearBitInLong8����nBitIndex=%dԽ��
	extern CString g_sLangTxt_ParaBoundsClear3;
	extern CString g_sLangID_ParaBoundsGet4;     //script_GetBitRangeInLong8����nBitEnd=%dԽ��
	extern CString g_sLangTxt_ParaBoundsGet4;
	extern CString g_sLangID_DevDaraTmpFile;     //�豸����ģ���ļ������ڣ�%s
	extern CString g_sLangTxt_DevDaraTmpFile;
	extern CString g_sLangID_CommunSetFile;     //ͨѶ�����ļ������ڣ�%s
	extern CString g_sLangTxt_CommunSetFile;
	extern CString g_sLangID_DevDataPoint;     //�豸���ݵ��
	extern CString g_sLangTxt_DevDataPoint;
	extern CString g_sLangID_OpenSerialFail;     //�򿪴���%dʧ�ܣ�
	extern CString g_sLangTxt_OpenSerialFail;
	extern CString g_sLangID_ReceiveSerialFail;     //��ȡ��������ʧ�ܣ�
	extern CString g_sLangTxt_ReceiveSerialFail;
	extern CString g_sLangID_SetSerialError;     //���ô������Դ���
	extern CString g_sLangTxt_SetSerialError;
	extern CString g_sLangID_SendMessageFail;     //��\"%s\"���ͱ���ʧ��
	extern CString g_sLangTxt_SendMessageFail;

	extern CString g_sLangID_ExistSameName;     //����ͬ����UDP������(IP=%s  Port=%d)
	extern CString g_sLangTxt_ExistSameName;
	extern CString g_sLangID_ExistSameName2;     //����ͬ����TCP������(IP=%s  Port=%d)
	extern CString g_sLangTxt_ExistSameName2;
	extern CString g_sLangID_SendMessageFail2;     //��\"%s\"����BroadCast����ʧ��
	extern CString g_sLangTxt_SendMessageFail2;
	extern CString g_sLangID_ItemNumber;       //��Ŀ��
	extern CString g_sLangTxt_ItemNumber;

	extern CString g_sLangID_PointTableFile;//����ļ�(*.xml)|*.xml||
	extern CString g_sLangTxt_PointTableFile;

	extern CString g_sLangID_AddBytesBlock;
	extern CString g_sLangTxt_AddBytesBlock;
	extern CString g_sLangID_AddDataSets;
	extern CString g_sLangTxt_AddDataSets;
	extern CString g_sLangID_DataDef;
	extern CString g_sLangTxt_DataDef;
	extern CString g_sLangID_DataByteBlock;
	extern CString g_sLangTxt_DataByteBlock;
	extern CString g_sLangID_Length;//����
	extern CString g_sLangTxt_Length;
	extern CString g_sLangID_Byte;
	extern CString g_sLangTxt_Byte;
	extern CString g_sLangID_Msg;
	extern CString g_sLangTxt_Msg;
	extern CString g_sLangID_DataTypeValue;
	extern CString g_sLangTxt_DataTypeValue;
	extern CString g_sLangID_FrameVariDefin2;//��������
	extern CString g_sLangTxt_FrameVariDefin2;


	extern CString g_sLangID_CurrentActSet;//_T("sCurrentActSet");
	extern CString g_sLangTxt_CurrentActSet;//_T("��ǰ���ֵ��");
	extern CString g_sLangID_SettingTotalNo;//_T("sSettingTotalNo");
	extern CString g_sLangTxt_SettingTotalNo;//_T("��ֵ������");
	extern CString g_sLangID_CommandTotalTime;//_T("sCommandTotalTime");
	extern CString g_sLangTxt_CommandTotalTime;//_T("������ʱ��");
	extern CString g_sLangID_CommandExecuTime;//_T("sCommandExecuTime");
	extern CString g_sLangTxt_CommandExecuTime;//_T("����ִ��ʱ��");
	extern CString g_sLangID_CommandChoseTime;//_T("sCCommandChoseTime");
	extern CString g_sLangTxt_CommandChoseTime;//_T("����ѡ��ʱ��");
	extern CString g_sLangID_CommandExecuMess;//_T("sCommandExecuMess");
	extern CString g_sLangTxt_CommandExecuMess;//_T("����ִ����Ϣ");
	extern CString g_sLangID_CommandChoseMess;//_T("sCommandChoseMess");
	extern CString g_sLangTxt_CommandChoseMess;//_T("����ѡ����Ϣ");
	extern CString g_sLangID_WrongMess;//_T("sWrongMess");
	extern CString g_sLangTxt_WrongMess;//_T("������Ϣ");
	extern CString g_sLangID_RecordPath;//_T("sRecordPath");
	extern CString g_sLangTxt_RecordPath;//_T("¼��·��");
	extern CString g_sLangID_EnaChangeTime;//_T("sEnaChangeTime");
	extern CString g_sLangTxt_EnaChangeTime;//_T("ѹ���޸ļ��ʱ��");
	extern CString g_sLangID_EnaChoseTime;//_T("sEnaChoseTime");
	extern CString g_sLangTxt_EnaChoseTime;//_T("ѹ��ѡ��ִ�м��ʱ��");
	extern CString g_sLangID_MonitErrorTime;//_T("sMonitErrorTime");
	extern CString g_sLangTxt_MonitErrorTime;//_T("���Ӵ�����Ϣ");
	extern CString g_sLangID_BeforEnaRead;//_T("sBeforEnaRead");
	extern CString g_sLangTxt_BeforEnaRead;//_T("Ͷ��ѹ��ǰ��״̬");
	extern CString g_sLangID_BeforEnaReadTime;//_T("sBeforEnaReadTime");
	extern CString g_sLangTxt_BeforEnaReadTime;//_T("Ͷ��ѹ��ǰ��״̬����ʱ");

	extern CString g_sLangID_WritDataMess;//_T("sWritDataMess");
	extern CString g_sLangTxt_WritDataMess;//_T("д������Ϣ");
	extern CString g_sLangID_SetEdtTime;//_T("sSetEdtTime");
	extern CString g_sLangTxt_SetEdtTime;//_T("���ñ༭��ʱ��");
	extern CString g_sLangID_SetActTime;//_T("sSetActTime");
	extern CString g_sLangTxt_SetActTime;//_T("���û��ʱ��");
	extern CString g_sLangID_SetEdtMess;//_T("sSetEdtMess");
	extern CString g_sLangTxt_SetEdtMess;//_T("���ñ༭����Ϣ");
	extern CString g_sLangID_SetActMess;//_T("sSetActMess");
	extern CString g_sLangTxt_SetActMess;//_T("���û����Ϣ");
	extern CString g_sLangID_TestConnSta;//_T("sTestConnSta");
	extern CString g_sLangTxt_TestConnSta;//_T("��������״̬");
