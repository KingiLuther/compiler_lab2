## TeaPL 语法

每个程序由变量声明、函数声明、函数定义和注释组成。

/////
```
program := (varDeclStmt | structDef | fnDeclStmt | fnDef | comment | < ; >)*
```

### 基本标识符、值、表达式和赋值

每个标识符以字母开头，只包含字母和数字，例如，alice、a0。

```
id := [a-zA-Z][a-zA-Z0-9]*
```

TeaPL 允许整数，例如，123。

```
num := [1-9][0-9]* | 0
```

**算术表达式**

表达式由标识符、值和运算符组成，例如，1+2、a*(b+c)。为了简化，不支持一元运算符，例如++、+=。

```
arithExpr := arithExpr arithBiOp arithExpr | exprUnit
exprUnit := num | id | < ( > arithExpr < ) > | fnCall | id < [ > id | num < ] > | id < . > id | arithUOp exprUnit
arithBiOp := < + > | < - > | < * > | < / >
arithUOp := < - >
```

**条件表达式**

```
boolExpr := boolExpr boolBiOp boolUnit | boolUnit
boolUnit := exprUnit comOp exprUnit | < ( > boolExpr < ) > | boolUOp boolUnit // 限制比较运算符的操作数为 exprUnit，而不是 rightVal，以避免混淆优先级。
boolBiOp := < && > | < || >
boolUOp := < ! >
comOp := < > > | < < > | < >= > | < <= > | < == > | < != >
```

**赋值**

不限制左值或右值可以是赋值。

```
assignStmt := leftVal < = > rightVal < ; >
leftVal := id | id < [ > id | num < ] > | id < . > id
rightVal := arithExpr | boolExpr
```

**函数调用**

```
fnCall := id < ( > rightVal (< , > rightVal)* | ϵ < ) >
```

### 变量声明

TeaPL 允许一次声明一个变量，它可以是原始类型或数组类型。开发者可以在声明时初始化变量。例如，它支持以下变量声明示例。

**原始类型**

```
let a:int; // 声明一个 int 类型的变量；类型字段可以忽略。
let b:int = 0; // 声明一个 int 类型的变量并初始化为 0。
```

**一维数组**

```
let c[10]:int; // 声明一个整数数组变量。
let d[10]:int = {0}; // 声明一个整数数组变量并初始化为零。
```

语法定义如下。

```
varDeclStmt := < let > (varDecl | varDef) < ; >
varDecl := id < : > type |  id < [ > num < ] >< : > type | id |  id < [ > num < ] >
varDef :=  id < : > type < = > rightVal | id < = > rightVal  // 原始类型
         | id < [ > num < ] >< : > type < = > < { > rightVal (< , > rightVal)* | ϵ < } > | id < [ > num < ] > < = > < { > rightVal (< , > rightVal)* | ϵ < } > // 数组
type := nativeType | structType
nativeType := < int >
structType := id
```

### 定义新结构

开发者可以使用保留关键字 `struct` 来定义新的自定义类型，例如，

```
struct MyStruct {
    node:int,
    len:int
}
```

语法定义如下。

```
structDef := < struct > id < { > (varDecl) (< , > varDecl)* < } >
```

### 函数声明和定义

每个函数声明以关键字 `fn` 开始。

```
fn foo(a:int, b:int)->int;
fn foo();
```

语法定义如下。

```
fnDeclStmt := fnDecl < ; >
fnDecl := < fn > id < ( > paramDecl < ) > // 无返回值
        | < fn > id < ( > paramDecl < ) > < -> > type // 有返回值
paramDecl := varDecl (< , > varDecl)* | ϵ
```

### 函数定义

我们还可以在声明函数的同时定义它。

```
fn foo(a:int, b:int)->int {
    return a + b;
}
```

语法规则如下。

```
fnDef := fnDecl codeBlock
codeBlock :=  < { > (varDeclStmt | assignStmt | callStmt | ifStmt | whileStmt | returnStmt | continueStmt | breakStmt | < ; > )* < } >
returnStmt ：= < ret > rightVal < ; >
continueStmt := < continue > < ; >
breakStmt := < break > < ; >
```

我们已经定义了 `varDeclStmt` 和 `assignStmt` 的语法。`callStmt` 只是以分号终止的函数调用。

```
callStmt := fnCall < ; >
```

接下来，我们定义每个其余的语句类型的语法。

### 控制流

**If-Else 语句**

条件应该用成对的括号括起来，我们进一步限制了语句体应该在成对的大括号内。下面是一个示例。

```
if (x >0) {
    if (y >0) {
        x++;
    }
    else {
        x--;
    }
} else {

}
```

此外，我们限制条件表达式为显式的逻辑操作，例如 x > 0；不允许隐式表达式，如 x，这意味着。我们定义语法如下。

```
ifStmt := < if > < ( > boolExpr < ) > codeBlock ( < else > codeBlock | ϵ )
```

**While 语句**

用于表示复杂循环。

示例：

```
while (x  > 0) {
    x--;
}
```

定义如下：

```
whileStmt := < while > < ( > boolExpr < ) > codeBlock


```

### 代码注释

与大多数编程语言类似，TeaPL 允许使用 "//" 进行单行注释，使用 "/* ... */" 进行多行注释。

```
int a = 0; // 这是一行注释。

/*
    特性：这是一个多行注释
*/
fn foo(){
    ...
}
```

```
comment :=  < // > _* | < /* > _* < */ >
```
