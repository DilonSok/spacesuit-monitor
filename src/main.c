#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "app/app_init.h"

int main(void)
{
    printk("Space Suit Monitor boot\n");

    app_ctx_t ctx;
    int rc = app_init(&ctx);
    if (rc != 0) {
        printk("app_init failed: %d\n", rc);
        while (1) { k_sleep(K_SECONDS(1)); }
    }

    printk("app_init OK\n");

    while (1) {
        k_sleep(K_SECONDS(1));
    }
}