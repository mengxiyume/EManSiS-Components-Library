- [**如何简单使用**](#如何简单使用)
  - [继承'Atom'类](#继承atom类)
  - [在派生类重写纯虚函数](#在派生类重写纯虚函数)
    - [重写'stopper()'](#重写stopper)
    - [重写'go()'](#重写go)
  - [使用控制函数对象控制计算流程](#使用控制函数对象控制计算流程)
    - [控制函数原型](#控制函数原型)
    - [三种控制函数](#三种控制函数)
      - [1.初始化控制函数](#1初始化控制函数)
      - [2.计算控制函数](#2计算控制函数)
      - [3.后处理操作函数](#3后处理操作函数)
    - [如何使用控制函数](#如何使用控制函数)
      - [1.使用构造函数传参传入控制函数对象](#1使用构造函数传参传入控制函数对象)
      - [2.使用setter函数传入控制函数对象](#2使用setter函数传入控制函数对象)
  - [实例化派生类](#实例化派生类)
  - [调用派生类对象的函数'go()'](#调用派生类对象的函数go)
  - [调用派生类对象的函数'cache()'获取计算结果](#调用派生类对象的函数cache获取计算结果)
- [**进阶用法**](#进阶用法)

# **如何简单使用**

---

## 继承'Atom'类

```cpp
class Example : public emansis::atom::Atom { /*code*/ };
```

## 在派生类重写纯虚函数

### 重写'stopper()'

```cpp
//stopper的返回值类型
/// @brief      结束状态
enum state_stopper {
    state_stop      = false,
    state_continue  = true
};
```

```cpp
public:
//基类的stopper是一个无参中间函数，通过它调用你的函数来进行控制
virtual state_stopper stopper() { 
    //这里调用你自己的stopper
    return stopper(conter_stopper);
}
private:
/// @brief 停止计算计数器 
int conter_stopper = 0;

/// @brief          停止器
/// @param conter   计数器的引用
/// @return         应该停止时返回Atom::state_stopper::state_stop，否则返回Atom::state_stopper::state_continue
state_stopper stopper(int& conter) { return --conter_stopper <= 0 ? state_stop : state_continue; }
```

### 重写'go()'

写入数据计算与处理的代码
调用'goRun()'函数进行处理

```cpp
public:
/// @brief 继承纯虚函数go
virtual void go () {
    //进行一些运行前操作
    setConter_stopper(3);
    //调用goRun进行运算
    goRun();
    //进行运算后操作如输出
}
```

## 使用控制函数对象控制计算流程

### 控制函数原型

```cpp
typedef std::function<void()(Precision_Type&& cache)> Proc;
/*
* void proc(Precisison_Type&& cache) {
*     //processing...
* }
* [](Precision_Type&& cache)->void {
*     //processing...
* };
*/
```

### 三种控制函数

#### 1.初始化控制函数

```cpp
//进行初始化操作，对cache引用参数进行初始刷写
initializer (Proc& newInitializer);
```

#### 2.计算控制函数

```cpp
//进行计算操作，对cache引用参数进行计算与更改
computation (Proc& newComputation);
```

#### 3.后处理操作函数

```cpp
//进行后处理操作
after       (Proc& newAfterProc);
//对cache引用参数进行补差与再计算
//或者进行其他与cache引用参数无关的外部操作
```

### 如何使用控制函数

#### 1.使用构造函数传参传入控制函数对象

```cpp
Example() : Atom(initProc_1, computProc_1) { }
```

#### 2.使用setter函数传入控制函数对象

```cpp
//对应函数在介绍时有原型介绍
initializer(const_cast<Proc&>(initProc));
computation(const_cast<Proc&>(computProc));
```

## 实例化派生类

```cpp
Example e1;
```

## 调用派生类对象的函数'go()'

```cpp
e1.go();
```

## 调用派生类对象的函数'cache()'获取计算结果

```cpp
std::cout << cache() << std::endl;
```

---

# **进阶用法**

---

通过lambda捕获列表传入额外参数

//TODO:还没写完