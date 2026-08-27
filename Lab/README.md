# CS61C Labs — 说明与索引

> 本仓库实际为 **UC Berkeley CS61C Fall 2020 (fa20)** 的官方 starter 仓库
> （`61c-teach/fa20-lab-starter`）。原 starter 仓库只含代码、不含要求文档；
> 现从 Wayback Machine 抓取了官方课程页的 spec 存档，整理到各 lab 目录下。
> 全部内容归 UC Berkeley CS61C 团队所有，仅供个人学习参考。

## 每个 lab 目录下的文件

| 文件 | 说明 |
|---|---|
| `SPEC.md` | 官方要求（markdown，推荐阅读） |
| `SPEC.html` | 官方要求（Wayback 存档的原始 HTML 页面） |
| 其余 `.c` / `.h` / `.s` / `.circ` / Makefile 等 | 课程 starter 代码 |

## Lab 列表

| Lab | 主题 | 截止时间（fa20 原安排） | 作业要求 |
|---|---|---|---|
| [lab00](lab00/SPEC.md) | 环境/账号设置（GitHub、Gradescope、Hive 等），Linux 与 Git 入门 | 9/4（本 lab 延期 1 周） | [SPEC.md](lab00/SPEC.md) |
| [lab01](lab01/SPEC.md) | C 语言复习、gdb 调试、链表判环 (ll_cycle) | 9/4 | [SPEC.md](lab01/SPEC.md) |
| [lab02](lab02/SPEC.md) | 位操作、Makefile、LFSR、动态内存管理 (vector) | 9/11 | [SPEC.md](lab02/SPEC.md) |
| [lab03](lab03/SPEC.md) | RISC-V 汇编与 Venus 模拟器、函数调用规范 | 9/18 | [SPEC.md](lab03/SPEC.md) |
| [lab04](lab04/SPEC.md) | RISC-V 调试与指针函数 | 9/25 | [SPEC.md](lab04/SPEC.md) |
| [lab05](lab05/SPEC.md) | Logisim 组合逻辑、状态机 FSM | 10/7–10/9（checkoff） | [SPEC.md](lab05/SPEC.md) |
| [lab06](lab06/SPEC.md) | 时序电路时序分析、流水线 | 10/16 | [SPEC.md](lab06/SPEC.md) |
| [lab07](lab07/SPEC.md) | 缓存命中率、矩阵转置优化 | 10/30 | [SPEC.md](lab07/SPEC.md) |
| [lab08](lab08/SPEC.md) | 虚拟内存、TLB 与页表 | 11/6 | [SPEC.md](lab08/SPEC.md) |
| [lab09](lab09/SPEC.md) | SIMD 数据级并行 | 11/13 | [SPEC.md](lab09/SPEC.md) |
| [lab10](lab10/SPEC.md) | OpenMP 并行与 false sharing | 11/20 | [SPEC.md](lab10/SPEC.md) |
| [lab11](lab11/SPEC.md) | MapReduce / Apache Spark | 12/4 | [SPEC.md](lab11/SPEC.md) |

## 获取方式与备注

- **spec 来源**：Wayback Machine 存档的官方课程页
  `https://inst.eecs.berkeley.edu/~cs61c/fa20/labs/labXX/`（每个 SPEC.md 头部都标注了存档链接）。
- **图片缺失**：spec 中引用的部分图片（多为 Logisim 电路图、示意图）当时未被 Wayback
  存档，现在原站会跳转到 CalNet 登录页，因此无法显示。仅 `lab00/inst_prompt.jpg`
  已成功存档并下载到 lab00 目录。
- **学期说明**：若你手上的课件标注为 "2020 Summer (su20)"，其 lab 内容与 fa20 几乎一致，
  以上 fa20 spec 同样适用。
