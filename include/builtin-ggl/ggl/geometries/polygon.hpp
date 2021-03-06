// Generic Geometry Library
//
// Copyright Barend Gehrels 1995-2009, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef GGL_GEOMETRIES_POLYGON_HPP
#define GGL_GEOMETRIES_POLYGON_HPP

#include <memory>
#include <vector>

#include <boost/concept/assert.hpp>

#include <ggl/core/exterior_ring.hpp>
#include <ggl/core/interior_rings.hpp>
#include <ggl/core/point_type.hpp>
#include <ggl/core/ring_type.hpp>
#include <ggl/core/concepts/point_concept.hpp>
#include <ggl/geometries/linear_ring.hpp>

namespace ggl
{

/*!
    \brief The \b polygon contains an outer ring and zero or more inner rings.
    \ingroup Geometry
    \tparam P point type
    \tparam PointList optional container type for points, for example std::vector, std::list, std::deque
    \tparam RingList optional container type for inner rings, for example std::vector, std::list, std::deque
    \tparam PointAlloc container-allocator-type
    \tparam RingAlloc container-allocator-type
    \note The container collecting the points in the rings can be different from the
    container collecting the inner rings. They all default to vector.
*/
template
<
    typename Point,
    template<typename, typename> class PointList = std::vector,
    template<typename, typename> class RingList = std::vector,
    template<typename> class PointAlloc = std::allocator,
    template<typename> class RingAlloc = std::allocator
>
class polygon
{
    BOOST_CONCEPT_ASSERT( (concept::Point<Point>) );

public:

    // Member types
    typedef Point point_type;
    typedef linear_ring<Point, PointList, PointAlloc> ring_type;
    typedef RingList<ring_type , RingAlloc<ring_type > > inner_container_type;

    inline ring_type const& outer() const { return m_outer; }
    inline inner_container_type const& inners() const { return m_inners; }

    inline ring_type& outer() { return m_outer; }
    inline inner_container_type & inners() { return m_inners; }

    /// Utility method, clears outer and inner rings
    inline void clear()
    {
        m_outer.clear();
        m_inners.clear();
    }

private:

    ring_type m_outer;
    inner_container_type m_inners;
};


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template
<
    typename Point,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct tag<polygon<Point, PointList, RingList, PointAlloc, RingAlloc> >
{
    typedef polygon_tag type;
};

template
<
    typename Point,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct ring_type<polygon<Point, PointList, RingList, PointAlloc, RingAlloc> >
{
    typedef typename polygon
        <
            Point, PointList, RingList, PointAlloc, RingAlloc
        >::ring_type type;
};

template
<
    typename Point,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct interior_type< polygon<Point, PointList, RingList, PointAlloc, RingAlloc> >
{
    typedef typename polygon
        <
            Point, PointList, RingList, PointAlloc, RingAlloc
        >::inner_container_type type;
};

template
<
    typename Point,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct exterior_ring< polygon<Point, PointList, RingList, PointAlloc, RingAlloc> >
{
    typedef polygon<Point, PointList, RingList, PointAlloc, RingAlloc> polygon_type;

    static inline typename polygon_type::ring_type& get(polygon_type& p)
    {
        return p.outer();
    }

    static inline typename polygon_type::ring_type const & get(polygon_type const& p)
    {
        return p.outer();
    }
};

template
<
    typename Point,
    template<typename, typename> class PointList,
    template<typename, typename> class RingList,
    template<typename> class PointAlloc,
    template<typename> class RingAlloc
>
struct interior_rings< polygon<Point, PointList, RingList, PointAlloc, RingAlloc> >
{
    typedef polygon<Point, PointList, RingList, PointAlloc, RingAlloc> polygon_type;

    static inline typename polygon_type::inner_container_type& get(
                    polygon_type& p)
    {
        return p.inners();
    }

    static inline typename polygon_type::inner_container_type const& get(
                    polygon_type const& p)
    {
        return p.inners();
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

} // namespace ggl

#endif // GGL_GEOMETRIES_POLYGON_HPP
