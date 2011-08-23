/*
Written by John MacCallum, The Center for New Music and Audio Technologies,
University of California, Berkeley.  Copyright (c) 2009-ll, The Regents of
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
*/

/** 	\file osc_bundle_s.h
	\author John MacCallum
	\brief Utilities for manipulating serialized OSC bundles


*/

#ifndef __OSC_BUNDLE_S_H__
#define __OSC_BUNDLE_S_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "osc_bundle_u.h"
#include "osc_message_s.h"
#include "osc_error.h"
#include "osc_array.h"

typedef struct _osc_bundle_s t_osc_bundle_s, t_osc_bndl_s;
typedef t_osc_array t_osc_bundle_array_s, t_osc_bndl_ar_s;

t_osc_bndl_s *osc_bundle_s_alloc(long len, char *ptr);
void osc_bundle_s_free(t_osc_bndl_s *bndl);
char *osc_bundle_s_getPtr(t_osc_bndl_s *bndl);
long osc_bundle_s_getLen(t_osc_bndl_s *bndl);
t_osc_err osc_bundle_s_getMsgCount(int len, char *buf, int *count);
t_osc_err osc_bundle_s_getMessagesWithCallback(int len, char *buf, void (*f)(t_osc_msg_s*, void *), void *context);
t_osc_err osc_bundle_s_lookupAddress(int len, char *buf, char *address, t_osc_array **osc_msg_s_array, int fullmatch);
t_osc_err osc_bundle_s_replaceMessage(long *len, char **bndl, char *old, char *new);
t_osc_err osc_bundle_s_appendMessage(long *len, char **bndl, char *msg);
t_osc_err osc_bundle_s_setBundleID(char *buf);
int osc_bundle_s_strcmpID(char *buf);
t_osc_err osc_bundle_s_deserialize(long len, char *ptr, t_osc_bndl_u **bndl);
t_osc_err osc_bundle_s_format(long len, char *bndl, long *buflen, char **buf);
t_osc_array *osc_bundle_array_s_alloc(long len);

t_osc_bundle_array_s *osc_bundle_array_s_alloc(long len);
#define osc_bundle_array_s_free(ar) osc_array_free((ar))
#define osc_bundle_array_s_clear(ar) osc_array_clear((ar))
#define osc_bundle_array_s_get(ar, idx) osc_array_get((ar), (idx))
#define osc_bundle_array_s_getLen(ar) osc_array_getLen((ar))
#define osc_bundle_array_s_copy(ar) osc_array_copy((ar))
#define osc_bundle_array_s_resize(ar, newlen) osc_array_resize((ar), (newlen))

#ifdef __cplusplus
}
#endif

#endif // __OSC_BUNDLE_S_H__