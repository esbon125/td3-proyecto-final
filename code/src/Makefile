CC=gcc
CFLAGS= -Wall -Wextra -g
MAKE=make

FXP_LIB=libfxp.a
FXP_PATH=../fxp
FXP_LIB_PATH=$(FXP_PATH)/out

CFLAGS=-I$(FXP_PATH)
LDFLAGS=-L$(FXP_LIB_PATH) -lfxp -lm


make: all
	$(PROGRAM)

$(PROGRAM):$(FXP_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OUT_DIR)/$@

$(FXP_LIB):
	$(MAKE) --directory=$(FXP_PATH) $@

clean:
	$(MAKE) --directory=$(FXP_PATH) clean
	rm -Rf $(OUT_DIR)
