/*
  Written by John MacCallum, The Center for New Music and Audio Technologies,
  University of California, Berkeley.  Copyright (c) 2009, The Regents of
  the University of California (Regents). 
  Permission to use, copy, modify, distribute, and distribute modified versions
  of this software and its documentation without fee and without a signed
  licensing agreement, is hereby granted, provided that the above copyright
  notice, this paragraph and the following two paragraphs appear in all copies,
  modifications, and distributions.

  IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
  SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
  OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
  BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
  HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
  MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  NAME: xydisplay
  DESCRIPTION: A 2-D graphical display/editor like pictctrl but supporting multiple points.
  AUTHORS: John MacCallum
  COPYRIGHT_YEARS: 2009
  SVN_REVISION: $LastChangedRevision: 587 $
  VERSION 0.0: First try
  VERSION 0.1: Added labels, and the ability to lock the display so that no new points can be added
  VERSION 0.1.1: added critical sections and fixed a memory leak
  VERSION 0.2: points are now output in the order in which they were entered
  VERSION 0.3: Added a middle outlet to output the distances from the current point to all others
  VERSION 0.4: New algorithm, ability to reshape it by dragging concentric circles
  VERSION 0.5: Points are now stored in a linked hashtable so that we can operate on them by name
  VERSION 0.6: Lots of bugfixes and UI features:  dump, add_point, etc.
  VERSION 0.6.1: Now rescales properly and fixes a problem where a black line would appear at the bottom of the window when resizing
  VERSION 0.7: Reworked the mouse interaction to be closer to Ali's js version and more sane than prev versions of this obj
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

#include "version.h"
#include "ext.h"
#include "ext_obex.h"
#include "ext_obex_util.h"
#include "ext_hashtab.h"
#include "jpatcher_api.h" 
#include "jgraphics.h"
#include "ext_critical.h"
#include "version.c"
#include "math.h"

#define OUTPUT_CONCATENATE 0
#define OUTPUT_LIST 1

#define XY_INNER 1
#define XY_OUTER 2

/*
#define MOUSEUP 0x10
#define MOUSEDOWN 0x20
*/

#define INSIDE_INNER_CIRCLE 0x1
#define ON_INNER_CIRCLE 0x2
//#define INSIDE_OUTER_CIRCLE 0x4
#define ON_OUTER_CIRCLE 0x4

typedef struct _point{
	//double x, y;
	t_pt pt;
	t_symbol *label;
	long index;
	t_jrgba color;
	long double exponent;
	long double weight;
	double inner_radius, outer_radius;
	unsigned long mousestate;
	struct _point *next;
	struct _point *prev;
} t_point;

typedef struct _xydisplay{
	t_jbox ob;
	void *selectedOutlet, *listOutlet, *distanceOutlet, *mouseposOutlet, *dumpOutlet;
	t_critical lock;
	t_jrgba bgcolor, pointcolor, bordercolor, selectedcolor, labelcolor, xhaircolor;
	float pointdiameter;
	t_point *points;
	t_hashtab *ht;
	long npoints;
	t_point *selected;
	double xmin, xmax, ymin, ymax;
	t_symbol *draw_circles, *draw_labels;
	long monotonic_point_counter;
	long outputmode;
	long rbf;
	long mouse_state;
	float line_width;
	long modifiers;
	t_pt xhairs;
} t_xydisplay;

static t_class *xydisplay_class;

void xydisplay_paint(t_xydisplay *x, t_object *patcherview);
void xydisplay_bang(t_xydisplay *x);
void xydisplay_list(t_xydisplay *x, t_symbol *msg, short argc, t_atom *argv);
void xydisplay_anything(t_xydisplay *x, t_symbol *msg, short argc, t_atom *argv);
void xydisplay_computeWeights(t_pt coords, t_rect r, t_point *points, int nweights, double *weights);
void xydisplay_move(t_xydisplay *x, double xx, double yy);
void xydisplay_mousedown(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers);
void xydisplay_mousedrag(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers);
void xydisplay_mouseup(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers);
void xydisplay_mousemove(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers);
void xydisplay_mouseleave(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers);
t_point *xydisplay_insertPoint(t_xydisplay *x, t_pt pt, t_symbol *label);
long double xydisplay_computeWeightFromDistances(double d1, double d2);
long double xydisplay_computeExponentFromDistances(double d1, double d2);
void xydisplay_exponent(t_xydisplay *x, double f);
void xydisplay_weight(t_xydisplay *x, double f);
t_point *xydisplay_selectPoint(t_xydisplay *x, t_pt pt);
void xydisplay_removePoint(t_xydisplay *x, t_point *p);
void xydisplay_addPoint(t_xydisplay *x, t_symbol *msg, int argc, t_atom *argv);
void xydisplay_outputPoints(t_xydisplay *x);
void xydisplay_outputDistance(t_xydisplay *x);
void xydisplay_rename(t_xydisplay *x, t_symbol *msg, int argc, t_atom *argv);
void xydisplay_dump(t_xydisplay *x);
void xydisplay_clear(t_xydisplay *x);
void xydisplay_free(t_xydisplay *x);
void xydisplay_assist(t_xydisplay *x, void *b, long m, long a, char *s);
double xydisplay_scale(double f, double min_in, double max_in, double min_out, double max_out);
double xydisplay_clip(double f, double min, double max);
t_max_err xydisplay_getvalueof(t_xydisplay *x, long *ac, t_atom **av);
t_max_err xydisplay_setvalueof(t_xydisplay *x, long ac, t_atom *av);
void *xydisplay_new(t_symbol *msg, int argc, t_atom *argv);


void xydisplay_paint(t_xydisplay *x, t_object *patcherview){
	t_rect rect;

	t_jgraphics *g_onscreen = (t_jgraphics *)patcherview_get_jgraphics(patcherview);    
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

	t_jsurface *s = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, rect.width, rect.height);
	t_jgraphics *g = jgraphics_create(s);

	jgraphics_set_source_jrgba(g_onscreen, &(x->bordercolor));
	jgraphics_set_line_width(g_onscreen, 1);
	jgraphics_rectangle(g_onscreen, 0., 0., rect.width, rect.height);
	jgraphics_stroke(g_onscreen);
    
	jgraphics_set_source_jrgba(g_onscreen, &(x->bgcolor));
	jgraphics_rectangle(g_onscreen, 0., 0., rect.width, rect.height);
	jgraphics_fill(g_onscreen);

	t_rect srect = rect;
	t_rect drect = rect;
	srect.x = srect.y = drect.x = drect.y = 0.;
	if(1){
		double s = rect.width / 128.;
		srect.width = 128.;
		srect.height = ceil(rect.height / s);
	}else{
	}

	// color
	{
		int i, j, k;
		int w = srect.width;
		int h = srect.height;
		double sum;
		double weights[x->npoints];
		for(i = 0; i < w; i++){
			for(j = 0; j < h; j++){
				t_point *p = x->points;
				sum = 0;
				t_jrgba color = {0., 0., 0., 1.};
				double ii = xydisplay_scale(i, 0, srect.width, 0, drect.width);
				double jj = xydisplay_scale(j, 0, srect.width, 0, drect.width);
				xydisplay_computeWeights((t_pt){ii, jj}, rect, x->points, x->npoints, weights);
				k = 0;
				while(p){
					color.red += weights[k] * p->color.red;
					color.green += weights[k] * p->color.green;
					color.blue += weights[k] * p->color.blue;
					sum += weights[k];
					p = p->next;
					k++;
				}
				color.red /= sum;
				color.green /= sum;
				color.blue /= sum;
				jgraphics_image_surface_set_pixel(s, i, j, color);
			}
		}
	}

	jgraphics_destroy(g);
	jgraphics_image_surface_draw(g_onscreen, s, srect, drect);

	g = g_onscreen;
	// draw points
	{
		jgraphics_set_line_width(g, 1);
		t_point *p = x->points;
		critical_enter(x->lock);
		t_jrgba white = {1., 1., 1., 1.};
		t_jrgba gray = {.75, .75, .75, 1.};
		t_jrgba black = {0., 0., 0., 1.};
		int i = 0;
		while(p){
			if(p == x->selected){
				jgraphics_set_source_jrgba(g, &(white));
			}else{
				jgraphics_set_source_jrgba(g, &(gray));
			}
			double inner_p = .4, outer_p = 1.25;
			//t_jrgba inner_color = (t_jrgba){pow(p->color.red, inner_p), pow(p->color.green, inner_p), pow(p->color.blue, inner_p), 0.6};
			//t_jrgba outer_color = (t_jrgba){pow(p->color.red, outer_p), pow(p->color.green, outer_p), pow(p->color.blue, outer_p), 0.6};

			t_jrgba color;
			t_pt pt = p->pt;
			pt.x *= rect.width;
			pt.y *= rect.height;
			{
				if(p == x->selected){
					if((p->mousestate == INSIDE_INNER_CIRCLE) || (p->mousestate == ON_INNER_CIRCLE)){
						color = white;
					}else{
						color = gray;
					}
				}else{
					color = gray;
				}
				jgraphics_set_dash(g, NULL, 0, 0);
				jgraphics_set_line_width(g, 2.);
				jgraphics_set_source_jrgba(g, &color);
				jgraphics_ellipse(g, pt.x - p->inner_radius, pt.y - p->inner_radius, p->inner_radius * 2, p->inner_radius * 2);
				jgraphics_stroke(g);

				if(p == x->selected){
					//post("%s is selected, comparing 0x%x to 0x%x and 0x%x", p->label->s_name, p->mousestate, (MOUSEUP | INSIDE_INNER_CIRCLE), (MOUSEUP | ON_OUTER_CIRCLE));
					if((p->mousestate == INSIDE_INNER_CIRCLE) || (p->mousestate == ON_OUTER_CIRCLE)){
						color = white;
					}else{
						color = gray;
					}
				}else{
					color = gray;
				}
				jgraphics_set_dash(g, (double[2]){3., 3.}, 2, 0);
				jgraphics_set_line_width(g, 1.);
				jgraphics_set_source_jrgba(g, &color);
				jgraphics_ellipse(g, pt.x - p->outer_radius, pt.y - p->outer_radius, p->outer_radius * 2, p->outer_radius * 2);
				jgraphics_stroke(g);
			}

			{
				if(p == x->selected){
					if(p->mousestate & 0xful){
						color = white;
					}else{
						color = gray;
					}
				}else{
					color = gray;
				}
				jgraphics_set_source_jrgba(g, &(color));
				jgraphics_set_font_size(g, 10);
				double w, h;
				jgraphics_text_measure(g, p->label->s_name, &w, &h);
				jgraphics_move_to(g, pt.x - (w / 2.), pt.y + (h / 2.));
				jgraphics_show_text(g, p->label->s_name);
			}
			jgraphics_stroke(g);

			p = p->next;
		}
		critical_exit(x->lock);
	}

	jgraphics_set_dash(g, NULL, 0, 0);

	// draw mouse cursor
	{
		jgraphics_set_source_jrgba(g, &(x->xhaircolor));
		jgraphics_move_to(g, x->xhairs.x - 4, x->xhairs.y - 4);
		jgraphics_line_to(g, x->xhairs.x + 4, x->xhairs.y + 4);
		jgraphics_move_to(g, x->xhairs.x + 4, x->xhairs.y - 4);
		jgraphics_line_to(g, x->xhairs.x - 4, x->xhairs.y + 4);
		jgraphics_stroke(g);
	}
}

void xydisplay_bang(t_xydisplay *x){
	xydisplay_outputPoints(x);
	xydisplay_outputDistance(x);
}

void xydisplay_list(t_xydisplay *x, t_symbol *msg, short argc, t_atom *argv){
	if(argc != 2 && argc != 3){
		object_error((t_object *)x, "list must be a either 2 or 3 elements long");
		return;
	}
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);
	x->npoints++;

	int i;
	critical_enter(x->lock);

	t_pt pt;
	t_atom *ptr = argv;
	t_atom name;

	//pt.x = atom_getfloat(argv + (i * 2));
	t_symbol *label = NULL;
	if(argc == 3){
		switch(atom_gettype(argv)){
		case A_FLOAT:
			{
				char buf[32];
				sprintf(buf, "%f", atom_getfloat(argv));
				label = gensym(buf);
			}
			break;
		case A_LONG:
			{
				char buf[32];
				sprintf(buf, "%ld", atom_getlong(argv));
				label = gensym(buf);
			}
			break;
		case A_SYM:
			label = atom_getsym(argv);
			break;
		}
		ptr++;
	}

	pt.x = atom_getfloat(ptr++);
	pt.x = xydisplay_scale(pt.x, x->xmin, x->xmax, 0, r.width);
	pt.y = atom_getfloat(ptr);
	pt.y = xydisplay_scale(pt.y, x->ymin, x->ymax, r.height, 0);
	x->selected = xydisplay_insertPoint(x, pt, label);
	//post("%s %f %f", label->s_name, pt.x, pt.y);

	critical_exit(x->lock);
	object_notify(x, _sym_modified, NULL);
	jbox_redraw(&(x->ob));
}

void xydisplay_anything(t_xydisplay *x, t_symbol *msg, short argc, t_atom *argv){
	if(argc == 2 || argc == 3){
		// we'll assume this is a new point
		t_atom buf[argc + 1];
		atom_setsym(buf, msg);
		memcpy(buf + 1, argv, argc * sizeof(t_atom));
		xydisplay_list(x, NULL, argc + 1, buf);
	}
}

void xydisplay_computeWeights(t_pt coords, t_rect r, t_point *points, int nweights, double *weights){
	t_point *p = points;
	int i = 0;
	double sum = 0;
	while(p){
		t_pt pt = p->pt;
		pt.x *= r.width;
		pt.y *= r.height;
		if(coords.x == pt.x && coords.y == pt.y){
			memset(weights, 0, nweights * sizeof(double));
			weights[i] = 1.;
			return;
		}else{
			double d = sqrtl(pow(coords.x - pt.x, 2.) + powl(coords.y - pt.y, 2.));
			weights[i] = powl(1. / d, p->exponent) * p->weight;
			if(isinf(weights[i])){
				memset(weights, 0, nweights * sizeof(double));
				weights[i] = 1.;
				return;
			}
		}
		sum += weights[i];
		p = p->next;
		i++;
	}
	for(i = 0; i < nweights; i++){
		//post("weights[%d]: %f %f, sum = %f", i, weights[i], weights[i] / sum, sum);
		weights[i] /= sum;
	}
}

void xydisplay_move(t_xydisplay *x, double xx, double yy){
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);

	double weights[x->npoints];

	double xx_screen = xydisplay_scale(xx, x->xmin, x->xmax, 0, r.width);
	double yy_screen = xydisplay_scale(yy, x->ymin, x->ymax, r.height, 0);
	xydisplay_computeWeights((t_pt){xx_screen,yy_screen}, r, x->points, x->npoints, weights);
	t_atom out[2];
	int i = 0;
	t_point *p = x->points;
	while(p){
		atom_setsym(out, p->label);
		atom_setfloat(out + 1, weights[i]);
		outlet_list(x->listOutlet, NULL, 2, out);
		i++;
		p = p->next;
	}
	outlet_bang(x->listOutlet);
	x->xhairs = (t_pt){xx_screen,yy_screen};
	jbox_redraw(&(x->ob));
}

// 0x10 = no modifiers 
// 0x11 = command 
// 0x12 = shift 
// 0x94 = control 
// 0x18 = option 

#define CIRCLE_HIT 3 // num pixels on either side of a circle that will register a hit

void xydisplay_mousedown(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
 	//t_rect r; 
	//jbox_get_rect_for_view((t_object *)x, patcherview, &r);
	x->modifiers = modifiers;
 	//post("0x%X", modifiers); 
 	t_rect r; 
	jbox_get_rect_for_view((t_object *)x, patcherview, &r);

	t_atom pos[2];
	atom_setfloat(pos, xydisplay_scale(pt.x, 0, r.width, x->xmin, x->xmax));
	atom_setfloat(pos + 1, xydisplay_scale(pt.y, r.height, 0, x->ymin, x->ymax));
	outlet_list(x->mouseposOutlet, NULL, 2, pos);

	//x->selected = NULL;
	switch(modifiers){
	case 0x10:
		{
			double weights[x->npoints];
			xydisplay_computeWeights(pt, r, x->points, x->npoints, weights);
			t_atom out[2];
			int i = 0;
			t_point *p = x->points;
			while(p){
				atom_setsym(out, p->label);
				atom_setfloat(out + 1, weights[i]);
				outlet_list(x->listOutlet, NULL, 2, out);
				i++;
				p = p->next;
			}
			outlet_bang(x->listOutlet);
			x->xhairs = pt;
		}
		break;
	case 0x12:
		{
			//x->selected = xydisplay_selectPoint(x, pt);
		}
		break;
	case (0x12 | 0x11):
		// command-shift -> delete a point 
		{
			t_point *p;
			if(p = xydisplay_selectPoint(x, pt)){
				xydisplay_removePoint(x, p);
				critical_enter(x->lock);
				x->selected = NULL;
				critical_exit(x->lock);
			}
		}
		break;
	case 0x1a:
		// option-shift
		x->selected = xydisplay_insertPoint(x, pt, NULL);
		break;
	}

 out:
	object_notify(x, _sym_modified, NULL);
	jbox_redraw(&(x->ob));
	//xydisplay_outputPoints(x);
	xydisplay_outputDistance(x);
}

void xydisplay_mousedrag(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
 	t_rect r; 
	jbox_get_rect_for_view((t_object *)x, patcherview, &r);

	switch(modifiers){
	case 0x10:
		{
			double weights[x->npoints];
			xydisplay_computeWeights(pt, r, x->points, x->npoints, weights);
			t_atom out[2];
			int i = 0;
			t_point *p = x->points;
			while(p){
				atom_setsym(out, p->label);
				atom_setfloat(out + 1, weights[i]);
				outlet_list(x->listOutlet, NULL, 2, out);
				i++;
				p = p->next;
			}
			outlet_bang(x->listOutlet);
			x->xhairs = pt;
		}
		break;
	case 0x12:
		post("selected = %p", x->selected);
		if(x->selected){
			post("mousestate: 0x%x", x->selected->mousestate);
			switch(x->selected->mousestate){
			case INSIDE_INNER_CIRCLE:
				post("inside");
				x->selected->pt = (t_pt){pt.x / r.width, pt.y / r.height};
				break;
			case ON_INNER_CIRCLE:
				post("on inner");
				{
					t_point *p = x->selected;
					t_pt sc = p->pt;
					sc.x *= r.width;
					sc.y *= r.height;
					p->inner_radius = sqrt(pow(pt.x - sc.x, 2.) + pow(pt.y - sc.y, 2.));
					p->exponent = xydisplay_computeExponentFromDistances(p->inner_radius, p->outer_radius);
					p->weight = xydisplay_computeWeightFromDistances(p->inner_radius, p->outer_radius);
				}
				break;
			case ON_OUTER_CIRCLE:
				post("on outer");
				{
					t_point *p = x->selected;
					t_pt sc = p->pt;
					sc.x *= r.width;
					sc.y *= r.height;
					p->outer_radius = sqrt(pow(pt.x - sc.x, 2.) + pow(pt.y - sc.y, 2.));
					p->exponent = xydisplay_computeExponentFromDistances(p->inner_radius, p->outer_radius);
					p->weight = xydisplay_computeWeightFromDistances(p->inner_radius, p->outer_radius);
				}
				break;
			}
		}
		break;
	}
	jbox_redraw(&(x->ob));
}

void xydisplay_mouseup(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
 	t_rect r; 
	jbox_get_rect_for_view((t_object *)x, patcherview, &r);
}

void xydisplay_mouseleave(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
 	t_rect r; 
	jbox_get_rect_for_view((t_object *)x, patcherview, &r);
	x->selected = NULL;
	jbox_redraw(&(x->ob));
}

void xydisplay_mousemove(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
 	t_rect r; 
	jbox_get_rect_for_view((t_object *)x, patcherview, &r);

	switch(modifiers){
	case 0x2:
		{
		// shift
			t_point *p = x->points;
			int i = 0;
			while(p){
				t_pt sc = p->pt;
				sc.x *= r.width;
				sc.y *= r.height;
				i++;
				double pos = sqrt(pow(pt.x - sc.x, 2.) + pow(pt.y - sc.y, 2.));
				p->mousestate = 0;
				if(fabs(pos - p->inner_radius) <= CIRCLE_HIT){
					p->mousestate |= ON_INNER_CIRCLE;
					if(x->selected){
						if(fabs(pos - p->inner_radius) < fabs(pos - x->selected->inner_radius)){
							x->selected = p;
						}
					}else{
						x->selected = p;
					}
				}else if(fabs(pos - p->outer_radius) <= CIRCLE_HIT){
					p->mousestate |= ON_OUTER_CIRCLE;
					if(x->selected){
						if(fabs(pos - p->outer_radius) < fabs(pos - x->selected->outer_radius)){
							x->selected = p;
						}
					}else{
						x->selected = p;
					}
				}else if(p->inner_radius - pos >= 0){
					p->mousestate |= INSIDE_INNER_CIRCLE;
					if(x->selected){
						if((p->inner_radius - pos) < (x->selected->inner_radius - pos)){
							x->selected = p;
						}
					}else{
						x->selected = p;
					}
				}else if(p == x->selected){
					x->selected = NULL;
				}

				p = p->next;
			}
		}
		break;
	}
	jbox_redraw(&(x->ob));
}

/*
void xydisplay_mousedown(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){ 
	x->modifiers = modifiers;
 	//post("0x%X", modifiers); 
 	t_rect r; 
	jbox_get_rect_for_view((t_object *)x, patcherview, &r);

	t_atom pos[2];
	atom_setfloat(pos, xydisplay_scale(pt.x, 0, r.width, x->xmin, x->xmax));
	atom_setfloat(pos + 1, xydisplay_scale(pt.y, r.height, 0, x->ymin, x->ymax));
	outlet_list(x->mouseposOutlet, NULL, 2, pos);

	x->selected = NULL;
	switch(modifiers){
	case 0x10:
		{
			double weights[x->npoints];
			xydisplay_computeWeights(pt, r, x->points, x->npoints, weights);
			t_atom out[2];
			int i = 0;
			t_point *p = x->points;
			while(p){
				atom_setsym(out, p->label);
				atom_setfloat(out + 1, weights[i]);
				outlet_list(x->listOutlet, NULL, 2, out);
				i++;
				p = p->next;
			}
			outlet_bang(x->listOutlet);
			x->xhairs = pt;
		}
		break;
	case 0x12:
		// shift -> edit points
		{
			t_point *p = x->points;
			int i = 0;
			while(p){
				t_pt sc = p->pt;
				sc.x *= r.width;
				sc.y *= r.height;
				i++;
				if(fabs(sqrt(pow(pt.x - sc.x, 2.) + pow(pt.y - sc.y, 2.)) - p->inner_radius) <= 5){
					p->dragging = XY_INNER;
					goto out;
				}else if(fabs(sqrt(pow(pt.x - sc.x, 2.) + pow(pt.y - sc.y, 2.)) - p->outer_radius) <= 5.){
					p->dragging = XY_OUTER;
					goto out;
				}else{
					p->dragging = 0;
				}


				p = p->next;
			}
		}
		{
			x->selected = xydisplay_selectPoint(x, pt);
			if(!(x->selected)){
				x->selected = xydisplay_insertPoint(x, pt, NULL);
			}
		}
		break;
	case (0x12 | 0x11):
		// command-shift -> delete a point 
		{
			t_point *p;
			if(p = xydisplay_selectPoint(x, pt)){
				xydisplay_removePoint(x, p);
				critical_enter(x->lock);
				x->selected = NULL;
				critical_exit(x->lock);
			}
		}
		break;
	}

 out:
	object_notify(x, _sym_modified, NULL);
	jbox_redraw(&(x->ob));
	//xydisplay_outputPoints(x);
	xydisplay_outputDistance(x);
}

void xydisplay_mousedrag(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
	x->modifiers = modifiers;
	t_rect r;
	jbox_get_rect_for_view((t_object *)x, patcherview, &r);

	t_atom pos[2];
	atom_setfloat(pos, xydisplay_scale(pt.x, 0, r.width, x->xmin, x->xmax));
	atom_setfloat(pos + 1, xydisplay_scale(pt.y, r.height, 0, x->ymin, x->ymax));
	outlet_list(x->mouseposOutlet, NULL, 2, pos);

	switch(modifiers){
	case 0x10:
		{
			double weights[x->npoints];
			xydisplay_computeWeights(pt, r, x->points, x->npoints, weights);
			t_atom out[2];
			int i = 0;
			t_point *p = x->points;
			while(p){
				atom_setsym(out, p->label);
				atom_setfloat(out + 1, weights[i]);
				outlet_list(x->listOutlet, NULL, 2, out);
				i++;
				p = p->next;
			}
			outlet_bang(x->listOutlet);
			x->xhairs = pt;
		}
		break;
	case 0x12:
		// shift -> edit points
		if(x->selected){
			critical_enter(x->lock);
			x->selected->pt.x = pt.x / r.width;
			x->selected->pt.y = pt.y / r.height;
			x->mouse_state = 1;
			critical_exit(x->lock);
		}else{
			t_point *p = x->points;
			while(p){
				t_pt sc = p->pt;
				sc.x *= r.width;
				sc.y *= r.height;
				if(p->dragging == XY_INNER){
					p->inner_radius = sqrt(pow(pt.x - sc.x, 2.) + pow(pt.y - sc.y, 2.));
					p->exponent = xydisplay_computeExponentFromDistances(p->inner_radius, p->outer_radius);
					p->weight = xydisplay_computeWeightFromDistances(p->inner_radius, p->outer_radius);
					break;
				}else if(p->dragging == XY_OUTER){
					p->outer_radius = sqrt(pow(pt.x - sc.x, 2.) + pow(pt.y - sc.y, 2.));
					p->exponent = xydisplay_computeExponentFromDistances(p->inner_radius, p->outer_radius);
					p->weight = xydisplay_computeWeightFromDistances(p->inner_radius, p->outer_radius);
					break;
				}
				p = p->next;
			}
		}
		break;
	case 0x13:
		break;
	}

	object_notify(x, _sym_modified, NULL);
	jbox_redraw(&(x->ob));
	//xydisplay_outputPoints(x);
	xydisplay_outputDistance(x);
}

void xydisplay_mouseup(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
	outlet_bang(x->mouseposOutlet);
	if(x->mouse_state){
		x->mouse_state = 0;
		jbox_redraw(&(x->ob));
	}
}

void xydisplay_mouseleave(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
	x->modifiers = 0;
	jbox_redraw(&(x->ob));
}

void xydisplay_mousemove(t_xydisplay *x, t_object *patcherview, t_pt pt, long modifiers){
	if(x->modifiers != modifiers){
		x->modifiers = modifiers;
		jbox_redraw(&(x->ob));
	}
}
*/
t_point *xydisplay_insertPoint(t_xydisplay *x, t_pt pt, t_symbol *label){
	critical_enter(x->lock);
	t_hashtab *ht = x->ht;
	t_point *p = NULL;
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);
	if(label){
		hashtab_lookup(ht, label, (t_object **)&p);
	}
	if(!p){
		p = (t_point *)sysmem_newptr(sizeof(t_point));
		p->next = x->points;
		p->prev = NULL;
		if(x->points){
			x->points->prev = p;
		}
		x->points = p;
		x->npoints++;
		p->color = (t_jrgba){(double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1.};
		p->inner_radius = 10.;
		p->outer_radius = 100.;
		p->exponent = xydisplay_computeExponentFromDistances(p->inner_radius, p->outer_radius);
		p->weight = xydisplay_computeWeightFromDistances(p->inner_radius, p->outer_radius);
	}
	if(!label){
		char buf[16];
		sprintf(buf, "%ld", x->monotonic_point_counter++);
		p->label = gensym(buf);
	}else{
		p->label = label;
	}

	hashtab_store(ht, p->label, (t_object *)p);

	/*
	p->x = pt.x;
	p->y = pt.y;
	*/
	p->pt.x = pt.x / r.width;
	p->pt.y = pt.y / r.height;
	critical_exit(x->lock);
	return p;
}

#define THRESH .9
long double xydisplay_computeWeightFromDistances(double d1, double d2){
	double dd1 = d1;
	double dd2 = d2;
	if((dd1 / dd2) <= 1 && (dd1 / dd2) >= THRESH){
		dd1 = THRESH * dd2;
	}else if((dd1 / dd2) >= 1 && (dd1 / dd2) <= (1. / THRESH)){
		dd1 = dd2 / THRESH;
	}

	long double w = expl(-((log(2.) + log(5.)) * (log(dd1) + log(dd2))) / (log(dd1) - log(dd2)));
	return w;
}

long double xydisplay_computeExponentFromDistances(double d1, double d2){
	double dd1 = d1;
	double dd2 = d2;
	if((dd1 / dd2) <= 1 && (dd1 / dd2) >= THRESH){
		dd1 = THRESH * dd2;
	}else if((dd1 / dd2) >= 1 && (dd1 / dd2) <= (1. / THRESH)){
		dd1 = dd2 / THRESH;
	}

	long double d = (2 * (log(2.) + log(5.))) / (-log(dd1) + log(dd2));
	return d;
}

void xydisplay_exponent(t_xydisplay *x, double f){
	t_point *p = x->points;
	while(p){
		p->exponent = f;
		p = p->next;
	}
	jbox_redraw(&(x->ob));
}

void xydisplay_weight(t_xydisplay *x, double f){
	if(x->selected){
		x->selected->weight = f;
	}
	jbox_redraw(&(x->ob));
}

t_point *xydisplay_selectPoint(t_xydisplay *x, t_pt pt){
	critical_enter(x->lock);
	t_point *p = x->points;
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);
	while(p){
		t_pt sc = p->pt;
		sc.x *= r.width;
		sc.y *= r.height;
		if(pt.x >= (sc.x - x->pointdiameter) && pt.x <= (sc.x + x->pointdiameter) &&
		   pt.y >= (sc.y - x->pointdiameter) && pt.y <= (sc.y + x->pointdiameter)){
			goto out;
		}
		p = p->next;
	}
 out:
	critical_exit(x->lock);
	return p;
}

void xydisplay_addPoint(t_xydisplay *x, t_symbol *msg, int argc, t_atom *argv){
	if(argc != 11){
		object_error((t_object *)x, "bad number of arguments--should be 11");
		return;
	}
	t_symbol *label = atom_getsym(argv);
	t_pt pt = {atom_getfloat(argv + 1), atom_getfloat(argv + 2)};
	x->selected = xydisplay_insertPoint(x, pt, label);
	x->selected->color = (t_jrgba){
		atom_getfloat(argv + 3),
		atom_getfloat(argv + 4),
		atom_getfloat(argv + 5),
		atom_getfloat(argv + 6)
	};
	x->selected->exponent = atom_getfloat(argv + 7);
	x->selected->weight = atom_getfloat(argv + 8);
	x->selected->inner_radius = atom_getfloat(argv + 9);
	x->selected->outer_radius = atom_getfloat(argv + 10);
	jbox_redraw(&(x->ob));
}

void xydisplay_removePoint(t_xydisplay *x, t_point *p){
	critical_enter(x->lock);
	if(p->prev){
		p->prev->next = p->next;
	}else{
		x->points = p->next;
	}
	if(p->next){
		p->next->prev = p->prev;
	}
	sysmem_freeptr((void *)p);
	x->npoints--;
	critical_exit(x->lock);
}

void xydisplay_outputPoints(t_xydisplay *x){
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);
	if(x->selected){
		t_atom out[2];
		critical_enter(x->lock);
		atom_setfloat(out, xydisplay_scale(x->selected->pt.x, 0, 1., x->xmin, x->xmax));
		atom_setfloat(out + 1, xydisplay_scale(x->selected->pt.y, 1., 0, x->ymin, x->ymax));
		critical_exit(x->lock);
		outlet_list(x->selectedOutlet, NULL, 2, out);
	}
	t_point *p = x->points;
	switch(x->outputmode){
	case OUTPUT_CONCATENATE:
		{
			long outlen = x->npoints * 2;
			t_atom out[outlen];
			t_atom *outptr = out + outlen - 1;
			critical_enter(x->lock);
			// since the points are pushed onto the front of the linked list, we should work backwards
			while(p){
				t_pt sc = p->pt;
				sc.x *= r.width;
				sc.y *= r.height;
				atom_setfloat(outptr--, xydisplay_scale(sc.y, r.height, 0, x->ymin, x->ymax));
				atom_setfloat(outptr--, xydisplay_scale(sc.x, 0, r.width, x->xmin, x->xmax));
				p = p->next;
			}
			critical_exit(x->lock);
			outlet_list(x->listOutlet, NULL, outlen, out);
		}
		break;
	case OUTPUT_LIST:
		{
			// we could go through and call the outlet for each point, but we would have to exit the critical
			// section and then re-enter at the beginning of the while loop.  since the outlet function can 
			// take a long time to return, we should make a copy of everything quickly and safely, and then 
			// output our copy.
			int npoints = x->npoints;
			t_atom out[3 * npoints];
			t_atom *ptr = out + (3 * npoints) - 1;
			critical_enter(x->lock);
			while(p){
				t_pt sc = p->pt;
				sc.x *= r.width;
				sc.y *= r.height;
				atom_setfloat(ptr--, xydisplay_scale(sc.y, r.height, 0, x->ymin, x->ymax));
				atom_setfloat(ptr--, xydisplay_scale(sc.x, 0, r.width, x->xmin, x->xmax));
				atom_setsym(ptr--, p->label);
				p = p->next;
			}
			critical_exit(x->lock);
			int i;
			outlet_anything(x->listOutlet, gensym("clear"), 0, NULL);
			ptr = out;
			for(i = 0; i < npoints; i++){
				t_symbol *sym = atom_getsym(ptr++);
				outlet_anything(x->listOutlet, sym, 2, ptr);
				ptr += 2;
			}
		}
		break;
	}
}

void xydisplay_outputDistance(t_xydisplay *x){
	if(!x->selected){
		return;
	}
	critical_enter(x->lock);
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);
	int npoints = x->npoints;
	t_atom out[npoints * 2];
	t_atom *ptr = out + (npoints * 2) - 1;
	t_point *p = x->points;
	double selx = xydisplay_scale(x->selected->pt.x, 0, 1., 0., 1.);
	double sely = xydisplay_scale(x->selected->pt.y, 1., 0, 0., 1.);

	while(p){
		t_pt sc = p->pt;
		sc.x *= r.width;
		sc.y *= r.height;
		atom_setfloat(ptr--, sqrt(pow(selx - xydisplay_scale(sc.x, 0., r.width, 0., 1.), 2.) + pow(sely - xydisplay_scale(sc.y, r.height, 0., 0., 1.), 2.)));
		atom_setsym(ptr--, p->label);
		p = p->next;
	}
	critical_exit(x->lock);
	outlet_list(x->distanceOutlet, NULL, npoints * 2, out);
}

void xydisplay_dump(t_xydisplay *x){
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);
	t_point *p = x->points;
	int counter = 0;
	while(p){
		t_pt sc = p->pt;
		sc.x *= r.width;
		sc.y *= r.height;
		t_atom a[12], *ptr = a;
		atom_setlong(ptr++, counter++);
		atom_setsym(ptr++, p->label);
		atom_setfloat(ptr++, p->pt.x * r.width);
		atom_setfloat(ptr++, p->pt.y * r.height);
		atom_setfloat(ptr++, p->color.red);
		atom_setfloat(ptr++, p->color.green);
		atom_setfloat(ptr++, p->color.blue);
		atom_setfloat(ptr++, p->color.alpha);
		atom_setfloat(ptr++, p->exponent);
		atom_setfloat(ptr++, p->weight);
		atom_setfloat(ptr++, p->inner_radius);
		atom_setfloat(ptr++, p->outer_radius);

		outlet_list(x->dumpOutlet, NULL, 12, a);
		p = p->next;
	}
}

void xydisplay_clear(t_xydisplay *x){
	critical_enter(x->lock);
	t_point *p = x->points;
	t_point *next;
	while(p){
		next = p->next;
		sysmem_freeptr(p);
		x->npoints--;
		p = next;
	}
	x->points = NULL;
	x->selected = NULL;
	x->monotonic_point_counter = 0; // not really monotonic i guess...
	hashtab_clear(x->ht);
	critical_exit(x->lock);
	object_notify(x, _sym_modified, NULL);
	jbox_redraw(&(x->ob));
}

void xydisplay_rename(t_xydisplay *x, t_symbol *msg, int argc, t_atom *argv){
	critical_enter(x->lock);
	if(argc == 1){
		if(x->selected){
			switch(atom_gettype(argv)){
			case A_FLOAT:
				{
					char buf[32];
					sprintf(buf, "%f", atom_getfloat(argv));
					x->selected->label = gensym(buf);
				}
				break;
			case A_LONG:
				{
					char buf[32];
					sprintf(buf, "%ld", atom_getlong(argv));
					x->selected->label = gensym(buf);
				}
				break;
			case A_SYM:
				x->selected->label = atom_getsym(argv);
				break;
			}
		}
	}else{
		/*
		t_point *p = x->points;
		t_symbol *oldname = atom_getsym(argv);
		while(p){
			//if(p->label == oldname){
			//}
			p = p->next;
		}
		*/
	}
	critical_exit(x->lock);
	jbox_redraw(&(x->ob));
}

void xydisplay_free(t_xydisplay *x){
	jbox_free(&(x->ob));
	t_point *p = x->points;
	t_point *next = NULL;
	while(p){
		next = p->next;
		sysmem_freeptr(p);
		p = next;
	}
	xydisplay_clear(x);
	critical_free(x->lock);
}

void xydisplay_assist(t_xydisplay *x, void *b, long io, long index, char *s){
	switch(io){
	case 1:
		switch(index){
		case 0:
			sprintf(s, "Point coordinates (list)");
			break;
		}
		break;
	case 2:
		switch(index){
		case 0:
			sprintf(s, "All point coordinates (list)");
			break;
		case 1:
			sprintf(s, "Selected point coordinates (list)");
			break;
		}
		break;
	}
}

double xydisplay_scale(double f, double min_in, double max_in, double min_out, double max_out){
	float m = (max_out - min_out) / (max_in - min_in);
	float b = (min_out - (m * min_in));
	return m * f + b;
}

double xydisplay_clip(double f, double min, double max){
	double ff = f;
	if(ff < min){
		ff = min;
	}
	if(ff > max){
		ff = max;
	}
	return ff;
}

// for pattr
t_max_err xydisplay_getvalueof(t_xydisplay *x, long *ac, t_atom **av){
	//post("getvalueof");
	t_rect r;
	jbox_get_patching_rect(&((x->ob.b_ob)), &r);
	int npoints = x->npoints;
	if(*ac && *av){
	}else{
		*ac = npoints * 2;
		*av = (t_atom *)sysmem_newptr(*ac * sizeof(t_atom));
	}
	critical_enter(x->lock);
	t_point *p = x->points;
	t_atom *outptr = *av;
	while(p){
		t_pt sc = p->pt;
		sc.x *= r.width;
		sc.y *= r.height;
		atom_setfloat(outptr++, xydisplay_scale(sc.x, 0, r.width, x->xmin, x->xmax));
		atom_setfloat(outptr++, xydisplay_scale(sc.y, r.height, 0, x->ymin, x->ymax));
		p = p->next;
	}
	critical_exit(x->lock);

	return MAX_ERR_NONE;
}

t_max_err xydisplay_setvalueof(t_xydisplay *x, long ac, t_atom *av){
	xydisplay_list(x, NULL, ac, av);
	return MAX_ERR_NONE;
}

/**************************************************
Object and instance creation functions.
**************************************************/

void *xydisplay_new(t_symbol *msg, int argc, t_atom *argv){
	t_xydisplay *x;
    
 	t_dictionary *d = NULL; 
 	long boxflags; 
    
	// box setup 
	if(!(d = object_dictionaryarg(argc, argv))){ 
		return NULL; 
	} 
    
	boxflags = 0 
		| JBOX_DRAWFIRSTIN 
		//| JBOX_NODRAWBOX
		| JBOX_DRAWINLAST
		//| JBOX_TRANSPARENT  
		//      | JBOX_NOGROW
		//| JBOX_GROWY
		| JBOX_GROWBOTH
		//      | JBOX_HILITE
		| JBOX_BACKGROUND
		| JBOX_DRAWBACKGROUND
		//      | JBOX_NOFLOATINSPECTOR
		//      | JBOX_MOUSEDRAGDELTA
		//      | JBOX_TEXTFIELD
		;

	if(x = (t_xydisplay *)object_alloc(xydisplay_class)){
		jbox_new((t_jbox *)x, boxflags, argc, argv); 
 		x->ob.b_firstin = (void *)x; 

		x->dumpOutlet = outlet_new(x, NULL);
		x->mouseposOutlet = outlet_new(x, NULL);
		x->selectedOutlet = outlet_new(x, NULL);
		x->distanceOutlet = outlet_new(x, NULL);
		x->listOutlet = outlet_new(x, NULL);
		x->npoints = 0;
		x->points = NULL;
		x->monotonic_point_counter = 0;
		x->mouse_state = 0;
		x->xhairs = (t_pt){-10., -10.};

		x->ht = hashtab_new(0);
		hashtab_flags(x->ht, OBJ_FLAG_DATA);

		critical_new(&(x->lock));
        
		attr_dictionary_process(x, d); 
 		jbox_ready((t_jbox *)x); 
        
		return x;
	}
	return NULL;
}

int main(void){
	t_class *c = class_new("xydisplay", (method)xydisplay_new, (method)xydisplay_free, sizeof(t_xydisplay), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY; 
 	jbox_initclass(c, JBOX_FIXWIDTH | JBOX_COLOR | JBOX_FONTATTR); 
    
	class_addmethod(c, (method)xydisplay_paint, "paint", A_CANT, 0); 
	class_addmethod(c, (method)xydisplay_bang, "bang", 0);
	//class_addmethod(c, (method)xydisplay_int, "int", A_LONG, 0);
	//class_addmethod(c, (method)xydisplay_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)xydisplay_anything, "anything", A_GIMME, 0);
	class_addmethod(c, (method)xydisplay_list, "list", A_GIMME, 0);
	class_addmethod(c, (method)xydisplay_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_getvalueof, "getvalueof", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_setvalueof, "setvalueof", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_mouseup, "mouseup", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method)xydisplay_clear, "clear", 0);
	class_addmethod(c, (method)xydisplay_rename, "rename", A_GIMME, 0);
	class_addmethod(c, (method)xydisplay_exponent, "exponent", A_FLOAT, 0);
	class_addmethod(c, (method)xydisplay_weight, "weight", A_FLOAT, 0);
	class_addmethod(c, (method)xydisplay_move, "move", A_FLOAT, A_FLOAT, 0);
	class_addmethod(c, (method)xydisplay_dump, "dump", 0);
	class_addmethod(c, (method)xydisplay_addPoint, "add_point", A_GIMME, 0);

    
	CLASS_STICKY_ATTR(c, "category", 0, "Color"); 
    
 	CLASS_ATTR_RGBA(c, "bgcolor", 0, t_xydisplay, bgcolor); 
 	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "bgcolor", 0, "0. 0. 0. 1."); 
 	CLASS_ATTR_STYLE_LABEL(c, "bgcolor", 0, "rgba", "Background Color"); 

 	CLASS_ATTR_RGBA(c, "pointcolor", 0, t_xydisplay, pointcolor); 
 	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "pointcolor", 0, "0. 0. 0. 1."); 
 	CLASS_ATTR_STYLE_LABEL(c, "pointcolor", 0, "rgba", "Point Color"); 

 	CLASS_ATTR_RGBA(c, "bordercolor", 0, t_xydisplay, bordercolor); 
 	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "bordercolor", 0, "0. 0. 0. 1."); 
 	CLASS_ATTR_STYLE_LABEL(c, "bordercolor", 0, "rgba", "Border Color"); 

 	CLASS_ATTR_RGBA(c, "selectedcolor", 0, t_xydisplay, selectedcolor); 
 	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "selectedcolor", 0, "1. 0. 0. 1."); 
 	CLASS_ATTR_STYLE_LABEL(c, "selectedcolor", 0, "rgba", "Selected Color"); 

 	CLASS_ATTR_RGBA(c, "labelcolor", 0, t_xydisplay, labelcolor); 
 	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "labelcolor", 0, "0. 0. 0. 1."); 
 	CLASS_ATTR_STYLE_LABEL(c, "labelcolor", 0, "rgba", "Label Color"); 

 	CLASS_ATTR_RGBA(c, "xhaircolor", 0, t_xydisplay, xhaircolor); 
 	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "xhaircolor", 0, "1. 1. 1. 1."); 
 	CLASS_ATTR_STYLE_LABEL(c, "xhaircolor", 0, "rgba", "Crosshair Color"); 
    
	CLASS_STICKY_ATTR_CLEAR(c, "category"); 

	CLASS_ATTR_FLOAT(c, "pointdiameter", 0, t_xydisplay, pointdiameter);
	CLASS_ATTR_DEFAULTNAME_SAVE(c, "pointdiameter", 0, "10.0");

	CLASS_ATTR_DOUBLE(c, "xmin", 0, t_xydisplay, xmin);
	CLASS_ATTR_DEFAULTNAME_SAVE(c, "xmin", 0, "0.0");
	CLASS_ATTR_DOUBLE(c, "xmax", 0, t_xydisplay, xmax);
	CLASS_ATTR_DEFAULTNAME_SAVE(c, "xmax", 0, "1.0");

	CLASS_ATTR_DOUBLE(c, "ymin", 0, t_xydisplay, ymin);
	CLASS_ATTR_DEFAULTNAME_SAVE(c, "ymin", 0, "0.0");
	CLASS_ATTR_DOUBLE(c, "ymax", 0, t_xydisplay, ymax);
	CLASS_ATTR_DEFAULTNAME_SAVE(c, "ymax", 0, "1.0");

	CLASS_ATTR_SYM(c, "draw_circles", 0, t_xydisplay, draw_circles);
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "draw_circles", 0, "edit");
	CLASS_ATTR_SYM(c, "draw_labels", 0, t_xydisplay, draw_labels);
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "draw_labels", 0, "edit");

	CLASS_ATTR_LONG(c, "outputmode", 0, t_xydisplay, outputmode);
	CLASS_ATTR_DEFAULTNAME_SAVE(c, "outputmode", 0, "0");

	CLASS_ATTR_LONG(c, "rbf", 0, t_xydisplay, rbf);
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c, "rbf", 0, 0);

	CLASS_ATTR_DOUBLE(c, "line_width", 0, t_xydisplay, line_width);
    	CLASS_ATTR_DEFAULTNAME_SAVE(c, "line_width", 0, "1.0");

	class_register(CLASS_BOX, c);
	xydisplay_class = c;

	common_symbols_init();

	version(0);

	return 0;
}
