/*
 *  goose_receiver_internal.h
 */

#ifndef GSP_GOOSE_RECEIVER_INTERNAL_H_
#define GSP_GOOSE_RECEIVER_INTERNAL_H_


#define ETH_BUFFER_LENGTH 1518
#define ETH_P_GOOSE 0x88b8
#ifndef DEBUG_GOOSE_SUBSCRIBER
#define DEBUG_GOOSE_SUBSCRIBER 0
#endif


struct sGspGooseSubscriber {
    char* goCBRef;
    int goCBRefLen;
    uint32_t timeAllowedToLive;
    uint32_t stNum;
    uint32_t sqNum;
    uint32_t confRev;
    MmsValue* timestamp;
    bool simulation;
    bool ndsCom;
    uint64_t invalidityTime;
    bool stateValid;
    uint8_t dstMac[6]; /* destination mac address */
    int32_t appId; /* APPID or -1 if APPID should be ignored */
    MmsValue* dataSetValues;
    bool dataSetValuesSelfAllocated;
    bool dstMacSet;
    GspGooseListener listener;
    void* listenerParameter;
};

#endif /* GSP_GOOSE_RECEIVER_INTERNAL_H_ */
