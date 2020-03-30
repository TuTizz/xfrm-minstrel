// source : https://croz.net/news/xfrm-programming/
#include <stdio.h>
#include <stdlib.h>
//#include <sys/socket.h>
//#include <linux/in.h>
#include <linux/xfrm.h>
#include <linux/ipsec.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <string.h>
#include "libnetlink.h"

int main() {
	struct rtnl_handle rth;
	struct {
		struct nlmsghdr                 n;
		struct xfrm_userpolicy_info     xpinfo;
		char                            buf[ 2048 ];
	} req;

	memset(&req, 0, sizeof(req));


	// nlmsghdr initialization
	req.n.nlmsg_len = NLMSG_LENGTH(sizeof(req.xpinfo));
	req.n.nlmsg_flags = NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
	req.n.nlmsg_type = XFRM_MSG_NEWPOLICY;

	// xfrm_userpolicy_info initialization
	req.xpinfo.sel.family = AF_INET;
	req.xpinfo.lft.soft_byte_limit = XFRM_INF;
	req.xpinfo.lft.hard_byte_limit = XFRM_INF;
	req.xpinfo.lft.soft_packet_limit = XFRM_INF;
	req.xpinfo.lft.hard_packet_limit = XFRM_INF;
	req.xpinfo.dir = XFRM_POLICY_IN;

	if (rtnl_open_byproto(&rth, 0, NETLINK_XFRM) < 0)
	   exit(1);

//if (rtnl_talk(&rth, &req.n, 0, 0, NULL, NULL, NULL) < 0)
	if (rtnl_talk(&rth, &req.n, NULL) < 0)
	   exit(2);

	rtnl_close(&rth);

	return 0;
}
