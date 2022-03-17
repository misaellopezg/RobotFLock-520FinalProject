#include "train_coordinator.h"
#include "enviro.h"
#include <cmath>
#include <string>
using namespace enviro;
using namespace std;

void MyTrainCoordinator::init()
{
    std::cout << "Starting train coordinator ID: " << id() << "\n"; 
    //Monitor leader position
    watch("Leader_Position", [this](Event e) {
                leader_x_pos = e.value()[0]; 
                leader_y_pos = e.value()[1]; 
                leader_theta = e.value()[2];
        });
    //Initialize train size to follow robot leader
    train_size = robot_train_pos.size(); 

}

void MyTrainCoordinator::update()
{
    //If leader has moved a significant distance, store leader's last position
    //Continue to buffer robot leader's position 
    if(check_leader_distance(leader_x_pos, leader_y_pos, prev_leader_x_pos, prev_leader_y_pos))
    {
        if(train_size < 4)
        {
            robot_train_pos.push_back(make_pair(prev_leader_x_pos,prev_leader_y_pos)); 
            robot_train_theta.push_back(leader_theta); 
        }
        else
        {
            robot_train_pos.pop_front();
            robot_train_pos.push_back(make_pair(prev_leader_x_pos,prev_leader_y_pos)); 
        }
        train_size = robot_train_pos.size(); 
        //store previous leader's position
        prev_leader_x_pos = leader_x_pos;
        prev_leader_y_pos = leader_y_pos; 
    }
    //Once 4 positions have been captured (the first being leader's current position), spawn 3 followers
   if(train_size == 4)
   {
        if(spawnflag)
        {
             std::cout << "Spawning 3 followers...\n";
            Agent& a1 = add_agent("Robot_Follower", robot_train_pos.at(3).first, robot_train_pos.at(3).second , robot_train_theta.at(3), { {"fill", "green"}});
            f1 = a1.get_id(); 
            Agent& a2 = add_agent("Robot_Follower", robot_train_pos.at(2).first, robot_train_pos.at(2).second , robot_train_theta.at(2), { {"fill", "yellow"}});
            f2 = a2.get_id();
            Agent& a3 = add_agent("Robot_Follower", robot_train_pos.at(1).first, robot_train_pos.at(1).second , robot_train_theta.at(1), { {"fill", "white"}});
            f3 = a3.get_id(); 
            spawnflag = 0; 
        }
        //Create channels for followers to communicate with coordinator
        if(!spawnflag)
        {
            string eventname = "FollowerPosition" + std::to_string(f1); 
            emit(Event(eventname, {robot_train_pos.at(3).first, robot_train_pos.at(3).second}));

            eventname = "FollowerPosition" + std::to_string(f2); 
            emit(Event(eventname, {robot_train_pos.at(2).first, robot_train_pos.at(2).second}));

            eventname = "FollowerPosition" + std::to_string(f3); 
            emit(Event(eventname, {robot_train_pos.at(1).first, robot_train_pos.at(1).second}));
            
        }
   }
}

bool check_leader_distance(double cx, double cy, double px, double py)
{
    //calculate hypotenuse length using x and y to determine distance
    double a = abs(cx - px), b = abs(cy-py); 
    if( sqrt(a*a + b*b) > 60 )
    {
        return 1; 
    }
    else
    {
        return 0; 
    }
}
