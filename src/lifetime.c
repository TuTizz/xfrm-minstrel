#include "lifetime.h"

struct xfrmnl_ltime_cfg* create_ltime_cfg(unsigned long long soft_bytelimit, 
		unsigned long long hard_bytelimit, unsigned long long soft_packetlimit, 
		unsigned long long hard_packetlimit, unsigned long long soft_addexpires, 
		unsigned long long hard_addexpires, unsigned long long soft_useexpires, 
		unsigned long long hard_useexpires){
	struct xfrmnl_ltime_cfg* ltime_cfg = xfrmnl_ltime_cfg_alloc();
	if (ltime_cfg != NULL) {
		xfrmnl_ltime_cfg_set_soft_bytelimit (ltime_cfg, soft_bytelimit);
	    xfrmnl_ltime_cfg_set_hard_bytelimit (ltime_cfg, hard_bytelimit);
	    xfrmnl_ltime_cfg_set_soft_packetlimit (ltime_cfg, soft_packetlimit);
	    xfrmnl_ltime_cfg_set_hard_packetlimit (ltime_cfg, hard_packetlimit);
	    xfrmnl_ltime_cfg_set_soft_addexpires (ltime_cfg, soft_addexpires);
	    xfrmnl_ltime_cfg_set_hard_addexpires (ltime_cfg, hard_addexpires);
	    xfrmnl_ltime_cfg_set_soft_useexpires (ltime_cfg, soft_useexpires);
	    xfrmnl_ltime_cfg_set_hard_useexpires (ltime_cfg, hard_useexpires);
   	}
    else {
        printf ("ERROR in xfrmnl_ltime_cfg_alloc\n");
		return NULL;

    }
   	return ltime_cfg;
}