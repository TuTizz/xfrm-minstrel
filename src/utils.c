#include "utils.h"

int get_mask(char * ip_mask) {
	const char d[2] = "/";
	char * ip;
	char * mask;

    ip = strdup(ip_mask);
    ip = strtok(ip,d);
 	mask = strtok(NULL,d);
 	return atoi(mask);
}

struct nl_addr* create_nl_addr(char *addr){
	int err=0;
	struct nl_addr *nl_address;
	if ((err = nl_addr_parse(addr, AF_INET, &nl_address)) < 0) {
        printf("Unable to parse IP address %s\n",addr);
        return NULL;
    }
    return nl_address;
}