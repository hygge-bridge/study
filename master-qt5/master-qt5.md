## Dividing Your Project and Ruling Your Code

### Designing a maintainable project

设置可维护项目首先需要将其分解成多个清晰被定义的模块，常用方式为：将engine与ui分离。如qt项目，分解成core + desktop

让每一层都有单一职责

### Defining data classes

Album类没有包含vector<Picture>，好处：

1. 加载album无需潜在加载pictures
2. 用户无需考虑何时加载pictures？是否加载部分？还是加载全部？
3. 解耦后，用户在想要图片时，就知道他们必须显示加载图片。

### Storing your data in a database

数据库层会被多个地方使用，所以需要一个单一的入口点。这个单例类负责打开连接，然后把这个连接借给其他类。（也就是其他类引用它）

单例模式，但是将构造函数设置为protected，可以支持多态单例

使用前置声明避免用户包含不必要的依赖，我的库应该是一个黑盒子。

crud操作放到数据库管理类会导致类的急剧膨胀，所以每个data类需要有一个单独的database类（dao），负责对应的crud操作。

databasemanager包含一个public const dao，public为了方便调用，const为了避免用户破坏数据，副作用就是所有暴露的接口都必须是const方法。不用namespace的原因是，使用一个class可以保存一个database的引用，更加方便。

使用sqlquery的prepare()避免sql注入，而且代码可读性也更强

保持const正确性，从而告知用户这个参数是否会被修改。（引用和指针需要考虑，对于值传递其实无所谓）

如果dao太多，对于databasemanager也是一个冗余，可以考虑一个dao的抽象类，然后virtual bool init（）通过map<string, const dao>来访问dao和初始化dao。
