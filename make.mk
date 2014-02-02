
-include $(OBJFILES:.o=.d)

#Compile object files
obj/%.o: src/%.cpp
	$(CC) $(CPP_COMPILE_FLAGS) -MMD $(INCLUDE_DIR) $(DEFINES) -c -o $@ $<

# All Target
all: $(TARGET)

# Tool invocations
$(TARGET): $(OBJS)
	@$(ECHO) 'Building target: $@'
	$(CC) $(CPP_LINK_FLAGS) $(LIBS_DIR) -o $@ $(OBJS) $(LIBS)
	@$(ECHO) 'Finished building target: $@'
	@$(ECHO) ' '

# Other Targets
clean:
	-$(RM) obj/* $(TARGET)
	-@$(ECHO) ' '

.PHONY: all clean dependents
.SECONDARY:
