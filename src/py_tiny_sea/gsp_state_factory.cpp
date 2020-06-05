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
#include <tiny_sea/gsp/state_factory.h>

namespace py = pybind11;
using namespace tiny_sea;

void
initGSPStateFactory(py::module& m)
{
    py::class_<gsp::StateFactory>(m, "StateFactory")
      .def(py::init<tiny_sea::time_t,
                    meter_t,
                    tiny_sea::time_t,
                    meter_t,
                    const NVector&,
                    velocity_t>())
      .def(
        "build",
        py::overload_cast<const NVector&, tiny_sea::time_t, gsp::DiscretState>(
          &gsp::StateFactory::build, py::const_))
      .def("build",
           py::overload_cast<const NVector&, tiny_sea::time_t>(
             &gsp::StateFactory::build, py::const_))
      .def("distance_to_target", &gsp::StateFactory::distanceToTarget);
}

