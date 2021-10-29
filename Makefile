
CC = gcc
EXTERN_LIBS = x11 xfixes cairo librsvg-2.0 glib-2.0
LIBS = `pkg-config --libs $(EXTERN_LIBS)`
INCLUDE = `pkg-config --cflags $(EXTERN_LIBS)`

CFLAGS = -g -Wall

TARGET = gnu-notch

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS) $(INCLUDE)

clean:
	$(RM) $(TARGET)