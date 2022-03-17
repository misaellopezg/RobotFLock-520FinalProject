#include "robot_follower.h"
#include "enviro.h"
#include <cmath>

using namespace enviro;
using namespace std;

void MyRobotFollower::init()
{
    cout << "Starting robot follower! ID: " << id() << "\n"; 
    //Rotate around looking for leader
    track_velocity(0,sweep_rotation);
}

void MyRobotFollower::update()
{
    //Set string to Robot_Leader to target leader
    string target = "Robot_Leader"; 
    //Bools are used to indicate sensor detection
    bool right_in, right_out, left_in, left_out, found;
    //Update x y position
    x_pos = x(); 
    y_pos = y(); 
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
   //leader to the left, positive number indicates leader to the right
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
    //Store previous magnitude to know last robot leader detection position
    prev_sensor_magnitude = sensor_magnitude; 
}
