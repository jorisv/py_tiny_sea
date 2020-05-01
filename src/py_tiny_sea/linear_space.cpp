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
#include <tiny_sea/core/linear_space.h>

namespace py = pybind11;
using namespace tiny_sea;

template<typename Unit>
void
stdLinearSpace(const char* name, py::module& m)
{
    using linear_space = LinearSpace<Unit>;
    py::class_<linear_space>(m, name)
      .def(py::init(&safeMakeLinearSpace<Unit>))
      .def_static("from_bound", &safeMakeLinearSpaceFromBound<Unit>)
      .def("start", &linear_space::start)
      .def("delta", &linear_space::delta)
      .def("stop", &linear_space::stop)
      .def("nr_points", &linear_space::nrPoints)
      .def("value", &linear_space::value)
      .def("index", &linear_space::safeIndex)
      .def("interpolation_weight", &linear_space::safeInterpolationWeight)
      .def("inside", &linear_space::inside);
}

void
initLinearSpace(py::module& m)
{
    py::class_<LinearSpaceInterpolationResult>(m,
                                               "LinearSpaceInterpolationResult")
      .def(py::init<>())
      .def(py::init<scale_t, std::size_t>())
      .def_readwrite("percent", &LinearSpaceInterpolationResult::percent)
      .def_readwrite("index", &LinearSpaceInterpolationResult::index);

    stdLinearSpace<latitude_t>("LatitudeLinearSpace", m);
    stdLinearSpace<longitude_t>("LongitudeLinearSpace", m);
    stdLinearSpace<scale_t>("ScaleLinearSpace", m);
    stdLinearSpace<meter_t>("MeterLinearSpace", m);
    stdLinearSpace<velocity_t>("VelocityLinearSpace", m);
    stdLinearSpace<radian_t>("RadianLinearSpace", m);
    stdLinearSpace<tiny_sea::time_t>("TimeLinearSpace", m);
}
