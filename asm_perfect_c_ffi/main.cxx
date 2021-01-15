#define corydale_noinline __attribute__((__noinline__))

extern void abort();
using int32_t = int;

namespace Corydale
{
    using StatusCode = int;
}

namespace Corydale::Drawing
{
    struct Canvas final
    {
        int32_t m_Width;
        int32_t m_Height;

        corydale_noinline StatusCode DrawRectangle(int32_t x, int32_t y, int32_t w, int32_t h) noexcept
        {
            abort();
            return 0;
        }
    };

    extern corydale_noinline StatusCode DrawRectangle(Canvas& canvas, int32_t x, int32_t y, int32_t w, int32_t h) noexcept
    {
        abort();
        return 0;
    }
}

using Corydale__Drawing__Canvas__Handle = struct Corydale__Drawing__Canvas*;

extern "C" int Corydale__Drawing__Canvas__DrawRectangle_Free(
    Corydale__Drawing__Canvas__Handle Handle,
    int32_t X,
    int32_t Y,
    int32_t W,
    int32_t H) noexcept
{
    return Corydale::Drawing::DrawRectangle(*reinterpret_cast<Corydale::Drawing::Canvas*>(Handle), X, Y, W, H);
}

extern "C" int Corydale__Drawing__Canvas__DrawRectangle_Method(
    Corydale__Drawing__Canvas__Handle Handle,
    int32_t X,
    int32_t Y,
    int32_t W,
    int32_t H) noexcept
{
    return reinterpret_cast<Corydale::Drawing::Canvas*>(Handle)->DrawRectangle(X, Y, W, H);
}
