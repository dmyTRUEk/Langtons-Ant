// this file contain World class

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "SaveScreenshot.cpp"
#include "Random.cpp"
#include "Color.cpp"

using namespace std;



const int world_size = 500;

bool working = true;





class Cell
{
public:
    //int id;
    //string name;

    int rotate;
    Color color;

    Cell (int _rotate, Color _color)
    {
        init(_rotate, _color);
    }

    void init (int _rotate, Color _color)
    {
        rotate = _rotate;
        color  = _color;
    }
};





int delay = 1e1;



Cell nothing( 0, Color(63, 63, 63));
Cell white  (-1, Color(255, 255, 255));
Cell red    (+1, Color(255, 0  , 0  ));
Cell green  (-1, Color(0  , 255, 0  ));
Cell cyan   (-1, Color(0  , 255, 255));
Cell yellow (-1, Color(255, 255, 0  ));
Cell pink   (-1, Color(255, 127, 255));

Cell grey   (+1, Color(192, 192, 192));
Cell red2   (+1, Color(127,   0,   0));
Cell green2 (+1, Color(  0, 127,   0));
Cell blue   (-1, Color(  0,   0, 255));
Cell grey2  (-1, Color(127, 127, 127));



Cell program[] =
{
    white,
    red,
    green,
    cyan,
    yellow,
    pink,

    grey,
    red2,
    green2,
    blue,
    grey2,
};





long long int step = 0;

class World
{
public:
    int at [world_size][world_size];
    int ant_x, ant_y, ant_angle;

    World (int x=0)
    {
        init(x);
    }

    void init (int _x)
    {
        for (int y = 0; y < world_size; y++)
        {
            for (int x = 0; x < world_size; x++)
            {
                at[x][y] = -1;
            }
        }

        ant_x = world_size/2;
        ant_y = world_size/2;
        ant_angle = 1;
        at[ant_x][ant_y] = _x;
    }

    int to_range (int x, int n)
    {
        if (x >= 0)
        {
            return x % n;
        }
        else
        {
            int ans = x;
            while (ans < 0)
                ans += n;
            return ans;
        }
    }

    void process ()
    {
        if (at[ant_x][ant_y] == -1)
        {
            at[ant_x][ant_y] = 1;       // that means, that this cell will be program[1]
        }
        else
        {
            // change cell color to next
            at[ant_x][ant_y] = (at[ant_x][ant_y] + 1) % (sizeof(program)/sizeof(*program));
        }

        // rotate ant on angle, that specified in program
        //ant_angle = (ant_angle + program[at[ant_x][ant_y]].rotate) % 4;
        ant_angle = to_range( ant_angle + program[at[ant_x][ant_y]].rotate, 4 );

        switch (ant_angle)
        {
            case 0:
                ant_x++;
                break;
            case 1:
                ant_y++;
                break;
            case 2:
                ant_x--;
                break;
            case 3:
                ant_y--;
                break;
            default:
                cout << "Error -> World.cpp -> class World -> process -> unknown ant_angle =" << ant_angle << "\n";
                working = false;
                break;
        }

        if ( ant_x < 0 || ant_x >= world_size || ant_y < 0 || ant_y >= world_size )
        {
            working = false;
        }

        step++;
    }

    string to_String ()
    {
        string ans;
        ans = ans + "world = {\n";
        ans = ans + "    ant_x = " + to_string(ant_x) + "\n";
        ans = ans + "    ant_y = " + to_string(ant_y) + "\n";
        ans = ans + "    ant_angle = " + to_string(ant_angle) + "\n";
        ans = ans + "\n";

        for (int y = 0; y < world_size; y++)
        {
            ans += "    ";
            for (int x = 0; x < world_size; x++)
            {
                ans = ans + to_string(at[x][y]) + " ";
            }
            ans += "\n";
        }
        ans += "}";
        return ans;
    }

};





World world;



void startCalculating ()
{
    //initRandomFunc(-1);
    world.init(-1);

    while (working) {
        //cout << world.to_String() << "\n\n\n";
        world.process();
        //if (step % 10000000 == 0) cout << "step = " << step << "\n";
        usleep(delay);
    }

    //cout << world.to_String() << "\n\n\n";

    cout << "\n --- Calculating finished --- \n";
}
