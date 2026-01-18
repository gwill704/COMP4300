
#include "Vec2.hpp"
#include "Entity.hpp"

namespace Physics
{
    Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        // TODO: retun the overlap rectangle size of a and b
        return Vec2f(0,0);
    }

    Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        // TODO: return previous overlap, of a and b (use the previous positions)
        return Vec2f(0,0);
    }
}
