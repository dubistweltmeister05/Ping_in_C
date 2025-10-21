/* ping.h */


#pragma once
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#pragma GCC diagnostic ignored "-Wformat-truncation="
#pragma GCC diagnostic push

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "birchutils.h"

#define packed __attribute__((packed))

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;


int main(int,char**);

struct s_icmp{
	int8 type;
	int8 code;
	int16 checksum;
	int8 data[];
};

typedef struct s_icmp icmp;

icmp* make_icmp(int8, int8, int8*, int16);


