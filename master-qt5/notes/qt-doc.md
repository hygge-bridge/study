# Model/View Tutorial

widget访问的数据的方法：

1. widget直接包含一个存储数据的内部容器
   - 优点：代码直观
   - 缺点：对于复杂应用，容易出现数据同步问题
2. widget不存储数据容器，而是通过一个被标准化的接口访问外部数据
   - 优点：避免了数据同步问题
   - 缺点：对于简单应用，复杂度会提升

## 1. Introduction

model/view的核心是将数据与视图分离。

标准widget的设计目的并不是将数据分离，所以qt提供了标准widget（直接操作数据）和view class（操作外部数据，也就是model）两种widget。

### 1.1 Standard Widgets

考虑传统的table widget，

展示数据：

1. 从数据库获取数据，保存到对象内部
2. 逐个填入到QTableWidgetItem

编辑数据：

1. 手动获取QTableWidgetItem的编辑信号，然后获取新值并保存到对象内部
2. 通过sql写入到数据库

假如某一个操作出现错误，就会导致内存和数据库的数据不一致，也就是数据不同步，在复杂交互中这是难以调试的，且这种耦合性导致单元测试更复杂。