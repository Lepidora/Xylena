#pragma once

//System includes
#include <cmath>

#include <cassert>
#include <initializer_list>

# define PI 3.14159265358979323846

//Vectors

template<constexpr int s, typename T = float>
struct vec {
    
    static_assert(s > 0, "Vector size cannot be less than or equal to zero");
    
    typedef T value;
    typedef vec<s, T> type;
    
    value data[s];
    
    //Constructors
    vec() {
        for (auto &i: data) { i = 0; }
    }
    
    vec(type &v) {
        for (int i = 0; i < s; i++) { data[i] = v.data[i]; }
    }
    
    vec(type const &v) {
        for (int i = 0; i < s; i++) { data[i] = v.data[i]; }
    }
    
    vec(vec<s-1, value> const &v, value val) {
        for (int i = 0; i < s-1; i++) { data[i] = v.data[i]; }
        data[s-1] = val;
    }
    
    vec(vec<s-1, value> const &v): vec(v, 0) {}
    
    vec(value v) {
        for (auto &i: data) { i = v; }
    }
    
    vec(value values[]) {
        assert(sizeof(values) <= sizeof(data));
        strcpy(data, values);
    }
    
    template<typename... V>
    vec(V... values): data{static_cast<value>(values)...} {}
    
    //Operators
    
    //++
    
    inline type operator++() {
        for (auto &i: data) { i += 1; }
        return *this;
    }
    
    //--
    
    inline type operator--() {
        for (auto &i: data) { i -= 1; }
        return *this;
    }
    
    //+
    
    inline type operator+(type const &v) {
        type newVec(*this);
        for (int i = 0; i < s; i++) { newVec->data[i] += v->data[i]; }
        return *newVec;
    }
    
    inline const type operator+(type const &v) const {
        type newVec(*this);
        for (int i = 0; i < s; i++) { newVec.data[i] += v.data[i]; }
        return newVec;
    }
    
    inline type operator+(T v) {
        type newVec(*this);
        for (auto &i: newVec.data) { i = (i + v); }
        return newVec;
    }
    
    //-
    
    inline type operator-(type &v) {
        type newVec(*this);
        for (int i = 0; i < s; i++) { newVec->data[i] -= v[i]; }
        return *newVec;
    }
    
    inline type operator-(T v) {
        type newVec(*this);
        for (auto &i: newVec->data) { i = (i - v); }
        return *newVec;
    }
    
    //*
    
    inline const type operator*(type const &v) const {
        type newVec(*this);
        for (int i = 0; i < s; i++) { newVec.data[i] *= v.data[i]; }
        return newVec;
    }
    
    inline const type operator*(T v) const {
        type newVec(*this);
        for (auto &i: newVec.data) { i = (i * v); }
        return newVec;
    }
    
    ///
    
    inline type operator/(type &v) {
        type newVec(*this);
        for (int i = 0; i < s; i++) { newVec[i] /= v[i]; }
        return *newVec;
    }
    
    inline type operator/(T v) {
        type newVec(*this);
        for (auto &i: newVec->data) { i = (i / v); }
        return *newVec;
    }
    
    //==
    
    inline type operator==(type &v) {
        type newVec(*this);
        bool result = true;
        for (int i = 0; i < s; i++) { result = (newVec[i] == v[i]); if(!result) break; }
        return result;
    }
    
    //!=
    
    inline type operator!=(type &v) {
        type newVec(*this);
        bool result = true;
        for (int i = 0; i < s; i++) { result = (newVec[i] != v[i]); if(!result) break; }
        return result;
    }
    
    //[]
    
    inline value & operator[](int v) {
        return data[v];
    }    
    
    inline const value & operator[](int v) const {
        return data[v];
    }
    
};

//Matrices

template<constexpr int w, constexpr int h, typename T = float>
struct mat {
    typedef vec<w, T> column;
    typedef vec<h, T> row;
    typedef mat<w, h, T> type;
    
    column data[w];
    
    //Constructors
    
    mat() {
        for (int i = 0; i < w; i++) { data[i] = column(0); data[i][i] = 1; }
    }
    
    mat(T v) {
        for (int i = 0; i < w; i++) { data[i] = column(0); data[i][i] = v; }
    }
    
    mat(type const &m) {
        for (int i = 0; i < w; i++) { data[i] = m.data[i]; }
    }
    
    mat(mat<w-1, h, T> const &m) {
        for (int i = 0; i < w-1; i++) { data[i] = m->data[i]; }
        data[w-1] = 0;
    }
    
    mat(std::initializer_list<column> values):data(values) {
        static_assert(values.size()*sizeof(column) <= sizeof(data), "Cannot initialise vector with more elements than its size");
    }
    
    template<typename... C>
    mat(C... columns): data{static_cast<column>(columns)...} {}
    
    //Functions
    
    inline T* ptr() {
        return &(data[0][0]);
    }
    
    //Operators
    
    //++
    
    inline type operator++() {
        for (auto &i: data) { i += 1; }
        return *this;
    }
    
    //--
    
    inline type operator--() {
        for (auto &i: data) { i -= 1; }
        return *this;
    }
    
    //+
    
    inline type operator+(const type &m) {
        type newMat(*this);
        for (int i = 0; i < w; i++) { newMat[i] += m[i]; }
        return *newMat;
    }
    
    inline type operator+(T v) {
        type newMat(*this);
        for (auto &i: newMat->data) { i = (i + v); }
        return *newMat;
    }
    
    //-
    
    inline type operator-(const type &m) {
        type newMat(*this);
        for (int i = 0; i < w; i++) { newMat[i] -= m[i]; }
        return *newMat;
    }
    
    inline type operator-(T v) {
        type newMat(*this);
        for (auto &i: newMat->data) { i = (i - v); }
        return *newMat;
    }
    
    //*
    
    inline type operator*(type const &m) {
        type newMat;
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                for (int k = 0; k < h; k++) {
                    newMat[i][j] += (*this)[k][j] * m[i][k];
                }
            }
        }
        return newMat;
    }
    
    inline type operator*(T v) {
        type newMat(*this);
        for (auto &i: newMat.data) { i = (i * v); }
        return *newMat;
    }
    
    ///
    
    inline type operator/(const type &m) {
        type newMat(*this);
        for (int i = 0; i < w; i++) {
            newMat[i] /= m[i];
        }
        return *newMat;
    }
    
    inline type operator/(T v) {
        type newMat(*this);
        for (auto &i: newMat->data) { i = (i / v); }
        return *newMat;
    }
    
    //==
    
    inline type operator==(const type &m) {
        type newMat(*this);
        bool result = true;
        for (int i = 0; i < w; i++) { result = (newMat[i] == m[i]); if(!result) break; }
        return result;
    }
    
    //!=
    
    inline type operator!=(const type &m) {
        type newMat(*this);
        bool result = true;
        for (int i = 0; i < w; i++) { result = (newMat[i] != m[i]); if(!result) break; }
        return result;
    }
    
    //[]
    
    inline column & operator[](int v) {
        return data[v];
    }
    
    inline const column & operator[](int v) const {
        return data[v];
    }
};

//Typedefs

//Vector types

typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

//Matrix types

typedef mat<2,2> mat2;
typedef mat<3,3> mat3;
typedef mat<4,4> mat4;

typedef mat<1,2> mat1x2;
typedef mat<1,3> mat1x3;
typedef mat<1,4> mat1x4;

typedef mat<2,1> mat2x1;
typedef mat<2,3> mat2x3;
typedef mat<2,4> mat2x4;

typedef mat<3,1> mat3x1;
typedef mat<3,2> mat3x2;
typedef mat<3,4> mat3x4;

typedef mat<4,1> mat4x1;
typedef mat<4,2> mat4x2;
typedef mat<4,3> mat4x3;

//Functions

//Vector Functions

template<int s, typename T = float>
inline T vecDot(vec<s,T> const &v, vec<s,T> const &v2) {
    
    vec<s,T> temp(v * v2);
    
    T ret;
    
    for (int i = 0; i < s; i++) {
        ret += temp[i];
    }
    
    return ret;
}

template<int s, typename T = float>
inline vec<s,T> vecSqrt(vec<s,T> const &v) {
    
    vec<s,T> ret;
    
    for (int i = 0; i < s; i++) {
        ret[i] = std::sqrt(v[i]);
    }
    
    return ret;
}

template<int s, typename T = float>
inline vec<s,T> vecInverseSqrt(vec<s,T> const v) {
    return 1.0f / vecSqrt(v);
}

template<typename T = float>
inline T inverseSqrt(T v) {
    return 1.0f / std::sqrt(v);
}

template<int s, typename T = float>
inline vec<s,T> vecNormalize(vec<s,T> const &v) {
    return v * inverseSqrt(vecDot(v, v));
}

//Matrix Functions

template<typename T = float>
inline mat4 ortho(T left, T right, T bottom, T top, T near, T far) {
    
    mat4 orth;
    orth[0][0] = 2 / (right - left);
    orth[1][1] = 2 / (top - bottom);
    orth[3][0] = -(right + left) / (right - left);
    orth[3][1] = -(top + bottom) / (top - bottom);
    orth[2][2] = -2 / (far - near);
    orth[3][2] = -(far + near) / (far - near);
    
    return orth;
}

inline mat4 scale(mat4 const &m, vec3 const &v) {
    
    mat4 scl;
    scl[0] = m[0] * v[0];
    scl[1] = m[1] * v[1];
    scl[2] = m[2] * v[2];
    scl[3] = m[3];
    
    return scl;
}

inline mat4 translate(mat4 const &m, vec3 const &v) {
    
    mat4 trl(m);
    trl[3] = (m[0] * v[0]) +
             (m[1] * v[1]) +
             (m[2] * v[2]) +
             (m[3]);
    
    return trl;
}

template<typename T = float>
inline mat4 rotate(mat4 const &m, T a, vec3 const &v) {
    
    T cosA = cos(a);
    T sinA = sin(a);
    
    vec3 ax = vecNormalize(v);
    vec3 tmp = ax * (((T)1) - cosA);
    
    mat4 r;
    
    r[0][0] = cosA + tmp[0] * ax[0];
    r[0][1] = tmp[0] * ax[1] + sinA * ax[2];
    r[0][2] = tmp[0] * ax[2] - sinA * ax[1];
    
    r[1][0] = tmp[1] * ax[0] - sinA * ax[2];
    r[1][1] = cosA + tmp[1] * ax[1];
    r[1][2] = tmp[1] * ax[2] + sinA * ax[0];
    
    r[2][0] = tmp[2] * ax[0] + sinA * ax[1];
    r[2][1] = tmp[2] * ax[1] - sinA * ax[0];
    r[2][2] = cosA + tmp[2] * ax[2];
    
    mat4 res;
    
    res[0] = m[0] * r[0][0] + m[1] * r[0][1] + m[2] * r[0][2];
    res[1] = m[0] * r[1][0] + m[1] * r[1][1] + m[2] * r[1][2];
    res[2] = m[0] * r[2][0] + m[1] * r[2][1] + m[2] * r[2][2];
    res[3] = m[3];
    
    return res;
}

template<typename T = float>
inline T radians(T v) {
    return v * PI / 180;
}