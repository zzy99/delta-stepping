CC = g++

all: serial.exe serial-check.exe parallel.exe parallel-check.exe

serial.exe: serial.cpp
	$(CC) -o serial.exe serial.cpp -std=c++11

serial-check.exe: serial-check.cpp
	$(CC) -o serial-check.exe serial-check.cpp -std=c++11

parallel.exe: parallel.cpp
	$(CC) -o parallel.exe -fopenmp parallel.cpp -std=c++11

parallel-check.exe: parallel-check.cpp
	$(CC) -o parallel-check.exe -fopenmp parallel-check.cpp -std=c++11

clean:
	rm -f *~ serial.exe serial-check.exe parallel.exe parallel-check.exe
