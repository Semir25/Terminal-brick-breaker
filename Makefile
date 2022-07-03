CC = clang++
OBJS = main.o terminal_size.o shape_gen.o vectorize.o

brick_breaker: $(OBJS)
	clang++ $(OBJS) -o $@

run: brick_breaker
	./brick_breaker

clean:
	rm -f a.out
	rm -f *.o
	rm -f brick_breaker

%.o: %.cpp
	$(CC) -c $< -o $@

