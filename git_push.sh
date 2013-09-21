#!/bin/bash

if [! -d /home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/project];
then
   echo 'Directory Created' 
   git clone git@10.42.0.95:/home/git/project.git
else

   echo 'Directory already exists' &
   rm -r project 
   git clone git@10.42.0.95:/home/git/project.git  

fi

cd project &
cp -r /home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag /home/turtlebot/fuerte_workspace/sandbox/project/map1.pgm &
git add .
git commit -am 'new file uploaded' 
git push origin master 

exec "$@"


