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
cp -r ../bagfiles/path_rec.bag ../project/map1.bag &
git add .
git commit -am 'new file uploaded' 
git add .
git push origin master 

exec "$@"


