// Copyright 2015-2019 Autoware Foundation. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Authors: Simon Thompson, Ryohsuke Mitsudome

#ifndef LANELET2_EXTENSION__VISUALIZATION__VISUALIZATION_HPP_
#define LANELET2_EXTENSION__VISUALIZATION__VISUALIZATION_HPP_

// NOLINTBEGIN(readability-identifier-naming)

#include "lanelet2_extension/regulatory_elements/autoware_traffic_light.hpp"
#include "lanelet2_extension/regulatory_elements/no_parking_area.hpp"
#include "lanelet2_extension/regulatory_elements/no_stopping_area.hpp"
#include "lanelet2_extension/utility/query.hpp"

#include <rclcpp/rclcpp.hpp>

#include <geometry_msgs/msg/polygon.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <lanelet2_core/LaneletMap.h>
#include <lanelet2_core/primitives/Lanelet.h>

#include <string>
#include <vector>

namespace lanelet::visualization
{
/**
 * [lanelet2Triangle converts lanelet into vector of triangles. Used for
 * triangulation]
 * @param ll        [input lanelet]
 * @param triangles [array of polygon message, each containing 3 vertices]
 */
void lanelet2Triangle(
  const lanelet::ConstLanelet & ll, std::vector<geometry_msgs::msg::Polygon> * triangles);

/**
 * [polygon2Triangle converts polygon into vector of triangles]
 * @param polygon   [input polygon]
 * @param triangles [array of polygon message, each containing 3 vertices]
 */
void polygon2Triangle(
  const geometry_msgs::msg::Polygon & polygon,
  std::vector<geometry_msgs::msg::Polygon> * triangles);

/**
 * [lanelet2Polygon converts lanelet into a polygon]
 * @param ll      [input lanelet]
 * @param polygon [polygon message containing shape of the input lanelet.]
 */
void lanelet2Polygon(const lanelet::ConstLanelet & ll, geometry_msgs::msg::Polygon * polygon);

/**
 * [initLineStringMarker initializes marker to visualize shape of linestring]
 * @param marker     [output marker message]
 * @param frame_id   [frame id of the marker]
 * @param ns         [namespace of the marker]
 * @param c          [color of the marker]
 */
void initLineStringMarker(
  visualization_msgs::msg::Marker * marker, const std::string & frame_id, const std::string & ns,
  const std_msgs::msg::ColorRGBA & c);

/**
 * [pushLineStringMarker pushes marker vertices to visualize shape of linestring]
 * @param marker     [output marker message]
 * @param ls         [input linestring]
 * @param c          [color of the marker]
 * @param lss        [thickness of the marker]
 */
void pushLineStringMarker(
  visualization_msgs::msg::Marker * marker, const lanelet::ConstLineString3d & ls,
  const std_msgs::msg::ColorRGBA & c, const float lss = 0.1);

/**
 * [initArrowsMarker initializes marker to visualize arrows with TRIANGLE_LIST]
 * @param marker     [output marker message]
 * @param frame_id   [frame id of the marker]
 * @param ns         [namespace of the marker]
 * @param c          [color of the marker]
 */
void initArrowsMarker(
  visualization_msgs::msg::Marker * marker, const std::string & frame_id, const std::string & ns,
  const std_msgs::msg::ColorRGBA & c);

/**
 * [pushArrowsMarker pushes marker to visualize arrows with TRIANGLE_LIST]
 * @param marker     [output marker message]
 * @param ls         [input linestring]
 * @param c          [color of the marker]
 */
void pushArrowsMarker(
  visualization_msgs::msg::Marker * marker, const lanelet::ConstLineString3d & ls,
  const std_msgs::msg::ColorRGBA & c);

/**
 * [initTrafficLightTriangleMarker initializes marker to visualize shape of traffic
 * lights]
 * @param marker   [created marker]
 * @param ns       [namespace of the marker]
 * @param duration [lifetime of the marker]
 */
void initTrafficLightTriangleMarker(
  visualization_msgs::msg::Marker * marker, const std::string & ns,
  const rclcpp::Duration & duration = rclcpp::Duration(0, 0));

/**
 * [pushTrafficLightTriangleMarker pushes marker vertices to visualize shape of traffic
 * lights]
 * @param marker   [created marker]
 * @param ls       [linestring that represents traffic light shape]
 * @param cl       [color of the marker]
 * @param scale    [scale of the marker]
 */
void pushTrafficLightTriangleMarker(
  visualization_msgs::msg::Marker * marker, const lanelet::ConstLineString3d & ls,
  const std_msgs::msg::ColorRGBA & cl, const double scale = 1.0);

/**
 * [laneletsBoundaryAsMarkerArray create marker array to visualize shape of
 * boundaries of lanelets]
 * @param  lanelets       [input lanelets]
 * @param  c              [color of the boundary]
 * @param  viz_centerline [flag to visualize centerline or not]
 * @return                [created marker array]
 */
visualization_msgs::msg::MarkerArray laneletsBoundaryAsMarkerArray(
  const lanelet::ConstLanelets & lanelets, const std_msgs::msg::ColorRGBA & c,
  const bool viz_centerline, const std::string & additional_namespace = "");
/**
 * [laneletsAsTriangleMarkerArray create marker array to visualize shape of the
 * lanelet]
 * @param  ns       [namespace of the marker]
 * @param  lanelets [input lanelets]
 * @param  c        [color of the marker]
 * @return          [created marker]
 */
visualization_msgs::msg::MarkerArray laneletsAsTriangleMarkerArray(
  const std::string & ns, const lanelet::ConstLanelets & lanelets,
  const std_msgs::msg::ColorRGBA & c);

/**
 * [laneletDirectionAsMarkerArray create marker array to visualize direction of
 * the lanelet]
 * @param  lanelets [input lanelets]
 * @return          [created marker array]
 */
visualization_msgs::msg::MarkerArray laneletDirectionAsMarkerArray(
  const lanelet::ConstLanelets & lanelets, const std::string & additional_namespace = "");

/**
 * [lineStringsAsMarkerArray creates marker array to visualize shape of
 * linestrings]
 * @param  line_strings [input linestrings]
 * @param  name_space   [namespace of the marker]
 * @param  c            [color of the marker]
 * @param  lss          [thickness of the marker]
 * @return              [created marker array]
 */
visualization_msgs::msg::MarkerArray lineStringsAsMarkerArray(
  const std::vector<lanelet::ConstLineString3d> & line_strings, const std::string & name_space,
  const std_msgs::msg::ColorRGBA & c, const float lss);

/**
 * [autowareTrafficLightsAsMarkerArray creates marker array to visualize traffic
 * lights]
 * @param  tl_reg_elems [traffic light regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 * @return              [created marker array]
 */
visualization_msgs::msg::MarkerArray autowareTrafficLightsAsMarkerArray(
  const std::vector<lanelet::AutowareTrafficLightConstPtr> & tl_reg_elems,
  const std_msgs::msg::ColorRGBA & c, const rclcpp::Duration & duration = rclcpp::Duration(0, 0),
  const double scale = 1.0);

/**
 * [generateTrafficLightRegulatoryElementIdMaker creates marker array to visualize traffic
 * light regulatory element ids]
 * @param lanelets      [lanelets]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 * @return              [created marker array]
 */
visualization_msgs::msg::MarkerArray generateTrafficLightRegulatoryElementIdMaker(
  const lanelet::ConstLanelets & lanelets, const std_msgs::msg::ColorRGBA & c,
  const rclcpp::Duration & duration = rclcpp::Duration(0, 0), const double scale = 0.5);

/**
 * [generateTrafficLightIdMarkerArray creates marker array to visualize traffic
 * light ids]
 * @param  tl_reg_elems [traffic light regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 * @return              [created marker array]
 */
visualization_msgs::msg::MarkerArray generateTrafficLightIdMaker(
  const std::vector<lanelet::AutowareTrafficLightConstPtr> & tl_reg_elems,
  const std_msgs::msg::ColorRGBA & c, const rclcpp::Duration & duration = rclcpp::Duration(0, 0),
  const double scale = 0.5);

/**
 * [trafficLightsAsTriangleMarkerArray creates marker array to visualize shape
 * of traffic lights]
 * @param  tl_reg_elems [traffic light regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 * @return              [created marker array]
 */
visualization_msgs::msg::MarkerArray trafficLightsAsTriangleMarkerArray(
  const std::vector<lanelet::TrafficLightConstPtr> & tl_reg_elems,
  const std_msgs::msg::ColorRGBA & c, const rclcpp::Duration & duration = rclcpp::Duration(0, 0),
  const double scale = 1.0);

/**
 * [detectionAreasAsMarkerArray creates marker array to visualize detection areas]
 * @param  da_reg_elems [detection area regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 */
visualization_msgs::msg::MarkerArray detectionAreasAsMarkerArray(
  const std::vector<lanelet::DetectionAreaConstPtr> & da_reg_elems,
  const std_msgs::msg::ColorRGBA & c, const rclcpp::Duration & duration = rclcpp::Duration(0, 0));

/**
 * [noParkingAreasAsMarkerArray creates marker array to visualize detection areas]
 * @param  no_reg_elems [no parking area regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 */
visualization_msgs::msg::MarkerArray noParkingAreasAsMarkerArray(
  const std::vector<lanelet::NoParkingAreaConstPtr> & no_reg_elems,
  const std_msgs::msg::ColorRGBA & c, const rclcpp::Duration & duration = rclcpp::Duration(0, 0));

/**
 * [noStoppingAreasAsMarkerArray creates marker array to visualize detection areas]
 * @param  no_reg_elems [mp stopping area regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 */
visualization_msgs::msg::MarkerArray noStoppingAreasAsMarkerArray(
  const std::vector<lanelet::NoStoppingAreaConstPtr> & no_reg_elems,
  const std_msgs::msg::ColorRGBA & c, const rclcpp::Duration & duration = rclcpp::Duration(0, 0));

/**
 * [speedBumpsAsMarkerArray creates marker array to visualize speed bumps]
 * @param  sb_reg_elems [speed bump regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 */
visualization_msgs::msg::MarkerArray speedBumpsAsMarkerArray(
  const std::vector<lanelet::SpeedBumpConstPtr> & sb_reg_elems, const std_msgs::msg::ColorRGBA & c,
  const rclcpp::Duration & duration = rclcpp::Duration(0, 0));

/**
 * [crosswalkAreasAsMarkerArray creates marker array to visualize crosswalk regulatory element]
 * @param  sb_reg_elems [crosswalk regulatory elements]
 * @param  c            [color of the marker]
 * @param  duration     [lifetime of the marker]
 */
visualization_msgs::msg::MarkerArray crosswalkAreasAsMarkerArray(
  const std::vector<lanelet::CrosswalkConstPtr> & cw_reg_elems, const std_msgs::msg::ColorRGBA & c,
  const rclcpp::Duration & duration = rclcpp::Duration(0, 0));

/**
 * [pedestrianMarkingsAsMarkerArray creates marker array to visualize pedestrian markings]
 * @param  pedestrian_markings [pedestrian marking polygon]
 * @param  c            [color of the marker]
 */
visualization_msgs::msg::MarkerArray pedestrianMarkingsAsMarkerArray(
  const lanelet::ConstLineStrings3d & pedestrian_markings, const std_msgs::msg::ColorRGBA & c);

/**
 * [parkingLotsAsMarkerArray creates marker array to visualize parking lots]
 * @param  parking_lots [parking lot polygon]
 * @param  c            [color of the marker]
 */
visualization_msgs::msg::MarkerArray parkingLotsAsMarkerArray(
  const lanelet::ConstPolygons3d & parking_lots, const std_msgs::msg::ColorRGBA & c);

/**
 * [parkingSpacesAsMarkerArray creates marker array to visualize parking spaces]
 * @param  parking_spaces [parking space line string]
 * @param  c            [color of the marker]
 */
visualization_msgs::msg::MarkerArray parkingSpacesAsMarkerArray(
  const lanelet::ConstLineStrings3d & parking_spaces, const std_msgs::msg::ColorRGBA & c);

/**
 * [detectionAreasAsMarkerArray creates marker array to visualize lanelet_id]
 * @param road_lanelets [road lanelets]
 * @param c [color of the marker]
 * @param duration [lifetime of the marker]
 * @param ns [namespace of the marker]
 * @param scale [scale of the marker]
 * @return visualization_msgs::msg::MarkerArray
 */
visualization_msgs::msg::MarkerArray generateLaneletIdMarker(
  const lanelet::ConstLanelets & road_lanelets, const std_msgs::msg::ColorRGBA & c,
  const std::string & ns = "lanelet_id", const double scale = 0.5);

visualization_msgs::msg::MarkerArray obstaclePolygonsAsMarkerArray(
  const lanelet::ConstPolygons3d & obstacle_polygons, const std_msgs::msg::ColorRGBA & c);

/**
 * [intersectionAreaAsMarkerArray creates marker array to visualize intersection area]
 * @param  intersection_areas [intersection area polygon]
 * @param  c                  [color of the marker]
 */
visualization_msgs::msg::MarkerArray intersectionAreaAsMarkerArray(
  const lanelet::ConstPolygons3d & intersection_areas, const std_msgs::msg::ColorRGBA & c);

/**
 * [noObstacleSegmentationAreaAsMarkerArray creates marker array to visualize no obstacle
 * segmentation area]
 * @param  no_obstacle_segmentation_area [no obstacle segmentation area polygon]
 * @param  c                             [color of the marker]
 */
visualization_msgs::msg::MarkerArray noObstacleSegmentationAreaAsMarkerArray(
  const lanelet::ConstPolygons3d & no_obstacle_segmentation_area,
  const std_msgs::msg::ColorRGBA & c);

/**
 * [noObstacleSegmentationAreaForRunOutAsMarkerArray creates marker array to visualize no obstacle
 * segmentation area for run out]
 * @param  no_obstacle_segmentation_area_for_run_out [no obstacle segmentation area for run out
 * polygon]
 * @param  c                                         [color of the marker]
 */
visualization_msgs::msg::MarkerArray noObstacleSegmentationAreaForRunOutAsMarkerArray(
  const lanelet::ConstPolygons3d & no_obstacle_segmentation_area_for_run_out,
  const std_msgs::msg::ColorRGBA & c);

/**
 * [hatchedRoadMarkingsAreaAsMarkerArray creates marker array to visualize hatched road markings
 * area]
 * @param  hatched_road_markings_area [hatched road markings area polygon]
 * @param  area_color                 [color of the area marker]
 * @param  line_color                 [color of the line marker]
 */
visualization_msgs::msg::MarkerArray hatchedRoadMarkingsAreaAsMarkerArray(
  const lanelet::ConstPolygons3d & hatched_road_markings_area,
  const std_msgs::msg::ColorRGBA & area_color, const std_msgs::msg::ColorRGBA & line_color);

}  // namespace lanelet::visualization

// NOLINTEND(readability-identifier-naming)

#endif  // LANELET2_EXTENSION__VISUALIZATION__VISUALIZATION_HPP_
