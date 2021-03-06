#include "../include/Vector2.h"
#include <iostream>

namespace my_math {

// Functions of KernelVector2.

KernelVector2::KernelVector2(void)
    :  x_(0),
       y_(0) {
  }

KernelVector2::KernelVector2(VECTOR_TYPE  x, VECTOR_TYPE  y)
    :  x_(x),
       y_(y)  {
}

KernelVector2::KernelVector2(const KernelVector2 & that)
    :  x_(that.x_),
       y_(that.y_) {
}

KernelVector2::KernelVector2(KernelVector2 && that)
    :  x_(std::move(that.x_)),
       y_(std::move(that.y_))  {
}

KernelVector2::KernelVector2(const sf::Vector2i & vect)
    :  x_(vect.x),
       y_(vect.y) {
}

KernelVector2::KernelVector2(const sf::Vector2f & vect)
    :  x_(vect.x),
       y_(vect.y) {
}

KernelVector2 & KernelVector2::operator=(const KernelVector2 & vect) {
  x_ = vect.x_;
  y_ = vect.y_;
  return *this;
}

KernelVector2 & KernelVector2::operator=(const KernelVector2 && vect) {
  x_ = vect.x_;
  y_ = vect.y_;
  return *this;
}

void KernelVector2::Dump(void) const
{
    std::cout << "x_ = " << x_ << " y_ = " << y_ << std::endl;
    return;
}

KernelVector2 & KernelVector2::operator+=(const KernelVector2 & vect) {
  x_ += vect.x_;
  y_ += vect.y_;  
  return *this;
}

KernelVector2 & KernelVector2::operator*=(const VECTOR_TYPE  k) {
  x_ *= k;
  y_ *= k;  
  return *this;
}

VECTOR_TYPE  KernelVector2::Len(void) const {
  return sqrt(x_ * x_ + y_ * y_);
}

void KernelVector2::Reset(const VECTOR_TYPE  x, const VECTOR_TYPE  y) {
  x_ = x;
  y_ = y;
  return;
}

void KernelVector2::Rotate(const VECTOR_TYPE degree) {
  if (!x_ && !y_) {
    return;
  }

  VECTOR_TYPE angle = atan2(y_, x_);
  angle += (degree * PI) / 180;
  VECTOR_TYPE len = Len( );
  x_ = len * cos(angle);
  y_ = len * sin(angle);
  return; 
}

float KernelVector2::GetX(void) const {
  return x_;
}

float KernelVector2::GetY(void) const {
  return y_;
}
//Functions for Vector2.

  Vector2 & Vector2::operator=(const Vector2 & vect) {
    KernelVector2::operator=(vect);
    return *this;
  }

Vector2 Vector2::operator+(const Vector2 & vect) const {
    Vector2 new_vect = Vector2(vect); 
    new_vect += *this;
    return new_vect;
}

Vector2 & Vector2::operator-=(const Vector2 & vect) {
  *this = *this - vect;
  return *this;
}

Vector2 Vector2::operator-(const Vector2 & vect) const {
  Vector2 new_vect = Vector2(*this);
  new_vect += vect * (-1);
  return new_vect;
}

Vector2 Vector2::operator-(void) const {
  Vector2 new_vect = Vector2(*this);
  new_vect *= (-1); 
  return new_vect;
}

Vector2 Vector2::operator*(const VECTOR_TYPE  k) const {
  Vector2 new_vect = Vector2(*this);
  new_vect *= k;  
  return new_vect;
}

Vector2 Vector2::operator/(const VECTOR_TYPE  k) const {
  Vector2 new_vect = Vector2(*this);
  new_vect *= 1 / k;  
  return new_vect;
}

VECTOR_TYPE  Vector2::SquareLen(void) const {
  float len = Len( );
    return len * len;
}

Vector2 Vector2::GetRotated(const VECTOR_TYPE  degree) const {
  Vector2 new_vect = Vector2(*this);
  new_vect.Rotate(degree);
  return new_vect;
}

float Vector2::GetClockwiseRotation(int* code_error = nullptr) const
{
  if (x_ == 0 && y_ == 0)
  {
    if (code_error)
    {
      *code_error = ZERO_VECTOR;
    }
    return 0.;
  }

  return atan2(y_, x_) + 90.;
}

void Vector2::Norm(void) {
  *this *= 1 / Len( );
  return ;  
}

Vector2 operator*(const VECTOR_TYPE k, const Vector2 & vect)
{
  Vector2 new_vect = Vector2(vect);
  new_vect *= k;
  return new_vect;
}

std::ostream& operator<<(std::ostream& stream, const my_math::Vector2& v)
{
  stream << v.x_ << " " << v.y_;
  return stream;
}

std::istream& operator>>(std::istream& stream, my_math::Vector2& v)
{
  stream >> v.x_ >> v.y_;
  return stream;
}

float Vector2::operator*(const Vector2& other) const
{
  return x_ * other.x_ + y_ * other.y_;
}

float Vector2::GetCosAngleBetweenVectors(const Vector2 & other) const
{
  return (*this * other) / (Len( ) * other.Len());
}

};  // namespace my_math