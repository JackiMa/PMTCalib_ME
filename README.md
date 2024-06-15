# PMTCalib : A framework for photomultiplier tube (PMT) calibration

该脚本来自论文：https://www.sciencedirect.com/science/article/pii/S0168900223009439

## Docker 使用步骤
安装CERN ROOT的docker环境后：
``` docker run -it -e DISPLAY=host.docker.internal:0.0 -v path/to/the/PMT-calibCode:/root/code rootproject/root /bin/bash ```
如果想将当前文件夹挂载到docker中（适用于powershell的代码）:
```docker run -it -e DISPLAY=host.docker.internal:0.0 -v "$(pwd):/root/code" rootproject/root /bin/bash```
注意：
- -e DISPLAY=host.docker.internal:0.0 打开X端口转发，使之实现图形化界面
- -v path/to/the/PMT-calibCode:/root/code 将本地PMT标定代码挂载到docker环境下的/root/code
- rootproject/root 使用CERN ROOT的docker环境
- /bin/bash 打开docker默认进入bash

提示：
- 第一次使用时，会自动下载 CERN ROOT 的docker镜像，如果国内无法下载，请挂梯子
- 启动镜像后，推荐使用vscode连接进入镜像使用。


## 非Docker使用步骤
1. 配置CERN ROOT的环境
2. 修改makefile，使之在该文件夹下可以编译通过
3. 进入到代码文件夹，修改makefile使之可以编译通过

## 代码使用说明
R6233-example.txt 是演示文件，在 R6233 文件夹下执行 `./ana-exec fitconfig.json` 即可运行，其中`fitconfig.json`是配置文件，可以在其中设置要拟合的文件和部分拟合参数。
