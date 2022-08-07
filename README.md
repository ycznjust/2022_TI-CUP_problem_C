# 2022_TI-CUP_problem_C
2022年电子设计大赛，C题——小车跟随行驶系统，控制代码的一部分。

开发环境使用keil

为什么用keil呢, keil使用CMSIS-DAP下载器, ~~可以快乐的无线下载调试~~

[基础部分视频b站地址](https://www.bilibili.com/video/BV19T411j74q)

[自由发挥部分视频b站地址](https://www.bilibili.com/video/BV1SN4y1V75X)

文件夹number_2是第二辆车的代码，number_3是第三辆车的代码

第一辆车是队友完成的，[代码地址](https://github.com/PtilopsisSak/TI_cup_2022_problem_C_MSP432P401R_car_1)

重要提示：

1. 代码写的很....一言难尽

2. 代码看不懂就多看看，我也有时候看不懂

3. 由于我在考研...希望大家还是别去私信我问问题了，可以去我队友主页问他

4. 队友的主页：https://github.com/PtilopsisSak

控制策略说明：

1. 测距使用的超声波，然后写了一个控制距离的控制器
2. 循迹使用最简单的灰度传感器
3. 通讯使用最简单的HC-05蓝牙
