cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
rosbuild_add_library(occupancy_grid_merge src/merge_grids.cpp src/merge_grids.h src/exceptions.h src/coordinate_conversions.h src/gcc_version.h src/coordinate_conversions.cpp)
#target_link_libraries(occ_comb_map occupancy_grid_merge)

rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
rosbuild_add_executable(stpoor_rec src/stpoor_rec.cpp)
rosbuild_add_executable(path_rec src/path_rec.cpp)
rosbuild_add_executable(read_path src/read_path.cpp)
rosbuild_add_executable(talker src/talker.cpp)
rosbuild_add_executable(listener src/listener.cpp)
rosbuild_add_executable(occ_comb_map src/occ_comb_map.cpp)
rosbuild_add_executable(align_pub src/align_pub.cpp)
target_link_libraries(occ_comb_map occupancy_grid_merge)


#target_link_libraries(example ${PROJECT_NAME})
