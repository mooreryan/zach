CC = gcc
MKDIR_P = mkdir -p

CFLAGS = -Wall -g -O2

SRC = src
BIN = bin
TEST_D = test_files

.PHONY: all
.PHONY: clean
.PHONY: test

all: zach

bin_dir:
	$(MKDIR_P) $(BIN)

clean:
	-rm -r $(BIN) *.o

test: zach
	$(BIN)/zach $(TEST_D)/tsv.txt > test_out.txt
	diff test_out.txt $(TEST_D)/cdhit_format.txt
	rm test_out.txt

zach: bin_dir
	$(CC) $(CFLAGS) -o $(BIN)/$@ $(SRC)/$@.c
