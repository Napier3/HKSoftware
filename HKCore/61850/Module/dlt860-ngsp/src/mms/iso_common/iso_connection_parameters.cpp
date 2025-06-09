/*
 *  iso_connection_parameters.c
 */

#include "libdlt860_platform_includes.h"
#include "stack_config.h"
#include "gsp_iso_connection_parameters.h"

using namespace GSP;

GspAcseAuthenticationParameter GspAcseAuthenticationParameter_create()
{
    GspAcseAuthenticationParameter self = (GspAcseAuthenticationParameter) GLOBAL_CALLOC(1, sizeof(struct sGspAcseAuthenticationParameter));
    return self;
}

void GspAcseAuthenticationParameter_destroy(GspAcseAuthenticationParameter self)
{
    if (self->mechanism == GSP_ACSE_AUTH_PASSWORD)
        if (self->value.password.octetString != nullptr)
            GLOBAL_FREEMEM(self->value.password.octetString);
    GLOBAL_FREEMEM(self);
}

void GspAcseAuthenticationParameter_setPassword(GspAcseAuthenticationParameter self, char* password)
{
    self->value.password.octetString = (uint8_t*) StringUtils_copyString(password);
    self->value.password.passwordLength = strlen(password);
}

void GspAcseAuthenticationParameter_setAuthMechanism(GspAcseAuthenticationParameter self, GspAcseAuthenticationMechanism mechanism)
{
    self->mechanism = mechanism;
}


GspIsoConnectionParameters GspIsoConnectionParameters_create()
{
    GspIsoConnectionParameters self = (GspIsoConnectionParameters) GLOBAL_CALLOC(1, sizeof(struct sGspIsoConnectionParameters));
    return self;
}

void GspIsoConnectionParameters_destroy(GspIsoConnectionParameters self)
{
    GLOBAL_FREEMEM(self);
}

void
GspIsoConnectionParameters_setTlsConfiguration(GspIsoConnectionParameters self, GspTLSConfiguration tlsConfig)
{
#if (CONFIG_MMS_SUPPORT_TLS == 1)
    self->tlsConfiguration = tlsConfig;
#endif
}


void GspIsoConnectionParameters_setAcseAuthenticationParameter(GspIsoConnectionParameters self,
                                                          GspAcseAuthenticationParameter acseAuthParameter)
{
    self->acseAuthParameter = acseAuthParameter;
}

void GspIsoConnectionParameters_setTcpParameters(GspIsoConnectionParameters self, const char* hostname, int tcpPort)
{
    self->hostname = hostname;
    self->tcpPort = tcpPort;
}

void GspIsoConnectionParameters_setRemoteApTitle(GspIsoConnectionParameters self, const char* apTitle, int aeQualifier)
{
    if (apTitle == nullptr){
        self->remoteApTitleLen = 0;
    } else {
        self->remoteAEQualifier = aeQualifier;
    }
}

void GspIsoConnectionParameters_setRemoteAddresses(GspIsoConnectionParameters self, GspPSelector pSelector, GspSSelector sSelector, GspTSelector tSelector)
{
    self->remotePSelector = pSelector;
    self->remoteSSelector = sSelector;
    self->remoteTSelector = tSelector;
}


void GspIsoConnectionParameters_setLocalApTitle(GspIsoConnectionParameters self, const char* apTitle, int aeQualifier)
{
    if (apTitle == nullptr){
        self->localApTitleLen = 0;
    } else {
        self->localAEQualifier = aeQualifier;
    }
}

void GspIsoConnectionParameters_setLocalAddresses(GspIsoConnectionParameters self, GspPSelector pSelector, GspSSelector sSelector, GspTSelector tSelector)
{
    self->localPSelector = pSelector;
    self->localSSelector = sSelector;
    self->localTSelector = tSelector;
}
