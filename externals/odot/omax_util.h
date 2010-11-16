#ifndef __OMAX_UTIL_H__
#define __OMAX_UTIL_H__

#include "osc_util.h"
#include "ext.h"
#include "ext_obex.h"
#include "ext_atomarray.h"

//t_atomarray *omax_util_oscMsg2MaxAtoms(t_osc_msg *msg);
void omax_util_oscMsg2MaxAtoms(t_osc_msg *msg, long *ac, t_atom *av);
int osc_util_make_bundle(int numAddresses,
			  t_symbol **addresses, 
			  int *numArgs,
			  char **typetags, 
			  t_atom **args, 
			  int *len, 
			 char *buffer);
int osc_util_check_pos_and_resize(char *buf, int len, char *pos);
int osc_util_make_bundle_from_atoms(long argc, t_atom *argv, int *len, char *buffer);


#endif //__OMAX_UTIL_H__
