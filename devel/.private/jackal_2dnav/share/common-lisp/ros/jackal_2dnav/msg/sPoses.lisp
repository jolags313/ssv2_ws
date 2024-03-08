; Auto-generated. Do not edit!


(cl:in-package jackal_2dnav-msg)


;//! \htmlinclude sPoses.msg.html

(cl:defclass <sPoses> (roslisp-msg-protocol:ros-message)
  ((poses
    :reader poses
    :initarg :poses
    :type (cl:vector geometry_msgs-msg:Pose)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Pose :initial-element (cl:make-instance 'geometry_msgs-msg:Pose))))
)

(cl:defclass sPoses (<sPoses>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <sPoses>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'sPoses)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jackal_2dnav-msg:<sPoses> is deprecated: use jackal_2dnav-msg:sPoses instead.")))

(cl:ensure-generic-function 'poses-val :lambda-list '(m))
(cl:defmethod poses-val ((m <sPoses>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:poses-val is deprecated.  Use jackal_2dnav-msg:poses instead.")
  (poses m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <sPoses>) ostream)
  "Serializes a message object of type '<sPoses>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'poses))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'poses))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <sPoses>) istream)
  "Deserializes a message object of type '<sPoses>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'poses) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'poses)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Pose))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<sPoses>)))
  "Returns string type for a message object of type '<sPoses>"
  "jackal_2dnav/sPoses")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sPoses)))
  "Returns string type for a message object of type 'sPoses"
  "jackal_2dnav/sPoses")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<sPoses>)))
  "Returns md5sum for a message object of type '<sPoses>"
  "db8ce58a1deaf0d1f2e7fdd257963e81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'sPoses)))
  "Returns md5sum for a message object of type 'sPoses"
  "db8ce58a1deaf0d1f2e7fdd257963e81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<sPoses>)))
  "Returns full string definition for message of type '<sPoses>"
  (cl:format cl:nil "geometry_msgs/Pose[] poses~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'sPoses)))
  "Returns full string definition for message of type 'sPoses"
  (cl:format cl:nil "geometry_msgs/Pose[] poses~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <sPoses>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'poses) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <sPoses>))
  "Converts a ROS message object to a list"
  (cl:list 'sPoses
    (cl:cons ':poses (poses msg))
))
