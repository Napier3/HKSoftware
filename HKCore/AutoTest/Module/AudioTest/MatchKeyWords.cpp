#include "StdAfx.h"
#include "MatchKeyWords.h"

CMatchKeyWords::CMatchKeyWords(void)
{
	m_lstOrderKeyWord = NULL;
	m_lstFlowKeyWord = NULL;
	m_lstKeyWord = NULL;
	m_lstTipKeyWord = NULL;

	m_pCurrentFlowWord = NULL;
	m_pCurrentTipWord = NULL;

	m_lstTempleteWords.clear();
}

CMatchKeyWords::~CMatchKeyWords(void)
{

}

//处理 结果状态
int CMatchKeyWords::DealResultFlag(tagVoiceFlag nWholeFlag,tagVoiceFlag nQuestionFlag,CString &strResult,CString &strOrderId,CString &strTipId)
{
	int nFlag = Flag_Error;
	switch(nWholeFlag)
	{
	//case Flag_Flow_NULL:
	case Flag_StarTest:
	case Flag_TestWait:
	case Flag_Question_ERROR:
	//case Flag_AnswerCustom:
		nFlag = MatchKeyWords(nWholeFlag,strResult,strOrderId,strTipId);
		break;
	case Flag_Flow_NULL:
	case Flag_Flow:
		nFlag = MatchFlowWords(nWholeFlag,strResult,strOrderId,strTipId);
		break;	
	case Flag_TipWord:
		nFlag = MatchTipWords(nWholeFlag,nQuestionFlag,strResult,strOrderId,strTipId);
		break;
	default:
		break;
	}

	return nFlag;
}

///////////////////////////////////////////////////////////////直接遍历
CAudioTipWord* CMatchKeyWords::GetCurrentTipWordPtr()
{
	if(m_pCurrentTipWord == NULL)
	{
		return NULL;
	}
	return m_pCurrentTipWord;
}

CAudioFlowWord* CMatchKeyWords::GetCurrenFlowWordPtr()
{
	if(m_pCurrentFlowWord == NULL)
	{
		return NULL;
	}
	return m_pCurrentFlowWord;
}

CExBaseList* CMatchKeyWords::GetOrderKeyWordList()
{
	return m_lstOrderKeyWord;
}

CExBaseList* CMatchKeyWords::GetFlowKeyWordList()
{
	return m_lstFlowKeyWord;
}

CExBaseList* CMatchKeyWords::GetKeyWordList()
{
	return m_lstKeyWord;
}

CExBaseList* CMatchKeyWords::GetTipKeyWordList()
{
	return m_lstTipKeyWord;
}

tagVoiceFlag CMatchKeyWords::MatchTipWords(tagVoiceFlag nWholeFlag,tagVoiceFlag nQuestionFlag,CString &strResult,CString &strOrderId,CString &strTipId)
{
	if(nQuestionFlag == Flag_AnswerConfirm || nQuestionFlag == Flag_AnswerCustom)
	{
		return MatchOrderWords(nWholeFlag,nQuestionFlag,strResult, strOrderId, strTipId);
	}
	//else if(nQuestionFlag == Flag_AnswerYse)
	else if(nQuestionFlag == Flag_AnswerFinish || nQuestionFlag == Flag_Answer_Success)
	{
		return MatchTipAnswer(strResult, strOrderId, strTipId);
	}
	strOrderId = QUESTION_ERROR_ORDERID;
	return Flag_Error;
}

tagVoiceFlag CMatchKeyWords::MatchTipAnswer(CString &strResult,CString &strOrderId,CString &strTipId)
{
	CExBaseList lstReplyWords;
	m_pCurrentTipWord->SelectChildrenByClassIDEx(lstReplyWords,VWCLASSID_CAUDIOREPLYKEYWORD);

	int nSize = lstReplyWords.GetCount();
	if(nSize <= 0)
	{
		lstReplyWords.RemoveAll();
		strOrderId = m_pCurrentTipWord->m_strOrder_Word_Id;
		return Flag_Question_ERROR;
	}

	if(m_pCurrentTipWord->m_strID == "SetIP")
	{
		lstReplyWords.RemoveAll();
		strOrderId = m_pCurrentTipWord->m_strOrder_Word_Id;
		return Flag_AnswerCustom;
	}

	if(m_pCurrentTipWord->m_strID == "TestModel")
	{
		int nCount = 0;
		list<CString>::iterator it;
		for(it = m_lstTempleteWords.begin();it != m_lstTempleteWords.end();it++)
		{
			CString strTemp = *it;
			if(strResult.Find(strTemp) >= 0)
			{
				strOrderId = m_pCurrentTipWord->m_strOrder_Word_Id;
				strTipId = "";
				strResult = strTemp + ".gbxml";
				lstReplyWords.RemoveAll();
				return Flag_Answer_Success;
			}//反向查找，在列表答案中 能找到语音输入的词，可以有多个
			else if(strTemp.Find(strResult) >= 0)
			{
				nCount++;
			}
		}
		if(nCount == 1)
		{
			strOrderId = m_pCurrentTipWord->m_strOrder_Word_Id;
			strTipId = "";
			lstReplyWords.RemoveAll();
			return Flag_Answer_Success;
		}
		strOrderId = QUESTION_ERROR_ORDERID;
		if(nCount > 1)
		{
			strOrderId = QUESTION_TEMPLETE_ORDERID;
		}
		lstReplyWords.RemoveAll();
		return Flag_Question_ERROR;
	}
	
	int nFalg = 0;
	POS posHead = lstReplyWords.GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioReplyKeyWord* pWord = (CAudioReplyKeyWord*)lstReplyWords.GetNext(posHead);
		if(strResult.Find(pWord->m_strValue,0) >= 0)
		{
			strOrderId = m_pCurrentTipWord->m_strOrder_Word_Id;
			strTipId = "";
			//strTipId = m_pCurrentTipWord->m_strTip_Word_Id;
			//下一步 确认答案后才能 进行下一步的问答
			//GetCurrentTipWord(m_pCurrentTipWord->m_strTip_Word_Id,Flag_Answer_Success);
			//将结果输入文字  替换成匹配的答案
			strResult = pWord->m_strValue;
			lstReplyWords.RemoveAll();
			return Flag_Answer_Success;
		}
	}

	lstReplyWords.RemoveAll();
	strOrderId = QUESTION_ERROR_ORDERID;
	return Flag_Question_ERROR;
}

tagVoiceFlag CMatchKeyWords::MatchFlowWords(tagVoiceFlag nWholeFlag,CString &strResult,CString &strOrderId,CString &strTipId)
{
	if((nWholeFlag != Flag_Flow) && (nWholeFlag != Flag_Flow_NULL))
	{
		strOrderId = FLOW_ORDERID;
		return nWholeFlag;
	}

	POS posHead = m_lstFlowKeyWord->GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioFlowWord* pFlowWord = (CAudioFlowWord*)m_lstFlowKeyWord->GetNext(posHead);
		if(MacthWords(pFlowWord,strResult) == Flag_Flow_OK)
		{
			m_pCurrentFlowWord = pFlowWord;
			strOrderId = pFlowWord->m_strOrder_Word_Id;
			if(pFlowWord->m_strID == "NewTest")
			{
				strTipId = pFlowWord->m_strTip_Word_Id;
				GetCurrentTipWord(strTipId,Flag_Flow_OK);
			}
			
			/*strTipId = pFlowWord->m_strTip_Word_Id;
			GetCurrentTipWord(strTipId,Flag_Flow_OK);*/
			return Flag_Flow_OK;
		}
	}

	strOrderId = FLOW_ORDERID;
	return Flag_Error;
}


tagVoiceFlag CMatchKeyWords::MacthWords(CAudioFlowWord* lstFlow,CString& strResult)
{
	CExBaseList lstBaseWords;
	lstFlow->SelectChildrenByClassIDEx(lstBaseWords,VWCLASSID_CAUDIOWORD);

	int nMatchFlag = 0;
	int nKeySize = 0;
	nKeySize = lstBaseWords.GetCount();

	POS posHead = lstBaseWords.GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioWord* pWord = (CAudioWord*)lstBaseWords.GetNext(posHead);
		if(strResult.Find(pWord->m_strValue,0) >= 0)
		{
			nMatchFlag += 1;
		}
	}
	if(nMatchFlag == nKeySize)
	{
		lstBaseWords.RemoveAll();
		return Flag_Flow_OK;
	}

	lstBaseWords.RemoveAll();
	return Flag_Error;
}

tagStepPageFlag CMatchKeyWords::MatchKeyWords(tagVoiceFlag nWholeFlag,CString &strResult,CString &strOrderId,CString &strTipId)
{
	POS posHead = m_lstKeyWord->GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioKeyWord* pWord = (CAudioKeyWord*)m_lstKeyWord->GetNext(posHead);
		if(strResult.Find(pWord->m_strValue,0) >= 0)
		{
			strOrderId = pWord->m_strOrder_Word_Id;
			strTipId = "";
			return GetStepFlag(pWord->m_strID);
		}
	}
	
	strOrderId = ERROR_ORDERID;
	return Step_NULL;
}

tagStepPageFlag CMatchKeyWords::GetStepFlag(CString strKeyWordId)
{
	if(strKeyWordId == "StopServer")
	{
		return StopServer;
	}
	else if(strKeyWordId == "StarServer")
	{
		return StarServer;
	}
	else if(strKeyWordId == "TestEnd")
	{
		return TestEnd;
	}
	else if(strKeyWordId == "TestStar")
	{
		return TestStar;
	}
	else if(strKeyWordId == "TestStop")
	{
		return TestStop;
	}
	else if(strKeyWordId == "TestProcessNext")
	{
		return TestProcessNext;
	}
	else if(strKeyWordId == "TestProcessUp")
	{
		return TestProcessUp;
	}
	else if(strKeyWordId == "TestProcessGo")
	{
		return TestProcessGo;
	}
	else if(strKeyWordId == "UpPage")
	{
		return UpPage;
	}
	else if(strKeyWordId == "NextPage")
	{
		return NextPage;
	}
	else if(strKeyWordId == "ReturnMain")
	{
		return ReturnMain;
	}
	else if(strKeyWordId == "StepOne")
	{
		return StepOne;
	}
	else if(strKeyWordId == "StepTwo")
	{
		return StepTwo;
	}
	else if(strKeyWordId == "StepThree")
	{
		return StepThree;
	}
	else if(strKeyWordId == "StepFour")
	{
		return StepFour;
	}
	else if(strKeyWordId == "StepFive")
	{
		return StepFive;
	}
	else if(strKeyWordId == "IP")
	{
		return FlagPingIP;
	}
	else
	{
		return Step_NULL;
	}
}

tagVoiceFlag CMatchKeyWords::MatchOrderWords(tagVoiceFlag nWholeFlag,tagVoiceFlag nQuestionFlag,CString &strResult,CString &strOrderId,CString &strTipId)
{
	POS posHead = m_lstOrderKeyWord->GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioOrderWord* pOrder = (CAudioOrderWord*)m_lstOrderKeyWord->GetNext(posHead);
		if(strResult.Find(pOrder->m_strValue,0) >= 0)
		{
			strOrderId = pOrder->m_strOrder_Word_Id;
			strTipId = "";
			if(pOrder->m_strFlag == ORDER_YES)
			{
				strOrderId = ANSWER_YES_ORDERID;
				return Flag_AnswerYse;
			}
			else if(pOrder->m_strFlag == ORDER_NO)
			{
				if(nQuestionFlag == Flag_AnswerCustom)
				{
					strOrderId = "30";
				}
				else
				{
					strOrderId = ANSWER_NO_ORDERID;
				}
				return Flag_AnswerNo;
			}
			else
			{
				strOrderId = ERROR_ORDERID;
				return Flag_Error;
			}
		}
	}
	strOrderId = ERROR_ORDERID;
	return Flag_Error;
}

void CMatchKeyWords::GetCurrentTipWord(CString& strTipId,tagVoiceFlag nWholeFlag)
{
	POS posHead = m_lstTipKeyWord->GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioTipWord* pTWord = (CAudioTipWord*)m_lstTipKeyWord->GetNext(posHead);
		if(pTWord->m_strID == strTipId)
		{
			if(pTWord->m_strID == "CheckType")
			{
				m_strPrevTipWordId = "";
			}
			else
			{
				m_strPrevTipWordId = m_pCurrentTipWord->m_strID;
			}
			m_pCurrentTipWord = pTWord;
			return;
		}
	}
}

void CMatchKeyWords::GetCurrentOrderWordValue(CString& strOrderId,CString& strValue)
{
	POS posHead = m_lstOrderKeyWord->GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioOrderWord* pOrderWord = (CAudioOrderWord*)m_lstOrderKeyWord->GetNext(posHead);
		if(pOrderWord->m_strID == strOrderId)
		{
			strValue = pOrderWord->m_strValue;
			return;
		}
	}
}

void CMatchKeyWords::GetCurrentTipWordValue(CString& strTipId,CString& strValue)
{
	if(m_pCurrentTipWord == NULL || strTipId.IsEmpty())
	{
		return;
	}

	if(strTipId == m_pCurrentTipWord->m_strID)
	{
		strValue = m_pCurrentTipWord->m_strValue;
	}
}

tagVoiceFlag CMatchKeyWords::MatchWakeUp(CString strResult,CString &strOrderId)
{
	POS posHead = m_lstKeyWord->GetHeadPosition();
	while(posHead != NULL)
	{
		CAudioKeyWord* pWord = (CAudioKeyWord*)m_lstKeyWord->GetNext(posHead);
		if((strResult.Find(pWord->m_strValue,0) >= 0) && (pWord->m_strID == "WakeUp"))
		{
			strOrderId = pWord->m_strOrder_Word_Id;
			return Flag_VoiceWakeUp;
		}
	}

	strOrderId = WAKEUP_ORDERID;
	return Flag_Error;
}
