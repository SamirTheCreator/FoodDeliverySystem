CC = gcc
SRC_DIR := ./src
BUILD_DIR := ./build

# Source files
DATABASE_SRC += \
	$(SRC_DIR)/foodle_db/foodle_db.c

SERVER_SRC += \
	$(SRC_DIR)/server/server.c \
	$(SRC_DIR)/server/handlers.c
	

CLIENT_SRC += \
	$(SRC_DIR)/client/client.c \
	$(SRC_DIR)/client/account.c \
	$(SRC_DIR)/client/customer.c \
	$(SRC_DIR)/client/restaurant.c \
	$(SRC_DIR)/client/dasher.c

# Include folders common to all targets
INC_FOLDER += $(SRC_DIR)/foodle_types

#INC_PARAMS=$(foreach d, $(INC_FOLDER), -I$d)
INC_PARAMS += -I$(INC_FOLDER)

# Optimization flags
OPT += -O3 -g3

# C flags common to all targets
#CFLAGS += $(OPT)
CFLAGS += $(INC_PARAMS)
CFLAGS += $(shell pkg-config --cflags mysqlclient)
CFLAGS += $(shell pkg-config --libs mysqlclient)

build: server client
	@echo "Building project"

server: mkdir
	@echo "Building $@"	
	@$(CC) $(CFLAGS) $(SERVER_SRC) $(DATABASE_SRC) -o $(BUILD_DIR)/$@ -lmysqlclient
	
client: mkdir
	@echo "Building $@"
	@$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(BUILD_DIR)/$@
	
mkdir:	
	@mkdir -p $(BUILD_DIR)

.PHONY: clean

clean:
	@echo "Deleting executables"
	@rm -rf $(BUILD_DIR)

