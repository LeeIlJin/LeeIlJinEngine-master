#pragma once


#define SAFE_RELEASE(p){ if(p){ (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE(p){ if(p){ delete (p); (p) = nullptr; } }
#define SAFE_RELEASE_DELETE(p){ if(p){ (p)->Release(); delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p){ if(p){ delete [] (p); (p) = nullptr; } }
#define HR(hr) assert(SUCCEEDED(hr))

#define TO_STR(parameter) #parameter
#define TO_WSTR(parameter) L#parameter

#define BIND_FUNCTION(class_name, function_name, object, parameter_count)\
BIND_FUNCTION_##parameter_count(class_name,function_name,object)

#define BIND_FUNCTION_0(class_name , function_name,object)\
std::bind(&class_name::function_name,object)

#define BIND_FUNCTION_1(class_name , function_name,object)\
std::bind(&class_name::function_name,object,std::placeholders::_1)

#define BIND_FUNCTION_2(class_name , function_name,object)\
std::bind(&class_name::function_name,object,std::placeholders::_1, std::placeholders::_2)

#define BIND_FUNCTION_3(class_name , function_name,object)\
std::bind(&class_name::function_name,object,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

#define BIND_FUNCTION_4(class_name , function_name,object)\
std::bind(&class_name::function_name,object,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define BIND_FUNCTION_5(class_name , function_name,object)\
std::bind(&class_name::function_name,object,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

#define BIND_FUNCTION_6(class_name , function_name,object)\
std::bind(&class_name::function_name,object,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6)

