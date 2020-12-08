# Implementation notes

## IR

暂且先用string去存IR，先不管那么多，等optimization的时候再去考虑是不是要用更牛逼的

## Symbol table
需要在运行的时候重新构建symbol table，而不是用sematic analyzer生成好的symbol table

## t v Problem
1. 需要保存全局的state来控制t v的后缀数大小，避免重复
2. hash map以operator为key，以对应的t为value，方便查找一样的值
3. t可以随意生成，v只有在面对变量的时候才可以使用，最好一个变量就一个v
4. 欸，那operator为key用来存t，variable为key用来存v，是不是更加合理一些(<op, l, r> / <=, variable, "">)

## READ WRITE function

1. Invoke is different from normal function (without CALL)
2. READ t1: read console value into t1
3. WRITE t3: write t3 value to console
4. Problem list 2.
5. 需要改scanner.l, parser.y
    1. 增加解析条目 （scanner.l）
    2. 增加keyword （parser.y）
    3. 把对应的keyword加入产生式Exp中
    4. 加入symbol table的初试化插入read 和 write function
        1. read: ret: int,  param: null, 
        2. write: ret int, param: int
6. 具体实现
    1. 读取到read函数，使用新t接受读取，生成对应的key value插入op表
    2. 读取到write函数，如果是常数，用新t生成常数再写入。如果是变量，就用对应生成的variable（注意function调用）
    
## Exp的实现（感觉超级麻烦）文档已经列出了一大部分了
1. Exp1 Assign Exp2 (not conditional)
    （不考虑给数组或结构体赋值的情况） 
    in: translate_Exp(Exp, place)
    ```c
    variable = symTab.lookup(Exp1.ID);
    ExpVisitor exp2.visit(Exp2);
    appendCode("variable.name := exp2.store_in"); // variable.name 就是v1
    this.store_in = exp2.store_in
    ```
    eg:
    ```c
    int a;
    a = 1 + 2;
    
    v1 := #1 + #2;
    ```
    ```c
    int a, i = 1;
    a = i + 1;
    
    v1 = #1;
    v2 = v1 + #1;
    ```
    哎呀，先不管这种最优的情况，先按照文档把通用的弄好
    ```c
    variable = symTab.lookup(Exp1.ID);
    tp = new_t();
    ExpVisitor exp2.translate_Exp(Exp2, tp);
    appendCode("variable.name := tp"); // variable.name 就是v1
    appendCode("place := variable.name");
    ```
2. Exp1 AND Exp2 (conditional)
    in: translate_cond_Exp(Exp, label_t, label_f)
    ```c
    label_1 = new_label()
    code_exp1 = translate_cond_Exp(Exp1, label_1, label_f)
    appendCode(code_exp1)
    appendCode("LABEL label_1")
    code_exp2 = translate_cond_Exp(Exp2, label_t, label_f)
    appendCode(code_exp2)
    ```
3. Exp1 OR Exp2 (conditional)
    in: translate_cond_Exp(Exp, label_t, label_f)
    ```c
    label_1 = new_label()
    code_exp1 = translate_cond_Exp(Exp1, label_t, label_1)
    appendCode(code_exp1)
    appendCode("LABEL label_1")
    code_exp2 = translate_cond_Exp(Exp2, label_t, label_f)
    appendCode(code_exp2)
    ```
4. Exp1 LT Exp2 (conditional) LE GE GT NE EQ
    in: translate_cond_Exp(Exp, label_t, label_f)
    ```c
    t1 = new_t();
    t2 = new_t();
    code_exp1 = translate_exp(Exp1, t1);
    code_exp2 = translate_exp(Exp2, t2);
    appendCode(code_exp1)
    appendCode(code_exp2)
    appendCode("IF t1 < t2 GOTO label_t")
    appendCode("GOTO label_f")
    ```
5. Exp1 PLUS Exp2 (non-conditional) MUL DIV MINUS
    in: translate_Exp(Exp, place)
    ```c
    t1 = new_t()
    t2 = new_t()
    code_exp1 = translate_exp(Exp1, t1);
    code_exp2 = translate_exp(Exp2, t2);
    appendCode(code_exp1)
    appendCode(code_exp2)
    appendCode("place := t1 + t2")
    ```
6. LP Exp RP (non-conditional / conditional)
    in: translate_Exp(Exp, place)  
        translate_cond_Exp(Exp, label_t, label_f)
    ```c
    translate_Exp(Exp, place):
        translate_Exp(Exp, place)
    
    translate_cond_Exp(Exp, label_t, label_f):
        translate_Exp(Exp, label_t, label_f)
    ```
        
7. MINUS Exp (non-conditional)
    in: translate_Exp(Exp, place)
    ```c
    tp = new_t();
    code_exp = translate_Exp(Exp, tp);
    appendCode(code_exp);
    appendCode("place := #0 - tp")
    ```
8. NOT Exp (conditional)
    in: translate_cond_Exp(Exp, label_t, label_f)
    ```c
    translate_cond_Exp(Exp, label_f, label_t);
    ```

## Problem list:
1. tags: 优化相关，实现相关
    从不复用寄存器的值会不会有什么问题，比如（根本矛盾应该在使用的时候，是否通过临时变量拿变量而不是直接用已经放在寄存器内的值）  
    ```c
    int a = -1;
    write(a);
    
    t1 := #1
    v1 := #0 - t1
    WRITE v1
    ```
    答：应该不会有什么问题，但是对于performance是一个影响，书上是用<op, l, r>这样的hash函数来解决的，在这里应该是{<=, a, ""> = "v1"}来解决的，表示a赋值的寄存器是v1 
    
2. tags: 优化相关，实现相关
   ```c
   int n = read();
   ```
   按照老师的样例应该是
   ```
   READ t1
   v1 := t1
   ```
   不知道可不可以直接READ v1
   
   于是就有两种实现方法  
   1. 只要看到Read function，就生成一个t变量去承接值（这个t变量key是唯一的），后续使用ASSIGN的步骤  
   2. 看到Read function，先不急着生成代码，如果后续还有算数操作就先用t，如果是类似 int n = read()的操作，可以直接用对应的变量去承接值
