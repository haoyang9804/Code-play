/*
  I write a blog about this code.
  https://haoyang9804.github.io/blog/C%2B%2B%20-Memory%20Management/
*/
#include <iostream>
#include <string>
using namespace std;
class ArrayWrapper
{
public:
    // default constructor produces a moderately sized array
    ArrayWrapper ()
        : _p_vals( new int[ 64 ] )
        , _size( 64 )
    {}
 
    ArrayWrapper (int n, string name)
        : _p_vals( new int[ n ] )
        , _size( n )
        , _name(name)
    {
    }
 
    // move constructor
    ArrayWrapper (ArrayWrapper&& other)
        : _p_vals( other._p_vals  )
        , _size( other._size )
        , _name( other._name )
    {
        cout << "move " << this->_name << endl;
        other._p_vals = NULL;
        other._size = 0;
    }
 
    // copy constructor
    ArrayWrapper (const ArrayWrapper& other)
        : _p_vals( new int[ other._size  ] )
        , _size( other._size )
        , _name( other._name )
    {
        cout << "copy " << this->_name << endl;
        for ( int i = 0; i < _size; ++i )
        {
            _p_vals[ i ] = other._p_vals[ i ];
        }
    }


    ~ArrayWrapper ()
    {
        cout << "delete " << this->_name << endl;
        delete [] _p_vals;
    }

    const int& size_() {
      return this->_size;
    }

    void rename(string name) {
      this->_name = name;
    }

 
private:
    int *_p_vals;
    int _size;
    string _name;
};


ArrayWrapper createAW(int x) {
  ArrayWrapper aw_1(x, "aw_1");
  ArrayWrapper aw_2(13, "aw_2");
  if (aw_1.size_() > aw_2.size_())
    return aw_1;
  return aw_2;
}

ArrayWrapper createAW_() {
  ArrayWrapper aw_3(15, "aw_3");
  return aw_3;  
}

int main() {
  // ArrayWrapper aw1(12, "aw1");
  // ArrayWrapper aw2(aw1); aw2.rename("aw2");
  // ArrayWrapper aw3(std::move(aw1)); aw3.rename("aw3");
  // ArrayWrapper aw4(createAW_()); aw4.rename("aw4");
  ArrayWrapper aw5(createAW(12)); aw5.rename("aw5");
}