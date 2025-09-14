/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 08:56:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/03 07:31:57 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Prints the main miniRt help banner and global key bindings.
 * Purely informational: writes a formatted overview to stdout.
 */
void	help_menu(void)
{
	printf("\n");
	printf("------------------------- miniRt -----------------------------\n");
	printf("   miniRt is a simple raytracing program build with C and Joy!\n");
	printf("   use below keys\\key comibinations to interact, enjoy...    \n");
	printf("   Press -                                                    \n");
	printf("   \tCtrl + L -> to select and toggle with light source       \n");
	printf("   \tCtrl + C -> to select and toggle with camera             \n");
	printf("   \tCtrl + N -> to select an object or select the next object\n");
	printf("   \tCtrl + E -> to de-select and exit interactive mode       \n");
	printf("   \tH        -> to display the help menu                     \n");
	printf("   \tEsc      -> to exit the program                          \n");
	printf("--------------------------------------------------------------\n");
	printf("\n");
}

/**
 * Prints the key map for interacting with the light source.
 * Lists selection/toggle shortcuts and movement along x, y, and z axes.
 */
void	help_light(void)
{
	printf("\n");
	printf("------------------------- miniRt -----------------------------\n");
	printf("   key map help                                               \n");
	printf("   Press -                                                    \n");
	printf("   \tCtrl + L -> to select and toggle with light source       \n");
	printf("   \tCtrl + C -> to select and toggle with camera             \n");
	printf("   \tCtrl + N -> to select an object or select the next object\n");
	printf("   \tCtrl + E -> to de-select and exit interactive mode       \n");
	printf("   \tA        -> to move left along x-axis                    \n");
	printf("   \tD        -> to move right along x-axis                   \n");
	printf("   \tW        -> to move up along y-axis                      \n");
	printf("   \tS        -> to move down along y-axis                    \n");
	printf("   \tZ        -> to move forward along z-axis                 \n");
	printf("   \tX        -> to move backward along z-axis                \n");
	printf("   \tH        -> to display the help menu                     \n");
	printf("   \tEsc      -> to exit the program                          \n");
	printf("--------------------------------------------------------------\n");
	printf("\n");
}

/**
 * Prints the key map for interacting with a sphere.
 * Includes selection/toggle, movement on all axes, and radius
 * resizing via keys.
 */
void	help_sphere(void)
{
	printf("\n");
	printf("------------------------- miniRt -----------------------------\n");
	printf("   miniRt is a simple raytracing program build with C and Joy!\n");
	printf("   use below keys\\key comibinations to interact, enjoy...    \n");
	printf("   Press -                                                    \n");
	printf("   \tCtrl + L -> to select and toggle with light source       \n");
	printf("   \tCtrl + C -> to select and toggle with camera             \n");
	printf("   \tCtrl + N -> to select an object or select the next object\n");
	printf("   \tCtrl + M -> to move the sphere along x,y,z axis          \n");
	printf("   \tCtrl + R -> to re-size the spihre radius                 \n");
	printf("   \tCtrl + E -> to de-select and exit interactive mode       \n");
	printf("   \tA        -> to move left along x-axis                    \n");
	printf("   \tD        -> to move right along x-axis                   \n");
	printf("   \tW        -> to move up along y-axis                      \n");
	printf("   \tS        -> to move down along y-axis                    \n");
	printf("   \tZ        -> to move forward along z-axis                 \n");
	printf("   \tX        -> to move backward along z-axis                \n");
	printf("   \tKEY_DOWN -> to decreas the radius                        \n");
	printf("   \tKEY_UP   -> to increase the raidius                      \n");
	printf("   \tH        -> to display the help menu                     \n");
	printf("   \tEsc      -> to exit the program                          \n");
	printf("--------------------------------------------------------------\n");
	printf("\n");
}

/**
 * Prints a concise summary of interactive mode controls.
 * Highlights how to enter/exit mode and manipulate the selected object.
 */
void	help_mode(void)
{
	printf("\n");
	printf("------------------------- miniRt -----------------------------\n");
	printf("   miniRt is a simple raytracing program build with C and Joy!\n");
	printf("   use below keys\\key comibinations to interact, enjoy...    \n");
	printf("   Press -                                                    \n");
	printf("   \tCtrl + L -> to select and toggle with light source       \n");
	printf("   \tCtrl + C -> to select and toggle with camera             \n");
	printf("   \tCtrl + N -> to select an object or select the next object\n");
	printf("   \tCtrl + M -> to move the sphere along x,y,z axis          \n");
	printf("   \tCtrl + R -> to re-size the spihre radius                 \n");
	printf("   \tCtrl + E -> to de-select and exit interactive mode       \n");
	printf("   \tH        -> to display the help menu                     \n");
	printf("   \tEsc      -> to exit the program                          \n");
	printf("--------------------------------------------------------------\n");
	printf("\n");
}

/**
 * Prints the key map for interacting with a cylinder.
 * Covers selection/toggle, movement, rotation, and resizing radius/height
 * (including arrow keys).
 */
void	help_cylinder(void)
{
	printf("\n");
	printf("------------------------- miniRt -----------------------------\n");
	printf("   key map help                                               \n");
	printf("   Press -                                                    \n");
	printf("   \tCtrl + L -> to select and toggle with light source       \n");
	printf("   \tCtrl + C -> to select and toggle with camera             \n");
	printf("   \tCtrl + N -> to select an object or select the next object\n");
	printf("   \tCtrl + M -> to move the cylinder along x,y,z axis        \n");
	printf("   \tCtrl + R -> to resize the cylinder radius/height         \n");
	printf("   \tCtrl + S -> to rotate the cylinder                       \n");
	printf("   \tCtrl + E -> to de-select and exit interactive mode       \n");
	printf("   \tA        -> to move/rotate left along x-axis             \n");
	printf("   \tD        -> to move/rotate right along x-axis            \n");
	printf("   \tW        -> to move/rotate up along y-axis               \n");
	printf("   \tS        -> to move/rotate down along y-axis             \n");
	printf("   \tZ        -> to move/rotate forward along z-axis          \n");
	printf("   \tX        -> to move/rotate backward along z-axis         \n");
	printf("   \tKEY_UP   -> to increase the radius                       \n");
	printf("   \tKEY_DOWN -> to decrease the radius                       \n");
	printf("   \tKEY_RIGHT-> to increase the height                       \n");
	printf("   \tKEY_LEFT -> to decrease the height                       \n");
	printf("   \tH        -> to display the help menu                     \n");
	printf("   \tEsc      -> to exit the program                          \n");
	printf("--------------------------------------------------------------\n");
	printf("\n");
}
