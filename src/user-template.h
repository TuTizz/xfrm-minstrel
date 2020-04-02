#ifndef USER_TEMPLATE_H
#define USER_TEMPLATE_H

#include "utils.h"

struct xfrmnl_user_tmpl* create_template(struct nl_addr *src_addr,
        struct nl_addr *dst_addr, int protocol, int mode);

#endif