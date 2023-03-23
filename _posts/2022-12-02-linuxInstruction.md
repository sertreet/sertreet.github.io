---
title: 一些常用的Linux命令
tags: Linux
---

# 安装V2Ray
Ubuntu/Debian 系统: `apt-get update -y && apt-get install curl -y`  
CentOS 系统: `yum update -y && yum install curl -y`  
安装V2Ray: `bash <(curl -s -L https://git.io/v2ray.sh)`  

# VMware tools安装  
> 1. `sudo apt install open-vm-tools`  
> 2. `sudo apt install open-vm-tools-desktop`  

重启ubuntu   

# 切换Python包安装源  
豆瓣源  
`-i https://pypi.douban.com/simple/`  
`pip install -i https://pypi.doubanio.com/simple/ --trusted-host pypi.doubanio.com pillow`  
pillow替换成要安装的软件  

这个方法更简单，直接一步到位：  
`pip config set global.index-url http://mirrors.aliyun.com/pypi/simple/`  
`pip config set global.trusted-host mirrors.aliyun.com`  

# Git提交代码  
将本地代码全部提交：`git  add .`  
为本次提交添加注释：`git commit -m "xxxx"`  
将提交的代码推送到主分支：`git push`  
查看本地代码状态，是否有待提交的代码：`git status`  
查看git合入的记录：`git log`  

# screen多重视窗管理器使用方法  
新建窗口：`screen` 或 `screen -S name`  
分离会话：快键键`Ctrl+A+D`实现分离  
列出窗口列表：`screen -ls`  
恢复到窗口：`screen -r xxxx(id号)或者name`  
杀死会话窗口：`kill -9 xxxx(id号)`  
清除死去窗口：`screen -wipe`  

# 在同一个内网里使用ubuntu的jupyter notebook  
要在内网中使用Ubuntu的Jupyter Notebook，需要进行以下步骤：  
+ 安装Jupyter Notebook。您可以使用Anaconda或pip安装Jupyter Notebook。  
+ 生成配置文件。在终端中输入以下命令：`jupyter notebook --generate-config`。  
+ 设置密码。在终端中输入以下命令：`jupyter notebook password`。这将提示您输入密码并确认密码。  
+ 开启端口。在终端中输入以下命令：`jupyter notebook --ip=0.0.0.0 --port=8888`。这将开启Jupyter Notebook服务器，并允许其他计算机通过IP地址和端口号访问它。   

如果想要更好的安全性，可以使用SSL证书来加密通信。有关如何使用SSL证书的详细信息，请参见Jupyter Notebook文档。  
如果计算机上有防火墙或路由器，则可能需要配置它们以允许其他计算机访问Jupyter Notebook服务器。  