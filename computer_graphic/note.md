视图变换
<img src="./img/view%20transform.png">

透视投影：先挤压到一个平面-》再正交投影

远平面上的一个vector挤压后Z不变

垂直可视角度：上下中心的夹角

经过MVP后，再通过viewport transform视口变换 to screen：先从[-1,1]的三次方的三维model，进行拉伸width/2，height/2，再将中心从原点移动width/2,height/2
转到二维屏幕上

三角形是最基础的多边形，所以多边形都可以由三角形组合而成

采样：例如判断每个像素点中心是否在三角形内，决定是否渲染该像素，当然期间会产生锯齿和走样的问题
因为采样的速度跟不上信号变化的速度

从频率上分析走样：两条完全不同的频率，根据相同的采样方式得到一样的结果


反走样方法：先对信号模糊，再采样

滤波：过滤掉一些特定频率

两张图片：
从时域-》频域

低频信息在中心，高频信息在外围，通过亮度表示信息数量，越亮信息越多

高通滤波：
对低频信号做滤波，去掉低频信号保留高频信号时，进行还原仍然可以看到图片的边界
高频信息更能反映图片的边界

当去掉最低频信息和最高频信息时

MSAA：增加像素内的采样点，原来只有一个点，可以增加成2*2的矩阵点分布，判断覆盖在每个像素内的百分比，从而实现模糊操作，实际上根据这个百分比就可以进行渲染了。也就是该方法中采样是包含的模糊操作内的

画家算法：先画远的面，再画近的面

Z-Buffer：深度缓存/深度缓冲

记录每个像素的最近的需要渲染的目标
深度值（Z值）越大，则离摄像机越远
则记录每个像素的最小深度，这样就可以解决物体叠加远近的问题
问题：解决不了透明物体的问题



