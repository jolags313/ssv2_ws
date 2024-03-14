;; Auto-generated. Do not edit!


(when (boundp 'jackal_2dnav::sPoses)
  (if (not (find-package "JACKAL_2DNAV"))
    (make-package "JACKAL_2DNAV"))
  (shadow 'sPoses (find-package "JACKAL_2DNAV")))
(unless (find-package "JACKAL_2DNAV::SPOSES")
  (make-package "JACKAL_2DNAV::SPOSES"))

(in-package "ROS")
;;//! \htmlinclude sPoses.msg.html


(defclass jackal_2dnav::sPoses
  :super ros::object
  :slots (_sPoses ))

(defmethod jackal_2dnav::sPoses
  (:init
   (&key
    ((:sPoses __sPoses) ())
    )
   (send-super :init)
   (setq _sPoses __sPoses)
   self)
  (:sPoses
   (&rest __sPoses)
   (if (keywordp (car __sPoses))
       (send* _sPoses __sPoses)
     (progn
       (if __sPoses (setq _sPoses (car __sPoses)))
       _sPoses)))
  (:serialization-length
   ()
   (+
    ;; jackal_2dnav/sInstance[] _sPoses
    (apply #'+ (send-all _sPoses :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; jackal_2dnav/sInstance[] _sPoses
     (write-long (length _sPoses) s)
     (dolist (elem _sPoses)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; jackal_2dnav/sInstance[] _sPoses
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _sPoses (let (r) (dotimes (i n) (push (instance jackal_2dnav::sInstance :init) r)) r))
     (dolist (elem- _sPoses)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get jackal_2dnav::sPoses :md5sum-) "89f29c293b2e6dbeec18915c4b5a83f6")
(setf (get jackal_2dnav::sPoses :datatype-) "jackal_2dnav/sPoses")
(setf (get jackal_2dnav::sPoses :definition-)
      "jackal_2dnav/sInstance[] sPoses

================================================================================
MSG: jackal_2dnav/sInstance
geometry_msgs/Pose objPose
string objLabel

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

")



(provide :jackal_2dnav/sPoses "89f29c293b2e6dbeec18915c4b5a83f6")


