# Makefile fulfilling #30

#Author: Travis Sanders
#Date Created: 03/13/14
#Last Modification Date: 03/16/14
#Lab/Project#: FINAL PROJECT

CXX = g++
CXXFLAGS = -std=c++0x
#CXXFLAGS = -g
#LDFLAGS = -lboost_date_timed

SRCS = travis_math.cpp
SRCS += battleships.cpp
SRCS += final_fantasy.cpp
SRCS += final.cpp

HEADERS = travis_math.h
HEADERS += battleships.h
HEADERS += final_fantasy.h

OBJS = travis_math.o
OBJS += battleships.o
OBJS += final_fantasy.o
OBJS += final.o

#target: dependencies
#	rule to build

test: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS} -o final

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)