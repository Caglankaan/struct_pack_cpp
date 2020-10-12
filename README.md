# Struct Pack

This header is c++ version of python's struct library. In python we can use pack and unpack like this: 

```python
>>> from struct import *
>>> pack('<hhl', 1, 2, 3)
b'\x01\x00\x02\x00\x03\x00\x00\x00'
>>> >>> unpack("BBBBBBBB", b'\x01\x00\x02\x00\x03\x00\x00\x00')
(1, 0, 2, 0, 3, 0, 0, 0)
```
in our version we can use it like this: 
```cpp
#include "struct_pack"
int main()
{
    std::shared_ptr<StructPack> s = StructPack::getInstance();
    try{
        short first = 1;
        short second = 2;
        int third = 3;
        std::string output = s->pack("<",first,second,third);
        std::vector<unsigned int> packages = s->unpack(output);
        std::cout << "output: " << output << "\n";
        std::cout << "unpack output: ";
        for(auto &package: packages)
        {
             std::cout << package <<" ";
        }
        return 0;
    }
    catch(const char* msg)
    {
        //handle error
    }
}


```
and output is: 

```bash
output: 0100020003000000
unpack output: 1 0 2 0 3 0 0 0 
```
