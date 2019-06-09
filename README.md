# 2Dto3D
convert 2d video to 3d
This is a project that can convert your 2d video into 3d.
1. 用ffmpeg将视频抽帧成图片。
2. 安装caffe，并将matlab配置好caffe
3. 将demo 运行在caffe/matlab/demo下面
4. 修改net_model, net_weight路径
5. 修改图片路径
运行成功后将显示单张图片深度图
将深度图和原图像放到dibr文件夹中，修改图片路径
运行程序，得到原图与深度图warping完成后的右视图。
左右视图同时播放即可呈现3d效果。（利用手机盒子等观看设备，或者任意可使左眼看到左边，右眼看到右边的设备均可）
