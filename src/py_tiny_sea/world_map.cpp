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
#include <tiny_sea/core/world_map.h>

// py_tiny_sea
#include <py_tiny_sea/linear_grid.h>
#include <py_tiny_sea/linear_list.h>

namespace py = pybind11;
using namespace tiny_sea;

void
initWorldMap(py::module& m)
{
    py::class_<WorldMapData>(m, "WorldMapData")
      .def(py::init<>())
      .def(py::init<radian_t, velocity_t>())
      .def_readwrite("wind_bearing", &WorldMapData::windBearing)
      .def_readwrite("wind_velocity", &WorldMapData::windVelocity);

    stdLinearGridAndBuilder<latitude_t,
                            longitude_t,
                            WorldMapData,
                            WorldMapDataInterpolator>(
      "WorldMapGrid", "WorldMapGridBuilder", m);

    py::class_<WorldMap>(m, "WorldMap")
      .def(py::init<const WorldMapGrid&>())
      .def("worldGrid", &WorldMap::worldGrid);

    auto timeParent =
      stdLinearList<tiny_sea::time_t, WorldMap, NullInterpolator<WorldMap>>(
        "_TimeWorldMap", m);
    py::class_<TimeWorldMap>(m, "TimeWorldMap", timeParent);

    py::class_<TimeWorldMapBuilder>(m, "TimeWorldMapBuilder")
      .def(py::init<const LinearSpace<tiny_sea::time_t>&>())
      .def("add", &TimeWorldMapBuilder::add)
      .def("build", &TimeWorldMapBuilder::build);
}

