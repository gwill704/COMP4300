
#include "Vec2.hpp"
#include "Entity.hpp"
#include <cmath>
#include <algorithm>

namespace Physics
{
    Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        // TODO: retun the overlap rectangle size of a and b
        Vec2f delta       = Vec2f ( std::abs(a->get<CTransform>().pos.x - b->get<CTransform>().pos.x),
                                    std::abs(a->get<CTransform>().pos.y - b->get<CTransform>().pos.y));
        Vec2f bbA        = a->get<CBoundingBox>().halfSize;
        Vec2f bbB        = b->get<CBoundingBox>().halfSize;
        Vec2f overlap = Vec2f ( bbA.x + bbB.x - delta.x, bbA.y + bbB.y - delta.y );
        if ( overlap.x < 0 || overlap.y < 0 ) overlap = Vec2f (0, 0);
        return overlap;
    }

    Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        // TODO: return previous overlap, of a and b (use the previous positions)
        Vec2f delta       = Vec2f ( std::abs(a->get<CTransform>().prevPos.x - b->get<CTransform>().prevPos.x),
                                    std::abs(a->get<CTransform>().prevPos.y - b->get<CTransform>().prevPos.y));
        Vec2f bbA        = a->get<CBoundingBox>().halfSize;
        Vec2f bbB        = b->get<CBoundingBox>().halfSize;
        Vec2f overlap = Vec2f ( bbA.x + bbB.x - delta.x, bbA.y + bbB.y - delta.y );
        return overlap;
    }
}
