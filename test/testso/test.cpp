#include "log.h"

#include <iostream>

int main(int argc, char *argv[])
{
	log_init("./testlog");
	log_info("mytest");

	return 0;
}