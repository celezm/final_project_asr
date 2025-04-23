// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from navigation_interfaces:action/GenerateInformation.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "navigation_interfaces/action/generate_information.hpp"


#ifndef NAVIGATION_INTERFACES__ACTION__DETAIL__GENERATE_INFORMATION__BUILDER_HPP_
#define NAVIGATION_INTERFACES__ACTION__DETAIL__GENERATE_INFORMATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "navigation_interfaces/action/detail/generate_information__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_Goal_key
{
public:
  Init_GenerateInformation_Goal_key()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::navigation_interfaces::action::GenerateInformation_Goal key(::navigation_interfaces::action::GenerateInformation_Goal::_key_type arg)
  {
    msg_.key = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_Goal>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_Goal_key();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_Result_final_content
{
public:
  explicit Init_GenerateInformation_Result_final_content(::navigation_interfaces::action::GenerateInformation_Result & msg)
  : msg_(msg)
  {}
  ::navigation_interfaces::action::GenerateInformation_Result final_content(::navigation_interfaces::action::GenerateInformation_Result::_final_content_type arg)
  {
    msg_.final_content = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_Result msg_;
};

class Init_GenerateInformation_Result_success
{
public:
  Init_GenerateInformation_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateInformation_Result_final_content success(::navigation_interfaces::action::GenerateInformation_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GenerateInformation_Result_final_content(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_Result>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_Result_success();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_Feedback_provisional_content
{
public:
  Init_GenerateInformation_Feedback_provisional_content()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::navigation_interfaces::action::GenerateInformation_Feedback provisional_content(::navigation_interfaces::action::GenerateInformation_Feedback::_provisional_content_type arg)
  {
    msg_.provisional_content = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_Feedback>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_Feedback_provisional_content();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_SendGoal_Request_goal
{
public:
  explicit Init_GenerateInformation_SendGoal_Request_goal(::navigation_interfaces::action::GenerateInformation_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Request goal(::navigation_interfaces::action::GenerateInformation_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Request msg_;
};

class Init_GenerateInformation_SendGoal_Request_goal_id
{
public:
  Init_GenerateInformation_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateInformation_SendGoal_Request_goal goal_id(::navigation_interfaces::action::GenerateInformation_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_GenerateInformation_SendGoal_Request_goal(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_SendGoal_Request>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_SendGoal_Request_goal_id();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_SendGoal_Response_stamp
{
public:
  explicit Init_GenerateInformation_SendGoal_Response_stamp(::navigation_interfaces::action::GenerateInformation_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Response stamp(::navigation_interfaces::action::GenerateInformation_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Response msg_;
};

class Init_GenerateInformation_SendGoal_Response_accepted
{
public:
  Init_GenerateInformation_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateInformation_SendGoal_Response_stamp accepted(::navigation_interfaces::action::GenerateInformation_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_GenerateInformation_SendGoal_Response_stamp(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_SendGoal_Response>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_SendGoal_Response_accepted();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_SendGoal_Event_response
{
public:
  explicit Init_GenerateInformation_SendGoal_Event_response(::navigation_interfaces::action::GenerateInformation_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Event response(::navigation_interfaces::action::GenerateInformation_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Event msg_;
};

class Init_GenerateInformation_SendGoal_Event_request
{
public:
  explicit Init_GenerateInformation_SendGoal_Event_request(::navigation_interfaces::action::GenerateInformation_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_GenerateInformation_SendGoal_Event_response request(::navigation_interfaces::action::GenerateInformation_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GenerateInformation_SendGoal_Event_response(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Event msg_;
};

class Init_GenerateInformation_SendGoal_Event_info
{
public:
  Init_GenerateInformation_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateInformation_SendGoal_Event_request info(::navigation_interfaces::action::GenerateInformation_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GenerateInformation_SendGoal_Event_request(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_SendGoal_Event>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_SendGoal_Event_info();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_GetResult_Request_goal_id
{
public:
  Init_GenerateInformation_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::navigation_interfaces::action::GenerateInformation_GetResult_Request goal_id(::navigation_interfaces::action::GenerateInformation_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_GetResult_Request>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_GetResult_Request_goal_id();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_GetResult_Response_result
{
public:
  explicit Init_GenerateInformation_GetResult_Response_result(::navigation_interfaces::action::GenerateInformation_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::navigation_interfaces::action::GenerateInformation_GetResult_Response result(::navigation_interfaces::action::GenerateInformation_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_GetResult_Response msg_;
};

class Init_GenerateInformation_GetResult_Response_status
{
public:
  Init_GenerateInformation_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateInformation_GetResult_Response_result status(::navigation_interfaces::action::GenerateInformation_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_GenerateInformation_GetResult_Response_result(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_GetResult_Response>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_GetResult_Response_status();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_GetResult_Event_response
{
public:
  explicit Init_GenerateInformation_GetResult_Event_response(::navigation_interfaces::action::GenerateInformation_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::navigation_interfaces::action::GenerateInformation_GetResult_Event response(::navigation_interfaces::action::GenerateInformation_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_GetResult_Event msg_;
};

class Init_GenerateInformation_GetResult_Event_request
{
public:
  explicit Init_GenerateInformation_GetResult_Event_request(::navigation_interfaces::action::GenerateInformation_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_GenerateInformation_GetResult_Event_response request(::navigation_interfaces::action::GenerateInformation_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GenerateInformation_GetResult_Event_response(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_GetResult_Event msg_;
};

class Init_GenerateInformation_GetResult_Event_info
{
public:
  Init_GenerateInformation_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateInformation_GetResult_Event_request info(::navigation_interfaces::action::GenerateInformation_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GenerateInformation_GetResult_Event_request(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_GetResult_Event>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_GetResult_Event_info();
}

}  // namespace navigation_interfaces


namespace navigation_interfaces
{

namespace action
{

namespace builder
{

class Init_GenerateInformation_FeedbackMessage_feedback
{
public:
  explicit Init_GenerateInformation_FeedbackMessage_feedback(::navigation_interfaces::action::GenerateInformation_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::navigation_interfaces::action::GenerateInformation_FeedbackMessage feedback(::navigation_interfaces::action::GenerateInformation_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_FeedbackMessage msg_;
};

class Init_GenerateInformation_FeedbackMessage_goal_id
{
public:
  Init_GenerateInformation_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GenerateInformation_FeedbackMessage_feedback goal_id(::navigation_interfaces::action::GenerateInformation_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_GenerateInformation_FeedbackMessage_feedback(msg_);
  }

private:
  ::navigation_interfaces::action::GenerateInformation_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::navigation_interfaces::action::GenerateInformation_FeedbackMessage>()
{
  return navigation_interfaces::action::builder::Init_GenerateInformation_FeedbackMessage_goal_id();
}

}  // namespace navigation_interfaces

#endif  // NAVIGATION_INTERFACES__ACTION__DETAIL__GENERATE_INFORMATION__BUILDER_HPP_
