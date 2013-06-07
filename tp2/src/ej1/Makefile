RM := rm -rf
TARGET = ej1
TARGET_PERFORMANCE = ej1_performance
OBJS1 = $(TARGET).o GrafoEj1.o
OBJS2 = $(TARGET_PERFORMANCE).o GrafoEj1.o
CPPFLAGS= -std=c++0x -lrt

# All Target
all: $(OBJS1) 
	g++  -o $(TARGET) $(OBJS1) $(CPPFLAGS)
	@echo ' '

%.o: %.cpp 
	g++  -c $< -o $@ $(CPPFLAGS)

# Other Targets
clean:
	-$(RM) $(OBJS1) $(TARGET)
	-@echo ' '

tiempos:
	g++  -o $(TARGET_PERFORMANCE) $(OBJS2) $(CPPFLAGS)
	
.PHONY: all clean dependents
