/**
 * @file ctvector.cpp
 *
 * Simple vector classes. Classes ctvector_fp and ctvector_int are
 * designed to be wrappers around double* and int* arrays,
 * respectively.  They provide a few convenient methods that function
 * like those of std::vector<T>, but unlike the STL classes explicitly
 * allow accessing a pointer to the underlying data array.
 */
  
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;
#include "ctvector.h"
using namespace ct;

    ostream& operator<<(ostream& s, const ctvector_int& v) {
        int n = v.size();
        s << "<";
        for (int i = 0; i < n; i++) {
            s << v[i];
            if (i < n-1) s << ", ";
        }
        s << ">";
        return s;
    }

    ostream& operator<<(ostream& s, const ctvector_fp& v) {
        int n = v.size();
        s << "<";
        for (int i = 0; i < n; i++) {
            s << v[i];
            if (i < n-1) s << ", ";
        }
        s << ">";
        return s;
    }

namespace ct {

    ctvector_fp::ctvector_fp(size_t n) : _size(0), _alloc(0), _data(0) {
        resize(n);
    }

    ctvector_fp::ctvector_fp(size_t n, value_type v0) 
        : _size(0), _alloc(0), _data(0) {
            resize(n, v0);
    }

    ctvector_fp::ctvector_fp(const ctvector_fp& x) {
        if (x._alloc > 0) {
            _data = new value_type[x._alloc];
            copy(x._data, x._data + x._alloc, _data);
        }
        else {
            _data = 0;
        }
        _size = x._size;
        _alloc = x._alloc;
    }

    ctvector_fp ctvector_fp::operator=(const ctvector_fp& x) {
        if (this == &x) return *this;
        if (_data) delete[] _data;
        if (x._alloc > 0) {
            _data = new value_type[x._alloc];
            copy(x._data, x._data + x._alloc, _data);
        }
        else {
            _data = 0;
        }
        _size = x._size;
        _alloc = x._alloc;
        return *this;
    }

    ctvector_fp::~ctvector_fp() {
        if (_data) delete[] _data;
        _data = 0;
    }

    void ctvector_fp::resize(size_t n) {
        size_t new_alloc = n+1;
        value_type* newdata = new value_type[new_alloc];
        size_t datalen = (n > _size ? _size : n);
	if (_data) {
	  copy(_data, _data + datalen, newdata);
	}
        if (_data) delete[] _data;
        _data = newdata;
        _alloc = new_alloc;
        _size = n;
    }

    void ctvector_fp::resize(size_t n, value_type v0) {
        size_t new_alloc = n+1;
        value_type* newdata = new value_type[new_alloc];
        fill(newdata, newdata + new_alloc, v0);
        size_t datalen = (n > _size ? _size : n);
	if (_data) {
	  copy(_data, _data + datalen, newdata);
	}
        if (_data) delete[] _data;
        _data = newdata;
        _alloc = new_alloc;
        _size = n;
    }

    void ctvector_fp::push_back(value_type x) {
        size_t loc = _size;
        if (_size == _alloc) {
            resize(2*_alloc);
        }
        _data[loc] = x;
        _size = loc + 1;
    }

    void ctvector_fp::clear() { fill(_data, _data + _size, 0.0); resize(0); }



    //-------------------------------------//
    //             ctvector_int            //
    //-------------------------------------//


    ctvector_int::ctvector_int(size_t n) : _size(0), _alloc(0), _data(0) {
        resize(n);
    }

    ctvector_int::ctvector_int(size_t n, value_type v0) 
        : _size(0), _alloc(0), _data(0) {
        resize(n, v0);
    }

    ctvector_int::ctvector_int(const ctvector_int& x) {
        if (x._alloc > 0) {
            _data = new value_type[x._alloc];
            copy(x._data, x._data + x._alloc, _data);
        }
        _size = x._size;
        _alloc = x._alloc;
    }

    ctvector_int ctvector_int::operator=(const ctvector_int& x) {
        if (this == &x) return *this;
        if (x._alloc > 0) {
            _data = new value_type[x._alloc];
            copy(x._data, x._data + x._alloc, _data);
        }
        _size = x._size;
        _alloc = x._alloc;
        return *this;
    }

    ctvector_int::~ctvector_int() {
        if (_alloc > 0) delete[] _data;
        _data = 0;
    }

    void ctvector_int::resize(size_t n) {
        size_t new_alloc = n+1;
        value_type* newdata = new value_type[new_alloc];
        size_t datalen = (n > _size ? _size : n);
	if (_data) {
	  copy(_data, _data + datalen, newdata);
	}
        if (_alloc > 0) delete[] _data;
        _data = newdata;
        _alloc = new_alloc;
        _size = n;
    }

    void ctvector_int::resize(size_t n, value_type v0) {
        size_t new_alloc = n+1;
        value_type* newdata = new value_type[new_alloc];
        fill(newdata, newdata + new_alloc, v0);
        size_t datalen = (n > _size ? _size : n);
	if (_data) {
	  copy(_data, _data + datalen, newdata);
	}
        if (_alloc > 0) delete[] _data;
        _data = newdata;
        _alloc = new_alloc;
        _size = n;
    }

    void ctvector_int::push_back(value_type x) {
        size_t loc = _size;
        if (_size == _alloc) {
            resize(2*_alloc);
        }
        _data[loc] = x;
        _size = loc + 1;
    }

    void ctvector_int::clear() { fill(_data, _data + _size, 0); resize(0); }
}

