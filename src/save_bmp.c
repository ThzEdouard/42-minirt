/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:43:06 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/26 13:39:18 by hthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define __STDC_WANT_LIB_EXT1__ 1
void	print_err_and_exit(const char *str)
{
    ft_putstr_fd("Error: ", STDERR_FILENO);
    ft_putstr_fd((char *)str, STDERR_FILENO);
    ft_putstr_fd(")\n", STDERR_FILENO);
    exit(0);
}

void	save_bmp(const char *filename, const unsigned char *data, int w, int h)
{
    int				filesize;
    unsigned char	bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char	bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 32,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
    unsigned char	bmppad[3] = {0, 0, 0};

    FILE *filePointer;
    filesize = 54 + 3 * w * h;
    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w >> 8);
    bmpinfoheader[6] = (unsigned char)(w >> 16);
    bmpinfoheader[7] = (unsigned char)(w >> 24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h >> 8);
    bmpinfoheader[10] = (unsigned char)(h >> 16);
    bmpinfoheader[11] = (unsigned char)(h >> 24);
    unsigned char *bgr_pixel;
    bgr_pixel  = malloc(sizeof(unsigned  char) * (WIDTH * HEIGHT * 3));
    filePointer = fopen(filename, "wb");
    fwrite(bmpfileheader, 1, 14, filePointer);
    fwrite(bmpinfoheader, 1, 40, filePointer);
    for (int i = 0; i < w * h; i++)
    {
        bgr_pixel[i * 3] = data[i * 3 + 2];
        bgr_pixel[i * 3 + 1] = data[i * 3 + 1];
        bgr_pixel[i * 3 + 2] = data[i * 3];
    }
    for (int i = 0; i < h; i++)
    {
        fwrite(&bgr_pixel[0] + (w *(h-i-1)*3), 3, w, filePointer);
        fwrite(bmppad, 1, (4 - (w *3) % 4) % 4, filePointer);
    }
    fclose(filePointer);
}