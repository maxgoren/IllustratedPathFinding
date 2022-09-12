#include <BearLibTerminal.h>
#include "Map.hpp"
#include "Actor.hpp"
#include "pathfinder.hpp"

class Engine {
    private:
        Map board;
        Actor player;
        PathFinder pf;
        int width;
        int height;
    public:
        Engine(int w, int h)
        {
            width = w;
            height = h;
            board = Map(w, h);
            player = Actor(10, 10);
        }
        void mainLoop()
        {
            char kp;
            bool inplay = true;
            while (inplay) {
                if (terminal_has_input()) {
                    kp = terminal_read();
                    switch (kp) {
                        case TK_Q:
                            inplay = false;
                            break;
                        case TK_UP: player.move(board, 0, -1); break;
                        case TK_DOWN: player.move(board, 0, 1); break;
                        case TK_LEFT: player.move(board, -1, 0); break;
                        case TK_RIGHT: player.move(board, 1, 0); break;
                        case TK_P: pf.find(board, board.map[player.location.y][player.location.x], board.map[11][63]); break;
                        default:
                            break;
                    }
                }
                render();
            }
        }
        void render()
        {
            terminal_clear();
            board.render();
            player.render();
            vector<Tile> p = pf.getPath();
            if (!p.empty()) {
                for (Tile t : p)
                {
                    terminal_put(t.x, t.y, t.symbol);
                }
            }
            terminal_put(63, 11, '%');
            terminal_refresh();
        }
};