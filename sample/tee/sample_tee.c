#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "tee_client_api.h"
#include "tee_client_id.h"


 /* example uuid */
static const TEEC_UUID EXAMPLE_uuid =
{ \
    0xffffffff, \
    0x0000, \
    0x0000, \
    { \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03 \
    } \
};

#define HELLO_CMD0 0
#define HELLO_CMD1 1

int main(void)
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_Result result;
    TEEC_Operation operation;
    uint32_t origin;
    char *str1 = "It's a nice day today!";
    char *str2 = "Let's enjoy the life!";

    result = TEEC_InitializeContext(NULL, &context);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("TEEC init failed\n");
        goto cleanup_1;
    }

    result = TEEC_OpenSession(&context, &session, &EXAMPLE_uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("Open session failed\n");
        goto cleanup_2;
    }

    operation.started = 1;
    operation.params[0].tmpref.buffer = str1;
    operation.params[0].tmpref.size = strlen(str1) + 1;

    operation.params[1].tmpref.buffer = str2;
    operation.params[1].tmpref.size = strlen(str2) + 1;
    operation.params[2].value.a = ':';
    operation.params[3].value.a = 0;

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,
                                            TEEC_MEMREF_TEMP_INPUT,
                                            TEEC_VALUE_INPUT,
                                            TEEC_VALUE_OUTPUT);

    result = TEEC_InvokeCommand(&session, HELLO_CMD0, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("Invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    result = TEEC_InvokeCommand(&session, HELLO_CMD1, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("Invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
   
    printf("The Secure World return %c%c\n", (char)(operation.params[2].value.a), (char)(operation.params[3].value.a));
    TEEC_CloseSession(&session);
cleanup_2:
    TEEC_FinalizeContext(&context);
cleanup_1:
    return 0;
}
