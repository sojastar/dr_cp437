#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>
#include "lib/cp437_console.c"

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
struct drb_foreign_object_ZTSPc {
    drb_foreign_object_kind kind;
    char *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPc = {"char*", drb_free_foreign_object_indirect};
static char *drb_ffi__ZTSPc_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    if (mrb_type(self) == MRB_TT_STRING)
        return RSTRING_PTR(self);
    return ((struct drb_foreign_object_ZTSPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPc_ToRuby(mrb_state *state, char *value) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "CharPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
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
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
}
static mrb_value drb_ffi__ZTSPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "CharPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPc_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSc_ToRuby(mrb, *drb_ffi__ZTSPc_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPc_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPc_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPc_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSc_ToRuby(mrb, drb_ffi__ZTSPc_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPc_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    char new_value = drb_ffi__ZTSc_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPc_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_GetString(mrb_state *state, mrb_value self) {
    return mrb_str_new_cstr_f(state, drb_ffi__ZTSPc_FromRuby(state, self));
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
    char *font_name_2 = drb_ffi__ZTSPc_FromRuby(state, args[2]);
    Glyph init_glyph_3 = drb_ffi__ZTS5Glyph_FromRuby(state, args[3]);
    init_console(width_0, height_1, font_name_2, init_glyph_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_delete_console_Binding(mrb_state *state, mrb_value value) {
    delete_console();
    return mrb_nil_value();
}
static mrb_value drb_ffi_resize_console_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 width_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 height_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    resize_console(width_0, height_1);
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
static mrb_value drb_ffi_set_gc_clear_background_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 background_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    set_gc_clear_background(background_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_clear_foreground_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 foreground_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    set_gc_clear_foreground(foreground_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_clear_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint8 index_0 = drb_ffi__ZTSh_FromRuby(state, args[0]);
    set_gc_clear_index(index_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_font_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *font_name_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    set_gc_font(font_name_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_clear_console_Binding(mrb_state *state, mrb_value value) {
    clear_console();
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
static mrb_value drb_ffi_draw_horizontal_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x1_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 x2_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    draw_horizontal_line(x1_0, x2_1, y_2);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_vertical_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y1_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y2_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    draw_vertical_line(x_0, y1_1, y2_2);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x1_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y1_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 x2_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 y2_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_line(x1_0, y1_1, x2_2, y2_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_antialiased_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x1_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y1_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 x2_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 y2_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_antialiased_line(x1_0, y1_1, x2_2, y2_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_stroke_rectangle_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 width_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 height_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    stroke_rectangle(x_0, y_1, width_2, height_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_fill_rectangle_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 width_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 height_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    fill_rectangle(x_0, y_1, width_2, height_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_window_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 width_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 height_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_window(x_0, y_1, width_2, height_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_thin_window_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 width_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 height_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_thin_window(x_0, y_1, width_2, height_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_thick_window_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 x_0 = drb_ffi__ZTSj_FromRuby(state, args[0]);
    Uint32 y_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 width_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 height_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_thick_window(x_0, y_1, width_2, height_3);
    return mrb_nil_value();
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "CP437Console");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "init_console", drb_ffi_init_console_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "delete_console", drb_ffi_delete_console_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "resize_console", drb_ffi_resize_console_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "update_console", drb_ffi_update_console_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_console_width", drb_ffi_get_console_width_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_console_height", drb_ffi_get_console_height_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_glyph_at", drb_ffi_get_glyph_at_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "get_console_pixel_width", drb_ffi_get_console_pixel_width_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "get_console_pixel_height", drb_ffi_get_console_pixel_height_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "set_gc_index", drb_ffi_set_gc_index_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_background", drb_ffi_set_gc_background_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_foreground", drb_ffi_set_gc_foreground_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_clear_background", drb_ffi_set_gc_clear_background_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_clear_foreground", drb_ffi_set_gc_clear_foreground_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_clear_index", drb_ffi_set_gc_clear_index_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_font", drb_ffi_set_gc_font_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "clear_console", drb_ffi_clear_console_Binding, MRB_ARGS_REQ(0));
    mrb_define_module_function_f(state, module, "draw_glyph_at", drb_ffi_draw_glyph_at_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "draw_horizontal_line", drb_ffi_draw_horizontal_line_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "draw_vertical_line", drb_ffi_draw_vertical_line_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "draw_line", drb_ffi_draw_line_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_antialiased_line", drb_ffi_draw_antialiased_line_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "stroke_rectangle", drb_ffi_stroke_rectangle_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "fill_rectangle", drb_ffi_fill_rectangle_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_window", drb_ffi_draw_window_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_thin_window", drb_ffi_draw_thin_window_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_thick_window", drb_ffi_draw_thick_window_Binding, MRB_ARGS_REQ(4));
    struct RClass *CharPointerClass = mrb_define_class_under_f(state, module, "CharPointer", object_class);
    mrb_define_class_method_f(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
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
