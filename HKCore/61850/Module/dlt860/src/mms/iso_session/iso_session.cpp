/*
 *  iso_session.c
 */

#include "libdlt860_platform_includes.h"
#include "stack_config.h"
#include "iso_session.h"
#include "buffer_chain.h"

#if ((DEBUG_ISO_SERVER == 1) || (DEBUG_ISO_CLIENT == 1))
#define DEBUG_SESSION 1
#else
#define DEBUG_SESSION 0
#endif

static int
parseAcceptParameters(GspIsoSession* session, GspByteBuffer* message, int startOffset, int parameterLength)
{
    uint8_t pi;
    uint8_t param_len;
    uint8_t param_val;
    uint8_t hasProtocolOptions = 0;
    uint8_t hasProtocolVersion = 0;
    int offset = startOffset;
    int maxOffset = offset + parameterLength;

    while (offset < maxOffset) {
        pi = message->buffer[offset++];
        param_len = message->buffer[offset++];

        switch (pi) {
        case 19: /* Protocol options */
            if (param_len != 1)
                return -1;
            session->protocolOptions = message->buffer[offset++];
            if (DEBUG_SESSION)
                printf("SESSION: Param - Protocol Options: %02x\n", session->protocolOptions);
            hasProtocolOptions = 1;
            break;
        case 21: /* TSDU Maximum Size */
            if (DEBUG_SESSION)
                printf("SESSION: Param - TODO TSDU Maximum Size\n");
            offset += 4;
            break;
        case 22: /* Version Number */
            param_val = message->buffer[offset++];
            if (DEBUG_SESSION)
                printf("SESSION: Param - Version number\n");
            if (param_val != 2)
                return -1;
            hasProtocolVersion = 1;
            break;
        case 23: /* Initial Serial Number */
            if (DEBUG_SESSION)
                printf("SESSION: Param - TODO Initial Serial Number\n");
            offset += param_len;
            break;
        case 26: /* Token Setting Item */
            param_val = message->buffer[offset++];
            if (DEBUG_SESSION)
                printf("SESSION: Param - Token Setting Item: %02x\n", param_val);
            break;
        case 55: /* Second Initial Serial Number */
            if (DEBUG_SESSION)
                printf("SESSION: Param - TODO Second Initial Serial Number\n");
            offset += param_len;
            break;
        case 56: /* Upper Limit Serial Number */
            if (DEBUG_SESSION)
                printf("SESSION: Param - TODO Upper Limit Serial Number\n");
            offset += param_len;
            break;
        case 57: /* Large Initial Serial Number */
            if (DEBUG_SESSION)
                printf("SESSION: Param - TODO Large Initial Serial Number\n");
            offset += param_len;
            break;
        case 58: /* Large Second Initial Serial Number */
            if (DEBUG_SESSION)
                printf("SESSION: Param - TODO Large Second Initial Serial Number\n");
            offset += param_len;
            break;
        default:
            if (DEBUG_SESSION)
                printf("SESSION: Param - Invalid Parameter with ID %02x\n", pi);
            break;
        }
    }

    if (hasProtocolOptions && hasProtocolVersion)
        return offset - startOffset;
    else
        return -1;
}

static GspIsoSessionIndication parseSessionHeaderParameters(GspIsoSession* session, GspByteBuffer* message, int parametersOctets)
{
    int offset = 2;
    uint8_t pgi;
    uint8_t parameterLength;

    while (offset < (parametersOctets + 2)) {
        pgi = message->buffer[offset++];
        parameterLength = message->buffer[offset++];

        switch (pgi) {
        case 1: /* Connection Identifier */
            if (DEBUG_SESSION)
                printf("SESSION: PGI - connection identifier\n");

            offset += parameterLength;
            break;
        case 5: /* Connection/Accept Item */
            if (DEBUG_SESSION)
                printf("SESSION: PGI - Connection/Accept Item\n");

            int connectAcceptLen;

            connectAcceptLen = parseAcceptParameters(session, message, offset, parameterLength);

            if (connectAcceptLen == -1)
                return GSP_SESSION_ERROR;

            offset += connectAcceptLen;
            break;
        case 17: /* Transport disconnect */
            offset += parameterLength;
            break;
        case 20: /* Session User Requirements */
            if (DEBUG_SESSION)
                printf("SESSION: Parameter - Session User Req\n");
            if (parameterLength != 2)
                return GSP_SESSION_ERROR;

            session->sessionRequirement = message->buffer[offset++] * 0x100;
            session->sessionRequirement += message->buffer[offset++];
            break;
        case 25: /* Enclosure item */
            offset += parameterLength;
            break;
        case 49:
            offset += parameterLength;
            break;
        case 51: /* Calling Session Selector */
            if (DEBUG_SESSION)
                printf("SESSION: Parameter - Calling Session Selector\n");

            if (parameterLength > 16)
                return GSP_SESSION_ERROR;

            {
                session->callingSessionSelector.size = parameterLength;

                int i;
                for (i = 0; i < session->callingSessionSelector.size; i++)
                    session->callingSessionSelector.value[i] = message->buffer[offset++];
            }

            break;
        case 52: /* Called Session Selector */
            if (DEBUG_SESSION)
                printf("SESSION: Parameter - Called Session Selector\n");

            if (parameterLength > 16)
                return GSP_SESSION_ERROR;

            {
               session->calledSessionSelector.size = parameterLength;

               int i;
               for (i = 0; i < session->calledSessionSelector.size; i++)
                   session->calledSessionSelector.value[i] = message->buffer[offset++];
            }

            break;
        case 60: /* Data Overflow */
            if (DEBUG_SESSION)
                printf("SESSION: Parameter - Data Overflow\n");
            offset += parameterLength;
            break;
        case 193: /* User Data */
            if (DEBUG_SESSION)
                printf("SESSION: PGI - user data\n");

            /* here we should return - the remaining data is for upper layers ! */
            GspByteBuffer_wrap(&session->userData, message->buffer + offset, message->size - offset, message->maxSize - offset);

            return GSP_SESSION_OK;

        case 194: /* Extended User Data */
            if (DEBUG_SESSION)
                printf("SESSION: PGI - extended user data\n");
            break;
        default:
            if (DEBUG_SESSION)
                printf("SESSION: invalid parameter/PGI\n");
            break;
        }
    }

    return GSP_SESSION_ERROR;
}

static const uint8_t dataSpdu[] = { 0x01, 0x00, 0x01, 0x00 };

void
GspIsoSession_createDataSpdu(GspIsoSession* session, BufferChain buffer, BufferChain payload)
{
    buffer->buffer = (uint8_t*) dataSpdu;
    buffer->partLength = 4;
    buffer->length = 4 + payload->length;
    buffer->nextPart = payload;
}

static int
encodeConnectAcceptItem(uint8_t* buf, int offset, uint8_t options)
{
    buf[offset++] = 5;
    buf[offset++] = 6;
    buf[offset++] = 0x13; /* Protocol Options */
    buf[offset++] = 1;
    buf[offset++] = options;
    buf[offset++] = 0x16; /* Version Number */
    buf[offset++] = 1;
    buf[offset++] = 2; /* Version = 2 */

    return offset;
}

static int
encodeSessionRequirement(GspIsoSession* self, uint8_t* buf, int offset)
{
    buf[offset++] = 0x14;
    buf[offset++] = 2;
    buf[offset++] = (uint8_t) (self->sessionRequirement / 0x100);
    buf[offset++] = (uint8_t) (self->sessionRequirement & 0x00ff);

    return offset;
}

static int
encodeCallingSessionSelector(GspIsoSession* self, uint8_t* buf, int offset)
{
    buf[offset++] = 0x33;
    buf[offset++] = self->callingSessionSelector.size;

    int i;
    for (i = 0; i < self->callingSessionSelector.size; i++)
        buf[offset++] = self->callingSessionSelector.value[i];

    return offset;
}

static int
encodeCalledSessionSelector(GspIsoSession* self, uint8_t* buf, int offset)
{
    buf[offset++] = 0x34;
    buf[offset++] = self->calledSessionSelector.size;

    int i;
    for (i = 0; i < self->calledSessionSelector.size; i++)
        buf[offset++] = self->calledSessionSelector.value[i];

    return offset;
}

static int
encodeSessionUserData(GspIsoSession* self, uint8_t* buf, int offset, uint8_t payloadLength)
{
    buf[offset++] = 0xc1;
    buf[offset++] = payloadLength;

    return offset;
}

void
GspIsoSession_createConnectSpdu(GspIsoSession* self, GspIsoConnectionParameters isoParameters, BufferChain buffer, BufferChain payload)
{
    int offset = 0;
    uint8_t* buf = buffer->buffer;
    int lengthOffset;

    buf[offset++] = 13; /* CONNECT SPDU */
    lengthOffset = offset;
    offset++; /* Skip byte for length - fill it later */

    self->calledSessionSelector = isoParameters->remoteSSelector;
    self->callingSessionSelector = isoParameters->localSSelector;

    offset = encodeConnectAcceptItem(buf, offset, 0);

    offset = encodeSessionRequirement(self, buf, offset);

    offset = encodeCallingSessionSelector(self, buf, offset);

    offset = encodeCalledSessionSelector(self, buf, offset);

    offset = encodeSessionUserData(self, buf, offset, payload->length);

    int spduLength = (offset - lengthOffset - 1) + payload->length;

    buf[lengthOffset] = spduLength;

    buffer->partLength = offset;
    buffer->length = offset + payload->length;
    buffer->nextPart = payload;
}

void
GspIsoSession_createAbortSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload)
{
    int offset = 0;
    uint8_t* buf = buffer->buffer;

    buf[offset++] = 25; /* ABORT-SPDU code */
    buf[offset++] = 5 + payload->length; /* LI */
    buf[offset++] = 17; /* PI-Code transport-disconnect */
    buf[offset++] = 1; /* LI = 1 */
    buf[offset++] = 11; /* transport-connection-released | user-abort | no-reason */
    buf[offset++] = 193; /* PGI-Code user data */
    buf[offset++] = payload->length; /* LI of user data */

    buffer->partLength = offset;
    buffer->length = payload->length + offset;
    buffer->nextPart = payload;
}

void
GspIsoSession_createFinishSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload)
{
    int offset = 0;
    uint8_t* buf = buffer->buffer;

    buf[offset++] = 9; /* FINISH-SPDU code */

    buf[offset++] = 2 + payload->length; /* LI */
    buf[offset++] = 193; /* PGI-Code user data */
    buf[offset++] = payload->length; /* LI of user data */

    buffer->partLength = offset;
    buffer->length = payload->length + offset;
    buffer->nextPart = payload;
}

void
GspIsoSession_createDisconnectSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload)
{
    int offset = 0;
    uint8_t* buf = buffer->buffer;

    buf[offset++] = 10; /* DISCONNECT-SPDU code */

    buf[offset++] = 2 + payload->length; /* LI */
    buf[offset++] = 193; /* PGI-Code user data */
    buf[offset++] = payload->length; /* LI of user data */

    buffer->partLength = offset;
    buffer->length = payload->length + offset;
    buffer->nextPart = payload;
}

void
GspIsoSession_createAcceptSpdu(GspIsoSession* self, BufferChain buffer, BufferChain payload)
{
    int offset = 0;
    uint8_t* buf = buffer->buffer;
    int lengthOffset;

    int payloadLength = payload->length;

    buf[offset++] = 14; /* ACCEPT SPDU */
    lengthOffset = offset;
    offset++;

    offset = encodeConnectAcceptItem(buf, offset, self->protocolOptions);

    offset = encodeSessionRequirement(self, buf, offset);

    offset = encodeCalledSessionSelector(self, buf, offset);

    offset = encodeSessionUserData(self, buf, offset, payloadLength);

    int spduLength = (offset - lengthOffset - 1) + payloadLength;

    buf[lengthOffset] = spduLength;

    buffer->partLength = offset;
    buffer->length = offset + payloadLength;
    buffer->nextPart = payload;
}

void
GspIsoSession_init(GspIsoSession* session)
{
    memset(session, 0, sizeof(GspIsoSession));
    session->sessionRequirement = 0x0002; /* default = duplex functional unit */

    session->callingSessionSelector.size = 2;
    session->callingSessionSelector.value[0] = 0;
    session->callingSessionSelector.value[1] = 1;

    session->calledSessionSelector.size = 2;
    session->calledSessionSelector.value[0] = 0;
    session->calledSessionSelector.value[1] = 1;
}

GspByteBuffer*
GspIsoSession_getUserData(GspIsoSession* session)
{
    return &session->userData;
}

GspIsoSessionIndication
GspIsoSession_parseMessage(GspIsoSession* session, GspByteBuffer* message)
{
    uint8_t* buffer = message->buffer;
    uint8_t id;
    uint8_t length;

    if (message->size > 1) {
        id = buffer[0];
        length = buffer[1];
    } else
        return GSP_SESSION_ERROR;

    switch (id) {
    case 13: /* CONNECT(CN) SPDU */
        if (length != (message->size - 2))
            return GSP_SESSION_ERROR;
        if (parseSessionHeaderParameters(session, message, length) == GSP_SESSION_OK)
            return GSP_SESSION_CONNECT;
        else {
            if (DEBUG_SESSION)
                printf("SESSION: error parsing connect spdu\n");
            return GSP_SESSION_ERROR;
        }
        break;
    case 14: /* ACCEPT SPDU */
        if (length != (message->size - 2))
            return GSP_SESSION_ERROR;
        if (parseSessionHeaderParameters(session, message, length) == GSP_SESSION_OK)
            return GSP_SESSION_CONNECT;
        else {
            if (DEBUG_SESSION)
                printf("SESSION: error parsing accept spdu\n");
            return GSP_SESSION_ERROR;
        }

        break;
    case 1: /* Give token / data SPDU */
        if (message->size < 4)
            return GSP_SESSION_ERROR;

        if ((length == 0) && (buffer[2] == 1) && (buffer[3] == 0)) {
            GspByteBuffer_wrap(&session->userData, message->buffer + 4, message->size - 4, message->maxSize - 4);

            return GSP_SESSION_DATA;
        }
        return GSP_SESSION_ERROR;

    case 8: /* NOT-FINISHED SPDU */
        return GSP_SESSION_NOT_FINISHED;

    case 9: /* FINISH SPDU */
        if (DEBUG_SESSION)
            printf("SESSION: recvd FINISH SPDU\n");

        if (length != (message->size - 2))
            return GSP_SESSION_ERROR;

        if (parseSessionHeaderParameters(session, message, length) == GSP_SESSION_OK)
            return GSP_SESSION_FINISH;
        else
            return GSP_SESSION_ERROR;

        break;

    case 10: /* DISCONNECT SPDU */
        if (DEBUG_SESSION)
            printf("SESSION: recvd DISCONNECT SPDU\n");

        if (length != (message->size - 2))
            return GSP_SESSION_ERROR;

        if (parseSessionHeaderParameters(session, message, length) == GSP_SESSION_OK)
            return GSP_SESSION_DISCONNECT;
        else
            return GSP_SESSION_ERROR;

        break;

    case 25: /* ABORT SPDU */
        return GSP_SESSION_ABORT;

    default:
        break;
    }

    return GSP_SESSION_ERROR;
}

