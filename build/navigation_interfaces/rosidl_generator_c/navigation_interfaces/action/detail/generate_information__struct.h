// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from navigation_interfaces:action/GenerateInformation.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "navigation_interfaces/action/generate_information.h"


#ifndef NAVIGATION_INTERFACES__ACTION__DETAIL__GENERATE_INFORMATION__STRUCT_H_
#define NAVIGATION_INTERFACES__ACTION__DETAIL__GENERATE_INFORMATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'key'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_Goal
{
  rosidl_runtime_c__String key;
} navigation_interfaces__action__GenerateInformation_Goal;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_Goal.
typedef struct navigation_interfaces__action__GenerateInformation_Goal__Sequence
{
  navigation_interfaces__action__GenerateInformation_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'final_content'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_Result
{
  bool success;
  rosidl_runtime_c__String final_content;
} navigation_interfaces__action__GenerateInformation_Result;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_Result.
typedef struct navigation_interfaces__action__GenerateInformation_Result__Sequence
{
  navigation_interfaces__action__GenerateInformation_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'provisional_content'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_Feedback
{
  rosidl_runtime_c__String provisional_content;
} navigation_interfaces__action__GenerateInformation_Feedback;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_Feedback.
typedef struct navigation_interfaces__action__GenerateInformation_Feedback__Sequence
{
  navigation_interfaces__action__GenerateInformation_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "navigation_interfaces/action/detail/generate_information__struct.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  navigation_interfaces__action__GenerateInformation_Goal goal;
} navigation_interfaces__action__GenerateInformation_SendGoal_Request;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_SendGoal_Request.
typedef struct navigation_interfaces__action__GenerateInformation_SendGoal_Request__Sequence
{
  navigation_interfaces__action__GenerateInformation_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} navigation_interfaces__action__GenerateInformation_SendGoal_Response;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_SendGoal_Response.
typedef struct navigation_interfaces__action__GenerateInformation_SendGoal_Response__Sequence
{
  navigation_interfaces__action__GenerateInformation_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  navigation_interfaces__action__GenerateInformation_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  navigation_interfaces__action__GenerateInformation_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  navigation_interfaces__action__GenerateInformation_SendGoal_Request__Sequence request;
  navigation_interfaces__action__GenerateInformation_SendGoal_Response__Sequence response;
} navigation_interfaces__action__GenerateInformation_SendGoal_Event;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_SendGoal_Event.
typedef struct navigation_interfaces__action__GenerateInformation_SendGoal_Event__Sequence
{
  navigation_interfaces__action__GenerateInformation_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} navigation_interfaces__action__GenerateInformation_GetResult_Request;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_GetResult_Request.
typedef struct navigation_interfaces__action__GenerateInformation_GetResult_Request__Sequence
{
  navigation_interfaces__action__GenerateInformation_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "navigation_interfaces/action/detail/generate_information__struct.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_GetResult_Response
{
  int8_t status;
  navigation_interfaces__action__GenerateInformation_Result result;
} navigation_interfaces__action__GenerateInformation_GetResult_Response;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_GetResult_Response.
typedef struct navigation_interfaces__action__GenerateInformation_GetResult_Response__Sequence
{
  navigation_interfaces__action__GenerateInformation_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  navigation_interfaces__action__GenerateInformation_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  navigation_interfaces__action__GenerateInformation_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  navigation_interfaces__action__GenerateInformation_GetResult_Request__Sequence request;
  navigation_interfaces__action__GenerateInformation_GetResult_Response__Sequence response;
} navigation_interfaces__action__GenerateInformation_GetResult_Event;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_GetResult_Event.
typedef struct navigation_interfaces__action__GenerateInformation_GetResult_Event__Sequence
{
  navigation_interfaces__action__GenerateInformation_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "navigation_interfaces/action/detail/generate_information__struct.h"

/// Struct defined in action/GenerateInformation in the package navigation_interfaces.
typedef struct navigation_interfaces__action__GenerateInformation_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  navigation_interfaces__action__GenerateInformation_Feedback feedback;
} navigation_interfaces__action__GenerateInformation_FeedbackMessage;

// Struct for a sequence of navigation_interfaces__action__GenerateInformation_FeedbackMessage.
typedef struct navigation_interfaces__action__GenerateInformation_FeedbackMessage__Sequence
{
  navigation_interfaces__action__GenerateInformation_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} navigation_interfaces__action__GenerateInformation_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // NAVIGATION_INTERFACES__ACTION__DETAIL__GENERATE_INFORMATION__STRUCT_H_
