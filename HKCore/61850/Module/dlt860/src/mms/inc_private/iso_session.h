/*
 *  ise_session.h
 */

#ifndef GSP_ISE_SESSION_H_
#define GSP_ISE_SESSION_H_

#include "byte_buffer.h"
#include "buffer_chain.h"
#include "gsp_iso_connection_parameters.h"

typedef struct {
	GspSSelector callingSessionSelector;
	GspSSelector calledSessionSelector;
	uint16_t sessionRequirement;
	uint8_t protocolOptions;
    GspByteBuffer userData;
} GspIsoSession;

typedef enum {
    GSP_SESSION_OK,
    GSP_SESSION_ERROR,
    GSP_SESSION_CONNECT,
    GSP_SESSION_GIVE_TOKEN,
    GSP_SESSION_DATA,
    GSP_SESSION_ABORT,
    GSP_SESSION_FINISH,
    GSP_SESSION_DISCONNECT,
    GSP_SESSION_NOT_FINISHED
} GspIsoSessionIndication;

LIB860_INTERNAL void GspIsoSession_init(GspIsoSession* session);

LIB860_INTERNAL GspByteBuffer* GspIsoSession_getUserData(GspIsoSession* session);

LIB860_INTERNAL void GspIsoSession_createConnectSpdu(GspIsoSession* self, GspIsoConnectionParameters isoParameters, BufferChain buffer, BufferChain payload);

LIB860_INTERNAL GspIsoSessionIndication GspIsoSession_parseMessage(GspIsoSession* session, GspByteBuffer* message);

LIB860_INTERNAL void GspIsoSession_createDataSpdu(GspIsoSession* session, BufferChain buffer, BufferChain payload);

LIB860_INTERNAL void GspIsoSession_createAcceptSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload);

LIB860_INTERNAL void GspIsoSession_createAbortSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload);

LIB860_INTERNAL void GspIsoSession_createFinishSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload);

LIB860_INTERNAL void GspIsoSession_createDisconnectSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload);

#endif /* ISE_SESSION_H_ */
