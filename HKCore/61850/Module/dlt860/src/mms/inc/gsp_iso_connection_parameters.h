/*
 *  gsp_iso_connection_parameters.h
 */

#ifndef GSP_ISO_CONNECTION_PARAMETERS_H_
#define GSP_ISO_CONNECTION_PARAMETERS_H_

#include "gsp_tls_config.h"
#include "libdlt860_common_api.h"
#include "gsp_mms_common.h"

typedef enum
{
    /** Neither ACSE nor TLS authentication used */
    GSP_ACSE_AUTH_NONE = 0,

    /** Use ACSE password for client authentication */
    GSP_ACSE_AUTH_PASSWORD = 1,

    /** Use ACSE certificate for client authentication */
    GSP_ACSE_AUTH_CERTIFICATE = 2,

    /** Use TLS certificate for client authentication */
    GSP_ACSE_AUTH_TLS = 3
} GspAcseAuthenticationMechanism;

typedef struct sGspAcseAuthenticationParameter* GspAcseAuthenticationParameter;

struct sGspAcseAuthenticationParameter
{
    GspAcseAuthenticationMechanism mechanism;

    union
    {
        struct
        {
            uint8_t* octetString;
            int passwordLength;
        } password;

        struct
        {
            uint8_t* buf;
            int length;
        } certificate;

    } value;
};

LIB860_API GspAcseAuthenticationParameter GspAcseAuthenticationParameter_create(void);

LIB860_API void GspAcseAuthenticationParameter_destroy(GspAcseAuthenticationParameter self);

LIB860_API void GspAcseAuthenticationParameter_setAuthMechanism(GspAcseAuthenticationParameter self, GspAcseAuthenticationMechanism mechanism);

LIB860_API void GspAcseAuthenticationParameter_setPassword(GspAcseAuthenticationParameter self, char* password);

typedef bool (*GspAcseAuthenticator)(void* parameter,
                                     GspAcseAuthenticationParameter authParameter,
                                     void** securityToken,
                                     GspIsoApplicationReference* appReference);

typedef struct {
    uint8_t size; /** 0 .. 4 - 0 means T-selector is not present */
    uint8_t value[4]; /** T-selector value */
} GspTSelector;

typedef struct {
    uint8_t size; /** 0 .. 16 - 0 means S-selector is not present */
    uint8_t value[16]; /** S-selector value */
} GspSSelector;

typedef struct {
    uint8_t size; /** 0 .. 16 - 0 means P-selector is not present */
    uint8_t value[16]; /** P-selector value */
} GspPSelector;

struct sGspIsoConnectionParameters
{
    GspAcseAuthenticationParameter acseAuthParameter;

#if (CONFIG_MMS_SUPPORT_TLS == 1)
    TLSConfiguration tlsConfiguration;
#endif

    const char* hostname;
    int tcpPort;

    uint8_t remoteApTitle[10];
    int remoteApTitleLen;
    int remoteAEQualifier;
    GspPSelector remotePSelector;
    GspSSelector remoteSSelector;
    GspTSelector remoteTSelector;

    uint8_t localApTitle[10];
    int localApTitleLen;
    int localAEQualifier;
    GspPSelector localPSelector;
    GspSSelector localSSelector;
    GspTSelector localTSelector;

};

typedef struct sGspIsoConnectionParameters* GspIsoConnectionParameters;

LIB860_API GspIsoConnectionParameters GspIsoConnectionParameters_create(void);

LIB860_API void GspIsoConnectionParameters_destroy(GspIsoConnectionParameters self);

LIB860_API void GspIsoConnectionParameters_setTlsConfiguration(GspIsoConnectionParameters self, GspTLSConfiguration tlsConfig);

LIB860_API void GspIsoConnectionParameters_setAcseAuthenticationParameter(GspIsoConnectionParameters self, GspAcseAuthenticationParameter acseAuthParameter);

LIB860_API void GspIsoConnectionParameters_setTcpParameters(GspIsoConnectionParameters self, const char* hostname, int tcpPort);

LIB860_API void GspIsoConnectionParameters_setRemoteApTitle(GspIsoConnectionParameters self, const char* apTitle, int aeQualifier);

LIB860_API void GspIsoConnectionParameters_setRemoteAddresses(GspIsoConnectionParameters self, GspPSelector pSelector, GspSSelector sSelector, GspTSelector tSelector);

LIB860_API void GspIsoConnectionParameters_setLocalApTitle(GspIsoConnectionParameters self, const char* apTitle, int aeQualifier);

LIB860_API void GspIsoConnectionParameters_setLocalAddresses(GspIsoConnectionParameters self, GspPSelector pSelector, GspSSelector sSelector, GspTSelector tSelector);

#endif /* GSP_ISO_CONNECTION_PARAMETERS_H_ */
