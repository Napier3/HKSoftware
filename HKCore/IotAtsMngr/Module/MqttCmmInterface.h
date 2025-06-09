#ifndef _MqttCmmInterface_h_
#define _MqttCmmInterface_h_

#define MQTT_QOS_DEFAULT         0
#define MQTT_TIMEOUT_DEFAULT     2000L 

#include "../../SttStudio/Module/CmmInterface/SttCmmInterface.h"
#include "SttMqttTopicParser.h"

//Mqtt事件接口
class CMqttMsgInterface
{
public://2021-7-16  lijunqing
	CMqttMsgInterface()				{}
	virtual ~CMqttMsgInterface()	{}

public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)	{	};
	virtual void OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser)	{	};

	virtual void OnMqttMsgRecieve(char *strTopic,char *pBuf,long nLen)
	{
		CSttMqttTopicParser oSttMqttTopicParser(strTopic);
		oSttMqttTopicParser.m_pMqttPkgBuffer = pBuf;
		oSttMqttTopicParser.m_nMqttPkgBufferLen = nLen;
		oSttMqttTopicParser.m_strTopic = strTopic;
		OnMqttMsgRecieve(oSttMqttTopicParser);
	};

	virtual void OnMqttDisconnected(char *pszErr) = 0;
};

//2023-4-10  lijunqing
//在一个应用中，有多个MQTT Client端的情况，如果每个客户端都有一个连接，会导致连接较多
//因此，暂时设计为一个应用程序，只有一个MQTT Client连接，如果有多个应用功能需要使用MQTT Client
//通过管理端进行处理，因此设计一下接口

//MQTT事件处理接口，共CMqttMsgInterface对象调用
class CMqttMsgProcessInterface
{
public:
	//根据收到的MQTT主题进行匹配，如果匹配成功，则返回TRUE，否则返回FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser) = 0;
	//MQTT消息处理
    virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser) = 0;
	
	//MQTT主题订阅接口函数：MQTT Client连接成功后，遍历各CMqttMsgProcessInterface
	//订阅相关的主题
    virtual BOOL MqttSubscribeTopic() = 0;
	
	//MQTT取消主题订阅接口函数：MQTT Client断开连接后，遍历各CMqttMsgProcessInterface
	//T取消订阅相关的主题
    virtual BOOL MqttUnSubscribeTopic() = 0;
};

class CMqttMsgProcessInterfaceMngr
{
public:
	CMqttMsgProcessInterfaceMngr()
	{
		
	}
	
	virtual ~CMqttMsgProcessInterfaceMngr()
	{
		m_listMqttMsgProcess.RemoveAll();
	}
	
protected:
	 CTLinkList<CMqttMsgProcessInterface> m_listMqttMsgProcess;
	 
	 	virtual CMqttMsgProcessInterface* MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser)
	 	{
            POS pos = m_listMqttMsgProcess.GetHeadPosition();
            CMqttMsgProcessInterface *p = NULL;

            while (pos != NULL)
            {
                p = m_listMqttMsgProcess.GetNext(pos);

                if (p->MqttMatch(oSttMqttTopicParser))
                {
                    return p;
                }
            }

            return NULL;
	 	}

public:
    virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser)
	{
        CMqttMsgProcessInterface *pFind = MqttMatch(oSttMqttTopicParser);

        if (pFind != NULL)
        {
            pFind->MqttMsgProcess(oSttMqttTopicParser);
        }
	}

     virtual BOOL MqttSubscribeTopic()
     {
         POS pos = m_listMqttMsgProcess.GetHeadPosition();
         CMqttMsgProcessInterface *p = NULL;

         while (pos != NULL)
         {
             p = m_listMqttMsgProcess.GetNext(pos);
             p->MqttSubscribeTopic();
         }

         return TRUE;
     }

     virtual BOOL MqttUnSubscribeTopic()
     {
         POS pos = m_listMqttMsgProcess.GetHeadPosition();
         CMqttMsgProcessInterface *p = NULL;

         while (pos != NULL)
         {
             p = m_listMqttMsgProcess.GetNext(pos);
             p->MqttUnSubscribeTopic();
         }

         return TRUE;
     }

     virtual void MqttAdd(CMqttMsgProcessInterface *p)
     {
		 if (m_listMqttMsgProcess.Find(p) == NULL)
		 {
			m_listMqttMsgProcess.AddTail(p);
			 p->MqttSubscribeTopic();
		}
     }
	 virtual void MqttRemove(CMqttMsgProcessInterface *p)
	 {
		 p->MqttUnSubscribeTopic();
		 m_listMqttMsgProcess.Remove(p);
	 }
};


#endif

