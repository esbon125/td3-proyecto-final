#FXP lib compilation
CC=gcc
AR=ar
OUT_DIR=out
FXP_LIB=libfxp.a

SOURCE=ulongy.c fxp_l.c fxp_aux.c print_as_bits.c fxp.c fxp_conv.c
OBJECTS=$(SOURCE:.c=.o)

CFLAGS=-O0
LDFLAGS=-lm

.PHONY: all clean
all: $(FXP_LIB)

$(FXP_LIB): $(OBJECTS)
	cd $(OUT_DIR); \
	$(AR) rcs $@ $?


%.o: %.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $(OUT_DIR)/$@  $?

clean:
	rm -Rf $(OUT_DIR)
