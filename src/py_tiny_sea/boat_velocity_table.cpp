// PyTinySea: TinySea python binding
// Copyright (C) 2019 Joris Vaillant
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// includes
// pybind11
#include <pybind11/pybind11.h>

// tiny_sea
#include <tiny_sea/core/boat_velocity_table.h>

// py_tiny_sea
#include <py_tiny_sea/linear_list.h>

namespace py = pybind11;
using namespace tiny_sea;

void
initBoatVelocityTable(py::module& m)
{
    stdLinearListAndBuilder<velocity_t,
                            velocity_t,
                            UnitsInterpolator<velocity_t>>(
      "WindToBoatVelocity", "WindToBoatVelocityBuilder", m);

    py::class_<BoatVelocity>(m, "BoatVelocity")
      .def(py::init<radian_t, BoatVelocity::WindToBoatVelocity>())
      .def_readwrite("relative_wind_bearing",
                     &BoatVelocity::relativeWindBearing)
      .def_readwrite("wind_velocity_to_boat_velocity",
                     &BoatVelocity::windVelocityToBoatVelocity);

    py::class_<BoatVelocityTable>(m, "BoatVelocityTable")
      .def(py::init<const std::vector<BoatVelocity>&, velocity_t>())
      .def("velocity_table", &BoatVelocityTable::velocityTable)
      .def("max_velocity", &BoatVelocityTable::maxVelocity);

    py::class_<BoatVelocityTableBuilder>(m, "BoatVelocityTableBuilder")
      .def(py::init<const LinearSpace<velocity_t>&>())
      .def("add", &BoatVelocityTableBuilder::add)
      .def("add_symetric", &BoatVelocityTableBuilder::addSymetric)
      .def("build", &BoatVelocityTableBuilder::build);
}
