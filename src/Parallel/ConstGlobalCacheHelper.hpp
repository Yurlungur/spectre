// Distributed under the MIT License.
// See LICENSE.txt for details.

// This stuff needs to be in a separate file so it can be used in
// ConstGlobalCache.ci

#pragma once

#include "Utilities/TMPL.hpp"

namespace Parallel {
namespace ConstGlobalCache_detail {
template <typename Tentacle>
using tentacle_cache_tags = typename Tentacle::const_global_cache_tag_list;
template <typename Metavariables>
using make_tag_list = tmpl::remove_duplicates<
    tmpl::flatten<tmpl::transform<typename Metavariables::component_list,
                                  tmpl::bind<tentacle_cache_tags, tmpl::_1>>>>;
}  // namespace ConstGlobalCache_detail
}  // namespace Parallel
