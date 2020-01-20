#include <csignal>

#include "../common/src/logger.hpp"
#include "palaceserver.hpp"

int main(int argc, char **argv)
{
	std::signal(SIGSEGV, &dumpStack);
	std::signal(SIGABRT, &dumpStack);
	
	return 0;
}
