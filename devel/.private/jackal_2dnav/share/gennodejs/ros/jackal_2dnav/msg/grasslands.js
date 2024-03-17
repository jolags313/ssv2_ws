// Auto-generated. Do not edit!

// (in-package jackal_2dnav.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let grassLimits = require('./grassLimits.js');

//-----------------------------------------------------------

class grasslands {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.grasslands = null;
    }
    else {
      if (initObj.hasOwnProperty('grasslands')) {
        this.grasslands = initObj.grasslands
      }
      else {
        this.grasslands = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type grasslands
    // Serialize message field [grasslands]
    // Serialize the length for message field [grasslands]
    bufferOffset = _serializer.uint32(obj.grasslands.length, buffer, bufferOffset);
    obj.grasslands.forEach((val) => {
      bufferOffset = grassLimits.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type grasslands
    let len;
    let data = new grasslands(null);
    // Deserialize message field [grasslands]
    // Deserialize array length for message field [grasslands]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.grasslands = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.grasslands[i] = grassLimits.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 32 * object.grasslands.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jackal_2dnav/grasslands';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '46f47fc035cf3ac098d5a2252afa7df8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    jackal_2dnav/grassLimits[] grasslands
    
    ================================================================================
    MSG: jackal_2dnav/grassLimits
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
    const resolved = new grasslands(null);
    if (msg.grasslands !== undefined) {
      resolved.grasslands = new Array(msg.grasslands.length);
      for (let i = 0; i < resolved.grasslands.length; ++i) {
        resolved.grasslands[i] = grassLimits.Resolve(msg.grasslands[i]);
      }
    }
    else {
      resolved.grasslands = []
    }

    return resolved;
    }
};

module.exports = grasslands;
