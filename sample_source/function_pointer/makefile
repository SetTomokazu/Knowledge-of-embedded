CFLAGS=-v
BRC=brc32
TARGET=function_pointer.exe
SOURCES=Scheduler.c TaskA.c TaskB.c
OBJS=Scheduler.obj TaskA.obj TaskB.obj
RESFILE=
HEADERS=
clean: $(TARGET)
	@erase $(OBJS) $(RESFILE) *.tds
$(TARGET): $(OBJS)
	$(CC) -e$(TARGET) $(CFLAGS) $(OBJS)
.c.obj:
	$(CC) $(CFLAGS) -o$*.obj /c $*.c
.cpp.obj:
	$(CC) $(CFLAGS) -o$*.obj /c $*.cpp
.rc.res:
	$(RC) $(RFLAGS) /r $*
