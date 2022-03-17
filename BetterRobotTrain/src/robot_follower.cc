#include "robot_follower.h"
#include "enviro.h"
#include <string>

using namespace enviro;
using namespace std;

void MyRobotFollower::init()
{
    //std::cout << "Just spawned! My id is: " << id() << "\n"; 
    //Create follower channel
    train_coordinator_ch = "FollowerPosition" + std::to_string(id());
    //std::cout << "Channel: " << train_coordinator_ch << "\n"; 
    watch(train_coordinator_ch, [this](Event e) {
                x_pos = e.value()[0]; 
                y_pos = e.value()[1];
                theta = e.value()[2];  
        });
}

void MyRobotFollower::update()
{
    //std::cout << id() << " X rec: " << x_pos << " Y rec: " << y_pos << " Theta: " << theta << "\n";
    //Use teleport for smoother positioning
    teleport(x_pos, y_pos, theta);
    //std::cout << "I'm alive!\n";
}

double robot_pos_error(double robot_x, double robot_y, double goal_x, double goal_y)
{
    //Consider robot position error to be absolute difference between robot's x y position
    //and goal's x y position
    return abs(goal_x - robot_x) + abs(goal_y - robot_y);  
}