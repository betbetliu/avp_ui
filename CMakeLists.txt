cmake_minimum_required(VERSION 2.8.3)
project(avp_ui)
#add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
# sensor_msgs
  cv_bridge
  planning_msgs
  localization_msgs
  message_filters
  perception_msgs
  geometry_msgs
)
find_package(OpenCV REQUIRED)
#find_package(Boost REQUIRED)



#set(BOOST_ROOT "/usr/local/lib/cmake/Boost-1.73.0")
#set(Boost_INCLUDE_DIRS /usr/include/boost)
#set(Boost_LIBRARY_DIRS /usr/local/lib/)
#set(Boost_LIBRARY_DIRS /usr/lib/x86_64-linux-gnu/)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# set(Boost_USE_STATIC_LIBS ON)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(Qt5Widgets REQUIRED)
#qt5_wrap_cpp(MOC include/avp_ui.h)
#qt5_wrap_ui(UIC src/avp_ui.ui)

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.ui)
#file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.hpp *.h) 
file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)


QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES client_plugin
   CATKIN_DEPENDS roscpp std_msgs sensor_msgs  planning_msgs perception_msgs localization_msgs message_filters cv_bridge 
   DEPENDS OpenCV 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# INCLUDE_DIRS include
  ${CMAKE_CURRENT_BINARY_DIR}/..
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
#  ${Boost_INCLUDE_DIRS}
)

## Declare a C++ executable
#add_executable(${PROJECT_NAME}_node src/main.cpp src/avp_ui.cpp include/avp_ui.h src/avp_ui.ui)
#target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} Qt5::Widgets)

add_executable(${PROJECT_NAME}_node  ${QT_SOURCES} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} Qt5::Widgets ${OpenCV_LIBS})


