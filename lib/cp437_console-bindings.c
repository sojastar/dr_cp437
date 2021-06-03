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
struct drb_foreign_object_ZTSP7Console {
    drb_foreign_object_kind kind;
    Console *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP7Console = {"Console*", drb_free_foreign_object_indirect};
static Console *drb_ffi__ZTSP7Console_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP7Console *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP7Console_ToRuby(mrb_state *state, Console *value) {
    struct drb_foreign_object_ZTSP7Console *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP7Console));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ConsolePointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP7Console);
    return mrb_obj_value(rdata);
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
struct drb_foreign_object_ZTS4Font {
    drb_foreign_object_kind kind;
    Font value;
};
static mrb_data_type ForeignObjectType_ZTS4Font = {"Font", drb_free_foreign_object_indirect};
static Font drb_ffi__ZTS4Font_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS4Font *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS4Font_ToRuby(mrb_state *state, Font value) {
    struct drb_foreign_object_ZTS4Font *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4Font));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Font");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS4Font);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPj {
    drb_foreign_object_kind kind;
    Uint32 *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPj = {"unsigned int*", drb_free_foreign_object_indirect};
static Uint32 *drb_ffi__ZTSPj_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSPj *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPj_ToRuby(mrb_state *state, Uint32 *value) {
    struct drb_foreign_object_ZTSPj *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPj));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Unsigned_intPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPj);
    return mrb_obj_value(rdata);
}
static size_t drb_ffi__ZTSm_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSm_ToRuby(mrb_state *state, size_t value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTS6Sprite {
    drb_foreign_object_kind kind;
    Sprite value;
};
static mrb_data_type ForeignObjectType_ZTS6Sprite = {"Sprite", drb_free_foreign_object_indirect};
static Sprite drb_ffi__ZTS6Sprite_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS6Sprite *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS6Sprite_ToRuby(mrb_state *state, Sprite value) {
    struct drb_foreign_object_ZTS6Sprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS6Sprite));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Sprite");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS6Sprite);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS7Console {
    drb_foreign_object_kind kind;
    Console value;
};
static mrb_data_type ForeignObjectType_ZTS7Console = {"Console", drb_free_foreign_object_indirect};
static Console drb_ffi__ZTS7Console_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS7Console_ToRuby(mrb_state *state, Console value) {
    struct drb_foreign_object_ZTS7Console *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7Console));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Console");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS7Console);
    return mrb_obj_value(rdata);
}
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
}
static Uint8 drb_ffi__ZTSh_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSh_ToRuby(mrb_state *state, Uint8 value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSPh {
    drb_foreign_object_kind kind;
    Uint8 *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPh = {"unsigned char*", drb_free_foreign_object_indirect};
static Uint8 *drb_ffi__ZTSPh_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    if (mrb_type(self) == MRB_TT_STRING)
        return RSTRING_PTR(self);
    return ((struct drb_foreign_object_ZTSPh *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPh_ToRuby(mrb_state *state, Uint8 *value) {
    struct drb_foreign_object_ZTSPh *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPh));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Unsigned_charPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPh);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPP4Font {
    drb_foreign_object_kind kind;
    Font **value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPP4Font = {"Font**", drb_free_foreign_object_indirect};
static Font **drb_ffi__ZTSPP4Font_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSPP4Font *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPP4Font_ToRuby(mrb_state *state, Font **value) {
    struct drb_foreign_object_ZTSPP4Font *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPP4Font));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "FontPointerPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPP4Font);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP5Glyph {
    drb_foreign_object_kind kind;
    Glyph *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP5Glyph = {"Glyph*", drb_free_foreign_object_indirect};
static Glyph *drb_ffi__ZTSP5Glyph_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP5Glyph *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP5Glyph_ToRuby(mrb_state *state, Glyph *value) {
    struct drb_foreign_object_ZTSP5Glyph *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP5Glyph));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "GlyphPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP5Glyph);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS14GraphicContext {
    drb_foreign_object_kind kind;
    GraphicContext value;
};
static mrb_data_type ForeignObjectType_ZTS14GraphicContext = {"GraphicContext", drb_free_foreign_object_indirect};
static GraphicContext drb_ffi__ZTS14GraphicContext_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS14GraphicContext_ToRuby(mrb_state *state, GraphicContext value) {
    struct drb_foreign_object_ZTS14GraphicContext *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS14GraphicContext));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "GraphicContext");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS14GraphicContext);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP6Sprite {
    drb_foreign_object_kind kind;
    Sprite *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP6Sprite = {"Sprite*", drb_free_foreign_object_indirect};
static Sprite *drb_ffi__ZTSP6Sprite_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP6Sprite *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP6Sprite_ToRuby(mrb_state *state, Sprite *value) {
    struct drb_foreign_object_ZTSP6Sprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP6Sprite));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "SpritePointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP6Sprite);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPFvPKciiPKjE {
    drb_foreign_object_kind kind;
    void (*value)(const char *, const int, const int, const Uint32 *);
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPFvPKciiPKjE = {"Function_0*", drb_free_foreign_object_indirect};
static void (*drb_ffi__ZTSPFvPKciiPKjE_FromRuby(mrb_state *state, mrb_value self))(const char *, const int, const int, const Uint32 *) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSPFvPKciiPKjE *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPFvPKciiPKjE_ToRuby(mrb_state *state, void (*value)(const char *, const int, const int, const Uint32 *)) {
    struct drb_foreign_object_ZTSPFvPKciiPKjE *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPFvPKciiPKjE));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Function_0Pointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPFvPKciiPKjE);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP4Font {
    drb_foreign_object_kind kind;
    Font *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP4Font = {"Font*", drb_free_foreign_object_indirect};
static Font *drb_ffi__ZTSP4Font_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP4Font *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP4Font_ToRuby(mrb_state *state, Font *value) {
    struct drb_foreign_object_ZTSP4Font *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP4Font));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "FontPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP4Font);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP7Console_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP7Console *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP7Console));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Console));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "ConsolePointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP7Console);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP7Console_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS7Console_ToRuby(mrb, *drb_ffi__ZTSP7Console_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP7Console_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP7Console_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP7Console_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS7Console_ToRuby(mrb, drb_ffi__ZTSP7Console_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP7Console_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Console new_value = drb_ffi__ZTS7Console_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP7Console_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
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
static mrb_value drb_ffi__ZTSPj_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPj *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPj));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Uint32));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Unsigned_intPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPj);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPj_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSj_ToRuby(mrb, *drb_ffi__ZTSPj_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPj_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPj_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPj_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSj_ToRuby(mrb, drb_ffi__ZTSPj_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPj_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPj_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPh_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPh *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPh));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Uint8));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Unsigned_charPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPh);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPh_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSh_ToRuby(mrb, *drb_ffi__ZTSPh_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPh_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPh_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPh_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSh_ToRuby(mrb, drb_ffi__ZTSPh_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPh_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Uint8 new_value = drb_ffi__ZTSh_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPh_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPh_GetString(mrb_state *state, mrb_value self) {
    return mrb_str_new_cstr_f(state, drb_ffi__ZTSPh_FromRuby(state, self));
}
static mrb_value drb_ffi__ZTSPP4Font_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPP4Font *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPP4Font));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Font *));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "FontPointerPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPP4Font);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPP4Font_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSP4Font_ToRuby(mrb, *drb_ffi__ZTSPP4Font_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPP4Font_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPP4Font_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPP4Font_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSP4Font_ToRuby(mrb, drb_ffi__ZTSPP4Font_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPP4Font_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Font *new_value = drb_ffi__ZTSP4Font_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPP4Font_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP5Glyph_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP5Glyph *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP5Glyph));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Glyph));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "GlyphPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP5Glyph);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP5Glyph_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS5Glyph_ToRuby(mrb, *drb_ffi__ZTSP5Glyph_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP5Glyph_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP5Glyph_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP5Glyph_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS5Glyph_ToRuby(mrb, drb_ffi__ZTSP5Glyph_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP5Glyph_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Glyph new_value = drb_ffi__ZTS5Glyph_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP5Glyph_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP6Sprite_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP6Sprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP6Sprite));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Sprite));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "SpritePointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP6Sprite);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP6Sprite_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS6Sprite_ToRuby(mrb, *drb_ffi__ZTSP6Sprite_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP6Sprite_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP6Sprite_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP6Sprite_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS6Sprite_ToRuby(mrb, drb_ffi__ZTSP6Sprite_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP6Sprite_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Sprite new_value = drb_ffi__ZTS6Sprite_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP6Sprite_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPFvPKciiPKjE_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPFvPKciiPKjE *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPFvPKciiPKjE));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(void (const char *, const int, const int, const Uint32 *)));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Function_0Pointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPFvPKciiPKjE);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPFvPKciiPKjE_GetValue(mrb_state *mrb, mrb_value value) {
    mrb_raise_f(mrb, mrb_exc_get_f(mrb, "RuntimeError"), "Cannot access underlying value of the function pointer");
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPFvPKciiPKjE_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPFvPKciiPKjE_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPFvPKciiPKjE_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_raise_f(mrb, mrb_exc_get_f(mrb, "RuntimeError"), "Cannot access underlying value of the function pointer");
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPFvPKciiPKjE_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_raise_f(mrb, mrb_exc_get_f(mrb, "RuntimeError"), "Cannot change underlying value of the function pointer");
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP4Font_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP4Font *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP4Font));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Font));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "FontPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP4Font);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP4Font_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS4Font_ToRuby(mrb, *drb_ffi__ZTSP4Font_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP4Font_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP4Font_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP4Font_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS4Font_ToRuby(mrb, drb_ffi__ZTSP4Font_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP4Font_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Font new_value = drb_ffi__ZTS4Font_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP4Font_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
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
    return drb_ffi__ZTSj_ToRuby(state, record.index);
}
static mrb_value drb_ffi__ZTS5Glyph_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Glyph *)DATA_PTR(self))->value)->index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Font_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS4Font *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS4Font *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Font");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS4Font);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS4Font_name_Get(mrb_state *state, mrb_value self) {
    Font record = drb_ffi__ZTS4Font_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.name);
}
static mrb_value drb_ffi__ZTS4Font_name_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Font *)DATA_PTR(self))->value)->name = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Font_width_Get(mrb_state *state, mrb_value self) {
    Font record = drb_ffi__ZTS4Font_FromRuby(state, self);
    return drb_ffi__ZTSh_ToRuby(state, record.width);
}
static mrb_value drb_ffi__ZTS4Font_width_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint8 new_value = drb_ffi__ZTSh_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Font *)DATA_PTR(self))->value)->width = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Font_height_Get(mrb_state *state, mrb_value self) {
    Font record = drb_ffi__ZTS4Font_FromRuby(state, self);
    return drb_ffi__ZTSh_ToRuby(state, record.height);
}
static mrb_value drb_ffi__ZTS4Font_height_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint8 new_value = drb_ffi__ZTSh_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Font *)DATA_PTR(self))->value)->height = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS4Font_glyph_data_Get(mrb_state *state, mrb_value self) {
    Font record = drb_ffi__ZTS4Font_FromRuby(state, self);
    return drb_ffi__ZTSPh_ToRuby(state, record.glyph_data);
}
static mrb_value drb_ffi__ZTS4Font_glyph_data_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint8 *new_value = drb_ffi__ZTSPh_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS4Font *)DATA_PTR(self))->value)->glyph_data = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS6Sprite_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS6Sprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS6Sprite *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Sprite");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS6Sprite);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS6Sprite_width_Get(mrb_state *state, mrb_value self) {
    Sprite record = drb_ffi__ZTS6Sprite_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.width);
}
static mrb_value drb_ffi__ZTS6Sprite_width_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS6Sprite *)DATA_PTR(self))->value)->width = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS6Sprite_height_Get(mrb_state *state, mrb_value self) {
    Sprite record = drb_ffi__ZTS6Sprite_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.height);
}
static mrb_value drb_ffi__ZTS6Sprite_height_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS6Sprite *)DATA_PTR(self))->value)->height = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS6Sprite_indices_Get(mrb_state *state, mrb_value self) {
    Sprite record = drb_ffi__ZTS6Sprite_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.indices);
}
static mrb_value drb_ffi__ZTS6Sprite_indices_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS6Sprite *)DATA_PTR(self))->value)->indices = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS6Sprite_foregrounds_Get(mrb_state *state, mrb_value self) {
    Sprite record = drb_ffi__ZTS6Sprite_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.foregrounds);
}
static mrb_value drb_ffi__ZTS6Sprite_foregrounds_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS6Sprite *)DATA_PTR(self))->value)->foregrounds = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS6Sprite_backgrounds_Get(mrb_state *state, mrb_value self) {
    Sprite record = drb_ffi__ZTS6Sprite_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.backgrounds);
}
static mrb_value drb_ffi__ZTS6Sprite_backgrounds_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS6Sprite *)DATA_PTR(self))->value)->backgrounds = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS7Console *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7Console *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Console");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS7Console);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS7Console_fonts_count_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSh_ToRuby(state, record.fonts_count);
}
static mrb_value drb_ffi__ZTS7Console_fonts_count_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint8 new_value = drb_ffi__ZTSh_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->fonts_count = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_fonts_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSPP4Font_ToRuby(state, record.fonts);
}
static mrb_value drb_ffi__ZTS7Console_fonts_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Font **new_value = drb_ffi__ZTSPP4Font_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->fonts = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_width_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.width);
}
static mrb_value drb_ffi__ZTS7Console_width_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->width = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_height_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.height);
}
static mrb_value drb_ffi__ZTS7Console_height_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->height = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_glyphs_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSP5Glyph_ToRuby(state, record.glyphs);
}
static mrb_value drb_ffi__ZTS7Console_glyphs_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Glyph *new_value = drb_ffi__ZTSP5Glyph_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->glyphs = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_size_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.size);
}
static mrb_value drb_ffi__ZTS7Console_size_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->size = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_pixel_width_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.pixel_width);
}
static mrb_value drb_ffi__ZTS7Console_pixel_width_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->pixel_width = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_pixel_height_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.pixel_height);
}
static mrb_value drb_ffi__ZTS7Console_pixel_height_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->pixel_height = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_pixels_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.pixels);
}
static mrb_value drb_ffi__ZTS7Console_pixels_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->pixels = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_graphic_context_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTS14GraphicContext_ToRuby(state, record.graphic_context);
}
static mrb_value drb_ffi__ZTS7Console_graphic_context_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    GraphicContext new_value = drb_ffi__ZTS14GraphicContext_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->graphic_context = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_left_scan_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.left_scan);
}
static mrb_value drb_ffi__ZTS7Console_left_scan_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->left_scan = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_right_scan_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.right_scan);
}
static mrb_value drb_ffi__ZTS7Console_right_scan_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->right_scan = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_vertices_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.vertices);
}
static mrb_value drb_ffi__ZTS7Console_vertices_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->vertices = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_vertex_count_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSm_ToRuby(state, record.vertex_count);
}
static mrb_value drb_ffi__ZTS7Console_vertex_count_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    size_t new_value = drb_ffi__ZTSm_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->vertex_count = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_sprites_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSP6Sprite_ToRuby(state, record.sprites);
}
static mrb_value drb_ffi__ZTS7Console_sprites_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Sprite *new_value = drb_ffi__ZTSP6Sprite_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->sprites = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_sprite_count_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSm_ToRuby(state, record.sprite_count);
}
static mrb_value drb_ffi__ZTS7Console_sprite_count_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    size_t new_value = drb_ffi__ZTSm_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->sprite_count = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Console_drb_upload_pixel_array_Get(mrb_state *state, mrb_value self) {
    Console record = drb_ffi__ZTS7Console_FromRuby(state, self);
    return drb_ffi__ZTSPFvPKciiPKjE_ToRuby(state, record.drb_upload_pixel_array);
}
static mrb_value drb_ffi__ZTS7Console_drb_upload_pixel_array_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    void (*new_value)(const char *, const int, const int, const Uint32 *) = drb_ffi__ZTSPFvPKciiPKjE_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Console *)DATA_PTR(self))->value)->drb_upload_pixel_array = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS14GraphicContext *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS14GraphicContext *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "CP437Console");
    struct RClass *klass = mrb_class_get_under_f(state, module, "GraphicContext");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS14GraphicContext);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS14GraphicContext_font_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSP4Font_ToRuby(state, record.font);
}
static mrb_value drb_ffi__ZTS14GraphicContext_font_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Font *new_value = drb_ffi__ZTSP4Font_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->font = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_foreground_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.foreground);
}
static mrb_value drb_ffi__ZTS14GraphicContext_foreground_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->foreground = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_background_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.background);
}
static mrb_value drb_ffi__ZTS14GraphicContext_background_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->background = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_clear_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.clear_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_clear_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->clear_index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_clear_foreground_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.clear_foreground);
}
static mrb_value drb_ffi__ZTS14GraphicContext_clear_foreground_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->clear_foreground = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_clear_background_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.clear_background);
}
static mrb_value drb_ffi__ZTS14GraphicContext_clear_background_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->clear_background = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_should_draw_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.should_draw_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_should_draw_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->should_draw_index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_should_draw_foreground_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.should_draw_foreground);
}
static mrb_value drb_ffi__ZTS14GraphicContext_should_draw_foreground_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->should_draw_foreground = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_should_draw_background_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.should_draw_background);
}
static mrb_value drb_ffi__ZTS14GraphicContext_should_draw_background_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->should_draw_background = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_top_left_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.window_top_left_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_top_left_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->window_top_left_index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_top_right_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.window_top_right_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_top_right_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->window_top_right_index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_bottom_left_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.window_bottom_left_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_bottom_left_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->window_bottom_left_index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_bottom_right_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.window_bottom_right_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_bottom_right_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->window_bottom_right_index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_top_bottom_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.window_top_bottom_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_top_bottom_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->window_top_bottom_index = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_left_right_index_Get(mrb_state *state, mrb_value self) {
    GraphicContext record = drb_ffi__ZTS14GraphicContext_FromRuby(state, self);
    return drb_ffi__ZTSj_ToRuby(state, record.window_left_right_index);
}
static mrb_value drb_ffi__ZTS14GraphicContext_window_left_right_index_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS14GraphicContext *)DATA_PTR(self))->value)->window_left_right_index = new_value;
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
    Console *ret_val = init_console(width_0, height_1, font_name_2, init_glyph_3);
    return drb_ffi__ZTSP7Console_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_free_console_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    free_console(console_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_update_console_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    update_console(console_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_get_console_width_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    int ret_val = get_console_width(console_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_console_height_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    int ret_val = get_console_height(console_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_console_pixel_width_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    int ret_val = get_console_pixel_width(console_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_console_pixel_height_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    int ret_val = get_console_pixel_height(console_0);
    return drb_ffi__ZTSi_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_resize_console_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 width_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 height_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    resize_console(console_0, width_1, height_2);
    return mrb_nil_value();
}
static mrb_value drb_ffi_get_current_font_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Font ret_val = get_current_font(console_0);
    return drb_ffi__ZTS4Font_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_set_gc_font_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    char *font_name_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    set_gc_font(console_0, font_name_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_background_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 background_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_background(console_0, background_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_foreground_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 foreground_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_foreground(console_0, foreground_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_clear_background_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 background_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_clear_background(console_0, background_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_clear_foreground_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 foreground_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_clear_foreground(console_0, foreground_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_clear_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_clear_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_window_top_left_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_window_top_left_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_window_top_right_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_window_top_right_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_window_bottom_left_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_window_bottom_left_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_window_bottom_right_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_window_bottom_right_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_window_top_bottom_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_window_top_bottom_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_set_gc_window_left_right_index_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 index_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    set_gc_window_left_right_index(console_0, index_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_clear_console_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    clear_console(console_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_get_glyph_at_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Glyph ret_val = get_glyph_at(console_0, x_1, y_2);
    return drb_ffi__ZTS5Glyph_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_draw_glyph_at_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    draw_glyph_at(console_0, x_1, y_2);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_string_at_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    char *string_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    Uint32 x_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 y_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_string_at(console_0, string_1, x_2, y_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_cp437_string_with_japanese_font_at_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    char *string_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    Uint32 x_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 y_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_cp437_string_with_japanese_font_at(console_0, string_1, x_2, y_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_horizontal_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x1_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 x2_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 y_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_horizontal_line(console_0, x1_1, x2_2, y_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_vertical_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y1_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 y2_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_vertical_line(console_0, x_1, y1_2, y2_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x1_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y1_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 x2_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    Uint32 y2_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    draw_line(console_0, x1_1, y1_2, x2_3, y2_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_antialiased_line_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x1_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y1_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 x2_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    Uint32 y2_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    draw_antialiased_line(console_0, x1_1, y1_2, x2_3, y2_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_stroke_rectangle_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 width_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    Uint32 height_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    stroke_rectangle(console_0, x_1, y_2, width_3, height_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_fill_rectangle_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 width_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    Uint32 height_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    fill_rectangle(console_0, x_1, y_2, width_3, height_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_window_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 width_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    Uint32 height_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    draw_window(console_0, x_1, y_2, width_3, height_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_thin_window_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 width_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    Uint32 height_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    draw_thin_window(console_0, x_1, y_2, width_3, height_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_draw_thick_window_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 x_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 y_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 width_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    Uint32 height_4 = drb_ffi__ZTSj_FromRuby(state, args[4]);
    draw_thick_window(console_0, x_1, y_2, width_3, height_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_get_polygon_vertices_array_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 *ret_val = get_polygon_vertices_array(console_0);
    return drb_ffi__ZTSPj_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_set_polygon_vertex_count_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    size_t count_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    set_polygon_vertex_count(console_0, count_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_fill_polygon_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    fill_polygon(console_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_create_sprite_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    Uint32 width_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    Uint32 height_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Sprite ret_val = create_sprite(console_0, width_1, height_2);
    return drb_ffi__ZTS6Sprite_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_get_sprite_count_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    size_t ret_val = get_sprite_count(console_0);
    return drb_ffi__ZTSm_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_draw_sprite_at_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Console *console_0 = drb_ffi__ZTSP7Console_FromRuby(state, args[0]);
    size_t sprite_index_1 = drb_ffi__ZTSm_FromRuby(state, args[1]);
    Uint32 x_2 = drb_ffi__ZTSj_FromRuby(state, args[2]);
    Uint32 y_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    draw_sprite_at(console_0, sprite_index_1, x_2, y_3);
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
    mrb_define_module_function_f(state, module, "free_console", drb_ffi_free_console_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "update_console", drb_ffi_update_console_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "get_console_width", drb_ffi_get_console_width_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "get_console_height", drb_ffi_get_console_height_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "get_console_pixel_width", drb_ffi_get_console_pixel_width_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "get_console_pixel_height", drb_ffi_get_console_pixel_height_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "resize_console", drb_ffi_resize_console_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "get_current_font", drb_ffi_get_current_font_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_gc_font", drb_ffi_set_gc_font_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_index", drb_ffi_set_gc_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_background", drb_ffi_set_gc_background_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_foreground", drb_ffi_set_gc_foreground_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_clear_background", drb_ffi_set_gc_clear_background_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_clear_foreground", drb_ffi_set_gc_clear_foreground_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_clear_index", drb_ffi_set_gc_clear_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_window_top_left_index", drb_ffi_set_gc_window_top_left_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_window_top_right_index", drb_ffi_set_gc_window_top_right_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_window_bottom_left_index", drb_ffi_set_gc_window_bottom_left_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_window_bottom_right_index", drb_ffi_set_gc_window_bottom_right_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_window_top_bottom_index", drb_ffi_set_gc_window_top_bottom_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "set_gc_window_left_right_index", drb_ffi_set_gc_window_left_right_index_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "clear_console", drb_ffi_clear_console_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "get_glyph_at", drb_ffi_get_glyph_at_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "draw_glyph_at", drb_ffi_draw_glyph_at_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "draw_string_at", drb_ffi_draw_string_at_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_cp437_string_with_japanese_font_at", drb_ffi_draw_cp437_string_with_japanese_font_at_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_horizontal_line", drb_ffi_draw_horizontal_line_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_vertical_line", drb_ffi_draw_vertical_line_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "draw_line", drb_ffi_draw_line_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "draw_antialiased_line", drb_ffi_draw_antialiased_line_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "stroke_rectangle", drb_ffi_stroke_rectangle_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "fill_rectangle", drb_ffi_fill_rectangle_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "draw_window", drb_ffi_draw_window_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "draw_thin_window", drb_ffi_draw_thin_window_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "draw_thick_window", drb_ffi_draw_thick_window_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "get_polygon_vertices_array", drb_ffi_get_polygon_vertices_array_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "set_polygon_vertex_count", drb_ffi_set_polygon_vertex_count_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "fill_polygon", drb_ffi_fill_polygon_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "create_sprite", drb_ffi_create_sprite_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "get_sprite_count", drb_ffi_get_sprite_count_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "draw_sprite_at", drb_ffi_draw_sprite_at_Binding, MRB_ARGS_REQ(4));
    struct RClass *ConsolePointerClass = mrb_define_class_under_f(state, module, "ConsolePointer", object_class);
    mrb_define_class_method_f(state, ConsolePointerClass, "new", drb_ffi__ZTSP7Console_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsolePointerClass, "value", drb_ffi__ZTSP7Console_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsolePointerClass, "[]", drb_ffi__ZTSP7Console_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsolePointerClass, "[]=", drb_ffi__ZTSP7Console_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, ConsolePointerClass, "nil?", drb_ffi__ZTSP7Console_IsNil, MRB_ARGS_REQ(0));
    struct RClass *CharPointerClass = mrb_define_class_under_f(state, module, "CharPointer", object_class);
    mrb_define_class_method_f(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_intPointerClass = mrb_define_class_under_f(state, module, "Unsigned_intPointer", object_class);
    mrb_define_class_method_f(state, Unsigned_intPointerClass, "new", drb_ffi__ZTSPj_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_intPointerClass, "value", drb_ffi__ZTSPj_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_intPointerClass, "[]", drb_ffi__ZTSPj_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Unsigned_intPointerClass, "[]=", drb_ffi__ZTSPj_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Unsigned_intPointerClass, "nil?", drb_ffi__ZTSPj_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_charPointerClass = mrb_define_class_under_f(state, module, "Unsigned_charPointer", object_class);
    mrb_define_class_method_f(state, Unsigned_charPointerClass, "new", drb_ffi__ZTSPh_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_charPointerClass, "value", drb_ffi__ZTSPh_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_charPointerClass, "[]", drb_ffi__ZTSPh_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Unsigned_charPointerClass, "[]=", drb_ffi__ZTSPh_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Unsigned_charPointerClass, "nil?", drb_ffi__ZTSPh_IsNil, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_charPointerClass, "str", drb_ffi__ZTSPh_GetString, MRB_ARGS_REQ(0));
    struct RClass *FontPointerPointerClass = mrb_define_class_under_f(state, module, "FontPointerPointer", object_class);
    mrb_define_class_method_f(state, FontPointerPointerClass, "new", drb_ffi__ZTSPP4Font_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontPointerPointerClass, "value", drb_ffi__ZTSPP4Font_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontPointerPointerClass, "[]", drb_ffi__ZTSPP4Font_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, FontPointerPointerClass, "[]=", drb_ffi__ZTSPP4Font_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, FontPointerPointerClass, "nil?", drb_ffi__ZTSPP4Font_IsNil, MRB_ARGS_REQ(0));
    struct RClass *GlyphPointerClass = mrb_define_class_under_f(state, module, "GlyphPointer", object_class);
    mrb_define_class_method_f(state, GlyphPointerClass, "new", drb_ffi__ZTSP5Glyph_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphPointerClass, "value", drb_ffi__ZTSP5Glyph_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphPointerClass, "[]", drb_ffi__ZTSP5Glyph_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GlyphPointerClass, "[]=", drb_ffi__ZTSP5Glyph_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, GlyphPointerClass, "nil?", drb_ffi__ZTSP5Glyph_IsNil, MRB_ARGS_REQ(0));
    struct RClass *SpritePointerClass = mrb_define_class_under_f(state, module, "SpritePointer", object_class);
    mrb_define_class_method_f(state, SpritePointerClass, "new", drb_ffi__ZTSP6Sprite_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpritePointerClass, "value", drb_ffi__ZTSP6Sprite_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpritePointerClass, "[]", drb_ffi__ZTSP6Sprite_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, SpritePointerClass, "[]=", drb_ffi__ZTSP6Sprite_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, SpritePointerClass, "nil?", drb_ffi__ZTSP6Sprite_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Function_0PointerClass = mrb_define_class_under_f(state, module, "Function_0Pointer", object_class);
    mrb_define_class_method_f(state, Function_0PointerClass, "new", drb_ffi__ZTSPFvPKciiPKjE_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Function_0PointerClass, "value", drb_ffi__ZTSPFvPKciiPKjE_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Function_0PointerClass, "[]", drb_ffi__ZTSPFvPKciiPKjE_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Function_0PointerClass, "[]=", drb_ffi__ZTSPFvPKciiPKjE_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Function_0PointerClass, "nil?", drb_ffi__ZTSPFvPKciiPKjE_IsNil, MRB_ARGS_REQ(0));
    struct RClass *FontPointerClass = mrb_define_class_under_f(state, module, "FontPointer", object_class);
    mrb_define_class_method_f(state, FontPointerClass, "new", drb_ffi__ZTSP4Font_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontPointerClass, "value", drb_ffi__ZTSP4Font_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontPointerClass, "[]", drb_ffi__ZTSP4Font_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, FontPointerClass, "[]=", drb_ffi__ZTSP4Font_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, FontPointerClass, "nil?", drb_ffi__ZTSP4Font_IsNil, MRB_ARGS_REQ(0));
    struct RClass *GlyphClass = mrb_define_class_under_f(state, module, "Glyph", object_class);
    mrb_define_class_method_f(state, GlyphClass, "new", drb_ffi__ZTS5Glyph_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "foreground", drb_ffi__ZTS5Glyph_foreground_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "foreground=", drb_ffi__ZTS5Glyph_foreground_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GlyphClass, "background", drb_ffi__ZTS5Glyph_background_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "background=", drb_ffi__ZTS5Glyph_background_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GlyphClass, "index", drb_ffi__ZTS5Glyph_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GlyphClass, "index=", drb_ffi__ZTS5Glyph_index_Set, MRB_ARGS_REQ(1));
    struct RClass *FontClass = mrb_define_class_under_f(state, module, "Font", object_class);
    mrb_define_class_method_f(state, FontClass, "new", drb_ffi__ZTS4Font_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontClass, "name", drb_ffi__ZTS4Font_name_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontClass, "name=", drb_ffi__ZTS4Font_name_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, FontClass, "width", drb_ffi__ZTS4Font_width_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontClass, "width=", drb_ffi__ZTS4Font_width_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, FontClass, "height", drb_ffi__ZTS4Font_height_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontClass, "height=", drb_ffi__ZTS4Font_height_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, FontClass, "glyph_data", drb_ffi__ZTS4Font_glyph_data_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, FontClass, "glyph_data=", drb_ffi__ZTS4Font_glyph_data_Set, MRB_ARGS_REQ(1));
    struct RClass *SpriteClass = mrb_define_class_under_f(state, module, "Sprite", object_class);
    mrb_define_class_method_f(state, SpriteClass, "new", drb_ffi__ZTS6Sprite_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpriteClass, "width", drb_ffi__ZTS6Sprite_width_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpriteClass, "width=", drb_ffi__ZTS6Sprite_width_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, SpriteClass, "height", drb_ffi__ZTS6Sprite_height_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpriteClass, "height=", drb_ffi__ZTS6Sprite_height_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, SpriteClass, "indices", drb_ffi__ZTS6Sprite_indices_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpriteClass, "indices=", drb_ffi__ZTS6Sprite_indices_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, SpriteClass, "foregrounds", drb_ffi__ZTS6Sprite_foregrounds_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpriteClass, "foregrounds=", drb_ffi__ZTS6Sprite_foregrounds_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, SpriteClass, "backgrounds", drb_ffi__ZTS6Sprite_backgrounds_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, SpriteClass, "backgrounds=", drb_ffi__ZTS6Sprite_backgrounds_Set, MRB_ARGS_REQ(1));
    struct RClass *ConsoleClass = mrb_define_class_under_f(state, module, "Console", object_class);
    mrb_define_class_method_f(state, ConsoleClass, "new", drb_ffi__ZTS7Console_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "fonts_count", drb_ffi__ZTS7Console_fonts_count_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "fonts_count=", drb_ffi__ZTS7Console_fonts_count_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "fonts", drb_ffi__ZTS7Console_fonts_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "fonts=", drb_ffi__ZTS7Console_fonts_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "width", drb_ffi__ZTS7Console_width_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "width=", drb_ffi__ZTS7Console_width_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "height", drb_ffi__ZTS7Console_height_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "height=", drb_ffi__ZTS7Console_height_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "glyphs", drb_ffi__ZTS7Console_glyphs_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "glyphs=", drb_ffi__ZTS7Console_glyphs_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "size", drb_ffi__ZTS7Console_size_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "size=", drb_ffi__ZTS7Console_size_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "pixel_width", drb_ffi__ZTS7Console_pixel_width_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "pixel_width=", drb_ffi__ZTS7Console_pixel_width_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "pixel_height", drb_ffi__ZTS7Console_pixel_height_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "pixel_height=", drb_ffi__ZTS7Console_pixel_height_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "pixels", drb_ffi__ZTS7Console_pixels_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "pixels=", drb_ffi__ZTS7Console_pixels_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "graphic_context", drb_ffi__ZTS7Console_graphic_context_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "graphic_context=", drb_ffi__ZTS7Console_graphic_context_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "left_scan", drb_ffi__ZTS7Console_left_scan_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "left_scan=", drb_ffi__ZTS7Console_left_scan_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "right_scan", drb_ffi__ZTS7Console_right_scan_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "right_scan=", drb_ffi__ZTS7Console_right_scan_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "vertices", drb_ffi__ZTS7Console_vertices_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "vertices=", drb_ffi__ZTS7Console_vertices_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "vertex_count", drb_ffi__ZTS7Console_vertex_count_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "vertex_count=", drb_ffi__ZTS7Console_vertex_count_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "sprites", drb_ffi__ZTS7Console_sprites_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "sprites=", drb_ffi__ZTS7Console_sprites_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "sprite_count", drb_ffi__ZTS7Console_sprite_count_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "sprite_count=", drb_ffi__ZTS7Console_sprite_count_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ConsoleClass, "drb_upload_pixel_array", drb_ffi__ZTS7Console_drb_upload_pixel_array_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ConsoleClass, "drb_upload_pixel_array=", drb_ffi__ZTS7Console_drb_upload_pixel_array_Set, MRB_ARGS_REQ(1));
    struct RClass *GraphicContextClass = mrb_define_class_under_f(state, module, "GraphicContext", object_class);
    mrb_define_class_method_f(state, GraphicContextClass, "new", drb_ffi__ZTS14GraphicContext_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "font", drb_ffi__ZTS14GraphicContext_font_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "font=", drb_ffi__ZTS14GraphicContext_font_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "index", drb_ffi__ZTS14GraphicContext_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "index=", drb_ffi__ZTS14GraphicContext_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "foreground", drb_ffi__ZTS14GraphicContext_foreground_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "foreground=", drb_ffi__ZTS14GraphicContext_foreground_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "background", drb_ffi__ZTS14GraphicContext_background_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "background=", drb_ffi__ZTS14GraphicContext_background_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "clear_index", drb_ffi__ZTS14GraphicContext_clear_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "clear_index=", drb_ffi__ZTS14GraphicContext_clear_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "clear_foreground", drb_ffi__ZTS14GraphicContext_clear_foreground_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "clear_foreground=", drb_ffi__ZTS14GraphicContext_clear_foreground_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "clear_background", drb_ffi__ZTS14GraphicContext_clear_background_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "clear_background=", drb_ffi__ZTS14GraphicContext_clear_background_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "should_draw_index", drb_ffi__ZTS14GraphicContext_should_draw_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "should_draw_index=", drb_ffi__ZTS14GraphicContext_should_draw_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "should_draw_foreground", drb_ffi__ZTS14GraphicContext_should_draw_foreground_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "should_draw_foreground=", drb_ffi__ZTS14GraphicContext_should_draw_foreground_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "should_draw_background", drb_ffi__ZTS14GraphicContext_should_draw_background_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "should_draw_background=", drb_ffi__ZTS14GraphicContext_should_draw_background_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "window_top_left_index", drb_ffi__ZTS14GraphicContext_window_top_left_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "window_top_left_index=", drb_ffi__ZTS14GraphicContext_window_top_left_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "window_top_right_index", drb_ffi__ZTS14GraphicContext_window_top_right_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "window_top_right_index=", drb_ffi__ZTS14GraphicContext_window_top_right_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "window_bottom_left_index", drb_ffi__ZTS14GraphicContext_window_bottom_left_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "window_bottom_left_index=", drb_ffi__ZTS14GraphicContext_window_bottom_left_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "window_bottom_right_index", drb_ffi__ZTS14GraphicContext_window_bottom_right_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "window_bottom_right_index=", drb_ffi__ZTS14GraphicContext_window_bottom_right_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "window_top_bottom_index", drb_ffi__ZTS14GraphicContext_window_top_bottom_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "window_top_bottom_index=", drb_ffi__ZTS14GraphicContext_window_top_bottom_index_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, GraphicContextClass, "window_left_right_index", drb_ffi__ZTS14GraphicContext_window_left_right_index_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, GraphicContextClass, "window_left_right_index=", drb_ffi__ZTS14GraphicContext_window_left_right_index_Set, MRB_ARGS_REQ(1));
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
