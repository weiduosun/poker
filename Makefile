all: play, test

test: quiz7.h quiz7.c quiz7_test.c quiz7_helpers.c deck.c
	gcc quiz7.c deck.c quiz7_helpers.c quiz7_test.c -o test -g

play: quiz7.h quiz7.c quiz7_run.c deck.c quiz7_helpers.c
	gcc quiz7.c deck.c quiz7_helpers.c quiz7_run.c -o play -g

.PHONY: clean
clean:
	rm -f play
	rm -f test
