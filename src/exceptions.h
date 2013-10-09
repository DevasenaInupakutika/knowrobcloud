#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <boost/format.hpp>
#include <stdexcept>
#include <geometry_msgs/Point.h>

namespace occupancy_grid_merge
{

using boost::format;

/// Base class for exceptions from this package
struct GridUtilsException: public std::logic_error
{
  GridUtilsException (const format& f) : std::logic_error(f.str()) {};
  GridUtilsException (const char* str) : std::logic_error(str) {};
};


/// Exception for point off map
struct PointOutOfBoundsException: public GridUtilsException
{
  PointOutOfBoundsException (const geometry_msgs::Point& p) :
    GridUtilsException(format("Point %1%, %2% is off grid") % p.x % p.y) {}
};


/// Exception for Cell off map
struct CellOutOfBoundsException: public GridUtilsException
{
  CellOutOfBoundsException (const unsigned x, const unsigned y) :
    GridUtilsException(format("Cell %1%, %2% is off grid") % x % y) {}
};

// Exception when data field is not a vector of the right size
struct DataSizeException: public GridUtilsException
{
  DataSizeException (const unsigned expected, const unsigned actual) :
    GridUtilsException (format ("Expected data vector to have size %1%, "
                                "but it has size %2%") % expected % actual) {}
};      


} // namespace occupancy_merge_grid

#endif
