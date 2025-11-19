---
title: Ubuntu代理设置全解
tags: Linux
---


## 🧩 一、Linux 上的“系统代理”其实是 GUI 层代理

当你在 Ubuntu 的图形界面中设置了：

> Settings → Network → Network Proxy
>  例如 SOCKS: 127.0.0.1:1080 或 HTTP: 127.0.0.1:1080

这实际上只影响：

- **GNOME 桌面程序**（比如 Firefox、Snap 应用、系统更新等）；
- 它通过 `gsettings` 或 `dconf` 传递配置；
- **命令行程序（git、curl、wget 等）不会自动使用**。

👉 换句话说：

> 你设置的“系统代理”，git 默认不会理会。


## 🧭 二、要让 `git` 走代理，你必须单独配置它

### ✅ 如果你的代理是 HTTP/HTTPS 代理（如 v2ray http 入站）

例如你的 V2Ray 监听：

```
127.0.0.1:10802 （protocol: http）
```

则执行：

```bash
git config --global http.proxy http://127.0.0.1:10802
git config --global https.proxy http://127.0.0.1:10802
```

确认：

```bash
git config --global --get http.proxy
git config --global --get https.proxy
```


### ✅ 如果你的代理是 SOCKS5（例如 127.0.0.1:1080 或 10801）

可以这样：

```bash
git config --global http.proxy socks5h://127.0.0.1:10801
git config --global https.proxy socks5h://127.0.0.1:10801
```

注意：

- `socks5h://` 中的 **h** 表示由代理解析域名（防止 DNS 泄露）；
- 如果你写 `socks5://`，git 会在本地解析域名，导致可能被污染。


### ✅ 取消代理（恢复直连）

```bash
git config --global --unset http.proxy
git config --global --unset https.proxy
```


## 🧠 三、通用环境变量法（影响所有命令行程序）

你也可以在终端中**导出代理变量**，这样不仅 `git`，`curl`、`wget`、`apt` 等也能自动使用代理。

### HTTP 代理：

```bash
export http_proxy="http://127.0.0.1:10802"
export https_proxy="http://127.0.0.1:10802"
```

### SOCKS5 代理：

```bash
export ALL_PROXY="socks5h://127.0.0.1:10801"
```

### 生效验证

```bash
echo $http_proxy
curl https://www.google.com
```

如果能打开，就说明走代理成功。

要让这些变量**永久生效**，可以加到：

```bash
~/.bashrc
```

或

```bash
~/.bash_profile
```


## 🧪 四、验证代理是否真的生效

### 1️⃣ 使用 curl 测试

```bash
curl -I https://google.com
```

如果能返回 `HTTP/2 200` 或重定向，说明代理生效。
 若提示 “Connection timed out” 则未使用代理。

### 2️⃣ 使用 ip 检查

```bash
curl -s https://ipinfo.io
```

查看 `ip` 字段是否为你的代理出口 IP。


## ✅ 总结表格

| 方式                             | 适用于           | 是否影响 git | 是否影响终端 |
| -------------------------------- | ---------------- | ------------ | ------------ |
| Ubuntu GUI 系统代理              | 桌面程序 (GNOME) | ❌ 否         | ❌ 否         |
| `git config --global http.proxy` | 仅 git           | ✅ 是         | ❌ 否         |
| `export http_proxy=...`          | 所有命令行程序   | ✅ 是         | ✅ 是         |


## 💡 推荐实践（给你当前的情况）

你使用 V2Ray core 本地监听：

- SOCKS5: `127.0.0.1:10801`
- HTTP: `127.0.0.1:10802`

那你可以直接在 Ubuntu 终端执行：

```bash
git config --global https.proxy socks5h://127.0.0.1:10801
git config --global http.proxy socks5h://127.0.0.1:10801
```

或者让所有终端命令都通过代理：

```bash
export ALL_PROXY="socks5h://127.0.0.1:10801"
```


