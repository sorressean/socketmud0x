/**
* Prevent any inheriting classes from copying, assigning, etc.
*/
#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

template <typename T>
class NonCopyable
{
  public: 
    NonCopyable (const NonCopyable &) = delete;
    T & operator = (const T &) = delete;

  protected:
    NonCopyable () = default;
    ~NonCopyable () = default; /// Protected non-virtual destructor
};
#endif
