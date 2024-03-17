; Auto-generated. Do not edit!


(cl:in-package jackal_2dnav-msg)


;//! \htmlinclude grasslands.msg.html

(cl:defclass <grasslands> (roslisp-msg-protocol:ros-message)
  ((grasslands
    :reader grasslands
    :initarg :grasslands
    :type (cl:vector jackal_2dnav-msg:grassLimits)
   :initform (cl:make-array 0 :element-type 'jackal_2dnav-msg:grassLimits :initial-element (cl:make-instance 'jackal_2dnav-msg:grassLimits))))
)

(cl:defclass grasslands (<grasslands>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <grasslands>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'grasslands)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jackal_2dnav-msg:<grasslands> is deprecated: use jackal_2dnav-msg:grasslands instead.")))

(cl:ensure-generic-function 'grasslands-val :lambda-list '(m))
(cl:defmethod grasslands-val ((m <grasslands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:grasslands-val is deprecated.  Use jackal_2dnav-msg:grasslands instead.")
  (grasslands m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <grasslands>) ostream)
  "Serializes a message object of type '<grasslands>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'grasslands))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'grasslands))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <grasslands>) istream)
  "Deserializes a message object of type '<grasslands>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'grasslands) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'grasslands)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'jackal_2dnav-msg:grassLimits))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<grasslands>)))
  "Returns string type for a message object of type '<grasslands>"
  "jackal_2dnav/grasslands")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'grasslands)))
  "Returns string type for a message object of type 'grasslands"
  "jackal_2dnav/grasslands")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<grasslands>)))
  "Returns md5sum for a message object of type '<grasslands>"
  "46f47fc035cf3ac098d5a2252afa7df8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'grasslands)))
  "Returns md5sum for a message object of type 'grasslands"
  "46f47fc035cf3ac098d5a2252afa7df8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<grasslands>)))
  "Returns full string definition for message of type '<grasslands>"
  (cl:format cl:nil "jackal_2dnav/grassLimits[] grasslands~%~%================================================================================~%MSG: jackal_2dnav/grassLimits~%float64 minX~%float64 maxX~%~%float64 minY~%float64 maxY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'grasslands)))
  "Returns full string definition for message of type 'grasslands"
  (cl:format cl:nil "jackal_2dnav/grassLimits[] grasslands~%~%================================================================================~%MSG: jackal_2dnav/grassLimits~%float64 minX~%float64 maxX~%~%float64 minY~%float64 maxY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <grasslands>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'grasslands) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <grasslands>))
  "Converts a ROS message object to a list"
  (cl:list 'grasslands
    (cl:cons ':grasslands (grasslands msg))
))
