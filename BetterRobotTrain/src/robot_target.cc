#include <iostream>
#include "robot_target.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace enviro;
using namespace std;

// Put your implementations here
void MyRobotTarget::init()
{
    std::cout << "Starting robot target ID: " << id() << "\n"; 
    robot_path = get_file_robot_path("paths/square_path.csv"); 
    x_pos = x(); 
    y_pos = y(); 
}

void MyRobotTarget::update()
{
    //If path index is greater than vector size, reset to 0
    if(path_index >= robot_path.size())
    {
        path_index = 0;
    }
    //Get current robot goal and move towards goal
    robot_goal = robot_path.at(path_index); 
    move_toward(robot_goal.first,robot_goal.second); 
    //If error between robot position and goal is minimum, advance
    double er = robot_pos_error(x_pos,y_pos,robot_goal.first,robot_goal.second); 
    if(er < 30)
    {
        path_index = path_index + 3; 
    }
    //Update x y position
    x_pos = x(); 
    y_pos = y(); 
    //cout << "GX: " << robot_goal.first << " GY: " << robot_goal.second << "\n"; 
    //cout << "X: " << x_pos << " Y: " << y_pos << " Theta: " << angle() << "\n"; 
    //cout << "Current error: " << er << "\n"; 
    //cout << "Path Index :" << path_index << "\n"; 
   
}

vector<pair <int,int>> get_file_robot_path(const string filepath)
{
    //Create vector to store pair of robot coordinates
    vector<pair <int,int>> robot_path; 
    pair<int,int> robot_coordinate; 
    pair<int,int> a = make_pair(0,250);

    //Open file
    ifstream file_in;
    file_in.open(filepath);
    //Use "," as delimiter for file
    string line, delim = ",";
    //Check to see if file exists, else error
    if(file_in.peek() == std::ifstream::traits_type::eof())
    {
        throw std::invalid_argument("Empty File. Exiting...");
    }
    if(file_in.is_open())
    {
        //While file is open, use delimiter to get x and y coordinates
        while(getline(file_in,line))
        {
            std::size_t endpos, startpos = 0; 
            endpos = line.find(delim); 
            robot_coordinate.first = stoi(line.substr(startpos, endpos - startpos));
            startpos = endpos + 1;
            endpos = std::string::npos;
            robot_coordinate.second = stoi(line.substr(startpos, endpos - startpos));
            robot_path.push_back(robot_coordinate);
        }
        file_in.close();
    }
    /*
    for(int x = 0; x < robot_path.size(); x++)
    {
        cout << "File x: " << robot_path.at(x).first << " File y: " << robot_path.at(x).second << "\n"; 
    }
    //*/
    return robot_path; 
}

double robot_pos_error(double robot_x, double robot_y, double goal_x, double goal_y)
{
    //Consider robot position error to be absolute difference between robot's x y position
    //and goal's x y position
    return abs(goal_x - robot_x) + abs(goal_y - robot_y);  
}