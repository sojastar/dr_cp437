#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>
#include "app/cp437_console.c"

// MRuby `typedef`s mrb_int in the mruby/value.h
// Then `#define`s mrb_int in mruby.h
// We need to undo the macro and avoid it's usage
// FIXME: I'm surely doing something wrong
#ifdef mrb_int
#undef mrb_int
#endif

void *(*drb_symbol_lookup)(const char *sym) = NULL;

static void (*drb_free_foreign_object_f)(mrb_state *, void *);
static struct RClass *(*mrb_module_get_f)(mrb_state *, const char *);
static mrb_int (*mrb_get_args_f)(mrb_state *, mrb_args_format, ...);
static struct RClass *(*mrb_module_get_under_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_class_get_under_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_define_module_under_f)(mrb_state *, struct RClass *, const char *);
static void (*mrb_define_module_function_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static struct RClass *(*mrb_define_class_under_f)(mrb_state *, struct RClass *, const char *, struct RClass *);
static void (*mrb_define_method_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static void (*mrb_define_class_method_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static struct RData *(*mrb_data_object_alloc_f)(mrb_state *, struct RClass *, void *, const mrb_data_type *);
static mrb_value (*mrb_str_new_cstr_f)(mrb_state *, const char *);
static void (*mrb_raise_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_exc_get_f)(mrb_state *, const char *);
static void drb_free_foreign_object_indirect(mrb_state *state, void *pointer) {
    drb_free_foreign_object_f(state, pointer);
}
static Uint32 drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, Uint32 value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTS5Glyph {
    drb_foreign_object_kind kind;
    Glyph value;
};
static mrb_data_type ForeignObjectType_ZTS5Glyph = {"Glyph", drb_free_foreign_object_indirect};
static Glyph drb_ffi__ZTS5Glyph_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS5Glyph *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS5Glyph_ToRuby(mrb_state *state, Glyph value) {
    struct drb_foreign_object_ZTS5Glyph *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Glyph));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Glyph");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS5Glyph);
    return mrb_obj_value(rdata);
}
static int drb_ffi__ZTSi_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSi_ToRuby(mrb_state *state, int value) {
    return mrb_fixnum_value(value);
}
static Uint8 drb_ffi__ZTSh_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSh_ToRuby(mrb_state *state, Uint8 value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTS5Glyph_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS5Glyph *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Glyph *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Glyph");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS5Glyph);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS5Glyph_foreground_Get(mrb_state *state, mrb_value self) {
    Glyph record = drb_ffi__ZTS5Glyph_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.foreground);
}
static mrb_value drb_ffi__ZTS5Glyph_foreground_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Glyph *)DATA_PTR(self))->value)->foreground = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Glyph_background_Get(mrb_state *state, mrb_value self) {
    Glyph record = drb_ffi__ZTS5Glyph_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.background);
}
static mrb_value drb_ffi__ZTS5Glyph_background_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Glyph *)DATA_PTR(self))->value)->background = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Glyph_index_Get(mrb_state *state, mrb_value self) {
    Glyph record = drb_ffi__ZTS5Glyph_FromRuby(state, self);
    return drb_ffi__ZTSh_ToRuby(state, record.index);
}
static mrb_value drb_ffi__ZTS5Glyph_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint8 new_value = drb_ffi__ZTSh_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Glyph *)DATA_PTR(self))->value)->index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_init_console_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 width_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 height_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Glyph init_glyph_2 = drb_ffi__ZTS5Glyph_FromRuby(state, args[2]);
    init_console(width_0, height_1, init_glyph_2);
    return mrb_nil_value();
}
static mrb_value drb_ffi_delete_console_Binding(mrb_state *state, mrb_value value) {
    delete_console();
    return mrb_nil_value();
}
static mrb_value drb_ffi_update_console_Binding(mrb_state *state, mrb_value value) {
    update_console();
    return mrb_nil_value();
}
static mrb_value drb_ffi_get_console_width_Binding(mrb_state *state, mrb_value value) {
    int ret_val = get_console_width();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_console_height_Binding(mrb_state *state, mrb_value value) {
    int ret_val = get_console_height();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_glyph_at_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Glyph ret_val = get_glyph_at(x_0, y_1);
    return drb_ffi__ZTS5Glyph_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_console_pixel_width_Binding(mrb_state *state, mrb_value value) {
    int ret_val = get_console_pixel_width();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_console_pixel_height_Binding(mrb_state *state, mrb_value value) {
    int ret_val = get_console_pixel_height();
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_set_gc_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint8 index_0 = drb_ffi__ZTSh_FromRuby(state, args[0]);
    set_gc_index(index_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_background_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 background_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    set_gc_background(background_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_foreground_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 foreground_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    set_gc_foreground(foreground_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_antialiased_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int antialiased_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    set_gc_antialiased(antialiased_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_glyph_at_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    draw_glyph_at(x_0, y_1);
    return mrb_nil_value();
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "CP437Console");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "init_console", drb_ffi_init_console_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "delete_console", drb_ffi_delete_console_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "update_console", drb_ffi_update_console_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_console_width", drb_ffi_get_console_width_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_console_height", drb_ffi_get_console_height_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_glyph_at", drb_ffi_get_glyph_at_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "get_console_pixel_width", drb_ffi_get_console_pixel_width_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_console_pixel_height", drb_ffi_get_console_pixel_height_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "set_gc_index", drb_ffi_set_gc_index_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_background", drb_ffi_set_gc_background_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_foreground", drb_ffi_set_gc_foreground_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_antialiased", drb_ffi_set_gc_antialiased_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "draw_glyph_at", drb_ffi_draw_glyph_at_Binding, MRB_ARGS_REQ(2));
    struct RClass *GlyphClass = mrb_define_class_under_f(state, module, "Glyph", object_class);
    mrb_define_class_method_f(state, GlyphClass, "new", drb_ffi__ZTS5Glyph_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "foreground", drb_ffi__ZTS5Glyph_foreground_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "foreground=", drb_ffi__ZTS5Glyph_foreground_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GlyphClass, "background", drb_ffi__ZTS5Glyph_background_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "background=", drb_ffi__ZTS5Glyph_background_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GlyphClass, "index", drb_ffi__ZTS5Glyph_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "index=", drb_ffi__ZTS5Glyph_index_Set, MRB_ARGS_REQ(1));
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *fnname)) {
  drb_symbol_lookup = lookup;
  if (!(drb_free_foreign_object_f = (void (*)(mrb_state *, void *)) lookup("drb_free_foreign_object"))) return -1;
  if (!(mrb_class_get_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_class_get_under"))) return -1;
  if (!(mrb_data_object_alloc_f = (struct RData *(*)(mrb_state *, struct RClass *, void *, const mrb_data_type *)) lookup("mrb_data_object_alloc"))) return -1;
  if (!(mrb_define_class_method_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_class_method"))) return -1;
  if (!(mrb_define_class_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *, struct RClass *)) lookup("mrb_define_class_under"))) return -1;
  if (!(mrb_define_method_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_method"))) return -1;
  if (!(mrb_define_module_function_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_module_function"))) return -1;
  if (!(mrb_define_module_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_define_module_under"))) return -1;
  if (!(mrb_exc_get_f = (struct RClass *(*)(mrb_state *, const char *)) lookup("mrb_exc_get"))) return -1;
  if (!(mrb_get_args_f = (mrb_int (*)(mrb_state *, mrb_args_format, ...)) lookup("mrb_get_args"))) return -1;
  if (!(mrb_module_get_f = (struct RClass *(*)(mrb_state *, const char *)) lookup("mrb_module_get"))) return -1;
  if (!(mrb_module_get_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_module_get_under"))) return -1;
  if (!(mrb_raise_f = (void (*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_raise"))) return -1;
  if (!(mrb_str_new_cstr_f = (mrb_value (*)(mrb_state *, const char *)) lookup("mrb_str_new_cstr"))) return -1;
  return 0;
}
