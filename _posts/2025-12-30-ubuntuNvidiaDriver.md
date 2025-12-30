---
title: ubuntu安装nvidia驱动进行深度学习训练
tags: Linux
---

在 Ubuntu Server 上安装 NVIDIA 驱动涉及几个步骤，需要注意你的 GPU 型号、内核版本以及是否使用了 `nouveau` 开源驱动。下面我给你整理一个详细的流程（适用于 Ubuntu 22.04/20.04 Server）：


## **步骤 1：检查你的 GPU 型号**

在终端输入：

```bash
lspci | grep -i nvidia
```

如果显示了 NVIDIA GPU 的信息，就可以继续。


## **步骤 2：更新系统并安装必要工具**

```bash
sudo apt update
sudo apt upgrade -y
sudo apt install build-essential dkms linux-headers-$(uname -r) -y
```

这些是编译 NVIDIA 驱动时需要的工具和内核头文件。


## **步骤 3：禁用 Nouveau 驱动（开源 NVIDIA 驱动）**

1. 创建配置文件：

```bash
sudo nano /etc/modprobe.d/blacklist-nouveau.conf
```

添加以下内容：

```
blacklist nouveau
options nouveau modeset=0
```

1. 更新 initramfs：

```bash
sudo update-initramfs -u
```

1. 重启服务器：

```bash
sudo reboot
```


## **步骤 4：添加 NVIDIA 官方 PPA（推荐）**

Ubuntu 提供了 NVIDIA 官方 PPA，可以方便地安装驱动。

```bash
sudo add-apt-repository ppa:graphics-drivers/ppa
sudo apt update
```

## **步骤 5：查找可用的 NVIDIA 驱动**

```bash
ubuntu-drivers devices
```

你会看到类似：

```
driver   : nvidia-driver-530 - distro non-free recommended
```

推荐安装 `recommended` 的版本。


## **步骤 6：安装 NVIDIA 驱动**

例如推荐的驱动是 `nvidia-driver-530`：

```bash
sudo apt install nvidia-driver-530 -y
```

安装完成后重启：

```bash
sudo reboot
```


## **步骤 7：验证驱动是否安装成功**

```bash
nvidia-smi
```

如果能看到 GPU 信息和驱动版本，就说明安装成功了。


### **注意事项**

1. Ubuntu Server 默认没有 GUI，`nvidia-smi` 就足够验证驱动。
2. 如果你使用的是最新 GPU，可能需要安装更高版本驱动。
3. 遇到黑屏或启动问题，检查 `nouveau` 是否完全禁用。


## 安装CUDA Toolkit Installer

去这里找最新的安装命令：https://developer.nvidia.com/cuda-downloads
```
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2204/x86_64/cuda-keyring_1.1-1_all.debsudo dpkg -i cuda-keyring_1.1-1_all.debsudo apt-get updatesudo apt-get -y install cuda-toolkit-13-1
```

安装好了 **CUDA Toolkit**，但是系统还找不到 `nvcc` 命令，这说明 **CUDA 的环境变量没有添加到 PATH 中**。我帮你整理一下最标准的做法。


## **1️⃣ 确认 CUDA 安装路径**

可以用命令确认：

```bash
ls /usr/local | grep cuda
```


## **2️⃣ 添加 CUDA 到环境变量**

编辑你的 `~/.bashrc` 文件（或者 `~/.zshrc`，如果你用 zsh）：

```bash
nano ~/.bashrc
```

在文件末尾添加：


```bash
export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
```

------

## **3️⃣ 让修改生效**

```bash
source ~/.bashrc
```

## **4️⃣ 验证**

```bash
nvcc -V
```

你应该能看到 CUDA 版本信息，例如：

```
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2024 NVIDIA Corporation
Built on ...
Cuda compilation tools, release 12.2, V12.2.91
```
