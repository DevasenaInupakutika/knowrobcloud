#!/bin/bash

if [! -d /home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/project];
then
 
   git clone git@10.42.0.95:/home/git/project.git
else

   echo "Directory already exists" &
   sudo rm -r /home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/project &
   git clone git@10.42.0.95:/home/git/project.git  

fi

cd project &
git init &
sudo cp -r /home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag /home/turtlebot/fuerte_workspace/sandbox/project/map1.pgm &
git add .
git commit -am 'new file uploaded' &
git remote add origin git@10.42.0.95:/home/git/project.git
git push origin master &

exec "$@"


