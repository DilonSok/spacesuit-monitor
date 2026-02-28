#pragma once

#include "app/app_messages.h"

int app_ipc_publish(const app_msg_t *msg, k_timeout_t timeout);
int app_ipc_receive(app_msg_t *out, k_timeout_t timeout);