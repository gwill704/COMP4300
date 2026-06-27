
#include "Vec2.hpp"
#include "Entity.hpp"
#include <algorithm>

namespace Physics
{
    Vec2f GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
          std::cout << "\n**OVERLAP**" << std::endl;
        // TODO: retun the overlap rectangle size of a and b
        auto & tA         = a->get<CTransform>();
        auto & tB         = b->get<CTransform>();
        auto & bbA        = a->get<CBoundingBox>();
        auto & bbB        = b->get<CBoundingBox>();
        
        std::cout << "pos (" << tA.pos.x << ", " << tA.pos.y << ")" << std::endl;
        std::cout << "pos B (" << tB.pos.x << ", " << tB.pos.y << ")" << std::endl;
        std::cout << "collR = (" << tA.pos.x << " + " << bbA.size.x << " - " << tB.pos.x
                  << ", "        << tA.pos.y << " + " << bbA.size.y << " - " << tB.pos.y << std::endl;
        std::cout << "collL = (" << tB.pos.x << " + " << bbB.size.x << " - " << tA.pos.x
                  << ", "        << tB.pos.y << " + " << bbB.size.y << " - " << tA.pos.y << std::endl;

        Vec2f collR = Vec2f ( tA.pos.x + bbA.size.x - tB.pos.x , tA.pos.y + bbA.size.y - tB.pos.y );
        Vec2f collL = Vec2f ( tB.pos.x + bbB.size.x - tA.pos.x , tB.pos.y + bbB.size.y - tA.pos.y );

        std::cout << "collR (" << collR.x << ", " << collR.y << ")\n";
        std::cout << "collL (" << collL.x << ", " << collL.y << ")\n";

        if (  ((collR.x > 0) && (collL.x > 0))  &&  ((collR.y > 0) && (collL.y > 0))  )
        {
          std::cout << "Entity with tag " << a->tag() << " collided with Entity tag " << b->tag() 
                    << std::endl << "with collision box of (" << std::min(collR.x, collL.x) << ", "
                    << std::min(collR.y, collL.y) << std::endl;
          return Vec2f( std::min(collR.x, collL.x), std::min(collR.y, collL.y) );
        }
        else
        {
          return Vec2f(0,0);
        }
    }

    Vec2f GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
          std::cout << "\n**PREVIOUS OVERLAP**" << std::endl;
        // TODO: return previous overlap, of a and b (use the previous positions)
        auto & tA         = a->get<CTransform>();
        auto & tB         = b->get<CTransform>();
        auto & bbA        = a->get<CBoundingBox>();
        auto & bbB        = b->get<CBoundingBox>();

        std::cout << "prevPos (" << tA.prevPos.x << ", " << tA.prevPos.y << ")" << std::endl;
        std::cout << "prevPos B (" << tB.prevPos.x << ", " << tB.prevPos.y << ")" << std::endl;
        std::cout << "collR = (" << tA.prevPos.x << " + " << bbA.size.x << " - " << tB.prevPos.x
                  << ", "        << tA.prevPos.y << " + " << bbA.size.y << " - " << tB.prevPos.y << std::endl;
        std::cout << "collL = (" << tB.prevPos.x << " + " << bbB.size.x << " - " << tA.prevPos.x
                  << ", "        << tB.prevPos.y << " + " << bbB.size.y << " - " << tA.prevPos.y << std::endl;
        Vec2f collR = Vec2f ( tA.prevPos.x + bbA.size.x - tB.prevPos.x , tA.prevPos.y + bbA.size.y - tB.prevPos.y );
        Vec2f collL = Vec2f ( tB.prevPos.x + bbB.size.x - tA.prevPos.x , tB.prevPos.y + bbB.size.y - tA.prevPos.y );

        std::cout << "prevPos (" << tA.prevPos.x << ", " << tA.prevPos.y << ")" << std::endl;
        std::cout << "collR (" << collR.x << ", " << collR.y << ")\n";
        std::cout << "collL (" << collL.x << ", " << collL.y << ")\n";

        if (  ((collR.x > 0) && (collL.x > 0))  &&  ((collR.y > 0) && (collL.y > 0))  )
        {
          std::cout << "Entity with tag " << a->tag() << " collided with Entity tag " << b->tag() 
                    << std::endl << "with collision box of (" << std::min(collR.x, collL.x) << ", "
                    << std::min(collR.y, collL.y) << std::endl;
          return Vec2f( std::min(collR.x, collL.x), std::min(collR.y, collL.y) );
        }
        else
        {
          return Vec2f(0,0);
        }
    }
}
