/** @file psh/expansion.h - @brief expanding shell parameters, substitutions,
 * and aliases */
/*
    Copyright 2020 Zhang Maiyun

    This file is part of Psh, P shell.

    Psh is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Psh is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _PSH_EXPANSION_H
#define _PSH_EXPANSION_H

#include "psh.h"

/** Parameter, command, and arithmetic expansion.
 *
 * @param state Psh internal state.
 * @param oldstring The line to be expanded.
 * @return The line after expansion, need to be free()d.
 */
char *psh_expand_parameter(psh_state *state, const char *oldstring);

/** Recursively expand aliases.
 *
 * @param state Psh internal state.
 * @param oldbuffer The line to be expanded.
 * @return The line after expansion, need to be free()d.
 */
char *expand_alias(psh_state *state, const char *oldbuffer);

#endif