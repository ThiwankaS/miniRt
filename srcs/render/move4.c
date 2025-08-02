/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 08:43:51 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/02 15:32:44 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * first checked any key_press event occured
 * if keydata.action != MLX_PRESS
 * ture means not a key press (return)
 * false means a key press so we continue
 * then check for the key combination
 *
 * Ctrl + N -> selecting object for the first time
 * Ctrl + L -> selecting the light source
 * Ctrl + C -> selecting the camera
 * Ctrl + E -> deselecting the object
 *
 * working with object
 * -------------------
 * if Ctrl + N presses setting the state.selected_object to store
 * the first object which is in the world.components linked list
 *
 * if(state.selected) if not NULL, and then pressing N will select
 * the next object in the linked list
 *
 * if the selected object is
 *
 * SPHERE
 * 		- can move
 * 		- can resize
 * PLANE
 * 		- can rotate
 * CYLINDER
 * 		- can move
 * 		- can resize
 * 		- can rotate
 *
 * working with light source
 * -------------------------
 *
 * once the light source is selected, light source can move
 * W - up along the y-axis
 * S - down along the y-axis
 * A - left along the x-axis
 * D - right along the x-axis
 * Z - forward along z-axis (+z is into the screen)
 * X - backward along the z-axis
 *
 * rotating or resizing a light source is meaningless as it is
 * considered as a point in the space
 *
 * working with camera
 * -------------------
 * once the camera is selected
 *
 * it can either rotate, move or zoom
 *
 * in move mood
 *
 * W - up along the y-axis
 * S - down along the y-axis
 * A - left along the x-axis
 * D - right along the x-axis
 * Z - forward along z-axis (+z is into the screen)
 * X - backward along the z-axis
 *
 * in rotate mood
 *
 * W - rotate clock wise on the y-axis
 * S - rotate anti- clock wise on the y-axis
 * A - rotate clock wise on the x-axis
 * D - rotate anti- clock wise on the x-axis
 * Z - rotate clock wise on the z-axis
 * X - rotate anti- clock wise on the z-axis
 *
 * in zoom mood
 *
 * A - zoomed out
 * D - zoomed in
 *
 * use below keys to choose mood
 *
 * Ctrl + M - to select moving mode
 * Ctrl + R - to select resizing mode
 * Ctrl + S - to select rotate mode
 * Ctrl + F - to select zooming mode
 *
 * Note
 * ------
 * if no object is selected or any mode not selected A,D,W,S,Z,X
 * keys will do nothing
*/
