# Nankai Rhythm

基于 C++17 + raylib 的四轨道图形化节奏游戏。玩家按下 `D F J K` 击打下落音符，系统根据命中时间误差判定 Perfect / Good / Bad / Miss，并统计分数、连击、准确率与评级。

## 编译方式

```bash
cmake -S . -B build
cmake --build build
```

## 操作说明

- `Enter`：开始游戏 / 从结算页返回菜单
- `H`：帮助界面
- `Esc`：退出或返回菜单
- `D F J K`：四条轨道按键

## 当前V1.0版本功能

- 主菜单
- 帮助界面
- 四轨道音符下落
- 谱面文件读取
- Perfect / Good / Bad / Miss 判定
- 分数、连击、最高连击、准确率
- 结算页面
