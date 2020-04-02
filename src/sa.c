#include "sa.h"

int add_sa(struct nl_addr * src_addr,struct nl_addr * dst_addr, int spi,int mode,int protocol,int replay_window,struct xfrmnl_ltime_cfg* ltime_cfg, struct auth_params *auth, struct crypto_params *crypto){
	int err=0;
	int family = AF_INET;
	int flags = 0;	
	
	struct nl_sock *socket;
    socket = nl_socket_alloc();  
    if (0 != nl_connect(socket, NETLINK_XFRM)) {
        printf("ERROR on nl_connect\n");
        return -1;
    } 
        
    struct xfrmnl_sa *sa;
    sa = xfrmnl_sa_alloc();
    if (sa == NULL) {
        printf("ERROR on xfrmnl_sa_alloc\n");
        xfrmnl_sa_put(sa);
        return -1;
    }
    xfrmnl_sa_set_spi (sa, spi);
    xfrmnl_sa_set_proto (sa, protocol);
    xfrmnl_sa_set_mode(sa, mode);
    if (0 != xfrmnl_sa_set_daddr (sa, dst_addr)) {
        printf("ERROR in xfrmnl_sa_set_daddr_wan \n"); 
        return -1;   
    }
    if (0 != xfrmnl_sa_set_saddr (sa, src_addr)) {
        printf("ERROR in xfrmnl_sa_set_saddr_wan \n");   
        return -1; 
    }
    if (ltime_cfg == NULL){
        printf("ERROR in xfrm_ltime_cfg\n");
        return -1;
    }
    else
    	xfrmnl_sa_set_lifetime_cfg(sa, ltime_cfg);
    
    xfrmnl_sa_set_family(sa, family);
    xfrmnl_sa_set_replay_window(sa, replay_window);
    xfrmnl_sa_set_flags(sa, flags);

    if (0 != xfrmnl_sa_set_auth_params(sa, auth->auth_alg_name, auth->auth_key_len, auth->auth_trunc_len, auth->auth_key)) {
       printf("ERROR in  xfrmnl_sa_set_auth_params\n");
       return -1;
    }
    if (protocol != IPPROTO_AH){
		if (0 != xfrmnl_sa_set_crypto_params(sa, crypto->crypto_alg_name, crypto->crypto_key_len,  crypto->crypto_key)) {
		   printf("ERROR in  xfrmnl_sa_set_crypto_params\n");
		   return -1;
		}
	}
    err = xfrmnl_sa_add(socket, sa, NLM_F_CREATE);
    if (err < 0) {
        printf("ERROR in xfrm_sad_add\n");
        return -1;
    }
    xfrmnl_sa_put(sa);
    nl_close(socket);
	return 0;
}
