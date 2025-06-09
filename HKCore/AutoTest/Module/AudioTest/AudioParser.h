#ifndef _AUDIOPARSER_H_
#define _AUDIOPARSER_H_

#include "AudioListener.h"
#include "AudioConfigMngr.h"
#include "AudioCmdInterface.h"

//命令提取模块
class CAudioParser
{
//private:
public:
	CExBaseList m_oAudios;
	CAudioListener m_oListener;
	CAudioConfigMngr m_oConfigMngr;
	CAudioCmdInterface* m_pCmdInterface;

	CAudioData*			m_pAudioData;
	bool				m_bVoiceFlag;

private:
	
	CAudioData* Parse(CString strResult);
	void CreateQuestionTip(CString &strResult);
	void CreateStepKeyWord(int nKeyFlag,CString strOrderId);
	void CreateFinishQuestion(CString &strResult);

	void StepFuntion();
	void SetFlowFlag();

public:
	CAudioParser();
	virtual ~CAudioParser();
	bool CreateVoice(CString &strResult);
	BOOL Initialization(bool bEnableKey = false);
	void SetCurInterface(CAudioCmdInterface* pInterface);
	bool ParseWakeUp(CString strResult);
	void ParseResult();
	void DoFirstCmd();
	void DoFirstCmd(CAudioData* pData);
	void ClearAudios();

	int GetIsWirteLog(CString &strLogPath);

	bool FindResultIP(CString &strResult);
	//处理结果字符串 去掉结尾和开头的标点
	void DealResultString(CString& strResult);
	
};

#endif