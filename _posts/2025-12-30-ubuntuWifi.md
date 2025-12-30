---
title: ubuntu连接wifi教程
tags: Linux
---

在 **Ubuntu Server** 上通常**没有图形界面**，连接 Wi‑Fi 一般用命令行完成。下面按**最常见、最稳妥**的方法给你说明。


## 一、确认无线网卡是否被识别

```bash
ip link
```

或

```bash
iw dev
```

如果看到类似 `wlan0`、`wlp2s0` 的接口，说明无线网卡可用。

如果没有，可能需要安装驱动（尤其是 USB Wi‑Fi）。


## 二、安装必要工具

Ubuntu Server 默认可能没装 Wi‑Fi 工具：

```bash
sudo apt update
sudo apt install -y network-manager
```

启用 NetworkManager：

```bash
sudo systemctl enable NetworkManager
sudo systemctl start NetworkManager
```


## 三、搜索附近 Wi‑Fi（关键步骤）

使用 `nmcli`（推荐）：

```bash
nmcli dev wifi list
```

你会看到类似：

```
IN-USE  SSID        SIGNAL  SECURITY
        HomeWifi    70      WPA2
        OfficeNet   55      WPA1 WPA2
```


## 四、连接 Wi‑Fi

```bash
sudo nmcli dev wifi connect "SSID名称" password "WiFi密码"
```

例如：

```bash
sudo nmcli dev wifi connect "HomeWifi" password "12345678"
```

成功后会显示：

```
Device 'wlp2s0' successfully activated
```


## 五、验证是否联网

```bash
ip a
ping -c 4 www.baidu.com
```


## 六、如果是隐藏 Wi‑Fi

```bash
sudo nmcli dev wifi connect "SSID" password "密码" hidden yes
```


## 七、老设备 / 无 NetworkManager（备用方案）

如果你**不想用 NetworkManager**，可以用 `wpa_supplicant`（较底层，不推荐新手）：

```bash
sudo apt install wpasupplicant
sudo wpa_passphrase SSID 密码 | sudo tee /etc/wpa_supplicant.conf
sudo wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
sudo dhclient wlan0
```

## 常见问题

### 1️⃣ nmcli 报错 “Device not found”

- 无线网卡驱动没装
- 被 BIOS 禁用
- 被 `rfkill` 禁用：

```bash
rfkill list
sudo rfkill unblock wifi
```

### 2️⃣ 每次重启后 Wi‑Fi 不自动连接

NetworkManager 会自动保存连接，一般不会出现该问题。


## 总结（最推荐流程）

```bash
sudo apt install network-manager
nmcli dev wifi list
sudo nmcli dev wifi connect "SSID" password "密码"
```


