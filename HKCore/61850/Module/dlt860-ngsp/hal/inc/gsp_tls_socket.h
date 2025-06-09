/*
 * gsp_tls_socket.h
 *
 * TLS socket API for protocol libraries using TCP/IP
 *
 * Copyright 2017-2018 Michael Zillgith, MZ Automation GmbH
 *
 * Abstraction layer for different TLS implementations
 *
 * The implementation has to connect the TLS API layer with the socket API layer
 * and perform all TLS tasks like handshake, encryption/decryption.
 *
 */

#ifndef GSP_SRC_TLS_SOCKET_API_H_
#define GSP_SRC_TLS_SOCKET_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gsp_tls_config.h"
#include "gsp_hal_socket.h"

typedef struct sTLSSocket* GspTLSSocket;

PAL_API GspTLSSocket GspTLSSocket_create(GspSocket socket, GspTLSConfiguration configuration, bool storeClientCert);

PAL_API bool GspTLSSocket_performHandshake(GspTLSSocket self);

PAL_API uint8_t* GspTLSSocket_getPeerCertificate(GspTLSSocket self, int* certSize);

PAL_API int GspTLSSocket_read(GspTLSSocket self, uint8_t* buf, int size);

PAL_API int GspTLSSocket_write(GspTLSSocket self, uint8_t* buf, int size);

PAL_API void GspTLSSocket_close(GspTLSSocket self);

#ifdef __cplusplus
}
#endif

#endif /* GSP_SRC_TLS_SOCKET_API_H_ */
