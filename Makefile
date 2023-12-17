CC ?= gcc
BUILD_DIR ?= ./build
PROJ_DIR = .

# Source files common to all targets
SRC_FILES += \
	$(PROJ_DIR)/src/foodle_db/foodle_db.c \

# Include folders common to all targets
INC_FOLDERS += \
	$(PROJ_DIR)/src/foodle_db \
	$(PROJ_DIR)/src/foodle_types \

INC_PARAMS=$(foreach d, $(INC_FOLDERS), -I$d)

# Optimization flags
OPT += -O3 -g3

# C flags common to all targets
# CFLAGS += $(OPT)
CFLAGS += $(INC_PARAMS)
CFLAGS += $(shell pkg-config --cflags mysqlclient)
CFLAGS += $(shell pkg-config --libs mysqlclient)


.PHONY: foodle_db
foodle_db:
	@echo "Building database_api"
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(BUILD_DIR)/foodle_db