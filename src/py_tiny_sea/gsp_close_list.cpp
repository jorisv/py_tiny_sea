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
#include <pybind11/stl.h>

// tiny_sea
#include <tiny_sea/gsp/close_list.h>

namespace py = pybind11;
using namespace tiny_sea;

void
initGSPCloseList(py::module& m)
{
    py::class_<gsp::CloseList>(m, "CloseList")
      .def(py::init<>())
      .def("contains", &gsp::CloseList::contains)
      .def("insert", &gsp::CloseList::insert)
      .def("store", &gsp::CloseList::store);

    py::class_<gsp::CloseList::Iterator>(m, "CloseListIterator");
}

