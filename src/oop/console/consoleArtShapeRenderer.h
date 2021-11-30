#include "../shapes/models/rectangle.h"
#include "../shapes/models/abstractions/shape.h"
#include "consoleEssentials.h"

class ConsoleArtShapeRenderer
{
    Shape *_obj;
    PIXELDATA _pixelData;
    COORD _lastPos, _updPos;

    void updObjShadow(PIXELDATA **buffer, u_int height, u_int width, int color)
    {
        const auto obj = static_cast<RectShape *>(_obj);
        auto halfSizeY = obj->GetY() / 2;
        auto halfSizeX = obj->GetX() / 2;
        for (u_int i = _lastPos.Y - halfSizeY; i < _lastPos.Y + halfSizeY; i++)
            for (u_int j = _lastPos.X - halfSizeX; j < _lastPos.X + halfSizeX; j++)
                if (i > 0 && i < height &&
                    j > 0 && j < width) // cull pixels
                    buffer[i][j].color = color;
    }

    void rectShapeCopyStrategy(PIXELDATA **buffer, int height, int width)
    {
        // fill last position with background color
        updObjShadow(buffer, height, width, 0);

        // update object position for renderer frame
        _lastPos = _updPos;

        // calculate new dimensions
        updObjShadow(buffer, height, width, _pixelData.color);
    }

public:
    void CopyTo(PIXELDATA **buffer, int height, int width)
    {
        if (_obj != nullptr)
            rectShapeCopyStrategy(buffer, height, width);
    }

    void UpdateColor(int color)
    {
        PIXELDATA p;
        p.color = color;
        _pixelData = p;
    }

    void UpdatePosition(int x, int y)
    {
        COORD newPos;
        newPos.X = x;
        newPos.Y = y;
        _updPos = newPos;
    }

    void UpdateData(RectShape &obj)
    {
        _obj = &obj;
    }
};