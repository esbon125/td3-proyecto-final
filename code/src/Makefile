CC=gcc
MAKE=make
PROGRAM ?= fir_filter

FXP_LIB=libfxp.a
FXP_PATH=/home/esbon1253/Documents/agenda_files/data/60/219649-c148-4b1c-9e95-0464b970eac3/tpfinal/code/fxp
FXP_LIB_PATH=$(FXP_PATH)/out

CFLAGS= -Wall -Wextra -g -I$(FXP_PATH)
LDFLAGS=-L$(FXP_LIB_PATH) -lfxp -lm
OUT_DIR = out

ifeq ($(PROGRAM), fir_filter)
	CFLAGS += -I../include
endif

all: $(PROGRAM)

$(PROGRAM): $(FXP_LIB)
	@mkdir -p $(OUT_DIR)
	$(CC) $@.c $(CFLAGS) $(LDFLAGS) -o $(OUT_DIR)/$@ 
	@cp $(OUT_DIR)/$(PROGRAM) ../utils/scripts/
$(FXP_LIB):
	$(MAKE) --directory=$(FXP_PATH) $@

clean:
	$(MAKE) --directory=$(FXP_PATH) clean
	rm -Rf $(OUT_DIR)

run_program: $(PROGRAM)
	@echo "=====RUNNING PROGRAM====="
	@cd $(OUT_DIR) && \
	./$(PROGRAM)
