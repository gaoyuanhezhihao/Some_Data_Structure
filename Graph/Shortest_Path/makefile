CC :=clang++
LD :=clang++
SRCDIR := src
HEADER_DIR := include
BUILDDIR := build
TARGET :=bin/runner

SRCEXT:=cpp
INCEXT:=h
SOURCES:=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
HEADERS:=$(shell find $(HEADER_DIR) -type f -name *.$(INCEXT))
OBJECTS:=$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS:= -std=c++11 
LDFLAGS:= 
INC:= -I include

$(TARGET):$(OBJECTS)
	@echo "Linking..."
	@echo "$(LD) $^ -o $(TARGET) $(LIB)"
	$(LD) -o $(TARGET)  $^ $(LDFLAGS) 
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)  $(HEADER_DIR)/%.$(INCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
clean:
	@echo "cleaning...";
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)";
	$(RM) -r $(BUILDDIR) $(TARGET)
.PHONY:clean
