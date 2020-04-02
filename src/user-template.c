#include "user-template.h"

//Adrien : Il manque des paramètres mais il a surement raison, genre le spi...
struct xfrmnl_user_tmpl* create_template(struct nl_addr *src_addr, 
        struct nl_addr *dst_addr, int protocol, int mode){
	struct xfrmnl_user_tmpl* templ = xfrmnl_user_tmpl_alloc();
    if (templ != NULL) {
        xfrmnl_user_tmpl_set_daddr  (templ, dst_addr);
        xfrmnl_user_tmpl_set_saddr  (templ, src_addr);
        xfrmnl_user_tmpl_set_proto (templ, protocol);
        xfrmnl_user_tmpl_set_mode (templ, mode);
        xfrmnl_user_tmpl_set_aalgos (templ, -1);
        xfrmnl_user_tmpl_set_ealgos (templ, -1);
        xfrmnl_user_tmpl_set_calgos (templ, -1);
    }
    else
    {
        printf ("ERROR in xfrmnl_user_tmpl_alloc\n");
        return NULL;
    }
    return templ;
}	