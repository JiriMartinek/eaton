**Description:**<br>
The problem to solve is following:<br>
    You monitor devices, which are sending data to you.<br>
    Each device have a unique name.<br>
    Each device produces measurements.<br>

**Challenge is:**<br>
    Compute number of messages you got or read from the devices.<br>


**Solution:**<br>
1. subdirectory .vscode contains settings for Visual Studio Code which was used by me to develop the receiver (server) and the sender - device simulator (client)<br>
2. all files are in this directory<br>
    server.cpp - required by the callenge<br>
    client.cpp - device simulator<br>
    common.h   - header file for both cpp files<br>

**How to build:**<br>
Makefile is included so call "make" command only.<br>
The result of the build should be 2 executable files (server and client).<br>

**How to run:**<br>
Open the 1st terminal and start the server "./server".<br>
Open the 2nd terminal and start the client "./client uniqueName measurementValue".<br>
Or you can use the runner.sh script which generates many clients with random names and values.<br>

**How it works:**<br>
The server starts 2 threads: message receiver and statistic printer.<br>
Message receiver waits for some data and stores number of messages to the map.<br>
Statistic printer shows each 5 seconds number of messages from the map.<br>
