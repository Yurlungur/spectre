// Distributed under the MIT License.
// See LICENSE.txt for details.

///\file
/// Defines Functions for calculating spacetime tensors from 3+1 quantities

#pragma once

#include "DataStructures/Tensor/TypeAliases.hpp"

/*!
* \ingroup GeneralRelativityGroup
* \brief Computes the spacetime metric from the spatial metric, lapse, and
* shift.
* \details The spacetime metric \f$ \psi_{ab} \f$ is calculated as
* \f{align}{
*   \psi_{tt} &=& - N^2 + N^m N^n g_{mn} \\
*   \psi_{ti} &=& g_{mi} N^m  \\
*   \psi_{ij} &=& g_{ij}
* \f}
* where \f$ N, N^i\f$ and \f$ g_{ij}\f$ are the lapse, shift and spatial metric
* respectively
*/
template <size_t SpatialDim, typename Frame, typename DataType>
tnsr::aa<DataType, SpatialDim, Frame> compute_spacetime_metric(
    const Scalar<DataType>& lapse,
    const tnsr::I<DataType, SpatialDim, Frame>& shift,
    const tnsr::ii<DataType, SpatialDim, Frame>& spatial_metric) noexcept;

/*!
 * \ingroup GeneralRelativityGroup
 * \brief Compute inverse spacetime metric from inverse spatial metric, lapse
 * and shift
 *
 * \details The inverse spacetime metric \f$ \psi^{ab} \f$ is calculated as
 * \f{align}
 *    \psi^{tt} &=& -  1/N^2 \\
 *    \psi^{ti} &=& N^i / N^2 \\
 *    \psi^{ij} &=& g^{ij} - N^i N^j / N^2
 * \f}
 * where \f$ N, N^i\f$ and \f$ g^{ij}\f$ are the lapse, shift and inverse
 * spatial metric respectively
 */
template <size_t SpatialDim, typename Frame, typename DataType>
tnsr::AA<DataType, SpatialDim, Frame> compute_inverse_spacetime_metric(
    const Scalar<DataType>& lapse,
    const tnsr::I<DataType, SpatialDim, Frame>& shift,
    const tnsr::II<DataType, SpatialDim, Frame>&
        inverse_spatial_metric) noexcept;

/*!
 * \ingroup GeneralRelativityGroup
 * \brief Computes spacetime derivative of spacetime metric from spatial metric,
 * lapse, shift, and their space and time derivatives.
 *
 * \details Computes the derivatives as:
 * \f{align}
 *     \partial_\mu \psi_{tt} &=& - 2 N \partial_\mu N
 *                 + 2 g_{mn} N^m \partial_\mu N^n
 *                 + N^m N^n \partial_\mu g_{mn} \\
 *     \partial_\mu \psi_{ti} &=& g_{mi} \partial_\mu N^m
 *                 + N^m \partial_\mu g_{mi} \\
 *     \partial_\mu \psi_{ij} &=& \partial_\mu g_{ij}
 * \f}
 * where \f$ N, N^i, g \f$ are the lapse, shift, and spatial metric
 * respectively.
 */
template <size_t SpatialDim, typename Frame, typename DataType>
tnsr::abb<DataType, SpatialDim, Frame> compute_derivatives_of_spacetime_metric(
    const Scalar<DataType>& lapse, const Scalar<DataType>& dt_lapse,
    const tnsr::i<DataType, SpatialDim, Frame>& deriv_lapse,
    const tnsr::I<DataType, SpatialDim, Frame>& shift,
    const tnsr::I<DataType, SpatialDim, Frame>& dt_shift,
    const tnsr::iJ<DataType, SpatialDim, Frame>& deriv_shift,
    const tnsr::ii<DataType, SpatialDim, Frame>& spatial_metric,
    const tnsr::ii<DataType, SpatialDim, Frame>& dt_spatial_metric,
    const tnsr::ijj<DataType, SpatialDim, Frame>&
        deriv_spatial_metric) noexcept;

/*!
 * \ingroup GeneralRelativityGroup
 * \brief Computes the auxiliary variable \f$\phi_{iab}\f$ used by the
 * generalized harmonic formulation of Einstein's equations.
 *
 * \details If \f$ N, N^i\f$ and \f$ g_{ij} \f$ are the lapse, shift and spatial
 * metric respectively, then \f$\phi_{iab} \f$ is computed as
 *
 * \f{align}
 *     \phi_{ktt} &=& - 2 N \partial_k N
 *                 + 2 g_{mn} N^m \partial_k N^n
 *                 + N^m N^n \partial_k g_{mn} \\
 *     \phi_{kti} &=& g_{mi} \partial_k N^m
 *                 + N^m \partial_k g_{mi} \\
 *     \phi_{kij} &=& \partial_k g_{ij}
 * \f}
 */
template <size_t SpatialDim, typename Frame, typename DataType>
tnsr::iaa<DataType, SpatialDim, Frame> compute_phi(
    const Scalar<DataType>& lapse,
    const tnsr::i<DataType, SpatialDim, Frame>& deriv_lapse,
    const tnsr::I<DataType, SpatialDim, Frame>& shift,
    const tnsr::iJ<DataType, SpatialDim, Frame>& deriv_shift,
    const tnsr::ii<DataType, SpatialDim, Frame>& spatial_metric,
    const tnsr::ijj<DataType, SpatialDim, Frame>&
        deriv_spatial_metric) noexcept;

/*!
 * \ingroup GeneralRelativityGroup
 * \brief Computes the conjugate momentum \f$\Pi_{ab}\f$ of the spacetime metric
 * \f$ \psi_{ab} \f$.
 *
 * \details If \f$ N, N^i\f$ are the lapse and shift
 * respectively, and \f$ \phi_{iab} = \partial_i \psi_{ab} \f$ then
 * \f$\Pi_{\mu\nu} = -(1/N) ( \partial_t \psi_{\mu\nu}  -
 *      N^m \phi_{m\mu\nu}) \f$ where \f$ \partial_t \psi_{ab} \f$ is computed
 * as
 *
 * \f{align}
 *     \partial_t \psi_{tt} &=& - 2 N \partial_t N
 *                 + 2 g_{mn} N^m \partial_t N^n
 *                 + N^m N^n \partial_t g_{mn} \\
 *     \partial_t \psi_{ti} &=& g_{mi} \partial_t N^m
 *                 + N^m \partial_t g_{mi} \\
 *     \partial_t \psi_{ij} &=& \partial_t g_{ij}
 * \f}
 */
template <size_t SpatialDim, typename Frame, typename DataType>
tnsr::aa<DataType, SpatialDim, Frame> compute_pi(
    const Scalar<DataType>& lapse, const Scalar<DataType>& dt_lapse,
    const tnsr::I<DataType, SpatialDim, Frame>& shift,
    const tnsr::I<DataType, SpatialDim, Frame>& dt_shift,
    const tnsr::ii<DataType, SpatialDim, Frame>& spatial_metric,
    const tnsr::ii<DataType, SpatialDim, Frame>& dt_spatial_metric,
    const tnsr::iaa<DataType, SpatialDim, Frame>& phi) noexcept;

/*!
 * \brief Computes spacetime normal one-form from lapse.
 *
 * \details If \f$N\f$ is the lapse, then
 * \f{align} n_t &=& - N \\
 * n_i &=& 0 \f}
 * is computed.
 */
template <size_t SpatialDim, typename Frame, typename DataType>
tnsr::a<DataType, SpatialDim, Frame> compute_spacetime_normal_one_form(
    const Scalar<DataType>& lapse) noexcept;

/*!
 * \ingroup GeneralRelativityGroup
 * \brief  Computes spacetime normal vector from lapse and shift.
 * \details If $N, N^i$ are the lapse and shift respectively, then
 * \f{align} n^t &=& 1/N \\
 * n^i &=& -\frac{N^i}{N} \f}
 * is computed.
 */
template <size_t SpatialDim, typename Frame, typename DataType>
tnsr::A<DataType, SpatialDim, Frame> compute_spacetime_normal_vector(
    const Scalar<DataType>& lapse,
    const tnsr::I<DataType, SpatialDim, Frame>& shift) noexcept;
