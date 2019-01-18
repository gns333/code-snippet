#include<type_traits>

/*
�������ж��Ƿ���ڳ�Ա����attr��Cpp03��
����������ͬ����Ա ģ��ʵ������������ʧ��
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
�������ж��Ƿ���ڳ�Ա����attr��Cpp17��
ģ��ƫ�ػ�
*/
template< typename, typename = void >																  
struct has_member_attr_cpp17 : std::false_type{};
template< typename T >																				  
struct has_member_attr_cpp17< T, std::void_t<decltype(std::declval<T>().attr)>> :std::true_type {};

/*
�������ж��Ƿ���ڳ�Ա����func(int)��Cpp17��
ģ��ƫ�ػ�
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