// Distributed under the MIT License.
// See LICENSE.txt for details.

/// \file
/// Defines tags related to domain quantities

#pragma once

#include <memory>
#include <unordered_map>

#include "DataStructures/DataBoxTag.hpp"
#include "DataStructures/Index.hpp"
#include "Domain/CoordinateMaps/CoordinateMap.hpp"
#include "Domain/Direction.hpp"
#include "Domain/Element.hpp"
#include "Domain/GridNormal.hpp"

namespace Tags {

/// \ingroup DataBoxTagsGroup
/// \ingroup ComputationalDomainGroup
/// The ::Element associated with the DataBox
template <size_t VolumeDim>
struct Element : db::DataBoxTag {
  static constexpr db::DataBoxString label = "Element";
  using type = ::Element<VolumeDim>;
};

/// \ingroup DataBoxTagsGroup
/// \ingroup ComputationalDomainGroup
/// The extents of DataVectors in the DataBox
template <size_t VolumeDim>
struct Extents : db::DataBoxTag {
  static constexpr db::DataBoxString label = "Extents";
  using type = ::Index<VolumeDim>;
};

/// \ingroup DataBoxTagsGroup
/// \ingroup ComputationalDomainGroup
/// The coordinate map from logical to grid coordinate
template <size_t VolumeDim>
struct ElementMap : db::DataBoxTag {
  static constexpr db::DataBoxString label = "ElementMap";
  using type = std::unique_ptr<::CoordinateMapBase<Frame::Logical, Frame::Grid,
                                                   VolumeDim>>;
};

namespace detail {
template <size_t VolumeDim>
auto make_unnormalized_grid_normals(
    const Index<VolumeDim>& extents,
    const std::unique_ptr<CoordinateMapBase<Frame::Logical, Frame::Grid,
                                            VolumeDim>>& map) noexcept {
  std::unordered_map<Direction<VolumeDim>,
                     tnsr::i<DataVector, VolumeDim, Frame::Grid>>
      result;
  for (const auto& d : Direction<VolumeDim>::all_directions()) {
    result.emplace(d, unnormalized_grid_normal(
                          extents.slice_away(d.dimension()), *map, d));
  }
  return result;
}
}  // namespace detail

/// \ingroup DataBoxTagsGroup
/// \ingroup ComputationalDomainGroup
/// The unnormalized grid normal one form on each side
template <size_t VolumeDim>
struct UnnormalizedGridNormal : db::ComputeItemTag {
  static constexpr db::DataBoxString label = "UnnormalizedGridNormal";
  static constexpr auto function =
      detail::make_unnormalized_grid_normals<VolumeDim>;
  using argument_tags = tmpl::list<Extents<VolumeDim>, ElementMap<VolumeDim>>;
};

}  // namespace Tags
