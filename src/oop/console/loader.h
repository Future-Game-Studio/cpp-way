#pragma once
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#define sleep(ms) Sleep(ms)
#endif

#ifdef __unix__
#include <unistd.h> // for sleep()
#endif

#include <future>

void animateCore(char t, int amimationDelay = 40)
{
    sleep(amimationDelay);
    std::cout << "\b" << t << std::flush;
}

void runLoader()
{
    sleep(2000);
    std::cout << "Warming up... " << std::flush;
    for (int i = 0; i < 10; i++)
    {
        animateCore('\\');
        animateCore('|');
        animateCore('/');
        animateCore('-');
    } 
}

std::future<void> runLoaderAsync()
{
    return std::async(std::launch::async, runLoader);
}