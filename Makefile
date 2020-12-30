SOURCE=ascii_console
SOURCE_PATH=app/
BINDER=../dragonruby-bind
BINDER_FFI_MODULE=ASCIIConsole
BINDER_CFLAGS='-I /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include -I../include -I.'
BINDER_OUTPUT_EXTENSION=-bindings.c
CC=clang
CFLAGS=-shared -isystem include -I../include -I. -fPIC
DYLIB_PATH=native/macos/
DYLIB_EXTENSION=.dylib

ascii_console:
	$(BINDER) --ffi-module=$(BINDER_FFI_MODULE) --compiler-flags=$(BINDER_CFLAGS) --output=$(SOURCE_PATH)$(SOURCE)$(BINDER_OUTPUT_EXTENSION) $(SOURCE_PATH)$(SOURCE).c
	$(CC) $(CFLAGS) -o $(DYLIB_PATH)$(SOURCE)$(DYLIB_EXTENSION) $(SOURCE_PATH)$(SOURCE)$(BINDER_OUTPUT_EXTENSION)

clean:
	rm -f $(SOURCE_PATH)$(SOURCE)$(BINDER_OUTPUT_EXTENSION) $(DYLIB_PATH)$(SOURCE)$(DYLIB_EXTENSION)
