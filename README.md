# 数据结构与算法

数据结构学习，作业代码

## 下载

```bash
    git clone git://github.com/messense/data-structure-learning.git
```
## 编译

```bash
    cd data-structure-learning
    make build
```

## 清理

```bash
    cd data-structure-learning
    make clean
```

## 测试

首先编译，然后
```bash
    cd data-structure-learning/bin
```
依次执行生成的可执行文件进行测试，如执行helloworld：`./helloworld`

## 项目文件结构说明

### src/commonlist.h

定义公用的链表结构体和链表节点结构体

### src/iterator.h & src/iterator.c

定义并实现通用的链表迭代器，使用方法(以linklist为例)
```c
    #include "iterator.h"
    #include "linklist.h"

    //先构造出链表
    list *list;
    list = malloc(sizeof(*list));
    //接着存储些数据，略
    //然后获取迭代器
    iterator *iter = iterator_create(list);
    //使用迭代器遍历节点
    Node *node;
    while((node = iterator_next(iter)) != NULL) {
    	//do something here
    }
    //销毁迭代器
    iterator_release(iter); //也可以简单地 free(iter);
    //销毁链表
    list_release(list);
```