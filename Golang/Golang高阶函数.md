## 定义
高阶函数是接收函数作为参数或返回函数作为输出的函数。

高阶函数是对其他函数进行操作的函数，要么将它们作为参数，要么返回它们。

## 举例
### 函数作为参数
```golang
package main

import "fmt"

func sum(x, y int) int {
	return x + y
}

func process(x int, y int, f func(int, int) int) int {
	return f(x, y)
}

func main() {
	x, y := 1, 2
	fmt.Println(process(x, y, sum))
}
```
输出结果
```
3
```

### 函数作为返回值
```golang
package main

import "fmt"

func addPrefix(str string) string {
	return "prefix_" + str
}

func addSuffix(str string) string {
	return str + "_suffix"
}

func process(idx int) func(string) string {
	switch idx {
	case 1:
		return addPrefix
	case 2:
		return addSuffix
	default:
		return addPrefix
	}
}

func main() {
	need_prefix := []string{"aaa", "bbb", "ccc"}
	need_suffix := []string{"AAA", "BBB", "CCC"}

	prefix_f := process(1)
	suffix_f := process(2)

	for i, v := range need_prefix {
		need_prefix[i] = prefix_f(v)
	}
	for i, v := range need_suffix {
		need_suffix[i] = suffix_f(v)
	}

	fmt.Println("need_prefix:", need_prefix)
	fmt.Println("need_suffix:", need_suffix)
}
```
输出结果
```golang
need_prefix: [prefix_aaa prefix_bbb prefix_ccc]
need_suffix: [AAA_suffix BBB_suffix CCC_suffix]
```

### 两者结合起来
`衣服，交通工具，水果分类`
#### 定义一个结构体
```golang
type Commodity struct {
	Name string
	Type string
}
type Cds []*Commodity
```
#### 自定义结构体的String()
先看一下没有自定义结构体的String()，打印出来的结果
```golang
[0xc0000ba000 0xc0000ba020 0xc0000ba040 0xc0000ba060 0xc0000ba080 0xc0000ba0a0]
map[clothes:[] fruit:[] others:[] transportation:[]]
map[clothes:[0xc0000ba080 0xc0000ba0a0] fruit:[0xc0000ba000 0xc0000ba020] others:[] transportation:[0xc0000ba040 0xc0000ba060]]
all fruit: [0xc0000ba000 0xc0000ba020]
```
全都是地址，所以我们需要实现自定义结构体的String()
```golang
func (cd *Commodity) String() string {
	return cd.Type + "," + cd.Name
}

func (cds Cds) String() string {
	var result string
	for _, v := range cds {
		// result = append(result, v.String()...)
		result += v.String() + " | "
	}

	return result
}
```
再看下打印结果,顺眼多了
```golang
fruit,apple | fruit,banana | transportation,car | transportation,bike | clothes,T-shirt | clothes,skirt | 
map[clothes: fruit: others: transportation:]
map[clothes:clothes,T-shirt | clothes,skirt |  fruit:fruit,apple | fruit,banana |  others: transportation:transportation,car | transportation,bike | ]
all fruit: fruit,apple | fruit,banana | 
```

定一个函数，参数是用来处理每一个结构体函数，这样可以省去我们多次的`for`遍历
```golang
func (cds Cds) process(f func(cd *Commodity)) {
	for _, v := range cds {
		f(v)
	}
}
```
正常情况下我们的输入是一串没有区分类别的数据，这种情况下我们肯定是需要去做分类的，所以我们定义个自动分类的函数
```golang
func classifier(types []string) (func(cd *Commodity), map[string]Cds) {
	result := make(map[string]Cds)

	for _, v := range types {
		result[v] = make(Cds, 0)
	}
	result["others"] = make(Cds, 0)

	appender := func(cd *Commodity) {
		if _, ok := result[cd.Type]; ok {
			result[cd.Type] = append(result[cd.Type], cd)
		} else {
			result["others"] = append(result["others"], cd)
		}
	}

	return appender, result
}

```
除了分类后，我们有时候可能需要在一大堆未分类的数据中找到我们需要的某一种类型，所以我们还需要定义一个查找函数
```golang
func (cds Cds) findType(f func(cd *Commodity) bool) Cds {
	result := make(Cds, 0)

	cds.process(func(c *Commodity) {
		if f(c) {
			result = append(result, c)
		}
	})
	return result
}

```
完整代码
```golang
package main

import "fmt"

type Commodity struct {
	Name string
	Type string
}

type Cds []*Commodity

func (cd *Commodity) String() string {
	return cd.Type + "," + cd.Name
}

func (cds Cds) String() string {
	var result string
	for _, v := range cds {
		// result = append(result, v.String()...)
		result += v.String() + " | "
	}

	return result
}

func main() {
	fruit1 := Commodity{"apple", "fruit"}
	fruit2 := Commodity{"banana", "fruit"}
	transportation1 := Commodity{"car", "transportation"}
	transportation2 := Commodity{"bike", "transportation"}
	clothes1 := Commodity{"T-shirt", "clothes"}
	clothes2 := Commodity{"skirt", "clothes"}

	all_commodity := Cds([]*Commodity{&fruit1, &fruit2,
		&transportation1, &transportation2,
		&clothes1, &clothes2})

	fmt.Println(all_commodity)

	types := []string{"fruit", "transportation", "clothes"}
	appender, cds := classifier(types)
	fmt.Println(cds)
	all_commodity.process(appender)
	fmt.Println(cds)

	all_fruit := all_commodity.findType(func(cd *Commodity) bool {
		return cd.Type == "fruit"
	})
	fmt.Println("all fruit:", all_fruit)
}

func (cds Cds) process(f func(cd *Commodity)) {
	for _, v := range cds {
		f(v)
	}
}

func (cds Cds) findType(f func(cd *Commodity) bool) Cds {
	result := make(Cds, 0)

	cds.process(func(c *Commodity) {
		if f(c) {
			result = append(result, c)
		}
	})
	return result
}

func classifier(types []string) (func(cd *Commodity), map[string]Cds) {
	result := make(map[string]Cds)

	for _, v := range types {
		result[v] = make(Cds, 0)
	}
	result["others"] = make(Cds, 0)

	appender := func(cd *Commodity) {
		if _, ok := result[cd.Type]; ok {
			result[cd.Type] = append(result[cd.Type], cd)
		} else {
			result["others"] = append(result["others"], cd)
		}
	}

	return appender, result
}
```
输出结果
```
fruit,apple | fruit,banana | transportation,car | transportation,bike | clothes,T-shirt | clothes,skirt | 
map[clothes: fruit: others: transportation:]
map[clothes:clothes,T-shirt | clothes,skirt |  fruit:fruit,apple | fruit,banana |  others: transportation:transportation,car | transportation,bike | ]
all fruit: fruit,apple | fruit,banana | 
```
