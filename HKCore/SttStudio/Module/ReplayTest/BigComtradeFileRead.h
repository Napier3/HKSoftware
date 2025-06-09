#ifndef _CBigComtradeFileRead_H_
#define _CBigComtradeFileRead_H_

#include "../../../Module/Record/Comtrade/ComtradeMngr.h"

#ifndef USE_Debug_BIG_ComtradeRead_Mode
#include "ComtradePlayConfig.h"
#endif

#include "ComtradeBufMngr.h"
#include "../../../Module/MemBuffer/BufferBase.h"

#define CMTRD_UPDATE_RAWTOREPLAY_ALL    0X000000F
#define CMTRD_UPDATE_RAWTOREPLAY_U		0X0000001
#define CMTRD_UPDATE_RAWTOREPLAY_I		0X0000002

#ifndef _Stt_Cmtrd_Save_File_
#define FILE_READBUF_SIZE	20*1024*1024		//���ļ������С20M
#else
#define FILE_READBUF_SIZE	20*1024*1024
#endif

#define USE_InsertComtradeFile_Mode   //��ֵ������ʹ���ļ���ʽ���������ʱ������ת��ʱ��ʵʱ��ֵ

class CBigComtradeFileRead
{
public:
	CBigComtradeFileRead();
	virtual ~CBigComtradeFileRead();

#ifdef USE_InsertComtradeFile_Mode
	CRcdComtradeFile* GetInsertComtradeFile(){return m_pInsertComtradeFile;}
#endif

	CRcdComtradeFile m_oSrcComtradeFile;	//����������ͨ����ԭʼ����
	double m_dInsertFreq;					//��ֵ��Ƶ��K3��ʵ�ʲ���Ƶ�ʣ���50KHz
	double m_fReplayStartTime;				//�ط���ͨ�����ݻ�������ʼʱ�䣬���ڻطŲ��λ�ͼ
	double m_fRawStartTime;					//m_pFileReadBuffer��ʼʱ�䣬����ԭʼ���λ�ͼ

	//cfg�ļ��в�������Ϣ
	float* m_pdSamRate; //��ͬ�Ĳ�����
	long* m_pnDataPoints;//��ͬ�������µĲ�������
	long m_nSamAmount;//�����ʵ�����
	BOOL m_bAnalysisFinish;					//�����ļ����ݽ���, zhouhj 2023.8.17 ������CComtradeSendSocket����
private:

#ifdef USE_InsertComtradeFile_Mode
	CRcdComtradeFile *m_pInsertComtradeFile;//����׼������ ,��ֵ֮���ComtradeFile
#else
	long m_nInsertTotalPoints;//��ǰ��ȡ�εģ�������ֵ�������ܲ�������
	double m_dInsertOffsetTime;//�ֳɶ�κ󣬲�ֵǰ���offsetʱ��
#endif

#ifndef USE_Debug_BIG_ComtradeRead_Mode
	CComtradePlayConfig *m_pComtradePlayConfigRef;//�������ö���,�����ط���ͨ�����ݻ���m_pReplayBuf
#endif

	CFile m_oFileRead;
	BOOL m_bIsBinaryMode;//true�ļ�Ϊbinaryģʽ��falseΪasciiģʽ
	CBufferBase m_oASII_ModeBuffer;
//	BOOL m_bHasOpenDataFile;//�ļ��Ƿ��Ѿ����򿪵ı�ʶ

	BYTE *m_pFileReadBuffer;				//���ļ���ȡ�Ļ����� 20M
	long m_nReplayBuffMaxLenth; //ReplayBuffMax��ÿ�����Ļ����С ��20M  ���ھݴ� ��ϵ�ǰ������ʵ��ͨ���� ����ʵ����Ҫ��ȡdata�ļ��Ĵ�С
	long m_nFileReadBufLen;					//�������С  ���ζ�ȡ��󻺴��С
//	double m_dInsertOffsetTime;//ΪSrc���ݵ�һ���㵽��ֵ�����ݵ�һ�����ʱ���
	long m_nReadBufDataLen;					//m_pFileReadBuffer���ݳ���
//	long m_nReadBufReadPos;

	BOOL m_bReadFileFinish;					//���ļ�����

	long m_nCurSrcBeginPointIndex;//�ط���ͨ�����ݻ���1����ʼ���������ڼ���ʱ�䣬��ǰm_oBigComtradeFile����ʼ�������ʵ��Comtrade�ļ���ʼ���Index����
	long m_nCurInsertBeginPointIndex;//��ǰ��ֵ�ο�ʼ�����ܵĲ�����ĵ������
	long m_nCurSrcIntervalPoints;//��ǰ���������е���
	long m_nCurIntervalDeliverPos;//��ʼ���Ժ󣬵�ǰ�δ��ݵ�λ��

	long m_nTotalPointsNum;//data�ļ��е��ܵĲ���������
	BOOL m_bAutoGenChABMap;//�Ƿ��Զ�����A\Bͨ��ӳ��(������������Զ�����,�Զ�����ͨ�����������������)

public:
	void SetAutoGenChABMap(BOOL bAutoGenChABMap){m_bAutoGenChABMap = bAutoGenChABMap;}
	BOOL GetAutoGenChABMap(){return m_bAutoGenChABMap;}
	BOOL GenerateComtradeChDataFromDataFile(BOOL bSeekToBegin,BOOL bResetCoef = TRUE);//ѭ����ȡBigComtrade�ļ�
	//����cfg�ļ��󣬳�ʼ��A\B\Kӳ���ϵ
	void InitChMapConfig();
	void RefreshChMapConfig();//�����ʼ��A\B\Kӳ���ϵ
	void UpdateChMapConfig();//���ڸ���CSttModuleChComtradeBind������ʹ�õ�ͨ��ӳ������
//	BOOL IsAnalogFinished(){return m_bAnalysisFinish;}
	void GenerateComtradeChDatas(BOOL bSeekToBegin);
	void ClearComtradeCfgFile();//20230815-wxy-���
	long GetTotalPointsNum();

protected:
	//��ʼ�����ļ�����
	void InitFileReadBuf(long nOnceReadFileLen);



	void InitSrcAnalogsBeginAng_SpecialSmpRate();//��ʼ���������Ƶ�ʵĳ�ʼ��λ ��Ҫ����ÿ���ܲ�1������������������

	BOOL GenerateComtradeChDataFromDataFile_BinaryMode(BOOL bSeekToBegin);//ѭ����ȡBigComtrade�ļ�
	BOOL GenerateComtradeChDataFromDataFile_ASIIMode(BOOL bSeekToBegin);//ѭ����ȡBigComtrade�ļ�

	//����m_pFileReadBuffer����ʣ�����ݣ����ļ������,��������AnalogData�У�����m_fRawStartTime,m_bReadFileFinish
	BOOL ReadBigComtradeDataFile(const CString &strComtradeFile);

	BOOL ReadBigDataAsBINARYMode(const CString& strComtradeFile);
	BOOL ReadBigDataAsASIIMode(const CString& strComtradeFile);

	long GetCurReadComtradePointsNum(double dInsertOffsetTime);//���ζ�ȡComtrde�ļ��ĵ���

	//��AnalogDataԭʼ���������ReplayBuf
	BOOL GenerateReplayBufFromRawData(UINT nUpdateMask = CMTRD_UPDATE_RAWTOREPLAY_ALL);

	//�ɻطŻ���ReplayBuf���AB����
	BOOL GenerateABBufFromReplayBuf(CComtradeDataBuffer *pABBuf);

	//�������ò�������λ�ļ������ݣ���������AnalogData��
	BOOL ReadLoopRawDataFile();

	void CloseReadFile();
	//ԭʼ���ݡ��ط��������
	void ResetDataBuf();

	void ClearTotalBuff();//������л��棬������ȡ��m_pFileReadBuffer���Լ������� ��ͬ�������µ��ܵ���
	void SetBigFileTotalSmpRates();//���������ļ��Ĳ����ʵ���Ա������
	void SetCurIntervalSmpRates();

	double CalCurRawStartTime();
	long CalSrcMaxSmpRateIntervalPoints();//����Դ�ļ��У������������£���Ҫ��ȡ���ܲ�����������֤ReplayBuff�����������
	double CalInsertOffsetTime();

public:
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	void AttachComtradePlayConfig(CComtradePlayConfig *pConfig){	m_pComtradePlayConfigRef = pConfig;	}
#endif
	
	BOOL IsAnalysisFinish()	{	return m_bAnalysisFinish;	}
	BOOL OpenComtradeFile(const CString &strComtradeFile,long nOnceReadFileLen,BOOL bInitDefault=TRUE);
	BOOL CheckComtradeFile(const CString &strComtradeFile);

	//��Comtrade�ļ������㲢��ʼ������
	BOOL OpenBigComtradeCfgFile(const CString &strComtradeFile,long nOnceReadFileLen);

	//��λ�ļ���һ�������LoopBuf����
	BOOL GenerateLoopBuf();

	//���ABBuf����
	BOOL GenerateABBuf(int nIndex);	

	//��ʼ����֮ǰ����ʼ��Loop\A\B����
	void BeginGenerateComtradeBuf(BOOL bResetCoef = TRUE);//2024-2-2 wuxinyi �޸�������ˢ��Ӳ������ʱ������m_dCoefValue �������Ӳ�����ʱ���α༭֮����ͼ����

	//��ȱ仯�󣬸���ReplayBuf�����ֵ
	void OnPTChanged();
	void OnCTChanged();

	//����(A-B)/K���Ƿ�ѡ�ı䣬��ӦReplayBufҲҪ���£������������¼������ֵ���������ֵ
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	BOOL UpdateChReplayBuf(CSttModuleChComtradeBind *pCh,CSttModuleComtradeBind *pModule,BOOL bSave=FALSE);
	BOOL UpdateChReplayBuf(int nModuleIndex,int nChIndex/*,BOOL bFromStart=FALSE*/);
#endif

	//2024-02-27 wuxinyi ���¿�����ͨ��
	BOOL UpdateBinaryChReplayBuf(CSttModuleComtradeBind *pModule);

//2024-01-08 wuxinyi ���α༭��ؽӿ�
public:
	BOOL InsertCyclePointsByRelTime(double dBeginTime, double dEndTime, double dInsertTime, int nCycleIndex);//����
	BOOL DeletePointsByRelTime(double dBeginTime, double dEndTime);//ɾ��
	BOOL InsertCyclePointsByPoint(long nBeginPoint, long nEndPoint, long nInserPoint, int nCycleIndex);//����	
	BOOL InsertNormalCyclePoints(double dVolValue,double dCurrentValue,double dTime_Second);
	

};


#endif