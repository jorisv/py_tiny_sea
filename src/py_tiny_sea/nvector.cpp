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
#include <tiny_sea/core/n_vector.h>

namespace py = pybind11;
using namespace tiny_sea;

void
initNVector(py::module& m)
{
    py::class_<NVector>(m, "NVector")
      .def(py::init<>())
      .def(py::init<double, double, double>())
      .def_static("from_lat_lon", &NVector::fromLatLon)
      .def("to_lat_lon", &NVector::toLatLon)
      .def("distance", &NVector::distance)
      .def("destination", &NVector::destination);
}

