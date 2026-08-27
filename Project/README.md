# CS61C Projects — 说明与索引

> 本仓库实际为 **UC Berkeley CS61C Fall 2020 (fa20)** 的官方 starter 仓库
> （`61c-teach/fa20-proj1-starter` ~ `fa20-proj4-starter`）。原 starter 仓库只含代码、
> 不含要求文档；现从 Wayback Machine 抓取官方课程页的 spec 存档，整理到各 project 目录下。
> 全部内容归 UC Berkeley CS61C 团队所有，仅供个人学习参考。

## 每个 project 目录下的文件

| 文件 | 说明 |
|---|---|
| `SPEC.md` | 官方要求（markdown，推荐阅读） |
| `SPEC.html` | 官方要求（Wayback 存档的原始 HTML 页面） |
| 其余 `.c` / `.h` / `.s` / `.circ` / Makefile 等 | 课程 starter 代码 |
| `README.md`（proj2–4 原有） | 仓库原主人都写的内容，未改动 |

## Project 列表

| Project | 名称 | 内容 | 截止时间（fa20 原安排） | 作业要求 |
|---|---|---|---|---|
| [proj1](proj1/SPEC.md) | Conway's Game of Life, in RGB! | RISC-V 汇编实现康威生命游戏 + 图像（PPM）读写（imageloader / steganography / gameoflife） | Part A 9/16，Part B 9/19 | [SPEC.md](proj1/SPEC.md) |
| [proj2](proj2/SPEC.md) | CS61Classify | RISC-V 汇编实现简单 ANN（神经元/矩阵运算）在 Venus 上分类 MNIST 手写数字 | Part A 10/1，Part B 10/5 | [SPEC.md](proj2/SPEC.md) |
| [proj3](proj3/SPEC.md) | CS61CPU | 用 Logisim Evolution 搭建 RISC-V 5 级流水线 CPU | Part A 10/16，Part B 11/1 | [SPEC.md](proj3/SPEC.md) |
| [proj4](proj4/SPEC.md) | Numc | 用 C + Python C 扩展实现一个简版 numpy（numc），并做性能优化 | 12/4 | [SPEC.md](proj4/SPEC.md) |

## 获取方式与备注

- **spec 来源**：Wayback Machine 存档的官方课程页
  `https://inst.eecs.berkeley.edu/~cs61c/fa20/projects/projN/`（每个 SPEC.md 头部都标注了存档链接）。
- **图片**：
  - proj1 的动图（`conway.gif` / `multi.gif` / `multicolor.gif` / `explodingconway.mp4`）已存档并下载到 `proj1/`。
  - proj4 的提速对比图已下载到 `proj4/speedup_images/`（SPEC.md 中已改为本地相对路径）。
  - proj2、proj3 引用的示意图（MNIST.png、immediates.png 等）当时未被存档，原站已跳转 CalNet 登录页，故无法显示。
