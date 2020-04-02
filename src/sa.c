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
        printf("sa null\n");
        xfrmnl_sa_put(sa);
        return -1;
    }
    

    if (0 != xfrmnl_sa_set_spi (sa, spi)) {
        printf ("ERROR in xfrmnl_sa_set_spi\n");
        return -1;
    }  

    if (0 != xfrmnl_sa_set_proto (sa, protocol)) {
        printf ("ERROR in xfrmnl_sa_set_proto\n");
        return -1;
    }  
    
    if (0 != xfrmnl_sa_set_mode(sa, mode)) {
        printf("ERROR in xfrmnl_sa_set_mode\n");
        return -1;
    }

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
    }
    else
    	if (0 != xfrmnl_sa_set_lifetime_cfg(sa, ltime_cfg)) {
            printf("ERROR in xfrm_sa_set_lifetime_cfg\n");
            return -1;
        }
    
    if (0 != xfrmnl_sa_set_family(sa, family)) {
        printf("ERROR in xfrmnl_sa_set_family\n");
        return -1;
    }
    if (0 != xfrmnl_sa_set_replay_window(sa, replay_window)) {
        printf("ERROR in xfrmnl_sa_set_replay_window\n");
        return -1;
    }
    if (0 != xfrmnl_sa_set_flags(sa, flags)){
        printf("ERROR in xfrmnl_sa_set_flags\n");
        return -1;
    }

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
// char address[30];
// // sa *init_sa = NULL;

// sa_struct* createSA(void){

//     sa_struct *sa = (sa_struct*) malloc(sizeof(sa_struct));

//     sa->spi =0;
//     sa->seq_number = 0;
//     sa->state = 0;
//     sa->replay = 0;
//     sa->rule_number = 0;
//     sa->mode =0;
//     sa->satype=0;
//     sa->protocol_next_layer=0; 
//     sa->protocol = (char *) malloc(30); 
//     sa->srcport=0; 
//     sa->dstport=0; 
//     sa->src = (char *) malloc(sizeof(char) * strlen(address)); 
//     sa->dst = (char *) malloc(sizeof(char) * strlen(address));
//     sa->src_tunnel = (char *) malloc(sizeof(char) * strlen(address));
//     sa->dst_tunnel = (char *) malloc(sizeof(char) * strlen(address)); 
//     sa->auth_alg = 0;
//     sa->iv = 0;
//     sa->encrypt_alg = 0;
//     sa->encrypt_key = (char *) malloc(30); 
//     sa->auth_key = (char *) malloc(30); 
//     sa->combined_enc_intr = 0;
//     sa->lft_byte_hard = 0;
//     sa->lft_byte_soft = 0;
//     sa->lft_byte_current = 0;
//     sa->lft_packet_hard = 0;
//     sa->lft_packet_soft = 0;
//     sa->lft_packet_current = 0;
//     sa->lft_hard_add_expires_seconds = 0;
//     sa->lft_hard_use_expires_seconds = 0;
//     sa->lft_soft_add_expires_seconds = 0;
//     sa->lft_soft_use_expires_seconds = 0;
//     sa->lft_current_add_expires_seconds = 0;
//     sa->lft_current_use_expires_seconds = 0;
// //    sa->next=NULL;
    
//     return sa;

// }

