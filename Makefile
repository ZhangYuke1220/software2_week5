CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lm
OBJS = initial.o func1.o optimize.o mtfuji.o
TARGET = mtfuji

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET) 