; Auto-generated. Do not edit!


(cl:in-package jackal_2dnav-msg)


;//! \htmlinclude grassLimits.msg.html

(cl:defclass <grassLimits> (roslisp-msg-protocol:ros-message)
  ((minX
    :reader minX
    :initarg :minX
    :type cl:float
    :initform 0.0)
   (maxX
    :reader maxX
    :initarg :maxX
    :type cl:float
    :initform 0.0)
   (minY
    :reader minY
    :initarg :minY
    :type cl:float
    :initform 0.0)
   (maxY
    :reader maxY
    :initarg :maxY
    :type cl:float
    :initform 0.0))
)

(cl:defclass grassLimits (<grassLimits>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <grassLimits>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'grassLimits)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jackal_2dnav-msg:<grassLimits> is deprecated: use jackal_2dnav-msg:grassLimits instead.")))

(cl:ensure-generic-function 'minX-val :lambda-list '(m))
(cl:defmethod minX-val ((m <grassLimits>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:minX-val is deprecated.  Use jackal_2dnav-msg:minX instead.")
  (minX m))

(cl:ensure-generic-function 'maxX-val :lambda-list '(m))
(cl:defmethod maxX-val ((m <grassLimits>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:maxX-val is deprecated.  Use jackal_2dnav-msg:maxX instead.")
  (maxX m))

(cl:ensure-generic-function 'minY-val :lambda-list '(m))
(cl:defmethod minY-val ((m <grassLimits>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:minY-val is deprecated.  Use jackal_2dnav-msg:minY instead.")
  (minY m))

(cl:ensure-generic-function 'maxY-val :lambda-list '(m))
(cl:defmethod maxY-val ((m <grassLimits>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_2dnav-msg:maxY-val is deprecated.  Use jackal_2dnav-msg:maxY instead.")
  (maxY m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <grassLimits>) ostream)
  "Serializes a message object of type '<grassLimits>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'minX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'maxX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'minY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'maxY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <grassLimits>) istream)
  "Deserializes a message object of type '<grassLimits>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'minX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'maxX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'minY) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'maxY) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<grassLimits>)))
  "Returns string type for a message object of type '<grassLimits>"
  "jackal_2dnav/grassLimits")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'grassLimits)))
  "Returns string type for a message object of type 'grassLimits"
  "jackal_2dnav/grassLimits")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<grassLimits>)))
  "Returns md5sum for a message object of type '<grassLimits>"
  "655810147826f0048b34a50ae9b43df0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'grassLimits)))
  "Returns md5sum for a message object of type 'grassLimits"
  "655810147826f0048b34a50ae9b43df0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<grassLimits>)))
  "Returns full string definition for message of type '<grassLimits>"
  (cl:format cl:nil "float64 minX~%float64 maxX~%~%float64 minY~%float64 maxY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'grassLimits)))
  "Returns full string definition for message of type 'grassLimits"
  (cl:format cl:nil "float64 minX~%float64 maxX~%~%float64 minY~%float64 maxY~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <grassLimits>))
  (cl:+ 0
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <grassLimits>))
  "Converts a ROS message object to a list"
  (cl:list 'grassLimits
    (cl:cons ':minX (minX msg))
    (cl:cons ':maxX (maxX msg))
    (cl:cons ':minY (minY msg))
    (cl:cons ':maxY (maxY msg))
))
