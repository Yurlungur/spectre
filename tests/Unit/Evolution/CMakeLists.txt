# Distributed under the MIT License.
# See LICENSE.txt for details.

add_subdirectory(Systems)

set(SPECTRE_TESTS "${SPECTRE_TESTS};${EVOLUTION_TESTS}" PARENT_SCOPE)
