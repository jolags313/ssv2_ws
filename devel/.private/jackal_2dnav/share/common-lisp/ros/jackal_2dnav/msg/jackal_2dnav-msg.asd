
(cl:in-package :asdf)

(defsystem "jackal_2dnav-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "sPoses" :depends-on ("_package_sPoses"))
    (:file "_package_sPoses" :depends-on ("_package"))
  ))