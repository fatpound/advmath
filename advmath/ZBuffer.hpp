#pragma once

#include <cassert>

#include <limits>
#include <memory>

class ZBuffer
{
public:
    ZBuffer(int in_width, int in_height)
        :
        width(in_width),
        height(in_height),
        pBuffer(std::make_unique<float[]>(width* height))
    {

    }
    ~ZBuffer() = default;
    ZBuffer(const ZBuffer&) = delete;
    ZBuffer(ZBuffer&&) = delete;
    ZBuffer& operator = (const ZBuffer&) = delete;
    ZBuffer& operator = (ZBuffer&&) = delete;


public:
    const float& At(int x, int y) const
    {
        return const_cast<ZBuffer*>(this)->At(x, y);
    }
    float& At(int x, int y)
    {
        assert(x >= 0);
        assert(x < width);
        assert(y >= 0);
        assert(y < height);

        return pBuffer[y * width + x];
    }

    bool TestAndSet(int x, int y, float depth)
    {
        float& depthInBuffer = At(x, y);

        if (depth < depthInBuffer)
        {
            depthInBuffer = depth;

            return true;
        }

        return false;
    }

    void Clear()
    {
        const int nDepths = width * height;

        for (int i = 0; i < nDepths; i++)
        {
            pBuffer[i] = std::numeric_limits<float>::infinity();
        }
    }


private:
    int width;
    int height;

    std::unique_ptr<float[]> pBuffer;
};