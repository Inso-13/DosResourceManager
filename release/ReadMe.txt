1.架构 MVC
M model 数据结构 IFile IFileNode(Node.c) IEvent(Event.c) IFileNodePointer
    view -> 设置event push入栈 -> main 查找event -> 激活槽函数pfun()【通过control调用diry.c】
V view 视图 view0 view1(view.c)
C control 控制器(active.c)


Base.c  IQuit() 退出
