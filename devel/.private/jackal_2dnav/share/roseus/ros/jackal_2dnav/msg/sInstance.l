;; Auto-generated. Do not edit!


(when (boundp 'jackal_2dnav::sInstance)
  (if (not (find-package "JACKAL_2DNAV"))
    (make-package "JACKAL_2DNAV"))
  (shadow 'sInstance (find-package "JACKAL_2DNAV")))
(unless (find-package "JACKAL_2DNAV::SINSTANCE")
  (make-package "JACKAL_2DNAV::SINSTANCE"))

(in-package "ROS")
;;//! \htmlinclude sInstance.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass jackal_2dnav::sInstance
  :super ros::object
  :slots (_objPose _objLabel ))

(defmethod jackal_2dnav::sInstance
  (:init
   (&key
    ((:objPose __objPose) (instance geometry_msgs::Pose :init))
    ((:objLabel __objLabel) "")
    )
   (send-super :init)
   (setq _objPose __objPose)
   (setq _objLabel (string __objLabel))
   self)
  (:objPose
   (&rest __objPose)
   (if (keywordp (car __objPose))
       (send* _objPose __objPose)
     (progn
       (if __objPose (setq _objPose (car __objPose)))
       _objPose)))
  (:objLabel
   (&optional __objLabel)
   (if __objLabel (setq _objLabel __objLabel)) _objLabel)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose _objPose
    (send _objPose :serialization-length)
    ;; string _objLabel
    4 (length _objLabel)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose _objPose
       (send _objPose :serialize s)
     ;; string _objLabel
       (write-long (length _objLabel) s) (princ _objLabel s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose _objPose
     (send _objPose :deserialize buf ptr-) (incf ptr- (send _objPose :serialization-length))
   ;; string _objLabel
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _objLabel (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get jackal_2dnav::sInstance :md5sum-) "7e34956c628ce888a52ead1e1e7269e9")
(setf (get jackal_2dnav::sInstance :datatype-) "jackal_2dnav/sInstance")
(setf (get jackal_2dnav::sInstance :definition-)
      "geometry_msgs/Pose objPose
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



(provide :jackal_2dnav/sInstance "7e34956c628ce888a52ead1e1e7269e9")


