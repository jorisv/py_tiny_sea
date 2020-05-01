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
// std
#include <string>

// pybind11
#include <pybind11/pybind11.h>

// tiny_sea
#include <tiny_sea/core/units.h>

namespace py = pybind11;
using namespace tiny_sea;

template<typename Unit>
void
stdUnit(const char* name, py::module& m)
{
    py::class_<Unit>(m, name)
      .def(py::init<>())
      .def(py::init<double>())
      .def("__repr__", [](const Unit& u) { return std::to_string(u.t); })
      .def_readwrite("t", &Unit::t);
}

void
initUnits(py::module& m)
{
    stdUnit<latitude_t>("latitude_t", m);
    stdUnit<longitude_t>("longitude_t", m);
    stdUnit<scale_t>("scale_t", m);
    stdUnit<meter_t>("meter_t", m);
    stdUnit<velocity_t>("velocity_t", m);
    stdUnit<radian_t>("radian_t", m);
    stdUnit<cost_t>("cost_t", m);
    stdUnit<tiny_sea::time_t>("time_t", m);
}
