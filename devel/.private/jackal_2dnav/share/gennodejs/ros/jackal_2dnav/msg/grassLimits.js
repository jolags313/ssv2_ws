// Auto-generated. Do not edit!

// (in-package jackal_2dnav.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class grassLimits {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.minX = null;
      this.maxX = null;
      this.minY = null;
      this.maxY = null;
    }
    else {
      if (initObj.hasOwnProperty('minX')) {
        this.minX = initObj.minX
      }
      else {
        this.minX = 0.0;
      }
      if (initObj.hasOwnProperty('maxX')) {
        this.maxX = initObj.maxX
      }
      else {
        this.maxX = 0.0;
      }
      if (initObj.hasOwnProperty('minY')) {
        this.minY = initObj.minY
      }
      else {
        this.minY = 0.0;
      }
      if (initObj.hasOwnProperty('maxY')) {
        this.maxY = initObj.maxY
      }
      else {
        this.maxY = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type grassLimits
    // Serialize message field [minX]
    bufferOffset = _serializer.float64(obj.minX, buffer, bufferOffset);
    // Serialize message field [maxX]
    bufferOffset = _serializer.float64(obj.maxX, buffer, bufferOffset);
    // Serialize message field [minY]
    bufferOffset = _serializer.float64(obj.minY, buffer, bufferOffset);
    // Serialize message field [maxY]
    bufferOffset = _serializer.float64(obj.maxY, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type grassLimits
    let len;
    let data = new grassLimits(null);
    // Deserialize message field [minX]
    data.minX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [maxX]
    data.maxX = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [minY]
    data.minY = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [maxY]
    data.maxY = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jackal_2dnav/grassLimits';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '655810147826f0048b34a50ae9b43df0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 minX
    float64 maxX
    
    float64 minY
    float64 maxY
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new grassLimits(null);
    if (msg.minX !== undefined) {
      resolved.minX = msg.minX;
    }
    else {
      resolved.minX = 0.0
    }

    if (msg.maxX !== undefined) {
      resolved.maxX = msg.maxX;
    }
    else {
      resolved.maxX = 0.0
    }

    if (msg.minY !== undefined) {
      resolved.minY = msg.minY;
    }
    else {
      resolved.minY = 0.0
    }

    if (msg.maxY !== undefined) {
      resolved.maxY = msg.maxY;
    }
    else {
      resolved.maxY = 0.0
    }

    return resolved;
    }
};

module.exports = grassLimits;
