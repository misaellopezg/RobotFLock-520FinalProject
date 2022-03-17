#include "robot_leader.h"
#include "enviro.h"
#include <cmath>
#include <vector>

using namespace enviro;
using namespace std;

#define FLOCK_X_OFFSET 30; 
#define FLOCK_Y_OFFSET 20; 

const int flock_height = 4;

void MyRobotLeader::init()
{
    cout << "Starting robot follower! ID: " << id() << "\n"; 
    //Rotate around looking for target
    track_velocity(0,sweep_rotation);
    //Initialize flock array
    flock_array = init_flock(flock_height, x_pos, y_pos, theta);
}

void MyRobotLeader::update()
{
    //Create flock and store information in flock vector
    if(createflock)
    {
        for(int x = 0; x < flock_array.size(); x ++)
        {
            Agent& v = add_agent("Robot_Follower", flock_array.at(x).at(1), flock_array.at(x).at(2), flock_array.at(x).at(3), { {"fill", "green"}});
            double a_id =  v.get_id(); 
            flock_array.at(x).at(0) = a_id;
        }
        createflock = 0; 
    }
    for(auto x: flock_array)
    {
        int a_id = x.at(0);
        //Emit flock information per unique channel
        string eventname = "FollowerPosition" + std::to_string(a_id); 
        //std::cout << eventname << "\n";
        //std:cout << "Values: " << x.at(1) << " " << x.at(2) << " " << x.at(3) << "\n";  
        emit(Event(eventname, {x.at(1), x.at(2), x.at(3)}));
    }
    //Set string to Robot_Target for targeting 
    string target = "Robot_Target"; 
    //Bools are used to indicate sensor detection
    bool right_in, right_out, left_in, left_out, found;
    //Set x y theta
    x_pos = x(); 
    y_pos = y(); 
    theta = angle(); 
    //Check to see which sensors found robot leader
    left_out = ( target == sensor_reflection_type(0) ); 
    left_in = ( target == sensor_reflection_type(1) ); 
    right_in = ( target == sensor_reflection_type(2) ); 
    right_out = ( target == sensor_reflection_type(3) ); 
    found = left_out || left_in || right_in || right_out; 
    /*
    std::cout << "Sensor Left Out: " << left_out;
    std::cout << " Sensor Left In: " << left_in;
    std::cout << " Sensor Right In: " << right_in; 
    std::cout << " Sensor Right Out: " << right_out << "\n";
    */
   //Calculate magnitude of sensor readings; 0 indicates target in front, negative number indicates
    //target to the left, positive number indicates target to the right
    sensor_magnitude = -1*left_out + -1*left_in + right_in + right_out; 
    if(!found)
    {
        //Rotate depending on whether detection was left or right 
        if(prev_sensor_magnitude > 0)
        {
            sweep_rotation = 2.0; 
        }
        if(prev_sensor_magnitude < 0)
        {
            sweep_rotation = -2.0;
        }
        track_velocity(0,sweep_rotation);
    }
    else
    {
        //Rotate and chase depending on sensor reading
        if(sensor_magnitude == 0)
        {
            track_velocity(4.0,0);
        }
        if(sensor_magnitude > 0)
        {
            track_velocity(4.0,1.5);
        }
        if(sensor_magnitude < 0)
        {
            track_velocity(4.0,-1.5);
        }
    }
    //Store previous magnitude to know last target detection position
    prev_sensor_magnitude = sensor_magnitude;  
    //Update flock vector with leader info
    update_flock(flock_array, x_pos, y_pos, theta);
}

vector<vector<double>> init_flock(int fh, double leader_x, double leader_y, double leader_theta)
{
    vector<vector<double>> flock_data;
    for(int x = 0; x < fh; x++)
    {
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
    
    for(int x = 0; x < v.size(); x++)
    {
        v.at(x).at(1) = flock_agent_x(leader_x, leader_theta, double((x+1)* -60) );
        v.at(x).at(2) = flock_agent_y(leader_y, leader_theta, double((x+1)* -60) );
        v.at(x).at(3) = leader_theta;
    }
}
