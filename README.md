# FRC_Team_573_2018_Robot_Code
This is the repo for FRC Team 573's 2018 FRC Robot Code.

This is a private repo so you will have to be invited to collabroate by the owner (Coach Eric). 
Before the 2019 season starts this repo will be made public so code developed here can be re used if needed in 2019.

---------- GITHUB ---------------

Github is an online code repository used for version control and collabroation so multiple coders can work on the same project.
It allows coders to work on there own version of code (branch) then merge it back into a master branch. 
You can commit you code to github as often as you like into the branch your working on. 

In order to make it easier to create new branches, commit code and perform a pull request (merge your code into the master branch) we will be using Github Desktop. https://desktop.github.com/ Please install it on your machine if you will be using it for coding as well. This will allow you to easily see changes you've made and commit those changes to the Github repo. We will go over how to use Github Desktop during the first weeks of build season.

Creating branches and pull requests. You can create branchs off of any active branch in the project, and I suggest this to test different paths you might try in your code. However any merging of branches will have to do done through a pull request. Right now when you submit a pull request set the reviewer to me (Coach Eric). That way I can make sure that everyone affected is ok with merging the code together.

-------- Google Drive -----------

The programming team also has a google drive that will house documents that are needed to be seen by other subteams as well. If you don't have access please let me know.  https://drive.google.com/open?id=10iLfheUd4BaSzzMyTS3-60ICF_zOHXeo1oWPGRdDKTk

This year the programming team will be the primary owner of the ICD, however that doesn't mean changes can be made without informing the other subteams. Once a rough TCD is agreed we will lock it down and require changes to go through an approval process. As in the electrical and programming student leads will have to both tell me that they agree on the change.

Other things on this drive would be controller button layouts, reference documents and calculation spreadsheets.

------- WPILib ----------

We will be using C++ this year for our robot code and Labview for our driver station. The WPILib provides libraries for FRC teams to use in their robot code as well as walk through tutuorials. Both of these will be very important resources for you to use during the year.

The tutorials can be found here https://wpilib.screenstepslive.com/s/currentCS/m/cpp

The WPILib C++ API help can be found here. http://first.wpi.edu/FRC/roborio/release/docs/cpp/ 

------- LimeLight ---------

We used LimeLight camera for vision. The website is https://limelightvision.io/ and there documentation can be found at http://docs.limelightvision.io/en/latest/

------ Code Structure ---------

Main code is in Robot.cpp

Created the following subsystem code files containing fucntions to be called in Robot.cpp
 -Drive.cpp
 -Appendage.cpp
 -Log.cpp
 -Autonomous.cpp

------- Anything Else --------

Please feel free to add sections to this readme or create others as you see fit as we develop the code. The idea of this repo is so a person new to our code, or the person who wrote it 2 months later, can easily find where anything is and understand why we did it that way.

-------- Questions -------

If you have any questions please contact Coach Eric.

------- Major Commit History ---

Combined Kevan and Chase branches on 1/19 into master, then recreated the branches.

Combined Kevan1 and Chase1 branches on 1/26 into master, then recreated the branches. Also included labview driver station in this commit.

------- Kevan's To-Do's ---------

~ Scouting App
 
 ------ Chase To- Do's ---------
 
 ~ Have compressor auto turn off when drive wheels get 70% + PWM signal. (If we use a compressor on the robot)
