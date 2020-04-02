#ifndef LIFETIME_H
#define LIFETIME_H

#include "utils.h"

struct xfrmnl_ltime_cfg* create_ltime_cfg(unsigned long long soft_bytelimit, 
        unsigned long long hard_bytelimit, unsigned long long soft_packetlimit, 
        unsigned long long hard_packetlimit, unsigned long long soft_addexpires, 
        unsigned long long hard_addexpires, unsigned long long soft_useexpires, 
        unsigned long long hard_useexpires);

#endif
