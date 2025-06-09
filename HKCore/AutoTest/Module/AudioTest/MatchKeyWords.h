#pragma once

#include "AudioDef.h"
#include "Audio/AudioFlowWord.h"
#include "Audio/AudioTipWord.h"
#include "Audio/AudioKeyWord.h"
#include "Audio/AudioReplyKeyWord.h"
#include "Audio/AudioOrderWord.h"
#include <list>

using namespace std;

class CMatchKeyWords
{
public:
	//指针析构在CAudioConfigMngr中进行
	CExBaseList* m_lstOrderKeyWord;
	CExBaseList* m_lstFlowKeyWord;
	CExBaseList* m_lstKeyWord;
	CExBaseList* m_lstTipKeyWord;

	CMatchKeyWords(void);
	~CMatchKeyWords(void);

	CAudioTipWord* GetCurrentTipWordPtr();
	CAudioFlowWord* GetCurrenFlowWordPtr();

	CExBaseList* GetOrderKeyWordList();
	CExBaseList* GetFlowKeyWordList();
	CExBaseList* GetKeyWordList();
	CExBaseList* GetTipKeyWordList();

public:
	//处理 结果状态
	int DealResultFlag(tagVoiceFlag nWholeFlag,tagVoiceFlag nQuestionFlag,CString &strResult,CString &strOrderId,CString &strTipId);
	//关键词匹配
	tagVoiceFlag MatchTipWords(tagVoiceFlag nWholeFlag,tagVoiceFlag nQuestionFlag,CString &strResult,CString &strOrderId,CString &strTipId);
	tagVoiceFlag MatchTipAnswer(CString &strResult,CString &strOrderId,CString &strTipId);

	tagVoiceFlag MatchFlowWords(tagVoiceFlag nWholeFlag,CString &strResult,CString &strOrderId,CString &strTipId);
	tagVoiceFlag MacthWords(CAudioFlowWord* lstFlow,CString& strResult);

	tagStepPageFlag MatchKeyWords(tagVoiceFlag nWholeFlag,CString &strResult,CString &strOrderId,CString &strTipId);
	tagStepPageFlag GetStepFlag(CString strKeyWordId);
	tagVoiceFlag MatchOrderWords(tagVoiceFlag nWholeFlag,tagVoiceFlag nQuestionFlag,CString &strResult,CString &strOrderId,CString &strTipId);

	tagVoiceFlag MatchWakeUp(CString strResult,CString &strOrderId);

	void GetCurrentTipWord(CString& strTipId,tagVoiceFlag nWholeFlag);
	void GetCurrentOrderWordValue(CString& strOrderId,CString& strValue);
	void GetCurrentTipWordValue(CString& strTipId,CString& strValue);

public:
	CAudioTipWord*					m_pCurrentTipWord;//当前问题
	CAudioFlowWord*					m_pCurrentFlowWord;//当前流程
	CString							m_strPrevTipWordId; //当前问题的上一步问题的Id】

	list<CString>					m_lstTempleteWords;

};
