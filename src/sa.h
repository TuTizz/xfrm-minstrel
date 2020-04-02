#ifndef SA_H
#define SA_H

#include "utils.h"

struct crypto_params {
	char *crypto_alg_name;
	char *crypto_key;
	unsigned int crypto_key_len;
};

struct auth_params {
	char *auth_alg_name;
	char *auth_key;
	unsigned int auth_key_len;
	unsigned int auth_trunc_len;
};

int add_sa(struct nl_addr *src_addr,struct nl_addr *dst_addr, int spi, int mode, 
        int protocol, int replay, struct xfrmnl_ltime_cfg* ltime_cfg, 
        struct auth_params *auth, struct crypto_params *crypto);

#endif