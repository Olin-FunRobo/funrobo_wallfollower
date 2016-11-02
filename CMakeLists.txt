cmake_minimum_required(VERSION 2.8.3)
project(funrobo_wallfollower)

add_definitions("-std=c++11")


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
)


find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

#MESSAGE(STATUS "INCLUDES : " ${Qt5Widgets_INCLUDE_DIRS})

set (sim_lib_src src/mainwindow.cpp src/worker.cpp)
set (sim_lib_ui assets/mainwindow.ui)
set (sim_bin_src src/main.cpp)
set (sim_lib_hdr include/funrobo_wallfollower/mainwindow.h)
set (worker_hdr include/funrobo_wallfollower/worker.h)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(sim_lib_ui_moc ${sim_lib_ui})
qt5_wrap_cpp(sim_lib_hdr_moc ${sim_lib_hdr})
qt5_wrap_cpp(worker_moc ${worker_hdr})


FILE(GLOB_RECURSE LibFiles "include/*.h")
add_custom_target(headers SOURCES ${LibFiles})

include_directories(
        include
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_BINARY_DIR}
        ${CMAKE_BINARY_DIR}
        ${catkin_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        )
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES funrobo_wallfollower
  CATKIN_DEPENDS roscpp rospy sensor_msgs std_msgs
  DEPENDS system_lib
)


add_library(sim_lib SHARED
    ${sim_lib_src}
    ${sim_lib_ui_moc}
    ${sim_lib_hdr_moc}
    ${worker_moc}
    )

target_link_libraries(sim_lib
    ${catkin_LIBRARIES}
    Qt5::Widgets
    )

add_executable(simulator
    ${sim_bin_src}
    )

target_link_libraries(simulator
    ${catkin_LIBRARIES}
    sim_lib
    )

install(TARGETS simulator
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY assets
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  FILES_MATCHING PATTERN "*.png")

