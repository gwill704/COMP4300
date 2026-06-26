
#include "Vec2.hpp"
#include "Entity.hpp"
#include <algorithm>

namespace Physics
{
    Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        // TODO: retun the overlap rectangle size of a and b
        auto & tA         = a->get<CTransform>();
        auto & tB         = b->get<CTransform>();
        auto & bbA        = a->get<CBoundingBox>();
        auto & bbB        = b->get<CBoundingBox>();

        Vec2f collR = Vec2f ( tA.pos.x + bbA.size.x - tB.pos.x , tA.pos.y + bbA.size.y - tB.pos.y );
        Vec2f collL = Vec2f ( tB.pos.x + bbB.size.x - tA.pos.x , tB.pos.y + bbB.size.y - tA.pos.y );

        if (  ((collR.x > 0) && (collL.x > 0))  &&  ((collR.y > 0) && (collL.y > 0))  )
        {
          std::cout << "Entity with tag " << a->tag() << " collided with Entity tag " << b->tag() 
                    << std::endl << "with collision box of (" << std::min(collR.x, collL.x) << ", "
                    << std::min(collR.y, collL.y) << std::endl;
          return Vec2f( std::min(collR.x, collL.x), std::min(collR.y, collL.y) );
        }
        
  
        return Vec2f(0,0);
    }

    Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        // TODO: return previous overlap, of a and b (use the previous positions)
        return Vec2f(0,0);
    }
}
