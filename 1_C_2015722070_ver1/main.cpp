#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"//main.cc includes Manager header file

int main(void)//start main function
{
	Manager ds;//declare manager class
	ds.run("command.txt");//call run function

	return 0;//return 0
}//end