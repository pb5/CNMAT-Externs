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
NAME: cc
DESCRIPTION: write and compile c code in max
AUTHORS: John MacCallum
COPYRIGHT_YEARS: 2009
SVN_REVISION: $LastChangedRevision: 587 $
VERSION 0.0: First try
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

#include "ext.h"
#include "ext_obex.h"
#include "ext_obex_util.h"
#include "ext_critical.h"
#include "ext_hashtab.h"

#ifdef CC_MSP
#include "z_dsp.h"
#endif

#include <libgen.h>
#include <dlfcn.h>

#define BUFSIZE 65536
#define OBJSIZE 65536

#ifdef CC_MSP
#define CFLAGS "-Wall -O3 -isysroot /Developer/SDKs/MacOSX10.5.sdk -I%s/c74support/max-includes -I%s/c74support/msp-includes -include %s/c74support/max-includes/macho-prefix.pch -F%s/c74support/max-includes -F%s/c74support/msp-includes -mmacosx-version-min=10.5 -fPIC"

#define LDFLAGS "-isysroot /Developer/SDKs/MacOSX10.5.sdk -F%s/c74support/max-includes -F%s/c74support/msp-includes -lmx -framework Carbon -framework MaxAPI -framework MaxAudioAPI"

#else
#define CFLAGS "-Wall -O3 -isysroot /Developer/SDKs/MacOSX10.5.sdk -I%s/c74support/max-includes -include %s/c74support/max-includes/macho-prefix.pch -F%s/c74support/max-includes -mmacosx-version-min=10.5 -fPIC"

#define LDFLAGS "-isysroot /Developer/SDKs/MacOSX10.5.sdk -F%s/c74support/max-includes -lmx -framework Carbon -framework MaxAPI"
#endif

typedef int (*ccmethod)(t_object *, char *, int, int, t_atom *, int, void **);
typedef int (*ccmethod_anything)(t_object *, char *, int, t_symbol *, int, t_atom *, int, void **);
typedef int (*ccmethod_float)(t_object *, char *, int, double, int, void **);
typedef int (*ccmethod_int)(t_object *, char *, int, long, int, void **);
typedef int (*ccmethod_bang)(t_object *, char *, int, int, void **);

#ifdef CC_MSP
typedef t_int *(*ccperform_method)(t_object *, char *, long, t_float **, long, t_float **, long, long);
#endif

typedef struct _cc{
#ifdef CC_MSP
	t_pxobject ob;
	t_float **svin, **svout;
	long nsiginlets, nsigoutlets;
	ccperform_method user_perform;
	long blksize, sr;
#else
	t_object ob;
#endif
	void **outlets;
	long ninlets, noutlets;
	long inlet;
	void **proxies;
	t_object *ed;
	char *code_buf;
	int code_buf_len;
	int code_len;
	char *basename;
	char *cfile_fullpath, *ofile_fullpath, *dfile_fullpath, *logfile_fullpath;
	char *cfile_path, *build_path;
        short cfile_path_id, build_path_id;
	void *handle;
	t_hashtab *ht;
	t_symbol **function_names;
	int num_functions;
	t_symbol *path_to_maxsdk;
	char *def_cflags;
	char *def_ldflags;
	t_symbol *user_cflags;
	t_symbol *user_ldflags;
	char *user_obj;
	int verbose;
	int cfile_is_tmp, build_path_is_tmp;
	int ok_to_compile; // we can't use critical_enter() because the function contained in a lib may call an outlet (or something worse...).
	int compiling;
} t_cc;

static t_class *cc_class;

void cc_compile(t_cc *x);
//void cc_docompile_lowpriority(t_cc *x, t_symbol *msg, short argc, t_atom *argv);
void cc_docompile_and_load_lowpriority(t_cc *x, t_symbol *msg, short argc, t_atom *argv);
int cc_docompile(t_cc *x);
void cc_load(t_cc *x, t_symbol *msg);
void cc_doload_lowpriority(t_cc *x, t_symbol *msg, short argc, t_atom *argv);
int cc_doload(t_cc *x, t_symbol *lib);
void cc_bang(t_cc *x);
void cc_float(t_cc *x, double d);
void cc_int(t_cc *x, long l);
void cc_list(t_cc *x, t_symbol *msg, short argc, t_atom *argv);
//void cc_read_symbols(t_cc *x);
void cc_edclose(t_cc *x, char **text, long size);
long cc_edsave(t_cc *x, char **text, long size);
void cc_okclose(t_cc *x, char *prompt, short *result);
void cc_dblclick(t_cc *x);
void cc_make_file_paths(t_cc *x);
int cc_make_build_dir(t_cc *x, char *path);
void cc_free(t_cc *x);
void cc_assist(t_cc *x, void *b, long m, long a, char *s);
void cc_post_log(t_cc *x, void (*p)(char *, ...));
void cc_write_template(t_cc *x, FILE *fp);
#ifdef CC_MSP
void cc_dsp(t_cc *x, t_signal **sp, short *count);
t_int *cc_perform(t_int *w);
#endif
void *cc_new(t_symbol *msg, short argc, t_atom *argv);
t_max_err cc_notify(t_cc *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void cc_get_basename(char *fp, char *basename);
t_max_err cc_cfile_set(t_cc *x, t_object *attr, long argc, t_atom *argv);
t_max_err cc_cfile_get(t_cc *x, t_object *attr, long *argc, t_atom **argv);
t_max_err cc_build_path_set(t_cc *x, t_object *attr, long argc, t_atom *argv);
t_max_err cc_build_path_get(t_cc *x, t_object *attr, long *argc, t_atom **argv);
t_max_err cc_maxsdk_set(t_cc *x, t_object *attr, long argc, t_atom *argv);
t_max_err cc_maxsdk_get(t_cc *x, t_object *attr, long *argc, t_atom **argv);
t_max_err cc_load_get(t_cc *x, t_object *attr, long *argc, t_atom **argv);
t_max_err cc_load_set(t_cc *x, t_object *attr, long argc, t_atom *argv);

t_symbol *ps_cc_instance_count;

void cc_compile(t_cc *x){
#ifdef CC_MSP
	canvas_stop_dsp();
#endif
	defer(x, (method)cc_docompile_and_load_lowpriority, NULL, 0, NULL);
}

/*
void cc_docompile_lowpriority(t_cc *x, t_symbol *msg, short argc, t_atom *argv){
	cc_docompile(x);
}
*/

void cc_docompile_and_load_lowpriority(t_cc *x, t_symbol *msg, short argc, t_atom *argv){
	if(cc_docompile(x)){
		return;
	}
	cc_doload(x, msg);
}

int cc_docompile(t_cc *x){
	while(!(x->ok_to_compile)){}
	x->compiling = 1;
	int ret = cc_make_build_dir(x, x->build_path);
	if(ret){
		goto out;
	}

	if(x->handle){
		dlclose(x->handle);
	}
	FILE *fp = fopen(x->cfile_fullpath, "r");
	if(fp){
		x->code_len = fread(x->code_buf, sizeof(char), x->code_buf_len, fp);
		fclose(fp);
	}else{
		fclose(fp);
		ret = 1;
		goto out;
	}

	char compbuf[2048];
	char flags[2048];
	sprintf(flags, "%s %s", x->def_cflags, x->user_cflags->s_name);
	sprintf(compbuf, "echo \"gcc %s -o %s -c %s\n\" > %s 2>&1", flags, x->ofile_fullpath, x->cfile_fullpath, x->logfile_fullpath);
	system(compbuf);

	sprintf(compbuf, "gcc %s -o %s -c %s >> %s 2>&1", flags, x->ofile_fullpath, x->cfile_fullpath, x->logfile_fullpath);

	if(x->verbose){
		post("%s", compbuf);
	}
	if(ret = system(compbuf)){
		error("cc: error compiling file:");
		cc_post_log(x, error);
		ret = 1;
		goto out;
	}

	sprintf(flags, "%s %s", x->def_ldflags, x->user_ldflags->s_name);
	sprintf(compbuf, "echo \"\ngcc %s -o %s -dynamiclib %s\n\" >> %s 2>&1", flags, x->dfile_fullpath, x->ofile_fullpath, x->logfile_fullpath);
	system(compbuf);

	sprintf(compbuf, "gcc %s -o %s -dynamiclib %s >> %s 2>&1", flags, x->dfile_fullpath, x->ofile_fullpath, x->logfile_fullpath);

	if(x->verbose){
		post("%s", compbuf);
	}
	if(ret = system(compbuf)){
		error("cc: error linking file:");
		cc_post_log(x, error);
		ret = 1;
		goto out;
	}

	system(compbuf);

 out:
	x->compiling = 0;
	return ret;
}

void cc_load(t_cc *x, t_symbol *msg){
#ifdef CC_MSP
	canvas_stop_dsp();
#endif
	defer(x, (method)cc_doload_lowpriority, msg, 0, NULL);
}

void cc_doload_lowpriority(t_cc *x, t_symbol *msg, short argc, t_atom *argv){
	cc_doload(x, msg);
}

int cc_doload(t_cc *x, t_symbol *lib){
	while(!(x->ok_to_compile)){}
	x->compiling = 1;
	int ret = 0;

	t_symbol *dfile_sym = lib;
	if(!dfile_sym){
		dfile_sym = gensym(x->dfile_fullpath);
	}
	char dfile[MAX_PATH_CHARS];
	strcpy(dfile, dfile_sym->s_name);
	//char *ptr = dfile->s_name;
	//if(*ptr != '/'){
	short outvol;
	long outtype;
	if(locatefile_extended(dfile, &outvol, &outtype, NULL, 0)){
		error("cc: couldn't locate %s", dfile);
		ret = 1;
		goto out;
	}else{
		char buf[MAX_PATH_CHARS];
		path_topathname(outvol, dfile, buf);
		char *ptr = buf;
		while(*ptr++ != ':'){}
		dfile_sym = gensym(ptr);
		strcpy(dfile, dfile_sym->s_name);
	}

	x->handle = dlopen(dfile, RTLD_NOW);
	if(!x->handle){
		error("cc: %s", dlerror());
		ret = 1;
		goto out;
	}

	// read the symbols from the dylib
	hashtab_clear(x->ht);
	char *err;
	char st[MAX_PATH_CHARS];
	sprintf(st, "%s/.%s", x->build_path, x->basename);

	char compbuf[1024];
	sprintf(compbuf, "nm %s | awk '$2 ~ /T/ {print $3}' > %s", dfile, st);
	if(system(compbuf)){
		error("cc: couldn't parse symbol table");
		ret = 1;
		goto out;
	}

	FILE *fp = fopen(st, "r");
	if(!fp){
		error("cc: couldn't read symbol table");
		ret = 1;
		goto out;
	}

	char buf[LINE_MAX];
	int i = 0;
	while(fgets(buf, LINE_MAX, fp)){
		buf[strlen(buf) - 1] = '\0'; // get rid of the newline char
		//ccmethod f = (ccmethod)dlsym(x->handle, buf + 1);
		long f = (long)dlsym(x->handle, buf + 1);
		if((err = dlerror()) == NULL){
			x->function_names[i] = gensym(buf + 1); // skip over the leading underscore
			hashtab_store(x->ht, x->function_names[i], (t_object *)f);
			post("%s", buf + 1);
		}
	}
	fclose(fp);
	remove(st);

	void (*f)(t_object *, char *);
	hashtab_lookup(x->ht, gensym("my_new"), (t_object **)&f);
	if(f){
		f((t_object *)x, x->user_obj);
	}
 out:
	x->compiling = 0;
	return ret;
}

void cc_bang(t_cc *x){
	while(x->compiling){};
	x->ok_to_compile = 0;
	long f = 0;
	hashtab_lookup(x->ht, gensym("my_bang"), (t_object **)(&f));
	if(!f){
		error("cc: doesn't respond to message bang");
		goto out;
	}
	int inlet = proxy_getinlet((t_object *)x);
	((ccmethod_bang)(f))((t_object *)x, x->user_obj, inlet, x->noutlets, x->outlets);
 out:
	x->ok_to_compile = 1;
}

void cc_float(t_cc *x, double d){
	while(x->compiling){};
	x->ok_to_compile = 0;
	long f = 0;
	hashtab_lookup(x->ht, gensym("my_float"), (t_object **)(&f));
	if(!f){
		error("cc: doesn't respond to message float");
		goto out;
	}
	int inlet = proxy_getinlet((t_object *)x);
	((ccmethod_float)(f))((t_object *)x, x->user_obj, inlet, d, x->noutlets, x->outlets);
 out:
	x->ok_to_compile = 1;
}

void cc_int(t_cc *x, long l){
	while(x->compiling){};
	x->ok_to_compile = 0;
	long f = 0;
	hashtab_lookup(x->ht, gensym("my_int"), (t_object **)(&f));
	if(!f){
		error("cc: doesn't respond to message int");
		goto out;
	}
	int inlet = proxy_getinlet((t_object *)x);
	((ccmethod_int)(f))((t_object *)x, x->user_obj, inlet, l, x->noutlets, x->outlets);
 out:
	x->ok_to_compile = 1;
}

void cc_list(t_cc *x, t_symbol *msg, short argc, t_atom *argv){
	while(x->compiling){};
	x->ok_to_compile = 0;
	long f = 0;
	hashtab_lookup(x->ht, gensym("my_list"), (t_object **)(&f));
	if(!f){
		error("cc: doesn't respond to message list");
		goto out;
	}
	int inlet = proxy_getinlet((t_object *)x);
	((ccmethod)(f))((t_object *)x, x->user_obj, inlet, argc, argv, x->noutlets, x->outlets);
 out:
	x->ok_to_compile = 1;
}

void cc_anything(t_cc *x, t_symbol *msg, int argc, t_atom *argv){
	while(x->compiling){};
	x->ok_to_compile = 0;
	long f = 0;
	int inlet = proxy_getinlet((t_object *)x);

	hashtab_lookup(x->ht, msg, (t_object **)(&f));
	if(f){
		((ccmethod)(f))((t_object *)x, x->user_obj, inlet, argc, argv, x->noutlets, x->outlets);
		goto out;
	}

	hashtab_lookup(x->ht, gensym("my_anything"), (t_object **)(&f));
	if(f){
		((ccmethod_anything)(f))((t_object *)x, x->user_obj, inlet, msg, argc, argv, x->noutlets, x->outlets);
		goto out;
	}
	error("cc: doesn't respond to the message %s", msg->s_name);
 out:
	x->ok_to_compile = 1;
}

void cc_edclose(t_cc *x, char **text, long size){
	if(size + 1 > x->code_buf_len){
		char *tmp = (char *)realloc(x->code_buf, (size * 2) * sizeof(char));
		if(tmp){
			x->code_buf = tmp;
			x->code_buf_len = size * 2;
		}else{
			error("cc: out of memory!");
			return;
		}
	}
	strncpy(x->code_buf, *text, size);
	x->code_buf[size] = '\0';
	x->code_len = size + 1;

	x->ed = NULL;
}

long cc_edsave(t_cc *x, char **text, long size){
	return 0;
}

void cc_okclose(t_cc *x, char *prompt, short *result){
	if(x->cfile_is_tmp){
		sprintf(prompt, "Save changes before closing?");
		*result = 1;
	}else{
		*result = 0;
	}
	return;
}

void cc_dblclick(t_cc *x){
	// this should be done only if the file was actually modified--otherwise, just use the buffer
	FILE *fp = fopen(x->cfile_fullpath, "r");
	if(fp){
		x->code_len = fread(x->code_buf, sizeof(char), x->code_buf_len, fp);
	}else{
		//}else if(x->cfile_is_tmp){
		fclose(fp);
		if(!(fp = fopen(x->cfile_fullpath, "w"))){
			error("cc: couldn't open %s", x->cfile_fullpath);
			return;
		}
		cc_write_template(x, fp);
		fclose(fp);
		fp = fopen(x->cfile_fullpath, "r");
		x->code_len = fread(x->code_buf, sizeof(char), x->code_buf_len, fp);
	}
	fclose(fp);
	if(x->ed){
		object_method(x->ed, gensym("settext"), x->code_buf, gensym("utf-8"));
	}else{
		x->ed = (t_object *)object_new(CLASS_NOBOX, gensym("jed"), (t_object *)x, 0);
		short path;
		char filename[MAX_FILENAME_CHARS];
		if(path_frompathname(x->cfile_fullpath, &path, filename)){
			error("cc: couldn't find %s", x->cfile_fullpath);
			return;
		}
		if(x->cfile_is_tmp){
			object_method(x->ed, gensym("filename"), filename, path);
			//object_attr_setsym(x->ed, gensym("title"), gensym("editor"));
		}else{
			object_method(x->ed, gensym("filename"), filename, path);
			//object_attr_setsym(x->ed, gensym("title"), gensym(x->cfile_fullpath));
		}
		object_method(x->ed, gensym("settext"), x->code_buf, gensym("utf-8"));
	}

	object_attr_setchar(x->ed, gensym("visible"), 1);
}

void cc_make_file_paths(t_cc *x){
}

int cc_make_build_dir(t_cc *x, char *path){
	char buf[MAX_PATH_CHARS];
	sprintf(buf, "mkdir -p %s/", path);
	if(system(buf)){
		error("cc: couldn't create directory %s", buf);
		return 1;
	}

	sprintf(buf, "%s/exists", path);
	FILE *fp = fopen(buf, "w");
	if(!fp){
		// directory doesn't exist, or we can't write to it
		error("cc: can't write to directory %s", path);
		fclose(fp);
		return 1;
	}

	fclose(fp);
	remove(buf);

	return 0;
}

void cc_free(t_cc *x){
#ifdef CC_MSP
	dsp_free((t_pxobject *)x);
	free(x->svin);
	free(x->svout);
#endif
	void (*f)(t_object *, char *);
	hashtab_lookup(x->ht, gensym("my_free"), (t_object **)&f);
	if(f){
		f((t_object *)x, x->user_obj);
	}

	if(x->cfile_is_tmp){
		char buf[MAX_PATH_CHARS + 20];
		sprintf(buf, "rm -f %s", x->cfile_fullpath);
		system(buf);
	}

	if(x->build_path_is_tmp){
		char buf[MAX_PATH_CHARS + 20];
		sprintf(buf, "rm -f %s/%s.{o,dylib,st,log}", x->build_path, x->basename);
		system(buf);
	}

	free(x->code_buf);
	free(x->function_names);
	if(x->handle){
		dlclose(x->handle);
	}
	free(x->def_cflags);
	free(x->def_ldflags);
	free(x->user_obj);
	int i;
	for(i = 0; i < x->ninlets - 1; i++){
		object_free(x->proxies[i]);
	}
	free(x->proxies);
	free(x->outlets);
}

void cc_assist(t_cc *x, void *b, long io, long index, char *s){
	switch(io){
	case 1:
		switch(index){
		case 0:
			sprintf(s, "");
			break;
		}
		break;
	case 2:
		switch(index){
		case 0:
			sprintf(s, "");
			break;
		}
		break;
	}
}

void cc_post_log(t_cc *x, void (*p)(char *, ...)){
	FILE *fp = fopen(x->logfile_fullpath, "r");
	char buf[LINE_MAX];
	while(fgets(buf, LINE_MAX, fp)){
		p("%s", buf);
	}
	fclose(fp);
}

void cc_write_template(t_cc *x, FILE *fp){
	if(!fp){
		return;
	}
	fprintf(fp, "#include \"ext.h\"\n");
	fprintf(fp, "#include \"ext_obex.h\"\n");
	fprintf(fp, "#include \"ext_obex_util.h\"\n\n");

#ifdef CC_MSP
	fprintf(fp, "#include \"z_dsp.h\"\n\n");

	fprintf(fp, "void my_perform(t_object *o, char *x, long nin, t_float **in, long nout, t_float **out, long blksize, long sr);\n\n");

	fprintf(fp, "long my_dsp(t_object *o, char *x, short *count){\n");
	fprintf(fp, "\treturn (long)my_perform;\n");
	fprintf(fp, "}\n\n");

	fprintf(fp, "void my_perform(t_object *o, char *x, long nin, t_float **in, long nout, t_float **out, long blksize, long sr){\n");
	fprintf(fp, "\n");
	fprintf(fp, "}\n\n");
#endif

	fprintf(fp, "int foo(t_object *o, char *x, int inlet, int argc, t_atom *argv, int numoutlets, void **outlets){\n");
	fprintf(fp, "\n\treturn 0; // non-zero indicates an error\n");
	fprintf(fp, "}\n");

	fprintf(fp, "\n");

	fprintf(fp, "int my_bang(t_object *o, char *x, int inlet, int numoutlets, void **outlets){\n");
	fprintf(fp, "\n\treturn 0; // non-zero indicates an error\n");
	fprintf(fp, "}\n");

	fprintf(fp, "\n");

	fprintf(fp, "int my_int(t_object *o, char *x, int inlet, long l, int numoutlets, void **outlets){\n");
	fprintf(fp, "\n\treturn 0; // non-zero indicates an error\n");
	fprintf(fp, "}\n");

	fprintf(fp, "\n");

	fprintf(fp, "int my_float(t_object *o, char *x, int inlet, double f, int numoutlets, void **outlets){\n");
	fprintf(fp, "\n\treturn 0; // non-zero indicates an error\n");
	fprintf(fp, "}\n");

	fprintf(fp, "\n");

	fprintf(fp, "int my_list(t_object *o, char *x, int inlet, int argc, t_atom *argv, int numoutlets, void **outlets){\n");
	fprintf(fp, "\n\treturn 0; // non-zero indicates an error\n");
	fprintf(fp, "}\n");

	fprintf(fp, "\n");

	fprintf(fp, "int my_anything(t_object *o, char *x, int inlet, t_symbol *msg, int argc, t_atom *argv, int numoutlets, void **outlets){\n");
	fprintf(fp, "\n\treturn 0; // non-zero indicates an error\n");
	fprintf(fp, "}\n");

	fprintf(fp, "\n");

	fprintf(fp, "void my_free(t_object *o, char *x){\n");
	fprintf(fp, "\t// free any instance data here\n");
	fprintf(fp, "}\n\n");

	fprintf(fp, "void my_new(t_object *o, char *x){\n");
	fprintf(fp, "\t// allocate and initialize any instance data/variables here\n");
	fprintf(fp, "\t// this function will be called each time you compile\n");
	fprintf(fp, "}\n");
}

#ifdef CC_MSP
void cc_dsp(t_cc *x, t_signal **sp, short *count){
	long (*dsp)(t_object *, char *, short *);
	hashtab_lookup(x->ht, gensym("my_dsp"), (t_object **)&dsp);
	if(dsp){
		x->user_perform = (ccperform_method)dsp((t_object *)x, x->user_obj, count);
	}

	x->blksize = sp[0]->s_n;
	x->sr = sp[0]->s_sr;
	int i;
	for(i = 0; i < x->nsiginlets; i++){
		x->svin[i] = sp[i]->s_vec;
	}
	for(i = 0; i < x->nsigoutlets; i++){
		x->svout[i] = sp[i + x->nsiginlets]->s_vec;
	}
	dsp_add(cc_perform, 1, x);
}

t_int *cc_perform(t_int *w){
	t_cc *x = (t_cc *)w[1];
	if(!(x->user_perform)){
		return w + 2;
	}

	x->user_perform((t_object *)x, x->user_obj, x->nsiginlets, x->svin, x->nsigoutlets, x->svout, x->blksize, x->sr);

	return w + 2;
}
#endif

void *cc_new(t_symbol *msg, short argc, t_atom *argv){
	t_cc *x;

	if(x = (t_cc *)object_alloc(cc_class)){
		x->ht = (t_hashtab *)hashtab_new(0);
		hashtab_flags(x->ht, OBJ_FLAG_DATA);

		x->ok_to_compile = 1;
		x->compiling = 0;

		x->cfile_is_tmp = 1;
		x->build_path_is_tmp = 1;

		x->ed = NULL;
		x->code_buf_len = BUFSIZE;
		x->code_buf = (char *)calloc(BUFSIZE, sizeof(char));

		x->cfile_path = (char *)calloc(MAX_FILENAME_CHARS, sizeof(char));
		x->build_path = (char *)calloc(MAX_FILENAME_CHARS, sizeof(char));
		x->basename = (char *)calloc(MAX_FILENAME_CHARS, sizeof(char));

		x->cfile_fullpath = (char *)calloc(MAX_PATH_CHARS, sizeof(char));
		x->ofile_fullpath = (char *)calloc(MAX_PATH_CHARS, sizeof(char));
		x->dfile_fullpath = (char *)calloc(MAX_PATH_CHARS, sizeof(char));
		//x->stfile_fullpath = (char *)calloc(MAX_PATH_CHARS, sizeof(char));
		x->logfile_fullpath = (char *)calloc(MAX_PATH_CHARS, sizeof(char));

		x->path_to_maxsdk = gensym("");

		x->verbose = 0;

		long ic = (long)(ps_cc_instance_count->s_thing);
		ic += 1;
		ps_cc_instance_count->s_thing = (void *)ic;

#ifdef CC_MSP
		sprintf(x->basename, "cc~_%ld", (long)ps_cc_instance_count->s_thing);
#else
		sprintf(x->basename, "cc_%ld", (long)ps_cc_instance_count->s_thing);
#endif

		// private?!?
		//short tmpdir = path_tempfolder();
		short tmpdir;
		sprintf(x->build_path, "/private/var/tmp");
		char fn[512];
		path_frompathname(x->build_path, &tmpdir, fn);
		x->cfile_path_id = x->build_path_id = tmpdir;

		sprintf(x->cfile_fullpath, "%s/%s.c", x->build_path, x->basename);
		sprintf(x->ofile_fullpath, "%s/%s.o", x->build_path, x->basename);
		sprintf(x->dfile_fullpath, "%s/%s.dylib", x->build_path, x->basename);
		//sprintf(x->stfile_fullpath, "%s/%s.st", x->build_path, x->basename);
		sprintf(x->logfile_fullpath, "%s/%s.log", x->build_path, x->basename);

		FILE *fp = fopen(x->cfile_fullpath, "w");
		if(fp){
			cc_write_template(x, fp);
			fclose(fp);
		}else{
			error("cc: couldn't write to tmp dir");
		}


		x->function_names = (t_symbol **)calloc(128, sizeof(t_symbol *));

		x->ninlets = 1;
		x->noutlets = 1;

		x->def_cflags = (char *)calloc(4096, sizeof(char));
		x->def_ldflags = (char *)calloc(4096, sizeof(char));
		attr_args_process(x, argc, argv);

		char *sdk = x->path_to_maxsdk->s_name;

#ifdef CC_MSP
		sprintf(x->def_cflags, CFLAGS, sdk, sdk, sdk, sdk, sdk);
		sprintf(x->def_ldflags, LDFLAGS, sdk, sdk);
#else
		sprintf(x->def_cflags, CFLAGS, sdk, sdk, sdk);
		sprintf(x->def_ldflags, LDFLAGS, sdk);
#endif

		x->user_cflags = gensym("");
		x->user_ldflags = gensym("");

		int i;
#ifdef CC_MSP
		dsp_setup((t_pxobject *)x, x->nsiginlets);
		for(i = 0; i < x->nsigoutlets; i++){
			outlet_new((t_object *)x, "signal");
		}
		x->svin = (t_float **)calloc(x->nsiginlets, sizeof(t_float *));
		x->svout = (t_float **)calloc(x->nsigoutlets, sizeof(t_float *));
#endif
		x->proxies = (void **)calloc(x->ninlets - 1, sizeof(void *));
		for(i = 0; i < x->ninlets - 1; i++){
			x->proxies[0] = proxy_new((t_object *)x, x->ninlets - (i + 1), &(x->inlet));
		}

		x->outlets = (void **)calloc(x->noutlets, sizeof(void *));
		for(i = x->noutlets - 1; i >= 0; i--){
			x->outlets[i] = outlet_new((t_object *)x, NULL);
		}

		x->user_obj = (char *)calloc(OBJSIZE, sizeof(char));
		x->handle = NULL;

		object_attach_byptr_register(x, x, CLASS_BOX);

		return x;
	}
	return NULL;
}

int main(void){
#ifdef CC_MSP
	t_class *c = class_new("cc~", (method)cc_new, (method)cc_free, sizeof(t_cc), 0L, A_GIMME, 0);
	class_dspinit(c);
	class_addmethod(c, (method)cc_dsp, "dsp", A_CANT, 0);
#else
	t_class *c = class_new("cc", (method)cc_new, (method)cc_free, sizeof(t_cc), 0L, A_GIMME, 0);
#endif

	class_addmethod(c, (method)cc_bang, "bang", 0);
	class_addmethod(c, (method)cc_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)cc_int, "int", A_LONG, 0);
	class_addmethod(c, (method)cc_list, "list", A_GIMME, 0);
	class_addmethod(c, (method)cc_anything, "anything", A_GIMME, 0);
	class_addmethod(c, (method)cc_assist, "assist", A_CANT, 0);
	//class_addmethod(c, (method)cc_notify, "notify", A_CANT, 0);

	//for the text editor and code
	class_addmethod(c, (method)cc_edclose, "edclose", A_CANT, 0); 
	class_addmethod(c, (method)cc_edsave, "edsave", A_CANT, 0); 
	class_addmethod(c, (method)cc_dblclick, "dblclick", A_CANT, 0);
	class_addmethod(c, (method)cc_okclose, "okclose", A_CANT, 0);  
	class_addmethod(c, (method)cc_compile, "compile", 0);

	CLASS_ATTR_SYM(c, "maxsdk", 0, t_cc, path_to_maxsdk);
	CLASS_ATTR_ACCESSORS(c, "maxsdk", cc_maxsdk_get, cc_maxsdk_set);

	CLASS_ATTR_LONG(c, "outlets", 0, t_cc, noutlets);
	CLASS_ATTR_LONG(c, "inlets", 0, t_cc, ninlets);
	CLASS_ATTR_LONG(c, "verbose", 0, t_cc, verbose);

	CLASS_ATTR_CHAR(c, "cfile", 0, t_cc, cfile_fullpath);
	CLASS_ATTR_ACCESSORS(c, "cfile", cc_cfile_get, cc_cfile_set);

	CLASS_ATTR_CHAR(c, "build_path", 0, t_cc, build_path);
	CLASS_ATTR_ACCESSORS(c, "build_path", cc_build_path_get, cc_build_path_set);

	CLASS_ATTR_CHAR(c, "load", 0, t_cc, dfile_fullpath);
	CLASS_ATTR_ACCESSORS(c, "load", cc_load_get, cc_load_set);

#ifdef CC_MSP
	CLASS_ATTR_LONG(c, "sigoutlets", 0, t_cc, nsigoutlets);
	CLASS_ATTR_LONG(c, "siginlets", 0, t_cc, nsiginlets);
#endif

	class_register(CLASS_BOX, c);
	cc_class = c;

	ps_cc_instance_count = gensym("cc_instance_count");
	ps_cc_instance_count->s_thing = 0;

	common_symbols_init();
    
	return 0;
}

void cc_get_basename(char *fp, char *bn){
	int len = strlen(fp);
	char buf[len];
	strcpy(buf, fp);
	char *filename = basename(fp);
	char *ptr = filename + strlen(filename);
	while(*ptr != '.'){
		ptr--;
	}
	strncpy(bn, filename, ptr - filename);
	bn[ptr - filename] = '\0';
}

t_max_err cc_cfile_set(t_cc *x, t_object *attr, long argc, t_atom *argv){
	if(argc == 0){
		return 1;
	}
	char old_file[MAX_PATH_CHARS];
	strcpy(old_file, x->cfile_fullpath);

	char *f = atom_getsym(argv)->s_name;

	FILE *fp;
	if(*f == '/'){
		// full path.  read it if it exists, otherwise write a template
		strcpy(x->cfile_fullpath, f);
		if(fp = fopen(f, "r")){
			x->code_len = fread(x->code_buf, sizeof(char), BUFSIZE, fp);
		}else{
			fclose(fp);
			if(fp = fopen(f, "w")){
				cc_write_template(x, fp);
				fclose(fp);
			}
		}
	}else{
		// not a full path.  try to find it in the search path and bail if not found
		short outvol;//, binflag;
		long outtype;
		//if(locatefile(f, &outvol, &binflag)){
		if(locatefile_extended(f, &outvol, &outtype, NULL, 0)){
			error("cc: couldn't locate %s", f);
			return 1;
		}else{
			char buf[MAX_PATH_CHARS];
			char *ptr = buf;
			path_topathname(outvol, f, buf);
			while(*ptr++ != ':'){}
			strcpy(x->cfile_fullpath, ptr);
		}
	}

	cc_get_basename(f, x->basename);
	sprintf(x->ofile_fullpath, "%s/%s.o", x->build_path, x->basename);
	sprintf(x->dfile_fullpath, "%s/%s.dylib", x->build_path, x->basename);
	sprintf(x->logfile_fullpath, "%s/%s.log", x->build_path, x->basename);

	if(x->cfile_is_tmp){
		char buf[MAX_PATH_CHARS + 20];
		sprintf(buf, "rm -f %s", old_file);
		system(buf);
	}

	x->cfile_is_tmp = 0;

	return 0;
}

t_max_err cc_cfile_get(t_cc *x, t_object *attr, long *argc, t_atom **argv){
	char alloc;
 
        atom_alloc(argc, argv, &alloc);     // allocate return atom
	atom_setsym(*argv, gensym(x->cfile_fullpath));

        return 0;
}

t_max_err cc_build_path_set(t_cc *x, t_object *attr, long argc, t_atom *argv){
	while(x->compiling){}
	x->ok_to_compile = 0;
	int ret = 0;
	if(argc == 0){
		ret = 1;
		goto out;
	}

	char old_path[MAX_PATH_CHARS];
	int old_path_len = strlen(x->ofile_fullpath) - 1;
	strncpy(old_path, x->ofile_fullpath, strlen(x->ofile_fullpath) - 1);
	old_path[old_path_len] = '\0';

	char *path = atom_getsym(argv)->s_name;

	if(cc_make_build_dir(x, path)){
		ret = 1;
		goto out;
	}

	strcpy(x->build_path, path);

	sprintf(x->ofile_fullpath, "%s/%s.o", path, x->basename);
	sprintf(x->dfile_fullpath, "%s/%s.dylib", path, x->basename);
	//sprintf(x->stfile_fullpath, "%s/%s.st", path, x->basename);
	sprintf(x->logfile_fullpath, "%s/%s.log", path, x->basename);

	if(x->build_path_is_tmp){
		char buf[MAX_PATH_CHARS + 20];
		sprintf(buf, "rm -f %s{o,dylib,st,log}", old_path);
		system(buf);
	}

	x->build_path_is_tmp = 0;

 out:
	x->ok_to_compile = 1;
	return ret;
}

t_max_err cc_build_path_get(t_cc *x, t_object *attr, long *argc, t_atom **argv){
	char alloc; 
        atom_alloc(argc, argv, &alloc);
	atom_setsym(*argv, gensym(x->build_path));
        return 0;
}

t_max_err cc_maxsdk_set(t_cc *x, t_object *attr, long argc, t_atom *argv){
	if(argc == 0){
		return 1;
	}
	x->path_to_maxsdk = atom_getsym(argv);
	char *sdk = x->path_to_maxsdk->s_name;
#ifdef CC_MSP
	sprintf(x->def_cflags, CFLAGS, sdk, sdk, sdk, sdk, sdk);
	sprintf(x->def_ldflags, LDFLAGS, sdk, sdk);
#else
	sprintf(x->def_cflags, CFLAGS, sdk, sdk, sdk);
	sprintf(x->def_ldflags, LDFLAGS, sdk);
#endif
	return 0;
}

t_max_err cc_maxsdk_get(t_cc *x, t_object *attr, long *argc, t_atom **argv){
	char alloc;
        atom_alloc(argc, argv, &alloc);
        atom_setsym(*argv, x->path_to_maxsdk);
        return 0;
}

t_max_err cc_load_set(t_cc *x, t_object *attr, long argc, t_atom *argv){
	if(argc == 0){
		return 1;
	}
	t_symbol *dfile_sym = atom_getsym(argv);
	char *dfile = dfile_sym->s_name;
	char buf[MAX_FILENAME_CHARS];
	cc_get_basename(dfile, buf);
	char *ptr = buf + strlen(buf);
	*ptr++ = '.';
	*ptr++ = 'c';
	*ptr = '\0';
	t_atom a;
	atom_setsym(&a, gensym(buf));
	cc_cfile_set(x, NULL, 1, &a);
	cc_load(x, dfile_sym);
	return 0;
}

t_max_err cc_load_get(t_cc *x, t_object *attr, long *argc, t_atom **argv){
	char alloc;
        atom_alloc(argc, argv, &alloc);
        atom_setsym(*argv, gensym(x->dfile_fullpath));
        return 0;
}