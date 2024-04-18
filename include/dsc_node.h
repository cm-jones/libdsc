/*
 * This file is part of libdsc.
 *
 * libdsc is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * libdsc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libdsc. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __DSC_NODE_H__
#define __DSC_NODE_H__

/**
 * @struct dsc_node_t
 * @brief Represents a node in the list.
 *
 * @param value The value stored in the node.
 * @param next Pointer to the next node in the list.
 */
struct dsc_node_t {
    int value;
    struct dsc_node_t *next;
};

#endif /* __DSC_NODE_H__ */
