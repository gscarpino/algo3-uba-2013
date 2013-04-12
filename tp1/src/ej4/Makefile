RM := rm -rf
TARGET = ej4
OBJS1 = $(TARGET).o Pieza.o Tablero.o Solucion.o
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

.PHONY: all clean dependents
