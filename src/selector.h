#ifndef SELECTOR_H
#define SELECTOR_H

#include "utils.h"

struct xfrmnl_sel* create_selector(struct nl_addr *src_addr, 
        struct nl_addr *dst_addr, int src_port, int dst_port, 
        int protocol);

#endif