#include "sp.h"


int add_sp(struct xfrmnl_sel* selector, struct xfrmnl_user_tmpl* templ, int direccion,int accion,struct xfrmnl_ltime_cfg* ltime_cfg){
	int err=0;
	int prioridad = 0;
	int family = AF_INET;

	struct nl_sock *socket;
    socket = nl_socket_alloc();  
    if (0 != nl_connect(socket, NETLINK_XFRM)) {
        printf("ERROR on nl_connect\n");
        return -1;
    } 

    struct xfrmnl_sp* sp =  xfrmnl_sp_alloc();
    
    if (ltime_cfg == NULL){
        printf("ERROR in xfrm_ltime_cfg\n");
    }
    else
    	if (0 != xfrmnl_sp_set_lifetime_cfg(sp, ltime_cfg)) {
            printf("ERROR in xfrm_sp_set_lifetime_cfg\n");
            return -1;
        }
    
    if (0 != xfrmnl_sp_set_priority (sp, prioridad)){
    	printf("ERROR in xfrmnl_sp_set_priority\n");
        return -1;
    }
    if (0 != xfrmnl_sp_set_sel (sp, selector)){
    	printf("ERROR in xfrmnl_sp_set_sel\n");
        return -1;
    }
    if (0 != xfrmnl_sp_set_action (sp, accion)){
    	printf("ERROR in xfrmnl_sp_set_action\n");
        return -1;
    }
    if (0 != xfrmnl_sp_set_dir (sp, direccion)){
    	printf("ERROR in xfrmnl_sp_set_dir\n");
        return -1;
    }
    
    
    xfrmnl_sp_add_usertemplate (sp, templ);
    
    
    if (0 != xfrmnl_sp_add(socket, sp, NLM_F_CREATE)){
    	printf("ERROR in xfrmnl_sp_add\n");
        return -1;
    }
    struct nl_cache * cachexfrm;
    xfrmnl_sp_alloc_cache(socket, &cachexfrm);
    
    struct xfrmnl_sp *sp_cacheado;
    int index = -1;
	for (sp_cacheado = (struct xfrmnl_sp*)nl_cache_get_first (cachexfrm);sp_cacheado != NULL;sp_cacheado = (struct xfrmnl_sp*)nl_cache_get_next ((struct nl_object*)sp_cacheado)) {
		int diff = xfrmnl_sel_cmp(xfrmnl_sp_get_sel(sp), xfrmnl_sp_get_sel(sp_cacheado));
		if ((xfrmnl_sp_get_dir(sp) == xfrmnl_sp_get_dir(sp_cacheado)) && (diff == 0)){ 
			index = xfrmnl_sp_get_index(sp_cacheado);
		}
		
	}
	nl_cache_put(cachexfrm);
    xfrmnl_sp_put(sp);
    xfrmnl_sp_put(sp_cacheado);
    nl_close(socket);
	return index;
}

// char address[30];

// sp_struct* createSPDnode(){
// 	sp_struct *sp = (sp_struct*) malloc(sizeof(sp_struct));
// 	sp->policy_id=0;
//     sp->index=0;
// 	sp->src = (char *) malloc(sizeof(char) * strlen(address)); 
// 	sp->dst = (char *) malloc(sizeof(char) * strlen(address));
// 	sp->src_tunnel = (char *) malloc(sizeof(char) * strlen(address));
// 	sp->dst_tunnel = (char *) malloc(sizeof(char) * strlen(address)); 
// 	sp->satype=0; 
//     sp->request_protocol = 0;
// 	sp->action_policy_type=0; 
// 	sp->policy_dir=0; 
// 	sp->protocol_next_layer=0; 
// 	sp->srcport=0; 
// 	sp->dstport=0; 
// 	sp->mode=0;
//     sp->lft_byte_hard = 0;
//     sp->lft_byte_soft = 0;
//     sp->lft_byte_current = 0;
//     sp->lft_packet_hard = 0;
//     sp->lft_packet_soft = 0;
//     sp->lft_packet_current = 0;
//     sp->lft_hard_add_expires_seconds = 0;
//     sp->lft_hard_use_expires_seconds = 0;
//     sp->lft_soft_add_expires_seconds = 0;
//     sp->lft_soft_use_expires_seconds = 0;
//     sp->lft_current_add_expires_seconds = 0;
//     sp->lft_current_use_expires_seconds = 0;
	
// 	// sp->next=NULL;
	
// 	return sp;

// }