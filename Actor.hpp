#ifndef ACTOR_HPP
#define ACTOR_HPP
#include <BearLibTerminal.h>
#include "Map.hpp"

class Actor {
    private:
        color_t color;
    public:
        Point location;
        Actor(int sx, int sy)
        {
            location.x = sx;
            location.y = sy;
            color = color_from_name("white");
        }
        Actor()
        {
            location.x = 10;
            location.y = 10;
            color = color_from_name("white");
        }
        bool canWalk(Map& map, Tile loc) {
            if (map.onMap(loc) && map.map[loc.y][loc.x].canWalk)
                return true;
            return false;
        }
        void move(Map& map, int dx, int dy) {
            Tile nextPos =  map.map[location.y + dy][location.x + dx];
            if (canWalk(map, nextPos)) {
                location = Point(nextPos.x, nextPos.y);
                color = color_from_name("white");
            } else {
                color = color_from_name("red");
            }
        }
        void render()
        {
            terminal_color(color);
            terminal_put(location.x, location.y, '@');
        }
};

#endif