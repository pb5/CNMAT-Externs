/* 
	jit.qt.h

	Copyright 2001-2004 - Cycling '74
	Jeremy Bernstein jeremy@bootsquad.com
	
*/

#ifndef __JIT_QT_H__
#define __JIT_QT_H__

#include <Movies.h>
#include <QuicktimeComponents.h>

#ifdef __cplusplus
	extern "C" {
#endif 

void *jit_qtcomponent_open(void *x, Component c, t_symbol *name);
t_jit_err jit_qtcomponent_close(void *x, void *o);

void jit_qtutils_gensymbols(void);
Movie jit_qtutils_moviefile_create(t_symbol **sname, short *resrefnum, FSSpec *fs, long flags);
long jit_qtutils_moviefile_close(Movie movie, short resrefnum);
Track jit_qtutils_trackmedia_add(Movie movie, long type, Rect *trackframe, long vol, long timescale);
Media jit_qtutils_trackmedia_get(Track track);
long jit_qtutils_trackmedia_close(Track track, long trackstart, long mediastart);
long jit_qtutils_trackmedia_dispose(Track track);
void jit_qtutils_type2str(unsigned long type, char *typestr);
OSType jit_qtutils_str2type(char *typestr);
void jit_qtutils_trackname_set(Track track, t_symbol *s);
t_symbol *jit_qtutils_trackname_get(Track track);
t_symbol *jit_qtutils_tracktype_get(Track track);
t_symbol *jit_qtutils_tracktypecode_get(Track track);

t_symbol *jit_qtutils_mediatype2sym(long type);
long jit_qtutils_sym2mediatype(t_symbol *s);
t_symbol *jit_qtutils_filetype2sym(long type);
long jit_qtutils_sym2filetype(t_symbol *s);

// substitutes for Apple's non-working 64-bit Endian swap functions
double jit_qtutils_double_BtoN(double d);
double jit_qtutils_double_NtoB(double d);

#ifdef __cplusplus
}
#endif

#endif

