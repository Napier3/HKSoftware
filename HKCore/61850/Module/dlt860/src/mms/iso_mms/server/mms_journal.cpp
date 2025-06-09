/*
 *  mms_journal.c
 */

#include "libdlt860_platform_includes.h"
#include "mms_device_model.h"
#include "mms_server_internal.h"

GspMmsJournal
GspMmsJournal_create(const char* name)
{
    if (DEBUG_MMS_SERVER)
        printf("MMS_SERVER: create new journal %s\n", name);

    GspMmsJournal self = (GspMmsJournal) GLOBAL_MALLOC(sizeof(struct sGspMmsJournal));

    self->name = StringUtils_copyString(name);

    return self;
}

void
GspMmsJournal_destroy(GspMmsJournal self)
{
    GLOBAL_FREEMEM(self->name);
    GLOBAL_FREEMEM(self);
}
