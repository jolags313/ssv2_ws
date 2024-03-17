# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "jackal_2dnav: 4 messages, 0 services")

set(MSG_I_FLAGS "-Ijackal_2dnav:/home/conlab/ssv2_ws/src/jackal_2dnav/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(jackal_2dnav_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg" NAME_WE)
add_custom_target(_jackal_2dnav_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "jackal_2dnav" "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg" "geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion"
)

get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg" NAME_WE)
add_custom_target(_jackal_2dnav_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "jackal_2dnav" "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg" "geometry_msgs/Pose:geometry_msgs/Point:jackal_2dnav/sInstance:geometry_msgs/Quaternion"
)

get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg" NAME_WE)
add_custom_target(_jackal_2dnav_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "jackal_2dnav" "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg" ""
)

get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg" NAME_WE)
add_custom_target(_jackal_2dnav_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "jackal_2dnav" "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg" "jackal_2dnav/grassLimits"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_cpp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_cpp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_cpp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg"
  "${MSG_I_FLAGS}"
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jackal_2dnav
)

### Generating Services

### Generating Module File
_generate_module_cpp(jackal_2dnav
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jackal_2dnav
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(jackal_2dnav_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(jackal_2dnav_generate_messages jackal_2dnav_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_cpp _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_cpp _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_cpp _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_cpp _jackal_2dnav_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jackal_2dnav_gencpp)
add_dependencies(jackal_2dnav_gencpp jackal_2dnav_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jackal_2dnav_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_eus(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_eus(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_eus(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg"
  "${MSG_I_FLAGS}"
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jackal_2dnav
)

### Generating Services

### Generating Module File
_generate_module_eus(jackal_2dnav
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jackal_2dnav
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(jackal_2dnav_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(jackal_2dnav_generate_messages jackal_2dnav_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_eus _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_eus _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_eus _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_eus _jackal_2dnav_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jackal_2dnav_geneus)
add_dependencies(jackal_2dnav_geneus jackal_2dnav_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jackal_2dnav_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_lisp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_lisp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_lisp(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg"
  "${MSG_I_FLAGS}"
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jackal_2dnav
)

### Generating Services

### Generating Module File
_generate_module_lisp(jackal_2dnav
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jackal_2dnav
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(jackal_2dnav_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(jackal_2dnav_generate_messages jackal_2dnav_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_lisp _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_lisp _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_lisp _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_lisp _jackal_2dnav_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jackal_2dnav_genlisp)
add_dependencies(jackal_2dnav_genlisp jackal_2dnav_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jackal_2dnav_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_nodejs(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_nodejs(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_nodejs(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg"
  "${MSG_I_FLAGS}"
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jackal_2dnav
)

### Generating Services

### Generating Module File
_generate_module_nodejs(jackal_2dnav
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jackal_2dnav
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(jackal_2dnav_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(jackal_2dnav_generate_messages jackal_2dnav_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_nodejs _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_nodejs _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_nodejs _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_nodejs _jackal_2dnav_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jackal_2dnav_gennodejs)
add_dependencies(jackal_2dnav_gennodejs jackal_2dnav_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jackal_2dnav_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_py(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Point.msg;/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg;/opt/ros/noetic/share/geometry_msgs/cmake/../msg/Quaternion.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_py(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav
)
_generate_msg_py(jackal_2dnav
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg"
  "${MSG_I_FLAGS}"
  "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav
)

### Generating Services

### Generating Module File
_generate_module_py(jackal_2dnav
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(jackal_2dnav_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(jackal_2dnav_generate_messages jackal_2dnav_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sInstance.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_py _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/sPoses.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_py _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grassLimits.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_py _jackal_2dnav_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/conlab/ssv2_ws/src/jackal_2dnav/msg/grasslands.msg" NAME_WE)
add_dependencies(jackal_2dnav_generate_messages_py _jackal_2dnav_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(jackal_2dnav_genpy)
add_dependencies(jackal_2dnav_genpy jackal_2dnav_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS jackal_2dnav_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jackal_2dnav)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/jackal_2dnav
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(jackal_2dnav_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(jackal_2dnav_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jackal_2dnav)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/jackal_2dnav
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(jackal_2dnav_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(jackal_2dnav_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jackal_2dnav)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/jackal_2dnav
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(jackal_2dnav_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(jackal_2dnav_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jackal_2dnav)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/jackal_2dnav
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(jackal_2dnav_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(jackal_2dnav_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/jackal_2dnav
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(jackal_2dnav_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(jackal_2dnav_generate_messages_py geometry_msgs_generate_messages_py)
endif()
