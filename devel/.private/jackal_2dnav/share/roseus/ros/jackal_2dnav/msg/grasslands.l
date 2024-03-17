;; Auto-generated. Do not edit!


(when (boundp 'jackal_2dnav::grasslands)
  (if (not (find-package "JACKAL_2DNAV"))
    (make-package "JACKAL_2DNAV"))
  (shadow 'grasslands (find-package "JACKAL_2DNAV")))
(unless (find-package "JACKAL_2DNAV::GRASSLANDS")
  (make-package "JACKAL_2DNAV::GRASSLANDS"))

(in-package "ROS")
;;//! \htmlinclude grasslands.msg.html


(defclass jackal_2dnav::grasslands
  :super ros::object
  :slots (_grasslands ))

(defmethod jackal_2dnav::grasslands
  (:init
   (&key
    ((:grasslands __grasslands) ())
    )
   (send-super :init)
   (setq _grasslands __grasslands)
   self)
  (:grasslands
   (&rest __grasslands)
   (if (keywordp (car __grasslands))
       (send* _grasslands __grasslands)
     (progn
       (if __grasslands (setq _grasslands (car __grasslands)))
       _grasslands)))
  (:serialization-length
   ()
   (+
    ;; jackal_2dnav/grassLimits[] _grasslands
    (apply #'+ (send-all _grasslands :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; jackal_2dnav/grassLimits[] _grasslands
     (write-long (length _grasslands) s)
     (dolist (elem _grasslands)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; jackal_2dnav/grassLimits[] _grasslands
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _grasslands (let (r) (dotimes (i n) (push (instance jackal_2dnav::grassLimits :init) r)) r))
     (dolist (elem- _grasslands)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get jackal_2dnav::grasslands :md5sum-) "46f47fc035cf3ac098d5a2252afa7df8")
(setf (get jackal_2dnav::grasslands :datatype-) "jackal_2dnav/grasslands")
(setf (get jackal_2dnav::grasslands :definition-)
      "jackal_2dnav/grassLimits[] grasslands

================================================================================
MSG: jackal_2dnav/grassLimits
float64 minX
float64 maxX

float64 minY
float64 maxY

")



(provide :jackal_2dnav/grasslands "46f47fc035cf3ac098d5a2252afa7df8")


