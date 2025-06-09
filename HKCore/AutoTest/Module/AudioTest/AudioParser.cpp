#include "stdafx.h"
#include "AudioParser.h"

#include <sapi.h>
#include <sphelper.h>
#include "..\..\..\Module\Log\LogPrint.h"
#include "../../AudioTest/AudioTestDlg.h"

CAudioParser::CAudioParser()
{
	m_pCmdInterface = NULL;
	m_pAudioData = NULL;
	m_bVoiceFlag = false;
}

CAudioParser::~CAudioParser()
{
	//析构时退出监听器的消息循环
	/*m_oListener.m_bExited = true;
	while (m_oListener.m_bExited)
	{
		CTickCount32 event;
		event.DoEvents(10);
	}*/

	m_oAudios.DeleteAll();

	if(m_pAudioData)
	{
		m_pAudioData->DeleteAll();
		delete m_pAudioData;
		m_pAudioData = NULL;
	}
}

BOOL CAudioParser::Initialization(bool bEnableKey)
{
	//初始化配置
	if(!m_oConfigMngr.InitConfig())
	{
		return FALSE;
	}
	//初始化监听
	m_oListener.m_bEnableKey = bEnableKey;
	//if(bEnableKey)

	{
		CString strStartKey = m_oConfigMngr.GetConfigValue(CFG_STARTKEY);
		CString strStopKey = m_oConfigMngr.GetConfigValue(CFG_STOPKEY);
		CString strKeyWord = m_oConfigMngr.GetConfigValue(CFG_KEYWORD);
		CString strVoiceTime = m_oConfigMngr.GetConfigValue(CFG_VOICETIME);
		if(!m_oListener.SetupListener(strKeyWord, strStartKey, strStopKey,strVoiceTime))
		{
			return FALSE;
		}
	}
/*	else
	{
		if(!m_oListener.SetupListener())
		{
			return FALSE;
		}
	}*/

	m_oListener.setAudioParser(this);
	/*CString strEnableLog = m_oConfigMngr.GetConfigValue(CFG_ENABLELOG);
	if(strEnableLog == "1")
	{
		//初始化记录文件
		CString strLogFilePath = m_oConfigMngr.GetConfigValue(CFG_LOGPATH);
		//以下暂时不处理
	}*/

	m_pAudioData = new CAudioData();
	m_pAudioData->m_nFunctionFlag = Flow_NewTest;

	return TRUE;
}

void CAudioParser::SetCurInterface(CAudioCmdInterface* pInterface)
{
	m_pCmdInterface = pInterface;
}

void CAudioParser::DoFirstCmd()
{
	CAudioData* pHead = (CAudioData*)m_oAudios.GetHead();
	if(m_pCmdInterface && pHead)
	{
		m_pCmdInterface->DoCmd(pHead);
		m_oAudios.DeleteAt((long)0);
	}
}

void CAudioParser::DoFirstCmd(CAudioData* pData)
{
	//调用分发接口
	if(m_pCmdInterface && pData)
	{
		m_pCmdInterface->DoCmd(pData);
	}
}

void CAudioParser::ClearAudios()
{
	m_oListener.Clear();
	m_oAudios.DeleteAll();
}

bool CAudioParser::CreateVoice(CString &strResult)
{
	if(strResult.IsEmpty())
	{
		return false;
	}
	m_bVoiceFlag = true;

	USES_CONVERSION;
	LPCWSTR Temp = A2CW((LPCSTR)strResult);

	ISpVoice *pVoice = NULL;
	if(FAILED(::CoInitialize(NULL)))
	{
		m_bVoiceFlag = false;
		return false;
	}

	CString strLog = "【语音输入：】" + strResult;
	CLogPrint::LogString(XLOGLEVEL_INFOR,strLog);
	HRESULT hr = CoCreateInstance(CLSID_SpVoice,NULL,CLSCTX_ALL,IID_ISpVoice,(void**)&pVoice);
	if(SUCCEEDED(hr))
	{
		pVoice->SetVolume(50);
		pVoice->SetRate(0);
		hr = pVoice->Speak(Temp,0,NULL);

		pVoice->Release();
		pVoice = NULL;
	}
	::CoUninitialize();

	//CString strLog = "【语音输入：】" + strResult;
	//CLogPrint::LogString(XLOGLEVEL_INFOR,strLog);

	m_bVoiceFlag = false;
	return true;
}

void CAudioParser::CreateQuestionTip(CString &strResult)
{
	CString strTipId = "";
	CString strOrderId = "";
	CString strOrderValue = "";
	CString strTipValue = "";

	tagVoiceFlag nWholeFlag = m_oListener.m_nWholeFlag;
	tagVoiceFlag nTipFlag = m_oListener.m_nTipWordFlag;
	tagStepPageFlag nStepFlag = m_oListener.m_nSetpPageFlag;

	if(nTipFlag == Flag_AnswerFinish || nTipFlag == Flag_Answer_Success)//方便重复选择答案，替换选择的答案
	{
		nTipFlag = (tagVoiceFlag)m_oConfigMngr.m_oMatchWords.DealResultFlag(nWholeFlag,nTipFlag,strResult,strOrderId,strTipId);

		if(nTipFlag == Flag_Answer_Success)
		{
			m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
			//语音播报 加上答案
			strOrderValue += strResult;
			if(CreateVoice(strOrderValue))
			{
				//语音提示播报结束  主界面要显示日志  ToDo
				
				//匹配成功答案后 等待确认答案
				m_oListener.m_nTipWordFlag = Flag_Answer_Success;

				m_pAudioData->m_nStepFlag = Flag_Answer_Success;
				m_pAudioData->m_strResultMess = "";
				m_pAudioData->m_strResultMess = strResult;
				DoFirstCmd(m_pAudioData);
			}
			return;
		}
		else if(nTipFlag == Flag_AnswerCustom)
		{
			/*m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
			if(CreateVoice(strOrderValue))
			{
				//语音提示播报结束  主界面要显示日志  ToDo
				//匹配成功答案后 等待确认答案
				m_oListener.m_nTipWordFlag = Flag_AnswerCustom;
				m_pAudioData->m_nStepFlag = Flag_AnswerCustom;
				m_pAudioData->m_strResultMess = "";
				m_pAudioData->m_strResultMess = strResult;
				DoFirstCmd(m_pAudioData);
				return;
			}*/

			/*CString strCurrentIP = g_pAudioTestDlg->GetCurrentListText();
			if(strCurrentIP != "")
			{
				strResult = strCurrentIP;
			}*/

			if(FindResultIP(strResult))
			{
				m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
				m_oListener.m_nTipWordFlag = Flag_AnswerCustom;
				m_pAudioData->m_nStepFlag = Flag_AnswerCustom;
				m_pAudioData->m_strResultMess = "";
				m_pAudioData->m_strResultMess = strResult;
				DoFirstCmd(m_pAudioData);
			}
			else
			{
				CString strCurrentIP = g_pAudioTestDlg->GetCurrentListText();
				if(strCurrentIP != "")
				{
					strResult = strCurrentIP;
				}
				if(FindResultIP(strResult))
				{
					m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
					m_oListener.m_nTipWordFlag = Flag_AnswerCustom;
					m_pAudioData->m_nStepFlag = Flag_AnswerCustom;
					m_pAudioData->m_strResultMess = "";
					m_pAudioData->m_strResultMess = strResult;
					DoFirstCmd(m_pAudioData);
				}
				else
				{
					m_oListener.m_nTipWordFlag = Flag_TW_Question;
					strOrderValue = "IP输入错误，请重新输入";
				}

				//m_oListener.m_nTipWordFlag = Flag_TW_Question;
				//strOrderValue = "IP输入错误，请重新输入";
			}
			CreateVoice(strOrderValue);
			return;
		}
		else if(nTipFlag == Flag_Question_ERROR)
		{
			if(strOrderId == QUESTION_TEMPLETE_ORDERID)
			{
				//答案  命令 匹配失败
				m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
				CreateVoice(strOrderValue);
				//语音提示播报结束  主界面要显示日志  ToDo
				m_oListener.m_nTipWordFlag == Flag_TW_Question;	
				return;
			}

			nStepFlag = (tagStepPageFlag)m_oConfigMngr.m_oMatchWords.DealResultFlag(Flag_Question_ERROR,nTipFlag,strResult,strOrderId,strTipId);
			if(nStepFlag == Step_NULL)
			{
				//答案  命令 匹配失败
				m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
				CreateVoice(strOrderValue);
				//语音提示播报结束  主界面要显示日志  ToDo
				m_oListener.m_nTipWordFlag == Flag_TW_Question;	
			}
			else
			{
				m_oListener.m_nSetpPageFlag = nStepFlag;
				CreateStepKeyWord(nStepFlag,strOrderId);
			}
			return;
		}
	}
	else if(m_oListener.m_nTipWordFlag == Flag_Answer_Success || m_oListener.m_nTipWordFlag == Flag_TW_Question 
		|| m_oListener.m_nTipWordFlag == Flag_AnswerCustomConfirm)
	{
		nStepFlag = (tagStepPageFlag)m_oConfigMngr.m_oMatchWords.DealResultFlag(Flag_Question_ERROR,nTipFlag,strResult,strOrderId,strTipId);
		if(nStepFlag == Step_NULL)
		{
			//命令 匹配失败
			m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
			CreateVoice(strOrderValue);
			//语音提示播报结束  主界面要显示日志  ToDo
		}
		else
		{
			m_oListener.m_nSetpPageFlag = nStepFlag;
			CreateStepKeyWord(nStepFlag,strOrderId);
		}
		return;
	}
	else if(nTipFlag == Flag_AnswerConfirm || nTipFlag == Flag_AnswerCustom)
	{
		int nTipFlagConfirm = (tagVoiceFlag)m_oConfigMngr.m_oMatchWords.DealResultFlag(nWholeFlag,nTipFlag,strResult,strOrderId,strTipId);

		if(!strOrderId.IsEmpty())
		{
			m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
			CreateVoice(strOrderValue);
			//语音提示播报结束  主界面要显示日志  ToDo
		}

		if(nTipFlagConfirm == Flag_AnswerYse)
		{
			//保留参数
			m_pAudioData->m_nConfirmFlag = 1;
		}
		else if( nTipFlagConfirm == Flag_AnswerNo)
		{
			//不保留
			m_pAudioData->m_nConfirmFlag = 0;	

		}
		else if(nTipFlagConfirm == Flag_Error)
		{
			return;
		}
		
		//m_oListener.m_nTipWordFlag = Flag_AnswerConfirm;
		
		//处理功能
		if(nTipFlag == Flag_AnswerConfirm)
		{
			m_oListener.m_nTipWordFlag = Flag_TW_Question;
			if(nTipFlagConfirm == Flag_AnswerYse)
			{
				StepFuntion();
			}
			//StepFuntion();
		}
		else if(nTipFlag == Flag_AnswerCustom)
		{
			if(nTipFlagConfirm == Flag_AnswerNo)
			{
				m_oListener.m_nTipWordFlag = Flag_TW_Question;
			}
			else
			{
				m_oListener.m_nTipWordFlag = Flag_AnswerCustomConfirm;
			}
		}
	}
}

void CAudioParser::CreateStepKeyWord(int nKeyFlag,CString strOrderId)
{
	CString strOrderValue = "";
	if(!strOrderId.IsEmpty())
	{
		m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
	}
	switch(nKeyFlag)
	{
	case ReturnMain:
		break;
	case TestProcessUp:
	case TestProcessNext:
	case StepOne:
	case StepTwo:
	case StepThree:
	case StepFour:
	case StepFive:
		if(m_oListener.m_nWholeFlag == Flag_StarTest)
		{
			strOrderValue = _T("好的，正在进行下一步");
		}
		else
		{
			strOrderValue += g_pAudioTestDlg->GetCurrentListText();
			if(CreateVoice(strOrderValue))
			{
			//语音提示播报结束  主界面要显示日志  ToDo
				/*if(nKeyFlag == ReturnMain)
				{
					m_oListener.m_nWholeFlag = Flag_Flow;
					m_oListener.m_nTipWordFlag = Flag_Question_NULL;
					m_oListener.m_nSetpPageFlag = Step_NULL;
					//m_oListener.m_nVoiceListenFlag = Flag_VoiceWait;

					//Function  进行页面跳转 主界面 ToDo
				}
				else*/
				{
					m_oListener.m_nTipWordFlag = Flag_AnswerConfirm;
					return;
				}
			}
		}
		break;
	case UpPage:
	case NextPage:
		//Function  进行列表的翻页  ToDo
		break;
	case TestProcessGo:
		break;
	case TestStar:
		//CreateVoice(strOrderValue);
		m_oListener.m_nWholeFlag = Flag_StarTest;
		break;
	case TestEnd:
		//CreateVoice(strOrderValue);
		m_oListener.m_nWholeFlag = Flag_EndTest;
		break;
	case TestStop:
		//CreateVoice(strOrderValue);
		m_oListener.m_nWholeFlag = Flag_StopTest;
		break;
	case FlagPingIP:
		//CreateVoice(strOrderValue);
		break;
	default:
		break;
	}

	if(strOrderValue != "")
	{
		CreateVoice(strOrderValue);
	}
	m_pAudioData->m_nStepFlag = nKeyFlag;
	DoFirstCmd(m_pAudioData);
	
}

void CAudioParser::StepFuntion()
{
	CString strTipValue = "";
	CString strOrderValue = "";

	if(m_oListener.m_nSetpPageFlag == TestProcessUp)
	{
		if(m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId.IsEmpty())
		{
			//已经是当前第一步，没有上一步
			CString strStarStepOrder = STEP_STAR_ORDER;
			m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strStarStepOrder,strOrderValue);
			CreateVoice(strOrderValue);
			//语音提示播报结束  主界面要显示日志  ToDo

			return;
		}
		m_oConfigMngr.m_oMatchWords.GetCurrentTipWord(m_oConfigMngr.m_oMatchWords.m_strPrevTipWordId,Flag_TW_Question);
	}
	else if(m_oListener.m_nSetpPageFlag == TestProcessNext)
	{
		//已经是最后一步  没有下一步
		if(m_oConfigMngr.m_oMatchWords.m_pCurrentTipWord->m_strTip_Word_Id.IsEmpty())
		{
			CString strEndStepOrder = STEP_END_ORDER;
			m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strEndStepOrder,strOrderValue);
			CreateVoice(strOrderValue);
			//语音提示播报结束  主界面要显示日志  ToDo

			return;
		}
		m_oConfigMngr.m_oMatchWords.GetCurrentTipWord(m_oConfigMngr.m_oMatchWords.m_pCurrentTipWord->m_strTip_Word_Id,Flag_TW_Question);
	}
	
	m_oConfigMngr.m_oMatchWords.GetCurrentTipWordValue(m_oConfigMngr.m_oMatchWords.m_pCurrentTipWord->m_strID,strTipValue);

	//Function  进行页面跳转  ToDo
	m_pAudioData->m_nStepFlag = m_oListener.m_nSetpPageFlag;
	DoFirstCmd(m_pAudioData);

	CreateVoice(strTipValue);
	//语音提示播报结束  主界面要显示日志  ToDo
}

void CAudioParser::CreateFinishQuestion(CString &strResult)
{
	CString strTipId = "";
	CString strOrderId = "";
	CString strTipValue = "";
	CString strOrderValue = "";
	tagStepPageFlag nStepFlag = m_oListener.m_nSetpPageFlag;
	nStepFlag = (tagStepPageFlag)m_oConfigMngr.m_oMatchWords.DealResultFlag(Flag_Question_ERROR, m_oListener.m_nTipWordFlag,strResult,strOrderId,strTipId);
	if(nStepFlag == Step_NULL)
	{
		m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
		CreateVoice(strOrderValue);
		//语音提示播报结束  主界面要显示日志  ToDo
		return;
	}
	else
	{
		m_oListener.m_nSetpPageFlag = nStepFlag;
		CreateStepKeyWord(nStepFlag,strOrderId);
	}
}

bool CAudioParser::ParseWakeUp(CString strResult)
{
	CString strOrderId = "";
	CString strOrderValue = "";

	DealResultString(strResult);

	if(strResult.Find(g_pAudioListener->m_strKeyWord) != -1)
	{
		CString strLog = "【用户输入：】" + strResult;
		CLogPrint::LogString(XLOGLEVEL_INFOR,strLog);

		g_pAudioListener->m_bStartParse = true;
		g_pAudioListener->m_bEnableKey = false;
		g_pAudioTestDlg->UpdateState(true);
		
		CString strId = WAKEUP_ORDERID;
		m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strId,strOrderValue);
		CreateVoice(strOrderValue);

		g_pAudioTestDlg->StartAudioTimer();
		return true;
	}

	return false;
}

CAudioData* CAudioParser::Parse(CString strResult)
{
	if(strResult == "。" )
	{
		//断句处不用分析
		return NULL;
	}
	//用户语音输入结束   主界面要显示日志  ToDo
	CString strLog = "【用户输入：】" + strResult;
	CLogPrint::LogString(XLOGLEVEL_INFOR,strLog);

	CAudioData* pCmdData = NULL;
///////////////////////////////////////////////
	//strResult.Remove('，');
	//strResult.Remove('。');
	
 	CString strTipId = "";
 	CString strOrderId = "";
 	tagVoiceFlag nWholeFlag = m_oListener.m_nWholeFlag;
 
 	if(nWholeFlag == Flag_Flow || nWholeFlag == Flag_Flow_NULL)
 	{
 		CString strTipValue = "";
 		CString strOrderValue = "";
 
 		tagVoiceFlag nWholeFlag2 = (tagVoiceFlag)m_oConfigMngr.m_oMatchWords.DealResultFlag(nWholeFlag,Flag_Question_NULL,strResult,strOrderId,strTipId);
 		if(nWholeFlag2 == Flag_Flow_OK)
 		{
 			m_oListener.m_nWholeFlag = nWholeFlag2;
 			//为空放回 1
 			if(!strOrderId.IsEmpty())
 			{
 				m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
 				CreateVoice(strOrderValue);
				//语音提示播报结束  主界面要显示日志  ToDo

 			}
			//配置流程成功  
			//Function  进行页面跳转 第一个步骤 ToDo
			m_pAudioData->m_nStepFlag = Flag_Flow_OK;
			SetFlowFlag();
			DoFirstCmd(m_pAudioData);
			if(m_pAudioData->m_nFunctionFlag != Flow_NewTest)
			{
				m_oListener.m_nWholeFlag = Flag_Flow_OK;
				m_oListener.m_nTipWordFlag = Flag_Question_NULL;
				return pCmdData;
			}

 			if(!strTipId.IsEmpty())
 			{
 				m_oConfigMngr.m_oMatchWords.GetCurrentTipWordValue(strTipId,strTipValue);
 				if(CreateVoice(strTipValue))
 				{
					//语音提示播报结束  主界面要显示日志  ToDo
 					m_oListener.m_nWholeFlag = Flag_TipWord;
 					m_oListener.m_nTipWordFlag = Flag_TW_Question;
					return pCmdData;
 				}
 			}
 		}
 		else
 		{
 			m_oConfigMngr.m_oMatchWords.GetCurrentOrderWordValue(strOrderId,strOrderValue);
 			CreateVoice(strOrderValue);
			m_oListener.m_nTipWordFlag = Flag_Question_NULL;
			m_oListener.m_nWholeFlag = Flag_Flow;
			//语音提示播报结束  主界面要显示日志  ToDo
 		}
		return pCmdData;
 	}
 	else if(nWholeFlag == Flag_TipWord)
 	{
 		CreateQuestionTip(strResult);
 	}
	else if(nWholeFlag == Flag_TestWait 
		|| nWholeFlag == Flag_StarTest
		|| nWholeFlag == Flag_StopTest
		|| nWholeFlag == Flag_EndTest)
	{
		/*CString strLog = "Parse  ";
		CString str;
		str.Format("%d",nWholeFlag);
		CLogPrint::LogString(XLOGLEVEL_INFOR,strLog+str);*/

		CreateFinishQuestion(strResult);
	}//目前 除了新建 其他的 除了开始进入功能界面 可以用语音  进入功能界面后，目前手动操作，不可使用语音
	else if(nWholeFlag == Flag_Flow_OK)
	{
		if(m_pAudioData->m_nFunctionFlag != Flow_NewTest)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("【提示信息：】 新建测试以外，其他无法使用语音控制"));
			return pCmdData;
		}
	}
	
///////////////////////////////////////////////////////////
	return pCmdData;
}

void CAudioParser::SetFlowFlag()
{
	if(m_oConfigMngr.m_oMatchWords.m_pCurrentFlowWord->m_strID == "NewTest")
	{
		m_pAudioData->m_nFunctionFlag == Flow_NewTest;
	}
	else if(m_oConfigMngr.m_oMatchWords.m_pCurrentFlowWord->m_strID == "CheckRecord")
	{
		m_pAudioData->m_nFunctionFlag == Flow_CheckRecord;
	}
	else if(m_oConfigMngr.m_oMatchWords.m_pCurrentFlowWord->m_strID == "SetSystem")
	{
		m_pAudioData->m_nFunctionFlag == Flow_SetSystem;
	}
	else if(m_oConfigMngr.m_oMatchWords.m_pCurrentFlowWord->m_strID == "QuitSystem")
	{
		m_pAudioData->m_nFunctionFlag == Flow_QuitSystem;
	}
	else
	{
		m_pAudioData->m_nFunctionFlag == Flow_NewTest;
	}
}

void CAudioParser::ParseResult()
{
	CString strResult = "";

	std::vector<CString> vecTemp;
	m_oListener.MoveToBuffer(vecTemp);
	
	for(int  i = 0;i < vecTemp.size(); i++)
	{
		CString strBuffer = vecTemp[i];
		strResult += strBuffer;
	}

	if(strResult.IsEmpty())
	{
		return;
	}
	strResult = strResult.MakeUpper();

	DealResultString(strResult);
	CAudioData* pCmdData = Parse(strResult);
}

int CAudioParser::GetIsWirteLog(CString& strLogPath)
{
	int nFlag = 0;
	CString strIsLog = m_oConfigMngr.GetConfigValue(CFG_ENABLELOG);
	if(strIsLog == "1")
	{
		nFlag = 1;
		//strLogPath = m_oConfigMngr.GetConfigValue(CFG_LOGPATH);
		strLogPath = _P_GetConfigPath();
		strLogPath += "Audio/";
	}
	return nFlag;
}

bool CAudioParser::FindResultIP(CString &strResult)
{
	if(strResult == "")
	{
		return false;
	}

	//去除多余数据  截取字符
	int nFirstPos = strResult.FindOneOf("0123456789");
	strResult = strResult.Mid(nFirstPos);
	//192.168.193.144
	int nPosPoint1 = strResult.Find(".",0);
	int nPosPoint2 = strResult.Find(".",nPosPoint1+1);
	int nPosPoint3 = strResult.Find(".",nPosPoint2+1);
	if(nPosPoint1 == -1 || nPosPoint2 == -1 || nPosPoint3 == -1)
	{
		return false;
	}
	int nAllLen = strResult.GetLength();
	if(nAllLen < nPosPoint3+2)
	{
		return false;
	}
	if(nAllLen > nPosPoint3+4)
	{
		strResult = strResult.Mid(0,nPosPoint3+4);
	}
	//是否有中文或者其他
	CString strTempResult = strResult;
	strTempResult.TrimLeft("0123456789.");

	if(!strTempResult.IsEmpty())
	{
		return false;
	}
		
	//判断是否 是合法的IP  //192.168.193.144
	CString strNum1 = strResult.Mid(0,nPosPoint1);
	CString strNum2 = strResult.Mid(nPosPoint1+1,(nPosPoint2-nPosPoint1-1));
	CString strNum3 = strResult.Mid(nPosPoint2+1,(nPosPoint3-nPosPoint2-1));
	CString strNum4 = strResult.Mid(nPosPoint3+1);
	int nNum1 = _ttoi(strNum1);
	if(nNum1 < 1 && nNum1 > 255)
	{
		return false;
	}
	int nNum2 = _ttoi(strNum2);
	if(nNum2 < 1 && nNum2 > 255)
	{
		return false;
	}
	int nNum3 = _ttoi(strNum3);
	if(nNum3 < 1 && nNum3 > 255)
	{
		return false;
	}
	int nNum4 = _ttoi(strNum4);
	if(nNum4 < 1 && nNum4 > 254)
	{
		return false;
	}
	return true;
}

void CAudioParser::DealResultString(CString& strResult)
{
	CString strTemp1 = strResult.Mid(0,1);
	int nLen = strResult.GetLength();
	if(strTemp1 == "," || strTemp1 == ".")
	{
		strResult = strResult.Mid(1,(nLen-1));
		nLen--;
	}
	CString strTemp2 = strResult.Mid(0,2);
	if(strTemp2 == "，" || strTemp2 == "。")
	{
		strResult = strResult.Mid(2,(nLen-2));
		nLen -= 2;
	}
	CString strTemp3 = strResult.Right(1);
	if(strTemp3 == "," || strTemp3 == ".")
	{
		strResult = strResult.Mid(0,(nLen-1));
		nLen--;
	}
	CString strTemp4 = strResult.Right(2);
	if(strTemp4 == "，" || strTemp4 == "。")
	{
		strResult = strResult.Mid(0,(nLen-2));
	}
}