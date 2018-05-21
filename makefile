.PHONY:clean
main:hash.c
	gcc -g -o $@ $^
clean:
	rm main
