# 520FinalProject
Final Project for EEP 520 Software Engineering for Embedded Applications

# Overview
The following project has the intent of using Enviro to create robot leading/following applications with the intent of realizing flock behvaior with robot agents. The project consists of 4 sub-projects, each one building off the previous one. 
The following 4 subj-projects are explained in order:

1. Looping Leader
   - Creates a robot agent that loops in a circular path. The agent obtains path information from a static CSV file containing X-Y coordinates under the sub-project's "paths" folder. 
2. Robot Follower 
   - Spawns a target agent that loops in a circulat path. A robot agent with sensors can be spawned using the "Spawn Follower" button that will then proceed to chase the target agent. 
3. Robot Train & Better Robot Train
   - Creates a target agent, robot leader agent, robot follower agent, and a train coordinator agent. Building off the two previous sub-projects, the robot leader agent chases the robot target. This time, the train coordinator agent stores leader agent positions. The train coordinator then spawns 3 followers that follow behind the robot leader. Better Robot Train improves on the previous by being able to spawn multiple agents behind the robot as a single unit. 
4. Robot Flock 
   - Creates a robot leader agent and three robot follower agents. Building off of Robot train, this sub-project showcases dynamic movement between the robot leader and the robot followers. While the leader rotates, each follower is able to oscillate on its own with respect to the leader's X-Y-Theta position. Along with this, the flock acts a single unit, providing information on it's front, back, left, and right sensors.  

# Installation

# Running the Project

# Challenges

# Acknolwedgements
ENVIRO: The multi-agent, multi-user, multi-everything simulator
Created by: Klavins Lab Software
https://github.com/klavinslab/enviro
http://klavinslab.org/elma/

Elma
Created by: Klavins Lab Software
https://github.com/klavinslab/elma_project

Enviro Docker Image
Created by: Eric Klavins
https://hub.docker.com/r/klavins/enviro

README has an overview of what the goal of the project is                                                                                                   |
| 10     | README has a description of key challenges and how they were addressed                                                                                      |
| 10     | README describes how to install and run the code (assuming the user has docker installed)                                                                   |
| 10     | README describes how to run and/or use the project                                                                                                            
