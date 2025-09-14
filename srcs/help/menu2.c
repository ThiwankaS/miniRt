/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:49:12 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/04 06:21:42 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Prints the key map for interacting with a plane.
 * Focuses on selecting/toggling and rotating the plane around x, y, and
 * z axes.
 */
void	help_plane(void)
{
	printf("\n");
	printf("------------------------- miniRt -----------------------------\n");
	printf("   key map help                                               \n");
	printf("   Press -                                                    \n");
	printf("   \tCtrl + L -> to select and toggle with light source       \n");
	printf("   \tCtrl + C -> to select and toggle with camera             \n");
	printf("   \tCtrl + N -> to select an object or select the next object\n");
	printf("   \tCtrl + S -> to rotate the plane                          \n");
	printf("   \tCtrl + E -> to de-select and exit interactive mode       \n");
	printf("   \tA        -> to rotate left along x-axis                  \n");
	printf("   \tD        -> to rotate right along x-axis                 \n");
	printf("   \tW        -> to rotate up along y-axis                    \n");
	printf("   \tS        -> to rotate down along y-axis                  \n");
	printf("   \tZ        -> to rotate forward along z-axis               \n");
	printf("   \tX        -> to rotate backward along z-axis              \n");
	printf("   \tH        -> to display the help menu                     \n");
	printf("   \tEsc      -> to exit the program                          \n");
	printf("--------------------------------------------------------------\n");
	printf("\n");
}

/**
 * Prints the key map for interacting with the camera.
 * Covers selection/toggle, movement, rotation, and zoom hints via x-axis
 * controls.
 */
void	help_camera(void)
{
	printf("\n");
	printf("------------------------- miniRt -----------------------------\n");
	printf("   key map help                                               \n");
	printf("   Press -                                                    \n");
	printf("   \tCtrl + L -> to select and toggle with light source       \n");
	printf("   \tCtrl + C -> to select and toggle with camera             \n");
	printf("   \tCtrl + N -> to select an object or select the next object\n");
	printf("   \tCtrl + M -> to move the camera along x,y,z axis          \n");
	printf("   \tCtrl + S -> to rotate the camera                         \n");
	printf("   \tCtrl + E -> to de-select and exit interactive mode       \n");
	printf("   \tA        -> to move/rotate left along x-axis/zoom out    \n");
	printf("   \tD        -> to move/rotate right along x-axis/zoom in    \n");
	printf("   \tW        -> to move/rotate up along y-axis               \n");
	printf("   \tS        -> to move/rotate down along y-axis             \n");
	printf("   \tZ        -> to move/rotate forward along z-axis          \n");
	printf("   \tX        -> to move/rotate backward along z-axis         \n");
	printf("   \tH        -> to display the help menu                     \n");
	printf("   \tEsc      -> to exit the program                          \n");
	printf("--------------------------------------------------------------\n");
	printf("\n");
}
