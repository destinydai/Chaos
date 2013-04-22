#pragma once


inline timespec* getTimeout(struct timespec* spec, unsigned numMs)
{
	struct timeval current;
	gettimeofday(&current,0);
	spec->tv_sec = current.tv_sec + ((numMs + current.tv_usec/1000)/1000);
	spec->tv_nsec = ((current.tv_usec/1000 + numMs)%1000) * 1000000;
	return spec;
}