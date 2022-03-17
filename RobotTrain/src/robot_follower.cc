#include "robot_follower.h"
#include "enviro.h"
#include <string>

using namespace enviro;
using namespace std;

void MyRobotFollower::init()
{
    std::cout << "Just spawned! My id is: " << id() << "\n"; 
    //Watch unique channel created by the Train Coordinator Agent to reviece instructions on which
    //next position to go to
    train_coordinator_ch = "FollowerPosition" + std::to_string(id());
    std:: cout << "Channel: " << train_coordinator_ch << "\n"; 
    watch(train_coordinator_ch, [this](Event e) {
                x_pos = e.value()[0]; 
                y_pos = e.value()[1]; 
        });
}

void MyRobotFollower::update()
{
    //Move to x y position specified by train coordinator
    //If error is small, dampen movement to prevent crashing
    move_toward(x_pos, y_pos); 
    if(robot_pos_error(x(), y(), x_pos, y_pos) < 10)
    {
        damp_movement(); 
    }
}

double robot_pos_error(double robot_x, double robot_y, double goal_x, double goal_y)
{
    //Consider robot position error to be absolute difference between robot's x y position
    //and goal's x y position
    return abs(goal_x - robot_x) + abs(goal_y - robot_y);  
}