;; Auto-generated. Do not edit!


(when (boundp 'jackal_2dnav::grassLimits)
  (if (not (find-package "JACKAL_2DNAV"))
    (make-package "JACKAL_2DNAV"))
  (shadow 'grassLimits (find-package "JACKAL_2DNAV")))
(unless (find-package "JACKAL_2DNAV::GRASSLIMITS")
  (make-package "JACKAL_2DNAV::GRASSLIMITS"))

(in-package "ROS")
;;//! \htmlinclude grassLimits.msg.html


(defclass jackal_2dnav::grassLimits
  :super ros::object
  :slots (_minX _maxX _minY _maxY ))

(defmethod jackal_2dnav::grassLimits
  (:init
   (&key
    ((:minX __minX) 0.0)
    ((:maxX __maxX) 0.0)
    ((:minY __minY) 0.0)
    ((:maxY __maxY) 0.0)
    )
   (send-super :init)
   (setq _minX (float __minX))
   (setq _maxX (float __maxX))
   (setq _minY (float __minY))
   (setq _maxY (float __maxY))
   self)
  (:minX
   (&optional __minX)
   (if __minX (setq _minX __minX)) _minX)
  (:maxX
   (&optional __maxX)
   (if __maxX (setq _maxX __maxX)) _maxX)
  (:minY
   (&optional __minY)
   (if __minY (setq _minY __minY)) _minY)
  (:maxY
   (&optional __maxY)
   (if __maxY (setq _maxY __maxY)) _maxY)
  (:serialization-length
   ()
   (+
    ;; float64 _minX
    8
    ;; float64 _maxX
    8
    ;; float64 _minY
    8
    ;; float64 _maxY
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _minX
       (sys::poke _minX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _maxX
       (sys::poke _maxX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _minY
       (sys::poke _minY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _maxY
       (sys::poke _maxY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _minX
     (setq _minX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _maxX
     (setq _maxX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _minY
     (setq _minY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _maxY
     (setq _maxY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get jackal_2dnav::grassLimits :md5sum-) "655810147826f0048b34a50ae9b43df0")
(setf (get jackal_2dnav::grassLimits :datatype-) "jackal_2dnav/grassLimits")
(setf (get jackal_2dnav::grassLimits :definition-)
      "float64 minX
float64 maxX

float64 minY
float64 maxY

")



(provide :jackal_2dnav/grassLimits "655810147826f0048b34a50ae9b43df0")


