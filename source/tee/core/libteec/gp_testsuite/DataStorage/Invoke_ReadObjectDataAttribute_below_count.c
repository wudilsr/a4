/*1PASS*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include "client_ds.h"

static TEEC_Session session;
static uint32_t origin;

void retrieveBufferFromUint32(uint32_t n, char *buffer)
{
   uint32_t i;
   for (i=0;i<4;i++)
    {
        buffer[i] = (n<<i*8)>>24;
    }
   return;
}

TEEC_Result Invoke_ReadObjectDataAttribute_below_count(TEEC_Context *context)
{
    TEEC_Result result; 
    TEEC_Operation operation;
    TEEC_SharedMemory shrdMem01, shrdMem02;
    uint32_t offset = 0;
    uint32_t OUT_ExpectedReturn = TEE_SUCCESS ;

    //allocate shared memory 
    shrdMem01.size = DS_BIG_SIZE;
    shrdMem01.flags = TEEC_MEM_OUTPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem01);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_ReadObjectDataAttribute_below_count: TEEC_AllocateSharedMemory shrdMem01 failed\n");
        goto error;
    }
    memset(shrdMem01.buffer, 0, shrdMem01.size);


    //config params
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_PARTIAL_OUTPUT,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.a = SHORTER_THAN_INITIAL ;
    operation.params[0].value.b = 0 ;
    
    operation.params[1].memref.parent = &shrdMem01;
    operation.params[1].memref.size = DS_BIG_SIZE;
    operation.params[1].memref.offset = OFFSET0 ;
    
    result = TEEC_InvokeCommand(&session, CMD_DS_ReadObjectData , &operation, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        printf("OUT_ExpectedReturn is 0x%x\n",OUT_ExpectedReturn);
        goto error1;
    }
    

    uint32_t cmp_count = 0;
    cmp_count = SHORTER_THAN_INITIAL>INITIAL_DATA_SIZE ? INITIAL_DATA_SIZE:SHORTER_THAN_INITIAL;
    if(strncmp(shrdMem01.buffer, INITIAL_DATA ,cmp_count))
    {
        printf("not same-------\n");
        result =-1;
        goto error;
    }
    result = TEEC_SUCCESS;
    
    error1:
         TEEC_ReleaseSharedMemory(&shrdMem01);
         
    error:
        return result;
}

int main(void)
{
    TEEC_Context context;
    TEEC_Result result;

    result = TEEC_InitializeContext(NULL, &context);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    result = TEEC_OpenSession(&context, &session, &EXAMPLE_uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    
    //start test
    if((result= Invoke_ReadObjectDataAttribute_below_count(&context)) != 0)   //CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28
    {
        TEEC_Error("Invoke_ReadObjectDataAttribute_below_count is failed!\n");
        goto error;
    }
    printf("Invoke_ReadObjectDataAttribute_below_count is successful!\n");

    TEEC_CloseSession(&session);
cleanup_2:
    TEEC_FinalizeContext(&context);
cleanup_1:
    return 0;
    error:
        TEEC_CloseSession(&session);
        TEEC_FinalizeContext(&context);
        return result;
}
