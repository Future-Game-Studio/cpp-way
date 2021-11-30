#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "../shapes/models/abstractions/shape.h"
#include "../shapes/models/rectangle.h"
#include "../shapes/views/shapeConsoleView.h"
#include "../shapes/views/cylinderConsoleView.h"
#include "../shapes/controllers/mainController.h"
#include "consoleArt.h"

#ifndef CTRL
#define CTRL(c) ((c)&037)
#endif

void runConsoleArt()
{
    auto consoleArt = ConsoleArtHost();

    auto dataRenderer = ConsoleArtShapeRenderer();

    // we can already start to render
    consoleArt.Start();

    auto [height, width] = consoleArt.GetBounds();
    int posX = width / 2, posY = height / 2, color = 1;
    bool moveForward, moveDown, animateX, animateY;

    consoleArt.OnFrame(
        // we can pack this captures to struct, but who cares...
        [&dataRenderer, &posX, &posY, &color, &moveForward, &moveDown, &animateY, &animateX](PIXELDATA **buffer, int width, int height) -> void
        {
            // this lambda is called every on frame update
            if (animateX)
            {
                const int offsetX = width * 0.4; // 40% offset
                if (posX < width / 2 - offsetX)
                    moveForward = true;
                else if (posX > width / 2 + offsetX)
                    moveForward = false;
                if (moveForward)
                    posX++;
                else
                    posX--;
            }

            if (animateY)
            {
                const int offsetY = height * 0.3; // 30% offset
                if (posY < height / 2 - offsetY)
                    moveDown = true;
                else if (posY > height / 2 + offsetY)
                    moveDown = false;
                if (moveDown)
                    posY++;
                else
                    posY--;
            }

            dataRenderer.UpdatePosition(posX, posY);
            dataRenderer.UpdateColor(color);
            dataRenderer.CopyTo(buffer, height, width);
        });

    consoleArt.OnKeyCheck(
        [&posX, &posY, &consoleArt, &color, &animateY, &animateX]() -> void
        {
            auto p = getch();
            auto [height, width] = consoleArt.GetBounds();
            if (p >= '1' && p <= '9')
                color = p - '0';
            switch (p)
            {
            case 'c':
                if (++color > 14)
                    color = 1;
                break;
            case 'y':
                animateY = !animateY;
                break;
                break;
            case 'x':
                animateX = !animateX;
                break;
            case 75:
                if (--posX < 0)
                    posX = width - 1;
                break;
            case 77:
                if (++posX > width)
                    posX = 0;
                break;
            case 80:
                if (++posY > height)
                    posY = 0;
                break;
            case 72:
                if (--posY < 0)
                    posY = height - 1;
                break;
            case (CTRL('c')):
                consoleArt.Stop();
                break;
            }
        });

    // prepare model
    auto rectangleModel = std::make_shared<RectShape>(5, 5);

    auto abstractModel = std::weak_ptr<RectShape>(rectangleModel);

    auto abstractModelPtr = abstractModel.lock().get();
    // register the data-change event
    abstractModelPtr->RegisterDataChangeHandler(
        [&dataRenderer](RectShape &obj) -> void
        {
            dataRenderer.UpdateData(obj);
        });

    dataRenderer.UpdateData(*abstractModelPtr);
    dataRenderer.UpdateColor(rand() % 15 + 3);

    // blocking call
    consoleArt.Wait();
}