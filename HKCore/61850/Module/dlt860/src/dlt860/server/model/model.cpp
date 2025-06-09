/*
 *  model.c
 */

#include "dlt860_model.h"

#include "stack_config.h"
#include "libdlt860_platform_includes.h"
#include "attributetype.h"

using namespace GSP;

static void
setAttributeValuesToNull(GspModelNode* node)
{
    if (node->modelType == GspDataAttributeModelType) {
        GspDataAttribute* da = (GspDataAttribute*) node;

        da->mmsValue = NULL;
    }

    GspModelNode* child = node->firstChild;

    while (child != NULL) {
        setAttributeValuesToNull(child);
        child = child->sibling;
    }
}

void
GspIedModel_setIedName(GspIedModel* self, const char* name)
{
    self->name = (char*) name;
}

void
GspIedModel_setAttributeValuesToNull(GspIedModel* iedModel)
{
    GspLogicalDevice* ld = iedModel->firstChild;

    while (ld != NULL) {

        GspLogicalNode* ln = (GspLogicalNode*) ld->firstChild;

        while (ln != NULL) {
            GspModelNode* node = ln->firstChild;

            while (node != NULL) {
                setAttributeValuesToNull(node);
                node = node->sibling;
            }

            ln = (GspLogicalNode*) ln->sibling;
        }

        ld = (GspLogicalDevice*) ld->sibling;
    }
}



int
GspIedModel_getLogicalDeviceCount(GspIedModel* self)
{
	if (self->firstChild == NULL)
		return 0;

	GspLogicalDevice* logicalDevice = self->firstChild;

	int ldCount = 1;

	while (logicalDevice->sibling != NULL) {
		logicalDevice = (GspLogicalDevice*) logicalDevice->sibling;
		ldCount++;
	}

	return ldCount;
}

GspDataSet*
GspIedModel_lookupDataSetFromModels(GspIedModel** self, const char *dataSetReference)
{
    while(*self)
    {
        auto ds = GspIedModel_lookupDataSet(*self, dataSetReference);
        if(ds)
        {
            return ds;
        }
        self = self + 1;
    }
    return nullptr;
}

GspDataSet*
GspIedModel_lookupDataSet(GspIedModel* self, const char* dataSetReference  /* e.g. ied1Inverter/LLN0$dataset1 */)
{
	GspDataSet* dataSet = self->dataSets;

	const char* separator = strchr(dataSetReference, '/');

	if (separator == NULL)
		return NULL;

	int ldNameLen = separator - dataSetReference;

	char domainName[65];

	int modelNameLen = strlen(self->name);

	memcpy(domainName, self->name, modelNameLen);

	while (dataSet != NULL) {

	    domainName[modelNameLen] = 0;

	    strncat(domainName, dataSet->logicalDeviceName, 64);

		if (strncmp(domainName, dataSetReference, ldNameLen) == 0) {
			if (strcmp(dataSet->name, separator + 1) == 0) {
				return dataSet;
			}
		}

		dataSet = dataSet->sibling;
	}

	return NULL;
}

GspLogicalDevice*
GspIedModel_getDevice(GspIedModel* self, const char* deviceName)
{
    GspLogicalDevice* device = self->firstChild;

    while (device != NULL) {

        char domainName[65];

        strncpy(domainName, self->name, 64);
        strncat(domainName, device->name, 64);

        if (strcmp(domainName, deviceName) == 0)
            return device;

        device = (GspLogicalDevice*) device->sibling;
    }

    return NULL;
}

GspLogicalDevice*
GspIedModel_getDeviceByInst(GspIedModel* self, const char* ldInst)
{
    GspLogicalDevice* device = self->firstChild;

    while (device != NULL) {

      if (strcmp(device->name, ldInst) == 0)
          return device;

      device = (GspLogicalDevice*) device->sibling;
    }

    return NULL;
}


GspLogicalDevice*
GspIedModel_getDeviceByIndex(GspIedModel* self, int index)
{
    GspLogicalDevice* logicalDevice = self->firstChild;

    int currentIndex = 0;

    while (logicalDevice) {

        if (currentIndex == index)
            return logicalDevice;

        currentIndex++;

        logicalDevice = (GspLogicalDevice*) logicalDevice->sibling;
    }

    return NULL;
}

static GspDataAttribute*
ModelNode_getDataAttributeByMmsValue(GspModelNode* self, GspMmsValue* value)
{
    GspModelNode* node = self->firstChild;

    while (node != NULL) {
        if (node->modelType == GspDataAttributeModelType) {
            GspDataAttribute* da = (GspDataAttribute*) node;

            if (da->mmsValue == value)
                return da;
        }

        GspDataAttribute* da = ModelNode_getDataAttributeByMmsValue(node, value);

        if (da != NULL)
            return da;

        node = node->sibling;
    }

    return NULL;
}

GspDataAttribute*
GspIedModel_lookupDataAttributeByMmsValue(GspIedModel* model, GspMmsValue* value)
{
    GspLogicalDevice* ld = model->firstChild;

    while (ld != NULL) {

        GspDataAttribute* da =
                ModelNode_getDataAttributeByMmsValue((GspModelNode*) ld, value);

        if (da != NULL)
            return da;


        ld = (GspLogicalDevice*) ld->sibling;
    }

    return NULL;
}

static GspModelNode*
getChildWithShortAddress(GspModelNode* node, uint32_t sAddr)
{
    GspModelNode* child;

    child = node->firstChild;

    while (child != NULL) {
        if (child->modelType == GspDataAttributeModelType) {
            GspDataAttribute* da = (GspDataAttribute*) child;

            if (da->sAddr == sAddr)
                return child;
        }

        GspModelNode* childChild = getChildWithShortAddress(child, sAddr);

        if (childChild != NULL)
            return childChild;

        child = child->sibling;
    }

    return NULL;
}

GspModelNode*
GspIedModel_getModelNodeByShortAddress(GspIedModel* model, uint32_t sAddr)
{
    GspModelNode* node = NULL;

    GspLogicalDevice* ld = (GspLogicalDevice*) model->firstChild;

    while (ld != NULL) {

        GspLogicalNode* ln = (GspLogicalNode*) ld->firstChild;

        while (ln != NULL) {

            GspModelNode* doNode = ln->firstChild;

            while (doNode != NULL) {
                GspModelNode* matchingNode = getChildWithShortAddress(doNode, sAddr);

                if (matchingNode != NULL)
                    return matchingNode;

                doNode = doNode->sibling;
            }

            ln = (GspLogicalNode*) ln->sibling;
        }

        ld = (GspLogicalDevice*) ld->sibling;
    }

    return node;
}

GspModelNode*
GspIedModel_getModelNodeByReference(GspIedModel* model, const char* objectReference, const char *fc)
{
    assert(strlen(objectReference) < 129);

    char objRef[130];

    strncpy(objRef, objectReference, 129);
    objRef[129] = 0;

    char* separator = strchr(objRef, '/');

    if (separator != NULL)
        *separator = 0;

    GspLogicalDevice* ld = GspIedModel_getDevice(model, objRef);

    if (ld == NULL) return NULL;

    if ((separator == NULL) || (*(separator + 1) == 0))
        return (GspModelNode*) ld;

    return GspModelNode_getChildWithFc((GspModelNode*) ld, separator + 1, GspFunctionalConstraint_fromString(fc));
}

GspModelNode*
GspIedModel_getModelNodeByObjectReference(GspIedModel* model, const char* objectReference)
{
    assert(strlen(objectReference) < 129);

    char objRef[130];

    strncpy(objRef, objectReference, 129);
    objRef[129] = 0;

    char* separator = strchr(objRef, '/');

    if (separator != NULL)
        *separator = 0;

    GspLogicalDevice* ld = GspIedModel_getDevice(model, objRef);

    if (ld == NULL) return NULL;

    if ((separator == NULL) || (*(separator + 1) == 0))
        return (GspModelNode*) ld;

    return GspModelNode_getChild((GspModelNode*) ld, separator + 1);
}

#if (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1)

SVControlBlock*
IedModel_getSVControlBlock(IedModel* self, LogicalNode* parentLN, const char* svcbName)
{
    SVControlBlock* retVal = NULL;

    SVControlBlock* svCb = self->svCBs;

    while (svCb != NULL) {
        if ((svCb->parent == parentLN) && (strcmp(svCb->name, svcbName) == 0)) {
            retVal = svCb;
            break;
        }


        svCb = svCb->sibling;
    }

    return retVal;
}

#endif /* (CONFIG_IEC61850_SAMPLED_VALUES_SUPPORT == 1) */

GspModelNode* GspIedModel_getModelNodeByShortObjectReference(GspIedModel* model, const char* objectReference)
{
    assert((strlen(model->name) + strlen(objectReference)) < 130);

    char objRef[130];

    strncpy(objRef, objectReference, 129);
    objRef[129] = 0;

    char* separator = strchr(objRef, '/');

    if (separator != NULL)
        *separator = 0;

    char ldName[65];
    strcpy(ldName, model->name);
    strcat(ldName, objRef);

    GspLogicalDevice* ld = GspIedModel_getDevice(model, ldName);

    if (ld == NULL) return NULL;

    if ((separator == NULL) || (*(separator + 1) == 0))
        return (GspModelNode*) ld;

    return GspModelNode_getChild((GspModelNode*) ld, separator + 1);
}


bool
GspDataObject_hasFCData(GspDataObject* dataObject, GspFunctionalConstraint fc)
{
	GspModelNode* modelNode = dataObject->firstChild;

	while (modelNode != NULL) {

		if (modelNode->modelType == GspDataAttributeModelType) {
			GspDataAttribute* dataAttribute = (GspDataAttribute*) modelNode;

			if (dataAttribute->fc == fc)
				return true;
		}
		else if (modelNode->modelType == GspDataObjectModelType) {

			if (GspDataObject_hasFCData((GspDataObject*) modelNode, fc))
				return true;
		}

		modelNode = modelNode->sibling;
	}

	return false;
}

bool
GspLogicalNode_hasFCData(GspLogicalNode* node, GspFunctionalConstraint fc)
{
	GspDataObject* dataObject = (GspDataObject*) node->firstChild;

	while (dataObject != NULL) {
		if (GspDataObject_hasFCData(dataObject, fc))
			return true;

		dataObject = (GspDataObject*) dataObject->sibling;
	}

	return false;
}

GspDataSet*
GspLogicalNode_getDataSet(GspLogicalNode* self, const char* dataSetName)
{
    assert(self->modelType == GspLogicalNodeModelType);
	assert(dataSetName != NULL);

	char dsName[66];

	GspLogicalDevice* ld = (GspLogicalDevice*) self->parent;

	if (strlen(dataSetName) > 32) {

		if (DEBUG_IED_SERVER) {
			printf("IED_SERVER: LogicalNode_getDataSet - data set name %s too long!\n", dataSetName);
		}

        return NULL;
	}

	StringUtils_createStringInBuffer(dsName, 3, self->name, "$", dataSetName);

	GspIedModel* iedModel = (GspIedModel*) ld->parent;

	GspDataSet* ds = iedModel->dataSets;

	while (ds != NULL) {
		if (strcmp(ds->logicalDeviceName, ld->name) == 0) {
			if (strcmp(ds->name, dsName) == 0) {
				return ds;
			}
		}

		ds = ds->sibling;
	}

	return NULL;
}

int
GspLogicalDevice_getLogicalNodeCount(GspLogicalDevice* logicalDevice)
{
	int lnCount = 0;

	GspLogicalNode* logicalNode = (GspLogicalNode*) logicalDevice->firstChild;

	while (logicalNode != NULL) {
		logicalNode = (GspLogicalNode*) logicalNode->sibling;
		lnCount++;
	}

	return lnCount;
}

GspModelNode*
GspLogicalDevice_getChildByMmsVariableName(GspLogicalDevice* logicalDevice, const char* mmsVariableName)
{


	char fcString[3];
	char nameRef[65];

	const char* separator = strchr(mmsVariableName,'$');

	if (separator == NULL)
		return NULL;

	if (strlen(separator) > 4) {
		fcString[0] = separator[1];
		fcString[1] = separator[2];
		fcString[2] = 0;

		const char* strpos = mmsVariableName;

		int targetPos = 0;

		while (strpos < separator) {
			nameRef[targetPos++] = strpos[0];
			strpos++;
		}

		nameRef[targetPos++] = '.';

		strpos = separator + 4;

		while (strpos[0] != 0) {
			nameRef[targetPos++] = strpos[0];
			strpos++;
		}

		nameRef[targetPos++] = 0;

		StringUtils_replace(nameRef, '$', '.');

		GspFunctionalConstraint fc = GspFunctionalConstraint_fromString(fcString);

		return GspModelNode_getChildWithFc((GspModelNode*) logicalDevice, nameRef, fc);
	}

	return NULL;
}

static int
createObjectReference(GspModelNode* node, char* objectReference)
{
    int bufPos;

    if (node->modelType != GspLogicalNodeModelType) {
        bufPos = createObjectReference(node->parent, objectReference);

        objectReference[bufPos++] = '.';
    }
    else {
        GspLogicalNode* lNode = (GspLogicalNode*) node;

        GspLogicalDevice* lDevice = (GspLogicalDevice*) lNode->parent;

        GspIedModel* iedModel = (GspIedModel*) lDevice->parent;

        bufPos = 0;

        int nameLength = strlen (iedModel->name) + strlen(lDevice->name);

        strncpy(objectReference, iedModel->name, 64);
        strncat(objectReference, lDevice->name, 64);

        bufPos += nameLength;

        objectReference[bufPos++] = '/';
    }

    /* append own name */
    int nameLength = strlen(node->name);

    int i;
    for (i = 0; i < nameLength; i++) {
        objectReference[bufPos++] = node->name[i];
    }

    return bufPos;
}

char*
GspModelNode_getObjectReference(GspModelNode* node, char* objectReference)
{
    if (objectReference == NULL)
        objectReference = (char*) GLOBAL_MALLOC(130);

    int bufPos = createObjectReference(node, objectReference);

    objectReference[bufPos] = 0;

    return objectReference;
}

string GspModelNode_getObjectReference(GspModelNode* node)
{
    char buf[130];
    GspModelNode_getObjectReference(node, buf);
    return string(buf);
}


int
GspModelNode_getChildCount(GspModelNode* modelNode) {
	int childCount = 0;

	GspModelNode* child = modelNode->firstChild;

	while (child != NULL) {
		childCount++;
		child = child->sibling;
	}

	return childCount;
}


GspModelNode*
GspModelNode_getChild(GspModelNode* self, const char* name)
{
   /* check for separator */
   const char* separator = strchr(name, '.');

   int nameElementLength = 0;

   if (separator != NULL)
       nameElementLength = (separator - name);
   else
       nameElementLength = strlen(name);

   GspModelNode* nextNode = self->firstChild;

   GspModelNode* matchingNode = NULL;

   while (nextNode != NULL) {
       int nodeNameLen = strlen(nextNode->name);

       if (nodeNameLen == nameElementLength) {
           if (memcmp(nextNode->name, name, nodeNameLen) == 0) {
               matchingNode = nextNode;
               break;
           }
       }

       nextNode = nextNode->sibling;
   }

   if ((separator != NULL) && (matchingNode != NULL)) {
       return GspModelNode_getChild(matchingNode, separator + 1);
   }
   else
       return matchingNode;
}

GspModelNode*
GspModelNode_getChildWithFc(GspModelNode* self, const char* name, GspFunctionalConstraint fc)
{
   /* check for separator */
   const char* separator = strchr(name, '.');

   int nameElementLength = 0;

   if (separator != NULL)
       nameElementLength = (separator - name);
   else
       nameElementLength = strlen(name);

   GspModelNode* nextNode = self->firstChild;

   GspModelNode* matchingNode = NULL;

   while (nextNode != NULL) {
       int nodeNameLen = strlen(nextNode->name);

       if (nodeNameLen == nameElementLength) {
           if (memcmp(nextNode->name, name, nodeNameLen) == 0) {

               if (separator == NULL) {
                   if (nextNode->modelType == GspDataAttributeModelType) {
                       GspDataAttribute* da = (GspDataAttribute*) nextNode;

                       if (da->fc == fc) {
                           matchingNode = nextNode;
                           break;
                       }
                   }
                   else
                   {
                       matchingNode = nextNode;
                       break;
                   }
               }
               else {

                   if (nextNode->modelType == GspDataAttributeModelType) {
                        GspDataAttribute* da = (GspDataAttribute*) nextNode;

                        if (da->fc == fc) {
                          matchingNode = nextNode;
                          break;
                        }
                   }
                   else {
                       matchingNode = nextNode;
                       break;
                   }

               }
           }
       }

       nextNode = nextNode->sibling;
   }

   if ((separator != NULL) && (matchingNode != NULL)) {
       return GspModelNode_getChildWithFc(matchingNode, separator + 1, fc);
   }
   else
       return matchingNode;
}

GspModelNodeType
GspModelNode_getType(GspModelNode* self)
{
    return self->modelType;
}

GspLogicalNode*
GspLogicalDevice_getLogicalNode(GspLogicalDevice* self, const char* nodeName)
{
    return (GspLogicalNode*) GspModelNode_getChild((GspModelNode*) self, nodeName);
}

GspSettingGroupControlBlock*
GspLogicalDevice_getSettingGroupControlBlock(GspLogicalDevice* self)
{
    GspIedModel* model = (GspIedModel*) self->parent;

    if (model == NULL)
        return NULL;

    GspLogicalNode* ln = GspLogicalDevice_getLogicalNode(self, "LLN0");

    if (ln == NULL) {
        if (DEBUG_IED_SERVER)
            printf("IED_SERVER: logical node LLN0 not found!\n");

        return NULL;
    }

    GspSettingGroupControlBlock* sgcb = model->sgcbs;

    while (sgcb != NULL) {
        if (sgcb->parent == ln)
            return sgcb;

        sgcb = sgcb->sibling;
    }

    return NULL;
}

void GspDataObject_getFCDA(GspDataObject *self, GspFunctionalConstraint fc, vector<GspDataAttribute *> &daVec)
{
    GspModelNode* modelNode = self->firstChild;

    while (modelNode != nullptr) {

        if (modelNode->modelType == GspDataAttributeModelType) {
            GspDataAttribute* dataAttribute = (GspDataAttribute*) modelNode;

            if (dataAttribute->fc == fc)
            {
                daVec.push_back(dataAttribute);
            }
        }
        else if (modelNode->modelType == GspDataObjectModelType) {
            GspDataObject_getFCDA((GspDataObject*) modelNode, fc, daVec);
        }

        modelNode = modelNode->sibling;
    }
}


string GspIedModel_getDataTypeStr(int type)
{   
    return scd::AttributeType::toString((scd::AttributeType::TYPE)type);
}