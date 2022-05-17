## 函数
函数是基本的代码块，通常我们会将一个功能封装成一个函数，方便我们调用，同时避免代码臃肿复杂。

### 函数的基本格式
```go
func TestFunc(a int, b string) (int, string) {
    // body
}
```
函数基本在每种语言都经常使用，所以感觉没什么记录的。

## 方法
方法与对象绑定，简单的来讲只是将对象传递给函数使其成为一种特殊(只属于该对象)的函数，因为`Golang`是没有`类`这个概念(在`Golang`里，`结构体`是`类`的简化版)，所以也可以将方法理解为`类的成员函数`，但需要注意的是，在`Golang`里几乎所有数据类型都可以与方法绑定。

### 方法的基本格式
```go
func (a objectType) TestMethod(a int, b string) (int, string) {
    // body
}
```

先定一个结构体
```go
type Test1 struct {
    aaa int
    bbb int
}

func (t Test1) String() string {
    res := fmt.Sprintf("aaa:%d, bbb:%d", t.aaa, t.bbb)
    return res
}
```
### 指针或者值作为绑定对象的区别
指针和值都可以绑定方法，并且我们不需要手动区分，这是因为`Golang`会自动解引用。

#### 只读对象的内部变量
指针和值是没有区别的，下面的代码分别使用了值和指针绑定:
```go
func (t *Test1) Sum() int {
    return t.aaa + t.bbb
}

func (t Test1) Mul() int {
    return t.aaa * t.bbb
}
```
然后我们定义一个对象来分别调用上面的两个方法:
```go
ttt := Test1{aaa: 5, bbb: 2}
fmt.Println("Sum:", ttt.Sum())
fmt.Println("Mul:", ttt.Mul())

// output:
// Sum: 7
// Mul: 10
```

#### 修改对象的内部变量
如果需要修改对象的内部变量，就必须在对象的指针类型上定义该方法，下面的代码分别使用了值和指针绑定:
```go
func (t *Test1) modifyByAddr(a int) {
    t.aaa = a
}

func (t Test1) modifyByValue(a int) {
    t.aaa = a
}
```
然后我们定义一个对象来分别调用上面的两个方法:
```go
fmt.Println("old value:", ttt)
ttt.modifyByValue(222)
fmt.Println("modifyByValue:", ttt)
ttt.modifyByAddr(111)
fmt.Println("modifyByAddr:", ttt)

// output
// old value: aaa:5, bbb:2
// modifyByValue: aaa:5, bbb:2
// modifyByAddr: aaa:111, bbb:2
```

### 函数与方法的区别
通过上面的例子来说明
- `函数`将变量当做参数传入`Test1Sum(ttt)`
- `方法`是被变量调用`ttt.Mul()`和`ttt.Sum()`

## 接口
接口定义了一组方法，但这些方法并没有实现，使用该接口的前提是对象实现了接口内部的方法，这里需要特别注意，对象必须实现接口里的所以方法，或者会报错。
下面我们定义了一个接口，包含两个方法，其中`modify(int, int)`我们没有在结构体`Test1`里实现。
```go
type TestInterface interface {
    Sum() int
    modify(int, int)
}
```

我们将对象赋给接口的时候就会报错，代码如下：
```go
ttt := new(Test1)
ttt.aaa = 5
ttt.bbb = 2

var test1Face TestInterface
test1Face = ttt
```
这时候就会报错如下信息:
```shell
src/test.go:44:14: cannot use ttt (variable of type Test1) as type TestInterface in assignment:
    Test1 does not implement TestInterface (Sum method has pointer receiver)
```

## 完整代码
```go
package main

import "fmt"

type TestInterface interface {
    Sum() int
    modify(int, int)
}

type Test1 struct {
    aaa int
    bbb int
}

func (t *Test1) modify(a, b int) {
    t.aaa = a
    t.bbb = b
}

func (t *Test1) Sum() int {
    return t.aaa + t.bbb
}

func (t Test1) Mul() int {
    return t.aaa * t.bbb
}

func Test1Sum(t *Test1) int {
    return t.aaa + t.bbb
}

func (t *Test1) modifyByAddr(a int) {
    t.aaa = a
}

func (t Test1) modifyByValue(a int) {
    t.aaa = a
}

func (t Test1) String() string {
    res := fmt.Sprintf("aaa:%d, bbb:%d", t.aaa, t.bbb)
    return res
}

func main() {
    ttt := new(Test1)
    ttt.aaa = 5
    ttt.bbb = 2

    var test1Face TestInterface
    test1Face = ttt
    test1Face.modify(123, 456)

    fmt.Println("Sum:", ttt.Sum())
    fmt.Println("Mul:", ttt.Mul())
    fmt.Println("Test1Sum:", Test1Sum(ttt))

    fmt.Println("old value:", ttt)
    ttt.modifyByValue(222)
    fmt.Println("modifyByValue:", ttt)
    ttt.modifyByAddr(111)
    fmt.Println("modifyByAddr:", ttt)
}

```