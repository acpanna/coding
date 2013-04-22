#ifndef GNUSTREAMS_H
#define GNUSTREAMS_H

#include <string>

// In th GNU c++ library 2.95.2, some stream manipulators are missing. Here are workarounds:
// 
namespace std {
  
// stream manipulators std::left, std::right and std:internal for output formatting...

inline ios& left(ios& i)
{ i.setf(ios::left, ios::adjustfield); return i; }

inline ios& right(ios& i)
{ i.setf(ios::right, ios::adjustfield); return i; }

inline ios& internal(ios& i)
{ i.setf(ios::internal, ios::adjustfield); return i; }


// stream manipulators std::fixed, std::scientific for floating point representation...

inline ios& fixed(ios& i)
{ i.setf(ios::fixed, ios::floatfield); return i; }

inline ios& scientific(ios& i)
{ i.setf(ios::scientific, ios::floatfield); return i; }


// GNU stream do not have support for flag boolalpha at all:-(

// instead of 
//	out << boolalpha << b;
// do
// 	out << as_alpha(b);
inline const char* boolalpha(bool b)
{ return b? "true" : "false"; }

// instead of 
//	in >> boolalpha >> b;
// do
// 	b = as_bool(in);
inline bool as_bool(istream& in)
{ string b; in >> b; return (b=="true") ? 1 : 0; }


} // namespace std



#endif
