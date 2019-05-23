CC = g++
SRCS = main.cpp \
		university.cpp \
		person.cpp \
		staff.cpp \
		president.cpp \
		professor.cpp \
		student.cpp \
		course.cpp \
		TA.cpp \
		roster.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = Assignment2
CFLAGS = -std=c++11

Debug: $(OBJS)
		$(CC) -o $(EXEC) $(OBJS)

main.o: main.cpp university.h professor.h president.h course.h
		$(CC) $(CFLAGS) -c main.cpp

university.o: university.cpp university.h person.h staff.h professor.h event.h
		$(CC) $(CFLAGS) -c university.cpp

person.o: person.cpp person.h
		$(CC) $(CFLAGS) -c person.cpp

staff.o: staff.cpp staff.h
		$(CC) $(CFLAGS) -c staff.cpp

president.o: president.cpp president.h event.h
		$(CC) $(CFLAGS) -c president.cpp

professor.o: professor.cpp professor.h university.h person.h
		$(CC) $(CFLAGS) -c professor.cpp

student.o: student.cpp student.h
		$(CC) $(CFLAGS) -c student.cpp

course.o: course.cpp course.h
		$(CC) $(CFLAGS) -c course.cpp

TA.o: TA.cpp TA.h
		$(CC) $(CFLAGS) -c TA.cpp

roster.o: roster.cpp roster.h
		$(CC) $(CFLAGS) -c roster.cpp

clean:
		rm -f $(OBJS)
