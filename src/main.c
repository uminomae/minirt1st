/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:51:40 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/12 16:54:05 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// main()
// 　├ validate_arg()
// 　├ begin()
//      └ read_rtfile	//ファイル読み込み
//      └ init	//初期化
//      └ scene	//環境設定
// 　├ run_raytracer()	//レイトレーシング
//      └ camera	//カメラ設定
//      └ hit	//交差判定
//      └ shade	//陰・影　Phong反射モデル
//      └ put	//陰・影　Phong反射モデル
//   ├ hook_mlx() //key・mouse操作、並列処理

//-----------------
// single thread
//-----------------
int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_ptr_list	alloc_list;
	t_scene		scene;
	t_para		para;

	validate_arg(argc, argv);
	begin_minirt(&mlx, &alloc_list, argv[1], &scene);
	run_raytracer(&mlx, &scene);
	hook_mlx(&mlx, &scene, &alloc_list, &para);
	mlx_loop(mlx.mlx_ptr);
}

//-----------------
// multi thread
//-----------------
// int	main(int argc, char **argv)
// {
// 	t_mlx		mlx;
// 	t_ptr_list	alloc_list;
// 	t_scene		scene;
// 	t_para		para;	

// 	validate_arg(argc, argv);
// 	begin_minirt(&mlx, &alloc_list, argv[1], &scene);
// 	scene.alloc_list = &alloc_list;
// 	scene.mlx = &mlx;
// 	para.scene = &scene;
// 	run_parallel(&para);
// 	hook_mlx(&mlx, &scene, &alloc_list, &para);
// 	mlx_loop(mlx.mlx_ptr);
// }
