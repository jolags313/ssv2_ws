// Auto-generated. Do not edit!

// (in-package jackal_2dnav.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let sInstance = require('./sInstance.js');

//-----------------------------------------------------------

class sPoses {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.sPoses = null;
    }
    else {
      if (initObj.hasOwnProperty('sPoses')) {
        this.sPoses = initObj.sPoses
      }
      else {
        this.sPoses = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type sPoses
    // Serialize message field [sPoses]
    // Serialize the length for message field [sPoses]
    bufferOffset = _serializer.uint32(obj.sPoses.length, buffer, bufferOffset);
    obj.sPoses.forEach((val) => {
      bufferOffset = sInstance.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type sPoses
    let len;
    let data = new sPoses(null);
    // Deserialize message field [sPoses]
    // Deserialize array length for message field [sPoses]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.sPoses = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.sPoses[i] = sInstance.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.sPoses.forEach((val) => {
      length += sInstance.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jackal_2dnav/sPoses';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '89f29c293b2e6dbeec18915c4b5a83f6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    jackal_2dnav/sInstance[] sPoses
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new sPoses(null);
    if (msg.sPoses !== undefined) {
      resolved.sPoses = new Array(msg.sPoses.length);
      for (let i = 0; i < resolved.sPoses.length; ++i) {
        resolved.sPoses[i] = sInstance.Resolve(msg.sPoses[i]);
      }
    }
    else {
      resolved.sPoses = []
    }

    return resolved;
    }
};

module.exports = sPoses;
