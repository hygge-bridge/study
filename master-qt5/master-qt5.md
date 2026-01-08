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

### Protecting your code with a smart pointer

使用new构造，如果后续代码发生了异常，就可能导致没有delete。然而使用try - catch的话，会导致代码非常臃肿。其实上述的核心问题是：不确定谁拥有这个指针的拥有权。比如谁负责销毁指针，通过参数传递给函数时，是调用者拥有还是被调用者拥有指针。

解决方法：通过简单的模版语义显示确定指针的拥有权（智能指针）。

- unique_ptr：只有一个用户拥有拥有权
- shared_ptr：多个用户共享拥有权
- weak_ptr：用户没有拥有权

注意：智能指针分配在栈上，让其出作用域自动析构。

unique_ptr好处（其余类似）：

1. 用户无需担心指针的声明周期，智能指针的实现会自动处理好内存的分配和析构的。
2. 在编译时已经显示制定了指针的拥有权，同行开发者一眼就知道谁拥有这个指针的拥有权。
3. 由于c++支持操作符重载，所以用户可以如同使用普通指针一样使用智能指针。
4. 如果要转移拥有权，使用std::move即可。void bar(std::unique_ptr<Album>& barAlbum)就无需move因为这是引用，没有占用拥有权。而使用裸指针，则一般就是void bar(Album& barAlbum)，调用者需要使用bar(*album)。智能指针减少了解引用`*`·的使用
5. 轻量，额外开销小。

shared_ptr：

使用引用计数，当引用同一对象时加1，出作用域-1，计数为0则析构

weak_ptr：

显示指定当前是用户，而不是拥有者。如下：

```
void bar(std::weak_ptr<Album> barAlbum) 
{ 
   qDebug() << "Album name" << barAlbum->name(); 
} // ref counter = 1 
void foo() 
{ 
    std::shared_ptr<Album> album(new Album()); // ref counter = 1 
    bar(std::weak_ptr<Album>(album)); // ref counter = 1 
} // ref counter = 0
```

究极好处：

1. 处理悬挂指针
2. 对于不需要保留强引用的场景如缓存（不适用shared_ptr是为了避免生命周期延长），使用weak_ptr就可以知道对象是否被析构了。使用裸指针就无法确定指针是否有效，比如其他人delete了但是没有将指针置空，当前用户还以为是有效指针。

由于C++标准没有规定函数参数的求值顺序，如foo(new Album(), new Picture())，可能先new两个，在构造unqiue_ptr。这就会导致如果后者抛出异常，那么album就内存泄漏了。make_unique解决这个问题，这会强制创建一个unique_ptr再创建第二个。

注意：qt容器重载了拷贝运算符。所以unique_ptr的唯一性会被打破，要用vector<unique_ptr>
