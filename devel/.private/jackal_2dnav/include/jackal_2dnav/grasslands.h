// Generated by gencpp from file jackal_2dnav/grasslands.msg
// DO NOT EDIT!


#ifndef JACKAL_2DNAV_MESSAGE_GRASSLANDS_H
#define JACKAL_2DNAV_MESSAGE_GRASSLANDS_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <jackal_2dnav/grassLimits.h>

namespace jackal_2dnav
{
template <class ContainerAllocator>
struct grasslands_
{
  typedef grasslands_<ContainerAllocator> Type;

  grasslands_()
    : grasslands()  {
    }
  grasslands_(const ContainerAllocator& _alloc)
    : grasslands(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::jackal_2dnav::grassLimits_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::jackal_2dnav::grassLimits_<ContainerAllocator> >> _grasslands_type;
  _grasslands_type grasslands;





  typedef boost::shared_ptr< ::jackal_2dnav::grasslands_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::jackal_2dnav::grasslands_<ContainerAllocator> const> ConstPtr;

}; // struct grasslands_

typedef ::jackal_2dnav::grasslands_<std::allocator<void> > grasslands;

typedef boost::shared_ptr< ::jackal_2dnav::grasslands > grasslandsPtr;
typedef boost::shared_ptr< ::jackal_2dnav::grasslands const> grasslandsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::jackal_2dnav::grasslands_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::jackal_2dnav::grasslands_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::jackal_2dnav::grasslands_<ContainerAllocator1> & lhs, const ::jackal_2dnav::grasslands_<ContainerAllocator2> & rhs)
{
  return lhs.grasslands == rhs.grasslands;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::jackal_2dnav::grasslands_<ContainerAllocator1> & lhs, const ::jackal_2dnav::grasslands_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace jackal_2dnav

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::jackal_2dnav::grasslands_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jackal_2dnav::grasslands_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jackal_2dnav::grasslands_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jackal_2dnav::grasslands_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jackal_2dnav::grasslands_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jackal_2dnav::grasslands_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::jackal_2dnav::grasslands_<ContainerAllocator> >
{
  static const char* value()
  {
    return "46f47fc035cf3ac098d5a2252afa7df8";
  }

  static const char* value(const ::jackal_2dnav::grasslands_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x46f47fc035cf3ac0ULL;
  static const uint64_t static_value2 = 0x98d5a2252afa7df8ULL;
};

template<class ContainerAllocator>
struct DataType< ::jackal_2dnav::grasslands_<ContainerAllocator> >
{
  static const char* value()
  {
    return "jackal_2dnav/grasslands";
  }

  static const char* value(const ::jackal_2dnav::grasslands_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::jackal_2dnav::grasslands_<ContainerAllocator> >
{
  static const char* value()
  {
    return "jackal_2dnav/grassLimits[] grasslands\n"
"\n"
"================================================================================\n"
"MSG: jackal_2dnav/grassLimits\n"
"float64 minX\n"
"float64 maxX\n"
"\n"
"float64 minY\n"
"float64 maxY\n"
;
  }

  static const char* value(const ::jackal_2dnav::grasslands_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::jackal_2dnav::grasslands_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.grasslands);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct grasslands_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::jackal_2dnav::grasslands_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::jackal_2dnav::grasslands_<ContainerAllocator>& v)
  {
    s << indent << "grasslands[]" << std::endl;
    for (size_t i = 0; i < v.grasslands.size(); ++i)
    {
      s << indent << "  grasslands[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::jackal_2dnav::grassLimits_<ContainerAllocator> >::stream(s, indent + "    ", v.grasslands[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // JACKAL_2DNAV_MESSAGE_GRASSLANDS_H
