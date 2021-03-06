// Distributed under the MIT License.
// See LICENSE.txt for details.

#pragma once

#include "DataStructures/Tensor/Tensor.hpp"

/*!
 * \ingroup GeneralRelativityGroup
 * \brief Raises or lowers the first index of a rank 3 tensor which is symmetric
 * in the last two indices.
 *
 * \details If \f$T_{abc}\f$ is a tensor with \f$T_{abc} = T_{acb}\f$ and the
 * indices \f$a,b,c,...\f$ can represent either spatial or spacetime indices,
 * then the tensor \f$ T^a_{bc} = g^{ad} T_{abc} \f$ is computed, where \f$
 * g^{ab}\f$ is the inverse metric, which is either a spatial or spacetime
 * metric. If a tensor \f$ S^a_{bc} \f$ is passed as an argument than the
 * corresponding tensor \f$ S_{abc} \f$ is calculated with respect to the metric
 * \f$g_{ab}\f$.
 */
template <typename DataType, typename Index0, typename Index1>
Tensor<DataType, Symmetry<2, 1, 1>,
       index_list<change_index_up_lo<Index0>, Index1, Index1>>
raise_or_lower_first_index(
    const Tensor<DataType, Symmetry<2, 1, 1>,
                 index_list<Index0, Index1, Index1>>& tensor,
    const Tensor<DataType, Symmetry<1, 1>,
                 index_list<change_index_up_lo<Index0>,
                            change_index_up_lo<Index0>>>& metric) noexcept;

/*!
 * \ingroup GeneralRelativityGroup
 * \brief Computes trace of a rank 3 tensor, which is symmetric in its last two
 * indices with all indices lower.
 *
 * \details If \f$ T_{abc} \f$ is a tensor such that \f$T_{abc} = T_{acb} \f$
 * then \f$ T_a = g^{bc}T_{abc} \f$ is computed, where \f$ g^{bc} \f$ is the
 * inverse metric. The indices \f$ a,b,c...\f$ can be spatial or spacetime.
 */
template <size_t Dim, typename Frame, IndexType TypeOfIndex, typename DataType>
tnsr::a<DataType, Dim, Frame, TypeOfIndex> trace_last_indices(
    const tnsr::abb<DataType, Dim, Frame, TypeOfIndex>& tensor,
    const tnsr::AA<DataType, Dim, Frame, TypeOfIndex>& upper_metric);
