#ifndef UTILS_H
#define UTILS_H

#include <linux/socket.h>
#include <linux/xfrm.h>
#include <netlink/addr.h>
#include <netlink/cache.h>
#include <netlink/genl/genl.h>
#include <netlink/netlink.h>
#include <netlink/object.h>
#include <netlink/xfrm/ae.h>
#include <netlink/xfrm/lifetime.h>
#include <netlink/xfrm/sa.h>
#include <netlink/xfrm/selector.h>
#include <netlink/xfrm/sp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SUCCESS 0
#define FAIL -1

int get_mask(char * ip_mask);
struct nl_addr* create_nl_addr(char *addr);

#endif /* UTILS_H */