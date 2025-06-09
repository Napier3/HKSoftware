#ifndef _MqttCmmInterface_h_
#define _MqttCmmInterface_h_

#define MQTT_QOS_DEFAULT         0
#define MQTT_TIMEOUT_DEFAULT     2000L 

#include "../../SttStudio/Module/CmmInterface/SttCmmInterface.h"
#include "SttMqttTopicParser.h"

//Mqtt�¼��ӿ�
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
//��һ��Ӧ���У��ж��MQTT Client�˵���������ÿ���ͻ��˶���һ�����ӣ��ᵼ�����ӽ϶�
//��ˣ���ʱ���Ϊһ��Ӧ�ó���ֻ��һ��MQTT Client���ӣ�����ж��Ӧ�ù�����Ҫʹ��MQTT Client
//ͨ������˽��д���������һ�½ӿ�

//MQTT�¼�����ӿڣ���CMqttMsgInterface�������
class CMqttMsgProcessInterface
{
public:
	//�����յ���MQTT�������ƥ�䣬���ƥ��ɹ����򷵻�TRUE�����򷵻�FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser) = 0;
	//MQTT��Ϣ����
    virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser) = 0;
	
	//MQTT���ⶩ�Ľӿں�����MQTT Client���ӳɹ��󣬱�����CMqttMsgProcessInterface
	//������ص�����
    virtual BOOL MqttSubscribeTopic() = 0;
	
	//MQTTȡ�����ⶩ�Ľӿں�����MQTT Client�Ͽ����Ӻ󣬱�����CMqttMsgProcessInterface
	//Tȡ��������ص�����
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

