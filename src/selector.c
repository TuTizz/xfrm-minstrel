#include "selector.h"

/*Adrien : missing ifindex et userid*/
/* To understand what sportmask is, report to ts2ports function 
https://github.com/strongswan/strongswan/blob/master/src/libcharon/plugins/kernel_netlink/kernel_netlink_ipsec.c
*/
struct xfrmnl_sel* create_selector(struct nl_addr *src_addr, 
        struct nl_addr *dst_addr, int src_port, int dst_port, 
        int protocol){
	int family = AF_INET;
	struct xfrmnl_sel* selector = xfrmnl_sel_alloc();
    if (selector != NULL) {
        xfrmnl_sel_set_daddr (selector, dst_addr);
        xfrmnl_sel_set_saddr (selector, src_addr);
        xfrmnl_sel_set_prefixlen_d(selector, nl_addr_get_prefixlen(dst_addr));
        xfrmnl_sel_set_prefixlen_s(selector, nl_addr_get_prefixlen(src_addr));
        xfrmnl_sel_set_family (selector, family);
        xfrmnl_sel_set_sport (selector, src_port);
        xfrmnl_sel_set_dport (selector, dst_port);
        xfrmnl_sel_set_sportmask (selector, ~0);//single port
        xfrmnl_sel_set_dportmask (selector, ~0);//single port
        xfrmnl_sel_set_proto (selector, protocol);
    }
    else
    {
        printf ("ERROR in xfrmnl_sel_alloc\n");
        return NULL;
    }
	return selector;
}