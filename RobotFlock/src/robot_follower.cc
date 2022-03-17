#include "robot_follower.h"
#include "enviro.h"
#include <string>
#include <cmath>
#include <chrono>

using namespace enviro;
using namespace std;

void MyRobotFollower::init()
{
    //std::cout << "Just spawned! My id is: " << id() << "\n";
    //Create follower channel for leader to communicate to 
    leader_ch = "FollowerPosition" + std::to_string(id());
    //std::cout << "Channel: " << train_coordinator_ch << "\n"; 
    watch(leader_ch, [this](Event e) {
                x_pos = e.value()[0]; 
                y_pos = e.value()[1];
                theta = e.value()[2];  
        });
    //Set random oscillation starting point
    //Set min and max distance agents are allowed to oscillate in.
    oscil_accum = rand() % 50 + 1;     // v2 in the range 1 to 100
    oscil_accum_max = oscil_accum * 2;
    oscil_accum_min = -1*oscil_accum_max; 
}

void MyRobotFollower::update()
{
    //Calculate x y offsets from leader to oscillate with respect to it's origin
    double new_x, new_y;
    new_x = x_offset(oscil_accum, x_pos, theta); 
    new_y = y_offset(oscil_accum, y_pos, theta); 
    //Use teleport for smoother positioning
    teleport(new_x, new_y, theta);
    //Create channel to return back sensors to leader
    leader_ch = "FollowerInfo" + std::to_string(id()); 
    emit( Event(leader_ch, {sensor_value(0), sensor_value(1), sensor_value(2)}) );
    //Tick up or down to oscillate agents
    if(tick)
    {
        //std::cout << "Ticking up!\n"; 
        if(oscil_accum < oscil_accum_max)
        {
            oscil_accum = oscil_accum + 0.5;
        }
        else
        {
            tick =  0; 
        }
    }
    if(!tick)
    {
        //std::cout << "Ticking down!\n"; 
        if(oscil_accum > oscil_accum_min)
        {
            oscil_accum = oscil_accum - 0.5;
        }
        else 
        {
            tick = 1;
        }
    }
}

double robot_pos_error(double robot_x, double robot_y, double goal_x, double goal_y)
{
    //Consider robot position error to be absolute difference between robot's x y position
    //and goal's x y position
    return abs(goal_x - robot_x) + abs(goal_y - robot_y);  
}

double x_offset(double f_offset, double rx, double rtheta)
{
    return rx - f_offset*cos(M_PI - rtheta + M_PI_2); 
}
double y_offset(double f_offset, double ry, double rtheta)
{
    return ry + f_offset*sin(M_PI - rtheta + M_PI_2); 
}