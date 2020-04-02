#include <stdio.h>
#include <stdlib.h>

#include "sa.h"
#include "sp.h"
#include "lifetime.h"
#include "user-template.h"
#include "selector.h"

int init_add_sa(char *src_tunnel, char *dst_tunnel, int spi, 
		struct auth_params *auth, struct crypto_params *crypto, 
		struct xfrmnl_ltime_cfg* ltime_cfg)
{
	int protocol = IPPROTO_ESP;
	int mode = XFRM_MODE_TUNNEL;

	// IPSEC_MODE_TUNNEL
	struct nl_addr * srcaddr = create_nl_addr(src_tunnel);
	if(srcaddr == NULL){
		return -1;
	}
	struct nl_addr * dstaddr = create_nl_addr(dst_tunnel);
	if(dstaddr == NULL){
		return -1;
	}
	int replay = 100;
	return add_sa(srcaddr, dstaddr, spi, mode, protocol, replay, ltime_cfg,
		auth, crypto);
}

int init_add_sp(char *src, char *dst, char *src_tunnel, char *dst_tunnel, 
		int srcport, int dstport, struct xfrmnl_ltime_cfg* ltime_cfg)
{
	int protocol = IPPROTO_ESP;
	int direction = XFRM_POLICY_OUT;
	// XFRM_POLICY_OUT; XFRM_POLICY_IN; XFRM_POLICY_FWD;
	int action = XFRM_POLICY_ALLOW;
	// XFRM_POLICY_ALLOW; XFRM_POLICY_BLOCK;
	// int spi = 0;
	int mode = XFRM_MODE_TUNNEL;
	// XFRM_MODE_TRANSPORT; XFRM_MODE_TUNNEL;
   	int protocol_next_layer = IPPROTO_TCP;
	//  IPPROTO_TCP; IPPROTO_UDP; IPPROTO_SCTP;
	struct nl_addr *srcaddr = create_nl_addr(src);
	struct nl_addr *dstaddr = create_nl_addr(dst);
	struct nl_addr *srcaddr_tunnel = create_nl_addr(src_tunnel);
	struct nl_addr *dstaddr_tunnel = create_nl_addr(dst_tunnel);
	struct xfrmnl_sel* selector = create_selector(srcaddr, dstaddr, 
		srcport, dstport, protocol_next_layer);
	struct xfrmnl_user_tmpl* templ = create_template(srcaddr_tunnel, 
		dstaddr_tunnel, protocol, mode);
	int index = add_sp(selector,templ,direction,action,ltime_cfg);
	if (index == -1)
		return -1;
	else{
		return 0;
	}

}
int main (void)
{
	if ( geteuid() != 0 ) {
		fprintf ( stderr, "Must be root in order to execute. You are UID=%u, EUID=%u\n", getuid(), geteuid() );
		return 1;
	}
	//lifetime
	unsigned long long lft_byte_soft = 9999999999999;
	unsigned long long lft_byte_hard = 9999999999999;
	unsigned long long lft_packet_soft = 9999999999999;
	unsigned long long lft_packet_hard = 9999999999999;
	unsigned long long lft_soft_add_expires_seconds = 9999999999999;
	unsigned long long lft_hard_add_expires_seconds = 9999999999999;
	unsigned long long lft_soft_use_expires_seconds = 9999999999999;
	unsigned long long lft_hard_use_expires_seconds = 9999999999999;

	struct xfrmnl_ltime_cfg* ltime_cfg = create_ltime_cfg(lft_byte_soft, 
		lft_byte_hard, lft_packet_soft, lft_packet_hard, 
		lft_soft_add_expires_seconds, lft_hard_add_expires_seconds, 
		lft_soft_use_expires_seconds, lft_hard_use_expires_seconds);
	if (ltime_cfg == NULL) {
	    return -1;
   	}

	//auth
   	struct auth_params *auth = malloc(sizeof(struct auth_params));
	auth->auth_alg_name="hmac(md5)";
	char *auth_key = "0123456789";
	auth->auth_key = auth_key;
	auth->auth_key_len = strlen(auth_key)*8;
	auth->auth_trunc_len = strlen(auth_key)*8;

	//encryption
	struct crypto_params *crypto = malloc(sizeof(struct crypto_params));
	crypto->crypto_alg_name="cbc(des)";
	crypto->crypto_key_len = 64;
	crypto->crypto_key = "12345678";
	// // sample 2
	// crypto->crypto_alg_name="cbc(des3_ede)";
	// crypto->crypto_key_len = 192;
	// crypto->crypto_key = "123456789012345678901234";
	// // sample 3
	//crypto->crypto_alg_name="cbc(aes)";
	//crypto->crypto_key = "123456789012345611111111111111111111111111111111111111";
	//crypto->crypto_key_len = 256;
	//printf("crypto->crypto_key_len %i \n",crypto->crypto_key_len);

	char *src = "192.168.100.1/24";
	char *dst = "192.168.200.1/24";
	char *src_tunnel = "10.10.10.1/24";
	char *dst_tunnel = "20.20.20.1/24";
	int srcport = 40001;
	int dstport = 40002;
	int spi = 0x203;
	init_add_sa(src_tunnel, dst_tunnel, spi, auth, crypto, ltime_cfg);
	init_add_sp(src, dst, src_tunnel, dst_tunnel, srcport, dstport, ltime_cfg);


	return 0;
}