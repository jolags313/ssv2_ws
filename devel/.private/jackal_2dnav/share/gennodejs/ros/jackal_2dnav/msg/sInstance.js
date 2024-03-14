// Auto-generated. Do not edit!

// (in-package jackal_2dnav.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class sInstance {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.objPose = null;
      this.objLabel = null;
    }
    else {
      if (initObj.hasOwnProperty('objPose')) {
        this.objPose = initObj.objPose
      }
      else {
        this.objPose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('objLabel')) {
        this.objLabel = initObj.objLabel
      }
      else {
        this.objLabel = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type sInstance
    // Serialize message field [objPose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.objPose, buffer, bufferOffset);
    // Serialize message field [objLabel]
    bufferOffset = _serializer.string(obj.objLabel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type sInstance
    let len;
    let data = new sInstance(null);
    // Deserialize message field [objPose]
    data.objPose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [objLabel]
    data.objLabel = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.objLabel);
    return length + 60;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jackal_2dnav/sInstance';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7e34956c628ce888a52ead1e1e7269e9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new sInstance(null);
    if (msg.objPose !== undefined) {
      resolved.objPose = geometry_msgs.msg.Pose.Resolve(msg.objPose)
    }
    else {
      resolved.objPose = new geometry_msgs.msg.Pose()
    }

    if (msg.objLabel !== undefined) {
      resolved.objLabel = msg.objLabel;
    }
    else {
      resolved.objLabel = ''
    }

    return resolved;
    }
};

module.exports = sInstance;
