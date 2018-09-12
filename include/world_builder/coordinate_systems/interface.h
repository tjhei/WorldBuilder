/*
  Copyright (C) 2018 by the authors of the World Builder code.

  This file is part of the World Builder.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _world_builder_coordinate_systems_interface_h
#define _world_builder_coordinate_systems_interface_h

#include <boost/property_tree/ptree.hpp>

#include <world_builder/coordinate_system.h>
#include <world_builder/parameters.h>
#include <world_builder/utilities.h>
#include <world_builder/world.h>


using boost::property_tree::ptree;

namespace WorldBuilder
{
  namespace CoordinateSystems
  {

    class Interface
    {
      public:
        /**
         * constructor
         */
        Interface();

        /**
         * Destructor
         */
        virtual
        ~Interface();

        /**
         * Read in the world builder file, and does parsing and preparation for the model to start.
         */
        // Todo: might have to rename this function, or split it up.
        virtual
        void decare_entries() = 0;

        /**
         * Returns what the natural coordinate system for this geometry model is.
         */
        virtual
        CoordinateSystem natural_coordinate_system() const = 0;

        /**
         * Returns what method should be used to go down with an angle into
         * the domain.
         * \sa DepthMethod
         */
        virtual
        DepthMethod depth_method() const = 0;

        /**
         * Takes the Cartesian points (x,z or x,y,z) and returns standardized
         * coordinates which are most 'natural' to the geometry model. For a box
         * this will  be (x,z) in 2d or (x,y,z) in 3d, and for a spheroid geometry
         * model it  will be (radius, longitude) in 2d and (radius, longitude,
         * latitude) in 3d.
         */
        virtual
        std::array<double,3> cartesian_to_natural_coordinates(const std::array<double,3> &position) const = 0;

        /**
         * Undoes the action of cartesian_to_natural_coordinates, and turns the
         * coordinate system which is most 'natural' to the geometry model into
         * Cartesian coordinates.
         */
        virtual
        std::array<double,3> natural_to_cartesian_coordinates(const std::array<double,3> &position) const = 0;

        /**
         * Computes the distance between two points which are on the same depth.
         * The input is two 3d points at that depth.
         */
        virtual
        double distance_between_points_at_same_depth(const Point<3> &point_1, const Point<3> &point_2) const = 0;

      protected:
        /**
         * A pointer to the world class to retrieve variables.
         */
        WorldBuilder::World *world;

    };


    /**
     * A factory function for creating coordinate systems.
     */
    std::unique_ptr<Interface>
    create_coordinate_system(const std::string name, World *world);

  }
}

#endif
