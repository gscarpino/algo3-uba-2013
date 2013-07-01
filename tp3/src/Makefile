RM := rm -rf
CC = g++

SOURCES_EXACTO = exacto_main.cpp exacto.cpp Grafo.cpp
SOURCES_GOLOSO = goloso_main.cpp goloso.cpp Grafo.cpp
SOURCES_LOCAL = local_main.cpp local.cpp goloso.cpp Grafo.cpp
SOURCES_GRASP = grasp_main.cpp grasp.cpp goloso.cpp local.cpp Grafo.cpp

TARGET_EXACTO = exacto
TARGET_GOLOSO = goloso
TARGET_LOCAL = local
TARGET_GRASP = grasp

OBJS_EXACTO = $(SOURCES_EXACTO:.cpp=.o)
OBJS_GOLOSO = $(SOURCES_GOLOSO:.cpp=.o)
OBJS_LOCAL = $(SOURCES_LOCAL:.cpp=.o)
OBJS_GRASP = $(SOURCES_GRASP:.cpp=.o)
CPPFLAGS= -std=c++0x -lrt

# All Target
all: exacto local goloso grasp

exacto:$(OBJS_EXACTO) 
	$(CC) $(LDFLAGS) $(OBJS_EXACTO) -o $(TARGET_EXACTO)

local:$(OBJS_LOCAL) 
	$(CC) $(LDFLAGS) $(OBJS_LOCAL) -o $(TARGET_LOCAL)

goloso:$(OBJS_GOLOSO) 
	$(CC) $(LDFLAGS) $(OBJS_GOLOSO) -o $(TARGET_GOLOSO)

grasp:$(OBJS_GRASP) 
	$(CC) $(LDFLAGS) $(OBJS_GRASP) -o $(TARGET_GRASP)
	
%.o: %.cpp 
	g++  -c $< -o $@ $(CPPFLAGS)

# Other Targets
clean:
	-$(RM) $(OBJS1) $(TARGET)
	-@echo ' '

.PHONY: all clean dependents
