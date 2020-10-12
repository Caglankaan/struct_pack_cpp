#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h> 
#include <memory>

enum endiannesss{little_end='<', big_end='>'};

class StructPack
{
    public:
        enum endiannesss end;
        std::string hex_representation{};
        int arg_count{};
        static std::shared_ptr<StructPack> getInstance() {
            static std::shared_ptr<StructPack> instance(new StructPack());
            return instance;
        }
        StructPack() {};
        StructPack(StructPack const&) = delete;
        ~StructPack() {};
        void operator=(StructPack const&) = delete;

        template<typename T>
        std::string tToHex( T t )
        {
            std::stringstream ss;
            ss << std::setfill ('0') << std::setw(sizeof(T)*2) 
                    << std::hex << t;
            
            
            std::string str{};
            if(end == little_end)
            {
                for(int i = sizeof(T)*2; i > 0; i-=2)
                {
                    str+= ss.str().substr(i-2,2);
                }
            }
            else
            {
                str = ss.str();
            }
            return str;
        }
        std::vector<unsigned int> unpack(const std::string packet_str)
        {
            std::vector<unsigned int> unpacked_bytes;
            for(int i = 0; i < packet_str.size(); i+=2)
            {
                std::stringstream ss;
                std::string str_byte = "0x" + packet_str.substr(i,2);
                unsigned int byte;
                ss << std::hex << str_byte;
                ss >> byte;
                unpacked_bytes.push_back(byte);
            }
            return unpacked_bytes;
        }

        template<typename T>
        std::string pack(const std::string &struct_type, T t)
        {
            hex_representation += tToHex(t);
            std::string ret = hex_representation;
            hex_representation.clear();
            
            return ret;
        }
        
       
        template<typename T, typename... Args>
        std::string pack(const std::string &struct_type, T t, Args... args)
        {
            if(struct_type.size() != 1 && struct_type != "<" && struct_type != ">")
            {
                throw "Wrong argument (<)!";
                 
            }
            end = (struct_type == "<") ? little_end : big_end;
            hex_representation += tToHex(t);
            
            return pack(struct_type, args...);
        }
};
