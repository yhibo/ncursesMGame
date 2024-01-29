# Compiler
CC = g++

# Flags
CFLAGS = -Wall -Wextra -std=c++11
RELEASEFLAGS = -O2
LDFLAGS = -lncurses -pthread

# Directories
BUILDDIR = build

# Source files
COMMON_SRCS = $(wildcard Common/*.cpp)
CLIENT_SRCS = $(wildcard Client/*.cpp) $(COMMON_SRCS)
SERVER_SRCS = $(wildcard Server/*.cpp) $(COMMON_SRCS)

# Targets
.PHONY: all client server clean release run

all: client server

client: | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/client $(CLIENT_SRCS) $(LDFLAGS)

server: | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/server $(SERVER_SRCS) $(LDFLAGS)

release: CFLAGS += $(RELEASEFLAGS)
release: all

clean:
	rm -rf $(BUILDDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

run:
	@command -v tmux >/dev/null 2>&1 || { echo >&2 "tmux not installed. Aborting."; exit 1; }
	@tmux new-session -d -s my_session './build/server 8080; read'
	@tmux split-window -t my_session -h './build/client 127.0.0.1 8080 a; read'
	@tmux split-window -t my_session -h './build/client 127.0.0.1 8080 b; read'
	@tmux -2 attach-session -t my_session