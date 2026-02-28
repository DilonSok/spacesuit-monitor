#include <zephyr/kernel.h>
#include <errno.h>
#include "app/app_config.h"
#include "app/app_ipc.h"

K_MSGQ_DEFINE(g_app_msgq, sizeof(app_msg_t), APP_MSGQ_DEPTH, 4);

int app_ipc_publish(const app_msg_t *msg, k_timeout_t timeout) {
  if (msg == NULL) {
    return -EINVAL;
  }
  return k_msgq_put(&g_app_msgq, msg, timeout);
}

int app_ipc_receive(app_msg_t *out, k_timeout_t timeout) {
if (out == NULL) {
    return -EINVAL;
  }
  return k_msgq_get(&g_app_msgq, out, timeout);
}