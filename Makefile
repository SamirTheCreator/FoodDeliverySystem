CC = gcc
SRC_DIR := ./src
BUILD_DIR := ./build

# Source files
DATABASE_SRC += \
	$(SRC_DIR)/foodle_db/foodle_db.c

SERVER_SRC += \
	$(SRC_DIR)/server/main.c \
	$(SRC_DIR)/server/handlers.c
	

CLIENT_SRC += \
	$(SRC_DIR)/client/GUI/LoginPage.c \
	$(SRC_DIR)/client/data_transfer.c \
	$(SRC_DIR)/client/account.c \
	$(SRC_DIR)/client/customer.c \
	$(SRC_DIR)/client/restaurant.c \
	$(SRC_DIR)/client/dasher.c

# Include folders common to all targets
INC_FOLDERS += \
	$(SRC_DIR)/foodle_types \
	$(SRC_DIR)/foodle_db

INC_PARAMS=$(foreach d, $(INC_FOLDERS), -I$d)

# Optimization flags
OPT += -O3 -g3

# C flags common to all targets
#CFLAGS += $(OPT)
CFLAGS += $(INC_PARAMS)
CFLAGS += $(shell pkg-config --cflags mysqlclient)
CFLAGS += $(shell pkg-config --libs mysqlclient)

all: server client
	@echo "Building project"

server: mkdir
	@echo "Building $@"	
	@$(CC) $(SERVER_SRC) $(DATABASE_SRC) -o $(BUILD_DIR)/$@ -Wno-format-overflow $(CFLAGS)
	
client: mkdir
	@echo "Building $@"
	@$(CC) $(CLIENT_SRC) -o $(BUILD_DIR)/$@ -Wall -Wextra -g -Wno-format -Wno-deprecated-declarations -Wno-format-security $(shell pkg-config --cflags --libs gtk+-3.0) -export-dynamic -lm $(CFLAGS)

mkdir:	
	@mkdir -p $(BUILD_DIR)
	@cp $(SRC_DIR)/client/GUI/*.glade $(BUILD_DIR)/
	@cp -r $(SRC_DIR)/client/GUI/images $(BUILD_DIR)/

.PHONY: clean

clean:
	@echo "Deleting executables"
	@rm -rf $(BUILD_DIR)

