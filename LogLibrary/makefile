CC = clang++ -std=c++11
CGLAGS = -Wall -g
LDFLAGS = -pthread
hehe:asynLog_test.o asynLog.o logFile.o
	${CC} -o hehe asynLog_test.o asynLog.o logFile.o ${LDFLAGS}
asynLog_test.o:asynLog.h
	${CC} -c asynLog_test.cpp
asynLog.o:asynLog.h logFile.h fixBuffer.h
	${CC} -c asynLog.cpp
logFile.o:logFile.h
	${CC} -c logFile.cpp
.PHONY:clean
clean:
	rm *.o
