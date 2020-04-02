#ifndef SP_H
#define SP_H

#include "utils.h"

int add_sp(struct xfrmnl_sel* selector, struct xfrmnl_user_tmpl* templ, int direccion,int accion,struct xfrmnl_ltime_cfg* ltime_cfg);

#endif
