CC :=g++ -g
LD :=g++ -g
SRCDIR := src
BUILDDIR := build
TARGET :=bin/runner

SRCEXT:=cpp
SOURCES:=$(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS:=$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEP:=$(OBJECTS:%.o=%.d)
CFLAGS:= -std=c++11 
LDFLAGS:= 
INC:= -I include

$(TARGET):$(OBJECTS)
	@echo "Linking..."
	@echo "$(LD) $^ -o $(TARGET) $(LIB)"
	$(LD) -o $(TARGET)  $^ $(LDFLAGS) 

-include $(DEP)
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(sort $(dir $(OBJECTS)))
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"
	$(CC) $(CFLAGS) $(INC) -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

	#$(CC) $(CFLAGS)  -MMD -c -o $@ $<
clean:
	@echo "cleaning...";
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)";
	$(RM) -r $(BUILDDIR) $(TARGET)
.PHONY:clean
