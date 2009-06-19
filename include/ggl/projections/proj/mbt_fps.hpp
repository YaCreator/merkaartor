#ifndef GGL_PROJECTIONS_MBT_FPS_HPP
#define GGL_PROJECTIONS_MBT_FPS_HPP

// Generic Geometry Library - projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright Barend Gehrels (1995-2009), Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande (2008-2009)
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Geometry Library by Barend Gehrels (Geodan, Amsterdam)

// Original copyright notice:
 
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/math/special_functions/hypot.hpp>

#include <ggl/projections/impl/base_static.hpp>
#include <ggl/projections/impl/base_dynamic.hpp>
#include <ggl/projections/impl/projects.hpp>
#include <ggl/projections/impl/factory_entry.hpp>

namespace ggl { namespace projection
{
    #ifndef DOXYGEN_NO_IMPL
    namespace impl { namespace mbt_fps{ 
            static const int MAX_ITER = 10;
            static const double LOOP_TOL = 1e-7;
            static const double C1 = 0.45503;
            static const double C2 = 1.36509;
            static const double C3 = 1.41546;
            static const double C_x = 0.22248;
            static const double C_y = 1.44492;
            static const double C1_2 = 0.33333333333333333333333333;


            // template class, using CRTP to implement forward/inverse
            template <typename Geographic, typename Cartesian, typename Parameters>
            struct base_mbt_fps_spheroid : public base_t_fi<base_mbt_fps_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>
            {

                 typedef double geographic_type;
                 typedef double cartesian_type;


                inline base_mbt_fps_spheroid(const Parameters& par)
                    : base_t_fi<base_mbt_fps_spheroid<Geographic, Cartesian, Parameters>,
                     Geographic, Cartesian, Parameters>(*this, par) {}

                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                	double k, V, t;
                	int i;
                
                	k = C3 * sin(lp_lat);
                	for (i = MAX_ITER; i ; --i) {
                		t = lp_lat / C2;
                		lp_lat -= V = (C1 * sin(t) + sin(lp_lat) - k) /
                			(C1_2 * cos(t) + cos(lp_lat));
                		if (fabs(V) < LOOP_TOL)
                			break;
                	}
                	t = lp_lat / C2;
                	xy_x = C_x * lp_lon * (1. + 3. * cos(lp_lat)/cos(t) );
                	xy_y = C_y * sin(t);
                }

                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                	double t;
                
                	lp_lat = C2 * (t = aasin(xy_y / C_y));
                	lp_lon = xy_x / (C_x * (1. + 3. * cos(lp_lat)/cos(t)));
                	lp_lat = aasin((C1 * sin(t) + sin(lp_lat)) / C3);
                }
            };

            // McBryde-Thomas Flat-Pole Sine (No. 2)
            template <typename Parameters>
            void setup_mbt_fps(Parameters& par)
            {
                par.es = 0;
                // par.inv = s_inverse;
                // par.fwd = s_forward;
            }

        }} // namespace impl::mbt_fps
    #endif // doxygen 

    /*!
        \brief McBryde-Thomas Flat-Pole Sine (No. 2) projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Cylindrical
         - Spheroid
        \par Example
        \image html ex_mbt_fps.gif
    */
    template <typename Geographic, typename Cartesian, typename Parameters = parameters>
    struct mbt_fps_spheroid : public impl::mbt_fps::base_mbt_fps_spheroid<Geographic, Cartesian, Parameters>
    {
        inline mbt_fps_spheroid(const Parameters& par) : impl::mbt_fps::base_mbt_fps_spheroid<Geographic, Cartesian, Parameters>(par)
        {
            impl::mbt_fps::setup_mbt_fps(this->m_par);
        }
    };

    #ifndef DOXYGEN_NO_IMPL
    namespace impl
    {

        // Factory entry(s)
        template <typename Geographic, typename Cartesian, typename Parameters>
        class mbt_fps_entry : public impl::factory_entry<Geographic, Cartesian, Parameters>
        {
            public :
                virtual projection<Geographic, Cartesian>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<mbt_fps_spheroid<Geographic, Cartesian, Parameters>, Geographic, Cartesian, Parameters>(par);
                }
        };

        template <typename Geographic, typename Cartesian, typename Parameters>
        inline void mbt_fps_init(impl::base_factory<Geographic, Cartesian, Parameters>& factory)
        {
            factory.add_to_factory("mbt_fps", new mbt_fps_entry<Geographic, Cartesian, Parameters>);
        }

    } // namespace impl 
    #endif // doxygen

}} // namespace ggl::projection

#endif // GGL_PROJECTIONS_MBT_FPS_HPP

