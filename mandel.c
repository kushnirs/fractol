/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:14:49 by sergee            #+#    #+#             */
/*   Updated: 2018/01/24 16:25:05 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define MAX_SOURCE_SIZE 0x100000
#define CL_BUILD_PROGRAM_FAILURE -11

static void kernel_fun(t_mlx data)
{
	cl_int ret;

	ret = clSetKernelArg(data.kernel.kernel, 0, sizeof(cl_mem), (void *)&data.kernel.memobj);
	ret = clSetKernelArg(data.kernel.kernel, 1, sizeof(int), (void *)&data.width);
	ret = clSetKernelArg(data.kernel.kernel, 2, sizeof(int), (void *)&data.high);
	ret = clSetKernelArg(data.kernel.kernel, 3, sizeof(double), (void *)&data.re);
	ret = clSetKernelArg(data.kernel.kernel, 4, sizeof(double), (void *)&data.im);
	ret = clSetKernelArg(data.kernel.kernel, 5, sizeof(double), (void *)&data.index);
	ret = clEnqueueNDRangeKernel(data.kernel.command_queue, data.kernel.kernel, 2, NULL, (size_t[3]){data.width, data.high, 0}, NULL, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(data.kernel.command_queue, data.kernel.memobj, CL_TRUE, 0,
		data.width * data.high * sizeof(int), data.data_adr, 0, NULL, NULL);
	mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
}

static int	mouse_action(int button, int x, int y, t_mlx *data)
{
	button == M_UP ? data->index -= data->index / 20 : 0;
	button == M_UP ? data->re = formula(data->re, data->re +
					(x - data->width / 2) * data->index, 0.05) : 0;
	button == M_UP ? data->im = formula(data->im, data->im +
					(y - data->high / 2) * data->index, 0.05) : 0;
	button == M_DOWN ? data->index += data->index / 20 : 0;
	kernel_fun(*data);	
	return (0);
}

int mandelbrot()
{
	int  fp;
	char fileName[] = "./mandel_kernel.cl";
	char *source_str;
	size_t source_size;
	cl_int ret;

	t_mlx	data;

	data = (t_mlx){.width = WIDTH, .high = HIGH,
		.index = 0.003, .re = -0.75, .im = 0};
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.high, "Mandelbrot");
	data.image = mlx_new_image(data.mlx, data.width, data.high);
	data.data_adr =
	(t_ui *)mlx_get_data_addr(data.image, &data.bpp, &data.sl, &data.endian);
	//////////
	fp = open(fileName, O_RDONLY);
	if (fp <= 0)
	{
		printf("Failed to load kernel.\n");
		exit(1);
	}
	 if (!(source_str = (char*)malloc(MAX_SOURCE_SIZE)))
	 	return(printf("su4ara\n"));
	source_size = read(fp, source_str, MAX_SOURCE_SIZE);
	close(fp);
	ret = clGetPlatformIDs(1, &data.kernel.platform_id, &data.kernel.ret_num_platforms);
	ret = clGetDeviceIDs(data.kernel.platform_id, CL_DEVICE_TYPE_CPU, 1, &data.kernel.device_id, &data.kernel.ret_num_devices);
	data.kernel.context = clCreateContext(NULL, 1, &data.kernel.device_id, NULL, NULL, &ret);
	data.kernel.command_queue = clCreateCommandQueue(data.kernel.context, data.kernel.device_id, 0, &ret);
	data.kernel.memobj = clCreateBuffer(data.kernel.context, CL_MEM_READ_WRITE,
		data.width * data.high * sizeof(int), NULL, &ret);
	data.kernel.program = clCreateProgramWithSource(data.kernel.context, 1, (const char **)&source_str,
		(const size_t *)&source_size, &ret);
	ret = clBuildProgram(data.kernel.program, 1, &data.kernel.device_id, NULL, NULL, NULL);
// 	if (ret == CL_BUILD_PROGRAM_FAILURE) {
//     // Determine the size of the log
//     size_t log_size;
//     clGetProgramBuildInfo(data.kernel.program, data.kernel.device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

//     // Allocate memory for the log
//     char *log = (char *) malloc(log_size);

//     // Get the log
//     clGetProgramBuildInfo(data.kernel.program, data.kernel.device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

//     // Print the log
//     printf("%s\n", log);
// }
	data.kernel.kernel = clCreateKernel(data.kernel.program, "draw_fract", &ret);
	kernel_fun(data);

	// ret = clReleaseKernel(data.kernel.kernel);
	// ret = clReleaseProgram(data.kernel.program);
	// ret = clReleaseMemObject(data.kernel.memobj);
 // 	ret = clReleaseCommandQueue(data.kernel.command_queue);
	// ret = clReleaseContext(data.kernel.context);
	// free(source_str);
	///////////
	// draw_fract(&data);
	// mlx_put_image_to_window(data.mlx, data.win, data.image, 0, 0);
	// for (int i = 300; i < 400; i++)
	// 	for (int k = 300; k < 400; k++)
	// 		printf("%d", data.data_adr[i + k * HIGH]);
	mlx_mouse_hook(data.win, &mouse_action, &data);
	mlx_key_hook(data.win, &key_action, &data);
	mlx_hook(data.win, 17, 0, &close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}