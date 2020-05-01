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
#include <tiny_sea/core/linear_grid.h>

namespace py = pybind11;
using namespace tiny_sea;

template<typename XUnit, typename YUnit, typename Data, typename Interp>
inline void
stdLinearGrid(const char* name, py::module& m)
{
    using linear_grid = LinearGrid<XUnit, YUnit, Data, Interp>;
    py::class_<linear_grid>(m, name)
      .def("__getitem__",
           [](const linear_grid& g, std::tuple<XUnit, YUnit> indexes) {
               return g.safeAt(std::get<0>(indexes), std::get<1>(indexes));
           })
      .def(
        "__getitem__",
        [](const linear_grid& g, std::tuple<std::size_t, std::size_t> indexes) {
            return g.safeAt(std::get<0>(indexes), std::get<1>(indexes));
        })
      .def("interpolated", &linear_grid::safeInterpolated)
      .def("x_space", &linear_grid::xSpace)
      .def("y_space", &linear_grid::ySpace)
      .def("values", &linear_grid::values);
}

template<typename XUnit, typename YUnit, typename Data, typename Interp>
inline void
stdLinearGridBuilder(const char* name, py::module& m)
{
    using x_linear_space = LinearSpace<XUnit>;
    using y_linear_space = LinearSpace<YUnit>;
    using linear_grid_builder = LinearGridBuilder<XUnit, YUnit, Data, Interp>;
    py::class_<linear_grid_builder>(m, name)
      .def(py::init<x_linear_space, y_linear_space>())
      .def("__getitem__",
           [](const linear_grid_builder& b,
              std::tuple<std::size_t, std::size_t> indexes) {
               return b.safeAt(std::get<0>(indexes), std::get<1>(indexes));
           })
      .def("__setitem__",
           [](linear_grid_builder& b,
              std::tuple<std::size_t, std::size_t> indexes,
              const typename linear_grid_builder::value_type& v) {
               b.safeAt(std::get<0>(indexes), std::get<1>(indexes)) = v;
           })
      .def("build", &linear_grid_builder::build);
}

template<typename XUnit, typename YUnit, typename Data, typename Interp>
inline void
stdLinearGridAndBuilder(const char* gridName,
                        const char* builderName,
                        py::module& m)
{
    stdLinearGrid<XUnit, YUnit, Data, Interp>(gridName, m);
    stdLinearGridBuilder<XUnit, YUnit, Data, Interp>(builderName, m);
}

