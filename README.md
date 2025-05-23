# PMTCalib : A framework for photomultiplier tube (PMT) calibration

该脚本的核心拟合程序来自论文：https://www.sciencedirect.com/science/article/pii/S0168900223009439  
该项目只是针对CERN ROOT的docker配置了运行环境，使得可以方便的在任意支持docker的设备上运行该脚本，从而降低对PMT增益拟合的门槛。  
本项目实现的思路：仅仅借用CERN ROOT的docker环境，PMT增益拟合代码在本地保存。这种方式可以最大限度的保持灵活性和通用性，即：不需要创建新的docker镜像，并且拟合代码方便进行修改，程序运行后不必保存镜像

## Docker 使用步骤
安装CERN ROOT的docker环境后：
``` docker run -it --rm -e DISPLAY=host.docker.internal:0.0 -v path/to/the/PMT-calibCode:/root/code rootproject/root /bin/bash ```
如果想将当前文件夹挂载到docker中（适用于powershell的代码）:
```docker run -it --rm -e DISPLAY=host.docker.internal:0.0 -v "$(pwd):/root/code" rootproject/root /bin/bash```
注意：
- --rm 运行后不保留当前容器。该项目仅仅借用CERN ROOT的docker环境，而项目代码保存在本底，故无需保留容器
- -e DISPLAY=host.docker.internal:0.0 打开X端口转发，使之实现图形化界面
- -v path/to/the/PMT-calibCode:/root/code 将本地PMT标定代码（当前README所在文件夹）挂载到docker环境下的/root/code
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
R6233-example.txt 是演示文件，在 `/R6233` 文件夹下执行 `./ana-exec fitconfig.json` 即可运行，其中`fitconfig.json`是配置文件，可以在其中设置要拟合的文件和部分拟合参数。  

## 模型选择说明
本程序实现了四种不同的PMT响应模型，可在`fitconfig.json`中配置使用哪种模型：

1. **SIMPLEGAUSS (简单高斯模型)**：最基础的模型，使用标准高斯分布描述响应
2. **TRUNCGAUSS (截断高斯模型)**：考虑光电倍增过程中物理限制的高斯模型
3. **ANATRUNCG (解析截断高斯模型)**：使用超几何函数进行精确计算，适合复杂情况
4. **EXPTRUNCG (显式截断高斯模型)**：ANATRUNCG的优化版本，用预计算多项式代替超几何函数，提高计算效率

不同模型的适用场景：
- 对于计算速度要求高的场景，推荐使用SIMPLEGAUSS或TRUNCGAUSS
- 对于物理精度要求高的场景，推荐使用ANATRUNCG或EXPTRUNCG
- 对于批量处理任务，EXPTRUNCG在保持精度的同时提高了效率

在配置文件中，通过设置`"model_type"`字段来选择不同模型。例如：
```json
{
  "model_type": "EXPTRUNCG",
  ...其他配置参数...
}
```

注意：
- 可能因为每个设备的docker是因地制宜创建环境的，总之如果无法直接运行，请先删除掉可执行文件ana-exec，然后执行`make`重新编译

## 进阶说明
- `batch.py`是批处理python脚本，会自动根据文件名批量生成 `fitconfig.json` 并执行拟合生成pdf文件。
- `PMT_Fit_Analysis.ipynb` 是从拟合得到pdf文件中提取信息的自动化脚本，请注意，在使用该脚本前确保拟合结果正确。如果批处理的结果不好，可以采用前面的方式手动调参`fitconfig.json`来进行针对性拟合。CERN ROOT的docker镜像没有安装相关包，该步代码建议在别的环境中运行，当然也可以根据自己的需求来各自实现。

## 关于调参拟合的说明
推荐手动指定 μ、Q0、Q1来进项调参。在进行实验时，如果没有更改实验条件，那么不同HV下的μ、Q0值应当是一致的，可以参考别的HV拟合较好的结果来手动调参。