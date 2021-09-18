OBJS = lunt_kase_assn4.o 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXE = WordFrequency.exe

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

lunt_kase_assn4.o: templatedBST.h lunt_kase_assn4.cpp wf_analyzer.h 
	$(CC) $(CFLAGS) lunt_kase_assn4.cpp

clean:
	rm -v *.o *~