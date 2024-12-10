/* ************************************************************************** */
/*												    */
/*									  :::	::::::::   */
/*   colors.h							 :+:	:+:    :+:   */
/*								    +:+ +:+	   +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>		+#+  +:+	 +#+	  */
/*								+#+#+#+#+#+   +#+	     */
/*   Created: 2024/12/02 17:33:18 by bmouhib	     #+#    #+#		 */
/*   Updated: 2024/12/02 17:35:17 by bmouhib	    ###   ########.fr	 */
/*												    */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Foreground Colors
# define NON_PRINT			"\001"
# define END_NP				"\002"

// Foreground Colors
# define RESET_COLOR		"\033[0m"	// Reset all attributes
# define BOLD				"\033[1m"	// Bold text
# define UNDERLINE			"\033[4m"	// Underline text
# define REVERSED   		"\033[7m"	// Reversed colors

// Standard Colors
# define BLACK				"\033[30m"     // Black text
# define RED				"\033[31m"     // Red text
# define GREEN				"\033[32m"     // Green text
# define YELLOW				"\033[33m"     // Yellow text
# define BLUE				"\033[34m"     // Blue text
# define MAGENTA			"\033[35m"     // Magenta text
# define CYAN				"\033[36m"     // Cyan text
# define WHITE				"\033[37m"     // White text

// Bright Colors
# define BRIGHT_BLACK		"\033[90m" // Bright black (gray)
# define BRIGHT_RED			"\033[91m" // Bright red
# define BRIGHT_GREEN		"\033[92m" // Bright green
# define BRIGHT_YELLOW		"\033[93m" // Bright yellow
# define BRIGHT_BLUE		"\033[94m" // Bright blue
# define BRIGHT_MAGENTA		"\033[95m" // Bright magenta
# define BRIGHT_CYAN		"\033[96m" // Bright cyan
# define BRIGHT_WHITE		"\033[97m" // Bright white

// Background Colors
# define BG_BLACK			"\033[40m"  // Black background
# define BG_RED				"\033[41m"  // Red background
# define BG_GREEN			"\033[42m"  // Green background
# define BG_YELLOW			"\033[43m"  // Yellow background
# define BG_BLUE			"\033[44m"  // Blue background
# define BG_MAGENTA			"\033[45m"  // Magenta background
# define BG_CYAN			"\033[46m"  // Cyan background
# define BG_WHITE			"\033[47m"  // White background

// Bright Background Colors
# define BG_BRIGHT_BLACK	"\033[100m" // Bright black background
# define BG_BRIGHT_RED		"\033[101m" // Bright red background
# define BG_BRIGHT_GREEN	"\033[102m" // Bright green background
# define BG_BRIGHT_YELLOW	"\033[103m" // Bright yellow background
# define BG_BRIGHT_BLUE		"\033[104m" // Bright blue background
# define BG_BRIGHT_MAGENTA	"\033[105m" // Bright magenta background
# define BG_BRIGHT_CYAN		"\033[106m" // Bright cyan background
# define BG_BRIGHT_WHITE	"\033[107m" // Bright white background

#endif