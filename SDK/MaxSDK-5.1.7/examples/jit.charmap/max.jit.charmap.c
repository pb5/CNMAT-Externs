/* 
	Copyright 2001-2005 - Cycling '74
	Joshua Kit Clayton jkc@cycling74.com	
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_jit_charmap 
{
	t_object		ob;
	void			*obex;
} t_max_jit_charmap;

t_jit_err jit_charmap_init(void); 

void *max_jit_charmap_new(t_symbol *s, long argc, t_atom *argv);
void max_jit_charmap_free(t_max_jit_charmap *x);
void *max_jit_charmap_class;
		 	
void main(void)
{	
	void *p,*q;
	
	jit_charmap_init();	
	setup(&max_jit_charmap_class, max_jit_charmap_new, (method)max_jit_charmap_free, (short)sizeof(t_max_jit_charmap), 
		0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_jit_charmap,obex));
	q = jit_class_findbyname(gensym("jit_charmap"));    
    max_jit_classex_mop_wrap(p,q,0); 		
    max_jit_classex_standard_wrap(p,q,0); 	
    addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
}

void max_jit_charmap_free(t_max_jit_charmap *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_jit_charmap_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_jit_charmap *x;
	void *o;

	if (x=(t_max_jit_charmap *)max_jit_obex_new(max_jit_charmap_class,gensym("jit_charmap"))) {
		if (o=jit_object_new(gensym("jit_charmap"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);			
			max_jit_attr_args(x,argc,argv);
		} else {
			jit_object_error((t_object *)x,"jit.charmap: could not allocate object");
			freeobject(x);
			x = NULL;
		}
	}
	return (x);
}
