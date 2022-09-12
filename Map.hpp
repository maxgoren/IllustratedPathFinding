#ifndef MAP_HPP
#define MAP_HPP
#include <vector>
#include <BearLibTerminal.h>
using namespace std;
class Point {
    public:
        int x;
        int y;
        Point(int X, int Y) {
            x = X;
            y = Y;
        }
        Point(const Point& p) {
            x = p.x;
            y = p.y;
        }
        Point() { x = 0; y = 0; }
        
};

class Tile  : public Point {
    public:
        bool canWalk;
        char symbol;
        int cost;
        Tile(int x, int y, char s, bool cw) : Point(x, y) {
            canWalk = cw;
            symbol = s;
            cost = 0;
        }
        Tile() : Point(0, 0)
        {
            symbol = '#';
            canWalk = false;
            cost = 0;
        }
        Tile(const Tile& p)
        {
            x = p.x;
            y = p.y;
            canWalk = p.canWalk;
            cost = p.cost;
            symbol = p.symbol;
        }
        bool operator==(const Tile& o) const {
            return (x == o.x && y == o.y);
        }
        bool operator!=(const Tile& o) const {
            return !(*this==o);
        }
        bool operator<(const Tile& o) const {
            return (x == o.x && y == o.y && cost < o.cost);
        }
};

class Map {
    public:
        int width;
        int height;
        vector<vector<Tile>> map;
        Map(int w, int h) {
            width = w;
            height = h;
            map = vector<vector<Tile>>(height, vector<Tile>(width));
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++) {
                    map[y][x].x = x;
                    map[y][x].y = y;
                    map[y][x].cost = 100;
                    map[y][x].canWalk = false;
                    map[y][x].symbol = '#';
                }
            }
            makeRooms();
        }
        Map() {
            width = 80;
            height = 40;
            map = vector<vector<Tile>>(height, vector<Tile>(width));
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++) {
                    map[y][x].x = x;
                    map[y][x].y = y;
                    map[y][x].cost = 100;
                    map[y][x].canWalk = false;
                    map[y][x].symbol = '#';
                }
            }
            makeRooms();
        }
        void dig_room(Point start, int width, int height) {
            for (int y = start.y; y < start.y+height; y++) {
                for (int x = start.x; x < start.x + width; x++) {
                    map[y][x].canWalk = true;
                    map[y][x].symbol = ' ';
                    map[y][x].cost = 1;
                }
            }
        }
        void makeRooms()
        {
            dig_room(Point(3,3),22, 25);
            dig_room(Point(28,28), 30, 3);
            dig_room(Point(23,25), 6, 6);
            dig_room(Point(55, 30), 3, 7);
            dig_room(Point(33,5), 35, 20);
            dig_room(Point(68,20), 10, 2);
            dig_room(Point(58, 35), 19, 2);
            dig_room(Point(75, 20), 3, 17);
        }
        void render()
        {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    terminal_put(x, y, map[y][x].symbol);
                }
            }
        }
        bool onMap(Tile loc) {
            return (loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height);
        }
};

#endif