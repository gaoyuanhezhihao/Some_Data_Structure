CC :=g++
LD :=g++
SRCDIR := src
BUILDDIR := build
TARGET :=bin/runner

SRCEXT:=cpp
SOURCES:=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS:=$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS:= -std=c++11 
LDFLAGS:= 
INC:= -I include

$(TARGET):$(OBJECTS)
	@echo "Linking..."
	@echo "$(LD) $^ -o $(TARGET) $(LIB)"
	$(LD) -o $(TARGET)  $^ $(LDFLAGS) 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
clean:
	@echo "cleaning...";
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)";
	$(RM) -r $(BUILDDIR) $(TARGET)
.PHONY:clean
