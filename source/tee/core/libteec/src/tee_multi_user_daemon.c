/*
 * FileName:
 * Author:         l00202565  Version: 0.0.1  Date: 2015-8-21
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> /*for errno*/
#include <fcntl.h>
#include <sys/types.h> /*for open close*/
#include <sys/stat.h>
#include <sys/ioctl.h> /*for ioctl*/
#include <sys/mman.h> /*for mmap*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <signal.h>
#include <sys/time.h>
#include <sys/mount.h>
#include <pthread.h>
#include <dirent.h>

//debug switch
#define LOG_NDEBUG 0
#define LOG_TAG "teecd"

#define BUF_MAX_SIZE 4096
#include <private/android_filesystem_config.h>
#include <cutils/sockets.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#include "tc_ns_client.h"
#include "tee_ca_daemon.h"

//symlink user0 when teecd init
static int symlink_user0(const char *oldpath, const char *newpath)
{
    int ret = 0;
    ret = symlink(oldpath, newpath);
    if (ret < 0) {
        if (NULL != strerror(errno))
            ALOGE("symlink file failed:errno=%d, err:%s\n",errno, strerror(errno));
        ALOGE("symlink user0 erro\n");
        return ret;
    } else {
        ret = chmod(newpath, S_IRUSR|S_IWUSR|S_IXUSR);
        if (ret < 0)
            ALOGE("chmod error");
        ret = chown(newpath, AID_SYSTEM, AID_SYSTEM);
        if (ret < 0)
            ALOGE("chown error");
    }
    return ret;
}

static int handle_notify(recv_msg_t* recvmsg)
{
    char username[64] = {0};
    int ret;
    int magic, status, userid;

    magic = recvmsg->magic;
    status = recvmsg->status;
    userid = recvmsg->userid;

    //TODO: add macro for magic, status, and userid validate value
    if ((magic == MU_MSG_MAGIC) && (status == MU_MSG_STAT_NEW_USER)) {
        //create user
        make_sec_storage_dir(SEC_STORAGE_DATA_USERS);
        symlink_user0(SEC_STORAGE_DATA_DIR, SEC_STORAGE_DATA_USER_0);
        snprintf(username, sizeof(username) - 1, "%s%d", SEC_STORAGE_DATA_USERS, userid);
        if (userid > MU_MSG_USERID_OWNER && userid < MU_MSG_USERID_MAX) {
            ret = make_sec_storage_dir(username);
            if (ret < 0) {
                ALOGE("mkdir fail ,ret=%d\n", ret);
                return ret;
            }
        } else {
            ALOGE("userid %d is not in the range\n", userid);
            return -1;
        }
    } else if ((magic == MU_MSG_MAGIC) && (status == MU_MSG_STAT_RM_USER)) {
        //delete user
        if (userid > MU_MSG_USERID_OWNER && userid < MU_MSG_USERID_MAX) {
            snprintf(username, sizeof(username) - 1, "%s%d", SEC_STORAGE_DATA_USERS, userid);
            ret = unlink_recursive(username);
            if (ret < 0) {
                ALOGE("rmdir fail ,ret=%d\n", ret);
                return ret;
            }
        } else {
            ALOGE("userid %d is not in the range\n", userid);
            return -1;
        }
    } else if ((magic == MU_MSG_MAGIC) && (status == MU_MSG_STAT_SWITCH_USER)) {
        //switch user
        ALOGE("swithc user cmd do not handle now\n");
    } else {
        //do nothing
        ALOGE("cmd no define to handle\n\n");
    }

    ALOGI("handle notify done\n");
    return 0;
}

void* thread_multi_user_server_work(void *dummy)
{
    int len, ret;
    recv_msg_t recvbuf;
    int mFrameworkSock;
    int mAcceptedConnection;
    struct sockaddr addr ;
    socklen_t alen;

    mFrameworkSock = android_get_control_socket(TEE_MULTIUSER_SOCKET_NAME);
    if (mFrameworkSock < 0){
        ALOGE("Obtaining file descriptor failed");
        if (NULL != strerror(errno))
            ALOGE("Obtaining file descriptor socket '%s' failed: %s : mFrameworkSock=%d : errno=%d",
                TEE_MULTIUSER_SOCKET_NAME, strerror(errno),mFrameworkSock,errno);

        pthread_exit(-1);
    }

    if (listen(mFrameworkSock, 1) < 0){
        ALOGE("Unable to listen");
        if (NULL != strerror(errno))
            ALOGE("Unable to listen on fd '%d' for socket '%s': %s",
                mFrameworkSock, TEE_MULTIUSER_SOCKET_NAME, strerror(errno));
        close(mFrameworkSock);
        pthread_exit(-1);
    }

    alen = sizeof(addr);
    memset(&addr, 0, alen);

    ALOGI("\n********* framework multi-user notify on socket successfully initialized *********\n");

    while(1) {
        if ((mAcceptedConnection = accept(mFrameworkSock, &addr, &alen)) < 0){
            ALOGE("Unable to accept \n");
            if (NULL != strerror(errno))
                ALOGE("Unable to accept framework connection (%s)", strerror(errno));
            pthread_exit(-1);
        }

        len = recv(mAcceptedConnection, (char*)(&recvbuf), sizeof(recv_msg_t), 0);
        if (len < 0) {
            ALOGE("socket '%s': receive message fail\n", TEE_MULTIUSER_SOCKET_NAME);
            goto close_socket;
        }
        ret = handle_notify(&recvbuf);
        if (ret < 0) {
            ALOGE("handle message erro %d\n", ret);
        }

close_socket:
        close(mAcceptedConnection);
    }

    pthread_exit(0);
    return NULL;
}
