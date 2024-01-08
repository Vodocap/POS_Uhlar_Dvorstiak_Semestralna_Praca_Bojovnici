TARGET_EXEC := Semstralka_Bojovnicic

BUILD_DIR := ./build
SRC_DIRS := ./Server ./Client ./Common

SRCS_CLIENT := $(wildcard ./Client/*.cpp)
SRCS_SERVER := $(wildcard ./Server/*.cpp)
SRCS_COMMON := $(wildcard ./Common/*.cpp)

OBJS_CLIENT := $(SRCS_CLIENT:%=$(BUILD_DIR)/%.o) $(SRCS_COMMON:%=$(BUILD_DIR)/%.o)
OBJS_SERVER := $(SRCS_SERVER:%=$(BUILD_DIR)/%.o) $(SRCS_COMMON:%=$(BUILD_DIR)/%.o)

DEPS_CLIENT := $(OBJS_CLIENT:.o=.d)
DEPS_SERVER := $(OBJS_SERVER:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	g++ $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Client: $(OBJS_CLIENT)
	g++ $(OBJS_CLIENT) -o $(BUILD_DIR)/Semstralka_Client

$(BUILD_DIR)/Server: $(OBJS_SERVER)
	g++ $(OBJS_SERVER) -o $(BUILD_DIR)/Semstralka_Server

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS_CLIENT) $(OBJS_SERVER)
	# Commands to combine Client and Server into one executable (if needed)

.PHONY: server client all clean

server: $(BUILD_DIR)/Server
client: $(BUILD_DIR)/Client
all: server client
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS_CLIENT) $(DEPS_SERVER)