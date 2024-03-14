; Auto-generated. Do not edit!


(cl:in-package jackal_2dnav-msg)


;//! \htmlinclude sInstance.msg.html

(cl:defclass <sInstance> (roslisp-msg-protocol:ros-message)
  ((objPose
    :reader objPose
    :initarg :objPose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (objLabel
    :reader objLabel
    :initarg :objLabel
    :type cl:string
    :initform ""))
)

(cl:defclass sInstance (<sInstance>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <sInstance>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'sInstance)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jackal_2dnav-msg:<sInstance> is deprecated: use jackal_2dnav-msg:sInstance instead.")))

(cl:ensure-generic-function 'objPose-val :lambda-list '(m))
(cl:defmethod objPose-val ((m <sInstance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:objPose-val is deprecated.  Use jackal_2dnav-msg:objPose instead.")
  (objPose m))

(cl:ensure-generic-function 'objLabel-val :lambda-list '(m))
(cl:defmethod objLabel-val ((m <sInstance>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:objLabel-val is deprecated.  Use jackal_2dnav-msg:objLabel instead.")
  (objLabel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <sInstance>) ostream)
  "Serializes a message object of type '<sInstance>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'objPose) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'objLabel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'objLabel))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <sInstance>) istream)
  "Deserializes a message object of type '<sInstance>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'objPose) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'objLabel) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'objLabel) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<sInstance>)))
  "Returns string type for a message object of type '<sInstance>"
  "jackal_2dnav/sInstance")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'sInstance)))
  "Returns string type for a message object of type 'sInstance"
  "jackal_2dnav/sInstance")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<sInstance>)))
  "Returns md5sum for a message object of type '<sInstance>"
  "7e34956c628ce888a52ead1e1e7269e9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'sInstance)))
  "Returns md5sum for a message object of type 'sInstance"
  "7e34956c628ce888a52ead1e1e7269e9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<sInstance>)))
  "Returns full string definition for message of type '<sInstance>"
  (cl:format cl:nil "geometry_msgs/Pose objPose~%string objLabel~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'sInstance)))
  "Returns full string definition for message of type 'sInstance"
  (cl:format cl:nil "geometry_msgs/Pose objPose~%string objLabel~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <sInstance>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'objPose))
     4 (cl:length (cl:slot-value msg 'objLabel))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <sInstance>))
  "Converts a ROS message object to a list"
  (cl:list 'sInstance
    (cl:cons ':objPose (objPose msg))
    (cl:cons ':objLabel (objLabel msg))
))
