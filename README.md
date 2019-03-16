Description:
The problem to solve is following:
    You monitor devices, which are sending data to you.
    Each device have a unique name.
    Each device produces measurements.

Challenge is:
    Compute number of messages you got or read from the devices.


Solution:
1. subdirectory .vscode contains settings for Visual Studio Code which was used by me to develop the receiver (server) and the sender - device simulator (client)
2. all files are in this directory
    server.cpp - required by the callenge
    client.cpp - device simulator
    common.h   - header file for both cpp files

How to build:
Makefile is included so call "make" command only.
The result of the build should be 2 executable files (server and client).

How to run:
Open the 1st terminal and start the server "./server".
Open the 2nd terminal and start the client "./client uniqueName measurementValue".
Or you can use the runner.sh script which generates many clients with random names and values

How it works:
The server starts 2 threads: message receiver and statistic printer.
Message receiver waits for some data and stores number of messages to the map.
Statistic printer shows each 5 seconds number of messages from the map.