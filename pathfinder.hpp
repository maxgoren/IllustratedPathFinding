#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP
#include <queue>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "Map.hpp"
using namespace std;

namespace std {
    template<> struct hash<Tile> {
        std::size_t operator()(const Tile& p) const noexcept {
            return std::hash<int>()(p.x ^ (p.y << 16));
        }
    };
}

class PriorityQueue {
    private:
        typedef std::pair<int, Tile> pqelem_t;
        std::priority_queue<pqelem_t, std::vector<pqelem_t>, greater<pqelem_t> > pq; 
    public:
        void put(int p, Tile t) {
            pqelem_t topush = make_pair(p, t);
            pq.push(topush);
        }
        Tile get()
        {
            Tile best = pq.top().second;
            pq.pop();
            return best;
        }
        bool empty() const {
            return pq.empty();
        }
        int size() const {
            return pq.size();
        }
};


class PathFinder {
    private:
        std::unordered_map<Tile, Tile> camefrom;
        std::unordered_map<Tile, int> cost;
        std::array<Point, 4> compass;
        vector<Tile> path;
        PriorityQueue pq;
        bool found;
    public:
        PathFinder()
        {
            compass[0] = Point(-1, 0);
            compass[1] = Point(0, -1);
            compass[2] = Point(1, 0);
            compass[3] = Point(0, 1);
        }
        inline int heuristic(Tile a, Tile b) {
            return std::abs(a.x - b.x) + std::abs(a.y - b.y);
        }
        void find(Map& board, Tile start, Tile goal) {
            camefrom.clear();
            cost.clear();
            path.clear();
            found = false;
            camefrom[start] = start;
            cost[start] = 0;
            pq.put(0, start);
            while (!pq.empty())
            {
                Tile curr = pq.get();
                cout<<"Pop: "<<curr.x<<"/"<<curr.y<<"\n";
                if (curr == goal) {
                    found = true;
                    break;
                }
                for (int i = 0; i < compass.size(); i++) {
                    Tile next = board.map[curr.y + compass[i].y][curr.x+compass[i].x];
                    if (board.onMap(next) && board.map[next.y][next.x].canWalk) {
                        int nc = cost[curr] + board.map[next.y][next.x].cost;
                        if (cost.find(next) == cost.end() || nc < cost[next]) {
                            cost[next] = nc;
                            camefrom[next] = curr;
                            pq.put(nc + heuristic(next, goal), next);
                            cout<<"Push: "<<next.x<<"/"<<next.y<<"\n";
                        }
                    }
                }
            }
            if (found)
            {
                path.clear();
                for (Tile crawl = goal; crawl != start; crawl = camefrom[crawl])
                {
                    crawl.symbol='*';
                    path.push_back(crawl);
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
            }
        }
        vector<Tile> getPath()
        {
            return path;
        }
};

#endif