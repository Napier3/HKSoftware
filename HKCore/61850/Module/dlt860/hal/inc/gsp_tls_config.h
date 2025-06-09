/*
 * gsp_tls_config.h
 *
 * TLS Configuration API for protocol stacks using TCP/IP
 *
 * Copyright 2017-2018 MZ Automation GmbH
 *
 * Abstraction layer for configuration of different TLS implementations
 *
 */

#ifndef GSP_SRC_TLS_CONFIG_H_
#define GSP_SRC_TLS_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gsp_hal_base.h"

typedef struct sTLSConfiguration* GspTLSConfiguration;

PAL_API GspTLSConfiguration GspTLSConfiguration_create(void);

/* will be called by stack automatically when appropriate */
PAL_API void GspTLSConfiguration_setClientMode(GspTLSConfiguration self);

PAL_API void GspTLSConfiguration_setChainValidation(GspTLSConfiguration self, bool value);

PAL_API void GspTLSConfiguration_setAllowOnlyKnownCertificates(GspTLSConfiguration self, bool value);

PAL_API bool GspTLSConfiguration_setOwnCertificate(GspTLSConfiguration self, uint8_t* certificate, int certLen);

PAL_API bool GspTLSConfiguration_setOwnCertificateFromFile(GspTLSConfiguration self, const char* filename);

PAL_API bool GspTLSConfiguration_setOwnKey(GspTLSConfiguration self, uint8_t* key, int keyLen, const char* keyPassword);

PAL_API bool GspTLSConfiguration_setOwnKeyFromFile(GspTLSConfiguration self, const char* filename, const char* keyPassword);

PAL_API bool GspTLSConfiguration_addAllowedCertificate(GspTLSConfiguration self, uint8_t* certifcate, int certLen);

PAL_API bool GspTLSConfiguration_addAllowedCertificateFromFile(GspTLSConfiguration self, const char* filename);

PAL_API bool GspTLSConfiguration_addCACertificate(GspTLSConfiguration self, uint8_t* certifcate, int certLen);

PAL_API bool GspTLSConfiguration_addCACertificateFromFile(GspTLSConfiguration self, const char* filename);

PAL_API void GspTLSConfiguration_setRenegotiationTime(GspTLSConfiguration self, int timeInMs);

PAL_API void GspTLSConfiguration_destroy(GspTLSConfiguration self);


#ifdef __cplusplus
}
#endif

#endif /* GSP_SRC_TLS_CONFIG_H_ */
