#include "robot_leader.h"
#include "enviro.h"
#include <cmath>
#include <vector>
#include <string> 

using namespace enviro;
using namespace std;

//Set constant flock size to avoid resizing
const int flock_height = 3;
//Set max sensor value to check for closer obstacles
const double max_sensor_val = 50; 

void MyRobotLeader::init()
{
    cout << "Starting robot follower! ID: " << id() << "\n"; 
    track_velocity(0,sweep_rotation);
    //Initialize flock array and sensors
    flock_array = init_flock(flock_height, x_pos, y_pos, theta);
    flock_sensors = init_flock_sensors(flock_height);
    //Set robot flock to move
    //track_velocity(line_velocity_max, 0); 
}

void MyRobotLeader::update()
{
    if(createflock)
    {
        //Create flock agents
        for(int x = 0; x < flock_array.size(); x ++)
        {
            Agent& v = add_agent("Robot_Follower", flock_array.at(x).at(1), flock_array.at(x).at(2), flock_array.at(x).at(3), { {"fill", "green"}});
            double a_id =  v.get_id(); 
            flock_array.at(x).at(0) = a_id;
        }
        createflock = 0; 
    }
    //Emit leader position info back to targets
    for(auto x: flock_array)
    {
        int a_id = x.at(0);
        string eventname = "FollowerPosition" + std::to_string(a_id);  
        emit(Event(eventname, {x.at(1), x.at(2), x.at(3)}));
    }
    if(setsensorchannel)
    {
        //Tried to make dynamic channel reading but did not undertsand how to do it
        //Create 3 Channels for robot following flock
        string fch = "FollowerInfo" + std::to_string( int(flock_array.at(0).at(0))); 
        watch(fch, [this](Event e) {
            flock_sensors.at(0).at(0) = e.value()[0]; 
            flock_sensors.at(0).at(1) = e.value()[1];
                flock_sensors.at(0).at(2) = e.value()[2];  
        });
        fch = "FollowerInfo" + std::to_string( int(flock_array.at(1).at(0))); 
        watch(fch, [this](Event e) {
            flock_sensors.at(1).at(0) = e.value()[0]; 
            flock_sensors.at(1).at(1) = e.value()[1];
                flock_sensors.at(1).at(2) = e.value()[2];  
        });
        fch = "FollowerInfo" + std::to_string( int(flock_array.at(2).at(0))); 
        watch(fch, [this](Event e) {
            flock_sensors.at(2).at(0) = e.value()[0]; 
            flock_sensors.at(2).at(1) = e.value()[1];
                flock_sensors.at(2).at(2) = e.value()[2];  
        });
        setsensorchannel = 0;
    }
    bool right_in, right_out, left_in, left_out, found;
    //Get leader x y theta
    x_pos = x(); 
    y_pos = y(); 
    theta = angle(); 
    //Get sensor values
    front_sensor = sensor_value(0); 
    back_sensor = flock_sensors.at(2).at(1); 
    //Loop through flock sensors to find min and max left right sensor values
    for(int x = 0; x < flock_height; x++)
    {
        if(x == 0)
        {
            left_sensor = flock_sensors.at(x).at(0); 
            right_sensor = flock_sensors.at(x).at(2); 
        }
        else
        {
            if( flock_sensors.at(x).at(0) > left_sensor)
            {
                left_sensor = flock_sensors.at(x).at(0);
            } 
            if( flock_sensors.at(x).at(2) > right_sensor)
            {
                right_sensor = flock_sensors.at(x).at(2);
            }   
        }
    }
    
    std::cout << "f:" << front_sensor << " b:" << back_sensor << " l:" << left_sensor << " r:" << right_sensor << "\n"; 
    update_flock(flock_array, x_pos, y_pos, theta);
}




vector<vector<double>> init_flock(int fh, double leader_x, double leader_y, double leader_theta)
{
    vector<vector<double>> flock_data;
    for(int x = 0; x < fh; x++)
    {
        //Initialize flock with relative positions based on leader position
        vector<double> agent_data;
        agent_data.push_back(0.0); 
        agent_data.push_back(flock_agent_x(leader_x, leader_theta, double((x+1)* -60) )); 
        agent_data.push_back(flock_agent_y(leader_y, leader_theta, double((x+1)* -60) )); 
        agent_data.push_back(leader_theta);
        flock_data.push_back(agent_data); 
    }
    return flock_data; 
}

void update_flock(vector<vector<double>>& v ,double leader_x, double leader_y, double leader_theta)
{
    //Update flock with relative positions based on leader position
    for(int x = 0; x < v.size(); x++)
    {
        v.at(x).at(1) = flock_agent_x(leader_x, leader_theta, double((x+1)* -60) );
        v.at(x).at(2) = flock_agent_y(leader_y, leader_theta, double((x+1)* -60) );
        v.at(x).at(3) = leader_theta;
    }
}

vector<vector<double>> init_flock_sensors(int fh)
{
    vector<vector<double>> v; 
    vector<double> r; 
    //Assumption: each flock agent has 3 sensors 0 = left, 1 = back, 2 = right
    for(int x = 0; x < 3; x++)
    {
        r.push_back(0.0); 
    }
    for(int x = 0; x < fh; x++)
    {
        v.push_back(r); 
    }
    return v;
}
