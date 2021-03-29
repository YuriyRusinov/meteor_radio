CC = gcc
LD = gcc
CFLAGS  = -fpic -Wall $(PG_CFLAGS) $(DEFINES) $(PG_INC) $(PG_INC_SERVER)
LIBDIR = -L$(shell pg_config --libdir)
LDFLAGS = -shared $(LIBDIR)  
RM      = rm -f
MV	= mv
CP      = cp -f
MKDIR	= mkdir -p
INSTALL = install --mode 755
build_dir = ../bld
tmp_dir = ../.tmp

OBJ     = $(tmp_dir)/rand.o

TARGET  = librandgeneration.so

all: $(TARGET)
	$(MKDIR) $(build_dir)
	$(MV) $< $(build_dir)

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) $^ $(LIBDIR) -lpq -lm -ljpeg -lgsl -lgslcblas -o $@

$(tmp_dir)/%.o : %.cpp rand.h
	$(MKDIR) $(tmp_dir)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	$(RM) $(build_dir)/$(TARGET) $(tmp_dir)/*.o

install: $(TARGET)
	$(MKDIR) $(libdir)
	$(INSTALL) $(TARGET) $(libdir)

uninstall:
	$(RM) $(libdir)/$(TARGET)
