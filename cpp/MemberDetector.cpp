#include<type_traits>

/*
编译期判断是否存在成员变量attr（Cpp03）
两个父类有同名成员 模板实例化存在歧义失败
*/
template < typename T >
class has_member_attr_cpp03                                                      
{                                                                              
private:                                                                       
    using Y = char[2];                                                         
    using N = char[1];	                                                       
                                                                               
    struct Fallback { int attr; };                                           
    struct Derived : T, Fallback { };                                          
																				
	template<typename U, U> struct Check;                                      
                                                                               
    template < typename U >
    static N& test ( Check<int Fallback::*, &U::attr>* );
    template < typename U >                                                    
    static Y& test ( U* );                                                     
public:                                                                        
    enum																		
	{																			
		value = sizeof(test<Derived>(nullptr)) == sizeof(Y)	    				
	};																			
};

/*
编译期判断是否存在成员变量attr（Cpp17）
模板偏特化
*/
template< typename, typename = void >																  
struct has_member_attr_cpp17 : std::false_type{};
template< typename T >																				  
struct has_member_attr_cpp17< T, std::void_t<decltype(std::declval<T>().attr)>> :std::true_type {};

/*
编译期判断是否存在成员函数func(int)（Cpp17）
模板偏特化
*/
template< typename, typename = void >
struct has_member_func_cpp17 : std::false_type {};
template< typename T >
struct has_member_func_cpp17< T, std::void_t<decltype(std::declval<T>().func(0))>> :std::true_type {};

struct A
{
	int attr;
	void func(int);
};

int main()
{
	static_assert(has_member_attr_cpp03<A>::value, "no attr member");
	static_assert(has_member_attr_cpp17<A>::value, "no attr member");
	static_assert(has_member_func_cpp17<A>::value, "no func member");
	return 0;
}