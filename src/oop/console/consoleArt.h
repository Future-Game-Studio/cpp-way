#pragma once
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <future>
#include <functional>
#include <exception>
#include <conio.h>
#include <tuple>
#ifdef _WIN32
#include <windows.h>
#include <winuser.h>
#define sleep(ms) Sleep(ms)
#elif __unix__
#include <unistd.h> // for sleep()
#endif
#include "consoleEssentials.h"
#include "consoleArtShapeRenderer.h"

class ConsoleArtHost
{
    UINT _backupConsoleCP;
    int _width, _height;
    PIXELDATA **_screenBuffer;
    std::future<void> _frameAsync;
    std::future<void> _frameKeysAsync;
    std::function<void(PIXELDATA **buffer, int width, int height)> _onFrameChanged;
    std::function<void()> _onKeyInputCheck;
    bool _isActive = false;
    int _frameInterval = 30;


    void prepareConsole()
    {
        _backupConsoleCP = GetConsoleOutputCP();
        SetConsoleOutputCP(437);
        hideCursor();
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int hasConsoleWidth = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        _width = 80;
        if (hasConsoleWidth)
        {
            _width = csbi.dwSize.X;
        }
        _height = csbi.srWindow.Bottom - csbi.srWindow.Top;
    }

    void prepareScreenBuffer()
    {
        _screenBuffer = new PIXELDATA *[_height];
        for (int i = 0; i < _height; i++)
        {
            _screenBuffer[i] = new PIXELDATA[_width];
        }
    }
    void finalizeScreenBuffer()
    {
        for (int i = 0; i < _height; i++)
        {
            delete[] _screenBuffer[i];
        }
        delete[] _screenBuffer;
        SetConsoleOutputCP(_backupConsoleCP);
    }

    void runFrameLoop()
    {
        _isActive = true;

        std::cout << "Starting renderer loop..." << std::endl;

        srand(time(NULL));

        try
        {
            while (_isActive)
            {
                printScreen(_width, _height, _screenBuffer);
                if (_onFrameChanged)
                    _onFrameChanged(_screenBuffer, _width, _height);
                sleep(_frameInterval);
            }
        }
        catch (std::exception &ex)
        {
            std::cout << "Unhandled error: " << ex.what() << std::endl;
        }
    }

    void runKeysLoop()
    {
        _isActive = true;

        try
        {
            while (_isActive)
            {
                if (_onKeyInputCheck)
                    _onKeyInputCheck();
            }
        }
        catch (std::exception &ex)
        {
            std::cout << "Unhandled error: " << ex.what() << std::endl;
        }
    }

public:
    ConsoleArtHost()
    {
    }

    void Start()
    {
        prepareConsole();
        prepareScreenBuffer();

        PIXELDATA se;
        se.elem = BLACK;
        se.color = 0;
        initScreen(_width, _height, _screenBuffer, se);
        _frameAsync = std::async(std::launch::async, &ConsoleArtHost::runFrameLoop, this);
        _frameKeysAsync = std::async(std::launch::async, &ConsoleArtHost::runKeysLoop, this);
    }

    std::tuple<int, int> GetBounds()
    {
        return std::make_tuple(_height, _width);
    }

    void OnKeyCheck(const std::function<void()> &onKeyCheck)
    {
        _onKeyInputCheck = onKeyCheck;
    }

    void OnFrame(const std::function<
                 void(PIXELDATA **buffer, int width, int height)>
                     &onFrameChanged)
    {
        _onFrameChanged = onFrameChanged;
    }

    void Wait()
    {
        _frameAsync.wait();
    }

    void Stop()
    {
        _isActive = false;

        // wait for thread to finish frame
        _frameAsync.wait();

        finalizeScreenBuffer();
    }
};
