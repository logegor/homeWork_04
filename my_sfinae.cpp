#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <list>

const uint8_t numBits = 8;

//мой аллокатор

template <class T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(T ip)
{
    for (size_t idx = numBits; idx <= sizeof(T) * numBits; idx += numBits)
    {
        if (idx != numBits)
            std::cout << ".";
        std::cout << (uint32_t)((uint8_t)(ip >> (sizeof(T)* numBits - idx)));
    }
    std::cout << std::endl;
};

template <class T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_ip(T ip)
{
    std::cout << ip;
    std::cout << std::endl;
};


template<class T>
typename std::enable_if<std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>::value
                        || std::is_same<T, std::list<typename T::value_type>>::value,
                        void>::type
print_ip(T ip)
{
    for (auto it = ip.begin(); it != std::prev(ip.end()); ++it)
    {
        std::cout << *it;
        std::cout << ".";
    }
    std::cout << ip.back();
    std::cout << std::endl;
};

// template<class T>
// typename std::enable_if<std::is_same<T, std::tuple<typename T::value_type>>::value, void>::type
// print_ip(T ip)
// {
//     for (auto it = ip.begin(); it != ip.end(); ++it)
//     {
//         std::cout << *it;
//         if (it != ip.end() - 1)
//             std::cout << ".";
//     }
//     std::cout << std::endl;
// };

int main()
{
    try
    {
        auto a = std::vector<int>{100, 200, 300, 400};
        print_ip( int8_t{-1} ); // 255
        print_ip( int16_t{0} ); // 0.0
        print_ip( int32_t{2130706433} ); // 127.0.0.1
        print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
        print_ip( std::string{"Hello, World!"} ); // Hello, World!
        print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
        print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
        // print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
