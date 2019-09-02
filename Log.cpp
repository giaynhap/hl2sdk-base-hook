#include "Log.h"
void LogWriter(const char text[])
{
	std::ofstream log_file(
		"log.txt", std::ios_base::out | std::ios_base::app);
	log_file << text << "\n";
}