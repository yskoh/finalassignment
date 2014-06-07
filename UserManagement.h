#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

#ifndef  __1STVER_H__
#define __1STVER_H__

typedef struct person{
	int id;
	char name[10];
	char address[100];
	char phone[30];
} Person;

#endif
